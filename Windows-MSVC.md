# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson (AVX512)
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36260.0 compiler).  

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

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 451.576 | 0.186007 | 205.637ms | 905 | 80 | 1011.08 | 1911.25 | 0.065445 | 5.40054 | 1(Win) | true |
| Jsonifier | 436.103 | 0.143957 | 208.294ms | 905 | 640 | 5194.74 | 1979.06 | 0.252008 | 5.60386 | 2(Loss) | true |
| Jsonifier (two-stage) | 157.209 | 0.15707 | 564.436ms | 905 | 40 | 2974.36 | 5490 | 0 | 15.6294 | 3(Loss) | true |
| simdjson (ondemand) | 68.0961 | 0.448526 | 1353.14ms | 905 | 320 | 1.03414e+06 | 12674.4 | 0.255767 | 36.247 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 536.072 | 0.346016 | 174.021ms | 905 | 30 | 931.034 | 1610 | 0 | 4.53333 | 1(Win) | true |
| Glaze | 507.318 | 0.0519143 | 181.945ms | 905 | 640 | 499.218 | 1701.25 | 0.274776 | 4.80144 | 2(Loss) | true |
| Jsonifier (two-stage) | 164.909 | 0.197496 | 541.22ms | 905 | 4890 | 522437 | 5233.64 | 0.0401491 | 14.8975 | 3(Loss) | true |
| simdjson (ondemand) | 66.944 | 0.0327139 | 1298.71ms | 905 | 40 | 711.538 | 12892.5 | 0.238587 | 36.8539 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1091.48 | 0.420416 | 82.1206ms | 905 | 4890 | 54041.8 | 790.736 | 0.157571 | 2.18903 | 1(Win) | true |
| Glaze | 77.8827 | 0.356008 | 1204.32ms | 905 | 4890 | 7.61106e+06 | 11081.7 | 0.156576 | 31.6847 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1501.41 | 0.298607 | 67.5101ms | 905 | 640 | 1885.73 | 574.844 | 0.794521 | 1.57362 | 1(Win) | true |
| Glaze | 275.743 | 0.164722 | 333.989ms | 905 | 80 | 2126.58 | 3130 | 0.0799361 | 8.86656 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 848.602 | 0.408628 | 207.302ms | 1811 | 2560 | 177062 | 2035.23 | 0.203034 | 2.87824 | 1(Win) | true |
| Glaze | 393.866 | 0.130393 | 451.002ms | 1811 | 40 | 1307.69 | 4385 | 0.0380228 | 6.24045 | 2(Loss) | true |
| Jsonifier (two-stage) | 338.068 | 0.111175 | 524.442ms | 1811 | 80 | 2580.7 | 5108.75 | 0.0244618 | 7.28667 | 3(Loss) | true |
| simdjson (ondemand) | 134.196 | 0.0843855 | 1304.16ms | 1811 | 40 | 4717.95 | 12870 | 0.0518269 | 18.4329 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1179.82 | 0.389073 | 149.47ms | 1811 | 2560 | 83043.3 | 1463.87 | 0.463782 | 2.06008 | 1(Win) | true |
| Glaze | 393.119 | 0.186914 | 385.834ms | 1811 | 30 | 2022.99 | 4393.33 | 0.227101 | 6.25181 | 2(Loss) | true |
| Jsonifier (two-stage) | 378.785 | 0.180256 | 466.36ms | 1811 | 4890 | 330324 | 4559.59 | 0.272947 | 6.49604 | 3(Loss) | true |
| simdjson (ondemand) | 144.568 | 0.0775456 | 1264.54ms | 1811 | 30 | 2574.71 | 11946.7 | 0.0557724 | 17.0892 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 450.941 | 0.191593 | 387.51ms | 1811 | 40 | 2153.85 | 3830 | 0 | 5.43361 | 1(Win) | true |
| Glaze | 132.112 | 0.290653 | 1306.32ms | 1798 | 4890 | 6.95911e+06 | 12979.2 | 0.379099 | 18.6926 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 691.966 | 0.321045 | 302.413ms | 1811 | 2560 | 164376 | 2495.94 | 0.246667 | 3.53836 | 1(Win) | true |
| Glaze | 354.736 | 0.0775795 | 500.168ms | 1798 | 160 | 2250 | 4833.75 | 0.257931 | 6.94312 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1494.15 | 0.176949 | 253.767ms | 3862 | 160 | 3044.03 | 2465 | 0.101523 | 1.6415 | 1(Win) | true |
| Glaze | 880.069 | 0.136624 | 430.332ms | 3862 | 40 | 1307.69 | 4185 | 0.0398089 | 2.79336 | 2(Loss) | true |
| Jsonifier (two-stage) | 391.263 | 0.16687 | 662.218ms | 3862 | 30 | 7402.3 | 9413.33 | 0.641483 | 6.30432 | 3(Loss) | true |
| simdjson (ondemand) | 296.094 | 0.342953 | 1248.66ms | 3862 | 640 | 1.1647e+06 | 12438.9 | 0.585679 | 8.34484 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1898.19 | 0.141545 | 200.146ms | 3862 | 320 | 2413.7 | 1940.31 | 0.24217 | 1.28657 | 1(Win) | true |
| Glaze | 1017.08 | 0.127096 | 374.798ms | 3862 | 80 | 1694.62 | 3621.25 | 0.309704 | 2.41309 | 2(Loss) | true |
| Jsonifier (two-stage) | 623.196 | 0.145908 | 610.175ms | 3862 | 40 | 2974.36 | 5910 | 0.0564334 | 3.95502 | 3(Loss) | true |
| simdjson (ondemand) | 324.979 | 0.0772391 | 1147.32ms | 3862 | 30 | 2298.85 | 11333.3 | 0.17616 | 7.59959 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 420.613 | 0.202198 | 891.282ms | 3862 | 2560 | 802514 | 8756.48 | 0.0944834 | 5.85764 | 1(Win) | true |
| Glaze | 350.353 | 0.108713 | 1138.57ms | 3862 | 40 | 5224.36 | 10512.5 | 0.481224 | 7.04377 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3657.94 | 0.199295 | 116.121ms | 3862 | 160 | 644.261 | 1006.88 | 0.0621118 | 0.656826 | 1(Win) | true |
| Glaze | 1099.43 | 0.277157 | 355.195ms | 3862 | 30 | 2586.21 | 3350 | 0 | 2.23331 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 864.171 | 0.23025 | 1080.07ms | 9578 | 40 | 23692.3 | 10570 | 0.188857 | 2.8521 | 1(Win) | true |
| Glaze | 675.211 | 0.216702 | 1404.71ms | 9578 | 1280 | 1.10003e+06 | 13528 | 0.245988 | 3.65467 | 2(Loss) | true |
| Jsonifier (two-stage) | 635.374 | 0.144963 | 1450.57ms | 9578 | 80 | 34745.3 | 14376.2 | 0.00869414 | 3.88526 | 3(Loss) | true |
| simdjson (ondemand) | 518.437 | 0.188278 | 1805.74ms | 9578 | 1280 | 1.40854e+06 | 17618.9 | 1.57825 | 4.76204 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1359.27 | 0.0669695 | 894.121ms | 9578 | 80 | 1620.25 | 6720 | 0.296736 | 1.81301 | 1(Win) | true |
| Glaze | 945.457 | 0.200077 | 1202.9ms | 9578 | 2560 | 956536 | 9661.25 | 0.111717 | 2.6108 | 2(Loss) | true |
| Jsonifier (two-stage) | 826.384 | 0.0838128 | 1361.1ms | 9578 | 30 | 2574.71 | 11053.3 | 0.180614 | 2.98572 | 3(Loss) | true |
| simdjson (ondemand) | 667.467 | 0.298046 | 1624.09ms | 9578 | 640 | 1.06472e+06 | 13685 | 0.241469 | 3.7029 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1225.92 | 0.156683 | 770.377ms | 9578 | 4890 | 666464 | 7450.96 | 0.166786 | 2.01151 | 1(Win) | true |
| Glaze | 803.132 | 0.102687 | 1227.02ms | 9578 | 30 | 4091.95 | 11373.3 | 0.292227 | 3.0783 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7592.12 | 0.374589 | 130.864ms | 9578 | 4890 | 99321.4 | 1203.13 | 0.326053 | 0.317227 | 1(Win) | true |
| Glaze | 2482.99 | 0.0881873 | 388.513ms | 9578 | 160 | 1683.96 | 3678.75 | 0.271095 | 0.987908 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1347.41 | 0.202048 | 282.085ms | 3873 | 80 | 2454.11 | 2741.25 | 0.0456204 | 1.81697 | 1(Win) | true |
| Glaze | 974.62 | 0.311708 | 388.445ms | 3873 | 1280 | 178621 | 3789.77 | 0.158986 | 2.52149 | 2(Loss) | true |
| Jsonifier (two-stage) | 547.806 | 0.0866052 | 702.102ms | 3873 | 80 | 2727.85 | 6742.5 | 0.037092 | 4.50281 | 3(Loss) | true |
| simdjson (ondemand) | 300.979 | 0.508033 | 1242.54ms | 3873 | 160 | 621908 | 12271.9 | 0.117275 | 8.20935 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1717.96 | 0.242422 | 217.232ms | 3873 | 4890 | 132838 | 2149.98 | 0.212072 | 1.42267 | 1(Win) | true |
| Glaze | 1151.55 | 0.131493 | 333.318ms | 3873 | 40 | 711.538 | 3207.5 | 0.0259875 | 2.13225 | 2(Loss) | true |
| Jsonifier (two-stage) | 592.439 | 0.351113 | 631.973ms | 3873 | 640 | 306677 | 6234.53 | 0.122653 | 4.16198 | 3(Loss) | true |
| simdjson (ondemand) | 313.836 | 0.125473 | 1183.85ms | 3873 | 4890 | 1.06635e+06 | 11769.1 | 0.326668 | 7.87059 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 424.519 | 0.164839 | 878.784ms | 3873 | 4890 | 1.00585e+06 | 8700.63 | 0.0546406 | 5.80206 | 1(Win) | true |
| Glaze | 333.556 | 0.0961717 | 1139.86ms | 3873 | 30 | 3402.3 | 11073.3 | 0.150739 | 7.40298 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3429.33 | 0.434842 | 120.671ms | 3873 | 4890 | 107262 | 1077.06 | 0.169344 | 0.702874 | 1(Win) | true |
| Glaze | 1046.32 | 0.332255 | 368.767ms | 3873 | 1280 | 176084 | 3530.08 | 0.255159 | 2.34725 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 822.803 | 1.36985 | 5738.49ms | 94653 | 160 | 3.61366e+08 | 109708 | 0.158055 | 3.00798 | 1(Win) | true |
| Jsonifier (two-stage) | 790.528 | 0.777322 | 5852.87ms | 94653 | 320 | 2.52108e+08 | 114187 | 0.330324 | 3.13081 | 2(Loss) | true |
| Glaze | 761.715 | 0.585004 | 6228.25ms | 94653 | 640 | 3.07596e+08 | 118506 | 0.388626 | 3.24923 | 3(Loss) | true |
| simdjson (ondemand) | 691.813 | 0.273693 | 6807.59ms | 94653 | 2560 | 3.26481e+08 | 130481 | 1.51752 | 3.57779 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1262.35 | 0.399193 | 9317.06ms | 94653 | 320 | 2.60749e+07 | 71507.8 | 0.474521 | 1.96055 | 1(Win) | true |
| Jsonifier (two-stage) | 1160.53 | 0.218766 | 5064.82ms | 94653 | 640 | 1.85308e+07 | 77781.9 | 0.307893 | 2.13259 | 2(Loss) | true |
| Glaze | 1104.19 | 0.298151 | 5214.81ms | 94653 | 640 | 3.80218e+07 | 81750.5 | 0.100243 | 2.24137 | 3(Loss) | true |
| simdjson (ondemand) | 978.306 | 0.458436 | 5505.26ms | 94653 | 2560 | 4.58054e+08 | 92269.8 | 0.369359 | 2.52993 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12405.1 | 0.252485 | 751.264ms | 94653 | 30 | 10126.4 | 7276.67 | 0.229568 | 0.198579 | 1(Win) | true |
| Glaze | 4714.33 | 0.421189 | 1947.88ms | 94653 | 2560 | 1.66504e+07 | 19147.6 | 0.0994503 | 0.524302 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12616.1 | 0.111339 | 743.061ms | 94653 | 40 | 2538.46 | 7155 | 0.255576 | 0.195378 | 1(Win) | true |
| Glaze | 5158.16 | 0.17958 | 1815.52ms | 94653 | 2560 | 2.52835e+06 | 17500.1 | 0.231785 | 0.479108 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1018.57 | 0.748977 | 6155.37ms | 124597 | 320 | 2.44301e+08 | 116659 | 0.254101 | 2.43007 | 1(Win) | true |
| Jsonifier | 962.099 | 0.848924 | 6446.99ms | 124597 | 320 | 3.51774e+08 | 123506 | 0.611737 | 2.57266 | 2(Loss) | true |
| Glaze | 897.53 | 0.348496 | 6967.46ms | 124597 | 2560 | 5.44945e+08 | 132391 | 0.00395388 | 2.7578 | 3(Loss) | true |
| simdjson (ondemand) | 867.35 | 0.455249 | 6883.4ms | 124597 | 1280 | 4.97891e+08 | 136998 | 0.126473 | 2.85376 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1449.6 | 0.0913721 | 5176.11ms | 124597 | 2560 | 1.4361e+07 | 81970.7 | 0.178019 | 1.70731 | 1(Win) | true |
| Jsonifier | 1378.88 | 0.593377 | 5510.5ms | 124597 | 40 | 1.04588e+07 | 86175 | 0.117838 | 1.79492 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1275.58 | 0.636148 | 5787.38ms | 124597 | 30 | 1.0535e+07 | 93153.3 | 0.406272 | 1.94027 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1259.17 | 0.0758724 | 5852.49ms | 124597 | 2560 | 1.31236e+07 | 94367.6 | 0.192687 | 1.96564 | 3(Tie) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12177.9 | 0.0869597 | 1158.28ms | 136037 | 30 | 2574.71 | 10653.3 | 0.0625391 | 0.202948 | 1(Win) | true |
| Glaze | 3987.68 | 0.541068 | 3302.45ms | 136076 | 640 | 1.9843e+07 | 32543.3 | 0.0110418 | 0.620313 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12253.6 | 0.0500188 | 1096.93ms | 136037 | 40 | 1121.79 | 10587.5 | 0.450664 | 0.201641 | 1(Win) | true |
| Glaze | 4255.16 | 0.11394 | 3080.21ms | 136076 | 2560 | 3.09118e+06 | 30497.6 | 0.0267767 | 0.581238 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 591.559 | 0.889749 | 5570.63ms | 2251027 | 80 | 8.34047e+10 | 3.62896e+06 | 0.353689 | 4.18519 | 1(Win) | true |
| Jsonifier (two-stage) | 553.794 | 0.762431 | 6026.86ms | 2251027 | 40 | 3.49402e+10 | 3.87644e+06 | 2.03494 | 4.47058 | 2(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 194.31 | 0.747222 | 7789.79ms | 2251027 | 40 | 2.72602e+11 | 1.1048e+07 | 10.8521 | 12.7412 | -(Loss) | false |
| Glaze | 177.85 | 0.596836 | 8600.94ms | 2251027 | 30 | 1.55698e+11 | 1.20705e+07 | 0.276465 | 13.9207 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 708.941 | 1.61412 | 5692.98ms | 2251027 | 80 | 1.91118e+11 | 3.0281e+06 | 0.85667 | 3.49221 | 1(Win) | true |
| Jsonifier (two-stage) | 648.813 | 0.989227 | 5923.32ms | 2251027 | 80 | 8.57048e+10 | 3.30873e+06 | 0.344973 | 3.81587 | 2(Loss) | true |
| simdjson (ondemand) | 207.618 | 0.592902 | 7722.19ms | 2251027 | 40 | 1.50334e+11 | 1.03399e+07 | 0.673995 | 11.9247 | 3(Loss) | true |
| Glaze | 189.875 | 0.793382 | 8578.61ms | 2251027 | 40 | 3.21848e+11 | 1.13061e+07 | 0.2944 | 13.0392 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1182.76 | 0.781037 | 5301.57ms | 2090234 | 160 | 2.77245e+10 | 1.68539e+06 | 2.25656 | 2.09308 | 1(Win) | true |
| Glaze | 773.934 | 0.29584 | 8118.2ms | 2090234 | 30 | 1.74188e+09 | 2.57568e+06 | 1.17118 | 3.19878 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1408.79 | 0.267125 | 8901.82ms | 2090234 | 40 | 5.71457e+08 | 1.41497e+06 | 2.14866 | 1.75731 | 1(Win) | true |
| Glaze | 1089.2 | 0.0753381 | 5581.26ms | 2090234 | 40 | 7.60436e+07 | 1.83015e+06 | 1.10523 | 2.273 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1269.14 | 0.747466 | 6275.96ms | 5373214 | 40 | 3.64326e+10 | 4.0376e+06 | 0.189124 | 1.95072 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1253.16 | 0.789736 | 6505.12ms | 5373214 | 80 | 8.34273e+10 | 4.0891e+06 | 1.96808 | 1.97558 | 1(Tie) | true |
| simdjson (ondemand) DID NOT CONVERGE | 439.829 | 0.519508 | 8119.92ms | 5373214 | 40 | 1.46536e+11 | 1.16507e+07 | 6.48782 | 5.62902 | -(Loss) | false |
| Glaze | 419.233 | 0.620966 | 8673.37ms | 5373214 | 40 | 2.30437e+11 | 1.2223e+07 | 0.360521 | 5.90557 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1498.84 | 1.12389 | 6228.5ms | 5373214 | 80 | 1.18112e+11 | 3.41885e+06 | 0.0393618 | 1.6518 | 1(Win) | true |
| Jsonifier | 1405.4 | 1.6872 | 6388.61ms | 5373214 | 80 | 3.02754e+11 | 3.64615e+06 | 1.99481 | 1.76158 | 2(Loss) | true |
| simdjson (ondemand) | 470.89 | 0.139975 | 8095.62ms | 5373214 | 40 | 9.28095e+09 | 1.08821e+07 | 0.171287 | 5.25765 | 3(Loss) | true |
| Glaze | 442.128 | 0.476306 | 8645.57ms | 5373214 | 30 | 9.14255e+10 | 1.15901e+07 | 0.4731 | 5.59976 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2717.61 | 1.44997 | 7465.22ms | 6661897 | 160 | 1.83848e+11 | 2.33782e+06 | 0.653947 | 0.91096 | 1(Win) | true |
| Glaze | 1133.26 | 2.58928 | 7230.05ms | 6661897 | 40 | 8.42861e+11 | 5.6062e+06 | 2.34298 | 2.18452 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4192.94 | 0.286204 | 9758.89ms | 6661897 | 80 | 1.50452e+09 | 1.51523e+06 | 0.0540055 | 0.590449 | 1(Win) | true |
| Glaze | 3116.53 | 0.0731828 | 6446.14ms | 6661897 | 80 | 1.78058e+08 | 2.03857e+06 | 0.740706 | 0.794402 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1325.33 | 0.136236 | 9308.12ms | 500299 | 320 | 7.69749e+07 | 360003 | 0.110538 | 1.8678 | 1(Win) | true |
| Jsonifier (two-stage) | 1139.06 | 0.416399 | 5469.07ms | 500299 | 80 | 2.43374e+08 | 418872 | 0.135299 | 2.17334 | 2(Loss) | true |
| Glaze | 717.787 | 0.194567 | 8520.61ms | 500299 | 160 | 2.67623e+08 | 664712 | 0.423197 | 3.44904 | 3(Loss) | true |
| simdjson (ondemand) | 573.387 | 0.204917 | 5415.96ms | 500299 | 40 | 1.163e+08 | 832112 | 0.0135216 | 4.31756 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1513.99 | 0.100495 | 9228.88ms | 500299 | 640 | 6.4192e+07 | 315142 | 0.0627094 | 1.63511 | 1(Win) | true |
| Jsonifier (two-stage) | 1263.95 | 0.366222 | 5373.78ms | 500299 | 160 | 3.05779e+08 | 377484 | 0.31041 | 1.9586 | 2(Loss) | true |
| Glaze | 817.747 | 0.15565 | 7964.82ms | 500299 | 160 | 1.3196e+08 | 583459 | 0.399135 | 3.02744 | 3(Loss) | true |
| simdjson (ondemand) | 540.777 | 0.623309 | 5819.44ms | 500299 | 320 | 9.67785e+09 | 882290 | 2.37387 | 4.57802 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7662.21 | 0.234135 | 6315.6ms | 500299 | 640 | 1.36039e+07 | 62269.5 | 0.407905 | 0.322946 | 1(Win) | true |
| Glaze | 3153.64 | 0.393039 | 7910.13ms | 500299 | 40 | 1.41438e+07 | 151292 | 0.128174 | 0.784716 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7646.11 | 0.272625 | 6234.43ms | 500299 | 320 | 9.261e+06 | 62400.6 | 0.0922315 | 0.323613 | 1(Win) | true |
| Glaze | 3318.02 | 0.233425 | 7380.58ms | 500299 | 160 | 1.80268e+07 | 143798 | 0.458463 | 0.745906 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2424.78 | 0.158831 | 5836.01ms | 1151920 | 160 | 8.28494e+07 | 453054 | 0.169832 | 1.02093 | 1(Win) | true |
| Jsonifier | 2150.71 | 0.4246 | 6658.28ms | 1151920 | 30 | 1.41111e+08 | 510787 | 0.03001 | 1.15103 | 2(Loss) | true |
| Glaze | 1371.34 | 0.349763 | 5239.32ms | 1151920 | 80 | 6.28044e+08 | 801081 | 0.190261 | 1.80531 | 3(Loss) | true |
| simdjson (ondemand) | 1234.3 | 0.193077 | 5866.42ms | 1151920 | 30 | 8.85903e+07 | 890027 | 0.225218 | 2.00579 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2621.05 | 0.251451 | 5739.24ms | 1151920 | 160 | 1.77714e+08 | 419129 | 1.19086 | 0.944502 | 1(Win) | true |
| Jsonifier | 2329.03 | 0.448038 | 6592.15ms | 1151920 | 320 | 1.42914e+09 | 471680 | 0.358527 | 1.06295 | 2(Loss) | true |
| Glaze | 1456.27 | 0.475095 | 10175.7ms | 1151920 | 640 | 8.22063e+09 | 754366 | 0.226863 | 1.70003 | 3(Loss) | true |
| simdjson (ondemand) | 1141.91 | 0.280906 | 6296.95ms | 1151920 | 30 | 2.19091e+08 | 962033 | 0.086003 | 2.16804 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3748.77 | 1.0112 | 9349.98ms | 1439562 | 30 | 4.11418e+08 | 366220 | 0.750128 | 0.66022 | 1(Win) | true |
| Glaze | 1963.18 | 0.347326 | 9108.43ms | 1439584 | 40 | 2.35986e+08 | 699320 | 0.761731 | 1.26086 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12038.8 | 0.0846664 | 5820.54ms | 1439562 | 2560 | 2.38648e+07 | 114038 | 0.466929 | 0.205591 | 1(Win) | true |
| Glaze | 5908.88 | 0.113296 | 6072.85ms | 1439584 | 640 | 4.43476e+07 | 232344 | 0.367908 | 0.418937 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1210.75 | 0.214896 | 4505.41ms | 56369 | 1280 | 1.16531e+07 | 44400.4 | 0.402972 | 2.04346 | 1(Win) | true |
| Glaze | 1012.89 | 0.135188 | 5500.1ms | 56369 | 30 | 154437 | 53073.3 | 1.25279 | 2.44408 | 2(Loss) | true |
| Jsonifier (two-stage) | 949.816 | 0.176586 | 5645.35ms | 56369 | 640 | 6.39281e+06 | 56598 | 0.00800667 | 2.60531 | 3(Loss) | true |
| simdjson (ondemand) | 699.518 | 0.140866 | 7702.54ms | 56369 | 4890 | 5.73066e+07 | 76849.5 | 0.290826 | 3.5379 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1710.56 | 0.223923 | 3701.24ms | 56369 | 640 | 3.16946e+06 | 31427 | 0.858168 | 1.44606 | 1(Win) | true |
| Glaze | 1387.33 | 0.139539 | 4493.03ms | 56369 | 1280 | 3.74214e+06 | 38748.9 | 0.00685456 | 1.78329 | 2(Loss) | true |
| Jsonifier (two-stage) | 1252.33 | 0.119559 | 4833.14ms | 56369 | 2560 | 6.74299e+06 | 42926.3 | 0.0037311 | 1.97562 | 3(Loss) | true |
| simdjson (ondemand) | 890.809 | 0.0726658 | 6491.51ms | 56369 | 4890 | 9.40332e+06 | 60347 | 0.201007 | 2.77799 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10817.8 | 0.0735596 | 516.525ms | 56369 | 160 | 2137.97 | 4969.38 | 0.0881168 | 0.22722 | 1(Win) | true |
| Glaze | 3021.21 | 0.488144 | 1789.66ms | 56369 | 320 | 2.41416e+06 | 17793.4 | 0.103512 | 0.817762 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11519.2 | 0.396373 | 470.804ms | 56369 | 1280 | 437982 | 4666.8 | 0.078619 | 0.213628 | 1(Win) | true |
| Glaze | 3259.15 | 0.219166 | 1675.97ms | 56369 | 1280 | 1.67274e+06 | 16494.4 | 0.140948 | 0.758167 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1386.44 | 0.288629 | 5924.44ms | 83958 | 320 | 8.89103e+06 | 57751.2 | 0.378039 | 1.78487 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 1316.22 | 0.131179 | 6153.68ms | 83958 | 2560 | 1.63016e+07 | 60832 | 0.203264 | 1.8801 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1316.14 | 0.137869 | 6174.67ms | 83958 | 1280 | 9.00462e+06 | 60836.1 | 0.776757 | 1.88026 | 2(Tie) | true |
| simdjson (ondemand) | 1012.02 | 0.323866 | 8140.58ms | 83958 | 160 | 1.0505e+07 | 79117.5 | 0.552855 | 2.44564 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1778.76 | 0.500636 | 5049.21ms | 83958 | 160 | 8.1256e+06 | 45013.8 | 0.116495 | 1.39099 | 1(Win) | true |
| Glaze | 1739.87 | 0.21077 | 5231.61ms | 83958 | 640 | 6.02128e+06 | 46019.8 | 0.327249 | 1.42211 | 2(Loss) | true |
| Jsonifier | 1675.24 | 0.188001 | 5373.31ms | 83958 | 640 | 5.16738e+06 | 47795.2 | 0.0192918 | 1.477 | 3(Loss) | true |
| simdjson (ondemand) | 1238.73 | 0.315949 | 7031.2ms | 83958 | 160 | 6.67305e+06 | 64637.5 | 0.268086 | 1.99764 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11214.7 | 0.064628 | 867.471ms | 94370 | 80 | 2151.9 | 8025 | 0.124766 | 0.219922 | 1(Win) | true |
| Glaze | 2994.83 | 0.321072 | 3035.31ms | 94370 | 320 | 2.97906e+06 | 30051.2 | 0.185444 | 0.825915 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11607.7 | 0.13454 | 791.851ms | 94370 | 30 | 3264.37 | 7753.33 | 0.0860585 | 0.212657 | 1(Win) | true |
| Glaze | 3255.73 | 0.165242 | 2816.35ms | 94370 | 1280 | 2.67069e+06 | 27643 | 0.206456 | 0.759587 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1007.44 | 0.337287 | 5077.64ms | 53331 | 2560 | 7.42273e+07 | 50485 | 0.473598 | 2.45572 | 1(Win) | true |
| Glaze | 985.219 | 0.254683 | 5297.91ms | 53331 | 4890 | 8.45287e+07 | 51623.4 | 0.730114 | 2.51137 | 2(Loss) | true |
| Jsonifier (two-stage) | 969.713 | 0.211499 | 5310.9ms | 53331 | 2560 | 3.15014e+07 | 52448.9 | 0.069439 | 2.5514 | 3(Loss) | true |
| simdjson (ondemand) | 610.128 | 0.203716 | 8415.99ms | 53331 | 2560 | 7.38254e+07 | 83360.2 | 0.245551 | 4.05644 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1491.62 | 0.18345 | 4309.89ms | 53331 | 1280 | 5.00825e+06 | 34097.3 | 0.0697021 | 1.65842 | 1(Win) | true |
| Glaze | 1379.46 | 0.104251 | 4442.13ms | 53331 | 4890 | 7.22457e+06 | 36869.9 | 0.401209 | 1.79337 | 2(Loss) | true |
| Jsonifier (two-stage) | 1367.92 | 0.180656 | 4632.82ms | 53331 | 1280 | 5.77505e+06 | 37180.9 | 0.140558 | 1.8084 | 3(Loss) | true |
| simdjson (ondemand) | 745.726 | 0.472065 | 7723ms | 53331 | 80 | 8.29265e+06 | 68202.5 | 0.157371 | 3.3184 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11053.9 | 0.375311 | 512.397ms | 58581 | 2560 | 921093 | 5054.06 | 0.302059 | 0.222544 | 1(Win) | true |
| Glaze | 4719.01 | 0.850211 | 1185.39ms | 58581 | 80 | 810505 | 11838.8 | 0.0527649 | 0.523125 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11720.4 | 0.209388 | 485.966ms | 58581 | 30 | 2988.51 | 4766.67 | 0.069979 | 0.209221 | 1(Win) | true |
| Glaze | 5342.71 | 0.332405 | 1055.57ms | 58581 | 640 | 773226 | 10456.7 | 0.204295 | 0.462078 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1178.43 | 0.349072 | 5520.22ms | 65103 | 320 | 1.08237e+07 | 52686.2 | 0.124403 | 2.09938 | 1(Win) | true |
| Glaze | 1117.94 | 0.206359 | 5579.81ms | 65103 | 4890 | 6.42276e+07 | 55537.1 | 0.487095 | 2.21318 | 2(Loss) | true |
| Jsonifier | 1051.41 | 0.464563 | 6102.46ms | 65103 | 160 | 1.20411e+07 | 59051.2 | 0.391015 | 2.35311 | 3(Loss) | true |
| simdjson (ondemand) | 745.365 | 0.472938 | 8518.62ms | 65103 | 80 | 1.24154e+07 | 83297.5 | 0.685564 | 3.32092 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1616.42 | 0.371652 | 4655.19ms | 65103 | 320 | 6.52105e+06 | 38410.3 | 0.338117 | 1.53034 | 1(Win) | true |
| Glaze | 1491.02 | 0.204088 | 4821.42ms | 65103 | 4890 | 3.53165e+07 | 41640.7 | 0.62354 | 1.65934 | 2(Loss) | true |
| Jsonifier | 1426.15 | 0.128792 | 5161.42ms | 65103 | 2560 | 8.0481e+06 | 43534.9 | 0.0956505 | 1.73487 | 3(Loss) | true |
| simdjson (ondemand) | 893.005 | 0.204818 | 7703.25ms | 65103 | 2560 | 5.19123e+07 | 69526 | 0.215423 | 2.77127 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11055.2 | 0.261725 | 683.486ms | 78778 | 2560 | 809849 | 6795.74 | 0.240266 | 0.222961 | 1(Win) | true |
| Glaze | 4288.58 | 0.20332 | 1801ms | 78778 | 1280 | 1.62387e+06 | 17518.3 | 0.167069 | 0.576452 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11794.1 | 0.186661 | 648.618ms | 78778 | 30 | 4241.38 | 6370 | 0.052356 | 0.209069 | 1(Win) | true |
| Glaze | 4869.29 | 0.317211 | 1556.58ms | 78778 | 640 | 1.53305e+06 | 15429.1 | 0.164327 | 0.507367 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1282.42 | 0.172598 | 892.731ms | 11812 | 4890 | 1.124e+06 | 8783.99 | 0.294405 | 1.92401 | 1(Win) | true |
| Jsonifier (two-stage) | 1083.85 | 0.121471 | 1060.38ms | 11812 | 30 | 4781.61 | 10393.3 | 0.287816 | 2.27819 | 2(Loss) | true |
| Glaze | 856.639 | 0.198872 | 1387.64ms | 11812 | 30 | 20517.2 | 13150 | 0.0253421 | 2.88563 | 3(Loss) | true |
| simdjson (ondemand) | 532.577 | 0.218501 | 2130.67ms | 11812 | 1280 | 2.73399e+06 | 21151.5 | 0.0816951 | 4.64216 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1423.28 | 0.386789 | 896.838ms | 11812 | 640 | 599784 | 7914.69 | 0.126507 | 1.7334 | 1(Win) | true |
| Jsonifier (two-stage) | 1213.23 | 0.214464 | 1030.64ms | 11812 | 2560 | 1.0151e+06 | 9284.96 | 0.0467203 | 2.03421 | 2(Loss) | true |
| Glaze | 964.814 | 0.339275 | 1309.8ms | 11812 | 640 | 1.00426e+06 | 11675.6 | 0.142057 | 2.55978 | 3(Loss) | true |
| simdjson (ondemand) | 580.515 | 0.368802 | 2084.1ms | 11812 | 640 | 3.27783e+06 | 19404.8 | 0.812566 | 4.25893 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8980.41 | 0.314902 | 131.352ms | 11812 | 160 | 2496.46 | 1254.38 | 0.0498504 | 0.268862 | 1(Win) | true |
| Glaze | 2690.1 | 0.212694 | 407.639ms | 11812 | 40 | 3173.08 | 4187.5 | 0.0596659 | 0.913533 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9609.89 | 0.42431 | 120.009ms | 11812 | 4890 | 120972 | 1172.21 | 0.0551476 | 0.251543 | 1(Win) | true |
| Glaze | 3244 | 0.153473 | 358.765ms | 11812 | 80 | 2272.15 | 3472.5 | 0.0719424 | 0.757193 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2221.95 | 0.120368 | 1103.29ms | 25388 | 30 | 5160.92 | 10896.7 | 0.430108 | 1.11105 | 1(Win) | true |
| Jsonifier | 2180.05 | 0.247704 | 1133.34ms | 25388 | 1280 | 968720 | 11106.1 | 0.2386 | 1.1326 | 2(Loss) | true |
| Glaze | 1454.88 | 0.47158 | 1693.66ms | 25388 | 320 | 1.97091e+06 | 16641.9 | 0.307013 | 1.69853 | 3(Loss) | true |
| simdjson (ondemand) | 1061.52 | 0.591689 | 2281.04ms | 25388 | 160 | 2.91414e+06 | 22808.8 | 0.0930793 | 2.32912 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2472.14 | 0.320782 | 1095.31ms | 25388 | 1280 | 1.2634e+06 | 9793.91 | 0.0382745 | 0.998581 | 1(Win) | true |
| Jsonifier | 2444.41 | 0.0804268 | 1114.52ms | 25388 | 40 | 2538.46 | 9905 | 0.0168294 | 1.00994 | 2(Loss) | true |
| Glaze | 1633.68 | 0.362138 | 1609.19ms | 25388 | 640 | 1.84354e+06 | 14820.5 | 0.041134 | 1.51246 | 3(Loss) | true |
| simdjson (ondemand) | 1204.97 | 0.11915 | 2211.59ms | 25388 | 30 | 17195.4 | 20093.3 | 0.380102 | 2.05183 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13586.3 | 0.137438 | 233.526ms | 31235 | 160 | 1452.83 | 2192.5 | 0.227531 | 0.179634 | 1(Win) | true |
| Glaze | 3764.23 | 0.364944 | 795.681ms | 31235 | 1280 | 1.06756e+06 | 7913.44 | 0.215684 | 0.65529 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14295.4 | 0.140403 | 213.375ms | 31235 | 160 | 1369.5 | 2083.75 | 0 | 0.170712 | 1(Win) | true |
| Glaze | 4198.08 | 0.059071 | 718.389ms | 31235 | 160 | 2810.93 | 7095.62 | 0.00880747 | 0.587231 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1516.29 | 0.321916 | 6927.43ms | 108313 | 160 | 7.6949e+06 | 68123.8 | 0.349241 | 1.63194 | 1(Win) | true |
| Jsonifier (two-stage) | 1124.39 | 0.41445 | 8999.44ms | 108313 | 40 | 5.79866e+06 | 91867.5 | 1.39093 | 2.20115 | 2(Loss) | true |
| Glaze | 922.496 | 0.363105 | 5920.56ms | 108313 | 80 | 1.32247e+07 | 111974 | 0.0480254 | 2.68298 | 3(Loss) | true |
| simdjson (ondemand) | 736.981 | 0.424391 | 7779.3ms | 108313 | 40 | 1.41527e+07 | 140160 | 0.317671 | 3.3587 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1804.94 | 0.0917012 | 6129.28ms | 108313 | 2560 | 7.05056e+06 | 57229.1 | 0.0839575 | 1.37101 | 1(Win) | true |
| Jsonifier (two-stage) | 1302.89 | 0.193845 | 8334.41ms | 108313 | 1280 | 3.02318e+07 | 79281.4 | 0.28378 | 1.89953 | 2(Loss) | true |
| Glaze | 1052.51 | 0.196368 | 5394.3ms | 108313 | 320 | 1.18851e+07 | 98141.9 | 0.552882 | 2.3516 | 3(Loss) | true |
| simdjson (ondemand) | 779.979 | 0.194194 | 7138.4ms | 108313 | 320 | 2.11649e+07 | 132433 | 0.679888 | 3.17344 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14072.9 | 0.1401 | 753.765ms | 108313 | 30 | 3172.41 | 7340 | 0.0453926 | 0.17508 | 1(Win) | true |
| Glaze | 2985.14 | 0.254252 | 3467.59ms | 108313 | 640 | 4.95379e+06 | 34603.1 | 0.436285 | 0.82847 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14498.6 | 0.186285 | 719.205ms | 108313 | 4890 | 861344 | 7124.52 | 0.248467 | 0.17011 | 1(Win) | true |
| Glaze | 3124.15 | 0.13249 | 3341.23ms | 108313 | 2560 | 4.91253e+06 | 33063.5 | 0.118284 | 0.791675 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1829.39 | 0.178824 | 5386.02ms | 183677 | 640 | 1.87642e+07 | 95752.3 | 0.284917 | 1.35293 | 1(Win) | true |
| Jsonifier | 1652.84 | 0.17245 | 5526.46ms | 183677 | 640 | 2.13774e+07 | 105980 | 0.505883 | 1.49749 | 2(Loss) | true |
| Glaze | 1345.61 | 0.140029 | 6682.31ms | 183677 | 640 | 2.12663e+07 | 130178 | 0.33245 | 1.83946 | 3(Loss) | true |
| simdjson (ondemand) | 1128.78 | 0.169059 | 8033.1ms | 183677 | 320 | 2.20251e+07 | 155183 | 0.0169126 | 2.19293 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2054.18 | 0.22306 | 9011.53ms | 183677 | 320 | 1.15778e+07 | 85274.1 | 0.625784 | 1.20483 | 1(Win) | true |
| Jsonifier | 1832.23 | 0.144617 | 5128.15ms | 183677 | 640 | 1.22339e+07 | 95603.6 | 0.320211 | 1.35085 | 2(Loss) | true |
| Glaze | 1561.65 | 0.269121 | 6044ms | 183677 | 160 | 1.458e+07 | 112169 | 0.0723831 | 1.58504 | 3(Loss) | true |
| simdjson (ondemand) | 1235.43 | 0.249342 | 7606.25ms | 183677 | 160 | 1.99979e+07 | 141787 | 0.162921 | 2.00357 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14157.9 | 0.0666043 | 1463.31ms | 213963 | 40 | 3685.9 | 14412.5 | 0.0404905 | 0.174509 | 1(Win) | true |
| Glaze | 3523.4 | 0.461009 | 5982.64ms | 213963 | 160 | 1.14049e+07 | 57913.1 | 0.508721 | 0.702304 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14461.4 | 0.0708717 | 1455.41ms | 213963 | 30 | 3000 | 14110 | 0.165094 | 0.170847 | 1(Win) | true |
| Glaze | 3775.14 | 0.426254 | 5458.38ms | 213963 | 80 | 4.24658e+06 | 54051.2 | 0.118083 | 0.655388 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 694.522 | 0.871284 | 8329.97ms | 1834197 | 40 | 1.92619e+10 | 2.5186e+06 | 0.692377 | 3.56472 | 1(Win) | true |
| Jsonifier (two-stage) | 583.68 | 0.323283 | 9425.17ms | 1834197 | 80 | 7.50928e+09 | 2.99689e+06 | 0.186498 | 4.24168 | 2(Loss) | true |
| Glaze | 195.951 | 0.468714 | 6315.35ms | 1834197 | 30 | 5.25212e+10 | 8.92687e+06 | 1.31625 | 12.6348 | 3(Loss) | true |
| simdjson (ondemand) | 125.953 | 0.812691 | 9839.51ms | 1834197 | 40 | 5.09546e+11 | 1.38879e+07 | 0.541825 | 19.6566 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 761.052 | 0.959605 | 8194.08ms | 1834197 | 30 | 1.45939e+10 | 2.29843e+06 | 0.531137 | 3.25307 | 1(Win) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 645.203 | 0.214464 | 9575.03ms | 1834197 | 160 | 5.40917e+09 | 2.71113e+06 | 2.82817 | 3.8372 | -(Loss) | false |
| Glaze | 203.085 | 1.82504 | 6141.81ms | 1834197 | 30 | 7.41313e+11 | 8.61328e+06 | 1.23481 | 12.191 | 3(Loss) | true |
| simdjson (ondemand) | 126.931 | 0.155449 | 9886.37ms | 1834197 | 30 | 1.37675e+10 | 1.37809e+07 | 1.00058 | 19.5052 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 813.748 | 0.205707 | 6745.18ms | 1834197 | 80 | 1.56423e+09 | 2.14959e+06 | 0.00837438 | 3.04232 | 1(Win) | true |
| Glaze | 533.086 | 1.22025 | 9930.36ms | 1833577 | 80 | 1.28172e+11 | 3.28021e+06 | 0.116663 | 4.64416 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 934.448 | 0.0581995 | 5899.24ms | 1834197 | 80 | 9.49532e+07 | 1.87194e+06 | 0.028321 | 2.64946 | 1(Win) | true |
| Glaze | 689.058 | 0.14902 | 8053.54ms | 1833577 | 160 | 2.2882e+09 | 2.53772e+06 | 0.377893 | 3.59301 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2147.01 | 0.391384 | 10420.5ms | 7351818 | 80 | 1.30682e+10 | 3.26558e+06 | 0.20273 | 1.15313 | 1(Win) | true |
| Jsonifier | 2012.66 | 0.286842 | 5329.91ms | 7351818 | 40 | 3.99386e+09 | 3.48356e+06 | 0.368327 | 1.23011 | 2(Loss) | true |
| Glaze | 701.176 | 0.314729 | 7111.11ms | 7351818 | 40 | 3.96159e+10 | 9.99925e+06 | 1.29086 | 3.53092 | 3(Loss) | true |
| simdjson (ondemand) | 483.858 | 0.193144 | 10284.6ms | 7351818 | 40 | 3.13311e+10 | 1.44903e+07 | 0.60153 | 5.1168 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2332.5 | 0.759981 | 5099.73ms | 7351818 | 80 | 4.17486e+10 | 3.00589e+06 | 0.0242382 | 1.06143 | 1(Win) | true |
| Jsonifier | 2261.46 | 0.269385 | 5167.43ms | 7351818 | 80 | 5.5802e+09 | 3.10032e+06 | 0.755589 | 1.09477 | 2(Loss) | true |
| Glaze | 730.235 | 0.229759 | 7018.77ms | 7351818 | 40 | 1.94657e+10 | 9.60134e+06 | 0.100354 | 3.39043 | 3(Loss) | true |
| simdjson (ondemand) | 490.644 | 0.953984 | 10278.8ms | 7351818 | 40 | 7.43359e+11 | 1.42899e+07 | 0.368824 | 5.04604 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 2153.82 | 0.18906 | 6736.66ms | 9930848 | 40 | 2.7645e+09 | 4.39722e+06 | 2.87722 | 1.14947 | -(Win) | false |
| Glaze | 1684.44 | 0.562755 | 8803.62ms | 9930228 | 30 | 3.0031e+10 | 5.62218e+06 | 0.752657 | 1.46978 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 3330.2 | 0.333026 | 8927.96ms | 9930848 | 30 | 2.69098e+09 | 2.84391e+06 | 0.0937967 | 0.743435 | 1(Tie) | true |
| Glaze STATISTICAL TIE | 3308.91 | 0.0554717 | 9004.64ms | 9930228 | 160 | 4.03285e+08 | 2.86203e+06 | 0.512367 | 0.748216 | 1(Tie) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 678.767 | 0.267721 | 8123.68ms | 1834197 | 40 | 1.90404e+09 | 2.57706e+06 | 0.910337 | 3.64745 | 1(Win) | true |
| Jsonifier (two-stage) | 597.388 | 0.280599 | 9193.99ms | 1834197 | 80 | 5.4006e+09 | 2.92813e+06 | 0.354163 | 4.14435 | 2(Loss) | true |
| simdjson (ondemand) | 219.857 | 0.413005 | 5608.91ms | 1834197 | 40 | 4.319e+10 | 7.9562e+06 | 0.349663 | 11.261 | 3(Loss) | true |
| Glaze | 194.336 | 0.924404 | 6296.36ms | 1834197 | 40 | 2.7693e+11 | 9.00106e+06 | 0.668597 | 12.7398 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 749.477 | 0.636853 | 8291.78ms | 1834197 | 160 | 3.53487e+10 | 2.33393e+06 | 0.317869 | 3.30334 | 1(Win) | true |
| Jsonifier (two-stage) | 678.362 | 0.395793 | 9264.55ms | 1834197 | 30 | 3.12484e+09 | 2.5786e+06 | 0.233688 | 3.64963 | 2(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 227.945 | 0.171654 | 5725.47ms | 1834197 | 40 | 6.94061e+09 | 7.67388e+06 | 8.37346 | 10.8614 | -(Loss) | false |
| Glaze | 204.666 | 0.316303 | 6344.62ms | 1834197 | 30 | 2.19244e+10 | 8.54672e+06 | 0.0757611 | 12.0968 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 843.83 | 0.245217 | 6626.56ms | 1834197 | 30 | 7.75182e+08 | 2.07296e+06 | 0.426972 | 2.93386 | 1(Win) | true |
| Glaze | 571.794 | 0.225607 | 9747.04ms | 1833577 | 160 | 7.61635e+09 | 3.05816e+06 | 0.69386 | 4.3297 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 943.242 | 0.093438 | 5736.31ms | 1834197 | 160 | 4.80411e+08 | 1.85448e+06 | 0.88112 | 2.62473 | 1(Win) | true |
| Glaze | 700.297 | 0.183945 | 7771.12ms | 1833577 | 40 | 8.43862e+08 | 2.49699e+06 | 1.43023 | 3.53533 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2192.37 | 0.220746 | 10084.7ms | 7351818 | 160 | 7.97384e+09 | 3.19802e+06 | 0.978177 | 1.12927 | 1(Win) | true |
| Jsonifier | 2104.69 | 0.257531 | 5064.69ms | 7351818 | 80 | 5.8879e+09 | 3.33124e+06 | 1.02706 | 1.17632 | 2(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 803.888 | 0.594751 | 6283.23ms | 7351818 | 40 | 1.07629e+11 | 8.72166e+06 | 3.82863 | 3.07979 | -(Loss) | false |
| Glaze | 715.423 | 0.268034 | 7060.82ms | 7351818 | 40 | 2.75996e+10 | 9.80014e+06 | 2.03999 | 3.46062 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2433 | 0.454142 | 10122.6ms | 7351818 | 40 | 6.85092e+09 | 2.88173e+06 | 0.563031 | 1.01759 | 1(Win) | true |
| Jsonifier | 2327.02 | 0.595153 | 5046.34ms | 7351818 | 30 | 9.64643e+09 | 3.01297e+06 | 0.380025 | 1.06393 | 2(Loss) | true |
| simdjson (ondemand) | 838.262 | 0.262997 | 6080.81ms | 7351818 | 40 | 1.93549e+10 | 8.36402e+06 | 0.277929 | 2.9535 | 3(Loss) | true |
| Glaze | 733.652 | 0.659307 | 6961.99ms | 7351818 | 30 | 1.19099e+11 | 9.55663e+06 | 0.066576 | 3.37464 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2477.25 | 0.43325 | 5669.48ms | 9930848 | 40 | 1.09741e+10 | 3.82311e+06 | 1.85926 | 0.999385 | 1(Win) | true |
| Glaze | 1233.78 | 1.32934 | 5310.72ms | 9930228 | 30 | 3.12344e+11 | 7.67574e+06 | 0.655718 | 2.00659 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3978.16 | 0.482339 | 7413.67ms | 9930848 | 160 | 2.10976e+10 | 2.3807e+06 | 0.227435 | 0.622344 | 1(Win) | true |
| Glaze | 3291.8 | 0.132248 | 9061.68ms | 9930228 | 40 | 5.79015e+08 | 2.87691e+06 | 0.613541 | 0.752109 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 708.647 | 0.208162 | 8141.35ms | 461466 | 80 | 1.33694e+08 | 621026 | 0.504466 | 3.49348 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 633.207 | 0.142874 | 8958.92ms | 461466 | 640 | 6.31066e+08 | 695015 | 1.02136 | 3.90972 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 630.43 | 0.267455 | 9155.98ms | 461466 | 30 | 1.04576e+08 | 698077 | 0.0539869 | 3.92689 | 2(Tie) | true |
| simdjson (ondemand) | 501 | 0.244775 | 5619.43ms | 461466 | 30 | 1.38695e+08 | 878420 | 0.14022 | 4.94147 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 885.777 | 0.590405 | 7383.16ms | 461466 | 640 | 5.50695e+09 | 496839 | 0.532959 | 2.79487 | 1(Win) | true |
| Jsonifier (two-stage) | 804.391 | 0.220653 | 8187.13ms | 461466 | 40 | 5.8294e+07 | 547108 | 0.128846 | 3.07767 | 2(Loss) | true |
| Glaze | 780.24 | 0.100129 | 8398.98ms | 461466 | 320 | 1.02069e+08 | 564042 | 0.259462 | 3.17288 | 3(Loss) | true |
| simdjson (ondemand) | 604.565 | 0.234099 | 5223.32ms | 461466 | 80 | 2.32318e+08 | 727942 | 0.0964118 | 4.09503 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3204.66 | 0.515729 | 7122.93ms | 461466 | 160 | 8.02562e+07 | 137328 | 1.98091 | 0.771862 | 1(Win) | true |
| Glaze | 2619.76 | 0.0870737 | 8701.04ms | 461466 | 2560 | 5.47733e+07 | 167988 | 0.00188347 | 0.944802 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9849.08 | 0.108307 | 4544.98ms | 461466 | 4890 | 1.14527e+07 | 44683.2 | 1.59382 | 0.251186 | 1(Win) | true |
| Glaze | 2820.71 | 0.0834252 | 8157.81ms | 461466 | 1280 | 2.16854e+07 | 156020 | 0.717971 | 0.877558 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 954.059 | 0.154713 | 9528.49ms | 728486 | 320 | 4.06159e+08 | 728192 | 0.752127 | 2.59489 | 1(Win) | true |
| Jsonifier | 922.935 | 0.211539 | 9841.45ms | 728486 | 80 | 2.02848e+08 | 752749 | 0.816429 | 2.68237 | 2(Loss) | true |
| Glaze | 874.659 | 0.641248 | 5049.11ms | 728486 | 80 | 2.07543e+09 | 794296 | 0.249127 | 2.83041 | 3(Loss) | true |
| simdjson (ondemand) | 706.83 | 0.538974 | 6161.88ms | 728486 | 80 | 2.24511e+09 | 982892 | 1.02319 | 3.50256 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1187.7 | 0.698947 | 8689.02ms | 728486 | 40 | 6.68618e+08 | 584945 | 0.177253 | 2.08434 | 1(Win) | true |
| Jsonifier | 1123.48 | 0.353437 | 9220.07ms | 728486 | 30 | 1.43305e+08 | 618383 | 0.856257 | 2.20359 | 2(Loss) | true |
| Glaze | 1026.39 | 0.259547 | 9834.55ms | 728486 | 30 | 9.2591e+07 | 676873 | 0.0408909 | 2.412 | 3(Loss) | true |
| simdjson (ondemand) | 866.395 | 0.0822405 | 5728.72ms | 728486 | 320 | 1.39166e+08 | 801873 | 0.0937357 | 2.85748 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3500.32 | 0.234103 | 5960.44ms | 837491 | 640 | 1.82616e+08 | 228177 | 0.372186 | 0.706937 | 1(Win) | true |
| Glaze | 1843.7 | 1.00582 | 5470.3ms | 837491 | 80 | 1.51885e+09 | 433201 | 0.112372 | 1.34246 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11281 | 0.148316 | 7305.9ms | 837491 | 1280 | 1.41141e+07 | 70800 | 0.641166 | 0.219341 | 1(Win) | true |
| Glaze | 3364.85 | 0.127966 | 6245.07ms | 837491 | 320 | 2.95235e+07 | 237364 | 0.144216 | 0.735653 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7922.1 | 0.123774 | 5731.92ms | 466906 | 2560 | 1.23901e+07 | 56206.8 | 0.376299 | 0.312329 | 1(Win) | true |
| Jsonifier (two-stage) | 7746.93 | 0.11564 | 5835.56ms | 466906 | 2560 | 1.13098e+07 | 57477.8 | 0.0507927 | 0.319378 | 2(Loss) | true |
| simdjson (ondemand) | 2994.73 | 0.0608723 | 7778.9ms | 466906 | 2560 | 2.09712e+07 | 148687 | 0.271671 | 0.826524 | 3(Loss) | true |
| Glaze | 2607.43 | 0.182263 | 8902.63ms | 466906 | 2560 | 2.48012e+08 | 170772 | 0.0784738 | 0.949302 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8373.4 | 0.575247 | 5822.06ms | 466906 | 80 | 7.48607e+06 | 53177.5 | 0.197843 | 0.295491 | 1(Win) | true |
| Jsonifier (two-stage) | 7935.86 | 0.341556 | 5846.79ms | 466906 | 320 | 1.17529e+07 | 56109.4 | 0.385777 | 0.311747 | 2(Loss) | true |
| simdjson (ondemand) | 3089.03 | 0.451959 | 7500.99ms | 466906 | 40 | 1.69774e+07 | 144148 | 0.0399056 | 0.801319 | 3(Loss) | true |
| Glaze | 2745.71 | 0.0824496 | 8427.6ms | 466906 | 2560 | 4.57685e+07 | 162172 | 0.348499 | 0.901532 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9420.37 | 0.282555 | 6772.42ms | 631514 | 320 | 1.04421e+07 | 63931.6 | 0.0981532 | 0.262673 | 1(Win) | true |
| Jsonifier | 8923.1 | 0.131495 | 6826.21ms | 631514 | 1280 | 1.00824e+07 | 67494.3 | 0.255732 | 0.277313 | 2(Loss) | true |
| simdjson (ondemand) | 3675.33 | 0.370134 | 8391.17ms | 631514 | 40 | 1.47146e+07 | 163865 | 0.329468 | 0.673478 | 3(Loss) | true |
| Glaze | 3400.06 | 0.156793 | 9317.9ms | 631514 | 320 | 2.4683e+07 | 177132 | 1.06386 | 0.728022 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9402.36 | 0.0946215 | 6640.96ms | 631514 | 2560 | 9.40398e+06 | 64054 | 0.0362112 | 0.263191 | 1(Win) | true |
| Jsonifier (two-stage) | 9247.89 | 0.166412 | 6792.85ms | 631514 | 1280 | 1.50336e+07 | 65123.9 | 0.274508 | 0.267594 | 2(Loss) | true |
| simdjson (ondemand) | 3731.91 | 0.185647 | 8386.77ms | 631514 | 160 | 1.43614e+07 | 161381 | 0.171273 | 0.66328 | 3(Loss) | true |
| Glaze | 3341.37 | 0.26165 | 9184.66ms | 631514 | 160 | 3.5586e+07 | 180243 | 0.319033 | 0.740606 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1274.94 | 1.24105 | 8901.11ms | 466906 | 160 | 3.00593e+09 | 349252 | 0.171014 | 1.94161 | 1(Win) | true |
| Jsonifier (two-stage) | 1112.82 | 0.967101 | 5097.12ms | 466906 | 160 | 2.39594e+09 | 400135 | 0.197824 | 2.22452 | 2(Loss) | true |
| Glaze | 1069.88 | 0.739742 | 5380.14ms | 466906 | 160 | 1.5166e+09 | 416194 | 0.326331 | 2.31382 | 3(Loss) | true |
| simdjson (ondemand) | 875.314 | 0.596815 | 6417.44ms | 466906 | 640 | 5.89915e+09 | 508704 | 1.00566 | 2.82814 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1797.12 | 0.156782 | 7504.21ms | 466906 | 320 | 4.82887e+07 | 247772 | 0.284732 | 1.3775 | 1(Win) | true |
| Jsonifier (two-stage) | 1502.41 | 0.103398 | 8789.59ms | 466906 | 640 | 6.01016e+07 | 296374 | 0.0494763 | 1.64771 | 2(Loss) | true |
| Glaze | 1398.95 | 0.34185 | 9370.19ms | 466906 | 30 | 3.55179e+07 | 318293 | 0.589252 | 1.76954 | 3(Loss) | true |
| simdjson (ondemand) | 1101.62 | 0.0842297 | 5522.13ms | 466906 | 640 | 7.41828e+07 | 404200 | 0.338449 | 2.2472 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 4757.68 | 0.0958754 | 9646.58ms | 475954 | 4890 | 4.09131e+07 | 95404.7 | 0.446988 | 0.520138 | 1(Win) | true |
| Jsonifier | 3768.58 | 0.301166 | 6234.72ms | 475954 | 1280 | 1.68421e+08 | 120445 | 2.06576 | 0.65636 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13395.5 | 0.111604 | 3600.46ms | 475954 | 40 | 57205.1 | 33885 | 0.523535 | 0.184713 | 1(Win) | true |
| Glaze | 5341.94 | 0.267631 | 8732.34ms | 475954 | 640 | 3.30968e+07 | 84970.2 | 0.222447 | 0.463291 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1499.17 | 1.23818 | 5243.09ms | 631514 | 80 | 1.97935e+09 | 401729 | 2.28743 | 1.65128 | 1(Win) | true |
| Jsonifier | 1279.7 | 0.383016 | 6141.57ms | 631514 | 40 | 1.2997e+08 | 470625 | 0.142922 | 1.93451 | 2(Loss) | true |
| Glaze | 1255.08 | 0.594327 | 6166.19ms | 631514 | 160 | 1.30134e+09 | 479855 | 0.384052 | 1.97239 | 3(Loss) | true |
| simdjson (ondemand) | 1162.95 | 0.372717 | 6805.53ms | 631514 | 40 | 1.49025e+08 | 517870 | 0.135352 | 2.12872 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1920.96 | 0.256686 | 9055.86ms | 631514 | 1280 | 8.28977e+08 | 313520 | 0.339118 | 1.28869 | 1(Win) | true |
| Jsonifier | 1624.78 | 0.237686 | 5379.06ms | 631514 | 320 | 2.48391e+08 | 370671 | 0.351186 | 1.52364 | 2(Loss) | true |
| Glaze | 1560.4 | 0.204624 | 5480.53ms | 631514 | 80 | 4.99e+07 | 385965 | 0.274741 | 1.58652 | 3(Loss) | true |
| simdjson (ondemand) | 1407 | 0.141295 | 5918.03ms | 631514 | 640 | 2.34105e+08 | 428044 | 0.182814 | 1.75944 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3905.46 | 0.188839 | 9186.04ms | 716365 | 2560 | 2.79351e+08 | 174929 | 0.795073 | 0.633515 | 1(Win) | true |
| Glaze | 2343.08 | 0.31734 | 7331.33ms | 716365 | 1280 | 1.09586e+09 | 291574 | 0.61933 | 1.05619 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10843.7 | 0.412599 | 6590.75ms | 716365 | 80 | 5.40582e+06 | 63002.5 | 0.334435 | 0.228201 | 1(Win) | true |
| Glaze | 5006.06 | 0.196428 | 7054.01ms | 716365 | 320 | 2.2995e+07 | 136470 | 0.190192 | 0.494474 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 964.484 | 0.322292 | 291.755ms | 2632 | 40 | 2814.1 | 2602.5 | 0.541401 | 2.50986 | 1(Win) | true |
| Jsonifier (two-stage) | 921.391 | 0.574993 | 279.078ms | 2632 | 1280 | 314065 | 2724.22 | 0.132093 | 2.65956 | 2(Loss) | true |
| Glaze | 806.683 | 0.29453 | 320.408ms | 2632 | 4890 | 410708 | 3111.6 | 0.240661 | 3.04 | 3(Loss) | true |
| simdjson (ondemand) | 640.197 | 0.519051 | 396.39ms | 2632 | 640 | 265060 | 3920.78 | 0.400889 | 3.83894 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1300.55 | 0.26714 | 235.611ms | 2632 | 80 | 2126.58 | 1930 | 0.129702 | 1.87405 | 1(Win) | true |
| Glaze | 1278.81 | 0.272128 | 234.923ms | 2632 | 4890 | 139513 | 1962.82 | 0.0701918 | 1.90636 | 2(Loss) | true |
| Jsonifier (two-stage) | 1218.11 | 0.132752 | 252.096ms | 2632 | 320 | 2394.59 | 2060.62 | 0.181653 | 2.00469 | 3(Loss) | true |
| simdjson (ondemand) | 1088.18 | 0.200812 | 270.63ms | 2632 | 30 | 643.678 | 2306.67 | 0.144718 | 2.25227 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9392.6 | 0.811772 | 30.3758ms | 2632 | 4890 | 23013.2 | 267.239 | 0.297979 | 0.238179 | 1(Win) | true |
| Glaze | 3272.78 | 0.518429 | 80.1531ms | 2632 | 4890 | 77308.2 | 766.953 | 0.0509372 | 0.723641 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10534.1 | 0.570396 | 27.6456ms | 2632 | 1280 | 2364.52 | 238.281 | 0.262985 | 0.207972 | 1(Win) | true |
| Glaze | 3825.78 | 0.211504 | 70.1974ms | 2632 | 1280 | 2464.79 | 656.094 | 0.0951701 | 0.614191 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1175.16 | 0.222934 | 283.17ms | 3370 | 4890 | 181772 | 2734.85 | 0.0386849 | 2.08335 | 1(Win) | true |
| Jsonifier | 1058.77 | 0.240362 | 307.545ms | 3370 | 4890 | 260314 | 3035.48 | 0.0802394 | 2.31544 | 2(Loss) | true |
| Glaze | 984.721 | 0.212807 | 353.527ms | 3370 | 80 | 3859.18 | 3263.75 | 0.191131 | 2.49035 | 3(Loss) | true |
| simdjson (ondemand) | 827.787 | 0.289991 | 401.467ms | 3370 | 40 | 5070.51 | 3882.5 | 0.192802 | 2.97303 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1547 | 0.321861 | 287.606ms | 3370 | 40 | 1788.46 | 2077.5 | 0.120192 | 1.5731 | 1(Win) | true |
| Jsonifier (two-stage) | 1522.27 | 0.125903 | 258.698ms | 3370 | 160 | 1130.5 | 2111.25 | 0.177305 | 1.60402 | 2(Loss) | true |
| Jsonifier | 1372.35 | 0.167069 | 275.449ms | 3370 | 160 | 2449.29 | 2341.88 | 0.133262 | 1.7815 | 3(Loss) | true |
| simdjson (ondemand) | 1348.48 | 0.290369 | 269.288ms | 3370 | 30 | 1436.78 | 2383.33 | 0.140056 | 1.81715 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10272.6 | 0.401717 | 37.4886ms | 3643 | 1280 | 2362.68 | 338.203 | 0.347705 | 0.220875 | 1(Win) | true |
| Glaze | 3240.07 | 0.364853 | 112.215ms | 3682 | 160 | 2501.57 | 1083.75 | 0.231214 | 0.738659 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11685.1 | 0.673328 | 32.94ms | 3643 | 4890 | 19598.1 | 297.321 | 0.243523 | 0.192099 | 1(Win) | true |
| Glaze | 3690.36 | 0.298122 | 99.1674ms | 3682 | 4890 | 39348.3 | 951.513 | 0.103591 | 0.649502 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 529.108 | 0.164388 | 848.023ms | 4630 | 4890 | 920289 | 8345.19 | 0.263274 | 4.66218 | 1(Win) | true |
| Jsonifier (two-stage) | 488.037 | 0.142622 | 926.637ms | 4630 | 40 | 6660.26 | 9047.5 | 0.119882 | 5.05173 | 2(Loss) | true |
| Glaze | 164.349 | 0.0939404 | 2732.32ms | 4630 | 4890 | 3.11489e+06 | 26866.7 | 0.899854 | 15.0459 | 3(Loss) | true |
| simdjson (ondemand) | 160.944 | 0.191802 | 2788.15ms | 4630 | 1280 | 3.54431e+06 | 27435.2 | 0.121162 | 15.3658 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 681.406 | 0.184921 | 846.898ms | 4630 | 40 | 5743.59 | 6480 | 0.0514139 | 3.61654 | 1(Win) | true |
| Jsonifier (two-stage) | 589.324 | 0.138402 | 922.633ms | 4630 | 40 | 4301.28 | 7492.5 | 0.167112 | 4.18091 | 2(Loss) | true |
| Glaze | 176.452 | 0.299845 | 2703.59ms | 4630 | 640 | 3.60317e+06 | 25023.9 | 0.185104 | 14.0149 | 3(Loss) | true |
| simdjson (ondemand) | 172.903 | 0.853395 | 2702.79ms | 4630 | 40 | 1.89984e+06 | 25537.5 | 0.0947217 | 14.2987 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1733.49 | 0.111098 | 259.648ms | 4630 | 320 | 2562.6 | 2547.19 | 0.159236 | 1.41123 | 1(Win) | true |
| Glaze | 1020.93 | 0.24489 | 421.499ms | 4630 | 40 | 4487.18 | 4325 | 0.115473 | 2.40809 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1758.39 | 0.219026 | 262.405ms | 4630 | 4890 | 147921 | 2511.1 | 0.0322371 | 1.39222 | 1(Win) | true |
| Glaze | 1120.69 | 0.230893 | 403.841ms | 4630 | 30 | 2482.76 | 3940 | 0 | 2.19587 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1195.41 | 0.100758 | 949.834ms | 11579 | 80 | 6930.38 | 9237.5 | 0 | 2.06569 | 1(Win) | true |
| Jsonifier | 1107.75 | 0.142534 | 1004.04ms | 11579 | 4890 | 987202 | 9968.51 | 0.1074 | 2.22819 | 2(Loss) | true |
| simdjson (ondemand) | 394.027 | 0.0927937 | 2872.33ms | 11579 | 40 | 27051.3 | 28025 | 0.18402 | 6.2764 | 3(Loss) | true |
| Glaze | 386.375 | 0.0757719 | 2897.39ms | 11579 | 30 | 14069 | 28580 | 0.0233209 | 6.39727 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1391.66 | 0.25703 | 971.892ms | 11579 | 2560 | 1.06484e+06 | 7934.84 | 0.0167407 | 1.7725 | 1(Win) | true |
| Jsonifier | 1360.34 | 0.115761 | 1008.92ms | 11579 | 40 | 3532.05 | 8117.5 | 0.2986 | 1.81504 | 2(Loss) | true |
| simdjson (ondemand) | 421.629 | 0.189503 | 2806.89ms | 11579 | 1280 | 3.15299e+06 | 26190.3 | 0.0107399 | 5.86581 | 3(Loss) | true |
| Glaze | 389.767 | 0.624475 | 2932.05ms | 11579 | 160 | 5.0082e+06 | 28331.2 | 0.0706433 | 6.34463 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4618.53 | 0.0911761 | 339.842ms | 14795 | 320 | 2482.76 | 3055 | 0.244898 | 0.530433 | 1(Win) | true |
| Glaze | 2809.98 | 0.115854 | 517.357ms | 14795 | 80 | 2707.28 | 5021.25 | 0.0249004 | 0.87661 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4914.1 | 0.125009 | 294.183ms | 14795 | 160 | 2061.32 | 2871.25 | 0.130776 | 0.497969 | 1(Win) | true |
| Glaze | 3133.73 | 0.380966 | 447.076ms | 14795 | 80 | 23538 | 4502.5 | 0.334262 | 0.784921 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 776.839 | 0.313273 | 418.049ms | 3223 | 30 | 4609.2 | 3956.67 | 0 | 3.16172 | 1(Win) | true |
| Jsonifier (two-stage) | 680.114 | 0.219783 | 462.742ms | 3223 | 160 | 15785.8 | 4519.38 | 0.0968992 | 3.61392 | 2(Loss) | true |
| Glaze | 461.211 | 0.193843 | 688.741ms | 3223 | 4890 | 816079 | 6664.4 | 0.0289724 | 5.34534 | 3(Loss) | true |
| simdjson (ondemand) | 422.014 | 0.178509 | 738.938ms | 3223 | 4890 | 826605 | 7283.39 | 0.0504404 | 5.84285 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 841.045 | 0.344591 | 427.421ms | 3223 | 2560 | 406005 | 3654.61 | 0.206929 | 2.9192 | 1(Win) | true |
| Jsonifier | 593.091 | 0.16764 | 375.618ms | 3223 | 40 | 3019.23 | 5182.5 | 0.208601 | 4.1563 | 2(Loss) | true |
| Glaze | 560.552 | 0.215666 | 625.835ms | 3223 | 30 | 4195.4 | 5483.33 | 0.182039 | 4.39006 | 3(Loss) | true |
| simdjson (ondemand) | 461.515 | 0.154405 | 772.488ms | 3223 | 30 | 3172.41 | 6660 | 0.1998 | 5.34383 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5310.92 | 0.795244 | 50.6224ms | 3223 | 80 | 1694.62 | 578.75 | 0.215517 | 0.443543 | 1(Win) | true |
| Glaze | 2577.13 | 0.381332 | 123.073ms | 3223 | 4890 | 101149 | 1192.68 | 0.251447 | 0.936068 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7680.48 | 0.953307 | 46.9975ms | 3223 | 2560 | 37260.6 | 400.195 | 0.303505 | 0.299438 | 1(Win) | true |
| Glaze | 2919.54 | 0.388907 | 107.918ms | 3223 | 4890 | 81977.2 | 1052.8 | 0.210901 | 0.822728 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1204.33 | 0.134623 | 481.538ms | 5839 | 80 | 3099.68 | 4623.75 | 0.027027 | 2.04334 | 1(Win) | true |
| Jsonifier | 1103.4 | 0.206697 | 523.183ms | 5839 | 30 | 3264.37 | 5046.67 | 0.0660066 | 2.23026 | 2(Loss) | true |
| simdjson (ondemand) | 744.639 | 0.131856 | 762.967ms | 5839 | 160 | 15556.2 | 7478.12 | 0.0250668 | 3.3113 | 3(Loss) | true |
| Glaze | 740.739 | 0.231317 | 762.807ms | 5839 | 2560 | 774106 | 7517.5 | 0.00207853 | 3.32961 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1531.21 | 0.279159 | 437.136ms | 5839 | 30 | 3091.95 | 3636.67 | 0.456204 | 1.60168 | 1(Win) | true |
| Jsonifier | 1343.72 | 0.20171 | 483.375ms | 5839 | 4890 | 341684 | 4144.11 | 0.218431 | 1.8296 | 2(Loss) | true |
| Glaze | 841.482 | 0.161305 | 735.363ms | 5839 | 40 | 4557.69 | 6617.5 | 0.238693 | 2.9295 | 3(Loss) | true |
| simdjson (ondemand) | 800.149 | 0.259788 | 821.396ms | 5839 | 2560 | 836787 | 6959.34 | 0.232397 | 3.08034 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7897.46 | 0.324061 | 88.1803ms | 6938 | 320 | 2358.84 | 837.812 | 0.112024 | 0.303052 | 1(Win) | true |
| Glaze | 3439.16 | 0.26714 | 189.523ms | 6960 | 80 | 2126.58 | 1930 | 0.520833 | 0.707703 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8818.45 | 0.373099 | 82.0389ms | 6938 | 320 | 2507.74 | 750.312 | 0.208681 | 0.27019 | 1(Win) | true |
| Glaze | 4397.56 | 0.183867 | 162.259ms | 6960 | 160 | 1232.31 | 1509.38 | 0.206612 | 0.551934 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 963.321 | 0.217106 | 484.899ms | 4857 | 4890 | 532900 | 4808.36 | 0.215844 | 2.55175 | 1(Win) | true |
| Glaze | 822.005 | 0.280952 | 589.888ms | 4857 | 40 | 10025.6 | 5635 | 0.558824 | 2.99934 | 2(Loss) | true |
| Jsonifier (two-stage) | 793.49 | 0.250566 | 635.108ms | 4857 | 40 | 8557.69 | 5837.5 | 0.0998289 | 3.10319 | 3(Loss) | true |
| simdjson (ondemand) | 644.514 | 0.191237 | 733.996ms | 4857 | 4890 | 923690 | 7186.81 | 0.250844 | 3.82555 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1508.18 | 0.18493 | 366.538ms | 4857 | 80 | 2580.7 | 3071.25 | 0.285714 | 1.62599 | 1(Win) | true |
| Glaze | 1380.83 | 0.35991 | 381.685ms | 4857 | 2560 | 373149 | 3354.49 | 0.0570923 | 1.77734 | 2(Loss) | true |
| Jsonifier (two-stage) | 1108.8 | 0.134492 | 476.99ms | 4857 | 80 | 2525.32 | 4177.5 | 0.0598086 | 2.21932 | 3(Loss) | true |
| simdjson (ondemand) | 869.843 | 0.228537 | 583.975ms | 4857 | 4890 | 724228 | 5325.09 | 0.941479 | 2.83153 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8124.64 | 0.268616 | 61.571ms | 4857 | 2560 | 6003.89 | 570.117 | 0.0754251 | 0.290018 | 1(Win) | true |
| Glaze | 2935.82 | 0.34716 | 161.041ms | 4857 | 4890 | 146705 | 1577.75 | 0.102856 | 0.82593 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9339.24 | 0.588669 | 57.3035ms | 4857 | 4890 | 41683.5 | 495.971 | 0.0619992 | 0.249965 | 1(Win) | true |
| Glaze | 3576.83 | 0.333667 | 135.279ms | 4857 | 80 | 1493.67 | 1295 | 0 | 0.673487 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1093.65 | 0.227441 | 622.077ms | 6701 | 30 | 5298.85 | 5843.33 | 0.397727 | 2.25429 | 1(Win) | true |
| Jsonifier | 1065.1 | 0.139065 | 656.375ms | 6701 | 80 | 5569.62 | 6000 | 0.0834028 | 2.31511 | 2(Loss) | true |
| Glaze | 1017.11 | 0.251104 | 658.505ms | 6701 | 2560 | 637219 | 6283.05 | 0.0435388 | 2.42225 | 3(Loss) | true |
| simdjson (ondemand) | 853.214 | 0.256547 | 784.142ms | 6701 | 40 | 14769.2 | 7490 | 0.178333 | 2.88392 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1682.62 | 0.222023 | 433.835ms | 6701 | 4890 | 347707 | 3798 | 0.0907392 | 1.46071 | 1(Win) | true |
| Jsonifier (two-stage) | 1472.27 | 0.100688 | 486.24ms | 6701 | 160 | 3056.21 | 4340.62 | 0.21645 | 1.67061 | 2(Loss) | true |
| Jsonifier | 1418.55 | 0.110988 | 517.077ms | 6701 | 80 | 2000 | 4505 | 0.111111 | 1.73498 | 3(Loss) | true |
| simdjson (ondemand) | 1203.75 | 0.509165 | 577.966ms | 6701 | 640 | 467636 | 5308.91 | 0.290527 | 2.04569 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7051.93 | 0.566137 | 92.066ms | 7376 | 40 | 1275.64 | 997.5 | 0.419463 | 0.340218 | 1(Win) | true |
| Glaze | 2931.72 | 0.319881 | 253.077ms | 7376 | 1280 | 75402.3 | 2399.38 | 0.149555 | 0.83267 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8697.75 | 0.393091 | 85.7899ms | 7376 | 80 | 808.544 | 808.75 | 0.154321 | 0.276034 | 1(Win) | true |
| Glaze | 3318.07 | 0.302129 | 218.373ms | 7376 | 40 | 1641.03 | 2120 | 0 | 0.737507 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1054.46 | 0.178866 | 164.703ms | 1691 | 320 | 2394.59 | 1529.38 | 0 | 2.30363 | 1(Win) | true |
| Jsonifier | 910.145 | 0.200385 | 181.961ms | 1691 | 320 | 4034.09 | 1771.88 | 0.141293 | 2.67494 | 2(Loss) | true |
| Jsonifier (two-stage) | 827.719 | 0.350502 | 204.683ms | 1691 | 4890 | 228041 | 1948.32 | 0.157996 | 2.94351 | 3(Loss) | true |
| simdjson (ondemand) | 539.804 | 0.333534 | 310.998ms | 1691 | 80 | 7943.04 | 2987.5 | 0.335852 | 4.55727 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1375.04 | 0.212404 | 144.506ms | 1691 | 320 | 1985.8 | 1172.81 | 0.292242 | 1.75501 | 1(Win) | true |
| Jsonifier | 1218.76 | 0.567118 | 165.812ms | 1691 | 2560 | 144159 | 1323.2 | 0.462661 | 1.98794 | 2(Loss) | true |
| Jsonifier (two-stage) | 1092.1 | 0.839401 | 181.033ms | 1691 | 30 | 4609.2 | 1476.67 | 0 | 2.22172 | 3(Loss) | true |
| simdjson (ondemand) | 711.6 | 0.129226 | 252.082ms | 1691 | 320 | 2744.51 | 2266.25 | 0 | 3.43635 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10220.3 | 1.03524 | 22.5107ms | 1996 | 320 | 1189.66 | 186.25 | 0 | 0.205807 | 1(Win) | true |
| Glaze | 3457.04 | 0.361433 | 58.9843ms | 1996 | 640 | 2534.82 | 550.625 | 0 | 0.668501 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12418.6 | 1.28764 | 18.6214ms | 1996 | 640 | 2493.13 | 153.281 | 0.708502 | 0.161357 | 1(Win) | true |
| Glaze | 4274.6 | 0.314539 | 47.9749ms | 1996 | 1280 | 2511.24 | 445.312 | 0.706714 | 0.536029 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1063.41 | 0.205268 | 201.999ms | 2158 | 320 | 5050.06 | 1935.31 | 0.402059 | 2.29022 | 1(Win) | true |
| Jsonifier | 909.878 | 0.159875 | 237.138ms | 2158 | 320 | 4184.56 | 2261.88 | 0.11065 | 2.68473 | 2(Loss) | true |
| Glaze | 740.298 | 0.134562 | 173.111ms | 2158 | 160 | 2238.99 | 2780 | 0.269058 | 3.30162 | 3(Loss) | true |
| simdjson (ondemand) | 679.966 | 0.314175 | 342.728ms | 2158 | 30 | 2712.64 | 3026.67 | 0 | 3.59314 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1545.44 | 0.335785 | 157.258ms | 2158 | 4890 | 97775.3 | 1331.68 | 0.1759 | 1.56815 | 1(Win) | true |
| Jsonifier (two-stage) | 1416.28 | 0.23167 | 181.501ms | 2158 | 320 | 3626.57 | 1453.12 | 0.0430293 | 1.71088 | 2(Loss) | true |
| Jsonifier | 1191.56 | 0.278091 | 208.524ms | 2158 | 4890 | 112812 | 1727.18 | 0.923737 | 2.04471 | 3(Loss) | true |
| simdjson (ondemand) | 883.748 | 0.154131 | 251.136ms | 2158 | 160 | 2061.32 | 2328.75 | 0.0536481 | 2.76505 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10515.7 | 0.340303 | 29.3949ms | 2866 | 4890 | 3825.72 | 259.918 | 0.557744 | 0.20992 | 1(Win) | true |
| Glaze | 3352.37 | 0.277825 | 86.0171ms | 2866 | 1280 | 6567.53 | 815.312 | 0.384763 | 0.708828 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13282.2 | 0.224202 | 24.1774ms | 2866 | 2560 | 544.915 | 205.781 | 0.0759878 | 0.161912 | 1(Win) | true |
| Glaze | 3930.06 | 0.215295 | 76.6299ms | 2866 | 640 | 1434.83 | 695.469 | 1.96035 | 0.59887 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1141.55 | 0.299128 | 384.692ms | 4390 | 40 | 4814.1 | 3667.5 | 0.204918 | 2.14854 | 1(Win) | true |
| Jsonifier (two-stage) | 949.618 | 0.172108 | 450.754ms | 4390 | 80 | 4606.01 | 4408.75 | 0.0283447 | 2.59361 | 2(Loss) | true |
| Glaze | 793.921 | 0.360241 | 533.787ms | 4390 | 1280 | 461925 | 5273.36 | 0.211407 | 3.0999 | 3(Loss) | true |
| simdjson (ondemand) | 491.123 | 0.355398 | 864.069ms | 4390 | 1280 | 1.17487e+06 | 8524.61 | 0.213081 | 5.02213 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1348.89 | 0.145492 | 369.363ms | 4390 | 80 | 1631.33 | 3103.75 | 0.200965 | 1.81673 | 1(Win) | true |
| Jsonifier (two-stage) | 1054.57 | 0.258267 | 453.688ms | 4390 | 40 | 4205.13 | 3970 | 0.421585 | 2.3271 | 2(Loss) | true |
| Glaze | 970.954 | 0.150226 | 525.421ms | 4390 | 160 | 6713.44 | 4311.88 | 0.276163 | 2.53106 | 3(Loss) | true |
| simdjson (ondemand) | 560.53 | 0.335944 | 797.52ms | 4390 | 1280 | 805891 | 7469.06 | 0.094227 | 4.39963 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8549.6 | 0.501637 | 53.0512ms | 4390 | 320 | 1930.94 | 489.688 | 0.448718 | 0.271071 | 1(Win) | true |
| Glaze | 2628.97 | 0.347412 | 192.7ms | 4390 | 40 | 1224.36 | 1592.5 | 0.46875 | 0.922289 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8555.06 | 0.385802 | 53.1975ms | 4390 | 320 | 1140.67 | 489.375 | 0.127877 | 0.274447 | 1(Win) | true |
| Glaze | 3115.63 | 0.415354 | 141.389ms | 4390 | 80 | 2492.09 | 1343.75 | 0.278293 | 0.774818 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1920.59 | 0.285401 | 481.318ms | 9378 | 30 | 5298.85 | 4656.67 | 0.431344 | 1.27967 | 1(Win) | true |
| Jsonifier | 1888.82 | 0.161302 | 504.146ms | 9378 | 40 | 2333.33 | 4735 | 0.0352113 | 1.30367 | 2(Loss) | true |
| Glaze | 1325.44 | 0.259491 | 731.172ms | 9378 | 2560 | 784848 | 6747.62 | 0.029533 | 1.85946 | 3(Loss) | true |
| simdjson (ondemand) | 1020.08 | 0.175121 | 898.26ms | 9378 | 40 | 9429.49 | 8767.5 | 0.0856164 | 2.41846 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2149.74 | 0.210942 | 475.187ms | 9378 | 4890 | 376606 | 4160.31 | 0.169796 | 1.14383 | 1(Win) | true |
| Jsonifier (two-stage) | 2123.1 | 0.193594 | 518.533ms | 9378 | 40 | 2660.26 | 4212.5 | 0.297619 | 1.15486 | 2(Loss) | true |
| Glaze | 1596.35 | 0.527909 | 614.314ms | 9378 | 640 | 559837 | 5602.5 | 0.0613189 | 1.54336 | 3(Loss) | true |
| simdjson (ondemand) | 1125.45 | 0.20628 | 858.733ms | 9378 | 2560 | 687898 | 7946.68 | 0.14676 | 2.1922 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12212.3 | 0.166829 | 94.6342ms | 11521 | 320 | 720.905 | 899.688 | 0.311634 | 0.196061 | 1(Win) | true |
| Glaze | 3459.84 | 0.215597 | 320.409ms | 11521 | 4890 | 229226 | 3175.66 | 0.346863 | 0.708865 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13909 | 0.418936 | 85.9688ms | 11521 | 4890 | 53553.9 | 789.939 | 0.0219084 | 0.17178 | 1(Win) | true |
| Glaze | 4001.74 | 0.118131 | 281.664ms | 11521 | 320 | 3366.38 | 2745.62 | 0.27391 | 0.611698 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1415.24 | 0.187045 | 326.423ms | 4669 | 80 | 2770.57 | 3146.25 | 0.438947 | 1.72983 | 1(Win) | true |
| Jsonifier (two-stage) | 1027.6 | 0.216327 | 441.61ms | 4669 | 4890 | 429665 | 4333.11 | 0.0256186 | 2.39354 | 2(Loss) | true |
| Glaze | 892.326 | 0.104545 | 517.367ms | 4669 | 80 | 2177.22 | 4990 | 0.0501253 | 2.7594 | 3(Loss) | true |
| simdjson (ondemand) | 673.972 | 0.124295 | 684.619ms | 4669 | 30 | 2022.99 | 6606.67 | 0.151592 | 3.65728 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1558.25 | 0.277019 | 307.191ms | 4669 | 40 | 2506.41 | 2857.5 | 0.0874126 | 1.57522 | 1(Win) | true |
| Jsonifier (two-stage) | 1107.64 | 0.184771 | 422.519ms | 4669 | 30 | 1655.17 | 4020 | 0.08285 | 2.22689 | 2(Loss) | true |
| Glaze | 987.844 | 0.146203 | 480.596ms | 4669 | 40 | 1737.18 | 4507.5 | 0.202952 | 2.49029 | 3(Loss) | true |
| simdjson (ondemand) | 658.197 | 0.0559145 | 714.231ms | 4669 | 160 | 2289.31 | 6765 | 0.0554017 | 3.74633 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11490.9 | 0.337627 | 42.8753ms | 4669 | 640 | 1095.46 | 387.5 | 0.0805802 | 0.200356 | 1(Win) | true |
| Glaze | 2725.78 | 0.44016 | 166.68ms | 4669 | 2560 | 132352 | 1633.55 | 0.240935 | 0.888354 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13563.7 | 0.383605 | 36.3262ms | 4669 | 1280 | 2029.88 | 328.281 | 0.382226 | 0.166919 | 1(Win) | true |
| Glaze | 3244.97 | 0.182828 | 146.907ms | 4669 | 320 | 2014.01 | 1372.19 | 0.11374 | 0.746057 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1722.03 | 0.215124 | 450.276ms | 7932 | 4890 | 436688 | 4392.8 | 0.170778 | 1.42822 | 1(Win) | true |
| Jsonifier | 1545.89 | 0.167815 | 507.57ms | 7932 | 30 | 2022.99 | 4893.33 | 0.0681663 | 1.59326 | 2(Loss) | true |
| Glaze | 1212.6 | 0.529843 | 619.064ms | 7932 | 640 | 699205 | 6238.28 | 0.0825867 | 2.03134 | 3(Loss) | true |
| simdjson (ondemand) | 1093.14 | 0.175283 | 704.956ms | 7932 | 30 | 4413.79 | 6920 | 0.0962464 | 2.25559 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1817.31 | 0.186238 | 430.979ms | 7932 | 40 | 2403.85 | 4162.5 | 0.301205 | 1.34908 | 1(Win) | true |
| Jsonifier | 1611.43 | 0.229572 | 488.94ms | 7932 | 4890 | 567924 | 4694.31 | 0.32227 | 1.52723 | 2(Loss) | true |
| Glaze | 1369.69 | 0.627459 | 564.747ms | 7932 | 320 | 384274 | 5522.81 | 0.153009 | 1.79868 | 3(Loss) | true |
| simdjson (ondemand) | 1075.53 | 0.124461 | 736.752ms | 7932 | 30 | 2298.85 | 7033.33 | 0 | 2.29352 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11060.7 | 0.446635 | 84.2777ms | 9249 | 4890 | 62034.9 | 797.464 | 0.2975 | 0.216192 | 1(Win) | true |
| Glaze | 3395.24 | 0.254252 | 264.45ms | 9249 | 4890 | 213348 | 2597.91 | 0.0757227 | 0.720279 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11985.4 | 0.365039 | 77.8964ms | 9249 | 320 | 2309.46 | 735.938 | 0.127226 | 0.198739 | 1(Win) | true |
| Glaze | 3680.97 | 0.166002 | 247.147ms | 9249 | 640 | 10126.8 | 2396.25 | 0.209096 | 0.663305 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 438.093 | 0.364037 | 1016.08ms | 4604 | 640 | 851941 | 10022.3 | 0.0576504 | 5.63011 | 1(Win) | true |
| Jsonifier (two-stage) | 427.756 | 0.267424 | 1050.19ms | 4604 | 2560 | 1.92894e+06 | 10264.5 | 0.138715 | 5.76674 | 2(Loss) | true |
| Glaze | 149.901 | 0.201471 | 2955.15ms | 4604 | 2560 | 8.91513e+06 | 29290.9 | 0.653712 | 16.4904 | 3(Loss) | true |
| simdjson (ondemand) | 97.1908 | 0.320052 | 4631.3ms | 4604 | 320 | 6.68978e+06 | 45176.2 | 0.0775344 | 25.456 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 564.136 | 0.15657 | 952.759ms | 4604 | 4890 | 726159 | 7783.09 | 0.135217 | 4.37304 | 1(Win) | true |
| Jsonifier (two-stage) | 545.431 | 0.176183 | 1012.47ms | 4604 | 30 | 6034.48 | 8050 | 0.0827472 | 4.5195 | 2(Loss) | true |
| Glaze | 165.292 | 0.168462 | 2770.56ms | 4604 | 4890 | 9.79219e+06 | 26563.4 | 0.145627 | 14.9624 | 3(Loss) | true |
| simdjson (ondemand) | 103.539 | 0.278694 | 4422.68ms | 4604 | 320 | 4.46964e+06 | 42406.6 | 0.103797 | 23.8972 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1388.37 | 0.172231 | 319.807ms | 4604 | 80 | 2373.42 | 3162.5 | 0.0789889 | 1.76332 | 1(Win) | true |
| Glaze | 818.533 | 0.173985 | 545.368ms | 4604 | 4890 | 425921 | 5364.13 | 0.020941 | 3.00852 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1466.02 | 0.144273 | 310.058ms | 4604 | 80 | 1493.67 | 2995 | 0 | 1.67275 | 1(Win) | true |
| Glaze | 864.516 | 0.381282 | 577.447ms | 4604 | 4890 | 1.83369e+06 | 5078.81 | 0.0671488 | 2.84729 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1588.54 | 0.208709 | 1106.43ms | 18245 | 30 | 15678.2 | 10953.3 | 0.182927 | 1.55306 | 1(Win) | true |
| Jsonifier | 1279.63 | 0.704662 | 1385.86ms | 18245 | 160 | 1.46892e+06 | 13597.5 | 0.584902 | 1.9288 | 2(Loss) | true |
| Glaze | 541.744 | 0.081263 | 3220.06ms | 18245 | 4890 | 3.33115e+06 | 32118.1 | 0.164741 | 4.56351 | 3(Loss) | true |
| simdjson (ondemand) | 354.014 | 0.341963 | 4950.09ms | 18245 | 160 | 4.51987e+06 | 49150 | 0.195446 | 6.98993 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1990.82 | 0.140934 | 1048.78ms | 18245 | 30 | 4551.72 | 8740 | 0.229358 | 1.23893 | 1(Win) | true |
| Jsonifier | 1586.12 | 0.114006 | 1266.72ms | 18245 | 40 | 6256.41 | 10970 | 0.152161 | 1.55679 | 2(Loss) | true |
| Glaze | 590.687 | 0.38936 | 3064.88ms | 18245 | 160 | 2.10473e+06 | 29456.9 | 0.0487763 | 4.18631 | 3(Loss) | true |
| simdjson (ondemand) | 385.297 | 0.152108 | 4836.04ms | 18245 | 1280 | 6.03966e+06 | 45159.4 | 0.0339192 | 6.42192 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 3192.06 | 0.400808 | 522.979ms | 24579 | 30 | 25988.5 | 7343.33 | 0.318761 | 0.771774 | 1(Tie) | true |
| Glaze STATISTICAL TIE | 3182.13 | 0.0798901 | 750.619ms | 24579 | 80 | 2770.57 | 7366.25 | 0.0849185 | 0.77433 | 1(Tie) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5163.52 | 0.346311 | 468.445ms | 24579 | 1280 | 316358 | 4539.61 | 0.0258211 | 0.476492 | 1(Win) | true |
| Glaze | 3718.72 | 0.234242 | 645.624ms | 24579 | 30 | 6540.23 | 6303.33 | 0.211977 | 0.663916 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 484.247 | 0.173183 | 918.607ms | 4604 | 4890 | 1.20575e+06 | 9067.1 | 0.257713 | 5.09465 | 1(Win) | true |
| Jsonifier (two-stage) | 451.256 | 0.29215 | 998.132ms | 4604 | 30 | 24241.4 | 9730 | 0.0342466 | 5.47465 | 2(Loss) | true |
| simdjson (ondemand) | 177.447 | 0.352487 | 2495.16ms | 4604 | 320 | 2.43426e+06 | 24743.8 | 0.00252595 | 13.9351 | 3(Loss) | true |
| Glaze | 147.92 | 0.14506 | 2984.81ms | 4604 | 2560 | 4.74624e+06 | 29683 | 0.00737007 | 16.7207 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 660.631 | 0.133678 | 838.336ms | 4604 | 80 | 6314.87 | 6646.25 | 0.0188111 | 3.73078 | 1(Win) | true |
| Jsonifier (two-stage) | 566.377 | 0.220739 | 916.543ms | 4604 | 4890 | 1.43195e+06 | 7752.29 | 0.664891 | 4.35531 | 2(Loss) | true |
| simdjson (ondemand) | 196.668 | 0.102661 | 2429.74ms | 4604 | 4890 | 2.56875e+06 | 22325.5 | 0.810843 | 12.5727 | 3(Loss) | true |
| Glaze | 165.957 | 0.132694 | 2851.68ms | 4604 | 2560 | 3.15521e+06 | 26457 | 0.0658931 | 14.9019 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1363.58 | 0.0747885 | 335.883ms | 4604 | 320 | 1855.8 | 3220 | 0.444444 | 1.79834 | 1(Win) | true |
| Glaze | 823.774 | 0.153189 | 568.853ms | 4604 | 40 | 2666.67 | 5330 | 0.124922 | 2.99023 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1444.31 | 0.258048 | 313.187ms | 4604 | 40 | 2461.54 | 3040 | 0 | 1.69769 | 1(Win) | true |
| Glaze | 877.558 | 0.178852 | 509.835ms | 4604 | 30 | 2402.3 | 5003.33 | 0.133067 | 2.79954 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1698.11 | 0.686483 | 1043.16ms | 18245 | 320 | 1.58331e+06 | 10246.6 | 0.131314 | 1.4534 | 1(Win) | true |
| Jsonifier | 1488.01 | 0.208808 | 1198.67ms | 18245 | 30 | 17885.1 | 11693.3 | 0.0570451 | 1.65913 | 2(Loss) | true |
| simdjson (ondemand) | 661.44 | 0.281084 | 2642.34ms | 18245 | 640 | 3.49912e+06 | 26305.9 | 0.00593937 | 3.73895 | 3(Loss) | true |
| Glaze | 551.999 | 0.093986 | 3214.13ms | 18245 | 4890 | 4.29186e+06 | 31521.4 | 0.346273 | 4.48099 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2128.85 | 0.184886 | 1012.04ms | 18245 | 30 | 6850.57 | 8173.33 | 0.0814996 | 1.15842 | 1(Win) | true |
| Jsonifier | 1802.17 | 0.283153 | 1121.54ms | 18245 | 1280 | 956645 | 9654.92 | 0.0961989 | 1.36951 | 2(Loss) | true |
| simdjson (ondemand) | 734.953 | 0.177617 | 2598.85ms | 18245 | 1280 | 2.26333e+06 | 23674.7 | 0.296771 | 3.36481 | 3(Loss) | true |
| Glaze | 601.297 | 0.167407 | 3065.34ms | 18245 | 1280 | 3.00376e+06 | 28937.1 | 0.138848 | 4.11387 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4843.05 | 0.187958 | 487.401ms | 24579 | 30 | 2482.76 | 4840 | 0.343171 | 0.510567 | 1(Win) | true |
| Glaze | 3275.32 | 0.197418 | 734.211ms | 24579 | 30 | 5988.51 | 7156.67 | 0.139535 | 0.752736 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5151.73 | 0.175965 | 456.007ms | 24579 | 40 | 2564.1 | 4550 | 0.364964 | 0.477149 | 1(Win) | true |
| Glaze | 3807.31 | 0.149462 | 670.006ms | 24579 | 30 | 2540.23 | 6156.67 | 0 | 0.647523 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 740.287 | 0.401118 | 667.352ms | 5094 | 640 | 443447 | 6562.34 | 0.183674 | 3.3219 | 1(Win) | true |
| Jsonifier (two-stage) | 666.609 | 0.436458 | 736.83ms | 5094 | 640 | 647500 | 7287.66 | 0.074985 | 3.6906 | 2(Loss) | true |
| Glaze | 595.163 | 0.186684 | 830.14ms | 5094 | 80 | 18575.9 | 8162.5 | 0.0919681 | 4.12924 | 3(Loss) | true |
| simdjson (ondemand) | 473.993 | 0.277103 | 1045.24ms | 5094 | 1280 | 1.03245e+06 | 10249.1 | 0.0969007 | 5.19844 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 877.802 | 0.329593 | 661.405ms | 5094 | 2560 | 851766 | 5534.3 | 0.0648938 | 2.80548 | 1(Win) | true |
| Jsonifier (two-stage) | 807.818 | 0.0902723 | 769.61ms | 5094 | 160 | 4715.41 | 6013.75 | 0.187422 | 3.04966 | 2(Loss) | true |
| Glaze | 763.689 | 0.41486 | 746.096ms | 5094 | 640 | 445726 | 6361.25 | 0.157449 | 3.22828 | 3(Loss) | true |
| simdjson (ondemand) | 572.626 | 0.300575 | 1013.89ms | 5094 | 1280 | 832324 | 8483.75 | 0.0460651 | 4.30926 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8213.71 | 0.527402 | 62.455ms | 5094 | 4890 | 47580.8 | 591.452 | 0.412293 | 0.287309 | 1(Win) | true |
| Glaze | 2795.48 | 0.3854 | 180.729ms | 5094 | 2560 | 114834 | 1737.81 | 0.206371 | 0.869916 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10807.4 | 0.599206 | 48.1083ms | 5094 | 4890 | 35476.3 | 449.509 | 0.204072 | 0.214932 | 1(Win) | true |
| Glaze | 3268.64 | 0.183756 | 155.064ms | 5094 | 160 | 1193.4 | 1486.25 | 0.0841751 | 0.739766 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1059.4 | 0.163762 | 745.932ms | 8051 | 40 | 5634.62 | 7247.5 | 0.380886 | 2.32412 | 1(Win) | true |
| Jsonifier | 1002.03 | 0.13773 | 810.438ms | 8051 | 40 | 4455.13 | 7662.5 | 0.0108743 | 2.45385 | 2(Loss) | true |
| Glaze | 855.65 | 0.206481 | 909.968ms | 8051 | 30 | 10298.9 | 8973.33 | 0.111566 | 2.87332 | 3(Loss) | true |
| simdjson (ondemand) | 725.255 | 0.196021 | 1072.87ms | 8051 | 30 | 12919.5 | 10586.7 | 0.347551 | 3.39583 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1275.69 | 0.098444 | 757.27ms | 8051 | 80 | 2808.54 | 6018.75 | 0.434243 | 1.93054 | 1(Win) | true |
| Jsonifier | 1169.54 | 0.149862 | 799.248ms | 8051 | 40 | 3871.79 | 6565 | 0.0761035 | 2.10805 | 2(Loss) | true |
| Glaze | 1097.77 | 0.214026 | 824.435ms | 8051 | 2560 | 573647 | 6994.18 | 0.257919 | 2.24636 | 3(Loss) | true |
| simdjson (ondemand) | 865.009 | 0.100694 | 1021.92ms | 8051 | 80 | 6390.82 | 8876.25 | 0.0422297 | 2.85548 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10616.1 | 0.220845 | 88.459ms | 9255 | 640 | 2157.64 | 831.406 | 0.662126 | 0.225771 | 1(Win) | true |
| Glaze | 3130.99 | 0.239343 | 285.607ms | 9255 | 4890 | 222607 | 2819 | 0.161383 | 0.782775 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12464.3 | 0.305986 | 74.4782ms | 9255 | 160 | 751.179 | 708.125 | 0.0881834 | 0.190779 | 1(Win) | true |
| Glaze | 3816.76 | 0.316846 | 243.955ms | 9255 | 40 | 2147.44 | 2312.5 | 0.108225 | 0.639322 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5207.64 | 0.48051 | 56.9153ms | 2889 | 320 | 2068.08 | 529.062 | 0.294464 | 0.449367 | 1(Win) | true |
| Jsonifier (two-stage) | 5089.82 | 0.399951 | 57.3778ms | 2889 | 4890 | 22919.9 | 541.309 | 0.249621 | 0.460963 | 2(Loss) | true |
| Glaze | 2877.46 | 0.580866 | 100.828ms | 2889 | 80 | 2474.68 | 957.5 | 0.789474 | 0.842004 | 3(Loss) | true |
| simdjson (ondemand) | 2774.24 | 0.179632 | 104.333ms | 2889 | 320 | 1018.42 | 993.125 | 0 | 0.86698 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5524.14 | 0.307275 | 54.8285ms | 2889 | 160 | 375.786 | 498.75 | 0.25 | 0.423133 | 1(Win) | true |
| Jsonifier (two-stage) | 5474.4 | 0.159374 | 55.5005ms | 2889 | 640 | 411.752 | 503.281 | 0.154991 | 0.426752 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 2946.7 | 0.816858 | 127.857ms | 2889 | 40 | 2333.33 | 935 | 0.531915 | 0.812894 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2935.66 | 0.144985 | 104.074ms | 2889 | 1280 | 2369.96 | 938.516 | 0.406234 | 0.818825 | 3(Tie) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 5864.8 | 0.251723 | 66.104ms | 3808 | 640 | 1554.94 | 619.219 | 0.126008 | 0.403638 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 5833.88 | 0.531991 | 73.1448ms | 3808 | 160 | 1754.72 | 622.5 | 0.201207 | 0.405119 | 1(Tie) | true |
| simdjson (ondemand) | 3365.51 | 0.211109 | 115.213ms | 3808 | 320 | 1660.56 | 1079.06 | 0.259965 | 0.717663 | 3(Loss) | true |
| Glaze | 3318.42 | 0.142963 | 115.286ms | 3808 | 320 | 783.307 | 1094.38 | 0.114351 | 0.724162 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 6211.17 | 0.246564 | 63.0614ms | 3808 | 640 | 1330.11 | 584.688 | 0.0534759 | 0.378175 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 6208.61 | 0.561598 | 62.4369ms | 3808 | 4890 | 52767.3 | 584.928 | 0.309269 | 0.378292 | 1(Tie) | true |
| simdjson (ondemand) | 3485.89 | 0.206187 | 107.911ms | 3808 | 1280 | 5906.07 | 1041.8 | 0.459545 | 0.690803 | 3(Loss) | true |
| Glaze | 3379.74 | 0.279791 | 112.229ms | 3808 | 4890 | 44198.2 | 1074.52 | 0.657558 | 0.712579 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1562.11 | 0.322811 | 181.802ms | 2889 | 80 | 2593.35 | 1763.75 | 0.0708215 | 1.56289 | 1(Win) | true |
| Glaze | 1304.99 | 0.168386 | 236.673ms | 2889 | 80 | 1011.08 | 2111.25 | 0.530035 | 1.87204 | 2(Loss) | true |
| Jsonifier (two-stage) | 1285.46 | 0.429325 | 221.323ms | 2889 | 30 | 2540.23 | 2143.33 | 0.155763 | 1.90189 | 3(Loss) | true |
| simdjson (ondemand) | 1189.94 | 0.530205 | 236.147ms | 2889 | 1280 | 192906 | 2315.39 | 0.0641502 | 2.05608 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1846.01 | 0.198552 | 167.469ms | 2889 | 80 | 702.532 | 1492.5 | 0.167785 | 1.32012 | 1(Win) | true |
| Jsonifier (two-stage) | 1497.88 | 0.452274 | 204.259ms | 2889 | 2560 | 177167 | 1839.38 | 0.687561 | 1.628 | 2(Loss) | true |
| Glaze | 1452 | 0.186915 | 210.2ms | 2889 | 80 | 1006.33 | 1897.5 | 0.396825 | 1.68573 | 3(Loss) | true |
| simdjson (ondemand) | 1316.69 | 0.204299 | 235.733ms | 2889 | 80 | 1462.03 | 2092.5 | 0.475624 | 1.86246 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7479.2 | 0.6268 | 41.5809ms | 2963 | 320 | 1794.57 | 377.812 | 0.738916 | 0.307174 | 1(Win) | true |
| Glaze | 3890.82 | 0.475383 | 80.4343ms | 2963 | 4890 | 58287.7 | 726.258 | 0.0225754 | 0.608868 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9110.69 | 0.391825 | 34.1994ms | 2963 | 640 | 945.202 | 310.156 | 0.150905 | 0.246795 | 1(Win) | true |
| Glaze | 4613.45 | 0.60749 | 65.7881ms | 2963 | 80 | 1107.59 | 612.5 | 0.409836 | 0.517609 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1669.7 | 0.252092 | 226.881ms | 3808 | 80 | 2405.06 | 2175 | 0.346021 | 1.46727 | 1(Win) | true |
| simdjson (ondemand) | 1549.89 | 0.167622 | 250.865ms | 3808 | 160 | 2468.16 | 2343.12 | 0.0799574 | 1.57604 | 2(Loss) | true |
| Glaze | 1440.61 | 0.340047 | 253.928ms | 3808 | 4890 | 359329 | 2520.88 | 0.207965 | 1.69615 | 3(Loss) | true |
| Jsonifier | 1400.81 | 0.214534 | 273.92ms | 3808 | 80 | 2474.68 | 2592.5 | 0.288462 | 1.73876 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1884.09 | 0.414858 | 217.828ms | 3808 | 40 | 2557.69 | 1927.5 | 0.0432526 | 1.29025 | 1(Win) | true |
| Glaze | 1650.72 | 0.230168 | 255.155ms | 3808 | 40 | 1025.64 | 2200 | 0 | 1.48315 | 2(Loss) | true |
| simdjson (ondemand) | 1632.18 | 0.218956 | 282.077ms | 3808 | 80 | 1898.73 | 2225 | 0.112486 | 1.49688 | 3(Loss) | true |
| Jsonifier | 1575.53 | 0.21692 | 256.173ms | 3808 | 40 | 1000 | 2305 | 0.0723589 | 1.55262 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7070.34 | 0.546932 | 62.6919ms | 4300 | 160 | 1610.06 | 580 | 0.215983 | 0.334544 | 1(Win) | true |
| Glaze | 3549.69 | 0.446488 | 121.451ms | 4300 | 4890 | 130102 | 1155.26 | 0.187162 | 0.679246 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7563.43 | 0.509986 | 58.5172ms | 4300 | 320 | 2446.61 | 542.188 | 0.97032 | 0.311169 | 1(Win) | true |
| Glaze | 4333.74 | 0.592824 | 100.227ms | 4300 | 80 | 2517.41 | 946.25 | 0.131926 | 0.553331 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3453.68 | 0.577252 | 6476.73ms | 466906 | 320 | 1.77246e+08 | 128928 | 0.00678627 | 0.716663 | 1(Win) | true |
| Glaze | 1755.22 | 0.141885 | 6558.55ms | 466906 | 320 | 4.14591e+07 | 253687 | 0.426051 | 1.41036 | 2(Loss) | true |
| simdjson (ondemand) | 1316.13 | 0.207894 | 8788.93ms | 466906 | 80 | 3.95764e+07 | 338322 | 0.0724686 | 1.88085 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3496.17 | 0.370486 | 6566.38ms | 466906 | 80 | 1.78118e+07 | 127361 | 0.0697323 | 0.707964 | 1(Win) | true |
| Glaze | 1750.74 | 0.328126 | 6663.98ms | 466906 | 80 | 5.5717e+07 | 254336 | 0.474549 | 1.41399 | 2(Loss) | true |
| simdjson (ondemand) | 1319.94 | 0.213325 | 8671.79ms | 466906 | 80 | 4.14311e+07 | 337346 | 0.370051 | 1.87544 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 3371.5 | 0.302376 | 5321.37ms | 699405 | 80 | 2.86284e+07 | 197836 | 0.348189 | 0.734229 | 1(Win) | true |
| Jsonifier | 2607.5 | 0.187506 | 6788.62ms | 699405 | 1280 | 2.94473e+08 | 255802 | 0.619273 | 0.949091 | 2(Loss) | true |
| simdjson (ondemand) | 1408.04 | 0.609153 | 6870.13ms | 767297 | 320 | 3.20703e+09 | 519697 | 0.408658 | 1.75806 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4471.51 | 0.613051 | 7928.32ms | 699405 | 40 | 3.34505e+07 | 149168 | 1.70049 | 0.553574 | 1(Win) | true |
| Glaze | 3277.7 | 0.176402 | 5437.08ms | 699405 | 640 | 8.24721e+07 | 203498 | 0.988259 | 0.755234 | 2(Loss) | true |
| simdjson (ondemand) | 1462.9 | 0.207615 | 6890.58ms | 767297 | 80 | 8.62791e+07 | 500206 | 0.637527 | 1.6921 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3079.08 | 0.462751 | 5576.76ms | 631514 | 30 | 2.45776e+07 | 195597 | 0.806343 | 0.803948 | 1(Win) | true |
| Glaze | 2503.64 | 0.145972 | 6528.92ms | 631514 | 320 | 3.94556e+07 | 240553 | 0.000519633 | 0.988767 | 2(Loss) | true |
