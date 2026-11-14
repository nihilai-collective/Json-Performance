# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the Clang 23.1.4 compiler).  

Latest Results: (Nov 14, 2026)
#### Using the following commits:
----
| Jsonifier: [d4727ec](https://github.com/nihilai-collective/Jsonifier/commit/d4727ec)  
| Glaze: [a53ddd59](https://github.com/stephenberry/glaze/commit/a53ddd59)  
| simdjson: [449f38e63](https://github.com/simdjson/simdjson/commit/449f38e63)  

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
*Environment generated via BenchmarkSuite commit: [27950a9](https://github.com/nihilai-collective/benchmarksuite/commit/27950a9)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1266.99 | 0.0686838 | 71.8255ms | 905 | 2560 | 560.399 | 681.2 | 0.202757 | 1(Win) | true |
| Glaze | 1200.01 | 0.287275 | 75.1683ms | 905 | 80 | 341.518 | 719.225 | 0.0868236 | 2(Loss) | true |
| Jsonifier (two-stage) | 346.308 | 0.105029 | 250.75ms | 905 | 160 | 1096.26 | 2492.22 | 2.36548 | 3(Loss) | true |
| simdjson (ondemand) | 184.657 | 0.138692 | 476.78ms | 905 | 40 | 1680.84 | 4673.93 | 0.00766723 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1362.2 | 0.151747 | 76.5172ms | 905 | 320 | 295.804 | 633.587 | 0.124138 | 1(Win) | true |
| Glaze | 1289.46 | 0.112703 | 71.2789ms | 905 | 640 | 364.194 | 669.331 | 0.0252181 | 2(Loss) | true |
| Jsonifier (two-stage) | 351.659 | 0.0628897 | 256.42ms | 905 | 320 | 762.366 | 2454.3 | 0.132627 | 3(Loss) | true |
| simdjson (ondemand) | 174.545 | 0.158051 | 496.635ms | 905 | 40 | 2443.08 | 4944.73 | 0.0776319 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1018.52 | 0.231612 | 87.8259ms | 905 | 4890 | 18836.1 | 847.382 | 0.00792924 | 1(Win) | true |
| Glaze | 132.357 | 0.125593 | 660.956ms | 905 | 40 | 2682.87 | 6520.82 | 0.0210818 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1266.29 | 0.132816 | 78.9666ms | 905 | 640 | 524.457 | 681.577 | 0.0286642 | 1(Win) | true |
| Glaze | 766.463 | 0.0932463 | 127.739ms | 905 | 40 | 44.1 | 1126.05 | 0.0310724 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 912.034 | 0.0472288 | 194.802ms | 1811 | 640 | 511.928 | 1893.68 | 0.0028053 | 1(Win) | true |
| Glaze | 773.394 | 0.0506972 | 219.838ms | 1811 | 640 | 820.322 | 2233.15 | 0.00923669 | 2(Loss) | true |
| Jsonifier (two-stage) | 374.727 | 0.128084 | 467.618ms | 1811 | 2560 | 89214.7 | 4608.97 | 0.0256991 | 3(Loss) | true |
| simdjson (ondemand) | 193.777 | 0.0657671 | 877.863ms | 1811 | 160 | 5497.55 | 8912.84 | 0.262952 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1078.06 | 0.153082 | 165.045ms | 1811 | 80 | 481.162 | 1602.05 | 0.124996 | 1(Win) | true |
| Glaze | 977.933 | 0.0500039 | 182.025ms | 1811 | 640 | 499.122 | 1766.08 | 0.143915 | 2(Loss) | true |
| Jsonifier (two-stage) | 405.831 | 0.059165 | 464.885ms | 1811 | 160 | 1014.37 | 4255.72 | 0.0127753 | 3(Loss) | true |
| simdjson (ondemand) | 204.19 | 0.0578616 | 821.183ms | 1811 | 30 | 718.575 | 8458.33 | 0 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 301.18 | 0.061894 | 587.149ms | 1811 | 40 | 503.895 | 5734.45 | 0.128588 | 1(Win) | true |
| Glaze | 223.414 | 0.0679099 | 777.932ms | 1798 | 40 | 1086.64 | 7675.02 | 0.16433 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 885.725 | 0.215498 | 212.297ms | 1811 | 30 | 529.72 | 1949.93 | 0.282859 | 1(Win) | true |
| Glaze | 707.026 | 0.068324 | 261.771ms | 1798 | 160 | 439.314 | 2425.24 | 0.0742747 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2026.32 | 0.721768 | 179.2ms | 3862 | 4890 | 841612 | 1817.62 | 1.22053 | 1(Win) | true |
| Glaze | 1330.85 | 0.226595 | 279.473ms | 3862 | 2560 | 100672 | 2767.48 | 0.0407944 | 2(Loss) | true |
| Jsonifier (two-stage) | 863.375 | 0.215589 | 433.719ms | 3862 | 1280 | 108265 | 4265.92 | 0.165408 | 3(Loss) | true |
| simdjson (ondemand) | 494.509 | 0.101693 | 761.295ms | 3862 | 40 | 2294.64 | 7447.98 | 0.0830632 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2775.29 | 0.212441 | 136.856ms | 3862 | 40 | 317.938 | 1327.1 | 0.0502601 | 1(Win) | true |
| Glaze | 1569.12 | 0.230711 | 257.601ms | 3862 | 30 | 879.771 | 2347.23 | 0.112063 | 2(Loss) | true |
| Jsonifier (two-stage) | 938.373 | 0.127339 | 400.86ms | 3862 | 40 | 999.204 | 3924.97 | 0.0690502 | 3(Loss) | true |
| simdjson (ondemand) | 481.8 | 0.0892611 | 765.394ms | 3862 | 30 | 1396.81 | 7644.43 | 0.0727669 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3026.48 | 0.117834 | 125.866ms | 3862 | 160 | 329.011 | 1216.96 | 0.0251716 | 1(Win) | true |
| Glaze | 550.828 | 0.0683117 | 680.232ms | 3862 | 80 | 1669.06 | 6686.46 | 0.0626658 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3246.41 | 0.222562 | 133.67ms | 3862 | 320 | 2040.19 | 1134.51 | 0.241877 | 1(Win) | true |
| Glaze | 2179.73 | 0.0735996 | 187.213ms | 3862 | 320 | 494.905 | 1689.7 | 0.130926 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1398.09 | 0.1263 | 663.278ms | 9578 | 1280 | 87157 | 6533.43 | 0.0382914 | 1(Win) | true |
| Glaze | 1199.64 | 0.0535545 | 774.151ms | 9578 | 320 | 5320.95 | 7614.18 | 0.320824 | 2(Loss) | true |
| simdjson (ondemand) | 877.151 | 0.203626 | 1038.06ms | 9578 | 1280 | 575542 | 10413.6 | 0.157516 | 3(Loss) | true |
| Jsonifier (two-stage) | 748.71 | 0.0959612 | 1229.57ms | 9578 | 30 | 4111.83 | 12200 | 0.181908 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2419.43 | 0.224773 | 622.165ms | 9578 | 640 | 46088.2 | 3775.39 | 0.0209045 | 1(Win) | true |
| Glaze | 1840.66 | 0.0839779 | 716.081ms | 9578 | 30 | 521.017 | 4962.5 | 0.028875 | 2(Loss) | true |
| simdjson (ondemand) | 1226.31 | 0.0515303 | 1006.7ms | 9578 | 30 | 441.972 | 7448.6 | 0.0376051 | 3(Loss) | true |
| Jsonifier (two-stage) | 975.195 | 0.125103 | 1189.35ms | 9578 | 30 | 4119.27 | 9366.63 | 0.0437916 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1293.63 | 0.0734107 | 663.778ms | 9578 | 30 | 806.069 | 7061 | 0.0207671 | 1(Win) | true |
| Glaze | 1138.6 | 0.0412215 | 820.536ms | 9578 | 80 | 874.878 | 8022.41 | 0.083913 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7889.29 | 0.0752892 | 127.415ms | 9578 | 640 | 486.317 | 1157.81 | 0.0226773 | 1(Win) | true |
| Glaze | 4296.94 | 0.0643801 | 255.541ms | 9578 | 320 | 599.357 | 2125.77 | 0.0473582 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2356.83 | 0.0780207 | 160.648ms | 3873 | 320 | 478.42 | 1567.18 | 0.11731 | 1(Win) | true |
| Glaze | 1308.42 | 0.140228 | 277.124ms | 3873 | 80 | 1253.6 | 2822.94 | 0.108604 | 2(Loss) | true |
| Jsonifier (two-stage) | 844.74 | 0.0921503 | 442.92ms | 3873 | 2560 | 41560.7 | 4372.45 | 0.0402751 | 3(Loss) | true |
| simdjson (ondemand) | 472.477 | 0.143949 | 788.47ms | 3873 | 1280 | 162091 | 7817.49 | 0.0039873 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2845.18 | 0.100915 | 134.131ms | 3873 | 160 | 274.606 | 1298.19 | 0.0597343 | 1(Win) | true |
| Glaze | 1471.87 | 0.173857 | 255.383ms | 3873 | 40 | 761.382 | 2509.45 | 0.157653 | 2(Loss) | true |
| Jsonifier (two-stage) | 896.333 | 0.148844 | 415.254ms | 3873 | 30 | 1128.6 | 4120.77 | 0.336985 | 3(Loss) | true |
| simdjson (ondemand) | 474.109 | 0.136243 | 793.893ms | 3873 | 40 | 4506.4 | 7790.57 | 0.0507835 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2944.97 | 0.160869 | 129.13ms | 3873 | 40 | 162.831 | 1254.2 | 0.229089 | 1(Win) | true |
| Glaze | 557.252 | 0.0726954 | 674.325ms | 3873 | 40 | 928.677 | 6628.2 | 0.0346882 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3458.3 | 0.394808 | 119.371ms | 3873 | 30 | 533.413 | 1068.03 | 0.523938 | 1(Win) | true |
| Glaze | 2247.58 | 0.0373585 | 182.109ms | 3873 | 1280 | 482.45 | 1643.36 | 0.0436607 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1571.61 | 0.171894 | 5783.92ms | 94653 | 160 | 1.55962e+06 | 57436.7 | 0.0611699 | 1(Win) | true |
| Glaze | 1127.17 | 0.0709111 | 8143.47ms | 94653 | 4890 | 1.57698e+07 | 80083.8 | 0.154834 | 2(Loss) | true |
| Jsonifier (two-stage) | 1089.11 | 0.214395 | 8365.48ms | 94653 | 320 | 1.01041e+07 | 82882.2 | 0.0630395 | 3(Loss) | true |
| simdjson (ondemand) | 869.374 | 0.12164 | 5320.17ms | 94653 | 640 | 1.02091e+07 | 103831 | 0.0597299 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2336.03 | 0.0483886 | 5514.13ms | 94653 | 30 | 10488.6 | 38641.7 | 0.0897073 | 1(Win) | true |
| Jsonifier (two-stage) | 1471.34 | 0.0713407 | 7984.55ms | 94653 | 4890 | 9.36761e+06 | 61351.2 | 0.184997 | 2(Loss) | true |
| Glaze | 1461.53 | 0.0958948 | 7625.65ms | 94653 | 2560 | 8.98014e+06 | 61762.7 | 0.0199018 | 3(Loss) | true |
| simdjson (ondemand) | 1065.56 | 0.29396 | 5228.88ms | 94653 | 30 | 1.8604e+06 | 84713.9 | 0.0180182 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12205.3 | 0.0648226 | 749.208ms | 94653 | 30 | 689.523 | 7395.83 | 0.130983 | 1(Win) | true |
| Glaze | 3745.2 | 0.0680996 | 2477.55ms | 94653 | 4890 | 1.3174e+06 | 24102.4 | 0.520332 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12643.2 | 0.0679818 | 725.514ms | 94653 | 40 | 942.328 | 7139.68 | 0.0680007 | 1(Win) | true |
| Glaze | 4420.17 | 0.0335354 | 2067.35ms | 94653 | 80 | 3752.21 | 20421.9 | 0.127885 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1644.5 | 0.101922 | 7292.92ms | 124597 | 1280 | 6.94211e+06 | 72255.9 | 0.0580447 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1359.02 | 0.102541 | 8769.94ms | 124597 | 2560 | 2.05778e+07 | 87434.1 | 0.344786 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1358.42 | 0.0537449 | 8816.53ms | 124597 | 4890 | 1.08077e+07 | 87473.1 | 0.235904 | 2(Tie) | true |
| simdjson (ondemand) | 1112.02 | 0.0893346 | 5511.69ms | 124597 | 2560 | 2.33276e+07 | 106855 | 0.00488346 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2256.82 | 0.0771031 | 6836.55ms | 124597 | 2560 | 4.21897e+06 | 52651.6 | 0.0404532 | 1(Win) | true |
| Jsonifier (two-stage) | 1826.36 | 0.498062 | 8617.7ms | 124597 | 80 | 8.40038e+06 | 65061 | 0.196721 | 2(Loss) | true |
| Glaze | 1719.24 | 0.0723939 | 8421.22ms | 124597 | 4890 | 1.2242e+07 | 69114.7 | 0.274162 | 3(Loss) | true |
| simdjson (ondemand) | 1351.27 | 0.192711 | 5352.65ms | 124597 | 160 | 4.59478e+06 | 87935.9 | 0.00307032 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12096.4 | 0.0435788 | 1087.91ms | 136037 | 40 | 873.792 | 10725 | 0.181993 | 1(Win) | true |
| Glaze | 3563.8 | 0.182262 | 3751.95ms | 136076 | 320 | 1.40954e+06 | 36414 | 0.0261043 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12388.6 | 0.0550136 | 1063.93ms | 136037 | 30 | 995.706 | 10472.1 | 0.0801486 | 1(Win) | true |
| Glaze | 3923.95 | 0.124575 | 3320.11ms | 136076 | 1280 | 2.17263e+06 | 33071.8 | 0.0562327 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 833.35 | 0.17714 | 8059.17ms | 2251027 | 80 | 1.66584e+09 | 2.57604e+06 | 0.0405385 | 1(Win) | true |
| Jsonifier (two-stage) | 739.772 | 0.140397 | 9073.1ms | 2251027 | 80 | 1.32791e+09 | 2.9019e+06 | 0.0985743 | 2(Loss) | true |
| Glaze | 599.186 | 0.215763 | 5439.95ms | 2251027 | 30 | 1.79273e+09 | 3.58277e+06 | 0.0646184 | 3(Loss) | true |
| simdjson (ondemand) | 537.179 | 0.217883 | 6009.34ms | 2251027 | 30 | 2.27453e+09 | 3.99633e+06 | 0.000175161 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1037.58 | 0.174065 | 8068.69ms | 2251027 | 160 | 2.07521e+09 | 2.06899e+06 | 0.101163 | 1(Win) | true |
| Jsonifier (two-stage) | 896.457 | 0.194363 | 9069.83ms | 2251027 | 160 | 3.46617e+09 | 2.3947e+06 | 0.266799 | 2(Loss) | true |
| Glaze | 692.889 | 0.753594 | 5469.9ms | 2251027 | 30 | 1.63543e+10 | 3.09826e+06 | 0.0148384 | 3(Loss) | true |
| simdjson (ondemand) | 617.641 | 0.177984 | 6048.92ms | 2251027 | 30 | 1.14808e+09 | 3.47572e+06 | 0.105723 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2954.34 | 0.23306 | 8752.88ms | 2090234 | 80 | 1.97831e+08 | 674737 | 0.0361751 | 1(Win) | true |
| Glaze | 1883.81 | 0.182255 | 6701.74ms | 2090234 | 160 | 5.95102e+08 | 1.05817e+06 | 0.188894 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2953.14 | 0.199289 | 8661.95ms | 2090234 | 160 | 2.8954e+08 | 675011 | 0.0472861 | 1(Win) | true |
| Glaze | 1972.41 | 0.187296 | 6428.24ms | 2090234 | 80 | 2.86646e+08 | 1.01064e+06 | 0.0918339 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1668.51 | 0.18029 | 9577.78ms | 5373214 | 160 | 4.90537e+09 | 3.07118e+06 | 0.367565 | 1(Win) | true |
| Jsonifier (two-stage) | 1586.09 | 0.276694 | 10055.9ms | 5373214 | 160 | 1.27859e+10 | 3.23077e+06 | 0.237739 | 2(Loss) | true |
| Glaze | 1218.72 | 0.129653 | 6325.54ms | 5373214 | 80 | 2.37744e+09 | 4.20464e+06 | 0.0529779 | 3(Loss) | true |
| simdjson (ondemand) | 1189.5 | 0.128075 | 6533.64ms | 5373214 | 80 | 2.43532e+09 | 4.30792e+06 | 0.0197823 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2008.02 | 0.263092 | 9572.33ms | 5373214 | 40 | 1.80305e+09 | 2.55192e+06 | 1.4247 | 1(Win) | true |
| Jsonifier (two-stage) | 1893.43 | 0.149842 | 10051.8ms | 5373214 | 160 | 2.63122e+09 | 2.70635e+06 | 0.056928 | 2(Loss) | true |
| Glaze | 1388.7 | 0.223472 | 6374.27ms | 5373214 | 40 | 2.7199e+09 | 3.68998e+06 | 0.0550377 | 3(Loss) | true |
| simdjson (ondemand) | 1346.85 | 0.288773 | 6549.19ms | 5373214 | 80 | 9.65677e+09 | 3.80464e+06 | 0.243661 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7386.84 | 0.152108 | 5428.75ms | 6661897 | 320 | 5.47688e+08 | 860081 | 0.148501 | 1(Win) | true |
| Glaze | 3550.71 | 0.225604 | 5642.77ms | 6661897 | 40 | 6.5181e+08 | 1.7893e+06 | 0.0272658 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7337.86 | 0.222244 | 5474.53ms | 6661897 | 320 | 1.18486e+09 | 865822 | 0.496182 | 1(Win) | true |
| Glaze | 4016.91 | 0.123762 | 10020.6ms | 6661897 | 320 | 1.22612e+09 | 1.58163e+06 | 0.104681 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2168.93 | 0.192697 | 5657.49ms | 500299 | 40 | 7.1875e+06 | 219980 | 0.126318 | 1(Win) | true |
| Jsonifier (two-stage) | 1442.18 | 0.0713571 | 8586.05ms | 500299 | 1280 | 7.13349e+07 | 330833 | 0.235798 | 2(Loss) | true |
| Glaze | 1275.29 | 0.270218 | 9664.7ms | 500299 | 40 | 4.08819e+07 | 374129 | 0.436091 | 3(Loss) | true |
| simdjson (ondemand) | 856.487 | 0.131888 | 7064.86ms | 500299 | 640 | 3.45471e+08 | 557069 | 0.484742 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2651.43 | 0.0820639 | 5524.37ms | 500299 | 1280 | 2.79134e+07 | 179949 | 0.134223 | 1(Win) | true |
| Jsonifier (two-stage) | 1663.28 | 0.114551 | 8312.02ms | 500299 | 320 | 3.45525e+07 | 286857 | 0.0148767 | 2(Loss) | true |
| Glaze | 1422.38 | 0.128333 | 9486.25ms | 500299 | 320 | 5.92995e+07 | 335439 | 0.0334552 | 3(Loss) | true |
| simdjson (ondemand) | 916.209 | 0.123699 | 7051.64ms | 500299 | 640 | 2.65571e+08 | 520757 | 0.155272 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8248.82 | 0.161385 | 5866.23ms | 500299 | 320 | 2.78837e+06 | 57841.3 | 0.000156679 | 1(Win) | true |
| Glaze | 2219.28 | 0.118339 | 5534.1ms | 500299 | 320 | 2.07127e+07 | 214989 | 0.049687 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8256.14 | 0.0665039 | 5785.86ms | 500299 | 4890 | 7.22285e+06 | 57790 | 0.288463 | 1(Win) | true |
| Glaze | 2343.37 | 0.119146 | 5248.8ms | 500299 | 640 | 3.76634e+07 | 203605 | 0.13195 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3014.4 | 0.158463 | 9473.78ms | 1151920 | 30 | 1.0005e+07 | 364436 | 0.106617 | 1(Win) | true |
| Jsonifier (two-stage) | 2825.93 | 0.171841 | 5035.83ms | 1151920 | 30 | 1.33875e+07 | 388742 | 0.474345 | 2(Loss) | true |
| Glaze | 1988.7 | 0.319563 | 7088.1ms | 1151920 | 40 | 1.24647e+08 | 552400 | 0.215273 | 3(Loss) | true |
| simdjson (ondemand) | 1784.54 | 0.103124 | 7880.14ms | 1151920 | 640 | 2.57924e+08 | 615597 | 0.0339605 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3364.54 | 0.0857535 | 9244.25ms | 1151920 | 1280 | 1.00348e+08 | 326510 | 0.204279 | 1(Win) | true |
| Jsonifier (two-stage) | 3206.74 | 0.0867463 | 9855.51ms | 1151920 | 640 | 5.65196e+07 | 342577 | 0.514263 | 2(Loss) | true |
| Glaze | 2146.85 | 0.175183 | 6984.89ms | 1151920 | 160 | 1.28573e+08 | 511707 | 0.139489 | 3(Loss) | true |
| simdjson (ondemand) | 1896.69 | 0.124684 | 7762.15ms | 1151920 | 320 | 1.66889e+08 | 579197 | 0.00496941 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14787.7 | 0.0695645 | 9368.68ms | 1439562 | 2560 | 1.06776e+07 | 92838.8 | 0.10045 | 1(Win) | true |
| Glaze | 4224.07 | 0.0831709 | 8448.81ms | 1439584 | 640 | 4.67664e+07 | 325017 | 0.0740741 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14790.4 | 0.0751564 | 9454.03ms | 1439562 | 2560 | 1.24586e+07 | 92821.7 | 0.171236 | 1(Win) | true |
| Glaze | 4912.63 | 0.0907029 | 7186.52ms | 1439584 | 1280 | 8.22429e+07 | 279462 | 0.00435314 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2551.65 | 0.07478 | 2182.23ms | 56369 | 4890 | 1.21372e+06 | 21067.8 | 0.0251327 | 1(Win) | true |
| Glaze | 1588.43 | 0.126838 | 3448.59ms | 56369 | 30 | 55279 | 33843.2 | 0.497954 | 2(Loss) | true |
| Jsonifier (two-stage) | 1302.69 | 0.162728 | 4152.32ms | 56369 | 640 | 2.88604e+06 | 41266.6 | 0.0947962 | 3(Loss) | true |
| simdjson (ondemand) | 761.588 | 0.0890503 | 7071.5ms | 56369 | 2560 | 1.01147e+07 | 70586.3 | 0.0889752 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3196.14 | 0.0399563 | 1825.97ms | 56369 | 30 | 1354.94 | 16819.6 | 0.0653573 | 1(Win) | true |
| Glaze | 1899.65 | 0.245194 | 2998.36ms | 56369 | 30 | 144435 | 28298.7 | 0.156535 | 2(Loss) | true |
| Jsonifier (two-stage) | 1680.14 | 0.0332344 | 3883.73ms | 56369 | 30 | 3392.23 | 31995.9 | 0.035121 | 3(Loss) | true |
| simdjson (ondemand) | 830.906 | 0.0578598 | 6664.54ms | 56369 | 4890 | 6.85235e+06 | 64697.7 | 0.0518831 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12630.3 | 0.0368417 | 435.313ms | 56369 | 320 | 786.831 | 4256.24 | 0.0182119 | 1(Win) | true |
| Glaze | 3361.66 | 0.140416 | 1615.67ms | 56369 | 1280 | 645379 | 15991.4 | 0.20536 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13276.1 | 0.0360756 | 427.452ms | 56369 | 320 | 682.841 | 4049.22 | 0.0196836 | 1(Win) | true |
| Glaze | 3908.83 | 0.0680885 | 1392.47ms | 56369 | 30 | 2630.6 | 13752.9 | 0.0819895 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2379.53 | 0.176122 | 3401.78ms | 83958 | 1280 | 4.49554e+06 | 33649 | 0.242167 | 1(Win) | true |
| Glaze | 1873.92 | 0.112434 | 4299.75ms | 83958 | 1280 | 2.95412e+06 | 42727.9 | 0.212253 | 2(Loss) | true |
| Jsonifier (two-stage) | 1784.91 | 0.0910208 | 4505.24ms | 83958 | 2560 | 4.26788e+06 | 44858.6 | 0.108358 | 3(Loss) | true |
| simdjson (ondemand) | 1108.24 | 0.0618779 | 7343.46ms | 83958 | 4890 | 9.77321e+06 | 72248.5 | 0.111799 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2758.6 | 0.0327646 | 3060.59ms | 83958 | 30 | 2713.17 | 29025.1 | 0.0333156 | 1(Win) | true |
| Jsonifier (two-stage) | 2258.83 | 0.177123 | 4228.98ms | 83958 | 40 | 157677 | 35446.9 | 0.112878 | 2(Loss) | true |
| Glaze | 2152.43 | 0.088707 | 3859.77ms | 83958 | 2560 | 2.78754e+06 | 37199.1 | 0.14987 | 3(Loss) | true |
| simdjson (ondemand) | 1212.15 | 0.114846 | 6785.36ms | 83958 | 640 | 3.68319e+06 | 66055.3 | 0.419007 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13354.9 | 0.0777874 | 687.368ms | 94370 | 30 | 824.378 | 6738.97 | 0.264916 | 1(Win) | true |
| Glaze | 2991.19 | 0.125166 | 3052.31ms | 94370 | 2560 | 3.6307e+06 | 30087.7 | 0.13652 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13713.6 | 0.116757 | 666.749ms | 94370 | 30 | 1761.39 | 6562.7 | 0.0859124 | 1(Win) | true |
| Glaze | 3425.83 | 0.0891377 | 2633.94ms | 94370 | 4890 | 2.68144e+06 | 26270.5 | 0.0553785 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1854.63 | 0.0880454 | 2747.72ms | 53331 | 4890 | 2.85079e+06 | 27423.4 | 0.268096 | 1(Win) | true |
| Glaze | 1535.58 | 0.192147 | 3330.59ms | 53331 | 320 | 1.29607e+06 | 33121.2 | 0.0309091 | 2(Loss) | true |
| Jsonifier (two-stage) | 1482.7 | 0.119027 | 3462.8ms | 53331 | 80 | 133363 | 34302.6 | 0.116692 | 3(Loss) | true |
| simdjson (ondemand) | 877.346 | 0.0853451 | 5813.61ms | 53331 | 2560 | 6.26636e+06 | 57970.8 | 0.0854149 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2574.41 | 0.162009 | 2513.27ms | 53331 | 640 | 655639 | 19756.1 | 0.00628009 | 1(Win) | true |
| Jsonifier (two-stage) | 2004.02 | 0.0448152 | 3180.01ms | 53331 | 30 | 3880.86 | 25379.2 | 0.0543457 | 2(Loss) | true |
| Glaze | 1969.9 | 0.0988189 | 3137.36ms | 53331 | 2560 | 1.66644e+06 | 25818.8 | 0.205553 | 3(Loss) | true |
| simdjson (ondemand) | 1012.28 | 0.14304 | 5581.41ms | 53331 | 320 | 1.65281e+06 | 50243.2 | 0.0709107 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14942.3 | 0.0917032 | 379.174ms | 58581 | 30 | 352.671 | 3738.87 | 0.0374585 | 1(Win) | true |
| Glaze | 4865.54 | 0.181829 | 1174.93ms | 58581 | 40 | 17435.7 | 11482.2 | 0.0510469 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16038.3 | 0.147725 | 354.899ms | 58581 | 30 | 794.378 | 3483.37 | 0.00382757 | 1(Win) | true |
| Glaze | 6122.37 | 0.141135 | 920.732ms | 58581 | 2560 | 424601 | 9125.09 | 0.278244 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1824.54 | 0.262456 | 3421.63ms | 65103 | 320 | 2.55246e+06 | 34028.9 | 0.163566 | 1(Win) | true |
| Jsonifier (two-stage) | 1730.23 | 0.066051 | 3611.83ms | 65103 | 4890 | 2.74702e+06 | 35883.7 | 0.0442354 | 2(Loss) | true |
| Glaze | 1689.32 | 0.153292 | 3739.81ms | 65103 | 640 | 2.03139e+06 | 36752.6 | 0.149565 | 3(Loss) | true |
| simdjson (ondemand) | 1053.8 | 0.109679 | 5928.24ms | 65103 | 1280 | 5.34492e+06 | 58917.5 | 0.12769 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2385.03 | 0.11746 | 3236.33ms | 65103 | 1280 | 1.19675e+06 | 26032 | 0.105857 | 1(Win) | true |
| Jsonifier (two-stage) | 2259.25 | 0.0997644 | 3403.07ms | 65103 | 2560 | 1.92426e+06 | 27481.3 | 0.0654567 | 2(Loss) | true |
| Glaze | 2094.09 | 0.131579 | 3486.08ms | 65103 | 1280 | 1.94803e+06 | 29648.7 | 0.0387947 | 3(Loss) | true |
| simdjson (ondemand) | 1196.28 | 0.0996387 | 5723.76ms | 65103 | 2560 | 6.84591e+06 | 51900 | 0.157387 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14125.4 | 0.0820248 | 539.781ms | 78778 | 40 | 761.302 | 5318.68 | 0.0142559 | 1(Win) | true |
| Glaze | 3976.49 | 0.184768 | 1886.83ms | 78778 | 1280 | 1.55982e+06 | 18893.2 | 0.012536 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15498.9 | 0.0854628 | 495.271ms | 78778 | 30 | 514.851 | 4847.33 | 0.0845111 | 1(Win) | true |
| Glaze | 5209.68 | 0.141994 | 1455.49ms | 78778 | 640 | 268353 | 14420.9 | 0.0288943 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2212.5 | 0.0268821 | 554.609ms | 11812 | 320 | 599.456 | 5091.43 | 0.0057078 | 1(Win) | true |
| Jsonifier (two-stage) | 1206.2 | 0.0410333 | 942.645ms | 11812 | 80 | 1174.83 | 9339.1 | 0.0157913 | 2(Loss) | true |
| Glaze | 1051.45 | 0.0904039 | 1083.48ms | 11812 | 4890 | 458725 | 10713.6 | 0.453013 | 3(Loss) | true |
| simdjson (ondemand) | 805.6 | 0.0830197 | 1405.71ms | 11812 | 4890 | 658991 | 13983.1 | 0.116922 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2353.97 | 0.0387381 | 507.44ms | 11812 | 160 | 549.847 | 4785.45 | 0.0410266 | 1(Win) | true |
| Jsonifier (two-stage) | 1385.11 | 0.0165615 | 929.44ms | 11812 | 320 | 580.537 | 8132.8 | 7.68494e-05 | 2(Loss) | true |
| Glaze | 1113.84 | 0.256706 | 1030.94ms | 11812 | 1280 | 862743 | 10113.4 | 0.220738 | 3(Loss) | true |
| simdjson (ondemand) | 854.923 | 0.11987 | 1353.57ms | 11812 | 30 | 7484.04 | 13176.4 | 0.0417239 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10229.6 | 0.147309 | 114.903ms | 11812 | 4890 | 12867.6 | 1101.2 | 0.118573 | 1(Win) | true |
| Glaze | 2354.24 | 0.0420395 | 489.854ms | 11812 | 320 | 1294.83 | 4784.9 | 0.191003 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10524.9 | 0.203178 | 109.637ms | 11812 | 80 | 378.314 | 1070.3 | 0.142687 | 1(Win) | true |
| Glaze | 2628.32 | 0.0443533 | 437.055ms | 11812 | 160 | 578.178 | 4285.93 | 0.132962 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2939.96 | 0.0425702 | 836.588ms | 25388 | 40 | 491.638 | 8235.45 | 0.0431249 | 1(Win) | true |
| Jsonifier (two-stage) | 2306.7 | 0.0394681 | 1066.92ms | 25388 | 80 | 1372.95 | 10496.3 | 0.0153602 | 2(Loss) | true |
| Glaze | 1764.34 | 0.13427 | 1394.53ms | 25388 | 40 | 13580.3 | 13722.9 | 0.0251949 | 3(Loss) | true |
| simdjson (ondemand) | 1631.64 | 0.062362 | 1507.76ms | 25388 | 80 | 6850.78 | 14839 | 0.108953 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3044.82 | 0.0221134 | 827.337ms | 25388 | 160 | 494.728 | 7951.84 | 0.00958806 | 1(Win) | true |
| Jsonifier (two-stage) | 2572.38 | 0.0213447 | 1054.72ms | 25388 | 160 | 645.78 | 9412.24 | 0.129716 | 2(Loss) | true |
| Glaze | 1825 | 0.0877714 | 1393.15ms | 25388 | 4890 | 663046 | 13266.8 | 0.558739 | 3(Loss) | true |
| simdjson (ondemand) | 1707.9 | 0.0900235 | 1452.05ms | 25388 | 30 | 4886.1 | 14176.4 | 0.0578762 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14161.2 | 0.0303114 | 215.268ms | 31235 | 1280 | 520.363 | 2103.5 | 0.0652613 | 1(Win) | true |
| Glaze | 3820.21 | 0.0422541 | 798.236ms | 31235 | 80 | 868.43 | 7797.48 | 0.126483 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15541.3 | 0.105157 | 196.765ms | 31235 | 30 | 121.872 | 1916.7 | 0.00347832 | 1(Win) | true |
| Glaze | 4190.58 | 0.174741 | 703.885ms | 31235 | 30 | 4628.57 | 7108.33 | 0.48866 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2739.18 | 0.0948269 | 3781.52ms | 108313 | 2560 | 3.27357e+06 | 37710.2 | 0.0837146 | 1(Win) | true |
| Jsonifier (two-stage) | 1723.28 | 0.0685312 | 6025.92ms | 108313 | 4890 | 8.25155e+06 | 59941.1 | 0.103142 | 2(Loss) | true |
| Glaze | 1539.89 | 0.0900865 | 6750.31ms | 108313 | 1280 | 4.67424e+06 | 67079.7 | 0.0695644 | 3(Loss) | true |
| simdjson (ondemand) | 677.723 | 0.200104 | 7843.22ms | 108313 | 320 | 2.97659e+07 | 152415 | 0.0401353 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3237.79 | 0.0808677 | 3524.77ms | 108313 | 4890 | 3.2548e+06 | 31903.1 | 0.0607845 | 1(Win) | true |
| Jsonifier (two-stage) | 1916.89 | 0.0933491 | 5668.61ms | 108313 | 2560 | 6.47777e+06 | 53886.8 | 0.0368403 | 2(Loss) | true |
| Glaze | 1671.64 | 0.165885 | 6455.62ms | 108313 | 640 | 6.72467e+06 | 61792.8 | 0.031072 | 3(Loss) | true |
| simdjson (ondemand) | 704.929 | 0.0785917 | 7627.66ms | 108313 | 2560 | 3.39519e+07 | 146533 | 0.0388817 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13804 | 0.128539 | 752.194ms | 108313 | 4890 | 452407 | 7482.99 | 0.0616889 | 1(Win) | true |
| Glaze | 2346.47 | 0.0686135 | 4497.64ms | 108313 | 4890 | 4.46129e+06 | 44021.6 | 0.3964 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14489 | 0.261246 | 714.122ms | 108313 | 40 | 13875.2 | 7129.2 | 0.0784885 | 1(Win) | true |
| Glaze | 2539.9 | 0.10557 | 4087.24ms | 108313 | 2560 | 4.719e+06 | 40669.1 | 0.0368714 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2828.18 | 0.0623184 | 6260.25ms | 183677 | 4890 | 7.28511e+06 | 61936.6 | 0.11032 | 1(Win) | true |
| Jsonifier (two-stage) | 2527.68 | 0.0858871 | 7003.76ms | 183677 | 2560 | 9.06901e+06 | 69299.8 | 0.0164163 | 2(Loss) | true |
| Glaze | 1920.6 | 0.0728969 | 9216.43ms | 183677 | 2560 | 1.13161e+07 | 91205.1 | 0.0242588 | 3(Loss) | true |
| simdjson (ondemand) | 1117.19 | 0.0679014 | 8087.79ms | 183677 | 2560 | 2.90172e+07 | 156794 | 0.0219871 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3128.44 | 0.0732233 | 5896.67ms | 183677 | 4890 | 8.21982e+06 | 55992.2 | 0.101303 | 1(Win) | true |
| Jsonifier (two-stage) | 2778.01 | 0.136229 | 6657.54ms | 183677 | 320 | 2.36118e+06 | 63055.3 | 0.0142108 | 2(Loss) | true |
| Glaze | 2048.06 | 0.113808 | 8836.89ms | 183677 | 1280 | 1.21276e+07 | 85528.6 | 0.0213662 | 3(Loss) | true |
| simdjson (ondemand) | 1165.03 | 0.138756 | 7853.89ms | 183677 | 320 | 1.39281e+07 | 150355 | 0.110521 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16113.9 | 0.0957156 | 1280.72ms | 213963 | 80 | 11752.6 | 12663 | 0.160446 | 1(Win) | true |
| Glaze | 3214.93 | 0.0867154 | 6427.25ms | 213963 | 4890 | 1.48128e+07 | 63469.8 | 0.0683499 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16580 | 0.0565947 | 1249.04ms | 213963 | 160 | 7762.09 | 12307 | 0.0109197 | 1(Win) | true |
| Glaze | 3639.48 | 0.143649 | 5672.55ms | 213963 | 1280 | 8.30253e+06 | 56065.9 | 0.178403 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 689.336 | 0.205566 | 7904.64ms | 1834197 | 80 | 2.17682e+09 | 2.53755e+06 | 0.0493819 | 1(Win) | true |
| Jsonifier (two-stage) | 599.35 | 0.143184 | 9104.83ms | 1834197 | 160 | 2.79411e+09 | 2.91854e+06 | 0.304023 | 2(Loss) | true |
| Glaze | 490.272 | 0.22757 | 5362.86ms | 1834197 | 30 | 1.97773e+09 | 3.56787e+06 | 0.000426957 | 3(Loss) | true |
| simdjson (ondemand) | 415.8 | 0.150547 | 6362.72ms | 1834197 | 80 | 3.20891e+09 | 4.20689e+06 | 0.0023673 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 795.174 | 0.110893 | 7934.23ms | 1834197 | 160 | 9.52125e+08 | 2.1998e+06 | 0.00338854 | 1(Win) | true |
| Jsonifier (two-stage) | 676.989 | 0.167602 | 9110.98ms | 1834197 | 160 | 3.00059e+09 | 2.58383e+06 | 0.00836594 | 2(Loss) | true |
| Glaze | 541.068 | 0.188821 | 5400.83ms | 1834197 | 80 | 2.98111e+09 | 3.23292e+06 | 0.154211 | 3(Loss) | true |
| simdjson (ondemand) | 449.921 | 0.36773 | 6345.43ms | 1834197 | 40 | 8.17593e+09 | 3.88785e+06 | 0.389511 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1555.17 | 0.178643 | 7092.58ms | 1834197 | 160 | 6.45991e+08 | 1.12478e+06 | 0.10006 | 1(Win) | true |
| Glaze | 922.009 | 0.206391 | 5925.38ms | 1833577 | 40 | 6.1287e+08 | 1.89655e+06 | 0.2127 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1561.75 | 0.201373 | 7138.25ms | 1834197 | 160 | 8.13941e+08 | 1.12004e+06 | 0.0469003 | 1(Win) | true |
| Glaze | 921.685 | 0.143539 | 5945.87ms | 1833577 | 160 | 1.18658e+09 | 1.89722e+06 | 0.0988178 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2130.29 | 0.199748 | 10262.4ms | 7351818 | 160 | 6.91508e+09 | 3.29122e+06 | 0.463826 | 1(Win) | true |
| Jsonifier (two-stage) | 2028.97 | 0.127412 | 5224.59ms | 7351818 | 80 | 1.55077e+09 | 3.45557e+06 | 0.0410523 | 2(Loss) | true |
| Glaze | 1548.8 | 0.18362 | 6859.48ms | 7351818 | 30 | 2.07281e+09 | 4.52689e+06 | 0.00763748 | 3(Loss) | true |
| simdjson (ondemand) | 1238.38 | 2.25394 | 8624.98ms | 7351818 | 40 | 6.51365e+11 | 5.66162e+06 | 3.58495 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2373.23 | 0.124031 | 10239.6ms | 7351818 | 160 | 2.14829e+09 | 2.95431e+06 | 0.10149 | 1(Win) | true |
| Jsonifier (two-stage) | 2251.73 | 0.205086 | 5836.03ms | 7351818 | 30 | 1.22335e+09 | 3.11371e+06 | 0.118556 | 2(Loss) | true |
| Glaze | 1662.68 | 0.280354 | 6917.61ms | 7351818 | 40 | 5.59047e+09 | 4.21684e+06 | 0.00961732 | 3(Loss) | true |
| simdjson (ondemand) | 1311.25 | 0.696182 | 8835.98ms | 7351818 | 80 | 1.10854e+11 | 5.34698e+06 | 0.0849155 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4560.51 | 1.27174 | 6527.81ms | 9930848 | 80 | 5.57998e+10 | 2.07669e+06 | 0.870331 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 2642.35 | 1.90974 | 5009.44ms | 9930228 | 40 | 1.8739e+11 | 3.58401e+06 | 6.96505 | -(Loss) | false |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4432.63 | 1.91599 | 6609.91ms | 9930848 | 30 | 5.02757e+10 | 2.13661e+06 | 0.469578 | 1(Win) | true |
| Glaze | 2688.24 | 1.22152 | 5132.69ms | 9930228 | 30 | 5.5553e+10 | 3.52282e+06 | 2.70866 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 608.845 | 0.181989 | 8973.9ms | 1834197 | 160 | 4.3741e+09 | 2.87303e+06 | 0.0516129 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 605.001 | 0.604629 | 8789.2ms | 1834197 | 40 | 1.22241e+10 | 2.89128e+06 | 3.02804 | 1(Tie) | true |
| simdjson (ondemand) | 417.264 | 0.186298 | 6382.92ms | 1834197 | 30 | 1.82982e+09 | 4.19214e+06 | 1.36386 | 3(Loss) | true |
| Glaze | 396.337 | 1.67018 | 6558.45ms | 1834197 | 40 | 2.17345e+11 | 4.41348e+06 | 0.47184 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 819.571 | 0.302591 | 8217.15ms | 1834197 | 40 | 1.66836e+09 | 2.13432e+06 | 0.244518 | 1(Win) | true |
| Jsonifier (two-stage) | 687.313 | 0.229975 | 8972.34ms | 1834197 | 160 | 5.48107e+09 | 2.54502e+06 | 0.162668 | 2(Loss) | true |
| Glaze | 497.513 | 1.68376 | 6041.55ms | 1834197 | 40 | 1.40186e+11 | 3.51594e+06 | 0.163458 | 3(Loss) | true |
| simdjson (ondemand) | 453.259 | 0.182898 | 6380.97ms | 1834197 | 40 | 1.99287e+09 | 3.85922e+06 | 0.885656 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1561.73 | 0.256096 | 7080.89ms | 1834197 | 160 | 1.31646e+09 | 1.12006e+06 | 0.263818 | 1(Win) | true |
| Glaze | 895.572 | 0.301418 | 6115.83ms | 1833577 | 80 | 2.77093e+09 | 1.95253e+06 | 0.0190853 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1563.69 | 0.407548 | 7117.61ms | 1834197 | 40 | 8.31395e+08 | 1.11865e+06 | 0.129646 | 1(Win) | true |
| Glaze | 904.088 | 0.333974 | 5963.05ms | 1833577 | 80 | 3.33804e+09 | 1.93414e+06 | 0.13342 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2158.59 | 0.240847 | 10084.9ms | 7351818 | 160 | 9.79149e+09 | 3.24806e+06 | 0.00268571 | 1(Win) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 1953.89 | 0.283885 | 5209.51ms | 7351818 | 80 | 8.30168e+09 | 3.58835e+06 | 5.07687 | -(Loss) | false |
| Glaze | 1544.43 | 0.209573 | 6874.31ms | 7351818 | 40 | 3.62065e+09 | 4.5397e+06 | 0.0249609 | 3(Loss) | true |
| simdjson (ondemand) | 1465.7 | 0.231437 | 7250.02ms | 7351818 | 40 | 4.90259e+09 | 4.78355e+06 | 0.0250084 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2406.21 | 0.243262 | 10068.4ms | 7351818 | 160 | 8.03881e+09 | 2.91381e+06 | 0.309964 | 1(Win) | true |
| Jsonifier (two-stage) | 2269.9 | 0.277072 | 5205.65ms | 7351818 | 80 | 5.85939e+09 | 3.08879e+06 | 0.394878 | 2(Loss) | true |
| Glaze | 1659.38 | 0.17782 | 6843.53ms | 7351818 | 40 | 2.25799e+09 | 4.22522e+06 | 0.120432 | 3(Loss) | true |
| simdjson (ondemand) | 1572.9 | 0.144274 | 7233.2ms | 7351818 | 80 | 3.30866e+09 | 4.45753e+06 | 0.0712485 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5630.84 | 0.139451 | 5247.37ms | 9930848 | 160 | 8.80219e+08 | 1.68195e+06 | 0.111158 | 1(Win) | true |
| Glaze | 2999.6 | 0.0925913 | 9841.68ms | 9930228 | 160 | 1.36726e+09 | 3.15716e+06 | 0.007657 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5611.32 | 0.269655 | 5247.74ms | 9930848 | 160 | 3.31422e+09 | 1.6878e+06 | 0.0551439 | 1(Win) | true |
| Glaze | 3434.18 | 0.193322 | 8597.27ms | 9930228 | 160 | 4.54733e+09 | 2.75763e+06 | 0.172869 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1294.06 | 0.131689 | 8768.03ms | 461466 | 320 | 6.4183e+07 | 340084 | 0.128599 | 1(Win) | true |
| Jsonifier (two-stage) | 989.225 | 0.138046 | 5674.25ms | 461466 | 160 | 6.03471e+07 | 444882 | 0.37546 | 2(Loss) | true |
| Glaze | 865.257 | 0.166603 | 6474.94ms | 461466 | 320 | 2.29776e+08 | 508622 | 0.0378599 | 3(Loss) | true |
| simdjson (ondemand) | 658.279 | 0.132835 | 8566.41ms | 461466 | 320 | 2.52367e+08 | 668544 | 0.0268842 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1744.99 | 0.0869162 | 8477.98ms | 461466 | 1280 | 6.15043e+07 | 252201 | 0.018895 | 1(Win) | true |
| Jsonifier (two-stage) | 1343.14 | 0.228179 | 5545.32ms | 461466 | 160 | 8.9435e+07 | 327655 | 0.0500032 | 2(Loss) | true |
| Glaze | 1045.75 | 0.259165 | 6362.96ms | 461466 | 80 | 9.51636e+07 | 420837 | 0.037726 | 3(Loss) | true |
| simdjson (ondemand) | 749.384 | 0.154341 | 8372.13ms | 461466 | 640 | 5.25788e+08 | 587267 | 0.0720214 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11105.1 | 0.194288 | 4000.35ms | 461466 | 160 | 948519 | 39629.4 | 0.0123976 | 1(Win) | true |
| Glaze | 2755.01 | 0.11336 | 8270.21ms | 461466 | 640 | 2.09861e+07 | 159741 | 0.18659 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11210.7 | 0.0222691 | 4027.71ms | 461466 | 80 | 6113.81 | 39256.2 | 0.00834194 | 1(Win) | true |
| Glaze | 2961.7 | 0.085886 | 7637.22ms | 461466 | 2560 | 4.16948e+07 | 148593 | 0.00379956 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1607.89 | 0.149218 | 5524.46ms | 728486 | 640 | 2.66043e+08 | 432081 | 0.132628 | 1(Win) | true |
| Jsonifier (two-stage) | 1239.84 | 0.0958112 | 7178.35ms | 728486 | 640 | 1.8447e+08 | 560346 | 0.0513289 | 2(Loss) | true |
| Glaze | 1204.8 | 0.166729 | 7390.49ms | 728486 | 320 | 2.95795e+08 | 576644 | 0.0895569 | 3(Loss) | true |
| simdjson (ondemand) | 992.14 | 0.128185 | 9239.24ms | 728486 | 320 | 2.57821e+08 | 700242 | 0.0751336 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2042.65 | 0.102904 | 5289.88ms | 728486 | 640 | 7.83968e+07 | 340115 | 0.27157 | 1(Win) | true |
| Jsonifier (two-stage) | 1777.85 | 0.205834 | 6997.92ms | 728486 | 160 | 1.03515e+08 | 390774 | 0.000470223 | 2(Loss) | true |
| Glaze | 1424.6 | 0.234868 | 7234.32ms | 728486 | 80 | 1.04952e+08 | 487671 | 0.167413 | 3(Loss) | true |
| simdjson (ondemand) | 1130.98 | 0.188881 | 8832.51ms | 728486 | 320 | 4.30786e+08 | 614281 | 0.0644838 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11641.6 | 0.132253 | 6872.31ms | 837491 | 1280 | 1.05379e+07 | 68607.1 | 0.0338112 | 1(Win) | true |
| Glaze | 3288.35 | 0.15895 | 6254.84ms | 837491 | 160 | 2.38475e+07 | 242886 | 0.0348845 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13452.6 | 0.528624 | 6014.88ms | 837491 | 160 | 1.57601e+07 | 59370.8 | 0.814448 | 1(Win) | true |
| Glaze | 3597.14 | 0.102035 | 5718.8ms | 837491 | 1280 | 6.56982e+07 | 222036 | 0.102443 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4943.54 | 0.223194 | 9122.41ms | 466906 | 80 | 3.23323e+06 | 90072.3 | 0.0479428 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4925.24 | 0.131975 | 9141.16ms | 466906 | 640 | 9.11111e+06 | 90407.1 | 0.239131 | 1(Tie) | true |
| simdjson (ondemand) | 4074.43 | 0.112666 | 5637.77ms | 466906 | 1280 | 1.94054e+07 | 109286 | 0.170929 | 3(Loss) | true |
| Glaze | 2301.68 | 0.204909 | 10017.8ms | 466906 | 80 | 1.25713e+07 | 193457 | 0.0455348 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 5030.25 | 0.226146 | 9103.83ms | 466906 | 160 | 6.41178e+06 | 88519.8 | 0.013544 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 5014.2 | 0.0534946 | 9112.85ms | 466906 | 4890 | 1.10353e+07 | 88803 | 0.22965 | 1(Tie) | true |
| simdjson (ondemand) | 4188.92 | 0.200049 | 5575.52ms | 466906 | 30 | 1.35659e+06 | 106299 | 0.306151 | 3(Loss) | true |
| Glaze | 2291.37 | 0.102896 | 5001.2ms | 466906 | 1280 | 5.11771e+07 | 194328 | 0.114479 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5414.4 | 0.135505 | 5856ms | 631514 | 640 | 1.45398e+07 | 111233 | 0.154819 | 1(Win) | true |
| Jsonifier (two-stage) | 5380.12 | 0.275715 | 5759.19ms | 631514 | 320 | 3.04827e+07 | 111942 | 0.240117 | 2(Loss) | true |
| simdjson (ondemand) | 4832.61 | 0.0677313 | 6386.61ms | 631514 | 2560 | 1.82398e+07 | 124624 | 0.106821 | 3(Loss) | true |
| Glaze | 2766.89 | 0.257428 | 5642.09ms | 631514 | 30 | 9.41926e+06 | 217667 | 0.377604 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5545.1 | 0.143882 | 5687.56ms | 631514 | 160 | 3.90731e+06 | 108611 | 0.033606 | 1(Win) | true |
| Jsonifier (two-stage) | 5486.67 | 0.127387 | 5691.47ms | 631514 | 640 | 1.25136e+07 | 109768 | 0.0141771 | 2(Loss) | true |
| simdjson (ondemand) | 4918 | 0.129963 | 6416.99ms | 631514 | 640 | 1.62109e+07 | 122460 | 0.187525 | 3(Loss) | true |
| Glaze | 2797.68 | 0.255643 | 5647.65ms | 631514 | 40 | 1.21143e+07 | 215271 | 0.107853 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2276.16 | 0.142824 | 5043.17ms | 466906 | 320 | 2.49806e+07 | 195626 | 0.0265568 | 1(Win) | true |
| Glaze | 1775.2 | 0.245918 | 6484.14ms | 466906 | 40 | 1.52196e+07 | 250831 | 0.0412133 | 2(Loss) | true |
| Jsonifier (two-stage) | 1755.94 | 0.132718 | 6472.74ms | 466906 | 320 | 3.62451e+07 | 253583 | 0.16001 | 3(Loss) | true |
| simdjson (ondemand) | 838.825 | 0.083859 | 6766.76ms | 466906 | 640 | 1.26822e+08 | 530834 | 0.0268262 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2907.93 | 0.112749 | 9350.25ms | 466906 | 640 | 1.90764e+07 | 153125 | 0.0749665 | 1(Win) | true |
| Jsonifier (two-stage) | 2184.7 | 0.127501 | 6160.13ms | 466906 | 320 | 2.16099e+07 | 203816 | 0.0197629 | 2(Loss) | true |
| Glaze | 2117.23 | 0.123495 | 6069.8ms | 466906 | 1280 | 8.63436e+07 | 210310 | 0.082806 | 3(Loss) | true |
| simdjson (ondemand) | 907.351 | 0.186377 | 6631.88ms | 466906 | 30 | 2.50966e+07 | 490743 | 0.0260693 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15480.1 | 0.0458433 | 2950.16ms | 475954 | 80 | 14455.2 | 29321.8 | 0.420562 | 1(Win) | true |
| Glaze | 4524.44 | 0.353488 | 5245.61ms | 475954 | 40 | 5.03048e+06 | 100323 | 0.0949588 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15564 | 0.0768747 | 2915.51ms | 475954 | 4890 | 2.45791e+06 | 29163.9 | 0.538572 | 1(Win) | true |
| Glaze | 5021.88 | 0.131477 | 9136.35ms | 475954 | 640 | 9.03808e+06 | 90385.5 | 0.00412141 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2276.29 | 0.131827 | 6882.17ms | 631514 | 640 | 7.78581e+07 | 264579 | 0.0716143 | 1(Win) | true |
| Jsonifier (two-stage) | 2188.27 | 0.216719 | 7110.14ms | 631514 | 160 | 5.6922e+07 | 275221 | 0.208411 | 2(Loss) | true |
| Glaze | 1967.01 | 0.272988 | 7914.24ms | 631514 | 30 | 2.09585e+07 | 306179 | 0.412752 | 3(Loss) | true |
| simdjson (ondemand) | 1095.89 | 0.470812 | 7004.91ms | 631514 | 30 | 2.0084e+08 | 549563 | 0.15391 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2703.15 | 0.344209 | 6444.96ms | 631514 | 40 | 2.3525e+07 | 222799 | 0.0216554 | 1(Win) | true |
| Jsonifier (two-stage) | 2674.36 | 0.0700175 | 6687.24ms | 631514 | 1280 | 3.18235e+07 | 225197 | 0.193897 | 2(Loss) | true |
| Glaze | 2268.97 | 0.086443 | 7529.89ms | 631514 | 1280 | 6.73875e+07 | 265433 | 0.58605 | 3(Loss) | true |
| simdjson (ondemand) | 1191.34 | 0.16198 | 6826.29ms | 631514 | 30 | 2.0116e+07 | 505532 | 0.0817742 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15788.4 | 0.173783 | 4414.88ms | 716365 | 320 | 1.80949e+06 | 43270.8 | 0.0535723 | 1(Win) | true |
| Glaze | 4084.22 | 0.255548 | 8664.79ms | 716365 | 160 | 2.92358e+07 | 167273 | 0.108171 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15851.1 | 0.100999 | 4325.54ms | 716365 | 2560 | 4.85089e+06 | 43099.8 | 0.201737 | 1(Win) | true |
| Glaze | 4745.09 | 0.32643 | 7355.36ms | 716365 | 160 | 3.53412e+07 | 143976 | 0.227346 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1612.91 | 0.10416 | 160.227ms | 2632 | 160 | 420.409 | 1556.24 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 1351.25 | 0.121938 | 189.757ms | 2632 | 2560 | 13134.8 | 1857.6 | 0.187843 | 2(Loss) | true |
| Glaze | 1173.15 | 0.18483 | 217.66ms | 2632 | 2560 | 40035.6 | 2139.59 | 0.393723 | 3(Loss) | true |
| simdjson (ondemand) | 941.627 | 0.115085 | 274.378ms | 2632 | 160 | 1505.82 | 2665.68 | 0.237369 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2184.17 | 0.148977 | 141.972ms | 2632 | 160 | 468.986 | 1149.21 | 0.0684783 | 1(Win) | true |
| Jsonifier (two-stage) | 1737.25 | 0.151979 | 176.184ms | 2632 | 80 | 385.749 | 1444.85 | 0.0761905 | 2(Loss) | true |
| Glaze | 1718.59 | 0.167535 | 170.247ms | 2632 | 640 | 3831.96 | 1460.54 | 0.222909 | 3(Loss) | true |
| simdjson (ondemand) | 1225.24 | 0.171429 | 231.039ms | 2632 | 640 | 7893.65 | 2048.63 | 0.118053 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9240.73 | 0.152715 | 30.2093ms | 2632 | 2560 | 440.52 | 271.631 | 0.171985 | 1(Win) | true |
| Glaze | 2953.26 | 0.506104 | 96.5016ms | 2632 | 30 | 555.099 | 849.933 | 0.816866 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10103.6 | 0.220213 | 27.7953ms | 2632 | 320 | 95.7762 | 248.434 | 0.00377349 | 1(Win) | true |
| Glaze | 3788.18 | 0.152492 | 72.401ms | 2632 | 320 | 326.703 | 662.606 | 0.132821 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1700.25 | 0.0662713 | 196.623ms | 3370 | 320 | 502.15 | 1890.24 | 0.102395 | 1(Win) | true |
| Jsonifier (two-stage) | 1635.85 | 0.049516 | 202.432ms | 3370 | 320 | 302.841 | 1964.66 | 0.048649 | 2(Loss) | true |
| Glaze | 1376.14 | 0.111521 | 237.114ms | 3370 | 160 | 1085.35 | 2335.43 | 0.0858312 | 3(Loss) | true |
| simdjson (ondemand) | 1174.44 | 0.148814 | 278.614ms | 3370 | 4890 | 81095.1 | 2736.52 | 0.0954283 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2152.38 | 0.136086 | 177.328ms | 3370 | 80 | 330.323 | 1493.17 | 0.0384937 | 1(Win) | true |
| Jsonifier (two-stage) | 2071.56 | 0.0476457 | 186.841ms | 3370 | 640 | 349.698 | 1551.43 | 0.016822 | 2(Loss) | true |
| Glaze | 1895.8 | 0.133471 | 194.055ms | 3370 | 4890 | 25035.7 | 1695.26 | 0.664052 | 3(Loss) | true |
| simdjson (ondemand) | 1546.54 | 0.139863 | 236.762ms | 3370 | 80 | 675.823 | 2078.11 | 0.04995 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9839.07 | 0.478972 | 42.912ms | 3643 | 160 | 457.668 | 353.106 | 0.143576 | 1(Win) | true |
| Glaze | 3258.01 | 0.172197 | 111.4ms | 3682 | 2560 | 8817.72 | 1077.78 | 0.0201472 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10511 | 0.586673 | 40.4635ms | 3643 | 30 | 112.809 | 330.533 | 0.833842 | 1(Win) | true |
| Glaze | 3895.39 | 0.0926908 | 94.0132ms | 3682 | 640 | 446.806 | 901.431 | 0.0592456 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 755.463 | 0.169195 | 594.042ms | 4630 | 40 | 3911.77 | 5844.77 | 0.0676785 | 1(Win) | true |
| Jsonifier (two-stage) | 687.467 | 0.140474 | 652.631ms | 4630 | 40 | 3256.21 | 6422.88 | 0.0548519 | 2(Loss) | true |
| Glaze | 486.558 | 0.303795 | 919.989ms | 4630 | 320 | 243222 | 9075 | 0.0974434 | 3(Loss) | true |
| simdjson (ondemand) | 453.016 | 0.0331798 | 989.53ms | 4630 | 160 | 1673.41 | 9746.93 | 0.0488212 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 926.344 | 0.167511 | 596.049ms | 4630 | 40 | 2550.14 | 4766.6 | 0.293545 | 1(Win) | true |
| Jsonifier (two-stage) | 730.906 | 0.524448 | 682.989ms | 4630 | 640 | 642427 | 6041.15 | 0.0817677 | 2(Loss) | true |
| Glaze | 550.739 | 0.125187 | 914.074ms | 4630 | 4890 | 492601 | 8017.43 | 0.0340476 | 3(Loss) | true |
| simdjson (ondemand) | 505.577 | 0.135571 | 981.72ms | 4630 | 4890 | 685540 | 8733.62 | 0.101688 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2784.62 | 0.0539025 | 164.631ms | 4630 | 640 | 467.551 | 1585.68 | 0.0673469 | 1(Win) | true |
| Glaze | 1605.79 | 0.135952 | 279.644ms | 4630 | 2560 | 35776.4 | 2749.75 | 0.0157234 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2895.53 | 0.0683573 | 157.093ms | 4630 | 640 | 695.433 | 1524.94 | 0.0473603 | 1(Win) | true |
| Glaze | 1855.48 | 0.0883902 | 244.229ms | 4630 | 80 | 353.954 | 2379.71 | 0.19659 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1580.62 | 0.0489083 | 722.388ms | 11579 | 160 | 1867.98 | 6986.24 | 0.0101976 | 1(Win) | true |
| Jsonifier (two-stage) | 1524.04 | 0.0541057 | 735.718ms | 11579 | 160 | 2458.97 | 7245.59 | 0.153822 | 2(Loss) | true |
| simdjson (ondemand) | 1059.45 | 0.0526517 | 1058.39ms | 11579 | 40 | 1204.66 | 10423 | 0.033111 | 3(Loss) | true |
| Glaze | 1053 | 0.0252449 | 1063.89ms | 11579 | 160 | 1121.38 | 10486.8 | 0.0275867 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1827.28 | 0.112687 | 725.78ms | 11579 | 80 | 3709.96 | 6043.2 | 0.0948244 | 1(Win) | true |
| Jsonifier (two-stage) | 1789.45 | 0.125871 | 759.595ms | 11579 | 4890 | 295026 | 6170.93 | 0.174788 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1174.62 | 0.105341 | 1049.21ms | 11579 | 4890 | 479572 | 9401.03 | 0.00894083 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 1174.19 | 0.0308108 | 1061.16ms | 11579 | 160 | 1343.35 | 9404.41 | 0.120034 | 3(Tie) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7021.71 | 0.144078 | 205.068ms | 14795 | 2560 | 21457.7 | 2009.43 | 0.109112 | 1(Win) | true |
| Glaze | 3418.37 | 0.0486738 | 421.066ms | 14795 | 80 | 322.904 | 4127.59 | 0.0106005 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7336.93 | 0.212642 | 197.06ms | 14795 | 1280 | 21404.7 | 1923.09 | 0.00889759 | 1(Win) | true |
| Glaze | 3906.86 | 0.104257 | 369.819ms | 14795 | 40 | 567.077 | 3611.5 | 0.0129234 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1263.81 | 0.108732 | 247.799ms | 3223 | 4890 | 34196.6 | 2432.09 | 0.179603 | 1(Win) | true |
| Jsonifier (two-stage) | 973.18 | 0.116679 | 326.377ms | 3223 | 30 | 407.421 | 3158.4 | 0.00422172 | 2(Loss) | true |
| Glaze | 877.155 | 0.21566 | 357.367ms | 3223 | 80 | 4568.77 | 3504.16 | 0.0289026 | 3(Loss) | true |
| simdjson (ondemand) | 703.728 | 0.139545 | 446.421ms | 3223 | 80 | 2971.87 | 4367.73 | 0.072172 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1956.6 | 0.127434 | 213.457ms | 3223 | 2560 | 10259.6 | 1570.93 | 0.122265 | 1(Win) | true |
| Jsonifier (two-stage) | 1382.54 | 0.0852142 | 287.294ms | 3223 | 160 | 574.264 | 2223.22 | 0.0157454 | 2(Loss) | true |
| Glaze | 1184.15 | 0.0713712 | 313.236ms | 3223 | 640 | 2196.52 | 2595.7 | 0.255419 | 3(Loss) | true |
| simdjson (ondemand) | 880.746 | 0.126969 | 399.759ms | 3223 | 160 | 3141.47 | 3489.88 | 0.0960842 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7866.66 | 0.0969706 | 41.9374ms | 3223 | 4890 | 701.987 | 390.724 | 0.0387827 | 1(Win) | true |
| Glaze | 1961.13 | 0.0563215 | 161.618ms | 3223 | 640 | 498.699 | 1567.31 | 0.0235331 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9527.61 | 0.0818717 | 35.728ms | 3223 | 4890 | 341.138 | 322.609 | 0.141872 | 1(Win) | true |
| Glaze | 2029.49 | 0.706416 | 165.613ms | 3223 | 80 | 9157.06 | 1514.51 | 0.0718569 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1731.14 | 0.140864 | 332.602ms | 5839 | 40 | 821.251 | 3216.68 | 0.134117 | 1(Win) | true |
| Jsonifier (two-stage) | 1602.67 | 0.0531309 | 355.204ms | 5839 | 160 | 545.258 | 3474.51 | 0.0715416 | 2(Loss) | true |
| Glaze | 1269.32 | 0.161103 | 444.075ms | 5839 | 2560 | 127875 | 4387.01 | 0.140186 | 3(Loss) | true |
| simdjson (ondemand) | 1228.01 | 0.081171 | 461.674ms | 5839 | 160 | 2167.69 | 4534.59 | 0.0416072 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2346.83 | 0.14121 | 294.109ms | 5839 | 2560 | 28740.1 | 2372.78 | 0.0943741 | 1(Win) | true |
| Jsonifier (two-stage) | 2234.8 | 0.122296 | 316.876ms | 5839 | 40 | 371.435 | 2491.72 | 0.0538159 | 2(Loss) | true |
| Glaze | 1603.39 | 0.140018 | 409.768ms | 5839 | 80 | 1891.73 | 3472.96 | 0.0579141 | 3(Loss) | true |
| simdjson (ondemand) | 1511.85 | 0.26879 | 418.428ms | 5839 | 30 | 2940.39 | 3683.23 | 0.110532 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12065.7 | 0.0657517 | 58.4957ms | 6938 | 2560 | 332.828 | 548.382 | 0.163637 | 1(Win) | true |
| Glaze | 2854.51 | 0.0801493 | 236.115ms | 6960 | 4890 | 16984.9 | 2325.29 | 0.0142121 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13316.8 | 0.158274 | 52.7958ms | 6938 | 320 | 197.896 | 496.859 | 0.161379 | 1(Win) | true |
| Glaze | 3241.12 | 0.131653 | 210.224ms | 6960 | 80 | 581.539 | 2047.92 | 0.0525197 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2166.51 | 0.0648165 | 216.849ms | 4857 | 320 | 614.52 | 2138 | 0.194191 | 1(Win) | true |
| Glaze | 1363.31 | 0.435377 | 342.676ms | 4857 | 1280 | 280086 | 3397.62 | 0.419532 | 2(Loss) | true |
| Jsonifier (two-stage) | 1268.78 | 0.0580135 | 372.546ms | 4857 | 160 | 717.698 | 3650.75 | 0.00684744 | 3(Loss) | true |
| simdjson (ondemand) | 639.614 | 0.0700042 | 782.783ms | 4857 | 160 | 4112.14 | 7241.86 | 0.212239 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2777.04 | 0.104828 | 191.939ms | 4857 | 160 | 489.156 | 1667.96 | 0.110043 | 1(Win) | true |
| Glaze | 1847.49 | 0.123809 | 266.687ms | 4857 | 2560 | 24667 | 2507.18 | 0.166424 | 2(Loss) | true |
| Jsonifier (two-stage) | 1708.1 | 0.0785572 | 329.864ms | 4857 | 80 | 363.056 | 2711.79 | 0.168531 | 3(Loss) | true |
| simdjson (ondemand) | 729.442 | 0.181389 | 655.46ms | 4857 | 40 | 5306.82 | 6350.05 | 0.325705 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11695.8 | 0.246264 | 42.709ms | 4857 | 4890 | 4651.42 | 396.039 | 0.564436 | 1(Win) | true |
| Glaze | 3110.64 | 0.112118 | 155.877ms | 4857 | 160 | 445.974 | 1489.08 | 0.0348248 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13340.5 | 0.319832 | 39.2512ms | 4857 | 320 | 394.626 | 347.212 | 0.0539724 | 1(Win) | true |
| Glaze | 4025.04 | 0.113034 | 119.35ms | 4857 | 320 | 541.456 | 1150.79 | 0.184452 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2129.25 | 0.0596531 | 304.553ms | 6701 | 160 | 512.875 | 3001.32 | 0.00833035 | 1(Win) | true |
| Jsonifier (two-stage) | 1650.18 | 0.0515243 | 394.778ms | 6701 | 160 | 637.032 | 3872.66 | 0.114879 | 2(Loss) | true |
| Glaze | 1621.94 | 0.0853578 | 401.135ms | 6701 | 320 | 3619.49 | 3940.08 | 0.211658 | 3(Loss) | true |
| simdjson (ondemand) | 871.991 | 0.0990063 | 745.573ms | 6701 | 80 | 4211.83 | 7328.71 | 0.079716 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2545.9 | 0.0700552 | 278.371ms | 6701 | 160 | 494.761 | 2510.14 | 0.0945269 | 1(Win) | true |
| Jsonifier (two-stage) | 2153.44 | 0.0883475 | 354.595ms | 6701 | 4890 | 33613.2 | 2967.61 | 0.0964324 | 2(Loss) | true |
| Glaze | 2120.25 | 0.124664 | 322.19ms | 6701 | 2560 | 36143.4 | 3014.06 | 0.472203 | 3(Loss) | true |
| simdjson (ondemand) | 987.195 | 0.139914 | 669.432ms | 6701 | 30 | 2461.02 | 6473.47 | 0.046836 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12348.6 | 0.186545 | 59.8552ms | 7376 | 4890 | 5521.79 | 569.642 | 0.0399047 | 1(Win) | true |
| Glaze | 3072.28 | 0.158441 | 235.781ms | 7376 | 40 | 526.4 | 2289.6 | 0.0334735 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13830.1 | 0.0975587 | 54.362ms | 7376 | 1280 | 315.164 | 508.624 | 0.0819362 | 1(Win) | true |
| Glaze | 3596.54 | 0.10981 | 201.243ms | 7376 | 80 | 369.015 | 1955.85 | 0.0166141 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1711.51 | 0.21317 | 97.6391ms | 1691 | 1280 | 5164.06 | 942.247 | 0.36481 | 1(Win) | true |
| Glaze | 1344.74 | 0.145441 | 124.118ms | 1691 | 320 | 973.484 | 1199.23 | 0.37114 | 2(Loss) | true |
| Jsonifier (two-stage) | 1256.65 | 0.326721 | 145.461ms | 1691 | 30 | 527.39 | 1283.3 | 0.00779302 | 3(Loss) | true |
| simdjson (ondemand) | 1066.59 | 0.209823 | 156.888ms | 1691 | 80 | 805.177 | 1511.99 | 0.0339073 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2420.99 | 0.0580894 | 86.9414ms | 1691 | 1280 | 191.649 | 666.118 | 0.0750007 | 1(Win) | true |
| Glaze | 1795.01 | 0.317755 | 108.015ms | 1691 | 80 | 651.967 | 898.413 | 0.171429 | 2(Loss) | true |
| Jsonifier (two-stage) | 1781.63 | 0.14815 | 113.957ms | 1691 | 4890 | 8793.52 | 905.162 | 0.149046 | 3(Loss) | true |
| simdjson (ondemand) | 1282.69 | 0.0875988 | 142.417ms | 1691 | 4890 | 5931.33 | 1257.26 | 0.21902 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11020.5 | 0.249411 | 20.3436ms | 1996 | 1280 | 237.553 | 172.727 | 0.00361857 | 1(Win) | true |
| Glaze | 3526.32 | 0.176827 | 57.2552ms | 1996 | 4890 | 4455.36 | 539.808 | 0.000335033 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13527.1 | 0.404003 | 17.0924ms | 1996 | 1280 | 413.707 | 140.72 | 0.0677778 | 1(Win) | true |
| Glaze | 4947.62 | 0.150293 | 42.2783ms | 1996 | 1280 | 427.972 | 384.738 | 0.00852927 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1819.94 | 0.282567 | 117.584ms | 2158 | 2560 | 26138 | 1130.82 | 0.02414 | 1(Win) | true |
| Jsonifier (two-stage) | 1559.67 | 0.133441 | 135.982ms | 2158 | 160 | 496.062 | 1319.53 | 0.215521 | 2(Loss) | true |
| Glaze | 1543.71 | 0.137409 | 137.908ms | 2158 | 320 | 1073.87 | 1333.17 | 0.343157 | 3(Loss) | true |
| simdjson (ondemand) | 1305.55 | 0.179913 | 161.16ms | 2158 | 640 | 5147.75 | 1576.36 | 0.418546 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2501.74 | 0.198859 | 101.424ms | 2158 | 4890 | 13086.3 | 822.638 | 0.0789114 | 1(Win) | true |
| Jsonifier (two-stage) | 2113.2 | 0.13624 | 122.796ms | 2158 | 4890 | 8608.79 | 973.893 | 0.017839 | 2(Loss) | true |
| Glaze | 1953.59 | 0.055808 | 122.292ms | 2158 | 2560 | 884.851 | 1053.46 | 0.162861 | 3(Loss) | true |
| simdjson (ondemand) | 1599.76 | 0.0860101 | 145.894ms | 2158 | 640 | 783.564 | 1286.46 | 0.389811 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10381.7 | 0.423707 | 29.0613ms | 2866 | 640 | 796.4 | 263.275 | 0.386064 | 1(Win) | true |
| Glaze | 3232.92 | 0.191764 | 90.6427ms | 2866 | 160 | 420.55 | 845.438 | 0.116667 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14511.9 | 0.159618 | 21.8942ms | 2866 | 4890 | 441.951 | 188.344 | 0.000822807 | 1(Win) | true |
| Glaze | 4392.43 | 0.0691663 | 65.7185ms | 2866 | 1280 | 237.105 | 622.259 | 0.24164 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2130.22 | 0.130024 | 202.141ms | 4390 | 40 | 261.208 | 1965.35 | 0.0618676 | 1(Win) | true |
| Jsonifier (two-stage) | 1183.48 | 0.0829254 | 360.621ms | 4390 | 80 | 688.452 | 3537.56 | 0.0894777 | 2(Loss) | true |
| Glaze | 988.616 | 0.127739 | 427.497ms | 4390 | 2560 | 74913.8 | 4234.84 | 0.0323039 | 3(Loss) | true |
| simdjson (ondemand) | 804.809 | 0.141688 | 523.939ms | 4390 | 4890 | 265654 | 5202.02 | 0.000313787 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2379.22 | 0.184928 | 192.375ms | 4390 | 30 | 317.678 | 1759.67 | 0.00378845 | 1(Win) | true |
| Jsonifier (two-stage) | 1378.89 | 0.127487 | 350.656ms | 4390 | 30 | 449.495 | 3036.23 | 0.00658754 | 2(Loss) | true |
| Glaze | 1113.35 | 0.265821 | 397.534ms | 4390 | 40 | 3996.76 | 3760.4 | 0.240801 | 3(Loss) | true |
| simdjson (ondemand) | 783.371 | 0.3022 | 542.008ms | 4390 | 2560 | 667763 | 5344.38 | 1.04477 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9604.29 | 0.536065 | 47.484ms | 4390 | 80 | 436.84 | 435.913 | 0.106212 | 1(Win) | true |
| Glaze | 2314.36 | 0.0762433 | 186.015ms | 4390 | 320 | 608.724 | 1808.98 | 0.0219344 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10179 | 0.0982139 | 44.3125ms | 4390 | 1280 | 208.868 | 411.3 | 0.0208985 | 1(Win) | true |
| Glaze | 2611.97 | 0.0522823 | 164.927ms | 4390 | 640 | 449.451 | 1602.86 | 0.0641992 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2779.83 | 0.0820256 | 327.555ms | 9378 | 80 | 557.149 | 3217.3 | 0.0552009 | 1(Win) | true |
| Jsonifier (two-stage) | 2242.09 | 0.111344 | 406.822ms | 9378 | 30 | 591.789 | 3988.93 | 0.000835638 | 2(Loss) | true |
| Glaze | 1678.45 | 0.228292 | 542.971ms | 9378 | 640 | 94703 | 5328.45 | 0.00155413 | 3(Loss) | true |
| simdjson (ondemand) | 1605.95 | 0.0927024 | 562.833ms | 9378 | 2560 | 68230.7 | 5569.02 | 0.0403367 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3005.1 | 0.0324901 | 316.621ms | 9378 | 640 | 598.393 | 2976.13 | 0.0971375 | 1(Win) | true |
| Jsonifier (two-stage) | 2555.09 | 0.161243 | 395.835ms | 9378 | 4890 | 155767 | 3500.28 | 0.00848952 | 2(Loss) | true |
| Glaze | 1797.54 | 0.151425 | 514.339ms | 9378 | 4890 | 277567 | 4975.45 | 0.063172 | 3(Loss) | true |
| simdjson (ondemand) | 1764.96 | 0.0966138 | 524.127ms | 9378 | 2560 | 61358 | 5067.3 | 0.0374322 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14142.9 | 0.130415 | 81.7839ms | 11521 | 4890 | 5019.61 | 776.876 | 0.220589 | 1(Win) | true |
| Glaze | 3592.63 | 0.0894323 | 311.966ms | 11521 | 80 | 598.461 | 3058.29 | 0.206795 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14984.5 | 0.0820689 | 76.9699ms | 11521 | 1280 | 463.518 | 733.245 | 0.0200268 | 1(Win) | true |
| Glaze | 4338.77 | 0.138288 | 259.397ms | 11521 | 40 | 490.541 | 2532.35 | 0.0388158 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2851.69 | 0.164294 | 160.32ms | 4669 | 80 | 526.475 | 1561.42 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 1763.33 | 0.137475 | 262.663ms | 4669 | 4890 | 58929.7 | 2525.16 | 0.421297 | 2(Loss) | true |
| Glaze | 1402.16 | 0.127214 | 325.867ms | 4669 | 80 | 1305.61 | 3175.6 | 0.0794494 | 3(Loss) | true |
| simdjson (ondemand) | 614.391 | 0.119828 | 729.165ms | 4669 | 4890 | 368793 | 7247.35 | 0.307329 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3222.44 | 0.078754 | 163.472ms | 4669 | 320 | 378.943 | 1381.78 | 0.0190008 | 1(Win) | true |
| Jsonifier (two-stage) | 1934.46 | 0.0370367 | 246.857ms | 4669 | 640 | 465.127 | 2301.78 | 0.0130996 | 2(Loss) | true |
| Glaze | 1645.66 | 0.149723 | 285.89ms | 4669 | 2560 | 42013 | 2705.73 | 0.0359351 | 3(Loss) | true |
| simdjson (ondemand) | 669.764 | 0.0541463 | 705.802ms | 4669 | 160 | 2073.3 | 6648.18 | 0.066604 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13545.9 | 0.114846 | 35.9612ms | 4669 | 1280 | 182.419 | 328.712 | 0.0984922 | 1(Win) | true |
| Glaze | 1995.48 | 0.239288 | 243.044ms | 4669 | 40 | 1140.4 | 2231.4 | 1.12987 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15380.1 | 0.0574112 | 31.9142ms | 4669 | 4890 | 135.092 | 289.511 | 0.121205 | 1(Win) | true |
| Glaze | 2357.34 | 0.24311 | 195.164ms | 4669 | 30 | 632.602 | 1888.87 | 0.223619 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2868.11 | 0.187963 | 271.175ms | 7932 | 30 | 737.292 | 2637.47 | 0.0531094 | 1(Win) | true |
| Jsonifier (two-stage) | 2581.13 | 0.0367588 | 300.453ms | 7932 | 640 | 742.761 | 2930.72 | 0.0134335 | 2(Loss) | true |
| Glaze | 1751.24 | 0.186814 | 440.145ms | 7932 | 30 | 1953.5 | 4319.53 | 0.0300868 | 3(Loss) | true |
| simdjson (ondemand) | 1019.29 | 0.0492632 | 753.609ms | 7932 | 160 | 2138.63 | 7421.39 | 0.0134728 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3082.94 | 0.128036 | 259.847ms | 7932 | 80 | 789.564 | 2453.68 | 0.313846 | 1(Win) | true |
| Jsonifier (two-stage) | 2784.6 | 0.0436158 | 289.191ms | 7932 | 320 | 449.238 | 2716.56 | 0.0417404 | 2(Loss) | true |
| Glaze | 1973.38 | 0.201695 | 399.364ms | 7932 | 30 | 1793.32 | 3833.3 | 0.00173912 | 3(Loss) | true |
| simdjson (ondemand) | 1101.02 | 0.142867 | 707.343ms | 7932 | 640 | 61662.8 | 6870.5 | 0.0425687 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14445.7 | 0.165017 | 69.1721ms | 9249 | 640 | 649.756 | 610.598 | 0.265681 | 1(Win) | true |
| Glaze | 3212.96 | 0.071515 | 283.418ms | 9249 | 80 | 308.365 | 2745.3 | 0.0564283 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16662.3 | 0.169325 | 56.3966ms | 9249 | 640 | 514.215 | 529.372 | 0.0844874 | 1(Win) | true |
| Glaze | 3722.69 | 0.111894 | 252.212ms | 9249 | 30 | 210.869 | 2369.4 | 0.119437 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 660.252 | 0.0929461 | 684.21ms | 4604 | 30 | 1146.13 | 6650.07 | 0.187819 | 1(Win) | true |
| Jsonifier (two-stage) | 547.692 | 0.172288 | 809.885ms | 4604 | 4890 | 932864 | 8016.76 | 0.429323 | 2(Loss) | true |
| Glaze | 388.578 | 0.0602215 | 1149.2ms | 4604 | 80 | 3704.3 | 11299.4 | 0.0239999 | 3(Loss) | true |
| simdjson (ondemand) | 331.827 | 0.0975208 | 1343.72ms | 4604 | 30 | 4995.31 | 13231.9 | 0.0951336 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 843.774 | 0.0898725 | 671.333ms | 4604 | 80 | 1749.69 | 5203.66 | 0.0703336 | 1(Win) | true |
| Jsonifier (two-stage) | 699.128 | 0.0887281 | 781.756ms | 4604 | 40 | 1242.05 | 6280.27 | 0.0486737 | 2(Loss) | true |
| Glaze | 444.568 | 0.11012 | 1124.02ms | 4604 | 4890 | 578411 | 9876.38 | 0.317668 | 3(Loss) | true |
| simdjson (ondemand) | 377.241 | 0.0396623 | 1325.13ms | 4604 | 160 | 3409.65 | 11639 | 0.0586046 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2014.38 | 0.142818 | 221.577ms | 4604 | 80 | 775.256 | 2179.69 | 0.16601 | 1(Win) | true |
| Glaze | 933.506 | 0.312165 | 461.65ms | 4604 | 2560 | 551880 | 4703.47 | 0.27087 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2062.39 | 0.107784 | 214.611ms | 4604 | 160 | 842.475 | 2128.95 | 0.187061 | 1(Win) | true |
| Glaze | 1173.48 | 0.11413 | 382.931ms | 4604 | 40 | 729.42 | 3741.62 | 0.224783 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1903.35 | 0.0560215 | 932.226ms | 18245 | 40 | 1049.11 | 9141.65 | 0.0154944 | 1(Win) | true |
| Jsonifier | 1890.42 | 0.0642053 | 949.441ms | 18245 | 80 | 2793.84 | 9204.17 | 0.0445252 | 2(Loss) | true |
| Glaze | 1215.38 | 0.150787 | 1442.54ms | 18245 | 640 | 298246 | 14316.4 | 0.198473 | 3(Loss) | true |
| simdjson (ondemand) | 1207.13 | 0.0970316 | 1500.09ms | 18245 | 4890 | 956561 | 14414.1 | 0.130857 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2281.51 | 0.0849115 | 913.501ms | 18245 | 30 | 1258.05 | 7626.43 | 0.0532949 | 1(Win) | true |
| Jsonifier | 2211.16 | 0.107829 | 927.141ms | 18245 | 4890 | 352069 | 7869.07 | 0.0164257 | 2(Loss) | true |
| simdjson (ondemand) | 1373.22 | 0.0609176 | 1416.74ms | 18245 | 40 | 2383.15 | 12670.8 | 0.13072 | 3(Loss) | true |
| Glaze | 1357.65 | 0.122943 | 1423.4ms | 18245 | 2560 | 635562 | 12816.1 | 0.0862543 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5746.5 | 0.191594 | 417.92ms | 24579 | 30 | 1832.34 | 4079.07 | 0.205506 | 1(Win) | true |
| Glaze | 3295.68 | 0.0408619 | 722.343ms | 24579 | 160 | 1351.43 | 7112.44 | 0.0680561 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5992.66 | 0.154663 | 398.866ms | 24579 | 80 | 2927.87 | 3911.51 | 0.0297111 | 1(Win) | true |
| Glaze | 3931.39 | 0.113135 | 606.119ms | 24579 | 30 | 1365.07 | 5962.37 | 0.0709505 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 704.596 | 0.0473183 | 637.166ms | 4604 | 160 | 1391.13 | 6231.54 | 0.020866 | 1(Win) | true |
| Jsonifier (two-stage) | 580.432 | 0.0843973 | 808.066ms | 4604 | 4890 | 199312 | 7564.56 | 0.317351 | 2(Loss) | true |
| Glaze | 390.141 | 0.0568401 | 1146.11ms | 4604 | 80 | 3273.61 | 11254.2 | 0.0734742 | 3(Loss) | true |
| simdjson (ondemand) | 328.125 | 0.144885 | 1342.62ms | 4604 | 2560 | 962228 | 13381.2 | 0.0292827 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 922.945 | 0.0877668 | 622.257ms | 4604 | 80 | 1394.66 | 4757.29 | 0.0228649 | 1(Win) | true |
| Jsonifier (two-stage) | 739.473 | 0.0318344 | 742.954ms | 4604 | 320 | 1143.33 | 5937.63 | 0.00205263 | 2(Loss) | true |
| Glaze | 449.941 | 0.0751713 | 1122.68ms | 4604 | 40 | 2152.4 | 9758.42 | 0.01563 | 3(Loss) | true |
| simdjson (ondemand) | 377.225 | 0.0674798 | 1311.26ms | 4604 | 80 | 4935.24 | 11639.5 | 0.0712579 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1995.68 | 0.0712051 | 228.697ms | 4604 | 320 | 785.348 | 2200.11 | 0.161662 | 1(Win) | true |
| Glaze | 1058.8 | 0.0636643 | 421.824ms | 4604 | 160 | 1115.2 | 4146.88 | 0.177557 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2065.68 | 0.127989 | 219.1ms | 4604 | 80 | 592.073 | 2125.55 | 0.218289 | 1(Win) | true |
| Glaze | 1171.71 | 0.129893 | 384.67ms | 4604 | 30 | 710.754 | 3747.27 | 0.00266854 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1957.48 | 0.127067 | 900.78ms | 18245 | 1280 | 163294 | 8888.86 | 0.0496776 | 1(Win) | true |
| Jsonifier | 1936.53 | 0.0706586 | 928.958ms | 18245 | 4890 | 197097 | 8985.05 | 0.23619 | 2(Loss) | true |
| Glaze | 1229.06 | 0.0730248 | 1442.06ms | 18245 | 30 | 3206.27 | 14156.9 | 0.176046 | 3(Loss) | true |
| simdjson (ondemand) | 1219.01 | 0.0735192 | 1446.09ms | 18245 | 30 | 3303.67 | 14273.7 | 0.0879633 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2411.41 | 0.0710078 | 880.598ms | 18245 | 80 | 2100.14 | 7215.61 | 0.043501 | 1(Win) | true |
| Jsonifier | 2264.96 | 0.134513 | 912.063ms | 18245 | 4890 | 522163 | 7682.16 | 0.288276 | 2(Loss) | true |
| simdjson (ondemand) | 1363.1 | 0.0968248 | 1419.28ms | 18245 | 4890 | 746992 | 12764.9 | 0.00646681 | 3(Loss) | true |
| Glaze | 1359.58 | 0.0761669 | 1461.23ms | 18245 | 40 | 3800.76 | 12797.9 | 0.0171933 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5777.4 | 0.171722 | 416.857ms | 24579 | 40 | 1941.68 | 4057.25 | 0.0972619 | 1(Win) | true |
| Glaze | 3317.77 | 0.0514279 | 720.729ms | 24579 | 160 | 2112.29 | 7065.09 | 0.0443397 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6075.39 | 0.252432 | 429.168ms | 24579 | 40 | 3794.29 | 3858.25 | 0.038431 | 1(Win) | true |
| Glaze | 3955.27 | 0.0934723 | 606.885ms | 24579 | 30 | 920.585 | 5926.37 | 0.0461003 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1499.82 | 0.0541605 | 331.858ms | 5094 | 160 | 492.406 | 3239.06 | 0.0811691 | 1(Win) | true |
| Jsonifier (two-stage) | 1097.84 | 0.157331 | 445.833ms | 5094 | 4890 | 237016 | 4425.06 | 0.0437375 | 2(Loss) | true |
| Glaze | 905.208 | 0.132121 | 541.971ms | 5094 | 1280 | 64353.5 | 5366.74 | 0.177681 | 3(Loss) | true |
| simdjson (ondemand) | 670.866 | 0.0916018 | 731.012ms | 5094 | 4890 | 215161 | 7241.41 | 0.114006 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1919.99 | 0.0971023 | 328.028ms | 5094 | 80 | 482.911 | 2530.22 | 0.0819413 | 1(Win) | true |
| Jsonifier (two-stage) | 1424.78 | 0.0844689 | 443.215ms | 5094 | 30 | 248.851 | 3409.67 | 0.147402 | 2(Loss) | true |
| Glaze | 1117.22 | 0.0757443 | 513.403ms | 5094 | 320 | 3471.29 | 4348.31 | 0.105972 | 3(Loss) | true |
| simdjson (ondemand) | 787.194 | 0.295968 | 690.981ms | 5094 | 640 | 213513 | 6171.31 | 0.418976 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10345.8 | 0.0831663 | 51.5669ms | 5094 | 2560 | 390.41 | 469.562 | 0.0421114 | 1(Win) | true |
| Glaze | 2777.63 | 0.109571 | 181.867ms | 5094 | 160 | 587.603 | 1748.98 | 0.0897756 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11337 | 0.249316 | 46.3212ms | 5094 | 320 | 365.235 | 428.509 | 0.0925319 | 1(Win) | true |
| Glaze | 3400.63 | 0.0592568 | 147.114ms | 5094 | 640 | 458.622 | 1428.56 | 0.0402665 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1778.7 | 0.0758171 | 439.49ms | 8051 | 40 | 428.438 | 4316.65 | 0.0962319 | 1(Win) | true |
| Jsonifier (two-stage) | 1324.04 | 0.272088 | 593.56ms | 8051 | 40 | 9958.15 | 5798.95 | 0.246339 | 2(Loss) | true |
| Glaze | 1263.83 | 0.151063 | 615.399ms | 8051 | 1280 | 107807 | 6075.21 | 0.23745 | 3(Loss) | true |
| simdjson (ondemand) | 1016.69 | 0.0800375 | 803.518ms | 8051 | 4890 | 178657 | 7552 | 0.888905 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2134.43 | 0.115804 | 437.908ms | 8051 | 30 | 520.599 | 3597.23 | 0.00185331 | 1(Win) | true |
| Jsonifier (two-stage) | 1875.05 | 0.0652317 | 559.103ms | 8051 | 80 | 570.796 | 4094.84 | 0.0766796 | 2(Loss) | true |
| Glaze | 1504.05 | 0.199339 | 584.637ms | 8051 | 4890 | 506372 | 5104.91 | 0.0120776 | 3(Loss) | true |
| simdjson (ondemand) | 1197.88 | 0.264692 | 734.112ms | 8051 | 30 | 8635.32 | 6409.7 | 0.152141 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11335.5 | 0.279039 | 82.4335ms | 9255 | 80 | 377.652 | 778.638 | 0.0753954 | 1(Win) | true |
| Glaze | 3114.74 | 0.103763 | 288.927ms | 9255 | 2560 | 22132.9 | 2833.71 | 0.136851 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13685.8 | 0.12928 | 68.1084ms | 9255 | 640 | 444.889 | 644.919 | 0.0615009 | 1(Win) | true |
| Glaze | 3924.66 | 0.123597 | 231.511ms | 9255 | 40 | 309.046 | 2248.93 | 0.046297 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 3741.06 | 0.0928136 | 77.3235ms | 2889 | 1280 | 598.052 | 736.466 | 0.0687991 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 3740.45 | 0.15815 | 77.462ms | 2889 | 320 | 434.249 | 736.587 | 0.02036 | 1(Tie) | true |
| simdjson (ondemand) | 3510.26 | 0.235002 | 83.9527ms | 2889 | 2560 | 8709.62 | 784.889 | 0.419817 | 3(Loss) | true |
| Glaze | 2226.58 | 0.141599 | 127.83ms | 2889 | 1280 | 3929.58 | 1237.4 | 0.592491 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4109.19 | 0.0547706 | 73.1112ms | 2889 | 1280 | 172.619 | 670.489 | 0.00279639 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4108.32 | 0.0773002 | 72.9961ms | 2889 | 640 | 171.992 | 670.631 | 0.244506 | 1(Tie) | true |
| simdjson (ondemand) | 3746.61 | 0.337105 | 79.5261ms | 2889 | 80 | 491.63 | 735.375 | 0.433267 | 3(Loss) | true |
| Glaze | 2295.29 | 0.0840696 | 126.359ms | 2889 | 640 | 651.744 | 1200.35 | 0.0835086 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 4314.59 | 0.222633 | 87.899ms | 3808 | 80 | 280.922 | 841.7 | 0.00297027 | 1(Win) | true |
| Jsonifier (two-stage) | 4224.58 | 0.0955706 | 89.7ms | 3808 | 640 | 431.973 | 859.634 | 0.213116 | 2(Loss) | true |
| Jsonifier | 4212.81 | 0.0923614 | 89.7641ms | 3808 | 640 | 405.706 | 862.036 | 0.0208489 | 3(Loss) | true |
| Glaze | 2620.44 | 0.0837626 | 142.188ms | 3808 | 4890 | 6589.52 | 1385.87 | 0.00987684 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 4579.37 | 0.174128 | 84.884ms | 3808 | 30 | 57.2057 | 793.033 | 0.172632 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4574.57 | 0.0581717 | 85.2536ms | 3808 | 640 | 136.489 | 793.866 | 0.0141732 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 4572.61 | 0.0560475 | 85.477ms | 3808 | 640 | 126.811 | 794.205 | 0.110248 | 1(Tie) | true |
| Glaze | 2692.14 | 0.104982 | 140.796ms | 3808 | 4890 | 9806.95 | 1348.96 | 0.038548 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2326.27 | 0.118088 | 122.167ms | 2889 | 1280 | 2503.79 | 1184.37 | 0.253876 | 1(Win) | true |
| Glaze | 1909.22 | 0.161118 | 148.198ms | 2889 | 2560 | 13839.3 | 1443.09 | 0.0164551 | 2(Loss) | true |
| Jsonifier (two-stage) | 1845.99 | 0.131552 | 153.268ms | 2889 | 4890 | 18851.2 | 1492.51 | 0.0380679 | 3(Loss) | true |
| simdjson (ondemand) | 847.609 | 0.1005 | 332.187ms | 2889 | 80 | 853.747 | 3250.51 | 0.049583 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2882.37 | 0.086737 | 114.797ms | 2889 | 640 | 439.931 | 955.867 | 0.106302 | 1(Win) | true |
| Jsonifier (two-stage) | 2250.53 | 0.0700176 | 143.487ms | 2889 | 640 | 470.239 | 1224.23 | 0.0311518 | 2(Loss) | true |
| Glaze | 2123.94 | 0.123634 | 158.31ms | 2889 | 640 | 1646.13 | 1297.2 | 0.353597 | 3(Loss) | true |
| simdjson (ondemand) | 894.625 | 0.143935 | 322.872ms | 2889 | 2560 | 50302.1 | 3079.69 | 0.325737 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10161.2 | 0.141589 | 30.5835ms | 2963 | 4890 | 758.137 | 278.092 | 0.440408 | 1(Win) | true |
| Glaze | 3654.57 | 0.282068 | 81.8506ms | 2963 | 160 | 761.058 | 773.206 | 0.0865654 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13412.9 | 0.242477 | 24.6752ms | 2963 | 1280 | 334.018 | 210.673 | 0.0578837 | 1(Win) | true |
| Glaze | 4572.67 | 0.176016 | 65.449ms | 2963 | 1280 | 1514.4 | 617.962 | 0.0227511 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2343 | 0.121023 | 161.311ms | 3808 | 160 | 562.993 | 1549.97 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 2237.77 | 0.119892 | 166.109ms | 3808 | 4890 | 18511.9 | 1622.86 | 0.0535169 | 2(Loss) | true |
| Glaze | 2085.05 | 0.298659 | 178.461ms | 3808 | 40 | 1082.36 | 1741.72 | 0.0712387 | 3(Loss) | true |
| simdjson (ondemand) | 1097.25 | 0.206517 | 339.992ms | 3808 | 30 | 1401.58 | 3309.73 | 0 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2673.62 | 0.0467119 | 157.102ms | 3808 | 1280 | 515.301 | 1358.31 | 0.0110994 | 1(Win) | true |
| Jsonifier | 2635.91 | 0.0729618 | 158.4ms | 3808 | 640 | 646.703 | 1377.74 | 0.182128 | 2(Loss) | true |
| Glaze | 2387.91 | 0.240074 | 170.121ms | 3808 | 40 | 533.225 | 1520.83 | 0.00931425 | 3(Loss) | true |
| simdjson (ondemand) | 1163.19 | 0.0864109 | 329.819ms | 3808 | 160 | 1164.54 | 3122.11 | 0.0406542 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11583.5 | 0.329746 | 38.5698ms | 4300 | 320 | 436.084 | 354.022 | 0.0308854 | 1(Win) | true |
| Glaze | 3247.67 | 0.07288 | 132.554ms | 4300 | 640 | 541.989 | 1262.69 | 0.190184 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14361.1 | 0.148963 | 31.5523ms | 4300 | 1280 | 231.597 | 285.55 | 0.176506 | 1(Win) | true |
| Glaze | 4453.03 | 0.395909 | 96.198ms | 4300 | 30 | 398.783 | 920.9 | 0.159519 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2292.3 | 0.15751 | 5000.57ms | 466906 | 80 | 7.48902e+06 | 194249 | 0.0472491 | 1(Win) | true |
| Glaze | 1743.79 | 0.0902597 | 6563.36ms | 466906 | 1280 | 6.79938e+07 | 255350 | 0.0813455 | 2(Loss) | true |
| simdjson (ondemand) | 1249.58 | 0.165249 | 9039.18ms | 466906 | 640 | 2.21917e+08 | 356341 | 0.367734 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2273.52 | 0.110737 | 5024.67ms | 466906 | 1280 | 6.02085e+07 | 195853 | 0.52882 | 1(Win) | true |
| Glaze | 1751.54 | 0.101314 | 6546.52ms | 466906 | 640 | 4.2456e+07 | 254219 | 0.227037 | 2(Loss) | true |
| simdjson (ondemand) | 1262.92 | 0.0765552 | 9060.01ms | 466906 | 1280 | 9.32542e+07 | 352577 | 0.174554 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3267.36 | 0.296832 | 5312.09ms | 699405 | 40 | 1.46874e+07 | 204142 | 0.222641 | 1(Win) | true |
| Glaze | 2514.55 | 0.124665 | 6903.29ms | 699405 | 640 | 6.9985e+07 | 265258 | 0.104103 | 2(Loss) | true |
| simdjson (ondemand) | 1629.64 | 0.101101 | 5722.44ms | 767297 | 640 | 1.31897e+08 | 449025 | 0.703207 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3268.95 | 0.143711 | 5234.96ms | 699405 | 320 | 2.7515e+07 | 204042 | 0.417121 | 1(Win) | true |
| Glaze | 2542.01 | 0.172402 | 6843.34ms | 699405 | 40 | 8.18553e+06 | 262393 | 0.0118415 | 2(Loss) | true |
| simdjson (ondemand) | 1638.14 | 0.155937 | 5771.31ms | 767297 | 80 | 3.88163e+07 | 446697 | 0.257472 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2528.84 | 0.305022 | 6056.43ms | 631514 | 160 | 8.44313e+07 | 238156 | 0.366374 | 1(Win) | true |
| Glaze | 1988.45 | 0.114903 | 7729.56ms | 631514 | 1280 | 1.5503e+08 | 302879 | 0.298522 | 2(Loss) | true |
