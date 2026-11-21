# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson (AVX512)
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-1020-azure using the Clang 24.0.0 compiler).  

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

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze STATISTICAL TIE | 1434.63 | 0.0779249 | 62.0821ms | 905 | 30 | 6.5931 | 601.6 | 0.00554109 | 1.64707 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1433.12 | 0.220731 | 61.9886ms | 905 | 30 | 53.0126 | 602.233 | 0.160772 | 1.65179 | 1(Tie) | true |
| Jsonifier (two-stage) | 1380.89 | 0.031607 | 65.0804ms | 905 | 640 | 24.9763 | 625.016 | 0.0624594 | 1.71725 | 3(Loss) | true |
| simdjson (ondemand) | 381.487 | 0.0536388 | 225.149ms | 905 | 30 | 44.1793 | 2262.4 | 0.309916 | 6.41134 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1507.02 | 0.0380869 | 60.0463ms | 905 | 320 | 15.2251 | 572.703 | 0.101049 | 1.57041 | 1(Win) | true |
| Glaze | 1434.54 | 0.0501997 | 82.399ms | 905 | 80 | 7.29731 | 601.638 | 0.0477634 | 1.65001 | 2(Loss) | true |
| Jsonifier | 1367.9 | 0.179541 | 61.6606ms | 905 | 40 | 51.3308 | 630.95 | 0.044926 | 1.73227 | 3(Loss) | true |
| simdjson (ondemand) | 383.563 | 0.0481484 | 233.053ms | 905 | 40 | 46.9513 | 2250.15 | 1.03866 | 6.3821 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2170.71 | 0.186045 | 42.5378ms | 905 | 40 | 21.8872 | 397.6 | 0.409117 | 1.07 | 1(Win) | true |
| Glaze | 193.598 | 0.11673 | 443.977ms | 905 | 4890 | 132425 | 4458.09 | 1.84275 | 12.7125 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4117.07 | 0.219951 | 29.6732ms | 905 | 30 | 6.37816 | 209.633 | 0.474759 | 0.523757 | 1(Win) | true |
| Glaze | 960.467 | 0.128046 | 97.3971ms | 905 | 80 | 105.914 | 898.6 | 0.0584584 | 2.50113 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1325.14 | 0.0985968 | 131.896ms | 1811 | 30 | 49.5402 | 1303.33 | 0.0511247 | 1.8309 | 1(Win) | true |
| Jsonifier (two-stage) | 1267.07 | 0.0892604 | 135.992ms | 1811 | 30 | 44.4092 | 1363.07 | 0.146944 | 1.91796 | 2(Loss) | true |
| Glaze | 899.565 | 0.0701883 | 196.709ms | 1811 | 30 | 54.4782 | 1919.93 | 0.171586 | 2.71622 | 3(Loss) | true |
| simdjson (ondemand) | 463.61 | 0.29005 | 379.483ms | 1811 | 640 | 74723.8 | 3725.34 | 0.0405419 | 5.30404 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1402.26 | 0.19656 | 131.764ms | 1811 | 4890 | 28660.2 | 1231.66 | 0.503247 | 1.72803 | 1(Win) | true |
| Jsonifier (two-stage) | 1392.39 | 0.0336878 | 127.322ms | 1811 | 160 | 27.9369 | 1240.39 | 0.061435 | 1.74111 | 2(Loss) | true |
| Glaze | 944.119 | 0.163716 | 185.764ms | 1811 | 4890 | 43860.6 | 1829.33 | 0.0510141 | 2.58554 | 3(Loss) | true |
| simdjson (ondemand) | 474.021 | 0.15763 | 368.102ms | 1811 | 2560 | 84442.8 | 3643.52 | 0.14574 | 5.18581 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 355.819 | 0.0455939 | 523.451ms | 1997 | 30 | 178.662 | 5352.4 | 0.180279 | 6.92754 | 1(Win) | true |
| Glaze | 270.626 | 0.119666 | 646.843ms | 1798 | 4890 | 281122 | 6336.08 | 0.0222112 | 9.11181 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 644.429 | 0.12178 | 316.568ms | 1997 | 160 | 2072.42 | 2955.31 | 0.0376582 | 3.80444 | 1(Win) | true |
| Glaze | 583.949 | 0.164662 | 303.771ms | 1798 | 30 | 701.352 | 2936.4 | 0.195632 | 4.20362 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2766.4 | 0.102145 | 134.39ms | 3862 | 30 | 55.4816 | 1331.37 | 0.149996 | 0.876739 | 1(Win) | true |
| Jsonifier | 2747.24 | 0.0395505 | 138.083ms | 3862 | 160 | 44.9836 | 1340.65 | 0.0727788 | 0.883289 | 2(Loss) | true |
| Glaze | 1422.42 | 0.0222352 | 269.758ms | 3862 | 160 | 53.0361 | 2589.32 | 0.0513867 | 1.72351 | 3(Loss) | true |
| simdjson (ondemand) | 795.255 | 0.0447483 | 465.796ms | 3862 | 30 | 128.851 | 4631.33 | 0.0518478 | 3.09568 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2988.95 | 0.0323917 | 125.96ms | 3862 | 160 | 25.4904 | 1232.24 | 0.0629333 | 0.810658 | 1(Win) | true |
| Jsonifier | 2943.4 | 0.0266221 | 129.03ms | 3862 | 320 | 35.5109 | 1251.31 | 0.133539 | 0.823096 | 2(Loss) | true |
| Glaze | 1436.83 | 0.0285197 | 265.417ms | 3862 | 160 | 85.5119 | 2563.35 | 0.0136521 | 1.70588 | 3(Loss) | true |
| simdjson (ondemand) | 820.257 | 0.0248614 | 456.152ms | 3862 | 30 | 37.3851 | 4490.17 | 0.217241 | 3.00032 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 941.84 | 0.0553136 | 405.232ms | 3862 | 80 | 374.303 | 3910.53 | 0.0671716 | 2.61133 | 1(Win) | true |
| Glaze | 788.637 | 0.231635 | 459.926ms | 3862 | 2560 | 299583 | 4670.2 | 0.397401 | 3.12133 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4209.08 | 0.0343318 | 96.3506ms | 3862 | 320 | 28.8797 | 875.034 | 0.0667385 | 0.571091 | 1(Win) | true |
| Glaze | 2581.91 | 0.109881 | 156.829ms | 3862 | 30 | 73.7069 | 1426.5 | 0.30705 | 0.942008 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1777.31 | 0.074951 | 516.317ms | 9578 | 30 | 445.145 | 5139.4 | 0.0512644 | 1.38603 | 1(Win) | true |
| Jsonifier (two-stage) | 1658.35 | 0.0481993 | 559.111ms | 9578 | 80 | 563.857 | 5508.06 | 0.262785 | 1.4856 | 2(Loss) | true |
| Glaze | 1384.1 | 0.0500652 | 649.941ms | 9578 | 40 | 436.664 | 6599.45 | 0.0426621 | 1.78189 | 3(Loss) | true |
| simdjson (ondemand) | 1275.48 | 0.0621982 | 725.751ms | 9578 | 30 | 595.22 | 7161.43 | 0.00418928 | 1.93445 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2509.74 | 0.319596 | 479.7ms | 9578 | 640 | 86591.4 | 3639.54 | 0.934027 | 0.979105 | 1(Win) | true |
| Jsonifier (two-stage) | 2419.49 | 0.122169 | 517.732ms | 9578 | 4890 | 104024 | 3775.3 | 0.248543 | 1.01607 | 2(Loss) | true |
| Glaze | 1945.12 | 0.0493368 | 605.496ms | 9578 | 30 | 161.034 | 4696 | 0.256298 | 1.26614 | 3(Loss) | true |
| simdjson (ondemand) | 1579.67 | 0.0706048 | 710.405ms | 9578 | 30 | 500.041 | 5782.4 | 0.00576429 | 1.55995 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4635.67 | 0.0718909 | 201.532ms | 9578 | 160 | 321.065 | 1970.44 | 0.0139582 | 0.527338 | 1(Win) | true |
| Glaze | 2005.19 | 0.207847 | 461.67ms | 9578 | 1280 | 114745 | 4555.32 | 0.454193 | 1.22776 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13367.3 | 0.151845 | 83.4339ms | 9578 | 30 | 32.2989 | 683.333 | 0.204459 | 0.178329 | 1(Win) | true |
| Glaze | 5468.65 | 0.137483 | 178.295ms | 9578 | 40 | 210.933 | 1670.3 | 0.0678982 | 0.445714 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2967.63 | 0.0652658 | 129.71ms | 3873 | 40 | 26.3942 | 1244.62 | 0.0702529 | 0.81697 | 1(Win) | true |
| Jsonifier (two-stage) | 2946.03 | 0.0571528 | 130.137ms | 3873 | 80 | 41.0759 | 1253.75 | 0.0896504 | 0.823573 | 2(Loss) | true |
| Glaze | 1422.5 | 0.0417072 | 264.086ms | 3873 | 80 | 93.8214 | 2596.54 | 0.0168522 | 1.72347 | 3(Loss) | true |
| simdjson (ondemand) | 799.09 | 0.0326491 | 531.974ms | 3873 | 30 | 68.323 | 4622.23 | 0.122023 | 3.08282 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3297.95 | 0.0480583 | 115.557ms | 3873 | 80 | 23.1758 | 1119.96 | 0.132641 | 0.733617 | 1(Win) | true |
| Jsonifier (two-stage) | 3056.15 | 0.0858086 | 124.412ms | 3873 | 40 | 43.0199 | 1208.58 | 0.116664 | 0.792958 | 2(Loss) | true |
| Glaze | 1385.24 | 0.0279307 | 269.197ms | 3873 | 160 | 88.742 | 2666.39 | 0.117063 | 1.76926 | 3(Loss) | true |
| simdjson (ondemand) | 791.275 | 0.0202699 | 475.029ms | 3873 | 80 | 71.6201 | 4667.89 | 0.137186 | 3.11184 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 934.203 | 0.0548404 | 422.931ms | 3873 | 40 | 188.051 | 3953.72 | 0.267594 | 2.63435 | 1(Win) | true |
| Glaze | 811.769 | 0.117241 | 455.829ms | 3873 | 4890 | 139156 | 4550.04 | 0.399861 | 3.0302 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4510.06 | 0.0286626 | 90.709ms | 3873 | 640 | 35.2647 | 818.964 | 0.0471473 | 0.531887 | 1(Win) | true |
| Glaze | 2592.41 | 0.089459 | 153.437ms | 3873 | 30 | 48.7368 | 1424.77 | 0.00233951 | 0.936905 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1722.39 | 0.209958 | 5331.89ms | 94653 | 320 | 3.87456e+06 | 52408.8 | 0.261603 | 1.4367 | 1(Win) | true |
| Jsonifier (two-stage) | 1538.34 | 0.137966 | 5977.9ms | 94653 | 640 | 4.1946e+06 | 58679.1 | 0.054521 | 1.60868 | 2(Loss) | true |
| Glaze | 1440.57 | 0.0889979 | 6237.83ms | 94653 | 1280 | 3.98079e+06 | 62661.4 | 0.492388 | 1.71788 | 3(Loss) | true |
| simdjson (ondemand) | 1137.7 | 0.204994 | 8285.17ms | 94653 | 160 | 4.23267e+06 | 79342.4 | 0.0417117 | 2.17545 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2511.54 | 0.146684 | 4986.14ms | 94653 | 320 | 889419 | 35941.4 | 0.634886 | 0.98508 | 1(Win) | true |
| Jsonifier (two-stage) | 2168.86 | 0.11159 | 5456.07ms | 94653 | 640 | 1.38051e+06 | 41620.2 | 0.104517 | 1.14081 | 2(Loss) | true |
| Glaze | 2007.35 | 0.0536897 | 5806.02ms | 94653 | 4890 | 2.85045e+06 | 44968.8 | 0.177895 | 1.23266 | 3(Loss) | true |
| simdjson (ondemand) | 1380.13 | 0.0424019 | 7811.65ms | 94653 | 4890 | 3.76106e+06 | 65405.8 | 0.174229 | 1.79306 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17815.5 | 0.468778 | 535.881ms | 94653 | 640 | 361066 | 5066.83 | 0.46755 | 0.138232 | 1(Win) | true |
| Glaze | 5397.78 | 0.081179 | 1668.76ms | 94653 | 2560 | 471808 | 16723.2 | 0.637727 | 0.457953 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18428.1 | 0.0411406 | 499.969ms | 94653 | 30 | 121.834 | 4898.4 | 0.00680541 | 0.133643 | 1(Win) | true |
| Glaze | 5948.22 | 0.118494 | 1567.89ms | 94653 | 1280 | 413899 | 15175.7 | 0.131247 | 0.415495 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1903.22 | 0.0484115 | 6305.02ms | 124597 | 4890 | 4.46731e+06 | 62433.8 | 0.358614 | 1.30028 | 1(Win) | true |
| Jsonifier | 1743.22 | 0.0442815 | 6853.86ms | 124597 | 4890 | 4.45517e+06 | 68164.1 | 0.256284 | 1.41968 | 2(Loss) | true |
| Glaze | 1612.52 | 0.0937818 | 7408.84ms | 124597 | 1280 | 6.11297e+06 | 73689 | 0.733722 | 1.5348 | 3(Loss) | true |
| simdjson (ondemand) | 1406.32 | 0.157977 | 8500.09ms | 124597 | 160 | 2.85074e+06 | 84493.7 | 0.0893913 | 1.75993 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2597.09 | 0.13838 | 5805.03ms | 124597 | 1280 | 5.13095e+06 | 45753.1 | 0.276148 | 0.952716 | 1(Win) | true |
| Jsonifier | 2347.53 | 0.252315 | 6391.36ms | 124597 | 80 | 1.30488e+06 | 50617 | 0.316993 | 1.0541 | 2(Loss) | true |
| Glaze | 2077.78 | 0.18012 | 6862.6ms | 124597 | 640 | 6.79079e+06 | 57188.4 | 0.222716 | 1.191 | 3(Loss) | true |
| simdjson (ondemand) | 1854.47 | 0.110551 | 7872.94ms | 124597 | 640 | 3.21127e+06 | 64074.9 | 0.624532 | 1.33448 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19545.5 | 0.042148 | 685.581ms | 136037 | 30 | 234.8 | 6637.6 | 0.241471 | 0.126191 | 1(Win) | true |
| Glaze | 6040.38 | 0.230704 | 2170.37ms | 136076 | 640 | 1.57226e+06 | 21484.1 | 0.0715284 | 0.409376 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18084.9 | 0.0347215 | 694.925ms | 136037 | 80 | 496.328 | 7173.66 | 0.0687808 | 0.136372 | 1(Win) | true |
| Glaze | 6822.15 | 0.0272285 | 1959.2ms | 136076 | 40 | 1073.07 | 19022.2 | 0.813382 | 0.362406 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 839.886 | 0.253965 | 8015.14ms | 2251027 | 160 | 6.742e+09 | 2.556e+06 | 1.41738 | 2.94775 | 1(Win) | true |
| Jsonifier (two-stage) | 796.076 | 0.374042 | 8655.14ms | 2251027 | 30 | 3.05222e+09 | 2.69666e+06 | 0.679015 | 3.10998 | 2(Loss) | true |
| Glaze | 777.94 | 0.0925109 | 8961.38ms | 2251027 | 30 | 1.95514e+08 | 2.75953e+06 | 1.10809 | 3.18249 | 3(Loss) | true |
| simdjson (ondemand) | 691.67 | 0.123896 | 9220.96ms | 2251027 | 30 | 4.43606e+08 | 3.10372e+06 | 1.45024 | 3.57925 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1031.04 | 0.248805 | 7841.4ms | 2251027 | 40 | 1.07346e+09 | 2.08211e+06 | 0.562129 | 2.40122 | 1(Win) | true |
| Jsonifier (two-stage) | 911.043 | 0.0902768 | 8811.7ms | 2251027 | 30 | 1.35755e+08 | 2.35636e+06 | 0.353689 | 2.71749 | 2(Loss) | true |
| simdjson (ondemand) | 908.694 | 0.0504105 | 8785.87ms | 2251027 | 160 | 2.26928e+08 | 2.36245e+06 | 0.660629 | 2.72454 | 3(Loss) | true |
| Glaze | 883.984 | 0.229225 | 9027.12ms | 2251027 | 40 | 1.23952e+09 | 2.42849e+06 | 1.07534 | 2.8007 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1987.53 | 0.0928361 | 6319.06ms | 2090326 | 80 | 6.93622e+07 | 1.003e+06 | 0.468223 | 1.24562 | 1(Win) | true |
| Glaze | 984.774 | 0.27826 | 6391.72ms | 2090234 | 80 | 2.53809e+09 | 2.02422e+06 | 1.07705 | 2.51404 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1989.76 | 0.137191 | 6479.33ms | 2090326 | 320 | 6.04546e+08 | 1.00188e+06 | 0.338744 | 1.24423 | 1(Win) | true |
| Glaze | 1006.95 | 0.0408998 | 6200.96ms | 2090234 | 160 | 1.04892e+08 | 1.97965e+06 | 0.108978 | 2.45867 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1697.35 | 0.125497 | 9769.44ms | 5373214 | 80 | 1.14837e+09 | 3.01899e+06 | 1.85002 | 1.45862 | 1(Win) | true |
| Jsonifier (two-stage) | 1661.13 | 0.154888 | 9617.47ms | 5373214 | 160 | 3.65274e+09 | 3.08483e+06 | 2.04426 | 1.49037 | 2(Loss) | true |
| Jsonifier | 1646.94 | 0.191554 | 9652.68ms | 5373214 | 40 | 1.42087e+09 | 3.11141e+06 | 0.242556 | 1.50326 | 3(Loss) | true |
| Glaze | 1575.31 | 0.210207 | 10173ms | 5373214 | 160 | 7.48082e+09 | 3.25288e+06 | 0.854518 | 1.57162 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2002 | 0.0734548 | 9607.43ms | 5373214 | 80 | 2.82795e+08 | 2.55959e+06 | 0.493396 | 1.23665 | 1(Win) | true |
| Jsonifier | 1962.05 | 0.547304 | 9541.33ms | 5373214 | 80 | 1.63453e+10 | 2.6117e+06 | 0.315241 | 1.26183 | 2(Loss) | true |
| simdjson (ondemand) | 1906.07 | 0.17131 | 9857.38ms | 5373214 | 40 | 8.48423e+08 | 2.6884e+06 | 0.344367 | 1.29887 | 3(Loss) | true |
| Glaze | 1780.02 | 0.11451 | 5012.62ms | 5373214 | 40 | 4.34676e+08 | 2.87879e+06 | 0.784672 | 1.39087 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5686.34 | 0.0582839 | 7178.3ms | 6661989 | 30 | 1.27222e+07 | 1.1173e+06 | 0.0198683 | 0.435382 | 1(Win) | true |
| Glaze | 3200.17 | 0.546915 | 6248.5ms | 6661897 | 80 | 9.43144e+09 | 1.98529e+06 | 0.362842 | 0.773628 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5676.44 | 0.0980973 | 7245.18ms | 6661989 | 40 | 4.82203e+07 | 1.11925e+06 | 0.0694517 | 0.436138 | 1(Win) | true |
| Glaze | 3549.57 | 0.0524396 | 5578.26ms | 6661897 | 160 | 1.40956e+08 | 1.78988e+06 | 0.278201 | 0.697482 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2267.87 | 0.28437 | 5496.35ms | 500299 | 80 | 2.8634e+07 | 210383 | 0.329934 | 1.09153 | 1(Win) | true |
| Jsonifier (two-stage) | 1924.13 | 0.18681 | 6446.71ms | 500299 | 40 | 8.58327e+06 | 247968 | 0.213412 | 1.28651 | 2(Loss) | true |
| Glaze | 1490.41 | 0.0578501 | 8160.71ms | 500299 | 1280 | 4.39e+07 | 320128 | 0.0403329 | 1.66094 | 3(Loss) | true |
| simdjson (ondemand) | 1114.09 | 0.088024 | 5526.49ms | 500299 | 320 | 4.54745e+07 | 428260 | 0.0300382 | 2.22206 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2758.48 | 0.185264 | 5306.21ms | 500299 | 80 | 8.21472e+06 | 172965 | 0.177837 | 0.897373 | 1(Win) | true |
| Jsonifier (two-stage) | 2248.07 | 0.16903 | 6366.49ms | 500299 | 160 | 2.05914e+07 | 212237 | 0.142317 | 1.10114 | 2(Loss) | true |
| Glaze | 1719.78 | 0.516729 | 7747.81ms | 500299 | 160 | 3.28822e+08 | 277433 | 0.680582 | 1.43947 | 3(Loss) | true |
| simdjson (ondemand) | 1268.8 | 0.308473 | 5406.77ms | 500299 | 30 | 4.03669e+07 | 376041 | 0.270781 | 1.95114 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9969.79 | 0.115303 | 4892.18ms | 500299 | 4890 | 1.48893e+07 | 47856.8 | 0.0312588 | 0.248192 | 1(Win) | true |
| Glaze | 3861.49 | 0.430866 | 6298.51ms | 500299 | 40 | 1.13369e+07 | 123559 | 0.27818 | 0.640943 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9960.89 | 0.166854 | 4895.64ms | 500299 | 320 | 2.04403e+06 | 47899.6 | 0.0170764 | 0.248408 | 1(Win) | true |
| Glaze | 4385.6 | 0.048119 | 5629.91ms | 500299 | 2560 | 7.01576e+06 | 108793 | 0.416905 | 0.564395 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3928.76 | 0.1222 | 7330.6ms | 1151920 | 160 | 1.86808e+07 | 279619 | 0.134152 | 0.630062 | 1(Win) | true |
| Jsonifier | 3202.52 | 0.296168 | 9092.5ms | 1151920 | 40 | 4.12853e+07 | 343028 | 0.0780351 | 0.773006 | 2(Loss) | true |
| Glaze | 2451.04 | 0.108215 | 5720.28ms | 1151920 | 640 | 1.50557e+08 | 448201 | 0.158912 | 1.01003 | 3(Loss) | true |
| simdjson (ondemand) | 2383.67 | 0.0798023 | 5918.65ms | 1151920 | 320 | 4.32844e+07 | 460867 | 0.101729 | 1.03856 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4547.93 | 0.0991285 | 7079.56ms | 1151920 | 160 | 9.17349e+06 | 241551 | 0.121589 | 0.544306 | 1(Win) | true |
| Jsonifier | 3616.44 | 0.243631 | 8719.24ms | 1151920 | 40 | 2.19081e+07 | 303767 | 0.466346 | 0.684525 | 2(Loss) | true |
| Glaze | 2742.13 | 0.0827759 | 5807ms | 1151920 | 160 | 1.75953e+07 | 400622 | 0.0211591 | 0.90282 | 3(Loss) | true |
| simdjson (ondemand) | 2687.39 | 0.0803407 | 5653.85ms | 1151920 | 160 | 1.72573e+07 | 408782 | 0.0973762 | 0.921198 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16895.3 | 0.120183 | 8379.1ms | 1439562 | 640 | 6.10373e+06 | 81257.5 | 0.508848 | 0.146489 | 1(Win) | true |
| Glaze | 4945.37 | 0.245255 | 6945.11ms | 1439584 | 30 | 1.3907e+07 | 277612 | 0.57581 | 0.500543 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16935.4 | 0.129544 | 8201.35ms | 1439562 | 640 | 7.0581e+06 | 81065.4 | 0.311796 | 0.146143 | 1(Win) | true |
| Glaze | 5860.08 | 0.43665 | 5817.46ms | 1439584 | 30 | 3.13946e+07 | 234279 | 0.101457 | 0.422437 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2323.64 | 0.0433702 | 2379.41ms | 56369 | 30 | 3020.27 | 23135.1 | 0.532698 | 1.06426 | 1(Win) | true |
| Jsonifier (two-stage) | 1903.03 | 0.119444 | 2871.55ms | 56369 | 640 | 728618 | 28248.5 | 0.131129 | 1.29977 | 2(Loss) | true |
| Glaze | 1663.65 | 0.114366 | 3264.03ms | 56369 | 1280 | 1.74809e+06 | 32313.1 | 0.20808 | 1.48697 | 3(Loss) | true |
| simdjson (ondemand) | 858.872 | 0.180192 | 6382.02ms | 56369 | 320 | 4.07048e+06 | 62591 | 0.174286 | 2.88142 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3043.49 | 0.0782992 | 2118.62ms | 56369 | 4890 | 935320 | 17663.2 | 0.0595769 | 0.812299 | 1(Win) | true |
| Jsonifier (two-stage) | 2413.21 | 0.0813925 | 2673.07ms | 56369 | 2560 | 841588 | 22276.4 | 0.0549379 | 1.02472 | 2(Loss) | true |
| Glaze | 2084.63 | 0.398709 | 2953.15ms | 56369 | 80 | 845721 | 25787.7 | 0.0666056 | 1.18648 | 3(Loss) | true |
| simdjson (ondemand) | 935.271 | 0.701337 | 6194.09ms | 56369 | 30 | 4.87506e+06 | 57478.2 | 0.384751 | 2.64594 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15051.3 | 0.0933391 | 370.897ms | 56369 | 30 | 333.413 | 3571.63 | 0.533871 | 0.163278 | 1(Win) | true |
| Glaze | 3548.87 | 0.175721 | 1494.27ms | 56369 | 40 | 28340.5 | 15147.8 | 0.158023 | 0.696398 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14805.2 | 0.0427568 | 362.289ms | 56369 | 40 | 96.4103 | 3631 | 0.0238742 | 0.166035 | 1(Win) | true |
| Glaze | 3875.61 | 0.792935 | 1361.79ms | 56369 | 80 | 967755 | 13870.8 | 0.0117167 | 0.637607 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2525.76 | 0.0772391 | 3202.42ms | 83958 | 4890 | 2.93173e+06 | 31700.8 | 0.376768 | 0.979364 | 1(Win) | true |
| Jsonifier | 2038.96 | 0.0923028 | 4000.46ms | 83958 | 2560 | 3.36339e+06 | 39269.3 | 0.202025 | 1.21339 | 2(Loss) | true |
| Glaze | 1984.7 | 0.167428 | 4147.23ms | 83958 | 320 | 1.45996e+06 | 40342.9 | 0.352071 | 1.24663 | 3(Loss) | true |
| simdjson (ondemand) | 1186.28 | 0.115796 | 6714.22ms | 83958 | 640 | 3.9095e+06 | 67495.6 | 0.327749 | 2.08619 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3223.56 | 0.116966 | 2873.44ms | 83958 | 80 | 67524.3 | 24838.5 | 0.358488 | 0.767155 | 1(Win) | true |
| Jsonifier | 2446.26 | 0.0437947 | 3669.54ms | 83958 | 40 | 8219.05 | 32731 | 0.265479 | 1.01122 | 2(Loss) | true |
| Glaze | 2421.48 | 0.133391 | 3715.42ms | 83958 | 640 | 1.24509e+06 | 33066 | 0.0428882 | 1.02166 | 3(Loss) | true |
| simdjson (ondemand) | 1339.75 | 0.157252 | 6299.75ms | 83958 | 320 | 2.82634e+06 | 59764 | 0.0515983 | 1.84715 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17887.4 | 0.164399 | 509.169ms | 94370 | 2560 | 175152 | 5031.38 | 0.00289581 | 0.137709 | 1(Win) | true |
| Glaze | 3456.67 | 0.207613 | 2670.57ms | 94370 | 320 | 935002 | 26036.1 | 0.0337505 | 0.715556 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18227.9 | 0.049168 | 516.238ms | 94370 | 30 | 176.8 | 4937.4 | 0.141574 | 0.13511 | 1(Win) | true |
| Glaze | 3558.11 | 0.0572118 | 2511.22ms | 94370 | 4890 | 1.02402e+06 | 25293.9 | 0.357146 | 0.695061 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1818.56 | 0.0813741 | 2838.36ms | 53331 | 2560 | 1.32592e+06 | 27967.4 | 0.0989868 | 1.36013 | 1(Win) | true |
| Jsonifier | 1696.59 | 0.104286 | 3088.67ms | 53331 | 2560 | 2.50205e+06 | 29977.9 | 1.04917 | 1.45796 | 2(Loss) | true |
| Glaze | 1411.04 | 0.128588 | 3526.61ms | 53331 | 2560 | 5.49949e+06 | 36044.7 | 0.320356 | 1.7533 | 3(Loss) | true |
| simdjson (ondemand) | 988.472 | 0.0713447 | 5135.63ms | 53331 | 4890 | 6.58966e+06 | 51453.6 | 1.12763 | 2.50325 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2308.04 | 0.216327 | 2695.13ms | 53331 | 40 | 90897.8 | 22036.2 | 0.0845621 | 1.07132 | 1(Win) | true |
| Jsonifier | 2268.22 | 0.157956 | 2674.4ms | 53331 | 1280 | 1.60573e+06 | 22423 | 0.314829 | 1.09018 | 2(Loss) | true |
| Glaze | 1868.63 | 0.273148 | 3359.24ms | 53331 | 320 | 1.76872e+06 | 27218 | 0.77328 | 1.32369 | 3(Loss) | true |
| simdjson (ondemand) | 1130.37 | 0.280464 | 5030.44ms | 53331 | 80 | 1.27398e+06 | 44994.5 | 0.229079 | 2.18893 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16358.6 | 0.127534 | 349.785ms | 58581 | 30 | 569.109 | 3415.17 | 0.213296 | 0.150247 | 1(Win) | true |
| Glaze | 5937.5 | 0.0981864 | 943.82ms | 58581 | 4890 | 417367 | 9409.22 | 0.154281 | 0.415846 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16322.7 | 0.196843 | 349.257ms | 58581 | 2560 | 116201 | 3422.66 | 0.121695 | 0.15054 | 1(Win) | true |
| Glaze | 6721.94 | 0.125912 | 854.132ms | 58581 | 30 | 3285.32 | 8311.17 | 0.2209 | 0.367163 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2207.21 | 0.366903 | 2870.1ms | 65103 | 320 | 3.40855e+06 | 28129.3 | 0.0147666 | 1.12064 | 1(Win) | true |
| Glaze | 1662.11 | 0.20678 | 3827.92ms | 65103 | 640 | 3.81839e+06 | 37354.4 | 0.0555099 | 1.48854 | 2(Loss) | true |
| Jsonifier | 1571.59 | 0.322128 | 3845.59ms | 65103 | 320 | 5.18238e+06 | 39505.8 | 0.202508 | 1.5742 | 3(Loss) | true |
| simdjson (ondemand) | 1213.27 | 0.1052 | 5253.4ms | 65103 | 2560 | 7.4192e+06 | 51173.4 | 0.0316106 | 2.03951 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2923.96 | 0.468109 | 2661.15ms | 65103 | 80 | 790394 | 21233.9 | 0.434858 | 0.845679 | 1(Win) | true |
| Jsonifier | 2026.37 | 0.0714482 | 3688.45ms | 65103 | 4890 | 2.34346e+06 | 30639.6 | 0.186185 | 1.22075 | 2(Loss) | true |
| Glaze | 1975.77 | 0.103925 | 3655.27ms | 65103 | 2560 | 2.73028e+06 | 31424.2 | 0.140746 | 1.25202 | 3(Loss) | true |
| simdjson (ondemand) | 1362.12 | 0.0792883 | 5105.75ms | 65103 | 2560 | 3.34372e+06 | 45581.2 | 0.026133 | 1.8165 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15766.2 | 0.0803819 | 480.81ms | 78778 | 30 | 440.144 | 4765.17 | 0.076306 | 0.156239 | 1(Win) | true |
| Glaze | 5219.36 | 0.121935 | 1456.09ms | 78778 | 4890 | 1.50639e+06 | 14394.2 | 0.0917142 | 0.473501 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16178.9 | 0.0409234 | 483.379ms | 78778 | 80 | 288.899 | 4643.61 | 0.00780703 | 0.152163 | 1(Win) | true |
| Glaze | 5915.88 | 0.0429619 | 1318.69ms | 78778 | 30 | 893.016 | 12699.5 | 0.497232 | 0.417665 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2499.78 | 0.107058 | 449.548ms | 11812 | 40 | 930.994 | 4506.32 | 0.034593 | 0.984782 | 1(Win) | true |
| Jsonifier (two-stage) | 1867.79 | 0.0663484 | 607.636ms | 11812 | 30 | 480.369 | 6031.1 | 0.060833 | 1.32009 | 2(Loss) | true |
| Glaze | 1733.54 | 0.0708516 | 664.019ms | 11812 | 30 | 635.913 | 6498.13 | 0.205278 | 1.42223 | 3(Loss) | true |
| simdjson (ondemand) | 1013.71 | 0.102681 | 1118.52ms | 11812 | 4890 | 636662 | 11112.4 | 0.246001 | 2.43666 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2772.96 | 0.049406 | 441.582ms | 11812 | 80 | 322.263 | 4062.38 | 0.0560331 | 0.887219 | 1(Win) | true |
| Jsonifier (two-stage) | 1993.68 | 0.0502935 | 604.731ms | 11812 | 40 | 323.013 | 5650.25 | 0.11167 | 1.23577 | 2(Loss) | true |
| Glaze | 1900.62 | 0.0809986 | 641.651ms | 11812 | 30 | 691.403 | 5926.9 | 0.0726032 | 1.29713 | 3(Loss) | true |
| simdjson (ondemand) | 1069.9 | 0.264425 | 1128.82ms | 11812 | 320 | 248037 | 10528.9 | 0.0175677 | 2.30812 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12391.6 | 0.111875 | 94.1199ms | 11812 | 30 | 31.0299 | 909.067 | 0.0366811 | 0.19406 | 1(Win) | true |
| Glaze | 3130.31 | 0.1225 | 364.263ms | 11812 | 4890 | 95028.1 | 3598.62 | 0.157437 | 0.78532 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12686.1 | 0.0483942 | 91.8791ms | 11812 | 160 | 29.5458 | 887.962 | 0.0590892 | 0.189238 | 1(Win) | true |
| Glaze | 3385.47 | 0.132055 | 337.072ms | 11812 | 80 | 1544.57 | 3327.4 | 0.0330479 | 0.725705 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3628.94 | 0.180943 | 675.508ms | 25388 | 1280 | 186549 | 6671.9 | 0.000362998 | 0.679554 | 1(Win) | true |
| Jsonifier | 3209.49 | 0.0347637 | 760.515ms | 25388 | 40 | 275.105 | 7543.85 | 0.0470361 | 0.768939 | 2(Loss) | true |
| Glaze | 2479.12 | 0.0937161 | 986.227ms | 25388 | 4890 | 409637 | 9766.32 | 0.1239 | 0.996058 | 3(Loss) | true |
| simdjson (ondemand) | 2065.53 | 0.133688 | 1180.78ms | 25388 | 1280 | 314333 | 11721.9 | 0.0115449 | 1.19592 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3847.98 | 0.235653 | 676.463ms | 25388 | 1280 | 281415 | 6292.1 | 0.440353 | 0.640718 | 1(Win) | true |
| Jsonifier | 3391.92 | 0.0373825 | 761.445ms | 25388 | 30 | 213.61 | 7138.1 | 0.134775 | 0.727212 | 2(Loss) | true |
| Glaze | 2675.78 | 0.0402804 | 996.105ms | 25388 | 30 | 398.533 | 9048.53 | 0.0877523 | 0.922778 | 3(Loss) | true |
| simdjson (ondemand) | 2152.53 | 0.0886818 | 1170.28ms | 25388 | 4890 | 486562 | 11248.1 | 0.0211899 | 1.14744 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17530.6 | 0.0818001 | 170.887ms | 31235 | 30 | 57.9586 | 1699.2 | 0.160602 | 0.138899 | 1(Win) | true |
| Glaze | 5449.86 | 0.0565919 | 556.687ms | 31235 | 30 | 287.04 | 5465.83 | 0.166212 | 0.452211 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18527.2 | 0.0546693 | 163.864ms | 31235 | 80 | 61.8076 | 1607.8 | 0.0854475 | 0.131371 | 1(Win) | true |
| Glaze | 5849.94 | 0.0499295 | 518.414ms | 31235 | 80 | 517.113 | 5092.02 | 0.321526 | 0.421044 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2703.81 | 0.0567568 | 3866.1ms | 108313 | 4890 | 2.29908e+06 | 38203.6 | 0.222114 | 0.915058 | 1(Win) | true |
| Jsonifier (two-stage) | 2357.18 | 0.347261 | 4385.59ms | 108313 | 160 | 3.70517e+06 | 43821.5 | 0.0651217 | 1.04969 | 2(Loss) | true |
| Glaze | 1721.67 | 0.398871 | 6007.42ms | 108313 | 80 | 4.58161e+06 | 59997.2 | 0.0163784 | 1.43741 | 3(Loss) | true |
| simdjson (ondemand) | 654.021 | 0.230755 | 8216.58ms | 108313 | 30 | 3.98477e+06 | 157939 | 0.0587645 | 3.78496 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3096.9 | 0.0874494 | 3529.19ms | 108313 | 2560 | 2.17802e+06 | 33354.5 | 0.0358835 | 0.798833 | 1(Win) | true |
| Jsonifier (two-stage) | 2651.25 | 0.111061 | 4143.37ms | 108313 | 1280 | 2.39658e+06 | 38960.9 | 0.392299 | 0.933194 | 2(Loss) | true |
| Glaze | 1865.75 | 0.06902 | 5817.64ms | 108313 | 1280 | 1.86901e+06 | 55363.9 | 0.0515963 | 1.32637 | 3(Loss) | true |
| simdjson (ondemand) | 664.381 | 0.0705031 | 8201.81ms | 108313 | 640 | 7.68996e+06 | 155476 | 0.0700992 | 3.72585 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17200.8 | 0.358252 | 613.8ms | 108313 | 320 | 148112 | 6005.26 | 0.0723327 | 0.14329 | 1(Win) | true |
| Glaze | 3897.13 | 0.11144 | 2694.54ms | 108313 | 4890 | 4.26643e+06 | 26505.5 | 0.343564 | 0.634679 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17470.4 | 0.0340836 | 614.338ms | 108313 | 30 | 121.834 | 5912.6 | 0.0501502 | 0.141082 | 1(Win) | true |
| Glaze | 4108.3 | 0.376608 | 2603.24ms | 108313 | 80 | 717308 | 25143.1 | 0.0794587 | 0.601999 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3651.7 | 0.221425 | 5058.47ms | 183677 | 320 | 3.61012e+06 | 47968.9 | 0.0341549 | 0.677603 | 1(Win) | true |
| Jsonifier | 2319.6 | 0.0656569 | 7729.21ms | 183677 | 2560 | 6.29337e+06 | 75516.4 | 0.111589 | 1.06694 | 2(Loss) | true |
| Glaze | 2256.31 | 0.221264 | 7964.64ms | 183677 | 80 | 2.3606e+06 | 77634.7 | 0.242359 | 1.09693 | 3(Loss) | true |
| simdjson (ondemand) | 1078.41 | 0.0554893 | 8400.49ms | 183677 | 640 | 5.19922e+06 | 162431 | 0.0931336 | 2.29544 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4037.87 | 0.0972467 | 4524.19ms | 183677 | 2560 | 4.5561e+06 | 43381.3 | 0.169344 | 0.612766 | 1(Win) | true |
| Jsonifier | 2490.07 | 0.152962 | 7302.86ms | 183677 | 160 | 1.85257e+06 | 70346.7 | 0.00122606 | 0.993892 | 2(Loss) | true |
| Glaze | 2358.99 | 0.172612 | 7692.98ms | 183677 | 320 | 5.25713e+06 | 74255.6 | 0.622236 | 1.04916 | 3(Loss) | true |
| simdjson (ondemand) | 1111.32 | 0.23243 | 8265.37ms | 183677 | 30 | 4.02661e+06 | 157622 | 0.0211098 | 2.22748 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21391.1 | 0.198185 | 959.015ms | 213963 | 1280 | 457472 | 9539.07 | 0.180382 | 0.115425 | 1(Win) | true |
| Glaze | 3966.28 | 0.110006 | 5163.03ms | 213963 | 640 | 2.04986e+06 | 51446.4 | 0.0649435 | 0.623911 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21598.7 | 0.136498 | 950.366ms | 213963 | 2560 | 425711 | 9447.38 | 0.00591717 | 0.11432 | 1(Win) | true |
| Glaze | 4242.61 | 0.131317 | 4824.42ms | 213963 | 640 | 2.55288e+06 | 48095.7 | 0.00846367 | 0.583249 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 830.256 | 1.06089 | 6631.17ms | 1834197 | 160 | 7.99335e+10 | 2.10685e+06 | 1.48802 | 2.98193 | 1(Win) | true |
| Jsonifier (two-stage) | 788.081 | 0.108375 | 6976.19ms | 1834197 | 30 | 1.73591e+08 | 2.2196e+06 | 0.226639 | 3.14152 | 2(Loss) | true |
| Glaze | 678.954 | 0.0617451 | 8040.95ms | 1834197 | 80 | 2.02444e+08 | 2.57635e+06 | 0.0865522 | 3.64646 | 3(Loss) | true |
| simdjson (ondemand) | 629.91 | 0.254963 | 8855.73ms | 1834197 | 40 | 2.00516e+09 | 2.77695e+06 | 0.0671845 | 3.93037 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 965.109 | 0.155844 | 6489.49ms | 1834197 | 30 | 2.39355e+08 | 1.81246e+06 | 0.00325902 | 2.56525 | 1(Win) | true |
| Jsonifier (two-stage) | 855.026 | 0.0955401 | 7261.71ms | 1834197 | 40 | 1.52815e+08 | 2.04582e+06 | 0.186694 | 2.89555 | 2(Loss) | true |
| Glaze | 759.337 | 0.104522 | 7965.71ms | 1834197 | 40 | 2.31898e+08 | 2.30362e+06 | 0.168631 | 3.26045 | 3(Loss) | true |
| simdjson (ondemand) | 674.821 | 0.160653 | 8833.3ms | 1834197 | 40 | 6.93669e+08 | 2.59213e+06 | 0.164228 | 3.66879 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1283.73 | 0.0957716 | 9201.85ms | 1922245 | 320 | 5.98541e+08 | 1.42802e+06 | 1.90831 | 1.92856 | 1(Win) | true |
| Glaze | 631.373 | 0.0943849 | 8562.06ms | 1833577 | 80 | 5.46666e+08 | 2.76958e+06 | 0.2732 | 3.92126 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1241.43 | 0.0974429 | 9170.76ms | 1922245 | 30 | 6.21143e+07 | 1.47667e+06 | 0.0328829 | 1.99427 | 1(Win) | true |
| Glaze | 662.556 | 0.106732 | 8264.85ms | 1833577 | 160 | 1.26958e+09 | 2.63923e+06 | 0.265653 | 3.73671 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2715.55 | 0.0832361 | 8073.33ms | 7351818 | 160 | 7.38955e+08 | 2.58189e+06 | 0.379842 | 0.911695 | 1(Win) | true |
| Jsonifier | 2495.61 | 0.305789 | 8733.84ms | 7351818 | 30 | 2.21411e+09 | 2.80943e+06 | 0.323392 | 0.992043 | 2(Loss) | true |
| simdjson (ondemand) | 2281.46 | 0.0544743 | 9712.44ms | 7351818 | 80 | 2.24202e+08 | 3.07314e+06 | 0.0125742 | 1.08518 | 3(Loss) | true |
| Glaze | 2085.68 | 0.091223 | 5016.85ms | 7351818 | 30 | 2.82113e+08 | 3.3616e+06 | 1.42211 | 1.18704 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2956.16 | 0.276371 | 8182.48ms | 7351818 | 40 | 1.71861e+09 | 2.37174e+06 | 0.805897 | 0.837495 | 1(Win) | true |
| Jsonifier | 2759.81 | 0.101436 | 8771.22ms | 7351818 | 160 | 1.06251e+09 | 2.54048e+06 | 0.949657 | 0.897075 | 2(Loss) | true |
| simdjson (ondemand) | 2532.73 | 0.0531479 | 9429.72ms | 7351818 | 80 | 1.7317e+08 | 2.76825e+06 | 0.287505 | 0.97751 | 3(Loss) | true |
| Glaze | 2298.31 | 0.186234 | 5016.02ms | 7351818 | 30 | 9.68305e+08 | 3.05061e+06 | 1.51765 | 1.07721 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5095.95 | 0.371993 | 5674.63ms | 10018896 | 30 | 1.45942e+09 | 1.87497e+06 | 0.18305 | 0.48582 | 1(Win) | true |
| Glaze | 3700.68 | 0.232324 | 7947.77ms | 9930228 | 160 | 5.65542e+09 | 2.55904e+06 | 0.178504 | 0.669001 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5326.56 | 0.0744277 | 5574.21ms | 10018896 | 160 | 2.8519e+08 | 1.7938e+06 | 0.446808 | 0.464793 | 1(Win) | true |
| Glaze | 3858.82 | 0.039091 | 7726.97ms | 9930228 | 30 | 2.7611e+07 | 2.45417e+06 | 0.17409 | 0.641585 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 847.508 | 0.144554 | 6572.07ms | 1834197 | 40 | 3.56059e+08 | 2.06396e+06 | 4.60301 | 2.92123 | -(Win) | false |
| Jsonifier (two-stage) | 789.709 | 0.0534151 | 6888.47ms | 1834197 | 80 | 1.11989e+08 | 2.21503e+06 | 0.146347 | 3.13504 | 2(Loss) | true |
| Glaze | 677.441 | 0.501139 | 8208.6ms | 1834197 | 160 | 2.67908e+10 | 2.58211e+06 | 0.416448 | 3.65461 | 3(Loss) | true |
| simdjson (ondemand) | 626.239 | 0.0982681 | 8773.81ms | 1834197 | 80 | 6.02735e+08 | 2.79322e+06 | 0.220126 | 3.95341 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 970.712 | 0.213375 | 6417.21ms | 1834197 | 40 | 5.9137e+08 | 1.802e+06 | 0.0385095 | 2.55045 | 1(Win) | true |
| Jsonifier (two-stage) | 880.439 | 0.0483667 | 6878.49ms | 1834197 | 80 | 7.38716e+07 | 1.98677e+06 | 0.0259576 | 2.81197 | 2(Loss) | true |
| Glaze | 749.792 | 0.420646 | 8075.21ms | 1834197 | 80 | 7.7043e+09 | 2.33295e+06 | 0.727135 | 3.30196 | 3(Loss) | true |
| simdjson (ondemand) | 695.556 | 0.0739831 | 8497.26ms | 1834197 | 80 | 2.76939e+08 | 2.51486e+06 | 0.0401139 | 3.55942 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1269.51 | 0.14071 | 9185.79ms | 1922245 | 40 | 1.6514e+08 | 1.44401e+06 | 2.4611 | 1.95012 | 1(Win) | true |
| Glaze | 658.443 | 0.0468206 | 8483.46ms | 1833577 | 40 | 6.18438e+07 | 2.65571e+06 | 0.0384131 | 3.76005 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1240.1 | 0.0852343 | 9361.82ms | 1922245 | 160 | 2.54012e+08 | 1.47827e+06 | 0.026778 | 1.99639 | 1(Win) | true |
| Glaze | 639.395 | 0.0736087 | 8291.35ms | 1833577 | 40 | 1.62098e+08 | 2.73483e+06 | 0.0716176 | 3.87208 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2640.97 | 0.11089 | 8302.72ms | 7351818 | 30 | 2.59998e+08 | 2.65479e+06 | 0.236913 | 0.937444 | 1(Win) | true |
| Jsonifier | 2454.97 | 0.198645 | 8857.72ms | 7351818 | 160 | 5.14956e+09 | 2.85593e+06 | 0.056928 | 1.00847 | 2(Loss) | true |
| simdjson (ondemand) | 2171.17 | 0.0782711 | 9962.11ms | 7351818 | 40 | 2.55544e+08 | 3.22925e+06 | 0.0616785 | 1.1403 | 3(Loss) | true |
| Glaze | 2073.62 | 0.0617996 | 5122.36ms | 7351818 | 30 | 1.30985e+08 | 3.38115e+06 | 0.495132 | 1.19394 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2872.81 | 0.107451 | 8383.7ms | 7351818 | 40 | 2.75078e+08 | 2.44055e+06 | 0.452555 | 0.861731 | 1(Win) | true |
| Jsonifier | 2605.52 | 0.369264 | 8919.45ms | 7351818 | 30 | 2.96209e+09 | 2.69092e+06 | 1.05323 | 0.950201 | 2(Loss) | true |
| simdjson (ondemand) | 2384.1 | 0.115974 | 9669.73ms | 7351818 | 30 | 3.48969e+08 | 2.94084e+06 | 0.488713 | 1.03845 | 3(Loss) | true |
| Glaze | 2227.11 | 0.0565843 | 5108.76ms | 7351818 | 80 | 2.53856e+08 | 3.14813e+06 | 0.0916824 | 1.11166 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5148.38 | 0.0694938 | 5776.87ms | 10018896 | 160 | 2.6614e+08 | 1.85588e+06 | 0.4498 | 0.480875 | 1(Win) | true |
| Glaze | 3239.6 | 0.142982 | 9160.57ms | 9930228 | 160 | 2.79525e+09 | 2.92326e+06 | 1.07525 | 0.764178 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5341.24 | 0.0911802 | 5748.86ms | 10018896 | 30 | 7.98139e+07 | 1.78887e+06 | 0.0836087 | 0.463511 | 1(Win) | true |
| Glaze | 3711.02 | 0.0903281 | 7886.4ms | 9930228 | 160 | 8.50153e+08 | 2.55191e+06 | 1.1644 | 0.667137 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1231.73 | 0.177473 | 9205.95ms | 461466 | 80 | 3.21663e+07 | 357291 | 0.145881 | 2.00978 | 1(Win) | true |
| Jsonifier (two-stage) | 1180.07 | 0.214567 | 9712.19ms | 461466 | 80 | 5.12252e+07 | 372935 | 0.124762 | 2.09777 | 2(Loss) | true |
| Glaze | 1057.24 | 0.227921 | 5335.9ms | 461466 | 40 | 3.60044e+07 | 416260 | 0.00493458 | 2.3415 | 3(Loss) | true |
| simdjson (ondemand) | 804.301 | 0.151947 | 7275.19ms | 461466 | 80 | 5.52987e+07 | 547169 | 0.142336 | 3.07798 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1729.92 | 0.0615664 | 8550.88ms | 461466 | 1280 | 3.13996e+07 | 254398 | 0.0656549 | 1.431 | 1(Win) | true |
| Jsonifier (two-stage) | 1523.48 | 0.349916 | 9171.47ms | 461466 | 30 | 3.06519e+07 | 288871 | 1.5387 | 1.6249 | 2(Loss) | true |
| Glaze | 1303.26 | 0.173756 | 5240.75ms | 461466 | 80 | 2.75415e+07 | 337684 | 0.598099 | 1.89955 | 3(Loss) | true |
| simdjson (ondemand) | 969.906 | 0.0521243 | 6571.04ms | 461466 | 640 | 3.57998e+07 | 453743 | 0.52413 | 2.55244 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13076.6 | 0.157829 | 3379.4ms | 461466 | 640 | 1.80569e+06 | 33654.7 | 0.0951086 | 0.189126 | 1(Win) | true |
| Glaze | 2980.42 | 0.0561123 | 7543.04ms | 461466 | 1280 | 8.78724e+06 | 147660 | 0.383928 | 0.830472 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13570.9 | 0.202654 | 3386.16ms | 461466 | 640 | 2.76411e+06 | 32428.9 | 0.20583 | 0.182247 | 1(Win) | true |
| Glaze | 3201.71 | 0.205757 | 6998.04ms | 461466 | 160 | 1.27981e+07 | 137454 | 0.0224216 | 0.773115 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1768.57 | 0.0605969 | 10083.4ms | 728486 | 1280 | 7.25284e+07 | 392825 | 1.50411 | 1.39965 | 1(Win) | true |
| Jsonifier | 1532.86 | 0.152906 | 5863.87ms | 728486 | 40 | 1.92107e+07 | 453230 | 0.141875 | 1.61493 | 2(Loss) | true |
| Glaze | 1363.97 | 0.0709553 | 6466.6ms | 728486 | 160 | 2.08988e+07 | 509350 | 0.397299 | 1.81498 | 3(Loss) | true |
| simdjson (ondemand) | 1244.44 | 0.0745802 | 7161.16ms | 728486 | 320 | 5.5474e+07 | 558272 | 0.251588 | 1.98933 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2370.7 | 0.147341 | 9431.51ms | 728486 | 160 | 2.98302e+07 | 293052 | 1.19478 | 1.04421 | 1(Win) | true |
| Jsonifier | 1882.08 | 0.206409 | 5611.12ms | 728486 | 30 | 1.74159e+07 | 369133 | 0.00388312 | 1.31533 | 2(Loss) | true |
| Glaze | 1651.31 | 0.114692 | 6345.3ms | 728486 | 640 | 1.49017e+08 | 420720 | 0.11792 | 1.49916 | 3(Loss) | true |
| simdjson (ondemand) | 1507.58 | 0.20983 | 6659.21ms | 728486 | 160 | 1.49601e+08 | 460830 | 0.0697588 | 1.64211 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17461.4 | 0.128984 | 4588.82ms | 837491 | 2560 | 8.91075e+06 | 45740.5 | 0.0404975 | 0.141664 | 1(Win) | true |
| Glaze | 3575.86 | 0.069245 | 5652.77ms | 837491 | 640 | 1.53093e+07 | 223357 | 0.0493346 | 0.692236 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17487.4 | 0.105518 | 4582.34ms | 837491 | 1280 | 2.97283e+06 | 45672.4 | 0.0699006 | 0.141475 | 1(Win) | true |
| Glaze | 3996.17 | 0.0703381 | 9937.36ms | 837491 | 640 | 1.26484e+07 | 199865 | 0.043862 | 0.619452 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 10261.3 | 0.116182 | 4453.83ms | 466906 | 640 | 1.6267e+06 | 43393.6 | 0.305492 | 0.241126 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 10226.2 | 0.181404 | 4441.85ms | 466906 | 640 | 3.99304e+06 | 43542.6 | 0.00705896 | 0.241955 | 1(Tie) | true |
| simdjson (ondemand) | 7977.49 | 0.0772404 | 5597.97ms | 466906 | 2560 | 4.75835e+06 | 55816.6 | 0.0916968 | 0.310169 | 3(Loss) | true |
| Glaze | 3482.42 | 0.147846 | 6582.55ms | 466906 | 320 | 1.14358e+07 | 127864 | 0.0517909 | 0.710807 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 10490.3 | 0.0914712 | 4329.28ms | 466906 | 2560 | 3.85913e+06 | 42446.4 | 0.175038 | 0.235859 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 10483.8 | 0.0741305 | 4358.56ms | 466906 | 2560 | 2.5378e+06 | 42472.9 | 0.412157 | 0.236006 | 1(Tie) | true |
| simdjson (ondemand) | 8081.82 | 0.10592 | 5577.95ms | 466906 | 1280 | 4.35916e+06 | 55096 | 0.000747281 | 0.306187 | 3(Loss) | true |
| Glaze | 3512.52 | 0.155797 | 6616.01ms | 466906 | 160 | 6.24112e+06 | 126768 | 0.0821838 | 0.704717 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 11154.6 | 0.38417 | 5544.65ms | 631514 | 40 | 1.72094e+06 | 53992 | 0.354088 | 0.221796 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 11079.6 | 0.314526 | 5434.68ms | 631514 | 1280 | 3.74144e+07 | 54357.3 | 0.0443899 | 0.223297 | 1(Tie) | true |
| simdjson (ondemand) | 9261.29 | 0.102502 | 6635.2ms | 631514 | 640 | 2.84362e+06 | 65029.7 | 0.250162 | 0.267159 | 3(Loss) | true |
| Glaze | 4183.89 | 0.0657344 | 7354.73ms | 631514 | 2560 | 2.29208e+07 | 143947 | 0.0469545 | 0.591621 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11399.3 | 0.0755344 | 5451.06ms | 631514 | 2560 | 4.07701e+06 | 52833.1 | 0.328818 | 0.21707 | 1(Win) | true |
| Jsonifier (two-stage) | 11323 | 0.0581425 | 5409.65ms | 631514 | 4890 | 4.67673e+06 | 53189.2 | 0.37909 | 0.218537 | 2(Loss) | true |
| simdjson (ondemand) | 9388.37 | 0.0438292 | 6481.08ms | 631514 | 4890 | 3.86564e+06 | 64149.4 | 0.00122056 | 0.263579 | 3(Loss) | true |
| Glaze | 4221.74 | 0.15832 | 7412.01ms | 631514 | 80 | 4.08079e+06 | 142656 | 0.0676294 | 0.586339 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1798.51 | 0.0688126 | 6448.48ms | 466906 | 640 | 1.8576e+07 | 247581 | 0.0616085 | 1.37631 | 1(Win) | true |
| Jsonifier | 1767.25 | 0.131597 | 6533.46ms | 466906 | 320 | 3.51809e+07 | 251960 | 0.139993 | 1.40067 | 2(Loss) | true |
| Glaze | 1731.61 | 0.0697316 | 6618.56ms | 466906 | 640 | 2.05777e+07 | 257145 | 0.0466469 | 1.42953 | 3(Loss) | true |
| simdjson (ondemand) | 935.01 | 0.0852213 | 6126.26ms | 466906 | 160 | 2.63537e+07 | 476226 | 0.149789 | 2.64765 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2363.84 | 0.0825528 | 5640.52ms | 466906 | 640 | 1.54762e+07 | 188370 | 0.135389 | 1.04716 | 1(Win) | true |
| Jsonifier | 2171.53 | 0.220613 | 6030.61ms | 466906 | 80 | 1.63712e+07 | 205052 | 0.115024 | 1.13989 | 2(Loss) | true |
| Glaze | 2071.48 | 0.250395 | 6238.28ms | 466906 | 30 | 8.69102e+06 | 214956 | 0.220581 | 1.19504 | 3(Loss) | true |
| simdjson (ondemand) | 1036.57 | 0.205376 | 5908.17ms | 466906 | 30 | 2.335e+07 | 429569 | 0.0253213 | 2.38827 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17059 | 0.188693 | 2704.75ms | 475954 | 1280 | 3.22663e+06 | 26608 | 0.0597706 | 0.144948 | 1(Win) | true |
| Glaze | 5785.13 | 0.27568 | 7844.23ms | 475954 | 160 | 7.48575e+06 | 78460.6 | 0.044716 | 0.427741 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17131.8 | 0.077531 | 2693.77ms | 475954 | 4890 | 2.0634e+06 | 26494.9 | 0.0799587 | 0.144317 | 1(Win) | true |
| Glaze | 6489.94 | 0.0738906 | 7021.58ms | 475954 | 2560 | 6.83703e+06 | 69939.8 | 0.164329 | 0.381319 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2337.27 | 0.121207 | 6638.18ms | 631514 | 160 | 1.56071e+07 | 257676 | 0.125937 | 1.05907 | 1(Win) | true |
| Glaze | 1918.54 | 0.0707415 | 8066.24ms | 631514 | 640 | 3.1561e+07 | 313915 | 0.000304124 | 1.29026 | 2(Loss) | true |
| Jsonifier | 1681.49 | 0.0579756 | 9170.29ms | 631514 | 640 | 2.75962e+07 | 358170 | 0.0565961 | 1.47218 | 3(Loss) | true |
| simdjson (ondemand) | 1234.87 | 0.0425989 | 6267.8ms | 631514 | 640 | 2.76247e+07 | 487709 | 0.158652 | 2.00471 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3030.54 | 0.119701 | 5785.25ms | 631514 | 320 | 1.8108e+07 | 198730 | 0.0206447 | 0.816797 | 1(Win) | true |
| Glaze | 2262.92 | 0.253833 | 7606.38ms | 631514 | 40 | 1.8255e+07 | 266142 | 0.133697 | 1.09396 | 2(Loss) | true |
| Jsonifier | 1937.28 | 0.188816 | 8801.67ms | 631514 | 30 | 1.03367e+07 | 310879 | 0.185227 | 1.27784 | 3(Loss) | true |
| simdjson (ondemand) | 1370.09 | 0.139071 | 5969.45ms | 631514 | 80 | 2.98972e+07 | 439575 | 0.0565823 | 1.8069 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16457.1 | 0.108643 | 4217.32ms | 716365 | 2560 | 5.20727e+06 | 41512.8 | 0.0390977 | 0.150343 | 1(Win) | true |
| Glaze | 4761.09 | 0.0666686 | 7363.06ms | 716365 | 2560 | 2.34282e+07 | 143492 | 0.191053 | 0.51987 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16572 | 0.0684506 | 4128.36ms | 716365 | 4890 | 3.89389e+06 | 41225 | 0.345047 | 0.149292 | 1(Win) | true |
| Glaze | 5589.81 | 0.0794231 | 6269.07ms | 716365 | 640 | 6.03042e+06 | 122219 | 0.185262 | 0.442806 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2641.62 | 0.066313 | 98.1343ms | 2632 | 320 | 127.051 | 950.2 | 0.0315623 | 0.911408 | 1(Win) | true |
| Jsonifier (two-stage) | 2582.82 | 0.134849 | 101.527ms | 2632 | 30 | 51.523 | 971.833 | 0 | 0.93384 | 2(Loss) | true |
| Glaze | 2115.19 | 0.0277465 | 123.01ms | 2632 | 640 | 69.3858 | 1186.69 | 0.0131652 | 1.14455 | 3(Loss) | true |
| simdjson (ondemand) | 1549.33 | 0.131433 | 165.775ms | 2632 | 30 | 136.024 | 1620.1 | 0.283129 | 1.57196 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3002.6 | 0.122272 | 92.4263ms | 2632 | 30 | 31.3437 | 835.967 | 0.12776 | 0.799468 | 1(Win) | true |
| Jsonifier (two-stage) | 2981.88 | 0.103625 | 94.618ms | 2632 | 40 | 30.4353 | 841.775 | 0.373797 | 0.805528 | 2(Loss) | true |
| Glaze | 2357.15 | 0.227318 | 112.321ms | 2632 | 640 | 3750.12 | 1064.88 | 0.71732 | 1.02349 | 3(Loss) | true |
| simdjson (ondemand) | 1723.96 | 0.0933903 | 155.254ms | 2632 | 160 | 295.83 | 1455.99 | 0.06572 | 1.40973 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10850 | 0.268095 | 25.6553ms | 2632 | 160 | 61.5478 | 231.344 | 0.159649 | 0.202997 | 1(Win) | true |
| Glaze | 3976.96 | 0.0337609 | 66.0961ms | 2632 | 1280 | 58.1178 | 631.154 | 0.0162127 | 0.597836 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11526.9 | 0.112208 | 24.1607ms | 2632 | 1280 | 76.4186 | 217.757 | 0.00897009 | 0.189713 | 1(Win) | true |
| Glaze | 4366.48 | 0.182295 | 60.271ms | 2632 | 40 | 43.9256 | 574.85 | 0.0493125 | 0.541765 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3202.01 | 0.062124 | 103.919ms | 3370 | 160 | 62.2088 | 1003.71 | 0.106367 | 0.75275 | 1(Win) | true |
| Glaze | 2318.97 | 0.251658 | 140.714ms | 3370 | 4890 | 59484 | 1385.91 | 0.0672647 | 1.04756 | 2(Loss) | true |
| Jsonifier | 2266.65 | 0.088088 | 144.662ms | 3370 | 40 | 62.4 | 1417.9 | 0.00470201 | 1.072 | 3(Loss) | true |
| simdjson (ondemand) | 1908.14 | 0.161414 | 172.213ms | 3370 | 40 | 295.651 | 1684.3 | 0.0751478 | 1.27684 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3444.05 | 0.0556247 | 99.6385ms | 3370 | 160 | 43.1097 | 933.169 | 0.0837903 | 0.697962 | 1(Win) | true |
| Glaze | 2741.05 | 0.0922348 | 125.447ms | 3370 | 30 | 35.0862 | 1172.5 | 0.031282 | 0.8836 | 2(Loss) | true |
| Jsonifier | 2562.24 | 0.0849394 | 135.547ms | 3370 | 40 | 45.4045 | 1254.33 | 0.080324 | 0.94638 | 3(Loss) | true |
| simdjson (ondemand) | 2179.52 | 0.094565 | 158.024ms | 3370 | 160 | 311.113 | 1474.58 | 0.146442 | 1.11581 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12412.4 | 0.0785318 | 30.5415ms | 3643 | 640 | 30.9227 | 279.9 | 0.0525016 | 0.181739 | 1(Win) | true |
| Glaze | 4474.22 | 0.256594 | 81.0015ms | 3682 | 4890 | 19830.6 | 784.813 | 0.0513675 | 0.534756 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14101.2 | 0.259332 | 27.0348ms | 3643 | 320 | 130.637 | 246.378 | 0.483036 | 0.15783 | 1(Win) | true |
| Glaze | 4770.23 | 0.0976919 | 76.5647ms | 3682 | 160 | 82.742 | 736.112 | 0.0203732 | 0.500665 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 909.371 | 0.0488033 | 486.781ms | 4630 | 30 | 168.461 | 4855.57 | 0.0254069 | 2.70816 | 1(Win) | true |
| Jsonifier (two-stage) | 853.98 | 0.0402363 | 520.327ms | 4630 | 80 | 346.253 | 5170.51 | 0.11642 | 2.88448 | 2(Loss) | true |
| Glaze | 761.79 | 0.215478 | 583.512ms | 4630 | 2560 | 399334 | 5796.23 | 0.0043197 | 3.2355 | 3(Loss) | true |
| simdjson (ondemand) | 739.051 | 0.0868663 | 612.852ms | 4630 | 30 | 808.047 | 5974.57 | 0.429421 | 3.33433 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1115.23 | 0.0611632 | 475.446ms | 4630 | 30 | 175.926 | 3959.27 | 0.0260923 | 2.20611 | 1(Win) | true |
| Jsonifier (two-stage) | 1006.62 | 0.180698 | 516.192ms | 4630 | 4890 | 307218 | 4386.48 | 0.261872 | 2.44456 | 2(Loss) | true |
| Glaze | 907.039 | 0.118814 | 573.024ms | 4630 | 40 | 1338.15 | 4868.05 | 0.178056 | 2.71565 | 3(Loss) | true |
| simdjson (ondemand) | 839.406 | 0.0506209 | 613.205ms | 4630 | 160 | 1134.48 | 5260.28 | 0.0041587 | 2.93515 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2007.11 | 0.0561152 | 223.745ms | 4630 | 30 | 45.7195 | 2199.93 | 0.028797 | 1.21892 | 1(Win) | true |
| Glaze | 1025.14 | 0.0560708 | 437.626ms | 4630 | 40 | 233.307 | 4307.23 | 0.016835 | 2.40144 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2023.26 | 0.0137615 | 227.233ms | 4630 | 320 | 28.8628 | 2182.38 | 0.0553848 | 1.20894 | 1(Win) | true |
| Glaze | 999.981 | 0.358059 | 444.895ms | 4630 | 320 | 79990.5 | 4415.6 | 0.295446 | 2.46087 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1972.15 | 0.134049 | 566.616ms | 11579 | 4890 | 275485 | 5599.27 | 0.169096 | 1.2495 | 1(Win) | true |
| Jsonifier | 1828.28 | 0.38229 | 610.368ms | 11579 | 320 | 170605 | 6039.88 | 0.145081 | 1.34838 | 2(Loss) | true |
| simdjson (ondemand) | 1773.16 | 0.29056 | 625.241ms | 11579 | 1280 | 419109 | 6227.63 | 0.0442513 | 1.38986 | 3(Loss) | true |
| Glaze | 1644.16 | 0.55894 | 671.779ms | 11579 | 320 | 450955 | 6716.24 | 0.0128869 | 1.49991 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2357.87 | 0.0530087 | 565.776ms | 11579 | 40 | 246.523 | 4683.3 | 0.141839 | 1.04379 | 1(Win) | true |
| Jsonifier | 2152.4 | 0.0478407 | 601.476ms | 11579 | 30 | 180.723 | 5130.37 | 0.0455015 | 1.14434 | 2(Loss) | true |
| simdjson (ondemand) | 2007.87 | 0.138842 | 633.356ms | 11579 | 30 | 1749.2 | 5499.67 | 0.0139422 | 1.22726 | 3(Loss) | true |
| Glaze | 1881.83 | 0.0807217 | 666.81ms | 11579 | 30 | 673.103 | 5868 | 0.0926784 | 1.30953 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5738.59 | 0.0585955 | 250.286ms | 14795 | 40 | 83.025 | 2458.72 | 0.01322 | 0.427111 | 1(Win) | true |
| Glaze | 3381.88 | 0.0434813 | 424.011ms | 14795 | 80 | 263.275 | 4172.12 | 0.00359516 | 0.727773 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5916.72 | 0.0326647 | 242.378ms | 14795 | 80 | 48.5418 | 2384.7 | 0.00419358 | 0.414042 | 1(Win) | true |
| Glaze | 3709.44 | 0.0420936 | 386.342ms | 14795 | 30 | 76.9069 | 3803.7 | 0.0429591 | 0.662636 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1862.87 | 0.0412381 | 173.978ms | 3223 | 320 | 148.15 | 1649.97 | 0.25428 | 1.3079 | 1(Win) | true |
| Jsonifier (two-stage) | 1629.64 | 0.0801859 | 191.165ms | 3223 | 80 | 182.987 | 1886.11 | 0.121428 | 1.49803 | 2(Loss) | true |
| Glaze | 1367.22 | 0.0729722 | 226.28ms | 3223 | 80 | 215.301 | 2248.12 | 0.0990694 | 1.79015 | 3(Loss) | true |
| simdjson (ondemand) | 1082.58 | 0.112305 | 289.7ms | 3223 | 30 | 305.013 | 2839.23 | 0.213217 | 2.26678 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2240.97 | 0.0837851 | 189.301ms | 3223 | 160 | 211.3 | 1371.59 | 0.844915 | 1.08402 | 1(Win) | true |
| Jsonifier (two-stage) | 1950.15 | 0.196161 | 175.223ms | 3223 | 4890 | 46743 | 1576.13 | 0.0406704 | 1.24858 | 2(Loss) | true |
| Glaze | 1574.59 | 0.0887636 | 211.55ms | 3223 | 80 | 240.186 | 1952.06 | 0.021136 | 1.55116 | 3(Loss) | true |
| simdjson (ondemand) | 1240.38 | 0.0578815 | 274.984ms | 3223 | 80 | 164.582 | 2478.03 | 0.223468 | 1.97477 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10200 | 0.0359266 | 32.6132ms | 3223 | 2560 | 30.0049 | 301.343 | 0.128814 | 0.222114 | 1(Win) | true |
| Glaze | 2915.34 | 0.525017 | 109.891ms | 3223 | 1280 | 39219.2 | 1054.32 | 0.319533 | 0.828763 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11425.3 | 0.187959 | 29.1544ms | 3223 | 80 | 20.4551 | 269.025 | 0.055788 | 0.19668 | 1(Win) | true |
| Glaze | 3155.9 | 0.557847 | 99.9814ms | 3223 | 40 | 1180.77 | 973.95 | 0.257732 | 0.764303 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2758.46 | 0.100295 | 206.579ms | 5839 | 30 | 122.976 | 2018.7 | 0.0330137 | 0.885951 | 1(Win) | true |
| Jsonifier | 2001.21 | 0.0650926 | 281.818ms | 5839 | 80 | 262.45 | 2782.57 | 0.113333 | 1.22424 | 2(Loss) | true |
| Glaze | 1833.1 | 0.221401 | 308.192ms | 5839 | 2560 | 115799 | 3037.76 | 0.119306 | 1.33881 | 3(Loss) | true |
| simdjson (ondemand) | 1817.83 | 0.137443 | 303.599ms | 5839 | 30 | 531.789 | 3063.27 | 0.0642429 | 1.34905 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3245.81 | 0.0881381 | 192.169ms | 5839 | 30 | 68.5931 | 1715.6 | 0.0952955 | 0.751618 | 1(Win) | true |
| Jsonifier | 2280.29 | 0.075023 | 266.658ms | 5839 | 80 | 268.519 | 2442.01 | 0.0220057 | 1.07344 | 2(Loss) | true |
| Glaze | 2095.19 | 0.103208 | 287.029ms | 5839 | 40 | 300.962 | 2657.75 | 0.321915 | 1.1706 | 3(Loss) | true |
| simdjson (ondemand) | 2080.94 | 0.0681267 | 282.48ms | 5839 | 160 | 531.76 | 2675.96 | 0.0729241 | 1.17734 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12235.4 | 0.0649828 | 57.0527ms | 6938 | 320 | 39.5166 | 540.775 | 0.0300585 | 0.19282 | 1(Win) | true |
| Glaze | 3897.92 | 0.198452 | 173.423ms | 6960 | 40 | 456.797 | 1702.85 | 0.0754207 | 0.625126 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12695.2 | 0.120969 | 54.7481ms | 6938 | 80 | 31.7998 | 521.188 | 0.2989 | 0.184967 | 1(Win) | true |
| Glaze | 4289.69 | 0.228929 | 155.647ms | 6960 | 30 | 376.437 | 1547.33 | 0.43054 | 0.566571 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2014.28 | 0.31885 | 235.1ms | 4857 | 2560 | 137629 | 2299.58 | 0.037861 | 1.21352 | 1(Win) | true |
| Jsonifier (two-stage) | 1789.37 | 0.0873134 | 264.886ms | 4857 | 40 | 204.343 | 2588.62 | 0.0267266 | 1.36956 | 2(Loss) | true |
| Glaze | 1622.6 | 0.0927939 | 289.848ms | 4857 | 80 | 561.361 | 2854.68 | 0.381247 | 1.51111 | 3(Loss) | true |
| simdjson (ondemand) | 823.596 | 0.0604667 | 573.342ms | 4857 | 80 | 925.19 | 5624.11 | 0.0899332 | 2.99244 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2656.7 | 0.169196 | 197.429ms | 4857 | 4890 | 42553.9 | 1743.51 | 0.036149 | 0.918242 | 1(Win) | true |
| Jsonifier (two-stage) | 2232.44 | 0.0754569 | 231.261ms | 4857 | 80 | 196.095 | 2074.86 | 0.0475709 | 1.09482 | 2(Loss) | true |
| Glaze | 2212.98 | 0.120983 | 231.143ms | 4857 | 40 | 256.503 | 2093.1 | 0.10841 | 1.10538 | 3(Loss) | true |
| simdjson (ondemand) | 908.308 | 0.135867 | 539.263ms | 4857 | 2560 | 122897 | 5099.59 | 0.247103 | 2.71152 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13044 | 0.142292 | 38.0026ms | 4857 | 160 | 40.8503 | 355.106 | 0.0474984 | 0.175981 | 1(Win) | true |
| Glaze | 3818.92 | 0.0841683 | 124.167ms | 4857 | 160 | 166.752 | 1212.91 | 0.196712 | 0.634352 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14532.9 | 0.185447 | 34.7081ms | 4857 | 80 | 27.9487 | 318.725 | 0.149254 | 0.156673 | 1(Win) | true |
| Glaze | 4278.45 | 0.122049 | 111.851ms | 4857 | 30 | 52.3782 | 1082.63 | 0.151095 | 0.565068 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2330.92 | 0.146379 | 281.615ms | 6701 | 40 | 644.233 | 2741.65 | 0.0796992 | 1.05206 | 1(Win) | true |
| Glaze | 1858.83 | 0.125879 | 346.508ms | 6701 | 4890 | 91583.4 | 3437.95 | 0.0140516 | 1.322 | 2(Loss) | true |
| Jsonifier | 1738.05 | 0.287219 | 374.02ms | 6701 | 1280 | 142755 | 3676.86 | 0.0120035 | 1.41269 | 3(Loss) | true |
| simdjson (ondemand) | 1112.56 | 0.276144 | 587.27ms | 6701 | 1280 | 322042 | 5744.02 | 0.194042 | 2.21504 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3010.57 | 0.0545383 | 265.037ms | 6701 | 80 | 107.22 | 2122.71 | 0.0371125 | 0.812407 | 1(Win) | true |
| Glaze | 2387.84 | 0.200899 | 288.83ms | 6701 | 2560 | 74005.4 | 2676.3 | 0.261655 | 1.02674 | 2(Loss) | true |
| Jsonifier | 2090.9 | 0.253631 | 329.198ms | 6701 | 2560 | 153836 | 3056.37 | 0.0408893 | 1.17402 | 3(Loss) | true |
| simdjson (ondemand) | 1226.84 | 0.0673142 | 547.852ms | 6701 | 80 | 983.567 | 5208.95 | 0.149997 | 2.00727 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12310.8 | 0.0490566 | 59.9343ms | 7376 | 640 | 50.2854 | 571.391 | 0.202493 | 0.192268 | 1(Win) | true |
| Glaze | 3530.04 | 0.114363 | 201.722ms | 7376 | 30 | 155.803 | 1992.7 | 0.0133804 | 0.69182 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15361.3 | 0.220797 | 49.1668ms | 7376 | 40 | 40.8917 | 457.925 | 0.122076 | 0.152342 | 1(Win) | true |
| Glaze | 3824.52 | 0.0520017 | 188.773ms | 7376 | 80 | 73.1834 | 1839.26 | 0.0401137 | 0.638435 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2528.68 | 0.099698 | 66.5849ms | 1691 | 80 | 32.3418 | 637.75 | 0 | 0.939762 | 1(Win) | true |
| Jsonifier (two-stage) | 2156.33 | 0.129991 | 77.4316ms | 1691 | 40 | 37.8045 | 747.875 | 0.233426 | 1.10547 | 2(Loss) | true |
| Glaze | 2066.66 | 0.0533721 | 80.9605ms | 1691 | 320 | 55.5042 | 780.322 | 0.0700342 | 1.15799 | 3(Loss) | true |
| simdjson (ondemand) | 1421.87 | 0.118323 | 115.872ms | 1691 | 80 | 144.078 | 1134.19 | 0.5731 | 1.70162 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3109.16 | 0.0397714 | 60.0219ms | 1691 | 640 | 27.2347 | 518.681 | 0.113741 | 0.755035 | 1(Win) | true |
| Jsonifier (two-stage) | 2836.53 | 0.18682 | 66.0371ms | 1691 | 30 | 33.8437 | 568.533 | 0.0058627 | 0.828208 | 2(Loss) | true |
| Glaze | 2376.22 | 0.168423 | 76.2869ms | 1691 | 30 | 39.1954 | 678.667 | 0.04914 | 1.00193 | 3(Loss) | true |
| simdjson (ondemand) | 1762.47 | 0.259633 | 99.3065ms | 1691 | 30 | 169.31 | 915 | 0.0619692 | 1.36929 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15513.3 | 0.107562 | 14.6579ms | 1996 | 1280 | 22.2965 | 122.703 | 0.154319 | 0.12609 | 1(Win) | true |
| Glaze | 4521.88 | 0.0727958 | 45.0016ms | 1996 | 640 | 60.1002 | 420.961 | 0.139384 | 0.512925 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17125.8 | 0.165991 | 13.5715ms | 1996 | 320 | 10.8928 | 111.15 | 0.112334 | 0.111777 | 1(Win) | true |
| Glaze | 5111.14 | 0.111967 | 40.2748ms | 1996 | 320 | 55.6437 | 372.428 | 0.098077 | 0.449385 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2639.62 | 0.0487825 | 81.2982ms | 2158 | 320 | 46.2912 | 779.669 | 0.0328557 | 0.905383 | 1(Win) | true |
| Glaze | 2182.5 | 0.0529925 | 98.4885ms | 2158 | 320 | 79.905 | 942.969 | 0.0908862 | 1.10347 | 2(Loss) | true |
| Jsonifier | 1885.99 | 0.306609 | 111.813ms | 2158 | 2560 | 28657.4 | 1091.22 | 0.0482312 | 1.2818 | 3(Loss) | true |
| simdjson (ondemand) | 1806.87 | 0.162589 | 117.316ms | 2158 | 40 | 137.179 | 1139 | 0.0643425 | 1.33996 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3501.81 | 0.055 | 67.9614ms | 2158 | 640 | 66.8688 | 587.705 | 0.100661 | 0.675275 | 1(Win) | true |
| Glaze | 2543.39 | 0.0839546 | 91.6044ms | 2158 | 160 | 73.8393 | 809.169 | 0.0363159 | 0.94205 | 2(Loss) | true |
| Jsonifier | 2228.06 | 0.117283 | 101.946ms | 2158 | 80 | 93.8884 | 923.688 | 0.00676682 | 1.08035 | 3(Loss) | true |
| simdjson (ondemand) | 2078.78 | 0.0939502 | 109.499ms | 2158 | 160 | 138.421 | 990.019 | 0.010731 | 1.15801 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15543.4 | 0.153777 | 20.0402ms | 2866 | 640 | 46.7976 | 175.845 | 0.169428 | 0.136136 | 1(Win) | true |
| Glaze | 4354.01 | 0.200751 | 66.028ms | 2866 | 40 | 63.5256 | 627.75 | 0.0292134 | 0.54542 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17946.8 | 0.0668344 | 17.7498ms | 2866 | 2560 | 26.5227 | 152.296 | 0.233437 | 0.113753 | 1(Win) | true |
| Glaze | 5182.39 | 0.052297 | 55.6389ms | 2866 | 1280 | 97.3768 | 527.407 | 0.177589 | 0.454514 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2363.46 | 0.0938513 | 177.596ms | 4390 | 40 | 110.554 | 1771.4 | 0.0414157 | 1.03169 | 1(Win) | true |
| Jsonifier (two-stage) | 1903.29 | 0.0404112 | 224.772ms | 4390 | 320 | 252.856 | 2199.68 | 0.0847414 | 1.28457 | 2(Loss) | true |
| Glaze | 1629.58 | 0.18925 | 258.916ms | 4390 | 4890 | 115600 | 2569.15 | 0.0689975 | 1.50347 | 3(Loss) | true |
| simdjson (ondemand) | 1007.08 | 0.137003 | 418.13ms | 4390 | 4890 | 158624 | 4157.19 | 0.0685211 | 2.44225 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2700.49 | 0.0555425 | 175.071ms | 4390 | 160 | 118.636 | 1550.33 | 0.0395235 | 0.900794 | 1(Win) | true |
| Jsonifier (two-stage) | 2080.56 | 0.0372105 | 223.284ms | 4390 | 320 | 179.412 | 2012.27 | 0.0651121 | 1.1743 | 2(Loss) | true |
| Glaze | 1801.61 | 0.0949335 | 251.653ms | 4390 | 30 | 146.006 | 2323.83 | 0.0732085 | 1.35822 | 3(Loss) | true |
| simdjson (ondemand) | 1071.34 | 0.161152 | 431.843ms | 4390 | 2560 | 101528 | 3907.85 | 0.355031 | 2.2946 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11918.4 | 0.210873 | 37.8346ms | 4390 | 40 | 21.9481 | 351.275 | 0.011863 | 0.193331 | 1(Win) | true |
| Glaze | 2946.98 | 0.301989 | 143.794ms | 4390 | 40 | 736.233 | 1420.65 | 0.0363816 | 0.824396 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12294.9 | 0.0655112 | 36.5327ms | 4390 | 320 | 15.9244 | 340.519 | 0.0257027 | 0.186067 | 1(Win) | true |
| Glaze | 3192.77 | 0.250194 | 133.931ms | 4390 | 4890 | 52632.9 | 1311.29 | 0.0738848 | 0.760293 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3510.31 | 0.0871857 | 257.433ms | 9378 | 30 | 148.028 | 2547.8 | 0.0797438 | 0.698457 | 1(Win) | true |
| Jsonifier | 3136.1 | 0.0450298 | 295.911ms | 9378 | 80 | 131.926 | 2851.81 | 0.0802765 | 0.782403 | 2(Loss) | true |
| Glaze | 2533.17 | 0.0635361 | 353.484ms | 9378 | 40 | 201.276 | 3530.57 | 0.0497782 | 0.96993 | 3(Loss) | true |
| simdjson (ondemand) | 2095.34 | 0.107375 | 431.256ms | 9378 | 80 | 1680.39 | 4268.3 | 0.0726812 | 1.1746 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3801.1 | 0.0541519 | 256.048ms | 9378 | 80 | 129.873 | 2352.89 | 0.207089 | 0.643923 | 1(Win) | true |
| Jsonifier | 3291.05 | 0.157005 | 292.786ms | 9378 | 4890 | 89020.7 | 2717.54 | 0.072648 | 0.744664 | 2(Loss) | true |
| Glaze | 2790.36 | 0.0755705 | 343.206ms | 9378 | 30 | 176.006 | 3205.17 | 0.021835 | 0.880245 | 3(Loss) | true |
| simdjson (ondemand) | 2227.89 | 0.168192 | 422.586ms | 9378 | 30 | 1367.62 | 4014.37 | 0.276439 | 1.1037 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18103 | 0.0332341 | 63.8226ms | 11521 | 640 | 26.0391 | 606.931 | 0.0797436 | 0.131043 | 1(Win) | true |
| Glaze | 5229.22 | 0.251217 | 212.329ms | 11521 | 30 | 835.844 | 2101.13 | 0.0491556 | 0.467737 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18570.6 | 0.127456 | 61.3879ms | 11521 | 40 | 22.7462 | 591.65 | 0.0197228 | 0.127767 | 1(Win) | true |
| Glaze | 5710.01 | 0.0625732 | 196.002ms | 11521 | 160 | 231.955 | 1924.21 | 0.108368 | 0.427629 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2533.54 | 0.0848322 | 178.955ms | 4669 | 160 | 355.66 | 1757.51 | 0.176341 | 0.962412 | 1(Win) | true |
| Jsonifier (two-stage) | 2316.46 | 0.10908 | 196.896ms | 4669 | 30 | 131.89 | 1922.2 | 0.257311 | 1.05339 | 2(Loss) | true |
| Glaze | 1633.99 | 0.0819397 | 279.72ms | 4669 | 40 | 199.433 | 2725.05 | 0.014065 | 1.50086 | 3(Loss) | true |
| simdjson (ondemand) | 616.331 | 0.0577984 | 733.354ms | 4669 | 30 | 523.085 | 7224.53 | 0.119643 | 4.00308 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2898.33 | 0.261433 | 165.217ms | 4669 | 30 | 483.941 | 1536.3 | 0.067216 | 0.840822 | 1(Win) | true |
| Jsonifier (two-stage) | 2389.37 | 0.104144 | 236.766ms | 4669 | 40 | 150.664 | 1863.55 | 0.172312 | 1.02072 | 2(Loss) | true |
| Glaze | 1843.58 | 0.0492572 | 256.133ms | 4669 | 80 | 113.228 | 2415.25 | 0.0258705 | 1.32816 | 3(Loss) | true |
| simdjson (ondemand) | 649.001 | 0.129042 | 700.548ms | 4669 | 2560 | 200658 | 6860.86 | 0.142164 | 3.80009 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15167.2 | 0.129325 | 32.2501ms | 4669 | 160 | 23.0635 | 293.575 | 0.165781 | 0.148344 | 1(Win) | true |
| Glaze | 3798.35 | 0.187003 | 120.246ms | 4669 | 80 | 384.455 | 1172.28 | 0.121411 | 0.637583 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16852.4 | 0.0372219 | 29.09ms | 4669 | 2560 | 24.7606 | 264.218 | 0.0750473 | 0.132613 | 1(Win) | true |
| Glaze | 4164.61 | 0.0630543 | 125.977ms | 4669 | 320 | 145.438 | 1069.18 | 0.0878991 | 0.579605 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3535.33 | 0.0613336 | 218.64ms | 7932 | 80 | 137.782 | 2139.7 | 0.149778 | 0.691011 | 1(Win) | true |
| Jsonifier | 2150.36 | 0.0712433 | 349.535ms | 7932 | 40 | 251.241 | 3517.8 | 0.0331757 | 1.14224 | 2(Loss) | true |
| Glaze | 2047.25 | 0.0901752 | 376.835ms | 7932 | 40 | 444.076 | 3694.97 | 0.0259294 | 1.20034 | 3(Loss) | true |
| simdjson (ondemand) | 1034.46 | 0.436791 | 746.657ms | 7932 | 160 | 163233 | 7312.57 | 0.335449 | 2.38475 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3783.53 | 0.0776461 | 207.314ms | 7932 | 30 | 72.2989 | 1999.33 | 0.233957 | 0.645945 | 1(Win) | true |
| Jsonifier | 2334.95 | 0.0835825 | 352.754ms | 7932 | 40 | 293.292 | 3239.7 | 0.0359986 | 1.05177 | 2(Loss) | true |
| Glaze | 2174.84 | 0.0366337 | 348.687ms | 7932 | 160 | 259.771 | 3478.2 | 0.0761308 | 1.1295 | 3(Loss) | true |
| simdjson (ondemand) | 1008.93 | 0.0630816 | 743.588ms | 7932 | 30 | 671.076 | 7497.6 | 0.0760822 | 2.44537 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17724.8 | 0.0518106 | 52.5756ms | 9249 | 640 | 42.5444 | 497.637 | 0.0100485 | 0.132314 | 1(Win) | true |
| Glaze | 3935.32 | 0.10046 | 225.187ms | 9249 | 40 | 202.804 | 2241.38 | 0.106074 | 0.622019 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19799.2 | 0.103321 | 47.6584ms | 9249 | 160 | 33.8994 | 445.5 | 0.0364626 | 0.117512 | 1(Win) | true |
| Glaze | 4460.79 | 0.0730551 | 202.183ms | 9249 | 80 | 166.939 | 1977.35 | 0.0303529 | 0.547696 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 893.76 | 0.0691378 | 499.329ms | 4604 | 80 | 922.892 | 4912.64 | 0.0409826 | 2.75549 | 1(Win) | true |
| Jsonifier (two-stage) | 820.327 | 0.108869 | 539.306ms | 4604 | 30 | 1018.66 | 5352.4 | 0.268512 | 3.00227 | 2(Loss) | true |
| Glaze | 643.925 | 0.583233 | 695.388ms | 4604 | 4890 | 7.73381e+06 | 6818.67 | 0.872956 | 3.82383 | 3(Loss) | true |
| simdjson (ondemand) | 541.85 | 0.124089 | 823.234ms | 4604 | 30 | 3033.2 | 8103.2 | 0.0863111 | 4.55413 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1063.51 | 0.185747 | 491.418ms | 4604 | 4890 | 287565 | 4128.51 | 0.126123 | 2.31334 | 1(Win) | true |
| Jsonifier (two-stage) | 970.21 | 0.0890814 | 536.42ms | 4604 | 30 | 487.568 | 4525.53 | 0.0875741 | 2.53673 | 2(Loss) | true |
| Glaze | 769.505 | 0.19664 | 668.002ms | 4604 | 30 | 3776.71 | 5705.9 | 0.228941 | 3.20384 | 3(Loss) | true |
| simdjson (ondemand) | 580.196 | 0.0974258 | 845.195ms | 4604 | 80 | 4348.69 | 7567.64 | 0.0563571 | 4.25144 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1687.42 | 0.0713063 | 289.3ms | 4918 | 30 | 117.845 | 2779.5 | 0.0119911 | 1.45329 | 1(Win) | true |
| Glaze | 846.154 | 0.134845 | 522.276ms | 4604 | 4890 | 239414 | 5189.03 | 0.292146 | 2.91136 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1712.91 | 0.0756355 | 278.062ms | 4918 | 30 | 128.671 | 2738.13 | 0.0974849 | 1.43092 | 1(Win) | true |
| Glaze | 875.739 | 0.028666 | 513.136ms | 4604 | 160 | 330.503 | 5013.73 | 0.0865874 | 2.81263 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2856.98 | 0.0425603 | 614.968ms | 18245 | 80 | 537.493 | 6090.27 | 0.113835 | 0.86281 | 1(Win) | true |
| Jsonifier | 2319.98 | 0.0431649 | 756.312ms | 18245 | 80 | 838.443 | 7499.99 | 0.137311 | 1.06354 | 2(Loss) | true |
| simdjson (ondemand) | 1949.36 | 0.185325 | 895.167ms | 18245 | 1280 | 350253 | 8925.9 | 0.193051 | 1.26636 | 3(Loss) | true |
| Glaze | 1824.38 | 0.0822767 | 971.208ms | 18245 | 30 | 1847.27 | 9537.37 | 0.36633 | 1.3535 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3318.45 | 0.0858652 | 608.154ms | 18245 | 40 | 810.797 | 5243.35 | 0.0403849 | 0.742162 | 1(Win) | true |
| Jsonifier | 2644.07 | 0.085083 | 742.316ms | 18245 | 40 | 1253.97 | 6580.68 | 0.052327 | 0.932757 | 2(Loss) | true |
| simdjson (ondemand) | 2127.63 | 0.126566 | 904.153ms | 18245 | 4890 | 523886 | 8178 | 0.108631 | 1.15972 | 3(Loss) | true |
| Glaze | 1982.33 | 0.0673737 | 956.924ms | 18245 | 40 | 1398.87 | 8777.45 | 0.0662244 | 1.24513 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6131.94 | 0.0711297 | 432.992ms | 24893 | 30 | 227.5 | 3871.5 | 0.0679722 | 0.401137 | 1(Win) | true |
| Glaze | 3795.83 | 0.0683039 | 637.388ms | 24579 | 80 | 1423.3 | 6175.29 | 0.306533 | 0.649453 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6101.6 | 0.119053 | 392.634ms | 24893 | 4890 | 104919 | 3890.75 | 0.292244 | 0.40298 | 1(Win) | true |
| Glaze | 4158.42 | 0.186022 | 567.357ms | 24579 | 2560 | 281475 | 5636.84 | 0.0122882 | 0.592635 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 976.252 | 0.0887559 | 456.964ms | 4604 | 40 | 637.384 | 4497.52 | 0.177006 | 2.52022 | 1(Win) | true |
| Jsonifier (two-stage) | 872.444 | 0.205371 | 521.543ms | 4604 | 1280 | 136737 | 5032.66 | 0.358716 | 2.82205 | 2(Loss) | true |
| Glaze | 684.228 | 0.123933 | 654.341ms | 4604 | 30 | 1897.41 | 6417.03 | 0.0899458 | 3.60406 | 3(Loss) | true |
| simdjson (ondemand) | 546.033 | 0.0499373 | 817.518ms | 4604 | 80 | 1289.95 | 8041.11 | 0.115322 | 4.51988 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1144.86 | 0.131465 | 469.334ms | 4604 | 4890 | 124307 | 3835.16 | 0.0850006 | 2.1473 | 1(Win) | true |
| Jsonifier (two-stage) | 1039.65 | 0.0515137 | 502.574ms | 4604 | 160 | 757.292 | 4223.27 | 0.0962485 | 2.36651 | 2(Loss) | true |
| Glaze | 783.399 | 0.148571 | 647.795ms | 4604 | 30 | 2080.15 | 5604.7 | 0.197657 | 3.14513 | 3(Loss) | true |
| simdjson (ondemand) | 609.677 | 0.158861 | 803.77ms | 4604 | 1280 | 167538 | 7201.71 | 0.0216698 | 4.04547 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1677.41 | 0.0273706 | 285.888ms | 4918 | 160 | 93.7103 | 2796.08 | 0.00514086 | 1.46247 | 1(Win) | true |
| Glaze | 852.426 | 0.24752 | 518.775ms | 4604 | 1280 | 208059 | 5150.85 | 0.0494095 | 2.88999 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1698.95 | 0.0388743 | 281.097ms | 4918 | 80 | 92.1361 | 2760.62 | 0.0452591 | 1.44448 | 1(Win) | true |
| Glaze | 877.876 | 0.0346341 | 505.874ms | 4604 | 80 | 240.05 | 5001.52 | 0.0860478 | 2.80616 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3056.58 | 0.104652 | 617.284ms | 18245 | 4890 | 173547 | 5692.57 | 0.168081 | 0.806025 | 1(Win) | true |
| Jsonifier | 2438.4 | 0.0835396 | 721.9ms | 18245 | 30 | 1066.06 | 7135.73 | 0.00887631 | 1.0114 | 2(Loss) | true |
| simdjson (ondemand) | 2005.59 | 0.0443006 | 895.851ms | 18245 | 80 | 1181.72 | 8675.66 | 0.14848 | 1.23103 | 3(Loss) | true |
| Glaze | 1892.89 | 0.153613 | 927.523ms | 18245 | 1280 | 255212 | 9192.16 | 0.366315 | 1.30416 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3563.61 | 0.0508843 | 570.731ms | 18245 | 40 | 246.907 | 4882.62 | 0.196832 | 0.69093 | 1(Win) | true |
| Jsonifier | 2758.22 | 0.255676 | 714.938ms | 18245 | 1280 | 332980 | 6308.34 | 0.273737 | 0.893946 | 2(Loss) | true |
| simdjson (ondemand) | 2140.05 | 0.221954 | 890.251ms | 18245 | 1280 | 416846 | 8130.55 | 0.123762 | 1.15303 | 3(Loss) | true |
| Glaze | 2052.85 | 0.238376 | 925.89ms | 18245 | 1280 | 522530 | 8475.93 | 0.0251049 | 1.20235 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5889.49 | 0.21678 | 406.364ms | 24893 | 1280 | 97734.1 | 4030.88 | 0.0312722 | 0.417694 | 1(Win) | true |
| Glaze | 3657.1 | 0.151446 | 628.341ms | 24579 | 2560 | 241218 | 6409.55 | 0.500855 | 0.674117 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5935.88 | 0.0527146 | 404.256ms | 24893 | 80 | 355.579 | 3999.38 | 0.091181 | 0.41458 | 1(Win) | true |
| Glaze | 4286.16 | 0.0447782 | 555.746ms | 24579 | 80 | 479.749 | 5468.85 | 0.194361 | 0.574942 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1853.07 | 0.0926187 | 266.267ms | 5094 | 30 | 176.869 | 2621.6 | 0.215344 | 1.32578 | 1(Win) | true |
| Jsonifier (two-stage) | 1685.8 | 0.0657863 | 291.811ms | 5094 | 80 | 287.518 | 2881.72 | 0.0399226 | 1.45528 | 2(Loss) | true |
| Glaze | 1295.02 | 0.122221 | 389.488ms | 5094 | 30 | 630.631 | 3751.3 | 0.062162 | 1.89934 | 3(Loss) | true |
| simdjson (ondemand) | 923.318 | 0.234568 | 528.893ms | 5094 | 1280 | 194968 | 5261.48 | 0.0360688 | 2.66738 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2251.24 | 0.0228717 | 263.569ms | 5094 | 160 | 38.9755 | 2157.93 | 0.0776812 | 1.08663 | 1(Win) | true |
| Jsonifier (two-stage) | 2006.31 | 0.081929 | 294.217ms | 5094 | 40 | 157.42 | 2421.38 | 0.10094 | 1.2206 | 2(Loss) | true |
| Glaze | 1597.74 | 0.210476 | 353.452ms | 5094 | 1280 | 52422.5 | 3040.55 | 0.379113 | 1.53638 | 3(Loss) | true |
| simdjson (ondemand) | 1031.6 | 0.235638 | 515.587ms | 5094 | 2560 | 315229 | 4709.22 | 0.00217322 | 2.38656 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14702.3 | 0.11954 | 35.3368ms | 5094 | 160 | 24.9629 | 330.425 | 0.0113503 | 0.155855 | 1(Win) | true |
| Glaze | 3418.13 | 0.124428 | 145.539ms | 5094 | 80 | 250.19 | 1421.25 | 0.0087943 | 0.711224 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16072.8 | 0.204758 | 32.7879ms | 5094 | 40 | 15.3205 | 302.25 | 0.0716332 | 0.141225 | 1(Win) | true |
| Glaze | 3690.91 | 0.232586 | 134.801ms | 5094 | 4890 | 45827.6 | 1316.21 | 0.144105 | 0.657824 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2529.42 | 0.0439468 | 312.352ms | 8051 | 160 | 284.73 | 3035.49 | 0.21604 | 0.970562 | 1(Win) | true |
| Jsonifier | 2030.89 | 0.0380834 | 385.212ms | 8051 | 160 | 331.681 | 3780.63 | 0.103216 | 1.21061 | 2(Loss) | true |
| Glaze | 1707.03 | 0.040785 | 457.165ms | 8051 | 160 | 538.44 | 4497.89 | 0.192962 | 1.44232 | 3(Loss) | true |
| simdjson (ondemand) | 1392.83 | 0.18959 | 554.679ms | 8051 | 2560 | 279623 | 5512.52 | 0.0017007 | 1.76759 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2902.27 | 0.0446233 | 310.985ms | 8051 | 160 | 222.981 | 2645.53 | 0.0207941 | 0.844421 | 1(Win) | true |
| Jsonifier | 2284.82 | 0.0605773 | 385.888ms | 8051 | 80 | 331.516 | 3360.45 | 0.281257 | 1.07457 | 2(Loss) | true |
| Glaze | 2013.53 | 0.060867 | 428.982ms | 8051 | 80 | 430.961 | 3813.22 | 0.145101 | 1.22131 | 3(Loss) | true |
| simdjson (ondemand) | 1578.29 | 0.068043 | 532.563ms | 8051 | 40 | 438.281 | 4864.77 | 0.045716 | 1.55963 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18642.1 | 0.0419866 | 50.0261ms | 9255 | 640 | 25.2909 | 473.458 | 0.0703435 | 0.125636 | 1(Win) | true |
| Glaze | 4209.24 | 0.106941 | 215.085ms | 9255 | 40 | 201.138 | 2096.88 | 0.274572 | 0.581016 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20008.9 | 0.0336814 | 46.7538ms | 9255 | 640 | 14.1275 | 441.116 | 0.0113336 | 0.116578 | 1(Win) | true |
| Glaze | 4650.62 | 0.112322 | 193.652ms | 9255 | 30 | 136.326 | 1897.87 | 0.0685449 | 0.525143 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6693.18 | 0.103919 | 44.1967ms | 2889 | 80 | 14.6391 | 411.637 | 0.045529 | 0.344237 | 1(Win) | true |
| Jsonifier (two-stage) | 6237.09 | 0.0628049 | 46.8955ms | 2889 | 640 | 49.2604 | 441.739 | 0.123295 | 0.373819 | 2(Loss) | true |
| Jsonifier | 5951 | 0.148565 | 47.3934ms | 2889 | 80 | 37.8475 | 462.975 | 0.216462 | 0.392121 | 3(Loss) | true |
| Glaze | 3440.78 | 0.083028 | 83.7501ms | 2889 | 80 | 35.3606 | 800.737 | 0.1792 | 0.696738 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6844.28 | 0.0683826 | 43.2676ms | 2889 | 320 | 24.2483 | 402.55 | 0.0775699 | 0.338319 | 1(Win) | true |
| Jsonifier | 6623.12 | 0.0548718 | 44.8027ms | 2889 | 1280 | 66.6927 | 415.992 | 0.0533079 | 0.350414 | 2(Loss) | true |
| Jsonifier (two-stage) | 6484.74 | 0.11529 | 44.9929ms | 2889 | 320 | 76.779 | 424.869 | 0.139554 | 0.358735 | 3(Loss) | true |
| Glaze | 3487.83 | 0.039896 | 82.5995ms | 2889 | 320 | 31.7829 | 789.938 | 0.28481 | 0.686703 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7741.87 | 0.089067 | 49.4355ms | 3808 | 320 | 55.8581 | 469.084 | 0.0526568 | 0.300641 | 1(Win) | true |
| Jsonifier (two-stage) | 7476 | 0.190545 | 52.9357ms | 3808 | 30 | 25.7023 | 485.767 | 0.206285 | 0.312903 | 2(Loss) | true |
| Jsonifier | 7354.12 | 0.0534843 | 53.9486ms | 3808 | 640 | 44.6441 | 493.817 | 0.0256229 | 0.319136 | 3(Loss) | true |
| Glaze | 3873.59 | 1.45672 | 117.975ms | 3808 | 640 | 119371 | 937.525 | 0.365317 | 0.621459 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8076.04 | 0.0587405 | 48.2577ms | 3808 | 320 | 22.3266 | 449.675 | 0.194207 | 0.288518 | 1(Win) | true |
| Jsonifier | 7819.4 | 0.0339471 | 49.4704ms | 3808 | 1280 | 31.8173 | 464.434 | 0.0102601 | 0.298827 | 2(Loss) | true |
| simdjson (ondemand) | 7781.75 | 0.034156 | 49.7942ms | 3808 | 1280 | 32.5225 | 466.68 | 0.00786869 | 0.299375 | 3(Loss) | true |
| Glaze | 4012.92 | 0.0505688 | 93.8852ms | 3808 | 160 | 33.5088 | 904.975 | 0.0138144 | 0.599358 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2228.66 | 0.275066 | 126.249ms | 2889 | 4890 | 56544.4 | 1236.24 | 0.000701543 | 1.08738 | 1(Win) | true |
| Jsonifier (two-stage) | 2200.63 | 0.0859072 | 128.963ms | 2889 | 80 | 92.5441 | 1251.99 | 0.00698938 | 1.10131 | 2(Loss) | true |
| Glaze | 2122.08 | 0.101022 | 135.065ms | 2889 | 30 | 51.6092 | 1298.33 | 0.0256805 | 1.14236 | 3(Loss) | true |
| simdjson (ondemand) | 1058.03 | 0.0301607 | 265.244ms | 2889 | 160 | 98.6962 | 2604.04 | 0.0386269 | 2.31696 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2441.01 | 0.140961 | 122.297ms | 2889 | 30 | 75.9414 | 1128.7 | 0.239787 | 0.991116 | 1(Win) | true |
| Glaze STATISTICAL TIE | 2389.05 | 0.211104 | 123.225ms | 2889 | 4890 | 28983 | 1153.25 | 0.00987892 | 1.01237 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2382.43 | 0.0494989 | 123.654ms | 2889 | 320 | 104.856 | 1156.45 | 0.0199925 | 1.01581 | 2(Tie) | true |
| simdjson (ondemand) | 1091.34 | 0.19008 | 260.73ms | 2889 | 4890 | 112604 | 2524.56 | 0.305252 | 2.24467 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12096.5 | 0.282442 | 26.0318ms | 2963 | 80 | 34.8253 | 233.6 | 0.107135 | 0.182134 | 1(Win) | true |
| Glaze | 5372.86 | 0.0724759 | 54.9281ms | 2963 | 320 | 46.4933 | 525.928 | 0.0362586 | 0.438171 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13107.1 | 0.336667 | 24.0106ms | 2963 | 80 | 42.1441 | 215.588 | 0.340922 | 0.165698 | 1(Win) | true |
| Glaze | 5688.45 | 0.122885 | 54.0408ms | 2963 | 80 | 29.8101 | 496.75 | 0 | 0.412597 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2814.5 | 0.0445237 | 134.527ms | 3808 | 320 | 105.615 | 1290.32 | 0.165203 | 0.861643 | 1(Win) | true |
| Glaze | 2329.62 | 0.0875292 | 160.733ms | 3808 | 40 | 74.4712 | 1558.88 | 0.0133661 | 1.04478 | 2(Loss) | true |
| Jsonifier | 1949.53 | 0.144285 | 190.922ms | 3808 | 30 | 216.717 | 1862.8 | 0.0339874 | 1.25285 | 3(Loss) | true |
| simdjson (ondemand) | 1379.36 | 0.0402036 | 268.227ms | 3808 | 80 | 89.6304 | 2632.8 | 0.0208947 | 1.77806 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3088.81 | 0.145353 | 125.809ms | 3808 | 40 | 116.82 | 1175.72 | 0.0290516 | 0.783771 | 1(Win) | true |
| Glaze | 2523.98 | 0.135854 | 154.868ms | 3808 | 30 | 114.626 | 1438.83 | 0.184992 | 0.963813 | 2(Loss) | true |
| Jsonifier | 2059.93 | 0.189117 | 186.309ms | 3808 | 30 | 333.482 | 1762.97 | 0.243314 | 1.18365 | 3(Loss) | true |
| simdjson (ondemand) | 1422.93 | 0.0885828 | 264.178ms | 3808 | 30 | 153.338 | 2552.2 | 0.0692693 | 1.72124 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10502.1 | 0.0800529 | 41.7486ms | 4300 | 640 | 62.5346 | 390.475 | 0.0841029 | 0.220404 | 1(Win) | true |
| Glaze | 4138.08 | 0.0449296 | 102.723ms | 4300 | 320 | 63.4388 | 990.991 | 0.153175 | 0.583033 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12304.2 | 0.157224 | 36.3496ms | 4300 | 320 | 87.8656 | 333.284 | 0.311261 | 0.186009 | 1(Win) | true |
| Glaze | 4773.92 | 0.121168 | 89.6214ms | 4300 | 40 | 43.3333 | 859 | 0.0193986 | 0.503779 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4412.21 | 0.108618 | 5178.41ms | 466906 | 640 | 7.69012e+06 | 100919 | 0.0559486 | 0.560934 | 1(Win) | true |
| Glaze | 2824.69 | 0.0801423 | 8215.67ms | 466906 | 640 | 1.02146e+07 | 157637 | 0.270997 | 0.876334 | 2(Loss) | true |
| simdjson (ondemand) | 1869.09 | 0.0944068 | 6147.67ms | 466906 | 640 | 3.2373e+07 | 238231 | 0.181163 | 1.32436 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4470.03 | 0.251947 | 5267.36ms | 466906 | 160 | 1.0078e+07 | 99613.7 | 0.296424 | 0.553691 | 1(Win) | true |
| Glaze | 2773.07 | 0.412556 | 8180.06ms | 466906 | 40 | 1.75534e+07 | 160571 | 0.304998 | 0.892661 | 2(Loss) | true |
| simdjson (ondemand) | 1875.13 | 0.0501774 | 6083.83ms | 466906 | 1280 | 1.81729e+07 | 237464 | 0.0924455 | 1.32013 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6111.47 | 0.114595 | 5650.61ms | 699405 | 640 | 1.0011e+07 | 109140 | 0.327197 | 0.404995 | 1(Win) | true |
| Glaze | 4047.97 | 0.133125 | 8494.84ms | 699405 | 640 | 3.0795e+07 | 164775 | 0.0234498 | 0.611494 | 2(Loss) | true |
| simdjson (ondemand) | 2487.76 | 0.200801 | 7594.91ms | 767297 | 160 | 5.58161e+07 | 294140 | 0.380815 | 0.994966 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6002.65 | 0.118273 | 5698.97ms | 699405 | 2560 | 4.42163e+07 | 111118 | 0.325876 | 0.412334 | 1(Win) | true |
| Glaze | 4081.06 | 0.174018 | 8743.53ms | 699405 | 80 | 6.47127e+06 | 163439 | 0.0226053 | 0.606547 | 2(Loss) | true |
| simdjson (ondemand) | 2534.65 | 0.188758 | 7393.21ms | 767297 | 80 | 2.37569e+07 | 288699 | 0.0993368 | 0.976648 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4189 | 0.049758 | 7531.01ms | 631514 | 1280 | 6.55062e+06 | 143772 | 0.127334 | 0.590911 | 1(Win) | true |
| Glaze | 2652.96 | 0.0782327 | 5844.05ms | 631514 | 320 | 1.00933e+07 | 227014 | 0.0906989 | 0.933123 | 2(Loss) | true |
