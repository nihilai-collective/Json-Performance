# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26200 using the MSVC 19.52.37029.0 compiler).  

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
*Environment generated via BenchmarkSuite commit: [71afc62](https://github.com/nihilai-collective/benchmarksuite/commit/71afc62)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 611.568 | 0.128668 | 142.346ms | 905 | 1280 | 4220.48 | 1411.25 | 0.132685 | 4.90461 | 1(Win) | true |
| Glaze | 601.45 | 0.121491 | 145.499ms | 905 | 4890 | 14862.6 | 1434.99 | 0.0986124 | 4.98487 | 2(Loss) | true |
| Jsonifier (two-stage) | 261.05 | 0.121694 | 330.361ms | 905 | 1280 | 20720.3 | 3306.17 | 0.0637604 | 11.5845 | 3(Loss) | true |
| simdjson (ondemand) | 122.106 | 0.0859617 | 703.471ms | 905 | 2560 | 94508.8 | 7068.24 | 0.0613816 | 24.8219 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 752.494 | 0.104402 | 117.652ms | 905 | 4890 | 7011.58 | 1146.95 | 0.184236 | 3.97627 | 1(Win) | true |
| Glaze | 732.05 | 0.190574 | 120.84ms | 905 | 1280 | 6461.83 | 1178.98 | 0.218196 | 4.08026 | 2(Loss) | true |
| Jsonifier (two-stage) | 277.628 | 0.121098 | 311.534ms | 905 | 1280 | 18140.7 | 3108.75 | 0.225666 | 10.8616 | 3(Loss) | true |
| simdjson (ondemand) | 126.908 | 0.0622202 | 680.778ms | 905 | 4890 | 87557.1 | 6800.8 | 0.188417 | 23.8873 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1121.47 | 0.118455 | 79.4409ms | 905 | 4890 | 4063.85 | 769.591 | 0.0331539 | 2.64683 | 1(Win) | true |
| Glaze | 86.6158 | 0.264432 | 1052.27ms | 905 | 2560 | 1.77735e+06 | 9964.41 | 0.0560903 | 35.0149 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1628.19 | 0.159757 | 60.2209ms | 905 | 4890 | 3506.85 | 530.082 | 0.0670605 | 1.80118 | 1(Win) | true |
| Glaze | 548.351 | 0.154275 | 173.585ms | 905 | 4890 | 28832.2 | 1573.95 | 0.057211 | 5.4752 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 793.463 | 0.360828 | 222.063ms | 1811 | 30 | 1850.57 | 2176.67 | 0.152905 | 3.77504 | 1(Win) | true |
| Jsonifier (two-stage) | 541.943 | 0.175271 | 336.701ms | 1811 | 320 | 9983.93 | 3186.88 | 0.472906 | 5.57065 | 2(Loss) | true |
| Glaze | 502.57 | 0.186348 | 350.89ms | 1811 | 4890 | 200540 | 3436.54 | 0.0425783 | 6.01225 | 3(Loss) | true |
| simdjson (ondemand) | 259.544 | 0.0650676 | 686.169ms | 1811 | 160 | 2999.61 | 6654.38 | 0.00939144 | 11.672 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1010.74 | 0.256249 | 173.465ms | 1811 | 160 | 3067.61 | 1708.75 | 0.0732064 | 2.94179 | 1(Win) | true |
| Jsonifier (two-stage) | 635.841 | 0.201261 | 286.149ms | 1811 | 80 | 2390.82 | 2716.25 | 0.138249 | 4.74433 | 2(Loss) | true |
| Glaze | 598.304 | 0.218675 | 299.25ms | 1811 | 30 | 1195.4 | 2886.67 | 0 | 4.99249 | 3(Loss) | true |
| simdjson (ondemand) | 281.746 | 0.117522 | 623.163ms | 1811 | 80 | 4151.9 | 6130 | 0.0814996 | 10.7308 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 417.002 | 0.095048 | 422.529ms | 1811 | 4890 | 75780.2 | 4141.72 | 0.0802087 | 7.25896 | 1(Win) | true |
| Glaze | 145.626 | 0.308596 | 1177.32ms | 1798 | 1280 | 1.69001e+06 | 11774.7 | 0.246099 | 20.8257 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 548.396 | 0.125896 | 326.669ms | 1811 | 160 | 2515.33 | 3149.38 | 0.0595711 | 5.48405 | 1(Win) | true |
| Glaze | 432.537 | 0.129087 | 417.918ms | 1798 | 2560 | 67040.5 | 3964.3 | 0.218272 | 6.99404 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1589.36 | 0.196473 | 239.344ms | 3862 | 640 | 13266.8 | 2317.34 | 0.208586 | 1.89482 | 1(Win) | true |
| Glaze | 946.05 | 0.104353 | 400.26ms | 3862 | 640 | 10563 | 3893.12 | 0.0320976 | 3.19546 | 2(Loss) | true |
| Jsonifier (two-stage) | 889.635 | 0.189484 | 430.386ms | 3862 | 40 | 2461.54 | 4140 | 0 | 3.39736 | 3(Loss) | true |
| simdjson (ondemand) | 565.216 | 0.256694 | 660.606ms | 3862 | 160 | 44765.7 | 6516.25 | 0 | 5.36255 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1954.38 | 0.216962 | 192.532ms | 3862 | 640 | 10699.3 | 1884.53 | 0.793916 | 1.52804 | 1(Win) | true |
| Glaze | 1100.02 | 0.119236 | 338.394ms | 3862 | 2560 | 40801.8 | 3348.2 | 0.107219 | 2.73702 | 2(Loss) | true |
| Jsonifier (two-stage) | 988.086 | 0.0681122 | 378.322ms | 3862 | 320 | 2062.7 | 3727.5 | 0.566856 | 3.04668 | 3(Loss) | true |
| simdjson (ondemand) | 617.968 | 0.152637 | 605.225ms | 3862 | 30 | 2482.76 | 5960 | 0.168067 | 4.89943 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 398.482 | 0.0781253 | 919.96ms | 3862 | 2560 | 133485 | 9242.81 | 0.0160624 | 7.60982 | 1(Win) | true |
| Glaze | 380.878 | 0.106317 | 991.419ms | 3862 | 80 | 8455.7 | 9670 | 0.10352 | 7.95987 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3911.63 | 0.10556 | 110.687ms | 3862 | 4890 | 4830.82 | 941.575 | 0.189189 | 0.755385 | 1(Win) | true |
| Glaze | 1653.25 | 0.0955348 | 256.656ms | 3862 | 4890 | 22150.4 | 2227.79 | 0.332984 | 1.81835 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 833.665 | 0.167313 | 1100.81ms | 9578 | 1280 | 430165 | 10956.8 | 0.249467 | 3.63801 | 1(Win) | true |
| Glaze | 707.862 | 0.148263 | 1312.28ms | 9578 | 320 | 117131 | 12904.1 | 0.591961 | 4.28565 | 2(Loss) | true |
| Jsonifier (two-stage) | 700.894 | 0.0726022 | 1309.04ms | 9578 | 2560 | 229184 | 13032.3 | 0.148448 | 4.32837 | 3(Loss) | true |
| simdjson (ondemand) | 671.585 | 0.104433 | 1361.37ms | 9578 | 1280 | 258247 | 13601.1 | 0.101197 | 4.51717 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1299.39 | 0.119274 | 908.059ms | 9578 | 1280 | 89985.8 | 7029.69 | 0.00889166 | 2.33121 | 1(Win) | true |
| Glaze | 1001.29 | 0.257511 | 1130.42ms | 9578 | 160 | 88295.6 | 9122.5 | 0.495731 | 3.02673 | 2(Loss) | true |
| Jsonifier (two-stage) | 986.458 | 0.0723743 | 1140.66ms | 9578 | 2560 | 114975 | 9259.69 | 0.027006 | 3.07317 | 3(Loss) | true |
| simdjson (ondemand) | 950.004 | 0.632578 | 1183.13ms | 9578 | 40 | 147974 | 9615 | 0.0867453 | 3.18925 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1164.16 | 0.315742 | 802.394ms | 9578 | 80 | 49099.7 | 7846.25 | 0.0159337 | 2.6032 | 1(Win) | true |
| Glaze | 887.356 | 0.227718 | 1046.11ms | 9578 | 1280 | 703332 | 10293.8 | 0.0462745 | 3.41755 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8332.31 | 0.342075 | 128.461ms | 9578 | 80 | 1125 | 1096.25 | 0.340909 | 0.35797 | 1(Win) | true |
| Glaze | 3433.94 | 0.294911 | 286.048ms | 9578 | 40 | 2461.54 | 2660 | 0.25 | 0.874572 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1671.3 | 0.252075 | 235.284ms | 3873 | 30 | 931.034 | 2210 | 0 | 1.80083 | 1(Win) | true |
| Glaze | 1000.21 | 0.110772 | 374.882ms | 3873 | 1280 | 21418.2 | 3692.81 | 0.0676533 | 3.02202 | 2(Loss) | true |
| Jsonifier (two-stage) | 913.581 | 0.116087 | 415.874ms | 3873 | 640 | 14097.6 | 4042.97 | 0.0270458 | 3.31018 | 3(Loss) | true |
| simdjson (ondemand) | 560.27 | 0.0843655 | 668.674ms | 3873 | 80 | 2474.68 | 6592.5 | 0.0757863 | 5.41057 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1894.14 | 0.410585 | 189.734ms | 3873 | 40 | 2564.1 | 1950 | 0.340716 | 1.58105 | 1(Win) | true |
| Glaze | 1148.58 | 0.126901 | 339.71ms | 3873 | 640 | 10658.2 | 3215.78 | 0.179455 | 2.61557 | 2(Loss) | true |
| Jsonifier (two-stage) | 1028.07 | 0.127185 | 367.203ms | 3873 | 1280 | 26725.9 | 3592.73 | 0.15463 | 2.93796 | 3(Loss) | true |
| simdjson (ondemand) | 597.928 | 0.0572113 | 624.323ms | 3873 | 4890 | 61076 | 6177.3 | 0.193193 | 5.06436 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 406.99 | 0.0661996 | 914.534ms | 3873 | 2560 | 92401.2 | 9075.35 | 0.0650363 | 7.45008 | 1(Win) | true |
| Glaze | 368.022 | 0.149307 | 1006.11ms | 3873 | 4890 | 1.09803e+06 | 10036.3 | 0.268517 | 8.2397 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4484.29 | 0.14747 | 98.0336ms | 3873 | 2560 | 3777.06 | 823.672 | 0.160985 | 0.657493 | 1(Win) | true |
| Glaze | 1705.43 | 0.089624 | 244.671ms | 3873 | 2560 | 9645.34 | 2165.78 | 0.0866489 | 1.76291 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 816.41 | 0.258653 | 5658.98ms | 94653 | 2560 | 2.09377e+08 | 110567 | 0.381842 | 3.72183 | 1(Win) | true |
| Jsonifier (two-stage) | 770.174 | 0.200734 | 6013.4ms | 94653 | 2560 | 1.41701e+08 | 117205 | 0.703938 | 3.94537 | 2(Loss) | true |
| Glaze | 758.357 | 0.5598 | 6057.68ms | 94653 | 1280 | 5.68325e+08 | 119031 | 0.126317 | 4.00692 | 3(Loss) | true |
| simdjson (ondemand) | 641.181 | 0.17615 | 7198.61ms | 94653 | 2560 | 1.57439e+08 | 140784 | 0.204792 | 4.73935 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1253.13 | 0.079312 | 8989.8ms | 94653 | 640 | 2.08898e+06 | 72034.1 | 0.392796 | 2.42462 | 1(Win) | true |
| Glaze | 1161.61 | 0.0968919 | 9508.13ms | 94653 | 4890 | 2.77226e+07 | 77709.6 | 0.0769971 | 2.61554 | 2(Loss) | true |
| Jsonifier (two-stage) | 1134.01 | 0.0892537 | 9744.44ms | 94653 | 320 | 1.61523e+06 | 79600.6 | 0.0212041 | 2.67924 | 3(Loss) | true |
| simdjson (ondemand) | 867.371 | 0.108202 | 6123.8ms | 94653 | 640 | 8.1154e+06 | 104071 | 0.0426574 | 3.5032 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12237 | 0.124743 | 747.093ms | 94653 | 30 | 2540.23 | 7376.67 | 0.0904568 | 0.247515 | 1(Win) | true |
| Glaze | 4116.66 | 0.0909031 | 2218.34ms | 94653 | 320 | 127141 | 21927.5 | 0.298389 | 0.737561 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12188.2 | 0.114068 | 745.429ms | 94653 | 1280 | 91353.6 | 7406.17 | 0.144308 | 0.247987 | 1(Win) | true |
| Glaze | 4540.61 | 0.0714266 | 1991.38ms | 94653 | 1280 | 258089 | 19880.2 | 0.287701 | 0.668123 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1013.35 | 0.142309 | 5996.28ms | 124597 | 2560 | 7.12863e+07 | 117260 | 0.150634 | 2.99869 | 1(Win) | true |
| Jsonifier | 992.938 | 0.159842 | 6099.11ms | 124597 | 2560 | 9.36689e+07 | 119670 | 0.216622 | 3.06027 | 2(Loss) | true |
| Glaze | 910.792 | 0.251776 | 6681.28ms | 124597 | 1280 | 1.38107e+08 | 130463 | 0.032467 | 3.33626 | 3(Loss) | true |
| simdjson (ondemand) | 840.422 | 0.316165 | 7239.1ms | 124597 | 320 | 6.39437e+07 | 141387 | 0.0134843 | 3.61589 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1451.48 | 0.0616236 | 5049.81ms | 124597 | 640 | 1.6288e+06 | 81864.7 | 0.0951406 | 2.09331 | 1(Win) | true |
| Jsonifier | 1426.07 | 0.0344941 | 5130.52ms | 124597 | 2560 | 2.11478e+06 | 83323.6 | 0.0078753 | 2.13064 | 2(Loss) | true |
| Glaze | 1284 | 0.0398191 | 5623.7ms | 124597 | 1280 | 1.73812e+06 | 92543 | 0.0019417 | 2.36631 | 3(Loss) | true |
| simdjson (ondemand) | 1126.12 | 0.0850901 | 6194.94ms | 124597 | 320 | 2.57963e+06 | 105518 | 0.00355404 | 2.69848 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12221.8 | 0.16137 | 1064.16ms | 136037 | 2560 | 751157 | 10615 | 0.0887648 | 0.248107 | 1(Win) | true |
| Glaze | 4572.34 | 0.154594 | 2846.48ms | 136076 | 4890 | 9.41415e+06 | 28382 | 0.11572 | 0.664107 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12575.3 | 0.0522794 | 1035.1ms | 136037 | 4890 | 142250 | 10316.7 | 0.130113 | 0.240762 | 1(Win) | true |
| Glaze | 5056.29 | 0.0626334 | 2578.47ms | 136076 | 2560 | 661534 | 25665.5 | 0.0418371 | 0.600081 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 562.41 | 0.838557 | 5697.88ms | 2251027 | 40 | 4.09808e+10 | 3.81705e+06 | 0.0307487 | 5.40396 | 1(Win) | true |
| Jsonifier | 543.829 | 1.05922 | 5904.76ms | 2251027 | 30 | 5.24486e+10 | 3.94747e+06 | 0.0451563 | 5.58867 | 2(Loss) | true |
| simdjson (ondemand) | 373.465 | 0.423128 | 8673.08ms | 2251027 | 30 | 1.7747e+10 | 5.74818e+06 | 0.0892091 | 8.1382 | 3(Loss) | true |
| Glaze | 352.781 | 0.413499 | 9065.65ms | 2251027 | 40 | 2.53256e+10 | 6.0852e+06 | 0.324079 | 8.61547 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 652.729 | 0.402055 | 5703.49ms | 2251027 | 80 | 1.3988e+10 | 3.28888e+06 | 0.181508 | 4.65607 | 1(Win) | true |
| Jsonifier | 628.37 | 0.598711 | 5893.95ms | 2251027 | 80 | 3.34699e+10 | 3.41637e+06 | 0.0419494 | 4.83668 | 2(Loss) | true |
| simdjson (ondemand) | 412.016 | 0.321618 | 8583ms | 2251027 | 30 | 8.42433e+09 | 5.21035e+06 | 0.380225 | 7.37677 | 3(Loss) | true |
| Glaze | 386.922 | 0.330626 | 9039.51ms | 2251027 | 80 | 2.69201e+10 | 5.54826e+06 | 0.37584 | 7.85526 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1177.06 | 0.149041 | 5276.39ms | 2090234 | 30 | 1.91127e+08 | 1.69354e+06 | 0.237203 | 2.58183 | 1(Win) | true |
| Glaze | 853.706 | 0.11487 | 7287.49ms | 2090234 | 30 | 2.15829e+08 | 2.335e+06 | 0.27476 | 3.55992 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1410.95 | 0.465362 | 8868.63ms | 2090234 | 320 | 1.38324e+10 | 1.41281e+06 | 0.0277959 | 2.15387 | 1(Win) | true |
| Glaze | 1144.08 | 0.104407 | 5427.43ms | 2090234 | 30 | 9.92796e+07 | 1.74236e+06 | 0.117987 | 2.65644 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1248.74 | 0.666792 | 6148.13ms | 5373214 | 40 | 2.99477e+10 | 4.10357e+06 | 0.103036 | 2.43383 | 1(Win) | true |
| Jsonifier | 1148.59 | 0.580603 | 6652.99ms | 5373214 | 80 | 5.36766e+10 | 4.46137e+06 | 0.155791 | 2.64607 | 2(Loss) | true |
| simdjson (ondemand) | 861.886 | 0.400206 | 9049.3ms | 5373214 | 30 | 1.69847e+10 | 5.94545e+06 | 1.27915 | 3.52636 | 3(Loss) | true |
| Glaze | 774.151 | 0.502007 | 9973.36ms | 5373214 | 30 | 3.31252e+10 | 6.61924e+06 | 0.284019 | 3.92601 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1426.73 | 0.653823 | 6155.79ms | 5373214 | 80 | 4.4116e+10 | 3.59164e+06 | 0.239046 | 2.13013 | 1(Win) | true |
| Jsonifier | 1321.07 | 0.621342 | 6643.12ms | 5373214 | 30 | 1.7426e+10 | 3.87889e+06 | 0.602317 | 2.30053 | 2(Loss) | true |
| simdjson (ondemand) | 939.727 | 0.123664 | 9008.72ms | 5373214 | 40 | 1.81891e+09 | 5.45296e+06 | 0.234185 | 3.23395 | 3(Loss) | true |
| Glaze | 827.318 | 0.398433 | 9969.19ms | 5373214 | 80 | 4.87218e+10 | 6.19386e+06 | 0.888597 | 3.67371 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2685.13 | 0.0657978 | 7349.45ms | 6661897 | 80 | 1.939e+08 | 2.36609e+06 | 0.168085 | 1.13183 | 1(Win) | true |
| Glaze | 1421.67 | 0.620412 | 6690.18ms | 6661897 | 40 | 3.07483e+10 | 4.46889e+06 | 0.81755 | 2.13779 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4090.26 | 0.0587648 | 9791.65ms | 6661897 | 320 | 2.66611e+08 | 1.55327e+06 | 0.0729179 | 0.742941 | 1(Win) | true |
| Glaze | 3097.13 | 0.0832745 | 6372.35ms | 6661897 | 160 | 4.66898e+08 | 2.05134e+06 | 0.0530421 | 0.981244 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1519.79 | 0.209248 | 8017.17ms | 500299 | 40 | 1.72614e+07 | 313940 | 0.139958 | 1.99976 | 1(Win) | true |
| Jsonifier (two-stage) | 1250.38 | 0.114022 | 9783.47ms | 500299 | 1280 | 2.42306e+08 | 381583 | 0.246531 | 2.4304 | 2(Loss) | true |
| Glaze | 821.285 | 0.143724 | 7385.62ms | 500299 | 160 | 1.11545e+08 | 580946 | 0.3262 | 3.70065 | 3(Loss) | true |
| simdjson (ondemand) | 540.675 | 0.314876 | 5602.74ms | 500299 | 30 | 2.31625e+08 | 882457 | 0.288885 | 5.62124 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1787.59 | 0.148685 | 7738.81ms | 500299 | 160 | 2.51987e+07 | 266908 | 0.00749379 | 1.70011 | 1(Win) | true |
| Jsonifier (two-stage) | 1439.8 | 0.0900824 | 9422.89ms | 500299 | 320 | 2.85156e+07 | 331380 | 0.0298085 | 2.11073 | 2(Loss) | true |
| Glaze | 926.524 | 0.106432 | 7032.57ms | 500299 | 160 | 4.80627e+07 | 514959 | 0.0651326 | 3.28033 | 3(Loss) | true |
| simdjson (ondemand) | 606.8 | 0.12444 | 5195.76ms | 500299 | 320 | 3.06363e+08 | 786293 | 0.182288 | 5.00872 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8616.69 | 0.116147 | 5559.49ms | 500299 | 160 | 661783 | 55371.9 | 0.0734214 | 0.352624 | 1(Win) | true |
| Glaze | 4182.96 | 0.156623 | 5835.27ms | 500299 | 1280 | 4.08519e+07 | 114063 | 0.179607 | 0.726441 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8672.19 | 0.127352 | 5521.93ms | 500299 | 160 | 785478 | 55017.5 | 0.0953332 | 0.350329 | 1(Win) | true |
| Glaze | 4650.66 | 0.0654835 | 5241.54ms | 500299 | 2560 | 1.1554e+07 | 102592 | 0.137719 | 0.653264 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2571.66 | 0.0926356 | 5443.09ms | 1151920 | 320 | 5.01098e+07 | 427178 | 0.131943 | 1.18173 | 1(Win) | true |
| Jsonifier | 2329.06 | 0.0469882 | 6024.94ms | 1151920 | 640 | 3.14369e+07 | 471673 | 0.0234483 | 1.30486 | 2(Loss) | true |
| Glaze | 1517.91 | 0.205844 | 9205.69ms | 1151920 | 40 | 8.8775e+07 | 723730 | 0.0138154 | 2.00227 | 3(Loss) | true |
| simdjson (ondemand) | 1198.38 | 0.12097 | 5822.96ms | 1151920 | 160 | 1.96758e+08 | 916702 | 0.00852167 | 2.53608 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2919.87 | 0.0968036 | 5280.37ms | 1151920 | 40 | 5.30592e+06 | 376235 | 0.0482621 | 1.04078 | 1(Win) | true |
| Jsonifier | 2616.93 | 0.0587842 | 5822.71ms | 1151920 | 160 | 9.74319e+06 | 419788 | 0.0206992 | 1.16134 | 2(Loss) | true |
| Glaze | 1657.63 | 0.0831295 | 8900.04ms | 1151920 | 160 | 4.85622e+07 | 662726 | 0.163074 | 1.83352 | 3(Loss) | true |
| simdjson (ondemand) | 1324.41 | 0.224761 | 5416.89ms | 1151920 | 80 | 2.78055e+08 | 829466 | 0.383792 | 2.29468 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4429.59 | 0.105088 | 7985.73ms | 1439562 | 1280 | 1.35785e+08 | 309932 | 0.0911918 | 0.685709 | 1(Win) | true |
| Glaze | 1934.77 | 0.12865 | 9060.79ms | 1439584 | 160 | 1.33338e+08 | 709591 | 0.271688 | 1.57047 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13054.8 | 0.0621651 | 5370.72ms | 1439562 | 640 | 2.73522e+06 | 105162 | 0.0910137 | 0.232629 | 1(Win) | true |
| Glaze | 7340.75 | 0.120596 | 9622.67ms | 1439584 | 1280 | 6.51132e+07 | 187024 | 0.394675 | 0.413905 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1188.26 | 0.0234004 | 4528.85ms | 56369 | 4890 | 548043 | 45240.7 | 0.0142766 | 2.55631 | 1(Win) | true |
| Glaze | 1061.89 | 0.0332536 | 5069.32ms | 56369 | 4890 | 1.38581e+06 | 50624.3 | 0.0628886 | 2.86082 | 2(Loss) | true |
| Jsonifier (two-stage) | 968.369 | 0.0475096 | 5543.67ms | 56369 | 1280 | 890370 | 55513.6 | 0.00281471 | 3.13734 | 3(Loss) | true |
| simdjson (ondemand) | 700.974 | 0.204944 | 7692.35ms | 56369 | 160 | 3.95248e+06 | 76690 | 0.122395 | 4.33471 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1776.09 | 0.0490487 | 3523.1ms | 56369 | 1280 | 282107 | 30267.3 | 0.057269 | 1.71014 | 1(Win) | true |
| Glaze | 1626.52 | 0.14944 | 3730.16ms | 56369 | 160 | 390314 | 33050.6 | 0.0662302 | 1.86729 | 2(Loss) | true |
| Jsonifier (two-stage) | 1350.92 | 0.0478122 | 4467.26ms | 56369 | 1280 | 463348 | 39793.3 | 0.062471 | 2.24851 | 3(Loss) | true |
| simdjson (ondemand) | 900.805 | 0.0885536 | 6411.39ms | 56369 | 640 | 1.78736e+06 | 59677.3 | 0.102269 | 3.37261 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11190.8 | 0.0864023 | 482.058ms | 56369 | 80 | 1378.16 | 4803.75 | 0.234742 | 0.269656 | 1(Win) | true |
| Glaze | 4143.27 | 0.133234 | 1306.12ms | 56369 | 640 | 191252 | 12974.7 | 0.338454 | 0.73206 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11952.1 | 0.0885931 | 454.729ms | 56369 | 2560 | 40647.6 | 4497.77 | 0.0338824 | 0.252385 | 1(Win) | true |
| Glaze | 4613.46 | 0.0891229 | 1162.6ms | 56369 | 2560 | 276087 | 11652.3 | 0.36877 | 0.656119 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1425.88 | 0.0442312 | 5616.45ms | 83958 | 1280 | 789633 | 56153.8 | 0.0959503 | 2.13072 | 1(Win) | true |
| Jsonifier | 1330.43 | 0.0462325 | 6021.81ms | 83958 | 1280 | 990942 | 60182.7 | 0.0914721 | 2.28346 | 2(Loss) | true |
| Glaze | 1321.27 | 0.0550568 | 6072.43ms | 83958 | 1280 | 1.42486e+06 | 60599.7 | 0.0378881 | 2.2994 | 3(Loss) | true |
| simdjson (ondemand) | 1032.14 | 0.0642393 | 7760.03ms | 83958 | 4890 | 1.21439e+07 | 77575.4 | 0.0701868 | 2.94344 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1941.49 | 0.038968 | 4609.1ms | 83958 | 2560 | 661164 | 41240.7 | 0.0322146 | 1.56451 | 1(Win) | true |
| Glaze | 1886.04 | 0.0469063 | 4704.75ms | 83958 | 2560 | 1.01514e+06 | 42453.2 | 0.00910846 | 1.61051 | 2(Loss) | true |
| Jsonifier | 1776.3 | 0.027243 | 4987.86ms | 83958 | 4890 | 737414 | 45076 | 0.040028 | 1.71013 | 3(Loss) | true |
| simdjson (ondemand) | 1306.17 | 0.0334154 | 6559.06ms | 83958 | 4890 | 2.05177e+06 | 61300.4 | 0.081663 | 2.32608 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11832.6 | 0.20368 | 759.603ms | 94370 | 320 | 76798.5 | 7605.94 | 0.168738 | 0.256142 | 1(Win) | true |
| Glaze | 3836.45 | 0.35703 | 2283.77ms | 94370 | 80 | 561188 | 23458.8 | 0.271017 | 0.790861 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12390.6 | 0.0937737 | 728.732ms | 94370 | 4890 | 226857 | 7263.42 | 0.0508087 | 0.244066 | 1(Win) | true |
| Glaze | 4553.85 | 0.116865 | 1974.61ms | 94370 | 4890 | 2.6085e+06 | 19763.1 | 0.122121 | 0.665856 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 955.349 | 0.211157 | 5431.27ms | 53331 | 40 | 505481 | 53237.5 | 0.0454147 | 3.17908 | 1(Win) | true |
| Glaze | 916.28 | 0.172757 | 5556.13ms | 53331 | 80 | 735639 | 55507.5 | 0.0675128 | 3.31536 | 2(Loss) | true |
| Jsonifier (two-stage) | 859.274 | 0.477261 | 5942.43ms | 53331 | 30 | 2.39403e+06 | 59190 | 0.02815 | 3.53445 | 3(Loss) | true |
| simdjson (ondemand) | 667.585 | 0.0986901 | 7689.03ms | 53331 | 160 | 904509 | 76185.6 | 0.148266 | 4.55155 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1381.89 | 0.0763032 | 4383.26ms | 53331 | 640 | 504750 | 36804.8 | 0.252386 | 2.19783 | 1(Win) | true |
| Glaze | 1330.68 | 0.0449885 | 4514.47ms | 53331 | 1280 | 378467 | 38221.5 | 0.296115 | 2.28253 | 2(Loss) | true |
| Jsonifier (two-stage) | 1222.22 | 0.0552148 | 4845.16ms | 53331 | 1280 | 675741 | 41613 | 0.289394 | 2.48463 | 3(Loss) | true |
| simdjson (ondemand) | 845.861 | 0.0688451 | 6577.89ms | 53331 | 4890 | 8.37947e+06 | 60128.6 | 0.0541594 | 3.59157 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11472.2 | 0.0835064 | 491.402ms | 58581 | 2560 | 42335.2 | 4869.8 | 0.0793485 | 0.263555 | 1(Win) | true |
| Glaze | 5377.66 | 0.405576 | 1065.11ms | 58581 | 80 | 142024 | 10388.8 | 0.0841548 | 0.563498 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12325.9 | 0.165472 | 457.196ms | 58581 | 40 | 2250 | 4532.5 | 0.128866 | 0.244106 | 1(Win) | true |
| Glaze | 6306.61 | 0.346476 | 888.145ms | 58581 | 1280 | 1.20581e+06 | 8858.52 | 0.027347 | 0.479578 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1023 | 0.141065 | 6111.13ms | 65103 | 80 | 586378 | 60691.2 | 0.154232 | 2.96886 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 1001.55 | 0.514259 | 6274.55ms | 65103 | 640 | 6.50433e+07 | 61991.1 | 0.102983 | 3.03266 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 993.681 | 0.195226 | 6456.5ms | 65103 | 4890 | 7.27599e+07 | 62481.9 | 1.11906 | 3.05717 | 2(Tie) | true |
| simdjson (ondemand) | 807.856 | 0.171825 | 7682.92ms | 65103 | 1280 | 2.23212e+07 | 76854.1 | 0.0703964 | 3.76105 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1444.21 | 0.0506545 | 5003.28ms | 65103 | 1280 | 606999 | 42990.4 | 0.0154492 | 2.10276 | 1(Win) | true |
| Glaze | 1408.64 | 0.0865209 | 5073.6ms | 65103 | 640 | 930727 | 44075.8 | 0.0527931 | 2.15644 | 2(Loss) | true |
| Jsonifier | 1372.59 | 0.0656654 | 5239.5ms | 65103 | 1280 | 1.12928e+06 | 45233.4 | 0.104728 | 2.21298 | 3(Loss) | true |
| simdjson (ondemand) | 1027.94 | 0.114406 | 6624.32ms | 65103 | 320 | 1.52796e+06 | 60399.4 | 0.0227703 | 2.9556 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10877.7 | 0.0965251 | 698.779ms | 78778 | 30 | 1333.33 | 6906.67 | 0.0482859 | 0.27846 | 1(Win) | true |
| Glaze | 3336 | 0.17315 | 2260.04ms | 78778 | 4890 | 7.43554e+06 | 22520.6 | 0.6709 | 0.910017 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11099.1 | 0.0691834 | 679.827ms | 78778 | 2560 | 56141 | 6768.91 | 0.0472988 | 0.272225 | 1(Win) | true |
| Glaze | 3947.32 | 0.473696 | 1963.69ms | 78778 | 640 | 5.20218e+06 | 19032.8 | 0.744761 | 0.768062 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1335.99 | 0.092057 | 847.139ms | 11812 | 1280 | 77119.5 | 8431.8 | 0.191429 | 2.2701 | 1(Win) | true |
| Jsonifier (two-stage) | 1167.28 | 0.0647608 | 969.668ms | 11812 | 2560 | 99991.9 | 9650.51 | 0.130912 | 2.59775 | 2(Loss) | true |
| Glaze | 934.047 | 0.0542313 | 1213.71ms | 11812 | 4890 | 209179 | 12060.2 | 0.0986147 | 3.2479 | 3(Loss) | true |
| simdjson (ondemand) | 562.37 | 0.120324 | 2040.06ms | 11812 | 640 | 371780 | 20030.9 | 0.0296504 | 5.3986 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1547.03 | 0.0506016 | 831.399ms | 11812 | 4890 | 66387.8 | 7281.57 | 0.0189463 | 1.95955 | 1(Win) | true |
| Jsonifier (two-stage) | 1315.89 | 0.0472641 | 964.633ms | 11812 | 4890 | 80052.9 | 8560.57 | 0.0393827 | 2.30377 | 2(Loss) | true |
| Glaze | 1122.12 | 0.0933006 | 1111.61ms | 11812 | 1280 | 112291 | 10038.8 | 0.0552848 | 2.70261 | 3(Loss) | true |
| simdjson (ondemand) | 613.523 | 0.0638253 | 1955.25ms | 11812 | 1280 | 175785 | 18360.9 | 0.131306 | 4.94665 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9233.44 | 0.193548 | 125.097ms | 11812 | 1280 | 7136.83 | 1220 | 0.115134 | 0.323889 | 1(Win) | true |
| Glaze | 3387.57 | 0.0865979 | 334.599ms | 11812 | 4890 | 40550.4 | 3325.34 | 0.199723 | 0.890592 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9855.74 | 0.180614 | 115.706ms | 11812 | 1280 | 5454.82 | 1142.97 | 0.530324 | 0.302348 | 1(Win) | true |
| Glaze | 3924.96 | 0.11057 | 291.504ms | 11812 | 2560 | 25780.4 | 2870.04 | 0.162227 | 0.764278 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2317.43 | 0.0861518 | 1048.6ms | 25388 | 1280 | 103701 | 10447.7 | 0.0470873 | 1.30882 | 1(Win) | true |
| Jsonifier | 2204.65 | 0.0838772 | 1104.55ms | 25388 | 1280 | 108611 | 10982.2 | 0.0227693 | 1.37595 | 2(Loss) | true |
| Glaze | 1485.9 | 0.120016 | 1635.32ms | 25388 | 640 | 244757 | 16294.4 | 0.273077 | 2.04232 | 3(Loss) | true |
| simdjson (ondemand) | 1143.28 | 0.216338 | 2144.09ms | 25388 | 160 | 335843 | 21177.5 | 0.3529 | 2.65533 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2597.28 | 0.0511089 | 1042.18ms | 25388 | 4890 | 111000 | 9322.02 | 0.187865 | 1.16744 | 1(Win) | true |
| Jsonifier | 2444.6 | 0.0883234 | 1093.19ms | 25388 | 1280 | 97949.4 | 9904.22 | 0.0346954 | 1.24075 | 2(Loss) | true |
| Glaze | 1694.84 | 0.113749 | 1524.18ms | 25388 | 640 | 168995 | 14285.6 | 0.463706 | 1.79059 | 3(Loss) | true |
| simdjson (ondemand) | 1248.04 | 0.0363307 | 2051.41ms | 25388 | 4890 | 242915 | 19399.9 | 0.197674 | 2.43261 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14676.2 | 0.184556 | 205.431ms | 31235 | 1280 | 17960.8 | 2029.69 | 0.0692361 | 0.204916 | 1(Win) | true |
| Glaze | 4958.67 | 0.0911969 | 600.743ms | 31235 | 4890 | 146765 | 6007.26 | 0.305803 | 0.610665 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15530.6 | 0.0767171 | 194.942ms | 31235 | 4890 | 10587.6 | 1918.02 | 0.116668 | 0.191852 | 1(Win) | true |
| Glaze | 5715.41 | 0.265967 | 514.746ms | 31235 | 320 | 61488.6 | 5211.88 | 0.0599233 | 0.527174 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1997.05 | 0.197972 | 5119.65ms | 108313 | 640 | 6.71075e+06 | 51724.1 | 0.0640008 | 1.52113 | 1(Win) | true |
| Jsonifier (two-stage) | 1453.98 | 0.199827 | 7126.71ms | 108313 | 30 | 604609 | 71043.3 | 0.0986286 | 2.09003 | 2(Loss) | true |
| Glaze | 1306.13 | 0.0553909 | 7928.47ms | 108313 | 640 | 1.22813e+06 | 79085 | 0.0854241 | 2.32633 | 3(Loss) | true |
| simdjson (ondemand) | 835.918 | 0.0431185 | 6326.69ms | 108313 | 2560 | 7.26778e+06 | 123571 | 0.0359608 | 3.63529 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2624.31 | 0.040148 | 4207.64ms | 108313 | 1280 | 319646 | 39360.9 | 0.0635551 | 1.15738 | 1(Win) | true |
| Jsonifier (two-stage) | 1754.93 | 0.120536 | 6261.03ms | 108313 | 80 | 402684 | 58860 | 0.00424755 | 1.73132 | 2(Loss) | true |
| Glaze | 1594.34 | 0.058161 | 6745.58ms | 108313 | 640 | 908743 | 64788.6 | 0.197608 | 1.90561 | 3(Loss) | true |
| simdjson (ondemand) | 945.279 | 0.171165 | 5688.84ms | 108313 | 40 | 1.39936e+06 | 109275 | 0.0656268 | 3.21465 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13441.4 | 0.140421 | 770.144ms | 108313 | 640 | 74527.4 | 7684.84 | 0.15226 | 0.22535 | 1(Win) | true |
| Glaze | 3986.19 | 0.0919476 | 2594.59ms | 108313 | 4890 | 2.7761e+06 | 25913.3 | 0.130909 | 0.761727 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14017.1 | 0.0815216 | 743.737ms | 108313 | 2560 | 92391.8 | 7369.26 | 0.0863274 | 0.216127 | 1(Win) | true |
| Glaze | 4572.78 | 0.132219 | 2272.77ms | 108313 | 4890 | 4.36209e+06 | 22589.2 | 0.998936 | 0.663531 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2250.86 | 0.0633503 | 7790.74ms | 183677 | 2560 | 6.22231e+06 | 77822.9 | 0.0521245 | 1.34988 | 1(Win) | true |
| Jsonifier | 2095.66 | 0.0440347 | 8345.97ms | 183677 | 640 | 867041 | 83586.2 | 0.066218 | 1.44994 | 2(Loss) | true |
| Glaze | 1713.82 | 0.0456181 | 5240.78ms | 183677 | 640 | 1.39134e+06 | 102209 | 0.0425167 | 1.77308 | 3(Loss) | true |
| simdjson (ondemand) | 1363.85 | 0.0388895 | 6570.82ms | 183677 | 2560 | 6.38672e+06 | 128436 | 0.347068 | 2.2281 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2629.58 | 0.0775416 | 6982.09ms | 183677 | 160 | 426899 | 66614.4 | 0.032849 | 1.15543 | 1(Win) | true |
| Jsonifier | 2441.38 | 0.0508658 | 7464.17ms | 183677 | 640 | 852457 | 71749.7 | 0.00130664 | 1.24453 | 2(Loss) | true |
| Glaze | 2010.07 | 0.0284843 | 9021.99ms | 183677 | 2560 | 1.57739e+06 | 87145.2 | 0.116408 | 1.51166 | 3(Loss) | true |
| simdjson (ondemand) | 1539.5 | 0.353682 | 5985.85ms | 183677 | 80 | 1.29559e+07 | 113782 | 0.0483145 | 1.97391 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13607.8 | 0.0633952 | 1506.5ms | 213963 | 4890 | 441902 | 14995.2 | 0.0416696 | 0.222997 | 1(Win) | true |
| Glaze | 4428.31 | 0.698008 | 4743.93ms | 213963 | 640 | 6.62067e+07 | 46078.8 | 0.0338978 | 0.686009 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14001.3 | 0.12925 | 1462.07ms | 213963 | 320 | 113541 | 14573.8 | 0.0257246 | 0.21647 | 1(Win) | true |
| Glaze | 5117.87 | 0.531837 | 4083.57ms | 213963 | 320 | 1.43882e+07 | 39870.3 | 0.568325 | 0.593383 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 601.32 | 0.593598 | 8939.92ms | 1834197 | 40 | 1.19268e+10 | 2.90898e+06 | 0.905197 | 5.05414 | 1(Win) | true |
| Jsonifier (two-stage) | 551.006 | 0.111279 | 9905.06ms | 1834197 | 30 | 3.74394e+08 | 3.17461e+06 | 0.0496403 | 5.51576 | 2(Loss) | true |
| Glaze | 297.328 | 0.284283 | 8849.03ms | 1834197 | 80 | 2.23775e+10 | 5.88315e+06 | 0.463906 | 10.2223 | 3(Loss) | true |
| simdjson (ondemand) | 180.709 | 0.25269 | 6798.67ms | 1834197 | 40 | 2.39315e+10 | 9.67982e+06 | 0.218979 | 16.8183 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 679.044 | 0.464403 | 8865.73ms | 1834197 | 80 | 1.14493e+10 | 2.57601e+06 | 0.11285 | 4.4755 | 1(Win) | true |
| Jsonifier (two-stage) | 592.621 | 0.245734 | 9983.43ms | 1834197 | 160 | 8.41757e+09 | 2.95168e+06 | 0.103353 | 5.12808 | 2(Loss) | true |
| Glaze | 312.366 | 0.399001 | 8825.88ms | 1834197 | 30 | 1.49773e+10 | 5.59993e+06 | 0.0426974 | 9.73012 | 3(Loss) | true |
| simdjson (ondemand) | 187.115 | 0.257606 | 6768.13ms | 1834197 | 40 | 2.31978e+10 | 9.34838e+06 | 0.0554334 | 16.243 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 733.431 | 0.121177 | 7410.53ms | 1834197 | 40 | 3.341e+08 | 2.38499e+06 | 0.050045 | 4.14374 | 1(Win) | true |
| Glaze | 663.247 | 0.174062 | 8172.83ms | 1833577 | 40 | 8.42393e+08 | 2.63648e+06 | 0.196026 | 4.58231 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 818.21 | 0.107906 | 6610.54ms | 1834197 | 40 | 2.12871e+08 | 2.13787e+06 | 0.0489344 | 3.71433 | 1(Win) | true |
| Glaze | 725.616 | 0.0991625 | 7472.14ms | 1833577 | 80 | 4.56846e+08 | 2.40986e+06 | 0.0156154 | 4.18859 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1964.48 | 0.107491 | 5380.3ms | 7351818 | 30 | 4.41527e+08 | 3.569e+06 | 0.320817 | 1.54709 | 1(Win) | true |
| Jsonifier | 1888.85 | 0.0873108 | 5567.84ms | 7351818 | 40 | 4.20136e+08 | 3.7119e+06 | 0.0331925 | 1.60903 | 2(Loss) | true |
| Glaze | 1057.68 | 0.631463 | 9953.44ms | 7351818 | 30 | 5.25651e+10 | 6.62888e+06 | 0.0573925 | 2.87364 | 3(Loss) | true |
| simdjson (ondemand) | 648.294 | 0.242577 | 7596.3ms | 7351818 | 40 | 2.75299e+10 | 1.08149e+07 | 0.017935 | 4.68837 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2097.36 | 0.43276 | 5447.43ms | 7351818 | 80 | 1.67428e+10 | 3.34288e+06 | 0.035137 | 1.44906 | 1(Win) | true |
| Jsonifier | 2041.8 | 0.0870927 | 5583.79ms | 7351818 | 30 | 2.68316e+08 | 3.43385e+06 | 0.500802 | 1.48849 | 2(Loss) | true |
| Glaze | 1082.69 | 0.514966 | 10366.3ms | 7351818 | 80 | 8.89669e+10 | 6.47575e+06 | 0.0191713 | 2.80718 | 3(Loss) | true |
| simdjson (ondemand) | 658.13 | 0.324467 | 7677.24ms | 7351818 | 40 | 4.77933e+10 | 1.06533e+07 | 0.426966 | 4.61817 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2207.21 | 0.343084 | 6371.34ms | 9930848 | 40 | 8.66855e+09 | 4.29084e+06 | 1.14554 | 1.37696 | 1(Win) | true |
| Glaze | 1758.99 | 0.589789 | 8026.73ms | 9930228 | 40 | 4.03313e+10 | 5.38387e+06 | 0.514761 | 1.72772 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 3322.9 | 0.115281 | 8841.68ms | 9930228 | 30 | 3.23832e+08 | 2.84998e+06 | 0.121786 | 0.914604 | 1(Win) | true |
| Jsonifier | 3155.2 | 0.041219 | 9308.55ms | 9930848 | 80 | 1.22463e+08 | 3.00165e+06 | 0.0288675 | 0.963215 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 617.042 | 0.355297 | 8796.87ms | 1834197 | 160 | 1.62317e+10 | 2.83486e+06 | 0.190716 | 4.92534 | 1(Win) | true |
| Jsonifier (two-stage) | 559.298 | 0.351622 | 9716.37ms | 1834197 | 160 | 1.93498e+10 | 3.12754e+06 | 0.0772575 | 5.43365 | 2(Loss) | true |
| simdjson (ondemand) | 302.089 | 0.42629 | 8669.06ms | 1834197 | 80 | 4.87442e+10 | 5.79043e+06 | 0.250413 | 10.0609 | 3(Loss) | true |
| Glaze | 295.147 | 0.378176 | 8882.52ms | 1834197 | 80 | 4.01877e+10 | 5.92662e+06 | 0.480167 | 10.2976 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 680.845 | 0.336228 | 8808.17ms | 1834197 | 160 | 1.19394e+10 | 2.5692e+06 | 0.512155 | 4.4637 | 1(Win) | true |
| Jsonifier (two-stage) | 610.267 | 0.325154 | 9709.68ms | 1834197 | 160 | 1.3898e+10 | 2.86633e+06 | 0.170565 | 4.97987 | 2(Loss) | true |
| simdjson (ondemand) | 323.19 | 0.260981 | 8533.71ms | 1834197 | 40 | 7.98094e+09 | 5.41238e+06 | 0.0422618 | 9.40412 | 3(Loss) | true |
| Glaze | 314.497 | 0.30655 | 8776.3ms | 1834197 | 40 | 1.16284e+10 | 5.56198e+06 | 0.101808 | 9.66425 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 734.928 | 0.0938733 | 7395.17ms | 1834197 | 160 | 7.98742e+08 | 2.38013e+06 | 0.930159 | 4.13526 | 1(Win) | true |
| Glaze | 588.337 | 0.17698 | 9180.39ms | 1833577 | 40 | 1.10676e+09 | 2.97216e+06 | 0.0948464 | 5.1657 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 814.201 | 0.0720487 | 6676.31ms | 1834197 | 80 | 1.91678e+08 | 2.1484e+06 | 0.155049 | 3.73276 | 1(Win) | true |
| Glaze | 735.244 | 0.21444 | 7360.95ms | 1833577 | 160 | 4.16165e+09 | 2.37831e+06 | 0.102304 | 4.13376 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1954.66 | 0.222965 | 5382.04ms | 7351818 | 80 | 5.11695e+09 | 3.58694e+06 | 0.300634 | 1.55487 | 1(Win) | true |
| Jsonifier (two-stage) | 1933.16 | 0.49161 | 5395.17ms | 7351818 | 80 | 2.54323e+10 | 3.62683e+06 | 1.1117 | 1.57203 | 2(Loss) | true |
| simdjson (ondemand) | 1113.39 | 0.349351 | 9313.94ms | 7351818 | 80 | 3.87176e+10 | 6.2972e+06 | 0.311665 | 2.72958 | 3(Loss) | true |
| Glaze | 1036.68 | 0.281644 | 10157ms | 7351818 | 80 | 2.90263e+10 | 6.76318e+06 | 0.152824 | 2.93174 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2158.28 | 0.107846 | 5342.61ms | 7351818 | 30 | 3.68219e+08 | 3.24853e+06 | 0.418025 | 1.40812 | 1(Win) | true |
| Jsonifier | 2115.82 | 0.103907 | 5423.78ms | 7351818 | 30 | 3.55666e+08 | 3.31372e+06 | 0.482645 | 1.43636 | 2(Loss) | true |
| simdjson (ondemand) | 1220.85 | 0.0792852 | 9073.64ms | 7351818 | 40 | 8.29301e+08 | 5.74294e+06 | 0.0141643 | 2.48951 | 3(Loss) | true |
| Glaze | 1091.48 | 0.324055 | 10103.1ms | 7351818 | 80 | 3.46648e+10 | 6.42362e+06 | 0.262091 | 2.78463 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2469.29 | 0.185187 | 5741.34ms | 9930848 | 80 | 4.03587e+09 | 3.83543e+06 | 0.41947 | 1.23083 | 1(Win) | true |
| Glaze | 1278.04 | 0.0740644 | 5205.82ms | 9930228 | 40 | 1.20479e+09 | 7.40997e+06 | 0.0991653 | 2.37817 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3628 | 0.0481904 | 8093.69ms | 9930848 | 80 | 1.26605e+08 | 2.61048e+06 | 0.0245226 | 0.83767 | 1(Win) | true |
| Glaze | 3331.96 | 0.0844198 | 8804.68ms | 9930228 | 80 | 4.60573e+08 | 2.84224e+06 | 0.10888 | 0.912108 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 718.148 | 0.107301 | 7768.56ms | 461466 | 30 | 1.29713e+07 | 612810 | 0.213313 | 4.23201 | 1(Win) | true |
| Jsonifier (two-stage) | 654.932 | 0.127932 | 8546.26ms | 461466 | 80 | 5.91202e+07 | 671960 | 0.0531743 | 4.64029 | 2(Loss) | true |
| Glaze | 637.37 | 0.135164 | 8794.33ms | 461466 | 40 | 3.48399e+07 | 690475 | 0.166103 | 4.76811 | 3(Loss) | true |
| simdjson (ondemand) | 502.566 | 0.2658 | 5539.91ms | 461466 | 40 | 2.16703e+08 | 875682 | 0.421977 | 6.04732 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 966.681 | 0.0588951 | 6847.14ms | 461466 | 160 | 1.15025e+07 | 455257 | 0.215314 | 3.144 | 1(Win) | true |
| Jsonifier (two-stage) | 861.622 | 0.0566065 | 7551.63ms | 461466 | 40 | 3.34379e+06 | 510768 | 0.0226731 | 3.52743 | 2(Loss) | true |
| Glaze | 813.414 | 0.0449768 | 7914.87ms | 461466 | 160 | 9.47446e+06 | 541039 | 0.0332804 | 3.73647 | 3(Loss) | true |
| simdjson (ondemand) | 613.952 | 0.220627 | 5062.33ms | 461466 | 40 | 1.00043e+08 | 716812 | 0.0450111 | 4.9504 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3776.26 | 0.102485 | 5945.35ms | 461466 | 2560 | 3.65188e+07 | 116541 | 0.116108 | 0.80402 | 1(Win) | true |
| Glaze | 3018.44 | 0.134624 | 7524.22ms | 461466 | 640 | 2.4657e+07 | 145800 | 0.394209 | 1.00671 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11459.9 | 0.150771 | 3948.57ms | 461466 | 40 | 134096 | 38402.5 | 0.0195262 | 0.264926 | 1(Win) | true |
| Glaze | 3260.23 | 0.0886159 | 7016.88ms | 461466 | 1280 | 1.83154e+07 | 134987 | 0.130975 | 0.932008 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1017.93 | 0.13502 | 8707.19ms | 728486 | 40 | 3.39674e+07 | 682502 | 0.29716 | 2.98554 | 1(Win) | true |
| Jsonifier | 931.472 | 0.226758 | 9493.84ms | 728486 | 80 | 2.28832e+08 | 745850 | 0.210606 | 3.26267 | 2(Loss) | true |
| Glaze | 866.31 | 0.231731 | 5071.3ms | 728486 | 160 | 5.52567e+08 | 801951 | 0.10298 | 3.50824 | 3(Loss) | true |
| simdjson (ondemand) | 769.026 | 0.21333 | 5731.74ms | 728486 | 40 | 1.48567e+08 | 903400 | 0.171869 | 3.95202 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1326.92 | 0.0279089 | 7752.59ms | 728486 | 640 | 1.36652e+07 | 523572 | 0.0053422 | 2.29041 | 1(Win) | true |
| Jsonifier | 1180 | 0.064072 | 8558.18ms | 728486 | 80 | 1.13842e+07 | 588760 | 0.0810369 | 2.57564 | 2(Loss) | true |
| Glaze | 1084.25 | 0.0790411 | 9249.28ms | 728486 | 160 | 4.10403e+07 | 640756 | 0.0749529 | 2.80313 | 3(Loss) | true |
| simdjson (ondemand) | 933.328 | 0.245992 | 5258.66ms | 728486 | 30 | 1.00586e+08 | 744367 | 0.226079 | 3.25627 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4043.19 | 0.151583 | 5117.34ms | 837491 | 1280 | 1.14768e+08 | 197540 | 0.557598 | 0.751084 | 1(Win) | true |
| Glaze | 2276.26 | 0.152818 | 8998.22ms | 837491 | 1280 | 3.68023e+08 | 350879 | 0.423603 | 1.33451 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12466.7 | 0.128088 | 6494.65ms | 837491 | 80 | 538720 | 64066.2 | 0.072243 | 0.243579 | 1(Win) | true |
| Glaze | 4359.32 | 0.123036 | 9373.32ms | 837491 | 1280 | 6.50428e+07 | 183215 | 0.1703 | 0.696981 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 6632.9 | 0.0429558 | 6710.83ms | 466906 | 2560 | 2.1288e+06 | 67131.5 | 0.125844 | 0.458064 | 1(Win) | true |
| Jsonifier | 6579.31 | 0.0827473 | 6775.79ms | 466906 | 640 | 2.00718e+06 | 67678.3 | 0.179986 | 0.461793 | 2(Loss) | true |
| simdjson (ondemand) | 4199.1 | 0.0498714 | 5433.59ms | 466906 | 640 | 1.7899e+06 | 106041 | 0.065233 | 0.72367 | 3(Loss) | true |
| Glaze | 2849.29 | 0.465654 | 8109.14ms | 466906 | 160 | 8.47292e+07 | 156276 | 0.0608268 | 1.06652 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 6842.64 | 0.0814115 | 6615.58ms | 466906 | 4890 | 1.37244e+07 | 65073.8 | 0.04441 | 0.443995 | 1(Win) | true |
| Jsonifier | 6799.15 | 0.244496 | 6610.44ms | 466906 | 40 | 1.02554e+06 | 65490 | 0.00508958 | 0.446856 | 2(Loss) | true |
| simdjson (ondemand) | 4349.94 | 0.185809 | 5305.83ms | 466906 | 160 | 5.78824e+06 | 102364 | 0.0439416 | 0.698552 | 3(Loss) | true |
| Glaze | 2958.62 | 0.156294 | 7783.15ms | 466906 | 1280 | 7.08228e+07 | 150501 | 0.767467 | 1.02707 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 7516.65 | 0.104453 | 8033.12ms | 631514 | 30 | 210126 | 80123.3 | 0.0624428 | 0.404248 | 1(Win) | true |
| Jsonifier | 7484.75 | 0.0539705 | 8047.59ms | 631514 | 2560 | 4.82796e+06 | 80464.7 | 0.0477436 | 0.405943 | 2(Loss) | true |
| simdjson (ondemand) | 5143.15 | 0.134157 | 5984.25ms | 631514 | 1280 | 3.15896e+07 | 117099 | 0.0694338 | 0.590817 | 3(Loss) | true |
| Glaze | 3521.9 | 0.116583 | 8744.8ms | 631514 | 320 | 1.27183e+07 | 171004 | 0.238641 | 0.862856 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7746.34 | 0.145612 | 7916.92ms | 631514 | 80 | 1.02531e+06 | 77747.5 | 0.00964754 | 0.392249 | 1(Win) | true |
| Jsonifier (two-stage) | 7665.16 | 0.0588971 | 7982.96ms | 631514 | 1280 | 2.74108e+06 | 78570.9 | 0.141194 | 0.396381 | 2(Loss) | true |
| simdjson (ondemand) | 5284.36 | 0.111734 | 5904.65ms | 631514 | 320 | 5.18919e+06 | 113970 | 0.0137116 | 0.575035 | 3(Loss) | true |
| Glaze | 3621.96 | 0.0662625 | 8595.67ms | 631514 | 1280 | 1.5539e+07 | 166280 | 0.0471002 | 0.839009 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1124.06 | 1.05955 | 5007.22ms | 466906 | 640 | 1.12748e+10 | 396133 | 0.0461706 | 2.7033 | 1(Win) | true |
| Glaze | 1020.02 | 0.920674 | 5604.64ms | 466906 | 640 | 1.0338e+10 | 436539 | 0.105228 | 2.97919 | 2(Loss) | true |
| Jsonifier (two-stage) | 986.688 | 0.829197 | 5729.6ms | 466906 | 640 | 8.9618e+09 | 451284 | 0.100134 | 3.07974 | 3(Loss) | true |
| simdjson (ondemand) | 844.708 | 1.50429 | 6598.57ms | 466906 | 160 | 1.00607e+10 | 527136 | 0.0548071 | 3.59759 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1938.46 | 0.0373985 | 6782.38ms | 466906 | 640 | 4.72318e+06 | 229706 | 0.0687491 | 1.56779 | 1(Win) | true |
| Glaze | 1606.68 | 0.0791384 | 7995.92ms | 466906 | 80 | 3.84828e+06 | 277141 | 0.0410609 | 1.89162 | 2(Loss) | true |
| Jsonifier (two-stage) | 1531.65 | 0.160834 | 8349.11ms | 466906 | 320 | 6.99595e+07 | 290717 | 0.0232239 | 1.98425 | 3(Loss) | true |
| simdjson (ondemand) | 1166.59 | 0.209488 | 5229.28ms | 466906 | 160 | 1.02297e+08 | 381691 | 0.358946 | 2.6052 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 4451.06 | 0.31225 | 5257.75ms | 475954 | 2560 | 2.59567e+08 | 101977 | 1.39926 | 0.682631 | 1(Win) | true |
| Jsonifier | 3890.96 | 0.187189 | 6036.68ms | 475954 | 160 | 7.62952e+06 | 116656 | 0.162607 | 0.78029 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16038.2 | 0.129087 | 2859.58ms | 475954 | 640 | 854207 | 28301.6 | 0.142642 | 0.189218 | 1(Win) | true |
| Glaze | 4847.32 | 0.225552 | 9459.57ms | 475954 | 2560 | 1.14199e+08 | 93640.5 | 0.238916 | 0.626821 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1399.93 | 0.315472 | 5480.14ms | 631514 | 640 | 1.17884e+09 | 430207 | 0.0291925 | 2.17077 | 1(Win) | true |
| Glaze | 1360.97 | 0.404371 | 5664.98ms | 631514 | 320 | 1.02466e+09 | 442521 | 0.527125 | 2.23301 | 2(Loss) | true |
| Jsonifier | 1323.84 | 0.916885 | 5850.66ms | 631514 | 80 | 1.39192e+09 | 454932 | 0.627993 | 2.29531 | 3(Loss) | true |
| simdjson (ondemand) | 1183.89 | 0.298634 | 6562.03ms | 631514 | 30 | 6.92375e+07 | 508710 | 0.0779143 | 2.567 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1932.5 | 0.110625 | 8938.23ms | 631514 | 40 | 4.75435e+06 | 311648 | 0.119383 | 1.57264 | 1(Win) | true |
| Glaze | 1820.12 | 0.0343711 | 9382.54ms | 631514 | 640 | 8.27812e+06 | 330889 | 0.0344124 | 1.66976 | 2(Loss) | true |
| Jsonifier | 1785.25 | 0.0384407 | 9512.88ms | 631514 | 1280 | 2.15258e+07 | 337352 | 0.102279 | 1.70235 | 3(Loss) | true |
| simdjson (ondemand) | 1505.13 | 0.484408 | 5543.81ms | 631514 | 40 | 1.5028e+08 | 400138 | 0.226698 | 2.01924 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3835.97 | 0.208373 | 9055.45ms | 716365 | 2560 | 3.52567e+08 | 178098 | 0.138568 | 0.791728 | 1(Win) | true |
| Glaze | 1691.48 | 0.275831 | 5070.15ms | 716365 | 320 | 3.97167e+08 | 403895 | 1.14902 | 1.79591 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13386.4 | 0.102755 | 5094.93ms | 716365 | 640 | 1.76007e+06 | 51035.3 | 0.0293828 | 0.226893 | 1(Win) | true |
| Glaze | 3142.94 | 0.273833 | 5597.75ms | 716365 | 1280 | 4.53501e+08 | 217369 | 0.434857 | 0.966931 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1158.88 | 0.144413 | 222.321ms | 2632 | 320 | 3130.78 | 2165.94 | 0.565873 | 2.60135 | 1(Win) | true |
| Jsonifier | 1119.49 | 0.188968 | 226.751ms | 2632 | 2560 | 45956.3 | 2242.15 | 0.123849 | 2.6921 | 2(Loss) | true |
| Glaze | 857.002 | 0.0946134 | 295.119ms | 2632 | 4890 | 37551 | 2928.9 | 0.0650332 | 3.5175 | 3(Loss) | true |
| simdjson (ondemand) | 664.809 | 0.155627 | 380.959ms | 2632 | 640 | 22096.6 | 3775.62 | 0.0826993 | 4.54385 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1490.83 | 0.167038 | 202.964ms | 2632 | 1280 | 10124.1 | 1683.67 | 0.283853 | 2.015 | 1(Win) | true |
| Jsonifier (two-stage) | 1453.67 | 0.214937 | 200.859ms | 2632 | 640 | 8815.51 | 1726.72 | 0.0271542 | 2.06923 | 2(Loss) | true |
| Glaze | 1408.18 | 0.118919 | 211.967ms | 2632 | 4890 | 21972.1 | 1782.49 | 0.181934 | 2.13494 | 3(Loss) | true |
| simdjson (ondemand) | 1041.81 | 0.113685 | 268.004ms | 2632 | 4890 | 36687 | 2409.35 | 0.0344602 | 2.89336 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9187.56 | 0.826502 | 29.3143ms | 2632 | 2560 | 13052.7 | 273.203 | 0.455451 | 0.306959 | 1(Win) | true |
| Glaze | 3489.48 | 0.119968 | 74.2609ms | 2632 | 4890 | 3641.6 | 719.325 | 0.440296 | 0.848879 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10947.4 | 0.338093 | 24.9993ms | 2632 | 4890 | 2938.53 | 229.284 | 0.456562 | 0.254234 | 1(Win) | true |
| Glaze | 4083.11 | 0.129309 | 63.9777ms | 2632 | 4890 | 3089.98 | 614.744 | 0.219021 | 0.7203 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1392.8 | 0.180144 | 233.07ms | 3370 | 2560 | 44234.5 | 2307.5 | 0.0372288 | 2.16449 | 1(Win) | true |
| Jsonifier | 1193.63 | 0.0798599 | 271.91ms | 3370 | 4890 | 22609.4 | 2692.54 | 0.0769532 | 2.52761 | 2(Loss) | true |
| Glaze | 950.743 | 0.125826 | 339.862ms | 3370 | 1280 | 23157 | 3380.39 | 0.04851 | 3.17701 | 3(Loss) | true |
| simdjson (ondemand) | 837.337 | 0.0799181 | 386.467ms | 3370 | 4890 | 46010.7 | 3838.22 | 0.0432814 | 3.61019 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1756.82 | 0.209013 | 213.595ms | 3370 | 160 | 2339.23 | 1829.38 | 0.0341763 | 1.71439 | 1(Win) | true |
| Jsonifier | 1537.74 | 0.286672 | 246.08ms | 3370 | 40 | 1435.9 | 2090 | 0 | 1.9621 | 2(Loss) | true |
| Glaze | 1491.1 | 0.100493 | 248.438ms | 3370 | 4890 | 22942 | 2155.38 | 0.296908 | 2.01917 | 3(Loss) | true |
| simdjson (ondemand) | 1297.88 | 0.145392 | 274.848ms | 3370 | 160 | 2073.9 | 2476.25 | 0.151668 | 2.33044 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9918.27 | 0.214403 | 37.4754ms | 3643 | 4890 | 2758.15 | 350.286 | 0.182429 | 0.290143 | 1(Win) | true |
| Glaze | 3905.66 | 0.248545 | 92.4334ms | 3682 | 320 | 1597.86 | 899.062 | 0.242718 | 0.759153 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11469 | 0.185982 | 32.7457ms | 3643 | 4890 | 1552.09 | 302.924 | 0.130548 | 0.249005 | 1(Win) | true |
| Glaze | 4549.06 | 0.169984 | 81.0659ms | 3682 | 4890 | 8418.76 | 771.902 | 0.409802 | 0.650156 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 504.868 | 0.054481 | 877.175ms | 4630 | 4890 | 111021 | 8745.87 | 0.118108 | 6.00686 | 1(Win) | true |
| Jsonifier (two-stage) | 503.071 | 0.11928 | 882.355ms | 4630 | 1280 | 140297 | 8777.11 | 0.0650195 | 6.0284 | 2(Loss) | true |
| simdjson (ondemand) | 308.723 | 0.0948332 | 1425.33ms | 4630 | 640 | 117740 | 14302.5 | 0.0196683 | 9.83194 | 3(Loss) | true |
| Glaze | 306.297 | 0.045185 | 1446.35ms | 4630 | 4890 | 207480 | 14415.8 | 0.0535937 | 9.90931 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 612.797 | 0.0512878 | 848.732ms | 4630 | 4890 | 66783 | 7205.5 | 0.0206905 | 4.94575 | 1(Win) | true |
| Jsonifier (two-stage) | 604.693 | 0.0752241 | 857.675ms | 4630 | 2560 | 77240.7 | 7302.07 | 0.123727 | 5.01151 | 2(Loss) | true |
| simdjson (ondemand) | 343.979 | 0.101715 | 1423.03ms | 4630 | 320 | 54552.4 | 12836.6 | 0.0170441 | 8.82161 | 3(Loss) | true |
| Glaze | 338.578 | 0.0839572 | 1427.9ms | 4630 | 1280 | 153451 | 13041.3 | 0.0197728 | 8.96163 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1531.82 | 0.0869288 | 290.928ms | 4630 | 4890 | 30703.3 | 2882.54 | 0.12328 | 1.97115 | 1(Win) | true |
| Glaze | 1150.41 | 0.0680646 | 386.596ms | 4630 | 4890 | 33374.2 | 3838.22 | 0.0208209 | 2.62872 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1652.5 | 0.0916684 | 269.909ms | 4630 | 4890 | 29337.9 | 2672.02 | 0.157887 | 1.81694 | 1(Win) | true |
| Glaze | 1172.44 | 0.137799 | 378.583ms | 4630 | 640 | 17236.7 | 3766.09 | 0.0124481 | 2.57695 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1189.47 | 0.0873254 | 937.261ms | 11579 | 1280 | 84124.7 | 9283.59 | 0.186473 | 2.54874 | 1(Win) | true |
| Jsonifier | 1114.74 | 0.100526 | 997.692ms | 11579 | 1280 | 126930 | 9906.02 | 0.214185 | 2.71983 | 2(Loss) | true |
| simdjson (ondemand) | 747.763 | 0.11621 | 1470.32ms | 11579 | 640 | 188488 | 14767.5 | 0.0953168 | 4.05817 | 3(Loss) | true |
| Glaze | 688.567 | 0.0515454 | 1607.63ms | 11579 | 2560 | 174932 | 16037.1 | 0.0284903 | 4.40807 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1400.01 | 0.170988 | 927.251ms | 11579 | 40 | 7275.64 | 7887.5 | 0.222363 | 2.16313 | 1(Win) | true |
| Jsonifier | 1274.71 | 0.0589997 | 996.141ms | 11579 | 4890 | 127740 | 8662.82 | 0.157731 | 2.37794 | 2(Loss) | true |
| simdjson (ondemand) | 820.52 | 0.11781 | 1483.21ms | 11579 | 1280 | 321765 | 13458 | 0.0121921 | 3.69778 | 3(Loss) | true |
| Glaze | 750.83 | 0.116504 | 1599.38ms | 11579 | 640 | 187898 | 14707.2 | 0.106354 | 4.04176 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4564.37 | 0.0826728 | 314.262ms | 14795 | 640 | 4179.97 | 3091.25 | 0.121457 | 0.66207 | 1(Win) | true |
| Glaze | 2811.38 | 0.238023 | 495.545ms | 14795 | 80 | 11416.1 | 5018.75 | 0.324838 | 1.07695 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4782.92 | 0.094897 | 299.178ms | 14795 | 320 | 2507.84 | 2950 | 0 | 0.627098 | 1(Win) | true |
| Glaze | 3160.27 | 0.212067 | 448.749ms | 14795 | 320 | 28686.4 | 4464.69 | 0.00699986 | 0.956976 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 817.064 | 0.137174 | 383.029ms | 3223 | 160 | 4260.61 | 3761.88 | 0.0830013 | 3.6966 | 1(Win) | true |
| Jsonifier (two-stage) | 686.865 | 0.0909118 | 451.957ms | 3223 | 2560 | 42370.1 | 4474.96 | 0.107253 | 4.40191 | 2(Loss) | true |
| Glaze | 599.992 | 0.125434 | 519.134ms | 3223 | 1280 | 52853.2 | 5122.89 | 0.010674 | 5.0455 | 3(Loss) | true |
| simdjson (ondemand) | 482.905 | 0.150827 | 639.274ms | 3223 | 320 | 29492.2 | 6365 | 0.0294493 | 6.27566 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1075.64 | 0.0879916 | 350.728ms | 3223 | 4890 | 30915.6 | 2857.55 | 0.0645336 | 2.80315 | 1(Win) | true |
| Jsonifier (two-stage) | 864.193 | 0.112981 | 421.197ms | 3223 | 2560 | 41338.2 | 3556.72 | 0.0857388 | 3.4953 | 2(Loss) | true |
| Glaze | 745.979 | 0.064723 | 471.397ms | 3223 | 4890 | 34777.1 | 4120.35 | 0.0872006 | 4.05372 | 3(Loss) | true |
| simdjson (ondemand) | 595.159 | 0.0921093 | 578.02ms | 3223 | 2560 | 57929.8 | 5164.49 | 0.0461171 | 5.08673 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7040.67 | 0.318688 | 46.6219ms | 3223 | 1280 | 2477.62 | 436.562 | 0.356633 | 0.408586 | 1(Win) | true |
| Glaze | 3235.47 | 0.592152 | 99.3827ms | 3223 | 80 | 2531.65 | 950 | 0.262467 | 0.914389 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7797.04 | 0.176289 | 41.5892ms | 3223 | 4890 | 2361.67 | 394.213 | 0.278216 | 0.368317 | 1(Win) | true |
| Glaze | 4132.7 | 0.528962 | 76.9874ms | 3223 | 160 | 2476.42 | 743.75 | 0 | 0.711368 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1199.34 | 0.15605 | 466.943ms | 5839 | 640 | 33596.8 | 4642.97 | 0.0840619 | 2.52082 | 1(Win) | true |
| Jsonifier | 1096.46 | 0.0988395 | 509.156ms | 5839 | 4890 | 123215 | 5078.63 | 0.0361051 | 2.7588 | 2(Loss) | true |
| Glaze | 922.803 | 0.0590147 | 608.801ms | 5839 | 4890 | 62013.7 | 6034.34 | 0.0588823 | 3.28286 | 3(Loss) | true |
| simdjson (ondemand) | 847.996 | 0.197725 | 662.231ms | 5839 | 30 | 5057.47 | 6566.67 | 0.152053 | 3.57534 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1499.11 | 0.130264 | 438.939ms | 5839 | 1280 | 29968.5 | 3714.53 | 0.0210278 | 2.01568 | 1(Win) | true |
| Jsonifier | 1362.3 | 0.0897077 | 475.562ms | 5839 | 4890 | 65751 | 4087.59 | 0.0997005 | 2.21708 | 2(Loss) | true |
| Glaze | 1130.09 | 0.13496 | 560.126ms | 5839 | 80 | 3537.97 | 4927.5 | 0 | 2.6797 | 3(Loss) | true |
| simdjson (ondemand) | 1053.74 | 0.0828272 | 589.914ms | 5839 | 2560 | 49045.5 | 5284.53 | 0.303987 | 2.87393 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7301.07 | 0.300514 | 85.2285ms | 6938 | 80 | 593.354 | 906.25 | 0.138122 | 0.405486 | 1(Win) | true |
| Glaze | 4260.55 | 0.138122 | 159.981ms | 6960 | 4890 | 22642.4 | 1557.91 | 0.176204 | 0.704371 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8736.37 | 0.221336 | 77.8865ms | 6938 | 4890 | 13741 | 757.362 | 0.0697544 | 0.339055 | 1(Win) | true |
| Glaze | 5251.64 | 0.16014 | 129.024ms | 6960 | 4890 | 20032.6 | 1263.91 | 0.17896 | 0.568985 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1049.71 | 0.155308 | 445.584ms | 4857 | 640 | 30058.7 | 4412.66 | 0.0177079 | 2.88031 | 1(Win) | true |
| Glaze | 851.959 | 0.211713 | 558.325ms | 4857 | 320 | 42397.7 | 5436.88 | 0.0689259 | 3.55065 | 2(Loss) | true |
| Jsonifier (two-stage) | 804.341 | 0.232981 | 585.898ms | 4857 | 320 | 57603.4 | 5758.75 | 0.162531 | 3.76524 | 3(Loss) | true |
| simdjson (ondemand) | 650.847 | 0.230473 | 730.791ms | 4857 | 160 | 43046.8 | 7116.88 | 0.00878272 | 4.65596 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1550.17 | 0.0819243 | 351.416ms | 4857 | 4890 | 29303 | 2988.06 | 0.0474324 | 1.94775 | 1(Win) | true |
| Glaze | 1524.94 | 0.298821 | 352.769ms | 4857 | 320 | 26363.6 | 3037.5 | 0.123609 | 1.97908 | 2(Loss) | true |
| Jsonifier (two-stage) | 1080.7 | 0.100893 | 488.95ms | 4857 | 2560 | 47872.2 | 4286.09 | 0.187392 | 2.79736 | 3(Loss) | true |
| simdjson (ondemand) | 931.055 | 0.136159 | 545.448ms | 4857 | 80 | 3670.89 | 4975 | 0.250627 | 3.24719 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9207.5 | 0.150663 | 52.9768ms | 4857 | 4890 | 2809.16 | 503.067 | 0.467365 | 0.317875 | 1(Win) | true |
| Glaze | 3494.09 | 0.298068 | 139.022ms | 4857 | 2560 | 39970.3 | 1325.66 | 0.0914292 | 0.856898 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10654 | 0.187872 | 47.666ms | 4857 | 4890 | 3262.42 | 434.765 | 0.035768 | 0.273146 | 1(Win) | true |
| Glaze | 4495.04 | 0.389045 | 108.472ms | 4857 | 1280 | 20572.1 | 1030.47 | 0.594875 | 0.660417 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1170.43 | 0.141921 | 552.382ms | 6701 | 640 | 38428.8 | 5460 | 0.00572377 | 2.58643 | 1(Win) | true |
| Jsonifier | 1109.43 | 0.150347 | 583.826ms | 6701 | 1280 | 96001.5 | 5760.23 | 0.229738 | 2.72734 | 2(Loss) | true |
| Glaze | 1023.85 | 0.201727 | 633.566ms | 6701 | 640 | 101465 | 6241.72 | 0.0825413 | 2.95696 | 3(Loss) | true |
| simdjson (ondemand) | 894.203 | 0.298025 | 726.803ms | 6701 | 30 | 13609.2 | 7146.67 | 0.0466636 | 3.39894 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1697.49 | 0.0690819 | 421.807ms | 6701 | 4890 | 33075.2 | 3764.72 | 0.419835 | 1.78098 | 1(Win) | true |
| Jsonifier (two-stage) | 1576.62 | 0.228555 | 461.833ms | 6701 | 30 | 2574.71 | 4053.33 | 0.246103 | 1.92067 | 2(Loss) | true |
| Jsonifier | 1475.75 | 0.0697494 | 486.181ms | 6701 | 4890 | 44611.2 | 4330.39 | 0.266768 | 2.05017 | 3(Loss) | true |
| simdjson (ondemand) | 1253.98 | 0.0650838 | 551.41ms | 6701 | 4890 | 53796.4 | 5096.24 | 0.145595 | 2.41444 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8193.06 | 0.146079 | 88.8769ms | 7376 | 4890 | 7691.96 | 858.569 | 0.302305 | 0.363028 | 1(Win) | true |
| Glaze | 3611.96 | 0.519614 | 203.089ms | 7376 | 40 | 4096.15 | 1947.5 | 0.386598 | 0.828162 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8933.33 | 0.301831 | 80.0284ms | 7376 | 1280 | 7230.25 | 787.422 | 0.148603 | 0.33193 | 1(Win) | true |
| Glaze | 4119.65 | 1.51777 | 174.629ms | 7376 | 40 | 26865.4 | 1707.5 | 0.836614 | 0.72501 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1083.11 | 0.092267 | 151.926ms | 1691 | 4890 | 9228.73 | 1488.92 | 0.216263 | 2.77084 | 1(Win) | true |
| Glaze | 1075.64 | 0.138308 | 153.208ms | 1691 | 4890 | 21026.3 | 1499.26 | 0.136068 | 2.7927 | 2(Loss) | true |
| Jsonifier (two-stage) | 923.097 | 0.0790721 | 177.998ms | 1691 | 4890 | 9331.44 | 1747.01 | 0.0728703 | 3.25759 | 3(Loss) | true |
| simdjson (ondemand) | 679.704 | 0.080904 | 239.929ms | 1691 | 4890 | 18017.6 | 2372.6 | 0.284791 | 4.43662 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1468.27 | 0.129701 | 133.817ms | 1691 | 4890 | 9923.62 | 1098.34 | 0.0946748 | 2.03556 | 1(Win) | true |
| Glaze | 1400.03 | 0.305907 | 137.554ms | 1691 | 640 | 7946.4 | 1151.88 | 0.189548 | 2.13309 | 2(Loss) | true |
| Jsonifier (two-stage) | 1196.83 | 0.129251 | 160.951ms | 1691 | 4890 | 14831.9 | 1347.44 | 0.0306238 | 2.50568 | 3(Loss) | true |
| simdjson (ondemand) | 753.87 | 0.106779 | 243.085ms | 1691 | 2560 | 13356.9 | 2139.18 | 0.177441 | 3.99629 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9139.25 | 0.369991 | 23.1523ms | 1996 | 1280 | 760.14 | 208.281 | 0.603774 | 0.302353 | 1(Win) | true |
| Glaze | 3900.55 | 0.303359 | 50.0085ms | 1996 | 4890 | 10717.5 | 488.016 | 1.01245 | 0.751179 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12803.7 | 0.611763 | 17.0054ms | 1996 | 4890 | 4045.07 | 148.671 | 0.0795125 | 0.209175 | 1(Win) | true |
| Glaze | 5709.55 | 0.273494 | 37.0929ms | 1996 | 4890 | 4065.59 | 333.395 | 1.43315 | 0.488717 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1177.27 | 0.0901742 | 179.654ms | 2158 | 4890 | 12151.4 | 1748.14 | 0.168734 | 2.55241 | 1(Win) | true |
| Glaze | 1151.01 | 0.0996897 | 182.355ms | 2158 | 4890 | 15536.5 | 1788.02 | 0.0529385 | 2.61417 | 2(Loss) | true |
| Jsonifier | 977.106 | 0.308522 | 217.035ms | 2158 | 80 | 3378.16 | 2106.25 | 0.297619 | 3.07101 | 3(Loss) | true |
| simdjson (ondemand) | 797.106 | 0.267656 | 262.958ms | 2158 | 320 | 15281.7 | 2581.88 | 0.0242014 | 3.79058 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze STATISTICAL TIE | 1477.05 | 0.478469 | 162.572ms | 2158 | 30 | 1333.33 | 1393.33 | 0 | 2.0283 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1472.9 | 0.109329 | 164.517ms | 2158 | 1280 | 2987.04 | 1397.27 | 0.0727395 | 2.0374 | 1(Tie) | true |
| Jsonifier | 1252.18 | 0.122583 | 196.505ms | 2158 | 4890 | 19849.1 | 1643.56 | 0.0121037 | 2.39975 | 3(Loss) | true |
| simdjson (ondemand) | 1031.96 | 0.14531 | 222.43ms | 2158 | 1280 | 10749.3 | 1994.3 | 0.121588 | 2.91661 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9615.32 | 0.266362 | 30.8824ms | 2866 | 2560 | 1467.6 | 284.258 | 0.0412088 | 0.295382 | 1(Win) | true |
| Glaze | 3459.79 | 0.215764 | 81.6954ms | 2866 | 4890 | 14207.6 | 790 | 0.1684 | 0.85687 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11732.2 | 0.798255 | 25.4657ms | 2866 | 640 | 2213.39 | 232.969 | 1.12732 | 0.236731 | 1(Win) | true |
| Glaze | 4304.56 | 0.660371 | 61.0211ms | 2866 | 2560 | 45010.2 | 634.961 | 0.191075 | 0.675375 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1173.3 | 0.096311 | 359.25ms | 4390 | 4890 | 57753 | 3568.26 | 0.0268123 | 2.57497 | 1(Win) | true |
| Jsonifier (two-stage) | 1013.48 | 0.14777 | 418.79ms | 4390 | 320 | 11923.9 | 4130.94 | 0.0529261 | 2.9866 | 2(Loss) | true |
| Glaze | 882.296 | 0.172199 | 478.592ms | 4390 | 640 | 42730.8 | 4745.16 | 0.0691017 | 3.43088 | 3(Loss) | true |
| simdjson (ondemand) | 542.837 | 0.148181 | 784.408ms | 4390 | 40 | 5224.36 | 7712.5 | 0.0108038 | 5.58191 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1399.33 | 0.26297 | 352.285ms | 4390 | 320 | 19808.4 | 2991.88 | 0.208464 | 2.16045 | 1(Win) | true |
| Jsonifier (two-stage) | 1175.41 | 0.0806577 | 410.793ms | 4390 | 4890 | 40359.9 | 3561.84 | 0.00206551 | 2.5711 | 2(Loss) | true |
| Glaze | 1124.68 | 0.311497 | 427.848ms | 4390 | 40 | 5378.21 | 3722.5 | 0.0223814 | 2.69311 | 3(Loss) | true |
| simdjson (ondemand) | 612.78 | 0.191194 | 734.813ms | 4390 | 320 | 54603.4 | 6832.19 | 0.371867 | 4.94653 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8672.74 | 0.277748 | 50.7468ms | 4390 | 2560 | 4602.13 | 482.734 | 0.161577 | 0.33761 | 1(Win) | true |
| Glaze | 3424.54 | 0.121565 | 125.588ms | 4390 | 2560 | 5654.36 | 1222.54 | 0.413886 | 0.873821 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9722.02 | 0.225033 | 45.4994ms | 4390 | 4890 | 4592.15 | 430.634 | 0.247604 | 0.299396 | 1(Win) | true |
| Glaze | 3913.49 | 0.116929 | 109.333ms | 4390 | 4890 | 7651.63 | 1069.8 | 0.413452 | 0.75662 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2027.88 | 0.0639312 | 444.267ms | 9378 | 4890 | 38875.1 | 4410.31 | 0.0530403 | 1.49189 | 1(Win) | true |
| Jsonifier | 1904.24 | 0.297337 | 474.522ms | 9378 | 30 | 5850.57 | 4696.67 | 0.212465 | 1.59002 | 2(Loss) | true |
| Glaze | 1414.95 | 0.0623005 | 637.488ms | 9378 | 4890 | 75828 | 6320.76 | 0.00455498 | 2.14014 | 3(Loss) | true |
| simdjson (ondemand) | 1110.31 | 0.0768955 | 816.765ms | 9378 | 160 | 6138.36 | 8055 | 0.13947 | 2.73142 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2337.04 | 0.255366 | 435.029ms | 9378 | 320 | 30560.7 | 3826.88 | 0.0163292 | 1.29306 | 1(Win) | true |
| Jsonifier | 2182.24 | 0.078406 | 464.078ms | 9378 | 4890 | 50492.2 | 4098.34 | 0.199214 | 1.38646 | 2(Loss) | true |
| Glaze | 1676.7 | 0.0635882 | 584.262ms | 9378 | 4890 | 56256.4 | 5334.03 | 0.0343102 | 1.80569 | 3(Loss) | true |
| simdjson (ondemand) | 1260.63 | 0.109789 | 762.934ms | 9378 | 1280 | 77655.8 | 7094.53 | 0.0220192 | 2.40417 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12935.6 | 0.114172 | 87.9936ms | 11521 | 4890 | 4598.72 | 849.387 | 0.287548 | 0.229392 | 1(Win) | true |
| Glaze | 4593.59 | 0.324745 | 234.958ms | 11521 | 320 | 19306.8 | 2391.88 | 0.208605 | 0.655715 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15376.9 | 0.199961 | 74.5992ms | 11521 | 640 | 1306.51 | 714.531 | 0.0655594 | 0.193039 | 1(Win) | true |
| Glaze | 5272.84 | 0.326686 | 206.693ms | 11521 | 640 | 29657.3 | 2083.75 | 0.194582 | 0.568737 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2053.41 | 0.0885073 | 219.707ms | 4669 | 4890 | 18012.1 | 2168.45 | 0.09234 | 1.46655 | 1(Win) | true |
| Jsonifier (two-stage) | 1434.84 | 0.183649 | 314.86ms | 4669 | 640 | 20787.3 | 3103.28 | 0.115671 | 2.10263 | 2(Loss) | true |
| Glaze | 1249.04 | 0.0727808 | 357.881ms | 4669 | 4890 | 32918.4 | 3564.91 | 0.167758 | 2.42026 | 3(Loss) | true |
| simdjson (ondemand) | 804.986 | 0.146619 | 556.362ms | 4669 | 640 | 42095 | 5531.41 | 0.00847362 | 3.76145 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2338.53 | 0.108263 | 207.315ms | 4669 | 2560 | 10878.4 | 1904.06 | 0.0369413 | 1.28601 | 1(Win) | true |
| Jsonifier (two-stage) | 1573.44 | 0.120331 | 300.961ms | 4669 | 1280 | 14842.8 | 2829.92 | 0.11306 | 1.9207 | 2(Loss) | true |
| Glaze | 1458.11 | 0.0936849 | 321.771ms | 4669 | 320 | 2619.12 | 3053.75 | 0.0204625 | 2.07476 | 3(Loss) | true |
| simdjson (ondemand) | 914.72 | 0.0679715 | 502.257ms | 4669 | 4890 | 53534.5 | 4867.83 | 0.0421528 | 3.30961 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10478.9 | 0.201235 | 45.2833ms | 4669 | 2560 | 1871.82 | 424.922 | 0.421091 | 0.277918 | 1(Win) | true |
| Glaze | 3832.34 | 0.369309 | 129.409ms | 4669 | 640 | 11783.6 | 1161.88 | 0.826887 | 0.780223 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12009 | 0.485201 | 39.8281ms | 4669 | 640 | 2071.38 | 370.781 | 0.042123 | 0.243669 | 1(Win) | true |
| Glaze | 4944.87 | 0.401663 | 104.227ms | 4669 | 640 | 8372.24 | 900.469 | 2.25577 | 0.597131 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2179.98 | 0.164493 | 351.601ms | 7932 | 640 | 20851.3 | 3470 | 0.18044 | 1.38756 | 1(Win) | true |
| Jsonifier | 1971.99 | 0.0945823 | 386.453ms | 7932 | 4890 | 64370.1 | 3835.99 | 0.0911108 | 1.53295 | 2(Loss) | true |
| Glaze | 1617.04 | 0.092488 | 470.747ms | 7932 | 2560 | 47921.8 | 4678.01 | 0.0208712 | 1.87148 | 3(Loss) | true |
| simdjson (ondemand) | 1304.51 | 0.104005 | 580.19ms | 7932 | 80 | 2909.81 | 5798.75 | 0.0215517 | 2.32225 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2415.24 | 0.0743335 | 330.773ms | 7932 | 4890 | 26504.7 | 3132 | 0.0681697 | 1.25083 | 1(Win) | true |
| Jsonifier | 2173.4 | 0.0774343 | 366.034ms | 7932 | 4890 | 35519.1 | 3480.51 | 0.0940876 | 1.39054 | 2(Loss) | true |
| Glaze | 1851.01 | 0.0963685 | 426.019ms | 7932 | 2560 | 39706.3 | 4086.72 | 0.0114714 | 1.63429 | 3(Loss) | true |
| simdjson (ondemand) | 1482.8 | 0.104112 | 526.63ms | 7932 | 2560 | 72217.3 | 5101.52 | 0.0973389 | 2.04225 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10603.1 | 0.128456 | 86.6875ms | 9249 | 4890 | 5583.9 | 831.881 | 0.212525 | 0.280467 | 1(Win) | true |
| Glaze | 3355.11 | 0.6376 | 282.644ms | 9249 | 1280 | 359652 | 2628.98 | 1.93216 | 0.89831 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11400.4 | 0.121992 | 79.6612ms | 9249 | 4890 | 4356.31 | 773.701 | 0.0290725 | 0.260642 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 4839.8 | 1.61398 | 218.143ms | 9249 | 40 | 34609 | 1822.5 | 3.05851 | 0.621402 | -(Loss) | false |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 413.177 | 0.101645 | 1068.5ms | 4604 | 1280 | 149340 | 10626.7 | 0.0632651 | 7.34034 | 1(Win) | true |
| Jsonifier (two-stage) | 406.054 | 0.147266 | 1100.55ms | 4604 | 320 | 81143.8 | 10813.1 | 0.017337 | 7.46081 | 2(Loss) | true |
| Glaze | 254.391 | 0.0485457 | 1732.36ms | 4604 | 2560 | 179726 | 17259.7 | 0.143013 | 11.932 | 3(Loss) | true |
| simdjson (ondemand) | 144.263 | 0.0304644 | 3047.44ms | 4604 | 4890 | 420389 | 30435.4 | 0.0890495 | 21.0525 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 513.684 | 0.102503 | 985.887ms | 4604 | 40 | 3070.51 | 8547.5 | 0.166016 | 5.9056 | 1(Win) | true |
| Jsonifier (two-stage) | 474.736 | 0.21177 | 1055.61ms | 4604 | 320 | 122757 | 9248.75 | 0.027038 | 6.38963 | 2(Loss) | true |
| Glaze | 289.539 | 0.112338 | 1639.39ms | 4604 | 640 | 185735 | 15164.5 | 0.0897222 | 10.4807 | 3(Loss) | true |
| simdjson (ondemand) | 152.427 | 0.0777297 | 3017.17ms | 4604 | 640 | 320848 | 28805.3 | 0.156466 | 19.9239 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1106.15 | 0.205938 | 399.496ms | 4604 | 160 | 10691.4 | 3969.38 | 0.0157431 | 2.72953 | 1(Win) | true |
| Glaze | 905.798 | 0.1145 | 489.112ms | 4604 | 1280 | 39430 | 4847.34 | 0.125555 | 3.33947 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1139.36 | 0.0603197 | 388.328ms | 4604 | 4890 | 26422.5 | 3853.66 | 0.0189685 | 2.63955 | 1(Win) | true |
| Glaze | 961.712 | 0.0869801 | 457.896ms | 4604 | 4890 | 77113.3 | 4565.52 | 0.354916 | 3.14683 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1478.4 | 0.130477 | 1176.57ms | 18245 | 640 | 150923 | 11769.4 | 0.0610322 | 2.05139 | 1(Win) | true |
| Jsonifier | 1241.2 | 0.0712481 | 1405.84ms | 18245 | 2560 | 255382 | 14018.5 | 0.0881308 | 2.44422 | 2(Loss) | true |
| Glaze | 878.334 | 0.128869 | 1990.43ms | 18245 | 30 | 19551.7 | 19810 | 0 | 3.45679 | 3(Loss) | true |
| simdjson (ondemand) | 554.273 | 0.0655035 | 3145.32ms | 18245 | 1280 | 541228 | 31392.1 | 0.165772 | 5.47951 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1740.14 | 0.0871012 | 1127.64ms | 18245 | 1280 | 97090.6 | 9999.06 | 0.0375176 | 1.74194 | 1(Win) | true |
| Jsonifier | 1443.44 | 0.0557205 | 1339.51ms | 18245 | 4890 | 220612 | 12054.4 | 0.034651 | 2.1008 | 2(Loss) | true |
| Glaze | 976.094 | 0.0853365 | 1904.55ms | 18245 | 1280 | 296199 | 17825.9 | 0.0490617 | 3.10937 | 3(Loss) | true |
| simdjson (ondemand) | 585.506 | 0.154618 | 3115.76ms | 18245 | 160 | 337805 | 29717.5 | 0.0840548 | 5.18587 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4114.37 | 0.172398 | 571.229ms | 24579 | 320 | 30869.8 | 5697.19 | 0.0933348 | 0.735629 | 1(Win) | true |
| Glaze | 2933.25 | 0.177299 | 804.918ms | 24579 | 1280 | 256952 | 7991.25 | 0.013685 | 1.0332 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4229.47 | 0.0772835 | 553.761ms | 24579 | 2560 | 46964.5 | 5542.15 | 0.0825327 | 0.715362 | 1(Win) | true |
| Glaze | 3311.85 | 0.196256 | 728.912ms | 24579 | 1280 | 246971 | 7077.73 | 0.0959397 | 0.914871 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 471.969 | 0.124163 | 929.327ms | 4604 | 640 | 85390.2 | 9302.97 | 0.0790022 | 6.4237 | 1(Win) | true |
| Jsonifier (two-stage) | 435.877 | 0.101667 | 1012.96ms | 4604 | 1280 | 134250 | 10073.3 | 0.110009 | 6.95426 | 2(Loss) | true |
| simdjson (ondemand) | 260.463 | 0.0387503 | 1691.81ms | 4604 | 4890 | 208660 | 16857.4 | 0.088905 | 11.6479 | 3(Loss) | true |
| Glaze | 255.933 | 0.0499358 | 1716.99ms | 4604 | 4890 | 358880 | 17155.7 | 0.12279 | 11.8576 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 606.872 | 0.105565 | 849.927ms | 4604 | 40 | 2333.33 | 7235 | 0.0230309 | 5.00799 | 1(Win) | true |
| Jsonifier (two-stage) | 521.872 | 0.0737663 | 968.803ms | 4604 | 2560 | 98605.1 | 8413.4 | 0.05893 | 5.80897 | 2(Loss) | true |
| simdjson (ondemand) | 292.607 | 0.0452716 | 1599.8ms | 4604 | 4890 | 225664 | 15005.5 | 0.141843 | 10.3723 | 3(Loss) | true |
| Glaze | 289.255 | 0.120757 | 1629.73ms | 4604 | 640 | 215036 | 15179.4 | 0.255934 | 10.4929 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 976.359 | 0.0991258 | 451.928ms | 4604 | 2560 | 50870.4 | 4497.03 | 0.00173723 | 3.09728 | 1(Win) | true |
| Glaze | 919.221 | 0.173627 | 482.714ms | 4604 | 640 | 44019.5 | 4776.56 | 0.0458175 | 3.29318 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1074.95 | 0.0664922 | 410.548ms | 4604 | 4890 | 36069.6 | 4084.56 | 0.039938 | 2.80413 | 1(Win) | true |
| Glaze | 1004.09 | 0.139775 | 441.681ms | 4604 | 320 | 11954.4 | 4372.81 | 0.0214439 | 3.01158 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1571.46 | 0.0930296 | 1105.55ms | 18245 | 1280 | 135810 | 11072.3 | 0.110193 | 1.92969 | 1(Win) | true |
| Jsonifier | 1416.77 | 0.0798346 | 1230.83ms | 18245 | 4890 | 470088 | 12281.3 | 0.0327656 | 2.14078 | 2(Loss) | true |
| simdjson (ondemand) | 986.426 | 0.100587 | 1772.96ms | 18245 | 1280 | 402949 | 17639.2 | 0.00265736 | 3.07576 | 3(Loss) | true |
| Glaze | 866.409 | 0.0983736 | 2016.06ms | 18245 | 640 | 249793 | 20082.7 | 0.0147848 | 3.50396 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1878.58 | 0.0784201 | 1055.87ms | 18245 | 1280 | 67529.2 | 9262.19 | 0.048946 | 1.61368 | 1(Win) | true |
| Jsonifier | 1672.16 | 0.0755777 | 1167.15ms | 18245 | 2560 | 158328 | 10405.5 | 0.0292898 | 1.81317 | 2(Loss) | true |
| simdjson (ondemand) | 1109.18 | 0.104872 | 1680.65ms | 18245 | 640 | 173212 | 15687 | 0.0865809 | 2.73604 | 3(Loss) | true |
| Glaze | 983.803 | 0.327741 | 1923.22ms | 18245 | 80 | 268796 | 17686.2 | 0.00706714 | 3.08574 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4356.35 | 0.0553827 | 540.299ms | 24579 | 4890 | 43425.1 | 5380.74 | 0.0334947 | 0.694451 | 1(Win) | true |
| Glaze | 3034.31 | 0.0904232 | 776.967ms | 24579 | 4890 | 238604 | 7725.11 | 0.236652 | 0.998404 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4557.01 | 0.0579326 | 516.97ms | 24579 | 4890 | 43423.5 | 5143.8 | 0.0800862 | 0.664317 | 1(Win) | true |
| Glaze | 3384.24 | 0.0964548 | 698.592ms | 24579 | 4890 | 218255 | 6926.34 | 0.0201351 | 0.895403 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 820.389 | 0.0815996 | 598.011ms | 5094 | 2560 | 59771.6 | 5921.6 | 0.0944206 | 3.69259 | 1(Win) | true |
| Jsonifier (two-stage) | 732.983 | 0.0779362 | 667.71ms | 5094 | 2560 | 68304.4 | 6627.73 | 0.114209 | 4.13244 | 2(Loss) | true |
| Glaze | 617.139 | 0.0723856 | 789.795ms | 5094 | 2560 | 83118.2 | 7871.84 | 0.155562 | 4.91036 | 3(Loss) | true |
| simdjson (ondemand) | 477.523 | 0.11126 | 1022.82ms | 5094 | 1280 | 163989 | 10173.4 | 0.00844802 | 6.35095 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 993.522 | 0.0654425 | 581.26ms | 5094 | 4890 | 50071.7 | 4889.69 | 0.0038766 | 3.04832 | 1(Win) | true |
| Jsonifier (two-stage) | 866.63 | 0.0620136 | 660.417ms | 5094 | 4890 | 59092.7 | 5605.64 | 0.0358938 | 3.49407 | 2(Loss) | true |
| Glaze | 814.57 | 0.129778 | 695.09ms | 5094 | 1280 | 76679 | 5963.91 | 0.0314292 | 3.71931 | 3(Loss) | true |
| simdjson (ondemand) | 579.375 | 0.0526887 | 949.194ms | 5094 | 4890 | 95442.7 | 8384.93 | 0.221184 | 5.23319 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8695.67 | 0.197879 | 58.0102ms | 5094 | 4890 | 5976.14 | 558.671 | 0.238095 | 0.337213 | 1(Win) | true |
| Glaze | 3315.61 | 0.143074 | 150.057ms | 5094 | 2560 | 11250.1 | 1465.2 | 0.0613562 | 0.90352 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11581.9 | 0.196498 | 44.1181ms | 5094 | 4890 | 3321.85 | 419.448 | 0.110619 | 0.251183 | 1(Win) | true |
| Glaze | 3872.86 | 0.322738 | 129.915ms | 5094 | 160 | 2622.25 | 1254.38 | 0.24975 | 0.770004 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1132.04 | 0.216943 | 679.693ms | 8051 | 40 | 8660.26 | 6782.5 | 0.0860797 | 2.67464 | 1(Win) | true |
| Jsonifier | 1031.79 | 0.0702982 | 748.471ms | 8051 | 2560 | 70056.4 | 7441.48 | 0.109066 | 2.93781 | 2(Loss) | true |
| Glaze | 863.367 | 0.0782647 | 891.338ms | 8051 | 2560 | 124017 | 8893.12 | 0.0773667 | 3.51072 | 3(Loss) | true |
| simdjson (ondemand) | 739.1 | 0.102433 | 1041.75ms | 8051 | 1280 | 144939 | 10388.4 | 0.0293383 | 4.10294 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1343.07 | 0.0630673 | 671.827ms | 8051 | 4890 | 63565.5 | 5716.79 | 0.239594 | 2.2551 | 1(Win) | true |
| Jsonifier | 1188.29 | 0.0700965 | 748.006ms | 8051 | 2560 | 52515.4 | 6461.41 | 0.0387062 | 2.55038 | 2(Loss) | true |
| Glaze | 1100.82 | 0.0571866 | 797.434ms | 8051 | 4890 | 77797.3 | 6974.83 | 0.0204741 | 2.75274 | 3(Loss) | true |
| simdjson (ondemand) | 887.626 | 0.127944 | 974.135ms | 8051 | 1280 | 156779 | 8650.08 | 0.130789 | 3.4154 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10883.1 | 0.141195 | 83.4487ms | 9255 | 4890 | 6411.96 | 811.002 | 0.131549 | 0.272616 | 1(Win) | true |
| Glaze | 3963.1 | 0.241111 | 223.275ms | 9255 | 2560 | 73817.4 | 2227.11 | 0.203874 | 0.759414 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13358.9 | 0.206434 | 68.5242ms | 9255 | 2560 | 4762.3 | 660.703 | 0.106534 | 0.221133 | 1(Win) | true |
| Glaze | 4302.46 | 0.200883 | 210.21ms | 9255 | 2560 | 43475.8 | 2051.45 | 0.173578 | 0.69608 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4653.44 | 0.119311 | 61.851ms | 2889 | 2560 | 1277.46 | 592.07 | 0.348455 | 0.632367 | 1(Win) | true |
| Jsonifier (two-stage) | 4622.03 | 0.109875 | 62.2843ms | 2889 | 4890 | 2097.65 | 596.094 | 0.124717 | 0.637829 | 2(Loss) | true |
| simdjson (ondemand) | 3754.74 | 0.133201 | 75.4991ms | 2889 | 4890 | 4671.51 | 733.783 | 0.308599 | 0.789871 | 3(Loss) | true |
| Glaze | 2836.72 | 0.369557 | 100.409ms | 2889 | 160 | 2061.32 | 971.25 | 0.517464 | 1.04649 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 5195.36 | 0.183265 | 56.9148ms | 2889 | 2560 | 2418.03 | 530.312 | 0.0589623 | 0.564434 | 1(Win) | true |
| Jsonifier | 5132.6 | 0.17819 | 57.9661ms | 2889 | 2560 | 2342.22 | 536.797 | 0.145328 | 0.571877 | 2(Loss) | true |
| simdjson (ondemand) | 4135.03 | 0.151765 | 70.6534ms | 2889 | 4890 | 5000.21 | 666.299 | 0.916391 | 0.714824 | 3(Loss) | true |
| Glaze | 2937.74 | 0.155217 | 100.927ms | 2889 | 2560 | 5424.85 | 937.852 | 0.523363 | 0.99858 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5385.12 | 0.256091 | 70.1733ms | 3808 | 640 | 1908.84 | 674.375 | 0.0463607 | 0.550861 | 1(Win) | true |
| Jsonifier (two-stage) | 5352 | 0.164536 | 70.0761ms | 3808 | 4890 | 6095.25 | 678.548 | 0.322439 | 0.553451 | 2(Loss) | true |
| simdjson (ondemand) | 4603.1 | 0.184213 | 81.1077ms | 3808 | 2560 | 5407.25 | 788.945 | 0.143792 | 0.645135 | 3(Loss) | true |
| Glaze | 3314.63 | 0.219354 | 112.918ms | 3808 | 160 | 924.135 | 1095.62 | 0.0570125 | 0.900556 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5936.51 | 0.120572 | 65.052ms | 3808 | 4890 | 2660.3 | 611.738 | 0.251599 | 0.496631 | 1(Win) | true |
| Jsonifier (two-stage) | 5897.28 | 0.132714 | 65.2636ms | 3808 | 4890 | 3266.12 | 615.808 | 0.284217 | 0.49982 | 2(Loss) | true |
| simdjson (ondemand) | 5087.49 | 0.188098 | 75.695ms | 3808 | 2560 | 4615.27 | 713.828 | 0.065624 | 0.58308 | 3(Loss) | true |
| Glaze | 3425.02 | 0.247163 | 109.555ms | 3808 | 1280 | 8791.15 | 1060.31 | 0.236337 | 0.862773 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1675.83 | 0.119459 | 167.873ms | 2889 | 640 | 2468.6 | 1644.06 | 0.227574 | 1.79303 | 1(Win) | true |
| Glaze | 1495.1 | 0.124168 | 187.074ms | 2889 | 4890 | 25602.7 | 1842.8 | 0.258686 | 2.01252 | 2(Loss) | true |
| Jsonifier (two-stage) | 1339.29 | 0.152316 | 208.926ms | 2889 | 1280 | 12567.5 | 2057.19 | 0.091227 | 2.24956 | 3(Loss) | true |
| simdjson (ondemand) | 1281.47 | 0.289694 | 216.857ms | 2889 | 320 | 12413.8 | 2150 | 0.0871333 | 2.34919 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2084.76 | 0.103297 | 151.346ms | 2889 | 4890 | 9113.09 | 1321.57 | 0.205286 | 1.43719 | 1(Win) | true |
| Glaze | 1815.59 | 0.140192 | 172.558ms | 2889 | 320 | 1448.28 | 1517.5 | 0.289137 | 1.65528 | 2(Loss) | true |
| Jsonifier (two-stage) | 1508.22 | 0.0708132 | 205.471ms | 2889 | 4890 | 8182.85 | 1826.77 | 0.0155786 | 1.99408 | 3(Loss) | true |
| simdjson (ondemand) | 1426.16 | 0.136162 | 208.205ms | 2889 | 640 | 4428.4 | 1931.88 | 0.0323415 | 2.1094 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10061.8 | 0.258652 | 30.6369ms | 2963 | 4890 | 2580.19 | 280.838 | 0.369457 | 0.283622 | 1(Win) | true |
| Glaze | 4613.45 | 0.788735 | 65.4351ms | 2963 | 80 | 1867.09 | 612.5 | 0 | 0.639301 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12477.7 | 0.329799 | 24.8591ms | 2963 | 4890 | 2727.71 | 226.462 | 1.33598 | 0.222271 | 1(Win) | true |
| Glaze | 5040.33 | 1.05505 | 58.3696ms | 2963 | 640 | 22390.8 | 560.625 | 1.81612 | 0.579563 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1695.15 | 0.136427 | 217.554ms | 3808 | 1280 | 10934.3 | 2142.34 | 0.00729395 | 1.77749 | 1(Win) | true |
| simdjson (ondemand) | 1658.35 | 0.103261 | 221.701ms | 3808 | 4890 | 25004.9 | 2189.88 | 0.306121 | 1.81845 | 2(Loss) | true |
| Jsonifier (two-stage) | 1633.87 | 0.10078 | 225.158ms | 3808 | 2560 | 12845.4 | 2222.7 | 0.0368926 | 1.84432 | 3(Loss) | true |
| Jsonifier | 1524.78 | 0.139816 | 240.591ms | 3808 | 2560 | 28387.8 | 2381.72 | 0.0689316 | 1.97473 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1955.33 | 0.106414 | 204.274ms | 3808 | 4890 | 19101.2 | 1857.28 | 0.12292 | 1.53802 | 1(Win) | true |
| Glaze | 1935.72 | 0.149532 | 204.934ms | 3808 | 2560 | 20147.3 | 1876.09 | 0.196103 | 1.55425 | 2(Loss) | true |
| simdjson (ondemand) | 1847.77 | 0.109522 | 211.859ms | 3808 | 2560 | 11861.5 | 1965.39 | 0.12704 | 1.62909 | 3(Loss) | true |
| Jsonifier | 1778.8 | 0.108487 | 224.681ms | 3808 | 4890 | 23988.5 | 2041.6 | 0.0232715 | 1.69113 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8191.36 | 0.233823 | 52.3842ms | 4300 | 320 | 438.48 | 500.625 | 0.249066 | 0.354427 | 1(Win) | true |
| Glaze | 3148.41 | 0.594935 | 141.685ms | 4300 | 80 | 4803.8 | 1302.5 | 0.191571 | 0.947674 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9809.43 | 0.295193 | 43.9161ms | 4300 | 1280 | 1949.27 | 418.047 | 0.168476 | 0.295863 | 1(Win) | true |
| Glaze | 5023.95 | 0.782464 | 98.2292ms | 4300 | 160 | 6526.73 | 816.25 | 1.55521 | 0.585596 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3168.6 | 0.0315483 | 7214.26ms | 466906 | 2560 | 5.03173e+06 | 140528 | 0.00111189 | 0.959076 | 1(Win) | true |
| Glaze | 1765.5 | 0.0286575 | 6428.2ms | 466906 | 640 | 3.34332e+06 | 252209 | 0.0645962 | 1.72143 | 2(Loss) | true |
| simdjson (ondemand) | 1452.63 | 0.239161 | 7867.45ms | 466906 | 80 | 4.29953e+07 | 306531 | 0.0191697 | 2.09197 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3182.99 | 0.0168891 | 7160.75ms | 466906 | 2560 | 1.42903e+06 | 139893 | 0.0962881 | 0.954687 | 1(Win) | true |
| Glaze | 1780.25 | 0.135485 | 6458.68ms | 466906 | 30 | 3.4451e+06 | 250120 | 0.0546106 | 1.70713 | 2(Loss) | true |
| simdjson (ondemand) | 1453.87 | 0.178245 | 7860.07ms | 466906 | 160 | 4.76831e+07 | 306271 | 0.00306111 | 2.09017 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2555.4 | 0.173148 | 6675.64ms | 699405 | 40 | 8.1702e+06 | 261018 | 0.0622176 | 1.18928 | 1(Win) | true |
| Jsonifier | 2405.8 | 0.0475415 | 7080.82ms | 699405 | 1280 | 2.22379e+07 | 277248 | 0.162517 | 1.26278 | 2(Loss) | true |
| simdjson (ondemand) | 1451.86 | 0.224701 | 6404.02ms | 767297 | 320 | 4.10428e+08 | 504009 | 0.177083 | 2.09263 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3904.24 | 0.080796 | 8770.8ms | 699405 | 320 | 6.09697e+06 | 170841 | 0.295271 | 0.778326 | 1(Win) | true |
| Glaze | 2538.24 | 0.097264 | 6677.81ms | 699405 | 640 | 4.18097e+07 | 262783 | 0.0713602 | 1.19733 | 2(Loss) | true |
| simdjson (ondemand) | 1140.27 | 0.308729 | 8171.08ms | 767297 | 160 | 6.28042e+08 | 641737 | 0.179754 | 2.66463 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2999.64 | 0.107137 | 5143.43ms | 631514 | 320 | 1.48066e+07 | 200777 | 0.180844 | 1.01313 | 1(Win) | true |
| Glaze | 2397.5 | 0.0536554 | 6441.99ms | 631514 | 160 | 2.90666e+06 | 251202 | 0.319986 | 1.26757 | 2(Loss) | true |
