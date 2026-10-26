# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the Clang 24.0.0 compiler).  

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

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1901.57 | 0.0515945 | 773.521ms | 905 | 4890 | 268.156 | 453.874 | 0.14472 | 2.89632 | 13.4994 | 2.29171 | 0.00114565 | 0.000123829 | 1.22021e-05 | 1(Win) | true |
| glaze | 1520.58 | 0.381073 | 785.097ms | 905 | 1280 | 5988.35 | 567.598 | 0.412455 | 3.55552 | 17.589 | 2.29171 | 0.00113432 | 0.000139848 | 2.07182e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 619.326 | 0.200534 | 873.968ms | 905 | 640 | 4998.2 | 1393.57 | 0.283535 | 8.28131 | 42.0011 | 5.06851 | 0.0011067 | 8.28729e-05 | 6.90608e-06 | 3(Loss) | true |
| simdjson (ondemand) | 288.453 | 0.0434519 | 1030.48ms | 905 | 4890 | 8265.56 | 2992.08 | 0.00451897 | 17.7432 | 89.6033 | 9.47956 | 0.00665153 | 0.000266188 | 0.00011592 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2049.84 | 0.112847 | 775.983ms | 905 | 2560 | 577.94 | 421.046 | 0.128566 | 2.65586 | 12.842 | 2.17127 | 0.00111015 | 0.000135532 | 2.41713e-05 | 1(Win) | true |
| glaze | 1665.29 | 0.0685213 | 783.839ms | 905 | 1280 | 161.428 | 518.273 | 0.35626 | 3.24858 | 16.9249 | 2.17127 | 0.00111619 | 8.80525e-05 | 6.90608e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 639.415 | 0.0912584 | 864.878ms | 905 | 2560 | 3884.35 | 1349.79 | 0.029047 | 8.10875 | 41.3834 | 4.94807 | 0.00168465 | 0.000109202 | 1.07907e-05 | 3(Loss) | true |
| simdjson (ondemand) | 290.994 | 0.0685758 | 1026.29ms | 905 | 640 | 2647.59 | 2965.95 | 0.00753284 | 17.5989 | 88.989 | 9.35912 | 0.00759496 | 6.73343e-05 | 5.17956e-06 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2481.76 | 0.0543063 | 763.495ms | 905 | 4890 | 174.417 | 347.768 | 0.291042 | 2.26908 | 8.82542 | 0.919339 | 0.00339446 | 9.26459e-05 | 3.59285e-05 | 1(Win) | true |
| glaze | 207.574 | 0.0669333 | 1146.51ms | 905 | 1280 | 9913.98 | 4157.93 | 0.0505368 | 24.3785 | 111.801 | 22.737 | 0.0785739 | 0.000214952 | 4.48895e-05 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5202.87 | 0.0641776 | 749.936ms | 905 | 1280 | 14.5073 | 165.884 | 0.0103622 | 1.21332 | 5.35249 | 0.272928 | 0.00221685 | 2.41713e-05 | 1.72652e-06 | 1(Win) | true |
| glaze | 870.683 | 0.0721908 | 842.089ms | 905 | 1280 | 655.468 | 991.263 | 0.172776 | 6.06659 | 24.5017 | 3.14917 | 0.00323032 | 0.000413501 | 0.000184738 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1308.58 | 0.0583429 | 867.229ms | 1811 | 160 | 94.8707 | 1319.83 | 0.0127874 | 3.98238 | 19.7195 | 4.06074 | 0.00057979 | 6.90226e-05 | 6.90226e-06 | 1(Win) | true |
| glaze | 977.715 | 0.0865172 | 910.335ms | 1811 | 1280 | 2989.7 | 1766.47 | 0.0430068 | 5.26474 | 26.487 | 4.27002 | 0.00145336 | 7.24738e-05 | 2.58835e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 757.83 | 0.0618842 | 962.77ms | 1811 | 4890 | 9726.62 | 2279.01 | 0.0845258 | 6.78634 | 33.3722 | 5.49973 | 0.00056336 | 0.000175478 | 7.6673e-05 | 3(Loss) | true |
| simdjson (ondemand) | 335.082 | 0.0891894 | 1256.2ms | 1811 | 2560 | 54100.7 | 5154.28 | 0.0620383 | 14.9638 | 70.8609 | 9.14357 | 0.00131014 | 0.000137182 | 2.91189e-05 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1438.39 | 0.0535684 | 851.598ms | 1811 | 4890 | 2023.06 | 1200.72 | 0.185919 | 3.62507 | 18.6273 | 3.80784 | 0.000822851 | 0.000113146 | 3.08273e-05 | 1(Win) | true |
| glaze | 1053.3 | 0.128253 | 898.036ms | 1811 | 80 | 353.802 | 1639.71 | 0.101493 | 4.91532 | 25.4859 | 4.04583 | 0.002119 | 9.66317e-05 | 4.14136e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 812.397 | 0.140766 | 945.56ms | 1811 | 160 | 1432.9 | 2125.94 | 0.012349 | 6.37058 | 32.2706 | 5.24682 | 0.00221218 | 0.00012079 | 4.48647e-05 | 3(Loss) | true |
| simdjson (ondemand) | 348.157 | 0.0732797 | 1233.07ms | 1811 | 4890 | 64619.4 | 4960.7 | 0.165952 | 14.4371 | 69.7388 | 8.8857 | 0.000692767 | 0.000101177 | 2.14549e-05 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 340.124 | 0.0518719 | 1247.78ms | 1811 | 1280 | 8880.45 | 5077.86 | 0.038232 | 14.9701 | 62.9144 | 11.1011 | 0.0190835 | 9.18864e-05 | 1.29417e-05 | 1(Win) | true |
| glaze | 302.722 | 0.0593496 | 1305.54ms | 1798 | 1280 | 14465.6 | 5664.3 | 0.0605263 | 16.7824 | 70.8415 | 12.1902 | 0.0199636 | 0.000245498 | 0.000122097 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 907.545 | 0.0553514 | 929.459ms | 1811 | 160 | 177.532 | 1903.05 | 0.0335101 | 5.69416 | 19.3771 | 1.25069 | 0.00057979 | 0.000134594 | 4.14136e-05 | 1(Win) | true |
| glaze | 658.238 | 0.0857234 | 1006.88ms | 1798 | 1280 | 6382.96 | 2604.99 | 0.0936025 | 7.80343 | 27.3231 | 2.17241 | 0.000749965 | 0.000122097 | 4.04095e-05 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3139.36 | 0.11112 | 850.111ms | 3862 | 1280 | 2175.38 | 1173.2 | 0.1257 | 1.66329 | 8.57898 | 1.01321 | 0.000279972 | 2.83208e-05 | 1.82062e-06 | 1(Win) | true |
| glaze | 1771.1 | 0.0506021 | 940.779ms | 3862 | 1280 | 1417.37 | 2079.55 | 0.0903958 | 2.90998 | 14.0316 | 1.72838 | 0.000288468 | 5.03706e-05 | 1.49696e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1598.19 | 0.0903566 | 964.209ms | 3862 | 320 | 1387.51 | 2304.53 | 0.0259067 | 3.22099 | 14.8856 | 1.78871 | 0.000521103 | 0.000121375 | 7.68708e-05 | 3(Loss) | true |
| simdjson (ondemand) | 788.417 | 0.0601862 | 1208.12ms | 3862 | 320 | 2529.62 | 4671.5 | 0.114387 | 6.46548 | 28.3881 | 3.55231 | 0.0130235 | 3.56033e-05 | 4.855e-06 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3464.68 | 0.0670842 | 837.475ms | 3862 | 4890 | 2486.83 | 1063.04 | 0.0125903 | 1.50369 | 8.09011 | 0.903418 | 0.000260522 | 6.60836e-05 | 2.41989e-05 | 1(Win) | true |
| glaze | 1833.62 | 0.0350165 | 928.634ms | 3862 | 640 | 316.615 | 2008.64 | 0.0489531 | 2.81314 | 13.5342 | 1.62118 | 0.00030546 | 2.71071e-05 | 1.17329e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1728.67 | 0.0653626 | 946.466ms | 3862 | 2560 | 4964.76 | 2130.59 | 0.112698 | 2.9707 | 14.3853 | 1.67892 | 0.00026217 | 5.5529e-05 | 1.17329e-05 | 3(Loss) | true |
| simdjson (ondemand) | 798.248 | 0.0332678 | 1195.97ms | 3862 | 4890 | 11521.4 | 4613.97 | 0.0486945 | 6.35474 | 27.8995 | 3.44381 | 0.0153952 | 8.13866e-05 | 4.21495e-05 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 930.864 | 0.0574059 | 1125.75ms | 3862 | 160 | 825.44 | 3956.64 | 0.0328454 | 5.49086 | 25.2613 | 5.21103 | 0.00735208 | 4.20766e-05 | 3.23666e-06 | 1(Win) | true |
| glaze | 877.751 | 0.076075 | 1158.89ms | 3862 | 2560 | 26085.9 | 4196.06 | 0.157925 | 5.78223 | 28.8309 | 5.62843 | 0.00804493 | 0.000178522 | 0.000106102 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5335.9 | 0.0891828 | 823.795ms | 3862 | 2560 | 970.09 | 690.248 | 0.210193 | 1.00444 | 5.11704 | 0.579752 | 0.000262574 | 3.6109e-05 | 6.37218e-06 | 1(Win) | true |
| glaze | 2389.37 | 0.0721149 | 915.805ms | 3862 | 320 | 395.421 | 1541.45 | 0.0838603 | 2.15223 | 8.50388 | 0.951321 | 0.00403531 | 3.15575e-05 | 1.37558e-05 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1815.72 | 0.0469406 | 1244.88ms | 9578 | 2560 | 14275.4 | 5030.66 | 0.351218 | 2.79647 | 14.32 | 2.73418 | 0.00147139 | 6.23989e-05 | 3.24229e-05 | 1(Win) | true |
| simdjson (ondemand) | 1388.76 | 0.0372856 | 1400.42ms | 9578 | 4890 | 29409.5 | 6577.3 | 0.0276595 | 3.63781 | 17.7348 | 2.94696 | 0.00388369 | 2.35928e-05 | 4.33423e-06 | 2(Loss) | true |
| glaze | 1356.92 | 0.0453585 | 1414.05ms | 9578 | 2560 | 23867.1 | 6731.64 | 0.0318444 | 3.74414 | 17.5221 | 3.48695 | 0.00173167 | 8.93976e-05 | 4.89811e-05 | 3(Loss) | true |
| jsonifier (two-stage) | 1319.92 | 0.0237072 | 1433.14ms | 9578 | 4890 | 13162.1 | 6920.32 | 0.030537 | 3.85185 | 18.3567 | 3.14857 | 0.00219948 | 9.64634e-05 | 1.80842e-05 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2843.37 | 0.060808 | 1195.71ms | 9578 | 2560 | 9768.84 | 3212.48 | 0.0533117 | 1.79935 | 10.0675 | 1.79495 | 0.0010255 | 2.64685e-05 | 8.80925e-06 | 1(Win) | true |
| simdjson (ondemand) | 1937.82 | 0.098388 | 1351.49ms | 9578 | 30 | 645.252 | 4713.7 | 0.0183827 | 2.63372 | 13.572 | 2.03435 | 0.00265887 | 6.9604e-06 | 0 | 2(Loss) | true |
| glaze | 1885.92 | 0.049605 | 1372.31ms | 9578 | 1280 | 7388.68 | 4843.43 | 0.0703101 | 2.68571 | 13.1486 | 2.49624 | 0.000288177 | 1.98208e-05 | 6.1991e-06 | 3(Loss) | true |
| jsonifier (two-stage) | 1800.55 | 0.0376242 | 1382.73ms | 9578 | 2560 | 9326.36 | 5073.05 | 0.0364497 | 2.83021 | 14.1322 | 2.22113 | 0.000207792 | 5.64445e-05 | 9.50257e-06 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4442.71 | 0.0885112 | 945.278ms | 9578 | 1280 | 4238.97 | 2056.02 | 0.00896677 | 1.15661 | 5.03654 | 1.00428 | 0.00155899 | 4.95928e-05 | 3.13218e-05 | 1(Win) | true |
| glaze | 1972.03 | 0.0258858 | 1199.19ms | 9578 | 4890 | 7029.98 | 4631.92 | 0.0647195 | 2.58455 | 12.6561 | 2.59397 | 0.00112991 | 3.43323e-05 | 1.84899e-05 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11642.5 | 0.233323 | 837.005ms | 9578 | 30 | 100.53 | 784.567 | 0.0594455 | 0.454263 | 1.84381 | 0.215389 | 0.000810886 | 6.9604e-06 | 0 | 1(Win) | true |
| glaze | 5686.96 | 0.0393964 | 920.444ms | 9578 | 4890 | 1958 | 1606.18 | 0.0462615 | 0.913266 | 4.37941 | 0.710483 | 0.000301197 | 2.26533e-05 | 6.68283e-06 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3325.07 | 0.0567706 | 844.357ms | 3873 | 2560 | 1018.07 | 1110.83 | 0.0644643 | 1.57408 | 8.53085 | 1.03305 | 0.000680593 | 7.35259e-05 | 2.40043e-05 | 1(Win) | true |
| glaze | 1924.64 | 0.0686798 | 923.929ms | 3873 | 80 | 138.977 | 1919.1 | 0.0390656 | 2.68431 | 13.0669 | 1.62097 | 0.000258198 | 5.16396e-05 | 6.45494e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 1586.41 | 0.0885798 | 993.964ms | 3873 | 1280 | 5444.34 | 2328.27 | 0.103343 | 3.23839 | 14.5482 | 1.73638 | 0.00136986 | 9.3395e-05 | 3.97383e-05 | 3(Loss) | true |
| simdjson (ondemand) | 776.2 | 0.0236785 | 1212.21ms | 3873 | 320 | 406.261 | 4758.54 | 0.0420473 | 6.57068 | 27.7506 | 3.60444 | 0.0162745 | 4.2764e-05 | 7.26181e-06 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3710.31 | 0.100564 | 839.253ms | 3873 | 1280 | 1282.83 | 995.491 | 0.232286 | 1.41645 | 8.08727 | 0.938807 | 0.000258803 | 5.08327e-05 | 1.14979e-05 | 1(Win) | true |
| glaze | 2027.8 | 0.0696841 | 936.626ms | 3873 | 80 | 128.885 | 1821.47 | 0.0027451 | 2.54891 | 12.63 | 1.52672 | 0.000258198 | 3.87297e-05 | 3.22747e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 1683.61 | 0.0472845 | 952.595ms | 3873 | 320 | 344.35 | 2193.85 | 0.0702742 | 3.05938 | 14.1069 | 1.64214 | 0.00102392 | 2.74335e-05 | 1.61374e-06 | 3(Loss) | true |
| simdjson (ondemand) | 786.538 | 0.0222896 | 1207.17ms | 3873 | 4890 | 5357.58 | 4696 | 0.0743761 | 6.47666 | 27.3181 | 3.50788 | 0.0188247 | 7.84098e-05 | 2.98327e-05 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 929.541 | 0.0985302 | 1135.03ms | 3873 | 640 | 9810.17 | 3973.55 | 0.0337894 | 5.48964 | 24.8841 | 5.10405 | 0.00875048 | 4.9219e-05 | 1.16996e-05 | 1(Win) | true |
| glaze | 886.578 | 0.036931 | 1156.5ms | 3873 | 2560 | 6060.16 | 4166.11 | 0.0289435 | 5.75504 | 28.9233 | 5.66434 | 0.00608429 | 0.000102876 | 4.98241e-05 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5618.9 | 0.0546272 | 823.792ms | 3873 | 1280 | 165.052 | 657.349 | 0.00392185 | 0.958919 | 4.92228 | 0.557707 | 0.000258803 | 4.1352e-05 | 1.55322e-05 | 1(Win) | true |
| glaze | 2588.88 | 0.0753246 | 904.333ms | 3873 | 160 | 184.785 | 1426.71 | 0.0254016 | 2.00942 | 8.46424 | 0.946037 | 0.00394236 | 4.67983e-05 | 1.12962e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1750.14 | 0.0524473 | 5912.17ms | 94653 | 320 | 234164 | 51577.7 | 0.196694 | 2.88157 | 13.1534 | 2.46205 | 0.00936285 | 1.54842e-05 | 1.17535e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1511.58 | 0.0347868 | 6730.96ms | 94653 | 2560 | 1.10477e+06 | 59717.6 | 0.0908725 | 3.32457 | 14.7963 | 2.78359 | 0.0113597 | 5.21683e-05 | 4.34564e-05 | 2(Loss) | true |
| glaze | 1424.7 | 0.0258235 | 7147.35ms | 94653 | 2560 | 685317 | 63359.4 | 0.079394 | 3.54515 | 15.7317 | 3.11511 | 0.0156561 | 4.0613e-05 | 2.80465e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1204.75 | 0.0208546 | 8252.57ms | 94653 | 4890 | 1.19396e+06 | 74927 | 0.0372604 | 4.16474 | 16.434 | 3.11327 | 0.0119258 | 4.08164e-05 | 3.13966e-05 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2920.67 | 0.101517 | 5096.84ms | 94653 | 160 | 157506 | 30906.6 | 0.023261 | 1.71897 | 9.0484 | 1.54597 | 0.00536222 | 5.3749e-05 | 4.33821e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2410.19 | 0.0175969 | 5789.67ms | 94653 | 4890 | 212396 | 37452.6 | 0.104212 | 2.09031 | 10.7249 | 1.87596 | 0.00563693 | 2.94499e-05 | 2.06264e-05 | 2(Loss) | true |
| glaze | 2130.33 | 0.0236611 | 6328.37ms | 94653 | 2560 | 257327 | 42372.9 | 0.231114 | 2.37278 | 11.8475 | 2.2397 | 0.00875354 | 1.50096e-05 | 1.05773e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1697.03 | 0.0328664 | 7388.29ms | 94653 | 2560 | 782405 | 53191.7 | 0.0684392 | 2.95752 | 12.5013 | 2.22821 | 0.00741884 | 2.5038e-05 | 1.83895e-05 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16503.6 | 0.0357018 | 1301.89ms | 94653 | 160 | 610.116 | 5469.6 | 0.035893 | 0.30887 | 1.29357 | 0.184463 | 9.42258e-05 | 2.77329e-06 | 9.24429e-07 | 1(Win) | true |
| glaze | 5314.74 | 0.110187 | 2460.34ms | 94653 | 640 | 224153 | 16984.5 | 0.117396 | 0.942347 | 4.15165 | 0.667185 | 0.000108307 | 1.79768e-05 | 1.46588e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16334.8 | 0.0491091 | 1293.92ms | 94653 | 30 | 220.947 | 5526.13 | 0.00422254 | 0.306051 | 1.28778 | 0.183185 | 0.000118327 | 1.16214e-05 | 3.16947e-06 | 1(Win) | true |
| glaze | 5940.51 | 0.105861 | 2255.69ms | 94653 | 1280 | 331210 | 15195.4 | 0.161597 | 0.851478 | 4.10075 | 0.6555 | 2.63545e-05 | 2.60491e-05 | 2.05108e-05 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1883.21 | 0.018331 | 7080.66ms | 124597 | 4890 | 654183 | 63097.2 | 0.0224902 | 2.67307 | 11.6553 | 2.12861 | 0.00852024 | 6.12084e-05 | 5.13607e-05 | 1(Win) | true |
| jsonifier | 1736.11 | 0.022431 | 7625.51ms | 124597 | 4890 | 1.15258e+06 | 68443.4 | 0.0360026 | 2.8911 | 12.4921 | 2.45474 | 0.0112528 | 4.69653e-05 | 3.91873e-05 | 2(Loss) | true |
| glaze | 1644.69 | 0.0525641 | 7978.08ms | 124597 | 640 | 923012 | 72247.7 | 0.0267792 | 3.06048 | 13.8949 | 2.76437 | 0.014502 | 6.08963e-05 | 4.68385e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1558.02 | 0.137823 | 8394.7ms | 124597 | 640 | 7.07119e+06 | 76266.9 | 0.00554007 | 3.22306 | 12.8059 | 2.38133 | 0.00968198 | 8.77705e-05 | 5.44129e-05 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2817.79 | 0.173923 | 6253.91ms | 124597 | 80 | 430333 | 42169.6 | 0.047257 | 1.78533 | 8.56788 | 1.44277 | 0.00484071 | 4.76536e-05 | 4.033e-05 | 1(Win) | true |
| jsonifier | 2508.82 | 0.0601202 | 6737.78ms | 124597 | 640 | 518917 | 47362.9 | 0.0899256 | 2.01086 | 9.38116 | 1.76536 | 0.00751739 | 3.2116e-05 | 2.59587e-05 | 2(Loss) | true |
| glaze | 2213.12 | 0.144975 | 7473.74ms | 124597 | 160 | 969422 | 53691.1 | 0.0264988 | 2.2842 | 10.9423 | 2.10394 | 0.0123299 | 1.88608e-05 | 1.42459e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2157.27 | 0.0665486 | 7512.91ms | 124597 | 4890 | 6.57043e+06 | 55081.2 | 0.120368 | 2.3286 | 9.80223 | 1.7074 | 0.0056435 | 4.41489e-05 | 3.10711e-05 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19033.9 | 0.0739714 | 1434.43ms | 136037 | 30 | 762.621 | 6816 | 0.0161359 | 0.267476 | 0.981674 | 0.129163 | 0.000150694 | 3.43044e-06 | 9.80126e-07 | 1(Win) | true |
| glaze | 5282 | 0.175758 | 3236.34ms | 136076 | 640 | 1.19337e+06 | 24568.7 | 0.276187 | 0.946087 | 4.03303 | 0.703225 | 0.00153886 | 3.84436e-05 | 2.87523e-05 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19195 | 0.07122 | 1421.77ms | 136037 | 320 | 7414.65 | 6758.78 | 0.0443208 | 0.264536 | 0.977925 | 0.128325 | 4.86081e-05 | 1.29331e-05 | 9.39542e-06 | 1(Win) | true |
| glaze | 5806.05 | 0.0701479 | 2993.73ms | 136076 | 2560 | 629319 | 22351.2 | 0.183262 | 0.865 | 4.00047 | 0.695604 | 0.00144088 | 1.53637e-05 | 8.99658e-06 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1060.43 | 0.175745 | 6286.47ms | 2251027 | 40 | 5.06321e+08 | 2.02442e+06 | 0.00421296 | 4.73923 | 25.6704 | 5.02601 | 0.00767501 | 0.0644294 | 0.00032483 | 1(Win) | true |
| jsonifier (two-stage) | 994.536 | 0.0844416 | 6713.99ms | 2251027 | 80 | 2.6578e+08 | 2.15854e+06 | 0.160725 | 5.05126 | 27.9772 | 5.29031 | 0.0104125 | 0.102213 | 0.000366383 | 2(Loss) | true |
| glaze | 889.392 | 0.0839331 | 7528.51ms | 2251027 | 160 | 6.56691e+08 | 2.41372e+06 | 0.0740689 | 5.65291 | 30.2429 | 5.75328 | 0.0101277 | 0.0630989 | 0.000417329 | 3(Loss) | true |
| simdjson (ondemand) | 682.005 | 0.143787 | 9786.67ms | 2251027 | 40 | 8.19379e+08 | 3.1477e+06 | 0.145793 | 7.36129 | 31.4436 | 5.44637 | 0.0145339 | 0.108092 | 0.00109619 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1296.73 | 0.106322 | 6284.03ms | 2251027 | 160 | 4.95715e+08 | 1.65551e+06 | 0.260091 | 3.88161 | 20.7296 | 3.82814 | 0.00705052 | 0.0415442 | 0.000156026 | 1(Win) | true |
| jsonifier (two-stage) | 1200.07 | 0.0875816 | 6717.33ms | 2251027 | 80 | 1.96365e+08 | 1.78885e+06 | 0.166026 | 4.18419 | 23.0868 | 4.10787 | 0.00973243 | 0.0783532 | 0.000275519 | 2(Loss) | true |
| glaze | 1060.06 | 0.0581568 | 7499.43ms | 2251027 | 160 | 2.21932e+08 | 2.02511e+06 | 0.014463 | 4.75506 | 25.2606 | 4.54991 | 0.009125 | 0.0397355 | 0.000545923 | 3(Loss) | true |
| simdjson (ondemand) | 793.655 | 0.0910824 | 9594.57ms | 2251027 | 80 | 4.85576e+08 | 2.70489e+06 | 0.000933967 | 6.3552 | 26.4981 | 4.25303 | 0.0108088 | 0.0753822 | 0.00112396 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1601.45 | 0.0712362 | 7898.31ms | 2090234 | 320 | 2.516e+08 | 1.24474e+06 | 0.0260796 | 3.12532 | 7.87999 | 0.405685 | 0.000234998 | 0.0507204 | 0.000167315 | 1(Win) | true |
| glaze | 956.403 | 0.0685279 | 6490.02ms | 2090234 | 160 | 3.2641e+08 | 2.08427e+06 | 0.0229227 | 5.25074 | 9.34205 | 0.534072 | 0.000239282 | 0.0693039 | 0.00123405 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1602.51 | 0.135545 | 7897.68ms | 2090234 | 80 | 2.27427e+08 | 1.24392e+06 | 0.0309801 | 3.12692 | 7.87982 | 0.40565 | 0.000236026 | 0.0506572 | 0.000385561 | 1(Win) | true |
| glaze | 991.76 | 0.0974096 | 6258.28ms | 2090234 | 30 | 1.15001e+08 | 2.00997e+06 | 0.0117611 | 5.08225 | 9.33804 | 0.533131 | 0.00023294 | 0.0435568 | 0.000413478 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2128.05 | 0.22938 | 7501.82ms | 5373214 | 40 | 1.22033e+09 | 2.40798e+06 | 0.28817 | 2.33996 | 12.4888 | 2.25768 | 0.00470722 | 0.0622093 | 0.00160389 | 1(Win) | true |
| jsonifier | 2102.04 | 0.0595244 | 7590.78ms | 5373214 | 40 | 8.42242e+07 | 2.43777e+06 | 0.0239635 | 2.40161 | 13.0713 | 2.6611 | 0.00331993 | 0.0380169 | 0.00076083 | 2(Loss) | true |
| glaze | 1730.33 | 0.141113 | 9200.72ms | 5373214 | 80 | 1.39713e+09 | 2.96145e+06 | 0.0197168 | 2.90289 | 15.3761 | 2.93514 | 0.00496574 | 0.0404108 | 0.001328 | 3(Loss) | true |
| simdjson (ondemand) | 1555.49 | 0.0978888 | 10241.1ms | 5373214 | 80 | 8.31934e+08 | 3.29432e+06 | 0.0487605 | 3.24615 | 13.8748 | 2.31421 | 0.00623592 | 0.0645978 | 0.00182465 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2534.39 | 0.100545 | 7493.5ms | 5373214 | 160 | 6.6125e+08 | 2.02191e+06 | 0.582414 | 1.97631 | 10.4461 | 1.76362 | 0.00447188 | 0.0521543 | 0.00129941 | 1(Win) | true |
| jsonifier | 2469.44 | 0.133526 | 7652.63ms | 5373214 | 30 | 2.30316e+08 | 2.07508e+06 | 0.111287 | 2.03891 | 11.0278 | 2.16682 | 0.00306538 | 0.0279201 | 0.00111618 | 2(Loss) | true |
| glaze | 2001.49 | 0.0945649 | 9183.97ms | 5373214 | 80 | 4.68934e+08 | 2.56024e+06 | 0.00682208 | 2.52272 | 13.3192 | 2.43967 | 0.004324 | 0.0294624 | 0.000869777 | 3(Loss) | true |
| simdjson (ondemand) | 1781.73 | 0.0834561 | 10151.7ms | 5373214 | 160 | 9.21764e+08 | 2.87602e+06 | 0.13385 | 2.82455 | 11.8054 | 1.81484 | 0.00472237 | 0.0502972 | 0.00255722 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4681.83 | 0.107679 | 8624.42ms | 6661897 | 80 | 1.70811e+08 | 1.35701e+06 | 0.0393809 | 1.07009 | 2.5412 | 0.127288 | 7.43257e-05 | 0.0280165 | 0.00101318 | 1(Win) | true |
| glaze | 3218.04 | 0.259895 | 6214.05ms | 6661897 | 80 | 2.10619e+09 | 1.97427e+06 | 0.731796 | 1.55121 | 4.23032 | 0.46932 | 7.59056e-05 | 0.063511 | 0.00550163 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4719.91 | 0.0541685 | 8563.94ms | 6661897 | 160 | 8.50633e+07 | 1.34606e+06 | 0.113112 | 1.06778 | 2.54115 | 0.127277 | 7.40921e-05 | 0.0279805 | 0.000720869 | 1(Win) | true |
| glaze | 3881.31 | 0.101909 | 5104.52ms | 6661897 | 160 | 4.45226e+08 | 1.63689e+06 | 0.0153358 | 1.29413 | 4.22889 | 0.468987 | 7.44176e-05 | 0.0247664 | 0.00111939 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2386.35 | 0.0738638 | 5304.74ms | 500299 | 320 | 6.97916e+06 | 199938 | 0.014818 | 2.1129 | 9.11343 | 1.73023 | 0.0117547 | 0.010809 | 0.000110478 | 1(Win) | true |
| jsonifier (two-stage) | 1818.12 | 0.0651573 | 6914.25ms | 500299 | 160 | 4.67798e+06 | 262426 | 0.0347243 | 2.77483 | 12.4489 | 2.15219 | 0.0143244 | 0.0413786 | 0.000164227 | 2(Loss) | true |
| glaze | 1807.36 | 0.0437012 | 6946.24ms | 500299 | 640 | 8.51792e+06 | 263988 | 0.0633996 | 2.79276 | 12.4413 | 2.35121 | 0.0142881 | 0.00488561 | 9.13766e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1208.71 | 0.203151 | 5118.41ms | 500299 | 160 | 1.02891e+08 | 394738 | 0.0457585 | 4.17347 | 14.9556 | 2.42038 | 0.0172203 | 0.0394437 | 0.000257746 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2936.03 | 0.0570896 | 5116.83ms | 500299 | 640 | 5.50849e+06 | 162506 | 0.125722 | 1.71421 | 7.9585 | 1.45209 | 0.00899727 | 0.00417056 | 3.45418e-05 | 1(Win) | true |
| glaze STATISTICAL TIE | 2156.99 | 0.0326309 | 6747.37ms | 500299 | 1280 | 6.66853e+06 | 221198 | 0.0126935 | 2.34059 | 11.2947 | 2.07663 | 0.00963383 | 0.00158037 | 3.92203e-05 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 2156.62 | 0.0266672 | 6704.33ms | 500299 | 1280 | 4.45531e+06 | 221237 | 0.00247537 | 2.33877 | 11.2849 | 1.87292 | 0.0104888 | 0.0298001 | 9.6091e-05 | 2(Tie) | true |
| simdjson (ondemand) | 1400.7 | 0.0957404 | 9696.31ms | 500299 | 1280 | 1.36135e+08 | 340631 | 0.0774238 | 3.60324 | 13.7904 | 2.1361 | 0.00916921 | 0.0245383 | 9.84958e-05 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10277.7 | 0.0253392 | 5435.11ms | 500299 | 2560 | 354238 | 46423.2 | 0.16694 | 0.489794 | 2.16111 | 0.352701 | 0.00244307 | 0.00529808 | 1.15126e-05 | 1(Win) | true |
| glaze | 5625.35 | 0.0522612 | 9310.93ms | 500299 | 4890 | 9.6079e+06 | 84816.5 | 0.19445 | 0.895164 | 3.64363 | 0.515386 | 0.00131894 | 0.0205876 | 2.83597e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10340.3 | 0.0453748 | 5368.67ms | 500299 | 1280 | 561092 | 46142.1 | 0.00221119 | 0.48707 | 2.16005 | 0.352463 | 0.00245628 | 0.0049962 | 8.82441e-06 | 1(Win) | true |
| glaze | 6570.06 | 0.143662 | 8131.5ms | 500299 | 320 | 3.48303e+06 | 72620.7 | 0.0164193 | 0.765475 | 3.63048 | 0.512286 | 0.00122205 | 0.000647769 | 2.15496e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3589.37 | 0.0622971 | 8028.77ms | 1151920 | 1280 | 4.65322e+07 | 306058 | 0.262271 | 1.38198 | 6.21172 | 0.977391 | 0.00583204 | 0.053967 | 3.80567e-05 | 1(Win) | true |
| jsonifier | 3159.21 | 0.071232 | 9132.76ms | 1151920 | 80 | 4.90828e+06 | 347732 | 0.246677 | 1.59792 | 6.95942 | 1.45937 | 0.0047111 | 0.0185211 | 0.000297384 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 2539.76 | 0.191224 | 5590.8ms | 1151920 | 320 | 2.18924e+08 | 432543 | 0.271607 | 1.97333 | 7.19182 | 1.08383 | 0.00737261 | 0.0484646 | 7.76258e-05 | 3(Tie) | true |
| glaze STATISTICAL TIE | 2530.84 | 0.0284538 | 5627.21ms | 1151920 | 320 | 4.88142e+06 | 434068 | 0.304924 | 1.99562 | 8.48756 | 1.64664 | 0.00748968 | 0.0136127 | 5.7217e-05 | 3(Tie) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4175.72 | 0.126779 | 7799.1ms | 1151920 | 1280 | 1.42393e+08 | 263082 | 0.0738138 | 1.19473 | 5.70985 | 0.857041 | 0.0044455 | 0.0450379 | 1.80236e-05 | 1(Win) | true |
| jsonifier | 3563.08 | 0.123757 | 9009.67ms | 1151920 | 80 | 1.16472e+07 | 308317 | 0.363667 | 1.40998 | 6.4583 | 1.33881 | 0.0034196 | 0.0120113 | 4.24075e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2923.4 | 0.271411 | 5288.2ms | 1151920 | 160 | 1.66434e+08 | 375780 | 0.0455859 | 1.72226 | 6.68512 | 0.960144 | 0.00424918 | 0.0353503 | 1.28156e-05 | 3(Loss) | true |
| glaze | 2806.44 | 0.0325987 | 5542.6ms | 1151920 | 640 | 1.04211e+07 | 391441 | 0.0334621 | 1.79308 | 7.98443 | 1.52586 | 0.00547642 | 0.00869614 | 0.000108542 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17436.6 | 0.0137198 | 8717.11ms | 1439562 | 4890 | 570617 | 78735.3 | 0.0313181 | 0.285873 | 0.881549 | 0.127247 | 0.000585215 | 0.0185095 | 2.78899e-06 | 1(Win) | true |
| glaze | 5667.71 | 0.0575853 | 6398.63ms | 1439584 | 1280 | 2.49053e+07 | 242231 | 0.265303 | 0.877688 | 2.78626 | 0.504902 | 0.000939527 | 0.0623599 | 7.2585e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17534.3 | 0.0935474 | 8576.04ms | 1439562 | 30 | 160942 | 78296.6 | 0.0100057 | 0.282857 | 0.881325 | 0.1272 | 0.000572697 | 0.018421 | 9.6094e-06 | 1(Win) | true |
| glaze | 7827.3 | 0.0344399 | 9352.93ms | 1439584 | 2560 | 9.34145e+06 | 175398 | 0.0109293 | 0.639321 | 2.78084 | 0.503639 | 0.000941642 | 0.0186169 | 3.83132e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2237.88 | 0.101683 | 3161.72ms | 56369 | 30 | 17898.9 | 24021.7 | 0.14715 | 2.26456 | 9.32976 | 1.86279 | 0.00463257 | 6.09082e-05 | 4.55333e-05 | 1(Win) | true |
| glaze | 1924.99 | 0.0440041 | 3550.08ms | 56369 | 2560 | 386589 | 27926.2 | 0.25192 | 2.62778 | 11.6203 | 2.29955 | 0.00733811 | 5.38929e-05 | 2.98535e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1890.42 | 0.0362486 | 3610.45ms | 56369 | 1280 | 136005 | 28436.9 | 0.111831 | 2.6614 | 12.1506 | 2.21847 | 0.003311 | 6.08712e-05 | 4.37269e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1519.86 | 0.0285772 | 4305.22ms | 56369 | 2560 | 261550 | 35370.2 | 0.125404 | 3.31975 | 14.0732 | 2.35126 | 0.00553704 | 0.000132948 | 9.65873e-05 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3291.51 | 0.0331761 | 2752.51ms | 56369 | 2560 | 75159.3 | 16332.2 | 0.0126794 | 1.52731 | 7.16481 | 1.37949 | 0.00189096 | 3.02208e-05 | 2.13784e-05 | 1(Win) | true |
| glaze | 2955.69 | 0.0442208 | 2929.38ms | 56369 | 4890 | 316319 | 18187.8 | 0.0397995 | 1.71054 | 9.1311 | 1.74403 | 0.00229753 | 2.15314e-05 | 1.39165e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2484.58 | 0.142143 | 3310.11ms | 56369 | 80 | 75669.2 | 21636.5 | 0.0644002 | 2.03787 | 9.9689 | 1.73147 | 0.00361191 | 2.17318e-05 | 1.30834e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1934.63 | 0.0398517 | 3910.53ms | 56369 | 2560 | 313920 | 27787.1 | 0.16885 | 2.59688 | 11.6939 | 1.82652 | 0.00620083 | 5.93536e-05 | 4.37547e-05 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13812.2 | 0.160587 | 1139.14ms | 56369 | 320 | 12500.4 | 3892.04 | 0.159876 | 0.369318 | 1.45089 | 0.237702 | 0.000129726 | 9.97889e-06 | 5.54383e-06 | 1(Win) | true |
| glaze | 6029.5 | 0.102691 | 1653.95ms | 56369 | 2560 | 214597 | 8915.77 | 0.289738 | 0.833362 | 3.1091 | 0.487839 | 0.000149517 | 1.7276e-05 | 9.73635e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14035 | 0.200147 | 1128.26ms | 56369 | 30 | 1763.1 | 3830.27 | 0.469525 | 0.364605 | 1.4417 | 0.235626 | 0.000134235 | 2.72017e-05 | 2.18796e-05 | 1(Win) | true |
| glaze | 6206.29 | 0.283251 | 1619.07ms | 56369 | 640 | 385247 | 8661.8 | 0.0317385 | 0.813112 | 3.02993 | 0.469833 | 0.000121798 | 1.36655e-05 | 7.65048e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2592.88 | 0.0271099 | 3876.37ms | 83958 | 2560 | 179414 | 30880.2 | 0.0348074 | 1.94545 | 8.64978 | 1.50279 | 0.00321083 | 4.81128e-05 | 3.55833e-05 | 1(Win) | true |
| glaze | 2235.38 | 0.038838 | 4344.67ms | 83958 | 4890 | 946336 | 35818.8 | 0.0406858 | 2.24777 | 10.4781 | 2.13264 | 0.00518929 | 8.22351e-05 | 5.67208e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2182.54 | 0.047425 | 4419.95ms | 83958 | 1280 | 387459 | 36686 | 0.162156 | 2.30141 | 9.89258 | 1.60181 | 0.00359793 | 2.80925e-05 | 1.57445e-05 | 3(Loss) | true |
| jsonifier | 1906.88 | 0.077474 | 4959.29ms | 83958 | 640 | 677282 | 41989.3 | 0.0169901 | 2.64915 | 9.48299 | 2.03976 | 0.0055549 | 0.000120391 | 8.96468e-05 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3446.97 | 0.0451853 | 3436.51ms | 83958 | 1280 | 141011 | 23228.7 | 0.148744 | 1.45391 | 7.19221 | 1.17751 | 0.00143659 | 1.67494e-05 | 1.13059e-05 | 1(Win) | true |
| glaze | 3032.31 | 0.0569023 | 3753.57ms | 83958 | 2560 | 577933 | 26405.2 | 0.153457 | 1.66057 | 8.81996 | 1.76211 | 0.00289416 | 3.2801e-05 | 2.27932e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2732.9 | 0.0782936 | 3920.43ms | 83958 | 640 | 336752 | 29298.1 | 0.114563 | 1.82556 | 8.28243 | 1.24765 | 0.00409057 | 3.27359e-05 | 2.4175e-05 | 3(Loss) | true |
| jsonifier | 2304.75 | 0.0498334 | 4598.85ms | 83958 | 640 | 191822 | 34740.7 | 0.433571 | 2.17951 | 8.01908 | 1.71281 | 0.00467592 | 1.42743e-05 | 9.7519e-06 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17571.1 | 0.0467029 | 1260.96ms | 94370 | 2560 | 14648.7 | 5121.95 | 0.179705 | 0.286322 | 0.964788 | 0.148872 | 0.000115031 | 1.30346e-05 | 8.29514e-06 | 1(Win) | true |
| glaze | 5099.84 | 0.0467226 | 2512.92ms | 94370 | 2560 | 174040 | 17647.3 | 0.0720044 | 0.984965 | 3.42092 | 0.637141 | 0.00134663 | 1.75796e-05 | 1.02986e-05 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17981.4 | 0.040108 | 1248.22ms | 94370 | 4890 | 19705.7 | 5005.07 | 0.00377376 | 0.280385 | 0.959415 | 0.147664 | 8.2116e-05 | 1.55373e-05 | 1.03127e-05 | 1(Win) | true |
| glaze | 5795.78 | 0.0756445 | 2307.48ms | 94370 | 640 | 88303.7 | 15528.2 | 0.10135 | 0.870695 | 3.36923 | 0.625209 | 0.00134984 | 7.74875e-06 | 4.66912e-06 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1866.6 | 0.0400749 | 3498.83ms | 53331 | 1280 | 152621 | 27247.7 | 0.0526985 | 2.70424 | 10.5109 | 1.86292 | 0.000830061 | 0.000161008 | 0.000115405 | 1(Win) | true |
| simdjson (ondemand) | 1833.36 | 0.0385892 | 3596.06ms | 53331 | 1280 | 146692 | 27741.7 | 0.0516949 | 2.75377 | 10.0279 | 1.68767 | 0.00109546 | 8.44959e-05 | 5.36449e-05 | 2(Loss) | true |
| jsonifier | 1659.51 | 0.114585 | 3808.22ms | 53331 | 640 | 789293 | 30647.8 | 0.0176889 | 3.03801 | 9.80291 | 1.7706 | 0.0127238 | 0.000345337 | 0.000273 | 3(Loss) | true |
| glaze | 1388.23 | 0.102776 | 4378.82ms | 53331 | 640 | 907395 | 36636.9 | 0.0604344 | 3.59372 | 11.6759 | 2.24038 | 0.0223215 | 0.000427489 | 0.000326352 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2309.46 | 0.0408578 | 3547.66ms | 53331 | 4890 | 395913 | 22022.7 | 0.0714505 | 2.18868 | 7.53622 | 1.26058 | 0.00937068 | 0.000158941 | 0.000133982 | 1(Win) | true |
| jsonifier (two-stage) | 2132.78 | 0.248892 | 3432.29ms | 53331 | 160 | 563650 | 23847 | 0.049664 | 2.3725 | 8.29499 | 1.36575 | 0.00902512 | 9.50432e-05 | 7.52377e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2058.74 | 0.0313901 | 3775.72ms | 53331 | 4890 | 294072 | 24704.7 | 0.0406757 | 2.45194 | 8.06068 | 1.24973 | 0.00900622 | 7.28981e-05 | 5.3112e-05 | 3(Loss) | true |
| glaze | 1860.9 | 0.0810928 | 4111.63ms | 53331 | 1280 | 628767 | 27331.1 | 0.000145782 | 2.69702 | 9.39609 | 1.72863 | 0.0176401 | 9.664e-05 | 7.36556e-05 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16838.2 | 0.0428757 | 1083.37ms | 58581 | 160 | 323.791 | 3317.88 | 0.0476357 | 0.305566 | 1.04892 | 0.161503 | 0.000117786 | 1.57901e-05 | 8.4285e-06 | 1(Win) | true |
| glaze | 6111.54 | 0.11895 | 1658.99ms | 58581 | 4890 | 578159 | 9141.26 | 0.366785 | 0.821899 | 2.4695 | 0.382633 | 5.52396e-05 | 4.90293e-05 | 3.12119e-05 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16921.2 | 0.0693675 | 1080.88ms | 58581 | 320 | 1678.47 | 3301.61 | 0.0546434 | 0.301318 | 1.03957 | 0.15942 | 8.17778e-05 | 1.41364e-05 | 9.81547e-06 | 1(Win) | true |
| glaze | 7510.71 | 0.130286 | 1491.13ms | 58581 | 4890 | 459254 | 7438.33 | 0.174079 | 0.67159 | 2.39745 | 0.365989 | 3.80226e-05 | 2.6192e-05 | 1.55344e-05 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1932.76 | 0.0444366 | 3997.76ms | 65103 | 2560 | 521639 | 32123.6 | 0.0639769 | 2.6171 | 8.45916 | 1.39157 | 0.00812233 | 0.000109148 | 7.66814e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1912.2 | 0.0939854 | 4008.75ms | 65103 | 4890 | 4.55371e+06 | 32468.9 | 0.144971 | 2.64238 | 8.99623 | 1.53852 | 0.00835651 | 0.000197717 | 0.000137944 | 2(Loss) | true |
| jsonifier | 1634.1 | 0.071039 | 4574.51ms | 65103 | 1280 | 932503 | 37994.7 | 0.163759 | 3.07762 | 9.44615 | 1.79005 | 0.00899192 | 0.000175119 | 0.000109202 | 3(Loss) | true |
| glaze | 1579.91 | 0.0490874 | 4696.22ms | 65103 | 4890 | 1.81964e+06 | 39297.8 | 0.084353 | 3.1949 | 10.812 | 2.09053 | 0.0191927 | 0.000109385 | 7.1587e-05 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2527.12 | 0.0712162 | 3783.72ms | 65103 | 2560 | 783698 | 24568.3 | 0.0135339 | 2.00172 | 7.18508 | 1.13303 | 0.00606178 | 5.15049e-05 | 3.66247e-05 | 1(Win) | true |
| simdjson (ondemand) | 2447.16 | 0.0731804 | 3831.77ms | 65103 | 640 | 220622 | 25371.1 | 0.120329 | 2.05277 | 6.84296 | 1.03272 | 0.00742105 | 3.37446e-05 | 2.39524e-05 | 2(Loss) | true |
| jsonifier | 2094.66 | 0.0459466 | 4301.43ms | 65103 | 2560 | 474813 | 29640.7 | 0.0891237 | 2.4151 | 7.59411 | 1.37447 | 0.00669638 | 6.17831e-05 | 4.23548e-05 | 3(Loss) | true |
| glaze | 2034.92 | 0.0627966 | 4467.91ms | 65103 | 2560 | 939763 | 30510.7 | 0.0471461 | 2.47678 | 8.94392 | 1.67193 | 0.0151708 | 4.58288e-05 | 3.15006e-05 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19436.2 | 0.0447692 | 1135.77ms | 78778 | 4890 | 14643.8 | 3865.39 | 0.386067 | 0.259134 | 0.859009 | 0.124019 | 3.39101e-05 | 3.38167e-05 | 2.21507e-05 | 1(Win) | true |
| glaze | 5050.77 | 0.132832 | 2243.82ms | 78778 | 2560 | 999399 | 14874.7 | 0.0814204 | 0.996462 | 2.74162 | 0.47394 | 0.000316519 | 2.40192e-05 | 1.51682e-05 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20134.8 | 0.0864973 | 1129.65ms | 78778 | 80 | 833.321 | 3731.29 | 0.0935538 | 0.254128 | 0.852053 | 0.122483 | 4.61741e-05 | 1.04725e-05 | 6.18828e-06 | 1(Win) | true |
| glaze | 5613.07 | 0.102098 | 2091.63ms | 78778 | 4890 | 913166 | 13384.6 | 0.139418 | 0.890773 | 2.68132 | 0.459964 | 0.000312659 | 2.5001e-05 | 1.59206e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2680.53 | 0.0343169 | 1181.71ms | 11812 | 4890 | 10170.2 | 4202.45 | 0.0573401 | 1.89512 | 9.35485 | 1.63651 | 0.00286255 | 4.69177e-05 | 2.50516e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1991.39 | 0.069224 | 1308.72ms | 11812 | 80 | 1226.7 | 5656.75 | 0.047311 | 2.55803 | 12.6921 | 2.17453 | 0.00396631 | 4.02133e-05 | 2.43397e-05 | 2(Loss) | true |
| glaze | 1786.67 | 0.0413283 | 1368.03ms | 11812 | 2560 | 17381.8 | 6304.92 | 0.247853 | 2.83109 | 13.6551 | 2.68312 | 0.00244455 | 5.28131e-05 | 2.81097e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1303.08 | 0.0940592 | 1608.08ms | 11812 | 640 | 42314.3 | 8644.75 | 0.0957602 | 3.87928 | 16.5587 | 2.91406 | 0.00343639 | 5.80712e-05 | 3.29379e-05 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3098.85 | 0.032324 | 1153.01ms | 11812 | 4890 | 6751.59 | 3635.16 | 0.0271395 | 1.64629 | 8.45031 | 1.42448 | 0.00194613 | 2.58827e-05 | 1.1842e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2209.78 | 0.0495184 | 1306.21ms | 11812 | 160 | 1019.53 | 5097.7 | 0.18966 | 2.30749 | 11.7873 | 1.96241 | 0.00328374 | 2.96309e-05 | 1.05825e-05 | 2(Loss) | true |
| glaze | 2031.45 | 0.0458242 | 1344.32ms | 11812 | 2560 | 16529.6 | 5545.19 | 0.173876 | 2.49883 | 12.5028 | 2.42584 | 0.00113546 | 2.62577e-05 | 1.16407e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1422.69 | 0.12069 | 1589.73ms | 11812 | 30 | 2739.58 | 7917.93 | 0.0197824 | 3.57665 | 15.671 | 2.718 | 0.00228017 | 5.36178e-05 | 4.23298e-05 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11348.5 | 0.142126 | 835.128ms | 11812 | 80 | 159.225 | 992.625 | 0.0327522 | 0.464092 | 2.01304 | 0.340332 | 0.000170378 | 2.43397e-05 | 1.2699e-05 | 1(Win) | true |
| glaze | 3972.68 | 0.0913511 | 1025.97ms | 11812 | 4890 | 32810.8 | 2835.57 | 0.375135 | 1.28196 | 5.23349 | 0.807146 | 0.000407907 | 4.51864e-05 | 2.31819e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12338.1 | 0.0518068 | 825.38ms | 11812 | 640 | 143.186 | 913.006 | 0.358442 | 0.428417 | 1.96614 | 0.329665 | 8.47919e-05 | 1.58737e-05 | 3.83614e-06 | 1(Win) | true |
| glaze | 4470.77 | 0.163276 | 987.439ms | 11812 | 4890 | 82762.6 | 2519.66 | 0.205117 | 1.1465 | 4.9647 | 0.74763 | 0.000430535 | 4.19836e-05 | 2.29914e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3743.89 | 0.0380023 | 1389.45ms | 25388 | 1280 | 7731.11 | 6467.04 | 0.0316529 | 1.3585 | 6.76532 | 1.07303 | 0.00179615 | 2.15407e-05 | 1.18166e-05 | 1(Win) | true |
| jsonifier | 3182.73 | 0.0289575 | 1501.66ms | 25388 | 4890 | 23729.6 | 7607.28 | 0.0197931 | 1.59508 | 7.36348 | 1.48881 | 0.00422443 | 2.34238e-05 | 1.29282e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2603.56 | 0.143347 | 1671.54ms | 25388 | 160 | 28432.7 | 9299.53 | 0.0399726 | 1.94786 | 8.35676 | 1.38759 | 0.00188549 | 5.24362e-05 | 3.91425e-05 | 3(Loss) | true |
| glaze | 2420.96 | 0.0281565 | 1743.65ms | 25388 | 2560 | 20299.3 | 10001 | 0.00648417 | 2.09515 | 9.38695 | 1.87266 | 0.00481299 | 2.23254e-05 | 1.18628e-05 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4052.11 | 0.119858 | 1390.68ms | 25388 | 320 | 16412.5 | 5975.13 | 0.00972877 | 1.25522 | 6.37211 | 0.980582 | 0.00171698 | 1.34168e-05 | 5.04668e-06 | 1(Win) | true |
| jsonifier | 3373.26 | 0.0805916 | 1508.13ms | 25388 | 640 | 21414.9 | 7177.59 | 0.0181739 | 1.50689 | 6.97042 | 1.39649 | 0.00426844 | 1.32937e-05 | 5.10822e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2822.81 | 0.10147 | 1652.84ms | 25388 | 320 | 24239.1 | 8577.22 | 0.0084169 | 1.79238 | 7.92469 | 1.29258 | 0.00121465 | 2.56026e-05 | 1.42784e-05 | 3(Loss) | true |
| glaze | 2589.73 | 0.0264853 | 1729.06ms | 25388 | 4890 | 29982.3 | 9349.18 | 0.0387551 | 1.96231 | 8.88148 | 1.76001 | 0.00481343 | 1.78337e-05 | 8.98127e-06 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18685.3 | 0.0977145 | 897.83ms | 31235 | 160 | 388.258 | 1594.19 | 0.0975247 | 0.277707 | 0.918201 | 0.128638 | 3.22155e-05 | 6.80327e-06 | 2.40115e-06 | 1(Win) | true |
| glaze | 5195.99 | 0.042972 | 1316.75ms | 31235 | 4890 | 29677.5 | 5732.88 | 0.0275571 | 0.976832 | 3.63685 | 0.652761 | 0.00221495 | 1.81159e-05 | 9.25761e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19441.3 | 0.0837269 | 890.007ms | 31235 | 160 | 263.318 | 1532.2 | 0.111892 | 0.267009 | 0.90024 | 0.124476 | 3.22155e-05 | 5.0024e-06 | 2.80134e-06 | 1(Win) | true |
| glaze | 5653.82 | 0.0610108 | 1267.49ms | 31235 | 4890 | 50526.7 | 5268.65 | 0.0114442 | 0.898638 | 3.51404 | 0.625004 | 0.0022373 | 2.51016e-05 | 1.39322e-05 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2387.15 | 0.0495198 | 5075.13ms | 108313 | 320 | 146930 | 43271.4 | 0.0105956 | 2.11518 | 8.4173 | 1.67899 | 0.0030647 | 5.59432e-05 | 3.97286e-05 | 1(Win) | true |
| glaze | 2152.79 | 0.0493713 | 5573.84ms | 108313 | 640 | 359160 | 47982.1 | 0.307542 | 2.34772 | 10.0548 | 1.80826 | 0.00254107 | 2.65434e-05 | 1.96479e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1968.92 | 0.0768598 | 6038.76ms | 108313 | 160 | 260149 | 52462.9 | 0.0295836 | 2.57222 | 11.4683 | 2.01178 | 0.00324621 | 4.86437e-05 | 3.42757e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1751 | 0.024331 | 6663.85ms | 108313 | 1280 | 263703 | 58992.1 | 0.0456042 | 2.88402 | 14.1303 | 2.02725 | 0.00270074 | 3.09649e-05 | 2.00807e-05 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2794.09 | 0.0338341 | 4630.68ms | 108313 | 1280 | 200263 | 36969.2 | 0.00635413 | 1.80662 | 7.61619 | 1.4966 | 0.00262579 | 1.54933e-05 | 1.07256e-05 | 1(Win) | true |
| glaze | 2415.94 | 0.129191 | 5225.24ms | 108313 | 160 | 488173 | 42755.8 | 0.0185536 | 2.0935 | 9.32253 | 1.64207 | 0.00206289 | 3.74493e-05 | 2.64857e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2243.34 | 0.0257376 | 5553.63ms | 108313 | 640 | 89884.8 | 46045.2 | 0.0020293 | 2.25443 | 10.6665 | 1.82933 | 0.00267279 | 3.77667e-05 | 3.13184e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1918.6 | 0.0518654 | 6362.25ms | 108313 | 320 | 249517 | 53839 | 0.0366505 | 2.63374 | 13.4325 | 1.87142 | 0.00256254 | 5.13558e-05 | 4.01902e-05 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18730.8 | 0.158709 | 1299.34ms | 108313 | 160 | 12256.7 | 5514.74 | 0.0337617 | 0.271664 | 1.2252 | 0.318881 | 0.000207789 | 3.693e-06 | 1.09636e-06 | 1(Win) | true |
| glaze | 5379.5 | 0.0791522 | 2670.87ms | 108313 | 4890 | 1.12957e+06 | 19201.7 | 0.0133928 | 0.94073 | 2.73668 | 0.384497 | 0.000284516 | 1.14377e-05 | 7.31237e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18708.7 | 0.0761605 | 1301.71ms | 108313 | 30 | 530.461 | 5521.23 | 0.0199271 | 0.272273 | 1.22052 | 0.317829 | 0.000207424 | 5.23175e-06 | 4.3085e-06 | 1(Win) | true |
| glaze | 6196.65 | 0.129708 | 2413.23ms | 108313 | 4890 | 2.28608e+06 | 16669.5 | 0.490528 | 0.816635 | 2.69244 | 0.374221 | 0.000284303 | 5.62824e-06 | 3.33994e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2956.67 | 0.0437216 | 6684.25ms | 183677 | 160 | 107353 | 59245 | 0.151039 | 1.71003 | 7.53245 | 1.24494 | 0.00185199 | 1.89871e-05 | 1.46657e-05 | 1(Win) | true |
| simdjson (ondemand) | 2801.5 | 0.0328797 | 7045.51ms | 183677 | 640 | 270497 | 62526.4 | 0.0491475 | 1.80363 | 8.86999 | 1.21936 | 0.00167102 | 3.66302e-05 | 2.79533e-05 | 2(Loss) | true |
| glaze | 2686.06 | 0.0193347 | 7317.25ms | 183677 | 2560 | 406997 | 65213.7 | 0.0168007 | 1.87977 | 8.90342 | 1.65719 | 0.00315732 | 2.63412e-05 | 1.9404e-05 | 3(Loss) | true |
| jsonifier | 2349.73 | 0.0431961 | 8273.53ms | 183677 | 320 | 331829 | 74548.3 | 0.038023 | 2.15359 | 7.88614 | 1.73778 | 0.00242408 | 4.5154e-05 | 3.32615e-05 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3324.46 | 0.0368569 | 6213.32ms | 183677 | 320 | 120685 | 52690.6 | 0.00437716 | 1.52078 | 7.06062 | 1.13756 | 0.00166951 | 9.18732e-06 | 6.85647e-06 | 1(Win) | true |
| simdjson (ondemand) | 3086.36 | 0.0163084 | 6613.68ms | 183677 | 4890 | 418934 | 56755.5 | 0.117611 | 1.63201 | 8.46144 | 1.12831 | 0.00139455 | 1.50627e-05 | 1.1727e-05 | 2(Loss) | true |
| glaze | 2930.62 | 0.0231078 | 6911.69ms | 183677 | 2560 | 488372 | 59771.7 | 0.0135606 | 1.71882 | 8.47309 | 1.55974 | 0.00293019 | 2.11351e-05 | 1.69625e-05 | 3(Loss) | true |
| jsonifier | 2557.29 | 0.0161169 | 7814.85ms | 183677 | 2560 | 311999 | 68497.6 | 0.0902518 | 1.97612 | 7.41166 | 1.62972 | 0.00216537 | 3.01395e-05 | 2.20772e-05 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 23061.2 | 0.0265553 | 1627.29ms | 213963 | 2560 | 14133.7 | 8848.24 | 0.00169522 | 0.220367 | 0.735866 | 0.166183 | 8.28633e-05 | 8.52404e-06 | 6.29307e-06 | 1(Win) | true |
| glaze | 5609.13 | 0.0875511 | 4388.45ms | 213963 | 1280 | 1.29843e+06 | 36378.3 | 0.175517 | 0.893243 | 3.0401 | 0.570884 | 0.000657127 | 8.02198e-06 | 5.6121e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 23211.2 | 0.0283881 | 1638.85ms | 213963 | 2560 | 15943.9 | 8791.06 | 0.1122 | 0.219082 | 0.733547 | 0.16566 | 8.39934e-05 | 1.19636e-05 | 9.32915e-06 | 1(Win) | true |
| glaze | 6651.85 | 0.0259471 | 3818.12ms | 213963 | 4890 | 309799 | 30675.8 | 0.071791 | 0.759917 | 3.01408 | 0.564888 | 0.00066197 | 7.34794e-06 | 4.32198e-06 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 840.168 | 0.0399953 | 6506.39ms | 1834197 | 160 | 1.10942e+08 | 2.082e+06 | 0.175278 | 6.01179 | 26.4339 | 5.73797 | 0.0308012 | 0.0812994 | 0.000557478 | 1(Win) | true |
| jsonifier (two-stage) | 758.478 | 0.185059 | 7194.79ms | 1834197 | 30 | 5.46446e+08 | 2.30623e+06 | 0.0693212 | 6.61736 | 30.5179 | 6.3156 | 0.0364791 | 0.144697 | 0.000274616 | 2(Loss) | true |
| glaze | 710.107 | 0.0734686 | 7667.08ms | 1834197 | 160 | 5.24045e+08 | 2.46333e+06 | 0.212889 | 7.0998 | 30.8935 | 6.44983 | 0.0352552 | 0.0826073 | 0.00301332 | 3(Loss) | true |
| simdjson (ondemand) | 595.623 | 0.172407 | 9182.04ms | 1834197 | 160 | 4.10184e+09 | 2.9368e+06 | 0.146511 | 8.45017 | 35.7163 | 6.22282 | 0.046386 | 0.146123 | 0.0040296 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 931.095 | 0.0437017 | 6525.18ms | 1834197 | 80 | 5.3925e+07 | 1.87868e+06 | 0.0877427 | 5.42283 | 23.428 | 5.03212 | 0.0299679 | 0.0550065 | 0.000123433 | 1(Win) | true |
| jsonifier (two-stage) | 833.726 | 0.0822043 | 7202.44ms | 1834197 | 30 | 8.92393e+07 | 2.09808e+06 | 0.089514 | 6.04869 | 27.5115 | 5.6101 | 0.0355135 | 0.1185 | 0.000635919 | 2(Loss) | true |
| glaze | 786.54 | 0.0793648 | 7679.38ms | 1834197 | 80 | 2.49228e+08 | 2.22395e+06 | 0.167718 | 6.39878 | 27.8804 | 5.7435 | 0.0337886 | 0.0591659 | 0.000649037 | 3(Loss) | true |
| simdjson (ondemand) | 653.536 | 0.0658601 | 8998.9ms | 1834197 | 80 | 2.48592e+08 | 2.67656e+06 | 0.150613 | 7.71221 | 32.6877 | 5.51549 | 0.041716 | 0.118761 | 0.0020337 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 852.805 | 0.0700568 | 6388.96ms | 1834197 | 160 | 3.3038e+08 | 2.05114e+06 | 0.238659 | 5.88186 | 12.5177 | 0.907936 | 0.00149274 | 0.0588874 | 0.000416432 | 1(Win) | true |
| glaze | 613.993 | 0.286207 | 8912.92ms | 1833577 | 30 | 1.99321e+09 | 2.84797e+06 | 0.0352656 | 8.20591 | 15.5348 | 0.9499 | 0.0010177 | 0.0490063 | 0.000345427 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 853.748 | 0.0618634 | 6383.14ms | 1834197 | 160 | 2.57052e+08 | 2.04888e+06 | 0.00861128 | 5.8829 | 12.5175 | 0.907899 | 0.00153671 | 0.0588427 | 0.00139973 | 1(Win) | true |
| glaze | 609.294 | 0.172537 | 8920.63ms | 1833577 | 30 | 7.35581e+08 | 2.86994e+06 | 0.0646576 | 8.2771 | 15.534 | 0.94973 | 0.00101016 | 0.0489114 | 0.000298215 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2586.68 | 0.149121 | 8444.99ms | 7351818 | 80 | 1.30699e+09 | 2.71052e+06 | 0.0401293 | 1.92198 | 8.54687 | 1.61666 | 0.00937035 | 0.0606155 | 0.00181761 | 1(Win) | true |
| jsonifier | 2553.1 | 0.155252 | 8579.98ms | 7351818 | 40 | 7.27088e+08 | 2.74616e+06 | 0.389252 | 1.96173 | 9.24793 | 2.08372 | 0.00693074 | 0.0335953 | 0.00110799 | 2(Loss) | true |
| glaze | 2187.67 | 0.0974356 | 10019.3ms | 7351818 | 40 | 3.90051e+08 | 3.20489e+06 | 0.347346 | 2.3032 | 10.7422 | 2.22434 | 0.00908672 | 0.0331946 | 0.00114353 | 3(Loss) | true |
| simdjson (ondemand) | 2165.63 | 0.0706703 | 10071.2ms | 7351818 | 160 | 8.37557e+08 | 3.2375e+06 | 0.335553 | 2.31322 | 9.8461 | 1.59187 | 0.0111311 | 0.0607131 | 0.00188915 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 2797.34 | 0.226237 | 8420.62ms | 7351818 | 40 | 1.28614e+09 | 2.5064e+06 | 0.49865 | 1.78348 | 7.79672 | 1.44035 | 0.00926025 | 0.0540214 | 0.00226413 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 2793.02 | 0.141395 | 8505.01ms | 7351818 | 40 | 5.03929e+08 | 2.51027e+06 | 0.323677 | 1.80132 | 8.498 | 1.90761 | 0.00676473 | 0.0269838 | 0.000994533 | 1(Tie) | true |
| simdjson (ondemand) | 2375.3 | 0.0533251 | 9896.55ms | 7351818 | 160 | 3.96402e+08 | 2.95173e+06 | 0.211828 | 2.11794 | 9.09103 | 1.4155 | 0.00998498 | 0.053498 | 0.00139772 | 3(Loss) | true |
| glaze | 2358.58 | 0.13453 | 9960.17ms | 7351818 | 30 | 4.79789e+08 | 2.97266e+06 | 0.176922 | 2.13872 | 9.99033 | 2.04822 | 0.00870144 | 0.027293 | 0.00311075 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5757.5 | 0.144822 | 5126.22ms | 9930848 | 40 | 2.27004e+08 | 1.64495e+06 | 0.311775 | 0.868926 | 2.45966 | 0.16772 | 0.000252345 | 0.0248255 | 0.000153844 | 1(Win) | true |
| glaze | 3660.91 | 0.193988 | 8045.21ms | 9930228 | 40 | 1.00728e+09 | 2.58684e+06 | 0.318675 | 1.37309 | 4.13202 | 0.480828 | 0.00106075 | 0.0415927 | 0.00350963 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5778.07 | 0.0782751 | 5127.06ms | 9930848 | 80 | 1.31687e+08 | 1.63909e+06 | 0.0194918 | 0.870303 | 2.45962 | 0.167713 | 0.000274775 | 0.0248006 | 0.000158938 | 1(Win) | true |
| glaze | 4027.78 | 0.139992 | 7298.98ms | 9930228 | 80 | 8.66732e+08 | 2.35122e+06 | 0.0159645 | 1.25347 | 4.13176 | 0.480769 | 0.00105969 | 0.0222898 | 0.00154665 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 845.302 | 0.0736867 | 6432.9ms | 1834197 | 160 | 3.72019e+08 | 2.06935e+06 | 0.173766 | 5.92691 | 25.9963 | 5.60782 | 0.0316075 | 0.0823799 | 5.21039e-05 | 1(Win) | true |
| jsonifier (two-stage) | 762.536 | 0.114779 | 7141.44ms | 1834197 | 80 | 5.54613e+08 | 2.29396e+06 | 0.0122121 | 6.54 | 30.0959 | 6.19031 | 0.0368002 | 0.145598 | 0.000862046 | 2(Loss) | true |
| glaze | 704.213 | 0.128207 | 7715.55ms | 1834197 | 40 | 4.05664e+08 | 2.48395e+06 | 0.0689803 | 7.15067 | 30.8677 | 6.4405 | 0.0354569 | 0.082195 | 0.000165454 | 3(Loss) | true |
| simdjson (ondemand) | 583.791 | 0.0647191 | 9318.92ms | 1834197 | 160 | 6.01676e+08 | 2.99632e+06 | 0.0924024 | 8.50074 | 35.6643 | 6.21233 | 0.0466621 | 0.146691 | 0.00441399 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 948.254 | 0.106182 | 6453.12ms | 1834197 | 80 | 3.0693e+08 | 1.84468e+06 | 0.176479 | 5.27274 | 23.0144 | 4.91233 | 0.0307549 | 0.0562852 | 1.52383e-05 | 1(Win) | true |
| jsonifier (two-stage) | 846.983 | 0.12572 | 7153.1ms | 1834197 | 40 | 2.69656e+08 | 2.06524e+06 | 0.0192495 | 5.8819 | 27.1154 | 5.49523 | 0.0359487 | 0.119398 | 0.00108294 | 2(Loss) | true |
| glaze | 781.804 | 0.0698857 | 7705.33ms | 1834197 | 80 | 1.95598e+08 | 2.23742e+06 | 0.0273744 | 6.45786 | 27.8841 | 5.74406 | 0.0342933 | 0.0588732 | 0.000141622 | 3(Loss) | true |
| simdjson (ondemand) | 646.498 | 0.0773741 | 9157.11ms | 1834197 | 80 | 3.50621e+08 | 2.70569e+06 | 0.0968452 | 7.73087 | 32.6664 | 5.51447 | 0.0418154 | 0.118395 | 0.00633297 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 856.292 | 0.0978291 | 6343ms | 1834197 | 80 | 3.19502e+08 | 2.04279e+06 | 0.0612178 | 5.78664 | 12.5179 | 0.907973 | 0.00131796 | 0.060232 | 0.000138105 | 1(Win) | true |
| glaze | 584.611 | 0.126127 | 9293.13ms | 1833577 | 30 | 4.26973e+08 | 2.99111e+06 | 0.0143189 | 8.4951 | 15.5344 | 0.950105 | 0.0010499 | 0.0810398 | 0.00942335 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 862.406 | 0.0843587 | 6330.54ms | 1834197 | 160 | 4.68434e+08 | 2.02831e+06 | 0.011369 | 5.79119 | 12.5177 | 0.907936 | 0.00133866 | 0.0603341 | 0.00090282 | 1(Win) | true |
| glaze | 618.39 | 0.334178 | 8823.18ms | 1833577 | 40 | 3.57182e+09 | 2.82772e+06 | 0.113724 | 8.14219 | 15.5335 | 0.949903 | 0.000988069 | 0.0488054 | 0.000810533 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2614.75 | 0.107641 | 8387.67ms | 7351818 | 160 | 1.33292e+09 | 2.68142e+06 | 0.147462 | 1.9074 | 8.4409 | 1.585 | 0.00951366 | 0.0609705 | 0.00210219 | 1(Win) | true |
| jsonifier | 2557.69 | 0.160407 | 8480.73ms | 7351818 | 30 | 5.80044e+08 | 2.74124e+06 | 0.137727 | 1.95337 | 9.1304 | 2.05933 | 0.00709007 | 0.0340956 | 0.00299905 | 2(Loss) | true |
| glaze | 2156.13 | 0.0893527 | 10171.1ms | 7351818 | 80 | 6.75374e+08 | 3.25177e+06 | 0.248622 | 2.31398 | 10.7355 | 2.22175 | 0.00904323 | 0.033184 | 0.00111202 | 3(Loss) | true |
| simdjson (ondemand) | 2130.93 | 0.176121 | 5020.89ms | 7351818 | 40 | 1.34318e+09 | 3.29023e+06 | 0.8337 | 2.33958 | 9.83427 | 1.5896 | 0.0112062 | 0.0608046 | 0.00535297 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2866.44 | 0.197854 | 8402.55ms | 7351818 | 30 | 7.02608e+08 | 2.44597e+06 | 0.341385 | 1.74401 | 7.69729 | 1.41155 | 0.00925337 | 0.0543766 | 0.00191813 | 1(Win) | true |
| jsonifier | 2824.17 | 0.0621162 | 8517.04ms | 7351818 | 160 | 3.80485e+08 | 2.48258e+06 | 0.60459 | 1.76888 | 8.38684 | 1.88592 | 0.00693128 | 0.0274153 | 0.00111038 | 2(Loss) | true |
| glaze | 2326.6 | 0.167434 | 10202.3ms | 7351818 | 30 | 7.63754e+08 | 3.01351e+06 | 0.489896 | 2.14675 | 9.99116 | 2.048 | 0.00873175 | 0.0273209 | 0.00338327 | 3(Loss) | true |
| simdjson (ondemand) | 2298.56 | 0.135533 | 10247.5ms | 7351818 | 40 | 6.83646e+08 | 3.05028e+06 | 0.0433605 | 2.18815 | 9.08595 | 1.41536 | 0.0100156 | 0.0536637 | 0.014814 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6008.61 | 0.0628752 | 10003ms | 9930848 | 160 | 1.57146e+08 | 1.5762e+06 | 0.065665 | 0.829778 | 2.45627 | 0.16772 | 0.000259118 | 0.0249046 | 0.00126855 | 1(Win) | true |
| glaze | 2781.68 | 0.134618 | 5175.23ms | 9930228 | 80 | 1.68036e+09 | 3.40449e+06 | 0.781248 | 1.78881 | 4.16785 | 0.480859 | 0.000971939 | 0.0757461 | 0.0299529 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6007.58 | 0.0661679 | 10005.4ms | 9930848 | 320 | 3.48192e+08 | 1.57647e+06 | 0.0679847 | 0.82816 | 2.45624 | 0.167714 | 0.000275319 | 0.0248915 | 0.00146086 | 1(Win) | true |
| glaze | 4007.9 | 0.201647 | 7299.26ms | 9930228 | 30 | 6.81067e+08 | 2.36288e+06 | 0.0706133 | 1.24794 | 4.16747 | 0.480771 | 0.000984455 | 0.0222798 | 0.00395438 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1242.58 | 0.0306119 | 9227.71ms | 461466 | 1280 | 1.5046e+07 | 354173 | 0.0469057 | 4.0248 | 17.1011 | 3.24615 | 0.0196109 | 0.0323829 | 9.4964e-05 | 1(Win) | true |
| glaze | 1179.13 | 0.0881444 | 9761.13ms | 461466 | 320 | 3.46334e+07 | 373231 | 0.191302 | 4.25431 | 19.05 | 3.78116 | 0.0136074 | 0.02717 | 0.000132594 | 2(Loss) | true |
| jsonifier (two-stage) | 1115.09 | 0.099824 | 5120.44ms | 461466 | 80 | 1.24172e+07 | 394667 | 0.0115654 | 4.5292 | 18.5173 | 3.47949 | 0.0264707 | 0.0731475 | 0.000116206 | 3(Loss) | true |
| simdjson (ondemand) | 1084.85 | 0.0889302 | 5263.44ms | 461466 | 640 | 8.32947e+07 | 405667 | 0.305867 | 4.58064 | 19.5697 | 3.50903 | 0.0105933 | 0.0775863 | 0.00026945 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1731.44 | 0.0762729 | 8375.79ms | 461466 | 1280 | 4.81075e+07 | 254174 | 0.179206 | 2.89865 | 12.7171 | 2.27447 | 0.0176493 | 0.00360563 | 8.09902e-05 | 1(Win) | true |
| glaze | 1538.21 | 0.0622775 | 9232.08ms | 461466 | 1280 | 4.0637e+07 | 286104 | 0.0946519 | 3.27306 | 15.1087 | 2.89415 | 0.0114581 | 0.00789448 | 5.41227e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1511.03 | 0.0359809 | 9398.99ms | 461466 | 640 | 7.02841e+06 | 291250 | 0.0150219 | 3.3418 | 14.156 | 2.51281 | 0.0237747 | 0.0227793 | 7.59875e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1499.17 | 0.109445 | 9317.62ms | 461466 | 640 | 6.60626e+07 | 293555 | 0.132965 | 3.31653 | 15.4714 | 2.58074 | 0.00322182 | 0.0250693 | 7.08036e-05 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14045 | 0.0678499 | 3905.68ms | 461466 | 80 | 36159.6 | 31334.2 | 0.0186264 | 0.35362 | 1.60702 | 0.264052 | 0.000519621 | 0.0076712 | 7.93666e-06 | 1(Win) | true |
| glaze | 3747.78 | 0.321266 | 6527.66ms | 461466 | 320 | 4.55419e+07 | 117426 | 0.56666 | 1.34277 | 4.97772 | 0.7885 | 0.0107692 | 0.0411853 | 0.000111723 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14153.2 | 0.0810206 | 3888.8ms | 461466 | 320 | 203100 | 31094.6 | 0.203359 | 0.352906 | 1.60583 | 0.263783 | 0.000499089 | 0.00754678 | 1.1519e-05 | 1(Win) | true |
| glaze | 4039.48 | 0.207297 | 5972.7ms | 461466 | 2560 | 1.30573e+08 | 108947 | 0.126177 | 1.24135 | 4.96361 | 0.785211 | 0.0107477 | 0.0166994 | 7.28597e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1648.09 | 0.0836742 | 5461.46ms | 728486 | 40 | 4.97652e+06 | 421542 | 0.0149073 | 3.00696 | 12.2915 | 2.22664 | 0.0167574 | 0.0677987 | 0.000145336 | 1(Win) | true |
| simdjson (ondemand) | 1633.27 | 0.0757852 | 5515.01ms | 728486 | 640 | 6.6508e+07 | 425366 | 0.219876 | 3.03356 | 12.9132 | 2.24614 | 0.00717832 | 0.069048 | 0.000180175 | 2(Loss) | true |
| glaze | 1553.63 | 0.0387398 | 5783.99ms | 728486 | 640 | 1.92062e+07 | 447171 | 0.1631 | 3.20118 | 14.8083 | 2.92523 | 0.0103716 | 0.028072 | 0.000147217 | 3(Loss) | true |
| jsonifier | 1446.05 | 0.118715 | 6220.97ms | 728486 | 80 | 2.60243e+07 | 480439 | 0.00170154 | 3.46539 | 13.5623 | 2.72781 | 0.0125836 | 0.0359805 | 0.000147961 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2229.78 | 0.21053 | 9785.02ms | 728486 | 80 | 3.4422e+07 | 311572 | 0.116006 | 2.22862 | 10.318 | 1.65807 | 0.00247618 | 0.0293049 | 4.23138e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2206.51 | 0.0882411 | 5004.23ms | 728486 | 160 | 1.23508e+07 | 314859 | 0.0686839 | 2.25865 | 9.52071 | 1.61236 | 0.0153038 | 0.0297296 | 4.09325e-05 | 2(Loss) | true |
| glaze | 1931.43 | 0.102209 | 5524.43ms | 728486 | 160 | 2.16265e+07 | 359701 | 0.0108342 | 2.57736 | 12.3116 | 2.36348 | 0.00896394 | 0.0105456 | 4.78046e-05 | 3(Loss) | true |
| jsonifier | 1833.74 | 0.145995 | 5779.56ms | 728486 | 40 | 1.22379e+07 | 378864 | 0.0732422 | 2.72513 | 10.7879 | 2.11296 | 0.0112166 | 0.00968598 | 3.672e-05 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18175.1 | 0.024789 | 5192.32ms | 837491 | 1280 | 151891 | 43944.3 | 0.0478266 | 0.278248 | 0.989658 | 0.145522 | 0.000270765 | 0.0137528 | 5.30789e-06 | 1(Win) | true |
| glaze | 4068.98 | 0.12384 | 5234.67ms | 837491 | 640 | 3.78174e+07 | 196289 | 0.0290433 | 1.22921 | 4.21743 | 0.763079 | 0.00665163 | 0.0587947 | 7.56855e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17967.2 | 0.0186314 | 5230.17ms | 837491 | 4890 | 335427 | 44452.9 | 0.211168 | 0.277846 | 0.989036 | 0.145382 | 0.000268107 | 0.0135902 | 1.35488e-05 | 1(Win) | true |
| glaze | 4726.39 | 0.0828211 | 9092.63ms | 837491 | 2560 | 5.01445e+07 | 168986 | 0.296772 | 1.0687 | 4.2087 | 0.761057 | 0.00665369 | 0.01823 | 3.37499e-05 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 8118.77 | 0.0350164 | 6242.23ms | 466906 | 4890 | 1.80356e+06 | 54845.3 | 0.0379121 | 0.614261 | 3.16049 | 0.382694 | 0.00088987 | 8.02524e-06 | 4.7053e-06 | 1(Win) | true |
| jsonifier | 8071.31 | 0.0347059 | 6277.49ms | 466906 | 4890 | 1.79262e+06 | 55167.8 | 0.241366 | 0.617231 | 3.16303 | 0.383683 | 0.000917985 | 2.21661e-05 | 1.40182e-05 | 2(Loss) | true |
| simdjson (ondemand) | 7004.51 | 0.0696149 | 7118.65ms | 466906 | 640 | 1.25339e+06 | 63570 | 0.258772 | 0.71367 | 3.44678 | 0.375193 | 0.000836417 | 9.19618e-06 | 6.29811e-06 | 3(Loss) | true |
| glaze | 3579.14 | 0.0390668 | 6722.58ms | 466906 | 2560 | 6.04724e+06 | 124409 | 0.0215862 | 1.39712 | 5.40651 | 0.952905 | 0.00170536 | 4.766e-05 | 3.78606e-05 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 8273.66 | 0.0876335 | 6317.23ms | 466906 | 640 | 1.42359e+06 | 53818.5 | 0.120196 | 0.603114 | 3.12616 | 0.374643 | 0.000892899 | 2.62365e-06 | 9.30326e-07 | 1(Win) | true |
| jsonifier | 8227.94 | 0.0469642 | 6233.24ms | 466906 | 2560 | 1.65368e+06 | 54117.6 | 0.227689 | 0.605494 | 3.1282 | 0.375508 | 0.000917786 | 1.2198e-05 | 5.98019e-06 | 2(Loss) | true |
| simdjson (ondemand) | 7113.19 | 0.113162 | 7140.26ms | 466906 | 320 | 1.60577e+06 | 62598.7 | 0.0770877 | 0.701269 | 3.40918 | 0.367782 | 0.000839884 | 2.60358e-06 | 8.90168e-07 | 3(Loss) | true |
| glaze | 3634.02 | 0.0227866 | 6671.88ms | 466906 | 2560 | 1.99565e+06 | 122530 | 0.212946 | 1.37871 | 5.35966 | 0.942438 | 0.00164563 | 1.98221e-05 | 1.6392e-05 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 9321.39 | 0.0280516 | 7209.37ms | 631514 | 4890 | 1.6063e+06 | 64610.4 | 0.0256168 | 0.532295 | 2.79582 | 0.297754 | 0.000707494 | 1.41197e-05 | 1.03798e-05 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 9298.84 | 0.131385 | 7210.13ms | 631514 | 320 | 2.31712e+06 | 64767.1 | 0.141054 | 0.532721 | 2.79678 | 0.29803 | 0.000732654 | 8.51624e-06 | 5.74017e-06 | 1(Tie) | true |
| simdjson (ondemand) | 8336.35 | 0.0777711 | 7991.73ms | 631514 | 320 | 1.01019e+06 | 72244.9 | 0.046227 | 0.605058 | 2.88938 | 0.293067 | 0.000641836 | 4.49762e-05 | 3.38324e-05 | 3(Loss) | true |
| glaze | 4246.47 | 0.0226128 | 7640.86ms | 631514 | 1280 | 1.31653e+06 | 141826 | 0.0334762 | 1.18718 | 5.07321 | 0.89637 | 0.00132681 | 7.31625e-06 | 5.18595e-06 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 9544.6 | 0.041487 | 7269.31ms | 631514 | 2560 | 1.75434e+06 | 63099.4 | 0.236672 | 0.525667 | 2.77143 | 0.292089 | 0.00071315 | 1.02766e-05 | 5.12719e-06 | 1(Win) | true |
| jsonifier | 9452.96 | 0.130032 | 7299.35ms | 631514 | 320 | 2.19625e+06 | 63711.1 | 0.0326612 | 0.523959 | 2.77053 | 0.291835 | 0.000726676 | 2.41978e-06 | 1.52412e-06 | 2(Loss) | true |
| simdjson (ondemand) | 8515.08 | 0.083015 | 7981.86ms | 631514 | 80 | 275798 | 70728.5 | 0.0574356 | 0.592859 | 2.86297 | 0.287898 | 0.000638149 | 1.80123e-05 | 1.10845e-05 | 3(Loss) | true |
| glaze | 4278.44 | 0.0391872 | 7626.48ms | 631514 | 640 | 1.94744e+06 | 140766 | 0.11481 | 1.17535 | 5.03876 | 0.888698 | 0.0012686 | 6.99213e-06 | 5.76244e-06 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1915.07 | 0.0355271 | 6139.16ms | 466906 | 1280 | 8.73412e+06 | 232511 | 0.196087 | 2.62236 | 8.17559 | 1.45902 | 0.0124873 | 0.0130574 | 0.000109315 | 1(Win) | true |
| glaze | 1841.62 | 0.0522544 | 6381.47ms | 466906 | 640 | 1.0216e+07 | 241784 | 0.00754166 | 2.73005 | 9.9531 | 1.79187 | 0.0138035 | 0.0127213 | 5.42635e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1724.65 | 0.0627921 | 6817.24ms | 466906 | 640 | 1.68209e+07 | 258184 | 0.00265806 | 2.92119 | 9.15417 | 1.52175 | 0.0170243 | 0.0295898 | 0.000131932 | 3(Loss) | true |
| simdjson (ondemand) | 1692.62 | 0.248904 | 6937.39ms | 466906 | 80 | 3.42998e+07 | 263069 | 0.0612145 | 2.95716 | 10.0086 | 1.51176 | 0.0122112 | 0.0323819 | 0.00015003 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2599.7 | 0.0372318 | 5267.34ms | 466906 | 1280 | 5.20534e+06 | 171280 | 0.0749944 | 1.92822 | 6.6934 | 1.12328 | 0.00589112 | 0.00240829 | 4.08674e-05 | 1(Win) | true |
| glaze | 2336.5 | 0.0808962 | 5808.47ms | 466906 | 320 | 7.60563e+06 | 190574 | 0.0405075 | 2.15023 | 8.45662 | 1.45122 | 0.0104735 | 0.00208133 | 3.96158e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2287.4 | 0.0707968 | 5919.56ms | 466906 | 640 | 1.21557e+07 | 194665 | 0.107975 | 2.18324 | 7.67292 | 1.18648 | 0.00940504 | 0.00811564 | 5.24028e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2108.47 | 0.0912294 | 6287.32ms | 466906 | 640 | 2.3756e+07 | 211184 | 0.128636 | 2.35727 | 8.58736 | 1.18834 | 0.00836968 | 0.00799903 | 3.52185e-05 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19442.5 | 0.0264967 | 3097.27ms | 475954 | 4890 | 187120 | 23346.1 | 0.112567 | 0.256216 | 1.01388 | 0.151351 | 0.000271407 | 0.000412892 | 1.16881e-05 | 1(Win) | true |
| glaze | 6359.43 | 0.235985 | 7901.77ms | 475954 | 2560 | 7.2628e+07 | 71375.2 | 0.220548 | 0.784341 | 2.12988 | 0.335757 | 0.00031963 | 0.0136799 | 1.39555e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19604.8 | 0.02435 | 3078.38ms | 475954 | 4890 | 155422 | 23152.7 | 0.00715863 | 0.255193 | 1.01269 | 0.151086 | 0.000267633 | 0.000332993 | 1.31726e-05 | 1(Win) | true |
| glaze | 7377.54 | 0.416181 | 6890.59ms | 475954 | 640 | 4.19615e+07 | 61525.3 | 0.154568 | 0.679699 | 2.11735 | 0.332885 | 0.000321689 | 0.000832949 | 0.000144145 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 2195.12 | 0.088827 | 7213.38ms | 631514 | 320 | 1.90059e+07 | 274362 | 0.0319479 | 2.27648 | 7.21951 | 1.14142 | 0.0121989 | 0.031129 | 0.000119282 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2190.42 | 0.0669901 | 7232.61ms | 631514 | 1280 | 4.34251e+07 | 274951 | 0.0217639 | 2.26482 | 7.73781 | 1.13257 | 0.00866746 | 0.0362825 | 0.000282021 | 1(Tie) | true |
| glaze | 2034.86 | 0.0992263 | 7814.39ms | 631514 | 160 | 1.37997e+07 | 295970 | 0.047688 | 2.46766 | 9.07237 | 1.65291 | 0.0116761 | 0.0133901 | 0.000160022 | 3(Loss) | true |
| jsonifier | 1740.52 | 0.173954 | 8926.52ms | 631514 | 40 | 1.44923e+07 | 346022 | 0.128396 | 2.88041 | 7.70767 | 1.47043 | 0.010049 | 0.0222543 | 0.000313018 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2879.96 | 0.216035 | 6314.23ms | 631514 | 80 | 1.6328e+07 | 209120 | 0.0343521 | 1.73409 | 6.12357 | 0.893639 | 0.00691424 | 0.0122037 | 2.61277e-05 | 1(Win) | true |
| simdjson (ondemand) | 2725.62 | 0.109879 | 6548.99ms | 631514 | 640 | 3.77261e+07 | 220962 | 0.300813 | 1.824 | 6.69471 | 0.895445 | 0.00621112 | 0.0126103 | 3.14918e-05 | 2(Loss) | true |
| glaze | 2488.53 | 0.0370073 | 7159.36ms | 631514 | 1280 | 1.02675e+07 | 242014 | 0.337301 | 2.01776 | 7.96997 | 1.40299 | 0.00853999 | 0.00398846 | 5.60459e-05 | 3(Loss) | true |
| jsonifier | 2047.8 | 0.030851 | 8486.48ms | 631514 | 1280 | 1.05376e+07 | 294101 | 0.0425247 | 2.44893 | 6.61157 | 1.22232 | 0.00787812 | 0.00619235 | 6.96949e-05 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20583 | 0.0241985 | 4070.1ms | 716365 | 4890 | 315456 | 33191.5 | 0.0774139 | 0.242119 | 0.825498 | 0.117465 | 0.000202188 | 0.00418491 | 8.46611e-06 | 1(Win) | true |
| glaze | 4829.68 | 0.0985634 | 7674.86ms | 716365 | 2560 | 4.97626e+07 | 141454 | 0.41587 | 1.03528 | 2.50063 | 0.441888 | 0.000504545 | 0.0455451 | 1.79476e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20758.7 | 0.0328148 | 4068.1ms | 716365 | 1280 | 149285 | 32910.5 | 0.0353984 | 0.241056 | 0.82477 | 0.117302 | 0.000204332 | 0.00419428 | 3.17685e-06 | 1(Win) | true |
| glaze | 5844.13 | 0.239175 | 6381.65ms | 716365 | 2560 | 2.00124e+08 | 116900 | 0.0818623 | 0.850373 | 2.49079 | 0.439604 | 0.000496742 | 0.00394538 | 1.36131e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2649.47 | 0.0950038 | 833.991ms | 2632 | 2560 | 2073.85 | 947.388 | 0.0110513 | 1.98831 | 7.68465 | 1.33359 | 0.000761659 | 9.83983e-05 | 7.16838e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2231.43 | 0.0508502 | 855.152ms | 2632 | 4890 | 1599.93 | 1124.87 | 0.0169851 | 2.33326 | 9.43161 | 1.6421 | 0.00123072 | 5.76513e-05 | 2.96026e-05 | 2(Loss) | true |
| glaze | 1906.21 | 0.153257 | 871.569ms | 2632 | 160 | 651.615 | 1316.79 | 0.103365 | 2.71839 | 11.234 | 2.12956 | 0.00241261 | 1.8997e-05 | 4.74924e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1514.61 | 0.218062 | 919.672ms | 2632 | 80 | 1044.77 | 1657.24 | 0.0309345 | 3.42089 | 11.7629 | 2.05927 | 0.00395612 | 1.8997e-05 | 1.8997e-05 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3149.84 | 0.134311 | 850.53ms | 2632 | 320 | 366.577 | 796.888 | 0.0235235 | 1.68776 | 6.7329 | 1.08777 | 0.000759878 | 2.49335e-05 | 8.31117e-06 | 1(Win) | true |
| jsonifier (two-stage) | 2554.89 | 0.0675655 | 849.055ms | 2632 | 4890 | 2154.7 | 982.457 | 0.0996019 | 2.04933 | 8.481 | 1.39628 | 0.00110081 | 6.46441e-05 | 3.65177e-05 | 2(Loss) | true |
| glaze | 2423.99 | 0.0772645 | 846.897ms | 2632 | 4890 | 3130.25 | 1035.51 | 0.256239 | 2.166 | 9.35524 | 1.69605 | 0.00161431 | 3.80716e-05 | 2.24545e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1824.79 | 0.108473 | 888.804ms | 2632 | 2560 | 5699.4 | 1375.54 | 0.23626 | 2.83202 | 10.0737 | 1.66945 | 0.00170082 | 8.57831e-05 | 3.94781e-05 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10050.7 | 0.123222 | 763.365ms | 2632 | 4890 | 463.081 | 249.74 | 0.0647283 | 0.581749 | 1.85562 | 0.302812 | 0.000380328 | 6.58095e-05 | 3.68285e-05 | 1(Win) | true |
| glaze | 3522.93 | 0.112842 | 807.616ms | 2632 | 4890 | 3160.92 | 712.496 | 0.216449 | 1.50926 | 4.58093 | 0.75076 | 0.00038328 | 8.10382e-05 | 3.58961e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11562.6 | 0.12308 | 755.473ms | 2632 | 4890 | 349.101 | 217.086 | 0.502094 | 0.514081 | 1.6478 | 0.254939 | 0.000380017 | 4.12572e-05 | 1.67049e-05 | 1(Win) | true |
| glaze | 3671.69 | 0.125063 | 805.544ms | 2632 | 4890 | 3574.4 | 683.628 | 0.382854 | 1.45285 | 4.06193 | 0.641337 | 0.000652035 | 6.27016e-05 | 2.95249e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2692.45 | 0.0797023 | 859.87ms | 3370 | 2560 | 2317.11 | 1193.66 | 0.0316676 | 1.94281 | 7.99436 | 1.33472 | 0.000859027 | 4.89151e-05 | 2.58485e-05 | 1(Win) | true |
| jsonifier | 2226.52 | 0.0528375 | 884.223ms | 3370 | 2560 | 1489.12 | 1443.45 | 0.0660203 | 2.32527 | 8.42493 | 1.61484 | 0.00138678 | 4.06853e-05 | 2.26029e-05 | 2(Loss) | true |
| glaze | 2129.68 | 0.0522051 | 899.606ms | 3370 | 4890 | 3035.04 | 1509.09 | 0.197731 | 2.41528 | 10.6783 | 2.04896 | 0.00100508 | 4.6786e-05 | 1.90542e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1903.09 | 0.153999 | 928.247ms | 3370 | 160 | 1082.18 | 1688.78 | 0.0658328 | 2.71898 | 9.58131 | 1.64421 | 0.00335497 | 5.37834e-05 | 3.33828e-05 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3041.91 | 0.0734755 | 860.744ms | 3370 | 4890 | 2946.88 | 1056.54 | 0.0624038 | 1.71426 | 7.07396 | 1.10862 | 0.000610159 | 4.8121e-05 | 2.0996e-05 | 1(Win) | true |
| glaze | 2611.77 | 0.105611 | 872.338ms | 3370 | 2560 | 4323.62 | 1230.54 | 0.038457 | 1.98806 | 9.20785 | 1.71041 | 0.00131665 | 4.34672e-05 | 2.23711e-05 | 2(Loss) | true |
| jsonifier | 2502.75 | 0.0640557 | 879.924ms | 3370 | 320 | 216.516 | 1284.14 | 0.00948988 | 2.08703 | 7.68249 | 1.42285 | 0.00137426 | 5.74926e-05 | 2.22552e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2338.05 | 0.0644497 | 888.186ms | 3370 | 4890 | 3837.97 | 1374.6 | 0.0485809 | 2.22466 | 8.23234 | 1.33323 | 0.000634129 | 8.19816e-05 | 4.30237e-05 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13790.6 | 0.265919 | 755.353ms | 3643 | 2560 | 1148.92 | 251.927 | 0.812207 | 0.425224 | 1.38732 | 0.207521 | 0.000274499 | 2.05874e-05 | 3.00233e-06 | 1(Win) | true |
| glaze | 3494.84 | 0.0885691 | 835.988ms | 3682 | 4890 | 3872.46 | 1004.75 | 0.107194 | 1.5002 | 4.38647 | 0.762901 | 0.000274535 | 2.59373e-05 | 4.10997e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16424.2 | 0.135041 | 751.463ms | 3643 | 160 | 13.0556 | 211.531 | 0.0561698 | 0.365686 | 1.30222 | 0.187208 | 0.000274499 | 1.71562e-05 | 0 | 1(Win) | true |
| glaze | 3814.35 | 0.191915 | 840.582ms | 3682 | 1280 | 3995.36 | 920.584 | 0.0806015 | 1.38427 | 4.03802 | 0.683053 | 0.000298114 | 1.08212e-05 | 1.27309e-06 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 979.337 | 0.101074 | 1185.36ms | 4630 | 40 | 830.687 | 4508.68 | 0.157908 | 5.20949 | 23.4598 | 4.76955 | 0.00739201 | 5.93952e-05 | 0 | 1(Win) | true |
| jsonifier (two-stage) | 956.145 | 0.0771007 | 1200.72ms | 4630 | 1280 | 16227.1 | 4618.04 | 0.279857 | 5.2652 | 26.0201 | 5.06048 | 0.0044754 | 4.69087e-05 | 8.26809e-06 | 2(Loss) | true |
| glaze | 788.987 | 0.0910033 | 1296.82ms | 4630 | 1280 | 33200.7 | 5596.43 | 0.0564633 | 6.402 | 29.7311 | 5.84579 | 0.00341573 | 8.43683e-05 | 3.84719e-05 | 3(Loss) | true |
| simdjson (ondemand) | 707.064 | 0.0570588 | 1365.5ms | 4630 | 4890 | 62086.8 | 6244.85 | 0.0825299 | 7.15069 | 31.4315 | 5.47927 | 0.00309871 | 0.00016382 | 7.68527e-05 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1251.68 | 0.0901602 | 1185.78ms | 4630 | 640 | 6474.15 | 3527.66 | 0.337828 | 4.07633 | 19.0503 | 3.746 | 0.00416847 | 2.66604e-05 | 1.68737e-06 | 1(Win) | true |
| jsonifier (two-stage) | 1215.24 | 0.0563588 | 1201.07ms | 4630 | 160 | 670.942 | 3633.46 | 0.0681633 | 4.21148 | 21.5944 | 4.03413 | 0.00293467 | 2.42981e-05 | 2.69978e-06 | 2(Loss) | true |
| glaze | 942.874 | 0.0730597 | 1302.23ms | 4630 | 1280 | 14983.8 | 4683.04 | 0.192285 | 5.38894 | 25.1987 | 4.79417 | 0.0017503 | 5.33207e-05 | 1.40051e-05 | 3(Loss) | true |
| simdjson (ondemand) | 814.186 | 0.0562374 | 1382.62ms | 4630 | 2560 | 23812.5 | 5423.22 | 0.172856 | 6.19971 | 28.151 | 4.72052 | 0.000762352 | 6.89289e-05 | 2.31169e-05 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1542.1 | 0.095386 | 1025.67ms | 4630 | 2560 | 19096.1 | 2863.31 | 0.0674709 | 3.30158 | 7.94125 | 0.456156 | 0.000225938 | 3.32411e-05 | 5.3152e-06 | 1(Win) | true |
| glaze | 913.032 | 0.0816064 | 1215.24ms | 4630 | 40 | 623.015 | 4836.1 | 0.00206782 | 5.48131 | 9.76242 | 0.679266 | 0.000410367 | 4.85961e-05 | 5.39957e-06 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1552.72 | 0.0678731 | 1020.1ms | 4630 | 4890 | 18217.2 | 2843.74 | 0.0563035 | 3.26328 | 7.83542 | 0.431966 | 0.000220311 | 3.36562e-05 | 9.27533e-06 | 1(Win) | true |
| glaze | 993.247 | 0.0446014 | 1180.57ms | 4630 | 2560 | 10064.3 | 4445.53 | 0.0460382 | 5.1043 | 9.2527 | 0.565875 | 0.000219611 | 3.72064e-05 | 1.6958e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2154.31 | 0.044297 | 1257.52ms | 11579 | 2560 | 13198.2 | 5125.82 | 0.189609 | 2.33039 | 11.0966 | 2.04068 | 0.00223559 | 4.62178e-05 | 2.18607e-05 | 1(Win) | true |
| jsonifier | 1956.96 | 0.13714 | 1307.47ms | 11579 | 40 | 2395.33 | 5642.73 | 0.0512722 | 2.55426 | 11.7053 | 2.46671 | 0.00421021 | 2.5909e-05 | 1.29545e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1670.52 | 0.0835799 | 1411.92ms | 11579 | 1280 | 39071.1 | 6610.29 | 0.0288529 | 3.03123 | 13.2532 | 2.21168 | 0.00116671 | 0.000134403 | 8.64982e-05 | 3(Loss) | true |
| glaze | 1494.62 | 0.15651 | 1475.99ms | 11579 | 320 | 42786.9 | 7388.21 | 0.132269 | 3.3376 | 14.5485 | 2.8436 | 0.00447092 | 1.34943e-05 | 1.8892e-06 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2648.68 | 0.0634806 | 1257.76ms | 11579 | 2560 | 17931 | 4169.09 | 0.329344 | 1.90812 | 9.35323 | 1.63641 | 0.00154472 | 3.59285e-05 | 1.71377e-05 | 1(Win) | true |
| jsonifier | 2283.56 | 0.0506769 | 1323.34ms | 11579 | 1280 | 7686.85 | 4835.7 | 0.151619 | 2.18768 | 9.97349 | 2.06503 | 0.00316447 | 2.77307e-05 | 1.03906e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1904.18 | 0.042886 | 1426.5ms | 11579 | 2560 | 15834.3 | 5799.14 | 0.116033 | 2.64485 | 12.0139 | 1.92573 | 0.000245461 | 2.67186e-05 | 1.28195e-05 | 3(Loss) | true |
| glaze | 1720.71 | 0.0873316 | 1476.65ms | 11579 | 2560 | 80409.9 | 6417.46 | 0.242382 | 2.92406 | 12.7788 | 2.43372 | 0.00373201 | 2.42559e-05 | 6.24109e-06 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4621.34 | 0.0558551 | 1049.08ms | 14795 | 4890 | 14220.9 | 3053.14 | 0.116629 | 1.09582 | 2.56999 | 0.144373 | 6.83092e-05 | 1.45133e-05 | 3.66287e-06 | 1(Win) | true |
| glaze | 3436.64 | 0.0534166 | 1157.79ms | 14795 | 2560 | 12312.7 | 4105.64 | 0.253437 | 1.47105 | 4.44164 | 0.532748 | 0.000947612 | 2.46863e-05 | 1.23828e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4190.81 | 0.0647618 | 1077.78ms | 14795 | 4890 | 23247.7 | 3366.8 | 0.176244 | 1.20613 | 2.532 | 0.135451 | 6.85994e-05 | 2.26269e-05 | 9.68934e-06 | 1(Win) | true |
| glaze | 3832.54 | 0.0396016 | 1108.6ms | 14795 | 4890 | 10394.2 | 3681.53 | 0.195676 | 1.32633 | 4.23853 | 0.486313 | 0.000963543 | 3.15284e-05 | 1.63654e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1767.16 | 0.145894 | 912.662ms | 3223 | 1280 | 8242.38 | 1739.34 | 0.00269506 | 2.9109 | 11.2644 | 2.11449 | 0.0013235 | 3.78141e-05 | 1.57559e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1416.49 | 0.0571871 | 963.99ms | 3223 | 2560 | 3942.13 | 2169.94 | 0.0578059 | 3.59166 | 14.0127 | 2.47285 | 0.00169146 | 3.97533e-05 | 1.62407e-05 | 2(Loss) | true |
| glaze | 1399.38 | 0.0438506 | 956.213ms | 3223 | 4890 | 4536.36 | 2196.46 | 0.0475257 | 3.67064 | 14.6693 | 2.81973 | 0.00136925 | 5.37421e-05 | 2.32861e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1181.87 | 0.0720498 | 1006.76ms | 3223 | 2560 | 8988.48 | 2600.7 | 0.190395 | 4.27915 | 15.6733 | 2.67887 | 0.00225467 | 0.000101929 | 4.83585e-05 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2155.22 | 0.113798 | 908.181ms | 3223 | 1280 | 3371.44 | 1426.16 | 0.0292987 | 2.42312 | 9.74217 | 1.72541 | 0.00151887 | 9.86561e-05 | 6.95683e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1676.72 | 0.153115 | 951.537ms | 3223 | 1280 | 10084.2 | 1833.15 | 0.0435317 | 3.02318 | 12.4902 | 2.08377 | 0.00110122 | 4.48437e-05 | 1.52711e-05 | 2(Loss) | true |
| glaze | 1642.93 | 0.0611877 | 947.623ms | 3223 | 4890 | 6407.93 | 1870.86 | 0.228223 | 3.11137 | 13.005 | 2.40521 | 0.00118226 | 4.73971e-05 | 2.06847e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1374.03 | 0.0872856 | 996.292ms | 3223 | 320 | 1220.01 | 2236.99 | 0.0329576 | 3.73266 | 14.0349 | 2.27242 | 0.00301156 | 2.6179e-05 | 4.84797e-06 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 7420.01 | 0.0688634 | 784.87ms | 3223 | 1280 | 104.159 | 414.244 | 0.0154625 | 0.734443 | 2.3444 | 0.408315 | 0.00031027 | 3.7087e-05 | 1.11503e-05 | 1(Win) | true |
| glaze | 3088.19 | 0.783494 | 844.188ms | 3223 | 320 | 19459.6 | 995.306 | 0.226176 | 1.67385 | 4.74899 | 0.738134 | 0.000319966 | 5.81756e-05 | 8.72634e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8419.13 | 0.0768939 | 778.404ms | 3223 | 320 | 25.2186 | 365.084 | 0.00941475 | 0.655664 | 2.18771 | 0.371083 | 0.00031027 | 2.71486e-05 | 6.78715e-06 | 1(Win) | true |
| glaze | 3310.41 | 0.213388 | 834.07ms | 3223 | 1280 | 5024.69 | 928.494 | 0.0515212 | 1.57791 | 4.20199 | 0.614955 | 0.000323117 | 4.77525e-05 | 2.18159e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2416.25 | 0.08721 | 977.182ms | 5839 | 1280 | 5170.53 | 2304.6 | 0.0247405 | 2.11153 | 8.40623 | 1.40332 | 0.000744857 | 2.89005e-05 | 1.36475e-05 | 1(Win) | true |
| simdjson (ondemand) | 2042.35 | 0.13348 | 1019ms | 5839 | 1280 | 16953.6 | 2726.52 | 0.170885 | 2.47598 | 9.19147 | 1.50403 | 0.00133304 | 0.000111856 | 6.55613e-05 | 2(Loss) | true |
| jsonifier | 1951.91 | 0.138067 | 1027.32ms | 5839 | 640 | 9929.27 | 2852.85 | 0.21462 | 2.58916 | 9.20586 | 1.88269 | 0.00160103 | 4.20128e-05 | 2.62245e-05 | 3(Loss) | true |
| glaze | 1787.09 | 0.181097 | 1050.37ms | 5839 | 30 | 955.275 | 3115.97 | 0.00855734 | 2.81523 | 10.9529 | 2.12656 | 0.00217503 | 6.27961e-05 | 1.71262e-05 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2835.49 | 0.0582193 | 961.35ms | 5839 | 4890 | 6392.42 | 1963.86 | 0.0175479 | 1.79859 | 7.56585 | 1.18856 | 0.000601519 | 4.69658e-05 | 2.34654e-05 | 1(Win) | true |
| simdjson (ondemand) | 2361.25 | 0.0520439 | 1007.02ms | 5839 | 4890 | 7366.15 | 2358.29 | 0.0985281 | 2.15333 | 8.28746 | 1.27899 | 0.00109068 | 4.04515e-05 | 1.66359e-05 | 2(Loss) | true |
| jsonifier | 2220.5 | 0.0700357 | 1017.3ms | 5839 | 2560 | 7896.83 | 2507.77 | 0.0840585 | 2.28953 | 8.36496 | 1.66775 | 0.00155059 | 3.7196e-05 | 1.75276e-05 | 3(Loss) | true |
| glaze | 2050.73 | 0.026806 | 1035.51ms | 5839 | 1280 | 678.162 | 2715.37 | 0.03966 | 2.45843 | 10.0343 | 1.89776 | 0.00139378 | 1.47178e-05 | 2.80977e-06 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14409.9 | 0.0698499 | 788.675ms | 6938 | 1280 | 131.671 | 459.17 | 0.132547 | 0.376614 | 1.24171 | 0.195734 | 0.000144134 | 3.5583e-05 | 1.66655e-05 | 1(Win) | true |
| glaze | 3911.54 | 0.155144 | 915.525ms | 6960 | 2560 | 17743.2 | 1696.92 | 0.480243 | 1.31951 | 3.88175 | 0.702586 | 0.000465944 | 3.14296e-05 | 1.173e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16156.2 | 0.0794414 | 783.922ms | 6938 | 2560 | 270.972 | 409.539 | 0.0769367 | 0.339697 | 1.16676 | 0.178293 | 0.000144134 | 3.21486e-05 | 1.84671e-05 | 1(Win) | true |
| glaze | 4266.89 | 0.458769 | 902.697ms | 6960 | 640 | 32595.9 | 1555.6 | 0.0921222 | 1.21427 | 3.52629 | 0.626006 | 0.000436422 | 2.33477e-05 | 1.12249e-05 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2001.19 | 0.0728543 | 977.515ms | 4857 | 2560 | 7279.62 | 2314.62 | 0.0108865 | 2.52826 | 9.44143 | 1.78505 | 0.00069986 | 7.91384e-05 | 4.26253e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1743.78 | 0.193187 | 1011.1ms | 4857 | 30 | 790.01 | 2656.3 | 0.00376478 | 2.90491 | 11.4937 | 2.01832 | 0.000432366 | 2.05888e-05 | 0 | 2(Loss) | true |
| glaze | 1691.87 | 0.0739982 | 1019.89ms | 4857 | 1280 | 5253.59 | 2737.8 | 0.136129 | 2.99155 | 11.9124 | 2.25468 | 0.00148143 | 6.72354e-05 | 3.02399e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1502.2 | 0.059109 | 1058.14ms | 4857 | 2560 | 8504.05 | 3083.47 | 0.0599993 | 3.37387 | 12.9444 | 2.15956 | 0.000465581 | 0.000157472 | 9.00762e-05 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2719.07 | 0.0651756 | 941.665ms | 4857 | 2560 | 3155.78 | 1703.53 | 0.0626851 | 1.88901 | 7.27857 | 1.28721 | 0.000413546 | 4.06147e-05 | 2.13127e-05 | 1(Win) | true |
| glaze | 2403.06 | 0.0492568 | 962.818ms | 4857 | 4890 | 4408.07 | 1927.54 | 0.209752 | 2.11717 | 9.05703 | 1.62384 | 0.00105508 | 4.42513e-05 | 1.70942e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2175.8 | 0.0676385 | 980.193ms | 4857 | 320 | 663.495 | 2128.88 | 0.251261 | 2.32886 | 9.55466 | 1.56702 | 0.000413064 | 3.47437e-05 | 1.02944e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1905.48 | 0.0677416 | 1013.53ms | 4857 | 4890 | 13260.1 | 2430.88 | 0.192001 | 2.66363 | 10.9067 | 1.70826 | 0.00150151 | 7.18715e-05 | 2.78728e-05 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10148.8 | 0.138616 | 785.493ms | 4857 | 320 | 128.079 | 456.406 | 0.127516 | 0.53924 | 1.68067 | 0.285979 | 0.000205888 | 1.35114e-05 | 7.07741e-06 | 1(Win) | true |
| glaze | 3520.53 | 0.275086 | 873.963ms | 4857 | 1280 | 16767.4 | 1315.71 | 0.55895 | 1.46705 | 3.81038 | 0.633931 | 0.000256235 | 4.87376e-05 | 1.25463e-05 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11324.5 | 0.096089 | 781.153ms | 4857 | 40 | 6.17885 | 409.025 | 0.218474 | 0.481949 | 1.57361 | 0.260037 | 0.000205888 | 1.02944e-05 | 0 | 1(Win) | true |
| glaze | 3852.82 | 0.142755 | 861.803ms | 4857 | 4890 | 14403.5 | 1202.24 | 0.324327 | 1.34131 | 3.32839 | 0.524398 | 0.000254266 | 9.1113e-05 | 6.1977e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2331.49 | 0.0614554 | 1020.68ms | 6701 | 2560 | 7263.92 | 2740.98 | 0.244822 | 2.16042 | 8.85256 | 1.48217 | 0.00034125 | 8.34763e-05 | 4.55273e-05 | 1(Win) | true |
| simdjson (ondemand) | 1981.74 | 0.216036 | 1071.6ms | 6701 | 80 | 3882.66 | 3224.72 | 0.122341 | 2.53613 | 9.79421 | 1.58812 | 0.000315251 | 5.03656e-05 | 2.61155e-05 | 2(Loss) | true |
| glaze | 1970.18 | 0.0427249 | 1069.79ms | 6701 | 4890 | 9391.61 | 3243.66 | 0.209022 | 2.55437 | 10.9275 | 2.14252 | 0.000502321 | 5.87771e-05 | 2.73133e-05 | 3(Loss) | true |
| jsonifier | 1686.9 | 0.0435866 | 1129.57ms | 6701 | 4890 | 13332.7 | 3788.36 | 0.109748 | 2.97259 | 9.65669 | 1.98582 | 0.00234577 | 6.35073e-05 | 3.2837e-05 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2858.01 | 0.120471 | 1002.64ms | 6701 | 640 | 4644.08 | 2236.02 | 0.0126496 | 1.76921 | 7.4471 | 1.15505 | 0.000304292 | 2.16852e-05 | 2.09857e-06 | 1(Win) | true |
| glaze | 2634.44 | 0.0720684 | 1017.23ms | 6701 | 2560 | 7824.09 | 2425.78 | 0.25194 | 1.91771 | 8.78884 | 1.6702 | 0.000946454 | 4.49443e-05 | 2.19767e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2548.86 | 0.0842682 | 1020.06ms | 6701 | 2560 | 11427.6 | 2507.22 | 0.0691273 | 1.99655 | 8.23623 | 1.24474 | 0.000942723 | 9.08796e-05 | 5.08903e-05 | 3(Loss) | true |
| jsonifier | 2092.31 | 0.0590733 | 1082.37ms | 6701 | 2560 | 8333.9 | 3054.31 | 0.0670988 | 2.40464 | 7.99537 | 1.60543 | 0.00153924 | 4.61685e-05 | 2.06942e-05 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14575.8 | 0.0681772 | 790.567ms | 7376 | 1280 | 138.568 | 482.601 | 0.262692 | 0.371751 | 1.21014 | 0.191025 | 0.000136316 | 2.42552e-05 | 5.71956e-06 | 1(Win) | true |
| glaze | 3360.44 | 0.122008 | 957.489ms | 7376 | 4890 | 31895.9 | 2093.27 | 0.453945 | 1.51303 | 3.92476 | 0.703227 | 0.000364804 | 2.34553e-05 | 4.07556e-06 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16139.8 | 0.0637704 | 784.919ms | 7376 | 1280 | 98.8769 | 435.836 | 0.113417 | 0.339932 | 1.13395 | 0.173807 | 0.000136316 | 2.75386e-05 | 9.21485e-06 | 1(Win) | true |
| glaze | 3747.43 | 0.253383 | 931.649ms | 7376 | 1280 | 28956 | 1877.1 | 0.547496 | 1.36273 | 3.6128 | 0.632592 | 0.000405771 | 5.46536e-05 | 3.45292e-05 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2130.07 | 0.17628 | 815.841ms | 1691 | 320 | 569.972 | 757.094 | 0.12812 | 2.5186 | 8.49556 | 1.48137 | 0.00164289 | 9.05529e-05 | 5.35925e-05 | 1(Win) | true |
| simdjson (ondemand) | 1911.78 | 0.0821819 | 823.692ms | 1691 | 320 | 153.785 | 843.541 | 0.044846 | 2.72285 | 9.43051 | 1.49379 | 0.000591366 | 3.88084e-05 | 0 | 2(Loss) | true |
| glaze STATISTICAL TIE | 1837.11 | 0.0793909 | 831.089ms | 1691 | 4890 | 2375.03 | 877.828 | 0.0792468 | 2.8425 | 10.3253 | 1.94382 | 0.00190168 | 7.71557e-05 | 1.22143e-05 | 3(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1833.29 | 0.0815133 | 827.632ms | 1691 | 4890 | 2514.15 | 879.656 | 0.0358919 | 2.85287 | 9.90006 | 1.68776 | 0.000594994 | 9.20306e-05 | 3.51917e-05 | 3(Tie) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2644.64 | 0.172389 | 806.691ms | 1691 | 2560 | 2828.88 | 609.786 | 0.00160151 | 2.02452 | 6.93969 | 1.10053 | 0.00145924 | 5.98296e-05 | 1.31671e-05 | 1(Win) | true |
| simdjson (ondemand) | 2345.01 | 0.256181 | 821.905ms | 1691 | 30 | 93.1138 | 687.7 | 0.0824682 | 2.24278 | 7.98758 | 1.1437 | 0.000591366 | 9.8561e-05 | 0 | 2(Loss) | true |
| glaze | 2265.54 | 0.0751433 | 821.401ms | 1691 | 1280 | 366.214 | 711.823 | 0.191263 | 2.32222 | 8.74985 | 1.56239 | 0.00129038 | 6.05226e-05 | 1.84802e-05 | 3(Loss) | true |
| jsonifier (two-stage) | 2252.37 | 0.10268 | 818.584ms | 1691 | 2560 | 1383.62 | 715.985 | 0.223242 | 2.34369 | 8.34595 | 1.30692 | 0.000594138 | 7.29967e-05 | 1.89422e-05 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10403.9 | 0.172955 | 761.722ms | 1996 | 2560 | 256.352 | 182.963 | 0.0294542 | 0.582656 | 1.57315 | 0.267535 | 0.000501198 | 0.000124468 | 6.12553e-05 | 1(Win) | true |
| glaze | 4156.01 | 0.222027 | 788.732ms | 1996 | 2560 | 2647.4 | 458.02 | 0.171896 | 1.3034 | 3.62776 | 0.602205 | 0.000582219 | 4.01193e-05 | 7.43675e-06 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12977.9 | 0.3566 | 757.842ms | 1996 | 40 | 10.9429 | 146.675 | 0.00568182 | 0.490093 | 1.30762 | 0.205411 | 0.000501002 | 3.75752e-05 | 0 | 1(Win) | true |
| glaze | 4556.69 | 0.190566 | 779.62ms | 1996 | 4890 | 3099 | 417.745 | 0.0923896 | 1.20264 | 3.05611 | 0.480461 | 0.000502436 | 3.924e-05 | 1.49583e-05 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2336.95 | 0.0881421 | 827.752ms | 2158 | 4890 | 2946.32 | 880.647 | 0.00915436 | 2.24793 | 7.76425 | 1.20716 | 0.000468225 | 0.000129826 | 6.60499e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2229.96 | 0.137508 | 837.785ms | 2158 | 1280 | 2061.44 | 922.899 | 0.0119373 | 2.34504 | 8.13948 | 1.32855 | 0.000761339 | 7.78354e-05 | 3.62025e-05 | 2(Loss) | true |
| glaze | 2059.26 | 0.0784832 | 845.239ms | 2158 | 4890 | 3008.44 | 999.4 | 0.0637321 | 2.50935 | 9.70621 | 1.8684 | 0.000466424 | 6.33018e-05 | 1.75312e-05 | 3(Loss) | true |
| jsonifier | 1989.85 | 0.128823 | 850.953ms | 2158 | 1280 | 2272.29 | 1034.27 | 0.0724166 | 2.61354 | 8.61168 | 1.63068 | 0.000846052 | 0.000145896 | 8.25417e-05 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2822.46 | 0.198192 | 823.852ms | 2158 | 80 | 167.075 | 729.163 | 0.0736604 | 1.85945 | 6.576 | 0.921223 | 0.000463392 | 5.7924e-05 | 5.7924e-06 | 1(Win) | true |
| jsonifier (two-stage) | 2742.2 | 0.0946064 | 824.71ms | 2158 | 320 | 161.323 | 750.503 | 0.00791073 | 1.93336 | 6.92169 | 1.03012 | 0.000858723 | 2.31696e-05 | 2.8962e-06 | 2(Loss) | true |
| glaze | 2472.19 | 0.0753254 | 836.504ms | 2158 | 4890 | 1922.79 | 832.474 | 0.011473 | 2.10596 | 8.47173 | 1.56951 | 0.000469552 | 2.93766e-05 | 7.29677e-06 | 3(Loss) | true |
| jsonifier | 2389.68 | 0.0709043 | 839.828ms | 2158 | 4890 | 1823.38 | 861.215 | 0.302825 | 2.19404 | 7.39388 | 1.33272 | 0.000684285 | 5.11721e-05 | 1.45935e-05 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13189.7 | 0.537359 | 754.883ms | 2866 | 2560 | 3174.35 | 207.225 | 0.0363942 | 0.451265 | 1.20237 | 0.187718 | 0.000350963 | 3.24385e-05 | 1.3357e-05 | 1(Win) | true |
| glaze | 3802.69 | 0.259114 | 814.793ms | 2866 | 1280 | 4439.79 | 718.763 | 0.0399065 | 1.40817 | 3.90963 | 0.714934 | 0.000876657 | 2.37155e-05 | 6.26963e-06 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17320.1 | 0.114468 | 752.356ms | 2866 | 1280 | 41.7665 | 157.807 | 0.450943 | 0.365597 | 1.02582 | 0.147942 | 0.000349464 | 1.71733e-05 | 9.54074e-06 | 1(Win) | true |
| glaze | 4274.57 | 0.210574 | 802.539ms | 2866 | 2560 | 4641.05 | 639.416 | 0.270937 | 1.2471 | 3.26378 | 0.570133 | 0.000353416 | 4.22518e-05 | 2.30341e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2425.01 | 0.0813526 | 910.739ms | 4390 | 2560 | 5049.93 | 1726.44 | 0.0520806 | 2.11354 | 9.87221 | 1.75216 | 0.00125774 | 0.000151 | 0.000102239 | 1(Win) | true |
| jsonifier (two-stage) | 1804.23 | 0.173975 | 974.564ms | 4390 | 40 | 651.895 | 2320.45 | 0.110013 | 2.79776 | 13.2358 | 2.29157 | 0.00191913 | 3.98633e-05 | 1.13895e-05 | 2(Loss) | true |
| glaze | 1726.3 | 0.107909 | 982.397ms | 4390 | 1280 | 8766.46 | 2425.21 | 0.0956696 | 2.97312 | 13.6825 | 2.66674 | 0.000867027 | 9.09382e-05 | 4.78716e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1324.06 | 0.0812969 | 1063.12ms | 4390 | 160 | 1057.26 | 3161.97 | 0.0259004 | 3.87018 | 16.5433 | 2.89954 | 0.00125 | 9.25399e-05 | 6.26424e-05 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2879.85 | 0.0380318 | 907.16ms | 4390 | 4890 | 1494.83 | 1453.77 | 0.0429209 | 1.79123 | 8.66059 | 1.46948 | 0.00126915 | 3.37726e-05 | 1.0947e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2054.98 | 0.058995 | 973.11ms | 4390 | 2560 | 3698.14 | 2037.31 | 0.00440973 | 2.47254 | 12.0232 | 2.00866 | 0.00185089 | 3.73719e-05 | 1.13895e-05 | 2(Loss) | true |
| glaze | 1969.63 | 0.141798 | 973.371ms | 4390 | 80 | 726.752 | 2125.59 | 0.203298 | 2.57027 | 12.1658 | 2.3328 | 0.000879841 | 2.2779e-05 | 8.54214e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1466.77 | 0.0490915 | 1047.82ms | 4390 | 2560 | 5026.41 | 2854.32 | 0.311029 | 3.45687 | 15.1362 | 2.58998 | 0.000662817 | 4.91173e-05 | 1.10336e-05 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10946.9 | 0.0983039 | 776.428ms | 4390 | 2560 | 361.846 | 382.447 | 0.00786526 | 0.504393 | 2.18405 | 0.374487 | 0.000280645 | 9.85905e-05 | 4.52022e-05 | 1(Win) | true |
| glaze | 3834.05 | 0.159579 | 852.634ms | 4390 | 4890 | 14848.2 | 1091.96 | 0.185412 | 1.35967 | 5.35034 | 0.83713 | 0.000468671 | 8.13338e-05 | 5.09151e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12087.1 | 0.148782 | 771.141ms | 4390 | 4890 | 1298.65 | 346.371 | 0.058586 | 0.461027 | 2.06879 | 0.348064 | 0.000228536 | 5.04493e-05 | 1.11799e-05 | 1(Win) | true |
| glaze | 3917.92 | 0.28091 | 846.41ms | 4390 | 2560 | 23067 | 1068.59 | 0.712036 | 1.32298 | 4.95558 | 0.749887 | 0.000471152 | 2.53595e-05 | 1.21903e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3428.72 | 0.0363769 | 1003.55ms | 9378 | 4890 | 4402.66 | 2608.42 | 0.0446162 | 1.47373 | 7.06185 | 1.13958 | 0.00110154 | 1.79029e-05 | 3.88151e-06 | 1(Win) | true |
| jsonifier | 2879.13 | 0.0458168 | 1055.22ms | 9378 | 2560 | 5185.44 | 3106.34 | 0.152642 | 1.76547 | 7.71199 | 1.56611 | 0.00301504 | 2.50753e-05 | 8.91381e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2576.72 | 0.0634578 | 1093.44ms | 9378 | 1280 | 6209.63 | 3470.91 | 0.0942218 | 1.94695 | 8.40958 | 1.39305 | 0.000594643 | 4.05704e-05 | 1.83275e-05 | 3(Loss) | true |
| glaze | 2362.42 | 0.0422156 | 1125.62ms | 9378 | 4890 | 12490 | 3785.76 | 0.0174672 | 2.13076 | 9.52028 | 1.88996 | 0.0027526 | 2.23732e-05 | 4.44847e-06 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3745.26 | 0.145834 | 1007.87ms | 9378 | 30 | 363.826 | 2387.97 | 0.0753212 | 1.34851 | 6.49424 | 1.00714 | 0.00125826 | 7.10884e-06 | 0 | 1(Win) | true |
| jsonifier | 3054.47 | 0.0776709 | 1063.56ms | 9378 | 160 | 827.534 | 2928.03 | 0.0115279 | 1.65188 | 7.14481 | 1.43399 | 0.00347156 | 9.9968e-06 | 1.99936e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2893.57 | 0.0350678 | 1071.73ms | 9378 | 4890 | 5744.84 | 3090.84 | 0.137282 | 1.74215 | 7.72393 | 1.2428 | 0.00031534 | 1.60712e-05 | 2.87842e-06 | 3(Loss) | true |
| glaze | 2570.75 | 0.129506 | 1111.49ms | 9378 | 40 | 811.974 | 3478.97 | 0.270204 | 1.95373 | 8.76786 | 1.72542 | 0.003135 | 1.33291e-05 | 7.99744e-06 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20262.4 | 0.252804 | 798.833ms | 11521 | 40 | 75.1667 | 542.25 | 0.163167 | 0.263966 | 0.99566 | 0.141654 | 8.6798e-05 | 6.50985e-06 | 0 | 1(Win) | true |
| glaze | 4728.83 | 0.209565 | 978.972ms | 11521 | 640 | 15173.7 | 2323.47 | 0.416246 | 1.0807 | 3.77971 | 0.682146 | 0.00112973 | 1.60034e-05 | 1.49184e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 22958.3 | 0.171059 | 788.154ms | 11521 | 80 | 53.6146 | 478.575 | 0.0836514 | 0.236235 | 0.9474 | 0.130371 | 8.6798e-05 | 1.08498e-06 | 0 | 1(Win) | true |
| glaze | 5307.99 | 0.141644 | 952.781ms | 11521 | 1280 | 11003.3 | 2069.95 | 0.460105 | 0.963386 | 3.54362 | 0.629806 | 0.00121653 | 4.3399e-06 | 1.15279e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2448.92 | 0.0396552 | 927.488ms | 4669 | 4890 | 2542.19 | 1818.23 | 0.0359141 | 2.07162 | 7.76333 | 1.54594 | 0.00108653 | 2.00163e-05 | 5.29972e-06 | 1(Win) | true |
| jsonifier (two-stage) | 1929.1 | 0.0698513 | 979.902ms | 4669 | 1280 | 3327.34 | 2308.18 | 0.106369 | 2.6222 | 10.8329 | 1.86121 | 0.00112962 | 2.72743e-05 | 7.36239e-06 | 2(Loss) | true |
| glaze | 1823.7 | 0.140217 | 986.665ms | 4669 | 40 | 468.815 | 2441.57 | 0.0446916 | 2.76682 | 9.72478 | 1.73592 | 0.000808524 | 0.000101735 | 2.67723e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1565.52 | 0.0511294 | 1034.57ms | 4669 | 2560 | 5413.91 | 2844.23 | 0.162278 | 3.21341 | 13.8576 | 1.99829 | 0.00133151 | 4.70189e-05 | 1.19639e-05 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2663.84 | 0.0219041 | 918.781ms | 4669 | 640 | 85.795 | 1671.54 | 0.0529732 | 1.90915 | 7.31377 | 1.4365 | 0.00126901 | 8.0317e-06 | 3.34654e-07 | 1(Win) | true |
| glaze | 2181.8 | 0.173033 | 954.057ms | 4669 | 640 | 7980.95 | 2040.84 | 0.130248 | 2.32052 | 8.95074 | 1.5635 | 0.000435385 | 1.23822e-05 | 2.00792e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 2048.87 | 0.0758338 | 973.051ms | 4669 | 1280 | 3476.6 | 2173.25 | 0.0108193 | 2.46801 | 10.3817 | 1.75155 | 0.00109248 | 1.42228e-05 | 2.00792e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1732.16 | 0.0694972 | 1012.63ms | 4669 | 1280 | 4085.23 | 2570.61 | 0.0535179 | 2.90716 | 13.0493 | 1.82395 | 0.00109465 | 3.01189e-05 | 3.84852e-06 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12655.3 | 0.0507895 | 779.456ms | 4669 | 640 | 20.4377 | 351.845 | 0.246185 | 0.438659 | 1.40051 | 0.357464 | 0.000214179 | 1.33862e-05 | 1.33862e-06 | 1(Win) | true |
| glaze | 3276.01 | 0.169002 | 883.864ms | 4669 | 1280 | 6753.9 | 1359.19 | 0.0611205 | 1.55896 | 3.17713 | 0.482116 | 0.000215852 | 2.84456e-05 | 6.69308e-07 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14124.2 | 0.0631547 | 776.412ms | 4669 | 2560 | 101.479 | 315.255 | 0.0589453 | 0.399507 | 1.28914 | 0.331763 | 0.00021443 | 4.72699e-05 | 1.49758e-05 | 1(Win) | true |
| glaze | 3751.64 | 0.241443 | 863.984ms | 4669 | 1280 | 10511 | 1186.87 | 0.0763488 | 1.36696 | 2.7085 | 0.37567 | 0.000249652 | 2.52664e-05 | 1.05416e-05 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2957.78 | 0.0529153 | 1005.33ms | 7932 | 4890 | 8955.84 | 2557.51 | 0.0327928 | 1.71267 | 7.09228 | 1.14813 | 0.000958531 | 1.93619e-05 | 3.55785e-06 | 1(Win) | true |
| simdjson (ondemand) | 2523.73 | 0.0802081 | 1044.08ms | 7932 | 80 | 462.386 | 2997.36 | 0.0154279 | 1.99386 | 8.68608 | 1.20008 | 0.000778492 | 2.20625e-05 | 1.5759e-06 | 2(Loss) | true |
| glaze | 2418.27 | 0.124773 | 1061.3ms | 7932 | 80 | 1218.68 | 3128.07 | 0.0199763 | 2.07957 | 8.62796 | 1.6059 | 0.00162002 | 6.30358e-06 | 0 | 3(Loss) | true |
| jsonifier | 2302.42 | 0.0942781 | 1079.94ms | 7932 | 640 | 6140.4 | 3285.47 | 0.00299606 | 2.18983 | 7.42095 | 1.63818 | 0.00151877 | 1.95017e-05 | 3.15179e-06 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3136.98 | 0.0645061 | 991.163ms | 7932 | 2560 | 6194.17 | 2411.41 | 0.109386 | 1.61386 | 6.82665 | 1.08359 | 0.000923278 | 1.68916e-05 | 6.59906e-06 | 1(Win) | true |
| simdjson (ondemand) | 2776.56 | 0.132933 | 1020.91ms | 7932 | 30 | 393.495 | 2724.43 | 0.246537 | 1.81483 | 8.21029 | 1.09745 | 0.000722811 | 2.94167e-05 | 4.20239e-06 | 2(Loss) | true |
| glaze | 2671.65 | 0.0581921 | 1036.74ms | 7932 | 2560 | 6949.82 | 2831.41 | 0.124444 | 1.88708 | 8.17196 | 1.50441 | 0.00158289 | 1.72364e-05 | 3.84124e-06 | 3(Loss) | true |
| jsonifier | 2392.33 | 0.0685542 | 1071.68ms | 7932 | 30 | 140.966 | 3162 | 0.0263477 | 2.10588 | 7.15608 | 1.57363 | 0.00155068 | 3.78215e-05 | 2.94167e-05 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 21413.1 | 0.0561089 | 780.18ms | 9249 | 4890 | 261.218 | 411.923 | 0.072133 | 0.258989 | 0.826576 | 0.182939 | 0.0001383 | 1.59195e-05 | 3.64821e-06 | 1(Win) | true |
| glaze | 3943.23 | 0.191111 | 967.918ms | 9249 | 1280 | 23391.8 | 2236.88 | 0.155875 | 1.29747 | 3.26424 | 0.619851 | 0.00036634 | 2.00191e-05 | 6.58855e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 23498.8 | 0.142716 | 776.631ms | 9249 | 2560 | 734.66 | 375.361 | 0.463642 | 0.235904 | 0.774138 | 0.170938 | 0.000108458 | 9.50272e-06 | 1.90054e-06 | 1(Win) | true |
| glaze | 4435.8 | 0.0976786 | 938.267ms | 9249 | 4890 | 18448.2 | 1988.49 | 0.0302082 | 1.15384 | 3.00551 | 0.560709 | 0.000358653 | 8.68938e-06 | 3.36078e-06 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 800.394 | 0.0283384 | 1298.5ms | 4604 | 4890 | 11817.4 | 5485.69 | 0.12778 | 6.25203 | 24.2417 | 5.34144 | 0.00499104 | 5.92532e-05 | 1.7545e-05 | 1(Win) | true |
| jsonifier (two-stage) | 737.555 | 0.104266 | 1346.75ms | 4604 | 160 | 6164.39 | 5953.07 | 0.0202668 | 6.87381 | 27.7921 | 5.77389 | 0.00667354 | 5.43006e-05 | 1.49327e-05 | 2(Loss) | true |
| glaze | 636.207 | 0.0680429 | 1429.48ms | 4604 | 160 | 3528.25 | 6901.39 | 0.122018 | 7.84659 | 33.0154 | 6.87185 | 0.00429382 | 0.00020227 | 0.000100456 | 3(Loss) | true |
| simdjson (ondemand) | 577.287 | 0.117454 | 1514.76ms | 4604 | 40 | 3192.13 | 7605.77 | 0.253875 | 8.81385 | 36.4555 | 6.65291 | 0.00623371 | 6.51607e-05 | 0 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 999.576 | 0.0384571 | 1287.41ms | 4604 | 640 | 1826.3 | 4392.58 | 0.0711632 | 5.10917 | 19.6848 | 4.30061 | 0.00453308 | 9.33292e-05 | 5.15856e-05 | 1(Win) | true |
| jsonifier (two-stage) | 888.383 | 0.0316567 | 1342.95ms | 4604 | 4890 | 11970.4 | 4942.37 | 0.04158 | 5.68237 | 23.553 | 4.80343 | 0.00551428 | 9.60754e-05 | 3.84657e-05 | 2(Loss) | true |
| glaze | 773.308 | 0.0573634 | 1409.39ms | 4604 | 1280 | 13578.3 | 5677.84 | 0.602956 | 6.50775 | 28.3877 | 5.80886 | 0.00440972 | 8.6881e-05 | 3.63135e-05 | 3(Loss) | true |
| simdjson (ondemand) | 649.671 | 0.0441897 | 1523.95ms | 4604 | 2560 | 22833.2 | 6758.37 | 0.0475563 | 7.72922 | 33.3094 | 5.92633 | 0.00483886 | 0.000217966 | 0.000140842 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1316.97 | 0.170903 | 1076.31ms | 4604 | 80 | 2597.21 | 3333.95 | 0.0651954 | 3.82467 | 9.39705 | 0.657689 | 0.000893245 | 2.71503e-05 | 0 | 1(Win) | true |
| glaze | 807.828 | 0.0565662 | 1291.49ms | 4604 | 2560 | 24198.4 | 5435.21 | 0.162491 | 6.25355 | 12.2687 | 1.00413 | 0.000548945 | 9.81653e-05 | 3.63984e-05 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1356 | 0.0392353 | 1070.43ms | 4604 | 4890 | 7892.46 | 3237.98 | 0.0589974 | 3.73889 | 9.27628 | 0.629019 | 0.000820617 | 4.43288e-05 | 1.3192e-05 | 1(Win) | true |
| glaze | 840.481 | 0.253711 | 1270.86ms | 4604 | 80 | 14053.4 | 5224.05 | 0.179137 | 6.06526 | 11.72 | 0.886186 | 0.000548436 | 3.52954e-05 | 0 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2596.18 | 0.0289472 | 1425.62ms | 18245 | 4890 | 18405.3 | 6702.08 | 0.153906 | 1.92632 | 7.99737 | 1.50436 | 0.00154778 | 2.37732e-05 | 1.08947e-05 | 1(Win) | true |
| jsonifier | 2228.85 | 0.0374321 | 1530.45ms | 18245 | 4890 | 41756.6 | 7806.64 | 0.0770829 | 2.24613 | 8.6261 | 1.94936 | 0.00208054 | 3.5912e-05 | 1.93907e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2094.02 | 0.0345652 | 1577.47ms | 18245 | 2560 | 21117.7 | 8309.29 | 0.124875 | 2.39888 | 10.0985 | 1.70902 | 0.00148776 | 2.33583e-05 | 8.67104e-06 | 3(Loss) | true |
| glaze | 1853.3 | 0.0336354 | 1687.33ms | 18245 | 2560 | 25528.7 | 9388.53 | 0.0939551 | 2.71546 | 11.5466 | 2.36213 | 0.00354877 | 1.92904e-05 | 7.06529e-06 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3019 | 0.15583 | 1429.64ms | 18245 | 30 | 2419.84 | 5763.43 | 0.0416592 | 1.65651 | 6.92886 | 1.25985 | 0.0013337 | 1.46159e-05 | 5.48095e-06 | 1(Win) | true |
| jsonifier | 2555.01 | 0.0842956 | 1533.52ms | 18245 | 640 | 21090.7 | 6810.06 | 0.016247 | 1.96717 | 7.55665 | 1.70447 | 0.0019448 | 1.05337e-05 | 2.39792e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2343.25 | 0.0759144 | 1575.16ms | 18245 | 320 | 10168.3 | 7425.5 | 0.127553 | 2.13135 | 9.34033 | 1.53322 | 0.000921485 | 1.25034e-05 | 5.13839e-06 | 3(Loss) | true |
| glaze | 2058.44 | 0.0383345 | 1696.07ms | 18245 | 2560 | 26880.1 | 8452.88 | 0.0832371 | 2.43958 | 10.4685 | 2.11368 | 0.00318604 | 2.1988e-05 | 9.18488e-06 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6943.12 | 0.149306 | 1086.03ms | 24579 | 160 | 4065.3 | 3376.06 | 0.239535 | 0.729577 | 1.9098 | 0.122137 | 8.39131e-05 | 5.59421e-06 | 0 | 1(Win) | true |
| glaze | 3954.85 | 0.0660505 | 1342.55ms | 24579 | 4890 | 74942.5 | 5926.98 | 0.097129 | 1.27669 | 3.55181 | 0.472111 | 0.000291136 | 2.75311e-05 | 1.28545e-05 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 7026.8 | 0.0469353 | 1079.6ms | 24579 | 4890 | 11987.3 | 3335.85 | 0.0345921 | 0.717258 | 1.89113 | 0.117784 | 0.000122837 | 9.38504e-06 | 2.70402e-06 | 1(Win) | true |
| glaze | 4364.42 | 0.0990337 | 1283.61ms | 24579 | 2560 | 72423.9 | 5370.78 | 0.302632 | 1.15324 | 3.40327 | 0.43765 | 0.000291709 | 2.31873e-05 | 1.20625e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 894.743 | 0.0323104 | 1238.29ms | 4604 | 4890 | 12293.3 | 4907.24 | 0.101212 | 5.63539 | 22.4668 | 4.96286 | 0.00506823 | 0.000125791 | 6.19627e-05 | 1(Win) | true |
| jsonifier (two-stage) | 790.7 | 0.0414249 | 1297.67ms | 4604 | 2560 | 13546 | 5552.95 | 0.071811 | 6.40456 | 26.9216 | 5.58124 | 0.00466425 | 0.000235614 | 0.000127691 | 2(Loss) | true |
| glaze | 671.883 | 0.0400316 | 1398.52ms | 4604 | 2560 | 17519.8 | 6534.95 | 0.0545148 | 7.46186 | 31.9767 | 6.64466 | 0.00580779 | 5.1331e-05 | 1.64599e-05 | 3(Loss) | true |
| simdjson (ondemand) | 595.194 | 0.0835053 | 1489.74ms | 4604 | 40 | 1517.89 | 7376.95 | 0.0729218 | 8.54287 | 35.3645 | 6.40758 | 0.00692876 | 7.05908e-05 | 1.08601e-05 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1109.22 | 0.048859 | 1235.4ms | 4604 | 2560 | 9575.49 | 3958.37 | 0.0473806 | 4.57096 | 18.2294 | 3.99153 | 0.00429484 | 3.66529e-05 | 6.78758e-06 | 1(Win) | true |
| jsonifier (two-stage) | 956.694 | 0.0360262 | 1302.17ms | 4604 | 4890 | 13368.1 | 4589.47 | 0.021825 | 5.30353 | 22.6811 | 4.60969 | 0.00402691 | 7.96853e-05 | 2.94933e-05 | 2(Loss) | true |
| glaze | 794.588 | 0.106158 | 1393.04ms | 4604 | 80 | 2752.83 | 5525.77 | 0.0271529 | 6.42316 | 27.8158 | 5.68527 | 0.00468343 | 0.000214487 | 7.87359e-05 | 3(Loss) | true |
| simdjson (ondemand) | 657.904 | 0.0585941 | 1518.32ms | 4604 | 1280 | 19573.3 | 6673.8 | 0.147963 | 7.6721 | 33.2539 | 5.90971 | 0.00435847 | 0.000146442 | 6.58395e-05 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1399.78 | 0.0444314 | 1053.14ms | 4604 | 4890 | 9498.19 | 3136.72 | 0.240379 | 3.62713 | 9.38858 | 0.65921 | 0.000477001 | 4.98366e-05 | 1.25702e-05 | 1(Win) | true |
| glaze | 814.712 | 0.0887861 | 1281.34ms | 4604 | 640 | 14653.2 | 5389.28 | 0.0158855 | 6.18547 | 12.2094 | 0.998697 | 0.000790074 | 2.98653e-05 | 6.78758e-06 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1431.75 | 0.318381 | 1047.49ms | 4604 | 40 | 3813.2 | 3066.68 | 0.0535611 | 3.55879 | 9.26781 | 0.630539 | 0.000792789 | 3.80104e-05 | 0 | 1(Win) | true |
| glaze | 779.513 | 0.0348189 | 1301.75ms | 4604 | 4890 | 18808.9 | 5632.64 | 0.304829 | 6.48234 | 11.7163 | 0.887056 | 0.00102645 | 5.8809e-05 | 1.42137e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2770.53 | 0.121332 | 1373.68ms | 18245 | 320 | 18580.9 | 6280.32 | 0.139775 | 1.82306 | 7.73719 | 1.44752 | 0.00131783 | 3.93944e-05 | 2.51781e-05 | 1(Win) | true |
| jsonifier | 2328.84 | 0.158046 | 1488.81ms | 18245 | 160 | 22309.9 | 7471.43 | 0.0281987 | 2.14401 | 8.34826 | 1.90052 | 0.00203378 | 2.50069e-05 | 1.64429e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2165.98 | 0.0293627 | 1552.24ms | 18245 | 4890 | 27206.8 | 8033.2 | 0.0511172 | 2.32874 | 9.78728 | 1.63924 | 0.00157133 | 2.14979e-05 | 9.06767e-06 | 3(Loss) | true |
| glaze | 1851.42 | 0.080274 | 1674.8ms | 18245 | 80 | 4553.23 | 9398.1 | 0.0305819 | 2.69186 | 11.225 | 2.28943 | 0.00400315 | 4.0422e-05 | 2.46643e-05 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3314.92 | 0.0898746 | 1368.44ms | 18245 | 40 | 890.174 | 5248.93 | 0.0799214 | 1.50962 | 6.66714 | 1.20236 | 0.0010222 | 2.32941e-05 | 9.59167e-06 | 1(Win) | true |
| jsonifier | 2733.72 | 0.0860212 | 1489.04ms | 18245 | 40 | 1199.09 | 6364.88 | 0.00405857 | 1.86286 | 7.27964 | 1.65574 | 0.00198685 | 1.50726e-05 | 2.74048e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2336.34 | 0.0518649 | 1588.4ms | 18245 | 1280 | 19097.3 | 7447.45 | 0.00405986 | 2.14526 | 9.37567 | 1.53976 | 0.00107645 | 1.69995e-05 | 5.73787e-06 | 3(Loss) | true |
| glaze | 2045.17 | 0.1022 | 1678.4ms | 18245 | 320 | 24192.7 | 8507.77 | 0.107333 | 2.43504 | 10.1983 | 2.05478 | 0.0037548 | 2.00397e-05 | 7.70759e-06 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 7463.04 | 0.110543 | 1062.57ms | 24579 | 640 | 7715.05 | 3140.86 | 0.112805 | 0.678164 | 1.9087 | 0.120876 | 9.54829e-05 | 6.42062e-06 | 1.65283e-06 | 1(Win) | true |
| glaze | 3647.45 | 0.0995069 | 1392.57ms | 24579 | 2560 | 104688 | 6426.51 | 0.093895 | 1.39391 | 3.55287 | 0.471216 | 0.000290295 | 4.92354e-05 | 3.27865e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 7450.43 | 0.244986 | 1061.62ms | 24579 | 80 | 4752.68 | 3146.18 | 0.137658 | 0.675137 | 1.89609 | 0.117865 | 9.81529e-05 | 7.1199e-06 | 1.01713e-06 | 1(Win) | true |
| glaze | 3973.39 | 0.0993917 | 1332.28ms | 24579 | 2560 | 88013 | 5899.34 | 0.310077 | 1.26249 | 3.41031 | 0.437813 | 0.00030053 | 1.9246e-05 | 8.32774e-06 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1748.88 | 0.0446852 | 1016.87ms | 5094 | 640 | 986.065 | 2777.79 | 0.391734 | 2.93009 | 13.1302 | 2.38614 | 0.00113185 | 2.72993e-05 | 3.06733e-06 | 1(Win) | true |
| jsonifier (two-stage) | 1556.92 | 0.0448269 | 1056.38ms | 5094 | 4890 | 9566.84 | 3120.27 | 0.0300104 | 3.23938 | 14.1496 | 2.52905 | 0.00139006 | 7.7761e-05 | 3.35211e-05 | 2(Loss) | true |
| glaze | 1274.19 | 0.0463538 | 1121.84ms | 5094 | 2560 | 7995.8 | 3812.64 | 0.0153911 | 3.97833 | 16.3441 | 3.16058 | 0.00423584 | 7.43829e-05 | 2.88329e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1152.21 | 0.0812277 | 1170.9ms | 5094 | 2560 | 30026.6 | 4216.27 | 0.0299339 | 4.3893 | 16.6781 | 2.84865 | 0.00467991 | 0.000191708 | 0.000111728 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2191.19 | 0.0502719 | 1019.41ms | 5094 | 2560 | 3180.15 | 2217.06 | 0.0938564 | 2.32625 | 10.6406 | 1.8192 | 0.000571751 | 3.87251e-05 | 9.04864e-06 | 1(Win) | true |
| jsonifier (two-stage) | 1912.19 | 0.056108 | 1058.82ms | 5094 | 4890 | 9936.03 | 2540.55 | 0.13593 | 2.65709 | 11.8954 | 2.00726 | 0.000943811 | 7.10568e-05 | 2.46491e-05 | 2(Loss) | true |
| glaze | 1644.06 | 0.0384022 | 1093.13ms | 5094 | 4890 | 6296.59 | 2954.9 | 0.475879 | 3.09178 | 12.9971 | 2.42167 | 0.0037133 | 6.43525e-05 | 2.88643e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1482.62 | 0.0742283 | 1127.88ms | 5094 | 1280 | 7571.99 | 3276.65 | 0.0404213 | 3.45272 | 13.7746 | 2.20259 | 0.00339815 | 8.03642e-05 | 4.04888e-05 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12098.4 | 0.108507 | 776.962ms | 5094 | 640 | 121.494 | 401.541 | 0.232157 | 0.452094 | 1.78661 | 0.303298 | 0.000196309 | 1.53367e-05 | 0 | 1(Win) | true |
| glaze | 3806.16 | 0.101115 | 867.512ms | 5094 | 4890 | 8144.78 | 1276.36 | 0.154961 | 1.35481 | 5.50648 | 0.906753 | 0.00039563 | 4.77325e-05 | 1.18428e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13678.1 | 0.281908 | 769.913ms | 5094 | 30 | 30.0747 | 355.167 | 0.159295 | 0.404293 | 1.67962 | 0.277581 | 0.000196309 | 1.30873e-05 | 0 | 1(Win) | true |
| glaze | 4140.06 | 0.207985 | 854.031ms | 5094 | 2560 | 15247.8 | 1173.42 | 0.0931642 | 1.24808 | 5.03514 | 0.800354 | 0.000561322 | 5.24514e-05 | 2.40786e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2302.83 | 0.14027 | 1077.34ms | 8051 | 40 | 874.917 | 3334.18 | 0.122569 | 2.18138 | 9.65408 | 1.64961 | 0.000732828 | 0.000102472 | 8.07353e-05 | 1(Win) | true |
| simdjson (ondemand) | 1751.82 | 0.0690304 | 1186.04ms | 8051 | 1280 | 11716.8 | 4382.88 | 0.441741 | 2.88109 | 11.0358 | 1.82437 | 0.00300603 | 0.000129351 | 7.11286e-05 | 2(Loss) | true |
| jsonifier | 1741.12 | 0.0766454 | 1186.66ms | 8051 | 640 | 7311.28 | 4409.82 | 0.128277 | 2.88436 | 11.2105 | 2.21699 | 0.00366996 | 4.65781e-05 | 2.11542e-05 | 3(Loss) | true |
| glaze | 1660.8 | 0.0844151 | 1205.07ms | 8051 | 2560 | 38989.1 | 4623.08 | 0.00645497 | 3.02712 | 13.289 | 2.57248 | 0.00293238 | 0.000113728 | 6.29289e-05 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2817.05 | 0.042123 | 1083.32ms | 8051 | 4890 | 6445.52 | 2725.55 | 0.239374 | 1.80378 | 8.2427 | 1.32232 | 0.000412071 | 2.77627e-05 | 9.62677e-06 | 1(Win) | true |
| simdjson (ondemand) | 2155.39 | 0.0996939 | 1161.23ms | 8051 | 160 | 2017.92 | 3562.24 | 0.0846712 | 2.3363 | 9.40442 | 1.45808 | 0.00216122 | 4.96833e-05 | 2.63942e-05 | 2(Loss) | true |
| glaze | 2071.99 | 0.0954221 | 1176.92ms | 8051 | 4890 | 61140.9 | 3705.63 | 0.0680432 | 2.44168 | 11.1677 | 2.10347 | 0.00294 | 7.49567e-05 | 3.81261e-05 | 3(Loss) | true |
| jsonifier | 1999.15 | 0.0361721 | 1188.62ms | 8051 | 2560 | 4940.8 | 3840.66 | 0.175179 | 2.52107 | 9.63483 | 1.85815 | 0.00352285 | 2.54239e-05 | 6.16189e-06 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20595 | 0.0581154 | 779.542ms | 9255 | 2560 | 158.801 | 428.564 | 0.246673 | 0.265722 | 1.07758 | 0.16456 | 0.00010805 | 2.50709e-05 | 1.13959e-05 | 1(Win) | true |
| glaze | 4089.08 | 0.0629218 | 959.977ms | 9255 | 4890 | 9020.13 | 2158.49 | 0.386448 | 1.24371 | 4.58768 | 0.845489 | 0.000268334 | 2.09692e-05 | 4.35292e-06 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 22919 | 0.177639 | 774.025ms | 9255 | 320 | 149.757 | 385.106 | 0.064875 | 0.239525 | 1.02247 | 0.152026 | 0.000108387 | 1.99217e-05 | 9.792e-06 | 1(Win) | true |
| glaze | 4720.04 | 0.0774615 | 925.889ms | 9255 | 4890 | 10259.9 | 1869.95 | 0.277325 | 1.08145 | 4.26072 | 0.770611 | 0.000279559 | 2.56756e-05 | 7.75571e-06 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5947.57 | 0.060324 | 781.6ms | 2889 | 4890 | 381.86 | 463.242 | 0.074039 | 0.919876 | 3.72344 | 0.427138 | 0.000729019 | 3.16411e-05 | 1.11133e-05 | 1(Win) | true |
| jsonifier | 5407.74 | 0.0592842 | 792.047ms | 2889 | 640 | 58.3879 | 509.486 | 0.78714 | 1.00928 | 3.84631 | 0.513673 | 0.000754478 | 6.49013e-06 | 0 | 2(Loss) | true |
| jsonifier (two-stage) | 5338.17 | 0.127306 | 789.867ms | 2889 | 4890 | 2111.14 | 516.125 | 0.0254264 | 1.00773 | 3.84631 | 0.513673 | 0.000771278 | 2.58367e-05 | 6.01676e-06 | 3(Loss) | true |
| glaze | 3317.97 | 0.0920976 | 820.631ms | 2889 | 2560 | 1497.23 | 830.377 | 0.145382 | 1.58801 | 6.31049 | 1.15853 | 0.000351684 | 2.04169e-05 | 7.43661e-06 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5986.24 | 0.200882 | 782.4ms | 2889 | 40 | 34.1923 | 460.25 | 0.278059 | 0.902579 | 3.64555 | 0.409484 | 0.000692281 | 2.59605e-05 | 0 | 1(Win) | true |
| jsonifier | 5715.52 | 0.174888 | 784.729ms | 2889 | 80 | 56.8582 | 482.05 | 0.0466975 | 0.961323 | 3.70197 | 0.480097 | 0.000830737 | 8.65351e-06 | 0 | 2(Loss) | true |
| jsonifier (two-stage) | 5667.59 | 0.0762802 | 786.477ms | 2889 | 4890 | 672.406 | 486.127 | 0.00844255 | 0.955876 | 3.70197 | 0.480097 | 0.00076066 | 2.49165e-05 | 7.14932e-06 | 3(Loss) | true |
| glaze | 3312.23 | 0.0740157 | 820.115ms | 2889 | 4890 | 1853.58 | 831.817 | 0.183454 | 1.5835 | 6.23434 | 1.14123 | 0.000348335 | 1.59267e-05 | 6.22911e-06 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7061.85 | 0.0605984 | 792.045ms | 3808 | 640 | 62.1526 | 514.255 | 0.0646756 | 0.765741 | 3.14575 | 0.339811 | 0.00052521 | 1.27199e-05 | 1.23096e-06 | 1(Win) | true |
| jsonifier (two-stage) | 6562.54 | 0.0836948 | 791.172ms | 3808 | 4890 | 1048.95 | 553.382 | 0.313141 | 0.82525 | 3.32379 | 0.398372 | 0.000293269 | 3.44233e-05 | 1.81514e-05 | 2(Loss) | true |
| jsonifier | 6355.89 | 0.181493 | 797.499ms | 3808 | 2560 | 2752.98 | 571.374 | 0.00369189 | 0.835628 | 3.32379 | 0.398372 | 0.000282506 | 3.7134e-05 | 1.9798e-05 | 3(Loss) | true |
| glaze | 3721.66 | 0.157304 | 839.096ms | 3808 | 80 | 188.491 | 975.8 | 0.2377 | 1.38815 | 6.03256 | 1.12447 | 0.000295431 | 1.96954e-05 | 0 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7289.13 | 0.0679058 | 788.505ms | 3808 | 640 | 73.255 | 498.22 | 0.0699854 | 0.747189 | 3.08666 | 0.326418 | 0.00052521 | 1.10787e-05 | 1.23096e-06 | 1(Win) | true |
| jsonifier (two-stage) | 6870.85 | 0.0788601 | 794.958ms | 3808 | 4890 | 849.566 | 528.551 | 0.940791 | 0.781848 | 3.21429 | 0.372899 | 0.000349227 | 2.2555e-05 | 5.85357e-06 | 2(Loss) | true |
| jsonifier | 6736.8 | 0.0996624 | 791.133ms | 3808 | 4890 | 1411.43 | 539.068 | 0.0818258 | 0.800586 | 3.21429 | 0.372899 | 0.000380858 | 2.29847e-05 | 5.74616e-06 | 3(Loss) | true |
| glaze | 3776.86 | 0.113244 | 837.816ms | 3808 | 2560 | 3035.29 | 961.538 | 0.332398 | 1.37525 | 5.97453 | 1.11135 | 0.000280249 | 1.92851e-05 | 8.82189e-06 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2502.97 | 0.0914383 | 857.03ms | 2889 | 2560 | 2593.46 | 1100.76 | 0.1152 | 2.06587 | 6.58706 | 1.13015 | 0.00183211 | 4.20507e-05 | 1.4062e-05 | 1(Win) | true |
| glaze | 2411.56 | 0.0710677 | 856.564ms | 2889 | 4890 | 3223.67 | 1142.48 | 0.0875625 | 2.13524 | 8.65317 | 1.49706 | 0.000413528 | 8.79862e-05 | 3.8932e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2157.74 | 0.18167 | 871.839ms | 2889 | 40 | 215.24 | 1276.88 | 0.225953 | 2.3866 | 8.84078 | 1.23607 | 0.00150571 | 7.78816e-05 | 2.59605e-05 | 3(Loss) | true |
| jsonifier (two-stage) | 2132.31 | 0.0558117 | 874.331ms | 2889 | 4890 | 2543.04 | 1292.1 | 0.038164 | 2.40886 | 8.3676 | 1.31983 | 0.000695042 | 5.64867e-05 | 1.80503e-05 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2807.1 | 0.205098 | 851.253ms | 2889 | 30 | 121.569 | 981.5 | 0.0849762 | 1.84337 | 5.99273 | 0.979232 | 0.00182301 | 9.23041e-05 | 4.61521e-05 | 1(Win) | true |
| glaze | 2720.62 | 0.118234 | 852.508ms | 2889 | 1280 | 1835.07 | 1012.7 | 0.139669 | 1.93371 | 7.96816 | 1.33022 | 0.000434028 | 0.000106817 | 6.16563e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2417.14 | 0.0963827 | 868.832ms | 2889 | 1280 | 1544.9 | 1139.85 | 0.0953166 | 2.13391 | 7.52683 | 1.11942 | 0.000696608 | 9.89746e-05 | 5.16507e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2372.83 | 0.120444 | 863.838ms | 2889 | 160 | 312.932 | 1161.13 | 0.0726134 | 2.21968 | 8.37868 | 1.12184 | 0.00120284 | 7.78816e-05 | 8.65351e-06 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8841.4 | 0.0355816 | 772.713ms | 2963 | 4890 | 63.2384 | 319.603 | 0.0390555 | 0.641911 | 1.48599 | 0.23996 | 0.000337496 | 5.36266e-05 | 1.50458e-05 | 1(Win) | true |
| glaze | 5215.33 | 0.130116 | 793.943ms | 2963 | 4890 | 2430.34 | 541.814 | 0.311662 | 1.03193 | 2.90922 | 0.46912 | 0.000338807 | 5.8872e-05 | 2.31899e-05 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10618.1 | 0.0720691 | 765.578ms | 2963 | 320 | 11.7712 | 266.125 | 0.124627 | 0.54465 | 1.30813 | 0.19946 | 0.000337496 | 3.37496e-05 | 0 | 1(Win) | true |
| glaze | 6023.39 | 0.105248 | 783.905ms | 2963 | 4890 | 1192.12 | 469.127 | 0.107911 | 0.905301 | 2.48127 | 0.378671 | 0.000337703 | 3.47158e-05 | 9.93853e-06 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2772.28 | 0.0620027 | 872.114ms | 3808 | 4890 | 3225.88 | 1309.96 | 0.212047 | 1.87184 | 7.0281 | 0.95352 | 0.000685995 | 5.16618e-05 | 1.23516e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2690.9 | 0.0766415 | 877.863ms | 3808 | 320 | 342.356 | 1349.58 | 0.0808773 | 1.93756 | 6.74632 | 1.01208 | 0.000558036 | 2.70811e-05 | 4.92384e-06 | 2(Loss) | true |
| glaze | 2639.45 | 0.0971416 | 880.48ms | 3808 | 80 | 142.911 | 1375.89 | 0.216662 | 1.97203 | 8.31985 | 1.47715 | 0.000548188 | 6.56513e-06 | 0 | 3(Loss) | true |
| jsonifier | 2082.47 | 0.0664 | 915.755ms | 3808 | 640 | 858.132 | 1743.89 | 0.109609 | 2.47547 | 6.7907 | 1.28099 | 0.000631893 | 8.20641e-05 | 4.47249e-05 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3025.54 | 0.100703 | 869.999ms | 3808 | 2560 | 3740.33 | 1200.31 | 0.586635 | 1.71331 | 6.10846 | 0.860032 | 0.000542751 | 4.00062e-05 | 1.21045e-05 | 1(Win) | true |
| simdjson (ondemand) | 2967.04 | 0.0694898 | 869.833ms | 3808 | 2560 | 1851.95 | 1223.98 | 0.270278 | 1.75021 | 6.67752 | 0.866859 | 0.000733755 | 6.05223e-05 | 2.54399e-05 | 2(Loss) | true |
| glaze | 2862.04 | 0.0871928 | 876.526ms | 3808 | 320 | 391.701 | 1268.88 | 0.228762 | 1.81777 | 7.80016 | 1.35058 | 0.000487461 | 2.62605e-05 | 8.20641e-07 | 3(Loss) | true |
| jsonifier | 2288.26 | 0.100061 | 909.726ms | 3808 | 640 | 1613.97 | 1587.05 | 0.142357 | 2.27434 | 6.33955 | 1.16649 | 0.000735294 | 3.73392e-05 | 1.39509e-05 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11486.1 | 0.0685654 | 771.746ms | 4300 | 640 | 38.3516 | 357.023 | 0.0617462 | 0.486212 | 1.15349 | 0.177674 | 0.000234375 | 1.09012e-05 | 3.99709e-06 | 1(Win) | true |
| glaze | 3023.94 | 0.139346 | 877.226ms | 4300 | 4890 | 17461.9 | 1356.11 | 0.427593 | 1.71938 | 3.39698 | 0.607442 | 0.000235935 | 5.97327e-05 | 1.99743e-05 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13170.4 | 0.0393477 | 768.262ms | 4300 | 320 | 4.8032 | 311.366 | 0.091415 | 0.4339 | 1.03581 | 0.15093 | 0.000236192 | 1.81686e-05 | 0 | 1(Win) | true |
| glaze | 3722.99 | 0.171707 | 846.303ms | 4300 | 4890 | 17491.8 | 1101.48 | 0.00617548 | 1.40379 | 2.85651 | 0.485814 | 0.000239787 | 1.97841e-05 | 6.37276e-06 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3556.41 | 0.0997448 | 6749.46ms | 466906 | 320 | 4.99075e+06 | 125204 | 0.133815 | 1.39102 | 6.27217 | 0.89185 | 0.00173124 | 0.00318921 | 1.8901e-05 | 1(Win) | true |
| glaze | 2545.93 | 0.0301379 | 9319.15ms | 466906 | 1280 | 3.55633e+06 | 174898 | 0.00147942 | 1.96805 | 7.42688 | 1.50352 | 0.00236112 | 0.00248891 | 1.06937e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1363.27 | 0.25871 | 8573.54ms | 466906 | 80 | 5.71234e+07 | 326625 | 0.250354 | 3.62591 | 14.6462 | 2.3563 | 0.00775713 | 0.0755256 | 1.23419e-05 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3580.04 | 0.0744537 | 6731.65ms | 466906 | 640 | 5.48829e+06 | 124378 | 0.0458913 | 1.38988 | 6.27098 | 0.891582 | 0.00158502 | 0.00302929 | 3.24276e-06 | 1(Win) | true |
| glaze | 2565.31 | 0.0883361 | 9259.45ms | 466906 | 80 | 1.88081e+06 | 173576 | 0.0215586 | 1.96515 | 7.4257 | 1.50325 | 0.0023588 | 0.00220938 | 1.60632e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1362.62 | 0.132988 | 8538.75ms | 466906 | 320 | 6.04342e+07 | 326780 | 0.0987113 | 3.64872 | 14.6466 | 2.35638 | 0.00772694 | 0.0838858 | 4.99364e-05 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4834.33 | 0.041607 | 7420.74ms | 699405 | 1280 | 4.2182e+06 | 137972 | 0.0140945 | 1.03917 | 3.88898 | 0.689049 | 0.00314443 | 0.000667699 | 3.12878e-06 | 1(Win) | true |
| glaze | 3623.54 | 0.0486742 | 9867.94ms | 699405 | 40 | 321107 | 184076 | 0.0491585 | 1.39458 | 4.84003 | 1.13546 | 0.00183506 | 0.000747528 | 9.75829e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1483.96 | 0.184492 | 6380.38ms | 767297 | 320 | 2.64844e+08 | 493108 | 0.0360776 | 3.34373 | 13.8534 | 2.1877 | 0.0108246 | 0.0746816 | 7.6486e-06 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4852.34 | 0.0961638 | 7447.73ms | 699405 | 160 | 2.79575e+06 | 137461 | 0.0561936 | 1.03526 | 3.88818 | 0.68887 | 0.00301714 | 0.000780896 | 2.226e-05 | 1(Win) | true |
| glaze | 3625.08 | 0.0281894 | 9796.81ms | 699405 | 1280 | 3.44354e+06 | 183997 | 0.0501728 | 1.38005 | 4.83925 | 1.13529 | 0.00186035 | 0.000671631 | 8.4201e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1464.48 | 0.160635 | 6446.27ms | 767297 | 640 | 4.12307e+08 | 499665 | 0.0286194 | 3.3748 | 13.8531 | 2.18763 | 0.0109053 | 0.0849825 | 4.27312e-05 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3600.5 | 0.0411669 | 8917.4ms | 631514 | 2560 | 1.21388e+07 | 167271 | 0.143588 | 1.37845 | 7.02252 | 1.20968 | 0.00350214 | 0.00014629 | 6.86037e-06 | 1(Win) | true |
| glaze | 2628.14 | 0.170919 | 6042.02ms | 631514 | 80 | 1.22727e+07 | 229158 | 0.525774 | 1.9007 | 8.57774 | 1.52634 | 0.00203081 | 3.74893e-05 | 8.51129e-07 | 2(Loss) | true |
