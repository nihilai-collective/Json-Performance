# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the Clang 23.1.4 compiler).  

Latest Results: (Nov 07, 2026)
#### Using the following commits:
----
| Jsonifier: [3e5ab01](https://github.com/nihilai-collective/Jsonifier/commit/3e5ab01)  
| Glaze: [0a363d40](https://github.com/stephenberry/glaze/commit/0a363d40)  
| simdjson: [dfe02cfe3](https://github.com/simdjson/simdjson/commit/dfe02cfe3)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `NEON` |
| **simdjson (ondemand)** | `arm64` |
| **Glaze** | utf8: `NEON64`, escape: `NEON`, float: `NEON`, struct-skip: `NEON64` |

> **Adaptive Sampling & Convergence (Apple M2 Pro (Virtual)-NEON):**  
> Iterations scale geometrically (100 → 200 → 400 ...) up to a maximum of 100000.  
> Scores evaluate a trailing window of `max(iterations/10, 30)` (cap: 100000) over at most 5s.  
> Canonical epochs are chosen by minimum (RSE + epoch-over-epoch mean shift).  
> Converged: RSE ≤ 10% and mean shift ≤ 5%. Tie detection: Welch's t-test with Bessel-corrected variance.

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

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1270.79 | 0.112884 | 73.3156ms | 905 | 640 | 376.182 | 679.166 | 0.306921 | 1(Win) | true |
| Glaze | 1203.01 | 0.306396 | 78.0395ms | 905 | 2560 | 12369.9 | 717.43 | 0.320105 | 2(Loss) | true |
| Jsonifier (two-stage) | 371.642 | 0.0935549 | 236.763ms | 905 | 2560 | 12084.3 | 2322.33 | 0.107817 | 3(Loss) | true |
| simdjson (ondemand) | 177.458 | 0.133649 | 485.034ms | 905 | 40 | 1690.05 | 4863.55 | 0.0785365 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1372.32 | 0.164157 | 72.0134ms | 905 | 160 | 170.541 | 628.919 | 0.038772 | 1(Win) | true |
| Glaze | 1354.84 | 0.0577009 | 67.4975ms | 905 | 4890 | 660.685 | 637.031 | 0.215544 | 2(Loss) | true |
| Jsonifier (two-stage) | 334.476 | 0.403343 | 266.676ms | 905 | 1280 | 138652 | 2580.38 | 0.801992 | 3(Loss) | true |
| simdjson (ondemand) | 173.059 | 0.343767 | 492.34ms | 905 | 640 | 188112 | 4987.18 | 0.0430037 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1033.29 | 0.0668223 | 87.3276ms | 905 | 320 | 99.6878 | 835.266 | 0.0205731 | 1(Win) | true |
| Glaze | 131.951 | 0.104456 | 658.311ms | 905 | 2560 | 119503 | 6540.9 | 0.15718 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 999.479 | 2.42504 | 92.0067ms | 905 | 40 | 17540.7 | 863.525 | 1.76278 | 1(Win) | true |
| Glaze | 763.684 | 0.0563499 | 127.235ms | 905 | 640 | 259.559 | 1130.15 | 0.0171467 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 926.375 | 0.095544 | 191.76ms | 1811 | 160 | 507.681 | 1864.37 | 0.0419218 | 1(Win) | true |
| Glaze | 748.132 | 0.0951683 | 227.588ms | 1811 | 160 | 772.299 | 2308.56 | 0.236365 | 2(Loss) | true |
| Jsonifier (two-stage) | 376.993 | 0.066555 | 465.869ms | 1811 | 80 | 743.74 | 4581.26 | 0.249579 | 3(Loss) | true |
| simdjson (ondemand) | 212.293 | 0.0749702 | 817.791ms | 1811 | 40 | 1488 | 8135.48 | 0.025922 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1102.79 | 0.147818 | 160.199ms | 1811 | 80 | 428.744 | 1566.12 | 0.164689 | 1(Win) | true |
| Glaze | 972.763 | 0.134928 | 191.946ms | 1811 | 80 | 459.113 | 1775.46 | 0.0246475 | 2(Loss) | true |
| Jsonifier (two-stage) | 403.594 | 0.0842677 | 431.655ms | 1811 | 4890 | 63588.5 | 4279.31 | 0.0553539 | 3(Loss) | true |
| simdjson (ondemand) | 220.408 | 0.0269467 | 789.956ms | 1811 | 160 | 713.365 | 7835.93 | 0.0122847 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 290.972 | 0.102189 | 598.839ms | 1811 | 160 | 5886.56 | 5935.63 | 0.0314935 | 1(Win) | true |
| Glaze | 224.405 | 0.0668345 | 774.265ms | 1798 | 80 | 2086.45 | 7641.14 | 0.210982 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 906.486 | 0.207626 | 205.473ms | 1811 | 40 | 625.948 | 1905.28 | 0.205554 | 1(Win) | true |
| Glaze | 716.246 | 0.0737978 | 256.925ms | 1798 | 160 | 499.415 | 2394.02 | 0.0765513 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2277.65 | 0.0718178 | 165.466ms | 3862 | 320 | 431.583 | 1617.06 | 0.010821 | 1(Win) | true |
| Glaze | 1231.83 | 0.0362725 | 298.298ms | 3862 | 640 | 752.758 | 2989.92 | 0.0103462 | 2(Loss) | true |
| Jsonifier (two-stage) | 849.546 | 0.0664036 | 437.797ms | 3862 | 160 | 1326.03 | 4335.36 | 0.0836847 | 3(Loss) | true |
| simdjson (ondemand) | 487.65 | 0.0912574 | 800.254ms | 3862 | 30 | 1425.17 | 7552.73 | 0.0189741 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2744.14 | 0.103652 | 138.669ms | 3862 | 320 | 619.324 | 1342.17 | 0.0957859 | 1(Win) | true |
| Glaze | 1239.89 | 0.216202 | 298.576ms | 3862 | 4890 | 201690 | 2970.49 | 0.435809 | 2(Loss) | true |
| Jsonifier (two-stage) | 919.054 | 0.215214 | 406.577ms | 3862 | 640 | 47606.1 | 4007.48 | 0.0339094 | 3(Loss) | true |
| simdjson (ondemand) | 499.567 | 0.10654 | 745.029ms | 3862 | 2560 | 157944 | 7372.56 | 0.282771 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2956.8 | 0.0320391 | 127.835ms | 3862 | 1280 | 203.869 | 1245.63 | 0.0364892 | 1(Win) | true |
| Glaze | 551.922 | 0.0566112 | 676.478ms | 3862 | 160 | 2283.46 | 6673.21 | 0.0423155 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3424.26 | 0.0632096 | 117.309ms | 3862 | 640 | 295.826 | 1075.59 | 0.0180167 | 1(Win) | true |
| Glaze | 2194.05 | 0.147707 | 186.433ms | 3862 | 80 | 491.842 | 1678.67 | 0.0312845 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1373.28 | 0.10738 | 671.3ms | 9578 | 2560 | 130592 | 6651.43 | 0.51562 | 1(Win) | true |
| Glaze | 1173.87 | 0.195671 | 772.275ms | 9578 | 640 | 148368 | 7781.32 | 0.0233587 | 2(Loss) | true |
| simdjson (ondemand) | 885.157 | 0.0911558 | 1077.89ms | 9578 | 4890 | 432700 | 10319.4 | 1.61134 | 3(Loss) | true |
| Jsonifier (two-stage) | 747.523 | 0.128419 | 1290.54ms | 9578 | 640 | 157595 | 12219.4 | 0.0508154 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2411.94 | 0.123434 | 619.047ms | 9578 | 4890 | 106855 | 3787.11 | 0.0125617 | 1(Win) | true |
| Glaze | 1826.1 | 0.0664184 | 754.796ms | 9578 | 40 | 441.507 | 5002.07 | 0.0677592 | 2(Loss) | true |
| simdjson (ondemand) | 1174.59 | 0.0372867 | 1001.52ms | 9578 | 80 | 672.627 | 7776.57 | 0.059117 | 3(Loss) | true |
| Jsonifier (two-stage) | 971.241 | 0.096028 | 1198.64ms | 9578 | 2560 | 208800 | 9404.76 | 0.0402468 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1343.82 | 0.0962392 | 661.038ms | 9578 | 30 | 1283.79 | 6797.27 | 0.000980796 | 1(Win) | true |
| Glaze | 1150.4 | 0.0820983 | 808.749ms | 9578 | 30 | 1274.81 | 7940.13 | 0.0197271 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7843.83 | 0.0502362 | 128.446ms | 9578 | 1280 | 438.064 | 1164.52 | 0.0663938 | 1(Win) | true |
| Glaze | 4277.07 | 0.119311 | 227.464ms | 9578 | 4890 | 31748.7 | 2135.64 | 0.0952348 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2342.04 | 0.0971542 | 161.677ms | 3873 | 160 | 375.622 | 1577.08 | 0.0336743 | 1(Win) | true |
| Glaze | 1168.13 | 0.117306 | 337.166ms | 3873 | 80 | 1100.64 | 3161.96 | 0.933265 | 2(Loss) | true |
| Jsonifier (two-stage) | 831.847 | 0.0805146 | 447.328ms | 3873 | 4890 | 62498.1 | 4440.22 | 0.139428 | 3(Loss) | true |
| simdjson (ondemand) | 476.847 | 0.11022 | 781.641ms | 3873 | 30 | 2186.63 | 7745.83 | 0.0344153 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2823.68 | 0.126838 | 134.625ms | 3873 | 160 | 440.435 | 1308.08 | 0.0620756 | 1(Win) | true |
| Glaze | 1465.52 | 0.0789786 | 254.953ms | 3873 | 160 | 633.942 | 2520.32 | 0.0195946 | 2(Loss) | true |
| Jsonifier (two-stage) | 889.098 | 0.187213 | 458.224ms | 3873 | 30 | 1814.63 | 4154.3 | 0.0296793 | 3(Loss) | true |
| simdjson (ondemand) | 482.937 | 0.0318681 | 760.928ms | 3873 | 320 | 1900.97 | 7648.17 | 0.105856 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2930 | 0.0596775 | 127.426ms | 3873 | 640 | 362.211 | 1260.61 | 0.118014 | 1(Win) | true |
| Glaze | 557.965 | 0.0656007 | 705.755ms | 3873 | 80 | 1508.65 | 6619.74 | 0.0315444 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3430.21 | 0.165953 | 117.814ms | 3873 | 2560 | 8174.57 | 1076.78 | 0.013856 | 1(Win) | true |
| Glaze | 2247.05 | 0.107242 | 188.919ms | 3873 | 160 | 497.185 | 1643.74 | 0.12449 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1539.17 | 0.0661979 | 6065.79ms | 94653 | 4890 | 7.37042e+06 | 58647.2 | 0.368068 | 1(Win) | true |
| Glaze | 1126.65 | 0.207442 | 8058.49ms | 94653 | 320 | 8.83962e+06 | 80120.8 | 0.36174 | 2(Loss) | true |
| Jsonifier (two-stage) | 1103.92 | 0.0766661 | 8244.19ms | 94653 | 1280 | 5.03052e+06 | 81770.8 | 0.0323111 | 3(Loss) | true |
| simdjson (ondemand) | 886.781 | 0.124787 | 5413.08ms | 94653 | 320 | 5.16322e+06 | 101793 | 0.24475 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2319.58 | 0.0490106 | 5490.19ms | 94653 | 4890 | 1.77885e+06 | 38915.7 | 0.067689 | 1(Win) | true |
| Jsonifier (two-stage) | 1499.52 | 0.061233 | 7958.09ms | 94653 | 2560 | 3.47838e+06 | 60198.1 | 0.0444441 | 2(Loss) | true |
| Glaze | 1461.4 | 0.10975 | 7668.88ms | 94653 | 1280 | 5.88235e+06 | 61768.4 | 0.115656 | 3(Loss) | true |
| simdjson (ondemand) | 1072.46 | 0.122077 | 5072.34ms | 94653 | 320 | 3.37854e+06 | 84169.5 | 0.139686 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12162 | 0.0587035 | 747.377ms | 94653 | 30 | 569.523 | 7422.17 | 0.0202056 | 1(Win) | true |
| Glaze | 3543.41 | 0.0539898 | 2498.1ms | 94653 | 30 | 5675.06 | 25474.9 | 0.0824968 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12479.5 | 0.076465 | 732.157ms | 94653 | 30 | 917.747 | 7233.33 | 0.171261 | 1(Win) | true |
| Glaze | 4321.75 | 0.089077 | 2214.88ms | 94653 | 2560 | 886176 | 20886.9 | 0.418786 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1655.77 | 0.255067 | 7326.83ms | 124597 | 80 | 2.68048e+06 | 71764.1 | 0.235079 | 1(Win) | true |
| Jsonifier (two-stage) | 1378.59 | 0.138359 | 8738.14ms | 124597 | 320 | 4.55102e+06 | 86193.1 | 0.0696524 | 2(Loss) | true |
| Glaze | 1367.68 | 0.0429996 | 8865.43ms | 124597 | 4890 | 6.82467e+06 | 86880.4 | 0.114912 | 3(Loss) | true |
| simdjson (ondemand) | 1129.65 | 0.146276 | 5409.98ms | 124597 | 320 | 7.5757e+06 | 105187 | 0.00902935 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2250.96 | 0.0453768 | 6914.34ms | 124597 | 4890 | 2.8058e+06 | 52788.6 | 0.014555 | 1(Win) | true |
| Jsonifier (two-stage) | 1838.88 | 0.103667 | 8365.36ms | 124597 | 640 | 2.87188e+06 | 64618.1 | 0.0289743 | 2(Loss) | true |
| Glaze | 1730.95 | 0.0609553 | 8282.57ms | 124597 | 4890 | 8.56205e+06 | 68647.2 | 0.0597095 | 3(Loss) | true |
| simdjson (ondemand) | 1366.66 | 0.0655851 | 5298.44ms | 124597 | 2560 | 8.32427e+06 | 86945.7 | 0.032552 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12100.1 | 0.0343896 | 1135.1ms | 136037 | 80 | 1087.63 | 10721.8 | 0.0383416 | 1(Win) | true |
| Glaze | 3591.66 | 0.176759 | 3638.96ms | 136076 | 320 | 1.30522e+06 | 36131.6 | 0.0796193 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12368.7 | 0.0235264 | 1087.99ms | 136037 | 160 | 974.314 | 10489 | 0.17286 | 1(Win) | true |
| Glaze | 3985.36 | 0.107928 | 3292.06ms | 136076 | 1280 | 1.5809e+06 | 32562.2 | 0.0822794 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 837.817 | 0.0645069 | 8029.93ms | 2251027 | 40 | 1.09279e+08 | 2.56231e+06 | 0.0618187 | 1(Win) | true |
| Jsonifier (two-stage) | 742.457 | 0.0599813 | 9477.8ms | 2251027 | 80 | 2.40625e+08 | 2.89141e+06 | 1.22072 | 2(Loss) | true |
| Glaze | 601.761 | 0.114538 | 5455.57ms | 2251027 | 30 | 5.00883e+08 | 3.56744e+06 | 0.506426 | 3(Loss) | true |
| simdjson (ondemand) | 536.335 | 0.776131 | 6035.05ms | 2251027 | 30 | 2.89522e+10 | 4.00262e+06 | 1.46349 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1036.76 | 0.17015 | 8327.7ms | 2251027 | 160 | 1.98605e+09 | 2.07063e+06 | 0.628638 | 1(Win) | true |
| Jsonifier (two-stage) | 898.16 | 0.138694 | 9206.61ms | 2251027 | 160 | 1.75829e+09 | 2.39016e+06 | 0.0451316 | 2(Loss) | true |
| Glaze | 700.357 | 0.291665 | 5454.87ms | 2251027 | 80 | 6.39412e+09 | 3.06522e+06 | 0.235855 | 3(Loss) | true |
| simdjson (ondemand) | 626.319 | 0.0614545 | 5965.34ms | 2251027 | 40 | 1.77475e+08 | 3.42756e+06 | 0.0571404 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3000.2 | 0.0903814 | 8539.71ms | 2090234 | 320 | 1.15398e+08 | 664424 | 0.162746 | 1(Win) | true |
| Glaze | 1891.94 | 0.0717434 | 6746.05ms | 2090234 | 320 | 1.82848e+08 | 1.05363e+06 | 0.027681 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2988.68 | 0.124334 | 8508.64ms | 2090234 | 160 | 1.10035e+08 | 666983 | 0.0472221 | 1(Win) | true |
| Glaze | 1983.14 | 0.10558 | 6480.71ms | 2090234 | 40 | 4.50514e+07 | 1.00518e+06 | 0.00697175 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1680.88 | 0.0533154 | 9541.24ms | 5373214 | 30 | 7.92542e+07 | 3.04858e+06 | 0.0416261 | 1(Win) | true |
| Jsonifier (two-stage) | 1590.03 | 0.333823 | 10034.6ms | 5373214 | 80 | 9.25941e+09 | 3.22278e+06 | 0.621955 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1196.67 | 0.2927 | 6475.34ms | 5373214 | 80 | 1.25677e+10 | 4.28214e+06 | 0.483344 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 1196.66 | 0.613989 | 6439.86ms | 5373214 | 80 | 5.53017e+10 | 4.28216e+06 | 3.00206 | 3(Tie) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2017.23 | 0.0842163 | 9772.34ms | 5373214 | 40 | 1.83066e+08 | 2.54026e+06 | 0.0477542 | 1(Win) | true |
| Jsonifier (two-stage) | 1907.14 | 0.0481833 | 10046.5ms | 5373214 | 80 | 1.34087e+08 | 2.6869e+06 | 0.0518756 | 2(Loss) | true |
| Glaze | 1404.07 | 0.0566403 | 6361.46ms | 5373214 | 40 | 1.70923e+08 | 3.6496e+06 | 0.0194246 | 3(Loss) | true |
| simdjson (ondemand) | 1365.43 | 0.0951996 | 6512.36ms | 5373214 | 30 | 3.82929e+08 | 3.75287e+06 | 0.152673 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7222.89 | 0.0487004 | 5566.79ms | 6661897 | 320 | 5.87203e+07 | 879603 | 0.224378 | 1(Win) | true |
| Glaze | 3563.17 | 0.136189 | 5546ms | 6661897 | 30 | 1.769e+08 | 1.78304e+06 | 0.0548854 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7228.3 | 0.0969331 | 5657ms | 6661897 | 80 | 5.80708e+07 | 878945 | 0.177895 | 1(Win) | true |
| Glaze | 4032.76 | 0.160014 | 5019.95ms | 6661897 | 40 | 2.54193e+08 | 1.57542e+06 | 0.308383 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2146.32 | 0.231432 | 5882.03ms | 500299 | 80 | 2.11742e+07 | 222298 | 0.0862819 | 1(Win) | true |
| Jsonifier (two-stage) | 1452.13 | 0.0512199 | 8577.36ms | 500299 | 1280 | 3.62525e+07 | 328568 | 0.0296502 | 2(Loss) | true |
| Glaze | 1273.8 | 0.253134 | 9683.33ms | 500299 | 30 | 2.697e+07 | 374567 | 0.170963 | 3(Loss) | true |
| simdjson (ondemand) | 742.811 | 0.834606 | 8258.5ms | 500299 | 80 | 2.29909e+09 | 642320 | 1.27083 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2634.03 | 0.0478471 | 5575.64ms | 500299 | 1280 | 9.61479e+06 | 181138 | 0.0104615 | 1(Win) | true |
| Jsonifier (two-stage) | 1673.05 | 0.123199 | 9156.07ms | 500299 | 160 | 1.97506e+07 | 285181 | 0.101991 | 2(Loss) | true |
| Glaze | 1423.3 | 0.0795892 | 9521.94ms | 500299 | 320 | 2.27784e+07 | 335222 | 0.0831211 | 3(Loss) | true |
| simdjson (ondemand) | 732.509 | 0.767615 | 8651.72ms | 500299 | 640 | 1.59992e+10 | 651353 | 0.398551 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7265.89 | 0.177397 | 6506.6ms | 500299 | 4890 | 6.63561e+07 | 65666 | 0.258538 | 1(Win) | true |
| Glaze | 1888.75 | 0.353872 | 6245.81ms | 500299 | 640 | 5.11423e+08 | 252612 | 2.12653 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7693.57 | 0.358891 | 6471.35ms | 500299 | 320 | 1.58518e+07 | 62015.7 | 0.593891 | 1(Win) | true |
| Glaze | 2013.94 | 0.27626 | 5851.69ms | 500299 | 1280 | 5.48293e+08 | 236910 | 1.02105 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 2508.84 | 1.11753 | 5377.08ms | 1151920 | 40 | 9.57797e+08 | 437874 | 0.643023 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2494.93 | 0.636476 | 5612.59ms | 1151920 | 160 | 1.25665e+09 | 440316 | 0.577112 | 1(Tie) | true |
| Glaze | 1841.52 | 0.460662 | 7693.68ms | 1151920 | 160 | 1.20831e+09 | 596550 | 1.24215 | 3(Loss) | true |
| simdjson (ondemand) | 1550.58 | 0.528522 | 8848.59ms | 1151920 | 320 | 4.48674e+09 | 708480 | 1.63955 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 2965.23 | 0.72306 | 5022.88ms | 1151920 | 160 | 1.14814e+09 | 370479 | 2.50456 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2949.36 | 0.40036 | 5476.6ms | 1151920 | 160 | 3.55803e+08 | 372472 | 0.47666 | 1(Tie) | true |
| Glaze | 1871.92 | 0.311533 | 7805.41ms | 1151920 | 640 | 2.13924e+09 | 586861 | 1.08766 | 3(Loss) | true |
| simdjson (ondemand) | 1621.81 | 0.473499 | 8854.47ms | 1151920 | 320 | 3.29181e+09 | 677366 | 1.35967 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13693.9 | 0.315322 | 5298.75ms | 1439562 | 640 | 6.39577e+07 | 100254 | 3.91031 | 1(Win) | true |
| Glaze | 3962.59 | 0.534942 | 9759.76ms | 1439584 | 30 | 1.03051e+08 | 346464 | 0.369032 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13389 | 0.133898 | 5268.77ms | 1439562 | 2560 | 4.82565e+07 | 102538 | 0.589568 | 1(Win) | true |
| Glaze | 4757.13 | 0.42508 | 8238.1ms | 1439584 | 160 | 2.40794e+08 | 288597 | 2.11761 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1991.99 | 0.245994 | 2829.03ms | 56369 | 4890 | 2.15508e+07 | 26986.9 | 0.839808 | 1(Win) | true |
| Glaze | 1439.38 | 0.184927 | 4110.1ms | 56369 | 1280 | 6.10581e+06 | 37347.9 | 0.135887 | 2(Loss) | true |
| Jsonifier (two-stage) | 1176.68 | 0.249504 | 4764.35ms | 56369 | 2560 | 3.32629e+07 | 45685.9 | 1.70867 | 3(Loss) | true |
| simdjson (ondemand) | 644.983 | 0.543714 | 8110.59ms | 56369 | 640 | 1.31433e+08 | 83347.4 | 0.193291 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2794.15 | 0.201111 | 2132.57ms | 56369 | 4890 | 7.32089e+06 | 19239.4 | 0.40692 | 1(Win) | true |
| Jsonifier (two-stage) | 1473.3 | 0.379941 | 4531.16ms | 56369 | 1280 | 2.46004e+07 | 36488 | 0.216491 | 2(Loss) | true |
| Glaze | 1411.63 | 1.21996 | 3653.41ms | 56369 | 640 | 1.38137e+08 | 38082 | 3.306 | 3(Loss) | true |
| simdjson (ondemand) | 798.397 | 1.01873 | 7022.5ms | 56369 | 30 | 1.4115e+07 | 67332 | 1.55157 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12570.9 | 0.119129 | 429.641ms | 56369 | 30 | 778.585 | 4276.37 | 0.0988958 | 1(Win) | true |
| Glaze | 3351.16 | 0.0627329 | 1617.57ms | 56369 | 4890 | 495210 | 16041.5 | 0.0153696 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13328.4 | 0.0671806 | 411.462ms | 56369 | 80 | 587.357 | 4033.31 | 0.0238581 | 1(Win) | true |
| Glaze | 3892.66 | 0.145098 | 1396.81ms | 56369 | 640 | 256974 | 13810 | 0.0529227 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2371.18 | 0.0682344 | 3546.78ms | 83958 | 2560 | 1.35907e+06 | 33767.4 | 0.166356 | 1(Win) | true |
| Glaze | 1881.86 | 0.0983112 | 4286.89ms | 83958 | 1280 | 2.23958e+06 | 42547.6 | 0.00535034 | 2(Loss) | true |
| Jsonifier (two-stage) | 1459.68 | 0.15646 | 5227.99ms | 83958 | 4890 | 3.60183e+07 | 54853.6 | 2.77076 | 3(Loss) | true |
| simdjson (ondemand) | 950.957 | 0.255768 | 8665.48ms | 83958 | 2560 | 1.18723e+08 | 84197.9 | 0.338082 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2703.12 | 0.0288605 | 3332.63ms | 83958 | 30 | 2192.42 | 29620.8 | 0.000112533 | 1(Win) | true |
| Glaze | 2173.09 | 0.0479777 | 3928.42ms | 83958 | 4890 | 1.52812e+06 | 36845.5 | 0.231602 | 2(Loss) | true |
| Jsonifier (two-stage) | 1819.64 | 0.475313 | 4948.85ms | 83958 | 640 | 2.79958e+07 | 44002.5 | 0.0373561 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1058.46 | 0.149179 | 8043.92ms | 83958 | 2560 | 3.26012e+07 | 75646.6 | 5.83217 | -(Loss) | false |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13374.2 | 0.0975243 | 682.775ms | 94370 | 30 | 1292.05 | 6729.23 | 0.0599016 | 1(Win) | true |
| Glaze | 2807.52 | 0.215267 | 3229.34ms | 94370 | 1280 | 6.09519e+06 | 32056.1 | 0.0587418 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13807.5 | 0.0653483 | 656.546ms | 94370 | 4890 | 88718.5 | 6518.07 | 0.0706966 | 1(Win) | true |
| Glaze | 2993.78 | 0.282593 | 2872.84ms | 94370 | 2560 | 1.84753e+07 | 30061.7 | 0.985668 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1856.85 | 0.035165 | 2829.38ms | 53331 | 40 | 3710.96 | 27390.6 | 0.062195 | 1(Win) | true |
| Glaze | 1535.37 | 0.15039 | 3352.85ms | 53331 | 640 | 1.58837e+06 | 33125.9 | 0.331952 | 2(Loss) | true |
| Jsonifier (two-stage) | 1494.49 | 0.155376 | 3368.87ms | 53331 | 640 | 1.78946e+06 | 34031.9 | 0.211572 | 3(Loss) | true |
| simdjson (ondemand) | 886.37 | 0.0702105 | 5829.7ms | 53331 | 30 | 48691.6 | 57380.5 | 0.0703576 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2592.53 | 0.0594913 | 2525.18ms | 53331 | 30 | 4086.38 | 19618 | 0.0786073 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1992.33 | 0.140725 | 3069.17ms | 53331 | 40 | 51622.3 | 25528.1 | 0.0532137 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1989.73 | 0.0856371 | 3207.41ms | 53331 | 80 | 38334.1 | 25561.5 | 0.0453035 | 2(Tie) | true |
| simdjson (ondemand) | 1016.2 | 0.0908895 | 5572.02ms | 53331 | 1280 | 2.64873e+06 | 50049.5 | 0.0839743 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14248.8 | 0.26789 | 408.147ms | 58581 | 4890 | 539488 | 3920.84 | 1.08969 | 1(Win) | true |
| Glaze | 4786.97 | 0.0652851 | 1179.27ms | 58581 | 4890 | 283876 | 11670.7 | 0.0685086 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16081.6 | 0.0750045 | 382.242ms | 58581 | 80 | 543.152 | 3473.99 | 0.0571782 | 1(Win) | true |
| Glaze | 6192.19 | 0.0759296 | 914.699ms | 58581 | 30 | 1407.89 | 9022.2 | 0.00110836 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1824.3 | 0.0285287 | 3441.44ms | 65103 | 80 | 7541.63 | 34033.4 | 0.0214449 | 1(Win) | true |
| Jsonifier (two-stage) | 1724.72 | 0.104981 | 3699.27ms | 65103 | 1280 | 1.8281e+06 | 35998.3 | 0.0948795 | 2(Loss) | true |
| Glaze | 1345.67 | 1.17449 | 4166.15ms | 65103 | 80 | 2.34918e+07 | 46138.5 | 0.214058 | 3(Loss) | true |
| simdjson (ondemand) | 1059.51 | 0.0782224 | 5987.93ms | 65103 | 1280 | 2.68947e+06 | 58600 | 0.136674 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2403.57 | 0.0680475 | 3180.19ms | 65103 | 40 | 12358.7 | 25831.2 | 0.077615 | 1(Win) | true |
| Jsonifier (two-stage) | 2254.3 | 0.056606 | 3376.69ms | 65103 | 4890 | 1.18854e+06 | 27541.6 | 0.0328238 | 2(Loss) | true |
| Glaze | 2092.82 | 0.331519 | 3547.03ms | 65103 | 80 | 773832 | 29666.8 | 0.0768788 | 3(Loss) | true |
| simdjson (ondemand) | 1214.52 | 0.10578 | 6375.06ms | 65103 | 640 | 1.87143e+06 | 51120.4 | 0.468242 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12383.2 | 0.461246 | 606.422ms | 78778 | 640 | 501177 | 6066.98 | 0.294172 | 1(Win) | true |
| Glaze | 3598.57 | 0.44955 | 2165.02ms | 78778 | 1280 | 1.1275e+07 | 20877.3 | 0.0314275 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13990.2 | 0.28728 | 546.684ms | 78778 | 1280 | 304638 | 5370.08 | 0.808586 | 1(Win) | true |
| Glaze | 4942.75 | 0.815881 | 1634.84ms | 78778 | 160 | 2.46063e+06 | 15199.7 | 0.176213 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1948.51 | 0.143102 | 573.617ms | 11812 | 4890 | 334690 | 5781.23 | 0.0577467 | 1(Win) | true |
| Jsonifier (two-stage) | 1168.72 | 0.0324194 | 1028.2ms | 11812 | 80 | 781.134 | 9638.58 | 0.00103751 | 2(Loss) | true |
| Glaze | 956.467 | 0.1373 | 1190.48ms | 11812 | 4890 | 1.27867e+06 | 11777.5 | 0.148809 | 3(Loss) | true |
| simdjson (ondemand) | 801.735 | 0.168351 | 1423.36ms | 11812 | 1280 | 716184 | 14050.5 | 0.135069 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2091.93 | 0.433852 | 587.126ms | 11812 | 320 | 174658 | 5384.89 | 0.0190311 | 1(Win) | true |
| Jsonifier (two-stage) | 1256.38 | 0.228932 | 983.621ms | 11812 | 1280 | 539294 | 8966.06 | 0.0510432 | 2(Loss) | true |
| Glaze | 1017.65 | 0.19011 | 1121.32ms | 11812 | 2560 | 1.1337e+06 | 11069.4 | 0.05294 | 3(Loss) | true |
| simdjson (ondemand) | 841.335 | 0.124355 | 1420.74ms | 11812 | 2560 | 709703 | 13389.2 | 2.43295 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 8766.97 | 0.513903 | 121.232ms | 11812 | 640 | 27905.6 | 1284.91 | 5.63854 | -(Win) | false |
| Glaze | 2264.33 | 0.0953462 | 520.67ms | 11812 | 30 | 674.99 | 4974.9 | 0.141845 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8283.63 | 1.0142 | 119.314ms | 11812 | 160 | 30434.8 | 1359.89 | 3.26249 | 1(Win) | true |
| Glaze | 2626.38 | 0.0677467 | 462.42ms | 11812 | 80 | 675.458 | 4289.1 | 0.159453 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2541.42 | 0.445368 | 892.108ms | 25388 | 1280 | 2.30438e+06 | 9526.93 | 0.533407 | 1(Win) | true |
| Jsonifier (two-stage) | 2129.03 | 0.0551532 | 1179.77ms | 25388 | 30 | 1180.2 | 11372.3 | 0.0477542 | 2(Loss) | true |
| Glaze | 1756.4 | 0.760358 | 1414.03ms | 25388 | 80 | 878890 | 13784.9 | 1.17404 | 3(Loss) | true |
| simdjson (ondemand) | 1512.81 | 0.132698 | 1635.31ms | 25388 | 4890 | 2.20561e+06 | 16004.6 | 1.37227 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3036.57 | 0.0325756 | 968.578ms | 25388 | 80 | 539.716 | 7973.43 | 0.0200626 | 1(Win) | true |
| Jsonifier (two-stage) | 2373.86 | 0.168984 | 1148.39ms | 25388 | 2560 | 760466 | 10199.4 | 0.645725 | 2(Loss) | true |
| Glaze | 1877.28 | 0.134867 | 1414.31ms | 25388 | 30 | 9076.7 | 12897.3 | 0.385412 | 3(Loss) | true |
| simdjson (ondemand) | 1657.4 | 0.0924345 | 1521.41ms | 25388 | 40 | 7293.41 | 14608.4 | 0.0375497 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12737.5 | 0.180694 | 238.262ms | 31235 | 4890 | 87320.1 | 2338.61 | 0.104857 | 1(Win) | true |
| Glaze | 3558.11 | 0.0824791 | 879.257ms | 31235 | 40 | 1907.19 | 8371.88 | 0.0949513 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14326.7 | 0.177448 | 216.307ms | 31235 | 30 | 408.372 | 2079.2 | 0.0672883 | 1(Win) | true |
| Glaze | 4202.08 | 0.087757 | 768.654ms | 31235 | 30 | 1161.02 | 7088.87 | 0.0390131 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2719.94 | 0.0682548 | 4021.36ms | 108313 | 2560 | 1.72008e+06 | 37977.1 | 0.0468196 | 1(Win) | true |
| Jsonifier (two-stage) | 1475.35 | 0.330163 | 6897.69ms | 108313 | 1280 | 6.83973e+07 | 70014.2 | 0.136453 | 2(Loss) | true |
| Glaze | 1390.59 | 0.277057 | 7576.24ms | 108313 | 640 | 2.71069e+07 | 74281.6 | 0.368933 | 3(Loss) | true |
| simdjson (ondemand) | 557.766 | 0.173335 | 9502.04ms | 108313 | 2560 | 2.63798e+08 | 185195 | 0.190146 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2650.92 | 0.193054 | 4064.34ms | 108313 | 4890 | 2.76717e+07 | 38965.8 | 2.09644 | 1(Win) | true |
| Jsonifier (two-stage) | 1715.45 | 0.190552 | 6282.43ms | 108313 | 2560 | 3.37036e+07 | 60214.9 | 0.652665 | 2(Loss) | true |
| Glaze | 1598.49 | 0.130908 | 6863.85ms | 108313 | 4890 | 3.49932e+07 | 64620.4 | 1.86864 | 3(Loss) | true |
| simdjson (ondemand) | 612.582 | 0.114401 | 8880.04ms | 108313 | 1280 | 4.76326e+07 | 168623 | 0.201208 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12767.2 | 0.116265 | 811.082ms | 108313 | 4890 | 432687 | 8090.68 | 0.211042 | 1(Win) | true |
| Glaze | 2168.62 | 0.158369 | 4819.5ms | 108313 | 2560 | 1.4567e+07 | 47631.8 | 0.201289 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13527.2 | 0.175911 | 800.254ms | 108313 | 2560 | 461929 | 7636.13 | 0.0262713 | 1(Win) | true |
| Glaze | 2337.78 | 0.163799 | 4447.38ms | 108313 | 2560 | 1.34097e+07 | 44185.3 | 0.249531 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2614.99 | 0.0928299 | 6798.75ms | 183677 | 4890 | 1.89083e+07 | 66986 | 0.246022 | 1(Win) | true |
| Jsonifier (two-stage) | 2317.29 | 0.937553 | 8012.49ms | 183677 | 30 | 1.50682e+07 | 75591.6 | 0.747874 | 2(Loss) | true |
| Glaze | 1779.38 | 0.215688 | 5081.53ms | 183677 | 1280 | 5.77074e+07 | 98443.2 | 0.1004 | 3(Loss) | true |
| simdjson (ondemand) | 973.158 | 0.725332 | 9693.49ms | 183677 | 80 | 1.36366e+08 | 180000 | 0.341697 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2907.37 | 0.150951 | 6527.42ms | 183677 | 1280 | 1.05874e+07 | 60249.6 | 0.511972 | 1(Win) | true |
| Jsonifier (two-stage) | 2426.4 | 0.412476 | 7338.66ms | 183677 | 640 | 5.67495e+07 | 72192.6 | 0.200878 | 2(Loss) | true |
| Glaze | 1915.49 | 0.131238 | 9510.56ms | 183677 | 2560 | 3.6873e+07 | 91448 | 0.346528 | 3(Loss) | true |
| simdjson (ondemand) | 981.65 | 0.255773 | 9670.35ms | 183677 | 1280 | 2.66635e+08 | 178442 | 0.465553 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12736 | 0.395553 | 1574.23ms | 213963 | 2560 | 1.02816e+07 | 16021.6 | 1.41759 | 1(Win) | true |
| Glaze | 2666.87 | 0.886559 | 7768.1ms | 213963 | 160 | 7.36223e+07 | 76513.3 | 0.0827747 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16226.6 | 0.23502 | 1490.2ms | 213963 | 30 | 26203.1 | 12575.1 | 0.067905 | 1(Win) | true |
| Glaze | 3057.55 | 0.469226 | 6697.15ms | 213963 | 640 | 6.27587e+07 | 66736.8 | 1.50764 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 579.667 | 0.416882 | 9492.1ms | 1834197 | 160 | 2.53211e+10 | 3.01764e+06 | 0.329116 | 1(Win) | true |
| Jsonifier (two-stage) | 497.447 | 0.72789 | 5532.39ms | 1834197 | 80 | 5.24108e+10 | 3.51641e+06 | 4.94384 | 2(Loss) | true |
| Glaze | 407.013 | 0.878176 | 6160.81ms | 1834197 | 40 | 5.69767e+10 | 4.29771e+06 | 0.139601 | 3(Loss) | true |
| simdjson (ondemand) | 324.374 | 1.17412 | 7908.63ms | 1834197 | 30 | 1.20266e+11 | 5.39262e+06 | 0.912181 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 641.102 | 0.846826 | 9465.71ms | 1834197 | 30 | 1.60157e+10 | 2.72847e+06 | 1.7058 | 1(Win) | true |
| Jsonifier (two-stage) | 539.692 | 0.720954 | 5350.45ms | 1834197 | 80 | 4.36822e+10 | 3.24115e+06 | 1.21542 | 2(Loss) | true |
| Glaze | 434.348 | 0.76548 | 6479.07ms | 1834197 | 80 | 7.60284e+10 | 4.02725e+06 | 4.65772 | 3(Loss) | true |
| simdjson (ondemand) | 338.385 | 0.648491 | 8100.5ms | 1834197 | 30 | 3.37132e+10 | 5.16934e+06 | 0.0900097 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1197.3 | 0.775143 | 8520.23ms | 1834197 | 80 | 1.02598e+10 | 1.46097e+06 | 2.82721 | 1(Win) | true |
| Glaze | 766.031 | 0.575134 | 7141.63ms | 1833577 | 160 | 2.7578e+10 | 2.28272e+06 | 0.988823 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1324.02 | 0.582009 | 8628.42ms | 1834197 | 320 | 1.89197e+10 | 1.32115e+06 | 1.30896 | 1(Win) | true |
| Glaze | 786.756 | 1.16875 | 7255.42ms | 1833577 | 40 | 2.69911e+10 | 2.22259e+06 | 1.51627 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1843.56 | 0.264313 | 5667.34ms | 7351818 | 80 | 8.08351e+09 | 3.80309e+06 | 3.50919 | 1(Win) | true |
| Jsonifier | 1691.9 | 0.621599 | 6145.34ms | 7351818 | 80 | 5.30827e+10 | 4.14401e+06 | 1.62171 | 2(Loss) | true |
| Glaze | 1347.25 | 1.39537 | 8281.8ms | 7351818 | 40 | 2.10927e+11 | 5.20412e+06 | 0.317642 | 3(Loss) | true |
| simdjson (ondemand) | 1179.39 | 0.435297 | 8843ms | 7351818 | 40 | 2.67858e+10 | 5.94479e+06 | 3.3599 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2010.98 | 0.28749 | 5787.93ms | 7351818 | 80 | 8.03726e+09 | 3.48647e+06 | 0.176919 | 1(Win) | true |
| Jsonifier | 1914.64 | 1.87543 | 5786.56ms | 7351818 | 30 | 1.41494e+11 | 3.6619e+06 | 1.37846 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1466.12 | 1.74269 | 8047.88ms | 7351818 | 40 | 2.77811e+11 | 4.78217e+06 | 1.9489 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1416.31 | 0.841623 | 8287.97ms | 7351818 | 40 | 6.94337e+10 | 4.95037e+06 | 3.51543 | 3(Tie) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5197.62 | 0.789296 | 5653.87ms | 9930848 | 30 | 6.20533e+09 | 1.82214e+06 | 2.25023 | 1(Win) | true |
| Glaze | 2859.26 | 0.921649 | 5017.6ms | 9930228 | 30 | 2.79552e+10 | 3.31212e+06 | 0.0276665 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5584.9 | 0.093685 | 5263.82ms | 9930848 | 80 | 2.01917e+08 | 1.69579e+06 | 0.12805 | 1(Win) | true |
| Glaze | 2876.45 | 1.53471 | 9675.5ms | 9930228 | 30 | 7.65909e+10 | 3.29232e+06 | 0.72885 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 612.776 | 2.53371 | 8624.98ms | 1834197 | 30 | 1.56936e+11 | 2.85459e+06 | 0.00394553 | 1(Win) | true |
| Jsonifier (two-stage) | 509.9 | 0.560019 | 10415.8ms | 1834197 | 40 | 1.47635e+10 | 3.43053e+06 | 0.666764 | 2(Loss) | true |
| Glaze | 490.178 | 0.28728 | 5467.09ms | 1834197 | 80 | 8.40784e+09 | 3.56856e+06 | 1.35523 | 3(Loss) | true |
| simdjson (ondemand) | 386.099 | 0.761347 | 6418.11ms | 1834197 | 80 | 9.51808e+10 | 4.53051e+06 | 0.427124 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 675.553 | 0.715061 | 8936.37ms | 1834197 | 40 | 1.37126e+10 | 2.58933e+06 | 1.17574 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 670.737 | 0.559677 | 9837.28ms | 1834197 | 160 | 3.40865e+10 | 2.60792e+06 | 4.8781 | 1(Tie) | true |
| Glaze | 542.126 | 0.185041 | 5358ms | 1834197 | 40 | 1.4259e+09 | 3.22661e+06 | 0.330575 | 3(Loss) | true |
| simdjson (ondemand) | 429.931 | 0.773715 | 6623.63ms | 1834197 | 80 | 7.92767e+10 | 4.06862e+06 | 3.26778 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1487.27 | 0.140091 | 7618.67ms | 1834197 | 160 | 4.34364e+08 | 1.17614e+06 | 1.44019 | 1(Win) | true |
| Glaze | 860.878 | 0.772148 | 6328.85ms | 1833577 | 30 | 7.37968e+09 | 2.03122e+06 | 3.62345 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1482.5 | 0.343031 | 7895.72ms | 1834197 | 80 | 1.31056e+09 | 1.17991e+06 | 0.0255642 | 1(Win) | true |
| Glaze | 880.327 | 0.490883 | 6222.06ms | 1833577 | 30 | 2.85225e+09 | 1.98635e+06 | 1.42467 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2066.06 | 0.0804958 | 5382.88ms | 7351818 | 80 | 5.96953e+08 | 3.39353e+06 | 0.380841 | 1(Win) | true |
| Jsonifier | 2048.31 | 0.191352 | 5247.38ms | 7351818 | 80 | 3.43203e+09 | 3.42293e+06 | 0.959594 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1477.69 | 0.445416 | 7346.94ms | 7351818 | 40 | 1.78655e+10 | 4.74472e+06 | 0.40894 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1471.98 | 0.0533206 | 7264.44ms | 7351818 | 80 | 5.16016e+08 | 4.76312e+06 | 0.126496 | 3(Tie) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2387.55 | 0.306718 | 5059.66ms | 7351818 | 40 | 3.24507e+09 | 2.93659e+06 | 2.58829 | 1(Win) | true |
| Jsonifier (two-stage) | 2268.66 | 0.284661 | 5260.91ms | 7351818 | 80 | 6.1915e+09 | 3.09047e+06 | 0.22981 | 2(Loss) | true |
| simdjson (ondemand) | 1574.1 | 0.399451 | 7237.68ms | 7351818 | 30 | 9.49675e+09 | 4.45414e+06 | 0.111448 | 3(Loss) | true |
| Glaze | 1558.26 | 0.0404924 | 7358.4ms | 7351818 | 40 | 1.32775e+08 | 4.4994e+06 | 1.61969 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5525.31 | 0.48621 | 5435.01ms | 9930848 | 40 | 2.77822e+09 | 1.71408e+06 | 0.328106 | 1(Win) | true |
| Glaze | 3008.16 | 0.0365606 | 9856.14ms | 9930228 | 160 | 2.11964e+08 | 3.14817e+06 | 0.0499142 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5544.2 | 0.126578 | 5392.76ms | 9930848 | 80 | 3.74024e+08 | 1.70823e+06 | 0.537197 | 1(Win) | true |
| Glaze | 3461.4 | 0.103846 | 8611.8ms | 9930228 | 160 | 1.29157e+09 | 2.73595e+06 | 0.142615 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1285.46 | 0.0438598 | 8937.6ms | 461466 | 1280 | 2.88606e+07 | 342359 | 0.0208161 | 1(Win) | true |
| Jsonifier (two-stage) | 994.558 | 0.0718658 | 5649.49ms | 461466 | 640 | 6.47208e+07 | 442496 | 0.0434592 | 2(Loss) | true |
| Glaze | 868.16 | 0.183099 | 6510.7ms | 461466 | 30 | 2.58447e+07 | 506921 | 0.303675 | 3(Loss) | true |
| simdjson (ondemand) | 665.162 | 0.134806 | 8576.15ms | 461466 | 80 | 6.36401e+07 | 661626 | 0.102853 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1731.93 | 0.141495 | 8652.99ms | 461466 | 80 | 1.03418e+07 | 254103 | 0.123262 | 1(Win) | true |
| Jsonifier (two-stage) | 1355.48 | 0.0880978 | 5522.83ms | 461466 | 320 | 2.61802e+07 | 324673 | 0.0468999 | 2(Loss) | true |
| Glaze | 1040.93 | 0.456065 | 6428.47ms | 461466 | 40 | 1.48715e+08 | 422786 | 0.189296 | 3(Loss) | true |
| simdjson (ondemand) | 751.858 | 0.219053 | 8366.74ms | 461466 | 320 | 5.26085e+08 | 585334 | 0.300165 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9709.53 | 0.172033 | 4569.59ms | 461466 | 4890 | 2.97315e+07 | 45325.4 | 0.524295 | 1(Win) | true |
| Glaze | 2778.82 | 0.18132 | 8560.68ms | 461466 | 320 | 2.63877e+07 | 158372 | 0.0134768 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9233.99 | 0.608001 | 4421.43ms | 461466 | 320 | 2.68695e+07 | 47659.6 | 2.29561 | 1(Win) | true |
| Glaze | 3004.27 | 0.174785 | 7616.3ms | 461466 | 80 | 5.24446e+06 | 146487 | 0.0128493 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1616.31 | 0.0937108 | 5597.13ms | 728486 | 160 | 2.59594e+07 | 429831 | 0.0662351 | 1(Win) | true |
| Jsonifier (two-stage) | 1239.76 | 0.0893633 | 7198.26ms | 728486 | 640 | 1.60496e+08 | 560381 | 0.283319 | 2(Loss) | true |
| Glaze | 1105.27 | 0.583203 | 7415.83ms | 728486 | 40 | 5.37531e+08 | 628568 | 0.420969 | 3(Loss) | true |
| simdjson (ondemand) | 1001.57 | 0.110699 | 9081.54ms | 728486 | 320 | 1.88679e+08 | 693652 | 0.0984982 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2038.9 | 0.185327 | 5489.36ms | 728486 | 30 | 1.19632e+07 | 340742 | 0.229231 | 1(Win) | true |
| Jsonifier (two-stage) | 1787.45 | 0.223868 | 7357.56ms | 728486 | 30 | 2.27134e+07 | 388676 | 0.0603994 | 2(Loss) | true |
| Glaze | 1432.21 | 0.0701937 | 7328.25ms | 728486 | 320 | 3.70999e+07 | 485080 | 0.0953552 | 3(Loss) | true |
| simdjson (ondemand) | 1143.98 | 0.165743 | 8828.04ms | 728486 | 80 | 8.10523e+07 | 607298 | 0.0173071 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11701.5 | 0.241952 | 7058.22ms | 837491 | 80 | 2.18185e+06 | 68255.7 | 0.480795 | 1(Win) | true |
| Glaze | 3267.57 | 0.0659292 | 6292.16ms | 837491 | 1280 | 3.32412e+07 | 244431 | 0.00359554 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13702.5 | 0.0852356 | 5907.69ms | 837491 | 1280 | 3.15947e+06 | 58288.2 | 0.00577042 | 1(Win) | true |
| Glaze | 3602.38 | 0.0835535 | 5815.77ms | 837491 | 320 | 1.09815e+07 | 221713 | 0.0380162 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 4984.29 | 0.0731647 | 9117.64ms | 466906 | 1280 | 5.46847e+06 | 89336 | 0.0119767 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 4975.97 | 0.0926702 | 9154.83ms | 466906 | 640 | 4.40113e+06 | 89485.4 | 0.0771144 | 1(Tie) | true |
| simdjson (ondemand) | 4063.23 | 0.202455 | 5633.15ms | 466906 | 160 | 7.87573e+06 | 109587 | 0.163524 | 3(Loss) | true |
| Glaze | 2280.63 | 0.15869 | 5093.16ms | 466906 | 320 | 3.07184e+07 | 195243 | 0.0293999 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5110.2 | 0.0981782 | 8970.16ms | 466906 | 640 | 4.68374e+06 | 87134.8 | 0.132022 | 1(Win) | true |
| Jsonifier (two-stage) | 5092.1 | 0.109832 | 9008.78ms | 466906 | 640 | 5.90344e+06 | 87444.5 | 0.0141896 | 2(Loss) | true |
| simdjson (ondemand) | 4131.79 | 0.0509383 | 5680.66ms | 466906 | 2560 | 7.71454e+06 | 107768 | 0.00608149 | 3(Loss) | true |
| Glaze | 2304.54 | 0.0767007 | 5056.36ms | 466906 | 640 | 1.40562e+07 | 193217 | 0.061711 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 5415.46 | 0.114867 | 5752.56ms | 631514 | 320 | 5.22194e+06 | 111211 | 0.0351258 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 5393.99 | 0.203976 | 5757.01ms | 631514 | 160 | 8.29895e+06 | 111654 | 0.0638565 | 1(Tie) | true |
| simdjson (ondemand) | 4818.13 | 0.156164 | 6617.63ms | 631514 | 80 | 3.04834e+06 | 124998 | 0.010589 | 3(Loss) | true |
| Glaze | 2763.69 | 0.083845 | 5637.58ms | 631514 | 640 | 2.1366e+07 | 217919 | 0.106577 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 5528.72 | 0.195378 | 5764.66ms | 631514 | 80 | 3.62376e+06 | 108933 | 0.0167277 | 1(Win) | true |
| Jsonifier | 5480.84 | 0.273091 | 5947.17ms | 631514 | 40 | 3.60204e+06 | 109884 | 0.562046 | 2(Loss) | true |
| simdjson (ondemand) | 4890.96 | 0.0840818 | 6502.14ms | 631514 | 640 | 6.8606e+06 | 123137 | 0.00215964 | 3(Loss) | true |
| Glaze | 2794.72 | 0.0650638 | 5572.23ms | 631514 | 1280 | 2.5164e+07 | 215499 | 0.0432671 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2313.23 | 0.185102 | 9885.3ms | 466906 | 80 | 1.01563e+07 | 192491 | 0.0115901 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1772.66 | 0.0972033 | 6430.04ms | 466906 | 320 | 1.90775e+07 | 251191 | 0.242178 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1763.88 | 0.329878 | 6558.61ms | 466906 | 30 | 2.08042e+07 | 252442 | 0.149382 | 2(Tie) | true |
| simdjson (ondemand) | 844.895 | 0.0663918 | 6764.28ms | 466906 | 320 | 3.91771e+07 | 527020 | 0.0793529 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2962.06 | 0.110073 | 9217.15ms | 466906 | 320 | 8.76164e+06 | 150327 | 0.14136 | 1(Win) | true |
| Jsonifier (two-stage) | 2207.25 | 0.11064 | 6111.84ms | 466906 | 1280 | 6.37658e+07 | 201733 | 0.291933 | 2(Loss) | true |
| Glaze | 2119.57 | 0.094026 | 6145.19ms | 466906 | 640 | 2.49713e+07 | 210079 | 0.183475 | 3(Loss) | true |
| simdjson (ondemand) | 910.882 | 0.0690258 | 6572.91ms | 466906 | 320 | 3.64341e+07 | 488841 | 0.0887825 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15473.3 | 0.0833887 | 2987.55ms | 475954 | 2560 | 1.53185e+06 | 29334.7 | 0.00294678 | 1(Win) | true |
| Glaze | 4538.4 | 0.0964206 | 5246ms | 475954 | 320 | 2.97587e+06 | 100014 | 0.0221486 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15593 | 0.0569002 | 2922.67ms | 475954 | 4890 | 1.34156e+06 | 29109.6 | 0.0436427 | 1(Win) | true |
| Glaze | 5040.98 | 0.0747368 | 9155.69ms | 475954 | 1280 | 5.79668e+06 | 90043.1 | 0.00878215 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2248.18 | 0.334517 | 8068.53ms | 631514 | 30 | 2.40914e+07 | 267888 | 0.370927 | 1(Win) | true |
| Glaze | 1979.98 | 0.117226 | 7920.33ms | 631514 | 160 | 2.03427e+07 | 304174 | 0.0186474 | 2(Loss) | true |
| Jsonifier (two-stage) | 1749.3 | 1.11972 | 8314.63ms | 631514 | 40 | 5.94451e+08 | 344286 | 0.227058 | 3(Loss) | true |
| simdjson (ondemand) | 982.861 | 0.296026 | 7809.63ms | 631514 | 640 | 2.10582e+09 | 612761 | 0.628313 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Glaze STATISTICAL TIE | 2292.71 | 0.291277 | 7772.68ms | 631514 | 30 | 1.75632e+07 | 262685 | 0.0402291 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 2287.98 | 1.12931 | 7850.01ms | 631514 | 160 | 1.41387e+09 | 263228 | 3.32843 | 1(Tie) | true |
| Jsonifier (two-stage) | 2196.58 | 0.470643 | 8064.36ms | 631514 | 640 | 1.0657e+09 | 274181 | 0.321035 | 3(Loss) | true |
| simdjson (ondemand) | 1061.46 | 0.316728 | 7706.27ms | 631514 | 640 | 2.06684e+09 | 567385 | 0.156196 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14026.4 | 0.311104 | 4896.8ms | 716365 | 1280 | 2.93897e+07 | 48706.6 | 1.87284 | 1(Win) | true |
| Glaze | 3933.27 | 0.220558 | 9393.43ms | 716365 | 160 | 2.34814e+07 | 173692 | 1.3501 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14336.9 | 0.155822 | 4901.89ms | 716365 | 4890 | 2.69605e+07 | 47651.9 | 0.222544 | 1(Win) | true |
| Glaze | 4218.83 | 0.285318 | 8096.92ms | 716365 | 640 | 1.36622e+08 | 161935 | 2.40639 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1385.76 | 0.755656 | 174.697ms | 2632 | 320 | 59950.7 | 1811.33 | 0.266396 | 1(Win) | true |
| Jsonifier (two-stage) | 1253.06 | 0.251491 | 210.995ms | 2632 | 40 | 1015.16 | 2003.15 | 0.0540523 | 2(Loss) | true |
| Glaze | 1077.11 | 0.465786 | 237.86ms | 2632 | 2560 | 301625 | 2330.38 | 0.674393 | 3(Loss) | true |
| simdjson (ondemand) | 857.528 | 0.202365 | 303.162ms | 2632 | 40 | 1403.48 | 2927.1 | 0.685373 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2040.21 | 0.296013 | 157.287ms | 2632 | 40 | 530.523 | 1230.3 | 0.323457 | 1(Win) | true |
| Jsonifier (two-stage) | 1618.27 | 0.135163 | 187.446ms | 2632 | 80 | 351.625 | 1551.09 | 0.60158 | 2(Loss) | true |
| Glaze | 1591.16 | 0.29952 | 190.486ms | 2632 | 1280 | 28576.1 | 1577.51 | 0.942688 | 3(Loss) | true |
| simdjson (ondemand) | 1178.33 | 0.143659 | 249.961ms | 2632 | 160 | 1498.38 | 2130.19 | 0.218399 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8309.19 | 0.269394 | 34.0228ms | 2632 | 1280 | 847.695 | 302.084 | 0.325626 | 1(Win) | true |
| Glaze | 2873.14 | 0.278574 | 95.048ms | 2632 | 30 | 177.689 | 873.633 | 1.40321 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9223.12 | 0.802556 | 30.5028ms | 2632 | 160 | 763.286 | 272.15 | 0.675113 | 1(Win) | true |
| Glaze | 3095.17 | 1.03432 | 73.9496ms | 2632 | 160 | 11257.2 | 810.962 | 0.126233 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1560.34 | 0.26812 | 227.171ms | 3370 | 30 | 914.961 | 2059.73 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 1526.45 | 0.264735 | 229.861ms | 3370 | 30 | 932.051 | 2105.47 | 0.534793 | 2(Loss) | true |
| Glaze | 1159.32 | 0.318671 | 274.933ms | 3370 | 2560 | 199792 | 2772.21 | 0.739685 | 3(Loss) | true |
| simdjson (ondemand) | 1079.07 | 0.213983 | 309.268ms | 3370 | 2560 | 103983 | 2978.39 | 0.317533 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1968.87 | 0.238866 | 202.995ms | 3370 | 40 | 608.131 | 1632.35 | 0.143757 | 1(Win) | true |
| Jsonifier (two-stage) | 1882.33 | 0.16377 | 205.72ms | 3370 | 4890 | 38233.4 | 1707.39 | 0.605389 | 2(Loss) | true |
| Glaze | 1772.41 | 0.565048 | 213.656ms | 3370 | 320 | 33593.2 | 1813.28 | 0.201352 | 3(Loss) | true |
| simdjson (ondemand) | 1405.59 | 0.21831 | 261.327ms | 3370 | 40 | 996.667 | 2286.5 | 0.0437158 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9115.81 | 0.237468 | 42.346ms | 3643 | 320 | 262.114 | 381.122 | 0.104242 | 1(Win) | true |
| Glaze | 3041.65 | 0.18271 | 123.591ms | 3682 | 160 | 711.859 | 1154.45 | 0.162679 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10216.6 | 0.136679 | 38.2009ms | 3643 | 1280 | 276.514 | 340.057 | 0.363156 | 1(Win) | true |
| Glaze | 3588.17 | 0.196246 | 104.617ms | 3682 | 160 | 590.126 | 978.612 | 0.32339 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 728.168 | 0.12217 | 637.167ms | 4630 | 30 | 1646.46 | 6063.87 | 0.277379 | 1(Win) | true |
| Jsonifier (two-stage) | 634.205 | 0.209914 | 696.905ms | 4630 | 4890 | 1.04447e+06 | 6962.28 | 0.677202 | 2(Loss) | true |
| Glaze | 447.904 | 0.220802 | 1005.65ms | 4630 | 1280 | 606471 | 9858.16 | 0.433901 | 3(Loss) | true |
| simdjson (ondemand) | 432.539 | 0.848806 | 1102.6ms | 4630 | 30 | 225243 | 10208.4 | 0.823706 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 905.748 | 0.0819268 | 652.087ms | 4630 | 80 | 1276.11 | 4874.99 | 0.000256412 | 1(Win) | true |
| Jsonifier (two-stage) | 756.201 | 0.586293 | 703.973ms | 4630 | 320 | 375031 | 5839.07 | 1.56332 | 2(Loss) | true |
| Glaze | 513.122 | 0.410144 | 991.56ms | 4630 | 160 | 199303 | 8605.19 | 0.347067 | 3(Loss) | true |
| simdjson (ondemand) | 475.052 | 0.467427 | 1059.04ms | 4630 | 320 | 604029 | 9294.8 | 0.0950695 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2505.88 | 0.318091 | 189.795ms | 4630 | 80 | 2513.25 | 1762.06 | 0.321737 | 1(Win) | true |
| Glaze | 1501.54 | 0.0602253 | 303.876ms | 4630 | 320 | 1003.68 | 2940.65 | 0.0630572 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2589.52 | 0.342744 | 178.768ms | 4630 | 40 | 1366.23 | 1705.15 | 0.0224759 | 1(Win) | true |
| Glaze | 1753.81 | 0.228441 | 263.774ms | 4630 | 40 | 1323.15 | 2517.68 | 0.0142307 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1473.39 | 0.114674 | 768.632ms | 11579 | 40 | 2954.57 | 7494.7 | 0.0783389 | 1(Win) | true |
| Jsonifier (two-stage) | 1392.93 | 0.216356 | 806.686ms | 11579 | 4890 | 1.43857e+06 | 7927.61 | 0.832809 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 975.671 | 0.133803 | 1145.24ms | 11579 | 4890 | 1.12145e+06 | 11318 | 0.704448 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 973.455 | 0.636718 | 1143.47ms | 11579 | 160 | 834688 | 11343.7 | 0.626031 | 3(Tie) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1738.56 | 0.209924 | 764.488ms | 11579 | 320 | 56889.9 | 6351.57 | 0.366603 | 1(Win) | true |
| Jsonifier (two-stage) | 1696.71 | 0.0862307 | 823.217ms | 11579 | 40 | 1259.82 | 6508.23 | 0.150991 | 2(Loss) | true |
| simdjson (ondemand) | 1125.24 | 0.999674 | 1126.04ms | 11579 | 40 | 384970 | 9813.52 | 0.748167 | 3(Loss) | true |
| Glaze | 1049.67 | 0.205975 | 1146.41ms | 11579 | 4890 | 2.29601e+06 | 10520 | 1.67308 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6626.91 | 0.188737 | 224.179ms | 14795 | 80 | 1291.84 | 2129.14 | 0.0464018 | 1(Win) | true |
| Glaze | 3131.14 | 0.113006 | 464.195ms | 14795 | 40 | 1037.26 | 4506.23 | 0.0171955 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6648.58 | 0.130323 | 225.027ms | 14795 | 30 | 229.476 | 2122.2 | 0.0628674 | 1(Win) | true |
| Glaze | 3700.14 | 0.172435 | 406.421ms | 14795 | 640 | 27671 | 3813.27 | 0.355615 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1168.82 | 0.280779 | 273.009ms | 3223 | 640 | 34892.6 | 2629.73 | 1.625 | 1(Win) | true |
| Jsonifier (two-stage) | 863.711 | 0.244404 | 362.366ms | 3223 | 2560 | 193660 | 3558.7 | 0.219018 | 2(Loss) | true |
| Glaze | 840.874 | 0.0840398 | 419.941ms | 3223 | 320 | 3019.81 | 3655.36 | 0.325064 | 3(Loss) | true |
| simdjson (ondemand) | 615.241 | 0.293352 | 509.165ms | 3223 | 2560 | 549853 | 4995.91 | 0.486506 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1814.07 | 0.215237 | 231.543ms | 3223 | 30 | 398.999 | 1694.37 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 1278.28 | 0.35446 | 311.013ms | 3223 | 320 | 23246.4 | 2404.56 | 0.266087 | 2(Loss) | true |
| Glaze | 941.832 | 0.564347 | 369.857ms | 3223 | 640 | 217093 | 3263.53 | 0.454581 | 3(Loss) | true |
| simdjson (ondemand) | 744.763 | 0.745102 | 460.413ms | 3223 | 320 | 302598 | 4127.07 | 0.000530034 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7293.52 | 0.133157 | 45.934ms | 3223 | 4890 | 1539.87 | 421.428 | 0.253476 | 1(Win) | true |
| Glaze | 1803.66 | 0.2445 | 171.554ms | 3223 | 80 | 1388.85 | 1704.14 | 0.5554 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8744.5 | 1.08583 | 39.0356ms | 3223 | 30 | 437.017 | 351.5 | 0.368481 | 1(Win) | true |
| Glaze | 2093.8 | 0.261267 | 159.001ms | 3223 | 30 | 441.31 | 1468 | 0.270941 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1575.14 | 0.125318 | 360.723ms | 5839 | 4890 | 95978.6 | 3535.24 | 0.16295 | 1(Win) | true |
| Jsonifier (two-stage) | 1525.29 | 0.0762268 | 387.402ms | 5839 | 160 | 1239.1 | 3650.78 | 0.00599223 | 2(Loss) | true |
| Glaze | 1230.61 | 0.0921216 | 478.25ms | 5839 | 160 | 2780.23 | 4525.01 | 0.114911 | 3(Loss) | true |
| simdjson (ondemand) | 1125.67 | 0.0970031 | 503.485ms | 5839 | 160 | 3684.23 | 4946.84 | 0.169014 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2161.09 | 0.0720946 | 315.366ms | 5839 | 320 | 1104.3 | 2576.71 | 0.0740349 | 1(Win) | true |
| Jsonifier (two-stage) | 2090.63 | 0.114021 | 346.681ms | 5839 | 80 | 737.871 | 2663.55 | 0.00375453 | 2(Loss) | true |
| Glaze | 1468.76 | 0.246371 | 432.994ms | 5839 | 1280 | 111678 | 3791.31 | 0.0116 | 3(Loss) | true |
| simdjson (ondemand) | 1414.6 | 0.165085 | 448.38ms | 5839 | 80 | 3378.43 | 3936.45 | 0.105536 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11633.3 | 0.506497 | 61.0403ms | 6938 | 80 | 663.905 | 568.763 | 0.0065937 | 1(Win) | true |
| Glaze | 2770.39 | 0.247106 | 255.56ms | 6960 | 30 | 1051.54 | 2395.9 | 0.399085 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12777.3 | 0.187738 | 56.8813ms | 6938 | 640 | 604.89 | 517.839 | 0.0509672 | 1(Win) | true |
| Glaze | 2995.09 | 0.203359 | 234.107ms | 6960 | 80 | 1624.86 | 2216.15 | 0.262402 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2065.5 | 0.12374 | 250.706ms | 4857 | 320 | 2464.06 | 2242.55 | 0.318928 | 1(Win) | true |
| Glaze | 1247.65 | 0.248121 | 372.183ms | 4857 | 4890 | 414941 | 3712.58 | 1.40064 | 2(Loss) | true |
| Jsonifier (two-stage) | 1137.43 | 0.242051 | 407.098ms | 4857 | 2560 | 248736 | 4072.33 | 0.115633 | 3(Loss) | true |
| simdjson (ondemand) | 623.202 | 0.0881555 | 783.927ms | 4857 | 160 | 6869.08 | 7432.58 | 0.0249807 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2375.98 | 0.533799 | 220.728ms | 4857 | 1280 | 138617 | 1949.51 | 0.0976454 | 1(Win) | true |
| Glaze | 1795.95 | 0.358768 | 294.408ms | 4857 | 30 | 2568.6 | 2579.13 | 0.427251 | 2(Loss) | true |
| Jsonifier (two-stage) | 1597.66 | 0.0501124 | 352.992ms | 4857 | 320 | 675.475 | 2899.24 | 0.269065 | 3(Loss) | true |
| simdjson (ondemand) | 681.594 | 0.150328 | 708.786ms | 4857 | 40 | 4174.71 | 6795.82 | 0.123086 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10657.5 | 0.395138 | 47.799ms | 4857 | 160 | 471.896 | 434.625 | 0.0603604 | 1(Win) | true |
| Glaze | 2901.01 | 0.133862 | 163.953ms | 4857 | 4890 | 22338.9 | 1596.68 | 0.379802 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12343.1 | 0.288057 | 41.3306ms | 4857 | 160 | 186.965 | 375.269 | 0.0750025 | 1(Win) | true |
| Glaze | 3719.81 | 0.206267 | 128.329ms | 4857 | 80 | 527.772 | 1245.22 | 0.0481609 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2019.58 | 0.0794428 | 333.827ms | 6701 | 160 | 1011.08 | 3164.31 | 0.0444213 | 1(Win) | true |
| Jsonifier (two-stage) | 1536.03 | 0.104893 | 431.436ms | 6701 | 40 | 761.792 | 4160.45 | 0.0180301 | 2(Loss) | true |
| Glaze | 1504.58 | 0.218413 | 428.915ms | 6701 | 80 | 6884.88 | 4247.41 | 0.0367736 | 3(Loss) | true |
| simdjson (ondemand) | 801.433 | 0.258119 | 801.049ms | 6701 | 4890 | 2.07155e+06 | 7973.93 | 0.127709 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2322.52 | 0.0709264 | 302.114ms | 6701 | 160 | 609.391 | 2751.57 | 0.0365834 | 1(Win) | true |
| Jsonifier (two-stage) | 2002.26 | 0.146191 | 385.554ms | 6701 | 40 | 870.84 | 3191.68 | 0.000783282 | 2(Loss) | true |
| Glaze | 1939.22 | 0.204193 | 347.804ms | 6701 | 2560 | 115917 | 3295.44 | 0.24858 | 3(Loss) | true |
| simdjson (ondemand) | 924.911 | 0.0938807 | 784.575ms | 6701 | 160 | 6732.11 | 6909.39 | 0.045792 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12230.6 | 0.229718 | 61.5877ms | 7376 | 320 | 558.585 | 575.141 | 0.0244565 | 1(Win) | true |
| Glaze | 2893.26 | 0.315714 | 264.612ms | 7376 | 40 | 2356.77 | 2431.28 | 0.662798 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13221.6 | 0.165176 | 57.8518ms | 7376 | 640 | 494.249 | 532.031 | 0.0787698 | 1(Win) | true |
| Glaze | 3413.22 | 0.15241 | 222.426ms | 7376 | 80 | 789.281 | 2060.9 | 0.428791 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1400 | 0.325345 | 119.17ms | 1691 | 2560 | 35955 | 1151.9 | 0.538345 | 1(Win) | true |
| Glaze | 1263.29 | 0.209983 | 132.214ms | 1691 | 160 | 1149.66 | 1276.56 | 0.0768079 | 2(Loss) | true |
| Jsonifier (two-stage) | 1164.58 | 0.0817285 | 143.387ms | 1691 | 320 | 409.87 | 1384.76 | 0.443275 | 3(Loss) | true |
| simdjson (ondemand) | 941.701 | 0.674197 | 173.42ms | 1691 | 40 | 5332.05 | 1712.5 | 0.642079 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2302.17 | 0.156686 | 92.766ms | 1691 | 320 | 385.498 | 700.497 | 0.199904 | 1(Win) | true |
| Jsonifier (two-stage) | 1706.26 | 0.138844 | 120.901ms | 1691 | 4890 | 8420.89 | 945.144 | 0.329709 | 2(Loss) | true |
| Glaze | 1630.65 | 0.238799 | 116.6ms | 1691 | 4890 | 27273.5 | 988.97 | 0.125049 | 3(Loss) | true |
| simdjson (ondemand) | 1256.65 | 0.331993 | 154.897ms | 1691 | 40 | 726.062 | 1283.3 | 0.658875 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10520.5 | 0.458635 | 21.9258ms | 1996 | 640 | 440.72 | 180.936 | 0.245512 | 1(Win) | true |
| Glaze | 3298.88 | 0.171199 | 61.2375ms | 1996 | 640 | 624.56 | 577.025 | 0.648101 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12608.4 | 0.53613 | 20.6565ms | 1996 | 640 | 419.297 | 150.973 | 1.40309 | 1(Win) | true |
| Glaze | 4614.63 | 0.574694 | 44.2436ms | 1996 | 160 | 899.17 | 412.5 | 0.118322 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1535.18 | 0.122079 | 139.529ms | 2158 | 160 | 428.535 | 1340.58 | 0.779958 | 1(Win) | true |
| Jsonifier (two-stage) | 1413.99 | 0.188418 | 154.711ms | 2158 | 160 | 1203.31 | 1455.48 | 0.449024 | 2(Loss) | true |
| Glaze | 1334.01 | 0.372547 | 166.495ms | 2158 | 1280 | 42282.4 | 1542.74 | 4.0436 | 3(Loss) | true |
| simdjson (ondemand) | 1214.64 | 0.167263 | 177.975ms | 2158 | 160 | 1285.07 | 1694.36 | 0.0556686 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2299.96 | 0.193673 | 109.755ms | 2158 | 160 | 480.531 | 894.812 | 0.113024 | 1(Win) | true |
| Jsonifier (two-stage) | 1923.75 | 0.408444 | 130.725ms | 2158 | 80 | 1527.43 | 1069.8 | 0.286613 | 2(Loss) | true |
| Glaze | 1819.21 | 0.234207 | 132.439ms | 2158 | 320 | 2246.39 | 1131.28 | 0.0220941 | 3(Loss) | true |
| simdjson (ondemand) | 1483.13 | 0.119404 | 156.462ms | 2158 | 320 | 878.485 | 1387.63 | 0.420036 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10251.2 | 1.223 | 34.501ms | 2866 | 40 | 425.317 | 266.625 | 1.04231 | 1(Win) | true |
| Glaze | 2968.26 | 0.175945 | 96.3993ms | 2866 | 160 | 419.973 | 920.819 | 0.179544 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13809.6 | 0.166154 | 22.9827ms | 2866 | 4890 | 528.833 | 197.922 | 0.965467 | 1(Win) | true |
| Glaze | 3643.3 | 0.600854 | 77.9663ms | 2866 | 2560 | 52016.4 | 750.208 | 0.915343 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2020.67 | 0.216171 | 218.509ms | 4390 | 40 | 802.4 | 2071.9 | 0.319566 | 1(Win) | true |
| Jsonifier (two-stage) | 1135.51 | 0.0778895 | 389.543ms | 4390 | 80 | 659.772 | 3687 | 0.0434146 | 2(Loss) | true |
| Glaze | 949.611 | 0.262096 | 464.907ms | 4390 | 4890 | 652929 | 4408.78 | 0.152881 | 3(Loss) | true |
| simdjson (ondemand) | 768.474 | 0.18232 | 554.926ms | 4390 | 1280 | 126284 | 5447.98 | 0.026207 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2185.2 | 0.218878 | 207.606ms | 4390 | 640 | 11254.7 | 1915.9 | 0.015824 | 1(Win) | true |
| Jsonifier (two-stage) | 1296.92 | 0.130625 | 374.161ms | 4390 | 40 | 711.24 | 3228.12 | 0.0111016 | 2(Loss) | true |
| Glaze | 1033.47 | 0.153213 | 436.176ms | 4390 | 80 | 3081.87 | 4051.05 | 0.383608 | 3(Loss) | true |
| simdjson (ondemand) | 829.032 | 0.191596 | 528.678ms | 4390 | 40 | 3744.74 | 5050.02 | 0.438496 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8519.86 | 0.321259 | 53.7421ms | 4390 | 320 | 797.488 | 491.397 | 0.0438993 | 1(Win) | true |
| Glaze | 2125.42 | 0.1676 | 201.592ms | 4390 | 80 | 871.916 | 1969.79 | 0.321964 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9509.31 | 0.86972 | 48.6058ms | 4390 | 30 | 439.857 | 440.267 | 0.0075706 | 1(Win) | true |
| Glaze | 2517.47 | 0.0978246 | 172.695ms | 4390 | 160 | 423.464 | 1663.03 | 0.00263067 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2575.07 | 0.0952745 | 356.895ms | 9378 | 160 | 1751.93 | 3473.14 | 0.140884 | 1(Win) | true |
| Jsonifier (two-stage) | 1874.89 | 0.429109 | 496.208ms | 9378 | 2560 | 1.07262e+06 | 4770.18 | 0.994458 | 2(Loss) | true |
| Glaze | 1575.4 | 0.201687 | 586.659ms | 9378 | 40 | 5243.9 | 5677 | 0.185785 | 3(Loss) | true |
| simdjson (ondemand) | 1511.12 | 0.0844609 | 609.05ms | 9378 | 160 | 3998.1 | 5918.49 | 0.381345 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2848.88 | 0.0539494 | 343.73ms | 9378 | 160 | 458.948 | 3139.32 | 0.0906671 | 1(Win) | true |
| Jsonifier (two-stage) | 2395.62 | 0.101744 | 430.811ms | 9378 | 30 | 432.838 | 3733.3 | 0.186061 | 2(Loss) | true |
| Glaze | 1765.81 | 0.0978829 | 543.916ms | 9378 | 160 | 3932.48 | 5064.85 | 0.0458836 | 3(Loss) | true |
| simdjson (ondemand) | 1677.67 | 0.153776 | 576.172ms | 9378 | 160 | 10752.3 | 5330.94 | 0.18982 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13454.9 | 0.511584 | 89.7284ms | 11521 | 40 | 698.092 | 816.6 | 0.00816327 | 1(Win) | true |
| Glaze | 3345.29 | 0.150143 | 342.65ms | 11521 | 40 | 972.708 | 3284.4 | 0.472727 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14311.8 | 0.17345 | 82.4172ms | 11521 | 320 | 567.404 | 767.709 | 0.0370283 | 1(Win) | true |
| Glaze | 4007.57 | 0.211438 | 280.083ms | 11521 | 30 | 1008.1 | 2741.63 | 0.404063 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2669.11 | 0.0841072 | 174.882ms | 4669 | 320 | 629.987 | 1668.24 | 0.000749288 | 1(Win) | true |
| Jsonifier (two-stage) | 1613.87 | 0.228831 | 276.312ms | 4669 | 1280 | 51021.2 | 2759.02 | 0.0817307 | 2(Loss) | true |
| Glaze | 1285.88 | 0.245141 | 352.751ms | 4669 | 640 | 46116.6 | 3462.76 | 0.202732 | 3(Loss) | true |
| simdjson (ondemand) | 557.242 | 0.0533116 | 838.317ms | 4669 | 160 | 2903.52 | 7990.62 | 0.0199492 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2972.85 | 0.120969 | 165.501ms | 4669 | 1280 | 4202.08 | 1497.79 | 0.00458988 | 1(Win) | true |
| Jsonifier (two-stage) | 1871.96 | 0.104232 | 257.948ms | 4669 | 80 | 491.753 | 2378.64 | 0.370161 | 2(Loss) | true |
| Glaze | 1502.79 | 0.161769 | 307.613ms | 4669 | 2560 | 58814.3 | 2962.95 | 0.0899632 | 3(Loss) | true |
| simdjson (ondemand) | 601.821 | 0.0673454 | 783.573ms | 4669 | 160 | 3972.37 | 7398.72 | 0.159318 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12170.3 | 0.605901 | 41.2103ms | 4669 | 640 | 3145.07 | 365.867 | 1.35439 | 1(Win) | true |
| Glaze | 1932.37 | 0.290592 | 241.582ms | 4669 | 30 | 1345.1 | 2304.27 | 0.0665875 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14680 | 0.187135 | 33.5353ms | 4669 | 1280 | 412.402 | 303.319 | 0.1274 | 1(Win) | true |
| Glaze | 2014.54 | 0.487948 | 226.053ms | 4669 | 1280 | 148886 | 2210.29 | 0.082324 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2734.15 | 0.149396 | 304.153ms | 7932 | 160 | 2733.49 | 2766.69 | 0.167339 | 1(Win) | true |
| Jsonifier (two-stage) | 2396.82 | 0.112798 | 324.212ms | 7932 | 40 | 506.943 | 3156.07 | 0.507277 | 2(Loss) | true |
| Glaze | 1700.15 | 0.386412 | 468.774ms | 7932 | 320 | 94588.9 | 4449.33 | 0.0551043 | 3(Loss) | true |
| simdjson (ondemand) | 879.718 | 0.150043 | 860.054ms | 7932 | 4890 | 813993 | 8598.83 | 0.203425 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2998.32 | 0.166783 | 273.882ms | 7932 | 40 | 708.225 | 2522.93 | 0.246787 | 1(Win) | true |
| Jsonifier (two-stage) | 2667.45 | 0.0710402 | 305.367ms | 7932 | 80 | 324.693 | 2835.88 | 0.021153 | 2(Loss) | true |
| Glaze | 1854.47 | 0.221525 | 425.097ms | 7932 | 640 | 52257.9 | 4079.09 | 0.87041 | 3(Loss) | true |
| simdjson (ondemand) | 949.195 | 0.154539 | 805.55ms | 7932 | 2560 | 388304 | 7969.43 | 0.352473 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13930.4 | 0.307309 | 67.8487ms | 9249 | 320 | 1211.61 | 633.188 | 0.35363 | 1(Win) | true |
| Glaze | 2969.14 | 0.166753 | 308.937ms | 9249 | 30 | 736.202 | 2970.73 | 0.180978 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15366 | 0.203388 | 61.5303ms | 9249 | 640 | 872.364 | 574.03 | 0.447034 | 1(Win) | true |
| Glaze | 3559.97 | 0.156351 | 261.119ms | 9249 | 30 | 450.217 | 2477.7 | 0.349903 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 635.301 | 0.118036 | 720.155ms | 4604 | 30 | 1996.46 | 6911.23 | 0.324193 | 1(Win) | true |
| Jsonifier (two-stage) | 570.225 | 0.0676899 | 818.855ms | 4604 | 40 | 1086.64 | 7699.98 | 0.124413 | 2(Loss) | true |
| Glaze | 359.163 | 0.240933 | 1277.94ms | 4604 | 4890 | 4.2422e+06 | 12224.9 | 0.987362 | 3(Loss) | true |
| simdjson (ondemand) | 332.023 | 0.0749432 | 1352.41ms | 4604 | 2560 | 251443 | 13224.1 | 0.0407735 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 848.505 | 0.154963 | 669.643ms | 4604 | 2560 | 164611 | 5174.65 | 0.0892991 | 1(Win) | true |
| Jsonifier (two-stage) | 704.75 | 0.0896185 | 838.331ms | 4604 | 40 | 1246.97 | 6230.18 | 0.0183282 | 2(Loss) | true |
| Glaze | 350.585 | 0.297927 | 1310.14ms | 4604 | 2560 | 3.56403e+06 | 12524 | 3.76227 | 3(Loss) | true |
| simdjson (ondemand) | 340.951 | 0.237024 | 1358.35ms | 4604 | 30 | 27950.7 | 12877.8 | 0.0549048 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1904.8 | 0.114751 | 254.09ms | 4604 | 640 | 4477.81 | 2305.08 | 0.180457 | 1(Win) | true |
| Glaze | 1031.08 | 0.158206 | 445.654ms | 4604 | 30 | 1361.62 | 4258.37 | 0.130109 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1561.72 | 0.697651 | 256.15ms | 4604 | 320 | 123108 | 2811.45 | 1.3239 | 1(Win) | true |
| Glaze | 1084.8 | 0.314001 | 426.032ms | 4604 | 1280 | 206748 | 4047.48 | 0.891844 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1759.4 | 0.128567 | 1031.74ms | 18245 | 40 | 6466.65 | 9889.62 | 0.487639 | 1(Win) | true |
| Jsonifier | 1738.17 | 0.296215 | 1014.09ms | 18245 | 4890 | 4.29957e+06 | 10010.4 | 0.367736 | 2(Loss) | true |
| simdjson (ondemand) | 1137.75 | 0.139899 | 1730.13ms | 18245 | 30 | 13732.3 | 15293.1 | 0.0714409 | 3(Loss) | true |
| Glaze | 1005.34 | 1.70561 | 1633.81ms | 18245 | 40 | 3.48566e+06 | 17307.5 | 2.73726 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2149.24 | 0.128065 | 994.562ms | 18245 | 80 | 8599.48 | 8095.8 | 0.168014 | 1(Win) | true |
| Jsonifier | 2137.94 | 0.147093 | 999.078ms | 18245 | 40 | 5732.46 | 8138.57 | 0.27033 | 2(Loss) | true |
| Glaze | 1237.78 | 0.189271 | 1560.77ms | 18245 | 4890 | 3.46163e+06 | 14057.3 | 0.116298 | 3(Loss) | true |
| simdjson (ondemand) | 1014.59 | 1.06618 | 1786.22ms | 18245 | 80 | 2.67457e+06 | 17149.5 | 0.208898 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4772.33 | 0.741792 | 499.034ms | 24579 | 320 | 424797 | 4911.72 | 3.6773 | 1(Win) | true |
| Glaze | 2675.03 | 0.470526 | 894.021ms | 24579 | 4890 | 8.3128e+06 | 8762.65 | 0.744086 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4970.46 | 0.620199 | 476.237ms | 24579 | 4890 | 4.18318e+06 | 4715.93 | 1.0793 | 1(Win) | true |
| Glaze | 3333.42 | 0.41157 | 711.577ms | 24579 | 1280 | 1.07213e+06 | 7031.93 | 1.46977 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 628.921 | 0.260635 | 696.09ms | 4604 | 4890 | 1.61903e+06 | 6981.35 | 0.00573391 | 1(Win) | true |
| Jsonifier (two-stage) | 552.18 | 0.0906927 | 837.131ms | 4604 | 30 | 1560.18 | 7951.6 | 0.11933 | 2(Loss) | true |
| Glaze | 309.399 | 0.392289 | 1370.61ms | 4604 | 2560 | 7.93388e+06 | 14191.1 | 0.027125 | 3(Loss) | true |
| simdjson (ondemand) | 283.462 | 1.96488 | 1582.45ms | 4604 | 640 | 5.9283e+07 | 15489.6 | 0.224063 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 793.077 | 0.279217 | 740.836ms | 4604 | 2560 | 611737 | 5536.31 | 0.234832 | 1(Win) | true |
| Jsonifier (two-stage) | 713.929 | 0.0719539 | 815.237ms | 4604 | 40 | 783.302 | 6150.07 | 0.133019 | 2(Loss) | true |
| Glaze | 414.078 | 0.336195 | 1243.45ms | 4604 | 2560 | 3.25333e+06 | 10603.6 | 0.371842 | 3(Loss) | true |
| simdjson (ondemand) | 325.196 | 0.265844 | 1502.19ms | 4604 | 4890 | 6.30004e+06 | 13501.7 | 0.83862 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1863.58 | 0.454652 | 243.129ms | 4604 | 4890 | 561099 | 2356.06 | 0.405718 | 1(Win) | true |
| Glaze | 984.035 | 0.222408 | 484.923ms | 4604 | 1280 | 126056 | 4461.95 | 3.15343 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1578.85 | 0.779523 | 265.6ms | 4604 | 320 | 150382 | 2780.95 | 0.952572 | 1(Win) | true |
| Glaze | 1022 | 0.402252 | 437.57ms | 4604 | 2560 | 764550 | 4296.2 | 0.667896 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1888.71 | 0.86795 | 1003.43ms | 18245 | 30 | 191809 | 9212.53 | 1.54722 | 1(Win) | true |
| Jsonifier (two-stage) | 1778.02 | 0.333287 | 984.902ms | 18245 | 2560 | 2.72328e+06 | 9786.05 | 0.640772 | 2(Loss) | true |
| simdjson (ondemand) | 1138.71 | 0.157816 | 1562.16ms | 18245 | 4890 | 2.84359e+06 | 15280.2 | 0.369109 | 3(Loss) | true |
| Glaze | 1017.45 | 0.317557 | 1725.67ms | 18245 | 2560 | 7.54999e+06 | 17101.4 | 2.09311 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2189.59 | 0.156457 | 957.533ms | 18245 | 4890 | 755894 | 7946.59 | 1.35249 | 1(Win) | true |
| Jsonifier | 2057.8 | 0.382044 | 987.159ms | 18245 | 1280 | 1.33573e+06 | 8455.52 | 0.861967 | 2(Loss) | true |
| simdjson (ondemand) | 1293.89 | 0.109158 | 1549.89ms | 18245 | 4890 | 1.05368e+06 | 13447.6 | 0.0834743 | 3(Loss) | true |
| Glaze | 1126.48 | 0.896172 | 1621.46ms | 18245 | 320 | 6.13158e+06 | 15446.1 | 0.00987205 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5557.68 | 0.171598 | 443.775ms | 24579 | 40 | 2095.21 | 4217.65 | 0.174752 | 1(Win) | true |
| Glaze | 2591.65 | 1.04043 | 849.361ms | 24579 | 320 | 2.83368e+06 | 9044.57 | 0.495449 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6082.26 | 0.0524406 | 392.722ms | 24579 | 640 | 2614.05 | 3853.89 | 0.266792 | 1(Win) | true |
| Glaze | 3657.16 | 0.216509 | 643.862ms | 24579 | 2560 | 492984 | 6409.44 | 0.326463 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1498.62 | 0.129748 | 328.26ms | 5094 | 30 | 530.713 | 3241.67 | 0.043169 | 1(Win) | true |
| Jsonifier (two-stage) | 1119.75 | 0.0551383 | 441.211ms | 5094 | 80 | 457.797 | 4338.49 | 0.0751425 | 2(Loss) | true |
| Glaze | 904.016 | 0.0788481 | 542.461ms | 5094 | 4890 | 87792.4 | 5373.82 | 0.232498 | 3(Loss) | true |
| simdjson (ondemand) | 670.453 | 0.103545 | 739.744ms | 5094 | 80 | 4503.33 | 7245.88 | 0.0890955 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1922.36 | 0.0688897 | 325.015ms | 5094 | 160 | 484.926 | 2527.11 | 0.0427678 | 1(Win) | true |
| Jsonifier (two-stage) | 1429.29 | 0.0715235 | 439.365ms | 5094 | 80 | 472.79 | 3398.91 | 0.0936921 | 2(Loss) | true |
| Glaze | 1110.91 | 0.0765177 | 510.707ms | 5094 | 320 | 3582.92 | 4373.02 | 0.00114339 | 3(Loss) | true |
| simdjson (ondemand) | 800.631 | 0.0978806 | 686.212ms | 5094 | 160 | 5643.74 | 6067.74 | 0.0325386 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10403.6 | 0.0734306 | 52.056ms | 5094 | 2560 | 300.985 | 466.955 | 0.0197461 | 1(Win) | true |
| Glaze | 2781.19 | 0.0332732 | 177.496ms | 5094 | 1280 | 432.37 | 1746.74 | 0.0578644 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11342 | 0.124877 | 45.9358ms | 5094 | 1280 | 366.194 | 428.32 | 0.0448499 | 1(Win) | true |
| Glaze | 3402.33 | 0.123293 | 146.675ms | 5094 | 160 | 495.864 | 1427.85 | 0.091837 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1775.9 | 0.037805 | 440.719ms | 8051 | 160 | 427.444 | 4323.45 | 0.00086737 | 1(Win) | true |
| Jsonifier (two-stage) | 1382.88 | 0.0240081 | 561.534ms | 8051 | 320 | 568.588 | 5552.21 | 0.119067 | 2(Loss) | true |
| Glaze | 1257.95 | 0.270332 | 691.216ms | 8051 | 160 | 43560.1 | 6103.61 | 0.118718 | 3(Loss) | true |
| simdjson (ondemand) | 1026.42 | 0.155002 | 792.621ms | 8051 | 30 | 4033.22 | 7480.43 | 0.0160444 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2127.91 | 0.0591421 | 442.613ms | 8051 | 160 | 728.632 | 3608.26 | 0.0143788 | 1(Win) | true |
| Jsonifier (two-stage) | 1870.8 | 0.0892291 | 559.763ms | 8051 | 40 | 536.438 | 4104.15 | 0.169864 | 2(Loss) | true |
| Glaze | 1518.23 | 0.0564797 | 585.663ms | 8051 | 640 | 5221.42 | 5057.22 | 0.107357 | 3(Loss) | true |
| simdjson (ondemand) | 1199.59 | 0.11427 | 737.443ms | 8051 | 80 | 4279.47 | 6400.55 | 0.040638 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8597.61 | 0.370641 | 93.4587ms | 9255 | 1280 | 18531.6 | 1026.59 | 2.44721 | 1(Win) | true |
| Glaze | 3171.18 | 0.153709 | 294.368ms | 9255 | 40 | 732.102 | 2783.28 | 0.0998022 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13123.9 | 0.126882 | 71.6831ms | 9255 | 320 | 233.008 | 672.531 | 0.0956289 | 1(Win) | true |
| Glaze | 3632.62 | 0.120707 | 250.902ms | 9255 | 80 | 688.126 | 2429.72 | 0.150449 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 3242.74 | 0.128029 | 89.4496ms | 2889 | 640 | 757.301 | 849.641 | 0.261084 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 3222.97 | 0.477963 | 86.7608ms | 2889 | 2560 | 42737.8 | 854.853 | 0.741483 | 1(Tie) | true |
| Jsonifier | 3135.51 | 0.909984 | 94.4239ms | 2889 | 2560 | 163677 | 878.698 | 2.33879 | 3(Loss) | true |
| Glaze | 2140.14 | 0.193309 | 151.822ms | 2889 | 40 | 247.728 | 1287.38 | 0.429712 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 3977.29 | 0.231294 | 84.5452ms | 2889 | 160 | 410.742 | 692.725 | 0.00180444 | 1(Win) | true |
| Jsonifier | 3708.36 | 1.00026 | 80.2008ms | 2889 | 2560 | 141383 | 742.961 | 1.18643 | 2(Loss) | true |
| simdjson (ondemand) | 3467.8 | 0.351717 | 91.7775ms | 2889 | 30 | 234.259 | 794.5 | 0.726873 | 3(Loss) | true |
| Glaze | 2311.96 | 0.319652 | 146.761ms | 2889 | 30 | 435.321 | 1191.7 | 0.114814 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 3937.82 | 0.2846 | 98.3485ms | 3808 | 30 | 206.668 | 922.233 | 0.446188 | 1(Win) | true |
| Jsonifier | 3890.97 | 0.401827 | 102.282ms | 3808 | 80 | 1125.24 | 933.337 | 0.441345 | 2(Loss) | true |
| simdjson (ondemand) | 3360.26 | 0.765636 | 102.394ms | 3808 | 320 | 21910 | 1080.75 | 0.930098 | 3(Loss) | true |
| Glaze | 2433.68 | 0.141626 | 156.012ms | 3808 | 320 | 1429.23 | 1492.22 | 0.30815 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 4272.46 | 0.270229 | 93.072ms | 3808 | 80 | 422.076 | 850 | 0.123682 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 4203.56 | 0.511601 | 94.0034ms | 3808 | 30 | 586.064 | 863.933 | 0.154095 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 4175.32 | 0.254518 | 94.3769ms | 3808 | 40 | 196.025 | 869.775 | 0.0392976 | 2(Tie) | true |
| Glaze | 2502.78 | 0.368176 | 155.156ms | 3808 | 40 | 1141.61 | 1451.03 | 0.398696 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2217.04 | 0.29082 | 133.211ms | 2889 | 80 | 1044.94 | 1242.72 | 0.090445 | 1(Win) | true |
| Glaze | 1736.24 | 0.258987 | 164.229ms | 2889 | 640 | 10809.7 | 1586.86 | 0.323417 | 2(Loss) | true |
| Jsonifier (two-stage) | 1722.74 | 0.230895 | 166.781ms | 2889 | 2560 | 34908.2 | 1599.29 | 0.0385275 | 3(Loss) | true |
| simdjson (ondemand) | 770.841 | 0.413221 | 364.522ms | 2889 | 2560 | 558431 | 3574.23 | 0.066109 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2728.61 | 0.513267 | 123.436ms | 2889 | 30 | 805.789 | 1009.73 | 0.273251 | 1(Win) | true |
| Jsonifier (two-stage) | 2089.57 | 0.155157 | 160.157ms | 2889 | 1280 | 5357.17 | 1318.53 | 0.579859 | 2(Loss) | true |
| Glaze | 2034.19 | 0.187887 | 154.474ms | 2889 | 320 | 2072.32 | 1354.43 | 0.717825 | 3(Loss) | true |
| simdjson (ondemand) | 832.438 | 0.0973562 | 353.193ms | 2889 | 320 | 3322.53 | 3309.75 | 0.0605585 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9480.75 | 0.418642 | 36.2094ms | 2963 | 320 | 498.211 | 298.05 | 0.22596 | 1(Win) | true |
| Glaze | 3448.47 | 0.260217 | 86.5993ms | 2963 | 320 | 1454.9 | 819.419 | 0.110719 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10563.4 | 2.055 | 28.863ms | 2963 | 4890 | 147772 | 267.504 | 0.245388 | 1(Win) | true |
| Glaze | 4201.18 | 0.51458 | 71.4112ms | 2963 | 160 | 1916.67 | 672.606 | 0.0417975 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1870.42 | 0.792493 | 208.366ms | 3808 | 320 | 75762.6 | 1941.59 | 0.478695 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE DID NOT CONVERGE | 1857.43 | 1.15785 | 205.504ms | 3808 | 160 | 81996.6 | 1955.17 | 6.3144 | -(Tie) | false |
| Glaze | 1623.81 | 0.242712 | 232.419ms | 3808 | 4890 | 144084 | 2236.47 | 1.29914 | 3(Loss) | true |
| simdjson (ondemand) | 907.837 | 0.826191 | 445.01ms | 3808 | 640 | 699067 | 4000.27 | 0.00621091 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2244.16 | 1.42009 | 208.32ms | 3808 | 80 | 42248 | 1618.24 | 0.610346 | 1(Win) | true |
| Jsonifier | 1982.57 | 0.388081 | 185.997ms | 3808 | 160 | 8085.37 | 1831.76 | 0.34134 | 2(Loss) | true |
| Glaze | 1846.1 | 1.4152 | 210.874ms | 3808 | 2560 | 1.98409e+06 | 1967.17 | 0.361591 | 3(Loss) | true |
| simdjson (ondemand) | 971.429 | 0.329122 | 393.93ms | 3808 | 4890 | 740276 | 3738.4 | 1.48748 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9968.7 | 0.307442 | 42.6243ms | 4300 | 2560 | 4094.74 | 411.368 | 1.55911 | 1(Win) | true |
| Glaze | 3029.58 | 0.25115 | 154.908ms | 4300 | 80 | 924.549 | 1353.59 | 1.02641 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11066 | 1.09463 | 40.897ms | 4300 | 160 | 2632.74 | 370.575 | 2.65957 | 1(Win) | true |
| Glaze | 4004.83 | 0.605095 | 109.693ms | 4300 | 80 | 3071.18 | 1023.96 | 0.00122073 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2088.2 | 1.29484 | 5009.36ms | 466906 | 80 | 6.09874e+08 | 213235 | 0.372381 | 1(Win) | true |
| Glaze | 1423.76 | 0.542524 | 7725.84ms | 466906 | 320 | 9.21245e+08 | 312748 | 0.483496 | 2(Loss) | true |
| simdjson (ondemand) | 1258.71 | 0.170015 | 9154.69ms | 466906 | 40 | 1.44692e+07 | 353757 | 0.144182 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2414.33 | 0.521069 | 9109.3ms | 466906 | 320 | 2.95534e+08 | 184431 | 0.751054 | 1(Win) | true |
| Glaze | 1473.73 | 0.262254 | 7663.16ms | 466906 | 1280 | 8.03663e+08 | 302141 | 2.45292 | 2(Loss) | true |
| simdjson (ondemand) | 1093.21 | 1.43451 | 9416.17ms | 466906 | 30 | 1.0242e+09 | 407312 | 0.313092 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3303.37 | 0.184721 | 5956.61ms | 699405 | 80 | 1.11293e+07 | 201917 | 0.32087 | 1(Win) | true |
| Glaze | 2265.94 | 0.640426 | 7906.48ms | 699405 | 80 | 2.84307e+08 | 294361 | 0.12416 | 2(Loss) | true |
| simdjson (ondemand) | 1516.93 | 0.266053 | 6263.61ms | 767297 | 320 | 5.27088e+08 | 482391 | 0.407284 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2784.25 | 0.316774 | 6072.22ms | 699405 | 640 | 3.68571e+08 | 239563 | 1.7469 | 1(Win) | true |
| Glaze | 2042.42 | 0.896512 | 7857.6ms | 699405 | 80 | 6.85754e+08 | 326575 | 0.124575 | 2(Loss) | true |
| simdjson (ondemand) | 1639.05 | 0.200787 | 5781.76ms | 767297 | 80 | 6.42847e+07 | 446449 | 0.0468105 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2544.97 | 0.235712 | 6073.08ms | 631514 | 80 | 2.48918e+07 | 236647 | 0.175307 | 1(Win) | true |
| Glaze | 1986.89 | 0.0894714 | 7843.13ms | 631514 | 160 | 1.17682e+07 | 303117 | 0.0622536 | 2(Loss) | true |
