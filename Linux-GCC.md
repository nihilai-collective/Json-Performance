# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-43-generic using the GCC 16.2.1 compiler).  

Latest Results: (Nov 17, 2026)
#### Using the following commits:
----
| Jsonifier: [79b3e67](https://github.com/nihilai-collective/Jsonifier/commit/79b3e67)  
| Glaze: [a53ddd59](https://github.com/stephenberry/glaze/commit/a53ddd59)  
| simdjson: [36c5b3cfc](https://github.com/simdjson/simdjson/commit/36c5b3cfc)  

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
*Environment generated via BenchmarkSuite commit: [71afc62](https://github.com/nihilai-collective/benchmarksuite/commit/71afc62)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2219.15 | 0.247562 | 751.467ms | 905 | 320 | 296.649 | 388.922 | 0.0425675 | 2.56597 | 11.7072 | 1.86961 | 0.00110497 | 4.14365e-05 | 3.45304e-06 | 1(Win) | true |
| Glaze | 1816.24 | 0.0495966 | 769.214ms | 905 | 4890 | 271.622 | 475.199 | 0.0806155 | 3.08096 | 14.032 | 1.94917 | 0.00110949 | 5.73953e-05 | 1.10723e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 615.931 | 0.0677044 | 852.757ms | 905 | 4890 | 4401.25 | 1401.25 | 0.367511 | 8.52582 | 42.8906 | 4.43094 | 0.00848049 | 0.000152753 | 2.44043e-05 | 3(Loss) | true |
| simdjson (ondemand) | 229.482 | 0.122922 | 1099.1ms | 905 | 1280 | 27357 | 3760.97 | 0.021225 | 22.5461 | 105.526 | 9.82431 | 0.0767559 | 0.000154523 | 6.21547e-05 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2601.7 | 0.0847463 | 744.056ms | 905 | 1280 | 101.166 | 331.735 | 0.12096 | 2.22573 | 11.0365 | 1.73039 | 0.00111533 | 9.75483e-05 | 8.6326e-07 | 1(Win) | true |
| Glaze | 1888.64 | 0.152964 | 754.623ms | 905 | 4890 | 2389.38 | 456.983 | 0.117053 | 2.9655 | 13.6652 | 2.06519 | 0.00114226 | 3.00534e-05 | 2.71159e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 620.081 | 0.0805868 | 852.295ms | 905 | 4890 | 6152.3 | 1391.88 | 0.123236 | 8.49274 | 42.2144 | 4.29172 | 0.00546475 | 0.000131512 | 2.25966e-05 | 3(Loss) | true |
| simdjson (ondemand) | 223.725 | 0.0873751 | 1103.01ms | 905 | 160 | 1817.87 | 3857.75 | 0.0961423 | 23.0737 | 104.842 | 9.68508 | 0.0916506 | 7.59669e-05 | 0 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1750.9 | 0.501275 | 759.845ms | 905 | 30 | 183.168 | 492.933 | 0.303378 | 3.17937 | 11.0895 | 1.10276 | 0.00445672 | 0 | 0 | 1(Win) | true |
| simdjson (reflection) | 260.054 | 0.0494572 | 1050.98ms | 905 | 2560 | 6897.17 | 3318.84 | 0.129443 | 19.8723 | 94.537 | 21.0276 | 0.0597341 | 0.000124309 | 5.17956e-06 | 2(Loss) | true |
| Glaze | 196.995 | 0.0389734 | 1157.64ms | 905 | 4890 | 14257.1 | 4381.2 | 0.162397 | 26.1306 | 110.857 | 23.4553 | 0.0883289 | 0.000435888 | 0.000180999 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3242.62 | 0.0455158 | 750.843ms | 905 | 2560 | 37.5724 | 266.166 | 0.247119 | 1.83161 | 7.77459 | 0.271823 | 0.00221297 | 3.23722e-05 | 7.76934e-06 | 1(Win) | true |
| simdjson (reflection) | 3142.17 | 0.407954 | 754.167ms | 905 | 40 | 50.225 | 274.675 | 0.00910084 | 1.87624 | 8.44862 | 1.05083 | 0.00110497 | 0.000138122 | 0 | 2(Loss) | true |
| Glaze | 684.763 | 0.0903894 | 848.719ms | 905 | 30 | 38.9379 | 1260.4 | 0.0158655 | 7.76376 | 22.0398 | 3.36685 | 0.00589319 | 0.00014733 | 0 | 3(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1263.45 | 0.0732156 | 853.18ms | 1811 | 320 | 320.535 | 1366.97 | 0.393144 | 4.12948 | 17.862 | 3.63943 | 0.0008369 | 0.000141496 | 4.31391e-05 | 1(Win) | true |
| Glaze | 1075.63 | 0.0510873 | 878.545ms | 1811 | 4890 | 3290.41 | 1605.67 | 0.115 | 4.87146 | 25.5257 | 3.72336 | 0.000952371 | 9.32723e-05 | 2.66492e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 710.81 | 0.142713 | 967.545ms | 1811 | 160 | 1923.86 | 2429.77 | 0.0501843 | 7.36616 | 33.3771 | 5.05577 | 0.00106985 | 8.62783e-05 | 2.41579e-05 | 3(Loss) | true |
| simdjson (ondemand) | 301.94 | 0.0653701 | 1297.23ms | 1811 | 4890 | 68369.5 | 5720.02 | 0.0162397 | 16.9453 | 87.8167 | 11.5422 | 0.00092177 | 0.000123874 | 4.70878e-05 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1401.84 | 0.183819 | 842.435ms | 1811 | 40 | 205.153 | 1232.03 | 0.0682691 | 3.80196 | 16.8459 | 3.40972 | 0.0012286 | 9.66317e-05 | 6.90226e-05 | 1(Win) | true |
| Glaze | 1146.09 | 0.0688399 | 863.743ms | 1811 | 2560 | 2755.01 | 1506.96 | 0.00404391 | 4.57589 | 24.7973 | 3.4804 | 0.000973219 | 7.98074e-05 | 1.2079e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 760.378 | 0.102561 | 954.947ms | 1811 | 2560 | 13892.5 | 2271.38 | 0.0382159 | 6.88684 | 32.3164 | 4.81336 | 0.00167876 | 7.03168e-05 | 3.17073e-05 | 3(Loss) | true |
| simdjson (ondemand) | 305.977 | 0.0684069 | 1289.38ms | 1811 | 1280 | 19084.1 | 5644.56 | 0.111446 | 16.6619 | 86.7305 | 11.2993 | 0.00112809 | 6.81599e-05 | 3.01974e-06 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 355.693 | 0.0641987 | 1254.2ms | 1997 | 40 | 472.626 | 5354.3 | 0.0392054 | 14.5898 | 64.2799 | 11.7476 | 0.00970205 | 0.000112669 | 5.00751e-05 | 1(Win) | true |
| Jsonifier | 335.091 | 0.0646681 | 1232.9ms | 1811 | 1280 | 14220.1 | 5154.13 | 0.12618 | 15.3501 | 64.3871 | 11.2772 | 0.0167328 | 0.000110868 | 3.45113e-05 | 2(Loss) | true |
| Glaze | 318.883 | 0.0843674 | 1258.13ms | 1798 | 640 | 13171.8 | 5377.23 | 0.0407224 | 16.139 | 69.1713 | 11.7558 | 0.0228266 | 0.000104283 | 3.82369e-05 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 826.136 | 0.106651 | 932.536ms | 1811 | 2560 | 12726.4 | 2090.58 | 0.0655526 | 6.34771 | 20.2408 | 1.03424 | 0.000779524 | 5.13356e-05 | 1.72557e-06 | 1(Win) | true |
| Glaze | 650.441 | 0.0797257 | 995.399ms | 1798 | 4890 | 21600.7 | 2636.22 | 0.0654311 | 8.0015 | 26.614 | 2.36263 | 0.000894086 | 8.39378e-05 | 1.46721e-05 | 2(Loss) | true |
| simdjson (reflection) | 649.157 | 0.0496363 | 1032.67ms | 1997 | 2560 | 5428.68 | 2933.78 | 0.00644474 | 8.04124 | 25.2954 | 2.57787 | 0.000905069 | 0.000102693 | 5.06619e-05 | 3(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3383.18 | 0.0622348 | 826.451ms | 3862 | 4890 | 2244.65 | 1088.65 | 0.010941 | 1.5704 | 7.20119 | 0.899016 | 0.000438598 | 4.52206e-05 | 1.202e-05 | 1(Win) | true |
| Glaze | 1761.92 | 0.0315047 | 925.646ms | 3862 | 320 | 138.788 | 2090.38 | 0.0460654 | 2.97944 | 14.6657 | 1.82108 | 0.000564798 | 3.07483e-05 | 4.855e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1634.96 | 0.0515484 | 944.961ms | 3862 | 4890 | 6594 | 2252.71 | 0.0592703 | 3.20202 | 14.8019 | 1.67582 | 0.000397296 | 6.00471e-05 | 2.45166e-05 | 3(Loss) | true |
| simdjson (ondemand) | 732.598 | 0.0312653 | 1225.67ms | 3862 | 4890 | 12081.7 | 5027.44 | 0.0796376 | 7.01389 | 32.3824 | 3.56525 | 0.000835946 | 7.34968e-05 | 3.29359e-05 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3784.3 | 0.078068 | 815.853ms | 3862 | 160 | 92.3679 | 973.256 | 0.154525 | 1.41824 | 6.70637 | 0.786121 | 0.000258933 | 1.4565e-05 | 0 | 1(Win) | true |
| Glaze | 1860.54 | 0.0980786 | 913.416ms | 3862 | 1280 | 4825.1 | 1979.58 | 0.289803 | 2.81691 | 14.1854 | 1.71129 | 0.000300403 | 1.73971e-05 | 1.82062e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1763.07 | 0.0840161 | 926.809ms | 3862 | 1280 | 3942.96 | 2089.03 | 0.0299272 | 2.97191 | 14.3084 | 1.56551 | 0.000261968 | 2.99392e-05 | 7.68708e-06 | 3(Loss) | true |
| simdjson (ondemand) | 749.466 | 0.0416112 | 1209.08ms | 3862 | 1280 | 5352.41 | 4914.28 | 0.042619 | 6.86131 | 31.8708 | 3.45236 | 0.00102703 | 1.88131e-05 | 2.22521e-06 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 997.119 | 0.0701499 | 1088.67ms | 3862 | 1280 | 8594.01 | 3693.73 | 0.0132209 | 5.18354 | 27.1207 | 5.31409 | 0.00706443 | 4.77408e-05 | 5.25958e-06 | 1(Win) | true |
| Jsonifier | 947.58 | 0.093696 | 1106.74ms | 3862 | 80 | 1061.02 | 3886.84 | 0.176887 | 5.49465 | 26.1261 | 5.37002 | 0.00862571 | 5.50233e-05 | 1.29467e-05 | 2(Loss) | true |
| Glaze | 931.306 | 0.0670463 | 1117.82ms | 3862 | 2560 | 17998.2 | 3954.76 | 0.0905287 | 5.57191 | 28.6515 | 5.68799 | 0.00704612 | 9.2245e-05 | 4.31892e-05 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5464.44 | 0.0906526 | 809.081ms | 3862 | 2560 | 955.727 | 674.011 | 0.116008 | 1.0003 | 5.21647 | 0.592439 | 0.000268036 | 2.62979e-05 | 5.76531e-06 | 1(Win) | true |
| simdjson (reflection) | 3985.7 | 0.0523291 | 816.433ms | 3862 | 40 | 9.35321 | 924.075 | 0.229432 | 1.32727 | 6.79208 | 0.533661 | 0.000517866 | 1.29467e-05 | 0 | 2(Loss) | true |
| Glaze | 2742.1 | 0.0700043 | 884.784ms | 3862 | 160 | 141.458 | 1343.16 | 0.0530746 | 1.93562 | 8.25065 | 0.995857 | 0.00469478 | 3.23666e-05 | 0 | 3(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1808.29 | 0.045842 | 1233.66ms | 9578 | 4890 | 26221 | 5051.34 | 0.0539895 | 2.81303 | 13.9978 | 2.68198 | 0.00135734 | 3.77057e-05 | 1.45613e-05 | 1(Win) | true |
| Glaze | 1472.54 | 0.0581166 | 1341.89ms | 9578 | 1280 | 16635 | 6203.07 | 0.0147378 | 3.46997 | 17.5313 | 3.48799 | 0.00159227 | 1.90867e-05 | 2.12075e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1315.75 | 0.0535202 | 1421ms | 9578 | 2560 | 35341 | 6942.27 | 0.079327 | 3.89886 | 18.7683 | 3.06985 | 0.00136972 | 2.4307e-05 | 5.38343e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1299.43 | 0.034052 | 1429.66ms | 9578 | 2560 | 14667.9 | 7029.47 | 0.360956 | 3.93372 | 19.4649 | 2.95344 | 0.00435144 | 2.54082e-05 | 5.62813e-06 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2839.13 | 0.0373472 | 1184.04ms | 9578 | 2560 | 3696.04 | 3217.29 | 0.229172 | 1.80898 | 9.90228 | 1.76373 | 0.0002967 | 2.00655e-05 | 3.26269e-06 | 1(Win) | true |
| Glaze | 2070.92 | 0.0279236 | 1313.64ms | 9578 | 4890 | 7417.78 | 4410.73 | 0.2262 | 2.47567 | 13.3648 | 2.54239 | 0.000203431 | 2.2269e-05 | 3.86451e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1737.54 | 0.059219 | 1386.54ms | 9578 | 640 | 6202.76 | 5257.04 | 0.0756701 | 2.9324 | 14.7119 | 2.15995 | 0.000159382 | 2.186e-05 | 4.07836e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1690.5 | 0.100276 | 1404.39ms | 9578 | 320 | 9394.31 | 5403.3 | 0.324267 | 3.02061 | 15.4449 | 2.05199 | 0.00320657 | 2.41439e-05 | 1.63134e-06 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4298.8 | 0.081951 | 940.944ms | 9578 | 640 | 1940.63 | 2124.85 | 0.246063 | 1.22072 | 5.4691 | 1.10221 | 0.00207556 | 1.5824e-05 | 3.26269e-07 | 1(Win) | true |
| simdjson (reflection) | 4090.61 | 0.0779619 | 944.587ms | 9578 | 2560 | 7758.51 | 2232.99 | 0.454893 | 1.27584 | 6.21549 | 1.15713 | 0.000595073 | 3.69499e-05 | 1.32139e-05 | 2(Loss) | true |
| Glaze | 2116.87 | 0.0397543 | 1147.33ms | 9578 | 2560 | 7533.03 | 4315 | 0.0361334 | 2.4468 | 12.7155 | 2.63771 | 0.00107412 | 3.17296e-05 | 1.17865e-05 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11279.9 | 0.233176 | 825.92ms | 9578 | 80 | 285.233 | 809.788 | 0.0447849 | 0.481082 | 2.23585 | 0.274589 | 0.000779129 | 2.21863e-05 | 9.13552e-06 | 1(Win) | true |
| simdjson (reflection) | 9222.92 | 0.201038 | 845.357ms | 9578 | 320 | 1268.58 | 990.391 | 0.0552486 | 0.572606 | 3.07329 | 0.321257 | 0.000110279 | 1.01143e-05 | 0 | 2(Loss) | true |
| Glaze | 5909.47 | 0.0649322 | 895.127ms | 9578 | 2560 | 2578.78 | 1545.71 | 0.0488767 | 0.890906 | 4.44805 | 0.7202 | 0.000151062 | 2.02286e-05 | 7.17791e-06 | 3(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3528 | 0.227373 | 827.564ms | 3873 | 30 | 169.995 | 1046.93 | 0.079661 | 1.51658 | 6.92332 | 0.830364 | 0.000714347 | 3.44264e-05 | 0 | 1(Win) | true |
| Glaze | 1902.04 | 0.117412 | 911.447ms | 3873 | 30 | 155.955 | 1941.9 | 0.0188783 | 2.72223 | 12.8533 | 1.7906 | 0.000516396 | 2.58198e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 1623.05 | 0.0791694 | 955.888ms | 3873 | 160 | 519.356 | 2275.7 | 0.133297 | 3.23084 | 14.5771 | 1.55797 | 0.00148141 | 4.84121e-05 | 1.45236e-05 | 3(Loss) | true |
| simdjson (ondemand) | 723.927 | 0.0634051 | 1241.6ms | 3873 | 1280 | 13395.6 | 5102.15 | 0.160637 | 7.0395 | 32.0147 | 3.66357 | 0.00507177 | 0.000123653 | 6.29357e-05 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3883.87 | 0.0765599 | 810.757ms | 3873 | 4890 | 2592.25 | 951.004 | 0.00462186 | 1.37731 | 6.4898 | 0.731475 | 0.000266382 | 5.78701e-05 | 2.02229e-05 | 1(Win) | true |
| Glaze | 2027.17 | 0.0298461 | 897.483ms | 3873 | 1280 | 378.531 | 1822.04 | 0.00321573 | 2.58146 | 12.4219 | 1.69171 | 0.000538181 | 4.4176e-05 | 5.04293e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1702.61 | 0.0494599 | 940.328ms | 3873 | 4890 | 5629.62 | 2169.36 | 0.230769 | 3.03757 | 14.1327 | 1.45908 | 0.00103907 | 5.24844e-05 | 1.22499e-05 | 3(Loss) | true |
| simdjson (ondemand) | 736.28 | 0.0274854 | 1231.35ms | 3873 | 4890 | 9296.58 | 5016.54 | 0.00436347 | 6.91968 | 31.5598 | 3.56468 | 0.00718598 | 7.57169e-05 | 2.6823e-05 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 950.521 | 0.0968843 | 1120.73ms | 3873 | 1280 | 18142.1 | 3885.85 | 0.0168709 | 5.36456 | 24.5474 | 5.13581 | 0.00694128 | 6.87855e-05 | 1.61374e-05 | 1(Win) | true |
| simdjson (reflection) | 902.624 | 0.104251 | 1134.28ms | 3873 | 40 | 727.946 | 4092.05 | 0.0167018 | 5.67413 | 27.488 | 5.36251 | 0.0104376 | 9.68242e-05 | 5.16396e-05 | 2(Loss) | true |
| Glaze | 839.721 | 0.0535818 | 1173.9ms | 3873 | 1280 | 7110 | 4398.58 | 0.0159117 | 6.07322 | 28.8727 | 5.8629 | 0.00653644 | 0.000143623 | 6.59615e-05 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6438.1 | 0.0468326 | 806.713ms | 3873 | 640 | 46.2015 | 573.706 | 0.0413804 | 0.844998 | 3.98502 | 0.476375 | 0.000319116 | 2.33992e-05 | 4.03434e-07 | 1(Win) | true |
| simdjson (reflection) | 3917.38 | 0.127652 | 832.533ms | 3873 | 1280 | 1854.24 | 942.87 | 0.172958 | 1.34415 | 6.77795 | 0.530338 | 0.000590426 | 2.01717e-05 | 2.01717e-06 | 2(Loss) | true |
| Glaze | 2713.62 | 0.0832083 | 886.798ms | 3873 | 80 | 102.617 | 1361.12 | 0.023883 | 1.92424 | 7.8394 | 0.993029 | 0.00422476 | 2.25923e-05 | 3.22747e-06 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1664.77 | 0.0361238 | 6223.11ms | 94653 | 1280 | 491084 | 54222.5 | 0.0538894 | 3.03008 | 13.8341 | 2.46038 | 0.00893498 | 2.46129e-05 | 1.74403e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1446.15 | 0.0509098 | 7032.2ms | 94653 | 640 | 646291 | 62419.8 | 0.0525473 | 3.50108 | 15.6443 | 2.74241 | 0.00958843 | 2.42663e-05 | 1.65242e-05 | 2(Loss) | true |
| simdjson (reflection) | 1408.22 | 0.0156777 | 7161.18ms | 94653 | 4890 | 493856 | 64100.7 | 0.0667013 | 3.57455 | 14.1504 | 2.60997 | 0.00812774 | 1.20449e-05 | 6.18987e-06 | 3(Loss) | true |
| Glaze | 1389.9 | 0.158949 | 7230.46ms | 94653 | 160 | 1.70505e+06 | 64945.8 | 0.00156864 | 3.63258 | 15.5413 | 3.09745 | 0.0155037 | 1.00367e-05 | 5.94276e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1361.93 | 0.074081 | 7366.2ms | 94653 | 640 | 1.54296e+06 | 66279.6 | 0.0259786 | 3.69872 | 14.5333 | 2.90228 | 0.0109176 | 9.13204e-05 | 4.97376e-05 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2551.85 | 0.0628612 | 5539.13ms | 94653 | 320 | 158225 | 35373.6 | 0.120654 | 1.96476 | 9.86479 | 1.56058 | 0.00580568 | 5.97577e-06 | 2.83932e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2067.07 | 0.0295819 | 6374.46ms | 94653 | 4890 | 816054 | 43669.5 | 0.0589885 | 2.43379 | 11.7149 | 1.85192 | 0.00669088 | 8.51242e-06 | 4.79202e-06 | 2(Loss) | true |
| Glaze | 1981.23 | 0.220178 | 6569.64ms | 94653 | 320 | 3.22031e+06 | 45561.6 | 0.0125501 | 2.54151 | 11.754 | 2.2347 | 0.00901319 | 8.28685e-06 | 3.86279e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1924.93 | 0.0217991 | 6667.49ms | 94653 | 1280 | 133759 | 46894.1 | 0.103481 | 2.62833 | 10.6729 | 2.02225 | 0.0072699 | 2.01063e-05 | 1.59547e-05 | 4(Loss) | true |
| simdjson (reflection) | 1827.32 | 0.120787 | 6954.96ms | 94653 | 80 | 284819 | 49399.3 | 0.0614004 | 2.76767 | 11.1051 | 1.90139 | 0.0044263 | 1.67718e-05 | 1.28099e-05 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20277.6 | 0.0239901 | 1182.94ms | 94653 | 4890 | 5577.11 | 4451.62 | 0.0764583 | 0.251048 | 1.20076 | 0.18066 | 3.00398e-05 | 3.92565e-06 | 1.57933e-06 | 1(Win) | true |
| simdjson (reflection) | 13408 | 0.0383926 | 1410.59ms | 94653 | 2560 | 17103.3 | 6732.43 | 0.039894 | 0.379776 | 2.045 | 0.302885 | 6.4091e-05 | 2.60821e-06 | 7.55226e-07 | 2(Loss) | true |
| Glaze | 7823.91 | 0.0312294 | 1901.4ms | 94653 | 4890 | 63483.1 | 11537.5 | 0.0563955 | 0.643762 | 3.47139 | 0.569279 | 6.95404e-05 | 5.60221e-06 | 2.97287e-06 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20553.2 | 0.0547578 | 1178.17ms | 94653 | 640 | 3701.54 | 4391.93 | 0.0276354 | 0.248564 | 1.19515 | 0.179403 | 4.07739e-05 | 2.06346e-06 | 3.30153e-07 | 1(Win) | true |
| simdjson (reflection) | 13488.4 | 0.0326479 | 1404.13ms | 94653 | 2560 | 12220.7 | 6692.26 | 0.0178118 | 0.376903 | 2.03945 | 0.301639 | 3.21899e-05 | 3.59454e-06 | 1.57648e-06 | 2(Loss) | true |
| Glaze | 9303.76 | 0.0433314 | 1712.39ms | 94653 | 1280 | 22623.9 | 9702.33 | 0.126313 | 0.543198 | 3.41879 | 0.557426 | 5.30804e-05 | 2.3771e-06 | 7.92368e-07 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1876.97 | 0.0965532 | 7098.73ms | 124597 | 160 | 597795 | 63306.7 | 0.0396541 | 2.7252 | 11.0253 | 1.98545 | 0.00550038 | 3.36084e-06 | 1.20388e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1833.25 | 0.0473472 | 7222.05ms | 124597 | 640 | 602756 | 64816.6 | 0.0222335 | 2.77482 | 12.2939 | 2.09245 | 0.00838125 | 1.27662e-05 | 9.86932e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1807.45 | 0.0183409 | 7324.12ms | 124597 | 4890 | 710940 | 65741.9 | 0.140243 | 2.8183 | 11.3267 | 2.21134 | 0.00779411 | 1.0345e-05 | 7.17077e-06 | 3(Loss) | true |
| Jsonifier | 1790.96 | 0.0186413 | 7371.83ms | 124597 | 4890 | 748006 | 66347.1 | 0.173142 | 2.84631 | 12.3526 | 2.33607 | 0.00937586 | 1.74567e-05 | 1.38475e-05 | 4(Loss) | true |
| Glaze | 1688.39 | 0.058282 | 7783.79ms | 124597 | 640 | 1.07676e+06 | 70377.6 | 0.0443548 | 3.01408 | 13.7735 | 2.74249 | 0.011224 | 4.40169e-05 | 3.69441e-05 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2625.58 | 0.0277854 | 6535.97ms | 124597 | 2560 | 404799 | 45256.7 | 0.0176704 | 1.91424 | 9.32803 | 1.41992 | 0.00507765 | 1.05371e-05 | 7.53053e-06 | 1(Win) | true |
| simdjson (ondemand) | 2435.87 | 0.127293 | 6900.62ms | 124597 | 80 | 308464 | 48781.4 | 0.0586713 | 2.06772 | 8.45646 | 1.55537 | 0.00567841 | 5.91908e-06 | 2.90938e-06 | 2(Loss) | true |
| Jsonifier | 2383.78 | 0.0455524 | 6975.22ms | 124597 | 640 | 329978 | 49847.2 | 0.087541 | 2.10955 | 9.41571 | 1.67292 | 0.00800457 | 6.44578e-06 | 3.34829e-06 | 3(Loss) | true |
| simdjson (reflection) | 2333.22 | 0.0313867 | 7125.63ms | 124597 | 2560 | 654085 | 50927.4 | 0.0203924 | 2.16548 | 8.77219 | 1.46003 | 0.00335046 | 1.74688e-05 | 1.3365e-05 | 4(Loss) | true |
| Glaze | 2134.72 | 0.0361924 | 7630.21ms | 124597 | 2560 | 1.03898e+06 | 55662.9 | 0.172055 | 2.36119 | 10.929 | 2.09467 | 0.0103069 | 1.02988e-05 | 6.00373e-06 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 23330.1 | 0.0339293 | 1282.28ms | 136037 | 4890 | 17407.6 | 5560.83 | 0.153317 | 0.220463 | 0.868551 | 0.125708 | 2.16409e-05 | 2.04744e-06 | 9.03459e-07 | 1(Win) | true |
| Glaze | 7234.49 | 0.0456133 | 2528.55ms | 136076 | 4890 | 327370 | 17938 | 0.154958 | 0.69785 | 3.79908 | 0.638224 | 7.87137e-05 | 5.71376e-06 | 4.247e-06 | 2(Loss) | true |
| simdjson (reflection) | 621.01 | 0.190225 | 5494.06ms | 136037 | 640 | 1.01073e+08 | 208910 | 0.0564019 | 8.13995 | 34.7252 | 7.11465 | 0.0269298 | 0.00481844 | 0.000294543 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 23431 | 0.0980418 | 1328.26ms | 136037 | 320 | 9429.89 | 5536.9 | 0.00468426 | 0.216735 | 0.864574 | 0.124826 | 6.25749e-05 | 2.68769e-06 | 8.72924e-07 | 1(Win) | true |
| Glaze | 8076.67 | 0.0779704 | 2349.75ms | 136076 | 160 | 25111.8 | 16067.5 | 0.210424 | 0.627476 | 3.76371 | 0.630104 | 0.000214586 | 1.14826e-06 | 4.59302e-08 | 2(Loss) | true |
| simdjson (reflection) | 627.012 | 0.637209 | 5457.59ms | 136037 | 40 | 6.95324e+07 | 206910 | 0.399216 | 7.96148 | 34.7199 | 7.11323 | 0.0273069 | 0.025779 | 5.05377e-05 | 3(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 938.592 | 0.0498806 | 7118.55ms | 2251027 | 160 | 2.08253e+08 | 2.2872e+06 | 0.00302617 | 5.37532 | 28.1848 | 6.00808 | 0.0147073 | 0.0647352 | 0.000465854 | 1(Win) | true |
| Glaze | 898.663 | 0.112032 | 7514.82ms | 2251027 | 40 | 2.86492e+08 | 2.38882e+06 | 0.132196 | 5.61007 | 30.3088 | 5.64286 | 0.00976837 | 0.0631215 | 0.000573116 | 2(Loss) | true |
| simdjson (reflection) | 828.604 | 0.196849 | 8101.43ms | 2251027 | 30 | 7.80291e+08 | 2.5908e+06 | 0.149897 | 6.09148 | 29.7225 | 5.43739 | 0.0104402 | 0.103729 | 0.000428975 | 3(Loss) | true |
| Jsonifier (two-stage) | 799.835 | 0.185674 | 8407.39ms | 2251027 | 30 | 7.45046e+08 | 2.68399e+06 | 0.0137389 | 6.27062 | 31.4887 | 6.3147 | 0.0232159 | 0.102754 | 0.00327541 | 4(Loss) | true |
| simdjson (ondemand) | 775.203 | 0.154658 | 8620.47ms | 2251027 | 80 | 1.46746e+09 | 2.76927e+06 | 0.0100265 | 6.46295 | 30.7418 | 5.87584 | 0.0143911 | 0.109188 | 0.00121987 | 5(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1113.22 | 0.125886 | 7183.43ms | 2251027 | 40 | 2.35729e+08 | 1.9284e+06 | 0.423725 | 4.53127 | 23.26 | 4.83302 | 0.0140062 | 0.0417914 | 0.000425961 | 1(Win) | true |
| Glaze | 1060.62 | 0.081017 | 7567.76ms | 2251027 | 160 | 4.30242e+08 | 2.02404e+06 | 0.0413048 | 4.71311 | 25.3565 | 4.46548 | 0.00895958 | 0.0395393 | 0.000524244 | 2(Loss) | true |
| simdjson (reflection) | 971.19 | 0.265617 | 8053.31ms | 2251027 | 30 | 1.03416e+09 | 2.21043e+06 | 0.0172802 | 5.19941 | 24.8459 | 4.27487 | 0.00910651 | 0.0773331 | 0.000489095 | 3(Loss) | true |
| simdjson (ondemand) | 928.465 | 0.0950884 | 8416.27ms | 2251027 | 30 | 1.45013e+08 | 2.31215e+06 | 0.056703 | 5.43239 | 25.8225 | 4.70766 | 0.011062 | 0.0759638 | 0.000486948 | 4(Loss) | true |
| Jsonifier (two-stage) | 921.407 | 0.165856 | 8436.1ms | 2251027 | 40 | 5.97282e+08 | 2.32986e+06 | 0.0558492 | 5.39821 | 26.6275 | 5.15798 | 0.0225172 | 0.0787801 | 0.000186482 | 5(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2105.28 | 0.11288 | 6030.27ms | 2090234 | 80 | 9.13897e+07 | 946859 | 0.0409574 | 2.39988 | 7.80015 | 0.373395 | 0.000336751 | 0.0515156 | 8.40277e-05 | 1(Win) | true |
| Glaze | 1448.91 | 0.0919441 | 8743.08ms | 2090234 | 160 | 2.56021e+08 | 1.3758e+06 | 0.0591507 | 3.4527 | 9.59413 | 0.598214 | 0.0117037 | 0.0701387 | 0.000841326 | 2(Loss) | true |
| simdjson (reflection) | 1045.71 | 0.0852545 | 5976.98ms | 2090326 | 160 | 4.22633e+08 | 1.90636e+06 | 0.0312586 | 4.86956 | 15.154 | 1.43489 | 0.0162659 | 0.0507805 | 0.00107602 | 3(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2097.4 | 0.258504 | 6065.96ms | 2090234 | 40 | 2.41447e+08 | 950417 | 0.0926952 | 2.40882 | 7.79989 | 0.373337 | 0.000374539 | 0.05137 | 8.16894e-05 | 1(Win) | true |
| Glaze | 1533.63 | 0.0680776 | 8273.08ms | 2090234 | 80 | 6.26395e+07 | 1.29979e+06 | 0.09236 | 3.29535 | 9.5901 | 0.597292 | 0.0117174 | 0.0437857 | 0.000211986 | 2(Loss) | true |
| simdjson (reflection) | 1048.17 | 0.146772 | 5972.91ms | 2090326 | 30 | 2.33763e+08 | 1.90188e+06 | 0.385476 | 4.85739 | 15.1539 | 1.43485 | 0.0162239 | 0.0506228 | 0.000408676 | 3(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1912.82 | 0.132419 | 8389.25ms | 5373214 | 30 | 3.77522e+08 | 2.67892e+06 | 0.171058 | 2.63055 | 14.0881 | 3.05068 | 0.00594949 | 0.0385223 | 0.000796376 | 1(Win) | true |
| Jsonifier (two-stage) | 1878.68 | 0.190838 | 8539.66ms | 5373214 | 30 | 8.12858e+08 | 2.7276e+06 | 0.165968 | 2.67054 | 14.0045 | 2.68706 | 0.00709756 | 0.062803 | 0.000280577 | 2(Loss) | true |
| simdjson (reflection) | 1859.35 | 0.111949 | 8639.14ms | 5373214 | 40 | 3.80753e+08 | 2.75595e+06 | 0.940319 | 2.7051 | 13.2173 | 2.31135 | 0.00473474 | 0.0626897 | 0.000110339 | 3(Loss) | true |
| simdjson (ondemand) | 1735.53 | 0.101291 | 9146.95ms | 5373214 | 80 | 7.15541e+08 | 2.95258e+06 | 0.357302 | 2.90152 | 13.6419 | 2.49428 | 0.00635996 | 0.0647222 | 0.00131173 | 4(Loss) | true |
| Glaze | 1636.99 | 0.25429 | 9669.66ms | 5373214 | 30 | 1.90089e+09 | 3.13032e+06 | 0.520225 | 3.0759 | 15.903 | 2.91918 | 0.0047503 | 0.0408182 | 0.00291187 | 5(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2217.56 | 0.168176 | 8354.43ms | 5373214 | 30 | 4.53073e+08 | 2.31079e+06 | 0.013042 | 2.26588 | 12.0548 | 2.56695 | 0.00568086 | 0.0283091 | 0.000825266 | 1(Win) | true |
| Jsonifier (two-stage) | 2160.23 | 0.162935 | 8550.25ms | 5373214 | 40 | 5.97522e+08 | 2.3721e+06 | 0.0680713 | 2.30244 | 11.9707 | 2.20331 | 0.00687353 | 0.0525562 | 0.000433684 | 2(Loss) | true |
| simdjson (reflection) | 2145.29 | 0.137706 | 8562.58ms | 5373214 | 160 | 1.73109e+09 | 2.38862e+06 | 0.00408509 | 2.34147 | 11.1739 | 1.82411 | 0.00409445 | 0.0514502 | 0.000130952 | 3(Loss) | true |
| simdjson (ondemand) | 2044.02 | 0.15489 | 8942.31ms | 5373214 | 160 | 2.41247e+09 | 2.50697e+06 | 0.0552986 | 2.45314 | 11.5822 | 2.00514 | 0.00491599 | 0.0515074 | 9.86572e-05 | 4(Loss) | true |
| Glaze | 1872.36 | 0.363439 | 9653.01ms | 5373214 | 40 | 3.95743e+09 | 2.73681e+06 | 0.0535693 | 2.68493 | 13.8601 | 2.43499 | 0.00438924 | 0.0297474 | 0.00274587 | 5(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6110.78 | 0.129664 | 6637.1ms | 6661897 | 80 | 1.45388e+08 | 1.03968e+06 | 0.127063 | 0.826261 | 2.5063 | 0.117149 | 9.68099e-05 | 0.0280065 | 4.45143e-05 | 1(Win) | true |
| Glaze | 3293.96 | 0.157143 | 6071.16ms | 6661897 | 40 | 3.6746e+08 | 1.92877e+06 | 0.196458 | 1.5273 | 4.3345 | 0.464357 | 0.00373825 | 0.0636596 | 0.00156126 | 2(Loss) | true |
| simdjson (reflection) | 274.583 | 0.161054 | 6939.04ms | 6661989 | 30 | 4.16604e+10 | 2.31382e+07 | 0.176172 | 13.3397 | 41.3171 | 5.67132 | 0.025452 | 0.181266 | 0.0667303 | 3(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6074.82 | 0.211879 | 6628.07ms | 6661897 | 160 | 7.85639e+08 | 1.04584e+06 | 0.210865 | 0.829698 | 2.50625 | 0.117138 | 0.000103824 | 0.0279742 | 4.7054e-05 | 1(Win) | true |
| Glaze | 3918.75 | 0.144302 | 5084.01ms | 6661897 | 40 | 2.18931e+08 | 1.62125e+06 | 0.148918 | 1.28672 | 4.33307 | 0.464028 | 0.00373796 | 0.0248763 | 5.07363e-05 | 2(Loss) | true |
| simdjson (reflection) | 383.946 | 0.320165 | 11494.5ms | 6661989 | 40 | 1.12273e+11 | 1.65476e+07 | 1.12265 | 13.0913 | 41.3255 | 5.67482 | 0.0241782 | 0.255712 | 0.121477 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2358.93 | 0.0351227 | 5361.84ms | 500299 | 1280 | 6.45973e+06 | 202262 | 0.0351995 | 2.12198 | 9.68451 | 1.72319 | 0.0103747 | 0.00747969 | 0.000114736 | 1(Win) | true |
| Glaze | 1820.67 | 0.0536631 | 6922.61ms | 500299 | 320 | 6.32845e+06 | 262058 | 0.11719 | 2.77161 | 11.6177 | 2.26098 | 0.0140567 | 0.00446565 | 9.99652e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1811.53 | 0.106623 | 6981.34ms | 500299 | 30 | 2.36588e+06 | 263381 | 0.0552483 | 2.78761 | 12.4105 | 2.10464 | 0.0139106 | 0.0397575 | 0.000169699 | 3(Loss) | true |
| simdjson (ondemand) | 1452.49 | 0.148101 | 8630.91ms | 500299 | 160 | 3.78679e+07 | 328487 | 0.0609223 | 3.46329 | 14.2526 | 2.4324 | 0.0170967 | 0.0343719 | 0.000357386 | 4(Loss) | true |
| simdjson (reflection) | 1446.54 | 0.0490053 | 8629.37ms | 500299 | 320 | 8.36056e+06 | 329838 | 0.0462364 | 3.48939 | 14.257 | 2.46033 | 0.0181896 | 0.0219667 | 0.000224291 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2940.26 | 0.0396786 | 5153.68ms | 500299 | 640 | 2.65326e+06 | 162272 | 0.0617446 | 1.71692 | 8.56672 | 1.45069 | 0.00743454 | 0.00284152 | 2.71275e-05 | 1(Win) | true |
| Glaze | 2161.88 | 0.110616 | 6797.72ms | 500299 | 80 | 4.76785e+06 | 220698 | 0.0766297 | 2.33645 | 10.5056 | 1.99146 | 0.00923685 | 0.00171602 | 5.91896e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2144.93 | 0.133456 | 6763.39ms | 500299 | 160 | 1.41004e+07 | 222442 | 0.143671 | 2.33913 | 11.2899 | 1.83221 | 0.00980031 | 0.0277989 | 5.14692e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1765.14 | 0.0504246 | 7961.16ms | 500299 | 320 | 5.94479e+06 | 270303 | 0.247574 | 2.85896 | 13.1088 | 2.15242 | 0.00884332 | 0.0203429 | 4.11004e-05 | 4(Loss) | true |
| simdjson (reflection) | 1715.21 | 0.109648 | 8173.78ms | 500299 | 30 | 2.79091e+06 | 278172 | 0.0609587 | 2.94505 | 13.1433 | 2.18758 | 0.0110013 | 0.0158684 | 5.68993e-05 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12453.3 | 0.0294486 | 4600.82ms | 500299 | 1280 | 162941 | 38313 | 0.148198 | 0.405794 | 1.81572 | 0.301818 | 0.00139568 | 0.00516246 | 2.54535e-06 | 1(Win) | true |
| simdjson (reflection) | 11199.6 | 0.0534562 | 4999.15ms | 500299 | 320 | 165959 | 42601.7 | 0.0386499 | 0.451211 | 2.18113 | 0.197082 | 0.00135663 | 0.000417026 | 1.45788e-05 | 2(Loss) | true |
| Glaze | 5912.76 | 0.0490694 | 8851.14ms | 500299 | 2560 | 4.01365e+06 | 80693.6 | 0.0311072 | 0.839645 | 3.76516 | 0.550621 | 0.00150804 | 0.0236324 | 2.09882e-05 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12472.8 | 0.0861594 | 4596.29ms | 500299 | 160 | 173802 | 38252.9 | 0.0150175 | 0.405379 | 1.81463 | 0.301572 | 0.00142219 | 0.0050575 | 2.41106e-06 | 1(Win) | true |
| simdjson (reflection) | 11161.5 | 0.0268177 | 5067.75ms | 500299 | 1280 | 168216 | 42747.2 | 0.0448476 | 0.452956 | 2.18004 | 0.196834 | 0.00137188 | 0.000946743 | 6.74284e-06 | 2(Loss) | true |
| Glaze | 7203.28 | 0.0516034 | 7361.35ms | 500299 | 640 | 747713 | 66236.8 | 0.00462614 | 0.696838 | 3.75128 | 0.547385 | 0.00156164 | 0.000196354 | 6.062e-06 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3622.15 | 0.118364 | 7968.47ms | 1151920 | 320 | 4.12384e+07 | 303289 | 0.0903868 | 1.38463 | 6.18085 | 0.947784 | 0.00590574 | 0.0561343 | 0.000171532 | 1(Win) | true |
| Jsonifier | 3322.07 | 0.141866 | 8534.3ms | 1151920 | 30 | 6.60243e+06 | 330684 | 0.216889 | 1.49803 | 6.67157 | 1.38546 | 0.00453012 | 0.0186849 | 0.000129118 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 3015.79 | 0.0233528 | 9529.3ms | 1151920 | 1280 | 9.26254e+06 | 364269 | 0.0390448 | 1.67842 | 6.95676 | 1.10169 | 0.00759896 | 0.0451433 | 8.19908e-05 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3008.89 | 0.121644 | 9533.25ms | 1151920 | 40 | 7.88998e+06 | 365104 | 0.238431 | 1.67711 | 6.95857 | 1.09083 | 0.00738398 | 0.0529797 | 0.000165593 | 3(Tie) | true |
| Glaze | 2552.74 | 0.0390311 | 5569.07ms | 1151920 | 640 | 1.80565e+07 | 430343 | 0.000642288 | 1.97327 | 8.47796 | 1.61292 | 0.00739159 | 0.0145489 | 0.000102385 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4222.49 | 0.0682313 | 7770.73ms | 1151920 | 1280 | 4.03352e+07 | 260168 | 0.0201098 | 1.1871 | 5.69546 | 0.829863 | 0.00441949 | 0.0471265 | 6.94533e-05 | 1(Win) | true |
| Jsonifier | 3856.23 | 0.0899665 | 8326.08ms | 1151920 | 160 | 1.05099e+07 | 284878 | 0.0960762 | 1.30168 | 6.18658 | 1.26739 | 0.00335547 | 0.0121718 | 2.13068e-05 | 2(Loss) | true |
| simdjson (ondemand) | 3597.02 | 0.0483969 | 8816.42ms | 1151920 | 320 | 6.99107e+06 | 305407 | 0.119225 | 1.40478 | 6.45925 | 0.968431 | 0.00409874 | 0.0362714 | 1.31492e-05 | 3(Loss) | true |
| simdjson (reflection) | 3493.29 | 0.0417668 | 9073.57ms | 1151920 | 1280 | 2.20825e+07 | 314477 | 0.136737 | 1.44512 | 6.47483 | 0.984222 | 0.00483811 | 0.0348663 | 2.18819e-05 | 4(Loss) | true |
| Glaze | 2854.36 | 0.0833573 | 5406.27ms | 1151920 | 160 | 1.64678e+07 | 384869 | 0.00607312 | 1.76125 | 7.99431 | 1.49585 | 0.00541696 | 0.00925718 | 3.22234e-05 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20133.1 | 0.0504291 | 7649.75ms | 1439562 | 320 | 378402 | 68190 | 0.0832685 | 0.251312 | 0.703086 | 0.104897 | 0.000438727 | 0.018208 | 4.32857e-06 | 1(Win) | true |
| Glaze | 5692.48 | 0.0635522 | 6371.4ms | 1439584 | 1280 | 3.00706e+07 | 241177 | 0.00849764 | 0.885591 | 3.1224 | 0.499162 | 0.000879334 | 0.0619488 | 1.46695e-05 | 2(Loss) | true |
| simdjson (reflection) | 566.02 | 0.798172 | 7434.41ms | 1439562 | 80 | 2.99833e+10 | 2.42548e+06 | 0.561217 | 8.88377 | 35.7848 | 6.43753 | 0.0157728 | 0.308775 | 0.00273622 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20184.3 | 0.0370935 | 7627.88ms | 1439562 | 640 | 407390 | 68016.9 | 0.0805825 | 0.250396 | 0.702708 | 0.104812 | 0.000437356 | 0.0179677 | 2.72761e-06 | 1(Win) | true |
| Glaze | 7902.02 | 0.0983594 | 9291.57ms | 1439584 | 640 | 1.869e+07 | 173740 | 0.0476622 | 0.638121 | 3.11679 | 0.497885 | 0.000887578 | 0.0181629 | 1.74269e-05 | 2(Loss) | true |
| simdjson (reflection) | 569.977 | 0.55145 | 7485.47ms | 1439562 | 160 | 2.82279e+10 | 2.40865e+06 | 0.436059 | 8.7989 | 35.7826 | 6.43685 | 0.0157781 | 0.308388 | 0.00600327 | 3(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2296.55 | 0.0883229 | 3076.75ms | 56369 | 80 | 34195.1 | 23408 | 0.0525738 | 2.20482 | 9.42132 | 1.80171 | 0.00292426 | 2.83844e-05 | 2.28406e-05 | 1(Win) | true |
| Glaze | 2025.17 | 0.143447 | 3400.13ms | 56369 | 80 | 115993 | 26544.8 | 0.0821928 | 2.49877 | 11.2196 | 2.27577 | 0.00530744 | 0.000117973 | 0.000100011 | 2(Loss) | true |
| Jsonifier (two-stage) | 1826.71 | 0.0283136 | 3680.06ms | 56369 | 2560 | 177735 | 29428.7 | 0.0298294 | 2.77343 | 12.2726 | 2.12839 | 0.00487188 | 3.76218e-05 | 2.22377e-05 | 3(Loss) | true |
| simdjson (reflection) | 1572.25 | 0.036573 | 4186.75ms | 56369 | 1280 | 200158 | 34191.7 | 0.00190565 | 3.22498 | 13.7995 | 2.40389 | 0.00430861 | 7.15985e-05 | 5.22922e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1326.39 | 0.0221978 | 4790.9ms | 56369 | 4890 | 395794 | 40529.4 | 0.125338 | 3.80709 | 15.0257 | 2.78824 | 0.008408 | 3.83683e-05 | 2.33743e-05 | 5(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3231.03 | 0.0560617 | 2752.13ms | 56369 | 80 | 6960.18 | 16637.9 | 0.100198 | 1.56936 | 7.42684 | 1.34426 | 0.00200797 | 1.06441e-05 | 1.10877e-06 | 1(Win) | true |
| Glaze | 2964.9 | 0.0457128 | 2900.9ms | 56369 | 2560 | 175863 | 18131.3 | 0.0577783 | 1.71037 | 8.95624 | 1.756 | 0.00188757 | 2.42404e-05 | 1.65553e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2407.61 | 0.0383935 | 3306.15ms | 56369 | 640 | 47033.1 | 22328.2 | 0.030268 | 2.1025 | 10.2707 | 1.66992 | 0.00241664 | 3.42054e-05 | 2.09557e-05 | 3(Loss) | true |
| simdjson (reflection) | 1797.8 | 0.0965691 | 4108.45ms | 56369 | 160 | 133412 | 29902 | 0.0612375 | 2.81055 | 12.2456 | 2.05315 | 0.00369485 | 2.50581e-05 | 1.10877e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1617.84 | 0.0451569 | 4466.49ms | 56369 | 1280 | 288184 | 33228.1 | 0.0859691 | 3.12162 | 12.8398 | 2.29514 | 0.00850454 | 2.13299e-05 | 1.02838e-05 | 5(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15132.2 | 0.0393484 | 1096.13ms | 56369 | 4890 | 9555.2 | 3552.53 | 0.168849 | 0.337375 | 1.41947 | 0.224485 | 0.000204434 | 1.11847e-05 | 5.80458e-06 | 1(Win) | true |
| simdjson (reflection) | 13054.8 | 0.117547 | 1149.81ms | 56369 | 320 | 7497.4 | 4117.84 | 0.137777 | 0.390869 | 1.69984 | 0.277546 | 0.000169198 | 7.04066e-06 | 2.6056e-06 | 2(Loss) | true |
| Glaze | 6357.31 | 0.0721628 | 1591.31ms | 56369 | 640 | 23830.9 | 8456.04 | 0.00105325 | 0.80029 | 3.0545 | 0.466338 | 7.87223e-05 | 7.95539e-06 | 2.52244e-06 | 3(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15419.3 | 0.101483 | 1086.44ms | 56369 | 4890 | 61213.4 | 3486.4 | 0.00946157 | 0.331895 | 1.40929 | 0.222197 | 0.000208881 | 1.05861e-05 | 5.61956e-06 | 1(Win) | true |
| simdjson (reflection) | 13319.9 | 0.0846234 | 1144.31ms | 56369 | 320 | 3732.6 | 4035.9 | 0.0190514 | 0.383265 | 1.68962 | 0.275222 | 0.000155726 | 4.71225e-06 | 2.43928e-06 | 2(Loss) | true |
| Glaze | 7225.53 | 0.21918 | 1481.12ms | 56369 | 80 | 21273.2 | 7439.96 | 0.221117 | 0.70293 | 2.97538 | 0.448722 | 7.1848e-05 | 1.7075e-05 | 1.24182e-05 | 3(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2542.08 | 0.0311488 | 3891.14ms | 83958 | 2560 | 246415 | 31497.3 | 0.0753659 | 1.96891 | 8.76062 | 1.44207 | 0.00283024 | 1.34414e-05 | 7.53725e-06 | 1(Win) | true |
| Glaze | 2431.95 | 0.106564 | 4050.76ms | 83958 | 320 | 393900 | 32923.6 | 0.0534475 | 2.07574 | 9.97514 | 2.07256 | 0.00431027 | 2.36726e-05 | 1.45906e-05 | 2(Loss) | true |
| simdjson (reflection) | 2240.36 | 0.0439082 | 4325.89ms | 83958 | 640 | 157601 | 35739.1 | 0.174456 | 2.2582 | 9.73037 | 1.63321 | 0.00302627 | 1.76986e-05 | 1.02172e-05 | 3(Loss) | true |
| Jsonifier | 2233.55 | 0.0218881 | 4334.98ms | 83958 | 1280 | 78805.5 | 35848.1 | 0.0114821 | 2.26437 | 8.89125 | 1.83539 | 0.00473913 | 4.10268e-05 | 2.7618e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1905.09 | 0.0217881 | 4940.67ms | 83958 | 4890 | 410053 | 42028.7 | 0.14399 | 2.65582 | 10.5584 | 1.8917 | 0.00595623 | 3.7101e-05 | 2.34804e-05 | 5(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3277.94 | 0.216004 | 3519.11ms | 83958 | 40 | 111354 | 24426.5 | 0.206486 | 1.52406 | 7.41654 | 1.1339 | 0.00168686 | 2.17371e-05 | 1.63772e-05 | 1(Win) | true |
| Glaze | 3235.14 | 0.0434584 | 3563.86ms | 83958 | 2560 | 296160 | 24749.7 | 0.105181 | 1.56237 | 8.47109 | 1.7268 | 0.00213133 | 1.40463e-05 | 8.83068e-06 | 2(Loss) | true |
| Jsonifier | 2772.58 | 0.0642073 | 3985.25ms | 83958 | 1280 | 440083 | 28878.7 | 0.124335 | 1.81474 | 7.54458 | 1.52686 | 0.00359582 | 2.27699e-05 | 1.35764e-05 | 3(Loss) | true |
| simdjson (reflection) | 2558.24 | 0.0732029 | 4245.86ms | 83958 | 2560 | 1.34381e+06 | 31298.3 | 0.0675663 | 1.9745 | 8.69522 | 1.39963 | 0.00228901 | 2.29467e-05 | 1.38043e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2325.78 | 0.0206066 | 4568.32ms | 83958 | 4890 | 246098 | 34426.6 | 0.171122 | 2.17391 | 9.09032 | 1.56113 | 0.00569353 | 1.99657e-05 | 1.2091e-05 | 5(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20192 | 0.129005 | 1189.07ms | 94370 | 640 | 21159.3 | 4457.13 | 0.277149 | 0.250973 | 0.900244 | 0.134153 | 0.00010628 | 3.95716e-06 | 1.67227e-06 | 1(Win) | true |
| Glaze | 5913.52 | 0.0850356 | 2269.4ms | 94370 | 2560 | 428764 | 15219.1 | 0.0233898 | 0.854808 | 3.65836 | 0.618332 | 0.00039447 | 1.65489e-05 | 8.96571e-06 | 2(Loss) | true |
| simdjson (reflection) | 546.362 | 0.159605 | 8850.01ms | 94370 | 2560 | 1.76947e+08 | 164723 | 1.33692 | 9.21422 | 38.8295 | 7.53837 | 0.022649 | 0.0143238 | 0.00031536 | 3(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20624.1 | 0.0724667 | 1178.7ms | 94370 | 30 | 299.995 | 4363.73 | 0.0244379 | 0.247554 | 0.894532 | 0.132871 | 0.000105966 | 1.34223e-05 | 8.12405e-06 | 1(Win) | true |
| Glaze | 7150.07 | 0.134791 | 2003.76ms | 94370 | 1280 | 368453 | 12587 | 0.0667342 | 0.708158 | 3.60407 | 0.605966 | 0.000362205 | 1.26166e-05 | 6.79672e-06 | 2(Loss) | true |
| simdjson (reflection) | 559.093 | 0.153384 | 8618.59ms | 94370 | 2560 | 1.56062e+08 | 160972 | 0.168406 | 9.01512 | 38.8305 | 7.53866 | 0.0230107 | 0.017364 | 0.000647447 | 3(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1671.37 | 0.0410762 | 3784.1ms | 53331 | 2560 | 399977 | 30430.4 | 0.0183146 | 3.02623 | 9.88145 | 1.7251 | 0.010564 | 0.000125484 | 7.64975e-05 | 1(Win) | true |
| simdjson (reflection) | 1565.35 | 0.0674343 | 4003.49ms | 53331 | 2560 | 1.22897e+06 | 32491.5 | 0.109965 | 3.22947 | 10.8558 | 1.89891 | 0.0104767 | 0.000160114 | 7.5765e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1533.46 | 0.0696029 | 4060.9ms | 53331 | 1280 | 682152 | 33167.2 | 0.11522 | 3.27733 | 10.6979 | 1.80513 | 0.0105931 | 0.000133131 | 5.86256e-05 | 3(Loss) | true |
| Glaze | 1475.3 | 0.065636 | 4183.9ms | 53331 | 2560 | 1.31077e+06 | 34474.7 | 0.0475983 | 3.4305 | 11.6365 | 2.27582 | 0.0190522 | 0.000124971 | 7.17732e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1423.47 | 0.0745552 | 4331.4ms | 53331 | 640 | 454149 | 35729.8 | 0.100722 | 3.54608 | 11.1027 | 2.05146 | 0.00484794 | 0.000151178 | 7.79331e-05 | 5(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2269.38 | 0.0331903 | 3546.2ms | 53331 | 4890 | 270567 | 22411.5 | 0.0245152 | 2.2206 | 7.66137 | 1.22524 | 0.0075112 | 2.20485e-05 | 1.11546e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2043.29 | 0.0534746 | 3808.5ms | 53331 | 2560 | 453560 | 24891.5 | 0.051099 | 2.46816 | 8.52551 | 1.31658 | 0.0073471 | 4.8071e-05 | 1.95858e-05 | 2(Loss) | true |
| Glaze | 1948.83 | 0.0505018 | 3942.48ms | 53331 | 4890 | 849441 | 26097.9 | 0.0477335 | 2.59435 | 9.40859 | 1.77395 | 0.0157468 | 3.29999e-05 | 1.73972e-05 | 3(Loss) | true |
| simdjson (reflection) | 1898.19 | 0.106618 | 4006.39ms | 53331 | 640 | 522299 | 26794.2 | 0.111624 | 2.67362 | 8.97365 | 1.46675 | 0.00906713 | 8.09215e-05 | 2.59582e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1627.27 | 0.0670803 | 4409.94ms | 53331 | 640 | 281325 | 31255 | 0.0106772 | 3.10053 | 9.22513 | 1.63481 | 0.00983627 | 4.86349e-05 | 2.26182e-05 | 5(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14700.2 | 0.162264 | 1120.07ms | 58581 | 640 | 24338.1 | 3800.43 | 0.0603187 | 0.345155 | 1.05758 | 0.167614 | 3.52877e-05 | 4.62234e-05 | 3.08334e-05 | 1(Win) | true |
| simdjson (reflection) | 11061.1 | 0.0506124 | 1249.79ms | 58581 | 4890 | 31955 | 5050.78 | 0.449485 | 0.458323 | 1.4967 | 0.212253 | 4.54372e-05 | 4.42364e-05 | 2.78642e-05 | 2(Loss) | true |
| Glaze | 7376.24 | 0.175427 | 1508.04ms | 58581 | 320 | 56492 | 7573.93 | 0.00457964 | 0.688705 | 2.43244 | 0.370342 | 4.85972e-05 | 6.66812e-06 | 2.18714e-06 | 3(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15031.3 | 0.0540808 | 1113.25ms | 58581 | 4890 | 19756.7 | 3716.71 | 0.193625 | 0.338858 | 1.04838 | 0.165549 | 3.4427e-05 | 2.40696e-05 | 1.43266e-05 | 1(Win) | true |
| simdjson (reflection) | 11089.6 | 0.0499647 | 1251.69ms | 58581 | 4890 | 30982.4 | 5037.79 | 0.00222303 | 0.45628 | 1.4875 | 0.210171 | 5.15602e-05 | 2.84925e-05 | 1.63792e-05 | 2(Loss) | true |
| Glaze | 8565.92 | 0.149655 | 1396.28ms | 58581 | 1280 | 121944 | 6522.03 | 0.122872 | 0.593333 | 2.36218 | 0.354176 | 3.52743e-05 | 4.8824e-05 | 3.066e-05 | 3(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1883.43 | 0.0329673 | 4044.74ms | 65103 | 4890 | 577535 | 32964.9 | 0.278382 | 2.72513 | 9.17213 | 1.57522 | 0.0103263 | 4.37784e-05 | 3.18043e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1858.02 | 0.0362144 | 4079.29ms | 65103 | 2560 | 374891 | 33415.7 | 0.120964 | 2.75067 | 9.15867 | 1.49313 | 0.0101084 | 6.86772e-05 | 5.5951e-05 | 2(Loss) | true |
| Jsonifier | 1731.26 | 0.0638796 | 4334.09ms | 65103 | 640 | 335877 | 35862.3 | 0.205407 | 2.9502 | 9.22254 | 1.68632 | 0.00914553 | 2.93285e-05 | 1.92723e-05 | 3(Loss) | true |
| Glaze | 1667.34 | 0.0421553 | 4462.51ms | 65103 | 2560 | 630810 | 37237.2 | 0.068844 | 3.07012 | 10.7723 | 2.11741 | 0.0133521 | 4.68188e-05 | 3.36186e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1595.83 | 0.0666192 | 4626.68ms | 65103 | 640 | 429939 | 38905.8 | 0.00844919 | 3.20541 | 9.4759 | 1.72305 | 0.0113166 | 3.32406e-05 | 2.49364e-05 | 5(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2371.11 | 0.0533083 | 3956.52ms | 65103 | 4890 | 952793 | 26184.8 | 0.212348 | 2.12463 | 7.39511 | 1.0931 | 0.00688614 | 6.609e-05 | 4.21104e-05 | 1(Win) | true |
| Jsonifier | 2264.85 | 0.0220096 | 3953.27ms | 65103 | 4890 | 178015 | 27413.4 | 0.085053 | 2.22124 | 7.42154 | 1.27603 | 0.00258306 | 2.73469e-05 | 1.59477e-05 | 2(Loss) | true |
| simdjson (reflection) | 2234.77 | 0.0351012 | 4111.83ms | 65103 | 2560 | 243456 | 27782.3 | 0.0273503 | 2.26053 | 7.63836 | 1.22003 | 0.00750848 | 7.03573e-05 | 3.84247e-05 | 3(Loss) | true |
| Glaze | 2004.54 | 0.058997 | 4481.07ms | 65103 | 2560 | 854815 | 30973.2 | 0.0296993 | 2.52712 | 8.9377 | 1.70282 | 0.0123088 | 6.43512e-05 | 4.39208e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1939.91 | 0.0446982 | 4492.49ms | 65103 | 2560 | 523913 | 32005.1 | 0.126021 | 2.60147 | 7.8295 | 1.35337 | 0.00786866 | 4.47848e-05 | 2.55365e-05 | 5(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18539.1 | 0.0619412 | 1136.41ms | 78778 | 2560 | 16130 | 4052.44 | 0.0431652 | 0.278972 | 0.830156 | 0.124578 | 2.55514e-05 | 2.14705e-05 | 1.56938e-05 | 1(Win) | true |
| Glaze | 5244.17 | 0.0658399 | 2167.6ms | 78778 | 4890 | 435055 | 14326.1 | 0.0280581 | 0.968839 | 2.87673 | 0.450253 | 8.46104e-05 | 2.18937e-05 | 1.48719e-05 | 2(Loss) | true |
| simdjson (reflection) | 633.675 | 0.11612 | 6432.12ms | 78778 | 2560 | 4.85207e+07 | 118560 | 0.265086 | 8.00511 | 29.3423 | 6.60943 | 0.0388506 | 0.000200583 | 8.93184e-05 | 3(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18397.3 | 0.0601078 | 1152.28ms | 78778 | 1280 | 7712.16 | 4083.68 | 0.000612196 | 0.276439 | 0.823656 | 0.123105 | 2.55068e-05 | 2.12325e-05 | 1.25352e-05 | 1(Win) | true |
| Glaze | 6037.65 | 0.079687 | 1988.4ms | 78778 | 4890 | 480793 | 12443.4 | 0.302762 | 0.834165 | 2.80596 | 0.434093 | 8.04155e-05 | 3.38712e-05 | 2.11513e-05 | 2(Loss) | true |
| simdjson (reflection) | 636.921 | 0.113195 | 6430ms | 78778 | 2560 | 4.56388e+07 | 117956 | 0.0830247 | 7.93503 | 29.3753 | 6.6079 | 0.0317734 | 0.0179112 | 0.000287695 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2504.73 | 0.0314693 | 1178.75ms | 11812 | 4890 | 9795.09 | 4497.42 | 0.129486 | 2.05303 | 10.1043 | 1.61179 | 0.00260961 | 2.82891e-05 | 1.06301e-05 | 1(Win) | true |
| Glaze | 1924.3 | 0.0616957 | 1306.73ms | 11812 | 1280 | 16696.3 | 5853.97 | 0.14652 | 2.65001 | 13.1048 | 2.62318 | 0.00150992 | 3.80307e-05 | 1.26328e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1772.03 | 0.0528602 | 1372.32ms | 11812 | 2560 | 28906.8 | 6356.99 | 0.109251 | 2.87085 | 13.5533 | 2.14397 | 0.0063971 | 2.3546e-05 | 7.50693e-06 | 3(Loss) | true |
| simdjson (reflection) | 1498.29 | 0.0917395 | 1485.96ms | 11812 | 640 | 30447.4 | 7518.45 | 0.0922125 | 3.39006 | 13.4807 | 2.15205 | 0.00408007 | 2.48688e-05 | 1.0847e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1103.69 | 0.0332111 | 1759.8ms | 11812 | 4890 | 56185.7 | 10206.4 | 0.120312 | 4.60484 | 17.7471 | 3.19638 | 0.00844762 | 7.19174e-05 | 4.06678e-05 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2839.02 | 0.0612875 | 1178.44ms | 11812 | 80 | 473.091 | 3967.85 | 0.0157491 | 1.80017 | 9.20166 | 1.40019 | 0.00169848 | 3.06891e-05 | 2.11649e-06 | 1(Win) | true |
| Glaze | 2209.02 | 0.0750669 | 1287.92ms | 11812 | 1280 | 18756.7 | 5099.46 | 0.0116573 | 2.32553 | 12.0412 | 2.3786 | 0.000666496 | 1.95114e-05 | 4.16684e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1963.54 | 0.0777474 | 1374.17ms | 11812 | 80 | 1591.58 | 5736.99 | 0.0703272 | 2.64315 | 12.65 | 1.9321 | 0.00639815 | 1.37572e-05 | 1.05825e-06 | 3(Loss) | true |
| simdjson (reflection) | 1606.83 | 0.0583268 | 1500.2ms | 11812 | 160 | 2675.24 | 7010.57 | 0.0663735 | 3.16644 | 12.982 | 2.02921 | 0.00335094 | 2.43397e-05 | 1.58737e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1170.67 | 0.063382 | 1753.45ms | 11812 | 80 | 2975.77 | 9622.52 | 0.0519884 | 4.33893 | 17.0127 | 3.02946 | 0.00775377 | 4.86793e-05 | 2.22232e-05 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15683.4 | 0.142682 | 797.16ms | 11812 | 160 | 168.044 | 718.263 | 0.152913 | 0.3407 | 1.63021 | 0.257365 | 8.46597e-05 | 6.34948e-06 | 0 | 1(Win) | true |
| simdjson (reflection) | 10305.7 | 0.129589 | 838.023ms | 11812 | 80 | 160.515 | 1093.06 | 0.0377523 | 0.518808 | 2.37242 | 0.355401 | 0.000104766 | 1.2699e-05 | 1.05825e-06 | 2(Loss) | true |
| Glaze | 3654.8 | 0.147938 | 1056.9ms | 11812 | 4890 | 101669 | 3082.19 | 0.228613 | 1.39977 | 4.61895 | 0.71512 | 0.000126799 | 7.07229e-05 | 4.3005e-05 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16821.8 | 0.0740933 | 790.53ms | 11812 | 640 | 157.557 | 669.653 | 0.136545 | 0.319171 | 1.58297 | 0.24636 | 8.49242e-05 | 5.95263e-06 | 6.61404e-07 | 1(Win) | true |
| simdjson (reflection) | 10406.4 | 0.0844495 | 837.436ms | 11812 | 4890 | 4086.48 | 1082.49 | 0.00283115 | 0.505892 | 2.34459 | 0.348718 | 0.000105643 | 1.59105e-05 | 2.94318e-06 | 2(Loss) | true |
| Glaze | 5173.1 | 0.143966 | 954.626ms | 11812 | 2560 | 25159.6 | 2177.57 | 0.0209925 | 0.996063 | 4.35083 | 0.655943 | 9.77555e-05 | 1.59398e-05 | 7.24237e-06 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3319.03 | 0.0553372 | 1469.35ms | 25388 | 1280 | 20858.3 | 7294.87 | 0.0928729 | 1.52942 | 7.15669 | 1.05042 | 0.00293597 | 1.69248e-05 | 9.2625e-06 | 1(Win) | true |
| Jsonifier | 3281.87 | 0.0266756 | 1475.32ms | 25388 | 4890 | 18938.8 | 7377.47 | 0.212853 | 1.54897 | 7.18631 | 1.38278 | 0.004003 | 1.91949e-05 | 9.76259e-06 | 2(Loss) | true |
| simdjson (reflection) | 2932.28 | 0.0521514 | 1565.83ms | 25388 | 2560 | 47470 | 8257.02 | 0.071387 | 1.72039 | 6.9779 | 1.03116 | 0.00197196 | 1.62478e-05 | 7.38538e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2233.66 | 0.0275268 | 1822.31ms | 25388 | 2560 | 22791.6 | 10839.6 | 0.176771 | 2.27016 | 8.98048 | 1.52061 | 0.00399287 | 1.64479e-05 | 6.56991e-06 | 4(Loss) | true |
| Glaze | 1873.6 | 0.0636183 | 2026.41ms | 25388 | 320 | 21628 | 12922.6 | 0.0369401 | 2.70477 | 9.40986 | 1.80814 | 0.00589144 | 5.78521e-06 | 4.92359e-07 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3542.22 | 0.0462935 | 1475.32ms | 25388 | 2560 | 25632.2 | 6835.22 | 0.0351246 | 1.43054 | 6.77734 | 0.960533 | 0.00302344 | 1.58786e-05 | 7.00072e-06 | 1(Win) | true |
| Jsonifier | 3498.2 | 0.0353592 | 1482.7ms | 25388 | 4890 | 29287.4 | 6921.24 | 0.00431019 | 1.45125 | 6.80696 | 1.29301 | 0.00395209 | 1.31618e-05 | 2.51314e-06 | 2(Loss) | true |
| simdjson (reflection) | 3165.06 | 0.0340488 | 1558.73ms | 25388 | 4890 | 33174.7 | 7649.75 | 0.0308052 | 1.59491 | 6.74409 | 0.973531 | 0.00120446 | 2.06851e-05 | 9.45651e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2358.34 | 0.0304804 | 1821.78ms | 25388 | 2560 | 25068.4 | 10266.5 | 0.0100648 | 2.14473 | 8.61999 | 1.43891 | 0.00354177 | 1.0878e-05 | 2.95415e-06 | 4(Loss) | true |
| Glaze | 1973.89 | 0.0291076 | 2008.9ms | 25388 | 2560 | 32633.5 | 12266.1 | 0.0768013 | 2.56476 | 8.93158 | 1.6984 | 0.00544082 | 1.32783e-05 | 2.29254e-06 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20762.7 | 0.087952 | 875.193ms | 31235 | 160 | 254.757 | 1434.69 | 0.133482 | 0.250669 | 0.668225 | 0.0968465 | 3.20154e-05 | 1.28061e-05 | 7.60365e-06 | 1(Win) | true |
| Glaze | 6506.54 | 0.0647441 | 1195.13ms | 31235 | 4890 | 42962.8 | 4578.17 | 0.0479016 | 0.781859 | 3.75185 | 0.631087 | 0.000709445 | 1.83254e-05 | 8.93026e-06 | 2(Loss) | true |
| simdjson (reflection) | 529.849 | 0.170258 | 6390.75ms | 31235 | 2560 | 2.34549e+07 | 56219.8 | 0.00676381 | 9.46397 | 38.2381 | 7.0414 | 0.0157081 | 0.000213352 | 0.000145145 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 21472.5 | 0.079912 | 871.123ms | 31235 | 160 | 196.635 | 1387.26 | 0.119984 | 0.24253 | 0.652025 | 0.0931647 | 3.20154e-05 | 6.00288e-06 | 4.00192e-07 | 1(Win) | true |
| Glaze | 7380.41 | 0.0905668 | 1140.53ms | 31235 | 4890 | 65338.4 | 4036.09 | 0.0882475 | 0.691484 | 3.62862 | 0.603938 | 0.000693679 | 1.25181e-05 | 5.66325e-06 | 2(Loss) | true |
| simdjson (reflection) | 528.27 | 0.169898 | 6391.52ms | 31235 | 2560 | 2.34957e+07 | 56387.8 | 0.117873 | 9.42019 | 38.2539 | 7.04537 | 0.0153636 | 9.83722e-05 | 6.37431e-05 | 3(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3209.82 | 0.0253668 | 3966.01ms | 108313 | 2560 | 170597 | 32181 | 0.00325904 | 1.57228 | 7.40082 | 1.50827 | 0.00210218 | 3.16971e-05 | 2.26845e-05 | 1(Win) | true |
| Glaze | 2221.45 | 0.068295 | 5417.53ms | 108313 | 640 | 645427 | 46499.1 | 0.0297834 | 2.26378 | 10.0551 | 1.92674 | 0.00310338 | 3.99306e-05 | 2.75821e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2160.37 | 0.0598005 | 5518.99ms | 108313 | 160 | 130808 | 47813.6 | 0.0716854 | 2.34023 | 10.3059 | 1.84188 | 0.0027634 | 7.4437e-06 | 4.09692e-06 | 3(Loss) | true |
| simdjson (reflection) | 1665.35 | 0.018885 | 6959.73ms | 108313 | 4890 | 670960 | 62026.3 | 0.0138481 | 3.03302 | 13.1045 | 2.04129 | 0.00220551 | 3.79175e-05 | 2.77485e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1441.24 | 0.0330375 | 7915.65ms | 108313 | 4890 | 2.74167e+06 | 71671.3 | 0.0330191 | 3.49067 | 14.907 | 2.64242 | 0.0027942 | 4.89153e-05 | 3.46606e-05 | 5(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3814.16 | 0.0931058 | 3638.12ms | 108313 | 160 | 101727 | 27082.1 | 0.0691664 | 1.3234 | 6.65907 | 1.33399 | 0.00187027 | 4.44314e-06 | 2.53894e-06 | 1(Win) | true |
| Glaze | 2462.84 | 0.0672263 | 5133.54ms | 108313 | 640 | 508802 | 41941.6 | 0.128091 | 2.05125 | 9.37268 | 1.76545 | 0.00275354 | 2.14223e-05 | 1.52481e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2428.89 | 0.0351222 | 5180.96ms | 108313 | 640 | 142787 | 42527.9 | 0.0346087 | 2.08177 | 9.56858 | 1.66868 | 0.00251615 | 8.07844e-06 | 4.80379e-06 | 3(Loss) | true |
| simdjson (reflection) | 1707.75 | 0.108335 | 6982.85ms | 108313 | 160 | 687018 | 60486.2 | 0.0617322 | 2.95485 | 12.7977 | 1.96928 | 0.00246375 | 1.71378e-05 | 1.00403e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1545.42 | 0.0465133 | 7614.73ms | 108313 | 2560 | 2.47436e+06 | 66839.7 | 0.00117821 | 3.2586 | 14.2468 | 2.49171 | 0.00292837 | 1.30265e-05 | 8.60498e-06 | 5(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19972.7 | 0.040401 | 1253.89ms | 108313 | 2560 | 11176.6 | 5171.82 | 0.0415919 | 0.254859 | 1.0938 | 0.288839 | 0.000109405 | 3.83005e-06 | 9.30463e-07 | 1(Win) | true |
| simdjson (reflection) | 15058.3 | 0.0868495 | 1425.75ms | 108313 | 640 | 22715.5 | 6859.67 | 0.00350794 | 0.337434 | 1.49385 | 0.193716 | 0.000175547 | 6.3762e-06 | 3.1304e-06 | 2(Loss) | true |
| Glaze | 5611.05 | 0.242142 | 2591.83ms | 108313 | 320 | 635862 | 18409.3 | 0.0115954 | 0.899603 | 3.01787 | 0.397404 | 0.000286438 | 8.68432e-06 | 5.33754e-06 | 3(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20205.4 | 0.036812 | 1251.47ms | 108313 | 4890 | 17318.6 | 5112.26 | 0.0764159 | 0.251804 | 1.08875 | 0.287694 | 0.000109548 | 3.99886e-06 | 1.88804e-06 | 1(Win) | true |
| simdjson (reflection) | 15550.3 | 0.0779856 | 1405.35ms | 108313 | 640 | 17174.9 | 6642.67 | 0.042181 | 0.326944 | 1.48913 | 0.192645 | 0.000183424 | 6.11653e-06 | 3.07269e-06 | 2(Loss) | true |
| Glaze | 6414.25 | 0.0642784 | 2353.74ms | 108313 | 4890 | 523972 | 16104 | 0.0938397 | 0.788176 | 2.97166 | 0.386768 | 0.00028319 | 5.89068e-06 | 3.00764e-06 | 3(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3368.03 | 0.013354 | 5942.14ms | 183677 | 4890 | 235879 | 52009 | 0.0457646 | 1.49787 | 6.8462 | 1.13769 | 0.00169939 | 9.44688e-06 | 5.84626e-06 | 1(Win) | true |
| Jsonifier | 2938.51 | 0.054571 | 6721.07ms | 183677 | 160 | 169317 | 59611.2 | 0.0808912 | 1.71878 | 6.95664 | 1.54562 | 0.00219594 | 9.11927e-06 | 5.92072e-06 | 2(Loss) | true |
| simdjson (reflection) | 2686.37 | 0.0864505 | 7258.38ms | 183677 | 160 | 508433 | 65206.3 | 0.0531097 | 1.88087 | 8.31028 | 1.22628 | 0.00130269 | 1.55164e-05 | 5.51239e-06 | 3(Loss) | true |
| Glaze | 2585.2 | 0.0341351 | 7570.29ms | 183677 | 640 | 342377 | 67758 | 0.000532683 | 1.9552 | 8.7666 | 1.71796 | 0.00317919 | 1.90382e-05 | 1.12545e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2328.84 | 0.0509836 | 8331.76ms | 183677 | 1280 | 1.88236e+06 | 75217 | 0.0240943 | 2.16146 | 9.38321 | 1.58252 | 0.00171344 | 0.000137648 | 1.85831e-05 | 5(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3755.21 | 0.0389421 | 5622.94ms | 183677 | 1280 | 422366 | 46646.7 | 0.00608333 | 1.34109 | 6.40735 | 1.03452 | 0.00145328 | 9.83384e-06 | 6.60977e-06 | 1(Win) | true |
| Jsonifier | 3204.07 | 0.0336245 | 6434.75ms | 183677 | 1280 | 432540 | 54670.4 | 0.0447125 | 1.5734 | 6.51762 | 1.44243 | 0.00201457 | 5.92923e-06 | 2.47973e-06 | 2(Loss) | true |
| Glaze | 2791.31 | 0.031685 | 7235.71ms | 183677 | 640 | 253035 | 62754.7 | 0.0412689 | 1.81101 | 8.3632 | 1.62297 | 0.00299172 | 3.28362e-06 | 1.19095e-06 | 3(Loss) | true |
| simdjson (reflection) | 2765.57 | 0.0380839 | 7318.01ms | 183677 | 1280 | 744787 | 63338.8 | 0.00552491 | 1.83712 | 8.13901 | 1.18581 | 0.00136249 | 9.43827e-06 | 5.08705e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2489.51 | 0.0339827 | 7961.82ms | 183677 | 4890 | 2.79582e+06 | 70362.6 | 0.0120884 | 2.01842 | 8.99345 | 1.49403 | 0.00170474 | 1.33336e-05 | 5.28402e-06 | 5(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 25985.2 | 0.0723391 | 1517.64ms | 213963 | 30 | 968.041 | 7852.6 | 0.0381893 | 0.195786 | 0.625482 | 0.146194 | 7.5714e-05 | 9.34741e-07 | 1.5579e-07 | 1(Win) | true |
| Glaze | 5389.97 | 0.0790971 | 4536.63ms | 213963 | 2560 | 2.29544e+06 | 37857.6 | 0.0188696 | 0.932433 | 3.5942 | 0.575291 | 0.000546055 | 2.06118e-05 | 1.36195e-05 | 2(Loss) | true |
| simdjson (reflection) | 463.755 | 0.362792 | 5661.41ms | 213963 | 320 | 8.1539e+08 | 439997 | 0.273089 | 10.7536 | 41.6914 | 8.45658 | 0.0396713 | 0.21227 | 0.000475199 | 3(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 26591.5 | 0.0653956 | 1511.99ms | 213963 | 40 | 1007.28 | 7673.55 | 0.0123787 | 0.194789 | 0.623014 | 0.145637 | 6.3095e-05 | 5.37476e-06 | 3.85581e-06 | 1(Win) | true |
| Glaze | 6300.64 | 0.170362 | 3975.07ms | 213963 | 4890 | 1.48855e+07 | 32385.7 | 0.198211 | 0.794135 | 3.56743 | 0.569169 | 0.000542633 | 8.73954e-06 | 4.89258e-06 | 2(Loss) | true |
| simdjson (reflection) | 466.115 | 0.360373 | 5672.77ms | 213963 | 320 | 7.96427e+08 | 437769 | 0.308685 | 10.7058 | 41.6908 | 8.456 | 0.042111 | 0.216192 | 0.000554301 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 836.095 | 0.130246 | 6592.97ms | 1834197 | 30 | 2.22758e+08 | 2.09214e+06 | 0.0929173 | 6.01973 | 25.516 | 5.77962 | 0.0362322 | 0.0828848 | 0.00255043 | 1(Win) | true |
| Jsonifier (two-stage) | 714.801 | 0.123423 | 7662.9ms | 1834197 | 80 | 7.29799e+08 | 2.44715e+06 | 0.377241 | 7.00849 | 29.8089 | 6.18428 | 0.0418663 | 0.146038 | 0.00973365 | 2(Loss) | true |
| Glaze | 653.993 | 0.0862115 | 8334.24ms | 1834197 | 160 | 8.50739e+08 | 2.67469e+06 | 0.236918 | 7.6498 | 32.3736 | 6.3238 | 0.0346072 | 0.0835471 | 0.0036918 | 3(Loss) | true |
| simdjson (reflection) | 619.767 | 0.0612195 | 8783.71ms | 1834197 | 160 | 4.77678e+08 | 2.82239e+06 | 0.162774 | 8.1402 | 34.8334 | 6.48967 | 0.0369364 | 0.135894 | 0.00755803 | 4(Loss) | true |
| simdjson (ondemand) | 530.928 | 0.133278 | 10315.9ms | 1834197 | 80 | 1.5425e+09 | 3.29466e+06 | 0.0642726 | 9.43941 | 38.0357 | 7.35418 | 0.0417746 | 0.148514 | 0.00973428 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 921.891 | 0.185589 | 6652.92ms | 1834197 | 30 | 3.72012e+08 | 1.89743e+06 | 0.102644 | 5.44757 | 22.5131 | 5.0806 | 0.0355 | 0.0565817 | 0.00516371 | 1(Win) | true |
| Jsonifier (two-stage) | 788.498 | 0.0524186 | 7571.75ms | 1834197 | 160 | 2.16363e+08 | 2.21843e+06 | 0.0945465 | 6.37839 | 26.8068 | 5.48513 | 0.0409841 | 0.119591 | 0.00389915 | 2(Loss) | true |
| Glaze | 722.239 | 0.0616978 | 8268.98ms | 1834197 | 160 | 3.57265e+08 | 2.42195e+06 | 0.0190547 | 6.94954 | 29.3656 | 5.62362 | 0.0331142 | 0.0598196 | 0.00366885 | 3(Loss) | true |
| simdjson (reflection) | 686.383 | 0.0526344 | 8553.46ms | 1834197 | 80 | 1.43942e+08 | 2.54847e+06 | 0.0730437 | 7.34685 | 31.8036 | 5.77333 | 0.0320177 | 0.111923 | 0.00350844 | 4(Loss) | true |
| simdjson (ondemand) | 577.87 | 0.0795708 | 10091.7ms | 1834197 | 80 | 4.64119e+08 | 3.02702e+06 | 0.0246834 | 8.72173 | 35.0131 | 6.65237 | 0.0371507 | 0.118641 | 0.0237046 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1298.24 | 0.0750353 | 8552.75ms | 1834197 | 30 | 3.06645e+07 | 1.34739e+06 | 0.135889 | 3.88809 | 13.1333 | 0.799078 | 0.00231071 | 0.060403 | 0.000216734 | 1(Win) | true |
| Glaze | 981.979 | 0.200291 | 5530.73ms | 1833577 | 160 | 2.03534e+09 | 1.78073e+06 | 0.0186192 | 5.12822 | 16.0488 | 1.05286 | 0.000995677 | 0.049589 | 9.92629e-05 | 2(Loss) | true |
| simdjson (reflection) | 883.168 | 0.032504 | 6466.25ms | 1922245 | 40 | 1.82081e+07 | 2.0757e+06 | 0.0698122 | 5.71409 | 18.1523 | 2.01851 | 0.0263587 | 0.0502403 | 0.000219886 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1299.78 | 0.0344596 | 8553.19ms | 1834197 | 160 | 3.44105e+07 | 1.34578e+06 | 0.126695 | 3.88442 | 13.1332 | 0.799039 | 0.00224277 | 0.0604543 | 0.000172034 | 1(Win) | true |
| Glaze | 979.877 | 0.129353 | 5558.43ms | 1833577 | 160 | 8.52568e+08 | 1.78455e+06 | 0.00793437 | 5.15452 | 16.048 | 1.05269 | 0.000995622 | 0.049528 | 0.000169297 | 2(Loss) | true |
| simdjson (reflection) | 883.619 | 0.0143839 | 6466.21ms | 1922245 | 40 | 3.56207e+06 | 2.07464e+06 | 0.0157811 | 5.71355 | 18.1521 | 2.01847 | 0.0263143 | 0.0501029 | 0.000231279 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2541.68 | 0.107031 | 8622.99ms | 7351818 | 160 | 1.39472e+09 | 2.75851e+06 | 0.404593 | 1.97092 | 8.35488 | 1.58777 | 0.0118606 | 0.0613811 | 0.00331083 | 1(Win) | true |
| Jsonifier | 2423.82 | 0.101436 | 8986.64ms | 7351818 | 80 | 6.88753e+08 | 2.89263e+06 | 0.165976 | 2.05983 | 8.78654 | 2.07722 | 0.00892984 | 0.0342188 | 0.00102611 | 2(Loss) | true |
| simdjson (reflection) | 2246.41 | 0.064733 | 9718.99ms | 7351818 | 160 | 6.53104e+08 | 3.12108e+06 | 0.380769 | 2.24024 | 9.7064 | 1.65692 | 0.00904143 | 0.0585418 | 0.00171125 | 3(Loss) | true |
| Glaze | 2063.9 | 0.149122 | 5118.4ms | 7351818 | 30 | 7.69871e+08 | 3.39709e+06 | 0.285978 | 2.43703 | 11.2406 | 2.23967 | 0.00906693 | 0.0335591 | 0.000965462 | 4(Loss) | true |
| simdjson (ondemand) | 1958.48 | 0.183754 | 5435.44ms | 7351818 | 30 | 1.29822e+09 | 3.57995e+06 | 0.0484366 | 2.58412 | 10.5051 | 1.87229 | 0.0102688 | 0.0614092 | 0.00538665 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2777.31 | 0.0779692 | 8594.51ms | 7351818 | 160 | 6.1988e+08 | 2.52447e+06 | 0.05195 | 1.80223 | 7.6058 | 1.41341 | 0.0115845 | 0.0546758 | 0.0010712 | 1(Win) | true |
| Jsonifier | 2638.1 | 0.0649647 | 8972.59ms | 7351818 | 160 | 4.7696e+08 | 2.65768e+06 | 0.256501 | 1.89834 | 8.03736 | 1.90278 | 0.00870516 | 0.0274322 | 0.000449578 | 2(Loss) | true |
| simdjson (reflection) | 2430.8 | 0.13087 | 9529.09ms | 7351818 | 160 | 2.27979e+09 | 2.88434e+06 | 0.105024 | 2.0645 | 8.95056 | 1.47816 | 0.00790538 | 0.0521445 | 0.0041338 | 3(Loss) | true |
| Glaze | 2220.28 | 0.126431 | 5102.93ms | 7351818 | 30 | 4.78191e+08 | 3.15781e+06 | 0.195096 | 2.26426 | 10.49 | 2.06508 | 0.00855446 | 0.0275965 | 0.000573513 | 4(Loss) | true |
| simdjson (ondemand) | 2079.99 | 0.257811 | 5343.92ms | 7351818 | 40 | 3.02084e+09 | 3.3708e+06 | 0.376768 | 2.41266 | 9.75062 | 1.69725 | 0.00909191 | 0.0536395 | 0.010965 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6320.46 | 0.0661816 | 9509.92ms | 9930848 | 320 | 3.14703e+08 | 1.49844e+06 | 0.212657 | 0.795903 | 2.51822 | 0.147587 | 0.000345044 | 0.0249843 | 0.000271977 | 1(Win) | true |
| Glaze | 3635.74 | 0.143289 | 8162.21ms | 9930228 | 160 | 2.22885e+09 | 2.60475e+06 | 0.0512976 | 1.37527 | 4.41557 | 0.474372 | 0.000795399 | 0.041717 | 0.00261332 | 2(Loss) | true |
| simdjson (reflection) | 271.703 | 0.186526 | 10576.9ms | 10018896 | 30 | 1.29078e+11 | 3.51662e+07 | 0.143882 | 13.6451 | 38.7655 | 5.79716 | 0.0262146 | 0.268749 | 0.126208 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6320.81 | 0.175482 | 9495.39ms | 9930848 | 40 | 2.76535e+08 | 1.49835e+06 | 0.0356993 | 0.796308 | 2.51818 | 0.14758 | 0.000363637 | 0.0249799 | 0.000460593 | 1(Win) | true |
| Glaze | 4019.13 | 0.234598 | 7344.94ms | 9930228 | 40 | 1.22225e+09 | 2.35628e+06 | 0.00772238 | 1.25141 | 4.4153 | 0.474313 | 0.000785458 | 0.0224236 | 0.000424064 | 2(Loss) | true |
| simdjson (reflection) | 306.343 | 1.92745 | 9352.86ms | 10018896 | 30 | 1.0842e+13 | 3.11897e+07 | 0.689507 | 13.2489 | 38.7853 | 5.80152 | 0.0258138 | 0.29146 | 0.142776 | 3(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 845.435 | 0.0601388 | 6456.24ms | 1834197 | 160 | 2.4772e+08 | 2.06903e+06 | 0.0945871 | 5.95639 | 25.0821 | 5.64263 | 0.0370487 | 0.0833002 | 0.000211986 | 1(Win) | true |
| Jsonifier (two-stage) | 720.186 | 0.107027 | 7584.22ms | 1834197 | 80 | 5.40604e+08 | 2.42885e+06 | 0.133628 | 6.97983 | 29.3736 | 6.06564 | 0.0427836 | 0.146958 | 0.0015607 | 2(Loss) | true |
| Glaze | 656.496 | 0.0418099 | 8300.86ms | 1834197 | 160 | 1.98567e+08 | 2.66449e+06 | 0.131342 | 7.69003 | 32.3366 | 6.31554 | 0.0349466 | 0.0832925 | 0.000574512 | 3(Loss) | true |
| simdjson (reflection) | 619.983 | 0.0620087 | 8785.08ms | 1834197 | 160 | 4.89732e+08 | 2.82141e+06 | 0.103844 | 8.13802 | 34.8364 | 6.49697 | 0.036911 | 0.136512 | 0.000341113 | 4(Loss) | true |
| simdjson (ondemand) | 535.413 | 0.141782 | 10187.6ms | 1834197 | 30 | 6.43695e+08 | 3.26706e+06 | 0.0731293 | 9.39355 | 37.4492 | 7.33897 | 0.0422521 | 0.148088 | 0.000582725 | 5(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 942.715 | 0.0920447 | 6474.1ms | 1834197 | 80 | 2.33356e+08 | 1.85552e+06 | 0.29491 | 5.32984 | 22.1049 | 4.95266 | 0.0362165 | 0.0567797 | 0.000225276 | 1(Win) | true |
| Jsonifier (two-stage) | 802.534 | 0.0503429 | 7531.66ms | 1834197 | 160 | 1.92646e+08 | 2.17963e+06 | 0.22637 | 6.27687 | 26.3978 | 5.37607 | 0.041543 | 0.120093 | 0.000245325 | 2(Loss) | true |
| Glaze | 719.855 | 0.0553663 | 8306.58ms | 1834197 | 30 | 5.4302e+07 | 2.42997e+06 | 0.0206602 | 7.01229 | 29.3558 | 5.62413 | 0.0337915 | 0.0594703 | 0.000267074 | 3(Loss) | true |
| simdjson (reflection) | 690.582 | 0.145058 | 8563.27ms | 1834197 | 30 | 4.0501e+08 | 2.53297e+06 | 0.00029741 | 7.3153 | 31.8243 | 5.79337 | 0.0318403 | 0.11217 | 0.00109905 | 4(Loss) | true |
| simdjson (ondemand) | 583.182 | 0.0646741 | 10052.6ms | 1834197 | 160 | 6.02093e+08 | 2.99945e+06 | 0.00569009 | 8.63065 | 34.453 | 6.64592 | 0.0372631 | 0.118976 | 0.000544697 | 5(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1293.76 | 0.137348 | 8574.42ms | 1834197 | 80 | 2.75877e+08 | 1.35205e+06 | 0.00210796 | 3.89334 | 13.1201 | 0.79908 | 0.00177249 | 0.0616749 | 0.000117068 | 1(Win) | true |
| Glaze | 958.466 | 0.265423 | 5700.9ms | 1833577 | 160 | 3.75182e+09 | 1.82441e+06 | 0.410927 | 5.23769 | 16.0435 | 1.05288 | 0.000998642 | 0.0766521 | 0.000151432 | 2(Loss) | true |
| simdjson (reflection) | 888.712 | 0.0263673 | 6423.47ms | 1922245 | 160 | 4.73311e+07 | 2.06276e+06 | 0.166988 | 5.68144 | 18.1621 | 2.01852 | 0.0246174 | 0.0519423 | 0.000106971 | 3(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1297.45 | 0.0620884 | 8542.71ms | 1834197 | 80 | 5.6056e+07 | 1.3482e+06 | 0.0595456 | 3.88806 | 13.1199 | 0.79904 | 0.00174471 | 0.0616282 | 9.69702e-05 | 1(Win) | true |
| Glaze | 1002.42 | 0.269008 | 5432.11ms | 1833577 | 160 | 3.52327e+09 | 1.74441e+06 | 0.101865 | 5.02356 | 16.0427 | 1.0527 | 0.000994112 | 0.0495293 | 0.000164852 | 2(Loss) | true |
| simdjson (reflection) | 890.745 | 0.0446625 | 6416.66ms | 1922245 | 80 | 6.75907e+07 | 2.05805e+06 | 0.0106716 | 5.67667 | 18.1619 | 2.01848 | 0.0245876 | 0.0519765 | 0.000198837 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2558.09 | 0.208931 | 8581.66ms | 7351818 | 30 | 9.83756e+08 | 2.74081e+06 | 0.643129 | 1.94403 | 8.24515 | 1.55788 | 0.0119509 | 0.0618819 | 0.002106 | 1(Win) | true |
| Jsonifier | 2480.15 | 0.0817658 | 8797.47ms | 7351818 | 80 | 4.27434e+08 | 2.82695e+06 | 0.0122745 | 2.0247 | 8.67708 | 2.04263 | 0.00905924 | 0.0343554 | 0.000289893 | 2(Loss) | true |
| simdjson (reflection) | 2251.68 | 0.0585191 | 9696.99ms | 7351818 | 160 | 5.31242e+08 | 3.11379e+06 | 0.230063 | 2.23809 | 9.70704 | 1.6587 | 0.00910173 | 0.058516 | 0.000823936 | 3(Loss) | true |
| Glaze | 2072.47 | 0.0752704 | 5113.48ms | 7351818 | 80 | 5.18745e+08 | 3.38304e+06 | 0.0405384 | 2.43301 | 11.2347 | 2.23762 | 0.00905191 | 0.0336095 | 0.00118296 | 4(Loss) | true |
| simdjson (ondemand) | 1960.66 | 0.110159 | 5391.09ms | 7351818 | 80 | 1.24141e+09 | 3.57597e+06 | 0.0467393 | 2.55752 | 10.3588 | 1.86883 | 0.0102979 | 0.0613653 | 0.00129864 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2801.17 | 0.173346 | 8552.36ms | 7351818 | 80 | 1.50601e+09 | 2.50296e+06 | 1.25398 | 1.78333 | 7.5028 | 1.38588 | 0.0117409 | 0.0552077 | 0.00271646 | 1(Win) | true |
| Jsonifier | 2707.57 | 0.0623695 | 8795.54ms | 7351818 | 40 | 1.04336e+08 | 2.58949e+06 | 0.0315705 | 1.86207 | 7.93435 | 1.87052 | 0.00890493 | 0.027786 | 0.000191232 | 2(Loss) | true |
| simdjson (reflection) | 2482.79 | 0.0708895 | 9536.77ms | 7351818 | 40 | 1.60299e+08 | 2.82393e+06 | 0.0289816 | 2.0312 | 8.95523 | 1.48303 | 0.00785139 | 0.0521101 | 0.000539084 | 3(Loss) | true |
| Glaze | 2204.16 | 0.10185 | 5133.57ms | 7351818 | 40 | 4.19844e+08 | 3.18092e+06 | 0.228958 | 2.28553 | 10.4912 | 2.06524 | 0.00874699 | 0.0276406 | 0.000357864 | 4(Loss) | true |
| simdjson (ondemand) | 2140.74 | 0.126074 | 5324.86ms | 7351818 | 30 | 5.11487e+08 | 3.27514e+06 | 0.209981 | 2.35154 | 9.61118 | 1.69576 | 0.00904392 | 0.0537896 | 0.00145819 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6235.89 | 0.0620313 | 9651.78ms | 9930848 | 320 | 2.84019e+08 | 1.51876e+06 | 0.0654051 | 0.807659 | 2.51581 | 0.147546 | 0.000326081 | 0.0250864 | 0.000593485 | 1(Win) | true |
| Glaze | 2978.22 | 0.595249 | 9830.05ms | 9930228 | 40 | 1.43306e+10 | 3.17982e+06 | 0.578763 | 1.68171 | 4.41437 | 0.474336 | 0.000715746 | 0.075734 | 0.0174977 | 2(Loss) | true |
| simdjson (reflection) | 394.289 | 0.370362 | 7274.79ms | 10018896 | 30 | 2.4165e+11 | 2.42329e+07 | 0.172727 | 12.7229 | 38.7489 | 5.79802 | 0.0227774 | 0.313614 | 0.159722 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6246.29 | 0.0597518 | 9614.06ms | 9930848 | 160 | 1.31326e+08 | 1.51623e+06 | 0.00657387 | 0.80625 | 2.51578 | 0.147539 | 0.00033375 | 0.0250597 | 0.00019738 | 1(Win) | true |
| Glaze | 4088.26 | 0.244189 | 7264.11ms | 9930228 | 30 | 9.59879e+08 | 2.31644e+06 | 0.210595 | 1.23453 | 4.414 | 0.474254 | 0.000774766 | 0.0224352 | 0.000407483 | 2(Loss) | true |
| simdjson (reflection) | 342.338 | 1.50942 | 8423.93ms | 10018896 | 30 | 5.32444e+12 | 2.79104e+07 | 0.487766 | 12.8897 | 38.772 | 5.80014 | 0.0233653 | 0.289008 | 0.146556 | 3(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1197.35 | 0.0404207 | 9579.33ms | 461466 | 320 | 7.06308e+06 | 367552 | 0.0398059 | 4.22089 | 17.8094 | 3.2223 | 0.0192569 | 0.0441569 | 9.04658e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1089.99 | 0.114202 | 5231.08ms | 461466 | 160 | 3.40174e+07 | 403753 | 0.188766 | 4.62357 | 19.2173 | 3.44868 | 0.022549 | 0.0894678 | 0.000168837 | 2(Loss) | true |
| Glaze | 1053.03 | 0.182117 | 5400.61ms | 461466 | 80 | 4.63435e+07 | 417926 | 0.0662238 | 4.78412 | 20.1525 | 3.94161 | 0.0243223 | 0.03391 | 0.000107023 | 3(Loss) | true |
| simdjson (ondemand) | 977.417 | 0.179833 | 5855.86ms | 461466 | 160 | 1.04901e+08 | 450256 | 0.0433662 | 5.15097 | 20.2893 | 3.60155 | 0.0122087 | 0.0850626 | 0.000602252 | 4(Loss) | true |
| simdjson (reflection) | 966.002 | 0.0621086 | 5903.69ms | 461466 | 640 | 5.12397e+07 | 455577 | 0.212507 | 5.22615 | 18.5842 | 3.24557 | 0.0105076 | 0.0574983 | 0.000337819 | 5(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1627.94 | 0.0336427 | 8751.64ms | 461466 | 1280 | 1.05876e+07 | 270335 | 0.0174958 | 3.10838 | 13.62 | 2.29702 | 0.0170618 | 0.00420672 | 1.3019e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1459.67 | 0.0505517 | 9670.94ms | 461466 | 1280 | 2.97337e+07 | 301498 | 0.0857257 | 3.44882 | 15.0203 | 2.52168 | 0.0197429 | 0.0272787 | 2.31633e-05 | 2(Loss) | true |
| Glaze | 1322.22 | 0.177263 | 5176.98ms | 461466 | 160 | 5.56964e+07 | 332840 | 0.00438293 | 3.82033 | 16.323 | 3.08259 | 0.0220731 | 0.0101651 | 2.79138e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1282.79 | 0.145606 | 5232.26ms | 461466 | 640 | 1.59702e+08 | 343072 | 0.249183 | 3.9129 | 16.3005 | 2.70006 | 0.00427311 | 0.0269939 | 3.06631e-05 | 4(Loss) | true |
| simdjson (reflection) | 1194.51 | 0.102466 | 5596.73ms | 461466 | 640 | 9.12106e+07 | 368427 | 0.237727 | 4.20461 | 14.9756 | 2.41374 | 0.00421051 | 0.0243085 | 8.45674e-05 | 5(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17956.5 | 0.0386991 | 3216.88ms | 461466 | 2560 | 230291 | 24508.6 | 0.305321 | 0.282307 | 1.43293 | 0.226548 | 0.000196206 | 0.00487413 | 6.02191e-06 | 1(Win) | true |
| simdjson (reflection) | 11360.9 | 0.161989 | 4634.76ms | 461466 | 2560 | 1.00801e+07 | 38737.1 | 0.239396 | 0.44506 | 2.24062 | 0.318281 | 0.00194896 | 0.00639773 | 4.0005e-05 | 2(Loss) | true |
| Glaze | 4606.07 | 0.0398867 | 5322.74ms | 461466 | 1280 | 1.85903e+06 | 95545.3 | 0.0798189 | 1.09659 | 4.66003 | 0.714445 | 0.00892719 | 0.0466754 | 2.09658e-05 | 3(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17938.2 | 0.117151 | 3209.29ms | 461466 | 640 | 528680 | 24533.6 | 0.124991 | 0.282829 | 1.43391 | 0.226281 | 0.00019754 | 0.00468134 | 2.48021e-05 | 1(Win) | true |
| simdjson (reflection) | 11277.5 | 0.226517 | 4625.47ms | 461466 | 160 | 1.25018e+06 | 39023.4 | 0.039864 | 0.449158 | 2.23952 | 0.31803 | 0.00213396 | 0.00833333 | 1.64693e-05 | 2(Loss) | true |
| Glaze | 5201.38 | 0.056015 | 9250.5ms | 461466 | 640 | 1.43758e+06 | 84609.9 | 0.139647 | 0.970216 | 4.64554 | 0.711034 | 0.00900923 | 0.013477 | 2.52524e-05 | 3(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1628.96 | 0.0610069 | 5530.31ms | 728486 | 160 | 1.08318e+07 | 426492 | 0.05951 | 3.10193 | 12.7204 | 2.19876 | 0.0149068 | 0.0749189 | 4.80534e-05 | 1(Win) | true |
| Jsonifier | 1499.79 | 0.0282757 | 5992.77ms | 728486 | 640 | 1.09797e+07 | 463225 | 0.112912 | 3.36591 | 13.411 | 2.59403 | 0.0126257 | 0.0415664 | 7.19064e-05 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1473.17 | 0.22534 | 6074.86ms | 728486 | 80 | 9.03452e+07 | 471595 | 0.0108132 | 3.39449 | 13.4126 | 2.30412 | 0.00802258 | 0.0764095 | 7.05916e-05 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1470.56 | 0.0758953 | 6114.37ms | 728486 | 640 | 8.22781e+07 | 472430 | 0.292138 | 3.41852 | 12.3394 | 2.08009 | 0.00709085 | 0.0583537 | 5.69911e-05 | 3(Tie) | true |
| Glaze | 1435.7 | 0.0377536 | 6268.64ms | 728486 | 640 | 2.13606e+07 | 483903 | 0.0633313 | 3.51864 | 15.2108 | 2.98489 | 0.0148749 | 0.0314392 | 9.33336e-05 | 5(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2151.63 | 0.0404536 | 5123.39ms | 728486 | 640 | 1.09195e+07 | 322890 | 0.228159 | 2.34589 | 10.0705 | 1.61359 | 0.0131104 | 0.0347978 | 3.34727e-05 | 1(Win) | true |
| simdjson (ondemand) | 1958.97 | 0.0945826 | 5406.45ms | 728486 | 640 | 7.20095e+07 | 354645 | 0.0135628 | 2.57136 | 10.888 | 1.73329 | 0.00284629 | 0.0297022 | 5.87027e-05 | 2(Loss) | true |
| Jsonifier | 1899.23 | 0.0348124 | 5589.31ms | 728486 | 320 | 5.18922e+06 | 365799 | 0.175618 | 2.65887 | 10.7549 | 2.00748 | 0.0111874 | 0.00849974 | 1.61508e-05 | 3(Loss) | true |
| simdjson (reflection) | 1813.49 | 0.147929 | 5777.38ms | 728486 | 160 | 5.13851e+07 | 383094 | 0.05063 | 2.77123 | 10.0508 | 1.5525 | 0.00283473 | 0.0271092 | 2.39195e-05 | 4(Loss) | true |
| Glaze | 1746.2 | 0.0627741 | 6034.96ms | 728486 | 320 | 1.99603e+07 | 397858 | 0.0514793 | 2.88918 | 12.7817 | 2.43988 | 0.0132055 | 0.0118987 | 1.47395e-05 | 5(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20478.7 | 0.0731748 | 4683.12ms | 837491 | 160 | 130316 | 39001.2 | 0.0226705 | 0.24701 | 0.835343 | 0.124872 | 0.000150405 | 0.0120918 | 6.45529e-06 | 1(Win) | true |
| Glaze | 4861.72 | 0.0478095 | 8827.57ms | 837491 | 2560 | 1.57924e+07 | 164282 | 0.0104494 | 1.03307 | 4.43638 | 0.73016 | 0.00590454 | 0.0593476 | 5.96005e-05 | 2(Loss) | true |
| simdjson (reflection) | 531.322 | 0.310632 | 9503.99ms | 837491 | 320 | 6.97731e+09 | 1.50322e+06 | 0.281575 | 9.46453 | 37.2111 | 7.11012 | 0.0290395 | 0.351734 | 0.00219571 | 3(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20541.2 | 0.048394 | 4659.96ms | 837491 | 640 | 226606 | 38882.5 | 0.0591176 | 0.246368 | 0.834691 | 0.124725 | 0.000130236 | 0.0116976 | 1.56606e-05 | 1(Win) | true |
| Glaze | 5721.02 | 0.0963721 | 7555.71ms | 837491 | 640 | 1.1585e+07 | 139607 | 0.0442285 | 0.877815 | 4.42726 | 0.728068 | 0.00588362 | 0.0203773 | 6.38328e-05 | 2(Loss) | true |
| simdjson (reflection) | 534.298 | 0.316568 | 9500.77ms | 837491 | 320 | 7.16599e+09 | 1.49485e+06 | 0.250038 | 9.40146 | 37.2114 | 7.11018 | 0.028981 | 0.352007 | 0.00220981 | 3(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7984.77 | 0.0548605 | 6332.23ms | 466906 | 1280 | 1.19802e+06 | 55765.7 | 0.171913 | 0.634248 | 3.08981 | 0.371932 | 0.000857891 | 1.27552e-05 | 9.77177e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 7944.25 | 0.0369511 | 6345.4ms | 466906 | 2560 | 1.09811e+06 | 56050.1 | 0.107691 | 0.634373 | 3.08868 | 0.371668 | 0.00085657 | 3.00348e-06 | 1.76193e-06 | 2(Loss) | true |
| simdjson (reflection) | 6967.23 | 0.0192337 | 7132.7ms | 466906 | 4890 | 738880 | 63910.1 | 0.0225276 | 0.725478 | 3.56443 | 0.370401 | 0.000853698 | 9.34621e-06 | 7.49309e-06 | 3(Loss) | true |
| simdjson (ondemand) | 6791.46 | 0.0183769 | 7302.38ms | 466906 | 2560 | 371634 | 65564.1 | 0.0310551 | 0.74403 | 3.59603 | 0.371035 | 0.000753019 | 5.18289e-06 | 3.24192e-06 | 4(Loss) | true |
| Glaze | 3229 | 0.0432974 | 7425.45ms | 466906 | 2560 | 9.12612e+06 | 137899 | 0.0466213 | 1.56454 | 6.44431 | 1.02742 | 0.00150494 | 1.14576e-05 | 7.32548e-06 | 5(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8135.33 | 0.0534912 | 6380.02ms | 466906 | 1280 | 1.09719e+06 | 54733.7 | 0.194239 | 0.627461 | 3.05685 | 0.364924 | 0.000864737 | 3.36658e-06 | 2.44127e-06 | 1(Win) | true |
| Jsonifier | 8070 | 0.0305735 | 6324.26ms | 466906 | 4890 | 1.39159e+06 | 55176.8 | 0.0732782 | 0.633183 | 3.0572 | 0.364808 | 0.000870529 | 6.05824e-06 | 5.02897e-06 | 2(Loss) | true |
| simdjson (reflection) | 7043.44 | 0.0367243 | 7196.15ms | 466906 | 1280 | 689934 | 63218.6 | 0.0348125 | 0.723412 | 3.54206 | 0.365254 | 0.000852658 | 7.26525e-06 | 6.24791e-06 | 3(Loss) | true |
| simdjson (ondemand) | 6956.06 | 0.0648026 | 7220.63ms | 466906 | 640 | 1.10128e+06 | 64012.7 | 0.0134208 | 0.734296 | 3.5567 | 0.362581 | 0.000797671 | 7.88435e-06 | 6.50559e-06 | 4(Loss) | true |
| Glaze | 3307.62 | 0.081661 | 7327.66ms | 466906 | 640 | 7.73457e+06 | 134621 | 0.132878 | 1.54741 | 6.39747 | 1.01715 | 0.00150653 | 6.42528e-06 | 5.43806e-06 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9057.42 | 0.111854 | 7405.55ms | 631514 | 80 | 442534 | 66493.4 | 0.0448715 | 0.559868 | 2.72586 | 0.284228 | 0.000586943 | 1.61517e-05 | 1.29253e-05 | 1(Win) | true |
| Jsonifier | 9031.48 | 0.0280954 | 7431.99ms | 631514 | 4890 | 1.71644e+06 | 66684.4 | 0.00319107 | 0.560272 | 2.72767 | 0.284694 | 0.000605416 | 1.63181e-05 | 1.33286e-05 | 2(Loss) | true |
| simdjson (reflection) | 8328.03 | 0.0231462 | 7977.24ms | 631514 | 4890 | 1.37009e+06 | 72317 | 0.0108804 | 0.605702 | 3.00657 | 0.289437 | 0.000636591 | 5.21841e-06 | 3.71879e-06 | 3(Loss) | true |
| simdjson (ondemand) | 8177.31 | 0.0173869 | 8112.58ms | 631514 | 4890 | 801863 | 73650 | 0.0700545 | 0.617842 | 3.02993 | 0.289906 | 0.000564442 | 3.96392e-06 | 2.57019e-06 | 4(Loss) | true |
| Glaze | 3846.3 | 0.0480348 | 8381.48ms | 631514 | 1280 | 7.24105e+06 | 156581 | 0.107847 | 1.31484 | 5.8562 | 0.962311 | 0.00140501 | 2.04741e-05 | 1.77314e-05 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9151.2 | 0.0545304 | 7393.25ms | 631514 | 1280 | 1.64853e+06 | 65812 | 0.00146129 | 0.552034 | 2.70327 | 0.279147 | 0.000573702 | 1.58758e-05 | 1.34721e-05 | 1(Win) | true |
| Jsonifier | 9132.26 | 0.0525198 | 7486.57ms | 631514 | 1280 | 1.53555e+06 | 65948.5 | 0.095408 | 0.552308 | 2.70494 | 0.279568 | 0.000592732 | 9.81644e-06 | 7.9447e-06 | 2(Loss) | true |
| simdjson (reflection) | 8364.93 | 0.021421 | 8016.21ms | 631514 | 2560 | 608924 | 71998 | 0.0499569 | 0.603563 | 3 | 0.288219 | 0.000673171 | 2.7173e-06 | 1.7004e-06 | 3(Loss) | true |
| simdjson (ondemand) | 8261.81 | 0.0291076 | 8101.22ms | 631514 | 4890 | 2.2016e+06 | 72896.7 | 0.00642905 | 0.61153 | 3.00993 | 0.285943 | 0.000584438 | 2.9374e-06 | 1.83414e-06 | 4(Loss) | true |
| Glaze | 3877.77 | 0.0368949 | 8347.14ms | 631514 | 2560 | 8.40574e+06 | 155311 | 0.0688016 | 1.30046 | 5.82432 | 0.955105 | 0.00132069 | 8.40923e-06 | 7.06388e-06 | 5(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2019.44 | 0.0527513 | 5841.97ms | 466906 | 1280 | 1.7317e+07 | 220495 | 0.0490959 | 2.48967 | 7.82178 | 1.31462 | 0.0116079 | 0.0168418 | 0.000241122 | 1(Win) | true |
| Glaze | 1729.02 | 0.0710565 | 6775.06ms | 466906 | 640 | 2.14311e+07 | 257531 | 0.0211405 | 2.91446 | 10.4253 | 1.86977 | 0.0135269 | 0.0148341 | 0.000126795 | 2(Loss) | true |
| Jsonifier (two-stage) | 1707.02 | 0.130885 | 6890.06ms | 466906 | 320 | 3.72999e+07 | 260849 | 0.0243831 | 2.93793 | 9.02451 | 1.431 | 0.0172651 | 0.0387796 | 0.000299599 | 3(Loss) | true |
| simdjson (reflection) | 1586.52 | 0.1896 | 7420.19ms | 466906 | 160 | 4.5307e+07 | 280663 | 0.0068338 | 3.16598 | 10.1644 | 1.53149 | 0.0134844 | 0.0321209 | 0.000153551 | 4(Loss) | true |
| simdjson (ondemand) | 1141.84 | 0.123673 | 5063.25ms | 466906 | 320 | 7.44299e+07 | 389963 | 0.0227854 | 4.36529 | 13.1698 | 2.75715 | 0.0141369 | 0.0519465 | 0.000136002 | 5(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2606.54 | 0.0762394 | 5313.72ms | 466906 | 1280 | 2.1712e+07 | 170830 | 0.121447 | 1.92009 | 6.38826 | 0.99016 | 0.00876273 | 0.00249662 | 3.88127e-05 | 1(Win) | true |
| Glaze | 2272.38 | 0.151747 | 5889.58ms | 466906 | 320 | 2.82936e+07 | 195952 | 0.0826258 | 2.20874 | 8.98589 | 1.54247 | 0.00684852 | 0.00141519 | 2.33117e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2170.83 | 0.067801 | 6237.22ms | 466906 | 1280 | 2.47565e+07 | 205118 | 0.100476 | 2.30343 | 7.59207 | 1.107 | 0.0128774 | 0.00819924 | 2.09139e-05 | 3(Loss) | true |
| simdjson (reflection) | 1868 | 0.379567 | 7024.48ms | 466906 | 80 | 6.54895e+07 | 238370 | 0.0408775 | 2.68373 | 9.10561 | 1.2836 | 0.00871731 | 0.0176536 | 4.92337e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1335.14 | 0.107166 | 9396.26ms | 466906 | 640 | 8.17514e+07 | 333504 | 0.253354 | 3.73862 | 11.8194 | 2.45234 | 0.0105463 | 0.0110172 | 3.86554e-05 | 5(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17909 | 0.095302 | 3320.82ms | 475954 | 80 | 46674.6 | 25345 | 0.0112461 | 0.282653 | 1.00424 | 0.147998 | 0.000269774 | 0.00118386 | 8.50923e-06 | 1(Win) | true |
| simdjson (reflection) | 11034.5 | 0.0727805 | 4882.12ms | 475954 | 640 | 573636 | 41135.2 | 0.0563942 | 0.453336 | 1.30937 | 0.183999 | 0.000264728 | 0.000459163 | 1.37553e-05 | 2(Loss) | true |
| Glaze | 7721.32 | 0.091154 | 6693.58ms | 475954 | 4890 | 1.40413e+07 | 58785.9 | 0.384688 | 0.651846 | 2.22759 | 0.324916 | 0.000276325 | 0.0195694 | 2.0054e-05 | 3(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17949.5 | 0.0493407 | 3298.76ms | 475954 | 30 | 4670.42 | 25287.8 | 0.190768 | 0.28232 | 1.00314 | 0.14775 | 0.000283361 | 0.000983498 | 9.03449e-05 | 1(Win) | true |
| simdjson (reflection) | 11040 | 0.105455 | 4881.5ms | 475954 | 1280 | 2.40625e+06 | 41114.6 | 0.00930222 | 0.455081 | 1.30829 | 0.183753 | 0.000274148 | 0.00170083 | 1.91113e-05 | 2(Loss) | true |
| Glaze | 9052.23 | 0.171625 | 5786.01ms | 475954 | 2560 | 1.89591e+07 | 50142.9 | 0.273434 | 0.555709 | 2.21522 | 0.322105 | 0.000266824 | 0.00299523 | 9.82894e-06 | 3(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2203.29 | 0.0974901 | 7223.34ms | 631514 | 320 | 2.27244e+07 | 273345 | 0.00681535 | 2.2859 | 7.13132 | 1.07135 | 0.0121941 | 0.0407249 | 0.000161442 | 1(Win) | true |
| simdjson (reflection) | 2089.07 | 0.17851 | 7740.34ms | 631514 | 160 | 4.23748e+07 | 288291 | 0.633106 | 2.41049 | 7.88574 | 1.14757 | 0.010031 | 0.0316619 | 0.000322093 | 2(Loss) | true |
| Jsonifier | 1928.55 | 0.193614 | 8163.75ms | 631514 | 40 | 1.4623e+07 | 312285 | 0.00112078 | 2.61601 | 7.29355 | 1.33499 | 0.0103779 | 0.0273418 | 0.000141565 | 3(Loss) | true |
| Glaze | 1825.92 | 0.074733 | 8681.71ms | 631514 | 160 | 9.72184e+06 | 329839 | 0.0368402 | 2.76038 | 9.28847 | 1.71576 | 0.0105347 | 0.0185522 | 0.000131242 | 4(Loss) | true |
| simdjson (ondemand) | 1509.95 | 0.0951845 | 5213.41ms | 631514 | 640 | 9.2247e+07 | 398859 | 0.14492 | 3.32702 | 10.1145 | 2.05533 | 0.0108851 | 0.048125 | 0.000494904 | 5(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2732.13 | 0.0912829 | 6638.95ms | 631514 | 640 | 2.59132e+07 | 220435 | 0.19166 | 1.83471 | 6.07353 | 0.832336 | 0.00962768 | 0.0122253 | 0.000119262 | 1(Win) | true |
| simdjson (reflection) | 2414.35 | 0.105703 | 7308.36ms | 631514 | 1280 | 8.89919e+07 | 249449 | 0.134444 | 2.06916 | 7.11025 | 0.966537 | 0.0067528 | 0.020916 | 0.000130771 | 2(Loss) | true |
| Jsonifier | 2315.97 | 0.0544039 | 7510.11ms | 631514 | 640 | 1.28097e+07 | 260046 | 0.239088 | 2.18495 | 6.23778 | 1.09628 | 0.00793855 | 0.00538403 | 0.000234122 | 3(Loss) | true |
| Glaze | 2218.45 | 0.0982879 | 7810.33ms | 631514 | 640 | 4.55667e+07 | 271477 | 0.100195 | 2.26886 | 8.22899 | 1.47596 | 0.0062035 | 0.00227214 | 8.51847e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1763.3 | 0.112464 | 9671.33ms | 631514 | 320 | 4.72162e+07 | 341551 | 0.0229026 | 2.8594 | 9.11251 | 1.82909 | 0.00797345 | 0.0176792 | 0.00016555 | 5(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 21220.9 | 0.0543455 | 4066.93ms | 716365 | 30 | 9183.07 | 32193.6 | 0.0652912 | 0.238595 | 0.715956 | 0.0983521 | 0.000204319 | 0.00457318 | 3.22461e-05 | 1(Win) | true |
| Glaze | 5177.21 | 0.131458 | 7152.53ms | 716365 | 2560 | 7.7036e+07 | 131959 | 0.0404678 | 0.96568 | 2.70595 | 0.438067 | 0.000357763 | 0.0501977 | 4.33269e-05 | 2(Loss) | true |
| simdjson (reflection) | 520.921 | 0.240298 | 8348.5ms | 716365 | 320 | 3.17816e+09 | 1.31148e+06 | 0.0889788 | 9.59777 | 30.5786 | 6.83213 | 0.0692943 | 0.289636 | 0.000524558 | 3(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 21156.8 | 0.0666395 | 4016ms | 716365 | 1280 | 592710 | 32291.2 | 0.0153607 | 0.236982 | 0.715198 | 0.0981804 | 0.000180647 | 0.00427973 | 5.80513e-06 | 1(Win) | true |
| Glaze | 6567.32 | 0.114124 | 5702.55ms | 716365 | 2560 | 3.60819e+07 | 104027 | 0.012068 | 0.764511 | 2.69622 | 0.435824 | 0.000337555 | 0.00421174 | 1.67834e-05 | 2(Loss) | true |
| simdjson (reflection) | 524.163 | 0.230558 | 8319.45ms | 716365 | 320 | 2.88966e+09 | 1.30337e+06 | 0.324702 | 9.5789 | 30.5777 | 6.83138 | 0.0693665 | 0.290283 | 0.000449588 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2409.46 | 0.104766 | 836.809ms | 2632 | 160 | 190.588 | 1041.76 | 0.0462174 | 2.18158 | 8.22112 | 1.33093 | 0.000759878 | 2.13716e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 2053.56 | 0.176521 | 855.038ms | 2632 | 160 | 744.853 | 1222.3 | 0.0194268 | 2.54478 | 10.2044 | 1.61854 | 0.00179284 | 6.64894e-05 | 3.08701e-05 | 2(Loss) | true |
| Glaze | 1994.4 | 0.0480204 | 856.999ms | 2632 | 4890 | 1786.1 | 1258.56 | 0.165988 | 2.62013 | 11.0616 | 2.13032 | 0.00045888 | 7.42785e-05 | 3.46529e-05 | 3(Loss) | true |
| simdjson (reflection) | 1752.42 | 0.0776848 | 873.675ms | 2632 | 160 | 198.101 | 1432.34 | 0.0283546 | 2.96819 | 9.53153 | 1.57219 | 0.00226776 | 3.56193e-05 | 2.37462e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1635.19 | 0.140436 | 915.613ms | 2632 | 640 | 2974.21 | 1535.04 | 0.0431399 | 3.17204 | 10.6535 | 1.97986 | 0.00223511 | 0.000114575 | 6.29274e-05 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2856.33 | 0.125683 | 825.803ms | 2632 | 40 | 48.7942 | 878.775 | 0.00474167 | 1.85395 | 7.25342 | 1.07713 | 0.000759878 | 1.8997e-05 | 0 | 1(Win) | true |
| Glaze | 2474.33 | 0.0678986 | 842.477ms | 2632 | 4890 | 2320 | 1014.45 | 0.0148374 | 2.12277 | 9.23367 | 1.68351 | 0.0010082 | 3.26328e-05 | 1.0256e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2366.66 | 0.0920796 | 849.603ms | 2632 | 1280 | 1220.78 | 1060.6 | 0.0744163 | 2.23231 | 9.23252 | 1.3636 | 0.000760769 | 6.73798e-05 | 3.05732e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1956.37 | 0.0532634 | 871.116ms | 2632 | 4890 | 2283.7 | 1283.03 | 0.0452764 | 2.65989 | 8.95061 | 1.58245 | 0.00195105 | 6.30901e-05 | 1.88027e-05 | 4(Loss) | true |
| simdjson (reflection) | 1938.73 | 0.0577793 | 867.675ms | 2632 | 4890 | 2736.48 | 1294.7 | 0.160658 | 2.70314 | 8.7462 | 1.35524 | 0.00173234 | 0.000153452 | 8.08828e-05 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12080.9 | 0.236589 | 744.406ms | 2632 | 320 | 77.324 | 207.772 | 0.1944 | 0.500854 | 1.74392 | 0.292173 | 0.000381127 | 2.13716e-05 | 2.37462e-06 | 1(Win) | true |
| simdjson (reflection) | 7239.89 | 0.243784 | 757.086ms | 2632 | 40 | 28.5744 | 346.7 | 0.483045 | 0.781117 | 2.7405 | 0.457827 | 0.000379939 | 1.8997e-05 | 1.8997e-05 | 2(Loss) | true |
| Glaze | 4585.42 | 0.0927009 | 782.875ms | 2632 | 4890 | 1259.19 | 547.403 | 0.261003 | 1.19028 | 4.06725 | 0.666414 | 0.000583195 | 6.30124e-05 | 2.5407e-05 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14151.1 | 0.254966 | 737.698ms | 2632 | 2560 | 523.593 | 177.376 | 0.0625047 | 0.442804 | 1.52546 | 0.240502 | 0.000598849 | 1.35057e-05 | 2.96828e-06 | 1(Win) | true |
| simdjson (reflection) | 8109.03 | 0.0615042 | 756.175ms | 2632 | 2560 | 92.7862 | 309.54 | 0.111302 | 0.709398 | 2.52356 | 0.406155 | 0.000379939 | 3.0128e-05 | 1.1131e-05 | 2(Loss) | true |
| Glaze | 5224.62 | 0.235276 | 772.98ms | 2632 | 2560 | 3270.83 | 480.431 | 0.0481107 | 1.05006 | 3.59005 | 0.569529 | 0.000381572 | 2.47851e-05 | 4.60083e-06 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2500.3 | 0.0754511 | 861.429ms | 3370 | 2560 | 2407.94 | 1285.4 | 0.0517191 | 2.085 | 8.49377 | 1.29021 | 0.000610743 | 5.0306e-05 | 1.00844e-05 | 1(Win) | true |
| Jsonifier | 2306.48 | 0.142471 | 870.92ms | 3370 | 80 | 315.283 | 1393.41 | 0.165685 | 2.25838 | 8.32611 | 1.52255 | 0.000919881 | 1.48368e-05 | 0 | 2(Loss) | true |
| simdjson (reflection) | 2196.14 | 0.0694532 | 877.108ms | 3370 | 1280 | 1322.32 | 1463.42 | 0.337192 | 2.35631 | 7.75697 | 1.24154 | 0.0017628 | 2.71235e-05 | 3.7092e-06 | 3(Loss) | true |
| Glaze | 2117.79 | 0.0884297 | 881.437ms | 3370 | 80 | 144.072 | 1517.56 | 0.0832619 | 2.49609 | 10.6374 | 2.05638 | 0.000593472 | 2.59644e-05 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 2040.53 | 0.0633144 | 918.417ms | 3370 | 4890 | 4862.81 | 1575.02 | 0.0527202 | 2.54143 | 8.63324 | 1.55994 | 0.00174935 | 6.8935e-05 | 2.62147e-05 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2866.91 | 0.144771 | 856.566ms | 3370 | 80 | 210.708 | 1121.03 | 0.0267541 | 1.82831 | 7.6635 | 1.07745 | 0.000593472 | 4.82196e-05 | 1.8546e-05 | 1(Win) | true |
| Jsonifier | 2612.07 | 0.0796997 | 853.211ms | 3370 | 2560 | 2461.75 | 1230.4 | 0.415435 | 2.02857 | 7.56944 | 1.32433 | 0.00106442 | 3.4426e-05 | 1.30981e-05 | 2(Loss) | true |
| Glaze | 2500.2 | 0.0516793 | 867.335ms | 3370 | 4890 | 2158 | 1285.45 | 0.0404281 | 2.08329 | 9.15015 | 1.69021 | 0.00105332 | 2.74283e-05 | 8.13141e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2466.71 | 0.0703791 | 873.274ms | 3370 | 2560 | 2152.54 | 1302.9 | 0.0871691 | 2.11081 | 7.38279 | 1.26558 | 0.00103 | 6.10859e-05 | 2.26029e-05 | 4(Loss) | true |
| simdjson (reflection) | 2428.79 | 0.0533941 | 873.847ms | 3370 | 4890 | 2441.04 | 1323.24 | 0.183856 | 2.14472 | 7.18368 | 1.08012 | 0.00105532 | 4.80603e-05 | 1.04373e-05 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14267.2 | 0.0946676 | 750.364ms | 3643 | 2560 | 136.044 | 243.511 | 0.229113 | 0.413796 | 1.30387 | 0.214658 | 0.000274928 | 2.76644e-05 | 1.1366e-05 | 1(Win) | true |
| Glaze | 4211.13 | 0.0917283 | 814.501ms | 3682 | 4890 | 2860.79 | 833.845 | 0.0793125 | 1.25886 | 4.2208 | 0.702879 | 0.000274813 | 3.61567e-05 | 1.08859e-05 | 2(Loss) | true |
| simdjson (reflection) | 544.768 | 0.15796 | 1382.57ms | 3643 | 640 | 64948.1 | 6377.45 | 0.0570939 | 9.29255 | 36.0878 | 7.56163 | 0.0156241 | 0.000106797 | 4.58928e-05 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18304.7 | 0.172075 | 743.477ms | 3643 | 30 | 3.2 | 189.8 | 0.0702988 | 0.336307 | 1.13752 | 0.173758 | 0.000274499 | 1.82999e-05 | 0 | 1(Win) | true |
| Glaze | 4639.72 | 0.0802503 | 803.408ms | 3682 | 4890 | 1803.79 | 756.819 | 0.108752 | 1.1495 | 3.92205 | 0.637154 | 0.000273535 | 3.40461e-05 | 1.19967e-05 | 2(Loss) | true |
| simdjson (reflection) | 540.057 | 0.089359 | 1387.75ms | 3643 | 2560 | 84597.2 | 6433.09 | 0.204959 | 9.34658 | 36.1112 | 7.56712 | 0.0150768 | 0.000349879 | 0.000196009 | 3(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 930.125 | 0.0738447 | 1206.91ms | 4630 | 640 | 7865 | 4747.23 | 0.116478 | 5.47845 | 25.5797 | 5.60216 | 0.00315234 | 8.0656e-05 | 1.61987e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 799.286 | 0.0565696 | 1292.3ms | 4630 | 4890 | 47756.5 | 5524.32 | 0.155668 | 6.36058 | 29.0862 | 5.94795 | 0.00435547 | 8.9794e-05 | 3.98398e-05 | 2(Loss) | true |
| Glaze | 776.424 | 0.0457406 | 1303.4ms | 4630 | 2560 | 17322.4 | 5686.98 | 0.0412505 | 6.57539 | 29.9333 | 5.70389 | 0.00609746 | 8.44526e-05 | 3.24818e-05 | 3(Loss) | true |
| simdjson (reflection) | 769.805 | 0.0600175 | 1313.97ms | 4630 | 640 | 7584.67 | 5735.88 | 0.122679 | 6.61212 | 27.8086 | 5.11382 | 0.00979347 | 0.000201809 | 0.000106641 | 4(Loss) | true |
| simdjson (ondemand) | 677.939 | 0.0627837 | 1385.73ms | 4630 | 640 | 10701.8 | 6513.14 | 0.0898751 | 7.4996 | 30.7261 | 5.91987 | 0.00772611 | 5.12959e-05 | 1.9236e-05 | 5(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1141.45 | 0.0896303 | 1214.88ms | 4630 | 30 | 360.644 | 3868.33 | 0.190799 | 4.47783 | 21.3168 | 4.63542 | 0.00115911 | 5.75954e-05 | 2.87977e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 947.72 | 0.0366008 | 1294.66ms | 4630 | 4890 | 14219.8 | 4659.09 | 0.0845114 | 5.37856 | 24.8127 | 4.97927 | 0.00245213 | 0.000111083 | 5.73304e-05 | 2(Loss) | true |
| Glaze | 906.145 | 0.0531124 | 1310.32ms | 4630 | 2560 | 17147.4 | 4872.85 | 0.0537928 | 5.62094 | 25.67 | 4.73261 | 0.00515946 | 0.000100736 | 4.15092e-05 | 3(Loss) | true |
| simdjson (reflection) | 894.661 | 0.0311205 | 1323.91ms | 4630 | 4890 | 11535.8 | 4935.4 | 0.0246963 | 5.6887 | 25.2114 | 4.52009 | 0.00524834 | 6.55898e-05 | 1.62097e-05 | 4(Loss) | true |
| simdjson (ondemand) | 749.826 | 0.0284733 | 1417.45ms | 4630 | 4890 | 13747.5 | 5888.72 | 0.0492734 | 6.7724 | 27.9158 | 5.2851 | 0.00249506 | 4.78342e-05 | 1.21463e-05 | 5(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1974.43 | 0.0878698 | 958.179ms | 4630 | 320 | 1235.69 | 2236.35 | 0.120598 | 2.60838 | 7.81598 | 0.410583 | 0.000215983 | 2.63229e-05 | 2.02484e-06 | 1(Win) | true |
| Glaze | 1562.87 | 0.0565129 | 1009.76ms | 4630 | 2560 | 6526.07 | 2825.26 | 0.063364 | 3.2794 | 9.99309 | 0.717495 | 0.000371895 | 4.43777e-05 | 1.03773e-05 | 2(Loss) | true |
| simdjson (reflection) | 1067.26 | 0.0217767 | 1143.55ms | 4630 | 160 | 129.874 | 4137.23 | 0.0138963 | 4.79108 | 15.3685 | 1.44384 | 0.000647948 | 2.15983e-05 | 8.09935e-06 | 3(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1979.52 | 0.166403 | 952.271ms | 4630 | 640 | 8817.55 | 2230.6 | 0.0138014 | 2.58307 | 7.70756 | 0.385314 | 0.00024433 | 3.03726e-05 | 6.41199e-06 | 1(Win) | true |
| Glaze | 1658.58 | 0.0448734 | 994.817ms | 4630 | 4890 | 6978.7 | 2662.22 | 0.207756 | 3.08756 | 9.48315 | 0.60432 | 0.000221945 | 3.63946e-05 | 1.31621e-05 | 2(Loss) | true |
| simdjson (reflection) | 1071.84 | 0.0279252 | 1137.05ms | 4630 | 30 | 39.7023 | 4119.57 | 0.0372069 | 4.76487 | 15.2991 | 1.42743 | 0.000431965 | 0 | 0 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1905.16 | 0.0534377 | 1322.05ms | 11579 | 640 | 6139.84 | 5796.16 | 0.11543 | 2.67185 | 12.4058 | 2.40625 | 0.00234517 | 8.50138e-05 | 5.37071e-05 | 1(Win) | true |
| Jsonifier | 1857.36 | 0.0867165 | 1328.68ms | 11579 | 40 | 1063.2 | 5945.32 | 0.034072 | 2.74164 | 12.6587 | 2.80706 | 0.00314362 | 8.85223e-05 | 2.80681e-05 | 2(Loss) | true |
| simdjson (reflection) | 1837.96 | 0.0348829 | 1337.2ms | 11579 | 2560 | 11244.3 | 6008.06 | 0.0154196 | 2.76791 | 11.76 | 2.0443 | 0.00404899 | 2.86416e-05 | 9.47972e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1626.2 | 0.0275377 | 1418.73ms | 11579 | 4890 | 17098.6 | 6790.45 | 0.0354516 | 3.12227 | 12.8988 | 2.36117 | 0.00303471 | 3.67176e-05 | 1.57538e-05 | 4(Loss) | true |
| Glaze | 1464.21 | 0.025377 | 1491.76ms | 11579 | 4890 | 17911.3 | 7541.68 | 0.0352059 | 3.46899 | 15.2814 | 2.83936 | 0.00519829 | 3.83071e-05 | 1.73786e-05 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2238.06 | 0.0344722 | 1321.01ms | 11579 | 4890 | 14146.4 | 4934 | 0.00100579 | 2.26441 | 10.7103 | 2.02228 | 0.00166549 | 3.24966e-05 | 1.2875e-05 | 1(Win) | true |
| Jsonifier | 2203.04 | 0.104022 | 1332.59ms | 11579 | 1280 | 34798.4 | 5012.44 | 0.00910318 | 2.33413 | 10.9611 | 2.42232 | 0.00234469 | 5.90374e-05 | 3.36682e-05 | 2(Loss) | true |
| simdjson (reflection) | 2070.05 | 0.0393489 | 1359.38ms | 11579 | 2560 | 11279.4 | 5334.47 | 0.0487927 | 2.45975 | 10.8992 | 1.84031 | 0.0023844 | 4.58467e-05 | 1.86895e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1777.12 | 0.0726412 | 1450.02ms | 11579 | 80 | 1629.91 | 6213.75 | 0.0257427 | 2.86551 | 12.0465 | 2.15977 | 0.00209863 | 2.69885e-05 | 5.3977e-06 | 4(Loss) | true |
| Glaze | 1640.31 | 0.052154 | 1495.55ms | 11579 | 4890 | 60279.9 | 6732.01 | 0.108264 | 3.09023 | 13.5602 | 2.44943 | 0.0047306 | 2.26593e-05 | 5.58094e-06 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5315 | 0.0995623 | 994.917ms | 14795 | 1280 | 8941.76 | 2654.68 | 0.0829215 | 0.969122 | 2.51443 | 0.129841 | 6.81185e-05 | 2.74058e-05 | 1.2726e-05 | 1(Win) | true |
| Glaze | 3586.2 | 0.0513372 | 1129.26ms | 14795 | 4890 | 19949.7 | 3934.42 | 0.333625 | 1.42476 | 4.54086 | 0.520446 | 7.21241e-05 | 3.33391e-05 | 1.52459e-05 | 2(Loss) | true |
| simdjson (reflection) | 410.541 | 0.0555123 | 4182.87ms | 14795 | 2560 | 931826 | 34368.3 | 0.130344 | 12.2993 | 43.1076 | 6.06023 | 0.00837596 | 9.02437e-05 | 4.69172e-05 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5532.84 | 0.144047 | 990.26ms | 14795 | 160 | 2159.04 | 2550.16 | 0.145612 | 0.929581 | 2.47279 | 0.120514 | 8.49104e-05 | 7.18148e-06 | 0 | 1(Win) | true |
| Glaze | 3929.52 | 0.100939 | 1090.63ms | 14795 | 640 | 8407.19 | 3590.67 | 0.0250152 | 1.30036 | 4.33721 | 0.474621 | 0.000128527 | 1.0033e-05 | 1.90098e-06 | 2(Loss) | true |
| simdjson (reflection) | 412.441 | 0.143207 | 4169.22ms | 14795 | 640 | 1.53609e+06 | 34210 | 0.18842 | 12.2528 | 43.0994 | 6.05914 | 0.00970767 | 0.000192738 | 0.000114481 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1667.57 | 0.0936751 | 918.059ms | 3223 | 2560 | 7632.03 | 1843.21 | 0.111003 | 3.09174 | 11.5662 | 2.04561 | 0.00119066 | 7.78099e-05 | 3.35722e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1451.65 | 0.11558 | 944.786ms | 3223 | 80 | 479.123 | 2117.38 | 0.0707923 | 3.61795 | 14.1272 | 2.39497 | 0.00119842 | 7.75675e-05 | 1.16351e-05 | 2(Loss) | true |
| Glaze | 1373.95 | 0.103691 | 964.399ms | 3223 | 160 | 860.965 | 2237.12 | 0.0619831 | 3.8196 | 14.6196 | 2.83339 | 0.0017666 | 7.17499e-05 | 4.46013e-05 | 3(Loss) | true |
| simdjson (reflection) | 1199.93 | 0.0637177 | 988.283ms | 3223 | 4890 | 13026.7 | 2561.55 | 0.209396 | 4.29621 | 15.3497 | 2.60255 | 0.00119933 | 0.000167761 | 9.04795e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1181.47 | 0.119263 | 993.265ms | 3223 | 40 | 385.071 | 2601.57 | 0.180022 | 4.42943 | 15.7384 | 2.731 | 0.00139621 | 5.42972e-05 | 0 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2101.45 | 0.171838 | 894.507ms | 3223 | 80 | 505.37 | 1462.65 | 0.0923835 | 2.52028 | 10.0689 | 1.65622 | 0.00107431 | 3.1027e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 1655.17 | 0.0630018 | 935.147ms | 3223 | 4890 | 6693.45 | 1857.02 | 0.0274909 | 3.15617 | 12.6292 | 2.00528 | 0.00134787 | 6.97314e-05 | 1.48473e-05 | 2(Loss) | true |
| Glaze | 1566.46 | 0.0640743 | 953.216ms | 3223 | 4890 | 7729.66 | 1962.19 | 0.289763 | 3.28433 | 13.0661 | 2.43376 | 0.00123556 | 3.28036e-05 | 7.67744e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1396.87 | 0.137512 | 973.167ms | 3223 | 640 | 5859.66 | 2200.41 | 0.116107 | 3.68339 | 14.1952 | 2.34595 | 0.00142821 | 0.000143015 | 5.4782e-05 | 4(Loss) | true |
| simdjson (reflection) | 1305.7 | 0.0571687 | 996.225ms | 3223 | 4890 | 8856.5 | 2354.06 | 0.19865 | 3.95025 | 14.2248 | 2.29103 | 0.00115365 | 0.000103741 | 2.73469e-05 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7704.45 | 0.0500323 | 768.941ms | 3223 | 80 | 3.18734 | 398.95 | 0.0563663 | 0.72457 | 2.06143 | 0.341917 | 0.00031027 | 2.71486e-05 | 3.87837e-06 | 1(Win) | true |
| simdjson (reflection) | 5912.45 | 0.12156 | 781.575ms | 3223 | 4890 | 1952.87 | 519.868 | 0.0167319 | 0.92251 | 2.67173 | 0.318958 | 0.000310968 | 0.000111672 | 5.39324e-05 | 2(Loss) | true |
| Glaze | 3384.16 | 0.0992205 | 822.509ms | 3223 | 4890 | 3971.28 | 908.259 | 0.191138 | 1.56628 | 4.96153 | 0.75799 | 0.000449416 | 0.000102789 | 3.81968e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8574.56 | 0.102506 | 767.818ms | 3223 | 30 | 4.05057 | 358.467 | 0.287436 | 0.670483 | 1.96153 | 0.318027 | 0.00031027 | 9.3081e-05 | 6.2054e-05 | 1(Win) | true |
| simdjson (reflection) | 6552.67 | 0.0420783 | 780.296ms | 3223 | 160 | 6.23333 | 469.075 | 0.165492 | 0.838729 | 2.52249 | 0.283276 | 0.00031027 | 2.13311e-05 | 0 | 2(Loss) | true |
| Glaze | 4104.41 | 0.0727343 | 803.793ms | 3223 | 4890 | 1450.79 | 748.875 | 0.0682012 | 1.29932 | 4.40242 | 0.633571 | 0.000310841 | 4.77143e-05 | 2.0304e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2384.17 | 0.155654 | 960.429ms | 5839 | 80 | 1057.33 | 2335.61 | 0.0476094 | 2.16372 | 8.49752 | 1.35366 | 0.000622966 | 7.49272e-05 | 2.78301e-05 | 1(Win) | true |
| Jsonifier | 2086.06 | 0.0756328 | 999.68ms | 5839 | 160 | 652.177 | 2669.39 | 0.0119423 | 2.4619 | 8.8659 | 1.76828 | 0.000640092 | 2.99709e-05 | 5.35194e-06 | 2(Loss) | true |
| simdjson (reflection) | 2073.75 | 0.266985 | 1003.89ms | 5839 | 30 | 1541.91 | 2685.23 | 0.130513 | 2.51093 | 9.23823 | 1.49615 | 0.000662214 | 0.000125592 | 6.27961e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2027.29 | 0.0405093 | 1025.7ms | 5839 | 640 | 792.381 | 2746.77 | 0.155169 | 2.57088 | 9.28001 | 1.53331 | 0.00103105 | 2.30134e-05 | 4.81675e-06 | 4(Loss) | true |
| Glaze | 1754.57 | 0.0793676 | 1052.7ms | 5839 | 4890 | 31026.4 | 3173.71 | 0.0019144 | 2.91961 | 11.2009 | 2.14044 | 0.0018855 | 5.29197e-05 | 2.10138e-05 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2821.98 | 0.096079 | 945.488ms | 5839 | 4890 | 17576.6 | 1973.26 | 0.041684 | 1.84926 | 7.67066 | 1.13855 | 0.000653388 | 5.20091e-05 | 1.63907e-05 | 1(Win) | true |
| simdjson (ondemand) | 2431.7 | 0.150162 | 976.628ms | 5839 | 320 | 3783.79 | 2289.96 | 0.00586766 | 2.15392 | 8.42764 | 1.32026 | 0.000872902 | 4.44211e-05 | 5.35194e-07 | 2(Loss) | true |
| Jsonifier | 2408.87 | 0.0526327 | 983.267ms | 5839 | 160 | 236.854 | 2311.66 | 0.0264891 | 2.1365 | 8.03939 | 1.55335 | 0.000671134 | 2.24782e-05 | 0 | 3(Loss) | true |
| simdjson (reflection) | 2273.47 | 0.124722 | 1000.74ms | 5839 | 640 | 5972.61 | 2449.34 | 0.0697406 | 2.28603 | 8.44434 | 1.2908 | 0.00090769 | 4.89703e-05 | 1.17743e-05 | 4(Loss) | true |
| Glaze | 1997.4 | 0.22524 | 1036.12ms | 5839 | 320 | 12618 | 2787.88 | 0.096866 | 2.60667 | 10.3408 | 1.91985 | 0.00152744 | 5.45898e-05 | 3.74636e-05 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14999.7 | 0.152595 | 764.46ms | 6938 | 2560 | 1159.92 | 441.116 | 0.085971 | 0.373352 | 1.05967 | 0.164889 | 0.000144528 | 2.10007e-05 | 8.50164e-06 | 1(Win) | true |
| Glaze | 2980.63 | 0.197242 | 952.076ms | 6960 | 2560 | 49390 | 2226.9 | 0.160192 | 1.74985 | 4.28635 | 0.706609 | 0.000288928 | 2.94091e-05 | 6.56654e-06 | 2(Loss) | true |
| simdjson (reflection) | 504.252 | 0.11779 | 2056.81ms | 6938 | 2560 | 611545 | 13121.6 | 0.0270681 | 10.043 | 38.7181 | 7.2557 | 0.00700372 | 0.000121219 | 6.43535e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16565.6 | 0.0691335 | 766.334ms | 6938 | 4890 | 372.856 | 399.418 | 0.0559789 | 0.337405 | 0.987028 | 0.148025 | 0.000144163 | 1.99547e-05 | 8.51833e-06 | 1(Win) | true |
| Glaze | 3470.9 | 0.361415 | 913.855ms | 6960 | 1280 | 61144.3 | 1912.35 | 0.722726 | 1.51006 | 3.91135 | 0.627299 | 0.000354256 | 3.62563e-05 | 1.77353e-05 | 2(Loss) | true |
| simdjson (reflection) | 502.075 | 0.0766491 | 2058.31ms | 6938 | 4890 | 498949 | 13178.5 | 0.0433204 | 10.0977 | 38.6877 | 7.24993 | 0.00725954 | 0.000180771 | 0.000102957 | 3(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1993.26 | 0.0465258 | 974.708ms | 4857 | 4890 | 5716.17 | 2323.83 | 0.0605424 | 2.58356 | 9.71196 | 1.72782 | 0.000837322 | 7.03136e-05 | 3.47779e-05 | 1(Win) | true |
| Glaze | 1814.31 | 0.0722377 | 988.417ms | 4857 | 1280 | 4353.63 | 2553.03 | 0.31727 | 2.83897 | 11.4159 | 2.25571 | 0.000235002 | 4.92202e-05 | 1.17421e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1667.08 | 0.149099 | 1009.45ms | 4857 | 80 | 1372.99 | 2778.51 | 0.182767 | 3.07889 | 11.9524 | 1.9547 | 0.000988264 | 4.11777e-05 | 1.54416e-05 | 3(Loss) | true |
| simdjson (reflection) | 1504.83 | 0.0525187 | 1049.87ms | 4857 | 4890 | 12779 | 3078.08 | 0.0546497 | 3.3969 | 12.9286 | 2.20507 | 0.000797197 | 0.000137343 | 7.0482e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1225.07 | 0.0767061 | 1115.54ms | 4857 | 1280 | 10766.8 | 3781.01 | 0.104723 | 4.16727 | 14.3984 | 2.73811 | 0.00187777 | 3.1205e-05 | 5.62976e-06 | 5(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2635.81 | 0.0806973 | 933.261ms | 4857 | 160 | 321.77 | 1757.33 | 0.114295 | 1.96485 | 7.59172 | 1.23348 | 0.000425932 | 6.04797e-05 | 2.05888e-05 | 1(Win) | true |
| Glaze | 2552.35 | 0.0728823 | 936.999ms | 4857 | 640 | 1119.65 | 1814.8 | 0.269361 | 2.02699 | 8.57752 | 1.59708 | 0.000855402 | 2.76663e-05 | 4.50381e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2015.05 | 0.223948 | 990.699ms | 4857 | 80 | 2120.06 | 2298.7 | 0.426675 | 2.60357 | 10.0677 | 1.50649 | 0.00144379 | 6.94873e-05 | 1.54416e-05 | 3(Loss) | true |
| simdjson (reflection) | 1736.36 | 0.0626874 | 1032.9ms | 4857 | 4890 | 13675 | 2667.65 | 0.0126429 | 2.95674 | 11.7231 | 1.91065 | 0.0014424 | 8.68605e-05 | 2.19362e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1517.21 | 0.111359 | 1071.42ms | 4857 | 320 | 3698.68 | 3052.97 | 0.0838001 | 3.3757 | 12.008 | 2.21289 | 0.00253822 | 5.46891e-05 | 2.57361e-06 | 5(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10094.9 | 0.117838 | 780.817ms | 4857 | 320 | 93.5533 | 458.847 | 0.139811 | 0.546575 | 1.67037 | 0.276096 | 0.000205888 | 1.22246e-05 | 6.43401e-07 | 1(Win) | true |
| simdjson (reflection) | 7821.01 | 0.192872 | 792.375ms | 4857 | 2560 | 3340.33 | 592.25 | 0.0333189 | 0.687759 | 2.00927 | 0.320157 | 0.000206934 | 2.80684e-05 | 9.24889e-06 | 2(Loss) | true |
| Glaze | 4005.03 | 0.0750665 | 850.039ms | 4857 | 4890 | 3685.75 | 1156.54 | 0.104919 | 1.30727 | 3.71752 | 0.606753 | 0.000359273 | 6.1977e-05 | 2.20204e-05 | 3(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11430.7 | 0.208326 | 773.775ms | 4857 | 160 | 114.025 | 405.225 | 0.157568 | 0.490582 | 1.54766 | 0.245831 | 0.000205888 | 4.50381e-05 | 3.47437e-05 | 1(Win) | true |
| simdjson (reflection) | 8294.81 | 0.117825 | 790.857ms | 4857 | 4890 | 2116.93 | 558.421 | 0.140725 | 0.651303 | 1.94174 | 0.303892 | 0.000206562 | 2.33677e-05 | 7.62082e-06 | 2(Loss) | true |
| Glaze | 4816.37 | 0.120498 | 827.622ms | 4857 | 2560 | 3437.92 | 961.719 | 0.0124711 | 1.09031 | 3.23286 | 0.496603 | 0.000207256 | 2.80684e-05 | 4.50381e-06 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2172.62 | 0.0701849 | 1029.42ms | 6701 | 640 | 2727.6 | 2941.42 | 0.0387631 | 2.36609 | 9.16236 | 1.43232 | 0.00124095 | 2.33174e-05 | 6.99522e-06 | 1(Win) | true |
| Glaze | 2031.48 | 0.0533188 | 1050.6ms | 6701 | 2560 | 7202.02 | 3145.77 | 0.353579 | 2.51922 | 10.4632 | 2.117 | 0.000157451 | 9.09962e-05 | 3.53259e-05 | 2(Loss) | true |
| simdjson (reflection) | 2009.59 | 0.0364889 | 1059.07ms | 6701 | 4890 | 6584.04 | 3180.03 | 0.227804 | 2.54033 | 9.78481 | 1.61424 | 0.000586733 | 6.20424e-05 | 2.8473e-05 | 3(Loss) | true |
| Jsonifier | 1925.42 | 0.152133 | 1067.49ms | 6701 | 40 | 1019.84 | 3319.05 | 0.127206 | 2.65878 | 9.24817 | 1.796 | 0.00168258 | 5.59618e-05 | 3.73079e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1620.08 | 0.0399085 | 1135.71ms | 6701 | 4890 | 12118.5 | 3944.61 | 0.109842 | 3.14875 | 10.847 | 1.9994 | 0.00119266 | 5.65187e-05 | 2.19727e-05 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2640.15 | 0.112164 | 991.426ms | 6701 | 160 | 1179.37 | 2420.53 | 0.13419 | 1.99407 | 8.097 | 1.17251 | 0.000872071 | 2.70482e-05 | 8.39427e-06 | 1(Win) | true |
| Glaze | 2589.49 | 0.0822645 | 991.111ms | 6701 | 160 | 659.472 | 2467.89 | 0.0283724 | 2.01417 | 8.82107 | 1.73586 | 0.00067434 | 4.2904e-05 | 2.05193e-05 | 2(Loss) | true |
| simdjson (reflection) | 2430.62 | 0.0548806 | 1014.82ms | 6701 | 4890 | 10181.1 | 2629.2 | 0.110515 | 2.14378 | 8.70288 | 1.36592 | 0.000601473 | 4.96828e-05 | 1.46485e-05 | 3(Loss) | true |
| Jsonifier | 2284.94 | 0.0577835 | 1027.81ms | 6701 | 160 | 417.885 | 2796.82 | 0.0225754 | 2.28886 | 8.09611 | 1.52335 | 0.00122277 | 2.42501e-05 | 4.66348e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2077.69 | 0.135956 | 1049.67ms | 6701 | 640 | 11191.7 | 3075.8 | 0.0297598 | 2.50767 | 9.03854 | 1.60452 | 0.00204354 | 5.12983e-05 | 1.30578e-05 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14446.2 | 0.164653 | 779.199ms | 7376 | 320 | 205.694 | 486.931 | 0.0860718 | 0.385626 | 1.15415 | 0.180586 | 0.000135999 | 2.75386e-05 | 3.38937e-06 | 1(Win) | true |
| Glaze | 3408.92 | 0.141212 | 946.007ms | 7376 | 2560 | 21736.4 | 2063.5 | 0.00626552 | 1.5124 | 4.11483 | 0.684382 | 0.00014516 | 4.31615e-05 | 1.4193e-05 | 2(Loss) | true |
| simdjson (reflection) | 502.858 | 0.139693 | 2143.77ms | 7376 | 2560 | 977552 | 13988.7 | 0.276581 | 10.0476 | 39.2732 | 7.99512 | 0.0139887 | 0.000326492 | 0.000175082 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16305.8 | 0.22865 | 763.43ms | 7376 | 80 | 77.838 | 431.4 | 0.16834 | 0.346201 | 1.07335 | 0.161876 | 0.000135575 | 2.88097e-05 | 1.18628e-05 | 1(Win) | true |
| Glaze | 3960.92 | 0.140328 | 899.398ms | 7376 | 2560 | 15899.5 | 1775.93 | 0.0620768 | 1.32893 | 3.79799 | 0.61307 | 0.000166397 | 3.25697e-05 | 1.57288e-05 | 2(Loss) | true |
| simdjson (reflection) | 516.94 | 0.121383 | 2089.08ms | 7376 | 2560 | 698416 | 13607.6 | 0.110607 | 9.89265 | 39.6961 | 8.1248 | 0.0156404 | 8.8918e-05 | 5.13172e-05 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2099.89 | 0.226999 | 805.215ms | 1691 | 40 | 121.563 | 767.975 | 0.00325521 | 2.5819 | 8.88232 | 1.44412 | 0.00118273 | 0.000147842 | 0 | 1(Win) | true |
| Glaze | 1959.97 | 0.0889887 | 810.687ms | 1691 | 4890 | 2621.6 | 822.799 | 0.0538868 | 2.71132 | 10.0727 | 1.97575 | 0.0011161 | 0.000144637 | 3.55545e-05 | 2(Loss) | true |
| simdjson (reflection) | 1821.25 | 0.13691 | 818.876ms | 1691 | 320 | 470.294 | 885.469 | 0.0480202 | 2.90642 | 9.87463 | 1.644 | 0.000899985 | 6.65287e-05 | 5.54406e-06 | 3(Loss) | true |
| Jsonifier (two-stage) | 1749.6 | 0.071998 | 819.384ms | 1691 | 2560 | 1127.43 | 921.731 | 0.0385928 | 3.02757 | 10.4181 | 1.65405 | 0.000594138 | 9.679e-05 | 1.80182e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1559.33 | 0.181855 | 835.754ms | 1691 | 1280 | 4527.6 | 1034.2 | 0.00808228 | 3.36612 | 10.6298 | 1.71082 | 0.000737822 | 9.4249e-05 | 1.89422e-05 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2541.54 | 0.0505675 | 794.945ms | 1691 | 1280 | 131.779 | 634.522 | 0.199118 | 2.11887 | 7.37138 | 1.06919 | 0.00118273 | 3.78844e-05 | 3.23403e-06 | 1(Win) | true |
| Glaze | 2424.12 | 0.0648173 | 800.452ms | 1691 | 4890 | 909.222 | 665.257 | 0.0215885 | 2.22007 | 8.57363 | 1.60201 | 0.00113061 | 4.83735e-05 | 9.55377e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2094.01 | 0.0399595 | 817.201ms | 1691 | 1280 | 121.221 | 770.131 | 0.189139 | 2.54342 | 8.90834 | 1.27853 | 0.000591366 | 4.85105e-05 | 9.24009e-07 | 3(Loss) | true |
| simdjson (reflection) | 2013.46 | 0.131321 | 819.247ms | 1691 | 640 | 708.025 | 800.941 | 0.0765311 | 2.64239 | 9.01419 | 1.40686 | 0.000884277 | 5.82126e-05 | 6.46807e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1814.72 | 0.079944 | 828.662ms | 1691 | 4890 | 2468.03 | 888.658 | 0.028501 | 2.92386 | 9.27322 | 1.3702 | 0.00101633 | 6.13134e-05 | 1.48749e-05 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8541.77 | 0.0679464 | 751.328ms | 1996 | 1280 | 29.3473 | 222.85 | 0.0910657 | 0.703762 | 1.46693 | 0.248998 | 0.000501002 | 4.34463e-05 | 1.56563e-05 | 1(Win) | true |
| simdjson (reflection) | 6464.98 | 0.0841181 | 759.032ms | 1996 | 80 | 4.90744 | 294.438 | 0.0637213 | 0.89127 | 1.87926 | 0.273547 | 0.000507265 | 2.50501e-05 | 0 | 2(Loss) | true |
| Glaze | 5279.12 | 0.12623 | 761.126ms | 1996 | 2560 | 530.352 | 360.578 | 0.213177 | 1.0671 | 3.45541 | 0.568637 | 0.000748959 | 3.44439e-05 | 1.0568e-05 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10078.9 | 0.128025 | 746.462ms | 1996 | 80 | 4.67706 | 188.863 | 0.152459 | 0.629791 | 1.30611 | 0.210421 | 0.001002 | 0 | 0 | 1(Win) | true |
| simdjson (reflection) | 7387.75 | 0.100256 | 752.975ms | 1996 | 2560 | 170.826 | 257.661 | 0.330011 | 0.794651 | 1.71744 | 0.233968 | 0.000501393 | 7.02577e-05 | 3.48353e-05 | 2(Loss) | true |
| Glaze | 6078.42 | 0.179073 | 757.804ms | 1996 | 1280 | 402.543 | 313.163 | 0.151946 | 0.942206 | 2.96042 | 0.462926 | 0.000501393 | 5.83198e-05 | 4.14892e-05 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2249.98 | 0.192276 | 812.741ms | 2158 | 160 | 494.895 | 914.688 | 0.109208 | 2.38799 | 8.08851 | 1.31696 | 0.000695088 | 4.92354e-05 | 2.31696e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2132.88 | 0.410123 | 821.028ms | 2158 | 2560 | 40090.4 | 964.908 | 0.00680071 | 2.51664 | 8.58573 | 1.30862 | 0.000468279 | 0.000117839 | 4.2719e-05 | 2(Loss) | true |
| Glaze | 2033.31 | 0.203677 | 822.79ms | 2158 | 2560 | 10879.8 | 1012.16 | 0.2495 | 2.62016 | 9.7317 | 1.90315 | 0.000551002 | 5.52088e-05 | 2.37126e-05 | 3(Loss) | true |
| Jsonifier | 1992.09 | 0.105721 | 826.44ms | 2158 | 80 | 95.4329 | 1033.1 | 0.0290473 | 2.68506 | 8.67609 | 1.53105 | 0.00131487 | 4.63392e-05 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 1944.94 | 0.136195 | 830.901ms | 2158 | 160 | 332.3 | 1058.14 | 0.113867 | 2.74613 | 8.68536 | 1.37535 | 0.00134094 | 6.08202e-05 | 2.8962e-06 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2576.38 | 0.144042 | 818.562ms | 2158 | 1280 | 1694.62 | 798.807 | 0.0180901 | 2.06262 | 7.34662 | 1 | 0.000468098 | 5.39417e-05 | 7.60253e-06 | 1(Win) | true |
| simdjson (reflection) | 2489.66 | 0.186792 | 821.996ms | 2158 | 320 | 762.936 | 826.631 | 0.0325009 | 2.13285 | 7.33133 | 1.11353 | 0.000686399 | 0.000102815 | 1.88253e-05 | 2(Loss) | true |
| Jsonifier | 2397.86 | 0.100247 | 826.121ms | 2158 | 2560 | 1895.13 | 858.277 | 0.0450373 | 2.20723 | 7.43513 | 1.22289 | 0.000489096 | 6.57075e-05 | 1.35759e-05 | 3(Loss) | true |
| Glaze | 2380.38 | 0.0659896 | 825.894ms | 2158 | 320 | 104.163 | 864.581 | 0.0902801 | 2.22422 | 8.49861 | 1.59546 | 0.000473529 | 1.88253e-05 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 2242.53 | 0.147292 | 832.896ms | 2158 | 160 | 292.352 | 917.725 | 0.0027242 | 2.35873 | 7.53429 | 1.0848 | 0.000822521 | 0.000162187 | 4.3443e-05 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11096.2 | 0.385033 | 743.457ms | 2866 | 4890 | 4398.57 | 246.322 | 0.0570472 | 0.536932 | 1.13643 | 0.187369 | 0.000349275 | 3.38929e-05 | 1.1916e-05 | 1(Win) | true |
| Glaze | 3807.25 | 0.205368 | 795.658ms | 2866 | 1280 | 2782.3 | 717.902 | 0.0400633 | 1.42389 | 4.01605 | 0.668179 | 0.000352189 | 5.6154e-05 | 2.67141e-05 | 2(Loss) | true |
| simdjson (reflection) | 547.233 | 0.0963221 | 1228.83ms | 2866 | 2560 | 59251.7 | 4994.64 | 0.238094 | 9.3694 | 34.918 | 7.32764 | 0.00882164 | 0.000187544 | 0.000105084 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14398.7 | 0.123528 | 746.847ms | 2866 | 40 | 2.19936 | 189.825 | 0.441434 | 0.42971 | 0.963015 | 0.146546 | 0.000348918 | 0 | 0 | 1(Win) | true |
| Glaze | 4549.64 | 0.433614 | 789.691ms | 2866 | 640 | 4342.95 | 600.758 | 0.011185 | 1.18575 | 3.3709 | 0.529659 | 0.000349464 | 3.81629e-05 | 9.26814e-06 | 2(Loss) | true |
| simdjson (reflection) | 528.44 | 0.0872591 | 1256.96ms | 2866 | 2560 | 52146.1 | 5172.26 | 0.0718438 | 9.63594 | 35.709 | 7.46895 | 0.00767702 | 0.00016083 | 8.00059e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2223.48 | 0.125462 | 917.024ms | 4390 | 640 | 3571.62 | 1882.91 | 0.00406634 | 2.32169 | 10.6164 | 1.73007 | 0.000931449 | 5.0541e-05 | 1.21014e-05 | 1(Win) | true |
| Glaze | 1853.21 | 0.0721457 | 951.209ms | 4390 | 80 | 212.516 | 2259.12 | 0.148068 | 2.77888 | 13.0267 | 2.59021 | 0.000839977 | 2.84738e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 1629.64 | 0.106953 | 989.852ms | 4390 | 640 | 4831.81 | 2569.05 | 0.0575027 | 3.14998 | 14.1048 | 2.26697 | 0.00339087 | 6.01509e-05 | 1.67284e-05 | 3(Loss) | true |
| simdjson (reflection) | 1433.41 | 0.117376 | 1026.99ms | 4390 | 80 | 940.241 | 2920.75 | 0.06159 | 3.57756 | 13.7934 | 2.21708 | 0.00283314 | 0.000142369 | 1.99317e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1080.78 | 0.037513 | 1120.98ms | 4390 | 4890 | 10325.8 | 3873.7 | 0.211251 | 4.7238 | 17.8326 | 3.18155 | 0.00246587 | 0.000175618 | 8.81349e-05 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2607.76 | 0.0385681 | 915.071ms | 4390 | 4890 | 1874.82 | 1605.45 | 0.0474922 | 1.98782 | 9.45039 | 1.45878 | 0.00093641 | 4.49525e-05 | 1.13662e-05 | 1(Win) | true |
| Glaze | 2167.53 | 0.0969581 | 945.253ms | 4390 | 80 | 280.582 | 1931.53 | 0.099563 | 2.38245 | 11.6367 | 2.27198 | 0.000583713 | 7.40319e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 1823.07 | 0.0797992 | 984.881ms | 4390 | 1280 | 4298.63 | 2296.47 | 0.0320362 | 2.81952 | 12.9369 | 1.99499 | 0.00317483 | 3.70159e-05 | 2.84738e-06 | 3(Loss) | true |
| simdjson (reflection) | 1580.65 | 0.0478552 | 1018.78ms | 4390 | 4890 | 7856.39 | 2648.67 | 0.213175 | 3.23551 | 12.8103 | 1.98361 | 0.00194465 | 6.09304e-05 | 1.78878e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1182.81 | 0.0343402 | 1112.81ms | 4390 | 2560 | 3782.2 | 3539.56 | 0.106934 | 4.29384 | 16.4166 | 2.8697 | 0.0027616 | 5.29435e-05 | 1.34361e-05 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13268.6 | 0.0368953 | 759.666ms | 4390 | 1280 | 17.3471 | 315.528 | 0.121472 | 0.430398 | 1.74146 | 0.277677 | 0.00022779 | 1.833e-05 | 3.91515e-06 | 1(Win) | true |
| simdjson (reflection) | 7999.1 | 0.184025 | 782.663ms | 4390 | 80 | 74.215 | 523.388 | 0.145474 | 0.681916 | 2.52346 | 0.390888 | 0.00022779 | 1.99317e-05 | 0 | 2(Loss) | true |
| Glaze | 3382.78 | 0.155631 | 861.722ms | 4390 | 4890 | 18141.8 | 1237.63 | 0.283494 | 1.52943 | 4.77472 | 0.753987 | 0.000296733 | 4.02476e-05 | 1.0388e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14231.1 | 0.0894848 | 757.991ms | 4390 | 640 | 44.3539 | 294.189 | 0.279618 | 0.409775 | 1.66743 | 0.260137 | 0.00022779 | 3.91515e-05 | 1.21014e-05 | 1(Win) | true |
| simdjson (reflection) | 8638.46 | 0.126252 | 777.374ms | 4390 | 80 | 29.9519 | 484.65 | 0.149817 | 0.634114 | 2.40979 | 0.364692 | 0.00022779 | 1.13895e-05 | 2.84738e-06 | 2(Loss) | true |
| Glaze | 4110.9 | 0.177307 | 838.454ms | 4390 | 1280 | 4173.66 | 1018.42 | 0.0835322 | 1.2787 | 4.36743 | 0.663098 | 0.000227968 | 2.11774e-05 | 6.76253e-06 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3110.57 | 0.0960479 | 1023.74ms | 9378 | 640 | 4880.86 | 2875.21 | 0.00630428 | 1.65515 | 7.46193 | 1.11836 | 0.00162748 | 2.78244e-05 | 5.83147e-06 | 1(Win) | true |
| Jsonifier | 2990.01 | 0.09088 | 1035.24ms | 9378 | 1280 | 9458.49 | 2991.15 | 0.00480562 | 1.70917 | 7.52932 | 1.46001 | 0.00240065 | 2.72413e-05 | 9.16373e-06 | 2(Loss) | true |
| simdjson (reflection) | 2820.64 | 0.0351278 | 1052.81ms | 9378 | 4890 | 6066.46 | 3170.75 | 0.095582 | 1.80254 | 7.15878 | 1.06825 | 0.00108237 | 2.52734e-05 | 6.47646e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2223.97 | 0.0777327 | 1143.02ms | 9378 | 30 | 293.151 | 4021.43 | 0.00414429 | 2.33996 | 9.02261 | 1.5144 | 0.00127248 | 1.42177e-05 | 7.10884e-06 | 4(Loss) | true |
| Glaze | 1844.65 | 0.0646391 | 1213.04ms | 9378 | 80 | 785.734 | 4848.39 | 0.013147 | 2.76444 | 9.47121 | 1.81009 | 0.0039574 | 3.99872e-05 | 7.99744e-06 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3403.9 | 0.0740976 | 1026.41ms | 9378 | 160 | 606.45 | 2627.44 | 0.025459 | 1.50938 | 6.91523 | 0.991043 | 0.00159082 | 1.86607e-05 | 0 | 1(Win) | true |
| Jsonifier | 3273.96 | 0.0432053 | 1033.75ms | 9378 | 4890 | 6811.72 | 2731.72 | 0.117287 | 1.56642 | 6.98262 | 1.33301 | 0.00241559 | 2.24604e-05 | 6.12756e-06 | 2(Loss) | true |
| simdjson (reflection) | 3102.23 | 0.0450078 | 1046.69ms | 9378 | 4890 | 8232.99 | 2882.95 | 0.0497512 | 1.6407 | 6.68693 | 0.956601 | 0.000910149 | 2.73014e-05 | 5.97491e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2392.42 | 0.0386539 | 1132.46ms | 9378 | 160 | 334.08 | 3738.29 | 0.044492 | 2.13726 | 8.38676 | 1.37375 | 0.00117762 | 2.13265e-05 | 1.99936e-06 | 4(Loss) | true |
| Glaze | 1999.69 | 0.0624819 | 1203.3ms | 9378 | 80 | 624.734 | 4472.48 | 0.0156537 | 2.55278 | 8.81926 | 1.66112 | 0.00389342 | 1.73278e-05 | 0 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 24008.3 | 0.0426682 | 777.38ms | 11521 | 4890 | 186.457 | 457.646 | 0.353746 | 0.229561 | 0.744814 | 0.111709 | 8.6869e-05 | 1.95784e-05 | 5.89304e-06 | 1(Win) | true |
| Glaze | 5814.34 | 0.0733948 | 927.493ms | 11521 | 4890 | 9406.32 | 1889.69 | 0.0538074 | 0.888842 | 3.91155 | 0.66496 | 0.000271399 | 2.26846e-05 | 5.53803e-06 | 2(Loss) | true |
| simdjson (reflection) | 519.799 | 0.436416 | 2868.29ms | 11521 | 320 | 2.72308e+06 | 21137.5 | 0.0798536 | 9.70287 | 37.9473 | 6.97318 | 0.0109319 | 4.66539e-05 | 2.52257e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 30756.2 | 0.0736946 | 763.778ms | 11521 | 4890 | 338.919 | 357.238 | 0.0187058 | 0.1833 | 0.69178 | 0.0991234 | 8.68513e-05 | 6.05279e-06 | 1.63301e-06 | 1(Win) | true |
| Glaze | 6957.24 | 0.113262 | 885.689ms | 11521 | 2560 | 8190.58 | 1579.26 | 0.150013 | 0.745349 | 3.64795 | 0.607847 | 0.000259953 | 1.51218e-05 | 4.27209e-06 | 2(Loss) | true |
| simdjson (reflection) | 523.315 | 0.115864 | 2855.08ms | 11521 | 4890 | 2.89376e+06 | 20995.5 | 0.182446 | 9.63623 | 37.951 | 6.97405 | 0.0104205 | 0.000110317 | 6.34389e-05 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3233.5 | 0.0581483 | 862.872ms | 4669 | 2560 | 1641.4 | 1377.05 | 0.368046 | 1.61654 | 6.74706 | 1.37117 | 0.00054214 | 3.59753e-05 | 1.39718e-05 | 1(Win) | true |
| Glaze | 2126.82 | 0.188483 | 944.02ms | 4669 | 30 | 467.145 | 2093.6 | 0.0700057 | 2.46839 | 9.59435 | 1.81795 | 0.00104234 | 1.42786e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 2113.33 | 0.0703761 | 936.697ms | 4669 | 1280 | 2814.33 | 2106.97 | 0.00407857 | 2.45805 | 9.61812 | 1.69908 | 0.00108796 | 6.72655e-05 | 2.67723e-05 | 3(Loss) | true |
| simdjson (reflection) | 1645.49 | 0.0403488 | 1007.09ms | 4669 | 4890 | 5829.47 | 2706.01 | 0.0821893 | 3.11669 | 12.665 | 1.99208 | 0.000834815 | 3.7317e-05 | 1.47604e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1301.44 | 0.0421499 | 1075.02ms | 4669 | 2560 | 5323.96 | 3421.38 | 0.152973 | 3.92445 | 14.9522 | 2.6783 | 0.00128474 | 0.000111858 | 6.83531e-05 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3556.07 | 0.0812012 | 851.301ms | 4669 | 160 | 165.407 | 1252.14 | 0.57222 | 1.46873 | 6.29921 | 1.26087 | 0.000501981 | 1.20475e-05 | 2.67723e-06 | 1(Win) | true |
| Glaze | 2308.22 | 0.0626055 | 926.968ms | 4669 | 2560 | 3733.85 | 1929.06 | 0.0162577 | 2.24584 | 8.88263 | 1.65282 | 0.00104973 | 3.04535e-05 | 4.85248e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2289.03 | 0.0920436 | 927.694ms | 4669 | 80 | 256.462 | 1945.24 | 0.0572237 | 2.29693 | 9.17113 | 1.58856 | 0.00107357 | 1.07089e-05 | 5.35447e-06 | 3(Loss) | true |
| simdjson (reflection) | 1696.82 | 0.0579789 | 1003.14ms | 4669 | 4890 | 11319.5 | 2624.15 | 0.0853583 | 3.02168 | 12.3958 | 1.92097 | 0.000787205 | 4.40621e-05 | 1.48042e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1414.16 | 0.0310721 | 1054.28ms | 4669 | 320 | 306.296 | 3148.65 | 0.03902 | 3.62261 | 14.1321 | 2.51317 | 0.00132389 | 2.74416e-05 | 6.69308e-06 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11948.2 | 0.0467273 | 764.452ms | 4669 | 160 | 4.85185 | 372.669 | 0.0754123 | 0.468609 | 1.25594 | 0.317199 | 0.000214179 | 1.47248e-05 | 2.67723e-06 | 1(Win) | true |
| simdjson (reflection) | 7831.2 | 0.142019 | 784.416ms | 4669 | 2560 | 1669.25 | 568.585 | 0.392523 | 0.698213 | 1.68002 | 0.225316 | 0.000214681 | 1.61471e-05 | 6.1911e-06 | 2(Loss) | true |
| Glaze | 3572.27 | 0.134376 | 860.119ms | 4669 | 1280 | 3591 | 1246.46 | 0.109554 | 1.46181 | 3.4607 | 0.498822 | 0.000215685 | 5.2708e-05 | 1.72347e-05 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13146.9 | 0.0533657 | 762.176ms | 4669 | 320 | 10.4538 | 338.688 | 0.167646 | 0.430783 | 1.14971 | 0.292782 | 0.000214179 | 4.68516e-06 | 0 | 1(Win) | true |
| simdjson (reflection) | 8583.53 | 0.0529052 | 772.458ms | 4669 | 40 | 3.01282 | 518.75 | 0.0417496 | 0.635479 | 1.57721 | 0.201542 | 0.000214179 | 0 | 0 | 2(Loss) | true |
| Glaze | 3943.28 | 0.0870598 | 843.974ms | 4669 | 4890 | 4725.82 | 1129.19 | 0.284949 | 1.32746 | 2.95716 | 0.386379 | 0.000226442 | 2.74184e-05 | 1.29646e-05 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3344.74 | 0.099793 | 960.085ms | 7932 | 80 | 407.503 | 2261.62 | 0.0475548 | 1.56795 | 6.40494 | 1.04564 | 0.000753278 | 2.52143e-05 | 3.15179e-06 | 1(Win) | true |
| Jsonifier | 2827.46 | 0.0623532 | 995.317ms | 7932 | 2560 | 7124.12 | 2675.39 | 0.0278074 | 1.81875 | 6.55724 | 1.45411 | 0.00101734 | 2.83169e-05 | 1.06373e-05 | 2(Loss) | true |
| simdjson (reflection) | 2660.4 | 0.144084 | 1022.49ms | 7932 | 320 | 5371 | 2843.39 | 0.0553123 | 1.95313 | 8.03429 | 1.19617 | 0.000615781 | 1.5365e-05 | 5.12166e-06 | 3(Loss) | true |
| Glaze | 2377.73 | 0.0471758 | 1045.71ms | 7932 | 4890 | 11015.1 | 3181.41 | 0.273678 | 2.17616 | 8.49458 | 1.65368 | 0.00182329 | 5.59975e-05 | 3.52949e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2112.46 | 0.0828978 | 1088.11ms | 7932 | 40 | 352.481 | 3580.93 | 0.118126 | 2.42157 | 9.38061 | 1.6001 | 0.00101803 | 1.26072e-05 | 0 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3485.89 | 0.0522725 | 951.195ms | 7932 | 4890 | 6292.06 | 2170.04 | 0.127348 | 1.47969 | 6.14183 | 0.980585 | 0.000785898 | 2.10635e-05 | 7.50242e-06 | 1(Win) | true |
| Jsonifier | 3006.88 | 0.0577638 | 986.184ms | 7932 | 4890 | 10326.5 | 2515.75 | 0.0301916 | 1.72393 | 6.29501 | 1.38944 | 0.00109128 | 4.05801e-05 | 2.03932e-05 | 2(Loss) | true |
| simdjson (reflection) | 2749.33 | 0.113488 | 1020.92ms | 7932 | 80 | 780.018 | 2751.41 | 0.175217 | 1.90119 | 7.87582 | 1.15431 | 0.000630358 | 3.46697e-05 | 2.20625e-05 | 3(Loss) | true |
| Glaze | 2528.81 | 0.0682555 | 1034.23ms | 7932 | 320 | 1334.01 | 2991.35 | 0.520543 | 2.0368 | 8.07526 | 1.55648 | 0.0019872 | 1.33951e-05 | 5.12166e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2295.66 | 0.0959033 | 1068.42ms | 7932 | 40 | 399.464 | 3295.15 | 0.0490861 | 2.23115 | 8.89788 | 1.5029 | 0.000690242 | 3.15179e-05 | 0 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20767.3 | 0.125437 | 769.676ms | 9249 | 4890 | 1387.99 | 424.731 | 0.121707 | 0.267382 | 0.719537 | 0.162937 | 0.000111547 | 2.53606e-05 | 1.15416e-05 | 1(Win) | true |
| Glaze | 3253.65 | 0.17892 | 1004.15ms | 9249 | 4890 | 115047 | 2710.96 | 0.00270698 | 1.58278 | 3.79436 | 0.624933 | 0.00038209 | 3.97766e-05 | 2.18451e-05 | 2(Loss) | true |
| simdjson (reflection) | 508.907 | 0.300055 | 2461.11ms | 9249 | 320 | 865494 | 17332.3 | 0.00191113 | 9.94147 | 40.8158 | 8.29486 | 0.0147982 | 8.85231e-05 | 4.89918e-05 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 23730 | 0.14 | 761.519ms | 9249 | 4890 | 1324.22 | 371.704 | 0.291159 | 0.237172 | 0.657152 | 0.1478 | 0.000108252 | 1.93024e-05 | 8.0924e-06 | 1(Win) | true |
| Glaze | 3420.33 | 0.429506 | 992.18ms | 9249 | 640 | 78518.6 | 2578.85 | 0.042127 | 1.51598 | 3.52752 | 0.565359 | 0.000378926 | 7.2643e-06 | 0 | 2(Loss) | true |
| simdjson (reflection) | 509.494 | 0.135506 | 2473.1ms | 9249 | 1280 | 704428 | 17312.3 | 0.0342314 | 9.96134 | 40.824 | 8.29744 | 0.0155013 | 0.000132785 | 7.30653e-05 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 849.351 | 0.052073 | 1241ms | 4604 | 2560 | 18550.7 | 5169.49 | 0.364596 | 6.06314 | 24.6661 | 5.45582 | 0.0051029 | 7.51724e-05 | 3.67378e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 741.156 | 0.0349181 | 1325.02ms | 4604 | 2560 | 10954.5 | 5924.14 | 0.0464154 | 6.99141 | 29.1405 | 5.84796 | 0.00290101 | 0.000115558 | 7.26271e-05 | 2(Loss) | true |
| Glaze | 658.743 | 0.114052 | 1392.12ms | 4604 | 320 | 18492.4 | 6665.29 | 0.0303252 | 7.85578 | 33.6911 | 6.93245 | 0.00403725 | 1.22176e-05 | 1.35752e-06 | 3(Loss) | true |
| simdjson (reflection) | 621.427 | 0.0800374 | 1443.15ms | 4604 | 160 | 5116.79 | 7065.54 | 0.0310582 | 8.34013 | 31.2881 | 6.03644 | 0.00571107 | 7.05908e-05 | 3.93679e-05 | 4(Loss) | true |
| simdjson (ondemand) | 500.378 | 0.0277649 | 1607.67ms | 4604 | 4890 | 29025.2 | 8774.79 | 0.00584232 | 10.2757 | 37.8312 | 7.69505 | 0.00488719 | 0.000142492 | 8.85244e-05 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1041.38 | 0.0825072 | 1224.35ms | 4604 | 80 | 968.107 | 4216.24 | 0.0790956 | 4.99509 | 20.3761 | 4.46595 | 0.00383362 | 2.71503e-05 | 8.14509e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 882.051 | 0.0921114 | 1314.26ms | 4604 | 40 | 840.951 | 4977.85 | 0.103351 | 5.88903 | 24.8184 | 4.85295 | 0.00235122 | 0.000114031 | 0 | 2(Loss) | true |
| Glaze | 754.12 | 0.0344948 | 1387.74ms | 4604 | 4890 | 19724.5 | 5822.3 | 0.0145931 | 6.83246 | 29.1901 | 5.89346 | 0.0046293 | 6.07634e-05 | 3.46458e-05 | 3(Loss) | true |
| simdjson (reflection) | 711.474 | 0.0340188 | 1433.31ms | 4604 | 4890 | 21552.6 | 6171.29 | 0.0966133 | 7.24837 | 27.1229 | 5.09622 | 0.00489994 | 0.000107446 | 3.74885e-05 | 4(Loss) | true |
| simdjson (ondemand) | 547.492 | 0.0752656 | 1633.93ms | 4604 | 2560 | 93271.3 | 8019.69 | 0.0784721 | 9.4252 | 33.0173 | 6.61556 | 0.0156979 | 0.000135242 | 6.71122e-05 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1506.75 | 0.069922 | 1031.04ms | 4918 | 1280 | 6063.63 | 3112.77 | 0.304914 | 3.42602 | 11.3817 | 1.34994 | 0.000647494 | 4.40029e-05 | 1.87449e-05 | 1(Win) | true |
| Jsonifier | 1451.33 | 0.0752843 | 1026.99ms | 4604 | 4890 | 25366.3 | 3025.31 | 0.101488 | 3.5877 | 9.57515 | 0.570157 | 0.000605591 | 4.80599e-05 | 2.25198e-05 | 2(Loss) | true |
| Glaze | 1194.46 | 0.0513428 | 1092.73ms | 4604 | 4890 | 17417.9 | 3675.9 | 0.0686551 | 4.33119 | 12.8554 | 1.10687 | 0.000551623 | 4.62388e-05 | 1.52353e-05 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1530.96 | 0.0486041 | 1028.51ms | 4918 | 2560 | 5675.92 | 3063.55 | 0.193639 | 3.39802 | 11.2666 | 1.32168 | 0.000612307 | 4.63857e-05 | 2.37489e-05 | 1(Win) | true |
| Jsonifier | 1489.08 | 0.0876177 | 1016.52ms | 4604 | 4890 | 32638.3 | 2948.61 | 0.146812 | 3.48782 | 9.45161 | 0.539975 | 0.000520042 | 6.62712e-05 | 3.53121e-05 | 2(Loss) | true |
| Glaze | 1309.66 | 0.0484711 | 1056.98ms | 4604 | 4890 | 12913 | 3352.56 | 0.0263576 | 3.97221 | 12.2183 | 0.967203 | 0.000572944 | 4.34405e-05 | 1.94994e-05 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2494.05 | 0.0906653 | 1437.24ms | 18245 | 320 | 12803 | 6976.52 | 0.0854816 | 2.03803 | 8.02017 | 1.46435 | 0.00145262 | 3.78528e-05 | 2.41505e-05 | 1(Win) | true |
| simdjson (reflection) | 2291.8 | 0.0584928 | 1509.4ms | 18245 | 1280 | 25243.4 | 7592.19 | 0.0365847 | 2.21868 | 8.31576 | 1.42806 | 0.00142171 | 2.4964e-05 | 1.31029e-05 | 2(Loss) | true |
| Jsonifier | 2174.76 | 0.0303545 | 1542.02ms | 18245 | 4890 | 28841.7 | 8000.8 | 0.102621 | 2.33831 | 8.27947 | 1.91072 | 0.00183945 | 5.95059e-05 | 3.30426e-05 | 3(Loss) | true |
| Glaze | 1796.89 | 0.0665509 | 1701.63ms | 18245 | 320 | 13289.3 | 9683.26 | 0.0305524 | 2.82371 | 12.1423 | 2.39156 | 0.00371215 | 1.76418e-05 | 4.96711e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1794 | 0.0210633 | 1714.48ms | 18245 | 4890 | 20408.3 | 9698.89 | 0.0350802 | 2.82669 | 10.3359 | 1.92201 | 0.00196414 | 2.0859e-05 | 7.95803e-06 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2933.47 | 0.0259748 | 1433.85ms | 18245 | 640 | 1519.17 | 5931.46 | 0.0706272 | 1.73714 | 6.95911 | 1.22324 | 0.00134232 | 2.2352e-05 | 5.30967e-06 | 1(Win) | true |
| simdjson (reflection) | 2537.37 | 0.103214 | 1521.62ms | 18245 | 30 | 1502.87 | 6857.4 | 0.128981 | 2.00524 | 7.82028 | 1.3066 | 0.000692427 | 2.00968e-05 | 7.30794e-06 | 2(Loss) | true |
| Jsonifier | 2457.08 | 0.0818148 | 1539.41ms | 18245 | 640 | 21483 | 7081.5 | 0.129307 | 2.06406 | 7.21677 | 1.66912 | 0.0018231 | 5.77213e-05 | 3.50267e-05 | 3(Loss) | true |
| Glaze | 2000.94 | 0.0874782 | 1691.89ms | 18245 | 320 | 18517 | 8695.82 | 0.0690823 | 2.53797 | 11.0264 | 2.13571 | 0.00356348 | 8.39271e-06 | 1.37024e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1981.34 | 0.218831 | 1715.95ms | 18245 | 80 | 29544.5 | 8781.81 | 0.00270453 | 2.56178 | 9.58425 | 1.74743 | 0.00201973 | 8.08441e-05 | 3.08304e-05 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6015.33 | 0.0878319 | 1128.51ms | 24579 | 2560 | 29988.4 | 3896.77 | 0.0885767 | 0.849376 | 1.89044 | 0.106026 | 0.000102937 | 1.36836e-05 | 5.29225e-06 | 1(Win) | true |
| Glaze | 3358.71 | 0.235228 | 1447.19ms | 24579 | 640 | 172481 | 6978.97 | 0.0982708 | 1.51392 | 3.92148 | 0.474633 | 0.000242267 | 1.35405e-05 | 3.36924e-06 | 2(Loss) | true |
| simdjson (reflection) | 518.848 | 0.271376 | 5326.88ms | 24893 | 640 | 9.86732e+06 | 45754.9 | 0.136932 | 9.73591 | 36.7935 | 6.03901 | 0.00726189 | 8.93826e-05 | 5.4546e-05 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6116.24 | 0.0651916 | 1121.94ms | 24579 | 4890 | 30524.7 | 3832.48 | 0.0679502 | 0.834927 | 1.8696 | 0.101184 | 0.000105798 | 1.66318e-05 | 6.41477e-06 | 1(Win) | true |
| Glaze | 3581.15 | 0.0917709 | 1394.23ms | 24579 | 4890 | 176442 | 6545.48 | 0.19025 | 1.42277 | 3.77273 | 0.441597 | 0.000279438 | 1.80379e-05 | 7.70438e-06 | 2(Loss) | true |
| simdjson (reflection) | 514.034 | 0.101038 | 5366.73ms | 24893 | 4890 | 1.06476e+07 | 46183.3 | 0.107904 | 9.77023 | 36.7971 | 6.03981 | 0.00730911 | 0.000160532 | 9.79817e-05 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 924.118 | 0.102512 | 1203.81ms | 4604 | 40 | 948.91 | 4751.25 | 0.116948 | 5.62892 | 23.8388 | 5.20135 | 0.00355669 | 4.34405e-05 | 1.62902e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 772.935 | 0.0401222 | 1296.07ms | 4604 | 2560 | 13298.3 | 5680.57 | 0.0615551 | 6.70014 | 28.163 | 5.60024 | 0.00409223 | 9.20565e-05 | 5.75247e-05 | 2(Loss) | true |
| Glaze | 639.812 | 0.0865386 | 1408.92ms | 4604 | 1280 | 45143.5 | 6862.51 | 0.120215 | 8.00023 | 33.7823 | 6.94593 | 0.00547147 | 8.4675e-05 | 5.03978e-05 | 3(Loss) | true |
| simdjson (reflection) | 622.651 | 0.0897959 | 1432.78ms | 4604 | 4890 | 196066 | 7051.64 | 0.0267359 | 8.27621 | 31.0638 | 5.96481 | 0.00470454 | 0.00011482 | 5.95641e-05 | 4(Loss) | true |
| simdjson (ondemand) | 491.845 | 0.116896 | 1628.88ms | 4604 | 40 | 4355.87 | 8927.02 | 0.100436 | 10.5231 | 37.6419 | 7.66442 | 0.00882928 | 6.51607e-05 | 0 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1132.64 | 0.0768865 | 1192.59ms | 4604 | 160 | 1421.38 | 3876.55 | 0.0706668 | 4.59738 | 19.4513 | 4.19699 | 0.00278426 | 4.34405e-05 | 5.43006e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 924.978 | 0.069991 | 1282.6ms | 4604 | 1280 | 14128.7 | 4746.83 | 0.0393015 | 5.58561 | 23.8999 | 4.62055 | 0.00240314 | 5.54884e-05 | 1.03511e-05 | 2(Loss) | true |
| Glaze | 738.969 | 0.0534415 | 1406.81ms | 4604 | 2560 | 25811.7 | 5941.68 | 0.287187 | 6.98067 | 29.5996 | 5.9627 | 0.00574628 | 4.15739e-05 | 1.84113e-05 | 3(Loss) | true |
| simdjson (reflection) | 696.078 | 0.0378757 | 1448.8ms | 4604 | 4890 | 27911.6 | 6307.79 | 0.00960768 | 7.37958 | 27.0766 | 5.066 | 0.00832138 | 0.0001838 | 0.000113665 | 4(Loss) | true |
| simdjson (ondemand) | 537.679 | 0.0577023 | 1652.56ms | 4604 | 1280 | 28419.8 | 8166.06 | 0.0904319 | 9.61562 | 33.1201 | 6.65408 | 0.0147577 | 0.000142878 | 7.12695e-05 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1538.91 | 0.0450577 | 1026.03ms | 4918 | 4890 | 9221.42 | 3047.72 | 0.00419867 | 3.39603 | 11.3867 | 1.35177 | 0.000703771 | 2.71113e-05 | 9.39747e-06 | 1(Win) | true |
| Jsonifier | 1417.51 | 0.104346 | 1028.81ms | 4604 | 4890 | 51083.3 | 3097.49 | 0.152052 | 3.68327 | 9.55191 | 0.570591 | 0.000314877 | 8.81691e-05 | 5.00587e-05 | 2(Loss) | true |
| Glaze | 1236.27 | 0.0504484 | 1077.53ms | 4604 | 4890 | 15698.1 | 3551.58 | 0.254249 | 4.20672 | 12.8371 | 1.11838 | 0.000890796 | 4.3174e-05 | 1.82112e-05 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1524.38 | 0.295867 | 1028.45ms | 4918 | 40 | 3314.69 | 3076.78 | 0.0935294 | 3.42233 | 11.2717 | 1.32351 | 0.000523587 | 5.08337e-05 | 2.03335e-05 | 1(Win) | true |
| Jsonifier | 1445.78 | 0.135504 | 1023.64ms | 4604 | 2560 | 43351.6 | 3036.91 | 0.313411 | 3.60046 | 9.42832 | 0.5404 | 0.000319016 | 4.36102e-05 | 1.51872e-05 | 2(Loss) | true |
| Glaze | 1326.76 | 0.0540367 | 1050.12ms | 4604 | 4890 | 15637.6 | 3309.35 | 0.0137226 | 3.92119 | 12.2024 | 0.968289 | 0.000759409 | 3.29579e-05 | 1.08823e-05 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2665.43 | 0.031247 | 1388.52ms | 18245 | 4890 | 20345.9 | 6527.95 | 0.0472539 | 1.91199 | 7.83217 | 1.41611 | 0.00136936 | 2.54881e-05 | 1.23854e-05 | 1(Win) | true |
| Jsonifier | 2320.97 | 0.0790239 | 1488.18ms | 18245 | 640 | 22461.8 | 7496.77 | 0.0250462 | 2.22547 | 8.10918 | 1.85678 | 0.00196955 | 1.24178e-05 | 2.141e-06 | 2(Loss) | true |
| simdjson (reflection) | 2286.71 | 0.0792033 | 1500.05ms | 18245 | 640 | 23245.2 | 7609.1 | 0.0415859 | 2.22102 | 8.34546 | 1.42834 | 0.00140252 | 2.15813e-05 | 1.1647e-05 | 3(Loss) | true |
| Glaze | 1836.69 | 0.0273511 | 1684.2ms | 18245 | 2560 | 17187.2 | 9473.44 | 0.0485991 | 2.75658 | 11.7976 | 2.31461 | 0.00346291 | 6.09756e-05 | 3.5562e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1830.35 | 0.0441951 | 1688.28ms | 18245 | 2560 | 45186.5 | 9506.27 | 0.101253 | 2.77259 | 10.0311 | 1.85733 | 0.0019941 | 4.81939e-05 | 2.51781e-05 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3135.51 | 0.0502622 | 1395.05ms | 18245 | 2560 | 19915.6 | 5549.26 | 0.0725495 | 1.64465 | 6.76881 | 1.17408 | 0.00125141 | 4.53463e-05 | 2.28873e-05 | 1(Win) | true |
| Jsonifier | 2621.95 | 0.0924497 | 1493.48ms | 18245 | 30 | 1129.2 | 6636.2 | 0.144452 | 1.94286 | 7.04768 | 1.61562 | 0.00169544 | 3.83667e-05 | 0 | 2(Loss) | true |
| simdjson (reflection) | 2547.54 | 0.155436 | 1512.04ms | 18245 | 160 | 18033.1 | 6830.04 | 0.0903079 | 1.99378 | 7.81058 | 1.29866 | 0.000859825 | 2.84324e-05 | 8.56399e-06 | 3(Loss) | true |
| Glaze | 2023.14 | 0.0570915 | 1682.21ms | 18245 | 1280 | 30859.4 | 8600.38 | 0.0165536 | 2.50876 | 10.7842 | 2.08375 | 0.00336098 | 1.99113e-05 | 8.52117e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1970.78 | 0.0319392 | 1724.6ms | 18245 | 2560 | 20356.4 | 8828.89 | 0.0228971 | 2.57704 | 9.64253 | 1.76174 | 0.00146249 | 5.08701e-05 | 2.92246e-05 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6461.03 | 0.136288 | 1091.49ms | 24579 | 1280 | 31293.4 | 3627.96 | 0.0621949 | 0.790555 | 1.88596 | 0.105497 | 6.30937e-05 | 2.00247e-05 | 9.24951e-06 | 1(Win) | true |
| Glaze | 3457.82 | 0.0707246 | 1415.45ms | 24579 | 4890 | 112402 | 6778.94 | 0.323455 | 1.47662 | 3.91025 | 0.475813 | 0.000347546 | 2.33378e-05 | 1.12238e-05 | 2(Loss) | true |
| simdjson (reflection) | 530.244 | 0.092585 | 5232.84ms | 24893 | 4890 | 8.40221e+06 | 44771.5 | 0.00556044 | 9.57697 | 36.8001 | 6.04387 | 0.00773168 | 0.000210644 | 0.000147396 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6593.91 | 0.0876523 | 1089.17ms | 24579 | 2560 | 24854.8 | 3554.85 | 0.135331 | 0.774122 | 1.86513 | 0.100655 | 6.67808e-05 | 7.48543e-06 | 1.90712e-06 | 1(Win) | true |
| Glaze | 3908.62 | 0.139005 | 1333.58ms | 24579 | 1280 | 88951.2 | 5997.09 | 0.038484 | 1.30296 | 3.76179 | 0.442166 | 0.000324051 | 3.22303e-05 | 1.82447e-05 | 2(Loss) | true |
| simdjson (reflection) | 529.97 | 0.123376 | 5233.81ms | 24893 | 2560 | 7.81909e+06 | 44794.7 | 0.0199464 | 9.54563 | 36.8171 | 6.04773 | 0.00763416 | 0.000118005 | 7.24193e-05 | 3(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1558.44 | 0.0337227 | 1045.3ms | 5094 | 4890 | 5403.68 | 3117.23 | 0.0388875 | 3.29631 | 14.0361 | 2.40067 | 0.000773636 | 5.86519e-05 | 1.97514e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1470.57 | 0.070983 | 1062.61ms | 5094 | 1280 | 7038.27 | 3303.5 | 0.0523867 | 3.47728 | 15.0879 | 2.54496 | 0.00177798 | 7.26958e-05 | 3.03666e-05 | 2(Loss) | true |
| Glaze | 1230.51 | 0.0341053 | 1129.16ms | 5094 | 4890 | 8865.48 | 3947.98 | 0.146615 | 4.14996 | 17.4117 | 3.31547 | 0.00530413 | 6.74839e-05 | 2.16783e-05 | 3(Loss) | true |
| simdjson (reflection) | 1059.61 | 0.11009 | 1195.23ms | 5094 | 30 | 764.271 | 4584.73 | 0.0152657 | 4.8162 | 16.0212 | 2.64036 | 0.00301008 | 8.50674e-05 | 4.58055e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1042.43 | 0.0393414 | 1203.63ms | 5094 | 4890 | 16437.3 | 4660.28 | 0.123346 | 4.88021 | 17.3952 | 2.92599 | 0.00415008 | 0.000112326 | 5.15061e-05 | 5(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1892.53 | 0.106808 | 1048.92ms | 5094 | 2560 | 19243.3 | 2566.94 | 0.0270495 | 2.71726 | 11.5734 | 1.84354 | 0.000511325 | 8.58854e-05 | 3.21303e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1772.61 | 0.194754 | 1068.3ms | 5094 | 40 | 1139.53 | 2740.6 | 0.0182409 | 2.89704 | 12.8838 | 2.0373 | 0.00107479 | 4.90773e-05 | 9.81547e-06 | 2(Loss) | true |
| Glaze | 1550.34 | 0.0474971 | 1104.07ms | 5094 | 4890 | 10831.9 | 3133.51 | 0.103073 | 3.30066 | 14.2311 | 2.61602 | 0.00503359 | 7.89653e-05 | 3.03898e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1274.94 | 0.112977 | 1176.4ms | 5094 | 40 | 741.266 | 3810.38 | 0.0501077 | 4.01048 | 14.7291 | 2.34079 | 0.00316549 | 6.38005e-05 | 0 | 4(Loss) | true |
| simdjson (reflection) | 1159.15 | 0.101086 | 1224.75ms | 5094 | 30 | 538.447 | 4191.03 | 0.155646 | 4.40628 | 15.1195 | 2.41417 | 0.00245387 | 4.58055e-05 | 1.96309e-05 | 5(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13649.8 | 0.057953 | 762.637ms | 5094 | 4890 | 208.03 | 355.903 | 0.0155416 | 0.412317 | 1.61739 | 0.263251 | 0.00019643 | 5.54403e-05 | 2.14375e-05 | 1(Win) | true |
| simdjson (reflection) | 8136.47 | 0.0719176 | 785.816ms | 5094 | 4890 | 901.622 | 597.067 | 0.421661 | 0.672695 | 2.41303 | 0.355713 | 0.00019643 | 7.63961e-05 | 4.27144e-05 | 2(Loss) | true |
| Glaze | 4212.4 | 0.0617227 | 848.576ms | 5094 | 4890 | 2477.75 | 1153.27 | 0.0406282 | 1.2436 | 5.17668 | 0.832352 | 0.000291052 | 7.25421e-05 | 2.86636e-05 | 3(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16331.4 | 0.12396 | 756.295ms | 5094 | 640 | 87.0191 | 297.464 | 0.0467275 | 0.352461 | 1.4998 | 0.236749 | 0.000196309 | 1.59501e-05 | 2.7606e-06 | 1(Win) | true |
| simdjson (reflection) | 8965.25 | 0.0520829 | 783.617ms | 5094 | 640 | 50.9757 | 541.872 | 0.0409293 | 0.606597 | 2.29388 | 0.329211 | 0.000196309 | 1.87107e-05 | 6.13467e-07 | 2(Loss) | true |
| Glaze | 4992.07 | 0.104492 | 826.957ms | 5094 | 2560 | 2647.05 | 973.146 | 0.199655 | 1.05434 | 4.69925 | 0.724382 | 0.000200374 | 4.25593e-05 | 1.59501e-05 | 3(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2211.26 | 0.0404411 | 1087.84ms | 8051 | 4890 | 9642.17 | 3472.24 | 0.00367392 | 2.30076 | 10.1353 | 1.63284 | 0.000931866 | 4.98611e-05 | 2.10062e-05 | 1(Win) | true |
| Jsonifier | 1910.07 | 0.0366601 | 1138.81ms | 8051 | 4890 | 10619.4 | 4019.77 | 0.0352527 | 2.66654 | 11.1009 | 2.0908 | 0.00183262 | 4.72702e-05 | 1.86693e-05 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1604.23 | 0.0395807 | 1221.3ms | 8051 | 4890 | 17548.5 | 4786.11 | 0.133283 | 3.14579 | 10.6683 | 1.69309 | 0.00192071 | 5.28075e-05 | 2.18698e-05 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 1602.74 | 0.0341106 | 1216.17ms | 8051 | 4890 | 13057.5 | 4790.56 | 0.126033 | 3.17142 | 13.5927 | 2.61123 | 0.00362231 | 4.51112e-05 | 1.56721e-05 | 3(Tie) | true |
| simdjson (ondemand) | 1591.53 | 0.0468132 | 1224.38ms | 8051 | 2560 | 13057 | 4824.3 | 0.0523829 | 3.17814 | 11.5345 | 1.87356 | 0.00282171 | 4.84703e-05 | 1.94075e-05 | 5(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2628.48 | 0.0876684 | 1094.57ms | 8051 | 640 | 4197.16 | 2921.09 | 0.130902 | 1.94619 | 8.74065 | 1.31164 | 0.000541664 | 4.46373e-05 | 6.21041e-06 | 1(Win) | true |
| Jsonifier | 2242.11 | 0.0795345 | 1135.28ms | 8051 | 640 | 4747.63 | 3424.46 | 0.0875738 | 2.28115 | 9.54242 | 1.73829 | 0.00170612 | 3.68743e-05 | 6.98671e-06 | 2(Loss) | true |
| Glaze | 1946.34 | 0.0341039 | 1189.94ms | 8051 | 2560 | 4633.53 | 3944.87 | 0.120505 | 2.62185 | 11.5787 | 2.16818 | 0.00346255 | 3.22165e-05 | 1.00919e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1922.94 | 0.049663 | 1195.95ms | 8051 | 320 | 1258.3 | 3992.86 | 0.232998 | 2.658 | 9.90784 | 1.51509 | 0.00239489 | 2.52298e-05 | 6.21041e-06 | 4(Loss) | true |
| simdjson (reflection) | 1728.66 | 0.0536155 | 1252.7ms | 8051 | 2560 | 14517.8 | 4441.61 | 0.10734 | 2.93531 | 10.116 | 1.55407 | 0.00189054 | 3.63406e-05 | 1.12078e-05 | 5(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 25479 | 0.160567 | 757.837ms | 9255 | 160 | 49.5017 | 346.413 | 0.0432822 | 0.225525 | 0.931172 | 0.143922 | 0.00010805 | 4.05186e-06 | 0 | 1(Win) | true |
| Glaze | 3659.55 | 0.148137 | 985.075ms | 9255 | 1280 | 16339.4 | 2411.84 | 0.0317343 | 1.40416 | 4.80886 | 0.812858 | 0.000168912 | 3.25837e-05 | 9.53876e-06 | 2(Loss) | true |
| simdjson (reflection) | 527.287 | 0.0972986 | 2415.62ms | 9255 | 4890 | 1.29712e+06 | 16739 | 0.488054 | 9.5822 | 37.9983 | 7.26375 | 0.0205013 | 0.000241466 | 0.000150297 | 3(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 27584.3 | 0.0837096 | 760.785ms | 9255 | 1280 | 91.8312 | 319.974 | 0.270043 | 0.20765 | 0.871637 | 0.130308 | 0.00010805 | 1.46036e-05 | 7.09076e-06 | 1(Win) | true |
| Glaze | 5287.85 | 0.0733667 | 904.378ms | 9255 | 4890 | 7333.32 | 1669.16 | 0.0409941 | 0.976078 | 4.47317 | 0.737012 | 0.000171156 | 4.33966e-05 | 1.92899e-05 | 2(Loss) | true |
| simdjson (reflection) | 530.679 | 0.0979112 | 2411.29ms | 9255 | 4890 | 1.29677e+06 | 16632 | 0.324497 | 9.50851 | 38.0025 | 7.26424 | 0.0204545 | 0.0001284 | 6.74813e-05 | 3(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5499.13 | 0.133818 | 778.169ms | 2889 | 320 | 143.843 | 501.019 | 0.100942 | 0.994484 | 3.89166 | 0.51298 | 0.000352631 | 5.08394e-05 | 8.65351e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 5473.08 | 0.0444554 | 779.74ms | 2889 | 2560 | 128.209 | 503.403 | 0.121292 | 0.998861 | 3.89166 | 0.51298 | 0.000346276 | 2.90704e-05 | 5.67887e-06 | 2(Loss) | true |
| simdjson (ondemand) | 5441.91 | 0.0944659 | 779.638ms | 2889 | 4890 | 1118.54 | 506.287 | 0.0672817 | 1.00351 | 3.89997 | 0.416753 | 0.000720171 | 1.91828e-05 | 2.83142e-06 | 3(Loss) | true |
| simdjson (reflection) | 5214.58 | 0.117122 | 777.779ms | 2889 | 4890 | 1872.58 | 528.358 | 0.0464701 | 1.04157 | 3.87643 | 0.422639 | 0.000858981 | 3.91443e-05 | 1.21043e-05 | 4(Loss) | true |
| Glaze | 3082.08 | 0.0363891 | 817.662ms | 2889 | 4890 | 517.438 | 893.929 | 0.22526 | 1.7148 | 7.24922 | 1.24264 | 0.00034699 | 2.57659e-05 | 5.73362e-06 | 5(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 5753.71 | 0.224463 | 779.112ms | 2889 | 160 | 184.845 | 478.85 | 0.218796 | 0.956012 | 3.75666 | 0.480789 | 0.000356957 | 7.13915e-05 | 3.24507e-05 | 1(Win) | true |
| Jsonifier | 5721.75 | 0.14687 | 777.959ms | 2889 | 640 | 320.1 | 481.525 | 0.280866 | 0.95605 | 3.75666 | 0.480789 | 0.000346681 | 4.97577e-05 | 1.67662e-05 | 2(Loss) | true |
| simdjson (ondemand) | 5611.33 | 0.123396 | 778.33ms | 2889 | 2560 | 939.729 | 491 | 0.106731 | 0.976239 | 3.82624 | 0.399792 | 0.000715943 | 1.7307e-05 | 3.24507e-06 | 3(Loss) | true |
| simdjson (reflection) | 5371.08 | 0.225054 | 781.937ms | 2889 | 80 | 106.619 | 512.962 | 0.0754846 | 1.01775 | 3.81308 | 0.406369 | 0.000891312 | 8.65351e-06 | 0 | 4(Loss) | true |
| Glaze | 3147.95 | 0.283213 | 815.146ms | 2889 | 40 | 245.769 | 875.225 | 0.0504378 | 1.71327 | 7.17965 | 1.22603 | 0.000346141 | 8.65351e-06 | 8.65351e-06 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 6666.72 | 0.0970474 | 772.58ms | 3808 | 320 | 89.4308 | 544.734 | 0.0373027 | 0.828466 | 3.302 | 0.383403 | 0.000262605 | 4.1032e-06 | 0 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 6550.16 | 0.114915 | 771.952ms | 3808 | 320 | 129.895 | 554.428 | 0.103041 | 0.849186 | 3.302 | 0.383403 | 0.000787815 | 1.31303e-05 | 8.20641e-07 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 6532.21 | 0.17306 | 776.082ms | 3808 | 4890 | 4526.64 | 555.952 | 0.059298 | 0.843771 | 3.31119 | 0.33167 | 0.000638469 | 2.26624e-05 | 9.55904e-06 | 2(Tie) | true |
| simdjson (reflection) | 6491.94 | 0.258086 | 777.927ms | 3808 | 80 | 166.749 | 559.4 | 0.160628 | 0.858682 | 3.29333 | 0.336134 | 0.000810793 | 2.62605e-05 | 0 | 4(Loss) | true |
| Glaze | 3511.62 | 0.063028 | 817.371ms | 3808 | 4890 | 2077.57 | 1034.16 | 0.054038 | 1.51875 | 6.58508 | 1.20746 | 0.000269425 | 1.68089e-05 | 8.96831e-06 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6869.4 | 0.202679 | 768.972ms | 3808 | 80 | 91.8467 | 528.663 | 0.740794 | 0.809385 | 3.25289 | 0.371061 | 0.000262605 | 1.31303e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6826.94 | 0.207927 | 769.241ms | 3808 | 80 | 97.8709 | 531.95 | 0.0611333 | 0.810727 | 3.25289 | 0.371061 | 0.000262605 | 2.62605e-05 | 6.56513e-06 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 6826.42 | 0.141168 | 771.96ms | 3808 | 320 | 180.48 | 531.991 | 0.227848 | 0.809595 | 3.2542 | 0.318803 | 0.000510439 | 1.88747e-05 | 0 | 2(Tie) | true |
| simdjson (reflection) | 6605.78 | 0.374051 | 777.729ms | 3808 | 640 | 2706.36 | 549.759 | 0.397199 | 0.832836 | 3.24422 | 0.323792 | 0.000543675 | 1.39509e-05 | 2.46192e-06 | 4(Loss) | true |
| Glaze | 3558.65 | 0.0522688 | 821.921ms | 3808 | 640 | 182.091 | 1020.5 | 0.120798 | 1.50001 | 6.53151 | 1.19433 | 0.000265888 | 3.28256e-06 | 0 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2869.9 | 0.0406274 | 822.697ms | 2889 | 640 | 97.3595 | 960.02 | 0.144806 | 1.87013 | 6.11769 | 0.996192 | 0.000346141 | 3.51549e-05 | 5.40845e-06 | 1(Win) | true |
| Glaze | 2390.38 | 0.11225 | 837.371ms | 2889 | 320 | 535.656 | 1152.61 | 0.0271051 | 2.23074 | 8.85739 | 1.54552 | 0.000347222 | 7.13915e-05 | 3.1369e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2254.71 | 0.164842 | 848.882ms | 2889 | 80 | 324.594 | 1221.96 | 0.0173931 | 2.31914 | 8.01211 | 1.19315 | 0.000350467 | 5.62478e-05 | 2.59605e-05 | 3(Loss) | true |
| simdjson (reflection) | 1997.5 | 0.0961764 | 867.033ms | 2889 | 2560 | 4505.03 | 1379.3 | 0.00232222 | 2.61896 | 9.23295 | 1.30737 | 0.000418073 | 0.000200248 | 0.000107358 | 4(Loss) | true |
| simdjson (ondemand) | 1359.42 | 0.0639311 | 933.252ms | 2889 | 1280 | 2148.93 | 2026.72 | 0.00543489 | 3.8219 | 12.091 | 2.41537 | 0.00065334 | 0.000180913 | 0.000107358 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3131.85 | 0.168356 | 821.947ms | 2889 | 40 | 87.7429 | 879.725 | 0.0786849 | 1.69039 | 5.59086 | 0.858082 | 0.000346141 | 6.92281e-05 | 0 | 1(Win) | true |
| Glaze | 2590.72 | 0.0447899 | 835.856ms | 2889 | 2560 | 580.838 | 1063.48 | 0.216483 | 2.06132 | 8.32399 | 1.40222 | 0.000347493 | 6.40901e-05 | 3.42084e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2499.2 | 0.0578482 | 846.025ms | 2889 | 4890 | 1988.75 | 1102.42 | 0.286771 | 2.1088 | 7.39495 | 1.03669 | 0.00047136 | 0.000103842 | 3.06501e-05 | 3(Loss) | true |
| simdjson (reflection) | 2136.71 | 0.111822 | 864.727ms | 2889 | 640 | 1330.58 | 1289.44 | 0.0547418 | 2.44367 | 8.72343 | 1.17342 | 0.000519752 | 0.000164417 | 8.05858e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1443.61 | 0.0572507 | 928.013ms | 2889 | 2560 | 3056.33 | 1908.53 | 0.164582 | 3.5948 | 11.7099 | 2.31395 | 0.000352631 | 0.000111144 | 2.90704e-05 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8931.82 | 0.116441 | 756.603ms | 2963 | 4890 | 663.6 | 316.367 | 0.292359 | 0.648065 | 1.48059 | 0.233885 | 0.00033791 | 7.76447e-05 | 4.3274e-05 | 1(Win) | true |
| simdjson (reflection) | 6786.47 | 0.0530955 | 764.569ms | 2963 | 1280 | 62.5606 | 416.378 | 0.0082564 | 0.829783 | 1.92609 | 0.291596 | 0.000337496 | 2.97945e-05 | 6.59171e-06 | 2(Loss) | true |
| Glaze | 5497.76 | 0.0946317 | 775.409ms | 2963 | 2560 | 605.627 | 513.98 | 0.156196 | 0.999527 | 2.97401 | 0.458657 | 0.000338023 | 8.13418e-05 | 3.78364e-05 | 3(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10849.6 | 0.0544652 | 746.171ms | 2963 | 1280 | 25.7563 | 260.446 | 0.0830216 | 0.548246 | 1.31455 | 0.195748 | 0.000337759 | 2.42575e-05 | 1.08104e-05 | 1(Win) | true |
| simdjson (reflection) | 7440.68 | 0.118847 | 759.937ms | 2963 | 160 | 32.594 | 379.769 | 0.140084 | 0.753736 | 1.75363 | 0.251434 | 0.000337496 | 8.43739e-06 | 0 | 2(Loss) | true |
| Glaze | 6695.59 | 0.12659 | 764.81ms | 2963 | 2560 | 730.679 | 422.029 | 0.0235969 | 0.830407 | 2.53156 | 0.365171 | 0.000337891 | 6.16984e-05 | 2.58395e-05 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2852.82 | 0.0424595 | 855.351ms | 3808 | 640 | 186.972 | 1272.98 | 0.202568 | 1.82978 | 6.42227 | 0.899947 | 0.000263015 | 4.88281e-05 | 6.56513e-06 | 1(Win) | true |
| simdjson (reflection) | 2489.13 | 0.136178 | 877.894ms | 3808 | 640 | 2526.33 | 1458.98 | 0.330299 | 2.12741 | 7.35714 | 1.00735 | 0.000529313 | 5.3752e-05 | 1.10787e-05 | 2(Loss) | true |
| Jsonifier | 2442.26 | 0.0508837 | 876.139ms | 3808 | 2560 | 1465.57 | 1486.98 | 0.0492053 | 2.15188 | 6.24081 | 1.14076 | 0.000267631 | 4.65714e-05 | 1.18993e-05 | 3(Loss) | true |
| Glaze | 2369.21 | 0.0883374 | 883.651ms | 3808 | 80 | 146.678 | 1532.83 | 0.0669147 | 2.23284 | 8.38157 | 1.51576 | 0.000262605 | 2.29779e-05 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 1765.77 | 0.0534188 | 936.491ms | 3808 | 4890 | 5902.32 | 2056.66 | 0.211896 | 2.93589 | 9.52495 | 1.84795 | 0.000489874 | 7.71167e-05 | 3.79676e-05 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3142.04 | 0.038514 | 850.177ms | 3808 | 4890 | 968.983 | 1155.81 | 0.139778 | 1.67449 | 6.02048 | 0.79438 | 0.000263679 | 6.498e-05 | 2.43272e-05 | 1(Win) | true |
| simdjson (reflection) | 2697.81 | 0.08445 | 871.858ms | 3808 | 2560 | 3308.34 | 1346.12 | 0.176816 | 1.93986 | 6.96928 | 0.905462 | 0.0003141 | 8.56544e-05 | 3.06714e-05 | 2(Loss) | true |
| Jsonifier | 2663.38 | 0.0649182 | 872.056ms | 3808 | 80 | 62.6829 | 1363.53 | 0.00183345 | 1.99123 | 5.84034 | 1.03598 | 0.000262605 | 2.29779e-05 | 0 | 3(Loss) | true |
| Glaze | 2475.99 | 0.0492752 | 877.384ms | 3808 | 320 | 167.148 | 1466.72 | 0.13596 | 2.09922 | 7.97637 | 1.4073 | 0.000262605 | 1.64128e-05 | 1.64128e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1844.19 | 0.0453349 | 936.122ms | 3808 | 4890 | 3897.21 | 1969.2 | 0.304393 | 2.81104 | 9.23582 | 1.77101 | 0.000269103 | 0.000118468 | 6.45504e-05 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12409.5 | 0.0808938 | 759.734ms | 4300 | 4890 | 349.436 | 330.456 | 0.376374 | 0.458129 | 1.06977 | 0.162558 | 0.000232939 | 3.25296e-05 | 1.33638e-05 | 1(Win) | true |
| Glaze | 3697.18 | 0.189439 | 842.028ms | 4300 | 4890 | 21589.6 | 1109.17 | 0.207374 | 1.42835 | 3.58116 | 0.600233 | 0.000504066 | 9.26428e-05 | 5.02211e-05 | 2(Loss) | true |
| simdjson (reflection) | 557.77 | 0.267167 | 1472.54ms | 4300 | 320 | 123464 | 7352.13 | 0.33602 | 9.17989 | 33.5747 | 7.40861 | 0.0103365 | 0.000242006 | 0.000162791 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14136.4 | 0.0529845 | 757.295ms | 4300 | 320 | 7.55972 | 290.087 | 0.0517353 | 0.40861 | 0.951395 | 0.134884 | 0.000232558 | 1.23547e-05 | 6.5407e-06 | 1(Win) | true |
| Glaze | 4236.06 | 0.552919 | 828.282ms | 4300 | 640 | 18336.4 | 968.069 | 0.505531 | 1.25837 | 3.03163 | 0.47721 | 0.00072202 | 3.08866e-05 | 9.44767e-06 | 2(Loss) | true |
| simdjson (reflection) | 552.886 | 0.0941237 | 1484.8ms | 4300 | 2560 | 124768 | 7417.09 | 0.0123411 | 9.1965 | 33.5838 | 7.41082 | 0.0106289 | 0.000349564 | 0.000222202 | 3(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3210.69 | 0.209868 | 7581.05ms | 466906 | 40 | 3.38853e+06 | 138685 | 0.0205519 | 1.57358 | 6.31273 | 1.26005 | 0.00185101 | 0.000172304 | 3.10555e-06 | 1(Win) | true |
| Glaze | 2547.82 | 0.0258273 | 9376.78ms | 466906 | 640 | 1.30394e+06 | 174767 | 0.0773654 | 1.98624 | 8.75464 | 1.96145 | 0.00261981 | 0.000774135 | 9.38358e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1887.96 | 0.145469 | 6260.28ms | 466906 | 320 | 3.76673e+07 | 235850 | 0.00480731 | 2.64373 | 11.9923 | 1.52298 | 0.00453522 | 0.0746748 | 3.64567e-05 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3220.76 | 0.0283041 | 7425.26ms | 466906 | 2560 | 3.91995e+06 | 138252 | 0.00237994 | 1.56377 | 6.31155 | 1.25978 | 0.00185393 | 0.000113174 | 1.12995e-05 | 1(Win) | true |
| Glaze | 2548.92 | 0.155628 | 9355.53ms | 466906 | 30 | 2.2174e+06 | 174692 | 0.290144 | 1.98785 | 8.75349 | 1.96119 | 0.0025851 | 0.000906035 | 2.07751e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1867.58 | 0.145395 | 6293.94ms | 466906 | 320 | 3.84546e+07 | 238425 | 0.0410295 | 2.67747 | 11.992 | 1.5229 | 0.00474153 | 0.0908918 | 1.49722e-05 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4144.31 | 0.0352662 | 8595.99ms | 699405 | 2560 | 8.24728e+06 | 160945 | 0.0920891 | 1.21125 | 4.79602 | 1.19835 | 0.00190331 | 0.000292565 | 8.06601e-06 | 1(Win) | true |
| Glaze | 3170.93 | 0.192153 | 5550.71ms | 699405 | 640 | 1.04558e+08 | 210350 | 0.0403503 | 1.58671 | 6.2876 | 1.35582 | 0.00202751 | 0.00107157 | 1.48743e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2441.4 | 0.100493 | 7858.44ms | 767297 | 1280 | 1.16127e+08 | 299726 | 0.0627442 | 2.05234 | 8.04353 | 1.07977 | 0.00360769 | 0.0968921 | 1.84566e-05 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4158.09 | 0.149257 | 8616.55ms | 699405 | 160 | 9.17188e+06 | 160411 | 0.0782375 | 1.20637 | 4.79552 | 1.19825 | 0.00201301 | 0.000270534 | 4.13745e-06 | 1(Win) | true |
| Glaze | 3164.73 | 0.101944 | 5535.68ms | 699405 | 30 | 1.38493e+06 | 210762 | 0.0324801 | 1.59631 | 6.2869 | 1.35566 | 0.0019976 | 0.00108902 | 3.56493e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2472.82 | 0.186997 | 7765.7ms | 767297 | 320 | 9.79856e+07 | 295918 | 0.0196257 | 2.03245 | 8.04403 | 1.07991 | 0.00340006 | 0.0916605 | 8.18987e-05 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2982.62 | 0.203396 | 5344.11ms | 631514 | 80 | 1.34941e+07 | 201923 | 0.0257281 | 1.70128 | 8.25722 | 1.35256 | 0.00544772 | 6.99509e-05 | 6.62891e-05 | 1(Win) | true |
| Glaze | 2172.79 | 0.0987368 | 7220.52ms | 631514 | 640 | 4.79369e+07 | 277183 | 0.374743 | 2.32318 | 9.80782 | 1.64384 | 0.00936898 | 1.84329e-05 | 1.60156e-05 | 2(Loss) | true |
