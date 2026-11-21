# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson (AVX512)
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.52.37029.0 compiler).  

Latest Results: (Nov 21, 2026)
#### Using the following commits:
----
| Jsonifier: [16b6b42](https://github.com/nihilai-collective/Jsonifier/commit/16b6b42)  
| Glaze: [fc0b48a0](https://github.com/stephenberry/glaze/commit/fc0b48a0)  
| simdjson: [81c2d7212](https://github.com/simdjson/simdjson/commit/81c2d7212)  

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
| Jsonifier | 503.986 | 0.30062 | 173.486ms | 905 | 80 | 2120.25 | 1712.5 | 0.145773 | 4.83569 | 1(Win) | true |
| Jsonifier (two-stage) | 494.068 | 0.232164 | 182.527ms | 905 | 160 | 2631.68 | 1746.88 | 0.395115 | 4.93035 | 2(Loss) | true |
| Glaze | 490.471 | 0.142734 | 184.265ms | 905 | 640 | 4037.46 | 1759.69 | 0.459608 | 4.9707 | 3(Loss) | true |
| simdjson (ondemand) | 157.352 | 0.167069 | 575.152ms | 905 | 40 | 3358.97 | 5485 | 0.335366 | 15.6502 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 619.803 | 0.24821 | 145.571ms | 905 | 80 | 955.696 | 1392.5 | 0.179856 | 3.92141 | 1(Win) | true |
| Jsonifier (two-stage) | 572.284 | 0.64962 | 156.296ms | 905 | 1280 | 122858 | 1508.12 | 0.0103616 | 4.24968 | 2(Loss) | true |
| Glaze | 564.274 | 0.284645 | 160.696ms | 905 | 640 | 12131.2 | 1529.53 | 0.112497 | 4.313 | 3(Loss) | true |
| simdjson (ondemand) | 163.849 | 0.142383 | 532.662ms | 905 | 40 | 2250 | 5267.5 | 0.26967 | 14.9865 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 836.393 | 0.269448 | 107.297ms | 905 | 4890 | 37803.9 | 1031.9 | 0.513362 | 2.88117 | 1(Win) | true |
| Glaze | 65.0952 | 1.33544 | 1369.11ms | 905 | 2560 | 8.02585e+07 | 13258.7 | 1.71837 | 37.9457 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1410.9 | 0.211123 | 72.922ms | 905 | 640 | 1067.46 | 611.719 | 0.229358 | 1.67817 | 1(Win) | true |
| Glaze | 502.762 | 0.403133 | 203.935ms | 905 | 30 | 1436.78 | 1716.67 | 0 | 4.87145 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 810.253 | 0.130611 | 222.243ms | 1811 | 320 | 2480.31 | 2131.56 | 0.220394 | 3.01645 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 804.81 | 0.407079 | 235.709ms | 1811 | 2560 | 195365 | 2145.98 | 0.129072 | 3.03819 | 1(Tie) | true |
| Glaze | 415.836 | 0.223052 | 394.48ms | 1811 | 30 | 2574.71 | 4153.33 | 0 | 5.90869 | 3(Loss) | true |
| simdjson (ondemand) | 317.104 | 0.441147 | 547.676ms | 1811 | 1280 | 738940 | 5446.48 | 0.144666 | 7.76398 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1111.28 | 0.313823 | 158.9ms | 1811 | 4890 | 116323 | 1554.15 | 0.149203 | 2.18905 | 1(Win) | true |
| Jsonifier (two-stage) | 1079.88 | 0.293978 | 164.319ms | 1811 | 4890 | 108099 | 1599.35 | 0.0262552 | 2.25377 | 2(Loss) | true |
| Glaze | 503.529 | 0.213936 | 357.614ms | 1811 | 40 | 2153.85 | 3430 | 0.0972763 | 4.87624 | 3(Loss) | true |
| simdjson (ondemand) | 357.075 | 0.187686 | 507.551ms | 1811 | 4890 | 402985 | 4836.81 | 0.106986 | 6.89195 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 435.063 | 0.128347 | 446.193ms | 1997 | 80 | 2525.32 | 4377.5 | 0.114351 | 5.64273 | 1(Win) | true |
| Glaze | 106.17 | 0.92039 | 1656.53ms | 1798 | 4890 | 1.08051e+08 | 16150.6 | 0.0246201 | 23.2719 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 551.626 | 0.162734 | 370.007ms | 1997 | 80 | 2525.32 | 3452.5 | 0 | 4.45734 | 1(Win) | true |
| Glaze | 388.602 | 0.101792 | 482.521ms | 1798 | 80 | 1613.92 | 4412.5 | 0.0566893 | 6.33075 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1456.31 | 0.179329 | 254.352ms | 3862 | 320 | 6582.19 | 2529.06 | 0.111084 | 1.68238 | 1(Win) | true |
| Jsonifier (two-stage) | 1423.59 | 0.118376 | 271.861ms | 3862 | 320 | 3001.47 | 2587.19 | 0.375849 | 1.72111 | 2(Loss) | true |
| Glaze | 912.409 | 0.221682 | 418.902ms | 3862 | 30 | 2402.3 | 4036.67 | 0.16488 | 2.69043 | 3(Loss) | true |
| simdjson (ondemand) | 630.194 | 0.235518 | 607.154ms | 3862 | 2560 | 485025 | 5844.38 | 0.0334301 | 3.90973 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1963.01 | 0.25518 | 195.15ms | 3862 | 80 | 1833.86 | 1876.25 | 0.334225 | 1.2377 | 1(Win) | true |
| Jsonifier (two-stage) | 1790.81 | 0.447416 | 208.681ms | 3862 | 30 | 2540.23 | 2056.67 | 0.162338 | 1.36394 | 2(Loss) | true |
| Glaze | 1097.79 | 0.18291 | 346.846ms | 3862 | 80 | 3012.66 | 3355 | 0.0744602 | 2.24014 | 3(Loss) | true |
| simdjson (ondemand) | 711.193 | 0.177475 | 582.562ms | 3862 | 80 | 6757.91 | 5178.75 | 0.0724638 | 3.46094 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 419.121 | 0.202627 | 909.847ms | 3862 | 2560 | 811673 | 8787.66 | 0.68747 | 5.8835 | 1(Win) | true |
| Glaze | 299.634 | 0.819462 | 1251.25ms | 3862 | 4890 | 4.96147e+07 | 12292 | 0.592079 | 8.24079 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3507.7 | 0.995206 | 115.951ms | 3862 | 30 | 3275.86 | 1050 | 0.318471 | 0.688244 | 1(Win) | true |
| Glaze | 1656.31 | 0.31719 | 236.464ms | 3862 | 2560 | 127357 | 2223.67 | 0.03163 | 1.4761 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 926.047 | 0.191921 | 1043.28ms | 9578 | 80 | 28669.3 | 9863.75 | 0.541971 | 2.66099 | 1(Win) | true |
| Jsonifier (two-stage) | 888.735 | 0.138065 | 1059.41ms | 9578 | 4890 | 984645 | 10277.9 | 0.736786 | 2.7716 | 2(Loss) | true |
| Glaze | 743.246 | 0.183256 | 1278.22ms | 9578 | 2560 | 1.2985e+06 | 12289.7 | 0.571698 | 3.31894 | 3(Loss) | true |
| simdjson (ondemand) | 647.975 | 0.196813 | 1466.8ms | 9578 | 30 | 23092 | 14096.7 | 0.475172 | 3.80842 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1426.83 | 0.259791 | 871.174ms | 9578 | 1280 | 354047 | 6401.8 | 0.248348 | 1.72742 | 1(Win) | true |
| Jsonifier (two-stage) | 1404.74 | 0.116647 | 876.574ms | 9578 | 40 | 2301.28 | 6502.5 | 0.115207 | 1.75475 | 2(Loss) | true |
| Glaze | 1090.44 | 0.211729 | 1116.71ms | 9578 | 30 | 9436.78 | 8376.67 | 0.23819 | 2.26457 | 3(Loss) | true |
| simdjson (ondemand) | 873.22 | 0.273439 | 1283.36ms | 9578 | 1280 | 1.04721e+06 | 10460.5 | 0.185565 | 2.82725 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1271.3 | 0.265624 | 761.731ms | 9578 | 80 | 29139.2 | 7185 | 0.0347826 | 1.94062 | 1(Win) | true |
| Glaze | 650.785 | 1.11456 | 1420.09ms | 9578 | 4890 | 1.19671e+08 | 14035.8 | 0.28599 | 3.79644 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7510.21 | 0.240546 | 134.302ms | 9578 | 160 | 1369.5 | 1216.25 | 0.61287 | 0.322361 | 1(Win) | true |
| Glaze | 4154.31 | 0.0988825 | 300.17ms | 9578 | 80 | 378.165 | 2198.75 | 0.170843 | 0.587935 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1398.75 | 0.154956 | 283.675ms | 3873 | 160 | 2678.85 | 2640.62 | 0.023663 | 1.75158 | 1(Win) | true |
| Jsonifier (two-stage) | 1366.73 | 0.247425 | 278.734ms | 3873 | 40 | 1788.46 | 2702.5 | 0.153941 | 1.79637 | 2(Loss) | true |
| Glaze | 1034.16 | 0.0789297 | 372.556ms | 3873 | 320 | 2543.01 | 3571.56 | 0.530896 | 2.37837 | 3(Loss) | true |
| simdjson (ondemand) | 663.12 | 0.175357 | 586.308ms | 3873 | 30 | 2862.07 | 5570 | 0.179856 | 3.71233 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1788.66 | 0.259871 | 215.311ms | 3873 | 80 | 2303.8 | 2065 | 0.486618 | 1.36515 | 1(Win) | true |
| Jsonifier (two-stage) | 1734.08 | 0.170621 | 219.16ms | 3873 | 160 | 2113.21 | 2130 | 0.058651 | 1.41224 | 2(Loss) | true |
| Glaze | 1225.07 | 0.133246 | 303.469ms | 3873 | 80 | 1291.14 | 3015 | 0.0829876 | 2.00085 | 3(Loss) | true |
| simdjson (ondemand) | 737.61 | 0.110485 | 533.464ms | 3873 | 40 | 1224.36 | 5007.5 | 0.3813 | 3.34125 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 438.082 | 0.693456 | 900.737ms | 3873 | 160 | 546942 | 8431.25 | 0.671642 | 5.62613 | 1(Win) | true |
| Glaze | 326.86 | 0.682809 | 1140.27ms | 3873 | 4890 | 2.91125e+07 | 11300.2 | 1.59092 | 7.55106 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3740.33 | 0.536278 | 115.327ms | 3873 | 40 | 1121.79 | 987.5 | 0.0844595 | 0.648477 | 1(Win) | true |
| Glaze | 1744.76 | 0.385194 | 224.257ms | 3873 | 2560 | 170224 | 2116.95 | 0.467168 | 1.40003 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 720.401 | 0.574958 | 6596.98ms | 94653 | 2560 | 1.32872e+09 | 125303 | 0.0203923 | 3.4358 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 706.621 | 1.8398 | 6704.49ms | 94653 | 320 | 1.76761e+09 | 127746 | 0.297555 | 3.50276 | 1(Tie) | true |
| simdjson (ondemand) | 702.876 | 0.595578 | 6736.04ms | 94653 | 1280 | 7.48856e+08 | 128427 | 1.46644 | 3.52157 | 3(Loss) | true |
| Glaze DID NOT CONVERGE | 673.955 | 1.00996 | 7266.92ms | 94653 | 640 | 1.1711e+09 | 133938 | 2.79558 | 3.6728 | -(Loss) | false |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1260.49 | 0.269816 | 9427.04ms | 94653 | 160 | 5.97377e+06 | 71613.8 | 0.577578 | 1.96345 | 1(Win) | true |
| simdjson (ondemand) | 1172.26 | 0.350874 | 5063.46ms | 94653 | 30 | 2.18999e+06 | 77003.3 | 0.190831 | 2.11098 | 2(Loss) | true |
| Jsonifier (two-stage) | 1135.52 | 0.295847 | 5029.61ms | 94653 | 160 | 8.84979e+06 | 79495 | 0.0629366 | 2.17956 | 3(Loss) | true |
| Glaze | 1093.36 | 0.132834 | 5321.92ms | 94653 | 640 | 7.6973e+06 | 82560.2 | 0.189045 | 2.26362 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11743.5 | 0.0821218 | 803.681ms | 94653 | 30 | 1195.4 | 7686.67 | 0.0866551 | 0.209659 | 1(Win) | true |
| Glaze | 4794.17 | 0.709171 | 2024.59ms | 94653 | 80 | 1.42638e+06 | 18828.8 | 0.219561 | 0.51576 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11628.6 | 0.205316 | 791.244ms | 94653 | 2560 | 650275 | 7762.58 | 0.177446 | 0.212086 | 1(Win) | true |
| Glaze | 5288.87 | 0.133031 | 1763.64ms | 94653 | 4890 | 2.52092e+06 | 17067.6 | 0.078966 | 0.467372 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1006.84 | 0.709947 | 6287.98ms | 124597 | 640 | 4.49293e+08 | 118018 | 0.711163 | 2.45835 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 945.693 | 0.427189 | 6421.2ms | 124597 | 2560 | 7.37557e+08 | 125649 | 1.58687 | 2.61738 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 935.977 | 0.349514 | 6616.57ms | 124597 | 2560 | 5.04028e+08 | 126953 | 0.996636 | 2.64444 | 2(Tie) | true |
| Glaze | 866.316 | 0.94954 | 7110.69ms | 124597 | 320 | 5.428e+08 | 137161 | 0.438444 | 2.85717 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1510.66 | 0.220998 | 9842.97ms | 124597 | 320 | 9.66966e+06 | 78657.8 | 0.12182 | 1.63839 | 1(Win) | true |
| simdjson (ondemand) | 1462.42 | 0.392844 | 5085.21ms | 124597 | 80 | 8.15088e+06 | 81252.5 | 0.12014 | 1.69237 | 2(Loss) | true |
| Jsonifier | 1397.91 | 0.183711 | 5171.63ms | 124597 | 640 | 1.56066e+07 | 85001.9 | 0.260968 | 1.77052 | 3(Loss) | true |
| Glaze | 1338.72 | 0.261072 | 5611.17ms | 124597 | 160 | 8.5916e+06 | 88760 | 0.528067 | 1.84881 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11622.4 | 0.0764983 | 1244.37ms | 136037 | 40 | 2916.67 | 11162.5 | 0.126752 | 0.212639 | 1(Win) | true |
| Glaze | 4026.83 | 0.823126 | 3385.71ms | 136076 | 640 | 4.50349e+07 | 32226.9 | 0.109695 | 0.614213 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11318.2 | 0.0676307 | 1203.91ms | 136037 | 40 | 2403.85 | 11462.5 | 0.0800349 | 0.218196 | 1(Win) | true |
| Glaze | 4248.03 | 0.174617 | 3150.1ms | 136076 | 1280 | 3.64225e+06 | 30548.8 | 0.0754997 | 0.582303 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 563.243 | 1.8975 | 5705.48ms | 2251027 | 40 | 2.09215e+11 | 3.8114e+06 | 3.99121 | 4.39534 | -(Win) | false |
| Jsonifier (two-stage) | 531.675 | 1.68938 | 6132.51ms | 2251027 | 80 | 3.72233e+11 | 4.0377e+06 | 1.55238 | 4.65645 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 183.661 | 1.06468 | 8293.07ms | 2251027 | 40 | 6.19473e+11 | 1.16886e+07 | 0.0662172 | 13.4802 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 183.319 | 1.4707 | 8255.26ms | 2251027 | 30 | 8.89847e+11 | 1.17105e+07 | 0.273138 | 13.5052 | 3(Tie) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 706.386 | 1.67581 | 5644.41ms | 2251027 | 40 | 1.0375e+11 | 3.03906e+06 | 1.87559 | 3.50476 | 1(Win) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 640.122 | 0.935871 | 6076.49ms | 2251027 | 30 | 2.95522e+10 | 3.35365e+06 | 2.89879 | 3.86746 | -(Loss) | false |
| simdjson (ondemand) | 198.421 | 1.05168 | 8082.76ms | 2251027 | 30 | 3.88397e+11 | 1.08191e+07 | 1.46555 | 12.4774 | 3(Loss) | true |
| Glaze | 191.963 | 1.01917 | 8247.83ms | 2251027 | 40 | 5.19612e+11 | 1.11832e+07 | 0.987481 | 12.8971 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 929.312 | 0.138553 | 6766.91ms | 2090326 | 80 | 7.06682e+08 | 2.14512e+06 | 0.162317 | 2.664 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 653.057 | 0.420943 | 9736.31ms | 2090234 | 30 | 4.95284e+09 | 3.05242e+06 | 3.41531 | 3.79087 | -(Loss) | false |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1363.37 | 0.11871 | 9431.99ms | 2090326 | 40 | 1.20513e+08 | 1.46218e+06 | 0.368858 | 1.81593 | 1(Win) | true |
| Glaze | 895.973 | 0.142975 | 6916.72ms | 2090234 | 160 | 1.61897e+09 | 2.22485e+06 | 0.980457 | 2.76324 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1183.74 | 1.33651 | 6556.31ms | 5373214 | 40 | 1.33894e+11 | 4.32889e+06 | 1.69614 | 2.0914 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1171.87 | 0.683716 | 6670.65ms | 5373214 | 80 | 7.1508e+10 | 4.37277e+06 | 1.34287 | 2.11263 | 1(Tie) | true |
| simdjson (ondemand) | 426.731 | 1.30684 | 8470.27ms | 5373214 | 30 | 7.38795e+11 | 1.20083e+07 | 0.298545 | 5.80176 | 3(Loss) | true |
| Glaze | 403.345 | 0.849082 | 9033.76ms | 5373214 | 40 | 4.6545e+11 | 1.27045e+07 | 1.9438 | 6.13821 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1464.16 | 1.13732 | 6409.21ms | 5373214 | 40 | 6.33741e+10 | 3.49981e+06 | 0.343714 | 1.6909 | 1(Win) | true |
| Jsonifier | 1408.06 | 1.48962 | 6689.96ms | 5373214 | 40 | 1.17553e+11 | 3.63925e+06 | 1.90302 | 1.75822 | 2(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 469.767 | 1.25129 | 8379.73ms | 5373214 | 30 | 5.58906e+11 | 1.09082e+07 | 2.515 | 5.27021 | -(Loss) | false |
| Glaze | 430.206 | 0.666403 | 9215.47ms | 5373214 | 30 | 1.89021e+11 | 1.19113e+07 | 0.0729254 | 5.75482 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 2105.18 | 0.767036 | 9868.9ms | 6661989 | 80 | 4.28696e+10 | 3.01796e+06 | 3.05938 | 1.176 | -(Win) | false |
| Glaze | 1081.56 | 0.781687 | 8772ms | 6661897 | 40 | 8.4337e+10 | 5.87417e+06 | 0.17146 | 2.28885 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3997.5 | 0.22664 | 5157.32ms | 6661989 | 30 | 3.89246e+08 | 1.58933e+06 | 0.62978 | 0.61933 | 1(Win) | true |
| Glaze | 2498.38 | 0.10813 | 8115.48ms | 6661897 | 30 | 2.26824e+08 | 2.54296e+06 | 0.679522 | 0.990961 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1392.94 | 0.0831636 | 8987.29ms | 500299 | 1280 | 1.03865e+08 | 342528 | 0.1369 | 1.77716 | 1(Win) | true |
| Jsonifier (two-stage) | 1139.21 | 0.349819 | 5479.7ms | 500299 | 40 | 8.5861e+07 | 418818 | 0.94096 | 2.17309 | 2(Loss) | true |
| Glaze | 684.727 | 0.45824 | 9046.1ms | 500299 | 30 | 3.05867e+08 | 696807 | 0.0478602 | 3.61557 | 3(Loss) | true |
| simdjson (ondemand) | 599.839 | 0.188497 | 5139.71ms | 500299 | 80 | 1.79841e+08 | 795418 | 0.0442967 | 4.12728 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1647.39 | 0.202011 | 8720.79ms | 500299 | 320 | 1.09539e+08 | 289623 | 0.478176 | 1.50267 | 1(Win) | true |
| Jsonifier (two-stage) | 1293.74 | 0.469788 | 5297.02ms | 500299 | 30 | 9.00517e+07 | 368793 | 0.0605212 | 1.91346 | 2(Loss) | true |
| Glaze | 759.936 | 0.239635 | 8594.06ms | 500299 | 40 | 9.05451e+07 | 627845 | 0.328385 | 3.25778 | 3(Loss) | true |
| simdjson (ondemand) | 586.717 | 0.360879 | 5354.61ms | 500299 | 30 | 2.58373e+08 | 813207 | 0.196366 | 4.21959 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8989.59 | 0.759748 | 5436.12ms | 500299 | 80 | 1.3008e+07 | 53075 | 0.193497 | 0.275312 | 1(Win) | true |
| Glaze | 3173.05 | 0.228356 | 7977.52ms | 500299 | 320 | 3.77293e+07 | 150367 | 0.276338 | 0.780036 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9271.7 | 0.171525 | 5333.02ms | 500299 | 1280 | 9.97256e+06 | 51460.1 | 0.196685 | 0.266862 | 1(Win) | true |
| Glaze | 3223.83 | 0.334176 | 7571.84ms | 500299 | 80 | 1.95685e+07 | 147999 | 0.204818 | 0.76781 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2482.93 | 0.338207 | 5612.51ms | 1151920 | 30 | 6.71743e+07 | 442443 | 1.13915 | 0.997053 | 1(Win) | true |
| Jsonifier | 2271.96 | 0.153125 | 6531.57ms | 1151920 | 160 | 8.77116e+07 | 483528 | 0.183211 | 1.08965 | 2(Loss) | true |
| Glaze | 1427.38 | 0.208229 | 9810.07ms | 1151920 | 160 | 4.1093e+08 | 769629 | 0.768979 | 1.73444 | 3(Loss) | true |
| simdjson (ondemand) | 1409.7 | 0.234455 | 5162.33ms | 1151920 | 30 | 1.00146e+08 | 779283 | 1.88026 | 1.75618 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2925.29 | 0.101573 | 5401.49ms | 1151920 | 640 | 9.31207e+07 | 375538 | 0.105793 | 0.846271 | 1(Win) | true |
| Jsonifier | 2421.54 | 0.225947 | 6320.17ms | 1151920 | 80 | 8.40553e+07 | 453660 | 0.139616 | 1.02234 | 2(Loss) | true |
| Glaze | 1548.88 | 0.262282 | 9631.49ms | 1151920 | 30 | 1.03817e+08 | 709260 | 0.856516 | 1.59839 | 3(Loss) | true |
| simdjson (ondemand) | 1307.28 | 0.156936 | 5606.32ms | 1151920 | 40 | 6.95686e+07 | 840338 | 0.784061 | 1.8938 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3904.22 | 0.499959 | 9568.35ms | 1439562 | 80 | 2.47259e+08 | 351639 | 0.184154 | 0.633895 | 1(Win) | true |
| Glaze | 2094.93 | 0.338403 | 8641.76ms | 1439584 | 160 | 7.86905e+08 | 655341 | 0.17043 | 1.1815 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12644.7 | 0.484191 | 5526.98ms | 1439562 | 160 | 4.4218e+07 | 108573 | 0.115839 | 0.195738 | 1(Win) | true |
| Glaze | 5997.32 | 0.209706 | 5946.08ms | 1439584 | 160 | 3.68723e+07 | 228918 | 0.151758 | 0.412755 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1329.39 | 0.28037 | 4247.16ms | 56369 | 320 | 4.11327e+06 | 40437.8 | 0.162794 | 1.8612 | 1(Win) | true |
| Glaze STATISTICAL TIE | 992.193 | 0.0864684 | 5499.41ms | 56369 | 4890 | 1.07328e+07 | 54180.7 | 0.0814835 | 2.49401 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 989.329 | 0.339351 | 5483.34ms | 56369 | 160 | 5.44022e+06 | 54337.5 | 0.265252 | 2.50152 | 2(Tie) | true |
| simdjson (ondemand) | 785.82 | 0.0789208 | 6858.96ms | 56369 | 4890 | 1.42537e+07 | 68409.7 | 0.591596 | 3.14932 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1835.55 | 0.169442 | 3492.16ms | 56369 | 1280 | 3.15211e+06 | 29287 | 0.735072 | 1.34756 | 1(Win) | true |
| Glaze | 1341.67 | 0.255009 | 4632.07ms | 56369 | 640 | 6.68162e+06 | 40067.8 | 0.633937 | 1.84403 | 2(Loss) | true |
| Jsonifier (two-stage) | 1287.92 | 0.223758 | 4715.65ms | 56369 | 640 | 5.58265e+06 | 41739.8 | 1.20162 | 1.92109 | 3(Loss) | true |
| simdjson (ondemand) | 1065.99 | 0.715321 | 5719.04ms | 56369 | 40 | 5.20523e+06 | 50430 | 0.211963 | 2.32149 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10424.9 | 0.201217 | 525.25ms | 56369 | 30 | 3229.89 | 5156.67 | 0.45045 | 0.236496 | 1(Win) | true |
| Glaze | 3111.88 | 0.0908883 | 1771.95ms | 56369 | 4890 | 1.20548e+06 | 17275 | 0.00254646 | 0.794156 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6628.57 | 0.123305 | 493.43ms | 56369 | 30 | 3000 | 8110 | 0.123457 | 0.371948 | 1(Win) | true |
| Glaze | 3378.15 | 0.0890398 | 1769.8ms | 56369 | 30 | 6022.99 | 15913.3 | 0.273052 | 0.731644 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1475.71 | 0.77188 | 5458.96ms | 83958 | 40 | 7.01584e+06 | 54257.5 | 0.249724 | 1.67716 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1461.37 | 0.279974 | 5720.32ms | 83958 | 320 | 7.52987e+06 | 54790 | 0.333117 | 1.6933 | 1(Tie) | true |
| Glaze | 1325.05 | 0.870785 | 6198.25ms | 83958 | 30 | 8.30616e+06 | 60426.7 | 0.110448 | 1.86761 | 3(Loss) | true |
| simdjson (ondemand) | 1179.58 | 0.293279 | 6869.03ms | 83958 | 320 | 1.26819e+07 | 67879.1 | 0.350652 | 2.09816 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1964.67 | 0.0767005 | 4694.14ms | 83958 | 4890 | 4.77802e+06 | 40754.1 | 0.0452374 | 1.25933 | 1(Win) | true |
| Jsonifier | 1830.54 | 0.204837 | 4873.89ms | 83958 | 640 | 5.13762e+06 | 43740.5 | 0.284799 | 1.35162 | 2(Loss) | true |
| Glaze | 1776.89 | 0.11663 | 5049.14ms | 83958 | 4890 | 1.35063e+07 | 45061.1 | 0.16552 | 1.39251 | 3(Loss) | true |
| simdjson (ondemand) | 1510.39 | 0.181994 | 6087.72ms | 83958 | 640 | 5.95721e+06 | 53012 | 0.324977 | 1.63832 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11184.5 | 0.11513 | 864.102ms | 94370 | 30 | 2574.71 | 8046.67 | 0.0414422 | 0.220426 | 1(Win) | true |
| Glaze | 3079.59 | 0.101929 | 2992.55ms | 94370 | 4890 | 4.339e+06 | 29224.1 | 0.0612845 | 0.803182 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11296.9 | 0.151459 | 827.807ms | 94370 | 30 | 4367.82 | 7966.67 | 0.209644 | 0.218478 | 1(Win) | true |
| Glaze | 3293.77 | 0.107084 | 2747.61ms | 94370 | 2560 | 2.19166e+06 | 27323.8 | 0.476896 | 0.750933 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1029.63 | 0.782932 | 5001.71ms | 53331 | 640 | 9.57249e+07 | 49396.7 | 0.0192916 | 2.40114 | 1(Win) | true |
| Glaze | 963.817 | 0.235659 | 5389.89ms | 53331 | 2560 | 3.95893e+07 | 52769.8 | 0.0932095 | 2.56708 | 2(Loss) | true |
| Jsonifier (two-stage) | 946.678 | 0.214277 | 5490.56ms | 53331 | 1280 | 1.69635e+07 | 53725.2 | 0.480719 | 2.61365 | 3(Loss) | true |
| simdjson (ondemand) | 657.695 | 0.283666 | 7821.72ms | 53331 | 320 | 1.53984e+07 | 77331.2 | 0.00242458 | 3.76231 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1568.07 | 0.0880028 | 4094.94ms | 53331 | 40 | 32589.7 | 32435 | 0.00513875 | 1.57746 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1366.94 | 0.410968 | 4542.58ms | 53331 | 160 | 3.74108e+06 | 37207.5 | 0.358183 | 1.81003 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1364.32 | 0.22003 | 4533.47ms | 53331 | 640 | 4.30601e+06 | 37279.1 | 0.226657 | 1.81321 | 2(Tie) | true |
| simdjson (ondemand) | 828.463 | 0.675116 | 6890.65ms | 53331 | 80 | 1.37423e+07 | 61391.2 | 0.0468527 | 2.98708 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11671.4 | 0.19354 | 508.143ms | 58581 | 30 | 2574.71 | 4786.67 | 0.139082 | 0.211245 | 1(Win) | true |
| Glaze | 4746.92 | 0.179958 | 1187.42ms | 58581 | 2560 | 1.14835e+06 | 11769.1 | 0.145826 | 0.520067 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11593 | 0.20518 | 495.389ms | 58581 | 4890 | 478082 | 4819.06 | 0.0867413 | 0.212341 | 1(Win) | true |
| Glaze | 5484.35 | 0.198207 | 1076.31ms | 58581 | 30 | 12229.9 | 10186.7 | 0.098264 | 0.450088 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1146.46 | 0.357099 | 5524.01ms | 65103 | 1280 | 4.78705e+07 | 54155.2 | 0.361523 | 2.15812 | 1(Win) | true |
| Glaze | 1115.2 | 0.222084 | 5573.93ms | 65103 | 2560 | 3.91357e+07 | 55673.7 | 0.0574266 | 2.21872 | 2(Loss) | true |
| Jsonifier | 1049.48 | 0.864057 | 6050.4ms | 65103 | 30 | 7.83903e+06 | 59160 | 0.893455 | 2.35757 | 3(Loss) | true |
| simdjson (ondemand) | 813.054 | 0.346451 | 7673.96ms | 65103 | 640 | 4.47949e+07 | 76362.8 | 0.0114571 | 3.0438 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1649.27 | 0.16628 | 4503.41ms | 65103 | 4890 | 1.91606e+07 | 37645.3 | 1.20069 | 1.49986 | 1(Win) | true |
| Glaze | 1603.84 | 0.114076 | 4661.3ms | 65103 | 2560 | 4.99237e+06 | 38711.4 | 0.171027 | 1.54263 | 2(Loss) | true |
| Jsonifier | 1420.78 | 0.224554 | 5079.82ms | 65103 | 1280 | 1.23254e+07 | 43699.3 | 0.328419 | 1.74142 | 3(Loss) | true |
| simdjson (ondemand) | 987.94 | 0.665018 | 7046.63ms | 65103 | 40 | 6.98664e+06 | 62845 | 0.172679 | 2.50518 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10848.9 | 0.112689 | 716.515ms | 78778 | 40 | 2435.9 | 6925 | 0.0240616 | 0.227141 | 1(Win) | true |
| Glaze | 4379.82 | 0.154957 | 1739.13ms | 78778 | 30 | 21195.4 | 17153.3 | 0.233736 | 0.563964 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11481.7 | 0.199164 | 665.752ms | 78778 | 4890 | 830478 | 6543.33 | 0.00875496 | 0.214757 | 1(Win) | true |
| Glaze | 5152.85 | 0.104769 | 1545.76ms | 78778 | 40 | 9333.33 | 14580 | 0.29633 | 0.47927 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1373.76 | 0.138083 | 866.356ms | 11812 | 40 | 5128.21 | 8200 | 0.243309 | 1.79641 | 1(Win) | true |
| Jsonifier (two-stage) | 1136.42 | 0.154048 | 1066.9ms | 11812 | 40 | 9326.92 | 9912.5 | 0.025227 | 2.17264 | 2(Loss) | true |
| Glaze | 824.281 | 0.17408 | 1369.98ms | 11812 | 2560 | 1.44888e+06 | 13666.2 | 0.0100051 | 2.99688 | 3(Loss) | true |
| simdjson (ondemand) | 621.106 | 0.15067 | 1930.02ms | 11812 | 30 | 22402.3 | 18136.7 | 0.0183756 | 3.98012 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1504.98 | 0.102039 | 868.655ms | 11812 | 40 | 2333.33 | 7485 | 0.156111 | 1.63661 | 1(Win) | true |
| Jsonifier (two-stage) | 1227.61 | 0.175195 | 1034.99ms | 11812 | 4890 | 1.26379e+06 | 9176.18 | 0.206841 | 2.01 | 2(Loss) | true |
| Glaze | 980.134 | 0.582708 | 1321.51ms | 11812 | 160 | 717625 | 11493.1 | 1.04929 | 2.51937 | 3(Loss) | true |
| simdjson (ondemand) | 656.84 | 0.679393 | 1850.09ms | 11812 | 80 | 1.08608e+06 | 17150 | 0.131023 | 3.76176 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6976.46 | 0.124094 | 167.822ms | 11812 | 640 | 2569.54 | 1614.69 | 0.0773545 | 0.348775 | 1(Win) | true |
| Glaze | 1638.52 | 0.162623 | 418.166ms | 11812 | 40 | 5000 | 6875 | 0.0726744 | 1.50277 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7250.98 | 0.471303 | 159.157ms | 11812 | 2560 | 137244 | 1553.55 | 0.0729707 | 0.335199 | 1(Win) | true |
| Glaze | 3177.1 | 0.111406 | 366.775ms | 11812 | 160 | 2496.46 | 3545.62 | 0.0176305 | 0.772836 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2339.31 | 0.120356 | 1106.88ms | 25388 | 30 | 4655.17 | 10350 | 0.544523 | 1.05507 | 1(Win) | true |
| Jsonifier | 2239.77 | 0.15587 | 1122.82ms | 25388 | 30 | 8517.24 | 10810 | 0.123495 | 1.10211 | 2(Loss) | true |
| Glaze | 1415.5 | 0.177076 | 1766.53ms | 25388 | 2560 | 2.34852e+06 | 17104.8 | 0.120207 | 1.74602 | 3(Loss) | true |
| simdjson (ondemand) | 1250.69 | 0.117934 | 1987.81ms | 25388 | 4890 | 2.54883e+06 | 19358.8 | 0.171907 | 1.97658 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2499.29 | 0.408472 | 1104.85ms | 25388 | 160 | 250535 | 9687.5 | 0.115994 | 0.987761 | 1(Win) | true |
| Jsonifier | 2428.92 | 0.263933 | 1102.69ms | 25388 | 2560 | 1.77198e+06 | 9968.16 | 0.117033 | 1.01641 | 2(Loss) | true |
| Glaze | 1575.55 | 0.223948 | 1672.13ms | 25388 | 1280 | 1.516e+06 | 15367.3 | 0.223697 | 1.56856 | 3(Loss) | true |
| simdjson (ondemand) | 1363.76 | 0.583893 | 1921.83ms | 25388 | 160 | 1.71936e+06 | 17753.8 | 0.0773885 | 1.81313 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11326.2 | 0.138183 | 283.13ms | 31235 | 160 | 2113.21 | 2630 | 0.0475059 | 0.216328 | 1(Win) | true |
| Glaze | 3820.74 | 0.22491 | 804.729ms | 31235 | 2560 | 787130 | 7796.41 | 0.122401 | 0.645408 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11909.3 | 0.104657 | 261.326ms | 31235 | 320 | 2192.79 | 2501.25 | 0.199501 | 0.205425 | 1(Win) | true |
| Glaze | 4264.57 | 0.0685933 | 736.975ms | 31235 | 160 | 3672.96 | 6985 | 0.0178923 | 0.578528 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1533.42 | 0.133057 | 6797.61ms | 108313 | 4890 | 3.92847e+07 | 67362.9 | 0.530958 | 1.6138 | 1(Win) | true |
| Jsonifier (two-stage) | 1143.23 | 0.336501 | 9260.21ms | 108313 | 160 | 1.47906e+07 | 90353.8 | 0.212117 | 2.16474 | 2(Loss) | true |
| Glaze | 964.836 | 0.340077 | 5557.84ms | 108313 | 80 | 1.06047e+07 | 107060 | 0.160865 | 2.56555 | 3(Loss) | true |
| simdjson (ondemand) | 805.814 | 0.761437 | 6537.68ms | 108313 | 40 | 3.81083e+07 | 128188 | 0.0578915 | 3.0716 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1828.96 | 0.192397 | 6149.92ms | 108313 | 640 | 7.55664e+06 | 56477.5 | 0.380465 | 1.35299 | 1(Win) | true |
| Jsonifier (two-stage) | 1283.65 | 0.280523 | 8485.57ms | 108313 | 320 | 1.63064e+07 | 80470.3 | 0.0641175 | 1.92808 | 2(Loss) | true |
| Glaze | 1100.43 | 0.142137 | 5091.05ms | 108313 | 640 | 1.13928e+07 | 93868.3 | 0.171655 | 2.2492 | 3(Loss) | true |
| simdjson (ondemand) | 926.059 | 0.156775 | 5865.44ms | 108313 | 640 | 1.95712e+07 | 111543 | 0.357498 | 2.67291 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14791.7 | 0.154799 | 724.857ms | 108313 | 30 | 3505.75 | 6983.33 | 0.0477099 | 0.166983 | 1(Win) | true |
| Glaze | 2945.67 | 0.377089 | 3528.54ms | 108313 | 160 | 2.7977e+06 | 35066.9 | 0.318019 | 0.839653 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15590.3 | 1.10038 | 698.574ms | 108313 | 160 | 850471 | 6625.62 | 0.236384 | 0.158217 | 1(Win) | true |
| Glaze | 3134.14 | 0.281701 | 3343.29ms | 108313 | 160 | 1.37918e+06 | 32958.1 | 0.0511751 | 0.789185 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1934.34 | 0.186687 | 9142.88ms | 183677 | 4890 | 1.39759e+08 | 90556.9 | 0.450675 | 1.27951 | 1(Win) | true |
| Jsonifier | 1769.42 | 0.613514 | 5340.05ms | 183677 | 40 | 1.47556e+07 | 98997.5 | 0.0345246 | 1.3989 | 2(Loss) | true |
| Glaze | 1420.17 | 0.330634 | 6468.94ms | 183677 | 320 | 5.322e+07 | 123343 | 0.239744 | 1.74296 | 3(Loss) | true |
| simdjson (ondemand) | 1379.12 | 0.126816 | 6565.12ms | 183677 | 1280 | 3.32098e+07 | 127015 | 0.565741 | 1.79481 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2214.9 | 0.278955 | 8472.25ms | 183677 | 160 | 7.78736e+06 | 79086.2 | 0.241241 | 1.11742 | 1(Win) | true |
| Jsonifier | 1943.12 | 0.16724 | 9712.24ms | 183677 | 640 | 1.45469e+07 | 90147.7 | 0.102331 | 1.27375 | 2(Loss) | true |
| simdjson (ondemand) | 1569.77 | 0.208626 | 6165.12ms | 183677 | 320 | 1.73429e+07 | 111588 | 0.0453472 | 1.5768 | 3(Loss) | true |
| Glaze | 1523.8 | 0.162074 | 6063.32ms | 183677 | 2560 | 8.88624e+07 | 114955 | 0.853134 | 1.62436 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14108.2 | 0.070192 | 1551.31ms | 213963 | 30 | 3091.95 | 14463.3 | 1.07151 | 0.175075 | 1(Win) | true |
| Glaze | 3568.71 | 0.283839 | 5787.34ms | 213963 | 1280 | 3.37138e+07 | 57177.7 | 0.382534 | 0.693366 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13777.8 | 0.121142 | 1497.04ms | 213963 | 4890 | 1.57404e+06 | 14810.2 | 0.0773896 | 0.179369 | 1(Win) | true |
| Glaze | 3791.36 | 0.29671 | 5420.68ms | 213963 | 160 | 4.0801e+06 | 53820 | 0.291788 | 0.652704 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 646.294 | 0.810717 | 8323.48ms | 1834197 | 40 | 1.92588e+10 | 2.70655e+06 | 1.16611 | 3.8306 | 1(Win) | true |
| Jsonifier (two-stage) | 560.456 | 0.715615 | 10104.3ms | 1834197 | 80 | 3.99078e+10 | 3.12108e+06 | 1.83423 | 4.41713 | 2(Loss) | true |
| Glaze | 202.953 | 0.710856 | 6266.18ms | 1834197 | 30 | 1.12612e+11 | 8.61888e+06 | 1.40228 | 12.1989 | 3(Loss) | true |
| simdjson (ondemand) | 118.461 | 1.17571 | 10116.2ms | 1834197 | 40 | 1.20561e+12 | 1.47663e+07 | 0.78826 | 20.8986 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 780.575 | 0.422906 | 8519.08ms | 1834197 | 40 | 3.5926e+09 | 2.24094e+06 | 1.07673 | 3.17168 | 1(Win) | true |
| Jsonifier (two-stage) | 657.011 | 0.422727 | 9781.02ms | 1834197 | 80 | 1.01334e+10 | 2.6624e+06 | 0.243087 | 3.76803 | 2(Loss) | true |
| Glaze | 208.938 | 0.410933 | 6346.77ms | 1834197 | 40 | 4.73432e+10 | 8.37198e+06 | 1.06563 | 11.8493 | 3(Loss) | true |
| simdjson (ondemand) | 127.306 | 1.82091 | 10193.2ms | 1834197 | 30 | 1.87799e+12 | 1.37403e+07 | 0.448719 | 19.4472 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 594.554 | 0.382711 | 9010.25ms | 1922245 | 30 | 4.17732e+09 | 3.08331e+06 | 3.6387 | 4.16382 | -(Win) | false |
| Glaze | 440.408 | 0.961779 | 5944.52ms | 1833577 | 80 | 1.16662e+11 | 3.97049e+06 | 1.02173 | 5.62133 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 824.777 | 0.187723 | 7228.33ms | 1922245 | 80 | 1.39273e+09 | 2.22266e+06 | 0.199027 | 3.00177 | 1(Win) | true |
| Glaze | 566.72 | 0.229856 | 10016.3ms | 1833577 | 160 | 8.04805e+09 | 3.08553e+06 | 0.986375 | 4.36863 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) DID NOT CONVERGE | 1879.92 | 0.503369 | 5724.14ms | 7351818 | 40 | 1.40975e+10 | 3.72954e+06 | 2.568 | 1.31688 | -(Win) | false |
| Jsonifier DID NOT CONVERGE | 1692.05 | 1.12899 | 5878.56ms | 7351818 | 30 | 6.56546e+10 | 4.14364e+06 | 10.4357 | 1.46275 | -(Loss) | false |
| Glaze | 647.764 | 1.55802 | 7417.59ms | 7351818 | 30 | 8.53147e+11 | 1.08238e+07 | 0.865508 | 3.82194 | 3(Loss) | true |
| simdjson (ondemand) | 441.657 | 1.87876 | 10840ms | 7351818 | 30 | 2.6686e+12 | 1.58748e+07 | 0.853744 | 5.6055 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2199.8 | 0.625829 | 5795.11ms | 7351818 | 30 | 1.19359e+10 | 3.18722e+06 | 1.04649 | 1.12537 | 1(Win) | true |
| Jsonifier | 2070.79 | 0.812687 | 5870.01ms | 7351818 | 30 | 2.27137e+10 | 3.38579e+06 | 1.04503 | 1.19549 | 2(Loss) | true |
| Glaze | 706.717 | 1.16326 | 7338.93ms | 7351818 | 40 | 5.32739e+11 | 9.92086e+06 | 1.46955 | 3.50316 | 3(Loss) | true |
| simdjson (ondemand) | 485.221 | 1.48571 | 10732.1ms | 7351818 | 40 | 1.84348e+12 | 1.44496e+07 | 1.27154 | 5.10233 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2079.4 | 0.389474 | 6827.22ms | 10018896 | 80 | 2.56218e+10 | 4.59495e+06 | 1.22792 | 1.19054 | 1(Win) | true |
| Glaze | 1395.99 | 0.969789 | 10452.7ms | 9930228 | 80 | 3.46256e+11 | 6.78385e+06 | 0.452446 | 1.77346 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3644.94 | 0.197756 | 8259.3ms | 10018896 | 40 | 1.07493e+09 | 2.62138e+06 | 1.51433 | 0.679232 | 1(Win) | true |
| Glaze | 2485.79 | 2.34675 | 5359.57ms | 9930228 | 40 | 3.19728e+11 | 3.80973e+06 | 0.16675 | 0.995968 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 675.188 | 0.109541 | 8284.29ms | 1834197 | 30 | 2.4161e+08 | 2.59073e+06 | 0.022897 | 3.66685 | 1(Win) | true |
| Jsonifier (two-stage) | 580.558 | 0.34103 | 9453.22ms | 1834197 | 80 | 8.44648e+09 | 3.01301e+06 | 1.32299 | 4.26439 | 2(Loss) | true |
| simdjson (ondemand) | 202.529 | 1.94414 | 5951.25ms | 1834197 | 40 | 1.12781e+12 | 8.63693e+06 | 0.698015 | 12.2241 | 3(Loss) | true |
| Glaze DID NOT CONVERGE | 192.69 | 1.39848 | 6123.42ms | 1834197 | 40 | 6.44682e+11 | 9.07794e+06 | 5.02767 | 12.8485 | -(Loss) | false |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 756.278 | 0.163613 | 8409.06ms | 1834197 | 40 | 5.72832e+08 | 2.31294e+06 | 0.361323 | 3.27364 | 1(Win) | true |
| Jsonifier (two-stage) | 645.338 | 1.04564 | 9321.06ms | 1834197 | 160 | 1.28529e+11 | 2.71056e+06 | 0.413031 | 3.83636 | 2(Loss) | true |
| simdjson (ondemand) | 226.999 | 0.230883 | 5844.81ms | 1834197 | 30 | 9.49621e+09 | 7.70589e+06 | 1.25827 | 10.9064 | 3(Loss) | true |
| Glaze | 206.907 | 0.532597 | 6270.71ms | 1834197 | 30 | 6.08221e+10 | 8.45418e+06 | 0.715741 | 11.9659 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 659.19 | 0.255957 | 8419.48ms | 1922245 | 30 | 1.52003e+09 | 2.78098e+06 | 1.46821 | 3.75551 | 1(Win) | true |
| Glaze | 420.832 | 0.364873 | 6531.41ms | 1833577 | 80 | 1.83888e+10 | 4.15518e+06 | 0.915773 | 5.88276 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 834.015 | 0.232414 | 6828.06ms | 1922245 | 160 | 4.17554e+09 | 2.19804e+06 | 0.472816 | 2.96846 | 1(Win) | true |
| Glaze | 527.401 | 0.344329 | 9920.13ms | 1833577 | 30 | 3.91008e+09 | 3.31557e+06 | 0.836143 | 4.69414 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2153.81 | 0.221229 | 10193.7ms | 7351818 | 160 | 8.29807e+09 | 3.25527e+06 | 0.0518275 | 1.14949 | 1(Win) | true |
| Jsonifier | 2106.11 | 0.433029 | 5167.37ms | 7351818 | 80 | 1.66246e+10 | 3.329e+06 | 0.139237 | 1.17544 | 2(Loss) | true |
| simdjson (ondemand) | 866.814 | 1.58545 | 5657.34ms | 7351818 | 40 | 6.5781e+11 | 8.08852e+06 | 2.28519 | 2.85623 | 3(Loss) | true |
| Glaze DID NOT CONVERGE | 679.785 | 0.57156 | 7152.1ms | 7351818 | 30 | 1.04254e+11 | 1.03139e+07 | 2.54958 | 3.64197 | -(Loss) | false |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2394.78 | 0.226902 | 10210ms | 7351818 | 160 | 7.06082e+09 | 2.92772e+06 | 0.501935 | 1.03382 | 1(Win) | true |
| Jsonifier (two-stage) | 2380.04 | 0.183918 | 10042.4ms | 7351818 | 40 | 1.17417e+09 | 2.94585e+06 | 0.213516 | 1.04024 | 2(Loss) | true |
| simdjson (ondemand) | 892.064 | 2.23276 | 5583.78ms | 7351818 | 30 | 9.23852e+11 | 7.85957e+06 | 2.16468 | 2.77539 | 3(Loss) | true |
| Glaze | 730.026 | 0.845624 | 7261.91ms | 7351818 | 40 | 2.63832e+11 | 9.60409e+06 | 1.4828 | 3.39135 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2289.05 | 0.328711 | 6537.91ms | 10018896 | 30 | 5.64782e+09 | 4.17413e+06 | 1.88783 | 1.08158 | 1(Win) | true |
| Glaze | 1087.88 | 1.68956 | 5851.01ms | 9930228 | 40 | 8.65302e+11 | 8.70521e+06 | 1.98889 | 2.27574 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3677.17 | 0.184117 | 8281.69ms | 10018896 | 160 | 3.66203e+09 | 2.5984e+06 | 2.03127 | 0.673288 | 1(Win) | true |
| Glaze | 2831.22 | 0.0681691 | 5148.3ms | 9930228 | 30 | 1.5598e+08 | 3.34492e+06 | 0.163463 | 0.874466 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 752.799 | 0.294557 | 7476.42ms | 461466 | 40 | 1.1861e+08 | 584602 | 0.0235147 | 3.28858 | 1(Win) | true |
| Jsonifier (two-stage) | 701.182 | 0.21249 | 8171.39ms | 461466 | 40 | 7.1147e+07 | 627638 | 0.0375607 | 3.53075 | 2(Loss) | true |
| Glaze | 616.591 | 0.124203 | 9162.75ms | 461466 | 160 | 1.25738e+08 | 713744 | 0.316511 | 4.0151 | 3(Loss) | true |
| simdjson (ondemand) | 552.533 | 0.352826 | 5344.17ms | 461466 | 40 | 3.15897e+08 | 796492 | 1.76138 | 4.48068 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1002.43 | 0.586908 | 6793.84ms | 461466 | 640 | 4.249e+09 | 439019 | 0.196419 | 2.46961 | 1(Win) | true |
| Jsonifier (two-stage) | 864.278 | 0.311368 | 7611.83ms | 461466 | 40 | 1.00549e+08 | 509198 | 0.0532166 | 2.86444 | 2(Loss) | true |
| Glaze | 794.802 | 0.127644 | 8305.51ms | 461466 | 320 | 1.59851e+08 | 553708 | 0.857269 | 3.11483 | 3(Loss) | true |
| simdjson (ondemand) | 667.558 | 0.45734 | 9474.31ms | 461466 | 80 | 7.27226e+08 | 659251 | 0.66805 | 3.70857 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3292.18 | 0.926703 | 6960.8ms | 461466 | 30 | 4.60377e+07 | 133677 | 0.00249352 | 0.751514 | 1(Win) | true |
| Glaze | 2643.16 | 0.159749 | 8573.79ms | 461466 | 2560 | 1.81113e+08 | 166501 | 0.182153 | 0.93647 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10702.3 | 0.124308 | 4195.26ms | 461466 | 2560 | 6.68902e+06 | 41120.9 | 0.0293619 | 0.231136 | 1(Win) | true |
| Glaze | 2863.09 | 0.089106 | 7969.04ms | 461466 | 2560 | 4.80247e+07 | 153711 | 0.39574 | 0.864547 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1092.97 | 0.103447 | 8405.14ms | 728486 | 160 | 6.91803e+07 | 635641 | 1.91355 | 2.26508 | 1(Win) | true |
| Jsonifier | 1001.14 | 0.960228 | 8778.18ms | 728486 | 80 | 3.55215e+09 | 693948 | 0.484708 | 2.47258 | 2(Loss) | true |
| Glaze | 925.318 | 0.257673 | 9701.05ms | 728486 | 320 | 1.1977e+09 | 750810 | 0.0515959 | 2.67551 | 3(Loss) | true |
| simdjson (ondemand) | 844.978 | 0.233327 | 5314.14ms | 728486 | 30 | 1.10409e+08 | 822197 | 0.020672 | 2.92998 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1414.1 | 0.330205 | 7560.33ms | 728486 | 40 | 1.05271e+08 | 491292 | 0.0222252 | 1.75073 | 1(Win) | true |
| Jsonifier | 1331.43 | 0.313797 | 8151.92ms | 728486 | 30 | 8.04317e+07 | 521800 | 0.0146949 | 1.85945 | 2(Loss) | true |
| Glaze | 1156.84 | 0.371231 | 9144.54ms | 728486 | 30 | 1.49109e+08 | 600547 | 0.337495 | 2.13999 | 3(Loss) | true |
| simdjson (ondemand) | 1020.41 | 0.358565 | 9990.04ms | 728486 | 30 | 1.78791e+08 | 680840 | 0.0435926 | 2.42608 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3768.37 | 0.764629 | 5501.6ms | 837491 | 30 | 7.87909e+07 | 211947 | 0.854945 | 0.656721 | 1(Win) | true |
| Glaze | 2071.07 | 0.276532 | 9804.61ms | 837491 | 160 | 1.81962e+08 | 385643 | 0.875796 | 1.19506 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11984.9 | 0.411409 | 6553.6ms | 837491 | 160 | 1.20271e+07 | 66641.9 | 0.128651 | 0.206465 | 1(Win) | true |
| Glaze | 3552.11 | 0.157034 | 5887.48ms | 837491 | 320 | 3.98955e+07 | 224850 | 0.098078 | 0.696879 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8161.83 | 0.298307 | 5656.22ms | 466906 | 320 | 8.47539e+06 | 54555.9 | 0.444234 | 0.303145 | 1(Win) | true |
| Jsonifier | 7994.26 | 0.113076 | 5631.29ms | 466906 | 2560 | 1.01551e+07 | 55699.5 | 0.171386 | 0.309515 | 2(Loss) | true |
| simdjson (ondemand) | 3981.89 | 0.114282 | 5809.48ms | 466906 | 2560 | 4.18095e+07 | 111825 | 0.125039 | 0.621574 | 3(Loss) | true |
| Glaze | 2880.76 | 0.195229 | 8075.86ms | 466906 | 320 | 2.91395e+07 | 154569 | 0.612887 | 0.859233 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8422.08 | 0.114668 | 5492.9ms | 466906 | 2560 | 9.40906e+06 | 52870.1 | 0.0330891 | 0.293807 | 1(Win) | true |
| Jsonifier (two-stage) | 8330.2 | 0.143531 | 5543.46ms | 466906 | 2560 | 1.50689e+07 | 53453.3 | 0.0279235 | 0.297056 | 2(Loss) | true |
| simdjson (ondemand) | 4203.16 | 0.114657 | 5600.11ms | 466906 | 1280 | 1.8885e+07 | 105939 | 0.259719 | 0.588873 | 3(Loss) | true |
| Glaze | 2967.75 | 0.25244 | 7989.91ms | 466906 | 160 | 2.29529e+07 | 150038 | 0.0437198 | 0.834103 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9106.17 | 0.108306 | 6617.38ms | 631514 | 2560 | 1.31352e+07 | 66137.4 | 0.318532 | 0.271723 | 1(Win) | true |
| Jsonifier | 8776.6 | 0.286377 | 6726.23ms | 631514 | 320 | 1.23578e+07 | 68620.9 | 0.050575 | 0.281951 | 2(Loss) | true |
| simdjson (ondemand) | 4947.69 | 0.232662 | 6254.79ms | 631514 | 640 | 5.13325e+07 | 121725 | 0.0353123 | 0.500264 | 3(Loss) | true |
| Glaze | 3481.06 | 0.289877 | 9009.68ms | 631514 | 80 | 2.01214e+07 | 173010 | 0.115734 | 0.711079 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 9561.37 | 0.279867 | 6569.64ms | 631514 | 320 | 9.94445e+06 | 62988.8 | 0.358891 | 0.258792 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 9555.54 | 0.268867 | 6538.18ms | 631514 | 320 | 9.18926e+06 | 63027.2 | 0.0918105 | 0.258975 | 1(Tie) | true |
| simdjson (ondemand) | 5207.71 | 0.263474 | 6033.3ms | 631514 | 1280 | 1.18838e+08 | 115648 | 0.318721 | 0.475289 | 3(Loss) | true |
| Glaze | 3507.22 | 0.197822 | 9002.17ms | 631514 | 1280 | 1.47707e+08 | 171720 | 0.588195 | 0.705806 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1312.38 | 1.9509 | 8697.85ms | 466906 | 80 | 3.50511e+09 | 339290 | 1.04341 | 1.88622 | 1(Win) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 1141.48 | 1.34242 | 5168.1ms | 466906 | 80 | 2.19376e+09 | 390088 | 4.10769 | 2.16873 | -(Loss) | false |
| Glaze STATISTICAL TIE | 1078.39 | 1.01838 | 5283.7ms | 466906 | 320 | 5.65818e+09 | 412909 | 0.322725 | 2.2956 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE DID NOT CONVERGE | 1056.38 | 0.483554 | 5599.87ms | 466906 | 320 | 1.3294e+09 | 421511 | 2.77651 | 2.34339 | -(Tie) | false |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1761.7 | 0.978273 | 7450.24ms | 466906 | 30 | 1.83415e+08 | 252753 | 0.966486 | 1.4052 | 1(Win) | true |
| Jsonifier (two-stage) | 1471.34 | 0.149713 | 8672.18ms | 466906 | 640 | 1.31382e+08 | 302634 | 1.57806 | 1.68226 | 2(Loss) | true |
| Glaze | 1426.62 | 0.371962 | 9036.34ms | 466906 | 40 | 5.39139e+07 | 312120 | 0.0662577 | 1.73527 | 3(Loss) | true |
| simdjson (ondemand) | 1368.81 | 0.298562 | 9424.34ms | 466906 | 40 | 3.77315e+07 | 325302 | 0.100574 | 1.80848 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 4992.53 | 0.0955837 | 9252.5ms | 475954 | 4890 | 3.69288e+07 | 90916.9 | 0.270676 | 0.49568 | 1(Win) | true |
| Jsonifier DID NOT CONVERGE | 3952.76 | 0.531372 | 6320.09ms | 475954 | 80 | 2.97863e+07 | 114832 | 2.51703 | 0.625854 | -(Loss) | false |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14317.1 | 0.506379 | 3269.9ms | 475954 | 160 | 4.12376e+06 | 31703.8 | 0.247778 | 0.172764 | 1(Win) | true |
| Glaze | 5611.29 | 0.151591 | 8162.21ms | 475954 | 640 | 9.62342e+06 | 80891.4 | 0.0740351 | 0.441025 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1530.73 | 0.92701 | 5136.8ms | 631514 | 160 | 2.12842e+09 | 393446 | 0.904192 | 1.61717 | 1(Win) | true |
| simdjson (ondemand) | 1398.71 | 0.404923 | 5535.96ms | 631514 | 320 | 9.72758e+08 | 430582 | 0.540155 | 1.76987 | 2(Loss) | true |
| Glaze | 1358.86 | 0.535266 | 5941.7ms | 631514 | 30 | 1.68842e+08 | 443210 | 0.676919 | 1.82182 | 3(Loss) | true |
| Jsonifier | 1328.15 | 0.456809 | 5935.79ms | 631514 | 640 | 2.74615e+09 | 453458 | 0.133252 | 1.86389 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2018.17 | 0.066521 | 8823.33ms | 631514 | 1280 | 5.04401e+07 | 298418 | 0.494217 | 1.22659 | 1(Win) | true |
| simdjson (ondemand) | 1791.48 | 0.335779 | 9630.98ms | 631514 | 30 | 3.82272e+07 | 336180 | 0.23839 | 1.38185 | 2(Loss) | true |
| Jsonifier STATISTICAL TIE | 1662.79 | 0.16706 | 5126.62ms | 631514 | 640 | 2.34326e+08 | 362198 | 0.185497 | 1.4888 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 1662.78 | 0.273509 | 5264.84ms | 631514 | 80 | 7.85109e+07 | 362200 | 0.197102 | 1.48881 | 3(Tie) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3894.34 | 0.295963 | 9280.24ms | 716365 | 640 | 1.72526e+08 | 175429 | 0.0753834 | 0.635312 | 1(Win) | true |
| Glaze | 2725.59 | 0.288373 | 6528.33ms | 716365 | 320 | 1.67189e+08 | 250653 | 0.209139 | 0.907924 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10935 | 0.0729995 | 6422.12ms | 716365 | 4890 | 1.01714e+07 | 62476.4 | 0.08169 | 0.226308 | 1(Win) | true |
| Glaze | 5339.67 | 0.0944959 | 6661.69ms | 716365 | 1280 | 1.87101e+07 | 127944 | 0.298675 | 0.463572 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1055.14 | 0.254868 | 242.002ms | 2632 | 4890 | 179759 | 2378.9 | 0.36528 | 2.31795 | 1(Win) | true |
| Jsonifier (two-stage) | 1001.03 | 0.232876 | 255.783ms | 2632 | 80 | 2727.85 | 2507.5 | 0 | 2.44934 | 2(Loss) | true |
| Glaze | 817.446 | 0.201295 | 315.588ms | 2632 | 160 | 6112.81 | 3070.62 | 0.347222 | 3.00148 | 3(Loss) | true |
| simdjson (ondemand) | 740.707 | 0.277746 | 350.22ms | 2632 | 80 | 7087.03 | 3388.75 | 0.184094 | 3.31507 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1416.18 | 0.379846 | 213.335ms | 2632 | 2560 | 116035 | 1772.42 | 0.0792777 | 1.72033 | 1(Win) | true |
| Glaze | 1382.96 | 0.242072 | 219.725ms | 2632 | 80 | 1544.3 | 1815 | 0.137552 | 1.76226 | 2(Loss) | true |
| Jsonifier (two-stage) | 1331.6 | 0.183386 | 226.095ms | 2632 | 160 | 1911.95 | 1885 | 0.0662691 | 1.83344 | 3(Loss) | true |
| simdjson (ondemand) | 1316.97 | 0.115971 | 222.053ms | 2632 | 320 | 1563.38 | 1905.94 | 0.0163934 | 1.85217 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9019.88 | 0.22811 | 31.434ms | 2632 | 4890 | 1970.46 | 278.282 | 0.63603 | 0.248504 | 1(Win) | true |
| Glaze | 3515.2 | 0.211576 | 75.7359ms | 2632 | 640 | 1460.78 | 714.062 | 0.0437828 | 0.677601 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9908.17 | 3.65689 | 29.7686ms | 2632 | 30 | 2574.71 | 253.333 | 0 | 0.22324 | 1(Win) | true |
| Glaze | 4017.12 | 0.672531 | 66.9801ms | 2632 | 1280 | 22603.6 | 624.844 | 0.0999251 | 0.590526 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1207.66 | 0.197073 | 272.472ms | 3370 | 160 | 4400.94 | 2661.25 | 0.0469484 | 2.02739 | 1(Win) | true |
| Jsonifier | 1143.05 | 0.306336 | 283.823ms | 3370 | 2560 | 189918 | 2811.68 | 0.059704 | 2.14457 | 2(Loss) | true |
| Glaze | 1026.18 | 0.26658 | 327.876ms | 3370 | 2560 | 178444 | 3131.88 | 0.0474182 | 2.39061 | 3(Loss) | true |
| simdjson (ondemand) | 917.855 | 0.2218 | 358.256ms | 3370 | 4890 | 294946 | 3501.51 | 0.29283 | 2.67614 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1650.26 | 0.203353 | 233.024ms | 3370 | 160 | 2509.43 | 1947.5 | 0 | 1.48151 | 1(Win) | true |
| simdjson (ondemand) | 1610.42 | 0.263518 | 227.745ms | 3370 | 4890 | 135242 | 1995.69 | 0.00286189 | 1.51698 | 2(Loss) | true |
| Jsonifier (two-stage) | 1581.85 | 0.266906 | 243.576ms | 3370 | 640 | 18820.2 | 2031.72 | 0.0384379 | 1.54394 | 3(Loss) | true |
| Jsonifier | 1453.22 | 0.0833935 | 265.762ms | 3370 | 320 | 1088.46 | 2211.56 | 0.408106 | 1.68276 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9588.23 | 0.528986 | 40.6028ms | 3643 | 640 | 2351.31 | 362.344 | 0.0431034 | 0.241579 | 1(Win) | true |
| Glaze | 3505.84 | 0.28169 | 104.123ms | 3682 | 4890 | 38925.7 | 1001.6 | 0.0110553 | 0.686914 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10070.2 | 2.30907 | 53.7967ms | 3643 | 40 | 2538.46 | 345 | 0.485437 | 0.227985 | 1(Win) | true |
| Glaze | 2459.85 | 0.500872 | 98.8861ms | 3682 | 40 | 2044.87 | 1427.5 | 0.528169 | 0.988566 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 557.984 | 0.179055 | 814.078ms | 4630 | 30 | 6022.99 | 7913.33 | 0.21106 | 4.41381 | 1(Win) | true |
| Jsonifier (two-stage) | 529.755 | 0.145995 | 881.343ms | 4630 | 40 | 5923.08 | 8335 | 0.10008 | 4.66156 | 2(Loss) | true |
| simdjson (ondemand) | 179.638 | 0.157701 | 2555.86ms | 4630 | 40 | 60102.6 | 24580 | 0.189496 | 13.7599 | 3(Loss) | true |
| Glaze | 175.639 | 0.137763 | 2588.87ms | 4630 | 2560 | 3.07064e+06 | 25139.7 | 0.0639026 | 14.0791 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 687.239 | 0.221167 | 826.175ms | 4630 | 40 | 8076.92 | 6425 | 0.232919 | 3.58844 | 1(Win) | true |
| Jsonifier (two-stage) | 639.62 | 0.147061 | 850.125ms | 4630 | 30 | 3091.95 | 6903.33 | 0.0483092 | 3.85318 | 2(Loss) | true |
| Glaze | 186.335 | 0.114894 | 2572.38ms | 4630 | 2560 | 1.89762e+06 | 23696.7 | 0.319993 | 13.2721 | 3(Loss) | true |
| simdjson (ondemand) | 185.63 | 0.0523042 | 2536.43ms | 4630 | 30 | 4643.68 | 23786.7 | 0.0841515 | 13.3191 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1581.91 | 0.513376 | 287.074ms | 4630 | 1280 | 262832 | 2791.25 | 0.841095 | 1.55008 | 1(Win) | true |
| Glaze | 929.551 | 0.405857 | 493.323ms | 4630 | 640 | 237872 | 4750.16 | 1.03197 | 2.64744 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1629.34 | 0.205567 | 325.66ms | 4630 | 30 | 931.034 | 2710 | 0.245399 | 1.50793 | 1(Win) | true |
| Glaze | 934.624 | 0.0812599 | 480.503ms | 4630 | 160 | 2358.1 | 4724.38 | 0.118922 | 2.6305 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1201.55 | 0.313859 | 971.954ms | 11579 | 640 | 532488 | 9190.31 | 0.115745 | 2.05333 | 1(Win) | true |
| Jsonifier | 1175.74 | 0.150106 | 969.515ms | 11579 | 4890 | 971915 | 9392.07 | 0.200819 | 2.09919 | 2(Loss) | true |
| simdjson (ondemand) | 421.561 | 0.0801167 | 2696.46ms | 11579 | 4890 | 2.15366e+06 | 26194.6 | 0.147454 | 5.86632 | 3(Loss) | true |
| Glaze | 402.036 | 0.202321 | 2796.91ms | 11579 | 30 | 92643.7 | 27466.7 | 0.463302 | 6.15019 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1548.03 | 0.139918 | 897.112ms | 11579 | 30 | 2988.51 | 7133.33 | 0 | 1.59246 | 1(Win) | true |
| Jsonifier | 1429.9 | 0.245931 | 962.059ms | 11579 | 2560 | 923416 | 7722.62 | 0.0652082 | 1.72549 | 2(Loss) | true |
| simdjson (ondemand) | 472.79 | 0.813103 | 2581.28ms | 11579 | 80 | 2.88528e+06 | 23356.2 | 0.284457 | 5.23129 | 3(Loss) | true |
| Glaze | 424.386 | 0.250621 | 2747.84ms | 11579 | 640 | 2.72167e+06 | 26020.2 | 0.0174174 | 5.82803 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4132.79 | 0.31866 | 357.07ms | 14795 | 1280 | 151499 | 3414.06 | 0.0274524 | 0.594092 | 1(Win) | true |
| Glaze | 2541.7 | 0.106252 | 577.44ms | 14795 | 80 | 2783.23 | 5551.25 | 0.0225124 | 0.969218 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4629.9 | 0.184361 | 317.45ms | 14795 | 80 | 2525.32 | 3047.5 | 0.0819672 | 0.530335 | 1(Win) | true |
| Glaze | 2816.99 | 0.0542378 | 541.102ms | 14795 | 160 | 1180.82 | 5008.75 | 0 | 0.874057 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 804.105 | 0.391714 | 424.058ms | 3223 | 40 | 8967.95 | 3822.5 | 0.108885 | 3.04445 | 1(Win) | true |
| Jsonifier (two-stage) | 698.956 | 0.189318 | 454.526ms | 3223 | 4890 | 338934 | 4397.55 | 0.148851 | 3.50683 | 2(Loss) | true |
| Glaze | 482.148 | 0.229869 | 656.778ms | 3223 | 40 | 8589.74 | 6375 | 0.0261506 | 5.09527 | 3(Loss) | true |
| simdjson (ondemand) | 471.12 | 0.230487 | 674.716ms | 3223 | 2560 | 578882 | 6524.22 | 0.11989 | 5.23166 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1109.64 | 0.135048 | 351.473ms | 3223 | 160 | 2238.99 | 2770 | 0.498866 | 2.20797 | 1(Win) | true |
| Jsonifier (two-stage) | 929.31 | 0.127517 | 395.007ms | 3223 | 40 | 711.538 | 3307.5 | 0.0252016 | 2.63505 | 2(Loss) | true |
| Glaze | 589.472 | 0.165527 | 593.385ms | 3223 | 4890 | 364283 | 5214.31 | 0.152246 | 4.17862 | 3(Loss) | true |
| simdjson (ondemand) | 530.633 | 0.179021 | 683.539ms | 3223 | 40 | 4301.28 | 5792.5 | 0.186674 | 4.64314 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8450.01 | 0.369535 | 40.4637ms | 3223 | 1280 | 2312.74 | 363.75 | 0.215239 | 0.272692 | 1(Win) | true |
| Glaze | 2561.41 | 0.392215 | 129.452ms | 3223 | 80 | 1772.15 | 1200 | 0.414938 | 0.948251 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9048.59 | 0.402732 | 48.9119ms | 3223 | 1280 | 2395.52 | 339.688 | 0.183655 | 0.252338 | 1(Win) | true |
| Glaze | 2984.17 | 0.826178 | 106.918ms | 3223 | 30 | 2172.41 | 1030 | 0 | 0.806164 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1217.92 | 0.182915 | 465.785ms | 5839 | 4890 | 342015 | 4572.13 | 0.107291 | 2.01344 | 1(Win) | true |
| Jsonifier | 1087.33 | 0.192444 | 527.921ms | 5839 | 80 | 7770.57 | 5121.25 | 0.0244141 | 2.25517 | 2(Loss) | true |
| simdjson (ondemand) | 866.525 | 0.106293 | 658.717ms | 5839 | 80 | 3732.59 | 6426.25 | 0.174757 | 2.84394 | 3(Loss) | true |
| Glaze | 778.449 | 0.229592 | 732.342ms | 5839 | 30 | 8091.95 | 7153.33 | 0.1396 | 3.15599 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1642.63 | 0.294985 | 399.777ms | 5839 | 40 | 4000 | 3390 | 0.394867 | 1.49457 | 1(Win) | true |
| Jsonifier | 1425.39 | 0.170648 | 466.464ms | 5839 | 30 | 1333.33 | 3906.67 | 0.25663 | 1.72574 | 2(Loss) | true |
| Glaze | 953.332 | 0.324289 | 660.167ms | 5839 | 1280 | 459264 | 5841.09 | 0.0615632 | 2.5848 | 3(Loss) | true |
| simdjson (ondemand) | 933.131 | 0.176031 | 688.485ms | 5839 | 4890 | 539611 | 5967.55 | 0.0826621 | 2.64153 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8062.87 | 0.276057 | 86.5655ms | 6938 | 320 | 1642.24 | 820.625 | 0.382263 | 0.296448 | 1(Win) | true |
| Glaze | 3604.93 | 0.300808 | 189.51ms | 6960 | 80 | 2454.11 | 1841.25 | 0.204082 | 0.677951 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8625.8 | 0.644744 | 83.7246ms | 6938 | 2560 | 62615.9 | 767.07 | 0.199 | 0.27765 | 1(Win) | true |
| Glaze | 4525.74 | 0.30889 | 150.954ms | 6960 | 4890 | 100359 | 1466.63 | 0.0282926 | 0.536191 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 992.393 | 0.235041 | 483.33ms | 4857 | 40 | 4814.1 | 4667.5 | 0.232641 | 2.4758 | 1(Win) | true |
| Jsonifier (two-stage) | 795.192 | 0.236313 | 601.291ms | 4857 | 2560 | 485072 | 5825 | 0.233915 | 3.09762 | 2(Loss) | true |
| Glaze | 773.737 | 0.189216 | 609.927ms | 4857 | 4890 | 627446 | 5986.52 | 0.32798 | 3.18466 | 3(Loss) | true |
| simdjson (ondemand) | 721.442 | 0.468725 | 667.275ms | 4857 | 640 | 579627 | 6420.47 | 0.0121666 | 3.41891 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1495.8 | 0.32784 | 377.598ms | 4857 | 30 | 3091.95 | 3096.67 | 0 | 1.63569 | 1(Win) | true |
| Glaze | 1358.82 | 0.361141 | 389.555ms | 4857 | 1280 | 193988 | 3408.83 | 0.125893 | 1.80743 | 2(Loss) | true |
| Jsonifier (two-stage) | 1124.27 | 0.263602 | 477.686ms | 4857 | 40 | 4717.95 | 4120 | 0 | 2.18375 | 3(Loss) | true |
| simdjson (ondemand) | 1026.98 | 0.727137 | 503.483ms | 4857 | 320 | 344188 | 4510.31 | 0.0485235 | 2.39617 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9160.93 | 0.146599 | 54.8624ms | 4857 | 1280 | 703.284 | 505.625 | 0 | 0.25497 | 1(Win) | true |
| Glaze | 3047.37 | 0.200911 | 155.581ms | 4857 | 320 | 2984.33 | 1520 | 0.37144 | 0.797986 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10508.6 | 0.441048 | 48.6321ms | 4857 | 640 | 2418.79 | 440.781 | 0.035461 | 0.221215 | 1(Win) | true |
| Glaze | 3610.81 | 0.191412 | 130.243ms | 4857 | 320 | 1929.37 | 1282.81 | 0.219727 | 0.670551 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1118.09 | 0.123663 | 586.311ms | 6701 | 160 | 7993.32 | 5715.62 | 0.0985114 | 2.20538 | 1(Win) | true |
| Jsonifier | 1101.11 | 0.103489 | 600.756ms | 6701 | 160 | 5772.01 | 5803.75 | 0.236356 | 2.23731 | 2(Loss) | true |
| Glaze | 1048.48 | 0.499392 | 624.234ms | 6701 | 1280 | 1.18591e+06 | 6095.08 | 0.198281 | 2.35067 | 3(Loss) | true |
| simdjson (ondemand) | 965.229 | 0.247323 | 671.041ms | 6701 | 2560 | 686414 | 6620.78 | 0.222523 | 2.55368 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1781.65 | 0.116266 | 455.573ms | 6701 | 160 | 2782.63 | 3586.88 | 0.0870474 | 1.37845 | 1(Win) | true |
| Jsonifier (two-stage) | 1507.15 | 0.249029 | 493.234ms | 6701 | 640 | 71358.3 | 4240.16 | 0.0552445 | 1.63171 | 2(Loss) | true |
| Jsonifier STATISTICAL TIE | 1465.89 | 0.195251 | 548.51ms | 6701 | 4890 | 354302 | 4359.53 | 0.440722 | 1.67873 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1465.73 | 0.197779 | 492.749ms | 6701 | 40 | 2974.36 | 4360 | 0.0763942 | 1.6842 | 3(Tie) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8667.6 | 0.227253 | 85.6587ms | 7376 | 320 | 1088.46 | 811.562 | 0.268817 | 0.276379 | 1(Win) | true |
| Glaze | 3019.01 | 0.314935 | 232.928ms | 7376 | 40 | 2153.85 | 2330 | 0 | 0.80888 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9562.35 | 0.364489 | 88.1161ms | 7376 | 320 | 2300.55 | 735.625 | 0.423012 | 0.249348 | 1(Win) | true |
| Glaze | 3566.86 | 0.279118 | 200.627ms | 7376 | 4890 | 148167 | 1972.13 | 0.438885 | 0.684899 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1129.71 | 0.126615 | 147.524ms | 1691 | 640 | 2090.77 | 1427.5 | 0.197412 | 2.14712 | 1(Win) | true |
| Jsonifier | 994.704 | 0.341627 | 167.912ms | 1691 | 80 | 2454.11 | 1621.25 | 0.384025 | 2.44213 | 2(Loss) | true |
| Jsonifier (two-stage) | 897.931 | 0.471083 | 192.173ms | 1691 | 2560 | 183247 | 1795.98 | 0.0805398 | 2.71283 | 3(Loss) | true |
| simdjson (ondemand) | 602.724 | 0.236067 | 266.291ms | 1691 | 160 | 6383.25 | 2675.62 | 0.302748 | 4.06629 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1419.29 | 0.476 | 137.891ms | 1691 | 80 | 2340.19 | 1136.25 | 0.10989 | 1.69954 | 1(Win) | true |
| Jsonifier | 1381.76 | 0.57496 | 159.172ms | 1691 | 2560 | 115276 | 1167.11 | 0.0334806 | 1.75036 | 2(Loss) | true |
| Jsonifier (two-stage) | 1215.96 | 0.295127 | 172.021ms | 1691 | 160 | 2451.26 | 1326.25 | 0.188147 | 2.00304 | 3(Loss) | true |
| simdjson (ondemand) | 846.542 | 0.262467 | 215.03ms | 1691 | 80 | 2000 | 1905 | 0.131406 | 2.87456 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10838.7 | 0.350026 | 21.2149ms | 1996 | 4890 | 1847.89 | 175.624 | 2.43127 | 0.19359 | 1(Win) | true |
| Glaze | 3657.35 | 0.309598 | 56.15ms | 1996 | 640 | 1661.75 | 520.469 | 0.14988 | 0.635889 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12207 | 1.25946 | 18.9929ms | 1996 | 640 | 2468.6 | 155.938 | 0.2 | 0.170932 | 1(Win) | true |
| Glaze | 4385.39 | 0.445247 | 46.3567ms | 1996 | 1280 | 4780.98 | 434.062 | 1.83746 | 0.525303 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1340.74 | 0.386109 | 160.726ms | 2158 | 80 | 2810.13 | 1535 | 0.162602 | 1.81983 | 1(Win) | true |
| Jsonifier (two-stage) | 1106.47 | 0.389671 | 198.287ms | 2158 | 80 | 4202.53 | 1860 | 0.268097 | 2.20865 | 2(Loss) | true |
| Jsonifier | 938.933 | 0.25573 | 223.026ms | 2158 | 4890 | 153640 | 2191.88 | 0.388521 | 2.60228 | 3(Loss) | true |
| simdjson (ondemand) | 797.686 | 0.163301 | 269.324ms | 2158 | 320 | 5680.25 | 2580 | 0.0242189 | 3.07185 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1668.11 | 0.43121 | 150.037ms | 2158 | 80 | 2264.24 | 1233.75 | 0.30303 | 1.45689 | 1(Win) | true |
| Jsonifier (two-stage) | 1476.61 | 0.368682 | 186.747ms | 2158 | 80 | 2112.34 | 1393.75 | 0.996377 | 1.64283 | 2(Loss) | true |
| Jsonifier | 1205.29 | 0.439239 | 216.769ms | 2158 | 40 | 2250 | 1707.5 | 0.0488281 | 2.02042 | 3(Loss) | true |
| simdjson (ondemand) | 1054.26 | 0.46462 | 214.277ms | 2158 | 2560 | 210593 | 1952.11 | 0.232661 | 2.31544 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10682.6 | 0.383646 | 29.3564ms | 2866 | 2560 | 2466.63 | 255.859 | 0.0305437 | 0.208084 | 1(Win) | true |
| Glaze | 3463.46 | 0.373808 | 82.5308ms | 2866 | 4890 | 42553.8 | 789.162 | 0.0125534 | 0.685086 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13172.2 | 0.710703 | 24.3025ms | 2866 | 320 | 695.925 | 207.5 | 0.598802 | 0.163216 | 1(Win) | true |
| Glaze | 4199.42 | 0.645193 | 68.1892ms | 2866 | 4890 | 86230.6 | 650.859 | 0.31903 | 0.559204 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1189.17 | 0.301401 | 369.398ms | 4390 | 2560 | 288250 | 3520.62 | 0.122198 | 2.06461 | 1(Win) | true |
| Jsonifier (two-stage) | 1029.5 | 0.319277 | 419.945ms | 4390 | 30 | 5057.47 | 4066.67 | 0.0820345 | 2.38358 | 2(Loss) | true |
| Glaze | 819.042 | 0.191528 | 525.061ms | 4390 | 4890 | 468693 | 5111.62 | 0.157179 | 3.00636 | 3(Loss) | true |
| simdjson (ondemand) | 594.956 | 0.622737 | 809.877ms | 4390 | 160 | 307248 | 7036.88 | 0.0443892 | 4.14521 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1412.17 | 0.180123 | 360.575ms | 4390 | 320 | 9125.29 | 2964.69 | 0.555556 | 1.73634 | 1(Win) | true |
| Jsonifier (two-stage) | 1210.66 | 0.118809 | 397.98ms | 4390 | 160 | 2700.86 | 3458.12 | 0.162925 | 2.02877 | 2(Loss) | true |
| Glaze | 995.336 | 0.238197 | 487.204ms | 4390 | 160 | 16061.3 | 4206.25 | 0.0594707 | 2.47485 | 3(Loss) | true |
| simdjson (ondemand) | 687.46 | 0.298239 | 671.822ms | 4390 | 30 | 9896.55 | 6090 | 0.550358 | 3.58686 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7017.01 | 0.399378 | 62.3414ms | 4390 | 1280 | 7267.83 | 596.641 | 0.645756 | 0.337945 | 1(Win) | true |
| Glaze | 2721.35 | 0.177036 | 160.923ms | 4390 | 320 | 2373.73 | 1538.44 | 0.222943 | 0.894007 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7499.14 | 0.246969 | 59.8294ms | 4390 | 1280 | 2433.32 | 558.281 | 0.139743 | 0.313654 | 1(Win) | true |
| Glaze | 3091.19 | 0.193082 | 140.516ms | 4390 | 1280 | 8753.32 | 1354.38 | 0.172751 | 0.783145 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2020.38 | 0.214812 | 466.741ms | 9378 | 30 | 2712.64 | 4426.67 | 0.449775 | 1.21717 | 1(Win) | true |
| Jsonifier (two-stage) | 2003.04 | 0.121117 | 449.151ms | 9378 | 160 | 4679.25 | 4465 | 0 | 1.22765 | 2(Loss) | true |
| Glaze | 1345.93 | 0.237292 | 682.863ms | 9378 | 2560 | 636472 | 6644.88 | 0.586166 | 1.83132 | 3(Loss) | true |
| simdjson (ondemand) | 1161.12 | 0.214146 | 754.57ms | 9378 | 80 | 21765.8 | 7702.5 | 0.983284 | 2.12431 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 2355.63 | 0.199008 | 427.574ms | 9378 | 30 | 1712.64 | 3796.67 | 0.0877193 | 1.04584 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 2349.45 | 0.121683 | 457.028ms | 9378 | 30 | 643.678 | 3806.67 | 0.0876424 | 1.04658 | 1(Tie) | true |
| Glaze | 1577.4 | 0.175091 | 629.487ms | 9378 | 4890 | 481916 | 5669.8 | 0.132954 | 1.56187 | 3(Loss) | true |
| simdjson (ondemand) | 1434.03 | 0.330516 | 719.915ms | 9378 | 30 | 12747.1 | 6236.67 | 0.483351 | 1.71704 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11715.9 | 0.289506 | 112.573ms | 11521 | 320 | 2358.84 | 937.812 | 0.232713 | 0.205551 | 1(Win) | true |
| Glaze | 3638.08 | 0.285908 | 299.063ms | 11521 | 2560 | 190867 | 3020.08 | 0.371294 | 0.674205 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13037.7 | 0.164138 | 100.855ms | 11521 | 1280 | 2449.12 | 842.734 | 0.00927128 | 0.183564 | 1(Win) | true |
| Glaze | 4497.22 | 0.160761 | 253.253ms | 11521 | 160 | 2468.16 | 2443.12 | 0.128074 | 0.543474 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1477.67 | 0.307437 | 309.783ms | 4669 | 30 | 2574.71 | 3013.33 | 0 | 1.66613 | 1(Win) | true |
| Jsonifier (two-stage) | 1090.46 | 0.169481 | 418.256ms | 4669 | 30 | 1436.78 | 4083.33 | 0.163532 | 2.24638 | 2(Loss) | true |
| Glaze | 924.637 | 0.0912225 | 496.417ms | 4669 | 160 | 3087.66 | 4815.62 | 0.0649351 | 2.66145 | 3(Loss) | true |
| simdjson (ondemand) | 807.564 | 0.10071 | 571.149ms | 4669 | 80 | 2466.77 | 5513.75 | 0.0226757 | 3.0495 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1671.4 | 0.100841 | 288.277ms | 4669 | 320 | 2309.46 | 2664.06 | 0.408879 | 1.46641 | 1(Win) | true |
| Jsonifier (two-stage) | 1172.54 | 0.0736496 | 405.728ms | 4669 | 160 | 1251.57 | 3797.5 | 0.230947 | 2.09535 | 2(Loss) | true |
| Glaze | 1028.93 | 0.123151 | 464.65ms | 4669 | 80 | 2272.15 | 4327.5 | 0.0578035 | 2.38997 | 3(Loss) | true |
| simdjson (ondemand) | 789.02 | 0.183864 | 615.255ms | 4669 | 30 | 3229.89 | 5643.33 | 0.23571 | 3.12175 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13680.9 | 0.375845 | 36.5006ms | 4669 | 1280 | 1915.34 | 325.469 | 0.239464 | 0.166452 | 1(Win) | true |
| Glaze | 2778.6 | 0.281856 | 176.265ms | 4669 | 160 | 3264.15 | 1602.5 | 0.391543 | 0.878031 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16000.7 | 0.586154 | 35.246ms | 4669 | 640 | 1702.83 | 278.281 | 0.168161 | 0.139819 | 1(Win) | true |
| Glaze | 3121.97 | 0.368816 | 153.191ms | 4669 | 80 | 2213.61 | 1426.25 | 0.0875657 | 0.779187 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1818.4 | 0.272745 | 432.63ms | 7932 | 30 | 3862.07 | 4160 | 0 | 1.3555 | 1(Win) | true |
| Jsonifier | 1590.39 | 0.175696 | 508.383ms | 7932 | 4890 | 341502 | 4756.42 | 0.00195829 | 1.54826 | 2(Loss) | true |
| simdjson (ondemand) | 1353.93 | 0.252361 | 578.791ms | 7932 | 2560 | 508931 | 5587.11 | 0.262169 | 1.82004 | 3(Loss) | true |
| Glaze | 1319.01 | 0.0935715 | 590.457ms | 7932 | 80 | 2303.8 | 5735 | 0.043573 | 1.86875 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1997.68 | 0.166701 | 427.378ms | 7932 | 30 | 1195.4 | 3786.67 | 0.438212 | 1.23105 | 1(Win) | true |
| Jsonifier | 1639.01 | 0.350521 | 473.776ms | 7932 | 1280 | 334996 | 4615.31 | 0.850149 | 1.50188 | 2(Loss) | true |
| Glaze | 1430.65 | 0.100156 | 558.335ms | 7932 | 40 | 1121.79 | 5287.5 | 0.205306 | 1.72079 | 3(Loss) | true |
| simdjson (ondemand) | 1346 | 0.11397 | 609.087ms | 7932 | 40 | 1641.03 | 5620 | 0.237812 | 1.83041 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11312.9 | 0.20413 | 92.5288ms | 9249 | 640 | 1621.19 | 779.688 | 0.2 | 0.211212 | 1(Win) | true |
| Glaze | 3504.45 | 0.406222 | 254.763ms | 9249 | 1280 | 133809 | 2516.95 | 0.00931099 | 0.699076 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12293.4 | 0.296503 | 78.5246ms | 9249 | 320 | 1448.28 | 717.5 | 0.437445 | 0.194205 | 1(Win) | true |
| Glaze | 3957.06 | 0.114048 | 228.115ms | 9249 | 320 | 2068.08 | 2229.06 | 0.0140174 | 0.617077 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 442.972 | 0.271304 | 995.309ms | 4604 | 2560 | 1.85127e+06 | 9911.95 | 0.155033 | 5.56185 | 1(Win) | true |
| Jsonifier (two-stage) | 432.867 | 0.248705 | 1080.53ms | 4604 | 30 | 19092 | 10143.3 | 0.131277 | 5.69301 | 2(Loss) | true |
| Glaze | 158.323 | 0.109349 | 2791.58ms | 4604 | 2560 | 2.35426e+06 | 27732.7 | 0.31508 | 15.6098 | 3(Loss) | true |
| simdjson (ondemand) | 99.1468 | 0.1012 | 4421.89ms | 4604 | 2560 | 5.14178e+06 | 44285 | 0.477904 | 24.9556 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 576.333 | 0.243471 | 918.017ms | 4604 | 4890 | 1.68239e+06 | 7618.36 | 0.012881 | 4.28033 | 1(Win) | true |
| Jsonifier (two-stage) | 537.093 | 0.165204 | 965.274ms | 4604 | 4890 | 891916 | 8174.97 | 0.0686578 | 4.59288 | 2(Loss) | true |
| Glaze | 185.126 | 0.076812 | 2687.58ms | 4604 | 40 | 13275.6 | 23717.5 | 0.220867 | 13.3548 | 3(Loss) | true |
| simdjson (ondemand) | 109.166 | 0.102643 | 4278.61ms | 4604 | 2560 | 4.36315e+06 | 40220.7 | 1.05741 | 22.6651 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1119.02 | 0.329073 | 420.855ms | 4918 | 2560 | 486998 | 4191.33 | 0.0260887 | 2.19792 | 1(Win) | true |
| Glaze | 769.401 | 0.143898 | 603.095ms | 4604 | 30 | 2022.99 | 5706.67 | 0.116686 | 3.20348 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1223.79 | 0.195695 | 396.73ms | 4918 | 40 | 2250 | 3832.5 | 0.0652742 | 2.01248 | 1(Win) | true |
| Glaze | 766.435 | 0.0888869 | 581.619ms | 4604 | 80 | 2074.37 | 5728.75 | 0.0218245 | 3.2123 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1577.69 | 0.139062 | 1137.92ms | 18245 | 4890 | 1.15019e+06 | 11028.7 | 0.33939 | 1.56392 | 1(Win) | true |
| Jsonifier | 1348.04 | 0.114296 | 1344ms | 18245 | 80 | 17411.4 | 12907.5 | 0.289687 | 1.83241 | 2(Loss) | true |
| Glaze | 587.322 | 0.543644 | 3070.3ms | 18245 | 160 | 4.15035e+06 | 29625.6 | 0.107709 | 4.20941 | 3(Loss) | true |
| simdjson (ondemand) | 405.708 | 0.490842 | 4450.19ms | 18245 | 80 | 3.54516e+06 | 42887.5 | 0.625615 | 6.0989 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1910.12 | 0.174137 | 1073.92ms | 18245 | 4890 | 1.23043e+06 | 9109.28 | 0.0934316 | 1.29218 | 1(Win) | true |
| Jsonifier | 1578.58 | 0.38158 | 1350.91ms | 18245 | 1280 | 2.26431e+06 | 11022.4 | 0.836931 | 1.56459 | 2(Loss) | true |
| Glaze | 643.031 | 0.126851 | 2909.34ms | 18245 | 2560 | 3.01617e+06 | 27059 | 0.184297 | 3.84666 | 3(Loss) | true |
| simdjson (ondemand) | 421.973 | 0.429806 | 4328.26ms | 18245 | 160 | 5.02554e+06 | 41234.4 | 0.0925448 | 5.86362 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4489.8 | 0.138573 | 563.011ms | 24893 | 40 | 2147.44 | 5287.5 | 0.0157629 | 0.547058 | 1(Win) | true |
| Glaze | 2989.96 | 0.611167 | 812.455ms | 24579 | 320 | 734627 | 7839.69 | 0.0438282 | 0.825123 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4660.96 | 0.13089 | 541.688ms | 24893 | 30 | 1333.33 | 5093.33 | 0.460224 | 0.52794 | 1(Win) | true |
| Glaze | 3381.23 | 0.0802278 | 714.988ms | 24579 | 80 | 2474.68 | 6932.5 | 0.14404 | 0.729451 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 515.208 | 0.23805 | 880.533ms | 4604 | 2560 | 1.05362e+06 | 8522.23 | 0.0499862 | 4.79054 | 1(Win) | true |
| Jsonifier (two-stage) | 467.595 | 0.246736 | 970.485ms | 4604 | 30 | 16103.4 | 9390 | 0.142197 | 5.27886 | 2(Loss) | true |
| simdjson (ondemand) | 190.348 | 0.108954 | 2345.84ms | 4604 | 4890 | 3.08863e+06 | 23066.8 | 0.101928 | 12.9905 | 3(Loss) | true |
| Glaze | 160.178 | 0.104057 | 2770.4ms | 4604 | 4890 | 3.97845e+06 | 27411.5 | 0.0418767 | 15.4413 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 689.822 | 0.173843 | 822.165ms | 4604 | 40 | 4897.44 | 6365 | 0.0261917 | 3.57258 | 1(Win) | true |
| Jsonifier (two-stage) | 601.677 | 0.17359 | 887.501ms | 4604 | 4890 | 784698 | 7297.46 | 0.168821 | 4.10014 | 2(Loss) | true |
| simdjson (ondemand) | 213.65 | 0.2842 | 2283.62ms | 4604 | 320 | 1.0916e+06 | 20550.9 | 0.331909 | 11.5736 | 3(Loss) | true |
| Glaze | 181.94 | 0.120414 | 2603.59ms | 4604 | 4890 | 4.12929e+06 | 24132.8 | 0.0903496 | 13.5933 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1135.63 | 0.124838 | 414.695ms | 4918 | 80 | 2126.58 | 4130 | 0.0604961 | 2.16694 | 1(Win) | true |
| Glaze | 734.042 | 0.209407 | 606.605ms | 4604 | 2560 | 401653 | 5981.56 | 0.0952543 | 3.35672 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1229.4 | 0.074227 | 387.396ms | 4918 | 160 | 1283.02 | 3815 | 0.0327761 | 2.00185 | 1(Win) | true |
| Glaze | 800.586 | 0.231632 | 560.65ms | 4604 | 2560 | 413136 | 5484.38 | 0.0939288 | 3.07753 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1683.21 | 0.148445 | 1062.39ms | 18245 | 4890 | 1.15147e+06 | 10337.3 | 0.105681 | 1.46691 | 1(Win) | true |
| Jsonifier | 1521.85 | 0.19818 | 1182.5ms | 18245 | 30 | 15402.3 | 11433.3 | 0 | 1.62298 | 2(Loss) | true |
| simdjson (ondemand) | 731.891 | 0.379705 | 2444.66ms | 18245 | 320 | 2.60758e+06 | 23773.8 | 0.0367918 | 3.37924 | 3(Loss) | true |
| Glaze | 586.367 | 0.180197 | 3001.55ms | 18245 | 1280 | 3.65977e+06 | 29673.9 | 0.457556 | 4.21816 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2136.69 | 0.240489 | 986.083ms | 18245 | 30 | 11505.7 | 8143.33 | 0.328542 | 1.1559 | 1(Win) | true |
| Jsonifier | 1852.5 | 0.26233 | 1104.76ms | 18245 | 2560 | 1.5542e+06 | 9392.62 | 0.157035 | 1.33247 | 2(Loss) | true |
| simdjson (ondemand) | 805.919 | 0.107311 | 2424.05ms | 18245 | 30 | 16103.4 | 21590 | 0.613779 | 3.06978 | 3(Loss) | true |
| Glaze | 640.961 | 0.170137 | 2897.28ms | 18245 | 1280 | 2.73043e+06 | 27146.4 | 0.0408831 | 3.85903 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4351.94 | 0.102608 | 561.424ms | 24893 | 80 | 2506.33 | 5455 | 0.0915751 | 0.5659 | 1(Win) | true |
| Glaze | 2852.49 | 0.114352 | 840.963ms | 24579 | 40 | 3532.05 | 8217.5 | 0.213415 | 0.864895 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4627.2 | 0.175598 | 517.242ms | 24893 | 4890 | 396888 | 5130.49 | 0.0278471 | 0.53214 | 1(Win) | true |
| Glaze | 3358.59 | 0.153463 | 719.904ms | 24579 | 4890 | 560955 | 6979.22 | 0.205486 | 0.734347 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 859.465 | 0.176067 | 580.694ms | 5094 | 4890 | 484315 | 5652.37 | 0.116844 | 2.85747 | 1(Win) | true |
| Jsonifier (two-stage) | 772.34 | 0.220266 | 650.91ms | 5094 | 30 | 5758.62 | 6290 | 0.0530223 | 3.18881 | 2(Loss) | true |
| Glaze | 626.437 | 0.150246 | 810.105ms | 5094 | 80 | 10860.8 | 7755 | 0.258565 | 3.92818 | 3(Loss) | true |
| simdjson (ondemand) | 337.91 | 0.165691 | 937.192ms | 5094 | 30 | 17023 | 14376.7 | 0.254394 | 7.30709 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1056.09 | 0.122292 | 584.004ms | 5094 | 80 | 2531.65 | 4600 | 0 | 2.33049 | 1(Win) | true |
| Jsonifier (two-stage) | 913.734 | 0.158353 | 651.263ms | 5094 | 30 | 2126.44 | 5316.67 | 0 | 2.69576 | 2(Loss) | true |
| Glaze | 816.473 | 0.238365 | 708.207ms | 5094 | 30 | 6034.48 | 5950 | 0.055991 | 3.02837 | 3(Loss) | true |
| simdjson (ondemand) | 636.908 | 0.125541 | 871.923ms | 5094 | 80 | 7335.44 | 7627.5 | 0 | 3.87969 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9391.73 | 0.204308 | 55.6575ms | 5094 | 1280 | 1429.58 | 517.266 | 0.19596 | 0.250146 | 1(Win) | true |
| Glaze | 2955.45 | 0.356378 | 171.195ms | 5094 | 80 | 2745.25 | 1643.75 | 0.0759878 | 0.824028 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11560.3 | 0.190352 | 45.6906ms | 5094 | 2560 | 1638.08 | 420.234 | 0.554631 | 0.201264 | 1(Win) | true |
| Glaze | 1956.91 | 0.378525 | 155.301ms | 5094 | 40 | 3532.05 | 2482.5 | 0.16756 | 1.25367 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1183.74 | 0.136425 | 682.134ms | 8051 | 80 | 6264.24 | 6486.25 | 0.28824 | 2.07742 | 1(Win) | true |
| Jsonifier | 1080.96 | 0.200155 | 734.18ms | 8051 | 2560 | 517439 | 7103.01 | 0.00384945 | 2.27587 | 2(Loss) | true |
| simdjson (ondemand) | 791.278 | 0.167444 | 1002.14ms | 8051 | 30 | 7919.54 | 9703.33 | 0.102951 | 3.11561 | 3(Loss) | true |
| Glaze | 525.413 | 0.201543 | 871.624ms | 8051 | 30 | 26023 | 14613.3 | 0.340987 | 4.69974 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1329.32 | 0.239981 | 693.47ms | 8051 | 2560 | 491850 | 5775.9 | 0.186985 | 1.85337 | 1(Win) | true |
| Jsonifier | 1278.03 | 0.178423 | 762.71ms | 8051 | 4890 | 561867 | 6007.73 | 0.274415 | 1.92882 | 2(Loss) | true |
| Glaze | 1177.39 | 0.111456 | 836.328ms | 8051 | 80 | 4226.27 | 6521.25 | 0.0191718 | 2.0974 | 3(Loss) | true |
| simdjson (ondemand) | 979.977 | 0.158824 | 909.789ms | 8051 | 4890 | 757200 | 7834.91 | 0.0300826 | 2.51777 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10931.7 | 0.412735 | 84.3488ms | 9255 | 4890 | 54304 | 807.403 | 0.00248339 | 0.218946 | 1(Win) | true |
| Glaze | 3400.44 | 0.157827 | 279.99ms | 9255 | 160 | 2685.14 | 2595.62 | 0.168269 | 0.719541 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13335.2 | 0.410857 | 71.3624ms | 9255 | 320 | 2366.38 | 661.875 | 0.284091 | 0.178141 | 1(Win) | true |
| Glaze | 3976.16 | 0.263863 | 225.687ms | 9255 | 4890 | 167761 | 2219.8 | 0.469873 | 0.615043 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 5366.93 | 0.185309 | 57.0403ms | 2889 | 1280 | 1158.37 | 513.359 | 0.348802 | 0.439636 | 1(Win) | true |
| Jsonifier | 5279.36 | 0.628209 | 56.097ms | 2889 | 160 | 1719.73 | 521.875 | 0.360577 | 0.442132 | 2(Loss) | true |
| simdjson (ondemand) | 3707.32 | 0.439645 | 86.4544ms | 2889 | 4890 | 52202.3 | 743.17 | 0.0480921 | 0.643884 | 3(Loss) | true |
| Glaze | 2775.11 | 0.324865 | 102.906ms | 2889 | 2560 | 26630.6 | 992.812 | 0.0708717 | 0.86826 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 5684.42 | 0.297434 | 53.4536ms | 2889 | 640 | 1330.11 | 484.688 | 0.385356 | 0.411558 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 5682.58 | 0.292586 | 52.3551ms | 2889 | 640 | 1287.93 | 484.844 | 0.616083 | 0.411154 | 1(Tie) | true |
| simdjson (ondemand) | 3976.02 | 0.450353 | 73.401ms | 2889 | 4890 | 47622.5 | 692.945 | 0.019094 | 0.598959 | 3(Loss) | true |
| Glaze | 2861.25 | 0.358304 | 100.326ms | 2889 | 4890 | 58209.9 | 962.924 | 0.105916 | 0.839967 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6329.57 | 0.429366 | 62.005ms | 3808 | 320 | 1942.01 | 573.75 | 0.325733 | 0.371702 | 1(Win) | true |
| Jsonifier (two-stage) | 6184.72 | 0.318693 | 62.02ms | 3808 | 320 | 1120.59 | 587.188 | 0.0531915 | 0.380914 | 2(Loss) | true |
| simdjson (ondemand) | 4832.06 | 0.372304 | 79.4904ms | 3808 | 320 | 2505.39 | 751.562 | 0.124585 | 0.495138 | 3(Loss) | true |
| Glaze | 3301.45 | 0 | 110.283ms | 3808 | 30 | 0 | 1100 | 0 | 0.727582 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 6939.35 | 1.50077 | 60.9493ms | 3808 | 30 | 1850.57 | 523.333 | 0 | 0.340651 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6925.56 | 0.458424 | 57.2327ms | 3808 | 320 | 1849.14 | 524.375 | 0.94451 | 0.340619 | 1(Tie) | true |
| simdjson (ondemand) | 5117.17 | 0.233355 | 75.8999ms | 3808 | 320 | 877.645 | 709.688 | 0.0440141 | 0.465858 | 3(Loss) | true |
| Glaze | 3502.44 | 0.369013 | 109.772ms | 3808 | 160 | 2342.37 | 1036.88 | 0.0603136 | 0.686026 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1444.92 | 0.510049 | 197.447ms | 2889 | 1280 | 121072 | 1906.8 | 0.0696037 | 1.6872 | 1(Win) | true |
| Jsonifier (two-stage) | 1356.68 | 0.316753 | 217.168ms | 2889 | 4890 | 202345 | 2030.82 | 0.190177 | 1.80128 | 2(Loss) | true |
| Glaze | 1257.74 | 0.269667 | 223.326ms | 2889 | 4890 | 170639 | 2190.57 | 0.00295752 | 1.94324 | 3(Loss) | true |
| simdjson (ondemand) | 1227.84 | 0.529088 | 240.068ms | 2889 | 1280 | 180416 | 2243.91 | 0.0348044 | 1.98898 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1886.7 | 0.197134 | 164.821ms | 2889 | 320 | 2651.94 | 1460.31 | 0.192226 | 1.28947 | 1(Win) | true |
| Jsonifier (two-stage) | 1546.83 | 0.302274 | 204.957ms | 2889 | 1280 | 37104.2 | 1781.17 | 0.258115 | 1.57666 | 2(Loss) | true |
| simdjson (ondemand) | 1535.18 | 0.120948 | 195.501ms | 2889 | 320 | 1507.74 | 1794.69 | 0.0174155 | 1.5869 | 3(Loss) | true |
| Glaze | 1522.85 | 0.340875 | 194.483ms | 2889 | 2560 | 97367.1 | 1809.22 | 0.262716 | 1.60126 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7830.59 | 0.585351 | 39.7291ms | 2963 | 4890 | 21818 | 360.859 | 0.87996 | 0.293194 | 1(Win) | true |
| Glaze | 4050.78 | 0.366779 | 73.1032ms | 2963 | 2560 | 16758.5 | 697.578 | 0.145381 | 0.584851 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10508.3 | 0.680949 | 30.7103ms | 2963 | 640 | 2145.91 | 268.906 | 0.635104 | 0.215887 | 1(Win) | true |
| Glaze | 4835.49 | 0.275986 | 62.0692ms | 2963 | 640 | 1664.71 | 584.375 | 0.214362 | 0.486385 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1784.57 | 0.263702 | 210.685ms | 3808 | 80 | 2303.8 | 2035 | 0 | 1.37013 | 1(Win) | true |
| simdjson (ondemand) | 1699.98 | 0.225384 | 226.307ms | 3808 | 160 | 3709.12 | 2136.25 | 0.058548 | 1.43609 | 2(Loss) | true |
| Glaze | 1464.35 | 0.281491 | 273.779ms | 3808 | 80 | 3898.73 | 2480 | 0.501505 | 1.67022 | 3(Loss) | true |
| Jsonifier | 1355.7 | 0.540083 | 279.885ms | 3808 | 1280 | 267914 | 2678.75 | 0.0700444 | 1.80736 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2112.54 | 0.130497 | 190.286ms | 3808 | 320 | 1610.4 | 1719.06 | 0.0545058 | 1.15542 | 1(Win) | true |
| Jsonifier (two-stage) | 2028.82 | 0.307921 | 215.181ms | 3808 | 80 | 2430.38 | 1790 | 0.13986 | 1.19944 | 2(Loss) | true |
| Glaze | 1790.06 | 0.176923 | 229.444ms | 3808 | 160 | 2061.32 | 2028.75 | 0.123381 | 1.3683 | 3(Loss) | true |
| Jsonifier | 1670.9 | 0.119119 | 249.237ms | 3808 | 320 | 2144.89 | 2173.44 | 0.187266 | 1.46578 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7215.35 | 0.478833 | 60.1056ms | 4300 | 4890 | 36215.9 | 568.344 | 0.0315922 | 0.32718 | 1(Win) | true |
| Glaze | 3287.21 | 0.493462 | 122.332ms | 4300 | 80 | 3031.65 | 1247.5 | 0 | 0.732442 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8040.78 | 0.94193 | 55.1385ms | 4300 | 40 | 923.077 | 510 | 0 | 0.296384 | 1(Win) | true |
| Glaze | 4466.49 | 0.283451 | 95.6338ms | 4300 | 640 | 4334.51 | 918.125 | 0.136333 | 0.535559 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3766.37 | 0.481487 | 6324.03ms | 466906 | 320 | 1.03689e+08 | 118224 | 0.356523 | 0.657182 | 1(Win) | true |
| Glaze | 1918.19 | 0.222711 | 6185.71ms | 466906 | 160 | 4.27641e+07 | 232133 | 0.0266621 | 1.29054 | 2(Loss) | true |
| simdjson (ondemand) | 1564.56 | 0.0884055 | 7359.48ms | 466906 | 640 | 4.05148e+07 | 284602 | 0.502988 | 1.5817 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3793.02 | 0.222397 | 6148.44ms | 466906 | 320 | 2.18121e+07 | 117394 | 0.423055 | 0.652539 | 1(Win) | true |
| Glaze | 1923.98 | 0.134404 | 6033.84ms | 466906 | 320 | 3.09622e+07 | 231434 | 0.172268 | 1.28668 | 2(Loss) | true |
| simdjson (ondemand) | 1559.76 | 0.117396 | 7451.75ms | 466906 | 1280 | 1.43767e+08 | 285478 | 0.28512 | 1.58701 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 3088.5 | 0.275645 | 5792.52ms | 699405 | 80 | 2.83499e+07 | 215964 | 0.131561 | 0.801505 | 1(Win) | true |
| Jsonifier | 2645.54 | 0.280711 | 6757.38ms | 699405 | 640 | 3.20575e+08 | 252124 | 0.0867494 | 0.935445 | 2(Loss) | true |
| simdjson (ondemand) | 1580.71 | 0.648361 | 5909.42ms | 767297 | 40 | 3.60342e+08 | 462925 | 0.419825 | 1.56602 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4489.4 | 0.571609 | 7806.38ms | 699405 | 30 | 2.16372e+07 | 148573 | 0.147856 | 0.551337 | 1(Win) | true |
| Glaze | 2996.12 | 0.399102 | 5812ms | 699405 | 40 | 3.15767e+07 | 222622 | 0.146576 | 0.826257 | 2(Loss) | true |
| simdjson (ondemand) | 1613.26 | 0.192904 | 5815.97ms | 767297 | 640 | 4.89983e+08 | 453586 | 2.02629 | 1.53414 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3570.23 | 0.207143 | 8829.43ms | 631514 | 320 | 3.90719e+07 | 168689 | 0.324432 | 0.693313 | 1(Win) | true |
| Glaze | 2470.25 | 0.352304 | 6113.57ms | 631514 | 40 | 2.95107e+07 | 243805 | 0.0951117 | 1.00217 | 2(Loss) | true |
