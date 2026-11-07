# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26200 using the MSVC 19.51.36260.0 compiler).  

Latest Results: (Nov 07, 2026)
#### Using the following commits:
----
| Jsonifier: [3e5ab01](https://github.com/nihilai-collective/Jsonifier/commit/3e5ab01)  
| Glaze: [0a363d40](https://github.com/stephenberry/glaze/commit/0a363d40)  
| simdjson: [dfe02cfe3](https://github.com/simdjson/simdjson/commit/dfe02cfe3)  

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
*Environment generated via BenchmarkSuite commit: [ed43ce8](https://github.com/nihilai-collective/benchmarksuite/commit/ed43ce8)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 504.843 | 0.151218 | 174.249ms | 905 | 4890 | 32681.6 | 1709.59 | 0.143079 | 5.95553 | 1(Win) | true |
| Jsonifier | 477.868 | 0.0761133 | 188.672ms | 905 | 4890 | 9240.83 | 1806.09 | 0.832172 | 6.29667 | 2(Loss) | true |
| Jsonifier (two-stage) | 267.258 | 0.136169 | 338.003ms | 905 | 160 | 3093.95 | 3229.38 | 0.289464 | 11.3074 | 3(Loss) | true |
| simdjson (ondemand) | 69.4988 | 0.0376318 | 1250.99ms | 905 | 4890 | 106798 | 12418.6 | 0.26282 | 43.669 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 602.496 | 0.52356 | 142.908ms | 905 | 40 | 2250 | 1432.5 | 0.408879 | 4.99097 | 1(Win) | true |
| Jsonifier | 540.055 | 0.176064 | 163.655ms | 905 | 640 | 5066.9 | 1598.12 | 0.649478 | 5.56522 | 2(Loss) | true |
| Jsonifier (two-stage) | 287.25 | 0.121403 | 308.628ms | 905 | 1280 | 17031.1 | 3004.61 | 0.200615 | 10.5095 | 3(Loss) | true |
| simdjson (ondemand) | 71.6245 | 0.0466841 | 1218.7ms | 905 | 80 | 2531.65 | 12050 | 0.0830565 | 42.3661 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1265.59 | 0.392565 | 69.3514ms | 905 | 1280 | 9173.66 | 681.953 | 0.171546 | 2.33328 | 1(Win) | true |
| Glaze | 24.3967 | 0.306876 | 981.422ms | 905 | 30 | 353575 | 35376.7 | 0.0659134 | 124.203 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1680.21 | 0.187012 | 59.6248ms | 905 | 1280 | 1181.19 | 513.672 | 0.106351 | 1.74591 | 1(Win) | true |
| Glaze | 297.965 | 0.0958117 | 313.494ms | 905 | 320 | 2464.64 | 2896.56 | 0.0323764 | 10.0616 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 637.9 | 0.065951 | 274.256ms | 1811 | 4890 | 15591.3 | 2707.48 | 0.0337386 | 4.7292 | 1(Win) | true |
| Jsonifier (two-stage) | 477.171 | 0.0832199 | 364.731ms | 1811 | 4890 | 44366.3 | 3619.47 | 0.41658 | 6.33396 | 2(Loss) | true |
| Glaze | 422.146 | 0.0890434 | 382.931ms | 1811 | 80 | 1061.71 | 4091.25 | 0.0915751 | 7.15719 | 3(Loss) | true |
| simdjson (ondemand) | 148.281 | 0.0777931 | 1171.52ms | 1811 | 640 | 52544.6 | 11647.5 | 0.126259 | 20.4566 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 838.4 | 0.267562 | 208.935ms | 1811 | 80 | 2430.38 | 2060 | 0 | 3.5716 | 1(Win) | true |
| Jsonifier (two-stage) | 578.526 | 0.14076 | 299.423ms | 1811 | 2560 | 45205.4 | 2985.35 | 0.0851231 | 5.20907 | 2(Loss) | true |
| Glaze | 572.422 | 0.197247 | 304.158ms | 1811 | 320 | 11333.8 | 3017.19 | 0.0933029 | 5.23417 | 3(Loss) | true |
| simdjson (ondemand) | 156.825 | 0.113068 | 1102.92ms | 1811 | 2560 | 396940 | 11013 | 0.00851197 | 19.3328 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 471.967 | 0.141492 | 369.179ms | 1811 | 640 | 17157.7 | 3659.38 | 0.297999 | 6.41027 | 1(Win) | true |
| Glaze | 150.117 | 0.0965534 | 1166.68ms | 1798 | 40 | 4865.38 | 11422.5 | 0.314696 | 20.2012 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 775.938 | 0.0621891 | 233.38ms | 1811 | 4890 | 9369.58 | 2225.83 | 0.0073757 | 3.86309 | 1(Win) | true |
| Glaze | 385.544 | 0.179795 | 465.056ms | 1798 | 40 | 2557.69 | 4447.5 | 0.0187406 | 7.83742 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1461.23 | 0.145271 | 254.256ms | 3862 | 1280 | 17161.5 | 2520.55 | 0.183207 | 2.06151 | 1(Win) | true |
| Glaze | 921.781 | 0.12516 | 406.924ms | 3862 | 640 | 16005.9 | 3995.62 | 0.0781494 | 3.2836 | 2(Loss) | true |
| Jsonifier (two-stage) | 849.751 | 0.0835532 | 435.313ms | 3862 | 4890 | 64132.1 | 4334.31 | 0.171043 | 3.55898 | 3(Loss) | true |
| simdjson (ondemand) | 307.212 | 0.123633 | 1199.68ms | 3862 | 4890 | 1.07429e+06 | 11988.8 | 0.00947118 | 9.87597 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1973.03 | 0.187717 | 190.116ms | 3862 | 1280 | 15717.1 | 1866.72 | 0 | 1.51762 | 1(Win) | true |
| Glaze | 1106.03 | 0.255544 | 335.764ms | 3862 | 30 | 2172.41 | 3330 | 0 | 2.72163 | 2(Loss) | true |
| Jsonifier (two-stage) | 994.018 | 0.092124 | 372.829ms | 3862 | 4890 | 56975.8 | 3705.26 | 0.199335 | 3.02686 | 3(Loss) | true |
| simdjson (ondemand) | 325.973 | 0.0597576 | 1136.68ms | 3862 | 160 | 7294.03 | 11298.8 | 0.0221214 | 9.2977 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 517.487 | 0.1364 | 722.618ms | 3862 | 1280 | 120632 | 7117.27 | 0.042828 | 5.8559 | 1(Win) | true |
| Glaze | 380.605 | 0.24297 | 973.46ms | 3862 | 4890 | 2.70326e+06 | 9676.93 | 0.15544 | 7.9669 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4191.37 | 0.172777 | 102.785ms | 3862 | 4890 | 11271.9 | 878.732 | 0.404915 | 0.707777 | 1(Win) | true |
| Glaze | 1056.18 | 0.101445 | 374.925ms | 3862 | 320 | 4004.6 | 3487.19 | 0.00896057 | 2.83982 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 983.173 | 0.177469 | 945.617ms | 9578 | 160 | 43496.5 | 9290.62 | 0.181305 | 3.08568 | 1(Win) | true |
| Jsonifier (two-stage) | 788.416 | 0.199546 | 1184.32ms | 9578 | 160 | 85515.3 | 11585.6 | 0.0808538 | 3.8476 | 2(Loss) | true |
| Glaze | 764.456 | 0.124556 | 1273.44ms | 9578 | 80 | 17719.9 | 11948.8 | 0.0732831 | 3.97264 | 3(Loss) | true |
| simdjson (ondemand) | 553.677 | 0.137859 | 1701.28ms | 9578 | 160 | 82761 | 16497.5 | 0.369895 | 5.48251 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1677.94 | 0.112461 | 766.41ms | 9578 | 80 | 2998.42 | 5443.75 | 0.297619 | 1.80277 | 1(Win) | true |
| Jsonifier (two-stage) | 1181.52 | 0.168896 | 1011.26ms | 9578 | 320 | 54557.1 | 7730.94 | 0.149785 | 2.56418 | 2(Loss) | true |
| Glaze | 1128.27 | 0.0986141 | 1025.84ms | 9578 | 1280 | 81585.7 | 8095.86 | 0.0896645 | 2.68338 | 3(Loss) | true |
| simdjson (ondemand) | 723.723 | 0.150408 | 1511.89ms | 9578 | 160 | 57658.8 | 12621.2 | 0.248213 | 4.19186 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1467.8 | 0.225086 | 640.598ms | 9578 | 320 | 62786.4 | 6223.12 | 0.453995 | 2.06449 | 1(Win) | true |
| Glaze | 900.124 | 0.5808 | 1021.11ms | 9578 | 2560 | 8.89279e+06 | 10147.8 | 0.15604 | 3.36925 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7749.13 | 0.418604 | 134.138ms | 9578 | 80 | 1947.78 | 1178.75 | 0.319149 | 0.385324 | 1(Win) | true |
| Glaze | 2539.45 | 0.0674637 | 389.037ms | 9578 | 2560 | 15074.7 | 3596.95 | 0.03691 | 1.18419 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1549.86 | 0.128111 | 243.465ms | 3873 | 2560 | 23862.6 | 2383.16 | 0.733811 | 1.94448 | 1(Win) | true |
| Glaze | 996.54 | 0.154793 | 381.419ms | 3873 | 2560 | 84265.3 | 3706.41 | 0.0147527 | 3.03423 | 2(Loss) | true |
| Jsonifier (two-stage) | 899.982 | 0.149082 | 428.077ms | 3873 | 640 | 23958.4 | 4104.06 | 0.0914564 | 3.36033 | 3(Loss) | true |
| simdjson (ondemand) | 309.962 | 0.0526614 | 1235.93ms | 3873 | 80 | 3150.32 | 11916.2 | 0.136183 | 9.78363 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1840.65 | 0.409224 | 199.562ms | 3873 | 30 | 2022.99 | 2006.67 | 0.500835 | 1.62592 | 1(Win) | true |
| Glaze | 1145.96 | 0.103743 | 330.026ms | 3873 | 160 | 1788.92 | 3223.12 | 0.0193949 | 2.61728 | 2(Loss) | true |
| Jsonifier (two-stage) | 1049.31 | 0.211017 | 363.435ms | 3873 | 30 | 1655.17 | 3520 | 0.189753 | 2.87813 | 3(Loss) | true |
| simdjson (ondemand) | 326.486 | 0.0956976 | 1164.57ms | 3873 | 320 | 37507.4 | 11313.1 | 0.0386869 | 9.29396 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 522.43 | 0.0902614 | 735.17ms | 3873 | 160 | 6515.72 | 7070 | 0.0176835 | 5.80183 | 1(Win) | true |
| Glaze | 379.078 | 0.809462 | 996.543ms | 3873 | 640 | 3.98118e+06 | 9743.59 | 0.123631 | 7.99687 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4660.67 | 0.286337 | 95.7729ms | 3873 | 160 | 823.899 | 792.5 | 0 | 0.632549 | 1(Win) | true |
| Glaze | 1083.86 | 0.064322 | 377.285ms | 3873 | 320 | 1537.52 | 3407.81 | 0.319927 | 2.78462 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 870.077 | 0.621083 | 5377.27ms | 94653 | 1280 | 5.31451e+08 | 103747 | 0.0595249 | 3.4921 | 1(Tie) | true |
| Glaze STATISTICAL TIE | 867.269 | 0.681551 | 5352.4ms | 94653 | 1280 | 6.44121e+08 | 104083 | 1.19288 | 3.5035 | 1(Tie) | true |
| Jsonifier (two-stage) | 781.842 | 0.625097 | 5905.85ms | 94653 | 1280 | 6.66708e+08 | 115456 | 0.9409 | 3.88624 | 3(Loss) | true |
| simdjson (ondemand) | 671.458 | 0.45888 | 6976.07ms | 94653 | 1280 | 4.87123e+08 | 134436 | 0.0129609 | 4.52541 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1420.43 | 0.157332 | 8055.91ms | 94653 | 4890 | 4.88849e+07 | 63550.1 | 0.50479 | 2.13896 | 1(Win) | true |
| Glaze | 1412.04 | 0.225156 | 8135.44ms | 94653 | 40 | 828712 | 63927.5 | 0.0117334 | 2.15178 | 2(Loss) | true |
| Jsonifier (two-stage) | 1199.13 | 0.0802031 | 9270.99ms | 94653 | 4890 | 1.78248e+07 | 75277.8 | 0.0449794 | 2.53386 | 3(Loss) | true |
| simdjson (ondemand) | 982.403 | 0.111974 | 5552.35ms | 94653 | 80 | 846861 | 91885 | 0.0380766 | 3.0931 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11971.9 | 0.120652 | 767.179ms | 94653 | 30 | 2482.76 | 7540 | 0.265957 | 0.252843 | 1(Win) | true |
| Glaze | 3882.05 | 1.25129 | 2289.51ms | 94653 | 2560 | 2.16721e+08 | 23252.7 | 0.729493 | 0.782027 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12527 | 0.0489612 | 724.798ms | 94653 | 4890 | 60867.6 | 7205.87 | 0.0484049 | 0.241357 | 1(Win) | true |
| Glaze | 4603.33 | 0.0955289 | 2004.5ms | 94653 | 1280 | 449163 | 19609.3 | 0.0449998 | 0.658879 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1034.6 | 0.517242 | 5934.75ms | 124597 | 1280 | 4.51715e+08 | 114851 | 0.102412 | 2.93691 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1013.41 | 1.00854 | 6104.54ms | 124597 | 640 | 8.94978e+08 | 117252 | 0.536972 | 2.99833 | 1(Tie) | true |
| Glaze | 970.008 | 0.630748 | 6145.04ms | 124597 | 2560 | 1.52833e+09 | 122499 | 0.0424291 | 3.1325 | 3(Loss) | true |
| simdjson (ondemand) | 814.813 | 1.64241 | 7384.04ms | 124597 | 320 | 1.83576e+09 | 145831 | 1.11816 | 3.72914 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1610.6 | 0.166665 | 9235.66ms | 124597 | 30 | 453575 | 73776.7 | 0.031617 | 1.88654 | 1(Win) | true |
| Glaze | 1597.75 | 0.296713 | 9262.16ms | 124597 | 30 | 1.46079e+06 | 74370 | 0.80032 | 1.9016 | 2(Loss) | true |
| Jsonifier (two-stage) | 1551.09 | 0.210865 | 9636.27ms | 124597 | 40 | 1.04379e+06 | 76607.5 | 0.175442 | 1.95895 | 3(Loss) | true |
| simdjson (ondemand) | 1238.37 | 0.174749 | 5850.9ms | 124597 | 40 | 1.12461e+06 | 95952.5 | 0.357402 | 2.45415 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13142.7 | 1.22573 | 1019.9ms | 136037 | 80 | 1.17119e+06 | 9871.25 | 0.0887199 | 0.230629 | 1(Win) | true |
| Glaze | 4426.51 | 1.23756 | 2893.39ms | 136076 | 2560 | 3.36988e+08 | 29317 | 0.813205 | 0.686046 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13275.3 | 0.117181 | 1023.89ms | 136037 | 640 | 83930.3 | 9772.66 | 1.03013 | 0.227882 | 1(Win) | true |
| Glaze | 5180.14 | 0.368596 | 2617.48ms | 136076 | 160 | 1.36427e+06 | 25051.9 | 0.553268 | 0.5858 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 692.686 | 0.560502 | 9724.74ms | 2251027 | 160 | 4.82795e+10 | 3.09916e+06 | 1.78009 | 4.3875 | 1(Win) | true |
| Jsonifier (two-stage) | 657.999 | 0.531392 | 10129.2ms | 2251027 | 160 | 4.80906e+10 | 3.26254e+06 | 0.862957 | 4.61873 | 2(Loss) | true |
| simdjson (ondemand) | 434.622 | 0.580872 | 7473.43ms | 2251027 | 30 | 2.46957e+10 | 4.93935e+06 | 0.0323359 | 6.9929 | 3(Loss) | true |
| Glaze | 386.083 | 1.18838 | 8180.47ms | 2251027 | 30 | 1.30988e+11 | 5.56033e+06 | 0.55443 | 7.87172 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 844.608 | 0.495598 | 9527.53ms | 2251027 | 160 | 2.53882e+10 | 2.54171e+06 | 0.575633 | 3.59827 | 1(Win) | true |
| Jsonifier (two-stage) | 797.588 | 0.901131 | 10033.9ms | 2251027 | 40 | 2.3531e+10 | 2.69155e+06 | 0.423882 | 3.81039 | 2(Loss) | true |
| simdjson (ondemand) | 485.586 | 0.22882 | 7390.33ms | 2251027 | 80 | 8.18669e+09 | 4.42094e+06 | 0.275529 | 6.25898 | 3(Loss) | true |
| Glaze | 451.44 | 0.613007 | 8093.75ms | 2251027 | 80 | 6.798e+10 | 4.75533e+06 | 1.20461 | 6.73244 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1234.44 | 0.626454 | 5012.62ms | 2090234 | 160 | 1.63737e+10 | 1.61482e+06 | 0.140414 | 2.46174 | 1(Win) | true |
| Glaze | 916.372 | 0.126125 | 6757.42ms | 2090234 | 80 | 6.02193e+08 | 2.17532e+06 | 0.175512 | 3.31637 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1517.97 | 0.459495 | 8180.39ms | 2090234 | 320 | 1.16514e+10 | 1.31321e+06 | 0.373379 | 2.00189 | 1(Win) | true |
| Glaze | 1286.04 | 0.135352 | 9922.13ms | 2090234 | 30 | 1.32048e+08 | 1.55003e+06 | 0.0852324 | 2.36318 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1506.61 | 0.423826 | 5110.34ms | 5373214 | 80 | 1.66239e+10 | 3.40121e+06 | 0.490567 | 2.01718 | 1(Win) | true |
| Jsonifier | 1415.23 | 0.155362 | 5512.66ms | 5373214 | 30 | 9.4935e+08 | 3.62082e+06 | 0.158919 | 2.14744 | 2(Loss) | true |
| simdjson (ondemand) | 962.196 | 0.277775 | 7998.34ms | 5373214 | 40 | 8.75362e+09 | 5.32562e+06 | 0.467452 | 3.15871 | 3(Loss) | true |
| Glaze | 854.839 | 1.06629 | 8755.8ms | 5373214 | 30 | 1.22566e+11 | 5.99446e+06 | 0.0700156 | 3.55522 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1773.36 | 0.763441 | 5141.61ms | 5373214 | 30 | 1.45998e+10 | 2.8896e+06 | 0.193827 | 1.71374 | 1(Win) | true |
| Jsonifier | 1616.14 | 0.461813 | 5502.29ms | 5373214 | 80 | 1.71527e+10 | 3.1707e+06 | 0.728331 | 1.88048 | 2(Loss) | true |
| simdjson (ondemand) | 1065.77 | 0.549379 | 8155.72ms | 5373214 | 30 | 2.09318e+10 | 4.80807e+06 | 0.914119 | 2.85159 | 3(Loss) | true |
| Glaze | 1006.05 | 0.332601 | 8386.65ms | 5373214 | 80 | 2.29597e+10 | 5.09348e+06 | 0.324922 | 3.02102 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2951.64 | 0.243676 | 6695.72ms | 6661897 | 40 | 1.10041e+09 | 2.15246e+06 | 0.225716 | 1.02961 | 1(Win) | true |
| Glaze | 1482.32 | 0.115717 | 6438.41ms | 6661897 | 80 | 1.96787e+09 | 4.28603e+06 | 0.137495 | 2.05028 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4772.76 | 0.14611 | 8695.53ms | 6661897 | 80 | 3.02626e+08 | 1.33116e+06 | 0.144777 | 0.636628 | 1(Win) | true |
| Glaze | 3390.8 | 0.106135 | 5827.59ms | 6661897 | 40 | 1.58185e+08 | 1.87368e+06 | 0.129168 | 0.896237 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1485.43 | 0.707505 | 8131.49ms | 500299 | 1280 | 6.61038e+09 | 321202 | 0.24467 | 2.04583 | 1(Win) | true |
| Jsonifier (two-stage) | 1227.38 | 0.38917 | 9858.72ms | 500299 | 1280 | 2.92949e+09 | 388734 | 1.0308 | 2.47597 | 2(Loss) | true |
| Glaze | 868.478 | 0.480818 | 6974.15ms | 500299 | 320 | 2.23282e+09 | 549378 | 0.149831 | 3.49947 | 3(Loss) | true |
| simdjson (ondemand) | 575.849 | 0.110432 | 5243.03ms | 500299 | 160 | 1.33953e+08 | 828554 | 0.154473 | 5.27785 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1797.5 | 0.85574 | 7807.54ms | 500299 | 160 | 8.25517e+08 | 265437 | 0.502059 | 1.69071 | 1(Win) | true |
| Jsonifier (two-stage) | 1449.11 | 0.0455994 | 9321.09ms | 500299 | 1280 | 2.88527e+07 | 329253 | 0.298103 | 2.09708 | 2(Loss) | true |
| Glaze | 985.108 | 0.157665 | 6791.1ms | 500299 | 40 | 2.33249e+07 | 484335 | 0.00653775 | 3.08526 | 3(Loss) | true |
| simdjson (ondemand) | 604.268 | 0.125552 | 5196.71ms | 500299 | 320 | 3.14481e+08 | 789587 | 0.0546269 | 5.02941 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8874.98 | 0.0521296 | 5437.17ms | 500299 | 1280 | 1.00532e+06 | 53760.4 | 0.120616 | 0.342298 | 1(Win) | true |
| Glaze | 4319.77 | 0.391387 | 5635.66ms | 500299 | 640 | 1.196e+08 | 110451 | 0.439904 | 0.703382 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8914.78 | 0.0717747 | 5377.01ms | 500299 | 2560 | 3.77764e+06 | 53520.4 | 0.0614191 | 0.340739 | 1(Win) | true |
| Glaze | 4788.12 | 0.162445 | 5156.89ms | 500299 | 640 | 1.67697e+07 | 99647.2 | 0.153589 | 0.634498 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) DID NOT CONVERGE | 2512.62 | 1.24664 | 5548.72ms | 1151920 | 160 | 4.75331e+09 | 437216 | 3.30684 | 1.20939 | -(Win) | false |
| Jsonifier | 2367.64 | 0.127766 | 5911.35ms | 1151920 | 320 | 1.12458e+08 | 463988 | 0.0304333 | 1.28351 | 2(Loss) | true |
| Glaze | 1648.34 | 0.157462 | 8469.21ms | 1151920 | 640 | 7.04828e+08 | 666461 | 0.0185179 | 1.84376 | 3(Loss) | true |
| simdjson (ondemand) | 1211.98 | 0.176988 | 5687.43ms | 1151920 | 80 | 2.05886e+08 | 906411 | 1.10403 | 2.50734 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) DID NOT CONVERGE | 2939.94 | 0.298259 | 5343.75ms | 1151920 | 160 | 1.98735e+08 | 373667 | 3.75798 | 1.03362 | -(Win) | false |
| Jsonifier | 2653.3 | 0.212249 | 5858.96ms | 1151920 | 30 | 2.31678e+07 | 414033 | 0.0636424 | 1.14545 | 2(Loss) | true |
| Glaze | 1787.07 | 0.242306 | 8317.59ms | 1151920 | 30 | 6.656e+07 | 614727 | 0.0358011 | 1.70064 | 3(Loss) | true |
| simdjson (ondemand) | 1203.92 | 1.55555 | 5893.35ms | 1151920 | 80 | 1.61179e+10 | 912481 | 1.0441 | 2.5243 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4572.08 | 0.102892 | 7814.02ms | 1439562 | 1280 | 1.22181e+08 | 300274 | 0.0992639 | 0.664281 | 1(Win) | true |
| Glaze | 1831.1 | 0.870538 | 9477.07ms | 1439584 | 320 | 1.36326e+10 | 749767 | 0.276473 | 1.65924 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13523.1 | 0.348748 | 5242.47ms | 1439562 | 1280 | 1.6045e+08 | 101520 | 0.197461 | 0.224578 | 1(Win) | true |
| Glaze | 7119.57 | 0.419586 | 9918.08ms | 1439584 | 2560 | 1.6759e+09 | 192834 | 0.670061 | 0.426692 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1288.24 | 0.0792236 | 4304.89ms | 56369 | 320 | 349743 | 41729.7 | 0.894315 | 2.35799 | 1(Win) | true |
| Glaze | 1196.77 | 0.168416 | 4557.43ms | 56369 | 2560 | 1.4651e+07 | 44919 | 0.0769337 | 2.53817 | 2(Loss) | true |
| Jsonifier (two-stage) | 1041.52 | 0.0581221 | 5300.6ms | 56369 | 1280 | 1.15197e+06 | 51614.7 | 0.0184627 | 2.9167 | 3(Loss) | true |
| simdjson (ondemand) | 677.545 | 0.072324 | 7978.8ms | 56369 | 640 | 2.10741e+06 | 79341.9 | 0.0743851 | 4.48421 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2056.53 | 0.784349 | 3234.2ms | 56369 | 30 | 1.2611e+06 | 26140 | 0.152788 | 1.47621 | 1(Win) | true |
| Jsonifier | 1904.72 | 0.106601 | 3317.83ms | 56369 | 640 | 579325 | 28223.4 | 0.219855 | 1.59433 | 2(Loss) | true |
| Jsonifier (two-stage) | 1423.42 | 0.166513 | 4239.07ms | 56369 | 320 | 1.26549e+06 | 37766.6 | 0.263262 | 2.13407 | 3(Loss) | true |
| simdjson (ondemand) | 850.503 | 0.179924 | 6941.79ms | 56369 | 160 | 2.06932e+06 | 63206.9 | 0.0900633 | 3.57218 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11383.3 | 0.160614 | 503.033ms | 56369 | 40 | 2301.28 | 4722.5 | 0.299085 | 0.265813 | 1(Win) | true |
| Glaze | 4197.82 | 0.106607 | 1323.64ms | 56369 | 1280 | 238571 | 12806.1 | 0.834143 | 0.722422 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11731.1 | 0.154058 | 477.993ms | 56369 | 40 | 1993.59 | 4582.5 | 0.380435 | 0.256728 | 1(Win) | true |
| Glaze | 4830.52 | 0.289508 | 1179.78ms | 56369 | 160 | 166086 | 11128.8 | 1.55904 | 0.626735 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1499.06 | 0.942886 | 5411.14ms | 83958 | 1280 | 3.24651e+08 | 53412.7 | 1.49282 | 2.0265 | 1(Win) | true |
| Jsonifier (two-stage) | 1436.21 | 0.953108 | 5570.6ms | 83958 | 1280 | 3.61398e+08 | 55750.1 | 0.405718 | 2.11521 | 2(Loss) | true |
| Jsonifier | 1360.5 | 0.61778 | 5929.19ms | 83958 | 2560 | 3.38401e+08 | 58852.1 | 0.818017 | 2.233 | 3(Loss) | true |
| simdjson (ondemand) | 971.898 | 0.11883 | 8683.16ms | 83958 | 80 | 766695 | 82383.8 | 0.137883 | 3.12652 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2320.45 | 0.275874 | 4028.99ms | 83958 | 160 | 1.44984e+06 | 34505.6 | 0.240324 | 1.3088 | 1(Win) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 1990.26 | 0.0678212 | 4522.81ms | 83958 | 640 | 476451 | 40230.3 | 3.51648 | 1.52623 | -(Loss) | false |
| Jsonifier | 1827.77 | 0.358343 | 4970.16ms | 83958 | 30 | 739264 | 43806.7 | 0.0380315 | 1.66187 | 3(Loss) | true |
| simdjson (ondemand) | 1175.95 | 0.592399 | 7233.94ms | 83958 | 2560 | 4.16498e+08 | 68088.2 | 0.00665453 | 2.58374 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12456.5 | 0.0959689 | 748.174ms | 94370 | 40 | 1923.08 | 7225 | 0.115473 | 0.242954 | 1(Win) | true |
| Glaze | 3850.19 | 0.664657 | 2301.89ms | 94370 | 40 | 965513 | 23375 | 0.135656 | 0.788554 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13003.1 | 0.103536 | 710.14ms | 94370 | 2560 | 131461 | 6921.29 | 0.0761335 | 0.232544 | 1(Win) | true |
| Glaze | 4605.85 | 1.06041 | 1985.67ms | 94370 | 30 | 1.288e+06 | 19540 | 0.845737 | 0.658846 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1069.24 | 0.195021 | 4801.37ms | 53331 | 30 | 258161 | 47566.7 | 0.0140135 | 2.84084 | 1(Win) | true |
| Glaze | 1054.1 | 0.241728 | 4922.87ms | 53331 | 30 | 408103 | 48250 | 0.0345543 | 2.8822 | 2(Loss) | true |
| Jsonifier (two-stage) | 919.282 | 0.412825 | 5661.33ms | 53331 | 80 | 4.17335e+06 | 55326.2 | 0.755639 | 3.30468 | 3(Loss) | true |
| simdjson (ondemand) | 639.764 | 0.134735 | 8328.92ms | 53331 | 80 | 917847 | 79498.8 | 0.181148 | 4.74871 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1637.26 | 0.094169 | 3777.71ms | 53331 | 320 | 273837 | 31064.4 | 0.0623316 | 1.85425 | 1(Win) | true |
| Glaze | 1625.05 | 0.119097 | 3799.76ms | 53331 | 640 | 889212 | 31297.7 | 0.0644433 | 1.86883 | 2(Loss) | true |
| Jsonifier (two-stage) | 1308.41 | 0.129603 | 4638.45ms | 53331 | 640 | 1.62437e+06 | 38872 | 0.142492 | 2.3214 | 3(Loss) | true |
| simdjson (ondemand) | 806.348 | 0.182288 | 7246ms | 53331 | 80 | 1.05759e+06 | 63075 | 0.268796 | 3.76802 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11299.3 | 0.14803 | 516.044ms | 58581 | 1280 | 68567.9 | 4944.3 | 0.0142189 | 0.267626 | 1(Win) | true |
| Glaze | 4435.88 | 1.04274 | 1243.6ms | 58581 | 4890 | 8.43356e+07 | 12594.4 | 2.36177 | 0.683674 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12180.3 | 0.172824 | 480.727ms | 58581 | 30 | 1885.06 | 4586.67 | 0.364697 | 0.246998 | 1(Win) | true |
| Glaze | 5653.35 | 1.01394 | 1008.63ms | 58581 | 4890 | 4.90952e+07 | 9882.15 | 0.419555 | 0.535196 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1121.91 | 0.815511 | 5534.56ms | 65103 | 2560 | 5.21417e+08 | 55340.5 | 0.136346 | 2.70688 | 1(Win) | true |
| Jsonifier | 1039.7 | 0.630239 | 5947.69ms | 65103 | 4890 | 6.92639e+08 | 59716.4 | 0.907516 | 2.92156 | 2(Loss) | true |
| Jsonifier (two-stage) | 1005.23 | 0.642594 | 6101.16ms | 65103 | 4890 | 7.70294e+08 | 61764.3 | 0.515742 | 3.0222 | 3(Loss) | true |
| simdjson (ondemand) | 721.515 | 0.484591 | 8592.69ms | 65103 | 4890 | 8.50298e+08 | 86050.9 | 0.08828 | 4.21102 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1754.86 | 0.166748 | 4429.92ms | 65103 | 30 | 104414 | 35380 | 0.794467 | 1.73002 | 1(Win) | true |
| Jsonifier | 1566.72 | 0.253711 | 4838.32ms | 65103 | 160 | 1.61741e+06 | 39628.8 | 0.170622 | 1.93858 | 2(Loss) | true |
| Jsonifier (two-stage) | 1494.41 | 0.535393 | 4979.65ms | 65103 | 80 | 3.95821e+06 | 41546.2 | 0.678341 | 2.03219 | 3(Loss) | true |
| simdjson (ondemand) | 945.296 | 0.196821 | 7478.32ms | 65103 | 160 | 2.67381e+06 | 65680 | 0.0723727 | 3.21409 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11426.4 | 0.0917507 | 688.059ms | 78778 | 80 | 2911.39 | 6575 | 0.265453 | 0.265425 | 1(Win) | true |
| Glaze | 2796 | 1.01947 | 2736.03ms | 78778 | 30 | 2.25114e+06 | 26870 | 0.473638 | 1.08645 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11900 | 0.125558 | 663.022ms | 78778 | 30 | 1885.06 | 6313.33 | 0.681699 | 0.253893 | 1(Win) | true |
| Glaze | 3191.48 | 1.30245 | 2401.03ms | 78778 | 2560 | 2.40653e+08 | 23540.4 | 0.988581 | 0.950274 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1355.06 | 0.30245 | 872.301ms | 11812 | 160 | 101147 | 8313.12 | 0.0826322 | 2.2376 | 1(Win) | true |
| Jsonifier (two-stage) | 1206.69 | 0.248927 | 976.875ms | 11812 | 640 | 345606 | 9335.31 | 0.406734 | 2.51314 | 2(Loss) | true |
| Glaze | 947.817 | 0.314326 | 1253.89ms | 11812 | 160 | 223296 | 11885 | 0.345876 | 3.20182 | 3(Loss) | true |
| simdjson (ondemand) | 533.087 | 0.216252 | 2200.44ms | 11812 | 160 | 334112 | 21131.2 | 0.0650272 | 5.69751 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1516.38 | 0.368188 | 853.294ms | 11812 | 640 | 478797 | 7428.75 | 1.2997 | 1.99918 | 1(Win) | true |
| Jsonifier (two-stage) | 1339.45 | 0.783661 | 967.941ms | 11812 | 40 | 173744 | 8410 | 0.0396511 | 2.26113 | 2(Loss) | true |
| Glaze | 1118.44 | 0.234424 | 1160.78ms | 11812 | 320 | 178391 | 10071.9 | 0.386221 | 2.71134 | 3(Loss) | true |
| simdjson (ondemand) | 566.455 | 0.972078 | 2087.22ms | 11812 | 4890 | 1.82737e+08 | 19886.5 | 0.0896423 | 5.35949 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9621.61 | 0.233807 | 124.69ms | 11812 | 1280 | 9591.26 | 1170.78 | 0.106652 | 0.310307 | 1(Win) | true |
| Glaze | 3576.26 | 0.112347 | 329.938ms | 11812 | 2560 | 32059.4 | 3149.88 | 0.504786 | 0.843286 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10581.9 | 0.164981 | 113.493ms | 11812 | 1280 | 3948.18 | 1064.53 | 0.132275 | 0.281325 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 4023.14 | 0.361693 | 304.037ms | 11812 | 40 | 4102.56 | 2800 | 3.89016 | 0.745674 | -(Loss) | false |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2354.24 | 0.263278 | 1087.77ms | 25388 | 160 | 117301 | 10284.4 | 0.176549 | 1.28845 | 1(Win) | true |
| Jsonifier | 2142.05 | 0.231963 | 1183ms | 25388 | 160 | 109990 | 11303.1 | 0.46106 | 1.41657 | 2(Loss) | true |
| Glaze | 1586.62 | 0.250187 | 1611.15ms | 25388 | 80 | 116608 | 15260 | 0.131234 | 1.91153 | 3(Loss) | true |
| simdjson (ondemand) | 1050.07 | 0.437818 | 2371.62ms | 25388 | 40 | 407635 | 23057.5 | 0.241563 | 2.8924 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2461.81 | 0.428452 | 1069.28ms | 25388 | 80 | 142051 | 9835 | 1.75892 | 1.2318 | 1(Win) | true |
| Jsonifier | 2374.81 | 0.132425 | 1151.11ms | 25388 | 640 | 116660 | 10195.3 | 0.0306607 | 1.27736 | 2(Loss) | true |
| Glaze | 1773.64 | 0.660742 | 1510.01ms | 25388 | 320 | 2.60338e+06 | 13650.9 | 0.0939462 | 1.7107 | 3(Loss) | true |
| simdjson (ondemand) | 1155.04 | 0.263744 | 2270.09ms | 25388 | 160 | 489040 | 20961.9 | 0.320053 | 2.62872 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14883.5 | 0.336915 | 205.291ms | 31235 | 1280 | 58199.7 | 2001.41 | 0.116968 | 0.201936 | 1(Win) | true |
| Glaze | 5287.42 | 0.122807 | 587.298ms | 31235 | 160 | 7658.81 | 5633.75 | 0.177187 | 0.571173 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16379.7 | 0.1244 | 188.591ms | 31235 | 4890 | 25027.7 | 1818.59 | 0.0964875 | 0.182096 | 1(Win) | true |
| Glaze | 5663.12 | 0.310455 | 531.759ms | 31235 | 30 | 8000 | 5260 | 0.25413 | 0.531587 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2115.62 | 0.218593 | 5084.53ms | 108313 | 80 | 911266 | 48825 | 0.867976 | 1.43588 | 1(Win) | true |
| Jsonifier (two-stage) | 1424.62 | 0.569466 | 7300.35ms | 108313 | 4890 | 8.33696e+08 | 72507.3 | 0.314013 | 2.13274 | 2(Loss) | true |
| Glaze | 1400.76 | 0.241521 | 7562.55ms | 108313 | 80 | 2.53766e+06 | 73742.5 | 0.521401 | 2.1692 | 3(Loss) | true |
| simdjson (ondemand) | 741.499 | 0.0460318 | 7130.66ms | 108313 | 1280 | 5.26338e+06 | 139306 | 0.0682979 | 4.09823 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2580.35 | 0.994598 | 4248.33ms | 108313 | 2560 | 4.05826e+08 | 40031.5 | 0.219947 | 1.17707 | 1(Win) | true |
| Glaze | 1784.57 | 0.216674 | 6349.52ms | 108313 | 40 | 629173 | 57882.5 | 0.131184 | 1.70216 | 2(Loss) | true |
| Jsonifier (two-stage) | 1769.06 | 0.231577 | 6392.85ms | 108313 | 30 | 548517 | 58390 | 0.330014 | 1.71736 | 3(Loss) | true |
| simdjson (ondemand) | 838.621 | 0.084202 | 6454.24ms | 108313 | 320 | 3.44211e+06 | 123173 | 0.0398481 | 3.62355 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13727 | 0.140751 | 783.895ms | 108313 | 40 | 4487.18 | 7525 | 0.871314 | 0.220457 | 1(Win) | true |
| Glaze | 3947.47 | 0.454554 | 2800.25ms | 108313 | 80 | 1.13184e+06 | 26167.5 | 1.58894 | 0.769331 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14366.5 | 0.119933 | 765.024ms | 108313 | 40 | 2974.36 | 7190 | 0.599078 | 0.210771 | 1(Win) | true |
| Glaze | 4299.8 | 0.879267 | 2406.06ms | 108313 | 4890 | 2.1818e+08 | 24023.3 | 0.014195 | 0.705672 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2276.61 | 0.352349 | 7935.47ms | 183677 | 40 | 2.93994e+06 | 76942.5 | 0.0943151 | 1.33469 | 1(Win) | true |
| Jsonifier | 2110.99 | 0.519232 | 8328.98ms | 183677 | 4890 | 9.07752e+08 | 82978.9 | 0.341173 | 1.43932 | 2(Loss) | true |
| Glaze | 1795.49 | 0.128128 | 5212.35ms | 183677 | 80 | 1.25003e+06 | 97560 | 0.0333239 | 1.69237 | 3(Loss) | true |
| simdjson (ondemand) | 1186.35 | 0.103609 | 7627.18ms | 183677 | 2560 | 5.99134e+07 | 147653 | 0.00029101 | 2.56153 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2679.84 | 0.12593 | 7012.47ms | 183677 | 80 | 542051 | 65365 | 0.015301 | 1.13367 | 1(Win) | true |
| Jsonifier | 2544.11 | 0.24596 | 7425.84ms | 183677 | 40 | 1.14717e+06 | 68852.5 | 0.112433 | 1.19421 | 2(Loss) | true |
| Glaze | 2017.77 | 0.630943 | 8962.9ms | 183677 | 2560 | 7.68049e+08 | 86812.9 | 0.081825 | 1.5058 | 3(Loss) | true |
| simdjson (ondemand) | 1328.55 | 0.14101 | 6920.99ms | 183677 | 80 | 2.76531e+06 | 131849 | 0.161855 | 2.28729 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15552.7 | 0.142332 | 1395.91ms | 213963 | 40 | 13948.7 | 13120 | 0.152207 | 0.195187 | 1(Win) | true |
| Glaze | 3808.43 | 0.398993 | 5407.01ms | 213963 | 1280 | 5.84961e+07 | 53578.8 | 0.520167 | 0.797712 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15526.8 | 0.455032 | 1359.61ms | 213963 | 320 | 1.14432e+06 | 13141.9 | 0.0665368 | 0.195016 | 1(Win) | true |
| Glaze | 4278.87 | 0.63109 | 4752.21ms | 213963 | 4890 | 4.42905e+08 | 47688.1 | 0.172663 | 0.709697 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 582.846 | 0.110543 | 9414.66ms | 1834197 | 30 | 3.30192e+08 | 3.00118e+06 | 0.263422 | 5.21435 | 1(Win) | true |
| Jsonifier (two-stage) | 516.418 | 0.137975 | 5268.36ms | 1834197 | 40 | 8.73681e+08 | 3.38723e+06 | 0.592554 | 5.88512 | 2(Loss) | true |
| Glaze | 303.463 | 0.736833 | 8487.27ms | 1834197 | 80 | 1.44314e+11 | 5.76422e+06 | 1.62839 | 10.0151 | 3(Loss) | true |
| simdjson (ondemand) | 194.102 | 0.80864 | 6277.84ms | 1834197 | 30 | 1.59318e+11 | 9.0119e+06 | 0.456436 | 15.6586 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 637.03 | 0.102758 | 9778.71ms | 1834197 | 30 | 2.38851e+08 | 2.74591e+06 | 0.238694 | 4.77081 | 1(Win) | true |
| Jsonifier (two-stage) | 559.016 | 0.598822 | 5209.62ms | 1834197 | 30 | 1.05332e+10 | 3.12912e+06 | 2.04705 | 5.4366 | 2(Loss) | true |
| Glaze | 324.994 | 0.797279 | 8503.69ms | 1834197 | 40 | 7.36583e+10 | 5.38233e+06 | 1.38165 | 9.35176 | 3(Loss) | true |
| simdjson (ondemand) | 201.36 | 0.80739 | 6369.55ms | 1834197 | 30 | 1.47582e+11 | 8.68707e+06 | 1.50919 | 15.0941 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 878.85 | 0.575137 | 6187.98ms | 1834197 | 160 | 2.09664e+10 | 1.99036e+06 | 0.386374 | 3.45791 | 1(Win) | true |
| Glaze | 686.302 | 0.965706 | 7924.44ms | 1833577 | 40 | 2.42169e+10 | 2.54791e+06 | 0.0239355 | 4.42821 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 1037.02 | 0.150683 | 5320.12ms | 1834197 | 30 | 1.93806e+08 | 1.68678e+06 | 2.63446 | 2.93043 | -(Win) | false |
| Glaze | 749.698 | 1.04672 | 7083.5ms | 1833577 | 80 | 4.76848e+10 | 2.33245e+06 | 1.2747 | 4.05387 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1882.78 | 0.134568 | 5633.42ms | 7351818 | 30 | 7.53344e+08 | 3.72388e+06 | 0.218291 | 1.61421 | 1(Win) | true |
| Jsonifier | 1733.88 | 0.843136 | 5961.9ms | 7351818 | 40 | 4.64951e+10 | 4.04367e+06 | 0.0163191 | 1.75285 | 2(Loss) | true |
| Glaze | 1089.47 | 1.17854 | 9549.66ms | 7351818 | 40 | 2.30097e+11 | 6.43548e+06 | 0.122194 | 2.78957 | 3(Loss) | true |
| simdjson (ondemand) | 674.914 | 0.466013 | 7152.22ms | 7351818 | 40 | 9.3745e+10 | 1.03883e+07 | 1.98987 | 4.50321 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2013.54 | 0.217695 | 5651.23ms | 7351818 | 80 | 4.59681e+09 | 3.48205e+06 | 0.409532 | 1.50938 | 1(Win) | true |
| Jsonifier | 1935.08 | 0.107725 | 5877.03ms | 7351818 | 40 | 6.09378e+08 | 3.62322e+06 | 0.576459 | 1.57062 | 2(Loss) | true |
| Glaze | 1157.42 | 0.816929 | 9489.01ms | 7351818 | 40 | 9.79576e+10 | 6.05766e+06 | 1.20762 | 2.62581 | 3(Loss) | true |
| simdjson (ondemand) | 712.143 | 0.113425 | 7111.94ms | 7351818 | 30 | 3.74108e+09 | 9.84527e+06 | 0.124478 | 4.26801 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2502.15 | 0.058743 | 5684.95ms | 9930848 | 80 | 3.955e+08 | 3.78506e+06 | 0.0383232 | 1.21466 | 1(Win) | true |
| Glaze | 1907.14 | 0.0680756 | 7451.74ms | 9930228 | 80 | 9.14171e+08 | 4.96566e+06 | 0.0136959 | 1.59365 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3662.41 | 0.0769032 | 8131.27ms | 9930848 | 30 | 1.18645e+08 | 2.58594e+06 | 0.0749647 | 0.829793 | 1(Win) | true |
| Glaze | 3582.72 | 0.16453 | 8201.07ms | 9930228 | 40 | 7.56557e+08 | 2.6433e+06 | 0.0897411 | 0.848257 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 566.995 | 0.883282 | 9603.28ms | 1834197 | 40 | 2.97025e+10 | 3.08508e+06 | 0.93489 | 5.3601 | 1(Win) | true |
| Jsonifier (two-stage) | 488.812 | 0.950267 | 5341.46ms | 1834197 | 80 | 9.251e+10 | 3.57852e+06 | 1.38792 | 6.21688 | 2(Loss) | true |
| simdjson (ondemand) | 343.133 | 0.771924 | 7614.87ms | 1834197 | 30 | 4.64556e+10 | 5.09781e+06 | 0.169914 | 8.8564 | 3(Loss) | true |
| Glaze | 318.298 | 0.592938 | 8304.22ms | 1834197 | 80 | 8.49442e+10 | 5.49557e+06 | 1.05028 | 9.54865 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 645.586 | 0.107261 | 9571.81ms | 1834197 | 30 | 2.53391e+08 | 2.70952e+06 | 1.14789 | 4.70756 | 1(Win) | true |
| Jsonifier (two-stage) | 540.735 | 0.22332 | 5349.02ms | 1834197 | 80 | 4.1751e+09 | 3.2349e+06 | 0.0527944 | 5.61897 | 2(Loss) | true |
| simdjson (ondemand) | 356.652 | 0.907943 | 7708.32ms | 1834197 | 30 | 5.94894e+10 | 4.90457e+06 | 1.32237 | 8.52108 | 3(Loss) | true |
| Glaze | 335.43 | 0.672829 | 8333.08ms | 1834197 | 80 | 9.84891e+10 | 5.21488e+06 | 1.01739 | 9.061 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 868.133 | 0.304093 | 6204.93ms | 1834197 | 80 | 3.00346e+09 | 2.01493e+06 | 0.272775 | 3.49997 | 1(Win) | true |
| Glaze | 623.725 | 0.0842464 | 8960.21ms | 1833577 | 160 | 8.92554e+08 | 2.80353e+06 | 0.672443 | 4.87229 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1023.96 | 0.083044 | 5433.24ms | 1834197 | 80 | 1.61004e+08 | 1.7083e+06 | 0.0281792 | 2.96788 | 1(Win) | true |
| Glaze | 795.124 | 0.222479 | 6897.24ms | 1833577 | 40 | 9.57561e+08 | 2.1992e+06 | 0.488651 | 3.8216 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1748.7 | 1.21923 | 6040.49ms | 7351818 | 30 | 7.16884e+10 | 4.0094e+06 | 0.133698 | 1.73774 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE DID NOT CONVERGE | 1713.42 | 0.54838 | 6007.59ms | 7351818 | 80 | 4.02823e+10 | 4.09195e+06 | 3.16868 | 1.77353 | -(Tie) | false |
| simdjson (ondemand) | 1161.51 | 1.1664 | 8750.06ms | 7351818 | 30 | 1.48716e+11 | 6.03631e+06 | 1.65945 | 2.61647 | 3(Loss) | true |
| Glaze | 1058.68 | 1.0124 | 9869.3ms | 7351818 | 30 | 1.34862e+11 | 6.62264e+06 | 0.718589 | 2.87067 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1965.2 | 0.895901 | 5959.05ms | 7351818 | 40 | 4.08653e+10 | 3.5677e+06 | 1.74472 | 1.54647 | 1(Win) | true |
| Jsonifier | 1851.47 | 0.943923 | 6142.55ms | 7351818 | 80 | 1.02216e+11 | 3.78684e+06 | 0.0132384 | 1.64145 | 2(Loss) | true |
| simdjson (ondemand) | 1314.9 | 0.788052 | 8620.93ms | 7351818 | 30 | 5.29703e+10 | 5.33213e+06 | 0.904881 | 2.31136 | 3(Loss) | true |
| Glaze | 1170.46 | 0.558787 | 9712.4ms | 7351818 | 80 | 8.96316e+10 | 5.99017e+06 | 1.4901 | 2.59652 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2587.91 | 1.35832 | 5376.51ms | 9930848 | 30 | 7.41307e+10 | 3.65963e+06 | 0.050708 | 1.17436 | 1(Win) | true |
| Glaze | 1229.66 | 0.931648 | 5383.94ms | 9930228 | 30 | 1.54445e+11 | 7.70148e+06 | 0.450418 | 2.47158 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3987.58 | 0.746245 | 7259.12ms | 9930848 | 160 | 5.02617e+10 | 2.37507e+06 | 0.220848 | 0.762035 | 1(Win) | true |
| Glaze | 3367.64 | 0.771576 | 8615.85ms | 9930228 | 160 | 7.53259e+10 | 2.81212e+06 | 0.300787 | 0.902347 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 819.858 | 0.184223 | 7013.12ms | 461466 | 320 | 3.12926e+08 | 536786 | 0.0439344 | 3.70677 | 1(Win) | true |
| Glaze | 770.905 | 0.202502 | 7482.99ms | 461466 | 40 | 5.34559e+07 | 570872 | 0.64583 | 3.94233 | 2(Loss) | true |
| Jsonifier (two-stage) | 715.956 | 0.610529 | 7769.94ms | 461466 | 320 | 4.50681e+09 | 614686 | 0.203348 | 4.24434 | 3(Loss) | true |
| simdjson (ondemand) | 561.217 | 0.275821 | 5142.45ms | 461466 | 80 | 3.74252e+08 | 784168 | 0.493619 | 5.41496 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1087.78 | 0.260358 | 6348.42ms | 461466 | 320 | 3.55048e+08 | 404573 | 0.538397 | 2.79395 | 1(Win) | true |
| Glaze STATISTICAL TIE | 937.51 | 2.14964 | 6886.97ms | 461466 | 40 | 4.07305e+09 | 469422 | 1.44631 | 3.24153 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 931.743 | 0.795669 | 7012.43ms | 461466 | 320 | 4.51963e+09 | 472328 | 0.17484 | 3.26153 | 2(Tie) | true |
| simdjson (ondemand) | 643.91 | 0.778664 | 9807.15ms | 461466 | 160 | 4.53158e+09 | 683462 | 0.101975 | 4.71969 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3806.58 | 0.0864895 | 6288.04ms | 461466 | 2560 | 2.55963e+07 | 115613 | 0.59989 | 0.797521 | 1(Win) | true |
| Glaze | 2967.51 | 1.2854 | 7535.42ms | 461466 | 640 | 2.3257e+09 | 148302 | 0.35431 | 1.02389 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10769 | 0.753262 | 4359.4ms | 461466 | 80 | 7.58075e+06 | 40866.2 | 0.502161 | 0.281911 | 1(Win) | true |
| Glaze | 3233.38 | 0.927991 | 7144.87ms | 461466 | 640 | 1.02102e+09 | 136108 | 0.00642914 | 0.939694 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 1047.61 | 0.139997 | 8936.35ms | 728486 | 640 | 5.51651e+08 | 663167 | 2.79177 | 2.901 | -(Win) | false |
| Jsonifier (two-stage) | 1025.17 | 1.02468 | 8261.22ms | 728486 | 160 | 7.71512e+09 | 677678 | 1.81042 | 2.96347 | 2(Loss) | true |
| Glaze | 929.65 | 0.857967 | 9040.7ms | 728486 | 640 | 2.63102e+10 | 747312 | 0.711772 | 3.26842 | 3(Loss) | true |
| simdjson (ondemand) | 827.889 | 0.220748 | 5524ms | 728486 | 320 | 1.0981e+09 | 839168 | 0.0535042 | 3.67094 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1456.28 | 0.0564598 | 7566.34ms | 728486 | 640 | 4.64317e+07 | 477065 | 0.112139 | 2.0869 | 1(Win) | true |
| Jsonifier | 1324.23 | 0.137431 | 8118.22ms | 728486 | 80 | 4.15889e+07 | 524636 | 0.325327 | 2.29515 | 2(Loss) | true |
| Glaze | 1228.86 | 2.56166 | 8137.98ms | 728486 | 30 | 6.29224e+09 | 565353 | 0.889972 | 2.47307 | 3(Loss) | true |
| simdjson (ondemand) | 980.053 | 0.296306 | 5248.08ms | 728486 | 320 | 1.4118e+09 | 708878 | 1.06234 | 3.10096 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4088.06 | 0.800917 | 5260.29ms | 837491 | 40 | 9.79405e+07 | 195372 | 0.259579 | 0.742852 | 1(Win) | true |
| Glaze | 2119.96 | 0.353769 | 5000.21ms | 837491 | 80 | 1.42114e+08 | 376750 | 0.543079 | 1.43273 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12541.8 | 0.2098 | 6675.81ms | 837491 | 80 | 1.42804e+06 | 63682.5 | 0.00392588 | 0.242139 | 1(Win) | true |
| Glaze | 4392.21 | 0.298536 | 9941.71ms | 837491 | 30 | 8.84116e+06 | 181843 | 1.32048 | 0.691779 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 6420.9 | 0.441804 | 7164.48ms | 466906 | 640 | 6.00769e+07 | 69348 | 0.447488 | 0.473135 | 1(Win) | true |
| Jsonifier DID NOT CONVERGE | 6272.41 | 0.331878 | 7285.99ms | 466906 | 4890 | 2.7143e+08 | 70989.7 | 2.77322 | 0.484358 | -(Loss) | false |
| simdjson (ondemand) | 3740.13 | 0.158513 | 6385.69ms | 466906 | 80 | 2.8491e+06 | 119054 | 0.207268 | 0.812459 | 3(Loss) | true |
| Glaze | 2905.27 | 0.356921 | 8388.18ms | 466906 | 320 | 9.57589e+07 | 153265 | 0.663529 | 1.04598 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 6701.3 | 0.0701506 | 7086.88ms | 466906 | 1280 | 2.78108e+06 | 66446.2 | 0.0272851 | 0.453374 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 6697.16 | 0.0812328 | 7071.53ms | 466906 | 640 | 1.8669e+06 | 66487.3 | 0.147096 | 0.453652 | 1(Tie) | true |
| simdjson (ondemand) | 3830.98 | 0.175979 | 6202.44ms | 466906 | 1280 | 5.35517e+07 | 116230 | 0.663217 | 0.793166 | 3(Loss) | true |
| Glaze | 2729.58 | 1.53654 | 8104.19ms | 466906 | 320 | 2.01052e+09 | 163130 | 0.0479142 | 1.11319 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 7363.35 | 0.0652738 | 8410.55ms | 631514 | 4890 | 1.3938e+07 | 81791.3 | 0.529521 | 0.412647 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 7334.78 | 0.441642 | 8567.69ms | 631514 | 30 | 3.94507e+06 | 82110 | 0.781407 | 0.414224 | 1(Tie) | true |
| simdjson (ondemand) | 4034.06 | 0.525766 | 7499ms | 631514 | 2560 | 1.57727e+09 | 149293 | 0.646554 | 0.753259 | 3(Loss) | true |
| Glaze | 3482.54 | 0.290416 | 9235.23ms | 631514 | 30 | 7.56723e+06 | 172937 | 0.634286 | 0.872648 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7650.89 | 0.156043 | 8616.88ms | 631514 | 80 | 1.20703e+06 | 78717.5 | 0.0571338 | 0.397113 | 1(Win) | true |
| Jsonifier (two-stage) | 7425.44 | 0.833186 | 8567.39ms | 631514 | 80 | 3.65339e+07 | 81107.5 | 0.312287 | 0.409176 | 2(Loss) | true |
| simdjson (ondemand) | 4202.43 | 1.06695 | 7239.83ms | 631514 | 640 | 1.49635e+09 | 143312 | 0.184461 | 0.723078 | 3(Loss) | true |
| Glaze | 3275.56 | 0.714552 | 9083.79ms | 631514 | 1280 | 2.20939e+09 | 183864 | 0.761493 | 0.927685 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1222.23 | 0.548087 | 9285.12ms | 466906 | 40 | 1.59482e+08 | 364315 | 0.0306417 | 2.48656 | 1(Win) | true |
| Jsonifier (two-stage) | 1121.82 | 0.430291 | 5172.88ms | 466906 | 30 | 8.75101e+07 | 396923 | 0.312537 | 2.70885 | 2(Loss) | true |
| Glaze | 1069.8 | 0.798678 | 5078.4ms | 466906 | 640 | 7.07253e+09 | 416222 | 0.739791 | 2.84033 | 3(Loss) | true |
| simdjson (ondemand) | 855.392 | 0.292297 | 6720.59ms | 466906 | 640 | 1.48169e+09 | 520552 | 0.627803 | 3.5527 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1892.27 | 0.387038 | 6915.8ms | 466906 | 1280 | 1.06173e+09 | 235314 | 0.319108 | 1.60601 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1568.26 | 0.201751 | 8383.38ms | 466906 | 160 | 5.25013e+07 | 283929 | 0.0222376 | 1.93782 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1556.53 | 1.66318 | 8148.71ms | 466906 | 160 | 3.62199e+09 | 286071 | 0.14287 | 1.95232 | 2(Tie) | true |
| simdjson (ondemand) | 1100.59 | 0.422119 | 5703.27ms | 466906 | 160 | 4.6666e+08 | 404581 | 0.284278 | 2.76141 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 4518.53 | 0.460214 | 5076.7ms | 475954 | 2560 | 5.47136e+08 | 100454 | 1.70133 | 0.672328 | 1(Win) | true |
| Jsonifier | 3994.95 | 0.146625 | 6003.29ms | 475954 | 2560 | 7.10496e+07 | 113620 | 0.384327 | 0.759957 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16026.9 | 0.0496164 | 2863.78ms | 475954 | 2560 | 505499 | 28321.4 | 0.103689 | 0.189379 | 1(Win) | true |
| Glaze | 5124.18 | 0.29812 | 9080.42ms | 475954 | 4890 | 3.41014e+08 | 88581 | 0.0994875 | 0.592893 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1403.38 | 0.218421 | 5739.28ms | 631514 | 40 | 3.51451e+07 | 429150 | 0.31166 | 2.16539 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1389.47 | 0.702571 | 5475.45ms | 631514 | 320 | 2.96756e+09 | 433445 | 0.802151 | 2.18696 | 1(Tie) | true |
| Glaze STATISTICAL TIE | 1376.59 | 1.75206 | 5670.81ms | 631514 | 40 | 2.35026e+09 | 437500 | 0.485253 | 2.2075 | 1(Tie) | true |
| simdjson (ondemand) | 1095.86 | 0.290319 | 7054.94ms | 631514 | 640 | 1.62924e+09 | 549575 | 0.538152 | 2.77321 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1975.31 | 0.175996 | 9058.97ms | 631514 | 160 | 4.60704e+07 | 304894 | 0.218174 | 1.53851 | 1(Win) | true |
| Glaze | 1895.29 | 0.105708 | 9399.15ms | 631514 | 320 | 3.6106e+07 | 317766 | 0.78539 | 1.60352 | 2(Loss) | true |
| Jsonifier | 1876.74 | 0.227367 | 9544.83ms | 631514 | 30 | 1.5971e+07 | 320907 | 0.906817 | 1.61929 | 3(Loss) | true |
| simdjson (ondemand) | 1381.26 | 0.0952225 | 6008.99ms | 631514 | 640 | 1.10325e+08 | 436020 | 0.0447027 | 2.20027 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4207.48 | 0.825935 | 8155.07ms | 716365 | 320 | 5.75528e+08 | 162372 | 0.629818 | 0.721654 | 1(Win) | true |
| Glaze | 1698.93 | 0.532878 | 5107.3ms | 716365 | 320 | 1.46934e+09 | 402122 | 0.426757 | 1.78784 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14604.1 | 0.0739861 | 4740.1ms | 716365 | 640 | 766651 | 46779.8 | 0.0557488 | 0.20801 | 1(Win) | true |
| Glaze | 3300.33 | 0.433449 | 5420.7ms | 716365 | 320 | 2.57621e+08 | 207003 | 0.149526 | 0.920832 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1143.38 | 0.111492 | 221.56ms | 2632 | 4890 | 29294.9 | 2195.32 | 0.565662 | 2.63622 | 1(Win) | true |
| Jsonifier (two-stage) | 925.164 | 0.287012 | 276.351ms | 2632 | 4890 | 296513 | 2713.11 | 0.173902 | 3.26257 | 2(Loss) | true |
| Glaze | 837.65 | 0.180496 | 292.274ms | 2632 | 320 | 9361.19 | 2996.56 | 0.425753 | 3.60345 | 3(Loss) | true |
| simdjson (ondemand) | 732.133 | 0.272828 | 358.636ms | 2632 | 320 | 27997.6 | 3428.44 | 0.191048 | 4.12921 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1582.39 | 0.268771 | 187.673ms | 2632 | 80 | 1454.11 | 1586.25 | 0.0788644 | 1.9067 | 1(Tie) | true |
| Glaze STATISTICAL TIE | 1576.8 | 0.2226 | 197.474ms | 2632 | 160 | 2009.04 | 1591.88 | 2.04327 | 1.89818 | 1(Tie) | true |
| Jsonifier (two-stage) | 1214.55 | 0.482943 | 244.309ms | 2632 | 30 | 2988.51 | 2066.67 | 0.161031 | 2.46594 | 3(Loss) | true |
| simdjson (ondemand) | 990.166 | 0.233798 | 306.051ms | 2632 | 80 | 2810.13 | 2535 | 0.197628 | 3.05227 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9654.12 | 1.05496 | 28.4681ms | 2632 | 320 | 2407.52 | 260 | 0 | 0.292366 | 1(Win) | true |
| Glaze | 3575.44 | 0.148981 | 74.1465ms | 2632 | 640 | 700.093 | 702.031 | 0.0222519 | 0.83091 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10880.1 | 0.559061 | 26.2745ms | 2632 | 1280 | 2129.29 | 230.703 | 0.0338524 | 0.254192 | 1(Win) | true |
| Glaze | 4011.32 | 0.191554 | 64.4708ms | 2632 | 4890 | 7025.68 | 625.746 | 0.242195 | 0.729425 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1235.18 | 0.105099 | 261.495ms | 3370 | 2560 | 19144.3 | 2601.95 | 0.204591 | 2.44186 | 1(Win) | true |
| Jsonifier (two-stage) | 1159.2 | 0.239862 | 288.885ms | 3370 | 80 | 3537.97 | 2772.5 | 0.359389 | 2.60197 | 2(Loss) | true |
| Glaze | 1048.49 | 0.154092 | 310.821ms | 3370 | 1280 | 28555.8 | 3065.23 | 0.246619 | 2.87696 | 3(Loss) | true |
| simdjson (ondemand) | 914.496 | 0.197421 | 361.823ms | 3370 | 320 | 15404 | 3514.38 | 0.195243 | 3.31019 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1789.22 | 0.251396 | 212.566ms | 3370 | 80 | 1631.33 | 1796.25 | 0.209205 | 1.68291 | 1(Win) | true |
| Jsonifier | 1633.45 | 0.107986 | 226.02ms | 3370 | 2560 | 11556.3 | 1967.54 | 0.338346 | 1.84196 | 2(Loss) | true |
| Jsonifier (two-stage) | 1475.95 | 0.348335 | 258.234ms | 3370 | 40 | 2301.28 | 2177.5 | 0.345622 | 2.03959 | 3(Loss) | true |
| simdjson (ondemand) | 1227.44 | 0.0838038 | 302.984ms | 3370 | 4890 | 23544.9 | 2618.36 | 0.220134 | 2.45531 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10598.2 | 0.444111 | 34.7793ms | 3643 | 1280 | 2712.96 | 327.812 | 0.285171 | 0.269616 | 1(Win) | true |
| Glaze | 4103.93 | 0.216689 | 89.0705ms | 3682 | 2560 | 8799.92 | 855.625 | 0.560095 | 0.724599 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11986.6 | 0.412284 | 31.0748ms | 3643 | 640 | 913.904 | 289.844 | 0.0539374 | 0.236764 | 1(Win) | true |
| Glaze | 4584.89 | 1.04564 | 81.9758ms | 3682 | 4890 | 313605 | 765.869 | 0.0700842 | 0.642364 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 623.509 | 0.20474 | 723.01ms | 4630 | 2560 | 538173 | 7081.72 | 0.025367 | 4.86195 | 1(Win) | true |
| Jsonifier (two-stage) | 591.842 | 0.212629 | 752.699ms | 4630 | 160 | 40263.8 | 7460.62 | 0.142617 | 5.12583 | 2(Loss) | true |
| simdjson (ondemand) | 344.396 | 0.149493 | 1311.03ms | 4630 | 1280 | 470215 | 12821 | 0.162962 | 8.81052 | 3(Loss) | true |
| Glaze | 342.188 | 0.151152 | 1330.85ms | 4630 | 160 | 60866.4 | 12903.8 | 0.11611 | 8.87007 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 787.386 | 0.271544 | 702.25ms | 4630 | 320 | 74202.1 | 5607.81 | 0.061336 | 3.84642 | 1(Win) | true |
| Jsonifier (two-stage) | 737.725 | 0.0959945 | 726.235ms | 4630 | 1280 | 42254.8 | 5985.31 | 0.0208801 | 4.10579 | 2(Loss) | true |
| Glaze | 386.604 | 0.0488551 | 1275.89ms | 4630 | 4890 | 152251 | 11421.3 | 0.318091 | 7.8446 | 3(Loss) | true |
| simdjson (ondemand) | 383.293 | 0.0456755 | 1313.59ms | 4630 | 4890 | 135387 | 11519.9 | 0.189715 | 7.9152 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1824.39 | 0.118438 | 251.414ms | 4630 | 4890 | 40180.3 | 2420.27 | 0.367404 | 1.65362 | 1(Win) | true |
| Glaze | 1210.61 | 0.209926 | 368.863ms | 4630 | 640 | 37520.3 | 3647.34 | 0.0471011 | 2.4969 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1874.52 | 0.143712 | 238.375ms | 4630 | 1280 | 14668.2 | 2355.55 | 0.196065 | 1.60212 | 1(Win) | true |
| Glaze | 1343.46 | 0.192062 | 346.188ms | 4630 | 30 | 1195.4 | 3286.67 | 0.101523 | 2.23692 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1380.53 | 0.0757502 | 807.2ms | 11579 | 2560 | 93984.5 | 7998.79 | 0.510975 | 2.19578 | 1(Win) | true |
| Jsonifier | 1304.89 | 0.167583 | 877.827ms | 11579 | 40 | 8044.87 | 8462.5 | 0.0295508 | 2.32549 | 2(Loss) | true |
| Glaze | 787.632 | 0.232952 | 1469.27ms | 11579 | 30 | 32000 | 14020 | 1.15159 | 3.8535 | 3(Loss) | true |
| simdjson (ondemand) | 749.872 | 1.74692 | 1453.07ms | 11579 | 2560 | 1.69415e+08 | 14726 | 1.7388 | 4.04702 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1720.92 | 0.2252 | 819.08ms | 11579 | 30 | 6264.37 | 6416.67 | 0.0519211 | 1.76178 | 1(Win) | true |
| Jsonifier | 1549.8 | 0.211673 | 847.785ms | 11579 | 640 | 145579 | 7125.16 | 0.037266 | 1.9553 | 2(Loss) | true |
| simdjson (ondemand) | 887.142 | 0.0445141 | 1394.95ms | 11579 | 4890 | 150127 | 12447.4 | 0.035766 | 3.42038 | 3(Loss) | true |
| Glaze | 866.415 | 0.0435267 | 1413.94ms | 11579 | 4890 | 150491 | 12745.2 | 0.058858 | 3.50087 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4432.63 | 0.150918 | 320.478ms | 14795 | 640 | 14769.6 | 3183.12 | 0.0392542 | 0.681558 | 1(Win) | true |
| Glaze | 3106.13 | 0.150531 | 478.378ms | 14795 | 80 | 3740.51 | 4542.5 | 0.0550055 | 0.974507 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4934.98 | 0.0968667 | 291.577ms | 14795 | 2560 | 19635.8 | 2859.1 | 0.291861 | 0.607777 | 1(Win) | true |
| Glaze | 3396.52 | 0.0767748 | 418.214ms | 14795 | 2560 | 26039.9 | 4154.14 | 0.413566 | 0.88941 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 793.552 | 0.369979 | 395.383ms | 3223 | 30 | 6160.92 | 3873.33 | 0.0859845 | 3.8047 | 1(Win) | true |
| Jsonifier (two-stage) | 684.773 | 0.0987688 | 449.506ms | 3223 | 2560 | 50316.2 | 4488.63 | 0.183961 | 4.41577 | 2(Loss) | true |
| Glaze | 639.27 | 0.413573 | 510.212ms | 3223 | 160 | 63266.9 | 4808.12 | 0.401346 | 4.73644 | 3(Loss) | true |
| simdjson (ondemand) | 494.991 | 0.0700727 | 622.364ms | 3223 | 4890 | 92583.4 | 6209.59 | 0.12063 | 6.11717 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1131.07 | 0.414311 | 345.354ms | 3223 | 40 | 5070.51 | 2717.5 | 0.648148 | 2.67063 | 1(Win) | true |
| Jsonifier (two-stage) | 893.09 | 0.0810458 | 413.702ms | 3223 | 4890 | 38045.2 | 3441.64 | 0.365531 | 3.38241 | 2(Loss) | true |
| Glaze | 830.728 | 0.237043 | 450.885ms | 3223 | 40 | 3076.92 | 3700 | 0.090009 | 3.63277 | 3(Loss) | true |
| simdjson (ondemand) | 572.004 | 0.0960408 | 606.133ms | 3223 | 2560 | 68182.7 | 5373.55 | 0.196613 | 5.29352 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6188.64 | 0.671141 | 48.1692ms | 3223 | 30 | 333.333 | 496.667 | 0 | 0.472531 | 1(Win) | true |
| Glaze | 3222.48 | 0.307693 | 97.4912ms | 3223 | 1280 | 11025.2 | 953.828 | 0.836582 | 0.921536 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8147.42 | 0.196448 | 40.2454ms | 3223 | 4890 | 2685.88 | 377.26 | 0.320439 | 0.356507 | 1(Win) | true |
| Glaze | 4122.3 | 0.376408 | 78.4753ms | 3223 | 1280 | 10082.5 | 745.625 | 0.313349 | 0.713727 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1199.8 | 0.088515 | 478.504ms | 5839 | 2560 | 43205.3 | 4641.21 | 0.194799 | 2.52165 | 1(Win) | true |
| Jsonifier | 1142.87 | 0.0976166 | 491.528ms | 5839 | 2560 | 57912.3 | 4872.38 | 0.084109 | 2.64782 | 2(Loss) | true |
| Glaze | 971.604 | 0.157027 | 569.949ms | 5839 | 80 | 6479.43 | 5731.25 | 0.0654736 | 3.11128 | 3(Loss) | true |
| simdjson (ondemand) | 867.601 | 0.130331 | 666.986ms | 5839 | 640 | 44782.6 | 6418.28 | 0.0559611 | 3.49189 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1530.68 | 0.0802989 | 439.542ms | 5839 | 4890 | 41729 | 3637.93 | 0.110853 | 1.97332 | 1(Win) | true |
| Jsonifier | 1442.62 | 0.293942 | 458.202ms | 5839 | 30 | 3862.07 | 3860 | 0.344234 | 2.09827 | 2(Loss) | true |
| Glaze | 1223.76 | 0.201714 | 534.953ms | 5839 | 320 | 26959.1 | 4550.31 | 0.213352 | 2.47388 | 3(Loss) | true |
| simdjson (ondemand) | 997.94 | 0.229714 | 654.452ms | 5839 | 320 | 52576.8 | 5580 | 1.26078 | 3.0365 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8727.12 | 0.904847 | 81.2475ms | 6938 | 2560 | 120480 | 758.164 | 0.0154544 | 0.34034 | 1(Win) | true |
| Glaze | 3930.94 | 0.201186 | 173.022ms | 6960 | 4890 | 56432.5 | 1688.55 | 0.522837 | 0.762743 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9715.77 | 0.220689 | 70.0192ms | 6938 | 2560 | 5782.48 | 681.016 | 0.623341 | 0.304549 | 1(Win) | true |
| Glaze | 4939.59 | 1.14529 | 137.791ms | 6960 | 80 | 18947.8 | 1343.75 | 0.655431 | 0.603023 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1176.57 | 0.12615 | 411.261ms | 4857 | 1280 | 31571.1 | 3936.88 | 0.478545 | 2.57183 | 1(Win) | true |
| Glaze | 997.301 | 0.25177 | 470.928ms | 4857 | 640 | 87513.1 | 4644.53 | 0.224893 | 3.03209 | 2(Loss) | true |
| Jsonifier (two-stage) | 906.159 | 0.0960082 | 526.579ms | 4857 | 2560 | 61657.2 | 5111.68 | 0.367742 | 3.34012 | 3(Loss) | true |
| simdjson (ondemand) | 671.973 | 0.20865 | 717.473ms | 4857 | 160 | 33097.1 | 6893.12 | 0.0453145 | 4.50932 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1766.25 | 0.203216 | 324.773ms | 4857 | 80 | 2272.15 | 2622.5 | 0.671785 | 1.70579 | 1(Win) | true |
| Jsonifier | 1625.05 | 0.0908236 | 335.886ms | 4857 | 4890 | 32772.4 | 2850.37 | 0.133544 | 1.85803 | 2(Loss) | true |
| Jsonifier (two-stage) | 1256.42 | 0.251287 | 440.05ms | 4857 | 30 | 2574.71 | 3686.67 | 0.362976 | 2.40033 | 3(Loss) | true |
| simdjson (ondemand) | 892.095 | 0.0785552 | 570.097ms | 4857 | 2560 | 42589.6 | 5192.27 | 0.0873455 | 3.39483 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9654.71 | 0.236471 | 50.4173ms | 4857 | 2560 | 3294.98 | 479.766 | 0.389294 | 0.301528 | 1(Win) | true |
| Glaze | 3405.88 | 0.905708 | 138.449ms | 4857 | 30 | 4551.72 | 1360 | 0.729927 | 0.877709 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10850.9 | 0.410824 | 47.4609ms | 4857 | 640 | 1968.31 | 426.875 | 0 | 0.266711 | 1(Win) | true |
| Glaze | 4393.71 | 0.149237 | 116.315ms | 4857 | 4890 | 12104.2 | 1054.23 | 1.9603 | 0.675487 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1220.61 | 0.063867 | 528.949ms | 6701 | 4890 | 54674.9 | 5235.56 | 0.11745 | 2.48062 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1211.1 | 0.323603 | 560.694ms | 6701 | 30 | 8747.13 | 5276.67 | 0.314861 | 2.50526 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1195.44 | 0.850223 | 568.258ms | 6701 | 640 | 1.32211e+06 | 5345.78 | 1.0903 | 2.5311 | 2(Tie) | true |
| simdjson (ondemand) | 875.871 | 1.42191 | 738.508ms | 6701 | 160 | 1.72212e+06 | 7296.25 | 0.811744 | 3.46006 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1978.51 | 0.185954 | 374.816ms | 6701 | 80 | 2886.08 | 3230 | 0 | 1.52533 | 1(Win) | true |
| Jsonifier (two-stage) | 1631.74 | 0.176214 | 458.581ms | 6701 | 640 | 30481.6 | 3916.41 | 0.227927 | 1.85283 | 2(Loss) | true |
| Jsonifier | 1519.15 | 0.158479 | 479.04ms | 6701 | 30 | 1333.33 | 4206.67 | 0.0791766 | 1.99412 | 3(Loss) | true |
| simdjson (ondemand) | 1177.78 | 0.060079 | 599.495ms | 6701 | 4890 | 51964 | 5425.93 | 0.121685 | 2.57192 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8120.41 | 0.614148 | 85.3796ms | 7376 | 80 | 2264.24 | 866.25 | 0.726744 | 0.364851 | 1(Win) | true |
| Glaze | 2869.68 | 1.02631 | 241.495ms | 7376 | 80 | 50631.3 | 2451.25 | 1.18679 | 1.04946 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10194.6 | 0.344805 | 76.825ms | 7376 | 160 | 905.66 | 690 | 0 | 0.289162 | 1(Win) | true |
| Glaze | 3836.16 | 0.29125 | 189.037ms | 7376 | 4890 | 139473 | 1833.68 | 1.6836 | 0.777508 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze STATISTICAL TIE | 1070.35 | 0.837933 | 157.548ms | 1691 | 30 | 4781.61 | 1506.67 | 0.220751 | 2.78056 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1068.65 | 0.261013 | 160.55ms | 1691 | 320 | 4964.64 | 1509.06 | 0.103648 | 2.79943 | 1(Tie) | true |
| Jsonifier (two-stage) | 771.436 | 0.833465 | 221.951ms | 1691 | 1280 | 388572 | 2090.47 | 0.172207 | 3.9033 | 3(Loss) | true |
| simdjson (ondemand) | 610.767 | 0.092326 | 269.039ms | 1691 | 4890 | 29059.8 | 2640.39 | 0.432294 | 4.93847 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1540.45 | 0.165721 | 135.69ms | 1691 | 1280 | 3852.62 | 1046.88 | 0.238237 | 1.93419 | 1(Win) | true |
| Jsonifier | 1512.46 | 0.469578 | 143.25ms | 1691 | 160 | 4011.01 | 1066.25 | 0.352941 | 1.96565 | 2(Loss) | true |
| Jsonifier (two-stage) | 1060.16 | 0.155971 | 193.899ms | 1691 | 4890 | 27525.8 | 1521.15 | 0.43385 | 2.83017 | 3(Loss) | true |
| simdjson (ondemand) | 757.373 | 0.102575 | 244.659ms | 1691 | 4890 | 23327.2 | 2129.28 | 0.0801911 | 3.97715 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9641.89 | 0.68629 | 22.0511ms | 1996 | 4890 | 8976.79 | 197.423 | 0.557835 | 0.284692 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 4301.77 | 1.2569 | 51.8306ms | 1996 | 80 | 2474.68 | 442.5 | 2.74725 | 0.681031 | -(Loss) | false |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12134.1 | 1.76757 | 19.7129ms | 1996 | 320 | 2460.42 | 156.875 | 0 | 0.223777 | 1(Win) | true |
| Glaze | 5477.8 | 1.61681 | 42.3917ms | 1996 | 80 | 2525.32 | 347.5 | 1.41844 | 0.512976 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1215.37 | 0.561556 | 189.486ms | 2158 | 30 | 2712.64 | 1693.33 | 0 | 2.44257 | 1(Win) | true |
| Jsonifier | 1088.9 | 0.703769 | 212.151ms | 2158 | 40 | 7076.92 | 1890 | 0.531915 | 2.75492 | 2(Loss) | true |
| Jsonifier (two-stage) | 988.249 | 0.567325 | 217.204ms | 2158 | 40 | 5583.33 | 2082.5 | 0.04 | 3.04312 | 3(Loss) | true |
| simdjson (ondemand) | 743.191 | 0.471782 | 295.327ms | 2158 | 2560 | 436943 | 2769.18 | 0.281503 | 4.06107 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1644.98 | 0.277259 | 155.922ms | 2158 | 1280 | 15401.5 | 1251.09 | 0.731465 | 1.79833 | 1(Win) | true |
| Jsonifier | 1462.16 | 0.118138 | 172.167ms | 2158 | 4890 | 13520.8 | 1407.53 | 0.107391 | 2.05011 | 2(Loss) | true |
| Jsonifier (two-stage) | 1338.56 | 0.453679 | 207.187ms | 2158 | 80 | 3892.41 | 1537.5 | 0.162866 | 2.2298 | 3(Loss) | true |
| simdjson (ondemand) | 945.292 | 0.0912058 | 241.848ms | 2158 | 4890 | 19280.8 | 2177.14 | 0.386575 | 3.18717 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8888.55 | 1.37159 | 30.873ms | 2866 | 40 | 711.538 | 307.5 | 0.271739 | 0.325994 | 1(Win) | true |
| Glaze | 3674.93 | 0.787625 | 78.5465ms | 2866 | 80 | 2745.25 | 743.75 | 0.506757 | 0.807912 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12900.2 | 1.21084 | 23.7805ms | 2866 | 160 | 1053.07 | 211.875 | 0.294118 | 0.217243 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 4789.89 | 0.503869 | 65.7776ms | 2866 | 320 | 2645.38 | 570.625 | 5.3886 | 0.603064 | -(Loss) | false |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1205.27 | 0.175069 | 360.043ms | 4390 | 640 | 23667.8 | 3473.59 | 0.309417 | 2.50782 | 1(Win) | true |
| Jsonifier (two-stage) | 1084.97 | 0.305604 | 405.727ms | 4390 | 320 | 44500 | 3858.75 | 0.89884 | 2.78805 | 2(Loss) | true |
| Glaze | 939.529 | 0.0806559 | 454.968ms | 4390 | 4890 | 63167 | 4456.09 | 0.158046 | 3.22165 | 3(Loss) | true |
| simdjson (ondemand) | 527.948 | 0.210751 | 835.979ms | 4390 | 30 | 8379.31 | 7930 | 0.750939 | 5.74648 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1461.08 | 0.0983711 | 337.852ms | 4390 | 2560 | 20340.2 | 2865.43 | 0.446501 | 2.06655 | 1(Win) | true |
| Jsonifier (two-stage) | 1273.5 | 0.131438 | 406.766ms | 4390 | 160 | 2987.42 | 3287.5 | 1.46605 | 2.37741 | 2(Loss) | true |
| Glaze | 1199.94 | 0.0968622 | 411.239ms | 4390 | 2560 | 29238.6 | 3489.02 | 0.153618 | 2.51584 | 3(Loss) | true |
| simdjson (ondemand) | 588 | 0.0563917 | 775.408ms | 4390 | 4890 | 78834.1 | 7120.12 | 0.0317325 | 5.15365 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8373.26 | 0 | 48.4786ms | 4390 | 30 | 0 | 500 | 0.671141 | 0.350653 | 1(Win) | true |
| Glaze | 3431.66 | 0.52501 | 121.648ms | 4390 | 40 | 1641.03 | 1220 | 0.826446 | 0.875723 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10054.2 | 0.351823 | 44.1188ms | 4390 | 640 | 1373.61 | 416.406 | 0.18797 | 0.289259 | 1(Win) | true |
| Glaze | 4223.59 | 0.320718 | 108.912ms | 4390 | 80 | 808.544 | 991.25 | 0.376884 | 0.702947 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2160.95 | 0.105988 | 434.539ms | 9378 | 2560 | 49259 | 4138.71 | 0.752187 | 1.39908 | 1(Win) | true |
| Jsonifier | 1997.44 | 0.13162 | 474.532ms | 9378 | 80 | 2778.48 | 4477.5 | 0.610433 | 1.5133 | 2(Loss) | true |
| Glaze | 1547.58 | 0.0718384 | 583.442ms | 9378 | 4890 | 84282.2 | 5779.06 | 0.287175 | 1.95718 | 3(Loss) | true |
| simdjson (ondemand) | 1041.16 | 0.789561 | 905.586ms | 9378 | 40 | 184000 | 8590 | 0.540332 | 2.90887 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2420.86 | 0.45616 | 423.997ms | 9378 | 160 | 45439.9 | 3694.38 | 0.973693 | 1.24992 | 1(Win) | true |
| Jsonifier | 2239.62 | 0.166945 | 484.404ms | 9378 | 30 | 1333.33 | 3993.33 | 0.672269 | 1.35068 | 2(Loss) | true |
| Glaze | 1870.98 | 0.101255 | 534.651ms | 9378 | 2560 | 59973.4 | 4780.16 | 0.456426 | 1.61602 | 3(Loss) | true |
| simdjson (ondemand) | 1155.64 | 0.169193 | 864.134ms | 9378 | 320 | 54864.3 | 7739.06 | 1.57778 | 2.62308 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14030 | 0.379278 | 84.4708ms | 11521 | 160 | 1411.56 | 783.125 | 0.555556 | 0.211322 | 1(Win) | true |
| Glaze | 4765.42 | 0.211499 | 243.75ms | 11521 | 160 | 3804.64 | 2305.62 | 0.0812568 | 0.631334 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16454.6 | 1.27304 | 72.5805ms | 11521 | 2560 | 184984 | 667.734 | 0.0818331 | 0.179293 | 1(Win) | true |
| Glaze | 5405.8 | 0.478818 | 224.358ms | 11521 | 40 | 3788.46 | 2032.5 | 0.367647 | 0.548088 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2041.35 | 0.245936 | 237.252ms | 4669 | 80 | 2302.22 | 2181.25 | 0.287356 | 1.47804 | 1(Win) | true |
| Jsonifier (two-stage) | 1398.85 | 0.184712 | 343.212ms | 4669 | 640 | 22124.8 | 3183.12 | 0.206591 | 2.15848 | 2(Loss) | true |
| Glaze | 1279.51 | 0.172429 | 351.818ms | 4669 | 160 | 5761.01 | 3480 | 0.0717875 | 2.36139 | 3(Loss) | true |
| simdjson (ondemand) | 670.557 | 1.10125 | 667.656ms | 4669 | 320 | 1.71119e+06 | 6640.31 | 0.801708 | 4.51767 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2399.57 | 0.212332 | 210.973ms | 4669 | 160 | 2483.88 | 1855.62 | 0.101146 | 1.25058 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1566.3 | 0.195461 | 316.06ms | 4669 | 640 | 19760.5 | 2842.81 | 0.408389 | 1.92146 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1555.08 | 0.312522 | 333.501ms | 4669 | 30 | 2402.3 | 2863.33 | 0.350467 | 1.94326 | 2(Tie) | true |
| simdjson (ondemand) | 796.192 | 0.174019 | 599.679ms | 4669 | 40 | 3788.46 | 5592.5 | 0.900768 | 3.80574 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8995.36 | 0.705033 | 45.2626ms | 4669 | 40 | 487.179 | 495 | 0.33557 | 0.324556 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 3322.56 | 0.273981 | 141.855ms | 4669 | 4890 | 65925.5 | 1340.14 | 2.83042 | 0.90219 | -(Loss) | false |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11983.7 | 0.483966 | 42.6902ms | 4669 | 640 | 2069.54 | 371.562 | 1.57285 | 0.242713 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 3652.57 | 0.950089 | 133.235ms | 4669 | 320 | 42927 | 1219.06 | 3.31038 | 0.815488 | -(Loss) | false |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2196.87 | 0.267237 | 374.795ms | 7932 | 30 | 2540.23 | 3443.33 | 0.289575 | 1.37268 | 1(Win) | true |
| Jsonifier | 2036.22 | 0.118267 | 388.969ms | 7932 | 80 | 1544.3 | 3715 | 0.0672495 | 1.48063 | 2(Loss) | true |
| Glaze | 1620.9 | 1.49208 | 484.417ms | 7932 | 160 | 775814 | 4666.88 | 0.255102 | 1.86728 | 3(Loss) | true |
| simdjson (ondemand) | 1144.57 | 0.16866 | 690.335ms | 7932 | 320 | 39760.9 | 6609.06 | 0.394 | 2.64764 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2286.33 | 0.424789 | 357.307ms | 7932 | 2560 | 505678 | 3308.59 | 0.439617 | 1.32149 | 1(Win) | true |
| Jsonifier | 2185.1 | 0.0957362 | 367.636ms | 7932 | 2560 | 28120 | 3461.88 | 0.298778 | 1.38263 | 2(Loss) | true |
| Glaze | 1929.73 | 0.189485 | 427.4ms | 7932 | 30 | 1655.17 | 3920 | 0.684932 | 1.56707 | 3(Loss) | true |
| simdjson (ondemand) | 1272.42 | 0.158779 | 636.889ms | 7932 | 40 | 3564.1 | 5945 | 0.307434 | 2.38447 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9827.89 | 0.486572 | 88.7131ms | 9249 | 40 | 762.821 | 897.5 | 0.0929368 | 0.300297 | 1(Win) | true |
| Glaze | 3041.56 | 1.02823 | 298.563ms | 9249 | 160 | 142264 | 2900 | 0.0861326 | 0.992457 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12293.4 | 0.847992 | 75.0182ms | 9249 | 40 | 1480.77 | 717.5 | 0.116279 | 0.240226 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 2988.11 | 2.37046 | 268.26ms | 9249 | 160 | 783393 | 2951.88 | 4.27645 | 1.00414 | -(Loss) | false |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 442.045 | 0.0932601 | 1027.06ms | 4604 | 1280 | 109835 | 9932.73 | 0.560787 | 6.86124 | 1(Win) | true |
| Jsonifier (two-stage) | 413.568 | 0.765193 | 1104.23ms | 4604 | 30 | 197989 | 10616.7 | 0.441501 | 7.33385 | 2(Loss) | true |
| Glaze | 292.797 | 0.0925069 | 1579.38ms | 4604 | 640 | 123159 | 14995.8 | 0.0323112 | 10.3675 | 3(Loss) | true |
| simdjson (ondemand) | 154.365 | 0.218971 | 2929.42ms | 4604 | 80 | 310340 | 28443.8 | 0.22463 | 19.6695 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 535.671 | 0.794505 | 999.887ms | 4604 | 30 | 127230 | 8196.67 | 1.95375 | 5.64946 | 1(Win) | true |
| Jsonifier (two-stage) | 492.138 | 0.177057 | 1022.87ms | 4604 | 640 | 159700 | 8921.72 | 0.275719 | 6.16064 | 2(Loss) | true |
| Glaze | 325.118 | 0.105886 | 1520.51ms | 4604 | 40 | 8179.49 | 13505 | 0.503438 | 9.32871 | 3(Loss) | true |
| simdjson (ondemand) | 163.345 | 0.290377 | 2983.34ms | 4604 | 40 | 243692 | 26880 | 0.160951 | 18.5934 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1538.8 | 0.324677 | 302.428ms | 4604 | 30 | 2574.71 | 2853.33 | 0 | 1.97064 | 1(Win) | true |
| Glaze | 951.788 | 0.19458 | 470.266ms | 4604 | 320 | 25783.3 | 4613.12 | 0.203638 | 3.17969 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1569.51 | 0.109681 | 289.354ms | 4604 | 80 | 753.165 | 2797.5 | 0.0892857 | 1.91221 | 1(Win) | true |
| Glaze | 1024.27 | 0.290236 | 441.85ms | 4604 | 30 | 4643.68 | 4286.67 | 0.625978 | 2.9539 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1513.25 | 0.0756201 | 1183.37ms | 18245 | 2560 | 193545 | 11498.3 | 0.287209 | 2.00417 | 1(Win) | true |
| Jsonifier | 1305.04 | 0.7639 | 1381.27ms | 18245 | 320 | 3.31945e+06 | 13332.8 | 1.57366 | 2.32393 | 2(Loss) | true |
| Glaze | 986.776 | 0.253353 | 1863.13ms | 18245 | 640 | 1.27727e+06 | 17633 | 0.420901 | 3.07583 | 3(Loss) | true |
| simdjson (ondemand) | 587.186 | 0.28063 | 3125.29ms | 18245 | 40 | 276609 | 29632.5 | 0.361466 | 5.17429 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1862.27 | 0.132663 | 1137.98ms | 18245 | 30 | 4609.2 | 9343.33 | 0.358038 | 1.6297 | 1(Win) | true |
| Jsonifier | 1538.91 | 0.176969 | 1293.62ms | 18245 | 640 | 256232 | 11306.6 | 0.293832 | 1.96995 | 2(Loss) | true |
| Glaze | 1089.3 | 0.312832 | 1764.67ms | 18245 | 4890 | 1.22103e+07 | 15973.4 | 1.08957 | 2.7858 | 3(Loss) | true |
| simdjson (ondemand) | 593.313 | 0.34787 | 3110.38ms | 18245 | 2560 | 2.66437e+07 | 29326.5 | 0.255594 | 5.11826 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5070.58 | 0.264682 | 472.782ms | 24579 | 640 | 95816.8 | 4622.81 | 0.0811853 | 0.596773 | 1(Win) | true |
| Glaze | 2884.75 | 0.219874 | 831.479ms | 24579 | 640 | 204288 | 8125.62 | 0.658098 | 1.0504 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5396.34 | 0.14677 | 451.592ms | 24579 | 80 | 3251.58 | 4343.75 | 0.258324 | 0.561426 | 1(Win) | true |
| Glaze | 3387.87 | 0.197651 | 704.904ms | 24579 | 1280 | 239376 | 6918.91 | 1.07048 | 0.894185 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 489.022 | 0.179201 | 936.974ms | 4604 | 4890 | 1.26592e+06 | 8978.57 | 1.03662 | 6.19847 | 1(Win) | true |
| Jsonifier (two-stage) | 431.838 | 0.147574 | 1046.09ms | 4604 | 320 | 72043.9 | 10167.5 | 0.177947 | 7.01808 | 2(Loss) | true |
| simdjson (ondemand) | 302.232 | 0.101511 | 1504.81ms | 4604 | 640 | 139187 | 14527.7 | 0.843571 | 10.0399 | 3(Loss) | true |
| Glaze | 287.95 | 0.0948679 | 1555.36ms | 4604 | 1280 | 267847 | 15248.2 | 0.508265 | 10.539 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 611.804 | 0.185186 | 878.99ms | 4604 | 30 | 5298.85 | 7176.67 | 1.28381 | 4.95175 | 1(Win) | true |
| Jsonifier (two-stage) | 539.338 | 0.135315 | 974.699ms | 4604 | 640 | 77664.2 | 8140.94 | 0.00767784 | 5.61986 | 2(Loss) | true |
| simdjson (ondemand) | 345.466 | 0.110662 | 1441.33ms | 4604 | 1280 | 253201 | 12709.5 | 1.00286 | 8.78175 | 3(Loss) | true |
| Glaze | 302.993 | 0.0577017 | 1602.98ms | 4604 | 2560 | 178987 | 14491.1 | 0.299124 | 10.0159 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1503.83 | 0.325258 | 309.633ms | 4604 | 320 | 28858.8 | 2919.69 | 0.669785 | 2.0061 | 1(Win) | true |
| Glaze | 977.888 | 0.354845 | 469.15ms | 4604 | 40 | 10153.8 | 4490 | 0.73692 | 3.10224 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1577.5 | 0.424875 | 306.924ms | 4604 | 30 | 4195.4 | 2783.33 | 0.60241 | 1.90526 | 1(Win) | true |
| Glaze | 1074.18 | 0.179255 | 449.013ms | 4604 | 40 | 2147.44 | 4087.5 | 0.925926 | 2.82138 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1605.15 | 0.124307 | 1126.88ms | 18245 | 640 | 116207 | 10840 | 0.253048 | 1.88937 | 1(Win) | true |
| Jsonifier | 1494.84 | 0.0763234 | 1207.85ms | 18245 | 2560 | 202047 | 11639.9 | 0.248057 | 2.0288 | 2(Loss) | true |
| simdjson (ondemand) | 1067.01 | 0.304745 | 1702.99ms | 18245 | 4890 | 1.20762e+07 | 16307.1 | 2.42235 | 2.8441 | 3(Loss) | true |
| Glaze | 975.598 | 0.831233 | 1854.05ms | 18245 | 80 | 1.75825e+06 | 17835 | 0.20982 | 3.11068 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1961.64 | 1.14559 | 1064.72ms | 18245 | 30 | 309759 | 8870 | 0.930752 | 1.54454 | 1(Win) | true |
| Jsonifier | 1752.52 | 0.109259 | 1158.9ms | 18245 | 1280 | 150621 | 9928.44 | 0.105331 | 1.73001 | 2(Loss) | true |
| simdjson (ondemand) | 1198.38 | 0.13566 | 1602.27ms | 18245 | 160 | 62075.1 | 14519.4 | 1.2875 | 2.5333 | 3(Loss) | true |
| Glaze | 1103.62 | 0.10128 | 1781.44ms | 18245 | 640 | 163183 | 15766.1 | 0.400995 | 2.74961 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5033.72 | 1.48739 | 493.738ms | 24579 | 30 | 143920 | 4656.67 | 0.143369 | 0.600715 | 1(Win) | true |
| Glaze | 2822.65 | 0.637361 | 843.016ms | 24579 | 640 | 1.79294e+06 | 8304.38 | 0.842441 | 1.07432 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5303.25 | 0.166018 | 461.463ms | 24579 | 40 | 2153.85 | 4420 | 0.151057 | 0.569342 | 1(Win) | true |
| Glaze | 3228.7 | 2.1005 | 739.299ms | 24579 | 30 | 697655 | 7260 | 0.64695 | 0.936454 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 907.424 | 0.089982 | 551.042ms | 5094 | 2560 | 59408.4 | 5353.63 | 0.0269896 | 3.33703 | 1(Win) | true |
| Jsonifier (two-stage) | 788.699 | 0.150966 | 629.222ms | 5094 | 640 | 55339.4 | 6159.53 | 0.0126852 | 3.84091 | 2(Loss) | true |
| Glaze | 712.123 | 0.0730884 | 693.253ms | 5094 | 4890 | 121567 | 6821.88 | 0.355222 | 4.25506 | 3(Loss) | true |
| simdjson (ondemand) | 479.166 | 1.62818 | 977.997ms | 5094 | 4890 | 1.33247e+08 | 10138.5 | 0.78997 | 6.32874 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1106.61 | 0.125553 | 560.652ms | 5094 | 80 | 2430.38 | 4390 | 0.457666 | 2.73015 | 1(Win) | true |
| Glaze STATISTICAL TIE | 981.913 | 0.918595 | 604.899ms | 5094 | 640 | 1.3219e+06 | 4947.5 | 0.0126342 | 3.08031 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 972.454 | 0.102493 | 636.943ms | 5094 | 160 | 4194.58 | 4995.62 | 0.336658 | 3.11407 | 2(Tie) | true |
| simdjson (ondemand) | 640.336 | 0.175747 | 893.301ms | 5094 | 30 | 5333.33 | 7586.67 | 0.352734 | 4.72809 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9225.91 | 0.277556 | 54.7138ms | 5094 | 1280 | 2734.07 | 526.562 | 0 | 0.31723 | 1(Win) | true |
| Glaze | 3065.22 | 0.266951 | 150.683ms | 5094 | 2560 | 45824.5 | 1584.88 | 2.20546 | 0.978776 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11643.6 | 0.322901 | 43.8387ms | 5094 | 2560 | 4646.47 | 417.227 | 0.23461 | 0.250008 | 1(Win) | true |
| Glaze | 3961.69 | 0.403695 | 135.505ms | 5094 | 80 | 1960.44 | 1226.25 | 0.306748 | 0.746925 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1207.12 | 0.447847 | 655.845ms | 8051 | 640 | 519324 | 6360.62 | 0.289031 | 2.50947 | 1(Win) | true |
| Jsonifier | 1164.51 | 0.902229 | 685.486ms | 8051 | 30 | 106161 | 6593.33 | 0 | 2.60376 | 2(Loss) | true |
| Glaze | 1002.22 | 0.083521 | 770.497ms | 8051 | 2560 | 104810 | 7661.02 | 0.274583 | 3.02423 | 3(Loss) | true |
| simdjson (ondemand) | 793.505 | 0.0676662 | 976.781ms | 8051 | 2560 | 109745 | 9676.09 | 0.0129201 | 3.82235 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1448.98 | 0.243829 | 647.285ms | 8051 | 640 | 106838 | 5298.91 | 0.179549 | 2.09051 | 1(Win) | true |
| Jsonifier | 1356.68 | 0.0625963 | 673.094ms | 8051 | 4890 | 61368.8 | 5659.41 | 0.172035 | 2.2331 | 2(Loss) | true |
| Glaze | 1340.26 | 0.155863 | 686.387ms | 8051 | 80 | 6378.16 | 5728.75 | 0.460324 | 2.26108 | 3(Loss) | true |
| simdjson (ondemand) | 968.837 | 0.148135 | 910.161ms | 8051 | 40 | 5512.82 | 7925 | 0.105263 | 3.1282 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11867.2 | 0.750429 | 82.5481ms | 9255 | 80 | 2492.09 | 743.75 | 0.506757 | 0.251266 | 1(Win) | true |
| Glaze | 4042.56 | 0.584459 | 232.232ms | 9255 | 30 | 4885.06 | 2183.33 | 0.924499 | 0.746944 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13927 | 0.41775 | 70.0369ms | 9255 | 320 | 2242.95 | 633.75 | 0.294985 | 0.21203 | 1(Win) | true |
| Glaze | 5180.49 | 0.357487 | 190.454ms | 9255 | 640 | 23741.8 | 1703.75 | 1.3034 | 0.574857 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 3913.24 | 0.191062 | 73.7848ms | 2889 | 320 | 579.056 | 704.062 | 0.221435 | 0.753991 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 3908.04 | 0.495023 | 74.9369ms | 2889 | 40 | 487.179 | 705 | 0.235849 | 0.753842 | 1(Tie) | true |
| simdjson (ondemand) | 3402.09 | 0.141044 | 85.2216ms | 2889 | 1280 | 1670.03 | 809.844 | 0.307751 | 0.872351 | 3(Loss) | true |
| Glaze | 2994.74 | 0.807371 | 97.7944ms | 2889 | 30 | 1655.17 | 920 | 0.719424 | 0.993631 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4307.57 | 0.22866 | 69.6572ms | 2889 | 1280 | 2737.92 | 639.609 | 0.110051 | 0.686893 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4290.8 | 0.320656 | 68.2472ms | 2889 | 1280 | 5426.35 | 642.109 | 0.206411 | 0.688698 | 1(Tie) | true |
| simdjson (ondemand) | 3679.69 | 0.529418 | 83.7601ms | 2889 | 160 | 2514.15 | 748.75 | 1.52542 | 0.815732 | 3(Loss) | true |
| Glaze | 3155.24 | 0.147597 | 93.2639ms | 2889 | 2560 | 4252.34 | 873.203 | 1.08529 | 0.927817 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 4891.03 | 0.749063 | 81.2704ms | 3808 | 80 | 2474.68 | 742.5 | 0.33557 | 0.609963 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 4797.52 | 0.99797 | 81.0499ms | 3808 | 4890 | 279065 | 756.973 | 0.19818 | 0.618702 | 1(Tie) | true |
| simdjson (ondemand) | 4060.48 | 0.204301 | 96.7587ms | 3808 | 160 | 534.198 | 894.375 | 0.486787 | 0.734657 | 3(Loss) | true |
| Glaze | 3397.98 | 0.487946 | 117.571ms | 3808 | 80 | 2175.63 | 1068.75 | 0.34965 | 0.878404 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 5193.75 | 0.151977 | 73.4536ms | 3808 | 4890 | 5522 | 699.223 | 0.0775576 | 0.568749 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 5182.49 | 0.134838 | 75.0072ms | 3808 | 2560 | 2285.5 | 700.742 | 0.139167 | 0.570053 | 1(Tie) | true |
| simdjson (ondemand) | 4239.31 | 0.132388 | 88.4852ms | 3808 | 4890 | 6289.42 | 856.646 | 0.490964 | 0.700738 | 3(Loss) | true |
| Glaze | 3246.12 | 0.392524 | 108.599ms | 3808 | 80 | 1542.72 | 1118.75 | 0.111607 | 0.904504 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1489.28 | 0.580634 | 197.868ms | 2889 | 40 | 4615.38 | 1850 | 0.179856 | 2.01742 | 1(Win) | true |
| Jsonifier | 1461.63 | 0.231394 | 198.503ms | 2889 | 160 | 3044.03 | 1885 | 0.734803 | 2.05853 | 2(Loss) | true |
| Jsonifier (two-stage) | 1198.47 | 0.156454 | 235.376ms | 2889 | 1280 | 16558.6 | 2298.91 | 0.345435 | 2.51726 | 3(Loss) | true |
| simdjson (ondemand) | 1120.56 | 0.51302 | 260.258ms | 2889 | 160 | 25457.5 | 2458.75 | 0.254842 | 2.69736 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2007.41 | 0.520944 | 162.637ms | 2889 | 40 | 2044.87 | 1372.5 | 0.182482 | 1.49267 | 1(Win) | true |
| Glaze | 1930.06 | 0.351921 | 161.454ms | 2889 | 80 | 2018.99 | 1427.5 | 0.174825 | 1.55066 | 2(Loss) | true |
| Jsonifier (two-stage) | 1495.85 | 0.212422 | 212.194ms | 2889 | 160 | 2449.29 | 1841.88 | 0.306331 | 2.00987 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1312.23 | 0.0957626 | 237.94ms | 2889 | 4890 | 19768.7 | 2099.61 | 4.89746 | 2.29372 | -(Loss) | false |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10405.5 | 0.464498 | 30.0779ms | 2963 | 1280 | 2036.65 | 271.562 | 0.401146 | 0.275085 | 1(Win) | true |
| Glaze | 4709.56 | 0.843949 | 66.419ms | 2963 | 40 | 1025.64 | 600 | 0.558659 | 0.628797 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11901.8 | 0.571824 | 25.6337ms | 2963 | 1280 | 2359.26 | 237.422 | 0.621321 | 0.23101 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 5118.1 | 0.347229 | 57.0936ms | 2963 | 4890 | 17971.6 | 552.106 | 3.06617 | 0.567185 | -(Loss) | false |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1579.38 | 0.163336 | 235.556ms | 3808 | 320 | 4513.71 | 2299.38 | 0.0543922 | 1.90335 | 1(Win) | true |
| Jsonifier (two-stage) | 1560.09 | 0.263564 | 248.05ms | 3808 | 320 | 12045.4 | 2327.81 | 0.60048 | 1.92882 | 2(Loss) | true |
| Jsonifier | 1480.77 | 0.412619 | 257.261ms | 3808 | 40 | 4096.15 | 2452.5 | 0.304878 | 2.04775 | 3(Loss) | true |
| simdjson (ondemand) | 1425.55 | 0.343923 | 270.677ms | 3808 | 40 | 3070.51 | 2547.5 | 0.295276 | 2.11031 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2075.2 | 0.530558 | 194.351ms | 3808 | 30 | 2586.21 | 1750 | 0.379507 | 1.45108 | 1(Win) | true |
| Jsonifier (two-stage) | 1936.85 | 0.259828 | 215.495ms | 3808 | 80 | 1898.73 | 1875 | 0.398406 | 1.55562 | 2(Loss) | true |
| Jsonifier | 1817.75 | 0.108458 | 226.229ms | 3808 | 2560 | 12019.6 | 1997.85 | 0.268585 | 1.65327 | 3(Loss) | true |
| simdjson (ondemand) | 1632.18 | 0.311629 | 238.273ms | 3808 | 40 | 1923.08 | 2225 | 0.0748503 | 1.84347 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9218.03 | 1.00539 | 48.8532ms | 4300 | 4890 | 97822.9 | 444.867 | 0.242911 | 0.316516 | 1(Win) | true |
| Glaze | 3175.84 | 1.43772 | 128.281ms | 4300 | 160 | 55143.1 | 1291.25 | 0.977517 | 0.942517 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11375.1 | 0.268047 | 38.8444ms | 4300 | 2560 | 2390.52 | 360.508 | 0.0759054 | 0.253567 | 1(Win) | true |
| Glaze | 4543.82 | 0.787825 | 101.318ms | 4300 | 80 | 4044.3 | 902.5 | 1.09589 | 0.64377 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 3055.58 | 0.0687021 | 7761.45ms | 466906 | 2560 | 2.56597e+07 | 145726 | 4.61364 | 0.994532 | -(Win) | false |
| Glaze | 1715.17 | 0.760201 | 6377.48ms | 466906 | 640 | 2.49275e+09 | 259610 | 1.67247 | 1.77178 | 2(Loss) | true |
| simdjson (ondemand) | 1341.33 | 0.128564 | 8480.11ms | 466906 | 1280 | 2.33152e+08 | 331966 | 0.218177 | 2.26544 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3007 | 0.277729 | 7651.22ms | 466906 | 30 | 5.07407e+06 | 148080 | 0.0539957 | 1.01062 | 1(Win) | true |
| Glaze | 1840.84 | 0.316407 | 6377.65ms | 466906 | 40 | 2.34304e+07 | 241888 | 0.273947 | 1.65091 | 2(Loss) | true |
| simdjson (ondemand) | 1339.27 | 0.0811425 | 8499.83ms | 466906 | 1280 | 9.31595e+07 | 332476 | 0.330624 | 2.26897 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2599.97 | 0.600099 | 6573.88ms | 699405 | 640 | 1.51686e+09 | 256543 | 0.711351 | 1.16882 | 1(Win) | true |
| Jsonifier | 2459.78 | 0.122337 | 6921.79ms | 699405 | 640 | 7.0431e+07 | 271165 | 0.185658 | 1.23496 | 2(Loss) | true |
| simdjson (ondemand) | 1288.6 | 0.803761 | 7229.7ms | 767297 | 320 | 6.66649e+09 | 567867 | 1.11263 | 2.35723 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3919.15 | 0.09502 | 9095.26ms | 699405 | 320 | 8.36864e+06 | 170191 | 0.303519 | 0.775433 | 1(Win) | true |
| Glaze | 2499.65 | 0.942458 | 6709.93ms | 699405 | 640 | 4.04766e+09 | 266839 | 0.0333657 | 1.21572 | 2(Loss) | true |
| simdjson (ondemand) | 1258.59 | 1.45501 | 7232.36ms | 767297 | 160 | 1.14501e+10 | 581404 | 1.15953 | 2.41362 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2627.3 | 0.282524 | 6068.77ms | 631514 | 80 | 3.35543e+07 | 229231 | 0.149733 | 1.15674 | 1(Win) | true |
| Glaze | 2558.88 | 0.152086 | 6371.99ms | 631514 | 30 | 3.84386e+06 | 235360 | 0.411848 | 1.18768 | 2(Loss) | true |
