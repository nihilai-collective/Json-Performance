# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson (AVX512)
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36260.0 compiler).  

Latest Results: (Nov 14, 2026)
#### Using the following commits:
----
| Jsonifier: [d4727ec](https://github.com/nihilai-collective/Jsonifier/commit/d4727ec)  
| Glaze: [a53ddd59](https://github.com/stephenberry/glaze/commit/a53ddd59)  
| simdjson: [449f38e63](https://github.com/simdjson/simdjson/commit/449f38e63)  

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
*Environment generated via BenchmarkSuite commit: [27950a9](https://github.com/nihilai-collective/benchmarksuite/commit/27950a9)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 467.475 | 0.303837 | 189.386ms | 905 | 80 | 2517.41 | 1846.25 | 0.0677507 | 5.21739 | 1(Win) | true |
| Glaze | 446.322 | 0.275116 | 200.384ms | 905 | 80 | 2264.24 | 1933.75 | 0.194301 | 5.47811 | 2(Loss) | true |
| Jsonifier (two-stage) | 165.129 | 0.157113 | 542.218ms | 905 | 30 | 2022.99 | 5226.67 | 0 | 14.8702 | 3(Loss) | true |
| simdjson (ondemand) | 69.1193 | 0.102167 | 1266.61ms | 905 | 4890 | 795852 | 12486.7 | 0.0775968 | 35.7099 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 545.94 | 0.33223 | 172.355ms | 905 | 2560 | 70619.7 | 1580.9 | 0.219428 | 4.45678 | 1(Win) | true |
| Glaze | 511.705 | 0.277657 | 171.138ms | 905 | 4890 | 107247 | 1686.67 | 0.141844 | 4.76457 | 2(Loss) | true |
| Jsonifier (two-stage) | 172.105 | 0.241559 | 512.534ms | 905 | 2560 | 375658 | 5014.8 | 0.182717 | 14.2598 | 3(Loss) | true |
| simdjson (ondemand) | 71.3089 | 0.0482469 | 1239.62ms | 905 | 30 | 1022.99 | 12103.3 | 0.137893 | 34.5898 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1153.89 | 0.264227 | 78.8434ms | 905 | 640 | 2499.78 | 747.969 | 0.0208855 | 2.06997 | 1(Win) | true |
| Glaze | 81.5662 | 0.40675 | 1131.42ms | 905 | 2560 | 4.74211e+06 | 10581.3 | 0.20086 | 30.2586 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 1554.32 | 0.534369 | 68.8082ms | 905 | 4890 | 43053.6 | 555.276 | 3.87431 | 1.52013 | -(Win) | false |
| Glaze | 269.43 | 0.104058 | 335.284ms | 905 | 30 | 333.333 | 3203.33 | 0 | 9.08987 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 964.526 | 0.107798 | 183.769ms | 1811 | 640 | 2384.59 | 1790.62 | 0.0873362 | 2.52836 | 1(Win) | true |
| Jsonifier (two-stage) | 365.036 | 0.17201 | 481.406ms | 1811 | 4890 | 323878 | 4731.33 | 0.00740634 | 6.74627 | 2(Loss) | true |
| Glaze | 308.205 | 0.12873 | 399.414ms | 1811 | 80 | 4162.97 | 5603.75 | 0.0223115 | 7.99573 | 3(Loss) | true |
| simdjson (ondemand) | 140.301 | 0.0712885 | 1239.44ms | 1811 | 30 | 2310.34 | 12310 | 0.0270856 | 17.6109 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1405.76 | 0.145494 | 126.681ms | 1811 | 640 | 2044.97 | 1228.59 | 0.114329 | 1.72393 | 1(Win) | true |
| Glaze | 510.789 | 0.0915454 | 344.543ms | 1811 | 160 | 1533.02 | 3381.25 | 0.0738825 | 4.80754 | 2(Loss) | true |
| Jsonifier (two-stage) | 418.861 | 0.190478 | 419.196ms | 1811 | 30 | 1850.57 | 4123.33 | 0.0807754 | 5.879 | 3(Loss) | true |
| simdjson (ondemand) | 146.453 | 0.188839 | 1192.93ms | 1811 | 1280 | 634797 | 11792.9 | 0.18581 | 16.8653 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 467.733 | 0.149832 | 376.167ms | 1811 | 40 | 1224.36 | 3692.5 | 0.0225632 | 5.20856 | 1(Win) | true |
| Glaze | 139.783 | 0.747285 | 1272.86ms | 1798 | 640 | 5.37799e+06 | 12266.9 | 0.109423 | 17.6658 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 729.313 | 0.156054 | 248.421ms | 1811 | 160 | 2185.14 | 2368.12 | 0.0263852 | 3.35803 | 1(Win) | true |
| Glaze | 386.958 | 0.117685 | 466.105ms | 1798 | 80 | 2175.63 | 4431.25 | 0.0282167 | 6.35861 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1487.93 | 0.103882 | 262.241ms | 3862 | 320 | 2115.89 | 2475.31 | 0.189729 | 1.64616 | 1(Win) | true |
| Glaze | 920.773 | 0.169516 | 413.122ms | 3862 | 30 | 1379.31 | 4000 | 0.249377 | 2.67493 | 2(Loss) | true |
| Jsonifier (two-stage) | 597.298 | 0.0954374 | 767.6ms | 3862 | 80 | 2770.57 | 6166.25 | 0.1417 | 4.12987 | 3(Loss) | true |
| simdjson (ondemand) | 302.72 | 0.0820342 | 1256.8ms | 3862 | 30 | 2988.51 | 12166.7 | 0.32769 | 8.17046 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1939.74 | 0.123438 | 194.933ms | 3862 | 160 | 878.931 | 1898.75 | 0.197889 | 1.25919 | 1(Win) | true |
| Glaze | 1056.08 | 0.151849 | 363.826ms | 3862 | 40 | 1121.79 | 3487.5 | 0.0239006 | 2.32866 | 2(Loss) | true |
| Jsonifier (two-stage) | 640.909 | 0.161208 | 577.958ms | 3862 | 30 | 2574.71 | 5746.67 | 0.349243 | 3.83939 | 3(Loss) | true |
| simdjson (ondemand) | 322.042 | 0.0782444 | 1170.62ms | 3862 | 30 | 2402.3 | 11436.7 | 0.0291545 | 7.6716 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 438.113 | 0.207977 | 861.162ms | 3862 | 2560 | 782573 | 8406.72 | 0.0567204 | 5.62864 | 1(Win) | true |
| Glaze | 350.77 | 0.129155 | 1094.37ms | 3862 | 30 | 5517.24 | 10500 | 0.253325 | 7.04122 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3866.76 | 0.589859 | 106.376ms | 3862 | 80 | 2525.32 | 952.5 | 0.263158 | 0.622615 | 1(Win) | true |
| Glaze | 1094.53 | 0.406969 | 355.113ms | 3862 | 640 | 120025 | 3365 | 0.00928764 | 2.24333 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 855.071 | 0.374389 | 1102.61ms | 9578 | 640 | 1.0237e+06 | 10682.5 | 0.0350918 | 2.8841 | 1(Win) | true |
| Glaze | 690.143 | 0.120473 | 1344.27ms | 9578 | 4890 | 1.24325e+06 | 13235.4 | 0.0532007 | 3.57516 | 2(Loss) | true |
| Jsonifier (two-stage) | 626.518 | 0.200747 | 1488.73ms | 9578 | 1280 | 1.09646e+06 | 14579.5 | 0.0241077 | 3.93988 | 3(Loss) | true |
| simdjson (ondemand) | 529.064 | 0.169184 | 1812.48ms | 9578 | 40 | 34128.2 | 17265 | 0.0869565 | 4.66637 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1339.94 | 0.289315 | 939.934ms | 9578 | 1280 | 497891 | 6816.95 | 0.198659 | 1.84103 | 1(Win) | true |
| Glaze | 973.114 | 0.0672489 | 1216.06ms | 9578 | 30 | 1195.4 | 9386.67 | 0.035524 | 2.53575 | 2(Loss) | true |
| Jsonifier (two-stage) | 852.987 | 0.169754 | 1316.11ms | 9578 | 2560 | 845952 | 10708.6 | 0.00583609 | 2.895 | 3(Loss) | true |
| simdjson (ondemand) | 682.579 | 0.209203 | 1607.19ms | 9578 | 640 | 501602 | 13382 | 0.00583771 | 3.62071 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1305.32 | 0.27945 | 720.999ms | 9578 | 1280 | 489479 | 6997.73 | 0.124078 | 1.88917 | 1(Win) | true |
| Glaze | 557.607 | 0.254236 | 1148.69ms | 9578 | 80 | 138758 | 16381.2 | 0.205605 | 4.43218 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8248.83 | 0.143697 | 125.562ms | 9578 | 640 | 1620.48 | 1107.34 | 0.211208 | 0.293227 | 1(Win) | true |
| Glaze | 2651.46 | 0.162474 | 373.946ms | 9578 | 80 | 2506.33 | 3445 | 0.0726216 | 0.924777 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1406.77 | 0.240125 | 265.841ms | 3873 | 4890 | 194373 | 2625.58 | 0.0402721 | 1.74171 | 1(Win) | true |
| Glaze | 1017.17 | 0.104133 | 369.13ms | 3873 | 160 | 2287.74 | 3631.25 | 0.171821 | 2.41473 | 2(Loss) | true |
| Jsonifier (two-stage) | 573.514 | 0.149566 | 655.064ms | 3873 | 4890 | 453717 | 6440.27 | 0.022329 | 4.29845 | 3(Loss) | true |
| simdjson (ondemand) | 310.438 | 0.258043 | 1212.18ms | 3873 | 640 | 603267 | 11898 | 0.0800441 | 7.95841 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1834.18 | 0.192403 | 206.727ms | 3873 | 80 | 1200.95 | 2013.75 | 0.186567 | 1.33454 | 1(Win) | true |
| Glaze | 1192.44 | 0.0698238 | 318.855ms | 3873 | 160 | 748.428 | 3097.5 | 0.201369 | 2.05835 | 2(Loss) | true |
| Jsonifier (two-stage) | 626.265 | 0.140101 | 601.086ms | 3873 | 4890 | 333863 | 5897.79 | 0.00962919 | 3.93412 | 3(Loss) | true |
| simdjson (ondemand) | 328.757 | 0.0679807 | 1141.84ms | 3873 | 40 | 2333.33 | 11235 | 0.074118 | 7.52052 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 460.671 | 0.141447 | 805.287ms | 3873 | 4890 | 628939 | 8017.83 | 0.271357 | 5.34442 | 1(Win) | true |
| Glaze | 342.449 | 0.361155 | 1106.88ms | 3873 | 640 | 971112 | 10785.8 | 0.0913494 | 7.20746 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2983.86 | 0.308933 | 131.963ms | 3873 | 2560 | 37437.4 | 1237.85 | 0.702301 | 0.811755 | 1(Win) | true |
| Glaze | 1117.01 | 0.140082 | 344.392ms | 3873 | 30 | 643.678 | 3306.67 | 0.100705 | 2.19564 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 835.017 | 0.413555 | 5551.32ms | 94653 | 2560 | 5.11664e+08 | 108103 | 0.228605 | 2.96416 | 1(Win) | true |
| Jsonifier (two-stage) | 822.776 | 0.241364 | 5651.42ms | 94653 | 2560 | 1.79511e+08 | 109712 | 0.0336351 | 3.00823 | 2(Loss) | true |
| Glaze | 805.426 | 0.383785 | 5783.77ms | 94653 | 1280 | 2.36812e+08 | 112075 | 0.0908164 | 3.07305 | 3(Loss) | true |
| simdjson (ondemand) | 748.073 | 0.259476 | 6196.53ms | 94653 | 1280 | 1.25483e+08 | 120668 | 0.314377 | 3.30868 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1258.6 | 0.0898539 | 9044.73ms | 94653 | 2560 | 1.06319e+07 | 71721.3 | 0.0655089 | 1.9664 | 1(Win) | true |
| Jsonifier (two-stage) | 1219.2 | 0.0575744 | 9304.71ms | 94653 | 4890 | 8.88566e+06 | 74039.1 | 0.205155 | 2.0299 | 2(Loss) | true |
| Glaze | 1165.67 | 0.0951343 | 9552.32ms | 94653 | 2560 | 1.38941e+07 | 77438.7 | 0.22181 | 2.12311 | 3(Loss) | true |
| simdjson (ondemand) | 1081.31 | 0.205659 | 5164.69ms | 94653 | 320 | 9.43224e+06 | 83480.3 | 0.0108547 | 2.2878 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13080.7 | 0.354378 | 705.635ms | 94653 | 2560 | 1.53102e+06 | 6900.86 | 0.0453047 | 0.188458 | 1(Win) | true |
| Glaze | 5207.7 | 0.290587 | 1763.16ms | 94653 | 4890 | 1.24061e+07 | 17333.6 | 0.0714738 | 0.474633 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13377.6 | 0.235512 | 692.255ms | 94653 | 2560 | 646513 | 6747.7 | 0.399293 | 0.184301 | 1(Win) | true |
| Glaze | 5836.3 | 0.0645312 | 1594.36ms | 94653 | 30 | 2988.51 | 15466.7 | 0.322234 | 0.423136 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1081.49 | 0.361881 | 5620.7ms | 124597 | 640 | 1.01177e+08 | 109871 | 0.0935205 | 2.28868 | 1(Win) | true |
| Jsonifier | 1041.13 | 0.954016 | 5910.03ms | 124597 | 160 | 1.89686e+08 | 114131 | 1.07319 | 2.37744 | 2(Loss) | true |
| Glaze | 997.801 | 0.304726 | 6148.36ms | 124597 | 1280 | 1.68561e+08 | 119087 | 0.136792 | 2.48064 | 3(Loss) | true |
| simdjson (ondemand) | 962.561 | 0.146219 | 6327.45ms | 124597 | 2560 | 8.34076e+07 | 123447 | 0.0187046 | 2.57154 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1581.14 | 0.165874 | 9983.95ms | 124597 | 640 | 9.94507e+06 | 75151.2 | 0.102604 | 1.56524 | 1(Win) | true |
| Jsonifier | 1457.64 | 0.0968477 | 5160.63ms | 124597 | 1280 | 7.97822e+06 | 81519 | 0.207057 | 1.69794 | 2(Loss) | true |
| Glaze | 1414.73 | 0.0900064 | 5236.63ms | 124597 | 2560 | 1.46303e+07 | 83991 | 0.229905 | 1.74945 | 3(Loss) | true |
| simdjson (ondemand) | 1362.08 | 0.142419 | 5369.43ms | 124597 | 640 | 9.87923e+06 | 87237.8 | 0.0469484 | 1.8171 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12730.5 | 0.197678 | 1047.44ms | 136037 | 4890 | 1.9845e+06 | 10190.9 | 0.042195 | 0.193983 | 1(Win) | true |
| Glaze | 4342.14 | 0.0958991 | 3073.38ms | 136076 | 30 | 24643.7 | 29886.7 | 0.144782 | 0.569399 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13218 | 0.0582549 | 1026.07ms | 136037 | 40 | 1307.69 | 9815 | 0.0849762 | 0.186804 | 1(Win) | true |
| Glaze | 4650.78 | 0.122088 | 2846.5ms | 136076 | 30 | 34816.1 | 27903.3 | 0 | 0.531434 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 673.175 | 0.68788 | 9857.1ms | 2251027 | 160 | 7.69928e+10 | 3.18899e+06 | 0.477971 | 3.67774 | 1(Win) | true |
| Jsonifier (two-stage) | 634.355 | 0.730468 | 5009.83ms | 2251027 | 40 | 2.44433e+10 | 3.38414e+06 | 1.36959 | 3.90283 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 198.762 | 1.05787 | 7540.65ms | 2251027 | 40 | 5.22181e+11 | 1.08006e+07 | 0.0516063 | 12.4561 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 194.89 | 0.945699 | 7836.48ms | 2251027 | 30 | 3.25544e+11 | 1.10152e+07 | 0.408186 | 12.7036 | 3(Tie) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 842.752 | 1.21644 | 9856.49ms | 2251027 | 30 | 2.8805e+10 | 2.54731e+06 | 0.0872056 | 2.93769 | 1(Win) | true |
| Jsonifier (two-stage) | 801.594 | 0.215243 | 5043.85ms | 2251027 | 40 | 1.32914e+09 | 2.6781e+06 | 2.27229 | 3.08856 | 2(Loss) | true |
| simdjson (ondemand) | 216.949 | 0.21143 | 7454.34ms | 2251027 | 30 | 1.3131e+10 | 9.89515e+06 | 0.292752 | 11.4119 | 3(Loss) | true |
| Glaze | 207.953 | 0.922379 | 7660.87ms | 2251027 | 40 | 3.62669e+11 | 1.03232e+07 | 0.287622 | 11.9057 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1254.34 | 0.077228 | 5023.74ms | 2090234 | 80 | 1.20504e+08 | 1.58921e+06 | 1.69939 | 1.97366 | 1(Win) | true |
| Glaze | 824.5 | 0.247541 | 7451.15ms | 2090234 | 80 | 2.86545e+09 | 2.41771e+06 | 0.4988 | 3.00258 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1486.24 | 0.106783 | 8523.92ms | 2090234 | 40 | 8.20507e+07 | 1.34124e+06 | 0.00552939 | 1.66579 | 1(Win) | true |
| Glaze | 1174.38 | 0.0428268 | 5358.2ms | 2090234 | 160 | 8.45513e+07 | 1.6974e+06 | 0.00460241 | 2.10814 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1452.62 | 0.817081 | 5348.55ms | 5373214 | 80 | 6.64636e+10 | 3.52762e+06 | 0.506511 | 1.70434 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1423.72 | 1.11216 | 5387.14ms | 5373214 | 80 | 1.28187e+11 | 3.59924e+06 | 1.17393 | 1.73896 | 1(Tie) | true |
| simdjson (ondemand) | 459.507 | 1.05413 | 7943.94ms | 5373214 | 30 | 4.14569e+11 | 1.11517e+07 | 0.306068 | 5.38793 | 3(Loss) | true |
| Glaze | 429.284 | 1.26212 | 8167.37ms | 5373214 | 30 | 6.80932e+11 | 1.19368e+07 | 1.49908 | 5.76722 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1748.09 | 0.95488 | 5994.84ms | 5373214 | 30 | 2.3505e+10 | 2.93137e+06 | 1.40459 | 1.41627 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE DID NOT CONVERGE | 1729.52 | 0.794371 | 5444.43ms | 5373214 | 80 | 4.43154e+10 | 2.96285e+06 | 5.04713 | 1.43143 | -(Tie) | false |
| simdjson (ondemand) | 491.232 | 0.985797 | 8016.79ms | 5373214 | 40 | 4.22991e+11 | 1.04315e+07 | 0.473979 | 5.04002 | 3(Loss) | true |
| Glaze | 465.889 | 0.915111 | 8195.98ms | 5373214 | 40 | 4.05239e+11 | 1.0999e+07 | 0.175503 | 5.31416 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2735.72 | 0.128171 | 7296.32ms | 6661897 | 160 | 1.41761e+09 | 2.32235e+06 | 0.0206645 | 0.904946 | 1(Win) | true |
| Glaze | 1460.97 | 0.0835843 | 6613.25ms | 6661897 | 80 | 1.05695e+09 | 4.34869e+06 | 0.0650061 | 1.6946 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4330.82 | 0.0913585 | 9343.92ms | 6661897 | 40 | 7.18479e+07 | 1.46699e+06 | 0.0583734 | 0.571661 | 1(Win) | true |
| Glaze | 3235.02 | 0.0763075 | 6191.06ms | 6661897 | 40 | 8.98328e+07 | 1.9639e+06 | 0.0853621 | 0.765303 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1392.94 | 0.0779758 | 8785.33ms | 500299 | 1280 | 9.13116e+07 | 342530 | 0.0578067 | 1.77714 | 1(Win) | true |
| Jsonifier (two-stage) | 1189.94 | 0.124321 | 5178.47ms | 500299 | 320 | 7.95155e+07 | 400964 | 0.874159 | 2.08041 | 2(Loss) | true |
| Glaze | 774.453 | 0.302372 | 7983.81ms | 500299 | 30 | 1.04105e+08 | 616077 | 0.257959 | 3.19664 | 3(Loss) | true |
| simdjson (ondemand) | 600.592 | 0.21662 | 5144.48ms | 500299 | 30 | 8.88423e+07 | 794420 | 0.14204 | 4.12205 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1619.56 | 0.194442 | 8564.45ms | 500299 | 320 | 1.05002e+08 | 294600 | 0.0429792 | 1.52852 | 1(Win) | true |
| Jsonifier (two-stage) | 1340.73 | 0.114857 | 5025.67ms | 500299 | 320 | 5.34617e+07 | 355868 | 0.0147505 | 1.84644 | 2(Loss) | true |
| Glaze | 849.259 | 0.251478 | 7747.13ms | 500299 | 40 | 7.98435e+07 | 561810 | 0.0148352 | 2.91517 | 3(Loss) | true |
| simdjson (ondemand) | 587.437 | 0.285646 | 5411.26ms | 500299 | 30 | 1.61479e+08 | 812210 | 0.0533239 | 4.21429 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8062.26 | 0.0972061 | 5930.81ms | 500299 | 4890 | 1.61824e+07 | 59179.8 | 0.00945667 | 0.30689 | 1(Win) | true |
| Glaze | 3333.54 | 0.202849 | 7362.89ms | 500299 | 1280 | 1.07895e+08 | 143128 | 0.144255 | 0.74247 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8169.55 | 0.308577 | 5896.44ms | 500299 | 320 | 1.0393e+07 | 58402.5 | 0.0685372 | 0.302874 | 1(Win) | true |
| Glaze | 3629.04 | 0.103372 | 6790.35ms | 500299 | 1280 | 2.36426e+07 | 131474 | 0.212755 | 0.682042 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2528.38 | 0.279732 | 5767.46ms | 1151920 | 40 | 5.90886e+07 | 434490 | 1.70354 | 0.979097 | 1(Win) | true |
| Jsonifier | 2199.41 | 0.160624 | 6438.96ms | 1151920 | 640 | 4.11943e+08 | 499479 | 0.181706 | 1.12556 | 2(Loss) | true |
| Glaze | 1500.16 | 0.320763 | 9484.66ms | 1151920 | 30 | 1.65524e+08 | 732293 | 0.173128 | 1.65027 | 3(Loss) | true |
| simdjson (ondemand) | 1280.37 | 0.18781 | 5671.78ms | 1151920 | 40 | 1.03865e+08 | 857998 | 0.100036 | 1.93359 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2857.73 | 0.108034 | 5436.19ms | 1151920 | 640 | 1.10383e+08 | 384416 | 0.101958 | 0.866274 | 1(Win) | true |
| Jsonifier | 2415.61 | 0.377936 | 6398.19ms | 1151920 | 30 | 8.86234e+07 | 454773 | 0.012462 | 1.02488 | 2(Loss) | true |
| Glaze | 1590.86 | 0.152012 | 5132.09ms | 1151920 | 160 | 1.76301e+08 | 690542 | 0.353 | 1.55622 | 3(Loss) | true |
| simdjson (ondemand) | 1229.93 | 0.110393 | 5996.9ms | 1151920 | 160 | 1.55557e+08 | 893189 | 0.139264 | 2.01288 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4063.59 | 0.274273 | 8655.88ms | 1439562 | 80 | 6.86909e+07 | 337848 | 0.0377532 | 0.609057 | 1(Win) | true |
| Glaze | 2099.11 | 0.30734 | 8336.06ms | 1439584 | 160 | 6.46488e+08 | 654035 | 0.190912 | 1.17923 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12935.8 | 0.256525 | 5499.83ms | 1439562 | 320 | 2.37183e+07 | 106130 | 0.106115 | 0.191317 | 1(Win) | true |
| Glaze | 6184.56 | 0.427396 | 5795.21ms | 1439584 | 40 | 3.60062e+07 | 221988 | 0.676734 | 0.400276 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1306.83 | 0.216447 | 4163.65ms | 56369 | 640 | 5.0737e+06 | 41135.9 | 0.0144318 | 1.89259 | 1(Win) | true |
| Glaze | 1047.3 | 0.226652 | 5217.23ms | 56369 | 640 | 8.66248e+06 | 51330 | 0.0609177 | 2.36275 | 2(Loss) | true |
| Jsonifier (two-stage) | 1018.51 | 0.234734 | 5327.43ms | 56369 | 640 | 9.82396e+06 | 52780.9 | 0.189822 | 2.42951 | 3(Loss) | true |
| simdjson (ondemand) | 750.337 | 0.135146 | 7239.45ms | 56369 | 2560 | 2.40003e+07 | 71644.7 | 0.133868 | 3.29825 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1844.53 | 0.0882053 | 3434.01ms | 56369 | 4890 | 3.23153e+06 | 29144.4 | 0.0223926 | 1.34105 | 1(Win) | true |
| Glaze | 1484.93 | 0.0966814 | 4174.77ms | 56369 | 2560 | 3.13613e+06 | 36202.1 | 0.334128 | 1.6661 | 2(Loss) | true |
| Jsonifier (two-stage) | 1329.17 | 0.105041 | 4609.93ms | 56369 | 2560 | 4.62038e+06 | 40444.6 | 0.00791916 | 1.86136 | 3(Loss) | true |
| simdjson (ondemand) | 941.079 | 0.287138 | 6268.84ms | 56369 | 320 | 8.60914e+06 | 57123.4 | 0.0300793 | 2.62953 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11177.7 | 0.0605783 | 501.667ms | 56369 | 160 | 1358.1 | 4809.38 | 0.0908855 | 0.219957 | 1(Win) | true |
| Glaze | 3232.76 | 0.093127 | 1690.7ms | 56369 | 4890 | 1.17272e+06 | 16629 | 0.378183 | 0.764404 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12012.9 | 0.108866 | 458.353ms | 56369 | 80 | 1898.73 | 4475 | 0.0558347 | 0.205153 | 1(Win) | true |
| Glaze | 3447.44 | 0.254657 | 1583.04ms | 56369 | 1280 | 2.0184e+06 | 15593.5 | 0.21439 | 0.716776 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1484.13 | 0.159164 | 6024.84ms | 83958 | 640 | 4.71903e+06 | 53950 | 0.302028 | 1.66721 | 1(Win) | true |
| Jsonifier | 1446.02 | 0.0760278 | 5623.92ms | 83958 | 4890 | 8.66622e+06 | 55371.8 | 0.028722 | 1.71129 | 2(Loss) | true |
| Glaze | 1393.15 | 0.163776 | 5796.68ms | 83958 | 4890 | 4.33247e+07 | 57473 | 0.397718 | 1.77622 | 3(Loss) | true |
| simdjson (ondemand) | 1079.77 | 0.117964 | 7509.85ms | 83958 | 1280 | 9.79431e+06 | 74153.4 | 0.165136 | 2.29199 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1915.43 | 0.147892 | 4768.33ms | 83958 | 1280 | 4.89208e+06 | 41802 | 0.237356 | 1.29161 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 1891.64 | 0.0470894 | 4871.81ms | 83958 | 40 | 15891 | 42327.5 | 0.0295229 | 1.30787 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1888.32 | 0.0988621 | 4795.37ms | 83958 | 2560 | 4.49857e+06 | 42402.1 | 0.0679413 | 1.31033 | 2(Tie) | true |
| simdjson (ondemand) | 1332.1 | 0.27946 | 6582.89ms | 83958 | 160 | 4.51448e+06 | 60106.9 | 0.109061 | 1.8576 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11845.8 | 0.313973 | 783.247ms | 94370 | 1280 | 728344 | 7597.5 | 0.123244 | 0.208152 | 1(Win) | true |
| Glaze | 3254.79 | 0.123606 | 2974.84ms | 94370 | 2560 | 2.99048e+06 | 27651.1 | 2.17454 | 0.759902 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12405 | 0.130109 | 747.996ms | 94370 | 40 | 3564.1 | 7255 | 0.0229779 | 0.19869 | 1(Win) | true |
| Glaze | 3479.02 | 0.0770936 | 2624.99ms | 94370 | 4890 | 1.94491e+06 | 25868.9 | 0.567986 | 0.7108 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1062.8 | 0.588709 | 4787.54ms | 53331 | 80 | 6.34959e+06 | 47855 | 0.00522439 | 2.32799 | 1(Win) | true |
| Glaze | 1049.24 | 0.188647 | 4950.05ms | 53331 | 2560 | 2.14066e+07 | 48473.6 | 0.26258 | 2.35812 | 2(Loss) | true |
| Jsonifier (two-stage) | 1023.53 | 0.182631 | 5018.73ms | 53331 | 4890 | 4.02731e+07 | 49691 | 0.00780549 | 2.417 | 3(Loss) | true |
| simdjson (ondemand) | 650.218 | 0.139315 | 7860.14ms | 53331 | 4890 | 5.80692e+07 | 78220.6 | 0.361822 | 3.80623 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1544.92 | 0.19781 | 4014.7ms | 53331 | 1280 | 5.4282e+06 | 32921.1 | 0.0241997 | 1.60122 | 1(Win) | true |
| Glaze | 1460.34 | 0.130063 | 4225.03ms | 53331 | 2560 | 5.25292e+06 | 34827.8 | 0.0726262 | 1.6941 | 2(Loss) | true |
| Jsonifier (two-stage) | 1446.38 | 0.104762 | 4254.15ms | 53331 | 4890 | 6.63616e+06 | 35164 | 0.0536694 | 1.71007 | 3(Loss) | true |
| simdjson (ondemand) | 773.029 | 0.187256 | 7091.32ms | 53331 | 4890 | 7.42249e+07 | 65793.6 | 0.122412 | 3.20143 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11836.3 | 0.295755 | 477.979ms | 58581 | 40 | 7794.87 | 4720 | 0.425532 | 0.207933 | 1(Win) | true |
| Glaze | 4967.39 | 0.288814 | 1133.8ms | 58581 | 1280 | 1.35053e+06 | 11246.8 | 0.0465194 | 0.497158 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12762.4 | 0.167431 | 457.037ms | 58581 | 80 | 4297.47 | 4377.5 | 0.0571429 | 0.193047 | 1(Win) | true |
| Glaze | 5709.63 | 0.178444 | 1004.02ms | 58581 | 2560 | 780443 | 9784.73 | 0.053068 | 0.432239 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1212.47 | 0.224899 | 5150.54ms | 65103 | 4890 | 6.48556e+07 | 51207.2 | 0.760703 | 2.04014 | 1(Win) | true |
| Glaze | 1174.96 | 0.225471 | 5295.85ms | 65103 | 4890 | 6.94138e+07 | 52841.8 | 0.0426032 | 2.10586 | 2(Loss) | true |
| Jsonifier | 1081.8 | 0.322281 | 5770.82ms | 65103 | 2560 | 8.75815e+07 | 57392.1 | 0.051618 | 2.28731 | 3(Loss) | true |
| simdjson (ondemand) | 779.28 | 0.146763 | 7998ms | 65103 | 4890 | 6.68585e+07 | 79672.3 | 0.0837872 | 3.17586 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1748.34 | 0.0993686 | 4246.18ms | 65103 | 4890 | 6.08916e+06 | 35512 | 0.144076 | 1.41485 | 1(Win) | true |
| Glaze | 1621.29 | 0.125112 | 4577.49ms | 65103 | 2560 | 5.87646e+06 | 38294.8 | 0.0937562 | 1.52601 | 2(Loss) | true |
| Jsonifier | 1499.81 | 0.175529 | 4887.44ms | 65103 | 2560 | 1.35165e+07 | 41396.5 | 0.031224 | 1.64964 | 3(Loss) | true |
| simdjson (ondemand) | 954.442 | 0.303971 | 7219.33ms | 65103 | 160 | 6.25585e+06 | 65050.6 | 0.235949 | 2.59308 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12107.7 | 0.162703 | 644.034ms | 78778 | 40 | 4076.92 | 6205 | 0.0268673 | 0.203338 | 1(Win) | true |
| Glaze | 4598.05 | 0.49044 | 1644.86ms | 78778 | 1280 | 8.21948e+06 | 16339.2 | 0.13406 | 0.537458 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12454 | 0.306684 | 609.845ms | 78778 | 1280 | 438114 | 6032.5 | 0 | 0.197888 | 1(Win) | true |
| Glaze | 5268.99 | 0.121354 | 1460.81ms | 78778 | 4890 | 1.4641e+06 | 14258.6 | 0.126158 | 0.468871 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1361 | 0.211963 | 845.435ms | 11812 | 2560 | 787931 | 8276.84 | 0.094772 | 1.8091 | 1(Win) | true |
| Jsonifier (two-stage) | 1170.19 | 0.130245 | 979.126ms | 11812 | 4890 | 768722 | 9626.48 | 0.0332813 | 2.106 | 2(Loss) | true |
| Glaze | 874.88 | 0.131082 | 1315.95ms | 11812 | 4890 | 1.39298e+06 | 12875.8 | 0.155935 | 2.8197 | 3(Loss) | true |
| simdjson (ondemand) | 576.679 | 0.259179 | 1998.1ms | 11812 | 640 | 1.64043e+06 | 19533.9 | 0.138573 | 4.28337 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1552.69 | 0.120385 | 838.501ms | 11812 | 40 | 3051.28 | 7255 | 0.0689655 | 1.59093 | 1(Win) | true |
| Jsonifier (two-stage) | 1314.45 | 0.0504736 | 964.236ms | 11812 | 160 | 2993.71 | 8570 | 0.02918 | 1.87753 | 2(Loss) | true |
| Glaze | 991.448 | 0.123513 | 1243.81ms | 11812 | 4890 | 963036 | 11362 | 0.0047244 | 2.49103 | 3(Loss) | true |
| simdjson (ondemand) | 626.693 | 0.806317 | 1938.65ms | 11812 | 160 | 3.36101e+06 | 17975 | 0.195095 | 3.94622 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8632.03 | 0.187898 | 260.124ms | 11812 | 80 | 481.013 | 1305 | 0.191205 | 0.280501 | 1(Win) | true |
| Glaze | 2890.26 | 0.282971 | 393.103ms | 11812 | 40 | 4865.38 | 3897.5 | 0.0213858 | 0.850413 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE DID NOT CONVERGE | 3769.22 | 6.5952 | 262.923ms | 11812 | 2560 | 9.94584e+07 | 2988.63 | 2.09981 | 0.647847 | -(Tie) | false |
| Glaze STATISTICAL TIE | 3342.67 | 0.242284 | 372.098ms | 11812 | 40 | 2666.67 | 3370 | 1.26953 | 0.734626 | 1(Tie) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2359.26 | 0.12303 | 1079.77ms | 25388 | 80 | 12753.2 | 10262.5 | 0.0975372 | 1.04463 | 1(Win) | true |
| Jsonifier | 2310.99 | 0.13781 | 1102.28ms | 25388 | 4890 | 1.01937e+06 | 10476.9 | 0.0658093 | 1.06668 | 2(Loss) | true |
| Glaze | 1523.96 | 0.295732 | 1654.9ms | 25388 | 40 | 88301.3 | 15887.5 | 0.036703 | 1.61944 | 3(Loss) | true |
| simdjson (ondemand) | 1163.78 | 0.109254 | 2120.63ms | 25388 | 4890 | 2.52638e+06 | 20804.5 | 0.315055 | 2.12288 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2514.87 | 0.123279 | 1082.16ms | 25388 | 40 | 5634.62 | 9627.5 | 0.439504 | 0.981426 | 1(Win) | true |
| Jsonifier | 2412.11 | 0.407528 | 1165.22ms | 25388 | 640 | 1.07093e+06 | 10037.7 | 0.447854 | 1.02346 | 2(Loss) | true |
| Glaze | 1616.01 | 0.406327 | 1587.06ms | 25388 | 320 | 1.18596e+06 | 14982.5 | 0.51153 | 1.52855 | 3(Loss) | true |
| simdjson (ondemand) | 1194.6 | 0.203104 | 2178.74ms | 25388 | 1280 | 2.169e+06 | 20267.8 | 0.0808818 | 2.06952 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13926.2 | 0.293127 | 229.666ms | 31235 | 4890 | 192238 | 2139 | 0.0833011 | 0.175294 | 1(Win) | true |
| Glaze | 3876.85 | 0.137554 | 788.505ms | 31235 | 4890 | 546234 | 7683.56 | 0.314711 | 0.636285 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15295.5 | 0.410598 | 206.097ms | 31235 | 40 | 2557.69 | 1947.5 | 0.0428082 | 0.159774 | 1(Win) | true |
| Glaze | 4369.88 | 0.299104 | 729.314ms | 31235 | 30 | 12471.3 | 6816.67 | 0.0978953 | 0.564363 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1593.42 | 0.435935 | 6697.78ms | 108313 | 80 | 6.38905e+06 | 64826.2 | 0.428155 | 1.55309 | 1(Win) | true |
| Jsonifier (two-stage) | 1183.95 | 0.0929761 | 8824.98ms | 108313 | 2560 | 1.68452e+07 | 87246.1 | 0.0320676 | 2.09049 | 2(Loss) | true |
| Glaze | 957.48 | 0.796773 | 5646.5ms | 108313 | 160 | 1.1822e+08 | 107882 | 0.657787 | 2.58501 | 3(Loss) | true |
| simdjson (ondemand) | 780.224 | 0.33572 | 6902.23ms | 108313 | 160 | 3.16079e+07 | 132392 | 0.0344502 | 3.1725 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1889.51 | 0.142757 | 5892.62ms | 108313 | 1280 | 7.7959e+06 | 54667.8 | 0.0122886 | 1.30966 | 1(Win) | true |
| Jsonifier (two-stage) | 1340.63 | 0.107364 | 8125.1ms | 108313 | 2560 | 1.75187e+07 | 77050.1 | 0.0499628 | 1.8461 | 2(Loss) | true |
| Glaze | 1047.78 | 0.216888 | 5281.37ms | 108313 | 320 | 1.463e+07 | 98585.3 | 0.311888 | 2.36226 | 3(Loss) | true |
| simdjson (ondemand) | 875.922 | 0.0971995 | 6294.81ms | 108313 | 1280 | 1.68178e+07 | 117928 | 0.119788 | 2.8259 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14744.5 | 0.232295 | 722.388ms | 108313 | 4890 | 1.29506e+06 | 7005.71 | 0.0456666 | 0.167216 | 1(Win) | true |
| Glaze | 3211.47 | 0.0711651 | 3262.27ms | 108313 | 4890 | 2.5621e+06 | 32164.5 | 0.0459488 | 0.77025 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14563.7 | 0.259196 | 768.032ms | 108313 | 2560 | 865198 | 7092.66 | 0.105631 | 0.169347 | 1(Win) | true |
| Glaze | 3403.26 | 0.0914259 | 3103.86ms | 108313 | 2560 | 1.97129e+06 | 30351.9 | 0.197419 | 0.726762 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1959.04 | 0.119113 | 9058.38ms | 183677 | 1280 | 1.45194e+07 | 89415.2 | 0.0646106 | 1.26341 | 1(Win) | true |
| Jsonifier | 1741.4 | 0.107628 | 5255.81ms | 183677 | 1280 | 1.50028e+07 | 100590 | 0.217238 | 1.42132 | 2(Loss) | true |
| Glaze | 1408.58 | 0.178288 | 6444.27ms | 183677 | 640 | 3.14612e+07 | 124358 | 0.537743 | 1.75721 | 3(Loss) | true |
| simdjson (ondemand) | 1243.23 | 0.144803 | 7337.02ms | 183677 | 640 | 2.66405e+07 | 140898 | 0.197117 | 1.99103 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2196.61 | 0.0930019 | 8448.64ms | 183677 | 2560 | 1.40809e+07 | 79744.8 | 0.307457 | 1.12669 | 1(Win) | true |
| Jsonifier | 1922.51 | 0.069507 | 9562.2ms | 183677 | 4890 | 1.96128e+07 | 91114.2 | 0.0408875 | 1.2874 | 2(Loss) | true |
| Glaze | 1586.46 | 0.223395 | 5926.97ms | 183677 | 320 | 1.94691e+07 | 110414 | 0.235749 | 1.56017 | 3(Loss) | true |
| simdjson (ondemand) | 1389.56 | 0.613979 | 7014.84ms | 183677 | 30 | 1.79714e+07 | 126060 | 0.087184 | 1.78142 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14662.5 | 0.151365 | 1425.68ms | 213963 | 4890 | 2.1698e+06 | 13916.5 | 0.0917014 | 0.168493 | 1(Win) | true |
| Glaze | 3666.81 | 0.186806 | 5586.55ms | 213963 | 2560 | 2.76645e+07 | 55648 | 0.013195 | 0.674857 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15145.7 | 0.0593534 | 1402.57ms | 213963 | 40 | 2557.69 | 13472.5 | 0.179057 | 0.163001 | 1(Win) | true |
| Glaze | 3941.88 | 0.121438 | 5244.01ms | 213963 | 1280 | 5.05815e+06 | 51764.9 | 0.0550564 | 0.627729 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 650.083 | 0.391932 | 8568.03ms | 1834197 | 80 | 8.89747e+09 | 2.69078e+06 | 0.162811 | 3.80826 | 1(Win) | true |
| Jsonifier (two-stage) | 578.02 | 0.445587 | 9521.22ms | 1834197 | 160 | 2.90932e+10 | 3.02624e+06 | 2.47935 | 4.28299 | 2(Loss) | true |
| Glaze | 193.815 | 0.494925 | 6399.92ms | 1834197 | 30 | 5.98571e+10 | 9.02522e+06 | 1.09784 | 12.7733 | 3(Loss) | true |
| simdjson (ondemand) | 127.282 | 0.439616 | 9618.91ms | 1834197 | 30 | 1.09504e+11 | 1.3743e+07 | 2.14685 | 19.451 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 735.112 | 0.349063 | 8663.44ms | 1834197 | 80 | 5.51927e+09 | 2.37954e+06 | 1.22945 | 3.36784 | 1(Win) | true |
| Jsonifier (two-stage) | 670.947 | 0.131782 | 9408.64ms | 1834197 | 30 | 3.54119e+08 | 2.6071e+06 | 0.0763995 | 3.68991 | 2(Loss) | true |
| Glaze | 212.109 | 1.21825 | 6088.41ms | 1834197 | 40 | 4.03741e+11 | 8.24682e+06 | 0.812021 | 11.6721 | 3(Loss) | true |
| simdjson (ondemand) | 134.557 | 0.159484 | 9417.42ms | 1834197 | 40 | 1.71938e+10 | 1.29999e+07 | 1.72562 | 18.3994 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 877.05 | 0.439782 | 6232.81ms | 1834197 | 30 | 2.30802e+09 | 1.99444e+06 | 0.53212 | 2.8227 | 1(Win) | true |
| Glaze | 612.971 | 0.638143 | 8798.7ms | 1833577 | 160 | 5.30243e+10 | 2.85272e+06 | 1.56377 | 4.03892 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1006.63 | 0.130931 | 5459.93ms | 1834197 | 30 | 1.55294e+08 | 1.7377e+06 | 0.133332 | 2.45947 | 1(Win) | true |
| Glaze | 768.652 | 0.110145 | 7153.14ms | 1833577 | 30 | 1.88359e+08 | 2.27494e+06 | 0.416003 | 3.22095 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2195.69 | 0.14199 | 9972.43ms | 7351818 | 30 | 6.16716e+08 | 3.19319e+06 | 0.914805 | 1.12756 | 1(Win) | true |
| Jsonifier | 2073.22 | 0.12425 | 5830.07ms | 7351818 | 80 | 1.41249e+09 | 3.38182e+06 | 0.117882 | 1.19416 | 2(Loss) | true |
| Glaze | 751.788 | 0.49546 | 6574.88ms | 7351818 | 40 | 8.54038e+10 | 9.32609e+06 | 1.74955 | 3.29316 | 3(Loss) | true |
| simdjson (ondemand) | 483.606 | 1.53967 | 10044.6ms | 7351818 | 30 | 1.4948e+12 | 1.44978e+07 | 0.283992 | 5.11937 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2412.56 | 0.207702 | 10116ms | 7351818 | 160 | 5.82954e+09 | 2.90614e+06 | 0.570004 | 1.02619 | 1(Win) | true |
| Jsonifier | 2228.33 | 0.643952 | 5148.69ms | 7351818 | 40 | 1.64209e+10 | 3.14641e+06 | 1.30016 | 1.11104 | 2(Loss) | true |
| Glaze DID NOT CONVERGE | 788.731 | 0.345059 | 6554.56ms | 7351818 | 30 | 2.82254e+10 | 8.88927e+06 | 2.66047 | 3.13894 | -(Loss) | false |
| simdjson (ondemand) | 511.344 | 0.159852 | 9933.79ms | 7351818 | 40 | 1.92159e+10 | 1.37114e+07 | 0.343164 | 4.84169 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2279.6 | 0.0671176 | 6315.88ms | 9930848 | 80 | 6.22038e+08 | 4.15458e+06 | 0.284803 | 1.08605 | 1(Win) | true |
| Glaze | 1750.21 | 0.0875846 | 8187.34ms | 9930228 | 80 | 1.79673e+09 | 5.41089e+06 | 0.596718 | 1.41456 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3599.52 | 0.0746663 | 8285.92ms | 9930848 | 30 | 1.15785e+08 | 2.63113e+06 | 0.0882239 | 0.687811 | 1(Win) | true |
| Glaze | 3521.26 | 0.0558385 | 8458.45ms | 9930228 | 30 | 6.76569e+07 | 2.68944e+06 | 0.00470956 | 0.703099 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 670.793 | 0.221291 | 8308.36ms | 1834197 | 30 | 9.98999e+08 | 2.6077e+06 | 0.194429 | 3.69081 | 1(Win) | true |
| Jsonifier (two-stage) | 613.668 | 0.488185 | 8877.87ms | 1834197 | 80 | 1.54911e+10 | 2.85044e+06 | 0.339871 | 4.03435 | 2(Loss) | true |
| simdjson (ondemand) | 219.451 | 0.605732 | 5656.91ms | 1834197 | 30 | 6.99355e+10 | 7.9709e+06 | 0.421884 | 11.2818 | 3(Loss) | true |
| Glaze | 205.811 | 0.717272 | 5961.15ms | 1834197 | 30 | 1.11492e+11 | 8.49918e+06 | 1.60944 | 12.0291 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 764.218 | 0.0996029 | 8241.1ms | 1834197 | 40 | 2.07903e+08 | 2.28891e+06 | 0.1685 | 3.23959 | 1(Win) | true |
| Jsonifier (two-stage) | 699.019 | 0.139936 | 8923.15ms | 1834197 | 30 | 3.67873e+08 | 2.5024e+06 | 0.293511 | 3.54176 | 2(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 233.567 | 0.191074 | 5556.65ms | 1834197 | 40 | 8.19091e+09 | 7.4892e+06 | 3.3133 | 10.6 | -(Loss) | false |
| Glaze | 216.434 | 0.501189 | 5990.39ms | 1834197 | 40 | 6.56305e+10 | 8.08204e+06 | 0.171948 | 11.439 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 894.602 | 0.0662479 | 6145.25ms | 1834197 | 40 | 6.71175e+07 | 1.95531e+06 | 0.104265 | 2.76739 | 1(Win) | true |
| Glaze | 626.183 | 0.10695 | 8776.36ms | 1833577 | 30 | 2.67595e+08 | 2.79253e+06 | 0.0233903 | 3.95369 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1008.04 | 0.0464768 | 5439.22ms | 1834197 | 160 | 1.04071e+08 | 1.73528e+06 | 0.047205 | 2.45601 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 773.168 | 0.0767822 | 7091.93ms | 1833577 | 160 | 4.82495e+08 | 2.26165e+06 | 4.72657 | 3.20213 | -(Loss) | false |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2247.83 | 0.232921 | 9896.86ms | 7351818 | 30 | 1.58344e+09 | 3.11911e+06 | 0.329165 | 1.10141 | 1(Win) | true |
| Jsonifier | 2112.04 | 0.206685 | 5025.67ms | 7351818 | 80 | 3.76612e+09 | 3.31965e+06 | 0.353901 | 1.17222 | 2(Loss) | true |
| simdjson (ondemand) | 820.701 | 0.370344 | 6042.15ms | 7351818 | 30 | 3.00297e+10 | 8.54299e+06 | 0.118826 | 3.01671 | 3(Loss) | true |
| Glaze | 753.769 | 0.499693 | 6524.24ms | 7351818 | 40 | 8.64132e+10 | 9.30158e+06 | 0.00154994 | 3.28457 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2513.31 | 0.0910858 | 9891.21ms | 7351818 | 40 | 2.58261e+08 | 2.78964e+06 | 0.239896 | 0.985066 | 1(Win) | true |
| Jsonifier | 2341.61 | 0.341607 | 5014.73ms | 7351818 | 80 | 8.36957e+09 | 2.9942e+06 | 0.538167 | 1.0573 | 2(Loss) | true |
| simdjson (ondemand) | 866.532 | 0.0782017 | 5972.67ms | 7351818 | 40 | 1.60145e+09 | 8.09115e+06 | 1.87193 | 2.85715 | 3(Loss) | true |
| Glaze | 785.618 | 0.46406 | 6533.1ms | 7351818 | 30 | 5.1456e+10 | 8.92449e+06 | 2.09433 | 3.15142 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2713.68 | 0.0566221 | 5289.66ms | 9930848 | 80 | 3.12405e+08 | 3.49002e+06 | 0.547449 | 0.91232 | 1(Win) | true |
| Glaze | 1326.1 | 0.0432954 | 5053.23ms | 9930228 | 40 | 3.82393e+08 | 7.1414e+06 | 0.710738 | 1.86694 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4293.27 | 0.0890569 | 6958.54ms | 9930848 | 30 | 1.15785e+08 | 2.20596e+06 | 0.0759484 | 0.576667 | 1(Win) | true |
| Glaze | 3510.97 | 0.035286 | 8444.31ms | 9930228 | 160 | 1.4494e+08 | 2.69732e+06 | 0.102243 | 0.705154 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 738.464 | 0.402122 | 7674.45ms | 461466 | 160 | 9.18878e+08 | 595951 | 0.72629 | 3.35235 | 1(Win) | true |
| Jsonifier (two-stage) | 682.959 | 0.238993 | 8353.44ms | 461466 | 40 | 9.4868e+07 | 644385 | 0.25772 | 3.62487 | 2(Loss) | true |
| Glaze | 662.776 | 0.245855 | 8734.46ms | 461466 | 40 | 1.06602e+08 | 664008 | 0.12622 | 3.73532 | 3(Loss) | true |
| simdjson (ondemand) | 521.725 | 0.169197 | 5372.2ms | 461466 | 40 | 8.14783e+07 | 843525 | 0.727506 | 4.74511 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 948.517 | 0.281587 | 7096.51ms | 461466 | 40 | 6.82768e+07 | 463975 | 0.226867 | 2.60999 | 1(Win) | true |
| Jsonifier (two-stage) | 854.708 | 0.188906 | 7736.93ms | 461466 | 80 | 7.56875e+07 | 514899 | 0.175341 | 2.89647 | 2(Loss) | true |
| Glaze | 820.938 | 0.205893 | 8148.13ms | 461466 | 40 | 4.87309e+07 | 536080 | 0.029216 | 3.0157 | 3(Loss) | true |
| simdjson (ondemand) | 636.092 | 0.107286 | 9989.51ms | 461466 | 160 | 8.81543e+07 | 691862 | 0.158198 | 3.89199 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3504.79 | 0.099526 | 6488.95ms | 461466 | 2560 | 3.99824e+07 | 125568 | 0.243237 | 0.705908 | 1(Win) | true |
| Glaze | 2805.54 | 0.267514 | 8176.8ms | 461466 | 160 | 2.81747e+07 | 156864 | 0.0183314 | 0.882246 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10744.3 | 0.0816044 | 4076.64ms | 461466 | 30 | 33517.2 | 40960 | 0.081314 | 0.230257 | 1(Win) | true |
| Glaze | 2936.83 | 0.23349 | 8209.74ms | 461466 | 2560 | 3.13397e+08 | 149851 | 0.302068 | 0.842859 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1064.38 | 0.294236 | 8479.15ms | 728486 | 30 | 1.10652e+08 | 652717 | 0.0954072 | 2.32597 | 1(Win) | true |
| Jsonifier | 1034.21 | 0.347105 | 8608.99ms | 728486 | 160 | 8.699e+08 | 671759 | 0.99346 | 2.39379 | 2(Loss) | true |
| Glaze | 963.011 | 0.1247 | 9328.22ms | 728486 | 160 | 1.29488e+08 | 721423 | 1.15122 | 2.57073 | 3(Loss) | true |
| simdjson (ondemand) | 787.439 | 0.153618 | 5612.97ms | 728486 | 320 | 5.87816e+08 | 882276 | 0.231921 | 3.14395 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1320.44 | 0.0975825 | 7959.49ms | 728486 | 320 | 8.4353e+07 | 526142 | 0.0939315 | 1.87486 | 1(Win) | true |
| Jsonifier | 1293.75 | 0.166758 | 7980.63ms | 728486 | 80 | 6.4151e+07 | 536996 | 0.338434 | 1.91356 | 2(Loss) | true |
| Glaze | 1179.8 | 0.308241 | 8805.86ms | 728486 | 30 | 9.88383e+07 | 588860 | 0.192093 | 2.09844 | 3(Loss) | true |
| simdjson (ondemand) | 951.633 | 0.109585 | 5217.76ms | 728486 | 160 | 1.02406e+08 | 730049 | 0.0441556 | 2.60151 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3734.72 | 0.514224 | 5504.63ms | 837491 | 80 | 9.6747e+07 | 213856 | 0.41496 | 0.662615 | 1(Win) | true |
| Glaze | 2253.71 | 0.326043 | 9181.28ms | 837491 | 40 | 5.3404e+07 | 354390 | 0.213058 | 1.0982 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12360 | 0.102341 | 6546.98ms | 837491 | 2560 | 1.11959e+07 | 64619.1 | 0.0438678 | 0.200215 | 1(Win) | true |
| Glaze | 3723.07 | 0.173447 | 5604.33ms | 837491 | 160 | 2.21519e+07 | 214526 | 0.124557 | 0.664895 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8545.29 | 0.233508 | 5228.56ms | 466906 | 640 | 9.47521e+06 | 52107.8 | 0.0868836 | 0.289548 | 1(Win) | true |
| Jsonifier | 8414.28 | 0.229677 | 5289.35ms | 466906 | 1280 | 1.8909e+07 | 52919.1 | 0.0497764 | 0.294078 | 2(Loss) | true |
| simdjson (ondemand) | 3226.42 | 0.260449 | 7066.32ms | 466906 | 160 | 2.06719e+07 | 138009 | 0.0285388 | 0.767198 | 3(Loss) | true |
| Glaze | 2981.14 | 0.131664 | 7687.29ms | 466906 | 640 | 2.47517e+07 | 149364 | 0.00753135 | 0.830301 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9014.91 | 0.202674 | 5253.89ms | 466906 | 30 | 300644 | 49393.3 | 0.135153 | 0.274475 | 1(Win) | true |
| Jsonifier (two-stage) | 8900.6 | 0.225065 | 5233.94ms | 466906 | 640 | 8.11362e+06 | 50027.7 | 0.0696975 | 0.278009 | 2(Loss) | true |
| simdjson (ondemand) | 3337.47 | 0.170109 | 6945.94ms | 466906 | 320 | 1.64826e+07 | 133417 | 0.170928 | 0.741644 | 3(Loss) | true |
| Glaze | 3095.5 | 0.318406 | 7575.83ms | 466906 | 80 | 1.67823e+07 | 143846 | 0.247048 | 0.799694 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9842.87 | 0.0877166 | 6148.89ms | 631514 | 4890 | 1.40862e+07 | 61187.3 | 0.317714 | 0.251378 | 1(Win) | true |
| Jsonifier (two-stage) | 9711.57 | 0.0750946 | 6305.75ms | 631514 | 4890 | 1.06051e+07 | 62014.6 | 0.31147 | 0.254773 | 2(Loss) | true |
| simdjson (ondemand) | 3810.58 | 0.0672008 | 8131.09ms | 631514 | 1280 | 1.44392e+07 | 158049 | 0.0863313 | 0.649558 | 3(Loss) | true |
| Glaze | 3569.87 | 0.173197 | 8735.77ms | 631514 | 320 | 2.73206e+07 | 168706 | 0.0294608 | 0.69338 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10220.4 | 0.183732 | 6088.6ms | 631514 | 640 | 7.502e+06 | 58926.9 | 0.0487655 | 0.242078 | 1(Win) | true |
| Jsonifier (two-stage) | 10123.5 | 0.406438 | 6197.72ms | 631514 | 160 | 9.35439e+06 | 59491.2 | 0.0252074 | 0.244418 | 2(Loss) | true |
| simdjson (ondemand) | 3901.81 | 0.0769227 | 7970.23ms | 631514 | 1280 | 1.80448e+07 | 154354 | 0.0847577 | 0.634384 | 3(Loss) | true |
| Glaze | 3649.51 | 0.0582359 | 8591.75ms | 631514 | 2560 | 2.36439e+07 | 165025 | 0.0408863 | 0.678292 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1327.2 | 0.365496 | 8628.39ms | 466906 | 1280 | 1.92468e+09 | 335500 | 0.334061 | 1.86513 | 1(Win) | true |
| Jsonifier (two-stage) | 1189.49 | 0.333745 | 9866.31ms | 466906 | 40 | 6.24348e+07 | 374342 | 0.301657 | 2.08105 | 2(Loss) | true |
| Glaze | 1126.42 | 0.389504 | 5061.87ms | 466906 | 640 | 1.51727e+09 | 395302 | 0.292509 | 2.19768 | 3(Loss) | true |
| simdjson (ondemand) | 948.419 | 0.311773 | 6087.05ms | 466906 | 30 | 6.42772e+07 | 469493 | 0.0447091 | 2.61022 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1838.19 | 0.232159 | 7162.29ms | 466906 | 80 | 2.53011e+07 | 242236 | 0.179769 | 1.34673 | 1(Win) | true |
| Jsonifier (two-stage) | 1570.37 | 0.136185 | 8301.97ms | 466906 | 320 | 4.77162e+07 | 283549 | 0.0765443 | 1.57631 | 2(Loss) | true |
| Glaze | 1457.9 | 0.534632 | 9448.19ms | 466906 | 40 | 1.06653e+08 | 305422 | 0.206424 | 1.69804 | 3(Loss) | true |
| simdjson (ondemand) | 1174.2 | 0.118978 | 5266.57ms | 466906 | 640 | 1.30281e+08 | 379215 | 0.137389 | 2.1083 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 5119.46 | 0.112406 | 8981.75ms | 475954 | 2560 | 2.54274e+07 | 88662.8 | 0.182598 | 0.483375 | 1(Win) | true |
| Jsonifier | 4047.51 | 0.194925 | 5758.13ms | 475954 | 640 | 3.05821e+07 | 112144 | 0.162583 | 0.611153 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14551.2 | 0.117701 | 3146.83ms | 475954 | 4890 | 6.59179e+06 | 31193.6 | 0.283016 | 0.169945 | 1(Win) | true |
| Glaze | 5713.07 | 0.0847683 | 8031.52ms | 475954 | 2560 | 1.16118e+07 | 79450.3 | 0.000442492 | 0.43315 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1579.05 | 0.240982 | 5025.51ms | 631514 | 80 | 6.75823e+07 | 381405 | 0.159534 | 1.5677 | 1(Win) | true |
| Jsonifier | 1380.2 | 0.465522 | 5595.36ms | 631514 | 320 | 1.32041e+09 | 436355 | 0.489664 | 1.79361 | 2(Loss) | true |
| Glaze | 1336.56 | 0.55323 | 5721.74ms | 631514 | 320 | 1.98861e+09 | 450603 | 0.0641914 | 1.85219 | 3(Loss) | true |
| simdjson (ondemand) | 1213.45 | 0.329858 | 6308.95ms | 631514 | 640 | 1.71538e+09 | 496321 | 0.39482 | 2.04009 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2047.77 | 0.0878544 | 8533.38ms | 631514 | 1280 | 8.54555e+07 | 294105 | 0.0426165 | 1.20882 | 1(Win) | true |
| Jsonifier | 1737.83 | 0.127179 | 9887.09ms | 631514 | 320 | 6.21624e+07 | 346557 | 0.118976 | 1.42448 | 2(Loss) | true |
| Glaze | 1699.04 | 0.110796 | 10042.3ms | 631514 | 640 | 9.87163e+07 | 354471 | 0.147977 | 1.45706 | 3(Loss) | true |
| simdjson (ondemand) | 1514.57 | 0.340075 | 5529.55ms | 631514 | 40 | 7.31466e+07 | 397642 | 0.0672263 | 1.63452 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4226.24 | 0.200222 | 8381.23ms | 716365 | 320 | 3.35225e+07 | 161652 | 0.223586 | 0.58547 | 1(Win) | true |
| Glaze | 2793.79 | 0.111391 | 6274.51ms | 716365 | 1280 | 9.49715e+07 | 244535 | 0.0591015 | 0.885759 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11534.3 | 0.244329 | 5965.02ms | 716365 | 320 | 6.70174e+06 | 59230.3 | 0.133662 | 0.214529 | 1(Win) | true |
| Glaze | 5485.25 | 0.149236 | 6445.17ms | 716365 | 640 | 2.21107e+07 | 124548 | 0.13343 | 0.451228 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1036.68 | 0.281633 | 258.136ms | 2632 | 80 | 3719.94 | 2421.25 | 0.155119 | 2.3529 | 1(Win) | true |
| Jsonifier (two-stage) | 957.129 | 0.234735 | 277.206ms | 2632 | 80 | 3031.65 | 2622.5 | 0.0952381 | 2.55958 | 2(Loss) | true |
| Glaze | 860.534 | 0.202142 | 317.009ms | 2632 | 160 | 5562.5 | 2916.88 | 0.10725 | 2.84528 | 3(Loss) | true |
| simdjson (ondemand) | 685.467 | 0.210137 | 379.694ms | 2632 | 4890 | 289544 | 3661.84 | 0.204289 | 3.58281 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1390.14 | 0.191743 | 232.831ms | 2632 | 160 | 1917.85 | 1805.62 | 0.103734 | 1.75461 | 1(Win) | true |
| Jsonifier | 1364.17 | 0.426339 | 233.063ms | 2632 | 40 | 2461.54 | 1840 | 0.719424 | 1.80154 | 2(Loss) | true |
| Jsonifier (two-stage) | 1274.96 | 0.186712 | 242.292ms | 2632 | 160 | 2161.95 | 1968.75 | 0.0634518 | 1.9151 | 3(Loss) | true |
| simdjson (ondemand) | 1188.37 | 0.0940077 | 253.021ms | 2632 | 320 | 1261.66 | 2112.19 | 0.162482 | 2.06216 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10337.5 | 0.806147 | 27.8069ms | 2632 | 640 | 2452.17 | 242.812 | 0.384615 | 0.214391 | 1(Win) | true |
| Glaze | 3697.65 | 0.172939 | 71.9461ms | 2632 | 1280 | 1764.07 | 678.828 | 0.0115075 | 0.641024 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11516.5 | 0.25185 | 24.9624ms | 2632 | 4890 | 1473.42 | 217.955 | 0.238722 | 0.189399 | 1(Win) | true |
| Glaze | 4327.71 | 0.386133 | 61.5238ms | 2632 | 320 | 1605.02 | 580 | 0.107875 | 0.541828 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1189.78 | 0.259221 | 283.083ms | 3370 | 80 | 3922.47 | 2701.25 | 0.0462963 | 2.06099 | 1(Win) | true |
| Jsonifier | 1106.33 | 0.23128 | 301.637ms | 3370 | 4890 | 220736 | 2904.99 | 0.759736 | 2.21648 | 2(Loss) | true |
| Glaze | 1041.95 | 0.234183 | 321.997ms | 3370 | 4890 | 255145 | 3084.5 | 0.0420294 | 2.35517 | 3(Loss) | true |
| simdjson (ondemand) | 853.196 | 0.295014 | 390.693ms | 3370 | 1280 | 158073 | 3766.88 | 0.0581058 | 2.88121 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1632.71 | 0.410868 | 243.318ms | 3370 | 1280 | 83725.5 | 1968.44 | 0.655161 | 1.49169 | 1(Win) | true |
| Jsonifier (two-stage) | 1600.94 | 0.129147 | 238.618ms | 3370 | 160 | 1075.47 | 2007.5 | 0.124378 | 1.52978 | 2(Loss) | true |
| Jsonifier STATISTICAL TIE | 1437.98 | 0.341728 | 271.084ms | 3370 | 40 | 2333.33 | 2235 | 0.223214 | 1.71503 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1433.57 | 0.123212 | 265.313ms | 3370 | 320 | 2441.61 | 2241.88 | 0.0837054 | 1.70777 | 3(Tie) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11128.7 | 0.293012 | 34.8729ms | 3643 | 1280 | 1071.05 | 312.188 | 0.050025 | 0.204182 | 1(Win) | true |
| Glaze | 3509.24 | 0.348825 | 105.184ms | 3682 | 160 | 1949.29 | 1000.62 | 0.062422 | 0.686332 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12335.7 | 0.384372 | 31.4341ms | 3643 | 1280 | 1500.04 | 281.641 | 0.0831486 | 0.182252 | 1(Win) | true |
| Glaze | 3936.65 | 0.236961 | 92.412ms | 3682 | 4890 | 21846.1 | 891.984 | 0.284798 | 0.607769 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 601.734 | 0.174214 | 759.202ms | 4630 | 4890 | 799153 | 7337.98 | 0.097231 | 4.09771 | 1(Win) | true |
| Jsonifier (two-stage) | 569.009 | 0.21932 | 798.087ms | 4630 | 30 | 8689.66 | 7760 | 0.0859845 | 4.33256 | 2(Loss) | true |
| Glaze | 174.614 | 0.196183 | 2552.5ms | 4630 | 1280 | 3.15018e+06 | 25287.3 | 0.256777 | 14.1612 | 3(Loss) | true |
| simdjson (ondemand) | 172.171 | 0.0840319 | 2586.48ms | 4630 | 4890 | 2.27112e+06 | 25646.1 | 0.00883217 | 14.3626 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 772.15 | 0.190103 | 729.215ms | 4630 | 4890 | 577894 | 5718.47 | 0.292353 | 3.1922 | 1(Win) | true |
| Jsonifier (two-stage) | 724.151 | 0.171077 | 787.767ms | 4630 | 40 | 4352.56 | 6097.5 | 0.0136687 | 3.39908 | 2(Loss) | true |
| Glaze | 187.03 | 0.0920126 | 2534.11ms | 4630 | 4890 | 2.30751e+06 | 23608.6 | 0.083751 | 13.2223 | 3(Loss) | true |
| simdjson (ondemand) | 186.459 | 0.11903 | 2544.88ms | 4630 | 2560 | 2.03398e+06 | 23680.8 | 0.0179832 | 13.2637 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1843.46 | 0.293347 | 251.483ms | 4630 | 2560 | 126386 | 2395.23 | 0.0652763 | 1.32922 | 1(Win) | true |
| Glaze | 1135.95 | 0.176457 | 400.64ms | 4630 | 4890 | 230056 | 3887.08 | 0.0111932 | 2.1642 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1880.44 | 0.16875 | 249.327ms | 4630 | 160 | 2512.19 | 2348.12 | 0.0797872 | 1.30293 | 1(Win) | true |
| Glaze | 1238.14 | 0.105152 | 380.656ms | 4630 | 160 | 2250 | 3566.25 | 0.174948 | 1.98555 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1339.71 | 0.149775 | 855.409ms | 11579 | 40 | 6096.15 | 8242.5 | 0.192464 | 1.84177 | 1(Win) | true |
| Jsonifier | 1307.85 | 0.157404 | 880.039ms | 11579 | 30 | 5298.85 | 8443.33 | 0.157667 | 1.88713 | 2(Loss) | true |
| simdjson (ondemand) | 415.643 | 0.161157 | 2706.29ms | 11579 | 1280 | 2.34645e+06 | 26567.5 | 0.159636 | 5.94952 | 3(Loss) | true |
| Glaze | 411.987 | 0.214386 | 2713.29ms | 11579 | 640 | 2.11324e+06 | 26803.3 | 0.298162 | 6.00216 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1680.84 | 0.146287 | 838.832ms | 11579 | 4890 | 451656 | 6569.69 | 0.36071 | 1.46672 | 1(Win) | true |
| Jsonifier | 1592.2 | 0.178191 | 853.232ms | 11579 | 4890 | 746837 | 6935.42 | 0.174191 | 1.54895 | 2(Loss) | true |
| simdjson (ondemand) | 454.521 | 0.206041 | 2666.26ms | 11579 | 640 | 1.6037e+06 | 24295 | 0.0629877 | 5.441 | 3(Loss) | true |
| Glaze | 446.842 | 0.0697691 | 2703.61ms | 11579 | 40 | 11891 | 24712.5 | 0.312626 | 5.53484 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5023.45 | 0.129701 | 297.281ms | 14795 | 80 | 1061.71 | 2808.75 | 0.0445236 | 0.488837 | 1(Win) | true |
| Glaze | 3063.98 | 0.189663 | 476.121ms | 14795 | 40 | 3051.28 | 4605 | 0.0362056 | 0.804647 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5256.84 | 0.220061 | 271.51ms | 14795 | 4890 | 170598 | 2684.05 | 0.116792 | 0.466346 | 1(Win) | true |
| Glaze | 3451.89 | 0.156394 | 425.516ms | 14795 | 40 | 1634.62 | 4087.5 | 0.223759 | 0.712957 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 717.624 | 0.181269 | 432.203ms | 3223 | 4890 | 294770 | 4283.15 | 0.0261099 | 3.41447 | 1(Win) | true |
| Jsonifier (two-stage) | 636.391 | 0.191672 | 500.561ms | 3223 | 4890 | 419081 | 4829.88 | 0.112406 | 3.85473 | 2(Loss) | true |
| Glaze | 460.729 | 0.266155 | 681.422ms | 3223 | 2560 | 807124 | 6671.37 | 0.135074 | 5.33822 | 3(Loss) | true |
| simdjson (ondemand) | 425.94 | 0.363111 | 731.947ms | 3223 | 1280 | 878844 | 7216.25 | 0.319308 | 5.7909 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 992.699 | 0.236369 | 387.434ms | 3223 | 4890 | 261923 | 3096.3 | 0.0141865 | 2.47265 | 1(Win) | true |
| Jsonifier (two-stage) | 857.227 | 0.181914 | 427.596ms | 3223 | 4890 | 208051 | 3585.62 | 0.342119 | 2.86629 | 2(Loss) | true |
| Glaze | 585.187 | 0.15224 | 600.556ms | 3223 | 40 | 2557.69 | 5252.5 | 0.268987 | 4.21154 | 3(Loss) | true |
| simdjson (ondemand) | 502.956 | 0.096516 | 696.185ms | 3223 | 80 | 2783.23 | 6111.25 | 0.142974 | 4.89435 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6630.14 | 0.292169 | 49.6941ms | 3223 | 1280 | 2348.29 | 463.594 | 0.270362 | 0.351258 | 1(Win) | true |
| Glaze | 2483.79 | 0.626438 | 128.731ms | 3223 | 40 | 2403.85 | 1237.5 | 0.0673854 | 0.980329 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8122.76 | 0.350685 | 40.8316ms | 3223 | 4890 | 8611.08 | 378.405 | 0.0705009 | 0.283436 | 1(Win) | true |
| Glaze | 3105.64 | 0.481228 | 101.591ms | 3223 | 4890 | 110925 | 989.714 | 0.47058 | 0.773429 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1118.11 | 0.166051 | 512.414ms | 5839 | 4890 | 334425 | 4980.27 | 0.0761758 | 2.19501 | 1(Win) | true |
| Jsonifier | 1035.04 | 0.13769 | 555.213ms | 5839 | 160 | 8779.87 | 5380 | 0.0232288 | 2.37058 | 2(Loss) | true |
| Glaze | 752.324 | 0.143592 | 752.103ms | 5839 | 4890 | 552378 | 7401.74 | 0.0530662 | 3.27133 | 3(Loss) | true |
| simdjson (ondemand) | 744.849 | 0.225925 | 766.283ms | 5839 | 1280 | 365155 | 7476.02 | 0.0699666 | 3.31139 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1491.15 | 0.280174 | 451.185ms | 5839 | 2560 | 280240 | 3734.38 | 0.0376427 | 1.64802 | 1(Win) | true |
| Jsonifier | 1324.78 | 0.369327 | 502.425ms | 5839 | 30 | 7229.89 | 4203.33 | 0.158856 | 1.85487 | 2(Loss) | true |
| Glaze | 924.649 | 0.14841 | 674.487ms | 5839 | 4890 | 390626 | 6022.29 | 0.0367481 | 2.66608 | 3(Loss) | true |
| simdjson (ondemand) | 862.947 | 0.23678 | 727.252ms | 5839 | 1280 | 298819 | 6452.89 | 0.0157366 | 2.85703 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8290.17 | 0.165857 | 93.3021ms | 6938 | 320 | 560.737 | 798.125 | 0.234375 | 0.288006 | 1(Win) | true |
| Glaze | 3926.2 | 0.320863 | 173.584ms | 6960 | 2560 | 75327.5 | 1690.59 | 0.10848 | 0.620931 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9147.03 | 0.163558 | 76.5282ms | 6938 | 1280 | 1791.68 | 723.359 | 0.204786 | 0.261163 | 1(Win) | true |
| Glaze | 4593.48 | 0.273037 | 149.134ms | 6960 | 160 | 2490.57 | 1445 | 0.0865801 | 0.52891 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1017.74 | 0.203075 | 468.114ms | 4857 | 80 | 6833.86 | 4551.25 | 0.0274725 | 2.4137 | 1(Win) | true |
| Jsonifier (two-stage) | 830.851 | 0.238155 | 573.52ms | 4857 | 40 | 7051.28 | 5575 | 0.0299043 | 2.95879 | 2(Loss) | true |
| Glaze | 824.199 | 0.271802 | 588.263ms | 4857 | 40 | 9333.33 | 5620 | 0.118483 | 2.99131 | 3(Loss) | true |
| simdjson (ondemand) | 683.185 | 0.258868 | 703.274ms | 4857 | 30 | 9241.38 | 6780 | 0.04914 | 3.60531 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1512.16 | 0.222825 | 367.295ms | 4857 | 2560 | 119264 | 3063.16 | 0.239039 | 1.62338 | 1(Win) | true |
| Glaze | 1435.17 | 0.28675 | 394.409ms | 4857 | 160 | 13704.4 | 3227.5 | 0.0775194 | 1.71159 | 2(Loss) | true |
| Jsonifier (two-stage) | 1160.54 | 0.161894 | 465.433ms | 4857 | 80 | 3340.19 | 3991.25 | 0.281074 | 2.12154 | 3(Loss) | true |
| simdjson (ondemand) | 942.9 | 0.166008 | 532.158ms | 4857 | 40 | 2660.26 | 4912.5 | 0.0169607 | 2.60774 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8600.17 | 0.357563 | 58.2113ms | 4857 | 640 | 2373.61 | 538.594 | 0.144844 | 0.274369 | 1(Win) | true |
| Glaze | 3007.79 | 0.410035 | 150.393ms | 4857 | 80 | 3189.87 | 1540 | 0.645161 | 0.807173 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9453.05 | 1.13691 | 51.8598ms | 4857 | 30 | 931.034 | 490 | 0 | 0.246236 | 1(Win) | true |
| Glaze | 3715.47 | 0.559942 | 129.466ms | 4857 | 2560 | 124749 | 1246.68 | 0.0219285 | 0.650249 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1115.04 | 0.160065 | 616.773ms | 6701 | 80 | 6732.59 | 5731.25 | 0.326087 | 2.2099 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1113.54 | 0.218503 | 588.754ms | 6701 | 2560 | 402551 | 5738.95 | 0.00204201 | 2.21219 | 1(Tie) | true |
| Glaze | 1092.41 | 0.133859 | 607.122ms | 6701 | 160 | 9811.32 | 5850 | 0.106724 | 2.25569 | 3(Loss) | true |
| simdjson (ondemand) | 915.719 | 0.168496 | 730.634ms | 6701 | 80 | 11061.7 | 6978.75 | 0.0896379 | 2.68967 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1807.48 | 0.193192 | 412.016ms | 6701 | 160 | 7465.02 | 3535.62 | 0.301418 | 1.36049 | 1(Win) | true |
| Jsonifier (two-stage) | 1522.07 | 0.293075 | 475.313ms | 6701 | 2560 | 387618 | 4198.59 | 0.272783 | 1.61542 | 2(Loss) | true |
| Jsonifier | 1461.61 | 0.215229 | 546.89ms | 6701 | 4890 | 433041 | 4372.29 | 0.289976 | 1.68337 | 3(Loss) | true |
| simdjson (ondemand) | 1299.56 | 0.0817369 | 550.363ms | 6701 | 160 | 2584.91 | 4917.5 | 0.050813 | 1.89801 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8236.28 | 0.232277 | 90.0256ms | 7376 | 640 | 2518.68 | 854.062 | 0.146574 | 0.29202 | 1(Win) | true |
| Glaze | 3090.3 | 0.25013 | 224.03ms | 7376 | 80 | 2593.35 | 2276.25 | 0.382932 | 0.789142 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9065.63 | 0.45714 | 80.5523ms | 7376 | 4890 | 61525.3 | 775.93 | 0.501803 | 0.263601 | 1(Win) | true |
| Glaze | 3635.89 | 0.137746 | 199.345ms | 7376 | 320 | 2272.63 | 1934.69 | 0.0484809 | 0.67222 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1134.63 | 0.249492 | 145.689ms | 1691 | 4890 | 61489 | 1421.31 | 0.648486 | 2.13889 | 1(Win) | true |
| Jsonifier | 976.632 | 0.222627 | 178.182ms | 1691 | 320 | 4324.45 | 1651.25 | 0.15163 | 2.49647 | 2(Loss) | true |
| Jsonifier (two-stage) | 876.447 | 0.507445 | 189.988ms | 1691 | 40 | 3487.18 | 1840 | 0.180832 | 2.80557 | 3(Loss) | true |
| simdjson (ondemand) | 581.884 | 0.232556 | 290.04ms | 1691 | 4890 | 203132 | 2771.45 | 0.17249 | 4.2096 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1413.12 | 0.366949 | 145.836ms | 1691 | 4890 | 85753.1 | 1141.21 | 0.0517019 | 1.70461 | 1(Win) | true |
| Jsonifier | 1300.86 | 0.279548 | 155.833ms | 1691 | 320 | 3843.16 | 1239.69 | 0.176145 | 1.86412 | 2(Loss) | true |
| Jsonifier (two-stage) | 1132.27 | 0.277972 | 173.355ms | 1691 | 4890 | 76647.3 | 1424.27 | 0.209603 | 2.14595 | 3(Loss) | true |
| simdjson (ondemand) | 704.412 | 0.131889 | 269.465ms | 1691 | 160 | 1458.73 | 2289.38 | 0.0273075 | 3.47585 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11425.7 | 0.559617 | 20.3011ms | 1996 | 2560 | 2225.26 | 166.602 | 0.117371 | 0.184494 | 1(Win) | true |
| Glaze | 3655.7 | 0.225712 | 65.7812ms | 1996 | 1280 | 1768.07 | 520.703 | 0.165314 | 0.63529 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13486.4 | 0.498625 | 17.2248ms | 1996 | 4890 | 2422.09 | 141.145 | 0.21218 | 0.149706 | 1(Win) | true |
| Glaze | 4583.38 | 0.24245 | 45.3249ms | 1996 | 1280 | 1297.79 | 415.312 | 0.150716 | 0.499985 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1344.02 | 0.359836 | 158.853ms | 2158 | 80 | 2428.8 | 1531.25 | 0.0816993 | 1.81789 | 1(Win) | true |
| Jsonifier (two-stage) | 1106.14 | 0.314045 | 188.625ms | 2158 | 4890 | 166946 | 1860.55 | 0.227547 | 2.20455 | 2(Loss) | true |
| Jsonifier | 998.892 | 0.183933 | 221.501ms | 2158 | 320 | 4595.51 | 2060.31 | 0.0151699 | 2.44274 | 3(Loss) | true |
| simdjson (ondemand) | 740.454 | 0.322522 | 282.652ms | 2158 | 2560 | 205715 | 2779.41 | 0.144968 | 3.30936 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1710.57 | 0.249066 | 149.929ms | 2158 | 160 | 1436.71 | 1203.12 | 0.0519211 | 1.41608 | 1(Win) | true |
| Jsonifier (two-stage) | 1438.55 | 0.290677 | 174.414ms | 2158 | 160 | 2766.9 | 1430.62 | 0.13089 | 1.68393 | 2(Loss) | true |
| Jsonifier | 1272.84 | 0.258506 | 194.822ms | 2158 | 160 | 2795.2 | 1616.88 | 0.0386698 | 1.92011 | 3(Loss) | true |
| simdjson (ondemand) | 876.048 | 0.406531 | 262.798ms | 2158 | 1280 | 116747 | 2349.22 | 0.0133005 | 2.7918 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11448.1 | 0.570572 | 27.7714ms | 2866 | 1280 | 2375.29 | 238.75 | 0.456026 | 0.193262 | 1(Win) | true |
| Glaze | 3540.31 | 0.327335 | 80.8611ms | 2866 | 2560 | 16349.1 | 772.031 | 0.324873 | 0.67286 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13687.5 | 0.156495 | 23.1336ms | 2866 | 320 | 31.25 | 199.688 | 0.46729 | 0.157225 | 1(Win) | true |
| Glaze | 4432.27 | 1.12224 | 66.1464ms | 2866 | 30 | 1436.78 | 616.667 | 0.543478 | 0.528879 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1195.54 | 0.120026 | 359.14ms | 4390 | 160 | 2826.65 | 3501.88 | 0.0893176 | 2.04926 | 1(Win) | true |
| Jsonifier (two-stage) | 1038.38 | 0.169449 | 418.171ms | 4390 | 160 | 7468.16 | 4031.88 | 0.0464828 | 2.36569 | 2(Loss) | true |
| Glaze | 837.64 | 0.142783 | 518.935ms | 4390 | 320 | 16297.4 | 4998.12 | 0.162297 | 2.94041 | 3(Loss) | true |
| simdjson (ondemand) | 550.872 | 0.210695 | 791.381ms | 4390 | 40 | 10256.4 | 7600 | 0.0438404 | 4.47994 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1398.48 | 0.318392 | 347.416ms | 4390 | 2560 | 232586 | 2993.71 | 0.221002 | 1.75514 | 1(Win) | true |
| Jsonifier (two-stage) | 1191.92 | 0.2086 | 413.758ms | 4390 | 40 | 2147.44 | 3512.5 | 0.0237192 | 2.0733 | 2(Loss) | true |
| Glaze | 1000.24 | 0.167934 | 477.402ms | 4390 | 160 | 7905.27 | 4185.62 | 0.164523 | 2.45717 | 3(Loss) | true |
| simdjson (ondemand) | 617.801 | 0.288989 | 753.227ms | 4390 | 30 | 11505.7 | 6776.67 | 0.0984737 | 3.9947 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9132.39 | 0.601896 | 49.652ms | 4390 | 320 | 2436.42 | 458.438 | 0.204082 | 0.256207 | 1(Win) | true |
| Glaze | 2917.12 | 0.361991 | 147.225ms | 4390 | 2560 | 69096.9 | 1435.2 | 0.263315 | 0.829505 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9706.37 | 0.300686 | 46.4437ms | 4390 | 1280 | 2153.04 | 431.328 | 0.34296 | 0.239405 | 1(Win) | true |
| Glaze | 3326.02 | 0.318053 | 130.275ms | 4390 | 160 | 2564.47 | 1258.75 | 0.0994036 | 0.724375 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2067.39 | 0.179153 | 447.74ms | 9378 | 4890 | 293719 | 4326.01 | 0.144344 | 1.18943 | 1(Win) | true |
| Jsonifier | 2055.4 | 0.118796 | 456.47ms | 9378 | 160 | 4275.16 | 4351.25 | 0.0861079 | 1.19751 | 2(Loss) | true |
| Glaze | 1447 | 0.2071 | 628.999ms | 9378 | 2560 | 419453 | 6180.74 | 0.0347481 | 1.70301 | 3(Loss) | true |
| simdjson (ondemand) | 1086.06 | 0.266834 | 860.359ms | 9378 | 1280 | 618019 | 8234.84 | 0.168586 | 2.27228 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 2351.3 | 0.269296 | 437.723ms | 9378 | 2560 | 268599 | 3803.67 | 0.03904 | 1.04557 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 2342.01 | 0.0843173 | 446.356ms | 9378 | 160 | 1658.81 | 3818.75 | 0.262553 | 1.04977 | 1(Tie) | true |
| Glaze | 1703.94 | 0.105478 | 577.929ms | 9378 | 160 | 4904.09 | 5248.75 | 0.0476531 | 1.4444 | 3(Loss) | true |
| simdjson (ondemand) | 1215.09 | 0.19787 | 788.423ms | 9378 | 2560 | 543010 | 7360.43 | 0.115031 | 2.03039 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12705.5 | 0.384228 | 90.0469ms | 11521 | 4890 | 53986.3 | 864.765 | 0.0179794 | 0.18871 | 1(Win) | true |
| Glaze | 3685.46 | 0.239379 | 296.988ms | 11521 | 80 | 4074.37 | 2981.25 | 0.0419111 | 0.66429 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14748 | 0.373883 | 88.5653ms | 11521 | 320 | 2482.76 | 745 | 0.167504 | 0.162227 | 1(Win) | true |
| Glaze | 4473.19 | 0.238492 | 251.72ms | 11521 | 80 | 2745.25 | 2456.25 | 0.152439 | 0.544354 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1505.56 | 0.188057 | 309.47ms | 4669 | 80 | 2474.68 | 2957.5 | 0 | 1.62763 | 1(Win) | true |
| Jsonifier (two-stage) | 1129.14 | 0.149042 | 433.281ms | 4669 | 320 | 11054 | 3943.44 | 0.00792393 | 2.17584 | 2(Loss) | true |
| Glaze | 936.754 | 0.219453 | 496.109ms | 4669 | 30 | 3264.37 | 4753.33 | 0.209937 | 2.62727 | 3(Loss) | true |
| simdjson (ondemand) | 752.57 | 0.116965 | 625.945ms | 4669 | 30 | 1436.78 | 5916.67 | 0.339175 | 3.26767 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1612.02 | 0.0982926 | 291.247ms | 4669 | 320 | 2358.84 | 2762.19 | 0.0113148 | 1.52188 | 1(Win) | true |
| Jsonifier (two-stage) | 1181.68 | 0.0980741 | 404.754ms | 4669 | 160 | 2185.14 | 3768.12 | 0.0830013 | 2.07872 | 2(Loss) | true |
| Glaze | 1038.11 | 0.170495 | 453.533ms | 4669 | 4890 | 261512 | 4289.24 | 0.109502 | 2.3707 | 3(Loss) | true |
| simdjson (ondemand) | 755.346 | 0.337094 | 635.083ms | 4669 | 1280 | 505439 | 5894.92 | 0.0119262 | 3.26257 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11514.1 | 0.245384 | 42.3727ms | 4669 | 1280 | 1152.63 | 386.719 | 0.0404204 | 0.200229 | 1(Win) | true |
| Glaze | 2904.93 | 0.353743 | 156.564ms | 4669 | 2560 | 75265.2 | 1532.81 | 0.0918274 | 0.834128 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13454.8 | 0.552545 | 37.9411ms | 4669 | 640 | 2139.96 | 330.938 | 0.282486 | 0.169856 | 1(Win) | true |
| Glaze | 3392.54 | 0.21094 | 135.048ms | 4669 | 160 | 1226.42 | 1312.5 | 0 | 0.713473 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1852.92 | 0.104714 | 435.695ms | 7932 | 80 | 1462.03 | 4082.5 | 0.0612745 | 1.3258 | 1(Win) | true |
| Jsonifier | 1644.47 | 0.13482 | 473.509ms | 7932 | 40 | 1538.46 | 4600 | 0.0724113 | 1.49576 | 2(Loss) | true |
| Glaze | 1321.34 | 0.444273 | 585.042ms | 7932 | 1280 | 828034 | 5724.92 | 0.00136467 | 1.8641 | 3(Loss) | true |
| simdjson (ondemand) | 1199.45 | 0.16886 | 648.148ms | 7932 | 30 | 3402.3 | 6306.67 | 0 | 2.05706 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1967.37 | 0.145572 | 414.906ms | 7932 | 80 | 2506.33 | 3845 | 0.324044 | 1.24947 | 1(Win) | true |
| Jsonifier | 1717.91 | 0.17159 | 471.621ms | 7932 | 30 | 1712.64 | 4403.33 | 0 | 1.43261 | 2(Loss) | true |
| Glaze | 1475.83 | 0.069726 | 542.525ms | 7932 | 160 | 2043.63 | 5125.62 | 0.207722 | 1.66629 | 3(Loss) | true |
| simdjson (ondemand) | 1240.09 | 0.13614 | 670.036ms | 7932 | 30 | 2068.97 | 6100 | 0.109409 | 1.98692 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11579.8 | 0.178432 | 80.8445ms | 9249 | 1280 | 2364.52 | 761.719 | 0.0410088 | 0.206563 | 1(Win) | true |
| Glaze | 3576.21 | 0.299178 | 258.16ms | 9249 | 2560 | 139393 | 2466.45 | 0.0775439 | 0.683236 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12702.8 | 0.196413 | 73.4272ms | 9249 | 320 | 595.219 | 694.375 | 0.0899281 | 0.187751 | 1(Win) | true |
| Glaze | 4004.78 | 0.106129 | 229.482ms | 9249 | 160 | 874.214 | 2202.5 | 0.170551 | 0.610041 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 448.796 | 0.268801 | 1020.93ms | 4604 | 30 | 20747.1 | 9783.33 | 0.10211 | 5.49684 | 1(Win) | true |
| Jsonifier (two-stage) | 428.673 | 0.190166 | 1028.53ms | 4604 | 2560 | 971231 | 10242.6 | 0.109192 | 5.75403 | 2(Loss) | true |
| Glaze | 162.868 | 0.420386 | 2751.76ms | 4604 | 160 | 2.05502e+06 | 26958.8 | 0.302297 | 15.1762 | 3(Loss) | true |
| simdjson (ondemand) | 96.7022 | 0.232678 | 4569.22ms | 4604 | 640 | 7.14312e+06 | 45404.5 | 0.0615611 | 25.5872 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 569.576 | 0.126803 | 919.105ms | 4604 | 80 | 7643.99 | 7708.75 | 0.468044 | 4.32938 | 1(Win) | true |
| Jsonifier (two-stage) | 545.982 | 0.528224 | 956.532ms | 4604 | 640 | 1.15486e+06 | 8041.88 | 0.69651 | 4.51817 | 2(Loss) | true |
| Glaze | 176.662 | 0.454166 | 2700.05ms | 4604 | 160 | 2.0386e+06 | 24853.8 | 0.0502689 | 13.9966 | 3(Loss) | true |
| simdjson (ondemand) | 105.866 | 0.108632 | 4335.63ms | 4604 | 2560 | 5.19652e+06 | 41474.3 | 0.66682 | 23.3707 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1450.28 | 0.185579 | 311.315ms | 4604 | 80 | 2525.32 | 3027.5 | 0.0826446 | 1.69351 | 1(Win) | true |
| Glaze | 897.92 | 0.163794 | 506.471ms | 4604 | 4890 | 313690 | 4889.88 | 0.00547949 | 2.74128 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1514.69 | 0.189088 | 294.645ms | 4604 | 80 | 2403.48 | 2898.75 | 0.129199 | 1.61585 | 1(Win) | true |
| Glaze | 937.186 | 0.120672 | 475.207ms | 4604 | 80 | 2556.96 | 4685 | 0.10661 | 2.62456 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1617.08 | 0.126559 | 1109.87ms | 18245 | 80 | 14835.4 | 10760 | 0.43951 | 1.52612 | 1(Win) | true |
| Jsonifier | 1346.37 | 0.207403 | 1294.25ms | 18245 | 2560 | 1.83921e+06 | 12923.5 | 0.541122 | 1.83367 | 2(Loss) | true |
| Glaze | 587.868 | 0.373155 | 3023.55ms | 18245 | 160 | 1.95176e+06 | 29598.1 | 0.103362 | 4.20532 | 3(Loss) | true |
| simdjson (ondemand) | 383.696 | 0.0710587 | 4620.45ms | 18245 | 4890 | 5.07758e+06 | 45347.9 | 0.120448 | 6.44832 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1988.28 | 0.27183 | 1009.43ms | 18245 | 1280 | 724330 | 8751.17 | 0.0847382 | 1.24119 | 1(Win) | true |
| Jsonifier | 1679.11 | 0.118127 | 1216.32ms | 18245 | 40 | 5993.59 | 10362.5 | 0.185305 | 1.4689 | 2(Loss) | true |
| Glaze | 645.004 | 0.380071 | 2911.17ms | 18245 | 160 | 1.68195e+06 | 26976.2 | 0.447458 | 3.83419 | 3(Loss) | true |
| simdjson (ondemand) | 406.366 | 0.199612 | 4552.32ms | 18245 | 640 | 4.67525e+06 | 42818 | 0.0346791 | 6.08873 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5327.35 | 0.162753 | 448.675ms | 24579 | 40 | 2051.28 | 4400 | 0 | 0.461151 | 1(Win) | true |
| Glaze | 3423.48 | 0.166378 | 697.997ms | 24579 | 4890 | 634588 | 6846.93 | 0.0647792 | 0.720098 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5545.83 | 0.224977 | 446.086ms | 24579 | 30 | 2712.64 | 4226.67 | 0 | 0.443529 | 1(Win) | true |
| Glaze | 3827.39 | 0.0705501 | 621.846ms | 24579 | 160 | 2987.03 | 6124.38 | 0.477351 | 0.644055 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 515.116 | 0.165972 | 906.426ms | 4604 | 80 | 16011.1 | 8523.75 | 0.219491 | 4.79246 | 1(Win) | true |
| Jsonifier (two-stage) | 460.243 | 0.218204 | 979.188ms | 4604 | 40 | 17333.3 | 9540 | 0.0699301 | 5.36151 | 2(Loss) | true |
| simdjson (ondemand) | 183.731 | 0.120837 | 2464.38ms | 4604 | 2560 | 2.13474e+06 | 23897.5 | 0.0544612 | 13.4579 | 3(Loss) | true |
| Glaze | 162.754 | 0.128255 | 2734.73ms | 4604 | 2560 | 3.06477e+06 | 26977.7 | 0.080297 | 15.1939 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 638.186 | 0.17417 | 858.301ms | 4604 | 40 | 5743.59 | 6880 | 0.0969932 | 3.86849 | 1(Win) | true |
| Jsonifier (two-stage) | 608.624 | 0.172521 | 896.897ms | 4604 | 4890 | 757469 | 7214.17 | 0.427849 | 4.05123 | 2(Loss) | true |
| simdjson (ondemand) | 195.259 | 0.129229 | 2373.63ms | 4604 | 30 | 25333.3 | 22486.7 | 0.029656 | 12.6649 | 3(Loss) | true |
| Glaze | 179.584 | 0.258787 | 2677.88ms | 4604 | 320 | 1.28107e+06 | 24449.4 | 0.161307 | 13.7727 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1436.51 | 0.262625 | 317.481ms | 4604 | 4890 | 315090 | 3056.52 | 0.128909 | 1.70884 | 1(Win) | true |
| Glaze | 848.721 | 0.292101 | 509.82ms | 4604 | 30 | 6850.57 | 5173.33 | 0.0643915 | 2.901 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1516.98 | 0.0765655 | 302.996ms | 4604 | 160 | 785.77 | 2894.38 | 0.0647389 | 1.61706 | 1(Win) | true |
| Glaze | 929.252 | 0.181713 | 473.334ms | 4604 | 40 | 2948.72 | 4725 | 0.247525 | 2.64178 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1747.73 | 0.594918 | 1027.68ms | 18245 | 320 | 1.12254e+06 | 9955.62 | 0.16979 | 1.41244 | 1(Win) | true |
| Jsonifier | 1597.04 | 0.127071 | 1123.22ms | 18245 | 40 | 7666.67 | 10895 | 0.168557 | 1.54823 | 2(Loss) | true |
| simdjson (ondemand) | 685.97 | 0.156513 | 2569.44ms | 18245 | 1280 | 2.01739e+06 | 25365.2 | 0.157755 | 3.60469 | 3(Loss) | true |
| Glaze | 585.719 | 0.218829 | 3037.9ms | 18245 | 640 | 2.70457e+06 | 29706.7 | 0.0447279 | 4.22301 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2273 | 0.161693 | 946.673ms | 18245 | 40 | 6128.21 | 7655 | 0.0217675 | 1.08538 | 1(Win) | true |
| Jsonifier | 1962.38 | 0.146435 | 1057.18ms | 18245 | 30 | 5057.47 | 8866.67 | 0.188324 | 1.25702 | 2(Loss) | true |
| simdjson (ondemand) | 745.834 | 0.107606 | 2511.82ms | 18245 | 4890 | 3.08168e+06 | 23329.3 | 0.0879622 | 3.31557 | 3(Loss) | true |
| Glaze | 641.529 | 0.119299 | 2905.76ms | 18245 | 2560 | 2.68023e+06 | 27122.4 | 0.315993 | 3.85534 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5243.2 | 0.0900096 | 467.471ms | 24579 | 160 | 2590.8 | 4470.62 | 0.0698519 | 0.47008 | 1(Win) | true |
| Glaze | 3364.24 | 0.139677 | 704.513ms | 24579 | 40 | 3788.46 | 6967.5 | 0.035868 | 0.731552 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5460.77 | 0.12957 | 450.25ms | 24579 | 80 | 2474.68 | 4292.5 | 0 | 0.449884 | 1(Win) | true |
| Glaze | 3859.27 | 0.156241 | 620.447ms | 24579 | 4890 | 440368 | 6073.78 | 0.0404377 | 0.638667 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 791.53 | 0.18158 | 637.993ms | 5094 | 40 | 4967.95 | 6137.5 | 0.0949539 | 3.10988 | 1(Win) | true |
| Jsonifier (two-stage) | 712.319 | 0.215543 | 694.7ms | 5094 | 30 | 6482.76 | 6820 | 0.048852 | 3.45185 | 2(Loss) | true |
| Glaze | 629.647 | 0.15986 | 783.94ms | 5094 | 4890 | 743897 | 7715.46 | 0.133219 | 3.90766 | 3(Loss) | true |
| simdjson (ondemand) | 486.288 | 0.205593 | 1014.16ms | 5094 | 30 | 12655.2 | 9990 | 0.133645 | 5.07355 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 937.194 | 0.169067 | 647.755ms | 5094 | 4890 | 375568 | 5183.58 | 0.100415 | 2.62826 | 1(Win) | true |
| Jsonifier (two-stage) | 850.873 | 0.227603 | 688.784ms | 5094 | 1280 | 216150 | 5709.45 | 1.01181 | 2.89639 | 2(Loss) | true |
| Glaze | 830.43 | 0.149924 | 711.839ms | 5094 | 40 | 3076.92 | 5850 | 0.0569476 | 2.97003 | 3(Loss) | true |
| simdjson (ondemand) | 608.896 | 0.182654 | 930.205ms | 5094 | 2560 | 543664 | 7978.4 | 0.110282 | 4.05293 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9480.5 | 0.420426 | 54.7861ms | 5094 | 2560 | 11881.6 | 512.422 | 0.244536 | 0.24719 | 1(Win) | true |
| Glaze | 2818.97 | 0.533957 | 180.578ms | 5094 | 30 | 2540.23 | 1723.33 | 0.193798 | 0.861733 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11137.9 | 0.308034 | 47.6939ms | 5094 | 1280 | 2310.59 | 436.172 | 0.233393 | 0.208176 | 1(Win) | true |
| Glaze | 3280.45 | 0.27515 | 151.11ms | 5094 | 4890 | 81189.6 | 1480.9 | 0.171841 | 0.739951 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1123.17 | 0.155291 | 701.895ms | 8051 | 4890 | 551076 | 6836.03 | 0.0602842 | 2.18939 | 1(Win) | true |
| Jsonifier | 1059.53 | 0.183993 | 758.596ms | 8051 | 30 | 5333.33 | 7246.67 | 0.230521 | 2.3215 | 2(Loss) | true |
| Glaze | 879.716 | 0.218139 | 868.866ms | 8051 | 2560 | 927942 | 8727.85 | 0.0380572 | 2.79811 | 3(Loss) | true |
| simdjson (ondemand) | 757.909 | 0.183015 | 1037.11ms | 8051 | 2560 | 879997 | 10130.5 | 0.0816786 | 3.25215 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1330.39 | 0.111962 | 697.986ms | 8051 | 80 | 3340.19 | 5771.25 | 0.0216638 | 1.85396 | 1(Win) | true |
| Jsonifier | 1250.62 | 0.0663348 | 741.777ms | 8051 | 160 | 2653.69 | 6139.38 | 0.0508751 | 1.97249 | 2(Loss) | true |
| Glaze | 1177.84 | 0.0709213 | 780.106ms | 8051 | 160 | 3419.81 | 6518.75 | 0.0767607 | 2.09323 | 3(Loss) | true |
| simdjson (ondemand) | 924.786 | 0.180346 | 961.034ms | 8051 | 40 | 8967.95 | 8302.5 | 0.19107 | 2.66853 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10930.3 | 0.258679 | 83.2557ms | 9255 | 160 | 698.113 | 807.5 | 0.466563 | 0.219252 | 1(Win) | true |
| Glaze | 3384.95 | 0.108828 | 276.24ms | 9255 | 320 | 2576.8 | 2607.5 | 0.11999 | 0.723978 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13074.5 | 0.462023 | 70.6844ms | 9255 | 4890 | 47570.3 | 675.072 | 0.110789 | 0.182141 | 1(Win) | true |
| Glaze | 4030.25 | 0.147095 | 234.788ms | 9255 | 160 | 1660.38 | 2190 | 0.0570451 | 0.606679 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 5510.33 | 0 | 54.7332ms | 2889 | 30 | 0 | 500 | 0 | 0.428349 | 1(Win) | true |
| Jsonifier | 5363.67 | 0.187012 | 54.9253ms | 2889 | 1280 | 1181.19 | 513.672 | 0.136695 | 0.437025 | 2(Loss) | true |
| Glaze | 2900.99 | 0.43552 | 97.6729ms | 2889 | 4890 | 83662.2 | 949.734 | 0.128467 | 0.827639 | 3(Loss) | true |
| simdjson (ondemand) | 2819.48 | 0.240429 | 106.573ms | 2889 | 320 | 1766.36 | 977.188 | 0.0960307 | 0.855183 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 5934.06 | 0.288547 | 51.391ms | 2889 | 1280 | 2297.39 | 464.297 | 0.452261 | 0.393855 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 5869.86 | 0.778791 | 51.8605ms | 2889 | 160 | 2137.97 | 469.375 | 0.132979 | 0.399794 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3078.4 | 0.273975 | 94.5814ms | 2889 | 80 | 481.013 | 895 | 0 | 0.780551 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 3058.58 | 0.473605 | 94.2004ms | 2889 | 4890 | 89001.2 | 900.798 | 0.0285378 | 0.785635 | 3(Tie) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6559.1 | 0.324442 | 59.2814ms | 3808 | 1280 | 4130.37 | 553.672 | 0.354007 | 0.359198 | 1(Win) | true |
| Jsonifier (two-stage) | 6457.4 | 0.498087 | 59.6241ms | 3808 | 4890 | 38370.6 | 562.393 | 0.30985 | 0.365313 | 2(Loss) | true |
| simdjson (ondemand) | 3534.8 | 0.386157 | 105.808ms | 3808 | 2560 | 40293.3 | 1027.38 | 0.0494522 | 0.68278 | 3(Loss) | true |
| Glaze | 3366.48 | 0.300736 | 114.688ms | 3808 | 160 | 1683.96 | 1078.75 | 0.231214 | 0.714373 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7009.1 | 0.294123 | 64.2265ms | 3808 | 640 | 1486.31 | 518.125 | 0 | 0.334843 | 1(Win) | true |
| Jsonifier (two-stage) | 6953.53 | 0.22274 | 56.587ms | 3808 | 1280 | 1732.16 | 522.266 | 0.0149566 | 0.338126 | 2(Loss) | true |
| simdjson (ondemand) | 3710.44 | 0.234012 | 109.835ms | 3808 | 320 | 1678.68 | 978.75 | 0.191939 | 0.649094 | 3(Loss) | true |
| Glaze | 3520.48 | 0.252256 | 106.982ms | 3808 | 320 | 2166.83 | 1031.56 | 0.27339 | 0.683092 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1443.81 | 0.310553 | 194.241ms | 2889 | 4890 | 171734 | 1908.26 | 0.0623931 | 1.69006 | 1(Win) | true |
| Jsonifier (two-stage) | 1357.22 | 0.25398 | 209.649ms | 2889 | 80 | 2126.58 | 2030 | 0.2457 | 1.8035 | 2(Loss) | true |
| Glaze | 1278.5 | 0.259568 | 222.576ms | 2889 | 160 | 5006.29 | 2155 | 0.4662 | 1.90723 | 3(Loss) | true |
| simdjson (ondemand) | 1116.16 | 0.145193 | 262.453ms | 2889 | 320 | 4110.4 | 2468.44 | 0.0379651 | 2.19237 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1869.01 | 0.257277 | 164.943ms | 2889 | 4890 | 70337 | 1474.13 | 0.113412 | 1.29975 | 1(Win) | true |
| Glaze | 1607.68 | 0.226084 | 192.988ms | 2889 | 80 | 1200.95 | 1713.75 | 0.0729927 | 1.51687 | 2(Loss) | true |
| Jsonifier (two-stage) | 1543.51 | 0.32032 | 204.898ms | 2889 | 40 | 1307.69 | 1785 | 0.0934579 | 1.57539 | 3(Loss) | true |
| simdjson (ondemand) | 1363.94 | 0.15704 | 224.27ms | 2889 | 160 | 1610.06 | 2020 | 0.0618429 | 1.79465 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8150.2 | 0.205973 | 38.5367ms | 2963 | 4890 | 2493.76 | 346.708 | 0.0707757 | 0.281002 | 1(Win) | true |
| Glaze | 4255.23 | 0.415387 | 70.7453ms | 2963 | 320 | 2434.86 | 664.062 | 0.047081 | 0.554304 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10784 | 0.732681 | 29.5128ms | 2963 | 640 | 2358.93 | 262.031 | 0.651659 | 0.207117 | 1(Win) | true |
| Glaze | 5079.98 | 0.499327 | 60.1926ms | 2963 | 320 | 2468.65 | 556.25 | 1.00111 | 0.468223 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1762.91 | 0.281153 | 211.038ms | 3808 | 80 | 2683.54 | 2060 | 0 | 1.38045 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 1447.57 | 0.119372 | 268.992ms | 3808 | 320 | 2869.91 | 2508.75 | 0.35 | 1.68991 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1438.34 | 0.313621 | 256.757ms | 3808 | 1280 | 80258 | 2524.84 | 0.0123755 | 1.70242 | 2(Tie) | true |
| Jsonifier | 1393.31 | 0.275719 | 264.784ms | 3808 | 4890 | 252544 | 2606.44 | 0.110918 | 1.75804 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2010.11 | 0.256387 | 207.296ms | 3808 | 30 | 643.678 | 1806.67 | 0 | 1.20713 | 1(Win) | true |
| Glaze | 1794.76 | 0.121228 | 222.823ms | 3808 | 320 | 1925.45 | 2023.44 | 0.263239 | 1.36054 | 2(Loss) | true |
| simdjson (ondemand) | 1716.3 | 0.246853 | 230.639ms | 3808 | 640 | 17460.8 | 2115.94 | 0.445038 | 1.42504 | 3(Loss) | true |
| Jsonifier | 1694.27 | 0.243529 | 232.594ms | 3808 | 4890 | 133241 | 2143.46 | 0.0355709 | 1.44213 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7690.88 | 0.29892 | 57.0468ms | 4300 | 1280 | 3251.66 | 533.203 | 0.277615 | 0.305822 | 1(Win) | true |
| Glaze | 3512.46 | 0.711852 | 113.468ms | 4300 | 40 | 2762.82 | 1167.5 | 0.0714286 | 0.684744 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8390.38 | 0.361975 | 52.5594ms | 4300 | 320 | 1001.57 | 488.75 | 0.385109 | 0.279552 | 1(Win) | true |
| Glaze | 4853.02 | 0.466909 | 88.8959ms | 4300 | 160 | 2490.57 | 845 | 0.14771 | 0.489871 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4058.09 | 0.345421 | 5872.6ms | 466906 | 160 | 2.29844e+07 | 109726 | 0.709777 | 0.609885 | 1(Win) | true |
| Glaze | 1834.98 | 0.139736 | 6283.4ms | 466906 | 320 | 3.67929e+07 | 242661 | 0.0670108 | 1.34909 | 2(Loss) | true |
| simdjson (ondemand) | 1406.15 | 0.121871 | 8186.29ms | 466906 | 320 | 4.76594e+07 | 316664 | 0.0594436 | 1.76044 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4097.98 | 0.428613 | 5750.31ms | 466906 | 80 | 1.73516e+07 | 108658 | 0.0528906 | 0.60398 | 1(Win) | true |
| Glaze | 1829.18 | 0.161973 | 6375.36ms | 466906 | 320 | 4.97486e+07 | 243429 | 0.1624 | 1.35335 | 2(Loss) | true |
| simdjson (ondemand) | 1405.83 | 0.170881 | 8124.78ms | 466906 | 160 | 4.68703e+07 | 316734 | 0.0859107 | 1.76085 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 3352.2 | 0.442204 | 5061.81ms | 699405 | 80 | 6.19346e+07 | 198975 | 0.289819 | 0.738454 | 1(Win) | true |
| Jsonifier | 2652.49 | 0.101261 | 6470.99ms | 699405 | 1280 | 8.29944e+07 | 251464 | 0.778838 | 0.93301 | 2(Loss) | true |
| simdjson (ondemand) | 1544.89 | 0.161633 | 6231.54ms | 767297 | 160 | 9.37812e+07 | 473660 | 1.00374 | 1.60232 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4680.16 | 0.443598 | 7436.63ms | 699405 | 80 | 3.19746e+07 | 142518 | 1.04758 | 0.528879 | 1(Win) | true |
| Glaze | 3447.9 | 0.219154 | 5020.34ms | 699405 | 160 | 2.87585e+07 | 193452 | 0.0245599 | 0.717959 | 2(Loss) | true |
| simdjson (ondemand) | 1470.55 | 0.390051 | 6130.36ms | 767297 | 80 | 3.01371e+08 | 497605 | 0.176535 | 1.6832 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3269.01 | 0.237796 | 9523.77ms | 631514 | 160 | 3.07087e+07 | 184232 | 0.163926 | 0.757238 | 1(Win) | true |
| Glaze | 2591.82 | 0.0990476 | 6083.55ms | 631514 | 640 | 3.39019e+07 | 232369 | 0.556808 | 0.955121 | 2(Loss) | true |
