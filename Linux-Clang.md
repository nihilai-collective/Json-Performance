# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson (AVX512)
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-1019-azure using the Clang 24.0.0 compiler).  

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
* **simdjson (reflection):** Absent from this run; current toolchain lacks P2996 static reflection support.
* **Jsonifier:** Evaluates both fused scalar structural iteration and two-stage indexing. Partial tests default strictly to two-stage parsing.
* **Summary Rows:** `*(combined)` metrics display best-of-variant ranks and are not additive with isolated test results.

---
*Environment generated via BenchmarkSuite commit: [71afc62](https://github.com/nihilai-collective/benchmarksuite/commit/71afc62)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1770 | 0.1077 | 49.912ms | 905 | 80 | 22.0631 | 487.613 | 0.0742866 | 1.32316 | 1(Win) | true |
| Glaze | 1339.51 | 0.463856 | 67.4853ms | 905 | 4890 | 43679.6 | 644.32 | 0.99465 | 1.76854 | 2(Loss) | true |
| Jsonifier (two-stage) | 493.263 | 0.0424942 | 181.805ms | 905 | 80 | 44.2272 | 1749.72 | 0.0772146 | 4.93996 | 3(Loss) | true |
| simdjson (ondemand) | 250.672 | 0.213926 | 355.565ms | 905 | 160 | 8680.22 | 3443.04 | 0.353952 | 9.79504 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1768.19 | 0.101589 | 51.8048ms | 905 | 80 | 19.6707 | 488.113 | 0.808034 | 1.32145 | 1(Win) | true |
| Glaze | 1320.63 | 0.485148 | 68.3071ms | 905 | 4890 | 49158.2 | 653.535 | 0.463278 | 1.79083 | 2(Loss) | true |
| Jsonifier (two-stage) | 479.202 | 0.0703287 | 181.597ms | 905 | 30 | 48.1333 | 1801.07 | 0.368786 | 5.08983 | 3(Loss) | true |
| simdjson (ondemand) | 245.84 | 0.258206 | 355.746ms | 905 | 80 | 6573.75 | 3510.71 | 0.0837425 | 9.98878 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2170.78 | 0.117189 | 44.6796ms | 905 | 160 | 34.7344 | 397.587 | 0.00314386 | 1.0611 | 1(Win) | true |
| Glaze | 186.817 | 0.568998 | 545.491ms | 905 | 640 | 442248 | 4619.89 | 0.0844888 | 13.1732 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3761.09 | 0.435293 | 30.7221ms | 905 | 80 | 79.8222 | 229.475 | 0.174008 | 0.57739 | 1(Win) | true |
| Glaze | 899.564 | 0.0804042 | 104.297ms | 905 | 160 | 95.2162 | 959.438 | 0.0273523 | 2.67249 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1245.09 | 0.0630009 | 142.384ms | 1811 | 160 | 122.195 | 1387.14 | 0.239373 | 1.94843 | 1(Win) | true |
| Glaze | 822.005 | 0.256539 | 214.781ms | 1811 | 2560 | 74376.2 | 2101.09 | 0.135368 | 2.97184 | 2(Loss) | true |
| Jsonifier (two-stage) | 442.157 | 0.167683 | 396.314ms | 1811 | 2560 | 109825 | 3906.09 | 0.247178 | 5.56015 | 3(Loss) | true |
| simdjson (ondemand) | 291.907 | 0.0458083 | 608.554ms | 1811 | 40 | 293.83 | 5916.62 | 0.136949 | 8.44028 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1318.97 | 0.51935 | 133.889ms | 1811 | 1280 | 59197 | 1309.44 | 0.146388 | 1.83777 | 1(Win) | true |
| Glaze | 868.557 | 0.0403038 | 202.664ms | 1811 | 40 | 25.6917 | 1988.47 | 0.310411 | 2.81064 | 2(Loss) | true |
| Jsonifier (two-stage) | 463.177 | 0.035136 | 386.702ms | 1811 | 40 | 68.6609 | 3728.82 | 0.279244 | 5.30577 | 3(Loss) | true |
| simdjson (ondemand) | 288.037 | 0.100415 | 598.645ms | 1811 | 80 | 2900.18 | 5996.11 | 0.0849187 | 8.55425 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 288.615 | 0.129624 | 610.141ms | 1811 | 4890 | 294224 | 5984.12 | 0.400677 | 8.53887 | 1(Win) | true |
| Glaze | 208.144 | 0.188487 | 833.571ms | 1798 | 2560 | 617245 | 8238.1 | 0.08168 | 11.8549 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 807.785 | 0.050557 | 226.72ms | 1811 | 40 | 46.7378 | 2138.07 | 0.0775019 | 3.02637 | 1(Win) | true |
| Glaze | 528.612 | 0.206613 | 334.416ms | 1798 | 4890 | 219649 | 3243.79 | 0.225215 | 4.64407 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2719.6 | 0.113626 | 141.532ms | 3862 | 40 | 94.7173 | 1354.28 | 0.291903 | 0.89251 | 1(Win) | true |
| Glaze | 1347.11 | 0.029907 | 278.944ms | 3862 | 80 | 53.488 | 2734.07 | 0.0292518 | 1.81946 | 2(Loss) | true |
| Jsonifier (two-stage) | 834.066 | 0.0393984 | 446.821ms | 3862 | 40 | 121.071 | 4415.82 | 0.0628027 | 2.95024 | 3(Loss) | true |
| simdjson (ondemand) | 644.051 | 0.0340928 | 582.694ms | 3862 | 30 | 114.033 | 5718.63 | 0.0122422 | 3.8257 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2756 | 0.065219 | 136.671ms | 3862 | 80 | 60.772 | 1336.39 | 0.00841751 | 0.879541 | 1(Win) | true |
| Glaze | 1379.43 | 0.0611608 | 285.566ms | 3862 | 30 | 80 | 2670 | 0.024975 | 1.77642 | 2(Loss) | true |
| Jsonifier (two-stage) | 849.013 | 0.156082 | 437.726ms | 3862 | 4890 | 224188 | 4338.09 | 0.0362681 | 2.89687 | 3(Loss) | true |
| simdjson (ondemand) | 661.902 | 0.0341032 | 568.688ms | 3862 | 40 | 144.041 | 5564.4 | 0.197892 | 3.72192 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 817.179 | 0.340567 | 491.793ms | 3862 | 1280 | 301582 | 4507.08 | 0.233876 | 3.01082 | 1(Win) | true |
| Glaze | 768.684 | 0.09373 | 483.394ms | 3862 | 40 | 806.763 | 4791.43 | 0.130089 | 3.20203 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4356.14 | 0.408118 | 92.9002ms | 3862 | 4890 | 58224.1 | 845.494 | 0.118764 | 0.550049 | 1(Win) | true |
| Glaze | 2336.64 | 0.191337 | 168.359ms | 3862 | 4890 | 44478.5 | 1576.23 | 0.634441 | 1.03916 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1731.48 | 0.0674263 | 538.046ms | 9578 | 40 | 506.097 | 5275.43 | 0.129521 | 1.42235 | 1(Win) | true |
| Glaze | 1350.68 | 0.102763 | 686.042ms | 9578 | 4890 | 236175 | 6762.76 | 0.152992 | 1.82564 | 2(Loss) | true |
| simdjson (ondemand) | 1201.2 | 0.0594594 | 769.49ms | 9578 | 40 | 817.743 | 7604.27 | 0.0803922 | 2.05335 | 3(Loss) | true |
| Jsonifier (two-stage) | 1018.88 | 0.33292 | 919.859ms | 9578 | 320 | 285057 | 8965.02 | 0.112777 | 2.42253 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2531.35 | 0.0268977 | 507.601ms | 9578 | 160 | 150.728 | 3608.46 | 0.160645 | 0.970798 | 1(Win) | true |
| Glaze | 1907.63 | 0.225788 | 630.551ms | 9578 | 1280 | 149614 | 4788.29 | 0.0309607 | 1.29042 | 2(Loss) | true |
| simdjson (ondemand) | 1561.21 | 0.0408651 | 733.611ms | 9578 | 30 | 171.495 | 5850.77 | 0.112679 | 1.57851 | 3(Loss) | true |
| Jsonifier (two-stage) | 1260.72 | 0.227936 | 867.882ms | 9578 | 640 | 174548 | 7245.27 | 0.0501153 | 1.95641 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3958.58 | 0.621864 | 221.195ms | 9578 | 30 | 6177.09 | 2307.47 | 0.289754 | 0.61738 | 1(Win) | true |
| Glaze | 1846.6 | 0.19788 | 492.9ms | 9578 | 4890 | 468511 | 4946.55 | 0.101492 | 1.33322 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12707.3 | 0.095648 | 82.8944ms | 9578 | 80 | 37.8171 | 718.825 | 0.0696064 | 0.187431 | 1(Win) | true |
| Glaze | 4994.69 | 0.126236 | 194.107ms | 9578 | 30 | 159.89 | 1828.8 | 0.109481 | 0.488345 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2823.74 | 0.0361514 | 134.655ms | 3873 | 160 | 35.7779 | 1308.04 | 0.329338 | 0.858385 | 1(Win) | true |
| Glaze | 1347.36 | 0.0489064 | 282.227ms | 3873 | 80 | 143.796 | 2741.34 | 0.0378322 | 1.81933 | 2(Loss) | true |
| Jsonifier (two-stage) | 838.688 | 0.0201632 | 491.562ms | 3873 | 160 | 126.164 | 4404 | 0.44139 | 2.93358 | 3(Loss) | true |
| simdjson (ondemand) | 606.383 | 0.0604212 | 614.836ms | 3873 | 30 | 406.351 | 6091.17 | 0.218963 | 4.06414 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3036.32 | 0.0857871 | 126.574ms | 3873 | 30 | 32.6713 | 1216.47 | 0.248736 | 0.797711 | 1(Win) | true |
| Glaze | 1368.11 | 0.0556719 | 273.041ms | 3873 | 30 | 67.7713 | 2699.77 | 0.212816 | 1.7906 | 2(Loss) | true |
| Jsonifier (two-stage) | 853.06 | 0.064001 | 450.215ms | 3873 | 30 | 230.372 | 4329.8 | 0.0762741 | 2.88417 | 3(Loss) | true |
| simdjson (ondemand) | 618.69 | 0.0405893 | 622.425ms | 3873 | 40 | 234.872 | 5970 | 0.389321 | 3.98207 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 865.93 | 0.0570752 | 432.722ms | 3873 | 40 | 237.074 | 4265.45 | 0.100319 | 2.84082 | 1(Win) | true |
| Glaze | 781.861 | 0.264217 | 482.865ms | 3873 | 640 | 99709.9 | 4724.09 | 0.0836177 | 3.1483 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4727.56 | 0.0766474 | 87.5974ms | 3873 | 80 | 28.6884 | 781.288 | 0.0176023 | 0.505651 | 1(Win) | true |
| Glaze | 2378.3 | 0.0878372 | 164.241ms | 3873 | 30 | 55.8264 | 1553.03 | 0.0945281 | 1.02307 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1560.89 | 0.152179 | 5773.71ms | 94653 | 320 | 2.4785e+06 | 57831.4 | 0.270164 | 1.58537 | 1(Win) | true |
| Jsonifier (two-stage) | 1433.19 | 0.082476 | 6304.23ms | 94653 | 1280 | 3.45406e+06 | 62984.3 | 0.171819 | 1.7267 | 2(Loss) | true |
| Glaze | 1382.4 | 0.0680098 | 6618.22ms | 94653 | 1280 | 2.52439e+06 | 65298.3 | 0.129925 | 1.79019 | 3(Loss) | true |
| simdjson (ondemand) | 1036.03 | 0.124023 | 8733.73ms | 94653 | 2560 | 2.98931e+07 | 87128.8 | 0.445007 | 2.38894 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2315.85 | 0.111104 | 5151.92ms | 94653 | 640 | 1.20029e+06 | 38978.3 | 0.0116758 | 1.06831 | 1(Win) | true |
| Jsonifier (two-stage) | 1961.59 | 0.12203 | 5894.54ms | 94653 | 1280 | 4.03643e+06 | 46017.9 | 0.00335649 | 1.26136 | 2(Loss) | true |
| Glaze | 1864.92 | 0.136913 | 6236.75ms | 94653 | 1280 | 5.62143e+06 | 48403.2 | 0.54033 | 1.32671 | 3(Loss) | true |
| simdjson (ondemand) | 1343.13 | 0.0590031 | 8128.56ms | 94653 | 4890 | 7.68934e+06 | 67207.1 | 0.540949 | 1.84247 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17481.9 | 0.0275354 | 520.647ms | 94653 | 80 | 161.721 | 5163.52 | 0.0198547 | 0.14087 | 1(Win) | true |
| Glaze | 5147.54 | 0.286701 | 1789.05ms | 94653 | 640 | 1.61774e+06 | 17536.2 | 0.088871 | 0.480217 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17776.1 | 0.0455237 | 530.654ms | 94653 | 40 | 213.763 | 5078.07 | 0.0496989 | 0.138511 | 1(Win) | true |
| Glaze | 5620.79 | 0.100736 | 1621.91ms | 94653 | 4890 | 1.27982e+06 | 16059.7 | 0.167751 | 0.439713 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1793.11 | 0.152421 | 6749.1ms | 124597 | 640 | 6.52938e+06 | 66267.7 | 0.01122 | 1.38014 | 1(Win) | true |
| Jsonifier | 1678.55 | 0.209187 | 7204.21ms | 124597 | 160 | 3.50862e+06 | 70790.2 | 0.135895 | 1.47439 | 2(Loss) | true |
| Glaze | 1562.21 | 0.188738 | 7522ms | 124597 | 1280 | 2.63796e+07 | 76062.2 | 0.0971283 | 1.58423 | 3(Loss) | true |
| simdjson (ondemand) | 1356.23 | 0.129394 | 8884.99ms | 124597 | 1280 | 1.64508e+07 | 87614 | 0.176012 | 1.82492 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2494.29 | 0.0640844 | 6130.32ms | 124597 | 4890 | 4.55757e+06 | 47638.7 | 0.250421 | 0.992003 | 1(Win) | true |
| Jsonifier | 2261.8 | 0.081189 | 6600.65ms | 124597 | 2560 | 4.65735e+06 | 52535.5 | 0.34566 | 1.09405 | 2(Loss) | true |
| Glaze | 2089.97 | 0.163033 | 7015.2ms | 124597 | 1280 | 1.09976e+07 | 56855 | 0.16563 | 1.18404 | 3(Loss) | true |
| simdjson (ondemand) | 1722.18 | 0.198516 | 8362.25ms | 124597 | 80 | 1.50086e+06 | 68996.6 | 0.0467196 | 1.43697 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18539.9 | 0.400024 | 719.949ms | 136037 | 640 | 501478 | 6997.61 | 0.030913 | 0.133018 | 1(Win) | true |
| Glaze | 5660.24 | 0.323724 | 2307.32ms | 136076 | 4890 | 2.69372e+07 | 22927 | 0.305264 | 0.436872 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18600.7 | 0.282066 | 704.853ms | 136037 | 1280 | 495413 | 6974.74 | 0.0365963 | 0.132579 | 1(Win) | true |
| Glaze | 6177.73 | 0.540187 | 2105.7ms | 136076 | 160 | 2.06022e+06 | 21006.5 | 0.661768 | 0.400229 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 781.227 | 0.694031 | 8323.73ms | 2251027 | 40 | 1.45487e+10 | 2.74792e+06 | 0.488172 | 3.16903 | 1(Win) | true |
| Jsonifier (two-stage) | 719.323 | 0.116093 | 9412.71ms | 2251027 | 160 | 1.92065e+09 | 2.9844e+06 | 0.587668 | 3.44176 | 2(Loss) | true |
| Glaze DID NOT CONVERGE | 713.175 | 0.180511 | 9476.32ms | 2251027 | 160 | 4.72384e+09 | 3.01012e+06 | 2.56491 | 3.47139 | -(Loss) | false |
| simdjson (ondemand) | 688.189 | 0.137497 | 9774.69ms | 2251027 | 30 | 5.5189e+08 | 3.11942e+06 | 0.209649 | 3.59745 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 966.5 | 0.0878234 | 8354.91ms | 2251027 | 160 | 6.08834e+08 | 2.22116e+06 | 0.194812 | 2.56158 | 1(Win) | true |
| Glaze | 855.413 | 0.145558 | 9461.54ms | 2251027 | 40 | 5.33755e+08 | 2.5096e+06 | 0.0644205 | 2.8942 | 2(Loss) | true |
| Jsonifier (two-stage) | 849.369 | 0.172158 | 9372.27ms | 2251027 | 40 | 7.57324e+08 | 2.52746e+06 | 0.419447 | 2.91482 | 3(Loss) | true |
| simdjson (ondemand) | 832.766 | 0.153019 | 9654.91ms | 2251027 | 40 | 6.22391e+08 | 2.57785e+06 | 0.191016 | 2.9729 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1853.17 | 0.0996613 | 6986.73ms | 2090234 | 80 | 9.19397e+07 | 1.07567e+06 | 0.407152 | 1.33593 | 1(Win) | true |
| Glaze | 922.324 | 0.100636 | 6742.79ms | 2090234 | 30 | 1.41921e+08 | 2.16128e+06 | 0.0603324 | 2.68428 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1819.23 | 0.539859 | 6899.39ms | 2090234 | 320 | 1.11976e+10 | 1.09574e+06 | 0.142903 | 1.36084 | 1(Win) | true |
| Glaze | 933.045 | 0.0937711 | 6642.57ms | 2090234 | 30 | 1.20405e+08 | 2.13645e+06 | 0.255441 | 2.65343 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1563.02 | 0.192041 | 10159ms | 5373214 | 80 | 3.17118e+09 | 3.27846e+06 | 0.558202 | 1.58391 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1562.48 | 0.464464 | 10093ms | 5373214 | 80 | 1.85623e+10 | 3.27959e+06 | 0.671208 | 1.58445 | 1(Tie) | true |
| simdjson (ondemand) | 1550.07 | 0.129768 | 5110.51ms | 5373214 | 30 | 5.52106e+08 | 3.30586e+06 | 1.71256 | 1.59718 | 3(Loss) | true |
| Glaze | 1439.85 | 0.622154 | 5403.09ms | 5373214 | 80 | 3.9221e+10 | 3.5589e+06 | 0.460783 | 1.71941 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1879.94 | 0.237727 | 10074.4ms | 5373214 | 30 | 1.25968e+09 | 2.72578e+06 | 0.193385 | 1.31693 | 1(Win) | true |
| Jsonifier | 1836.66 | 0.174562 | 10215.5ms | 5373214 | 40 | 9.48789e+08 | 2.79001e+06 | 0.224536 | 1.34797 | 2(Loss) | true |
| simdjson (ondemand) | 1802.17 | 0.247334 | 5033.41ms | 5373214 | 80 | 3.9567e+09 | 2.8434e+06 | 0.637848 | 1.37372 | 3(Loss) | true |
| Glaze | 1710.51 | 0.112979 | 5330.55ms | 5373214 | 40 | 4.58214e+08 | 2.99577e+06 | 0.804985 | 1.44739 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5142.24 | 0.0644843 | 7826.43ms | 6661897 | 320 | 2.03118e+08 | 1.23551e+06 | 0.398835 | 0.481444 | 1(Win) | true |
| Glaze | 2689.16 | 0.255568 | 7299.14ms | 6661897 | 160 | 5.83306e+09 | 2.36255e+06 | 1.12471 | 0.920532 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5207.53 | 0.100053 | 7800.91ms | 6661897 | 30 | 4.47005e+07 | 1.22002e+06 | 0.0631149 | 0.475399 | 1(Win) | true |
| Glaze | 3243.21 | 0.181224 | 6113.2ms | 6661897 | 80 | 1.00825e+09 | 1.95895e+06 | 0.481218 | 0.763359 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1993.15 | 0.17155 | 6237.54ms | 500299 | 160 | 2.69825e+07 | 239382 | 0.343977 | 1.24191 | 1(Win) | true |
| Jsonifier (two-stage) | 1744.21 | 0.19494 | 6996.64ms | 500299 | 160 | 4.54972e+07 | 273547 | 0.303297 | 1.41918 | 2(Loss) | true |
| Glaze | 1412.66 | 0.187236 | 8623.97ms | 500299 | 80 | 3.19927e+07 | 337747 | 0.629593 | 1.75239 | 3(Loss) | true |
| simdjson (ondemand) | 1051.22 | 0.215962 | 5862.2ms | 500299 | 40 | 3.84314e+07 | 453875 | 0.204283 | 2.35492 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2443.35 | 0.114418 | 5882.55ms | 500299 | 640 | 3.19489e+07 | 195274 | 0.359784 | 1.0131 | 1(Win) | true |
| Jsonifier (two-stage) | 2039.33 | 0.122694 | 6785.79ms | 500299 | 640 | 5.27361e+07 | 233960 | 0.0151785 | 1.21384 | 2(Loss) | true |
| Glaze | 1649.81 | 0.12718 | 8423.25ms | 500299 | 320 | 4.32893e+07 | 289199 | 0.535563 | 1.50052 | 3(Loss) | true |
| simdjson (ondemand) | 1173.93 | 0.182382 | 5665.59ms | 500299 | 640 | 3.51658e+08 | 406432 | 0.262502 | 2.10879 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9980.17 | 0.0960402 | 4798.84ms | 500299 | 2560 | 5.39672e+06 | 47807 | 0.158714 | 0.247894 | 1(Win) | true |
| Glaze | 3664.08 | 0.179288 | 6799.79ms | 500299 | 320 | 1.74415e+07 | 130216 | 0.0168546 | 0.675496 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9887.28 | 0.120567 | 4865.46ms | 500299 | 1280 | 4.33283e+06 | 48256.2 | 0.744951 | 0.250216 | 1(Win) | true |
| Glaze | 3890.87 | 0.0739939 | 6301.64ms | 500299 | 2560 | 2.10765e+07 | 122626 | 0.353096 | 0.63616 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3584.95 | 0.243349 | 7854.54ms | 1151920 | 30 | 1.66824e+07 | 306435 | 0.394937 | 0.690499 | 1(Win) | true |
| Jsonifier | 2949.04 | 0.192706 | 9692.42ms | 1151920 | 1280 | 6.59603e+08 | 372513 | 0.193678 | 0.839429 | 2(Loss) | true |
| Glaze | 2288.52 | 0.237698 | 6160.73ms | 1151920 | 80 | 1.04154e+08 | 480030 | 0.0859832 | 1.08174 | 3(Loss) | true |
| simdjson (ondemand) | 2234.55 | 0.10045 | 6329.77ms | 1151920 | 160 | 3.90193e+07 | 491622 | 0.100074 | 1.10787 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4171.71 | 0.0858878 | 7647.07ms | 1151920 | 1280 | 6.5477e+07 | 263335 | 0.233206 | 0.593396 | 1(Win) | true |
| Jsonifier | 3282.14 | 0.143461 | 9425.73ms | 1151920 | 1280 | 2.95126e+08 | 334707 | 0.144927 | 0.754256 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 2561.88 | 0.103606 | 5962.08ms | 1151920 | 320 | 6.31609e+07 | 428809 | 0.186083 | 0.966319 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 2554.14 | 0.268498 | 6005.86ms | 1151920 | 40 | 5.33457e+07 | 430108 | 0.0499547 | 0.969267 | 3(Tie) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16459.9 | 0.342264 | 8386.8ms | 1439562 | 160 | 1.30391e+07 | 83407.2 | 0.456192 | 0.150358 | 1(Win) | true |
| Glaze | 4788.35 | 0.285383 | 7523.13ms | 1439584 | 80 | 5.35612e+07 | 286716 | 0.382317 | 0.516964 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16227.5 | 0.193998 | 8453.49ms | 1439562 | 160 | 4.30992e+06 | 84601.6 | 0.0148586 | 0.152506 | 1(Win) | true |
| Glaze | 5808.67 | 0.159858 | 6170.48ms | 1439584 | 320 | 4.56815e+07 | 236353 | 0.590144 | 0.426175 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2072.55 | 0.171234 | 2597.4ms | 56369 | 4890 | 9.64628e+06 | 25938 | 0.0117115 | 1.19316 | 1(Win) | true |
| Jsonifier (two-stage) | 1695.48 | 0.131066 | 3220.76ms | 56369 | 1280 | 2.21047e+06 | 31706.4 | 0.199344 | 1.45892 | 2(Loss) | true |
| Glaze | 1515.73 | 0.07624 | 3616.27ms | 56369 | 2560 | 1.87174e+06 | 35466.6 | 0.716615 | 1.63198 | 3(Loss) | true |
| simdjson (ondemand) | 786.845 | 0.160916 | 6828.15ms | 56369 | 1280 | 1.54708e+07 | 68320.5 | 0.154852 | 3.14521 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2741.37 | 0.215996 | 2322.7ms | 56369 | 1280 | 2.2964e+06 | 19609.8 | 0.0258109 | 0.901824 | 1(Win) | true |
| Jsonifier (two-stage) | 2139.92 | 0.151401 | 2886.03ms | 56369 | 1280 | 1.85161e+06 | 25121.3 | 0.0242632 | 1.15565 | 2(Loss) | true |
| Glaze | 1881.75 | 0.0916382 | 3219.19ms | 56369 | 2560 | 1.75448e+06 | 28567.9 | 0.00967773 | 1.3144 | 3(Loss) | true |
| simdjson (ondemand) | 904.329 | 0.0662183 | 6298.86ms | 56369 | 2560 | 3.96666e+06 | 59444.8 | 0.12988 | 2.73633 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15200.2 | 0.0864307 | 363.418ms | 56369 | 30 | 280.309 | 3536.63 | 0.319432 | 0.161588 | 1(Win) | true |
| Glaze | 3609.07 | 0.0992417 | 1528.06ms | 56369 | 2560 | 559395 | 14895.2 | 0.643989 | 0.684735 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15109.5 | 0.366188 | 355.822ms | 56369 | 1280 | 217269 | 3557.87 | 0.124549 | 0.162568 | 1(Win) | true |
| Glaze | 3791.99 | 0.117056 | 1420.62ms | 56369 | 2560 | 704978 | 14176.6 | 0.1213 | 0.651621 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2336.06 | 0.265433 | 3390.01ms | 83958 | 160 | 1.3243e+06 | 34275 | 0.087469 | 1.05891 | 1(Win) | true |
| Jsonifier | 1938.01 | 0.277283 | 4162.52ms | 83958 | 160 | 2.09982e+06 | 41314.9 | 0.504515 | 1.27659 | 2(Loss) | true |
| Glaze | 1704.39 | 0.060207 | 4700.1ms | 83958 | 4890 | 3.91189e+06 | 46977.7 | 0.384722 | 1.45172 | 3(Loss) | true |
| simdjson (ondemand) | 1183.62 | 0.110279 | 6857.7ms | 83958 | 640 | 3.56174e+06 | 67647.1 | 0.0381837 | 2.09086 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3019.48 | 0.110199 | 3061.07ms | 83958 | 2560 | 2.18604e+06 | 26517.3 | 0.0596821 | 0.819064 | 1(Win) | true |
| Jsonifier | 2333.52 | 0.217363 | 3868.14ms | 83958 | 320 | 1.78e+06 | 34312.3 | 0.0613403 | 1.06011 | 2(Loss) | true |
| Glaze | 2150.91 | 0.0728218 | 4079.13ms | 83958 | 4890 | 3.59346e+06 | 37225.5 | 0.373574 | 1.1502 | 3(Loss) | true |
| simdjson (ondemand) | 1350.45 | 0.179861 | 6424.14ms | 83958 | 160 | 1.81954e+06 | 59290.3 | 0.036523 | 1.83242 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17127.8 | 0.443725 | 516.887ms | 94370 | 640 | 347917 | 5254.53 | 0.238398 | 0.143774 | 1(Win) | true |
| Glaze | 3136.84 | 0.0675895 | 2890.31ms | 94370 | 4890 | 1.83887e+06 | 28690.7 | 0.354878 | 0.788496 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17876.6 | 0.130023 | 507.362ms | 94370 | 4890 | 209531 | 5034.42 | 0.0990108 | 0.137704 | 1(Win) | true |
| Glaze | 3370.67 | 0.0698122 | 2680.96ms | 94370 | 4890 | 1.69905e+06 | 26700.4 | 0.219549 | 0.733748 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1647.06 | 0.216734 | 3077.95ms | 53331 | 1280 | 5.73334e+06 | 30879.6 | 0.300957 | 1.50172 | 1(Win) | true |
| Jsonifier | 1597.86 | 0.598991 | 3199.4ms | 53331 | 160 | 5.81627e+06 | 31830.4 | 0.610133 | 1.54802 | 2(Loss) | true |
| Glaze | 1334.15 | 0.0864782 | 3814.3ms | 53331 | 2560 | 2.78228e+06 | 38121.8 | 0.401274 | 1.85433 | 3(Loss) | true |
| simdjson (ondemand) | 989.229 | 0.0697927 | 5232.68ms | 53331 | 4890 | 6.29644e+06 | 51414.2 | 0.301863 | 2.50127 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2194.31 | 0.192659 | 2842.82ms | 53331 | 1280 | 2.55242e+06 | 23178.3 | 0.598599 | 1.1269 | 1(Win) | true |
| Jsonifier | 2141.51 | 0.230046 | 3068.52ms | 53331 | 320 | 955210 | 23749.8 | 0.755582 | 1.15473 | 2(Loss) | true |
| Glaze | 1701.96 | 0.0952824 | 3584.62ms | 53331 | 2560 | 2.07551e+06 | 29883.4 | 0.320382 | 1.45329 | 3(Loss) | true |
| simdjson (ondemand) | 1064.15 | 0.129251 | 5430.61ms | 53331 | 1280 | 4.88462e+06 | 47794.2 | 0.196621 | 2.32507 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16115.1 | 0.309227 | 349.647ms | 58581 | 2560 | 294202 | 3466.77 | 0.519734 | 0.152319 | 1(Win) | true |
| Glaze | 5550.4 | 0.350867 | 1021.77ms | 58581 | 160 | 199558 | 10065.4 | 0.220257 | 0.444819 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15951.8 | 0.382416 | 341.038ms | 58581 | 40 | 7175.06 | 3502.25 | 0.0461821 | 0.153919 | 1(Win) | true |
| Glaze | 6235.55 | 0.123523 | 908.091ms | 58581 | 4890 | 598923 | 8959.47 | 0.186677 | 0.395823 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2001.08 | 0.756092 | 3105.28ms | 65103 | 80 | 4.40265e+06 | 31026.8 | 0.283224 | 1.23611 | 1(Win) | true |
| Glaze | 1704.57 | 0.0983493 | 3683.33ms | 65103 | 2560 | 3.28517e+06 | 36424 | 0.231457 | 1.45136 | 2(Loss) | true |
| Jsonifier | 1449.28 | 0.279343 | 4256.95ms | 65103 | 1280 | 1.83307e+07 | 42839.8 | 0.0706658 | 1.70675 | 3(Loss) | true |
| simdjson (ondemand) | 1185.04 | 0.0576871 | 5400.12ms | 65103 | 4890 | 4.46686e+06 | 52392.3 | 0.34525 | 2.08798 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2653.91 | 0.0917476 | 2829.56ms | 65103 | 4890 | 2.25284e+06 | 23394.6 | 0.474995 | 0.93174 | 1(Win) | true |
| Glaze | 2176.65 | 0.0783533 | 3379.95ms | 65103 | 4890 | 2.44258e+06 | 28524.1 | 0.319003 | 1.13633 | 2(Loss) | true |
| Jsonifier | 1851.58 | 0.339281 | 3910.8ms | 65103 | 320 | 4.14178e+06 | 33532 | 0.275804 | 1.33586 | 3(Loss) | true |
| simdjson (ondemand) | 1263.43 | 0.273467 | 5435.89ms | 65103 | 320 | 5.77908e+06 | 49141.6 | 0.267089 | 1.95838 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16690.1 | 0.072964 | 461.558ms | 78778 | 160 | 1725.96 | 4501.39 | 0.35993 | 0.147422 | 1(Win) | true |
| Glaze | 4894.75 | 0.426942 | 1547.83ms | 78778 | 80 | 343540 | 15348.8 | 0.104053 | 0.5049 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16717.8 | 0.200415 | 459.798ms | 78778 | 4890 | 396661 | 4493.92 | 0.352898 | 0.1472 | 1(Win) | true |
| Glaze | 5314.45 | 0.249529 | 1418.9ms | 78778 | 1280 | 1.59273e+06 | 14136.6 | 0.338686 | 0.464937 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2285.91 | 0.127622 | 493.648ms | 11812 | 40 | 1582.12 | 4927.93 | 0.428526 | 1.07696 | 1(Win) | true |
| Jsonifier (two-stage) | 1751.51 | 0.0929529 | 650.968ms | 11812 | 80 | 2859.14 | 6431.46 | 0.13604 | 1.40736 | 2(Loss) | true |
| Glaze | 1647.29 | 0.146903 | 690.343ms | 11812 | 2560 | 258348 | 6838.37 | 0.501324 | 1.49701 | 3(Loss) | true |
| simdjson (ondemand) | 899.492 | 0.402929 | 1253.05ms | 11812 | 320 | 814816 | 12523.5 | 0.162709 | 2.74611 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2573.48 | 0.179813 | 480.967ms | 11812 | 2560 | 158594 | 4377.26 | 0.0655896 | 0.955975 | 1(Win) | true |
| Glaze | 1873.63 | 0.0864585 | 733.187ms | 11812 | 40 | 1080.82 | 6012.27 | 0.35619 | 1.31578 | 2(Loss) | true |
| Jsonifier (two-stage) | 1867.81 | 0.104106 | 637.026ms | 11812 | 30 | 1182.65 | 6031.03 | 0.181059 | 1.31915 | 3(Loss) | true |
| simdjson (ondemand) | 944.298 | 0.259552 | 1258.8ms | 11812 | 640 | 613560 | 11929.3 | 0.197133 | 2.61335 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11689.1 | 0.142607 | 101.468ms | 11812 | 40 | 75.5487 | 963.7 | 0.267046 | 0.205748 | 1(Win) | true |
| Glaze | 2684.5 | 0.139983 | 424.215ms | 11812 | 4890 | 168726 | 4196.24 | 0.0948022 | 0.91607 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11605.1 | 0.441611 | 96.4087ms | 11812 | 160 | 2940.01 | 970.675 | 0.382287 | 0.207111 | 1(Win) | true |
| Glaze | 2957.75 | 0.0901685 | 397.634ms | 11812 | 80 | 943.463 | 3808.57 | 0.0354338 | 0.83104 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3329.29 | 0.167695 | 737.96ms | 25388 | 2560 | 380746 | 7272.39 | 0.170158 | 0.740743 | 1(Win) | true |
| Jsonifier | 2994.63 | 0.280694 | 828.142ms | 25388 | 640 | 329622 | 8085.1 | 0.0745561 | 0.824008 | 2(Loss) | true |
| Glaze | 2361.27 | 0.207756 | 1028.39ms | 25388 | 80 | 36304.7 | 10253.8 | 0.565412 | 1.04566 | 3(Loss) | true |
| simdjson (ondemand) | 1845.27 | 0.13056 | 1316.88ms | 25388 | 2560 | 751269 | 13121 | 0.199296 | 1.33886 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3577.3 | 0.468901 | 724.615ms | 25388 | 30 | 30215.5 | 6768.2 | 0.0689024 | 0.689121 | 1(Win) | true |
| Jsonifier | 3105.52 | 0.129598 | 824.631ms | 25388 | 2560 | 261353 | 7796.41 | 0.13704 | 0.794449 | 2(Loss) | true |
| Glaze | 2523.59 | 0.0893676 | 1060.47ms | 25388 | 4890 | 359490 | 9594.2 | 0.499032 | 0.978168 | 3(Loss) | true |
| simdjson (ondemand) | 1913.96 | 0.169162 | 1327.89ms | 25388 | 1280 | 586145 | 12650.1 | 0.31291 | 1.29043 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17599.3 | 0.360258 | 173.542ms | 31235 | 30 | 1115.43 | 1692.57 | 0.0827831 | 0.138426 | 1(Win) | true |
| Glaze | 4891.15 | 0.307335 | 614.659ms | 31235 | 640 | 224215 | 6090.19 | 0.214281 | 0.503877 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18071.8 | 0.345147 | 167.762ms | 31235 | 4890 | 158271 | 1648.32 | 0.809501 | 0.134695 | 1(Win) | true |
| Glaze | 5327.2 | 0.34192 | 557.583ms | 31235 | 320 | 116973 | 5591.68 | 0.0786822 | 0.462468 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2663.63 | 0.174645 | 3875.75ms | 108313 | 1280 | 5.87133e+06 | 38779.9 | 0.279256 | 0.928818 | 1(Win) | true |
| Jsonifier (two-stage) | 2264.92 | 0.581758 | 4651.29ms | 108313 | 80 | 5.63157e+06 | 45606.6 | 0.235648 | 1.09239 | 2(Loss) | true |
| Glaze | 1599.31 | 0.0882751 | 6460.72ms | 108313 | 1280 | 4.16087e+06 | 64587.5 | 0.033344 | 1.54737 | 3(Loss) | true |
| simdjson (ondemand) | 661.684 | 0.728317 | 8062.75ms | 108313 | 30 | 3.87812e+07 | 156110 | 0.338554 | 3.74105 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3070.23 | 0.102279 | 3552.78ms | 108313 | 2560 | 3.03135e+06 | 33644.2 | 0.0864125 | 0.805729 | 1(Win) | true |
| Jsonifier (two-stage) | 2529.93 | 0.0722467 | 4280.67ms | 108313 | 4890 | 4.25491e+06 | 40829.4 | 0.429196 | 0.977926 | 2(Loss) | true |
| Glaze | 1742.21 | 0.0736006 | 6135.81ms | 108313 | 2560 | 4.8749e+06 | 59290 | 0.319954 | 1.42043 | 3(Loss) | true |
| simdjson (ondemand) | 675.665 | 0.148234 | 7926.39ms | 108313 | 2560 | 1.31473e+08 | 152880 | 0.274863 | 3.66356 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19788.9 | 0.431922 | 528.069ms | 108313 | 640 | 325320 | 5219.87 | 0.236796 | 0.124438 | 1(Win) | true |
| Glaze | 3650.73 | 0.778997 | 2987.55ms | 108313 | 40 | 1.94327e+06 | 28294.5 | 0.0706763 | 0.67755 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20280.7 | 0.339745 | 512.193ms | 108313 | 640 | 191638 | 5093.28 | 0.824932 | 0.121422 | 1(Win) | true |
| Glaze | 3818.05 | 0.319886 | 2696.77ms | 108313 | 320 | 2.39673e+06 | 27054.5 | 0.466223 | 0.647793 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3369.92 | 0.527186 | 5113.78ms | 183677 | 80 | 6.00742e+06 | 51979.9 | 0.0237648 | 0.734256 | 1(Win) | true |
| Jsonifier | 2146.41 | 0.152064 | 8215.79ms | 183677 | 320 | 4.92816e+06 | 81609.7 | 0.0215078 | 1.15309 | 2(Loss) | true |
| Glaze | 2117.39 | 0.0621455 | 8356.55ms | 183677 | 2560 | 6.76653e+06 | 82728.2 | 0.113951 | 1.1689 | 3(Loss) | true |
| simdjson (ondemand) | 1126.32 | 0.274876 | 8104.17ms | 183677 | 80 | 1.46201e+07 | 155523 | 0.706968 | 2.19775 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3748.22 | 0.22281 | 4820.4ms | 183677 | 160 | 1.73479e+06 | 46733.6 | 1.25546 | 0.660124 | 1(Win) | true |
| Jsonifier | 2256.37 | 0.111294 | 8027.62ms | 183677 | 2560 | 1.91104e+07 | 77632.6 | 0.0293944 | 1.09686 | 2(Loss) | true |
| Glaze | 2235.11 | 0.205535 | 8237.7ms | 183677 | 160 | 4.15149e+06 | 78371.1 | 0.0331725 | 1.10733 | 3(Loss) | true |
| simdjson (ondemand) | 1138.9 | 0.155398 | 7960.7ms | 183677 | 1280 | 7.31214e+07 | 153805 | 0.322131 | 2.17345 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 23342 | 0.372194 | 879.289ms | 213963 | 640 | 677518 | 8741.81 | 0.258092 | 0.10574 | 1(Win) | true |
| Glaze | 3727.61 | 0.138995 | 5596.13ms | 213963 | 1280 | 7.41007e+06 | 54740.4 | 0.490163 | 0.663851 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 23950.7 | 0.163956 | 856.946ms | 213963 | 2560 | 499497 | 8519.62 | 0.337301 | 0.103044 | 1(Win) | true |
| Glaze | 3975.7 | 0.103215 | 5152.09ms | 213963 | 1280 | 3.59209e+06 | 51324.5 | 0.0587464 | 0.622405 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 780.592 | 0.105755 | 6947.78ms | 1834197 | 40 | 2.2465e+08 | 2.2409e+06 | 0.704008 | 3.17166 | 1(Win) | true |
| Jsonifier (two-stage) | 714.813 | 0.125553 | 7613.98ms | 1834197 | 40 | 3.77592e+08 | 2.44711e+06 | 0.951564 | 3.46354 | 2(Loss) | true |
| Glaze | 631.172 | 0.203523 | 8577.29ms | 1834197 | 30 | 9.54427e+08 | 2.77139e+06 | 0.141987 | 3.92245 | 3(Loss) | true |
| simdjson (ondemand) | 573.192 | 0.196562 | 9544.08ms | 1834197 | 40 | 1.4393e+09 | 3.05173e+06 | 0.313157 | 4.31923 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 868.304 | 0.154495 | 7133.75ms | 1834197 | 160 | 1.54987e+09 | 2.01453e+06 | 0.388034 | 2.85123 | 1(Win) | true |
| Jsonifier (two-stage) | 813.249 | 0.174645 | 7520.93ms | 1834197 | 80 | 1.12888e+09 | 2.15091e+06 | 0.763595 | 3.04428 | 2(Loss) | true |
| Glaze | 692.552 | 0.146886 | 8664.52ms | 1834197 | 160 | 2.20225e+09 | 2.52577e+06 | 0.253664 | 3.57476 | 3(Loss) | true |
| simdjson (ondemand) | 645.776 | 0.164457 | 9346.12ms | 1834197 | 30 | 5.95327e+08 | 2.70872e+06 | 0.0247928 | 3.83379 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1160.63 | 0.136828 | 9612.52ms | 1834197 | 80 | 3.40208e+08 | 1.50713e+06 | 1.47785 | 2.1331 | 1(Win) | true |
| Glaze | 615.715 | 0.0883456 | 8928.4ms | 1833577 | 30 | 1.88855e+08 | 2.84001e+06 | 0.0418416 | 4.02097 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1180.39 | 0.148608 | 9444.93ms | 1834197 | 160 | 7.75977e+08 | 1.48191e+06 | 0.227893 | 2.0974 | 1(Win) | true |
| Glaze | 623.379 | 0.0961157 | 8832.9ms | 1833577 | 40 | 2.90766e+08 | 2.80509e+06 | 0.0430151 | 3.97156 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2626.04 | 0.169453 | 8812.91ms | 7351818 | 30 | 6.14054e+08 | 2.66989e+06 | 1.18803 | 0.942732 | 1(Win) | true |
| Jsonifier | 2376.36 | 0.174889 | 9432.86ms | 7351818 | 160 | 4.26e+09 | 2.95041e+06 | 0.78584 | 1.0418 | 2(Loss) | true |
| simdjson (ondemand) | 2042.23 | 0.548259 | 5149.44ms | 7351818 | 40 | 1.41714e+10 | 3.43313e+06 | 0.0148759 | 1.21223 | 3(Loss) | true |
| Glaze | 1944.06 | 0.138808 | 5423.75ms | 7351818 | 80 | 2.00489e+09 | 3.6065e+06 | 0.955536 | 1.27344 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2740.68 | 0.336736 | 8776.27ms | 7351818 | 40 | 2.96834e+09 | 2.55822e+06 | 0.578813 | 0.90331 | 1(Win) | true |
| Jsonifier | 2602.88 | 0.489744 | 9276.03ms | 7351818 | 160 | 2.78445e+10 | 2.69365e+06 | 0.174992 | 0.951161 | 2(Loss) | true |
| simdjson (ondemand) | 2179.78 | 1.44608 | 5180.96ms | 7351818 | 80 | 1.73075e+11 | 3.21648e+06 | 2.02446 | 1.13573 | 3(Loss) | true |
| Glaze | 2037.72 | 0.193717 | 5651.06ms | 7351818 | 40 | 1.77705e+09 | 3.44074e+06 | 0.709996 | 1.21488 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5046.81 | 0.24372 | 5814.78ms | 9930848 | 160 | 3.34689e+09 | 1.87659e+06 | 1.87746 | 0.490553 | 1(Win) | true |
| Glaze | 3119.81 | 0.287641 | 9504.31ms | 9930228 | 80 | 6.09892e+09 | 3.03551e+06 | 0.792949 | 0.793539 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4972.88 | 0.248521 | 5989.71ms | 9930848 | 30 | 6.72053e+08 | 1.90449e+06 | 0.116659 | 0.497826 | 1(Win) | true |
| Glaze | 3559.24 | 0.232388 | 8038.2ms | 9930228 | 40 | 1.52929e+09 | 2.66074e+06 | 0.807309 | 0.695587 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 783.488 | 0.154332 | 6898.34ms | 1834197 | 80 | 9.49793e+08 | 2.23261e+06 | 0.771349 | 3.1599 | 1(Win) | true |
| Jsonifier (two-stage) | 743.692 | 0.0928288 | 7377.05ms | 1834197 | 80 | 3.81384e+08 | 2.35209e+06 | 0.0515154 | 3.329 | 2(Loss) | true |
| Glaze | 652.275 | 0.35132 | 8431.27ms | 1834197 | 30 | 2.66291e+09 | 2.68173e+06 | 1.66563 | 3.79562 | 3(Loss) | true |
| simdjson (ondemand) | 577.128 | 0.175766 | 9866.01ms | 1834197 | 40 | 1.13521e+09 | 3.03092e+06 | 0.172631 | 4.28967 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 873.378 | 0.204696 | 6966.47ms | 1834197 | 30 | 5.04229e+08 | 2.00283e+06 | 0.143044 | 2.83469 | 1(Win) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 814.158 | 0.27714 | 7589.26ms | 1834197 | 160 | 5.67274e+09 | 2.14851e+06 | 14.3025 | 3.04088 | -(Loss) | false |
| Glaze | 688.761 | 0.238906 | 8603.59ms | 1834197 | 80 | 2.94511e+09 | 2.53967e+06 | 0.750018 | 3.59453 | 3(Loss) | true |
| simdjson (ondemand) | 627.838 | 0.0842963 | 9509.85ms | 1834197 | 40 | 2.20635e+08 | 2.78611e+06 | 0.441571 | 3.9433 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1149.61 | 0.0685925 | 9711.77ms | 1834197 | 80 | 8.71431e+07 | 1.52158e+06 | 0.152249 | 2.15356 | 1(Win) | true |
| Glaze | 593.475 | 0.0840723 | 9159.66ms | 1833577 | 30 | 1.84086e+08 | 2.94643e+06 | 0.593722 | 4.17166 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1138.99 | 0.0770326 | 9756.37ms | 1834197 | 40 | 5.59838e+07 | 1.53577e+06 | 0.110801 | 2.17363 | 1(Win) | true |
| Glaze | 619.371 | 0.0725257 | 8835.38ms | 1833577 | 160 | 6.70811e+08 | 2.82324e+06 | 0.290712 | 3.99727 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2445.2 | 0.231878 | 8737.16ms | 7351818 | 80 | 3.53646e+09 | 2.86734e+06 | 0.360433 | 1.01237 | 1(Win) | true |
| Jsonifier | 2405.87 | 0.228012 | 8995.56ms | 7351818 | 30 | 1.32458e+09 | 2.91422e+06 | 0.876866 | 1.02903 | 2(Loss) | true |
| simdjson (ondemand) | 2082.36 | 0.134474 | 5196.62ms | 7351818 | 80 | 1.64001e+09 | 3.36697e+06 | 2.43338 | 1.18889 | 3(Loss) | true |
| Glaze | 1961.01 | 0.356819 | 5343.76ms | 7351818 | 40 | 6.51011e+09 | 3.57533e+06 | 0.225263 | 1.26247 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2928.23 | 0.115949 | 8618.32ms | 7351818 | 30 | 2.31224e+08 | 2.39436e+06 | 1.66149 | 0.845442 | 1(Win) | true |
| Jsonifier | 2618.96 | 0.142555 | 9266.92ms | 7351818 | 30 | 4.36938e+08 | 2.67711e+06 | 1.03693 | 0.945325 | 2(Loss) | true |
| simdjson (ondemand) | 2351.06 | 0.220462 | 10283.1ms | 7351818 | 30 | 1.29673e+09 | 2.98216e+06 | 1.76078 | 1.053 | 3(Loss) | true |
| Glaze | 2161.32 | 0.288711 | 5394.28ms | 7351818 | 30 | 2.63147e+09 | 3.24396e+06 | 1.33912 | 1.14548 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4852.59 | 0.11372 | 6110.1ms | 9930848 | 40 | 1.97041e+08 | 1.9517e+06 | 0.421159 | 0.510172 | 1(Win) | true |
| Glaze | 2815.24 | 0.488164 | 5022.82ms | 9930228 | 80 | 2.1573e+10 | 3.36391e+06 | 1.45827 | 0.879322 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4869.18 | 0.0781428 | 6089.64ms | 9930848 | 80 | 1.84811e+08 | 1.94505e+06 | 1.79245 | 0.508427 | 1(Win) | true |
| Glaze | 3580.93 | 0.0807091 | 8351.5ms | 9930228 | 160 | 7.28941e+08 | 2.64462e+06 | 0.263945 | 0.691377 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1160.76 | 0.292351 | 9684.83ms | 461466 | 640 | 7.86295e+08 | 379138 | 1.55011 | 2.13267 | 1(Win) | true |
| Jsonifier (two-stage) | 1116.41 | 0.311589 | 5142.06ms | 461466 | 320 | 4.8278e+08 | 394201 | 1.45771 | 2.21741 | 2(Loss) | true |
| Glaze | 1022.09 | 0.120276 | 5449.68ms | 461466 | 320 | 8.58229e+07 | 430575 | 0.0289246 | 2.42204 | 3(Loss) | true |
| simdjson (ondemand) | 796.316 | 0.258499 | 7295.39ms | 461466 | 160 | 3.26547e+08 | 552655 | 1.10902 | 3.10884 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1613.64 | 0.162121 | 8765.02ms | 461466 | 160 | 3.12798e+07 | 272730 | 0.052371 | 1.53411 | 1(Win) | true |
| Jsonifier (two-stage) | 1477.77 | 0.600576 | 9635.73ms | 461466 | 40 | 1.27956e+08 | 297806 | 0.4798 | 1.67518 | 2(Loss) | true |
| Glaze | 1310.86 | 0.094573 | 5265.23ms | 461466 | 320 | 3.22591e+07 | 335725 | 0.16526 | 1.88853 | 3(Loss) | true |
| simdjson (ondemand) | 939.163 | 0.148275 | 6724.84ms | 461466 | 160 | 7.72416e+07 | 468596 | 0.0617208 | 2.63599 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12948.7 | 0.298412 | 3386.92ms | 461466 | 640 | 6.58322e+06 | 33987 | 0.18671 | 0.190974 | 1(Win) | true |
| Glaze | 2898.02 | 0.287468 | 7862.43ms | 461466 | 80 | 1.52456e+07 | 151858 | 0.724867 | 0.854061 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12986.1 | 0.18779 | 3407.35ms | 461466 | 1280 | 5.18414e+06 | 33889.1 | 0.235125 | 0.190404 | 1(Win) | true |
| Glaze | 3107.28 | 0.267649 | 7146.19ms | 461466 | 320 | 4.59834e+07 | 141631 | 0.565099 | 0.79661 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1698.91 | 0.169454 | 5295.29ms | 728486 | 30 | 1.44055e+07 | 408932 | 0.122747 | 1.45714 | 1(Win) | true |
| Jsonifier | 1410.47 | 0.125597 | 6326.64ms | 728486 | 640 | 2.44934e+08 | 492557 | 0.915149 | 1.75514 | 2(Loss) | true |
| Glaze | 1344.05 | 0.118078 | 6570.12ms | 728486 | 320 | 1.19207e+08 | 516900 | 1.46212 | 1.84191 | 3(Loss) | true |
| simdjson (ondemand) | 1179.88 | 0.136208 | 7470.42ms | 728486 | 80 | 5.14592e+07 | 588821 | 0.800713 | 2.09818 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2198.2 | 0.0843115 | 9924.05ms | 728486 | 1280 | 9.08851e+07 | 316049 | 0.696086 | 1.12617 | 1(Win) | true |
| Jsonifier | 1802.42 | 0.307872 | 5843.25ms | 728486 | 30 | 4.22467e+07 | 385449 | 0.267007 | 1.37347 | 2(Loss) | true |
| Glaze | 1619.27 | 0.115667 | 6398.42ms | 728486 | 160 | 3.94042e+07 | 429044 | 0.0516711 | 1.52885 | 3(Loss) | true |
| simdjson (ondemand) | 1535.88 | 0.14876 | 6767.03ms | 728486 | 30 | 1.35837e+07 | 452339 | 0.265473 | 1.61185 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17130.2 | 0.133218 | 4653.01ms | 837491 | 2560 | 9.87655e+06 | 46624.9 | 0.200552 | 0.14441 | 1(Win) | true |
| Glaze | 3643.47 | 0.173549 | 5859.93ms | 837491 | 320 | 4.63154e+07 | 219212 | 0.0314677 | 0.679387 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17693.6 | 0.574866 | 4675.01ms | 837491 | 80 | 5.38708e+06 | 45140.3 | 0.254472 | 0.139809 | 1(Win) | true |
| Glaze | 3929.04 | 0.406764 | 5234.15ms | 837491 | 40 | 2.73484e+07 | 203279 | 0.113716 | 0.630047 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10032.5 | 0.30737 | 4557.8ms | 466906 | 80 | 1.48887e+06 | 44383.5 | 0.187837 | 0.246628 | 1(Win) | true |
| Jsonifier (two-stage) | 9695.3 | 0.233546 | 4510.27ms | 466906 | 4890 | 5.62591e+07 | 45927 | 0.0268481 | 0.255158 | 2(Loss) | true |
| simdjson (ondemand) | 7646.61 | 0.259298 | 6074.25ms | 466906 | 80 | 1.82394e+06 | 58231.9 | 0.0993313 | 0.323565 | 3(Loss) | true |
| Glaze | 3281.16 | 0.152601 | 6956.17ms | 466906 | 160 | 6.8618e+06 | 135707 | 0.026756 | 0.754385 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 10499.5 | 0.437565 | 4481.06ms | 466906 | 80 | 2.75486e+06 | 42409.4 | 0.495243 | 0.235641 | 1(Win) | true |
| Jsonifier | 10355.7 | 0.0996641 | 4440.3ms | 466906 | 1280 | 2.35066e+06 | 42998.3 | 0.0600293 | 0.238919 | 2(Loss) | true |
| simdjson (ondemand) | 7445 | 0.0631005 | 6042.75ms | 466906 | 4890 | 6.96473e+06 | 59808.8 | 0.428305 | 0.332335 | 3(Loss) | true |
| Glaze | 3367.78 | 0.484402 | 6977.91ms | 466906 | 40 | 1.64075e+07 | 132216 | 0.817838 | 0.734999 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 11331.8 | 0.168294 | 5487.71ms | 631514 | 640 | 5.12018e+06 | 53147.5 | 0.113139 | 0.218319 | 1(Win) | true |
| Jsonifier | 10879 | 0.352523 | 5543.91ms | 631514 | 80 | 3.04688e+06 | 55359.8 | 0.134212 | 0.227412 | 2(Loss) | true |
| simdjson (ondemand) | 8528.75 | 0.0838037 | 7119.4ms | 631514 | 4890 | 1.7125e+07 | 70615.1 | 0.940165 | 0.290087 | 3(Loss) | true |
| Glaze | 3939.63 | 0.147551 | 7950.81ms | 631514 | 160 | 8.14063e+06 | 152872 | 0.0139106 | 0.628303 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 11077.5 | 0.083321 | 5551.8ms | 631514 | 2560 | 5.25329e+06 | 54367.7 | 0.300217 | 0.223359 | 1(Win) | true |
| Jsonifier | 10960 | 0.173742 | 5603.94ms | 631514 | 640 | 5.83361e+06 | 54950.8 | 0.0650472 | 0.225756 | 2(Loss) | true |
| simdjson (ondemand) | 8755.26 | 0.147378 | 7079.04ms | 631514 | 1280 | 1.31554e+07 | 68788.2 | 0.539366 | 0.282605 | 3(Loss) | true |
| Glaze | 3970.37 | 0.111956 | 7794.71ms | 631514 | 640 | 1.84578e+07 | 151688 | 0.585316 | 0.623459 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1725.83 | 0.158703 | 6857.08ms | 466906 | 640 | 1.07304e+08 | 258007 | 1.57166 | 1.4343 | 1(Win) | true |
| Jsonifier (two-stage) | 1686.4 | 0.152755 | 6838.09ms | 466906 | 160 | 2.60283e+07 | 264039 | 0.278812 | 1.46784 | 2(Loss) | true |
| Glaze | 1641.41 | 0.113046 | 6993.45ms | 466906 | 320 | 3.00945e+07 | 271276 | 0.124217 | 1.50808 | 3(Loss) | true |
| simdjson (ondemand) | 871.571 | 0.0676561 | 6498.62ms | 466906 | 320 | 3.82311e+07 | 510889 | 0.317055 | 2.84037 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 2099.6 | 0.491494 | 6383.98ms | 466906 | 40 | 4.34594e+07 | 212077 | 0.476724 | 1.17897 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2073.51 | 0.400114 | 5846.06ms | 466906 | 40 | 2.95308e+07 | 214746 | 0.429741 | 1.19383 | 1(Tie) | true |
| Glaze | 2003.19 | 0.309834 | 6422.61ms | 466906 | 80 | 3.79456e+07 | 222283 | 0.405348 | 1.23576 | 3(Loss) | true |
| simdjson (ondemand) | 957.568 | 0.133488 | 6261ms | 466906 | 320 | 1.23297e+08 | 465007 | 0.672252 | 2.5853 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17510 | 0.460083 | 2653.24ms | 475954 | 320 | 4.55176e+06 | 25922.6 | 0.202573 | 0.141209 | 1(Win) | true |
| Glaze | 5467.08 | 0.165909 | 8425.87ms | 475954 | 640 | 1.21434e+07 | 83025.2 | 0.645716 | 0.452667 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17383.1 | 0.275861 | 2653.19ms | 475954 | 640 | 3.32076e+06 | 26111.9 | 0.175832 | 0.142228 | 1(Win) | true |
| Glaze | 6025.31 | 0.0593144 | 7502.85ms | 475954 | 4890 | 9.76341e+06 | 75333.1 | 0.105369 | 0.410742 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2117.62 | 0.133151 | 7226.67ms | 631514 | 320 | 4.58893e+07 | 284404 | 0.00574591 | 1.16895 | 1(Win) | true |
| Glaze | 1808.15 | 0.202336 | 8556.71ms | 631514 | 160 | 7.26719e+07 | 333081 | 0.323822 | 1.36907 | 2(Loss) | true |
| Jsonifier | 1648.19 | 0.0979612 | 9600.06ms | 631514 | 320 | 4.10023e+07 | 365406 | 0.473401 | 1.50195 | 3(Loss) | true |
| simdjson (ondemand) | 1128.85 | 0.169331 | 6586.52ms | 631514 | 80 | 6.52908e+07 | 533513 | 0.357471 | 2.19301 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2785.39 | 0.166741 | 6164.38ms | 631514 | 160 | 2.07968e+07 | 216220 | 1.40991 | 0.888725 | 1(Win) | true |
| Glaze | 2212.95 | 0.193056 | 7994.31ms | 631514 | 80 | 2.20841e+07 | 272152 | 0.0926289 | 1.11867 | 2(Loss) | true |
| Jsonifier | 1873.05 | 0.236387 | 9283.75ms | 631514 | 80 | 4.62173e+07 | 321538 | 2.11033 | 1.32165 | 3(Loss) | true |
| simdjson (ondemand) | 1284.32 | 0.144426 | 6263.45ms | 631514 | 160 | 7.33893e+07 | 468932 | 0.691093 | 1.92756 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15684.9 | 0.544684 | 4240.35ms | 716365 | 80 | 4.50284e+06 | 43556.6 | 0.206825 | 0.157734 | 1(Win) | true |
| Glaze | 4623.35 | 0.271617 | 7744.1ms | 716365 | 160 | 2.57744e+07 | 147767 | 0.312643 | 0.535354 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15829.7 | 0.0672563 | 4303.31ms | 716365 | 4890 | 4.12002e+06 | 43158.1 | 0.163108 | 0.156292 | 1(Win) | true |
| Glaze | 5294.96 | 0.151711 | 6677.73ms | 716365 | 2560 | 9.80888e+07 | 129024 | 0.398687 | 0.467472 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2403.57 | 0.0508818 | 108.971ms | 2632 | 640 | 180.702 | 1044.31 | 0.00628366 | 1.00187 | 1(Win) | true |
| Jsonifier (two-stage) | 2342.29 | 0.0920719 | 109.418ms | 2632 | 30 | 29.2057 | 1071.63 | 0.0934027 | 1.02966 | 2(Loss) | true |
| Glaze | 1989.65 | 0.128809 | 128.71ms | 2632 | 30 | 79.2195 | 1261.57 | 0.238366 | 1.21668 | 3(Loss) | true |
| simdjson (ondemand) | 1452.98 | 0.0721296 | 175.825ms | 2632 | 160 | 248.427 | 1727.53 | 0.149196 | 1.67605 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2739.77 | 0.168215 | 101.148ms | 2632 | 160 | 380.011 | 916.163 | 0.466053 | 0.876919 | 1(Win) | true |
| Jsonifier (two-stage) | 2708.17 | 0.110121 | 101.471ms | 2632 | 40 | 41.6692 | 926.85 | 0.0917927 | 0.887547 | 2(Loss) | true |
| Glaze | 2451.91 | 0.0519032 | 112.637ms | 2632 | 160 | 45.172 | 1023.72 | 0.080042 | 0.984152 | 3(Loss) | true |
| simdjson (ondemand) | 1685.61 | 0.0950918 | 162.367ms | 2632 | 160 | 320.822 | 1489.12 | 0.0508109 | 1.4407 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12515.9 | 0.171788 | 22.7243ms | 2632 | 160 | 18.9912 | 200.55 | 0.0186951 | 0.172447 | 1(Win) | true |
| Glaze | 3842.5 | 0.0463572 | 79.9183ms | 2632 | 640 | 58.6892 | 653.239 | 0.0184144 | 0.617932 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14016.6 | 0.144052 | 20.5319ms | 2632 | 320 | 21.2948 | 179.078 | 0.210706 | 0.150962 | 1(Win) | true |
| Glaze | 4358.71 | 0.0921073 | 60.4088ms | 2632 | 160 | 45.0157 | 575.875 | 0.00434103 | 0.542539 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2834.94 | 0.129898 | 117.012ms | 3370 | 30 | 65.0575 | 1133.67 | 0.0352713 | 0.851236 | 1(Win) | true |
| Jsonifier | 2276 | 0.034124 | 147.066ms | 3370 | 320 | 74.2989 | 1412.07 | 0.223682 | 1.06756 | 2(Loss) | true |
| Glaze | 2216.93 | 0.0588742 | 149.865ms | 3370 | 40 | 29.1385 | 1449.7 | 0.352847 | 1.09631 | 3(Loss) | true |
| simdjson (ondemand) | 1877.88 | 0.0965599 | 173.699ms | 3370 | 80 | 218.477 | 1711.44 | 0.284765 | 1.29794 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3390.33 | 0.0409353 | 108.466ms | 3370 | 320 | 48.1862 | 947.956 | 0.167843 | 0.710333 | 1(Win) | true |
| Glaze | 2539.16 | 0.112196 | 136.237ms | 3370 | 40 | 80.666 | 1265.72 | 0.00855826 | 0.954933 | 2(Loss) | true |
| Jsonifier | 2399.76 | 0.0844927 | 145.622ms | 3370 | 40 | 51.2179 | 1339.25 | 0.0311023 | 1.01009 | 3(Loss) | true |
| simdjson (ondemand) | 2095.05 | 0.2274 | 200.719ms | 3370 | 30 | 365.068 | 1534.03 | 0.0434773 | 1.16113 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13285.6 | 0.0710138 | 28.6081ms | 3643 | 1280 | 44.1423 | 261.505 | 0.0447927 | 0.167672 | 1(Win) | true |
| Glaze | 4243.67 | 0.219453 | 86.7758ms | 3682 | 40 | 131.895 | 827.45 | 0.0583783 | 0.565379 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14293 | 0.0854588 | 26.944ms | 3643 | 640 | 27.6161 | 243.072 | 0.17454 | 0.154238 | 1(Win) | true |
| Glaze | 4758.03 | 0.102016 | 81.0667ms | 3682 | 160 | 90.6918 | 738 | 0.371245 | 0.502034 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 905.09 | 0.219462 | 492.564ms | 4630 | 2560 | 293452 | 4878.54 | 0.081429 | 2.72088 | 1(Win) | true |
| Jsonifier (two-stage) | 841.873 | 0.0478056 | 546.824ms | 4630 | 30 | 188.602 | 5244.87 | 0.456765 | 2.92662 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 696.324 | 0.0907922 | 643.348ms | 4630 | 80 | 2651.72 | 6341.18 | 0.0532519 | 3.53983 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 693.119 | 0.217176 | 672.275ms | 4630 | 2560 | 490014 | 6370.5 | 0.684725 | 3.5571 | 3(Tie) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1060.85 | 0.0448136 | 491.7ms | 4630 | 40 | 139.167 | 4162.25 | 0.0188164 | 2.31908 | 1(Win) | true |
| Jsonifier (two-stage) | 967.264 | 0.0344142 | 549.212ms | 4630 | 80 | 197.441 | 4564.95 | 0.162368 | 2.54342 | 2(Loss) | true |
| Glaze | 825.901 | 0.105667 | 636.496ms | 4630 | 40 | 1276.57 | 5346.3 | 0.144233 | 2.98322 | 3(Loss) | true |
| simdjson (ondemand) | 782.619 | 0.358998 | 645.188ms | 4630 | 1280 | 525114 | 5641.97 | 0.300009 | 3.14749 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1989.35 | 0.0530608 | 230.686ms | 4630 | 40 | 55.4814 | 2219.57 | 0.0259126 | 1.22937 | 1(Win) | true |
| Glaze | 1003.45 | 0.184769 | 446.416ms | 4630 | 2560 | 169226 | 4400.31 | 0.0925329 | 2.45182 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1933.49 | 0.0321024 | 226.638ms | 4630 | 80 | 42.9975 | 2283.7 | 0.0984273 | 1.2651 | 1(Win) | true |
| Glaze | 1035.84 | 0.0487165 | 432.238ms | 4630 | 30 | 129.375 | 4262.73 | 0.0618139 | 2.37592 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1848.46 | 0.0549358 | 585.28ms | 11579 | 40 | 430.818 | 5973.95 | 0.363163 | 1.33311 | 1(Win) | true |
| Jsonifier | 1788.41 | 0.0345906 | 648.103ms | 11579 | 80 | 364.935 | 6174.54 | 0.327491 | 1.37861 | 2(Loss) | true |
| simdjson (ondemand) | 1673.86 | 0.119646 | 652.908ms | 11579 | 4890 | 304655 | 6597.1 | 0.0720784 | 1.47276 | 3(Loss) | true |
| Glaze | 1626.34 | 0.0687257 | 699.363ms | 11579 | 30 | 653.247 | 6789.83 | 0.0732021 | 1.51679 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2246.78 | 0.19527 | 616.642ms | 11579 | 2560 | 235793 | 4914.85 | 0.586367 | 1.09589 | 1(Win) | true |
| Jsonifier | 2005.98 | 0.0377307 | 688.25ms | 11579 | 40 | 172.558 | 5504.82 | 0.0410415 | 1.22819 | 2(Loss) | true |
| simdjson (ondemand) | 1928.34 | 0.12544 | 685.286ms | 11579 | 40 | 2064 | 5726.48 | 0.252829 | 1.27787 | 3(Loss) | true |
| Glaze | 1821.28 | 0.0617087 | 713.731ms | 11579 | 30 | 419.955 | 6063.1 | 0.082947 | 1.35354 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5463.23 | 0.058747 | 266.45ms | 14795 | 40 | 92.0795 | 2582.65 | 0.267097 | 0.448427 | 1(Win) | true |
| Glaze | 3114.34 | 0.238255 | 451.353ms | 14795 | 2560 | 298279 | 4530.53 | 0.156424 | 0.790133 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5617.26 | 0.135943 | 259.818ms | 14795 | 30 | 349.799 | 2511.83 | 0.341211 | 0.435987 | 1(Win) | true |
| Glaze | 3453.91 | 0.305429 | 411.316ms | 14795 | 640 | 99634.3 | 4085.12 | 0.457985 | 0.711977 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1722.28 | 0.150144 | 180.069ms | 3223 | 30 | 215.402 | 1784.67 | 0.169678 | 1.41388 | 1(Win) | true |
| Jsonifier (two-stage) | 1555.64 | 0.127302 | 207.013ms | 3223 | 30 | 189.799 | 1975.83 | 0.0253122 | 1.56956 | 2(Loss) | true |
| Glaze | 1348.27 | 0.120692 | 237.398ms | 3223 | 40 | 302.82 | 2279.72 | 0.617534 | 1.81506 | 3(Loss) | true |
| simdjson (ondemand) | 1015.31 | 0.216713 | 308.072ms | 3223 | 2560 | 110188 | 3027.35 | 0.152438 | 2.41563 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2171.68 | 0.204627 | 162.939ms | 3223 | 4890 | 41017.2 | 1415.35 | 0.566043 | 1.11783 | 1(Win) | true |
| Jsonifier (two-stage) | 1798.4 | 0.227447 | 189.82ms | 3223 | 4890 | 73895.4 | 1709.13 | 0.106436 | 1.35324 | 2(Loss) | true |
| Glaze | 1513.61 | 0.13668 | 228.481ms | 3223 | 30 | 231.114 | 2030.7 | 0.292962 | 1.61577 | 3(Loss) | true |
| simdjson (ondemand) | 1161.1 | 0.14393 | 296.102ms | 3223 | 40 | 580.692 | 2647.22 | 0.0795798 | 2.10791 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11039.1 | 0.231227 | 31.1187ms | 3223 | 80 | 33.1606 | 278.438 | 0.00448954 | 0.203238 | 1(Win) | true |
| Glaze | 2655.19 | 0.0911814 | 119.483ms | 3223 | 320 | 356.526 | 1157.62 | 0.379992 | 0.91014 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11582.9 | 0.0755289 | 29.2167ms | 3223 | 640 | 25.7096 | 265.366 | 0.41506 | 0.191746 | 1(Win) | true |
| Glaze | 2863.25 | 0.255682 | 110.162ms | 3223 | 4890 | 36839.2 | 1073.5 | 0.236932 | 0.842592 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2556.87 | 0.242979 | 221.374ms | 5839 | 4890 | 136932 | 2177.86 | 0.030331 | 0.955504 | 1(Win) | true |
| Jsonifier | 1886.78 | 0.210672 | 300.522ms | 5839 | 2560 | 98967 | 2951.33 | 0.386816 | 1.29936 | 2(Loss) | true |
| simdjson (ondemand) | 1771.06 | 0.271395 | 323.78ms | 5839 | 1280 | 93201.4 | 3144.16 | 0.00777671 | 1.3854 | 3(Loss) | true |
| Glaze | 1745.72 | 0.0972667 | 331.44ms | 5839 | 30 | 288.786 | 3189.8 | 0.314596 | 1.40634 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2928.35 | 0.32414 | 210.527ms | 5839 | 2560 | 97260.8 | 1901.59 | 0.523106 | 0.832901 | 1(Win) | true |
| Jsonifier | 2102.7 | 0.137619 | 287.204ms | 5839 | 30 | 398.478 | 2648.27 | 0.377769 | 1.16529 | 2(Loss) | true |
| simdjson (ondemand) | 1983.68 | 0.0933218 | 315.351ms | 5839 | 80 | 549.024 | 2807.16 | 0.202124 | 1.23477 | 3(Loss) | true |
| Glaze | 1928.61 | 0.175746 | 312.16ms | 5839 | 2560 | 65917.5 | 2887.32 | 0.146197 | 1.27129 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11847.8 | 0.478531 | 59.9732ms | 6938 | 30 | 214.257 | 558.467 | 0.362771 | 0.198967 | 1(Win) | true |
| Glaze | 4092.07 | 0.350865 | 165.104ms | 6960 | 2560 | 82918.7 | 1622.06 | 0.0893279 | 0.594829 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13706 | 0.156667 | 54.3059ms | 6938 | 320 | 183.041 | 482.75 | 0.164153 | 0.170682 | 1(Win) | true |
| Glaze | 4595.07 | 0.320761 | 153.279ms | 6960 | 30 | 644.052 | 1444.5 | 0.0877659 | 0.528951 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1807.71 | 0.20584 | 264.197ms | 4857 | 40 | 1112.75 | 2562.35 | 0.294214 | 1.35473 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1559.73 | 0.261888 | 301.338ms | 4857 | 2560 | 154849 | 2969.74 | 0.145227 | 1.572 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1554.32 | 0.609241 | 302.569ms | 4857 | 320 | 105483 | 2980.08 | 0.176376 | 1.57792 | 2(Tie) | true |
| simdjson (ondemand) | 771.277 | 0.130797 | 600.209ms | 4857 | 4890 | 301732 | 6005.62 | 0.337752 | 3.19491 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2422.85 | 0.0885518 | 217.897ms | 4857 | 160 | 458.564 | 1911.8 | 0.556881 | 1.0069 | 1(Win) | true |
| Jsonifier (two-stage) | 2064.62 | 0.106838 | 255.358ms | 4857 | 80 | 459.62 | 2243.51 | 0.116583 | 1.18416 | 2(Loss) | true |
| Glaze | 1942.69 | 0.244694 | 260.658ms | 4857 | 4890 | 166450 | 2384.32 | 0.355302 | 1.2585 | 3(Loss) | true |
| simdjson (ondemand) | 853.964 | 0.637307 | 584.813ms | 4857 | 320 | 382389 | 5424.11 | 0.184009 | 2.8836 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12147.6 | 0.101432 | 41.1303ms | 4857 | 320 | 47.8695 | 381.309 | 0.523133 | 0.189065 | 1(Win) | true |
| Glaze | 3490.58 | 0.193733 | 139.228ms | 4857 | 30 | 198.276 | 1327 | 0.00251199 | 0.693762 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14269.3 | 0.190508 | 36.022ms | 4857 | 80 | 30.5948 | 324.613 | 0.0423761 | 0.159494 | 1(Win) | true |
| Glaze | 3957.2 | 0.217185 | 123.772ms | 4857 | 40 | 258.512 | 1170.53 | 0.121889 | 0.611293 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2118.84 | 0.194229 | 301.885ms | 6701 | 4890 | 167811 | 3016.07 | 0.66657 | 1.15757 | 1(Win) | true |
| Glaze | 1662.8 | 0.182827 | 386.07ms | 6701 | 4890 | 241427 | 3843.25 | 0.490569 | 1.47735 | 2(Loss) | true |
| Jsonifier | 1636.85 | 0.14408 | 397.029ms | 6701 | 4890 | 154731 | 3904.18 | 0.0500827 | 1.50118 | 3(Loss) | true |
| simdjson (ondemand) | 1092.94 | 0.262426 | 623.502ms | 6701 | 30 | 7063.5 | 5847.13 | 0.022798 | 2.25429 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2860.16 | 0.057589 | 256.554ms | 6701 | 80 | 132.454 | 2234.34 | 0.490458 | 0.855048 | 1(Win) | true |
| Glaze | 2243.96 | 0.429311 | 318.605ms | 6701 | 30 | 4484.51 | 2847.9 | 0.714684 | 1.0931 | 2(Loss) | true |
| Jsonifier | 2052.43 | 0.0751819 | 348.391ms | 6701 | 160 | 876.778 | 3113.66 | 0.0100354 | 1.19599 | 3(Loss) | true |
| simdjson (ondemand) | 1136.81 | 0.142347 | 586.975ms | 6701 | 4890 | 313117 | 5621.49 | 0.22404 | 2.16624 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12950 | 0.485553 | 56.8025ms | 7376 | 4890 | 34015.8 | 543.187 | 0.652206 | 0.180993 | 1(Win) | true |
| Glaze | 3153.35 | 0.186134 | 225.735ms | 7376 | 80 | 1379.23 | 2230.74 | 0.173967 | 0.775341 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14980 | 0.10631 | 50.3165ms | 7376 | 640 | 159.493 | 469.578 | 0.00532364 | 0.155717 | 1(Win) | true |
| Glaze | 3566.49 | 0.178527 | 204.562ms | 7376 | 30 | 371.954 | 1972.33 | 0.101506 | 0.685001 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2248.32 | 0.057407 | 75.2922ms | 1691 | 320 | 54.2564 | 717.275 | 0.369946 | 1.05986 | 1(Win) | true |
| Jsonifier (two-stage) | 1966.1 | 0.205398 | 84.4651ms | 1691 | 30 | 85.1506 | 820.233 | 0.162292 | 1.21666 | 2(Loss) | true |
| Glaze | 1892.75 | 0.107974 | 90.2616ms | 1691 | 320 | 270.824 | 852.022 | 0.0583512 | 1.26683 | 3(Loss) | true |
| simdjson (ondemand) | 1361.24 | 0.085582 | 124.904ms | 1691 | 160 | 164.475 | 1184.7 | 0.194817 | 1.7747 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2998.39 | 0.0594376 | 67.0797ms | 1691 | 320 | 32.7028 | 537.844 | 0.453457 | 0.784946 | 1(Win) | true |
| Jsonifier (two-stage) | 2524.84 | 0.144712 | 71.7109ms | 1691 | 160 | 136.694 | 638.719 | 0.833744 | 0.938054 | 2(Loss) | true |
| Glaze | 2259.34 | 0.072496 | 80.9801ms | 1691 | 160 | 42.8421 | 713.775 | 0.104965 | 1.05461 | 3(Loss) | true |
| simdjson (ondemand) | 1601.08 | 0.273688 | 110.991ms | 1691 | 30 | 227.978 | 1007.23 | 0.405383 | 1.50164 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12954.5 | 1.56076 | 17.2068ms | 1996 | 4890 | 25719.7 | 146.94 | 0.481588 | 0.154338 | 1(Win) | true |
| Glaze | 4395.68 | 0.518292 | 45.962ms | 1996 | 2560 | 12896.1 | 433.047 | 0.138926 | 0.52756 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15301.7 | 0.657646 | 15.3418ms | 1996 | 320 | 214.178 | 124.4 | 1.71709 | 0.125667 | 1(Win) | true |
| Glaze | 5171.24 | 0.128235 | 40.5075ms | 1996 | 160 | 35.6503 | 368.1 | 0.0509113 | 0.445024 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2401.92 | 0.12922 | 90.2888ms | 2158 | 320 | 392.276 | 856.825 | 0.00948178 | 0.997873 | 1(Win) | true |
| Glaze | 1923.45 | 0.209392 | 111.051ms | 2158 | 30 | 150.585 | 1069.97 | 0.211397 | 1.25419 | 2(Loss) | true |
| simdjson (ondemand) | 1726.46 | 0.516688 | 124.401ms | 2158 | 1280 | 48557.3 | 1192.05 | 0.0220913 | 1.40031 | 3(Loss) | true |
| Jsonifier | 1511.28 | 0.11395 | 137.223ms | 2158 | 80 | 192.632 | 1361.78 | 0.150313 | 1.60509 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3094.51 | 0.301646 | 75.5489ms | 2158 | 4890 | 19679.8 | 665.057 | 0.618246 | 0.766251 | 1(Win) | true |
| Glaze | 2312.18 | 0.15547 | 97.9863ms | 2158 | 320 | 612.777 | 890.081 | 0.0778816 | 1.03763 | 2(Loss) | true |
| simdjson (ondemand) | 2004.78 | 0.590163 | 112.081ms | 2158 | 1280 | 46980.9 | 1026.56 | 0.438061 | 1.19955 | 3(Loss) | true |
| Jsonifier | 1968.84 | 0.159978 | 122.283ms | 2158 | 40 | 111.856 | 1045.3 | 0.117849 | 1.22556 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14902.1 | 0.431109 | 20.9753ms | 2866 | 80 | 50.0176 | 183.412 | 0.0750239 | 0.1417 | 1(Win) | true |
| Glaze | 4234.28 | 0.153193 | 69.5201ms | 2866 | 80 | 78.2278 | 645.5 | 0.194024 | 0.560263 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17810.1 | 0.142729 | 18.0414ms | 2866 | 640 | 30.7062 | 153.466 | 0.615223 | 0.114581 | 1(Win) | true |
| Glaze | 4853.36 | 0.136421 | 59.4724ms | 2866 | 160 | 94.4388 | 563.163 | 0.0999822 | 0.485219 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2296.94 | 0.103334 | 193.313ms | 4390 | 30 | 106.424 | 1822.7 | 0.386206 | 1.06172 | 1(Win) | true |
| Jsonifier (two-stage) | 1805.51 | 0.266653 | 240.498ms | 4390 | 1280 | 48936.4 | 2318.81 | 0.265493 | 1.35454 | 2(Loss) | true |
| Glaze | 1604.3 | 0.0988465 | 268.679ms | 4390 | 30 | 199.62 | 2609.63 | 0.242103 | 1.52623 | 3(Loss) | true |
| simdjson (ondemand) | 936.592 | 0.565148 | 477.885ms | 4390 | 30 | 19145.8 | 4470.07 | 1.62707 | 2.62604 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2515.76 | 0.45759 | 181.141ms | 4390 | 80 | 4639.1 | 1664.16 | 0.355518 | 0.96707 | 1(Win) | true |
| Jsonifier (two-stage) | 1945.87 | 0.821482 | 233.255ms | 4390 | 320 | 99965.3 | 2151.55 | 0.168476 | 1.2555 | 2(Loss) | true |
| Glaze | 1738.76 | 0.321482 | 259.087ms | 4390 | 2560 | 153391 | 2407.82 | 0.361636 | 1.40744 | 3(Loss) | true |
| simdjson (ondemand) | 996.569 | 0.215853 | 440.711ms | 4390 | 2560 | 210509 | 4201.04 | 0.144462 | 2.46676 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11304.1 | 0.272367 | 40.5038ms | 4390 | 160 | 162.811 | 370.363 | 0.32296 | 0.202931 | 1(Win) | true |
| Glaze | 2642.26 | 0.171914 | 163.401ms | 4390 | 80 | 593.595 | 1584.49 | 0.0118321 | 0.920558 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11946.3 | 0.0393837 | 38.202ms | 4390 | 1280 | 24.3843 | 350.455 | 0.0198442 | 0.191396 | 1(Win) | true |
| Glaze | 2831.48 | 0.0666035 | 150.471ms | 4390 | 320 | 310.347 | 1478.6 | 0.0141583 | 0.858339 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3401.28 | 0.163852 | 269.258ms | 9378 | 30 | 556.878 | 2629.47 | 0.608364 | 0.720278 | 1(Win) | true |
| Jsonifier | 2897.47 | 0.293054 | 311.267ms | 9378 | 2560 | 209469 | 3086.68 | 0.254051 | 0.846978 | 2(Loss) | true |
| Glaze | 2412.27 | 0.0559465 | 375.657ms | 9378 | 160 | 688.389 | 3707.53 | 0.274361 | 1.01866 | 3(Loss) | true |
| simdjson (ondemand) | 1927.98 | 0.459238 | 465.842ms | 9378 | 640 | 290448 | 4638.81 | 0.125864 | 1.27631 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3819.95 | 0.0902301 | 266.541ms | 9378 | 40 | 178.512 | 2341.28 | 0.0445112 | 0.640432 | 1(Win) | true |
| Jsonifier | 3368.75 | 0.0882111 | 316.97ms | 9378 | 80 | 438.753 | 2654.86 | 0.0145937 | 0.727619 | 2(Loss) | true |
| Glaze | 2615.97 | 0.0603542 | 362.109ms | 9378 | 30 | 127.73 | 3418.83 | 0.305126 | 0.939017 | 3(Loss) | true |
| simdjson (ondemand) | 1986.32 | 0.374703 | 475.102ms | 9378 | 320 | 91085.3 | 4502.58 | 0.519892 | 1.23862 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17355.8 | 0.273616 | 66.6264ms | 11521 | 160 | 480.059 | 633.062 | 0.330624 | 0.136482 | 1(Win) | true |
| Glaze | 5085.29 | 0.155775 | 229.464ms | 11521 | 30 | 339.834 | 2160.6 | 0.106339 | 0.480829 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18704.3 | 0.0575642 | 63.5697ms | 11521 | 320 | 36.589 | 587.419 | 0.0818592 | 0.126402 | 1(Win) | true |
| Glaze | 5409.52 | 0.0733195 | 204.443ms | 11521 | 40 | 88.7077 | 2031.1 | 0.0492102 | 0.451291 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2635.46 | 0.135857 | 178.17ms | 4669 | 80 | 421.492 | 1689.54 | 0.485194 | 0.924323 | 1(Win) | true |
| Jsonifier (two-stage) | 2195.86 | 0.539511 | 211.206ms | 4669 | 40 | 4787.41 | 2027.78 | 0.0603746 | 1.11136 | 2(Loss) | true |
| Glaze | 1571.27 | 0.194565 | 288.093ms | 4669 | 2560 | 77824.1 | 2833.82 | 0.0241996 | 1.56059 | 3(Loss) | true |
| simdjson (ondemand) | 624.272 | 0.0565436 | 733.43ms | 4669 | 30 | 487.964 | 7132.63 | 0.0658509 | 3.95112 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2900.6 | 0.207509 | 163.85ms | 4669 | 40 | 405.887 | 1535.1 | 0.0499674 | 0.838204 | 1(Win) | true |
| Jsonifier (two-stage) | 2386.2 | 0.0871216 | 199.156ms | 4669 | 40 | 105.717 | 1866.03 | 0.296963 | 1.02253 | 2(Loss) | true |
| Glaze | 1789.13 | 0.0825689 | 272.91ms | 4669 | 40 | 168.91 | 2488.75 | 0.21543 | 1.36997 | 3(Loss) | true |
| simdjson (ondemand) | 638.042 | 0.315222 | 731.6ms | 4669 | 1280 | 619431 | 6978.7 | 0.564033 | 3.86406 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17715.8 | 0.0777759 | 27.9278ms | 4669 | 640 | 24.4566 | 251.341 | 0.446837 | 0.124576 | 1(Win) | true |
| Glaze | 3626.38 | 0.216912 | 129.272ms | 4669 | 30 | 212.809 | 1227.87 | 0.138643 | 0.667838 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19881.5 | 0.228284 | 25.0934ms | 4669 | 320 | 83.6475 | 223.963 | 0.0864352 | 0.109542 | 1(Win) | true |
| Glaze | 3944.11 | 0.0833018 | 116.156ms | 4669 | 160 | 141.507 | 1128.95 | 0.0886564 | 0.612397 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3293.28 | 0.297573 | 233.491ms | 7932 | 2560 | 119601 | 2296.96 | 0.134558 | 0.742591 | 1(Win) | true |
| Glaze | 1978.43 | 0.0680469 | 388.279ms | 7932 | 40 | 270.769 | 3823.5 | 0.273621 | 1.24222 | 2(Loss) | true |
| Jsonifier | 1970.37 | 0.178936 | 388.548ms | 7932 | 2560 | 120811 | 3839.14 | 0.199845 | 1.24753 | 3(Loss) | true |
| simdjson (ondemand) | 1038.06 | 0.0481796 | 754.537ms | 7932 | 30 | 369.799 | 7287.17 | 0.0535474 | 2.37579 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3788.95 | 0.107142 | 218.791ms | 7932 | 40 | 183.025 | 1996.47 | 0.0746592 | 0.644658 | 1(Win) | true |
| Glaze | 2119.25 | 0.111038 | 378.299ms | 7932 | 40 | 628.356 | 3569.45 | 0.519774 | 1.15928 | 2(Loss) | true |
| Jsonifier | 2074.97 | 0.0678855 | 376.906ms | 7932 | 80 | 489.987 | 3645.61 | 0.0298215 | 1.18431 | 3(Loss) | true |
| simdjson (ondemand) | 1062.78 | 0.0487161 | 725.611ms | 7932 | 40 | 480.933 | 7117.7 | 0.25871 | 2.31966 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17651.7 | 0.244466 | 52.4406ms | 9249 | 30 | 44.769 | 499.7 | 0.388402 | 0.132483 | 1(Win) | true |
| Glaze | 3442.61 | 0.275104 | 261.781ms | 9249 | 30 | 1490.49 | 2562.17 | 0.0299315 | 0.711576 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20831.7 | 0.107359 | 45.8935ms | 9249 | 160 | 33.0625 | 423.419 | 0.300545 | 0.110978 | 1(Win) | true |
| Glaze | 4201.73 | 0.0687219 | 221.986ms | 9249 | 80 | 166.5 | 2099.26 | 0.0672403 | 0.581439 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 821.126 | 0.0867443 | 559.497ms | 4604 | 80 | 1721.17 | 5347.19 | 0.0577073 | 2.99904 | 1(Win) | true |
| Jsonifier (two-stage) | 718.46 | 0.718511 | 603.02ms | 4604 | 640 | 1.23399e+06 | 6111.29 | 1.23111 | 3.42859 | 2(Loss) | true |
| Glaze | 567.533 | 0.0797907 | 764.15ms | 4604 | 80 | 3048.48 | 7736.5 | 0.274779 | 4.34578 | 3(Loss) | true |
| simdjson (ondemand) | 521.442 | 0.116984 | 863.441ms | 4604 | 30 | 2910.92 | 8420.33 | 0.00395851 | 4.73277 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 963.178 | 0.186162 | 552.746ms | 4604 | 4890 | 352166 | 4558.57 | 0.477235 | 2.55481 | 1(Win) | true |
| Jsonifier (two-stage) | 895.036 | 0.128094 | 589.09ms | 4604 | 30 | 1184.59 | 4905.63 | 0.0210598 | 2.74909 | 2(Loss) | true |
| Glaze | 665.264 | 0.337954 | 750.623ms | 4604 | 1280 | 636809 | 6599.97 | 0.224967 | 3.70581 | 3(Loss) | true |
| simdjson (ondemand) | 544.141 | 0.085632 | 884.746ms | 4604 | 40 | 1909.76 | 8069.07 | 0.280429 | 4.53291 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1499.79 | 0.496366 | 309.292ms | 4604 | 640 | 135143 | 2927.55 | 0.276131 | 1.63591 | 1(Win) | true |
| Glaze | 814.992 | 0.0635356 | 557.369ms | 4604 | 30 | 351.495 | 5387.43 | 0.0997139 | 3.02297 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1446.06 | 0.18287 | 303.42ms | 4604 | 4890 | 150762 | 3036.34 | 0.33453 | 1.69649 | 1(Win) | true |
| Glaze | 812.073 | 0.0898688 | 546.618ms | 4604 | 30 | 708.303 | 5406.8 | 0.0560707 | 3.0335 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2471.87 | 0.430972 | 687.778ms | 18245 | 640 | 588999 | 7039.12 | 0.782654 | 0.997179 | 1(Win) | true |
| Jsonifier | 2009.4 | 0.177257 | 864.327ms | 18245 | 4890 | 1.15205e+06 | 8659.2 | 0.194122 | 1.22793 | 2(Loss) | true |
| simdjson (ondemand) | 1816.14 | 0.128708 | 967.525ms | 18245 | 40 | 6082.23 | 9580.65 | 0.197837 | 1.35928 | 3(Loss) | true |
| Glaze | 1662.19 | 0.347836 | 1060.11ms | 18245 | 320 | 424255 | 10468 | 0.0274124 | 1.48552 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3052.54 | 0.174599 | 664.704ms | 18245 | 2560 | 253564 | 5700.11 | 0.239354 | 0.806841 | 1(Win) | true |
| Jsonifier | 2354.18 | 0.209012 | 837.91ms | 18245 | 2560 | 610933 | 7391.03 | 0.189142 | 1.04771 | 2(Loss) | true |
| simdjson (ondemand) | 1993.8 | 0.139373 | 976.978ms | 18245 | 2560 | 378721 | 8726.93 | 0.122706 | 1.23716 | 3(Loss) | true |
| Glaze | 1802.02 | 0.137399 | 1064.49ms | 18245 | 4890 | 860683 | 9655.72 | 0.0185572 | 1.36993 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5450.69 | 0.195826 | 434.259ms | 24579 | 4890 | 346798 | 4300.44 | 0.295089 | 0.451108 | 1(Win) | true |
| Glaze | 3613.99 | 0.0863409 | 662.646ms | 24579 | 80 | 2508.86 | 6486 | 0.0493127 | 0.682102 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5204.05 | 0.757065 | 426.548ms | 24579 | 40 | 46512.7 | 4504.25 | 0.0491886 | 0.472497 | 1(Win) | true |
| Glaze | 4037.89 | 0.0694294 | 596.807ms | 24579 | 80 | 1299.56 | 5805.1 | 0.0236917 | 0.610225 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 862.63 | 0.162311 | 516.196ms | 4604 | 4890 | 333754 | 5089.92 | 0.0495685 | 2.85386 | 1(Win) | true |
| Jsonifier (two-stage) | 802.247 | 0.238099 | 552.985ms | 4604 | 1280 | 217361 | 5473.02 | 0.36582 | 3.06956 | 2(Loss) | true |
| Glaze | 583.756 | 0.173562 | 752.59ms | 4604 | 2560 | 436270 | 7521.49 | 0.116255 | 4.22507 | 3(Loss) | true |
| simdjson (ondemand) | 509.082 | 0.106963 | 867.441ms | 4604 | 4890 | 416175 | 8624.78 | 1.0437 | 4.84778 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1058.63 | 0.365725 | 502.535ms | 4604 | 1280 | 294512 | 4147.55 | 0.100537 | 2.32329 | 1(Win) | true |
| Jsonifier (two-stage) | 950.309 | 0.847438 | 564.345ms | 4604 | 320 | 490576 | 4620.3 | 0.114097 | 2.5893 | 2(Loss) | true |
| Glaze | 652.391 | 0.143367 | 746.785ms | 4604 | 4890 | 455264 | 6730.19 | 0.107746 | 3.77909 | 3(Loss) | true |
| simdjson (ondemand) | 548.715 | 0.317603 | 884.657ms | 4604 | 4890 | 3.1583e+06 | 8001.81 | 0.191518 | 4.49506 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1429.92 | 0.353545 | 318.825ms | 4604 | 30 | 3535.56 | 3070.6 | 0.226369 | 1.71599 | 1(Win) | true |
| Glaze | 797.658 | 0.0430854 | 554.89ms | 4604 | 80 | 449.975 | 5504.51 | 0.664775 | 3.08819 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1472.07 | 0.0328765 | 306.818ms | 4604 | 80 | 76.9264 | 2982.69 | 0.010476 | 1.66663 | 1(Win) | true |
| Glaze | 836.07 | 0.0586648 | 536.611ms | 4604 | 80 | 759.329 | 5251.61 | 0.309657 | 2.94587 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2767.45 | 0.119037 | 637.333ms | 18245 | 4890 | 273905 | 6287.3 | 1.29438 | 0.890445 | 1(Win) | true |
| Jsonifier | 2198.2 | 0.115359 | 797.243ms | 18245 | 4890 | 407727 | 7915.48 | 0.244185 | 1.12212 | 2(Loss) | true |
| simdjson (ondemand) | 1821.3 | 0.106667 | 960.854ms | 18245 | 4890 | 507801 | 9553.5 | 0.0269227 | 1.35531 | 3(Loss) | true |
| Glaze | 1701.33 | 0.317843 | 1025.8ms | 18245 | 4890 | 5.1671e+06 | 10227.2 | 0.00138415 | 1.45121 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3236.46 | 0.169547 | 628.604ms | 18245 | 2560 | 212699 | 5376.18 | 0.22854 | 0.760906 | 1(Win) | true |
| Jsonifier | 2560.11 | 0.0825623 | 787.49ms | 18245 | 40 | 1259.49 | 6796.5 | 0.319317 | 0.963147 | 2(Loss) | true |
| simdjson (ondemand) | 2021.45 | 0.355526 | 955.22ms | 18245 | 320 | 299679 | 8607.58 | 0.260102 | 1.22048 | 3(Loss) | true |
| Glaze | 1888.23 | 0.148558 | 1042.25ms | 18245 | 2560 | 479745 | 9214.88 | 0.241203 | 1.30726 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5578.28 | 0.0402239 | 423.77ms | 24579 | 40 | 114.276 | 4202.07 | 0.136826 | 0.440895 | 1(Win) | true |
| Glaze | 3638.54 | 0.311294 | 646.031ms | 24579 | 1280 | 514783 | 6442.24 | 0.063929 | 0.677548 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5522.98 | 0.139426 | 423.338ms | 24579 | 4890 | 171230 | 4244.15 | 0.306765 | 0.445296 | 1(Win) | true |
| Glaze | 4195.11 | 0.0591162 | 589.215ms | 24579 | 80 | 872.859 | 5587.54 | 0.0239315 | 0.587202 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1678.58 | 0.0842437 | 298.256ms | 5094 | 80 | 475.554 | 2894.12 | 0.00259152 | 1.46145 | 1(Win) | true |
| Jsonifier (two-stage) | 1510.67 | 0.0797824 | 327.964ms | 5094 | 30 | 197.476 | 3215.8 | 0.156274 | 1.62528 | 2(Loss) | true |
| Glaze | 1185.5 | 0.0904846 | 412.525ms | 5094 | 30 | 412.464 | 4097.87 | 0.000813438 | 2.07461 | 3(Loss) | true |
| simdjson (ondemand) | 864.427 | 0.649135 | 579.563ms | 5094 | 160 | 212937 | 5619.93 | 0.157724 | 2.84892 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2025.89 | 0.0354693 | 290.55ms | 5094 | 160 | 115.747 | 2397.96 | 0.0693778 | 1.20855 | 1(Win) | true |
| Jsonifier (two-stage) | 1829.46 | 0.0260969 | 335.456ms | 5094 | 640 | 307.347 | 2655.43 | 1.24677 | 1.33883 | 2(Loss) | true |
| Glaze | 1489.42 | 0.181459 | 378.518ms | 5094 | 4890 | 171297 | 3261.67 | 0.182156 | 1.64832 | 3(Loss) | true |
| simdjson (ondemand) | 982.365 | 0.217776 | 553.537ms | 5094 | 40 | 4639.31 | 4945.23 | 0.245789 | 2.50532 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13249.3 | 0.347358 | 39.7206ms | 5094 | 80 | 129.771 | 366.663 | 0.0306916 | 0.172819 | 1(Win) | true |
| Glaze | 3145.77 | 0.636546 | 155.676ms | 5094 | 30 | 2898.98 | 1544.3 | 0.00215843 | 0.772222 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15113.6 | 0.0386797 | 34.9969ms | 5094 | 2560 | 39.5718 | 321.432 | 0.0790511 | 0.149818 | 1(Win) | true |
| Glaze | 3466.95 | 0.100474 | 147.203ms | 5094 | 160 | 317.138 | 1401.24 | 0.496192 | 0.700007 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2213.77 | 0.153132 | 351.02ms | 8051 | 4890 | 137936 | 3468.3 | 0.637355 | 1.10919 | 1(Win) | true |
| Jsonifier | 1759.35 | 0.270401 | 441.357ms | 8051 | 2560 | 356492 | 4364.12 | 0.265288 | 1.39814 | 2(Loss) | true |
| Glaze | 1530.53 | 0.458214 | 511.558ms | 8051 | 640 | 338167 | 5016.58 | 0.349208 | 1.60883 | 3(Loss) | true |
| simdjson (ondemand) | 1318.26 | 0.117828 | 586.471ms | 8051 | 80 | 3767.75 | 5824.35 | 0.112761 | 1.86846 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2610.14 | 0.366835 | 343.429ms | 8051 | 2560 | 298095 | 2941.62 | 0.0132943 | 0.939387 | 1(Win) | true |
| Jsonifier | 2050.98 | 0.291696 | 423.412ms | 8051 | 1280 | 152632 | 3743.58 | 0.176215 | 1.19674 | 2(Loss) | true |
| Glaze | 1883.19 | 0.140613 | 469.834ms | 8051 | 40 | 1314.69 | 4077.15 | 0.48693 | 1.30573 | 3(Loss) | true |
| simdjson (ondemand) | 1483.39 | 0.340627 | 563.066ms | 8051 | 640 | 198944 | 5176.02 | 0.043119 | 1.65946 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17108.9 | 0.124997 | 55.1496ms | 9255 | 80 | 33.2657 | 515.888 | 0.167468 | 0.136808 | 1(Win) | true |
| Glaze | 3800.47 | 0.322931 | 235.9ms | 9255 | 2560 | 143991 | 2322.41 | 0.110595 | 0.643661 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17871.2 | 0.439517 | 50.0582ms | 9255 | 160 | 753.904 | 493.881 | 0.399556 | 0.130695 | 1(Win) | true |
| Glaze | 4266.08 | 0.357829 | 212.285ms | 9255 | 1280 | 70154.6 | 2068.94 | 0.0877172 | 0.572522 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6397.44 | 0.297345 | 46.0447ms | 2889 | 30 | 49.1954 | 430.667 | 0.069611 | 0.361475 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6006.73 | 0.35142 | 48.2834ms | 2889 | 4890 | 12705.2 | 458.68 | 0.0362071 | 0.384147 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 6005.77 | 0.117149 | 48.5373ms | 2889 | 320 | 92.4248 | 458.753 | 0.00476813 | 0.38448 | 2(Tie) | true |
| Glaze | 3175.71 | 0.21213 | 91.6874ms | 2889 | 40 | 135.481 | 867.575 | 0.651767 | 0.755036 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6503.16 | 0.075496 | 47.1127ms | 2889 | 320 | 32.7374 | 423.666 | 0.35793 | 0.354458 | 1(Win) | true |
| Jsonifier | 6396.05 | 0.0424473 | 46.9359ms | 2889 | 1280 | 42.7939 | 430.76 | 0.0719503 | 0.361788 | 2(Loss) | true |
| Jsonifier (two-stage) | 6365.68 | 0.0805721 | 47.2365ms | 2889 | 320 | 38.9157 | 432.816 | 0.466403 | 0.363799 | 3(Loss) | true |
| Glaze | 3228.41 | 0.088895 | 89.6392ms | 2889 | 80 | 46.0429 | 853.413 | 0.0454266 | 0.742445 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7408.01 | 0.262687 | 52.4098ms | 3808 | 40 | 66.3327 | 490.225 | 0.98465 | 0.313386 | 1(Win) | true |
| Jsonifier (two-stage) | 7089.49 | 0.231169 | 53.698ms | 3808 | 40 | 56.0897 | 512.25 | 0.230475 | 0.329766 | 2(Loss) | true |
| Jsonifier | 6855.51 | 0.666339 | 53.3092ms | 3808 | 30 | 373.789 | 529.733 | 0.0691693 | 0.342717 | 3(Loss) | true |
| Glaze | 3662.93 | 0.0721834 | 103.118ms | 3808 | 160 | 81.9465 | 991.444 | 0.157979 | 0.656432 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 7703.3 | 0.0968498 | 51.1306ms | 3808 | 30 | 6.25402 | 471.433 | 0.0424058 | 0.303125 | 1(Win) | true |
| Jsonifier | 7536.33 | 0.0436149 | 51.2959ms | 3808 | 640 | 28.2699 | 481.878 | 0.201925 | 0.309481 | 2(Loss) | true |
| simdjson (ondemand) | 7495.93 | 0.203381 | 51.6101ms | 3808 | 80 | 77.6703 | 484.475 | 0.305383 | 0.309549 | 3(Loss) | true |
| Glaze | 3763.31 | 0.0953229 | 101.933ms | 3808 | 40 | 33.8462 | 965 | 0.0862813 | 0.638557 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2070.45 | 0.0708563 | 136.509ms | 2889 | 160 | 142.247 | 1330.71 | 0.0305196 | 1.16995 | 1(Win) | true |
| Glaze | 2044.85 | 0.343375 | 137.615ms | 2889 | 2560 | 54795.8 | 1347.37 | 0.012207 | 1.18518 | 2(Loss) | true |
| Jsonifier (two-stage) | 2023.55 | 0.212621 | 141.51ms | 2889 | 40 | 335.228 | 1361.55 | 0.357485 | 1.19808 | 3(Loss) | true |
| simdjson (ondemand) | 968.977 | 0.273048 | 290.957ms | 2889 | 1280 | 77153.8 | 2843.38 | 0.437912 | 2.53006 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2224.8 | 0.139956 | 133.796ms | 2889 | 80 | 240.316 | 1238.39 | 0.0695985 | 1.08735 | 1(Win) | true |
| Glaze | 2196.78 | 0.0364421 | 138.218ms | 2889 | 320 | 66.8468 | 1254.18 | 0.131983 | 1.10168 | 2(Loss) | true |
| Jsonifier (two-stage) | 2159.5 | 0.221905 | 136.054ms | 2889 | 4890 | 39195.1 | 1275.83 | 0.18133 | 1.12054 | 3(Loss) | true |
| simdjson (ondemand) | 1008.95 | 0.0496339 | 286.473ms | 2889 | 80 | 146.961 | 2730.72 | 0.096036 | 2.42619 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11401 | 0.260679 | 26.8762ms | 2963 | 80 | 33.3949 | 247.85 | 0.0100857 | 0.192896 | 1(Win) | true |
| Glaze | 4874.48 | 0.172946 | 61.633ms | 2963 | 320 | 321.646 | 579.7 | 0.00646928 | 0.483799 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14997.9 | 0.154961 | 21.7771ms | 2963 | 320 | 27.277 | 188.409 | 0.0878298 | 0.140777 | 1(Win) | true |
| Glaze | 5335.54 | 0.108433 | 56.3451ms | 2963 | 320 | 105.531 | 529.606 | 0.210797 | 0.440034 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2508.22 | 0.106093 | 150.427ms | 3808 | 160 | 377.531 | 1447.88 | 0.125027 | 0.967145 | 1(Win) | true |
| Glaze | 2110.65 | 0.0710229 | 179.718ms | 3808 | 30 | 44.8 | 1720.6 | 0.230009 | 1.15342 | 2(Loss) | true |
| Jsonifier | 1824 | 0.0785253 | 209.531ms | 3808 | 160 | 391.094 | 1991 | 0.0829417 | 1.33873 | 3(Loss) | true |
| simdjson (ondemand) | 1195.73 | 0.0611138 | 304.166ms | 3808 | 40 | 137.804 | 3037.12 | 0.125236 | 2.04883 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2724.75 | 0.0976308 | 144.33ms | 3808 | 160 | 270.917 | 1332.82 | 0.0323667 | 0.889383 | 1(Win) | true |
| Glaze | 2212.4 | 0.23849 | 174.001ms | 3808 | 80 | 1226.02 | 1641.47 | 0.0777344 | 1.09901 | 2(Loss) | true |
| Jsonifier | 1884.29 | 0.08689 | 202.998ms | 3808 | 160 | 448.702 | 1927.3 | 0.00907924 | 1.29527 | 3(Loss) | true |
| simdjson (ondemand) | 1291.23 | 0.720762 | 287.966ms | 3808 | 640 | 262995 | 2812.5 | 0.0864254 | 1.89712 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10063.8 | 0.118856 | 44.018ms | 4300 | 320 | 75.0592 | 407.481 | 0.496339 | 0.229051 | 1(Win) | true |
| Glaze | 3716.43 | 0.141292 | 115.055ms | 4300 | 40 | 97.225 | 1103.42 | 0.35295 | 0.649965 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11889.4 | 0.234441 | 37.1564ms | 4300 | 80 | 52.3087 | 344.913 | 0.338182 | 0.191497 | 1(Win) | true |
| Glaze | 4240.96 | 0.509893 | 98.059ms | 4300 | 40 | 972.356 | 966.95 | 0.955314 | 0.566093 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3951.68 | 0.285257 | 5792.48ms | 466906 | 320 | 3.30611e+07 | 112680 | 0.332999 | 0.626326 | 1(Win) | true |
| Glaze | 2506.52 | 0.201374 | 9072.99ms | 466906 | 160 | 2.04759e+07 | 177647 | 0.131036 | 0.987537 | 2(Loss) | true |
| simdjson (ondemand) | 1687.38 | 0.0862415 | 6752.35ms | 466906 | 1280 | 6.62939e+07 | 263885 | 0.140388 | 1.46698 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3888.21 | 0.129408 | 5819.38ms | 466906 | 1280 | 2.81121e+07 | 114520 | 0.348249 | 0.636545 | 1(Win) | true |
| Glaze | 2468.96 | 0.135108 | 9219.76ms | 466906 | 320 | 1.89996e+07 | 180350 | 0.147742 | 1.0026 | 2(Loss) | true |
| simdjson (ondemand) | 1685.55 | 0.102806 | 6712.6ms | 466906 | 640 | 4.72058e+07 | 264173 | 0.249928 | 1.46863 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5578.95 | 0.275541 | 6529.87ms | 699405 | 160 | 1.73638e+07 | 119557 | 0.000292746 | 0.443655 | 1(Win) | true |
| Glaze | 3819.85 | 0.172695 | 8965.6ms | 699405 | 320 | 2.90988e+07 | 174615 | 0.280175 | 0.648007 | 2(Loss) | true |
| simdjson (ondemand) | 2252.65 | 0.0647201 | 8344.21ms | 767297 | 1280 | 5.65756e+07 | 324841 | 0.272509 | 1.0989 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5589.83 | 0.183638 | 6311.89ms | 699405 | 160 | 7.68255e+06 | 119325 | 0.209805 | 0.442798 | 1(Win) | true |
| Glaze | 3874.79 | 0.146403 | 9007.89ms | 699405 | 320 | 2.0324e+07 | 172140 | 0.217489 | 0.638852 | 2(Loss) | true |
| simdjson (ondemand) | 2214.23 | 0.260159 | 8374.59ms | 767297 | 640 | 4.73086e+08 | 330476 | 0.305309 | 1.11799 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3791.58 | 0.274332 | 8199.46ms | 631514 | 640 | 1.21523e+08 | 158841 | 0.0976054 | 0.652855 | 1(Win) | true |
| Glaze | 2377.43 | 0.203721 | 6514.38ms | 631514 | 160 | 4.26131e+07 | 253323 | 0.478838 | 1.04127 | 2(Loss) | true |
