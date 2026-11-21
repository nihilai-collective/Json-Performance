# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the Clang 23.1.5 compiler).  

Latest Results: (Nov 21, 2026)
#### Using the following commits:
----
| Jsonifier: [16b6b42](https://github.com/nihilai-collective/Jsonifier/commit/16b6b42)  
| Glaze: [fc0b48a0](https://github.com/stephenberry/glaze/commit/fc0b48a0)  
| simdjson: [81c2d7212](https://github.com/simdjson/simdjson/commit/81c2d7212)  

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
*Environment generated via BenchmarkSuite commit: [71afc62](https://github.com/nihilai-collective/benchmarksuite/commit/71afc62)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1208.9 | 0.160422 | 74.9236ms | 905 | 320 | 419.754 | 713.934 | 0.101215 | 1(Win) | true |
| Glaze | 1103.42 | 0.14764 | 80.1973ms | 905 | 320 | 426.751 | 782.181 | 0.118917 | 2(Loss) | true |
| Jsonifier (two-stage) | 1083.79 | 0.294682 | 87.5735ms | 905 | 80 | 440.559 | 796.35 | 0.322308 | 3(Loss) | true |
| simdjson (ondemand) | 278.714 | 0.17522 | 315.993ms | 905 | 2560 | 75368.6 | 3096.64 | 0.11276 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1305.92 | 0.148493 | 74.206ms | 905 | 640 | 616.386 | 660.894 | 0.213234 | 1(Win) | true |
| Glaze | 1192.78 | 0.120946 | 74.5628ms | 905 | 640 | 490.159 | 723.583 | 0.372148 | 2(Loss) | true |
| Jsonifier (two-stage) | 867.907 | 1.48811 | 83.8253ms | 905 | 30 | 6569.63 | 994.433 | 0.698711 | 3(Loss) | true |
| simdjson (ondemand) | 280.874 | 0.209671 | 326.796ms | 905 | 40 | 1660.4 | 3072.82 | 0.296618 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1020.61 | 0.165964 | 96.2417ms | 905 | 1280 | 2521.23 | 845.645 | 1.00178 | 1(Win) | true |
| Glaze | 123.47 | 0.133469 | 709.165ms | 905 | 30 | 2611.32 | 6990.17 | 0.0424226 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1206.59 | 0.403023 | 89.89ms | 905 | 30 | 249.321 | 715.3 | 0.36481 | 1(Win) | true |
| Glaze | 767.878 | 0.159297 | 139.658ms | 905 | 40 | 128.23 | 1123.97 | 0.0911111 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 910.62 | 0.184755 | 213.306ms | 1811 | 160 | 1964.6 | 1896.62 | 0.789818 | 1(Win) | true |
| Jsonifier (two-stage) | 853.771 | 0.0852826 | 209.097ms | 1811 | 160 | 476.206 | 2022.91 | 0.0777975 | 2(Loss) | true |
| Glaze | 744.169 | 0.224668 | 253.28ms | 1811 | 40 | 1087.52 | 2320.85 | 0.175632 | 3(Loss) | true |
| simdjson (ondemand) | 277.597 | 0.2733 | 610.061ms | 1811 | 640 | 185040 | 6221.62 | 0.198058 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1040.62 | 0.114916 | 168.239ms | 1811 | 4890 | 17788 | 1659.69 | 0.345484 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1039.31 | 0.468205 | 191.075ms | 1811 | 640 | 38743.9 | 1661.79 | 1.27341 | 1(Tie) | true |
| Glaze | 903.067 | 0.264548 | 210.809ms | 1811 | 80 | 2047.85 | 1912.49 | 0.10665 | 3(Loss) | true |
| simdjson (ondemand) | 309.262 | 0.0979893 | 592.884ms | 1811 | 30 | 898.386 | 5584.6 | 0.00238746 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 317.032 | 0.104871 | 621.479ms | 1997 | 40 | 1587.53 | 6007.25 | 0.00527169 | 1(Win) | true |
| Glaze | 216.592 | 0.0922312 | 817.406ms | 1798 | 40 | 2132.6 | 7916.75 | 0.0511312 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 956.728 | 0.139973 | 211.521ms | 1997 | 40 | 310.548 | 1990.62 | 0.155553 | 1(Win) | true |
| Glaze | 677.55 | 0.0643865 | 281.058ms | 1798 | 160 | 424.821 | 2530.74 | 0.0417193 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2278.2 | 0.258758 | 190.055ms | 3862 | 30 | 524.989 | 1616.67 | 0.594384 | 1(Win) | true |
| Jsonifier (two-stage) | 2218.89 | 0.10164 | 171.236ms | 3862 | 160 | 455.413 | 1659.88 | 0.00564768 | 2(Loss) | true |
| Glaze | 1236.9 | 0.209724 | 318.055ms | 3862 | 30 | 1169.95 | 2977.67 | 0.32457 | 3(Loss) | true |
| simdjson (ondemand) | 606.448 | 0.130431 | 613.108ms | 3862 | 2560 | 160634 | 6073.22 | 0.218061 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2679.65 | 0.0734681 | 148.324ms | 3862 | 320 | 326.3 | 1374.47 | 0.0399995 | 1(Win) | true |
| Jsonifier | 2662.47 | 0.145989 | 148.904ms | 3862 | 80 | 326.277 | 1383.34 | 0.296407 | 2(Loss) | true |
| Glaze | 1444.66 | 0.0876531 | 258.96ms | 3862 | 1280 | 6391.98 | 2549.44 | 0.106816 | 3(Loss) | true |
| simdjson (ondemand) | 638.221 | 0.0898636 | 625.721ms | 3862 | 30 | 806.809 | 5770.87 | 0.239137 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2973.91 | 0.406605 | 127.903ms | 3862 | 1280 | 32458.2 | 1238.47 | 0.357528 | 1(Win) | true |
| Glaze | 524.519 | 0.14072 | 733.934ms | 3862 | 1280 | 124976 | 7021.84 | 0.0051071 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3477.78 | 0.154229 | 117.011ms | 3862 | 4890 | 13045.6 | 1059.04 | 0.0501508 | 1(Win) | true |
| Glaze | 2080.79 | 0.0705615 | 195.579ms | 3862 | 320 | 499.174 | 1770.04 | 0.0273727 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1345.24 | 0.0528483 | 704.458ms | 9578 | 80 | 1030.16 | 6790.09 | 0.0402999 | 1(Win) | true |
| Jsonifier | 1331.11 | 0.0876542 | 701.165ms | 9578 | 4890 | 176919 | 6862.14 | 0.135688 | 2(Loss) | true |
| Glaze | 1117.37 | 0.0415545 | 815.917ms | 9578 | 160 | 1846.34 | 8174.8 | 0.323374 | 3(Loss) | true |
| simdjson (ondemand) | 812.172 | 0.0537262 | 1165.69ms | 9578 | 40 | 1460.45 | 11246.8 | 0.00815117 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2325.29 | 0.0597668 | 670.667ms | 9578 | 320 | 1763.87 | 3928.24 | 0.0895763 | 1(Win) | true |
| Jsonifier (two-stage) | 2073.36 | 0.291129 | 689.278ms | 9578 | 2560 | 421125 | 4405.55 | 0.612301 | 2(Loss) | true |
| Glaze | 1736.61 | 0.137814 | 762.609ms | 9578 | 1280 | 67257.4 | 5259.84 | 0.175202 | 3(Loss) | true |
| simdjson (ondemand) | 1091.35 | 0.213031 | 1146.77ms | 9578 | 1280 | 406922 | 8369.68 | 0.544656 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1227.62 | 0.0690972 | 717.202ms | 9578 | 40 | 1057.31 | 7440.65 | 0.511293 | 1(Win) | true |
| Glaze | 1095.09 | 0.0684306 | 937.559ms | 9578 | 80 | 2606.4 | 8341.14 | 0.0810084 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7424.97 | 0.199733 | 140.791ms | 9578 | 80 | 483.005 | 1230.21 | 0.0862927 | 1(Win) | true |
| Glaze | 3964.37 | 0.14544 | 250.427ms | 9578 | 4890 | 54913 | 2304.09 | 1.07527 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2221.69 | 0.122703 | 175.407ms | 3873 | 80 | 332.911 | 1662.51 | 0.625383 | 1(Win) | true |
| Jsonifier (two-stage) | 2177.98 | 0.147448 | 181.204ms | 3873 | 80 | 500.212 | 1695.88 | 0.0545144 | 2(Loss) | true |
| Glaze | 1253.29 | 0.173786 | 310.965ms | 3873 | 4890 | 128272 | 2947.12 | 0.361611 | 3(Loss) | true |
| simdjson (ondemand) | 612.841 | 0.0849336 | 619.144ms | 3873 | 4890 | 128135 | 6026.98 | 0.681567 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2638.33 | 0.270441 | 147.13ms | 3873 | 30 | 430.033 | 1399.97 | 0.987788 | 1(Win) | true |
| Jsonifier (two-stage) | 2617.33 | 0.273295 | 155.649ms | 3873 | 30 | 446.234 | 1411.2 | 0.108773 | 2(Loss) | true |
| Glaze | 1376.32 | 0.0467397 | 277.64ms | 3873 | 640 | 1006.95 | 2683.67 | 0.399146 | 3(Loss) | true |
| simdjson (ondemand) | 641.319 | 0.230089 | 630.685ms | 3873 | 640 | 112387 | 5759.35 | 0.0501107 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3100.7 | 0.179312 | 122.368ms | 3873 | 2560 | 11679.9 | 1191.21 | 0.00304959 | 1(Win) | true |
| Glaze | 524.749 | 0.181196 | 755.318ms | 3873 | 1280 | 208208 | 7038.76 | 2.40933 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3569.18 | 0.183894 | 121.37ms | 3873 | 4890 | 17709.3 | 1034.85 | 0.638719 | 1(Win) | true |
| Glaze | 2105.39 | 0.126489 | 194.993ms | 3873 | 4890 | 24079.3 | 1754.34 | 0.763465 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1562.56 | 0.0311052 | 5941.91ms | 94653 | 30 | 9686.86 | 57769.4 | 0.0191026 | 1(Win) | true |
| Glaze | 1142.7 | 0.0569104 | 8153.18ms | 94653 | 2560 | 5.17404e+06 | 78995.7 | 4.68768 | 2(Loss) | true |
| Jsonifier (two-stage) | 1110.2 | 0.0562364 | 8243ms | 94653 | 4890 | 1.02237e+07 | 81307.7 | 0.0710207 | 3(Loss) | true |
| simdjson (ondemand) | 835.156 | 0.636025 | 5771.63ms | 94653 | 40 | 1.89035e+07 | 108085 | 0.796094 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2319.77 | 0.119575 | 5459.56ms | 94653 | 640 | 1.3856e+06 | 38912.5 | 0.0203901 | 1(Win) | true |
| Jsonifier (two-stage) | 1503.22 | 0.181354 | 8454.86ms | 94653 | 320 | 3.79515e+06 | 60050 | 0.0303954 | 2(Loss) | true |
| Glaze | 1475.52 | 0.0619292 | 7653.14ms | 94653 | 2560 | 3.67461e+06 | 61177.2 | 0.0387479 | 3(Loss) | true |
| simdjson (ondemand) | 962.404 | 0.628194 | 5391.34ms | 94653 | 320 | 1.11094e+08 | 93794.4 | 0.341544 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11515.8 | 0.0317993 | 802.138ms | 94653 | 80 | 497.053 | 7838.6 | 0.0647018 | 1(Win) | true |
| Glaze | 3307.13 | 0.142034 | 2577.77ms | 94653 | 640 | 961899 | 27295 | 0.823921 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11824.1 | 0.207742 | 777.352ms | 94653 | 1280 | 321954 | 7634.28 | 0.0393119 | 1(Win) | true |
| Glaze | 4216.21 | 0.19367 | 2218.57ms | 94653 | 320 | 550172 | 21409.8 | 0.28685 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1667.93 | 0.316889 | 7268.08ms | 124597 | 80 | 4.07722e+06 | 71241.1 | 0.00822842 | 1(Win) | true |
| Jsonifier (two-stage) | 1382.05 | 0.0528245 | 8723.52ms | 124597 | 2560 | 5.28053e+06 | 85977.2 | 0.104472 | 2(Loss) | true |
| Glaze | 1361.69 | 0.0688158 | 8874.31ms | 124597 | 4890 | 1.76338e+07 | 87263 | 0.0431054 | 3(Loss) | true |
| simdjson (ondemand) | 1113.2 | 0.0673916 | 5490.97ms | 124597 | 2560 | 1.3247e+07 | 106741 | 0.0365517 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2264.75 | 0.0501955 | 6909.46ms | 124597 | 4890 | 3.39168e+06 | 52467.2 | 0.0624136 | 1(Win) | true |
| Jsonifier (two-stage) | 1858.06 | 0.0308399 | 8430.31ms | 124597 | 40 | 15559 | 63951.1 | 0.103741 | 2(Loss) | true |
| Glaze | 1728.7 | 0.0810828 | 8546.28ms | 124597 | 2560 | 7.95191e+06 | 68736.4 | 2.05972 | 3(Loss) | true |
| simdjson (ondemand) | 1366.46 | 0.137549 | 5426.1ms | 124597 | 320 | 4.57814e+06 | 86958.4 | 0.102734 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10632.7 | 0.76892 | 1195.42ms | 136037 | 320 | 2.81667e+06 | 12201.5 | 1.98194 | 1(Win) | true |
| Glaze | 3084.59 | 0.951405 | 4032.87ms | 136076 | 160 | 2.56341e+07 | 42071.1 | 0.600912 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11802.4 | 0.036347 | 1174.2ms | 136037 | 80 | 1277.03 | 10992.2 | 0.0140989 | 1(Win) | true |
| Glaze | 3685.28 | 0.313191 | 3453.51ms | 136076 | 640 | 7.78433e+06 | 35213.7 | 0.00254245 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 721.854 | 0.386541 | 9465.31ms | 2251027 | 160 | 2.11434e+10 | 2.97393e+06 | 1.75474 | 1(Win) | true |
| Jsonifier (two-stage) | 658.116 | 0.0649756 | 5083.86ms | 2251027 | 30 | 1.34765e+08 | 3.26196e+06 | 0.073399 | 2(Loss) | true |
| Glaze | 544.359 | 1.37285 | 5910.21ms | 2251027 | 30 | 8.7935e+10 | 3.94363e+06 | 3.26639 | 3(Loss) | true |
| simdjson (ondemand) | 508.78 | 0.867354 | 6250.19ms | 2251027 | 80 | 1.07148e+11 | 4.2194e+06 | 0.119554 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 891.883 | 0.0890881 | 9413.71ms | 2251027 | 40 | 1.83927e+08 | 2.40698e+06 | 0.126927 | 1(Win) | true |
| Jsonifier (two-stage) | 702.681 | 0.92184 | 5175.06ms | 2251027 | 80 | 6.34521e+10 | 3.05508e+06 | 1.64733 | 2(Loss) | true |
| Glaze | 644.625 | 0.965122 | 5989.83ms | 2251027 | 30 | 3.09908e+10 | 3.33023e+06 | 0.864485 | 3(Loss) | true |
| simdjson (ondemand) | 619.345 | 0.279613 | 6210.05ms | 2251027 | 30 | 2.81794e+09 | 3.46616e+06 | 0.799004 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2755.2 | 0.342448 | 9069.93ms | 2090326 | 640 | 3.92908e+09 | 723537 | 2.62812 | 1(Win) | true |
| Glaze | 1899 | 0.111354 | 7140.14ms | 2090234 | 40 | 5.46523e+07 | 1.04971e+06 | 0.101094 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2920.87 | 0.534772 | 8972.2ms | 2090326 | 30 | 3.99634e+08 | 682499 | 0.0213917 | 1(Win) | true |
| Glaze | 1729.58 | 0.664108 | 6970.3ms | 2090234 | 160 | 9.37362e+09 | 1.15254e+06 | 0.655773 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1345.7 | 0.79591 | 5731.7ms | 5373214 | 80 | 7.3483e+10 | 3.80789e+06 | 1.05299 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1220.37 | 1.35768 | 6070.77ms | 5373214 | 30 | 9.7499e+10 | 4.19897e+06 | 0.172001 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1193.97 | 0.0793523 | 6561.38ms | 5373214 | 40 | 4.63939e+08 | 4.29181e+06 | 0.615578 | 2(Tie) | true |
| Glaze | 1114.67 | 1.22973 | 6975.83ms | 5373214 | 30 | 9.58766e+10 | 4.59713e+06 | 0.102132 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1573.31 | 0.789635 | 5711.93ms | 5373214 | 80 | 5.29155e+10 | 3.25702e+06 | 0.890257 | 1(Win) | true |
| Jsonifier (two-stage) | 1484.95 | 1.0401 | 5926.61ms | 5373214 | 40 | 5.15297e+10 | 3.45083e+06 | 2.0504 | 2(Loss) | true |
| simdjson (ondemand) | 1278.82 | 1.14328 | 6664.16ms | 5373214 | 40 | 8.39494e+10 | 4.00705e+06 | 1.34052 | 3(Loss) | true |
| Glaze | 1207.99 | 0.467649 | 6933.48ms | 5373214 | 80 | 3.14829e+10 | 4.24202e+06 | 4.15754 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7242.77 | 0.465203 | 5833.51ms | 6661989 | 30 | 4.99579e+08 | 877202 | 0.679902 | 1(Win) | true |
| Glaze | 3485.81 | 0.324585 | 5780ms | 6661897 | 80 | 2.79985e+09 | 1.82261e+06 | 2.07242 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7262.1 | 0.205585 | 5685.02ms | 6661989 | 40 | 1.29398e+08 | 874867 | 0.0107799 | 1(Win) | true |
| Glaze | 3579.69 | 0.555711 | 5179.63ms | 6661897 | 160 | 1.55641e+10 | 1.77481e+06 | 0.290763 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2148.55 | 0.10443 | 5986.23ms | 500299 | 320 | 1.72094e+07 | 222067 | 0.1428 | 1(Win) | true |
| Jsonifier (two-stage) | 1362.87 | 0.656527 | 9363.27ms | 500299 | 40 | 2.11309e+08 | 350088 | 0.149763 | 2(Loss) | true |
| Glaze | 1265.7 | 0.255129 | 5021.76ms | 500299 | 30 | 2.77483e+07 | 376963 | 0.173606 | 3(Loss) | true |
| simdjson (ondemand) | 816.606 | 0.224666 | 7532.26ms | 500299 | 40 | 6.89239e+07 | 584275 | 0.0707713 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2173.96 | 0.954785 | 6093.84ms | 500299 | 80 | 3.51283e+08 | 219471 | 1.9084 | 1(Win) | true |
| Jsonifier (two-stage) | 1589.23 | 0.163539 | 8750.34ms | 500299 | 160 | 3.857e+07 | 300223 | 0.223144 | 2(Loss) | true |
| Glaze | 1421.47 | 0.17079 | 9903.08ms | 500299 | 80 | 2.62904e+07 | 335655 | 0.105446 | 3(Loss) | true |
| simdjson (ondemand) | 868.236 | 0.0963015 | 7369.09ms | 500299 | 640 | 1.79238e+08 | 549531 | 0.26402 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9148.29 | 0.636744 | 5389.52ms | 500299 | 40 | 4.41132e+06 | 52154.2 | 0.791742 | 1(Win) | true |
| Glaze | 2110.61 | 0.238113 | 5904.69ms | 500299 | 160 | 4.63584e+07 | 226059 | 1.10993 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9189.35 | 0.14742 | 5324.38ms | 500299 | 640 | 3.7496e+06 | 51921.2 | 0.328467 | 1(Win) | true |
| Glaze | 2243.31 | 0.110642 | 5423.69ms | 500299 | 640 | 3.54404e+07 | 212687 | 0.133461 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2880.73 | 0.236384 | 5279.05ms | 1151920 | 40 | 3.2504e+07 | 381347 | 0.463355 | 1(Win) | true |
| Jsonifier (two-stage) | 2202.56 | 0.303086 | 6663.37ms | 1151920 | 640 | 1.46252e+09 | 498764 | 0.760008 | 2(Loss) | true |
| Glaze | 1724.64 | 0.86655 | 7543.11ms | 1151920 | 30 | 9.14018e+08 | 636976 | 0.872727 | 3(Loss) | true |
| simdjson (ondemand) | 1530.58 | 0.484056 | 9142.46ms | 1151920 | 320 | 3.86254e+09 | 717738 | 0.979324 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3074.14 | 0.236093 | 5110.57ms | 1151920 | 640 | 4.55557e+08 | 357354 | 1.18164 | 1(Win) | true |
| Jsonifier (two-stage) | 2475.42 | 0.746625 | 6161.77ms | 1151920 | 160 | 1.7566e+09 | 443786 | 0.0885242 | 2(Loss) | true |
| Glaze | 2175.48 | 0.0616184 | 7092.25ms | 1151920 | 320 | 3.09816e+07 | 504971 | 0.103212 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1491.07 | 1.1498 | 8772.36ms | 1151920 | 30 | 2.15285e+09 | 736758 | 6.10615 | -(Loss) | false |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14526.1 | 0.126292 | 9857.42ms | 1439562 | 320 | 4.55894e+06 | 94510.8 | 0.0612905 | 1(Win) | true |
| Glaze | 4230.1 | 0.0972678 | 8629.21ms | 1439584 | 1280 | 1.27562e+08 | 324553 | 0.0282408 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14468.8 | 0.203686 | 5103.82ms | 1439562 | 80 | 2.9882e+06 | 94885.4 | 0.0681542 | 1(Win) | true |
| Glaze | 4958.39 | 0.182258 | 7101.38ms | 1439584 | 80 | 2.0373e+07 | 276883 | 0.0545609 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2062.43 | 0.35481 | 2535.42ms | 56369 | 1280 | 1.09477e+07 | 26065.2 | 0.989678 | 1(Win) | true |
| Glaze | 1447.84 | 0.759443 | 3998ms | 56369 | 160 | 1.27219e+07 | 37129.7 | 0.531837 | 2(Loss) | true |
| Jsonifier (two-stage) | 1129.34 | 1.80297 | 4690.83ms | 56369 | 40 | 2.94625e+07 | 47601 | 0.00770351 | 3(Loss) | true |
| simdjson (ondemand) | 699.773 | 0.134499 | 8005.84ms | 56369 | 4890 | 5.22056e+07 | 76821.6 | 1.54563 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2826.03 | 0.445807 | 2187.49ms | 56369 | 640 | 4.60258e+06 | 19022.3 | 0.502691 | 1(Win) | true |
| Glaze | 1906.44 | 0.19876 | 3594.08ms | 56369 | 40 | 125647 | 28197.9 | 0.145632 | 2(Loss) | true |
| Jsonifier (two-stage) | 1464.59 | 0.221361 | 4372.86ms | 56369 | 2560 | 1.69003e+07 | 36705 | 0.295118 | 3(Loss) | true |
| simdjson (ondemand) | 784.596 | 0.226297 | 7019.96ms | 56369 | 640 | 1.5386e+07 | 68516.4 | 0.0310081 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11274.4 | 0.260522 | 499.762ms | 56369 | 30 | 4629.13 | 4768.1 | 0.0293532 | 1(Win) | true |
| Glaze | 3102.24 | 0.341683 | 1746.91ms | 56369 | 640 | 2.24366e+06 | 17328.6 | 0.888518 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11516.8 | 0.306547 | 490.964ms | 56369 | 640 | 131037 | 4667.78 | 0.168458 | 1(Win) | true |
| Glaze | 3695.94 | 0.310521 | 1461.78ms | 56369 | 320 | 652774 | 14545.1 | 0.126836 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2368.34 | 0.366493 | 3419.42ms | 83958 | 80 | 1.22817e+06 | 33807.8 | 0.219547 | 1(Win) | true |
| Glaze | 1841.22 | 0.130079 | 4377.76ms | 83958 | 2560 | 8.19154e+06 | 43486.7 | 0.114157 | 2(Loss) | true |
| Jsonifier (two-stage) | 1811.68 | 0.0870935 | 4673.15ms | 83958 | 1280 | 1.89647e+06 | 44195.9 | 0.0546945 | 3(Loss) | true |
| simdjson (ondemand) | 1101.46 | 0.992386 | 7724.36ms | 83958 | 30 | 1.56124e+07 | 72693.3 | 0.712255 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2711.03 | 0.0431535 | 3122.85ms | 83958 | 80 | 12995 | 29534.4 | 0.0174766 | 1(Win) | true |
| Jsonifier (two-stage) | 2283.06 | 0.0567498 | 4260.59ms | 83958 | 30 | 11883.4 | 35070.7 | 0.0199557 | 2(Loss) | true |
| Glaze | 2170.73 | 0.0710314 | 3896.52ms | 83958 | 2560 | 1.75733e+06 | 36885.6 | 0.13598 | 3(Loss) | true |
| simdjson (ondemand) | 1214.12 | 0.0584738 | 6936.31ms | 83958 | 2560 | 3.80685e+06 | 65948 | 0.00800105 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12749.7 | 0.0364098 | 716.163ms | 94370 | 160 | 1056.87 | 7058.84 | 0.125129 | 1(Win) | true |
| Glaze | 3004.91 | 0.164332 | 3087.41ms | 94370 | 1280 | 3.10067e+06 | 29950.3 | 0.090288 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13088.7 | 0.0580841 | 699.516ms | 94370 | 80 | 1276.09 | 6876.04 | 0.166425 | 1(Win) | true |
| Glaze | 3448.9 | 0.262272 | 2638.73ms | 94370 | 160 | 749428 | 26094.8 | 0.0216086 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1845.75 | 0.0334788 | 2787.05ms | 53331 | 30 | 2553.15 | 27555.5 | 0.351503 | 1(Win) | true |
| Jsonifier (two-stage) | 1565.15 | 0.0721022 | 3360.65ms | 53331 | 2560 | 1.40535e+06 | 32495.5 | 0.46524 | 2(Loss) | true |
| Glaze | 1529.89 | 0.13912 | 3462.54ms | 53331 | 30 | 64170.8 | 33244.4 | 0.0165469 | 3(Loss) | true |
| simdjson (ondemand) | 887.926 | 0.0484214 | 5872.95ms | 53331 | 4890 | 3.76174e+06 | 57280 | 0.0289847 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2572.76 | 0.0806849 | 2529.54ms | 53331 | 2560 | 651305 | 19768.8 | 0.066532 | 1(Win) | true |
| Jsonifier (two-stage) | 2078.51 | 0.0417508 | 3041.32ms | 53331 | 40 | 4174.89 | 24469.7 | 0.00698192 | 2(Loss) | true |
| Glaze | 1974.56 | 0.200125 | 3092.96ms | 53331 | 160 | 425149 | 25757.8 | 0.00177127 | 3(Loss) | true |
| simdjson (ondemand) | 1016.94 | 0.136345 | 5502.76ms | 53331 | 1280 | 5.95197e+06 | 50013.3 | 0.152296 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14177.2 | 0.0618611 | 439.106ms | 58581 | 160 | 950.799 | 3940.64 | 0.0922223 | 1(Win) | true |
| Glaze | 4769.44 | 0.140554 | 1193.19ms | 58581 | 1280 | 346956 | 11713.6 | 0.0881079 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15044.4 | 0.129573 | 391.899ms | 58581 | 2560 | 59269.6 | 3713.5 | 0.137399 | 1(Win) | true |
| Glaze | 6137.47 | 0.0647909 | 938.865ms | 58581 | 4890 | 170087 | 9102.64 | 0.0275291 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1838.57 | 0.141771 | 3511ms | 65103 | 640 | 1.46688e+06 | 33769.2 | 0.104026 | 1(Win) | true |
| Jsonifier (two-stage) | 1765.2 | 0.0716605 | 3573.18ms | 65103 | 4890 | 3.10657e+06 | 35172.8 | 0.0692827 | 2(Loss) | true |
| Glaze | 1678.27 | 0.215877 | 3841.78ms | 65103 | 320 | 2.04099e+06 | 36994.7 | 0.078421 | 3(Loss) | true |
| simdjson (ondemand) | 1073.44 | 0.0410552 | 5865.73ms | 65103 | 40 | 22555.1 | 57839.4 | 0.150219 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2448.12 | 0.119111 | 3094.24ms | 65103 | 1280 | 1.16801e+06 | 25361.1 | 0.0233602 | 1(Win) | true |
| Jsonifier (two-stage) | 2333 | 0.0346028 | 3464.03ms | 65103 | 30 | 2543.98 | 26612.5 | 0.18811 | 2(Loss) | true |
| Glaze | 2130.44 | 0.14672 | 3608.28ms | 65103 | 640 | 1.1701e+06 | 29142.8 | 0.0936733 | 3(Loss) | true |
| simdjson (ondemand) | 1224.02 | 0.088643 | 5704.93ms | 65103 | 1280 | 2.58776e+06 | 50723.9 | 0.255633 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13493.6 | 0.0504441 | 593.277ms | 78778 | 80 | 631.048 | 5567.7 | 0.0193041 | 1(Win) | true |
| Glaze | 4094.43 | 0.068374 | 1894.14ms | 78778 | 40 | 6296 | 18349 | 0.176616 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14130.7 | 0.111762 | 542.453ms | 78778 | 40 | 1412.32 | 5316.7 | 0.0275784 | 1(Win) | true |
| Glaze | 5201.43 | 0.0719603 | 1461.89ms | 78778 | 4890 | 528274 | 14443.8 | 0.142071 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2198.46 | 0.059573 | 518.565ms | 11812 | 80 | 745.415 | 5123.95 | 0.01952 | 1(Win) | true |
| Jsonifier (two-stage) | 1245.07 | 0.0214268 | 913.479ms | 11812 | 320 | 1202.61 | 9047.53 | 0.0935499 | 2(Loss) | true |
| Glaze | 1048.46 | 0.090971 | 1082.1ms | 11812 | 2560 | 244560 | 10744.1 | 0.0586749 | 3(Loss) | true |
| simdjson (ondemand) | 817.034 | 0.0639568 | 1398.88ms | 11812 | 4890 | 380232 | 13787.4 | 0.129348 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2339.28 | 0.0289436 | 508.4ms | 11812 | 320 | 621.636 | 4815.5 | 0.0508383 | 1(Win) | true |
| Jsonifier (two-stage) | 1426.16 | 0.0699838 | 910.386ms | 11812 | 30 | 916.7 | 7898.7 | 0.0021101 | 2(Loss) | true |
| Glaze | 1125.09 | 0.13423 | 1132.57ms | 11812 | 40 | 7224.91 | 10012.4 | 0.0820491 | 3(Loss) | true |
| simdjson (ondemand) | 865.548 | 0.0956518 | 1357.23ms | 11812 | 40 | 6198.85 | 13014.6 | 0.0160102 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9131.25 | 0.0686112 | 127.17ms | 11812 | 640 | 458.518 | 1233.65 | 0.0577887 | 1(Win) | true |
| Glaze | 2354.62 | 0.0869743 | 484.523ms | 11812 | 2560 | 44322.9 | 4784.13 | 0.0630187 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9433.38 | 0.0486195 | 123.073ms | 11812 | 1280 | 431.462 | 1194.14 | 0.0435911 | 1(Win) | true |
| Glaze | 2612.47 | 0.0773499 | 444.51ms | 11812 | 4890 | 54396.7 | 4311.93 | 0.0462222 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2930.85 | 0.041132 | 868.604ms | 25388 | 30 | 346.378 | 8261.03 | 0.000806995 | 1(Win) | true |
| Jsonifier (two-stage) | 2208.5 | 0.0351174 | 1115ms | 25388 | 80 | 1185.76 | 10963 | 0.0144826 | 2(Loss) | true |
| Glaze | 1752.09 | 0.10737 | 1501.16ms | 25388 | 1280 | 281786 | 13818.9 | 0.0357964 | 3(Loss) | true |
| simdjson (ondemand) | 1649.32 | 0.0459243 | 1483.19ms | 25388 | 160 | 7271.95 | 14679.9 | 0.0310703 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2824.23 | 1.29625 | 885.897ms | 25388 | 40 | 493967 | 8572.92 | 0.265345 | 1(Win) | true |
| Jsonifier (two-stage) | 2460.15 | 0.031488 | 1124.51ms | 25388 | 30 | 288.102 | 9841.63 | 0.0145661 | 2(Loss) | true |
| Glaze | 1819.02 | 0.377772 | 1370.88ms | 25388 | 1280 | 3.23632e+06 | 13310.4 | 0.292731 | 3(Loss) | true |
| simdjson (ondemand) | 1718.11 | 0.0949172 | 1429.65ms | 25388 | 2560 | 458023 | 14092.2 | 0.00973682 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12976.3 | 0.0422437 | 233.998ms | 31235 | 320 | 300.923 | 2295.57 | 0.112183 | 1(Win) | true |
| Glaze | 3814.65 | 0.0704792 | 867.581ms | 31235 | 4890 | 148116 | 7808.84 | 0.390808 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14066.2 | 0.119857 | 218.304ms | 31235 | 40 | 257.703 | 2117.7 | 0.0188848 | 1(Win) | true |
| Glaze | 4379.91 | 0.12817 | 686.528ms | 31235 | 1280 | 97260.1 | 6801.06 | 0.0617012 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2772.92 | 0.0376208 | 3768.5ms | 108313 | 80 | 15712.1 | 37251.5 | 0.0520513 | 1(Win) | true |
| Jsonifier (two-stage) | 1749.19 | 0.221179 | 6151.06ms | 108313 | 160 | 2.72958e+06 | 59053.1 | 0.115398 | 2(Loss) | true |
| Glaze | 1537.92 | 0.149495 | 6925.12ms | 108313 | 320 | 3.22623e+06 | 67165.5 | 0.305818 | 3(Loss) | true |
| simdjson (ondemand) | 686.493 | 0.0622316 | 8287.81ms | 108313 | 1280 | 1.12233e+07 | 150468 | 0.286536 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3248.54 | 0.0597369 | 3506.3ms | 108313 | 4890 | 1.76433e+06 | 31797.5 | 1.55196 | 1(Win) | true |
| Jsonifier (two-stage) | 1941.94 | 0.0523493 | 5636.15ms | 108313 | 4890 | 3.79159e+06 | 53191.9 | 0.0591466 | 2(Loss) | true |
| Glaze | 1399.14 | 0.381237 | 6855.06ms | 108313 | 640 | 5.07003e+07 | 73827.9 | 0.106545 | 3(Loss) | true |
| simdjson (ondemand) | 570.95 | 1.06203 | 7935.28ms | 108313 | 160 | 5.90684e+08 | 180918 | 0.0877251 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11397.1 | 0.304093 | 950.78ms | 108313 | 160 | 121536 | 9063.3 | 0.459162 | 1(Win) | true |
| Glaze | 2344.53 | 0.186579 | 4500.1ms | 108313 | 320 | 2.16236e+06 | 44058.1 | 0.0956698 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11581.1 | 0.089353 | 922.945ms | 108313 | 4890 | 310588 | 8919.27 | 0.0278838 | 1(Win) | true |
| Glaze | 2566.34 | 0.0904939 | 4267.14ms | 108313 | 40 | 53067.8 | 40250 | 0.0410804 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2708.73 | 0.252499 | 6943.13ms | 183677 | 160 | 4.26594e+06 | 64667.9 | 0.0525169 | 1(Win) | true |
| Jsonifier (two-stage) | 2320.23 | 0.0714199 | 7676.76ms | 183677 | 4890 | 1.42166e+07 | 75496.1 | 0.363673 | 2(Loss) | true |
| Glaze | 1836.23 | 0.211464 | 9684.64ms | 183677 | 320 | 1.3022e+07 | 95395.6 | 0.0881812 | 3(Loss) | true |
| simdjson (ondemand) | 1129.55 | 0.094503 | 8092.67ms | 183677 | 640 | 1.37459e+07 | 155078 | 0.0238142 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2866.03 | 0.175322 | 6294.09ms | 183677 | 640 | 7.34851e+06 | 61118.7 | 0.161942 | 1(Win) | true |
| Jsonifier (two-stage) | 2235.8 | 0.520894 | 7244.5ms | 183677 | 320 | 5.32954e+07 | 78346.7 | 0.530154 | 2(Loss) | true |
| Glaze | 1962.08 | 0.213877 | 9356.86ms | 183677 | 320 | 1.16669e+07 | 89276.8 | 0.195196 | 3(Loss) | true |
| simdjson (ondemand) | 1174.63 | 0.0955461 | 7894.8ms | 183677 | 640 | 1.29931e+07 | 149126 | 0.179696 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14700.6 | 0.198941 | 1492.84ms | 213963 | 30 | 22876 | 13880.5 | 0.250859 | 1(Win) | true |
| Glaze | 3238.68 | 0.0497416 | 6415.87ms | 213963 | 4890 | 4.80273e+06 | 63004.3 | 0.0351208 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15470.6 | 0.0787581 | 1376.59ms | 213963 | 2560 | 276243 | 13189.6 | 0.185355 | 1(Win) | true |
| Glaze | 3672.1 | 0.310407 | 5903.51ms | 213963 | 30 | 892550 | 55568 | 0.00989876 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 589.068 | 2.32754 | 8840.06ms | 1834197 | 30 | 1.4331e+11 | 2.96948e+06 | 1.9658 | 1(Win) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 554.997 | 0.246161 | 10229.9ms | 1834197 | 160 | 9.63096e+09 | 3.15178e+06 | 7.53197 | -(Loss) | false |
| simdjson (ondemand) STATISTICAL TIE | 410.14 | 0.0985526 | 6530.59ms | 1834197 | 30 | 5.30012e+08 | 4.26495e+06 | 0.398018 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 408.154 | 0.779001 | 6609.8ms | 1834197 | 30 | 3.34381e+10 | 4.28571e+06 | 2.7944 | 3(Tie) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 722.15 | 1.13164 | 8567.78ms | 1834197 | 40 | 3.00549e+10 | 2.42225e+06 | 2.2579 | 1(Win) | true |
| Jsonifier (two-stage) | 636.871 | 0.207674 | 9769.45ms | 1834197 | 80 | 2.60281e+09 | 2.74659e+06 | 0.132479 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 429.379 | 0.648315 | 6738.97ms | 1834197 | 80 | 5.5805e+10 | 4.07385e+06 | 0.625912 | 3(Tie) | true |
| Glaze STATISTICAL TIE DID NOT CONVERGE | 421.148 | 0.981524 | 6524.22ms | 1834197 | 80 | 1.32958e+11 | 4.15347e+06 | 8.71504 | -(Tie) | false |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1296.98 | 2.16687 | 7927.12ms | 1922245 | 30 | 2.8141e+10 | 1.41344e+06 | 3.82129 | 1(Win) | true |
| Glaze | 872.192 | 0.463379 | 6297.58ms | 1833577 | 30 | 2.58921e+09 | 2.00488e+06 | 0.599361 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1484.08 | 0.84263 | 7748.07ms | 1922245 | 40 | 4.33346e+09 | 1.23524e+06 | 3.95514 | 1(Win) | true |
| Glaze | 877.702 | 0.282299 | 6316.45ms | 1833577 | 80 | 2.53053e+09 | 1.99229e+06 | 0.879808 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2087.12 | 0.593772 | 5172.62ms | 7351818 | 80 | 3.1829e+10 | 3.35929e+06 | 0.00985984 | 1(Win) | true |
| Jsonifier (two-stage) | 1823.53 | 1.15523 | 5747.1ms | 7351818 | 40 | 7.89148e+10 | 3.84488e+06 | 1.4165 | 2(Loss) | true |
| Glaze | 1494.11 | 0.451092 | 7401.06ms | 7351818 | 30 | 1.34423e+10 | 4.69257e+06 | 0.354002 | 3(Loss) | true |
| simdjson (ondemand) | 1430.83 | 0.188365 | 7463.82ms | 7351818 | 80 | 6.81559e+09 | 4.90011e+06 | 0.252811 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2311.38 | 0.39264 | 5172.58ms | 7351818 | 40 | 5.67407e+09 | 3.03335e+06 | 0.164798 | 1(Win) | true |
| Jsonifier (two-stage) | 2124.31 | 0.48106 | 5641.89ms | 7351818 | 30 | 7.5626e+09 | 3.30047e+06 | 1.28999 | 2(Loss) | true |
| Glaze | 1594.34 | 0.119448 | 7215.75ms | 7351818 | 80 | 2.20737e+09 | 4.39759e+06 | 1.30635 | 3(Loss) | true |
| simdjson (ondemand) | 1536.81 | 0.188549 | 7502.1ms | 7351818 | 30 | 2.21982e+09 | 4.5622e+06 | 0.0856183 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5489 | 0.167766 | 5500.83ms | 10018896 | 160 | 1.36453e+09 | 1.74071e+06 | 0.127372 | 1(Win) | true |
| Glaze | 3204.91 | 0.280902 | 9337.42ms | 9930228 | 30 | 2.0669e+09 | 2.95491e+06 | 0.237554 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5497.33 | 0.106442 | 5511.91ms | 10018896 | 80 | 2.7381e+08 | 1.73807e+06 | 0.0278511 | 1(Win) | true |
| Glaze | 3318.53 | 0.122551 | 9062.16ms | 9930228 | 30 | 3.66927e+08 | 2.85374e+06 | 0.100705 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 644.402 | 0.461318 | 8558.22ms | 1834197 | 160 | 2.50899e+10 | 2.7145e+06 | 0.389093 | 1(Win) | true |
| Jsonifier (two-stage) | 547.055 | 0.455805 | 10261.8ms | 1834197 | 80 | 1.69933e+10 | 3.19753e+06 | 0.175235 | 2(Loss) | true |
| Glaze | 470.39 | 0.0794318 | 5615.31ms | 1834197 | 40 | 3.48999e+08 | 3.71867e+06 | 0.0787012 | 3(Loss) | true |
| simdjson (ondemand) | 404.34 | 0.538531 | 6548.03ms | 1834197 | 80 | 4.34222e+10 | 4.32613e+06 | 0.551081 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 757.518 | 0.295003 | 8505.55ms | 1834197 | 30 | 1.39213e+09 | 2.30915e+06 | 0.39892 | 1(Win) | true |
| Jsonifier (two-stage) | 644.314 | 0.228533 | 9662.64ms | 1834197 | 30 | 1.15482e+09 | 2.71487e+06 | 0.115539 | 2(Loss) | true |
| Glaze | 517.483 | 0.104624 | 5806.18ms | 1834197 | 30 | 3.75216e+08 | 3.38026e+06 | 0.0995747 | 3(Loss) | true |
| simdjson (ondemand) | 442.392 | 0.11493 | 6760.85ms | 1834197 | 30 | 6.19533e+08 | 3.95402e+06 | 0.0136931 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1518.86 | 0.367065 | 7853.99ms | 1922245 | 40 | 7.85105e+08 | 1.20695e+06 | 0.00599269 | 1(Win) | true |
| Glaze | 860.365 | 0.354008 | 6479.09ms | 1833577 | 80 | 4.14143e+09 | 2.03243e+06 | 0.145133 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1510.98 | 0.444016 | 7829.4ms | 1922245 | 30 | 8.70596e+08 | 1.21325e+06 | 0.251912 | 1(Win) | true |
| Glaze | 876.201 | 0.428234 | 6347.06ms | 1833577 | 30 | 2.19116e+09 | 1.9957e+06 | 1.05961 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2107.34 | 0.296335 | 5209.15ms | 7351818 | 40 | 3.8882e+09 | 3.32706e+06 | 2.91794 | 1(Win) | true |
| Jsonifier (two-stage) | 1666.65 | 0.728825 | 6249.47ms | 7351818 | 30 | 2.82014e+10 | 4.2068e+06 | 0.359659 | 2(Loss) | true |
| Glaze | 1415 | 0.89627 | 7529.62ms | 7351818 | 30 | 5.91662e+10 | 4.95493e+06 | 0.2135 | 3(Loss) | true |
| simdjson (ondemand) | 1226.95 | 0.879947 | 8218.16ms | 7351818 | 40 | 1.01137e+11 | 5.71438e+06 | 0.537914 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2062.57 | 0.401659 | 5619.8ms | 7351818 | 80 | 1.49135e+10 | 3.39928e+06 | 0.716863 | 1(Win) | true |
| Jsonifier (two-stage) | 1933.46 | 0.844624 | 6022.9ms | 7351818 | 30 | 2.81427e+10 | 3.62626e+06 | 1.10923 | 2(Loss) | true |
| Glaze | 1527.93 | 0.820209 | 7476.68ms | 7351818 | 30 | 4.24967e+10 | 4.58873e+06 | 1.36441 | 3(Loss) | true |
| simdjson (ondemand) | 1398.62 | 0.439147 | 8347.87ms | 7351818 | 40 | 1.93851e+10 | 5.01296e+06 | 3.13936 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4759.97 | 0.539748 | 6159.03ms | 10018896 | 80 | 9.39082e+09 | 2.00732e+06 | 0.523871 | 1(Win) | true |
| Glaze | 2504.3 | 0.509429 | 5725.13ms | 9930228 | 80 | 2.96895e+10 | 3.78157e+06 | 0.601281 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5397.52 | 0.353224 | 5981.68ms | 10018896 | 80 | 3.12782e+09 | 1.77021e+06 | 3.23188 | 1(Win) | true |
| Glaze | 2916.4 | 0.509272 | 10060.3ms | 9930228 | 40 | 1.09392e+10 | 3.24723e+06 | 0.548424 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1137.05 | 0.253574 | 5014.2ms | 461466 | 640 | 6.16465e+08 | 387044 | 0.148816 | 1(Win) | true |
| Jsonifier (two-stage) | 882.847 | 0.629894 | 6371.54ms | 461466 | 30 | 2.95778e+08 | 498488 | 0.47142 | 2(Loss) | true |
| Glaze | 753.572 | 0.483209 | 7572.67ms | 461466 | 320 | 2.5483e+09 | 584003 | 3.24873 | 3(Loss) | true |
| simdjson (ondemand) | 590.509 | 0.468051 | 9692.87ms | 461466 | 160 | 1.94685e+09 | 745270 | 0.114894 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1536.95 | 0.949626 | 9627.48ms | 461466 | 80 | 5.91502e+08 | 286339 | 0.793823 | 1(Win) | true |
| Jsonifier (two-stage) | 1176.16 | 0.502983 | 6268.98ms | 461466 | 320 | 1.13345e+09 | 374172 | 3.8643 | 2(Loss) | true |
| Glaze | 870.635 | 0.713498 | 7276.41ms | 461466 | 160 | 2.08119e+09 | 505480 | 0.228133 | 3(Loss) | true |
| simdjson (ondemand) | 669.522 | 0.663117 | 9588.7ms | 461466 | 160 | 3.03983e+09 | 657317 | 1.24888 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10319.6 | 0.0615142 | 4326.32ms | 461466 | 4890 | 3.36519e+06 | 42645.7 | 0.126713 | 1(Win) | true |
| Glaze | 2535.25 | 0.159442 | 9186.7ms | 461466 | 1280 | 9.80519e+07 | 173588 | 0.405282 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10425.3 | 0.0427401 | 4381.75ms | 461466 | 40 | 13020.7 | 42213.4 | 0.0220752 | 1(Win) | true |
| Glaze | 2854.43 | 0.355972 | 8600ms | 461466 | 40 | 1.20485e+07 | 154177 | 0.893245 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1477.1 | 0.171343 | 6028.34ms | 728486 | 320 | 2.07829e+08 | 470340 | 0.961755 | 1(Win) | true |
| Glaze | 1129.08 | 0.499154 | 8170.47ms | 728486 | 30 | 2.82998e+08 | 615314 | 1.54463 | 2(Loss) | true |
| Jsonifier (two-stage) | 1074.11 | 0.588142 | 8053.55ms | 728486 | 40 | 5.7885e+08 | 646801 | 0.0878028 | 3(Loss) | true |
| simdjson (ondemand) | 893.674 | 0.16161 | 9836.05ms | 728486 | 320 | 5.05094e+08 | 777396 | 0.465407 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1888.9 | 0.458167 | 5694.35ms | 728486 | 30 | 8.51909e+07 | 367800 | 0.28556 | 1(Win) | true |
| Jsonifier (two-stage) | 1537.62 | 0.487183 | 7856.89ms | 728486 | 80 | 3.87629e+08 | 451826 | 0.239647 | 2(Loss) | true |
| Glaze | 1298.47 | 0.52016 | 7874.65ms | 728486 | 30 | 2.32368e+08 | 535046 | 0.0526718 | 3(Loss) | true |
| simdjson (ondemand) | 1019.14 | 0.186574 | 9740.32ms | 728486 | 640 | 1.03529e+09 | 681692 | 1.74396 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10542.6 | 0.120154 | 7595.55ms | 837491 | 4890 | 4.05181e+07 | 75758.8 | 0.0180524 | 1(Win) | true |
| Glaze | 2983.69 | 0.425569 | 7106.07ms | 837491 | 80 | 1.03821e+08 | 267687 | 0.1288 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12428.1 | 0.380654 | 6518.54ms | 837491 | 160 | 9.57491e+06 | 64265.3 | 0.55245 | 1(Win) | true |
| Glaze | 3059.59 | 0.522173 | 6285.22ms | 837491 | 320 | 5.94583e+08 | 261046 | 1.99587 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 4920.12 | 0.0884841 | 9194ms | 466906 | 4890 | 3.13579e+07 | 90501 | 0.619884 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 4899.14 | 0.682992 | 9273.36ms | 466906 | 40 | 1.54138e+07 | 90888.6 | 0.162072 | 1(Tie) | true |
| simdjson (ondemand) | 3600.59 | 0.239459 | 6301.21ms | 466906 | 1280 | 1.12249e+08 | 123668 | 0.336727 | 3(Loss) | true |
| Glaze | 2100.82 | 0.339823 | 5296.57ms | 466906 | 160 | 8.30052e+07 | 211953 | 1.31581 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5145.72 | 0.35185 | 9272.24ms | 466906 | 30 | 2.781e+06 | 86533.3 | 0.707745 | 1(Win) | true |
| Jsonifier (two-stage) | 4920.29 | 0.277256 | 9255.35ms | 466906 | 1280 | 8.05841e+07 | 90498 | 0.499221 | 2(Loss) | true |
| simdjson (ondemand) | 3771.06 | 0.232448 | 6260.92ms | 466906 | 1280 | 9.64262e+07 | 118077 | 1.22051 | 3(Loss) | true |
| Glaze | 2200.65 | 0.175885 | 5309.85ms | 466906 | 160 | 2.02645e+07 | 202339 | 0.00408642 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 5032.3 | 0.402825 | 6307.26ms | 631514 | 320 | 7.43732e+07 | 119679 | 2.7884 | 1(Win) | true |
| Jsonifier | 4880.15 | 0.300788 | 6438.15ms | 631514 | 640 | 8.81863e+07 | 123410 | 3.13682 | 2(Loss) | true |
| simdjson (ondemand) | 4498.43 | 0.24281 | 7225.2ms | 631514 | 640 | 6.76326e+07 | 133882 | 0.0800554 | 3(Loss) | true |
| Glaze | 2507.22 | 0.766545 | 6140.04ms | 631514 | 40 | 1.35617e+08 | 240209 | 0.216501 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 5059.24 | 0.444036 | 6406.16ms | 631514 | 160 | 4.47046e+07 | 119041 | 0.445445 | 1(Win) | true |
| Jsonifier | 4863.68 | 0.635006 | 6416.43ms | 631514 | 30 | 1.85487e+07 | 123828 | 0.113147 | 2(Loss) | true |
| simdjson (ondemand) | 4474.2 | 0.242065 | 6953.16ms | 631514 | 640 | 6.79482e+07 | 134607 | 0.586858 | 3(Loss) | true |
| Glaze | 2579.16 | 0.397243 | 6057.92ms | 631514 | 40 | 3.44177e+07 | 233509 | 0.0620397 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2122.64 | 0.39655 | 5381.59ms | 466906 | 80 | 5.53596e+07 | 209775 | 0.0977175 | 1(Win) | true |
| Jsonifier (two-stage) | 1608.49 | 0.509559 | 7062.24ms | 466906 | 80 | 1.59185e+08 | 276829 | 1.12999 | 2(Loss) | true |
| Glaze | 1499.36 | 0.428732 | 7579.77ms | 466906 | 320 | 5.18766e+08 | 296978 | 0.599053 | 3(Loss) | true |
| simdjson (ondemand) | 771.94 | 0.22212 | 7493.44ms | 466906 | 160 | 2.62656e+08 | 576828 | 0.56947 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2713.25 | 0.3812 | 5220.36ms | 466906 | 80 | 3.13095e+07 | 164112 | 0.265691 | 1(Win) | true |
| Jsonifier (two-stage) | 1968.74 | 0.577129 | 6634.89ms | 466906 | 640 | 1.09046e+09 | 226173 | 0.0171659 | 2(Loss) | true |
| Glaze DID NOT CONVERGE | 1827.82 | 0.911896 | 6806.56ms | 466906 | 80 | 3.94797e+08 | 243611 | 5.008 | -(Loss) | false |
| simdjson (ondemand) | 867.506 | 0.382941 | 7091.07ms | 466906 | 40 | 1.54539e+08 | 513283 | 0.376455 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12849.4 | 0.116321 | 3600.79ms | 475954 | 30 | 50652.9 | 35325 | 0.830322 | 1(Win) | true |
| Glaze | 3994.43 | 1.16427 | 5771.64ms | 475954 | 40 | 7.0014e+07 | 113634 | 2.28038 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13280.4 | 0.095627 | 3522.06ms | 475954 | 4890 | 5.22368e+06 | 34178.5 | 0.0175599 | 1(Win) | true |
| Glaze | 4650.32 | 0.495118 | 5033.19ms | 475954 | 80 | 1.86841e+07 | 97607.3 | 0.12932 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2147.98 | 0.460437 | 7428.49ms | 631514 | 160 | 2.66666e+08 | 280384 | 1.81931 | 1(Win) | true |
| Jsonifier (two-stage) | 1947.58 | 0.356989 | 7962.69ms | 631514 | 640 | 7.79945e+08 | 309234 | 0.557574 | 2(Loss) | true |
| Glaze | 1799.65 | 0.234369 | 8874.59ms | 631514 | 160 | 9.84259e+07 | 334653 | 1.15014 | 3(Loss) | true |
| simdjson (ondemand) | 975.028 | 0.798499 | 7910.27ms | 631514 | 30 | 7.29796e+08 | 617683 | 0.0362183 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2537.83 | 0.240601 | 6844.94ms | 631514 | 1280 | 4.17297e+08 | 237312 | 0.179504 | 1(Win) | true |
| Jsonifier (two-stage) | 2308.54 | 0.428003 | 7692.59ms | 631514 | 640 | 7.97932e+08 | 260883 | 0.839339 | 2(Loss) | true |
| Glaze | 2093.12 | 0.280173 | 8201.93ms | 631514 | 160 | 1.0398e+08 | 287732 | 0.569992 | 3(Loss) | true |
| simdjson (ondemand) | 1039.78 | 0.487886 | 7646.54ms | 631514 | 320 | 2.55545e+09 | 579215 | 1.33058 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12740.1 | 0.72069 | 5365.92ms | 716365 | 160 | 2.3897e+07 | 53624.5 | 0.687463 | 1(Win) | true |
| Glaze | 3594.59 | 0.523846 | 5019.49ms | 716365 | 160 | 1.58598e+08 | 190057 | 0.143366 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13173.6 | 0.72693 | 5167.14ms | 716365 | 160 | 2.27387e+07 | 51859.7 | 0.157475 | 1(Win) | true |
| Glaze | 4117.74 | 0.147996 | 8491.09ms | 716365 | 2560 | 1.54345e+08 | 165911 | 0.0361749 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1410.22 | 0.307447 | 183.989ms | 2632 | 2560 | 76661.2 | 1779.91 | 2.25514 | 1(Win) | true |
| Jsonifier (two-stage) | 1295.54 | 0.157574 | 202.079ms | 2632 | 80 | 745.645 | 1937.47 | 0.106984 | 2(Loss) | true |
| Glaze | 1160.87 | 0.460447 | 235.051ms | 2632 | 640 | 63437 | 2162.23 | 1.00241 | 3(Loss) | true |
| simdjson (ondemand) | 846.091 | 0.459345 | 299.863ms | 2632 | 30 | 5571.06 | 2966.67 | 0.706074 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1853.21 | 0.932813 | 154.525ms | 2632 | 160 | 25540.6 | 1354.44 | 2.17179 | 1(Win) | true |
| Jsonifier (two-stage) | 1549.32 | 0.405694 | 189.634ms | 2632 | 160 | 6912.08 | 1620.11 | 0.878723 | 2(Loss) | true |
| Glaze | 1496.36 | 0.207082 | 206.488ms | 2632 | 4890 | 59005.2 | 1677.45 | 0.0291937 | 3(Loss) | true |
| simdjson (ondemand) | 1122.28 | 0.285448 | 257.05ms | 2632 | 640 | 26085.6 | 2236.57 | 0.485957 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7515.25 | 0.331019 | 38.5475ms | 2632 | 640 | 782.294 | 333.997 | 0.00467841 | 1(Win) | true |
| Glaze | 2732.75 | 0.420729 | 94.5851ms | 2632 | 2560 | 38231.1 | 918.513 | 0.86479 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8231.05 | 0.333123 | 34.6708ms | 2632 | 640 | 660.469 | 304.952 | 0.0445569 | 1(Win) | true |
| Glaze | 3719.33 | 0.297192 | 75.9027ms | 2632 | 320 | 1287.27 | 674.872 | 0.639982 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1438.81 | 0.339211 | 224.132ms | 3370 | 4890 | 280737 | 2233.71 | 0.310547 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1431.94 | 0.551193 | 225.312ms | 3370 | 1280 | 195896 | 2244.42 | 0.226629 | 1(Tie) | true |
| Glaze | 1295.53 | 0.130604 | 283.019ms | 3370 | 160 | 1679.58 | 2480.74 | 0.149119 | 3(Loss) | true |
| simdjson (ondemand) | 1082.94 | 0.316085 | 323.556ms | 3370 | 80 | 7039.54 | 2967.72 | 0.000842403 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1954.36 | 0.228059 | 202.55ms | 3370 | 2560 | 36006.7 | 1644.47 | 0.0461514 | 1(Win) | true |
| Jsonifier | 1924.68 | 0.22142 | 203.723ms | 3370 | 2560 | 34996 | 1669.83 | 0.711 | 2(Loss) | true |
| Glaze | 1751.26 | 0.291128 | 213.831ms | 3370 | 160 | 4567.17 | 1835.19 | 0.0742983 | 3(Loss) | true |
| simdjson (ondemand) | 1321.91 | 0.435844 | 277.365ms | 3370 | 4890 | 549068 | 2431.24 | 1.95219 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8695.58 | 0.208112 | 46.8745ms | 3643 | 640 | 442.483 | 399.541 | 0.111189 | 1(Win) | true |
| Glaze | 2956.08 | 0.293514 | 128.292ms | 3682 | 640 | 7779.92 | 1187.87 | 3.2142 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8217.57 | 1.44429 | 44.9348ms | 3643 | 640 | 23862.7 | 422.781 | 0.126973 | 1(Win) | true |
| Glaze | 3648.05 | 0.690056 | 102.005ms | 3682 | 40 | 1764.72 | 962.55 | 0.277998 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 653.651 | 0.091689 | 697.995ms | 4630 | 40 | 1534.49 | 6755.15 | 0.0985404 | 1(Win) | true |
| Jsonifier (two-stage) | 586.563 | 0.380297 | 790.539ms | 4630 | 30 | 24586.7 | 7527.77 | 4.7949 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 410.648 | 0.298077 | 1120.95ms | 4630 | 2560 | 2.62978e+06 | 10752.5 | 2.22387 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 404.156 | 1.06657 | 1092.33ms | 4630 | 160 | 2.1725e+06 | 10925.3 | 0.0307678 | 3(Tie) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 766.136 | 0.22494 | 730.395ms | 4630 | 2560 | 430252 | 5763.35 | 1.56219 | 1(Win) | true |
| Jsonifier (two-stage) | 738.101 | 0.0629368 | 800.395ms | 4630 | 80 | 1134.04 | 5982.26 | 0.468561 | 2(Loss) | true |
| simdjson (ondemand) | 512.839 | 0.0610274 | 1172.96ms | 4630 | 80 | 2208.72 | 8609.94 | 0.126872 | 3(Loss) | true |
| Glaze | 502.918 | 0.175254 | 1002.67ms | 4630 | 4890 | 1.15775e+06 | 8779.78 | 1.87986 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1997.36 | 0.68202 | 204.882ms | 4630 | 320 | 72743 | 2210.67 | 1.63685 | 1(Win) | true |
| Glaze | 1236.44 | 0.212603 | 361.413ms | 4630 | 4890 | 281878 | 3571.14 | 3.11791 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2679.46 | 0.184989 | 176.341ms | 4630 | 80 | 743.448 | 1647.91 | 0.00379253 | 1(Win) | true |
| Glaze | 1460.31 | 0.223205 | 300.888ms | 4630 | 4890 | 222734 | 3023.68 | 0.423701 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1180.89 | 0.548336 | 944.753ms | 11579 | 640 | 1.68266e+06 | 9351.09 | 0.0786121 | 1(Win) | true |
| Jsonifier (two-stage) | 1049.72 | 0.922299 | 989.51ms | 11579 | 160 | 1.50612e+06 | 10519.6 | 0.160455 | 2(Loss) | true |
| simdjson (ondemand) | 964.445 | 0.211949 | 1192.12ms | 11579 | 4890 | 2.87977e+06 | 11449.7 | 0.101947 | 3(Loss) | true |
| Glaze | 905.399 | 0.673977 | 1243.22ms | 11579 | 320 | 2.16223e+06 | 12196.4 | 0.179962 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1503.67 | 0.564866 | 924.732ms | 11579 | 320 | 550653 | 7343.76 | 1.55965 | 1(Win) | true |
| Jsonifier (two-stage) | 1251.14 | 1.479 | 933.771ms | 11579 | 80 | 1.36319e+06 | 8826.01 | 0.599012 | 2(Loss) | true |
| Glaze | 1058.45 | 0.331576 | 1195.65ms | 11579 | 640 | 765852 | 10432.8 | 0.549135 | 3(Loss) | true |
| simdjson (ondemand) | 1031.96 | 0.393898 | 1239.48ms | 11579 | 1280 | 2.27403e+06 | 10700.6 | 1.322 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6978.56 | 0.193663 | 253.438ms | 14795 | 80 | 1226.53 | 2021.85 | 0.00123648 | 1(Win) | true |
| Glaze | 2898.21 | 0.60743 | 527.223ms | 14795 | 1280 | 1.11937e+06 | 4868.39 | 0.552239 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5592.62 | 2.22073 | 237.364ms | 14795 | 40 | 125561 | 2522.9 | 1.30908 | 1(Win) | true |
| Glaze | 3886.34 | 0.0905636 | 427.993ms | 14795 | 30 | 324.323 | 3630.57 | 0.151262 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1260.48 | 0.212175 | 284.997ms | 3223 | 40 | 1070.77 | 2438.5 | 0.472096 | 1(Win) | true |
| Jsonifier (two-stage) | 919.276 | 0.107412 | 346.032ms | 3223 | 40 | 515.938 | 3343.6 | 0.104568 | 2(Loss) | true |
| Glaze | 713.696 | 0.288825 | 439.791ms | 3223 | 4890 | 756613 | 4306.73 | 0.0206707 | 3(Loss) | true |
| simdjson (ondemand) | 583.986 | 0.398646 | 521.647ms | 3223 | 2560 | 1.12702e+06 | 5263.29 | 1.58072 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1941.91 | 0.107347 | 236.06ms | 3223 | 320 | 923.819 | 1582.82 | 0.661203 | 1(Win) | true |
| Jsonifier (two-stage) | 1253.22 | 0.446059 | 307.572ms | 3223 | 1280 | 153202 | 2452.65 | 0.46376 | 2(Loss) | true |
| Glaze | 991.987 | 0.719037 | 354.316ms | 3223 | 640 | 317681 | 3098.52 | 0.11942 | 3(Loss) | true |
| simdjson (ondemand) | 815.002 | 0.121537 | 428.051ms | 3223 | 4890 | 102737 | 3771.39 | 0.0238753 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7826.7 | 0.297472 | 43.3576ms | 3223 | 320 | 436.723 | 392.719 | 0.530315 | 1(Win) | true |
| Glaze | 1791.3 | 0.397248 | 174.293ms | 3223 | 4890 | 227205 | 1715.9 | 0.12173 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9440.36 | 0.154997 | 36.7191ms | 3223 | 1280 | 325.989 | 325.591 | 0.178682 | 1(Win) | true |
| Glaze | 2039.75 | 0.190146 | 158.382ms | 3223 | 30 | 246.3 | 1506.9 | 0.282343 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1500.66 | 0.940752 | 367.52ms | 5839 | 320 | 389954 | 3710.71 | 1.02028 | 1(Win) | true |
| Jsonifier (two-stage) | 1430.42 | 0.434062 | 397.124ms | 5839 | 640 | 182738 | 3892.9 | 2.06587 | 2(Loss) | true |
| Glaze | 1227.37 | 0.123578 | 471.312ms | 5839 | 2560 | 80473.4 | 4536.96 | 0.0433522 | 3(Loss) | true |
| simdjson (ondemand) | 1100.99 | 0.157327 | 511.057ms | 5839 | 2560 | 162090 | 5057.72 | 0.101297 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2173.06 | 0.144276 | 365.67ms | 5839 | 160 | 2186.94 | 2562.51 | 2.67292 | 1(Win) | true |
| Jsonifier (two-stage) | 2093.55 | 0.249399 | 344.935ms | 5839 | 30 | 1320.14 | 2659.83 | 0.00125323 | 2(Loss) | true |
| Glaze | 1476.32 | 0.295226 | 441.708ms | 5839 | 1280 | 158721 | 3771.88 | 0.00161555 | 3(Loss) | true |
| simdjson (ondemand) | 1459 | 0.220471 | 457.308ms | 5839 | 40 | 2832.23 | 3816.65 | 0.037977 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10408.9 | 0.427314 | 76.4972ms | 6938 | 160 | 1180.52 | 635.669 | 0.369304 | 1(Win) | true |
| Glaze | 2748.05 | 0.0724551 | 257.54ms | 6960 | 160 | 490.035 | 2415.38 | 0.0548268 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12806.3 | 0.329362 | 56.6407ms | 6938 | 160 | 463.33 | 516.669 | 0.40445 | 1(Win) | true |
| Glaze | 2914.47 | 0.252198 | 240.256ms | 6960 | 2560 | 84454.4 | 2277.46 | 0.417582 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2036.74 | 0.0836311 | 235.054ms | 4857 | 160 | 578.792 | 2274.22 | 0.149278 | 1(Win) | true |
| Glaze | 1294.18 | 0.148167 | 370.821ms | 4857 | 2560 | 71992.6 | 3579.08 | 0.337706 | 2(Loss) | true |
| Jsonifier (two-stage) | 1149.4 | 0.264237 | 405.728ms | 4857 | 4890 | 554483 | 4029.92 | 1.19352 | 3(Loss) | true |
| simdjson (ondemand) | 581.387 | 0.174141 | 816.076ms | 4857 | 2560 | 492772 | 7967.15 | 0.409721 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2606.51 | 0.150951 | 208.329ms | 4857 | 80 | 575.676 | 1777.09 | 1.67169 | 1(Win) | true |
| Glaze | 1685.69 | 0.247702 | 290.708ms | 4857 | 2560 | 118599 | 2747.83 | 0.392472 | 2(Loss) | true |
| Jsonifier (two-stage) | 1512.65 | 0.282978 | 368.244ms | 4857 | 4890 | 367176 | 3062.17 | 1.67902 | 3(Loss) | true |
| simdjson (ondemand) | 679.783 | 0.267012 | 716.727ms | 4857 | 30 | 9930.69 | 6813.93 | 0.37071 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9842.22 | 0.381047 | 53.1467ms | 4857 | 160 | 514.55 | 470.625 | 0.570433 | 1(Win) | true |
| Glaze | 2868.04 | 0.244128 | 182.214ms | 4857 | 80 | 1243.63 | 1615.04 | 0.164586 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11079.6 | 0.329995 | 47.6556ms | 4857 | 30 | 57.0989 | 418.067 | 0.682347 | 1(Win) | true |
| Glaze | 3468.49 | 1.0278 | 145.825ms | 4857 | 160 | 30143.2 | 1335.45 | 1.43076 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2027.39 | 0.10113 | 354.154ms | 6701 | 40 | 406.471 | 3152.12 | 0.327013 | 1(Win) | true |
| Jsonifier (two-stage) | 1547.23 | 0.171628 | 423.612ms | 6701 | 2560 | 128644 | 4130.34 | 0.0106574 | 2(Loss) | true |
| Glaze | 1264.03 | 1.55709 | 452.396ms | 6701 | 80 | 495772 | 5055.7 | 1.01177 | 3(Loss) | true |
| simdjson (ondemand) | 840.174 | 0.150598 | 833.036ms | 6701 | 40 | 5248.55 | 7606.25 | 2.22282 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2235.77 | 0.182722 | 317.152ms | 6701 | 4890 | 133387 | 2858.33 | 0.299184 | 1(Win) | true |
| Jsonifier (two-stage) | 2066.12 | 0.230004 | 374.51ms | 6701 | 30 | 1518.31 | 3093.03 | 0.090608 | 2(Loss) | true |
| Glaze | 2034.13 | 0.295057 | 351.83ms | 6701 | 30 | 2577.82 | 3141.67 | 0.265606 | 3(Loss) | true |
| simdjson (ondemand) | 943.846 | 0.182924 | 817.872ms | 6701 | 40 | 6135.87 | 6770.77 | 0.0412141 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8492.92 | 0.644675 | 83.7043ms | 7376 | 1280 | 36493.8 | 828.255 | 0.712094 | 1(Win) | true |
| Glaze | 2833.12 | 0.14278 | 281.227ms | 7376 | 2560 | 32172.6 | 2482.88 | 0.0257139 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9520.77 | 0.588689 | 75.8646ms | 7376 | 160 | 3026.84 | 738.837 | 1.42097 | 1(Win) | true |
| Glaze | 3309.5 | 0.179154 | 218.615ms | 7376 | 80 | 1160 | 2125.49 | 0.315627 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1288.04 | 0.851986 | 119.353ms | 1691 | 40 | 4551.46 | 1252.03 | 0.0592023 | 1(Win) | true |
| Jsonifier (two-stage) | 1146.38 | 0.574259 | 170.664ms | 1691 | 1280 | 83532.1 | 1406.74 | 0.0576242 | 2(Loss) | true |
| Glaze | 1028.58 | 0.282756 | 158.587ms | 1691 | 640 | 12578.1 | 1567.85 | 0.0680135 | 3(Loss) | true |
| simdjson (ondemand) | 804.216 | 0.828747 | 194.074ms | 1691 | 640 | 176753 | 2005.26 | 0.0619068 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1880.61 | 0.672706 | 106.356ms | 1691 | 1280 | 42594.1 | 857.52 | 0.0316237 | 1(Win) | true |
| Glaze | 1374.63 | 0.172956 | 134.723ms | 1691 | 4890 | 20132.4 | 1173.16 | 1.75363 | 2(Loss) | true |
| Jsonifier (two-stage) | 1327.8 | 0.460384 | 158.637ms | 1691 | 320 | 10004.9 | 1214.53 | 3.11343 | 3(Loss) | true |
| simdjson (ondemand) | 981.853 | 0.321584 | 173.511ms | 1691 | 2560 | 71420.6 | 1642.47 | 1.55953 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9204.43 | 0.816728 | 27.2294ms | 1996 | 160 | 456.459 | 206.806 | 0.256225 | 1(Win) | true |
| Glaze | 3528.05 | 0.119273 | 57.2167ms | 1996 | 640 | 265.04 | 539.542 | 0.0587537 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12337 | 0.491767 | 18.4873ms | 1996 | 640 | 368.471 | 154.295 | 0.16883 | 1(Win) | true |
| Glaze | 4860.29 | 0.252962 | 41.8702ms | 1996 | 4890 | 4799.73 | 391.651 | 0.0994688 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1725.49 | 0.200491 | 125.744ms | 2158 | 80 | 457.468 | 1192.72 | 0.002096 | 1(Win) | true |
| Glaze | 1543.78 | 0.169628 | 164.719ms | 2158 | 160 | 818.171 | 1333.11 | 0.303312 | 2(Loss) | true |
| Jsonifier (two-stage) | 1460.96 | 0.838177 | 146.525ms | 2158 | 320 | 44611.7 | 1408.68 | 0.543857 | 3(Loss) | true |
| simdjson (ondemand) | 970.357 | 1.23952 | 186.296ms | 2158 | 40 | 27644.6 | 2120.9 | 0.135346 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2112.62 | 0.258298 | 123.197ms | 2158 | 640 | 4052.1 | 974.159 | 1.22154 | 1(Win) | true |
| Glaze | 2005.09 | 0.454286 | 125.347ms | 2158 | 30 | 652.248 | 1026.4 | 0.40753 | 2(Loss) | true |
| Jsonifier | 1789.87 | 0.333536 | 135.114ms | 2158 | 2560 | 37651.8 | 1149.82 | 0.702633 | 3(Loss) | true |
| simdjson (ondemand) | 1316.67 | 0.425252 | 167.483ms | 2158 | 1280 | 56552.7 | 1563.06 | 4.80341 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11106.5 | 0.444882 | 31.4414ms | 2866 | 160 | 191.784 | 246.094 | 0.104236 | 1(Win) | true |
| Glaze | 2954.84 | 0.453539 | 102.405ms | 2866 | 30 | 528 | 925 | 1.18929 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12036.2 | 0.240271 | 26.0716ms | 2866 | 4890 | 1455.75 | 227.084 | 2.2321 | 1(Win) | true |
| Glaze | 4049.31 | 0.190377 | 77.2052ms | 2866 | 640 | 1056.82 | 674.986 | 0.0947676 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2101.29 | 0.119939 | 204.989ms | 4390 | 4890 | 27924.8 | 1992.41 | 0.153817 | 1(Win) | true |
| Jsonifier (two-stage) | 1214.96 | 0.131569 | 352.847ms | 4390 | 30 | 616.645 | 3445.9 | 0.0406445 | 2(Loss) | true |
| Glaze | 984.94 | 0.221929 | 432.074ms | 4390 | 2560 | 227813 | 4250.64 | 0.517355 | 3(Loss) | true |
| simdjson (ondemand) | 785.602 | 0.125561 | 596.664ms | 4390 | 80 | 3582.01 | 5329.2 | 0.275187 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2365.95 | 0.0998897 | 194.449ms | 4390 | 160 | 499.898 | 1769.54 | 0.0127136 | 1(Win) | true |
| Jsonifier (two-stage) | 1434.88 | 0.044303 | 346.641ms | 4390 | 80 | 133.677 | 2917.76 | 0.0372856 | 2(Loss) | true |
| simdjson (ondemand) | 897.674 | 0.175977 | 488.109ms | 4390 | 30 | 2020.81 | 4663.87 | 0.058641 | 3(Loss) | true |
| Glaze | 819.136 | 2.05428 | 465.214ms | 4390 | 30 | 330719 | 5111.03 | 1.47342 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8271.98 | 0.239294 | 57.3987ms | 4390 | 320 | 469.38 | 506.122 | 0.0735294 | 1(Win) | true |
| Glaze | 2294.03 | 0.0426167 | 187.056ms | 4390 | 640 | 387.142 | 1825.01 | 0.0138717 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8699.21 | 0.285465 | 52.8779ms | 4390 | 320 | 603.983 | 481.266 | 0.712156 | 1(Win) | true |
| Glaze | 2491.3 | 0.247444 | 175.668ms | 4390 | 30 | 518.741 | 1680.5 | 0.0832392 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2307.98 | 2.5363 | 373.758ms | 9378 | 30 | 289788 | 3875.07 | 4.5742 | 1(Win) | true |
| Jsonifier (two-stage) | 2140.98 | 0.351531 | 485.344ms | 9378 | 160 | 34501.8 | 4177.32 | 0.675419 | 2(Loss) | true |
| Glaze | 1582.34 | 0.221088 | 553.627ms | 9378 | 2560 | 399751 | 5652.1 | 0.729824 | 3(Loss) | true |
| simdjson (ondemand) | 1559.71 | 0.0693259 | 617.298ms | 9378 | 160 | 2528.39 | 5734.11 | 0.0226765 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2869.81 | 0.0557174 | 347.784ms | 9378 | 160 | 482.409 | 3116.43 | 0.0244612 | 1(Win) | true |
| Jsonifier (two-stage) | 2373.81 | 0.104811 | 459.468ms | 9378 | 2560 | 39919.4 | 3767.6 | 1.74584 | 2(Loss) | true |
| Glaze | 1825.36 | 0.158309 | 532.345ms | 9378 | 320 | 19252.3 | 4899.61 | 0.0714853 | 3(Loss) | true |
| simdjson (ondemand) | 1631.38 | 0.437353 | 566.356ms | 9378 | 1280 | 735840 | 5482.2 | 0.358101 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12458.2 | 0.45647 | 93.1282ms | 11521 | 30 | 486.202 | 881.933 | 0.946204 | 1(Win) | true |
| Glaze | 3331.39 | 0.0890398 | 337.611ms | 11521 | 1280 | 11038.5 | 3298.11 | 0.312152 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13259.8 | 0.389099 | 88.854ms | 11521 | 160 | 1663.22 | 828.619 | 0.0716041 | 1(Win) | true |
| Glaze | 3977.44 | 0.260258 | 287.412ms | 11521 | 40 | 2067.48 | 2762.4 | 0.807707 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2617.89 | 0.216766 | 176.454ms | 4669 | 2560 | 34799.2 | 1700.88 | 0.106426 | 1(Win) | true |
| Jsonifier (two-stage) | 1699.9 | 0.166424 | 278.313ms | 4669 | 30 | 570.11 | 2619.4 | 0.00381752 | 2(Loss) | true |
| Glaze | 1274.46 | 0.284737 | 374.695ms | 4669 | 40 | 3958.63 | 3493.8 | 0.29489 | 3(Loss) | true |
| simdjson (ondemand) | 563.402 | 0.269909 | 797.118ms | 4669 | 320 | 145611 | 7903.25 | 0.0189364 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2987.18 | 0.168391 | 165.097ms | 4669 | 4890 | 30808.7 | 1490.6 | 0.211851 | 1(Win) | true |
| Jsonifier (two-stage) | 1839.99 | 0.123959 | 262.579ms | 4669 | 1280 | 11518.1 | 2419.96 | 0.135794 | 2(Loss) | true |
| Glaze | 1468.47 | 0.66888 | 319.729ms | 4669 | 4890 | 2.01151e+06 | 3032.21 | 0.585475 | 3(Loss) | true |
| simdjson (ondemand) | 622.384 | 0.0837872 | 750.2ms | 4669 | 320 | 11498.4 | 7154.27 | 0.601977 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8019.75 | 0.58548 | 57.9974ms | 4669 | 2560 | 27051.4 | 555.217 | 0.261459 | 1(Win) | true |
| Glaze | 1959.62 | 0.301941 | 241.837ms | 4669 | 30 | 1412.12 | 2272.23 | 0.0601103 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9257.71 | 0.650278 | 56.443ms | 4669 | 2560 | 25042.6 | 480.973 | 0.0177019 | 1(Win) | true |
| Glaze | 1776.25 | 1.45188 | 244.91ms | 4669 | 80 | 105971 | 2506.8 | 0.267553 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2676.72 | 0.395345 | 333.509ms | 7932 | 40 | 4993.13 | 2826.05 | 0.0135624 | 1(Win) | true |
| Jsonifier (two-stage) | 2156.3 | 0.435795 | 358.565ms | 7932 | 1280 | 299172 | 3508.11 | 1.11297 | 2(Loss) | true |
| Glaze | 1572.2 | 0.709704 | 573.241ms | 7932 | 160 | 186563 | 4811.44 | 1.27296 | 3(Loss) | true |
| simdjson (ondemand) | 820.597 | 0.479409 | 933.424ms | 7932 | 4890 | 9.55054e+06 | 9218.34 | 0.960317 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2872.18 | 0.291238 | 305.57ms | 7932 | 320 | 18827.2 | 2633.72 | 0.873012 | 1(Win) | true |
| Jsonifier (two-stage) | 2278.2 | 1.06269 | 352.023ms | 7932 | 2560 | 3.18741e+06 | 3320.41 | 0.899491 | 2(Loss) | true |
| Glaze | 1557.46 | 2.48845 | 478.81ms | 7932 | 30 | 438238 | 4856.97 | 1.13045 | 3(Loss) | true |
| simdjson (ondemand) | 977.523 | 0.450659 | 834.485ms | 7932 | 2560 | 3.11349e+06 | 7738.48 | 0.47306 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10293.9 | 0.762078 | 72.024ms | 9249 | 30 | 1279.22 | 856.867 | 1.13077 | 1(Win) | true |
| Glaze | 2957.99 | 0.325804 | 318.126ms | 9249 | 30 | 2831.58 | 2981.93 | 0.139535 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15480.7 | 0.612136 | 65.3245ms | 9249 | 40 | 486.589 | 569.775 | 3.25306 | 1(Win) | true |
| Glaze | 3438.58 | 0.362713 | 277.474ms | 9249 | 30 | 2597.04 | 2565.17 | 1.70771 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 623.41 | 0.146106 | 773.051ms | 4604 | 30 | 3176.75 | 7043.07 | 0.000473276 | 1(Win) | true |
| Jsonifier (two-stage) | 459.877 | 1.33226 | 927.268ms | 4604 | 640 | 1.0355e+07 | 9547.59 | 1.01727 | 2(Loss) | true |
| Glaze | 343.998 | 0.591504 | 1269.23ms | 4604 | 160 | 911999 | 12763.8 | 0.356086 | 3(Loss) | true |
| simdjson (ondemand) | 288.795 | 0.269189 | 1547.73ms | 4604 | 4890 | 8.19057e+06 | 15203.6 | 2.38247 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 727.401 | 0.969847 | 776.24ms | 4604 | 160 | 548339 | 6036.17 | 1.57585 | 1(Win) | true |
| Jsonifier (two-stage) | 655.744 | 0.247341 | 949.247ms | 4604 | 80 | 21942.4 | 6695.77 | 0.974186 | 2(Loss) | true |
| Glaze | 425.265 | 0.184942 | 1228.96ms | 4604 | 4890 | 1.78291e+06 | 10324.7 | 0.114731 | 3(Loss) | true |
| simdjson (ondemand) | 300.533 | 0.294684 | 1521.17ms | 4604 | 2560 | 4.74503e+06 | 14609.8 | 0.322792 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1850.26 | 0.423415 | 271.519ms | 4918 | 1280 | 147454 | 2534.88 | 1.08405 | 1(Win) | true |
| Glaze | 821.853 | 0.367893 | 508.519ms | 4604 | 1280 | 494465 | 5342.46 | 0.810749 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2133.53 | 0.0797556 | 248.864ms | 4918 | 320 | 983.679 | 2198.32 | 0.242247 | 1(Win) | true |
| Glaze | 1123.78 | 0.159858 | 434.117ms | 4604 | 30 | 1170.3 | 3907.1 | 0.00341271 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1827.02 | 0.0883455 | 1000.93ms | 18245 | 30 | 2123.7 | 9523.6 | 0.0732052 | 1(Win) | true |
| Jsonifier | 1709.3 | 0.139322 | 1071.76ms | 18245 | 4890 | 983554 | 10179.5 | 0.101406 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1141.5 | 0.169774 | 1510.68ms | 18245 | 2560 | 1.71443e+06 | 15242.9 | 0.0186732 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 1137.87 | 0.157262 | 1651.82ms | 18245 | 30 | 17348.8 | 15291.5 | 3.40502 | 3(Tie) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2106.19 | 0.157474 | 993.021ms | 18245 | 4890 | 827600 | 8261.25 | 1.5617 | 1(Win) | true |
| Jsonifier (two-stage) | 2092.43 | 0.131799 | 1023.14ms | 18245 | 4890 | 587381 | 8315.59 | 0.872775 | 2(Loss) | true |
| simdjson (ondemand) | 1365.16 | 0.0618686 | 1414.2ms | 18245 | 4890 | 304068 | 12745.6 | 0.0743216 | 3(Loss) | true |
| Glaze | 1277.64 | 0.918213 | 1629ms | 18245 | 40 | 625487 | 13618.7 | 0.609477 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5730.86 | 0.117865 | 447.103ms | 24893 | 160 | 3814.19 | 4142.45 | 0.257636 | 1(Win) | true |
| Glaze | 3240.68 | 0.0722111 | 726.269ms | 24579 | 4890 | 133405 | 7233.17 | 0.00171709 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5349.8 | 0.286536 | 435.51ms | 24893 | 2560 | 413884 | 4437.51 | 0.0627597 | 1(Win) | true |
| Glaze | 3886.56 | 0.0746191 | 618.886ms | 24579 | 4890 | 99039 | 6031.13 | 0.157161 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 694.353 | 0.0527076 | 646.02ms | 4604 | 80 | 888.682 | 6323.46 | 0.0100825 | 1(Win) | true |
| Jsonifier (two-stage) | 573.79 | 0.0745111 | 774.037ms | 4604 | 40 | 1300.37 | 7652.12 | 0.0090397 | 2(Loss) | true |
| Glaze | 395.243 | 0.0682231 | 1130.41ms | 4604 | 80 | 4595.1 | 11108.9 | 0.0141798 | 3(Loss) | true |
| simdjson (ondemand) | 330.833 | 0.158636 | 1332.37ms | 4604 | 1280 | 567367 | 13271.7 | 0.16502 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 905.095 | 0.0703143 | 628.038ms | 4604 | 4890 | 56895.5 | 4851.11 | 0.0307737 | 1(Win) | true |
| Jsonifier (two-stage) | 722.255 | 0.0638963 | 758.939ms | 4604 | 40 | 603.533 | 6079.18 | 0.0204291 | 2(Loss) | true |
| Glaze | 453.02 | 0.0908247 | 1116.75ms | 4604 | 2560 | 198374 | 9692.11 | 0.0291963 | 3(Loss) | true |
| simdjson (ondemand) | 377.376 | 0.0980681 | 1318.47ms | 4604 | 30 | 3905.71 | 11634.9 | 0.095026 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2163.11 | 0.0799014 | 223.664ms | 4918 | 80 | 240.114 | 2168.25 | 0.0242189 | 1(Win) | true |
| Glaze | 1056.69 | 0.0835647 | 458.593ms | 4604 | 80 | 964.526 | 4155.18 | 0.0757517 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2194.19 | 0.112147 | 219.96ms | 4918 | 80 | 459.72 | 2137.54 | 0.00175439 | 1(Win) | true |
| Glaze | 1158.79 | 0.186923 | 406.517ms | 4604 | 80 | 4013.1 | 3789.06 | 0.261631 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1967.02 | 0.0645664 | 895.649ms | 18245 | 30 | 978.599 | 8845.77 | 0.00150729 | 1(Win) | true |
| Jsonifier | 1459.38 | 0.499299 | 945.518ms | 18245 | 320 | 1.13403e+06 | 11922.8 | 0.298507 | 2(Loss) | true |
| Glaze | 1228.1 | 0.0962694 | 1444.42ms | 18245 | 30 | 5581.07 | 14168 | 0.03951 | 3(Loss) | true |
| simdjson (ondemand) | 1221.22 | 0.062698 | 1528.56ms | 18245 | 40 | 3192.03 | 14247.9 | 0.00386008 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2393.12 | 0.047667 | 886.592ms | 18245 | 80 | 960.918 | 7270.76 | 0.0844847 | 1(Win) | true |
| Jsonifier | 2352.6 | 0.119135 | 884.835ms | 18245 | 2560 | 198752 | 7395.97 | 0.0458335 | 2(Loss) | true |
| Glaze | 1382.15 | 0.0535362 | 1507.23ms | 18245 | 80 | 3633.83 | 12589 | 0.0529514 | 3(Loss) | true |
| simdjson (ondemand) | 1366.39 | 0.145594 | 1565.52ms | 18245 | 1280 | 439981 | 12734.1 | 0.0687147 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4240.7 | 0.279877 | 528.697ms | 24893 | 1280 | 314212 | 5598.08 | 0.482109 | 1(Win) | true |
| Glaze | 3328.85 | 0.0763733 | 722.653ms | 24579 | 40 | 1156.87 | 7041.57 | 0.0380031 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5268.83 | 1.17801 | 461.396ms | 24893 | 80 | 225380 | 4505.71 | 0.126623 | 1(Win) | true |
| Glaze | 3912.31 | 0.114038 | 710.926ms | 24579 | 1280 | 59754.4 | 5991.44 | 0.0647119 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1314.63 | 0.354595 | 401.659ms | 5094 | 80 | 13736.1 | 3695.34 | 3.89114 | 1(Win) | true |
| Jsonifier (two-stage) | 1030.44 | 0.265561 | 530.148ms | 5094 | 40 | 6269.95 | 4714.52 | 0.192825 | 2(Loss) | true |
| Glaze | 921.654 | 0.213448 | 589.742ms | 5094 | 40 | 5063.2 | 5270.98 | 0.101554 | 3(Loss) | true |
| simdjson (ondemand) | 522.706 | 0.956326 | 960.786ms | 5094 | 160 | 1.26396e+06 | 9293.98 | 2.47788 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1533.68 | 1.39422 | 389.223ms | 5094 | 2560 | 4.99291e+06 | 3167.56 | 2.59227 | 1(Win) | true |
| Jsonifier (two-stage) | 1286.57 | 1.38013 | 508.757ms | 5094 | 40 | 108631 | 3775.95 | 1.17856 | 2(Loss) | true |
| Glaze | 1127.32 | 0.129672 | 593.83ms | 5094 | 80 | 2498.11 | 4309.36 | 0.118496 | 3(Loss) | true |
| simdjson (ondemand) | 631.423 | 0.273375 | 801.476ms | 5094 | 2560 | 1.13249e+06 | 7693.76 | 1.08034 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9726.49 | 0.181364 | 61.0787ms | 5094 | 80 | 65.6441 | 499.462 | 0.9423 | 1(Win) | true |
| Glaze | 2178.68 | 0.457006 | 217.736ms | 5094 | 1280 | 132918 | 2229.8 | 0.735302 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9455.59 | 0.489315 | 52.3141ms | 5094 | 640 | 4044.8 | 513.772 | 0.0498514 | 1(Win) | true |
| Glaze | 2907.77 | 0.881503 | 173.529ms | 5094 | 30 | 6506.77 | 1670.7 | 0.175267 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1307.22 | 0.859137 | 508.597ms | 8051 | 320 | 814851 | 5873.56 | 0.272937 | 1(Win) | true |
| Glaze | 1279.92 | 0.201391 | 743.075ms | 8051 | 40 | 5838.18 | 5998.85 | 0.111286 | 2(Loss) | true |
| Jsonifier (two-stage) | 1238.38 | 0.364609 | 608.278ms | 8051 | 1280 | 654121 | 6200.07 | 1.53515 | 3(Loss) | true |
| simdjson (ondemand) | 817.537 | 0.497464 | 909.803ms | 8051 | 640 | 1.39697e+06 | 9391.67 | 0.781429 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1888.01 | 0.124647 | 627.164ms | 8051 | 2560 | 65779.5 | 4066.72 | 0.332877 | 1(Win) | true |
| Jsonifier | 1822.11 | 0.422871 | 517.161ms | 8051 | 640 | 203210 | 4213.81 | 1.81592 | 2(Loss) | true |
| Glaze | 1310.82 | 0.368565 | 710.506ms | 8051 | 1280 | 596557 | 5857.42 | 0.755239 | 3(Loss) | true |
| simdjson (ondemand) | 970.233 | 0.399472 | 913.16ms | 8051 | 1280 | 1.27917e+06 | 7913.6 | 1.73241 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9161.61 | 0.243859 | 101.395ms | 9255 | 4890 | 26989.6 | 963.396 | 0.787888 | 1(Win) | true |
| Glaze | 2462.69 | 0.321099 | 354.706ms | 9255 | 2560 | 339041 | 3583.99 | 1.12052 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10710.1 | 0.704249 | 79.8037ms | 9255 | 1280 | 43114.7 | 824.103 | 1.15242 | 1(Win) | true |
| Glaze | 3284.31 | 0.430928 | 288.312ms | 9255 | 1280 | 171667 | 2687.4 | 2.59023 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 3299.83 | 0.22932 | 95.0032ms | 2889 | 4890 | 17927 | 834.943 | 4.00785 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 3152.21 | 2.28948 | 89.9455ms | 2889 | 640 | 256282 | 874.042 | 0.624443 | 1(Tie) | true |
| Jsonifier | 3081.16 | 0.311488 | 94.8241ms | 2889 | 2560 | 19860.6 | 894.198 | 0.433384 | 3(Loss) | true |
| Glaze | 2068.85 | 0.118221 | 154.042ms | 2889 | 320 | 793.196 | 1331.74 | 0.155819 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 3428.93 | 0.703204 | 91.1158ms | 2889 | 640 | 20432.5 | 803.506 | 0.581689 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3408.7 | 0.664784 | 107.548ms | 2889 | 80 | 2309.77 | 808.275 | 1.6954 | 1(Tie) | true |
| Jsonifier (two-stage) | 3179.07 | 0.975083 | 84.7359ms | 2889 | 160 | 11426.1 | 866.656 | 0.595601 | 3(Loss) | true |
| Glaze | 2075.57 | 0.385108 | 142.625ms | 2889 | 1280 | 33450 | 1327.42 | 1.19995 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4010.59 | 0.852986 | 103.465ms | 3808 | 30 | 1789.71 | 905.5 | 0.454848 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3973.73 | 0.433652 | 109.023ms | 3808 | 30 | 471.197 | 913.9 | 0.152955 | 1(Tie) | true |
| Jsonifier | 3806.81 | 0.24031 | 102.75ms | 3808 | 2560 | 13454.1 | 953.972 | 1.12788 | 3(Loss) | true |
| Glaze | 2468.96 | 0.240561 | 162.129ms | 3808 | 30 | 375.61 | 1470.9 | 0.650666 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4533.96 | 0.435398 | 96.6724ms | 3808 | 40 | 486.487 | 800.975 | 1.2483 | 1(Win) | true |
| simdjson (ondemand) | 4185.34 | 0.188875 | 94.8921ms | 3808 | 160 | 429.736 | 867.694 | 0.359573 | 2(Loss) | true |
| Jsonifier (two-stage) | 4038.84 | 0.248349 | 96.6367ms | 3808 | 4890 | 24384.5 | 899.166 | 0.0816568 | 3(Loss) | true |
| Glaze | 2483.37 | 0.38027 | 159.385ms | 3808 | 640 | 19791.3 | 1462.36 | 0.655505 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Glaze | 1888.58 | 0.114479 | 174.812ms | 2889 | 320 | 892.537 | 1458.86 | 0.161775 | 1(Win) | true |
| Jsonifier (two-stage) | 1735.25 | 0.321909 | 177.215ms | 2889 | 160 | 4179.83 | 1587.76 | 1.44472 | 2(Loss) | true |
| Jsonifier | 1657.31 | 0.733208 | 134.541ms | 2889 | 30 | 4457.22 | 1662.43 | 1.08641 | 3(Loss) | true |
| simdjson (ondemand) | 797.143 | 0.435417 | 382.759ms | 2889 | 40 | 9059.29 | 3456.3 | 1.40932 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2833.85 | 0.426108 | 123.051ms | 2889 | 30 | 514.875 | 972.233 | 0.725213 | 1(Win) | true |
| Jsonifier (two-stage) | 2328.28 | 0.109418 | 150.325ms | 2889 | 320 | 536.479 | 1183.35 | 0.0522607 | 2(Loss) | true |
| Glaze | 2219.36 | 0.130415 | 142.199ms | 2889 | 320 | 838.778 | 1241.42 | 0.0229124 | 3(Loss) | true |
| simdjson (ondemand) | 900.469 | 0.192229 | 355.705ms | 2889 | 30 | 1037.8 | 3059.7 | 0.135994 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9456.75 | 0.485365 | 33.7988ms | 2963 | 320 | 673.078 | 298.806 | 0.487064 | 1(Win) | true |
| Glaze | 3451.07 | 0.384938 | 91.8586ms | 2963 | 80 | 794.744 | 818.8 | 0.125027 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11177.2 | 0.265646 | 31.4333ms | 2963 | 2560 | 1154.63 | 252.812 | 1.67165 | 1(Win) | true |
| Glaze | 4590.26 | 0.491274 | 70.9961ms | 2963 | 160 | 1463.37 | 615.594 | 0.161691 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2357.67 | 0.241318 | 200.842ms | 3808 | 30 | 414.506 | 1540.33 | 0.979279 | 1(Win) | true |
| Glaze | 2086.08 | 0.158421 | 213.625ms | 3808 | 160 | 1216.96 | 1740.87 | 0.582466 | 2(Loss) | true |
| Jsonifier (two-stage) | 1777.22 | 0.646406 | 204.158ms | 3808 | 640 | 111662 | 2043.42 | 2.06608 | 3(Loss) | true |
| simdjson (ondemand) | 843.742 | 1.56708 | 426.543ms | 3808 | 40 | 181976 | 4304.15 | 2.88397 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2596.34 | 0.681062 | 191.659ms | 3808 | 30 | 2722.48 | 1398.73 | 0.404374 | 1(Win) | true |
| Glaze | 2360.78 | 0.151801 | 191.182ms | 3808 | 160 | 872.475 | 1538.3 | 0.0886503 | 2(Loss) | true |
| Jsonifier (two-stage) | 2254.71 | 0.593003 | 191.714ms | 3808 | 1280 | 116772 | 1610.67 | 0.283383 | 3(Loss) | true |
| simdjson (ondemand) | 1046.75 | 0.16286 | 401.659ms | 3808 | 30 | 957.766 | 3469.4 | 0.441013 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9402.63 | 1.76026 | 48.178ms | 4300 | 30 | 1768.12 | 436.133 | 1.26028 | 1(Win) | true |
| Glaze | 2756.02 | 0.329191 | 157.532ms | 4300 | 2560 | 61419.9 | 1487.94 | 0.349484 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11909 | 0.332429 | 41.8927ms | 4300 | 4890 | 6407.54 | 344.344 | 0.585642 | 1(Win) | true |
| Glaze | 3479.96 | 0.772275 | 116.074ms | 4300 | 320 | 26502.2 | 1178.4 | 2.35105 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1851.94 | 0.761095 | 5690.17ms | 466906 | 160 | 5.35798e+08 | 240437 | 2.5487 | 1(Win) | true |
| Glaze | 1440.52 | 0.970583 | 7630.97ms | 466906 | 80 | 7.2007e+08 | 309108 | 0.537526 | 2(Loss) | true |
| simdjson (ondemand) | 1199.95 | 0.469843 | 5003.39ms | 466906 | 30 | 9.11928e+07 | 371079 | 0.443971 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2133.61 | 0.509544 | 5586.45ms | 466906 | 160 | 1.8093e+08 | 208696 | 0.0521635 | 1(Win) | true |
| Glaze | 1537.06 | 0.374115 | 7533.67ms | 466906 | 640 | 7.51736e+08 | 289693 | 0.745414 | 2(Loss) | true |
| simdjson (ondemand) | 1132.81 | 2.91079 | 5167.2ms | 466906 | 30 | 3.92725e+09 | 393072 | 1.04444 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3398.26 | 0.132298 | 5647.83ms | 699405 | 160 | 1.07888e+07 | 196278 | 0.425502 | 1(Win) | true |
| Glaze | 2308.49 | 0.319568 | 8301.87ms | 699405 | 160 | 1.3641e+08 | 288935 | 0.307819 | 2(Loss) | true |
| simdjson (ondemand) | 1413.3 | 0.435305 | 6872.86ms | 767297 | 640 | 3.25107e+09 | 517761 | 0.788168 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2983.73 | 0.267322 | 5726.65ms | 699405 | 1280 | 4.57109e+08 | 223547 | 0.412743 | 1(Win) | true |
| Glaze | 2233.17 | 0.285439 | 7694.11ms | 699405 | 1280 | 9.30359e+08 | 298680 | 1.35733 | 2(Loss) | true |
| simdjson (ondemand) | 1444.33 | 0.239764 | 6551.82ms | 767297 | 640 | 9.44366e+08 | 506636 | 2.20025 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2268.91 | 0.437947 | 6517.63ms | 631514 | 320 | 4.32438e+08 | 265439 | 0.264291 | 1(Win) | true |
| Glaze | 1997.75 | 0.134615 | 7762.33ms | 631514 | 80 | 1.31753e+07 | 301469 | 0.158013 | 2(Loss) | true |
