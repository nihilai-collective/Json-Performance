# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

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
| **simdjson (reflection)** | `arm64` |
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
* **simdjson (reflection):** C++26 static reflection API (P2996). Minified serialization only.
* **Jsonifier:** Evaluates both fused scalar structural iteration and two-stage indexing. Partial tests default strictly to two-stage parsing.
* **Summary Rows:** `*(combined)` metrics display best-of-variant ranks and are not additive with isolated test results.

---
*Environment generated via BenchmarkSuite commit: [ed43ce8](https://github.com/nihilai-collective/benchmarksuite/commit/ed43ce8)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1596.41 | 1.35137 | 78.3601ms | 905 | 4890 | 261015 | 540.636 | 4.26131 | 1(Tie) | true |
| Glaze STATISTICAL TIE | 1455.93 | 4.66487 | 67.362ms | 905 | 320 | 244706 | 592.8 | 1.2 | 1(Tie) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 356.68 | 0.799932 | 257.525ms | 905 | 4890 | 1.83213e+06 | 2419.75 | 6.93986 | -(Loss) | false |
| simdjson (ondemand) | 185.644 | 0.245511 | 472.376ms | 905 | 2560 | 333519 | 4649.1 | 0.379275 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1764.26 | 2.07899 | 49.399ms | 905 | 2560 | 264800 | 489.2 | 3.28193 | 1(Win) | true |
| Glaze | 1521.91 | 1.97585 | 57.1699ms | 905 | 2560 | 321416 | 567.1 | 1.55802 | 2(Loss) | true |
| Jsonifier (two-stage) | 349.541 | 0.322887 | 253.244ms | 905 | 4890 | 310822 | 2469.17 | 1.93535 | 3(Loss) | true |
| simdjson (ondemand) | 188.626 | 0.262867 | 466.807ms | 905 | 2560 | 370346 | 4575.6 | 0.672948 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1958.67 | 1.62027 | 46.753ms | 905 | 4890 | 249263 | 440.645 | 0.0555361 | 1(Win) | true |
| simdjson (reflection) | 205.759 | 0.316429 | 422.843ms | 905 | 2560 | 450998 | 4194.6 | 0.204606 | 2(Loss) | true |
| Glaze | 129.029 | 0.214319 | 664.76ms | 905 | 2560 | 526118 | 6689 | 0.185036 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3563.79 | 2.60811 | 33.3481ms | 905 | 4890 | 195090 | 242.179 | 1.11864 | 1(Win) | true |
| simdjson (reflection) | 2691.17 | 2.08939 | 42.602ms | 905 | 4890 | 219565 | 320.707 | 0.946411 | 2(Loss) | true |
| Glaze | 879.971 | 0.883229 | 113.744ms | 905 | 320 | 24013.6 | 980.8 | 0 | 3(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 951.39 | 0.330423 | 185.239ms | 1811 | 4890 | 175942 | 1815.35 | 0.0522969 | 1(Win) | true |
| Glaze | 890.165 | 0.263214 | 198.07ms | 1811 | 4890 | 127534 | 1940.21 | 0.0107098 | 2(Loss) | true |
| Jsonifier (two-stage) | 527.99 | 0.233662 | 331.018ms | 1811 | 4890 | 285674 | 3271.09 | 0.287999 | 3(Loss) | true |
| simdjson (ondemand) | 162.195 | 0.190215 | 1072.01ms | 1811 | 2560 | 1.05024e+06 | 10648.3 | 0.149097 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1183.6 | 1.91416 | 151.844ms | 1811 | 320 | 249653 | 1459.2 | 0.653595 | 1(Win) | true |
| Glaze | 1033.18 | 0.434898 | 170.041ms | 1811 | 4890 | 258446 | 1671.64 | 0.188394 | 2(Loss) | true |
| Jsonifier (two-stage) | 584.429 | 0.453196 | 301.735ms | 1811 | 320 | 57397.9 | 2955.2 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 164.876 | 0.380885 | 1046.64ms | 1811 | 160 | 254702 | 10475.2 | 0.198959 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 316.439 | 0.165619 | 608.863ms | 1997 | 2560 | 254352 | 6018.5 | 0.180781 | 1(Win) | true |
| Jsonifier | 292.333 | 0.290182 | 596.529ms | 1811 | 640 | 188105 | 5908 | 0.498518 | 2(Loss) | true |
| Glaze | 219.778 | 0.247438 | 788.607ms | 1798 | 640 | 238519 | 7802 | 0.025641 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 920.054 | 0.297925 | 199.017ms | 1811 | 4890 | 152944 | 1877.18 | 0.174837 | 1(Win) | true |
| simdjson (reflection) | 721.725 | 0.900866 | 266.08ms | 1997 | 1280 | 723341 | 2638.8 | 0.527744 | 2(Loss) | true |
| Glaze | 706.775 | 0.448415 | 257.774ms | 1798 | 2560 | 302983 | 2426.1 | 0.0453197 | 3(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2644.76 | 0.995326 | 146.362ms | 3862 | 1280 | 245920 | 1392.6 | 0.447201 | 1(Win) | true |
| Glaze | 1483.44 | 0.43094 | 252.983ms | 3862 | 2560 | 293060 | 2482.8 | 0.289157 | 2(Loss) | true |
| Jsonifier (two-stage) | 964.766 | 0.303468 | 395.309ms | 3862 | 2560 | 343594 | 3817.6 | 0.199475 | 3(Loss) | true |
| simdjson (ondemand) | 465.213 | 0.209891 | 793.26ms | 3862 | 2560 | 706885 | 7917 | 0.0908609 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3346.44 | 0.787048 | 114.983ms | 3862 | 1280 | 96044.3 | 1100.6 | 1.41909 | 1(Win) | true |
| Glaze | 1639.55 | 1.10733 | 230.702ms | 3862 | 320 | 198005 | 2246.4 | 0.142248 | 2(Loss) | true |
| Jsonifier (two-stage) | 1031.97 | 0.235756 | 384.294ms | 3862 | 4890 | 346194 | 3568.98 | 0.310744 | 3(Loss) | true |
| simdjson (ondemand) | 475.563 | 0.192914 | 783.062ms | 3862 | 2560 | 571448 | 7744.7 | 0.417888 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 822.21 | 0.245123 | 453.326ms | 3862 | 2560 | 308652 | 4479.5 | 0.0200956 | 1(Win) | true |
| simdjson (reflection) | 806.493 | 0.370481 | 461.864ms | 3862 | 1280 | 366410 | 4566.8 | 0.244648 | 2(Loss) | true |
| Glaze | 571.133 | 0.148645 | 648.975ms | 3862 | 4890 | 449325 | 6448.74 | 0.282365 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5454.81 | 2.76812 | 79.2131ms | 3862 | 640 | 223571 | 675.2 | 0.588928 | 1(Win) | true |
| simdjson (reflection) | 3632.42 | 0.209906 | 114.416ms | 3862 | 4890 | 22150.9 | 1013.95 | 0.0738715 | 2(Loss) | true |
| Glaze | 2593 | 1.56473 | 159.93ms | 3862 | 640 | 316142 | 1420.4 | 0.367439 | 3(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1379.8 | 0.226063 | 667.002ms | 9578 | 1280 | 286672 | 6620 | 0.361228 | 1(Win) | true |
| Glaze | 1146.65 | 0.115632 | 804.891ms | 9578 | 2560 | 217214 | 7966.1 | 0.0965663 | 2(Loss) | true |
| simdjson (ondemand) | 777.028 | 0.102612 | 1183.56ms | 9578 | 4890 | 711518 | 11755.4 | 0.301707 | 3(Loss) | true |
| Jsonifier (two-stage) | 768.569 | 0.181916 | 1267.89ms | 9578 | 1280 | 598320 | 11884.8 | 0.0302816 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2378.47 | 0.354038 | 624.947ms | 9578 | 1280 | 236626 | 3840.4 | 1.08444 | 1(Win) | true |
| Glaze | 1629.26 | 0.391975 | 768.953ms | 9578 | 640 | 309076 | 5606.4 | 0.270386 | 2(Loss) | true |
| simdjson (ondemand) | 1024.84 | 0.124549 | 1143.12ms | 9578 | 2560 | 315473 | 8912.9 | 0.175839 | 3(Loss) | true |
| Jsonifier (two-stage) | 1011.95 | 0.153101 | 1158.02ms | 9578 | 320 | 61113.2 | 9026.4 | 0.185775 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1490.61 | 0.102617 | 620.917ms | 9578 | 4890 | 193359 | 6127.88 | 0.385661 | 1(Win) | true |
| simdjson (reflection) | 1317.7 | 0.387011 | 701.731ms | 9578 | 320 | 230310 | 6932 | 0.196577 | 2(Loss) | true |
| Glaze | 1158.04 | 0.136772 | 798.043ms | 9578 | 2560 | 297943 | 7887.7 | 0.259225 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 11003.3 | 0.880881 | 92.585ms | 9578 | 4890 | 261485 | 830.142 | 1.1381 | 1(Win) | true |
| Jsonifier | 9148.93 | 1.42843 | 101.118ms | 9578 | 30 | 6101.63 | 998.4 | 0 | 2(Loss) | true |
| Glaze | 5268.41 | 0.391589 | 188.189ms | 9578 | 4890 | 225403 | 1733.78 | 2.10136 | 3(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2599.79 | 0.512798 | 145.766ms | 3873 | 4890 | 259549 | 1420.72 | 0.139069 | 1(Win) | true |
| Glaze | 1629.14 | 0.785431 | 231.078ms | 3873 | 640 | 202944 | 2267.2 | 0.211268 | 2(Loss) | true |
| Jsonifier (two-stage) | 790.724 | 0.240081 | 453.948ms | 3873 | 4890 | 614992 | 4671.14 | 0.212852 | 3(Loss) | true |
| simdjson (ondemand) | 453.267 | 0.36872 | 820.662ms | 3873 | 160 | 144445 | 8148.8 | 0.295392 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3249.65 | 0.460892 | 118.214ms | 3873 | 4890 | 134193 | 1136.61 | 0.715532 | 1(Win) | true |
| Glaze | 1714.74 | 0.281879 | 219.878ms | 3873 | 4890 | 180273 | 2154.01 | 0.383283 | 2(Loss) | true |
| Jsonifier (two-stage) | 934.083 | 0.237015 | 400.398ms | 3873 | 4890 | 429521 | 3954.23 | 0.178139 | 3(Loss) | true |
| simdjson (ondemand) | 464.21 | 0.192317 | 801.181ms | 3873 | 2560 | 599434 | 7956.7 | 0.34443 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 829.364 | 0.183249 | 450.023ms | 3873 | 4890 | 325685 | 4453.51 | 0.148643 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 826.915 | 0.245306 | 451.616ms | 3873 | 2560 | 307348 | 4466.7 | 0.198856 | 1(Tie) | true |
| Glaze | 582.862 | 0.138123 | 638.268ms | 3873 | 4890 | 374631 | 6336.97 | 0.0358108 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5413.84 | 1.01187 | 78.592ms | 3873 | 4890 | 233047 | 682.248 | 0.183238 | 1(Win) | true |
| simdjson (reflection) | 3621.87 | 0.44074 | 114.322ms | 3873 | 1280 | 25858.6 | 1019.8 | 0.255604 | 2(Loss) | true |
| Glaze | 2821.47 | 0.737674 | 149.956ms | 3873 | 2560 | 238734 | 1309.1 | 0.494071 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1262.62 | 0.125004 | 7172.77ms | 94653 | 640 | 5.11158e+06 | 71492.8 | 0.031322 | 1(Win) | true |
| Glaze | 1143.85 | 0.152239 | 7980.04ms | 94653 | 320 | 4.61883e+06 | 78916 | 0.0923352 | 2(Loss) | true |
| Jsonifier (two-stage) | 1030.56 | 0.225736 | 8874.52ms | 94653 | 640 | 2.50209e+07 | 87591.2 | 0.0593315 | 3(Loss) | true |
| simdjson (reflection) | 863.195 | 0.277636 | 5347.34ms | 94653 | 160 | 1.34872e+07 | 104574 | 0.0352026 | 4(Loss) | true |
| simdjson (ondemand) | 773.198 | 0.163728 | 5985.93ms | 94653 | 320 | 1.16918e+07 | 116746 | 0.00205578 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2112.58 | 0.290229 | 6574.11ms | 94653 | 320 | 4.92123e+06 | 42728.8 | 0.080443 | 1(Win) | true |
| Glaze | 1698.33 | 0.105361 | 7144.32ms | 94653 | 2560 | 8.02824e+06 | 53151 | 0.0839823 | 2(Loss) | true |
| Jsonifier (two-stage) | 1519.55 | 0.0773989 | 7814.78ms | 94653 | 2560 | 5.41188e+06 | 59404.5 | 0.255683 | 3(Loss) | true |
| simdjson (reflection) | 1050.57 | 0.141424 | 5443.93ms | 94653 | 320 | 4.72516e+06 | 85923.2 | 0.083866 | 4(Loss) | true |
| simdjson (ondemand) | 983.793 | 0.158248 | 5721.34ms | 94653 | 640 | 1.34932e+07 | 91755.2 | 0.0174407 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12790.2 | 0.270107 | 712.862ms | 94653 | 1280 | 465154 | 7057.6 | 0.0907647 | 1(Win) | true |
| simdjson (reflection) | 9478.76 | 0.586459 | 950.214ms | 94653 | 80 | 249535 | 9523.2 | 0 | 2(Loss) | true |
| Glaze | 5158.89 | 0.470161 | 1732.63ms | 94653 | 40 | 270714 | 17497.6 | 0.0243902 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13313.9 | 0.197532 | 684.511ms | 94653 | 2560 | 459171 | 6780 | 0.200188 | 1(Win) | true |
| simdjson (reflection) | 9630.04 | 0.318254 | 952.6ms | 94653 | 640 | 569563 | 9373.6 | 0.170401 | 2(Loss) | true |
| Glaze | 6535.2 | 0.162524 | 1383.86ms | 94653 | 2560 | 1.2901e+06 | 13812.6 | 0.246759 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1406.1 | 0.052321 | 8780.97ms | 124597 | 4890 | 9.55968e+06 | 84506.6 | 0.131816 | 1(Win) | true |
| Glaze | 1327.45 | 0.0793829 | 8989.08ms | 124597 | 1280 | 6.46312e+06 | 89513.6 | 0.185549 | 2(Loss) | true |
| Jsonifier (two-stage) | 1287.4 | 0.0545283 | 9301.21ms | 124597 | 4890 | 1.23864e+07 | 92298.7 | 0.194943 | 3(Loss) | true |
| simdjson (reflection) | 1108.06 | 0.121729 | 5525.86ms | 124597 | 1280 | 2.18113e+07 | 107237 | 0.375878 | 4(Loss) | true |
| simdjson (ondemand) | 992.876 | 0.108535 | 6149.62ms | 124597 | 320 | 5.39901e+06 | 119678 | 0.00869077 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2155.75 | 0.0585773 | 7480.25ms | 124597 | 4890 | 5.09781e+06 | 55119.9 | 0.0206661 | 1(Win) | true |
| Glaze | 1873.14 | 0.0726649 | 8329.01ms | 124597 | 2560 | 5.43958e+06 | 63436.3 | 0.126112 | 2(Loss) | true |
| Jsonifier (two-stage) | 1862.67 | 0.0777092 | 8260.87ms | 124597 | 2560 | 6.29112e+06 | 63792.8 | 0.0850348 | 3(Loss) | true |
| simdjson (reflection) | 1325.49 | 0.181304 | 5638.63ms | 124597 | 320 | 8.45342e+06 | 89646.4 | 0.107202 | 4(Loss) | true |
| simdjson (ondemand) | 1255.27 | 0.177445 | 5884.72ms | 124597 | 320 | 9.02854e+06 | 94660.8 | 0.165919 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14067.4 | 0.232037 | 934.278ms | 136037 | 640 | 293076 | 9222.4 | 0.0433915 | 1(Win) | true |
| Glaze | 4701.26 | 0.102351 | 2780.39ms | 136076 | 2560 | 2.04343e+06 | 27603.7 | 0.198555 | 2(Loss) | true |
| simdjson (reflection) | 389.426 | 0.155101 | 8897.65ms | 136037 | 320 | 8.54364e+07 | 333144 | 0.186956 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14372 | 0.102598 | 946.365ms | 136037 | 4890 | 419442 | 9026.96 | 0.343014 | 1(Win) | true |
| Glaze | 5426.53 | 0.212373 | 2383.08ms | 136076 | 320 | 825409 | 23914.4 | 0.0368115 | 2(Loss) | true |
| simdjson (reflection) | 387.532 | 0.0808591 | 8587.32ms | 136037 | 1280 | 9.37922e+07 | 334772 | 0.204316 | 3(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 908.054 | 0.139606 | 7393.98ms | 2251027 | 160 | 1.74286e+09 | 2.36412e+06 | 0.0608801 | 1(Win) | true |
| Jsonifier (two-stage) | 775.618 | 0.136076 | 8659.12ms | 2251027 | 160 | 2.2696e+09 | 2.76779e+06 | 0.159689 | 2(Loss) | true |
| Glaze | 649.513 | 0.211608 | 5027.55ms | 2251027 | 30 | 1.46748e+09 | 3.30516e+06 | 0.135877 | 3(Loss) | true |
| simdjson (ondemand) | 588.578 | 0.153229 | 5486.76ms | 2251027 | 40 | 1.24938e+09 | 3.64735e+06 | 0.104807 | 4(Loss) | true |
| simdjson (reflection) | 568.09 | 0.717395 | 5443.83ms | 2251027 | 40 | 2.93971e+10 | 3.77889e+06 | 4.42457 | 5(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1158.28 | 0.356919 | 7397.57ms | 2251027 | 30 | 1.31279e+09 | 1.85339e+06 | 0.0894009 | 1(Win) | true |
| Jsonifier (two-stage) | 947.508 | 0.410241 | 8648.49ms | 2251027 | 40 | 3.45569e+09 | 2.26568e+06 | 0.0320242 | 2(Loss) | true |
| simdjson (reflection) | 753.43 | 0.17184 | 5114.75ms | 2251027 | 30 | 7.19196e+08 | 2.8493e+06 | 0.919876 | 3(Loss) | true |
| simdjson (ondemand) | 683.869 | 0.108876 | 5547.04ms | 2251027 | 80 | 9.34482e+08 | 3.13912e+06 | 0.0127408 | 4(Loss) | true |
| Glaze | 629.51 | 0.273955 | 5876.52ms | 2251027 | 80 | 6.98239e+09 | 3.41019e+06 | 0.573609 | 5(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Glaze | 1804.23 | 0.125135 | 6976.62ms | 2090234 | 320 | 6.11663e+08 | 1.10485e+06 | 0.00941396 | 1(Win) | true |
| Jsonifier | 1326.61 | 0.346484 | 9546.56ms | 2090234 | 40 | 1.08425e+09 | 1.50262e+06 | 0.265777 | 2(Loss) | true |
| simdjson (reflection) | 861.426 | 0.200687 | 7256.26ms | 2090326 | 40 | 8.62762e+08 | 2.31418e+06 | 0.0399925 | 3(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Glaze | 1875.75 | 0.169491 | 6753.39ms | 2090234 | 160 | 5.19103e+08 | 1.06272e+06 | 0.041085 | 1(Win) | true |
| Jsonifier | 1348.71 | 0.197945 | 9538.38ms | 2090234 | 40 | 3.42373e+08 | 1.478e+06 | 0.713962 | 2(Loss) | true |
| simdjson (reflection) | 861.733 | 0.223397 | 7177.7ms | 2090326 | 40 | 1.06831e+09 | 2.31335e+06 | 0.168027 | 3(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1808.87 | 0.125722 | 9159.12ms | 5373214 | 160 | 2.02955e+09 | 2.83287e+06 | 0.259632 | 1(Win) | true |
| Jsonifier (two-stage) | 1587.91 | 0.140713 | 10040.4ms | 5373214 | 160 | 3.29918e+09 | 3.22707e+06 | 0.574851 | 2(Loss) | true |
| simdjson (reflection) | 1382.07 | 0.236547 | 5615.43ms | 5373214 | 80 | 6.15362e+09 | 3.70769e+06 | 0.493302 | 3(Loss) | true |
| simdjson (ondemand) | 1276.71 | 0.304991 | 6051.02ms | 5373214 | 80 | 1.1988e+10 | 4.01366e+06 | 0.534414 | 4(Loss) | true |
| Glaze | 1259.79 | 0.264884 | 6198.41ms | 5373214 | 30 | 3.48258e+09 | 4.06757e+06 | 0.0687637 | 5(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2221.91 | 0.0838396 | 8815.61ms | 5373214 | 160 | 5.98181e+08 | 2.30626e+06 | 0.298397 | 1(Win) | true |
| Jsonifier (two-stage) | 1902.75 | 0.179239 | 10035.7ms | 5373214 | 30 | 6.99018e+08 | 2.69309e+06 | 0.0993951 | 2(Loss) | true |
| simdjson (reflection) | 1607.26 | 0.247065 | 5611.83ms | 5373214 | 40 | 2.48185e+09 | 3.18821e+06 | 0.051764 | 3(Loss) | true |
| simdjson (ondemand) | 1476.25 | 0.134207 | 5991.79ms | 5373214 | 40 | 8.68069e+08 | 3.47115e+06 | 0.030413 | 4(Loss) | true |
| Glaze | 1431.67 | 0.185802 | 6188.3ms | 5373214 | 40 | 1.76908e+09 | 3.57925e+06 | 0.241975 | 5(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7749.4 | 0.165283 | 5287.47ms | 6661897 | 160 | 2.93791e+08 | 819842 | 0.0158104 | 1(Win) | true |
| Glaze | 3615.97 | 0.0786109 | 5461.45ms | 6661897 | 160 | 3.05234e+08 | 1.75701e+06 | 0.259313 | 2(Loss) | true |
| simdjson (reflection) | 312.466 | 0.132126 | 6126.96ms | 6661989 | 30 | 2.16521e+10 | 2.0333e+07 | 0.32478 | 3(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7774.94 | 0.199013 | 5225.71ms | 6661897 | 80 | 2.11571e+08 | 817149 | 0.0732839 | 1(Win) | true |
| Glaze | 4092.55 | 0.228319 | 5091.09ms | 6661897 | 40 | 5.02518e+08 | 1.5524e+06 | 0.187381 | 2(Loss) | true |
| simdjson (reflection) | 311.649 | 0.208133 | 6163ms | 6661989 | 30 | 5.40106e+10 | 2.03863e+07 | 0.52651 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2100.75 | 0.181287 | 5801.72ms | 500299 | 160 | 2.71246e+07 | 227120 | 0.0408428 | 1(Win) | true |
| Jsonifier (two-stage) | 1414.66 | 0.0716844 | 8689.28ms | 500299 | 640 | 3.74098e+07 | 337270 | 0.0598097 | 2(Loss) | true |
| Glaze | 1376.68 | 0.0870885 | 8913.65ms | 500299 | 640 | 5.83032e+07 | 346574 | 0.0811866 | 3(Loss) | true |
| simdjson (ondemand) | 1180.11 | 0.109885 | 5210.73ms | 500299 | 320 | 6.31595e+07 | 404303 | 0.148775 | 4(Loss) | true |
| simdjson (reflection) | 1154.96 | 0.129845 | 5289.28ms | 500299 | 640 | 1.84144e+08 | 413107 | 0.0557414 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2624.62 | 0.222044 | 5696.32ms | 500299 | 160 | 2.6069e+07 | 181787 | 0.0395911 | 1(Win) | true |
| Jsonifier (two-stage) | 1628.11 | 0.195907 | 8848.01ms | 500299 | 160 | 5.27367e+07 | 293053 | 0.0207514 | 2(Loss) | true |
| Glaze | 1586.22 | 0.08167 | 8721.3ms | 500299 | 640 | 3.86224e+07 | 300792 | 0.0243416 | 3(Loss) | true |
| simdjson (ondemand) | 1309.18 | 0.181589 | 5080.2ms | 500299 | 160 | 7.00741e+07 | 364443 | 0.0760092 | 4(Loss) | true |
| simdjson (reflection) | 1278.42 | 0.111454 | 5280.05ms | 500299 | 320 | 5.53665e+07 | 373211 | 0.048897 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8658.21 | 0.0641862 | 5517.71ms | 500299 | 4890 | 6.11779e+06 | 55106.3 | 0.0597923 | 1(Win) | true |
| simdjson (reflection) | 8129.25 | 0.0626453 | 5876.21ms | 500299 | 4890 | 6.61066e+06 | 58692.1 | 0.0412879 | 2(Loss) | true |
| Glaze | 2225.86 | 0.110177 | 5495.15ms | 500299 | 320 | 1.78484e+07 | 214354 | 0.103273 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8684.47 | 0.0573565 | 5550.88ms | 500299 | 4890 | 4.85566e+06 | 54939.7 | 0.222573 | 1(Win) | true |
| simdjson (reflection) | 8158.91 | 0.0991179 | 5922.32ms | 500299 | 2560 | 8.60082e+06 | 58478.7 | 0.00974619 | 2(Loss) | true |
| Glaze | 2342.57 | 0.0990833 | 5240.58ms | 500299 | 1280 | 5.21297e+07 | 203675 | 0.271461 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3077.07 | 0.0811584 | 9156.67ms | 1151920 | 1280 | 1.0746e+08 | 357014 | 0.0630391 | 1(Win) | true |
| Jsonifier (two-stage) | 2682.48 | 0.153936 | 5265.14ms | 1151920 | 320 | 1.27175e+08 | 409530 | 0.146136 | 2(Loss) | true |
| simdjson (ondemand) | 2270.6 | 0.0756999 | 6224.81ms | 1151920 | 640 | 8.58489e+07 | 483818 | 0.221657 | 3(Loss) | true |
| simdjson (reflection) | 2230.21 | 0.0861672 | 6329.98ms | 1151920 | 640 | 1.15297e+08 | 492579 | 0.153243 | 4(Loss) | true |
| Glaze | 2000.5 | 0.105422 | 7044.87ms | 1151920 | 320 | 1.07246e+08 | 549140 | 0.0607127 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3536.08 | 0.140765 | 8992.7ms | 1151920 | 320 | 6.11985e+07 | 310670 | 0.0113316 | 1(Win) | true |
| Jsonifier (two-stage) | 3041.41 | 0.181032 | 5131.19ms | 1151920 | 160 | 6.84111e+07 | 361200 | 0.0672858 | 2(Loss) | true |
| simdjson (ondemand) | 2468.89 | 0.121004 | 6100.08ms | 1151920 | 640 | 1.85533e+08 | 444960 | 0.109194 | 3(Loss) | true |
| simdjson (reflection) | 2404.78 | 0.183863 | 6312.57ms | 1151920 | 320 | 2.25753e+08 | 456822 | 0.0650129 | 4(Loss) | true |
| Glaze | 2183.77 | 0.158792 | 7236.32ms | 1151920 | 320 | 2.04191e+08 | 503056 | 0.242089 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 20504.5 | 0.0580861 | 6766.71ms | 1439562 | 4890 | 7.39633e+06 | 66954.7 | 0.150871 | 1(Win) | true |
| Glaze | 4014.08 | 0.063393 | 8743.58ms | 1439584 | 1280 | 6.01721e+07 | 342020 | 0.0834926 | 2(Loss) | true |
| simdjson (reflection) | 357.317 | 0.101431 | 5795.2ms | 1439562 | 80 | 1.21503e+09 | 3.84217e+06 | 0.260919 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 20570.5 | 0.10413 | 6751.93ms | 1439562 | 1280 | 6.18209e+06 | 66739.8 | 0.0709717 | 1(Win) | true |
| Glaze | 4625.85 | 0.153397 | 8019.32ms | 1439584 | 80 | 1.65811e+07 | 296787 | 0.250773 | 2(Loss) | true |
| simdjson (reflection) | 356.422 | 0.204662 | 5847.49ms | 1439562 | 80 | 4.97159e+09 | 3.85181e+06 | 0.204285 | 3(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1866.98 | 0.0689124 | 2949.14ms | 56369 | 4890 | 1.92533e+06 | 28793.9 | 0.0420925 | 1(Win) | true |
| Glaze | 1490.35 | 0.124333 | 3653.71ms | 56369 | 30 | 60338.3 | 36070.4 | 0.023663 | 2(Loss) | true |
| Jsonifier (two-stage) | 1276.92 | 0.0929955 | 4200.73ms | 56369 | 4890 | 7.49521e+06 | 42099.4 | 0.132645 | 3(Loss) | true |
| simdjson (reflection) | 1067.81 | 0.0690938 | 5036.33ms | 56369 | 4890 | 5.91669e+06 | 50343.8 | 0.022823 | 4(Loss) | true |
| simdjson (ondemand) | 1010.52 | 0.0592121 | 5335.04ms | 56369 | 4890 | 4.85204e+06 | 53198.3 | 0.118501 | 5(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2542.9 | 0.0962638 | 2585.73ms | 56369 | 2560 | 1.0602e+06 | 21140.3 | 0.319219 | 1(Win) | true |
| Glaze | 1998.27 | 0.0700007 | 3152.27ms | 56369 | 4890 | 1.73414e+06 | 26902.1 | 0.0635515 | 2(Loss) | true |
| Jsonifier (two-stage) | 1629.83 | 0.0924614 | 3948.74ms | 56369 | 2560 | 2.381e+06 | 32983.7 | 0.0166777 | 3(Loss) | true |
| simdjson (ondemand) | 1215.35 | 0.0910034 | 4933.26ms | 56369 | 2560 | 4.14792e+06 | 44232.1 | 0.0549073 | 4(Loss) | true |
| simdjson (reflection) | 1200.76 | 0.191281 | 5376.53ms | 56369 | 160 | 1.17336e+06 | 44769.6 | 0.182599 | 5(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12888.4 | 0.313202 | 422.891ms | 56369 | 1280 | 218443 | 4171 | 0.358337 | 1(Win) | true |
| simdjson (reflection) | 10269.1 | 0.201744 | 531.234ms | 56369 | 2560 | 285534 | 5234.9 | 0.0477336 | 2(Loss) | true |
| Glaze | 2908.49 | 0.133754 | 1853.98ms | 56369 | 2560 | 1.56458e+06 | 18483 | 0.316968 | 3(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13415.8 | 0.184473 | 403.165ms | 56369 | 4890 | 267193 | 4007.05 | 0.140693 | 1(Win) | true |
| simdjson (reflection) | 10695.1 | 0.158268 | 510.878ms | 56369 | 1280 | 81004.7 | 5026.4 | 0.0557369 | 2(Loss) | true |
| Glaze | 3252.6 | 0.178802 | 1668.11ms | 56369 | 640 | 558915 | 16527.6 | 0.0846351 | 3(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2041.84 | 0.135092 | 3994.24ms | 83958 | 640 | 1.79607e+06 | 39214 | 0.0357143 | 1(Win) | true |
| Glaze | 1808.73 | 0.0767206 | 4498.94ms | 83958 | 4890 | 5.64039e+06 | 44267.8 | 0.268963 | 2(Loss) | true |
| Jsonifier (two-stage) | 1758.33 | 0.128885 | 4609.61ms | 83958 | 1280 | 4.40899e+06 | 45536.6 | 0.0303145 | 3(Loss) | true |
| simdjson (reflection) | 1485.79 | 0.118314 | 5447.05ms | 83958 | 1280 | 5.20342e+06 | 53889.6 | 0.017069 | 4(Loss) | true |
| simdjson (ondemand) | 1416.91 | 0.067631 | 5723.92ms | 83958 | 2560 | 3.73912e+06 | 56509.1 | 0.0929918 | 5(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2523.31 | 0.102471 | 3637.85ms | 83958 | 2560 | 2.70662e+06 | 31731.6 | 0.108527 | 1(Win) | true |
| Glaze | 2272.2 | 0.133461 | 3982.73ms | 83958 | 1280 | 2.83107e+06 | 35238.4 | 0.021572 | 2(Loss) | true |
| Jsonifier (two-stage) | 2195.52 | 0.0886391 | 4248.34ms | 83958 | 2560 | 2.6751e+06 | 36469.1 | 0.281852 | 3(Loss) | true |
| simdjson (ondemand) | 1681.87 | 0.0582136 | 5225.72ms | 83958 | 4890 | 3.75576e+06 | 47606.9 | 0.217337 | 4(Loss) | true |
| simdjson (reflection) | 1656.66 | 0.241814 | 5320.61ms | 83958 | 160 | 2.18544e+06 | 48331.2 | 0.135915 | 5(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14932.5 | 0.166966 | 609.623ms | 94370 | 1280 | 129619 | 6027 | 0.0498008 | 1(Win) | true |
| Glaze | 2535.1 | 0.271278 | 3593.9ms | 94370 | 40 | 370993 | 35500.8 | 0.18594 | 2(Loss) | true |
| simdjson (reflection) | 366.961 | 0.139351 | 6698.5ms | 94370 | 320 | 3.73765e+07 | 245253 | 0.0496061 | 3(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15453 | 0.177746 | 587.543ms | 94370 | 2560 | 274334 | 5824 | 0.109769 | 1(Win) | true |
| Glaze | 2791.44 | 0.167881 | 3263.82ms | 94370 | 640 | 1.87498e+06 | 32240.8 | 0.0993517 | 2(Loss) | true |
| simdjson (reflection) | 368.234 | 0.0724147 | 6241.86ms | 94370 | 1280 | 4.00944e+07 | 244405 | 0.399619 | 3(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1688.88 | 0.0746136 | 3022.92ms | 53331 | 4890 | 2.46892e+06 | 30114.9 | 0.00642081 | 1(Win) | true |
| Glaze | 1514.17 | 0.0766029 | 3430.97ms | 53331 | 4890 | 3.23749e+06 | 33589.6 | 0.100204 | 2(Loss) | true |
| Jsonifier (two-stage) | 1453.86 | 0.146479 | 3488.53ms | 53331 | 1280 | 3.36105e+06 | 34983 | 0.411601 | 3(Loss) | true |
| simdjson (reflection) | 1277.8 | 0.127339 | 4030.97ms | 53331 | 1280 | 3.28825e+06 | 39803 | 0.0849904 | 4(Loss) | true |
| simdjson (ondemand) | 1047.86 | 0.243635 | 4951.96ms | 53331 | 160 | 2.23746e+06 | 48537.6 | 0.0724685 | 5(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2409.3 | 0.155695 | 2792.29ms | 53331 | 640 | 691361 | 21110 | 0.00947508 | 1(Win) | true |
| Glaze | 2014.19 | 0.0817198 | 3120.07ms | 53331 | 4890 | 2.0822e+06 | 25251.1 | 0.151148 | 2(Loss) | true |
| Jsonifier (two-stage) | 1963.27 | 0.159368 | 3221.2ms | 53331 | 640 | 1.09089e+06 | 25906 | 0.0973695 | 3(Loss) | true |
| simdjson (reflection) | 1522.29 | 0.0926844 | 3952.08ms | 53331 | 2560 | 2.45482e+06 | 33410.5 | 0.210857 | 4(Loss) | true |
| simdjson (ondemand) | 1244.4 | 0.0689646 | 4658.35ms | 53331 | 4890 | 3.88511e+06 | 40871.5 | 0.0318797 | 5(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16078.3 | 0.326357 | 351.598ms | 58581 | 2560 | 329200 | 3474.7 | 0.0201416 | 1(Win) | true |
| simdjson (reflection) | 12016.5 | 0.59333 | 470.751ms | 58581 | 640 | 486999 | 4649.2 | 0.684338 | 2(Loss) | true |
| Glaze | 3911.37 | 0.0878799 | 1437.43ms | 58581 | 4890 | 770449 | 14283.3 | 0.042598 | 3(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17298.5 | 0.741689 | 327.581ms | 58581 | 320 | 183608 | 3229.6 | 0.222442 | 1(Win) | true |
| simdjson (reflection) | 12580.4 | 0.633516 | 451.864ms | 58581 | 640 | 506544 | 4440.8 | 1.11111 | 2(Loss) | true |
| Glaze | 4789.71 | 0.241355 | 1185.7ms | 58581 | 640 | 507212 | 11664 | 0.0959298 | 3(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1761.12 | 0.263694 | 3639.56ms | 65103 | 160 | 1.38276e+06 | 35254.4 | 0.0817587 | 1(Win) | true |
| Glaze | 1679 | 0.0933533 | 3746.76ms | 65103 | 2560 | 3.05069e+06 | 36978.5 | 0.244678 | 2(Loss) | true |
| Jsonifier (two-stage) | 1659.73 | 0.201132 | 4131.51ms | 65103 | 160 | 905757 | 37408 | 0.281498 | 3(Loss) | true |
| simdjson (reflection) | 1506.71 | 0.0772538 | 4119.31ms | 65103 | 4890 | 4.95556e+06 | 41207.1 | 0.185993 | 4(Loss) | true |
| simdjson (ondemand) | 1242 | 0.112959 | 5026.95ms | 65103 | 1280 | 4.08142e+06 | 49989.4 | 0.175143 | 5(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2372.87 | 0.0880218 | 3250.28ms | 65103 | 4890 | 2.59383e+06 | 26165.3 | 0.199694 | 1(Win) | true |
| Glaze | 2181.36 | 0.0739691 | 3466.88ms | 65103 | 4890 | 2.16748e+06 | 28462.5 | 0.0920948 | 2(Loss) | true |
| Jsonifier (two-stage) | 2124.88 | 0.0942903 | 3565.86ms | 65103 | 2560 | 1.94316e+06 | 29219.1 | 0.0551313 | 3(Loss) | true |
| simdjson (reflection) | 1811.71 | 0.236859 | 4124.22ms | 65103 | 30 | 197663 | 34269.9 | 0.0997009 | 4(Loss) | true |
| simdjson (ondemand) | 1475.93 | 0.0765528 | 4848.27ms | 65103 | 2560 | 2.65479e+06 | 42066.3 | 0.265776 | 5(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16864.6 | 0.458362 | 452.559ms | 78778 | 640 | 266841 | 4454.8 | 0.0448752 | 1(Win) | true |
| Glaze | 3486.48 | 0.0925177 | 2153.07ms | 78778 | 4890 | 1.94355e+06 | 21548.6 | 0.252865 | 2(Loss) | true |
| simdjson (reflection) | 444.765 | 0.10406 | 8722.49ms | 78778 | 640 | 1.97741e+07 | 168918 | 0.173039 | 3(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17763.4 | 0.311844 | 429.27ms | 78778 | 1280 | 222660 | 4229.4 | 0.240589 | 1(Win) | true |
| Glaze | 4253.3 | 0.324463 | 1765.27ms | 78778 | 640 | 2.10218e+06 | 17663.6 | 0.0793219 | 2(Loss) | true |
| simdjson (reflection) | 444.425 | 0.0748704 | 8734.6ms | 78778 | 1280 | 2.05042e+07 | 169047 | 0.0081641 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1931.22 | 0.199231 | 585.237ms | 11812 | 2560 | 345731 | 5833 | 0.440817 | 1(Win) | true |
| Jsonifier (two-stage) | 1312.3 | 0.451887 | 868.675ms | 11812 | 320 | 481492 | 8584 | 0.111711 | 2(Loss) | true |
| Glaze | 1044.2 | 0.201334 | 1083.95ms | 11812 | 1280 | 603848 | 10788 | 0.252769 | 3(Loss) | true |
| simdjson (reflection) | 1017.58 | 0.131322 | 1156.28ms | 11812 | 1280 | 270519 | 11070.2 | 0.0776257 | 4(Loss) | true |
| simdjson (ondemand) | 772.822 | 0.166184 | 1528.59ms | 11812 | 2560 | 1.50214e+06 | 14576.2 | 0.158911 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2305.34 | 0.538501 | 569.154ms | 11812 | 160 | 110783 | 4886.4 | 0.065445 | 1(Win) | true |
| Jsonifier (two-stage) | 1519.15 | 0.386081 | 855.169ms | 11812 | 320 | 262272 | 7415.2 | 0.140449 | 2(Loss) | true |
| Glaze | 1153.25 | 0.129424 | 1057.6ms | 11812 | 4890 | 781516 | 9767.89 | 0.326615 | 3(Loss) | true |
| simdjson (reflection) | 1100.64 | 0.205659 | 1110.04ms | 11812 | 640 | 283552 | 10234.8 | 0.325439 | 4(Loss) | true |
| simdjson (ondemand) | 839.266 | 0.144599 | 1429.08ms | 11812 | 1280 | 482159 | 13422.2 | 0.280832 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11282.9 | 0.865452 | 103.221ms | 11812 | 80 | 5972.9 | 998.4 | 0 | 1(Win) | true |
| simdjson (reflection) | 8623.91 | 0.523684 | 132.751ms | 11812 | 4890 | 228815 | 1306.23 | 0.719271 | 2(Loss) | true |
| Glaze | 1907.48 | 0.305947 | 603.452ms | 11812 | 320 | 104465 | 5905.6 | 0.0813449 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11605.4 | 0.37922 | 101.953ms | 11812 | 4890 | 66255.3 | 970.654 | 0.149977 | 1(Win) | true |
| simdjson (reflection) | 8965.22 | 0.711598 | 129.072ms | 11812 | 2560 | 204660 | 1256.5 | 0.467364 | 2(Loss) | true |
| Glaze | 2019.22 | 0.299861 | 563.694ms | 11812 | 1280 | 358205 | 5578.8 | 0.0286718 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2791.96 | 0.630991 | 882.744ms | 25388 | 80 | 239538 | 8672 | 0.0737463 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1876.54 | 1.90643 | 1142.37ms | 25388 | 30 | 1.81512e+06 | 12902.4 | 2.07254 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1875.55 | 0.134413 | 1354.47ms | 25388 | 1280 | 385381 | 12909.2 | 0.108568 | 2(Tie) | true |
| Glaze | 1706.5 | 0.288407 | 1443.32ms | 25388 | 320 | 535802 | 14188 | 0.0394856 | 4(Loss) | true |
| simdjson (ondemand) | 1475.67 | 0.0810758 | 1708.43ms | 25388 | 4890 | 865308 | 16407.4 | 0.207049 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3046.13 | 0.127623 | 873.892ms | 25388 | 2560 | 263424 | 7948.4 | 0.3885 | 1(Win) | true |
| Jsonifier (two-stage) | 2598.29 | 0.964354 | 1124.08ms | 25388 | 30 | 242257 | 9318.4 | 0.459982 | 2(Loss) | true |
| simdjson (reflection) | 1999 | 0.127132 | 1296.14ms | 25388 | 1280 | 303495 | 12112 | 0.0561742 | 3(Loss) | true |
| Glaze | 1809.75 | 0.128196 | 1453.9ms | 25388 | 4890 | 1.4384e+06 | 13378.6 | 0.219336 | 4(Loss) | true |
| simdjson (ondemand) | 1566.67 | 0.0949881 | 1626.35ms | 25388 | 4890 | 1.05378e+06 | 15454.3 | 0.0695293 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 20324.8 | 0.692689 | 150.313ms | 31235 | 2560 | 263845 | 1465.6 | 0.986353 | 1(Win) | true |
| Glaze | 3002.58 | 0.308549 | 1002.84ms | 31235 | 320 | 299842 | 9920.8 | 0.361562 | 2(Loss) | true |
| simdjson (reflection) | 340.431 | 0.0700881 | 8820.84ms | 31235 | 2560 | 9.6284e+06 | 87501 | 0.121747 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 22917.4 | 1.00319 | 134.963ms | 31235 | 1280 | 217634 | 1299.8 | 0.322086 | 1(Win) | true |
| Glaze | 3294.55 | 0.224755 | 910.847ms | 31235 | 640 | 264295 | 9041.6 | 0.106289 | 2(Loss) | true |
| simdjson (reflection) | 340.095 | 0.0731731 | 8812.85ms | 31235 | 2560 | 1.05154e+07 | 87587.3 | 0.006964 | 3(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2704.53 | 0.0619419 | 3830.34ms | 108313 | 4890 | 2.73688e+06 | 38193.4 | 0.018272 | 1(Win) | true |
| Jsonifier (two-stage) | 1674.61 | 0.0553164 | 6198.97ms | 108313 | 4890 | 5.69312e+06 | 61683.2 | 0.0791708 | 2(Loss) | true |
| Glaze | 1608.84 | 0.0579001 | 6429.41ms | 108313 | 4890 | 6.75772e+06 | 64204.7 | 0.0685705 | 3(Loss) | true |
| simdjson (reflection) | 1285.81 | 0.0640524 | 8064.26ms | 108313 | 2560 | 6.77825e+06 | 80334.7 | 0.136616 | 4(Loss) | true |
| simdjson (ondemand) | 1239.34 | 0.0636945 | 8538.52ms | 108313 | 2560 | 7.21475e+06 | 83346.8 | 0.000719878 | 5(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3201.25 | 0.135703 | 3532.29ms | 108313 | 640 | 1.22711e+06 | 32267.2 | 0.0247868 | 1(Win) | true |
| Jsonifier (two-stage) | 1867.76 | 0.16382 | 5879.26ms | 108313 | 30 | 246250 | 55304.5 | 0.0154321 | 2(Loss) | true |
| Glaze | 1771.02 | 0.157682 | 6143.87ms | 108313 | 640 | 5.41324e+06 | 58325.2 | 0.200539 | 3(Loss) | true |
| simdjson (reflection) | 1338.74 | 0.128844 | 8097.24ms | 108313 | 30 | 296494 | 77158.4 | 0.199468 | 4(Loss) | true |
| simdjson (ondemand) | 1332.44 | 0.0981455 | 8232.16ms | 108313 | 2560 | 1.48201e+07 | 77523.7 | 0.268897 | 5(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14877.2 | 0.115749 | 700.282ms | 108313 | 4890 | 315835 | 6943.2 | 0.155814 | 1(Win) | true |
| simdjson (reflection) | 8482.81 | 0.0972589 | 1221.62ms | 108313 | 4890 | 685881 | 12177 | 0.153922 | 2(Loss) | true |
| Glaze | 2078.51 | 0.130471 | 5015.18ms | 108313 | 2560 | 1.07629e+07 | 49696.8 | 0.155101 | 3(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15417.5 | 0.125882 | 679.046ms | 108313 | 4890 | 347833 | 6699.87 | 0.143517 | 1(Win) | true |
| simdjson (reflection) | 8744.36 | 0.26753 | 1254.36ms | 108313 | 160 | 159798 | 11812.8 | 0.0947226 | 2(Loss) | true |
| Glaze | 2138.37 | 0.200903 | 4879.92ms | 108313 | 160 | 1.50691e+06 | 48305.6 | 0.142224 | 3(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2905.99 | 0.0778237 | 6088.97ms | 183677 | 2560 | 5.63359e+06 | 60278.3 | 0.281067 | 1(Win) | true |
| Jsonifier (two-stage) | 2430.53 | 0.0682759 | 7620.47ms | 183677 | 4890 | 1.184e+07 | 72069.8 | 0.237916 | 2(Loss) | true |
| Glaze | 2089.45 | 0.0671829 | 8410.96ms | 183677 | 2560 | 8.12085e+06 | 83834.4 | 0.0398563 | 3(Loss) | true |
| simdjson (reflection) | 1964.94 | 0.100891 | 8949.93ms | 183677 | 1280 | 1.03545e+07 | 89146.6 | 0.0724124 | 4(Loss) | true |
| simdjson (ondemand) | 1889.24 | 0.0641261 | 9355.54ms | 183677 | 2560 | 9.04994e+06 | 92718.9 | 0.0128328 | 5(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3228.63 | 0.0945011 | 5673.63ms | 183677 | 1280 | 3.36478e+06 | 54254.6 | 0.0718317 | 1(Win) | true |
| Jsonifier (two-stage) | 2656.51 | 0.0539023 | 6886.37ms | 183677 | 4890 | 6.17745e+06 | 65939.1 | 0.0753031 | 2(Loss) | true |
| Glaze | 2259.18 | 0.115486 | 8031.4ms | 183677 | 2560 | 2.0526e+07 | 77536 | 0.146813 | 3(Loss) | true |
| simdjson (reflection) | 2027.02 | 0.0477269 | 8968.68ms | 183677 | 4890 | 8.31821e+06 | 86416.5 | 0.0281775 | 4(Loss) | true |
| simdjson (ondemand) | 2018.83 | 0.097207 | 8961.86ms | 183677 | 2560 | 1.82114e+07 | 86767 | 0.220105 | 5(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 18039.7 | 0.311371 | 1204.11ms | 213963 | 320 | 396939 | 11311.2 | 1.04283 | 1(Win) | true |
| Glaze | 2438.65 | 0.339696 | 8492.56ms | 213963 | 40 | 3.2316e+06 | 83673.6 | 0.106968 | 2(Loss) | true |
| simdjson (reflection) | 310.369 | 0.624738 | 7724.53ms | 213963 | 160 | 2.69921e+09 | 657446 | 0.405259 | 3(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 18426.8 | 0.190362 | 1197.59ms | 213963 | 160 | 71097.8 | 11073.6 | 0.12987 | 1(Win) | true |
| Glaze | 2670.82 | 0.153316 | 7756.07ms | 213963 | 320 | 4.39045e+06 | 76400 | 0.0922316 | 2(Loss) | true |
| simdjson (reflection) | 352.571 | 0.109563 | 7419.47ms | 213963 | 320 | 1.28665e+08 | 578752 | 0.0350977 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 705.475 | 0.129354 | 7704.67ms | 1834197 | 80 | 8.22963e+08 | 2.4795e+06 | 0.141389 | 1(Win) | true |
| Jsonifier (two-stage) | 586.065 | 0.146316 | 9325.76ms | 1834197 | 80 | 1.52572e+09 | 2.9847e+06 | 0.0610744 | 2(Loss) | true |
| Glaze | 534.874 | 0.111654 | 10227.6ms | 1834197 | 160 | 2.13334e+09 | 3.27036e+06 | 0.0127219 | 3(Loss) | true |
| simdjson (reflection) | 524.404 | 0.35626 | 5055.47ms | 1834197 | 40 | 5.64878e+09 | 3.33565e+06 | 0.0633398 | 4(Loss) | true |
| simdjson (ondemand) | 428.624 | 0.842424 | 5775.42ms | 1834197 | 30 | 3.54587e+10 | 4.08103e+06 | 0.722173 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 812.417 | 0.184859 | 7759.05ms | 1834197 | 80 | 1.26738e+09 | 2.15311e+06 | 0.0359536 | 1(Win) | true |
| Jsonifier (two-stage) | 660.121 | 0.244126 | 9400.06ms | 1834197 | 30 | 1.25543e+09 | 2.64986e+06 | 0.111298 | 2(Loss) | true |
| Glaze | 594.774 | 0.0938328 | 10214.8ms | 1834197 | 160 | 1.21848e+09 | 2.941e+06 | 0.199514 | 3(Loss) | true |
| simdjson (reflection) | 586.741 | 0.141197 | 10363.1ms | 1834197 | 40 | 7.08783e+08 | 2.98126e+06 | 0.0847959 | 4(Loss) | true |
| simdjson (ondemand) | 536.437 | 0.194305 | 5411.03ms | 1834197 | 30 | 1.20433e+09 | 3.26083e+06 | 0.393081 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1399.77 | 0.142526 | 7936.67ms | 1834197 | 160 | 5.0756e+08 | 1.24965e+06 | 0.248666 | 1(Win) | true |
| Glaze | 941.076 | 0.200381 | 5761.36ms | 1833577 | 160 | 2.2181e+09 | 1.85812e+06 | 0.129597 | 2(Loss) | true |
| simdjson (reflection) | 818.036 | 0.147898 | 7018.08ms | 1922245 | 160 | 1.75759e+09 | 2.24097e+06 | 0.0335456 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1401.6 | 0.292989 | 8072.08ms | 1834197 | 30 | 4.01118e+08 | 1.24803e+06 | 0.074584 | 1(Win) | true |
| Glaze | 943.834 | 0.12127 | 5804.49ms | 1833577 | 160 | 8.07664e+08 | 1.85269e+06 | 0.0173555 | 2(Loss) | true |
| simdjson (reflection) | 806.98 | 0.731102 | 7081.57ms | 1922245 | 40 | 1.10334e+10 | 2.27167e+06 | 0.22995 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2119.3 | 0.132125 | 5034.58ms | 7351818 | 40 | 7.64244e+08 | 3.30828e+06 | 0.661465 | 1(Win) | true |
| Jsonifier (two-stage) | 1973.61 | 0.119434 | 5355.64ms | 7351818 | 30 | 5.40066e+08 | 3.55249e+06 | 0.155652 | 2(Loss) | true |
| simdjson (reflection) | 1780.89 | 0.212974 | 5890.49ms | 7351818 | 80 | 5.62421e+09 | 3.93694e+06 | 0.0497195 | 3(Loss) | true |
| simdjson (ondemand) | 1677.63 | 0.0950469 | 6296.76ms | 7351818 | 80 | 1.2623e+09 | 4.17925e+06 | 0.0872887 | 4(Loss) | true |
| Glaze | 1589.33 | 0.179007 | 6913.22ms | 7351818 | 80 | 4.98877e+09 | 4.41145e+06 | 0.393922 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2352 | 0.14429 | 10335.4ms | 7351818 | 80 | 1.48004e+09 | 2.98097e+06 | 0.0107336 | 1(Win) | true |
| Jsonifier (two-stage) | 2173.82 | 0.129919 | 5421.29ms | 7351818 | 40 | 7.02343e+08 | 3.22531e+06 | 0.216877 | 2(Loss) | true |
| simdjson (reflection) | 1956.51 | 0.21167 | 5920.8ms | 7351818 | 40 | 2.30145e+09 | 3.58354e+06 | 0.161949 | 3(Loss) | true |
| simdjson (ondemand) | 1805.3 | 0.642258 | 6346.26ms | 7351818 | 30 | 1.86652e+10 | 3.88371e+06 | 0.529016 | 4(Loss) | true |
| Glaze | 1708.62 | 0.20377 | 6685.43ms | 7351818 | 80 | 5.59336e+09 | 4.10346e+06 | 0.622568 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6870.04 | 0.138945 | 8723.25ms | 9930848 | 320 | 1.17405e+09 | 1.37856e+06 | 0.0592729 | 1(Win) | true |
| Glaze | 3345.15 | 0.136241 | 9198.49ms | 9930228 | 30 | 4.46296e+08 | 2.83103e+06 | 0.0274219 | 2(Loss) | true |
| simdjson (reflection) | 314.353 | 0.148502 | 9144.23ms | 10018896 | 30 | 6.11211e+10 | 3.0395e+07 | 0.154117 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6856.25 | 0.22798 | 8675.85ms | 9930848 | 80 | 7.93384e+08 | 1.38134e+06 | 0.0913572 | 1(Win) | true |
| Glaze | 3445.03 | 0.113576 | 8578.57ms | 9930228 | 160 | 1.55965e+09 | 2.74894e+06 | 0.0681453 | 2(Loss) | true |
| simdjson (reflection) | 312.501 | 0.329712 | 9185.18ms | 10018896 | 30 | 3.0488e+11 | 3.05752e+07 | 0.245422 | 3(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 717.028 | 0.249798 | 7884.67ms | 1834197 | 160 | 5.94177e+09 | 2.43955e+06 | 0.629164 | 1(Win) | true |
| Jsonifier (two-stage) | 593.932 | 0.174241 | 9180.2ms | 1834197 | 160 | 4.21347e+09 | 2.94516e+06 | 0.177255 | 2(Loss) | true |
| Glaze | 534.91 | 0.114702 | 10224ms | 1834197 | 160 | 2.25107e+09 | 3.27013e+06 | 0.32717 | 3(Loss) | true |
| simdjson (reflection) | 526.432 | 0.2778 | 10351.2ms | 1834197 | 40 | 3.40826e+09 | 3.3228e+06 | 0.0388579 | 4(Loss) | true |
| simdjson (ondemand) | 485.468 | 0.26842 | 5404.85ms | 1834197 | 80 | 7.48322e+09 | 3.60317e+06 | 0.237331 | 5(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 833.104 | 0.203195 | 7582.78ms | 1834197 | 160 | 2.91232e+09 | 2.09965e+06 | 0.0200374 | 1(Win) | true |
| Jsonifier (two-stage) | 667.08 | 0.329103 | 9188.65ms | 1834197 | 40 | 2.97894e+09 | 2.62221e+06 | 0.0474532 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 591.395 | 0.360109 | 10239.5ms | 1834197 | 40 | 4.53801e+09 | 2.9578e+06 | 0.264433 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 586.922 | 0.164913 | 10326.1ms | 1834197 | 160 | 3.86512e+09 | 2.98034e+06 | 0.172301 | 3(Tie) | true |
| simdjson (ondemand) | 533.43 | 0.411681 | 5459.12ms | 1834197 | 30 | 5.4674e+09 | 3.27921e+06 | 0.581321 | 5(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1392.36 | 0.252312 | 7949.02ms | 1834197 | 320 | 3.21526e+09 | 1.25631e+06 | 0.575257 | 1(Win) | true |
| Glaze | 921.327 | 0.288382 | 6257.22ms | 1833577 | 40 | 1.1983e+09 | 1.89795e+06 | 0.215488 | 2(Loss) | true |
| simdjson (reflection) | 828.657 | 0.143212 | 6930.51ms | 1922245 | 160 | 1.60599e+09 | 2.21225e+06 | 0.219457 | 3(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1402.66 | 0.226055 | 7868.99ms | 1834197 | 80 | 6.35773e+08 | 1.24708e+06 | 0.0120617 | 1(Win) | true |
| Glaze | 940.127 | 0.370625 | 5823.76ms | 1833577 | 40 | 1.90088e+09 | 1.86e+06 | 0.0269607 | 2(Loss) | true |
| simdjson (reflection) | 827.579 | 0.223205 | 6932.57ms | 1922245 | 160 | 3.91135e+09 | 2.21513e+06 | 0.0559377 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2185.02 | 0.155329 | 10000.4ms | 7351818 | 40 | 9.93674e+08 | 3.20877e+06 | 3.02402 | 1(Win) | true |
| Jsonifier (two-stage) | 1981.84 | 0.327743 | 5353.27ms | 7351818 | 80 | 1.07549e+10 | 3.53774e+06 | 0.343542 | 2(Loss) | true |
| simdjson (reflection) | 1792.72 | 0.165453 | 5912.03ms | 7351818 | 80 | 3.34968e+09 | 3.91094e+06 | 0.0484619 | 3(Loss) | true |
| simdjson (ondemand) | 1669.29 | 0.267909 | 6351.92ms | 7351818 | 30 | 3.79859e+09 | 4.20013e+06 | 0.0996562 | 4(Loss) | true |
| Glaze | 1589.24 | 0.284537 | 6605.11ms | 7351818 | 40 | 6.30302e+09 | 4.4117e+06 | 0.0530266 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2436.64 | 0.235135 | 10413.2ms | 7351818 | 30 | 1.3733e+09 | 2.87742e+06 | 0.0842945 | 1(Win) | true |
| Jsonifier (two-stage) | 2205.65 | 0.113133 | 5280.17ms | 7351818 | 80 | 1.03463e+09 | 3.17876e+06 | 0.14405 | 2(Loss) | true |
| simdjson (reflection) | 1959.36 | 0.307427 | 5866.33ms | 7351818 | 30 | 3.63051e+09 | 3.57833e+06 | 0.171643 | 3(Loss) | true |
| simdjson (ondemand) | 1822.33 | 0.130888 | 6291.15ms | 7351818 | 30 | 7.60775e+08 | 3.8474e+06 | 0.173143 | 4(Loss) | true |
| Glaze | 1720.04 | 0.209539 | 6665.08ms | 7351818 | 80 | 5.83624e+09 | 4.07622e+06 | 0.198538 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6994.13 | 0.097196 | 8571.56ms | 9930848 | 320 | 5.54308e+08 | 1.35411e+06 | 0.179451 | 1(Win) | true |
| Glaze | 2990.5 | 0.17545 | 9864.7ms | 9930228 | 30 | 9.26105e+08 | 3.16676e+06 | 0.229327 | 2(Loss) | true |
| simdjson (reflection) | 317.066 | 0.176598 | 9092.13ms | 10018896 | 30 | 8.4964e+10 | 3.01349e+07 | 0.230891 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7029.98 | 0.171895 | 8799.95ms | 9930848 | 30 | 1.60883e+08 | 1.3472e+06 | 1.04797 | 1(Win) | true |
| Glaze | 3431.33 | 0.295468 | 8596.25ms | 9930228 | 40 | 2.65995e+09 | 2.75992e+06 | 0.348894 | 2(Loss) | true |
| simdjson (reflection) | 316.42 | 0.155361 | 9114.19ms | 10018896 | 30 | 6.60266e+10 | 3.01965e+07 | 0.152465 | 3(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1050.73 | 0.21245 | 5383.75ms | 461466 | 80 | 6.33436e+07 | 418842 | 0.186072 | 1(Win) | true |
| Jsonifier (two-stage) | 956.784 | 0.173567 | 5821.58ms | 461466 | 640 | 4.07911e+08 | 459966 | 0.210788 | 2(Loss) | true |
| Glaze | 784.309 | 0.12012 | 7113.75ms | 461466 | 640 | 2.90747e+08 | 561116 | 0.245041 | 3(Loss) | true |
| simdjson (reflection) | 767.861 | 0.157488 | 7371.03ms | 461466 | 640 | 5.21425e+08 | 573136 | 0.374995 | 4(Loss) | true |
| simdjson (ondemand) | 730.577 | 0.103028 | 7908.76ms | 461466 | 320 | 1.23257e+08 | 602385 | 0.275342 | 5(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1551.67 | 0.16731 | 9743.76ms | 461466 | 80 | 1.80143e+07 | 283622 | 0.0474094 | 1(Win) | true |
| Jsonifier (two-stage) | 1398.21 | 0.246967 | 5358.43ms | 461466 | 30 | 1.81275e+07 | 314752 | 0.143484 | 2(Loss) | true |
| Glaze | 1028.64 | 0.121047 | 6818.57ms | 461466 | 320 | 8.58242e+07 | 427834 | 0.00747898 | 3(Loss) | true |
| simdjson (reflection) | 922.018 | 0.156658 | 7317.03ms | 461466 | 640 | 3.57838e+08 | 477310 | 0.20128 | 4(Loss) | true |
| simdjson (ondemand) | 911.42 | 0.103567 | 7579.41ms | 461466 | 320 | 8.00274e+07 | 482860 | 0.325491 | 5(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12468.1 | 0.13017 | 3570.6ms | 461466 | 1280 | 2.70217e+06 | 35297.2 | 0.969621 | 1(Win) | true |
| simdjson (reflection) | 8814.6 | 0.119982 | 5144.05ms | 461466 | 1280 | 4.59321e+06 | 49927.2 | 0.216646 | 2(Loss) | true |
| Glaze | 2377.53 | 0.0644961 | 9525.06ms | 461466 | 2560 | 3.64867e+07 | 185103 | 0.0124811 | 3(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12581.9 | 0.0649252 | 3509.73ms | 461466 | 4890 | 2.52188e+06 | 34977.9 | 0.151512 | 1(Win) | true |
| simdjson (reflection) | 8667.52 | 0.215181 | 5063.9ms | 461466 | 160 | 1.90993e+06 | 50774.4 | 0.176779 | 2(Loss) | true |
| Glaze | 2548.34 | 0.180854 | 8925.33ms | 461466 | 160 | 1.56077e+07 | 172696 | 0.0231567 | 3(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1394.54 | 0.101826 | 6336.38ms | 728486 | 640 | 1.64695e+08 | 498184 | 0.0161412 | 1(Win) | true |
| Jsonifier (two-stage) | 1231.45 | 0.168647 | 7258.28ms | 728486 | 30 | 2.71576e+07 | 564164 | 0.0952007 | 2(Loss) | true |
| simdjson (reflection) | 1147.4 | 0.0995455 | 7762.58ms | 728486 | 640 | 2.32507e+08 | 605490 | 0.00132126 | 3(Loss) | true |
| Glaze | 1141.46 | 0.115807 | 7790.37ms | 728486 | 640 | 3.17958e+08 | 608638 | 0.395122 | 4(Loss) | true |
| simdjson (ondemand) | 1074.67 | 0.25342 | 8195.04ms | 728486 | 320 | 8.58862e+08 | 646466 | 0.00358887 | 5(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1924.87 | 0.195341 | 5897.68ms | 728486 | 40 | 1.98832e+07 | 360928 | 0.16935 | 1(Win) | true |
| Jsonifier (two-stage) | 1823.92 | 0.178014 | 6792.37ms | 728486 | 640 | 2.94252e+08 | 380905 | 0.256046 | 2(Loss) | true |
| Glaze | 1454.35 | 0.336277 | 7882.37ms | 728486 | 30 | 7.74138e+07 | 477696 | 0.619574 | 3(Loss) | true |
| simdjson (reflection) | 1362.27 | 0.214689 | 7717.92ms | 728486 | 160 | 1.91803e+08 | 509984 | 0.0846368 | 4(Loss) | true |
| simdjson (ondemand) | 1342.9 | 0.249421 | 7924.68ms | 728486 | 30 | 4.99508e+07 | 517342 | 0.0972234 | 5(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15908.5 | 0.0775719 | 5038.52ms | 837491 | 2560 | 3.88286e+06 | 50205.5 | 0.0149364 | 1(Win) | true |
| Glaze | 2744.88 | 0.223501 | 7832.79ms | 837491 | 40 | 1.69173e+07 | 290976 | 0.0329815 | 2(Loss) | true |
| simdjson (reflection) | 354.058 | 0.39044 | 7050.97ms | 837491 | 30 | 2.32725e+09 | 2.25583e+06 | 0.071066 | 3(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15893.9 | 0.242946 | 5068.34ms | 837491 | 4890 | 7.28831e+07 | 50251.5 | 0.282789 | 1(Win) | true |
| Glaze | 2938.85 | 0.12 | 6967.07ms | 837491 | 1280 | 1.36139e+08 | 271771 | 0.174569 | 2(Loss) | true |
| simdjson (reflection) | 352.051 | 0.324757 | 7019.71ms | 837491 | 80 | 4.34266e+09 | 2.26869e+06 | 0.0790669 | 3(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 5203.53 | 0.137266 | 8634.07ms | 466906 | 640 | 8.83011e+06 | 85572 | 0.0719344 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 5202.92 | 0.0722978 | 8858.48ms | 466906 | 2560 | 9.80065e+06 | 85582 | 0.0168288 | 1(Tie) | true |
| simdjson (reflection) | 4110.08 | 0.131464 | 5560.73ms | 466906 | 640 | 1.29823e+07 | 108338 | 0.0494995 | 3(Loss) | true |
| simdjson (ondemand) | 3827.47 | 0.145621 | 5879.9ms | 466906 | 1280 | 3.67363e+07 | 116337 | 0.245234 | 4(Loss) | true |
| Glaze | 2522 | 0.0876211 | 9062.37ms | 466906 | 2560 | 6.1267e+07 | 176557 | 0.0461254 | 5(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5342.73 | 0.125514 | 8769.08ms | 466906 | 640 | 7.00322e+06 | 83342.4 | 0.0316665 | 1(Win) | true |
| Jsonifier (two-stage) | 5313.05 | 0.133984 | 8536.12ms | 466906 | 640 | 8.06965e+06 | 83808 | 0.0898095 | 2(Loss) | true |
| simdjson (ondemand) | 4207.12 | 0.0990419 | 5574.21ms | 466906 | 640 | 7.03247e+06 | 105839 | 0.207056 | 3(Loss) | true |
| simdjson (reflection) | 4162.13 | 0.0808942 | 5607.28ms | 466906 | 1280 | 9.58678e+06 | 106983 | 0.0639764 | 4(Loss) | true |
| Glaze | 2566.72 | 0.0867393 | 9006.19ms | 466906 | 1280 | 2.89831e+07 | 173481 | 0.14316 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 5545.91 | 0.159205 | 5738.25ms | 631514 | 30 | 896713 | 108595 | 0.188235 | 1(Win) | true |
| Jsonifier | 5508.25 | 0.17723 | 5668.33ms | 631514 | 80 | 3.00404e+06 | 109338 | 0.0117055 | 2(Loss) | true |
| simdjson (ondemand) | 4726.33 | 0.0762159 | 6581.23ms | 631514 | 2560 | 2.41462e+07 | 127426 | 0.0372903 | 3(Loss) | true |
| simdjson (reflection) | 4713.26 | 0.0866716 | 6585.95ms | 631514 | 2560 | 3.13991e+07 | 127780 | 0.0134625 | 4(Loss) | true |
| Glaze | 3064.14 | 0.217219 | 5247.88ms | 631514 | 40 | 7.29126e+06 | 196550 | 0.159298 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 5612.95 | 0.465196 | 5698.1ms | 631514 | 30 | 7.47442e+06 | 107298 | 0.215191 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 5597.81 | 0.236279 | 5697.28ms | 631514 | 30 | 1.93866e+06 | 107588 | 0.0158655 | 1(Tie) | true |
| simdjson (ondemand) | 4824.03 | 0.176464 | 6495.31ms | 631514 | 320 | 1.55314e+07 | 124846 | 0.226965 | 3(Loss) | true |
| simdjson (reflection) | 4778.59 | 0.0775964 | 6578.37ms | 631514 | 2560 | 2.44845e+07 | 126033 | 0.073419 | 4(Loss) | true |
| Glaze | 3067.22 | 0.134727 | 5232.97ms | 631514 | 1280 | 8.95772e+07 | 196353 | 0.248537 | 5(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2086.04 | 0.100833 | 5458.73ms | 466906 | 1280 | 5.9297e+07 | 213455 | 0.00440392 | 1(Win) | true |
| Jsonifier (two-stage) | 1710.56 | 0.076373 | 6723.22ms | 466906 | 1280 | 5.05907e+07 | 260310 | 0.191787 | 2(Loss) | true |
| Glaze | 1668.03 | 0.117984 | 6817.86ms | 466906 | 1280 | 1.26972e+08 | 266948 | 0.497541 | 3(Loss) | true |
| simdjson (reflection) | 1351.53 | 0.120375 | 8469.98ms | 466906 | 640 | 1.00661e+08 | 329462 | 0.0804382 | 4(Loss) | true |
| simdjson (ondemand) | 1053.42 | 0.219938 | 5388.62ms | 466906 | 40 | 3.45712e+07 | 422694 | 0.522556 | 5(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2780.57 | 0.0773954 | 9867.61ms | 466906 | 2560 | 3.93245e+07 | 160139 | 0.0472492 | 1(Win) | true |
| Jsonifier (two-stage) | 2152.24 | 0.556355 | 6560.56ms | 466906 | 80 | 1.05992e+08 | 206890 | 1.0361 | 2(Loss) | true |
| Glaze | 2114.92 | 0.146889 | 6299.29ms | 466906 | 160 | 1.53029e+07 | 210541 | 0.0136809 | 3(Loss) | true |
| simdjson (reflection) | 1503.49 | 0.101448 | 8400.96ms | 466906 | 640 | 5.77734e+07 | 296162 | 0.0217496 | 4(Loss) | true |
| simdjson (ondemand) | 1202.9 | 0.16919 | 5186.69ms | 466906 | 30 | 1.1767e+07 | 370167 | 0.0184387 | 5(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14394.9 | 0.53361 | 2865.1ms | 475954 | 640 | 1.81193e+07 | 31532.4 | 0.0164937 | 1(Win) | true |
| simdjson (reflection) | 12051.3 | 0.0841247 | 3784.51ms | 475954 | 4890 | 4.90933e+06 | 37664.6 | 0.277836 | 2(Loss) | true |
| Glaze | 4047.73 | 0.0646158 | 5803.74ms | 475954 | 2560 | 1.34408e+07 | 112138 | 0.300153 | 3(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16436.9 | 0.163197 | 2774.54ms | 475954 | 1280 | 2.5997e+06 | 27615 | 0.0846648 | 1(Win) | true |
| simdjson (reflection) | 12223.8 | 0.141698 | 3819.28ms | 475954 | 40 | 110739 | 37132.8 | 0.172652 | 2(Loss) | true |
| Glaze | 4413.99 | 0.0836539 | 5232.69ms | 475954 | 2560 | 1.89444e+07 | 102833 | 0.400103 | 3(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2169.9 | 0.107044 | 7199.89ms | 631514 | 640 | 5.64926e+07 | 277551 | 0.374023 | 1(Win) | true |
| Jsonifier (two-stage) | 2039.73 | 0.255332 | 7473.88ms | 631514 | 160 | 9.0939e+07 | 295264 | 0.110423 | 2(Loss) | true |
| Glaze | 1939.47 | 0.125934 | 7965.65ms | 631514 | 1280 | 1.95748e+08 | 310527 | 0.133144 | 3(Loss) | true |
| simdjson (reflection) | 1728.29 | 0.101552 | 9017.49ms | 631514 | 640 | 8.01478e+07 | 348471 | 0.153591 | 4(Loss) | true |
| simdjson (ondemand) | 1362.01 | 0.130303 | 5703.22ms | 631514 | 160 | 5.31173e+07 | 442184 | 0.0112183 | 5(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2714.92 | 0.164082 | 6561.55ms | 631514 | 320 | 4.23958e+07 | 221833 | 0.106273 | 1(Win) | true |
| Jsonifier (two-stage) | 2560.19 | 0.0953727 | 6955.83ms | 631514 | 1280 | 6.44288e+07 | 235240 | 0.0861139 | 2(Loss) | true |
| Glaze | 2388.07 | 0.128779 | 7724.2ms | 631514 | 160 | 1.68765e+07 | 252195 | 1.86163 | 3(Loss) | true |
| simdjson (reflection) | 1919.82 | 0.124289 | 8972.59ms | 631514 | 320 | 4.86474e+07 | 313706 | 0.627708 | 4(Loss) | true |
| simdjson (ondemand) | 1533.49 | 0.119925 | 5370.13ms | 631514 | 640 | 1.41972e+08 | 392736 | 0.0909707 | 5(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17571.4 | 0.115799 | 3918.24ms | 716365 | 1280 | 2.59465e+06 | 38880.2 | 0.0550712 | 1(Win) | true |
| Glaze | 4037.09 | 0.167223 | 8965.57ms | 716365 | 160 | 1.28128e+07 | 169226 | 0.0605476 | 2(Loss) | true |
| simdjson (reflection) | 437.358 | 0.131385 | 9933.3ms | 716365 | 320 | 1.34784e+09 | 1.56206e+06 | 0.178675 | 3(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17614.4 | 0.0798341 | 3883.33ms | 716365 | 4890 | 4.68833e+06 | 38785.2 | 0.140467 | 1(Win) | true |
| Glaze | 4624.65 | 0.0656166 | 7787.19ms | 716365 | 2560 | 2.40535e+07 | 147725 | 0.0764348 | 2(Loss) | true |
| simdjson (reflection) | 437.453 | 0.118205 | 9921.34ms | 716365 | 320 | 1.09051e+09 | 1.56172e+06 | 0.0395105 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1585.52 | 0.491902 | 162.256ms | 2632 | 4890 | 296545 | 1583.12 | 0.0999202 | 1(Win) | true |
| Jsonifier (two-stage) | 1288.36 | 0.488501 | 196.34ms | 2632 | 4890 | 442933 | 1948.27 | 0.114333 | 2(Loss) | true |
| Glaze | 1238.93 | 0.26682 | 206.473ms | 2632 | 2560 | 74809.2 | 2026 | 0.00987069 | 3(Loss) | true |
| simdjson (reflection) | 1077.65 | 0.426295 | 232.294ms | 2632 | 2560 | 252392 | 2329.2 | 0.509191 | 4(Loss) | true |
| simdjson (ondemand) | 909.644 | 0.360084 | 280.073ms | 2632 | 2560 | 252742 | 2759.4 | 0.151976 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2100.13 | 1.50749 | 148.635ms | 2632 | 640 | 207764 | 1195.2 | 0.335796 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1879.58 | 0.530797 | 163.033ms | 2632 | 4890 | 245705 | 1335.44 | 0.235719 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1876.57 | 0.533502 | 164.586ms | 2632 | 4890 | 249015 | 1337.59 | 0.16518 | 2(Tie) | true |
| simdjson (reflection) | 1344.09 | 0.315562 | 216.879ms | 2632 | 4890 | 169822 | 1867.49 | 0.381166 | 4(Loss) | true |
| simdjson (ondemand) | 1210.58 | 0.436692 | 240.155ms | 2632 | 4890 | 400906 | 2073.44 | 0.962794 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10190.5 | 2.51039 | 27.21ms | 2632 | 4890 | 186970 | 246.315 | 1.27658 | 1(Win) | true |
| simdjson (reflection) | 7107.36 | 1.96115 | 37.801ms | 2632 | 4890 | 234578 | 353.165 | 1.16437 | 2(Loss) | true |
| Glaze | 3171.68 | 1.45458 | 83.466ms | 2632 | 1280 | 169620 | 791.4 | 0.126199 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11327 | 5.25604 | 25.3312ms | 2632 | 1280 | 173647 | 221.6 | 1.9469 | 1(Win) | true |
| simdjson (reflection) | 7570.86 | 2.07188 | 35.5889ms | 2632 | 4890 | 230739 | 331.544 | 1.42048 | 2(Loss) | true |
| Glaze | 3366.07 | 0.887591 | 77.14ms | 2632 | 4890 | 214220 | 745.698 | 0.586834 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1737.05 | 0.513009 | 189.091ms | 3370 | 2560 | 230636 | 1850.2 | 0.184102 | 1(Win) | true |
| Jsonifier | 1676.52 | 0.43684 | 196.564ms | 3370 | 1280 | 89763.5 | 1917 | 0.0938086 | 2(Loss) | true |
| Glaze | 1447.13 | 0.298374 | 224.329ms | 3370 | 4890 | 214722 | 2220.87 | 0.778937 | 3(Loss) | true |
| simdjson (reflection) | 1338.58 | 0.307488 | 243.27ms | 3370 | 4890 | 266522 | 2400.96 | 0.35462 | 4(Loss) | true |
| simdjson (ondemand) | 1132.37 | 0.235889 | 288.436ms | 3370 | 4890 | 219185 | 2838.2 | 0.0351451 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2194.98 | 0.964141 | 176.7ms | 3370 | 1280 | 255089 | 1464.2 | 0.367447 | 1(Win) | true |
| Glaze STATISTICAL TIE | 2132.05 | 0.494979 | 179.112ms | 3370 | 4890 | 272238 | 1507.42 | 0.171129 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 2119.42 | 0.969084 | 182.961ms | 3370 | 1280 | 276414 | 1516.4 | 1.7172 | 2(Tie) | true |
| simdjson (reflection) | 1648.48 | 0.453284 | 225.428ms | 3370 | 1280 | 99963.5 | 1949.6 | 0.469675 | 4(Loss) | true |
| simdjson (ondemand) | 1506.25 | 0.254003 | 243.572ms | 3370 | 4890 | 143632 | 2133.7 | 0.0655803 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10866.8 | 2.14762 | 33.899ms | 3643 | 4890 | 230537 | 319.712 | 0.601657 | 1(Win) | true |
| Glaze | 3943.43 | 0.616296 | 92.916ms | 3682 | 4890 | 147268 | 890.451 | 0.307802 | 2(Loss) | true |
| simdjson (reflection) | 375.317 | 0.346976 | 971.655ms | 3643 | 320 | 330119 | 9256.8 | 0.407844 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12925 | 3.27056 | 30.507ms | 3643 | 2560 | 197853 | 268.8 | 0.370645 | 1(Win) | true |
| Glaze | 4681.28 | 1.16858 | 78.4151ms | 3682 | 2560 | 196697 | 750.1 | 0.279181 | 2(Loss) | true |
| simdjson (reflection) | 364.573 | 0.192081 | 949.993ms | 3643 | 2560 | 857740 | 9529.6 | 0.0671141 | 3(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 818.77 | 0.194954 | 545.096ms | 4630 | 4890 | 540518 | 5392.86 | 0.208041 | 1(Win) | true |
| Jsonifier (two-stage) | 720.125 | 0.117408 | 617.48ms | 4630 | 4890 | 253424 | 6131.59 | 0.287744 | 2(Loss) | true |
| simdjson (reflection) | 595.939 | 0.15564 | 744.52ms | 4630 | 4890 | 650293 | 7409.34 | 0.0802538 | 3(Loss) | true |
| Glaze | 532.554 | 0.226138 | 834.806ms | 4630 | 1280 | 449980 | 8291.2 | 0.309717 | 4(Loss) | true |
| simdjson (ondemand) | 485.541 | 0.204921 | 920.025ms | 4630 | 1280 | 444522 | 9094 | 0.0131938 | 5(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1031.98 | 0.236886 | 540.504ms | 4630 | 2560 | 262992 | 4278.7 | 0.0210389 | 1(Win) | true |
| Jsonifier (two-stage) | 881.973 | 0.319782 | 616.536ms | 4630 | 160 | 41008.9 | 5006.4 | 0.224215 | 2(Loss) | true |
| simdjson (reflection) | 711.262 | 0.753479 | 839.755ms | 4630 | 80 | 175039 | 6208 | 0.308325 | 3(Loss) | true |
| simdjson (ondemand) | 551.939 | 0.22188 | 914.95ms | 4630 | 40 | 12603.1 | 8000 | 0.0533049 | 4(Loss) | true |
| Glaze | 545.206 | 0.20643 | 924.328ms | 4630 | 640 | 178883 | 8098.8 | 0.0642483 | 5(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Glaze | 1735.92 | 0.338069 | 256.143ms | 4630 | 4890 | 361594 | 2543.61 | 0.0831755 | 1(Win) | true |
| simdjson (reflection) | 947.634 | 0.213755 | 471.688ms | 4630 | 4890 | 485092 | 4659.51 | 0.282242 | 2(Loss) | true |
| Jsonifier | 842.655 | 0.984547 | 533.242ms | 4630 | 320 | 851698 | 5240 | 0.183542 | 3(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Glaze | 1999.33 | 0.390447 | 223.943ms | 4630 | 2560 | 190353 | 2208.5 | 0.973007 | 1(Win) | true |
| simdjson (reflection) | 958.061 | 0.47048 | 468.355ms | 4630 | 640 | 300911 | 4608.8 | 0.225147 | 2(Loss) | true |
| Jsonifier | 844.008 | 0.312826 | 527.572ms | 4630 | 1280 | 342834 | 5231.6 | 0.360651 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1692.51 | 0.196294 | 657.917ms | 11579 | 2560 | 419889 | 6524.4 | 0.101261 | 1(Win) | true |
| Jsonifier (two-stage) | 1550.97 | 0.188879 | 716.709ms | 11579 | 2560 | 462958 | 7119.8 | 0.106631 | 2(Loss) | true |
| simdjson (reflection) | 1250.18 | 0.337822 | 879.373ms | 11579 | 1280 | 1.13968e+06 | 8832.8 | 0.978599 | 3(Loss) | true |
| Glaze | 1090.56 | 0.137417 | 1026.31ms | 11579 | 1280 | 247817 | 10125.6 | 0.0394882 | 4(Loss) | true |
| simdjson (ondemand) | 984.186 | 0.258866 | 1119.94ms | 11579 | 4890 | 4.12521e+06 | 11220 | 0.544161 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2034.98 | 0.419732 | 657.947ms | 11579 | 640 | 332007 | 5426.4 | 0.0294768 | 1(Win) | true |
| Jsonifier (two-stage) | 1845.35 | 0.334985 | 727.807ms | 11579 | 80 | 32145.8 | 5984 | 0 | 2(Loss) | true |
| simdjson (reflection) | 1584.67 | 0.144016 | 814.008ms | 11579 | 1280 | 128913 | 6968.4 | 0.0631023 | 3(Loss) | true |
| Glaze | 1211.14 | 0.151355 | 1021.92ms | 11579 | 4890 | 931223 | 9117.53 | 0.130059 | 4(Loss) | true |
| simdjson (ondemand) | 1131 | 0.364962 | 1106.12ms | 11579 | 4890 | 6.20904e+06 | 9763.6 | 1.09757 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7679.38 | 0.329333 | 188.591ms | 14795 | 4890 | 179043 | 1837.34 | 0.328925 | 1(Win) | true |
| Glaze | 3292.48 | 0.301982 | 433.825ms | 14795 | 2560 | 428730 | 4285.4 | 0.676596 | 2(Loss) | true |
| simdjson (reflection) | 298.949 | 0.0683996 | 4790.37ms | 14795 | 4890 | 5.09628e+06 | 47197.4 | 0.0431308 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7873.67 | 0.482464 | 182.837ms | 14795 | 2560 | 191358 | 1792 | 0.425913 | 1(Win) | true |
| Glaze | 3730.33 | 0.44345 | 386.481ms | 14795 | 640 | 180055 | 3782.4 | 0.295234 | 2(Loss) | true |
| simdjson (reflection) | 299.707 | 0.100405 | 4746.32ms | 14795 | 1280 | 2.85995e+06 | 47078 | 0.195039 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1302.61 | 0.381306 | 239.897ms | 3223 | 4890 | 395869 | 2359.65 | 0.474767 | 1(Win) | true |
| Jsonifier (two-stage) | 1043.37 | 0.168552 | 298.573ms | 3223 | 4890 | 120566 | 2945.94 | 0.114027 | 2(Loss) | true |
| Glaze | 936.873 | 0.425692 | 331.152ms | 3223 | 1280 | 249666 | 3280.8 | 0.170399 | 3(Loss) | true |
| simdjson (reflection) | 869.995 | 0.431298 | 357.848ms | 3223 | 1280 | 297202 | 3533 | 0.00566059 | 4(Loss) | true |
| simdjson (ondemand) | 858.305 | 0.271262 | 361.305ms | 3223 | 4890 | 461451 | 3581.12 | 1.03848 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1870.1 | 1.17665 | 220.56ms | 3223 | 640 | 239369 | 1643.6 | 0.508475 | 1(Win) | true |
| Jsonifier (two-stage) | 1381.93 | 0.432759 | 282.448ms | 3223 | 2560 | 237181 | 2224.2 | 0.0808625 | 2(Loss) | true |
| Glaze | 1224.19 | 0.304246 | 304.516ms | 3223 | 4890 | 285352 | 2510.79 | 0.255126 | 3(Loss) | true |
| simdjson (ondemand) | 1098.22 | 0.47096 | 358.938ms | 3223 | 1280 | 222393 | 2798.8 | 0.540156 | 4(Loss) | true |
| simdjson (reflection) | 1083.09 | 0.464773 | 337.398ms | 3223 | 2560 | 445365 | 2837.9 | 0.878004 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9083.02 | 3.92696 | 36.375ms | 3223 | 1280 | 226040 | 338.4 | 1.31737 | 1(Win) | true |
| simdjson (reflection) | 7772.35 | 1.79259 | 42.0652ms | 3223 | 4890 | 245746 | 395.465 | 1.7234 | 2(Loss) | true |
| Glaze | 1966.85 | 0.469852 | 160.648ms | 3223 | 4890 | 263640 | 1562.75 | 0.493363 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10007.2 | 2.15659 | 33.5931ms | 3223 | 4890 | 214554 | 307.148 | 0.85615 | 1(Win) | true |
| simdjson (reflection) | 8379.75 | 3.6924 | 39.159ms | 3223 | 1280 | 234793 | 366.8 | 1.21413 | 2(Loss) | true |
| Glaze | 2201.15 | 1.39816 | 143.912ms | 3223 | 640 | 243959 | 1396.4 | 1.10482 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1822.15 | 0.26795 | 312.47ms | 5839 | 1280 | 85827.1 | 3056 | 0.261097 | 1(Win) | true |
| Jsonifier (two-stage) | 1676.45 | 0.825751 | 338.882ms | 5839 | 320 | 240737 | 3321.6 | 0.096432 | 2(Loss) | true |
| simdjson (reflection) | 1459.84 | 0.180617 | 385.868ms | 5839 | 4890 | 232108 | 3814.45 | 0.812535 | 3(Loss) | true |
| simdjson (ondemand) | 1439.36 | 0.228555 | 390.874ms | 5839 | 4890 | 382323 | 3868.74 | 0.732787 | 4(Loss) | true |
| Glaze | 1372.09 | 0.368354 | 416.523ms | 5839 | 320 | 71513.7 | 4058.4 | 0.41225 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2336.61 | 0.360787 | 297.143ms | 5839 | 4890 | 361507 | 2383.16 | 0.589052 | 1(Win) | true |
| Jsonifier (two-stage) | 2170.45 | 0.437027 | 320.764ms | 5839 | 2560 | 321835 | 2565.6 | 0.341827 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1808.07 | 0.297692 | 363.052ms | 5839 | 1280 | 107594 | 3079.8 | 0.293083 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1787.53 | 0.837758 | 367.771ms | 5839 | 320 | 217951 | 3115.2 | 0.0513347 | 3(Tie) | true |
| Glaze | 1677.46 | 0.446525 | 389.86ms | 5839 | 1280 | 281237 | 3319.6 | 0.408016 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17158.2 | 1.81318 | 41.547ms | 6938 | 4890 | 239065 | 385.623 | 0.587032 | 1(Win) | true |
| Glaze | 2689.45 | 1.18918 | 252.9ms | 6960 | 320 | 275636 | 2468 | 0.0324044 | 2(Loss) | true |
| simdjson (reflection) | 345.207 | 0.0846816 | 1978.54ms | 6938 | 4890 | 1.28824e+06 | 19167 | 0.523573 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17839.3 | 2.58505 | 39.1859ms | 6938 | 2560 | 235338 | 370.9 | 0.0269542 | 1(Win) | true |
| Glaze | 2839.28 | 0.35261 | 236.171ms | 6960 | 4890 | 332277 | 2337.77 | 1.25024 | 2(Loss) | true |
| simdjson (reflection) | 346.259 | 0.23539 | 1928.28ms | 6938 | 320 | 647427 | 19108.8 | 0.0418831 | 3(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1713.33 | 0.421313 | 275.143ms | 4857 | 2560 | 332126 | 2703.5 | 0.263314 | 1(Win) | true |
| Jsonifier (two-stage) | 1326.8 | 0.314156 | 354.631ms | 4857 | 2560 | 307931 | 3491.1 | 0.424986 | 2(Loss) | true |
| Glaze | 1291.54 | 0.432704 | 364.167ms | 4857 | 1280 | 308254 | 3586.4 | 0.686752 | 3(Loss) | true |
| simdjson (reflection) | 1051.1 | 0.232966 | 443.313ms | 4857 | 4890 | 515398 | 4406.81 | 0.843501 | 4(Loss) | true |
| simdjson (ondemand) | 935.913 | 0.182068 | 498.68ms | 4857 | 4890 | 397045 | 4949.18 | 0.0642191 | 5(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2457.55 | 1.00055 | 239.108ms | 4857 | 320 | 113805 | 1884.8 | 0.254022 | 1(Win) | true |
| Glaze | 2077.25 | 0.298647 | 266.248ms | 4857 | 4890 | 216862 | 2229.87 | 0.349916 | 2(Loss) | true |
| Jsonifier (two-stage) | 1738.28 | 0.29758 | 318.775ms | 4857 | 4890 | 307479 | 2664.7 | 0.026132 | 3(Loss) | true |
| simdjson (reflection) | 1276.52 | 0.212491 | 409.426ms | 4857 | 4890 | 290717 | 3628.6 | 0.085607 | 4(Loss) | true |
| simdjson (ondemand) | 1145.51 | 0.61763 | 436.45ms | 4857 | 640 | 399184 | 4043.6 | 0.30572 | 5(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12314.3 | 1.87399 | 39.348ms | 4857 | 4890 | 242974 | 376.147 | 1.3874 | 1(Win) | true |
| simdjson (reflection) | 9224.18 | 1.44385 | 52.6369ms | 4857 | 4890 | 257061 | 502.158 | 0.532107 | 2(Loss) | true |
| Glaze | 2776.31 | 0.878271 | 170.332ms | 4857 | 1280 | 274832 | 1668.4 | 0.855717 | 3(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14140.7 | 2.05743 | 35.3211ms | 4857 | 4890 | 222102 | 327.565 | 0.0197943 | 1(Win) | true |
| simdjson (reflection) | 10185.1 | 1.57385 | 48.4091ms | 4857 | 4890 | 250518 | 454.78 | 0.833068 | 2(Loss) | true |
| Glaze | 2583.38 | 0.773831 | 187.467ms | 4857 | 1280 | 246412 | 1793 | 0.0334523 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1820.04 | 0.277226 | 354.613ms | 6701 | 4890 | 463335 | 3511.23 | 0.649904 | 1(Win) | true |
| Jsonifier (two-stage) | 1700.3 | 0.255659 | 381.771ms | 6701 | 2560 | 236368 | 3758.5 | 0.0346002 | 2(Loss) | true |
| Glaze | 1556.25 | 0.617795 | 418.971ms | 6701 | 320 | 205950 | 4106.4 | 0.175644 | 3(Loss) | true |
| simdjson (reflection) | 1388.94 | 0.255349 | 463.306ms | 6701 | 4890 | 674976 | 4601.04 | 0.1706 | 4(Loss) | true |
| simdjson (ondemand) | 1251.75 | 0.157641 | 518.033ms | 6701 | 2560 | 165813 | 5105.3 | 0.0685092 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2407.54 | 0.378384 | 316.897ms | 6701 | 2560 | 258249 | 2654.4 | 0.166038 | 1(Win) | true |
| Glaze | 2306.23 | 0.356938 | 322.819ms | 6701 | 2560 | 250438 | 2771 | 0.0577742 | 2(Loss) | true |
| Jsonifier (two-stage) | 2184.19 | 0.231817 | 343.966ms | 6701 | 4890 | 224957 | 2925.83 | 0.420872 | 3(Loss) | true |
| simdjson (reflection) | 1663.44 | 0.166766 | 429.105ms | 6701 | 4890 | 200720 | 3841.78 | 0.578055 | 4(Loss) | true |
| simdjson (ondemand) | 1557.92 | 0.273636 | 455.039ms | 6701 | 1280 | 161268 | 4102 | 0.0682128 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14286.7 | 1.49759 | 52.2081ms | 7376 | 4890 | 265874 | 492.368 | 0.772249 | 1(Win) | true |
| Glaze | 2465.57 | 0.230681 | 290.247ms | 7376 | 4890 | 211806 | 2853.01 | 0.383636 | 2(Loss) | true |
| simdjson (reflection) | 357.339 | 0.095219 | 2036.89ms | 7376 | 4890 | 1.71806e+06 | 19685.2 | 0.0530661 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15078.7 | 1.53748 | 49.5199ms | 7376 | 4890 | 251562 | 466.506 | 1.31027 | 1(Win) | true |
| Glaze | 2658.93 | 0.288971 | 268.362ms | 7376 | 4890 | 285790 | 2645.54 | 0.55846 | 2(Loss) | true |
| simdjson (reflection) | 361.668 | 0.404007 | 1972.34ms | 7376 | 40 | 246978 | 19449.6 | 0.274967 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1541.3 | 0.319038 | 107.676ms | 1691 | 4890 | 54489 | 1046.3 | 0.383943 | 1(Win) | true |
| Glaze | 1419.47 | 0.6867 | 118.168ms | 1691 | 2560 | 155814 | 1136.1 | 0.167519 | 2(Loss) | true |
| Jsonifier (two-stage) | 1305.82 | 0.515075 | 128.156ms | 1691 | 4890 | 197865 | 1234.98 | 0.217277 | 3(Loss) | true |
| simdjson (ondemand) | 1183.96 | 0.558902 | 138.759ms | 1691 | 4890 | 283393 | 1362.09 | 0.671806 | 4(Loss) | true |
| simdjson (reflection) | 1149.52 | 0.734267 | 144.387ms | 1691 | 2560 | 271645 | 1402.9 | 0.489431 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2284.18 | 0.950079 | 95.456ms | 1691 | 4890 | 220017 | 706.016 | 1.25657 | 1(Win) | true |
| Glaze | 1927.64 | 1.25622 | 105.274ms | 1691 | 1280 | 141376 | 836.6 | 0.876777 | 2(Loss) | true |
| Jsonifier (two-stage) | 1551.83 | 1.56477 | 115.762ms | 1691 | 320 | 84615.8 | 1039.2 | 2.60664 | 3(Loss) | true |
| simdjson (ondemand) | 1454.34 | 0.438829 | 127.765ms | 1691 | 4890 | 115786 | 1108.86 | 2.33132 | 4(Loss) | true |
| simdjson (reflection) | 1376.98 | 0.489336 | 140.172ms | 1691 | 4890 | 160604 | 1171.16 | 0.433988 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11699 | 3.3068 | 18.6921ms | 1996 | 4890 | 141563 | 162.709 | 0.300734 | 1(Win) | true |
| simdjson (reflection) | 10277.1 | 3.00941 | 21.985ms | 1996 | 4890 | 151932 | 185.22 | 0.150701 | 2(Loss) | true |
| Glaze | 3191.71 | 1.66441 | 62.5149ms | 1996 | 2560 | 252252 | 596.4 | 1.77474 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14744.7 | 3.74836 | 15.0851ms | 1996 | 4890 | 114509 | 129.099 | 4.78846 | 1(Win) | true |
| simdjson (reflection) | 11599.8 | 4.47688 | 18.357ms | 1996 | 2560 | 138168 | 164.1 | 0.905797 | 2(Loss) | true |
| Glaze | 3797.95 | 3.96618 | 53.1049ms | 1996 | 640 | 252899 | 501.2 | 0.397456 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1693.02 | 1.32484 | 126.061ms | 2158 | 640 | 165994 | 1215.6 | 0.496032 | 1(Win) | true |
| Glaze | 1594.66 | 0.541949 | 132.366ms | 2158 | 4890 | 239217 | 1290.58 | 0.410907 | 2(Loss) | true |
| Jsonifier (two-stage) | 1547.39 | 1.02485 | 136.983ms | 2158 | 1280 | 237814 | 1330 | 0.635593 | 3(Loss) | true |
| simdjson (ondemand) | 1476.05 | 0.533974 | 143.446ms | 2158 | 4890 | 271051 | 1394.28 | 0.423786 | 4(Loss) | true |
| simdjson (reflection) | 1404.29 | 0.511157 | 160.919ms | 2158 | 4890 | 274416 | 1465.53 | 0.445991 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2313.43 | 2.03763 | 111.543ms | 2158 | 320 | 105145 | 889.6 | 0.724638 | 1(Win) | true |
| Glaze | 2142.44 | 0.607425 | 118.955ms | 2158 | 1280 | 43579.3 | 960.6 | 0.020816 | 2(Loss) | true |
| Jsonifier (two-stage) | 2031.42 | 0.30339 | 124.495ms | 2158 | 2560 | 24185 | 1013.1 | 0.326797 | 3(Loss) | true |
| simdjson (reflection) | 1675.04 | 0.519996 | 145.961ms | 2158 | 4890 | 199600 | 1228.64 | 0.420347 | 4(Loss) | true |
| simdjson (ondemand) | 1594.73 | 0.524235 | 148.974ms | 2158 | 4890 | 223816 | 1290.52 | 0.736659 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13909.6 | 4.0729 | 21.1579ms | 2866 | 2560 | 163973 | 196.5 | 3.63924 | 1(Win) | true |
| Glaze | 2978.02 | 0.98334 | 95.5832ms | 2866 | 1280 | 104259 | 917.8 | 0.109075 | 2(Loss) | true |
| simdjson (reflection) | 395.702 | 0.141404 | 697.023ms | 2866 | 2560 | 244221 | 6907.3 | 0.1691 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17114.8 | 4.54863 | 18.7912ms | 2866 | 2560 | 135086 | 159.7 | 1.17574 | 1(Win) | true |
| Glaze | 3420.85 | 0.881999 | 83.348ms | 2866 | 4890 | 242846 | 798.992 | 0.16341 | 2(Loss) | true |
| simdjson (reflection) | 396.39 | 0.201694 | 696.138ms | 2866 | 2560 | 495147 | 6895.3 | 0.447222 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1795.91 | 0.419921 | 237.349ms | 4390 | 2560 | 245321 | 2331.2 | 0.275292 | 1(Win) | true |
| Jsonifier (two-stage) | 1271.95 | 0.31973 | 335.038ms | 4390 | 2560 | 283527 | 3291.5 | 0.0577578 | 2(Loss) | true |
| Glaze | 1040.11 | 0.208973 | 403.96ms | 4390 | 4890 | 345986 | 4025.17 | 0.253554 | 3(Loss) | true |
| simdjson (reflection) | 874.693 | 0.359572 | 482.152ms | 4390 | 2560 | 758281 | 4786.4 | 0.863995 | 4(Loss) | true |
| simdjson (ondemand) | 780.738 | 0.437092 | 539.889ms | 4390 | 640 | 351596 | 5362.4 | 0.23927 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2251.31 | 0.373815 | 225.112ms | 4390 | 4890 | 236308 | 1859.64 | 0.244692 | 1(Win) | true |
| Jsonifier (two-stage) | 1490.47 | 0.303184 | 324.705ms | 4390 | 4890 | 354654 | 2808.93 | 0.85304 | 2(Loss) | true |
| Glaze | 1231.94 | 0.903293 | 386.212ms | 4390 | 320 | 301548 | 3398.4 | 0.328484 | 3(Loss) | true |
| simdjson (reflection) | 995.372 | 0.509988 | 479.144ms | 4390 | 4890 | 2.25003e+06 | 4206.1 | 3.04291 | 4(Loss) | true |
| simdjson (ondemand) | 776.661 | 0.338096 | 587.448ms | 4390 | 4890 | 1.62426e+06 | 5390.55 | 2.17703 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10035.1 | 4.69797 | 46.7341ms | 4390 | 640 | 245861 | 417.2 | 2.85996 | 1(Win) | true |
| simdjson (reflection) | 8338.24 | 1.97875 | 53.6069ms | 4390 | 2560 | 252698 | 502.1 | 0.139609 | 2(Loss) | true |
| Glaze | 1607.89 | 1.55935 | 264.254ms | 4390 | 1280 | 2.11014e+06 | 2603.8 | 1.0635 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11382.9 | 3.68101 | 39.433ms | 4390 | 1280 | 234622 | 367.8 | 0.27115 | 1(Win) | true |
| simdjson (reflection) | 8762.31 | 2.11129 | 51.3549ms | 4390 | 2560 | 260513 | 477.8 | 0.674252 | 2(Loss) | true |
| Glaze | 1599.29 | 0.724423 | 250.525ms | 4390 | 1280 | 460328 | 2617.8 | 0.375767 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2489.02 | 0.96226 | 356.706ms | 9378 | 640 | 765117 | 3593.2 | 0.144928 | 1(Win) | true |
| Jsonifier (two-stage) | 2323 | 0.449878 | 391.204ms | 9378 | 640 | 191995 | 3850 | 0.0103907 | 2(Loss) | true |
| simdjson (reflection) | 1847.84 | 0.440242 | 494.957ms | 9378 | 320 | 145286 | 4840 | 0 | 3(Loss) | true |
| Glaze | 1641.17 | 0.186906 | 549.798ms | 9378 | 4890 | 507303 | 5449.5 | 0.253911 | 4(Loss) | true |
| simdjson (ondemand) | 1501.14 | 0.0941092 | 603.896ms | 9378 | 4890 | 153727 | 5957.84 | 0.153558 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2907.62 | 0.298386 | 347.296ms | 9378 | 2560 | 215647 | 3075.9 | 0.644591 | 1(Win) | true |
| Jsonifier (two-stage) | 2668.13 | 1.08154 | 386.659ms | 9378 | 320 | 420578 | 3352 | 0.143403 | 2(Loss) | true |
| simdjson (reflection) | 2037.07 | 1.30011 | 487.945ms | 9378 | 80 | 260651 | 4390.4 | 0.290698 | 3(Loss) | true |
| Glaze | 1822.06 | 0.363745 | 528.753ms | 9378 | 2560 | 816079 | 4908.5 | 0.699573 | 4(Loss) | true |
| simdjson (ondemand) | 1681.53 | 0.216993 | 582.141ms | 9378 | 2560 | 340991 | 5318.7 | 0.239352 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 20995.8 | 1.42333 | 54.91ms | 11521 | 4890 | 271292 | 523.308 | 0.481562 | 1(Win) | true |
| Glaze | 2862.61 | 0.327161 | 392.382ms | 11521 | 1280 | 201831 | 3838.2 | 0.852449 | 2(Loss) | true |
| simdjson (reflection) | 333.026 | 0.0971393 | 3341.18ms | 11521 | 4890 | 5.02253e+06 | 32992.2 | 0.2922 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 21878.3 | 1.97866 | 52.7939ms | 11521 | 2560 | 252777 | 502.2 | 0.722022 | 1(Win) | true |
| Glaze | 3126.72 | 0.322936 | 353.05ms | 11521 | 2560 | 329667 | 3514 | 1.50789 | 2(Loss) | true |
| simdjson (reflection) | 334.639 | 0.255927 | 3291.27ms | 11521 | 640 | 4.51896e+06 | 32833.2 | 0.105878 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2791.84 | 0.633469 | 162.259ms | 4669 | 2560 | 261311 | 1594.9 | 0.281356 | 1(Win) | true |
| Jsonifier (two-stage) | 1732.44 | 0.395289 | 262.701ms | 4669 | 2560 | 264242 | 2570.2 | 0.472429 | 2(Loss) | true |
| Glaze | 1506.33 | 0.185525 | 301.05ms | 4669 | 2560 | 76993.3 | 2956 | 0.464678 | 3(Loss) | true |
| simdjson (reflection) | 1264.18 | 0.309784 | 357.938ms | 4669 | 2560 | 304780 | 3522.2 | 0.682382 | 4(Loss) | true |
| simdjson (ondemand) | 1166.12 | 0.550917 | 390.301ms | 4669 | 640 | 283214 | 3818.4 | 0.209952 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3148.85 | 0.595341 | 155.527ms | 4669 | 4890 | 346564 | 1414.07 | 0.975294 | 1(Win) | true |
| Jsonifier (two-stage) | 1850.36 | 0.446467 | 256.141ms | 4669 | 2560 | 295498 | 2406.4 | 0.492775 | 2(Loss) | true |
| Glaze | 1766.39 | 1.12895 | 270.444ms | 4669 | 320 | 259164 | 2520.8 | 0.849591 | 3(Loss) | true |
| simdjson (reflection) | 1344.36 | 0.221681 | 347.505ms | 4669 | 4890 | 263622 | 3312.14 | 0.273604 | 4(Loss) | true |
| simdjson (ondemand) | 1293.19 | 0.601693 | 396.089ms | 4669 | 640 | 274697 | 3443.2 | 0.116306 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14569 | 2.18553 | 33.238ms | 4669 | 4890 | 218179 | 305.629 | 1.15477 | 1(Win) | true |
| simdjson (reflection) | 8112.71 | 1.40557 | 57.15ms | 4669 | 4890 | 291027 | 548.856 | 0.0465956 | 2(Loss) | true |
| Glaze | 2017.35 | 0.550569 | 226.14ms | 4669 | 1280 | 189024 | 2207.2 | 0.473416 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16023.7 | 2.42449 | 30.2369ms | 4669 | 4890 | 221960 | 277.883 | 0.471695 | 1(Win) | true |
| simdjson (reflection) | 8699.36 | 1.41647 | 53.93ms | 4669 | 4890 | 257037 | 511.843 | 1.03493 | 2(Loss) | true |
| Glaze | 2106.29 | 0.440775 | 216.188ms | 4669 | 1280 | 111136 | 2114 | 0.207704 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2938.37 | 1.10171 | 265.752ms | 7932 | 320 | 257416 | 2574.4 | 0.0621118 | 1(Win) | true |
| Jsonifier (two-stage) | 2488.26 | 0.221172 | 309.309ms | 7932 | 2560 | 115738 | 3040.1 | 0.339956 | 2(Loss) | true |
| simdjson (reflection) | 1971.58 | 0.394809 | 390.998ms | 7932 | 640 | 146856 | 3836.8 | 0.166528 | 3(Loss) | true |
| Glaze | 1952.42 | 0.188227 | 391.677ms | 7932 | 4890 | 260072 | 3874.45 | 0.00380569 | 4(Loss) | true |
| simdjson (ondemand) | 1793.98 | 0.209629 | 425.438ms | 7932 | 4890 | 382069 | 4216.62 | 0.1251 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3108.95 | 0.314508 | 258.225ms | 7932 | 4890 | 286358 | 2433.15 | 0.194769 | 1(Win) | true |
| Jsonifier (two-stage) | 2666.76 | 0.297306 | 301.014ms | 7932 | 2560 | 182072 | 2836.6 | 0.727934 | 2(Loss) | true |
| Glaze | 2204.19 | 0.31612 | 358.555ms | 7932 | 2560 | 301310 | 3431.9 | 0.418422 | 3(Loss) | true |
| simdjson (reflection) | 2056.51 | 0.238085 | 383.555ms | 7932 | 4890 | 375038 | 3678.34 | 0.0200629 | 4(Loss) | true |
| simdjson (ondemand) | 2005.93 | 0.269874 | 392.264ms | 7932 | 2560 | 265155 | 3771.1 | 0.236564 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17280.6 | 1.54646 | 53.3809ms | 9249 | 4890 | 304688 | 510.429 | 0.539858 | 1(Win) | true |
| Glaze | 2393.5 | 0.250143 | 373.002ms | 9249 | 4890 | 415534 | 3685.2 | 0.340854 | 2(Loss) | true |
| simdjson (reflection) | 343.385 | 0.13012 | 2582.58ms | 9249 | 1280 | 1.42996e+06 | 25687 | 0.115878 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17567.3 | 1.97875 | 55.8052ms | 9249 | 2560 | 252698 | 502.1 | 0.29964 | 1(Win) | true |
| Glaze | 2596.49 | 0.314423 | 347.303ms | 9249 | 2560 | 292069 | 3397.1 | 0.239009 | 2(Loss) | true |
| simdjson (reflection) | 344.603 | 0.109061 | 2586.09ms | 9249 | 1280 | 997475 | 25596.2 | 0.292156 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 654.627 | 0.385893 | 676.528ms | 4604 | 640 | 428743 | 6707.2 | 0.142925 | 1(Win) | true |
| Jsonifier (two-stage) | 567.775 | 0.283973 | 832.382ms | 4604 | 640 | 308641 | 7733.2 | 0.0258558 | 2(Loss) | true |
| simdjson (reflection) | 522.804 | 0.282786 | 844.39ms | 4604 | 1280 | 721969 | 8398.4 | 0.14268 | 3(Loss) | true |
| Glaze | 450.038 | 0.121405 | 985.299ms | 4604 | 4890 | 686046 | 9756.32 | 0.0946157 | 4(Loss) | true |
| simdjson (ondemand) | 400.964 | 0.174213 | 1106.49ms | 4604 | 1280 | 465833 | 10950.4 | 0.0109597 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 839.83 | 0.200745 | 666.258ms | 4604 | 2560 | 281980 | 5228.1 | 0.189003 | 1(Win) | true |
| Jsonifier (two-stage) | 698.092 | 0.497729 | 765.927ms | 4604 | 320 | 313605 | 6289.6 | 0.0509035 | 2(Loss) | true |
| simdjson (reflection) | 631.721 | 0.310163 | 829.298ms | 4604 | 160 | 74356.6 | 6950.4 | 0.137931 | 3(Loss) | true |
| Glaze | 537.104 | 0.126232 | 961.978ms | 4604 | 2560 | 272604 | 8174.8 | 0.102861 | 4(Loss) | true |
| simdjson (ondemand) | 463.762 | 0.253934 | 1089.99ms | 4604 | 640 | 369915 | 9467.6 | 0.0211202 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1947.28 | 0.407264 | 230.137ms | 4604 | 2560 | 215878 | 2254.8 | 0.106553 | 1(Win) | true |
| simdjson (reflection) | 1688.57 | 0.85807 | 284.617ms | 4918 | 320 | 181775 | 2777.6 | 0.572738 | 2(Loss) | true |
| Glaze | 1084.98 | 0.549466 | 409.62ms | 4604 | 640 | 316435 | 4046.8 | 0.167752 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1961.02 | 0.419365 | 227.096ms | 4604 | 2560 | 225700 | 2239 | 0.250739 | 1(Win) | true |
| simdjson (reflection) | 1673.35 | 0.324547 | 281.148ms | 4918 | 4890 | 404638 | 2802.86 | 0.00926688 | 2(Loss) | true |
| Glaze | 1166.01 | 0.649586 | 385.768ms | 4604 | 320 | 191466 | 3765.6 | 0.0636943 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1885.95 | 0.226127 | 933.561ms | 18245 | 640 | 278556 | 9226 | 0.0477141 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 1798.09 | 0.787978 | 1032.5ms | 18245 | 40 | 232569 | 9676.8 | 0.0882613 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 1797.65 | 0.261072 | 984.245ms | 18245 | 640 | 408676 | 9679.2 | 0.207056 | 2(Tie) | true |
| simdjson (ondemand) | 1416.09 | 0.219568 | 1245.32ms | 18245 | 640 | 465828 | 12287.2 | 0 | 4(Loss) | true |
| Glaze | 1335.98 | 0.2457 | 1389.75ms | 18245 | 40 | 40960 | 13024 | 0.0491159 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2255.5 | 0.114482 | 917.04ms | 18245 | 4890 | 381403 | 7714.4 | 0.0842506 | 1(Win) | true |
| Jsonifier | 2103.05 | 0.220314 | 970.362ms | 18245 | 1280 | 425290 | 8273.6 | 0.197829 | 2(Loss) | true |
| simdjson (reflection) | 2088.29 | 0.231113 | 964.725ms | 18245 | 4890 | 1.81329e+06 | 8332.09 | 0.0515532 | 3(Loss) | true |
| simdjson (ondemand) | 1607.79 | 0.15244 | 1226.91ms | 18245 | 1280 | 348368 | 10822.2 | 0.101746 | 4(Loss) | true |
| Glaze | 1488.19 | 0.157829 | 1310.07ms | 18245 | 2560 | 871732 | 11691.9 | 0.0538544 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8733.37 | 0.996356 | 275.542ms | 24579 | 320 | 228846 | 2684 | 0.14881 | 1(Win) | true |
| Glaze | 3397.55 | 0.535846 | 717.161ms | 24579 | 80 | 109337 | 6899.2 | 0 | 2(Loss) | true |
| simdjson (reflection) | 325.781 | 0.441794 | 7790.95ms | 24893 | 40 | 4.14574e+06 | 72870.4 | 0.134487 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9022.8 | 0.305623 | 264.195ms | 24579 | 4890 | 308267 | 2597.9 | 0.0887139 | 1(Win) | true |
| Glaze | 3805.75 | 0.291225 | 625.474ms | 24579 | 640 | 205915 | 6159.2 | 0.194452 | 2(Loss) | true |
| simdjson (reflection) | 323.018 | 0.114224 | 7345.8ms | 24893 | 2560 | 1.80408e+07 | 73493.7 | 0.378466 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 700.711 | 0.159275 | 632.767ms | 4604 | 4890 | 487075 | 6266.08 | 0.0316766 | 1(Win) | true |
| Jsonifier (two-stage) | 592.683 | 0.324588 | 739.932ms | 4604 | 1280 | 740117 | 7408.2 | 0.469242 | 2(Loss) | true |
| simdjson (reflection) | 515.632 | 0.151904 | 845.445ms | 4604 | 4890 | 818159 | 8515.22 | 0.336849 | 3(Loss) | true |
| Glaze | 444.801 | 0.293272 | 1013.02ms | 4604 | 1280 | 1.07274e+06 | 9871.2 | 0.27631 | 4(Loss) | true |
| simdjson (ondemand) | 398.537 | 0.14886 | 1109.01ms | 4604 | 2560 | 688545 | 11017.1 | 0.432897 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 912.757 | 0.181023 | 610.968ms | 4604 | 4890 | 370797 | 4810.39 | 0.669509 | 1(Win) | true |
| Jsonifier (two-stage) | 747.343 | 0.240462 | 723.235ms | 4604 | 2560 | 510932 | 5875.1 | 0.148302 | 2(Loss) | true |
| simdjson (reflection) | 633.911 | 0.126043 | 826.889ms | 4604 | 4890 | 372700 | 6926.4 | 0.116854 | 3(Loss) | true |
| Glaze | 533.735 | 0.254277 | 968.908ms | 4604 | 640 | 280035 | 8226.4 | 0.397133 | 4(Loss) | true |
| simdjson (ondemand) | 463.625 | 0.393576 | 1092.03ms | 4604 | 320 | 444574 | 9470.4 | 0.454087 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1952.21 | 0.412149 | 230.315ms | 4604 | 2560 | 219971 | 2249.1 | 0.111032 | 1(Win) | true |
| simdjson (reflection) | 1709.59 | 0.262931 | 280.63ms | 4918 | 4890 | 254438 | 2743.44 | 0.765373 | 2(Loss) | true |
| Glaze | 1094.18 | 0.436227 | 415.564ms | 4604 | 80 | 24513.8 | 4012.8 | 0.317965 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1978.85 | 0.314711 | 225.197ms | 4604 | 4890 | 238440 | 2218.82 | 0.208821 | 1(Win) | true |
| simdjson (reflection) | 1719.08 | 0.35714 | 276.868ms | 4918 | 2560 | 243053 | 2728.3 | 0.586649 | 2(Loss) | true |
| Glaze | 1164.63 | 0.201495 | 403.713ms | 4604 | 4890 | 282184 | 3770.06 | 0.717517 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1986.01 | 0.241822 | 887.49ms | 18245 | 640 | 287276 | 8761.2 | 0.35279 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1971.51 | 0.472854 | 897.386ms | 18245 | 80 | 139326 | 8825.6 | 0 | 1(Tie) | true |
| simdjson (reflection) | 1805.58 | 0.136038 | 976.448ms | 18245 | 2560 | 439964 | 9636.7 | 0.201943 | 3(Loss) | true |
| simdjson (ondemand) | 1410.81 | 0.22462 | 1298.46ms | 18245 | 640 | 491166 | 12333.2 | 1.66167 | 4(Loss) | true |
| Glaze | 1335.32 | 0.317348 | 1326.16ms | 18245 | 30 | 51298.9 | 13030.4 | 0 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2390.87 | 0.305504 | 869.961ms | 18245 | 640 | 316367 | 7277.6 | 0.0990317 | 1(Win) | true |
| Jsonifier | 2362.31 | 0.152234 | 874.188ms | 18245 | 4890 | 614815 | 7365.58 | 0.131853 | 2(Loss) | true |
| simdjson (reflection) | 2097.98 | 0.312109 | 961.521ms | 18245 | 640 | 428824 | 8293.6 | 0.202156 | 3(Loss) | true |
| simdjson (ondemand) | 1603.49 | 0.116294 | 1225.77ms | 18245 | 4890 | 778719 | 10851.2 | 0.192175 | 4(Loss) | true |
| Glaze | 1489.61 | 0.237968 | 1309.89ms | 18245 | 640 | 494494 | 11680.8 | 0.150448 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8981.67 | 0.399038 | 264.151ms | 24579 | 2560 | 277641 | 2609.8 | 0.184261 | 1(Win) | true |
| Glaze | 3331.11 | 0.342414 | 721.446ms | 24579 | 80 | 46445.5 | 7036.8 | 0.136612 | 2(Loss) | true |
| simdjson (reflection) | 324.328 | 0.0716709 | 7410.42ms | 24893 | 2560 | 7.04548e+06 | 73196.9 | 0.313372 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9443.76 | 0.308859 | 253.605ms | 24579 | 4890 | 287388 | 2482.1 | 0.00405373 | 1(Win) | true |
| Glaze | 3814.68 | 0.128717 | 621.246ms | 24579 | 4890 | 305910 | 6144.79 | 0.197063 | 2(Loss) | true |
| simdjson (reflection) | 324.194 | 0.0768748 | 7396.74ms | 24893 | 2560 | 8.11243e+06 | 73227.1 | 0.0411219 | 3(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1271.73 | 0.347276 | 387.724ms | 5094 | 1280 | 225261 | 3820 | 0.209864 | 1(Win) | true |
| Jsonifier (two-stage) | 1129.99 | 0.272739 | 434.032ms | 5094 | 4890 | 672314 | 4299.18 | 0.0413528 | 2(Loss) | true |
| simdjson (reflection) | 838.717 | 0.231146 | 587.711ms | 5094 | 1280 | 229440 | 5792.2 | 0.0448678 | 3(Loss) | true |
| Glaze | 821.637 | 0.150091 | 597.834ms | 5094 | 4890 | 385104 | 5912.61 | 0.561633 | 4(Loss) | true |
| simdjson (ondemand) | 752.225 | 0.258921 | 657.565ms | 5094 | 1280 | 357904 | 6458.2 | 0.24525 | 5(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1667.02 | 0.350528 | 384.148ms | 5094 | 1280 | 133565 | 2914.2 | 0.0343265 | 1(Win) | true |
| Jsonifier (two-stage) | 1474 | 0.226717 | 428.642ms | 5094 | 4890 | 273024 | 3295.8 | 0.0393169 | 2(Loss) | true |
| Glaze | 1075.73 | 0.361635 | 557.599ms | 5094 | 1280 | 341396 | 4516 | 0.106402 | 3(Loss) | true |
| simdjson (reflection) | 1001.74 | 0.262359 | 580.967ms | 5094 | 1280 | 207212 | 4849.6 | 0.10734 | 4(Loss) | true |
| simdjson (ondemand) | 950.056 | 0.208391 | 610.444ms | 5094 | 2560 | 290681 | 5113.4 | 0.0742594 | 5(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12618.4 | 1.81553 | 41.8051ms | 5094 | 4890 | 238906 | 384.995 | 0.51817 | 1(Win) | true |
| simdjson (reflection) | 9627.11 | 1.42478 | 54.2021ms | 5094 | 4890 | 252773 | 504.618 | 1.51866 | 2(Loss) | true |
| Glaze | 2231.69 | 0.280867 | 218.355ms | 5094 | 4890 | 182794 | 2176.84 | 0.309689 | 3(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12523.9 | 2.57635 | 44.3558ms | 5094 | 2560 | 255675 | 387.9 | 2.39054 | 1(Win) | true |
| simdjson (reflection) | 9959.03 | 2.09977 | 50.923ms | 5094 | 2560 | 268575 | 487.8 | 0.163733 | 2(Loss) | true |
| Glaze | 2549.34 | 0.896887 | 200.29ms | 5094 | 320 | 93473.5 | 1905.6 | 0.334728 | 3(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1605.13 | 0.181585 | 482.738ms | 8051 | 4890 | 368935 | 4783.43 | 0.176743 | 1(Win) | true |
| Jsonifier (two-stage) | 1413.48 | 0.730574 | 616.598ms | 8051 | 160 | 251981 | 5432 | 0.322959 | 2(Loss) | true |
| Glaze | 1192.17 | 0.345462 | 652.247ms | 8051 | 640 | 316815 | 6440.4 | 0.598839 | 3(Loss) | true |
| simdjson (reflection) | 1126.6 | 0.142104 | 687.932ms | 8051 | 4890 | 458653 | 6815.25 | 0.357149 | 4(Loss) | true |
| simdjson (ondemand) | 1008.36 | 0.341176 | 769.096ms | 8051 | 4890 | 3.30013e+06 | 7614.35 | 1.15513 | 5(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1942.57 | 0.177744 | 480.588ms | 8051 | 4890 | 241348 | 3952.5 | 0.0836596 | 1(Win) | true |
| Jsonifier (two-stage) | 1630.02 | 1.2905 | 612.734ms | 8051 | 160 | 591225 | 4710.4 | 1.07527 | 2(Loss) | true |
| Glaze | 1487.39 | 0.13474 | 621.013ms | 8051 | 4890 | 236565 | 5162.09 | 0.345737 | 3(Loss) | true |
| simdjson (reflection) | 1462.35 | 0.181653 | 624.087ms | 8051 | 4890 | 444825 | 5250.46 | 0.285623 | 4(Loss) | true |
| simdjson (ondemand) | 1238.32 | 0.324036 | 717.642ms | 8051 | 4890 | 1.97393e+06 | 6200.38 | 1.30517 | 5(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15061.9 | 3.34769 | 66.4991ms | 9255 | 640 | 246301 | 586 | 1.28032 | 1(Win) | true |
| Glaze | 2548 | 0.665408 | 349.558ms | 9255 | 640 | 340026 | 3464 | 0.324374 | 2(Loss) | true |
| simdjson (reflection) | 345.976 | 0.146456 | 2560.64ms | 9255 | 1280 | 1.78684e+06 | 25511.2 | 0.021956 | 3(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16517.6 | 1.34417 | 56.4521ms | 9255 | 4890 | 252274 | 534.354 | 0.474168 | 1(Win) | true |
| Glaze | 2970.16 | 0.147594 | 304.578ms | 9255 | 4890 | 94067.9 | 2971.64 | 0.0620149 | 2(Loss) | true |
| simdjson (reflection) | 345.102 | 0.0834607 | 2564.41ms | 9255 | 4890 | 2.22808e+06 | 25575.8 | 0.112581 | 3(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 3975.52 | 0.98909 | 72.4012ms | 2889 | 4890 | 229767 | 693.032 | 1.16482 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 3966.23 | 0.983462 | 72.076ms | 2889 | 4890 | 228225 | 694.655 | 0.135823 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3757.21 | 1.23165 | 76.7209ms | 2889 | 2560 | 208823 | 733.3 | 0.258433 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 3746.56 | 0.876434 | 76.927ms | 2889 | 4890 | 203131 | 735.385 | 0.0251451 | 3(Tie) | true |
| Glaze | 2628.97 | 0.721633 | 107.991ms | 2889 | 1280 | 73209.2 | 1048 | 0.493733 | 5(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 4302.93 | 1.49421 | 69.505ms | 2889 | 2560 | 234331 | 640.3 | 0.202618 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 4255.52 | 1.09099 | 69.802ms | 2889 | 4890 | 243972 | 647.434 | 0.392921 | 1(Tie) | true |
| simdjson (ondemand) | 3988.37 | 1.88542 | 74.2111ms | 2889 | 1280 | 217135 | 690.8 | 1.53934 | 3(Loss) | true |
| simdjson (reflection) | 3800.68 | 1.21051 | 75.3349ms | 2889 | 4890 | 376547 | 724.915 | 0.640639 | 4(Loss) | true |
| Glaze | 2659.43 | 0.479074 | 108.271ms | 2889 | 2560 | 63061.4 | 1036 | 0.115964 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 4423.77 | 0.69063 | 85.856ms | 3808 | 4890 | 157184 | 820.928 | 0.925946 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 4392.95 | 0.675982 | 85.9799ms | 3808 | 4890 | 152708 | 826.686 | 0.507125 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4367.52 | 0.905082 | 86.049ms | 3808 | 2560 | 144991 | 831.5 | 0.471242 | 1(Tie) | true |
| Jsonifier (two-stage) | 4314 | 0.714339 | 86.1079ms | 3808 | 4890 | 176828 | 841.816 | 1.33814 | 4(Loss) | true |
| Glaze | 2790.74 | 0.754622 | 133.146ms | 3808 | 2560 | 246862 | 1301.3 | 0.875969 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 4624.46 | 1.12927 | 83.765ms | 3808 | 2560 | 201328 | 785.3 | 0.731144 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 4595.5 | 0.810577 | 84.0151ms | 3808 | 4890 | 200644 | 790.249 | 0.0190424 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 4547.6 | 0.739856 | 85.087ms | 3808 | 4890 | 170700 | 798.573 | 0.335898 | 1(Tie) | true |
| Jsonifier (two-stage) | 4484.1 | 0.721892 | 85.3199ms | 3808 | 4890 | 167146 | 809.881 | 1.94882 | 4(Loss) | true |
| Glaze | 3126.37 | 2.6927 | 121.405ms | 3808 | 160 | 156534 | 1161.6 | 0 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2338.45 | 0.689935 | 121.819ms | 2889 | 2560 | 169159 | 1178.2 | 0.460437 | 1(Win) | true |
| Glaze | 1949.04 | 0.709769 | 145.836ms | 2889 | 2560 | 257708 | 1413.6 | 0.0849618 | 2(Loss) | true |
| Jsonifier (two-stage) | 1891.24 | 0.967009 | 151.154ms | 2889 | 1280 | 254022 | 1456.8 | 0.301122 | 3(Loss) | true |
| simdjson (reflection) | 1415.01 | 0.283194 | 198.948ms | 2889 | 2560 | 77836.8 | 1947.1 | 0.22133 | 4(Loss) | true |
| simdjson (ondemand) | 1157.6 | 0.367726 | 240.91ms | 2889 | 4890 | 374573 | 2380.07 | 0.306266 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2917.37 | 0.702873 | 111.883ms | 2889 | 2560 | 112799 | 944.4 | 0.0847817 | 1(Win) | true |
| Jsonifier (two-stage) | 2265.71 | 0.502273 | 141.179ms | 2889 | 4890 | 182421 | 1216.03 | 0.125663 | 2(Loss) | true |
| Glaze | 2193.78 | 1.11553 | 134.639ms | 2889 | 2560 | 502476 | 1255.9 | 2.82463 | 3(Loss) | true |
| simdjson (reflection) | 1578.62 | 0.386244 | 189.659ms | 2889 | 4890 | 222215 | 1745.3 | 0.200009 | 4(Loss) | true |
| simdjson (ondemand) | 1246.22 | 0.313717 | 236.373ms | 2889 | 4890 | 235228 | 2210.81 | 0.0355441 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12897 | 3.74493 | 24.5821ms | 2963 | 2560 | 172351 | 219.1 | 0.87477 | 1(Win) | true |
| simdjson (reflection) | 9327.11 | 2.19803 | 32.671ms | 2963 | 4890 | 216842 | 302.96 | 1.28397 | 2(Loss) | true |
| Glaze | 3592.34 | 1.56843 | 83.8321ms | 2963 | 1280 | 194827 | 786.6 | 1.20947 | 3(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14271.8 | 2.88721 | 22.539ms | 2963 | 4890 | 159798 | 197.994 | 0.804472 | 1(Win) | true |
| simdjson (reflection) | 10430.1 | 2.35586 | 29.6799ms | 2963 | 4890 | 199200 | 270.92 | 0.0813614 | 2(Loss) | true |
| Glaze | 3992.31 | 0.947638 | 74.2052ms | 2963 | 4890 | 219993 | 707.796 | 0.562588 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2307.15 | 0.496591 | 159.87ms | 3808 | 4890 | 298778 | 1574.06 | 0.591751 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2223.3 | 0.440322 | 168.697ms | 3808 | 4890 | 252958 | 1633.43 | 0.576628 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 2209 | 0.867437 | 167.782ms | 3808 | 1280 | 260309 | 1644 | 0.268358 | 2(Tie) | true |
| simdjson (reflection) | 1568.9 | 0.319405 | 238.088ms | 3808 | 4890 | 267297 | 2314.73 | 0.132362 | 4(Loss) | true |
| simdjson (ondemand) | 1459.7 | 0.498476 | 250.939ms | 3808 | 2560 | 393727 | 2487.9 | 0.245789 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2769.22 | 0.59215 | 147.839ms | 3808 | 4890 | 294884 | 1311.41 | 0.0542491 | 1(Win) | true |
| Jsonifier (two-stage) | 2616.42 | 0.514402 | 157.852ms | 3808 | 4890 | 249284 | 1388 | 0.186852 | 2(Loss) | true |
| Glaze | 2532.14 | 0.727333 | 159.746ms | 3808 | 2560 | 278565 | 1434.2 | 0.0278823 | 3(Loss) | true |
| simdjson (reflection) | 1933.75 | 0.657223 | 199.388ms | 3808 | 1280 | 194996 | 1878 | 0.341953 | 4(Loss) | true |
| simdjson (ondemand) | 1556.62 | 0.315397 | 247.742ms | 3808 | 4890 | 264761 | 2333 | 0.176172 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14693.6 | 2.30812 | 30.335ms | 4300 | 4890 | 202911 | 279.087 | 0.427174 | 1(Win) | true |
| Glaze | 3227.51 | 0.512255 | 128.706ms | 4300 | 4890 | 207149 | 1270.58 | 0.635279 | 2(Loss) | true |
| simdjson (reflection) | 417.367 | 0.172064 | 988.87ms | 4300 | 1280 | 365839 | 9825.4 | 0.21419 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17783.2 | 5.13626 | 26.113ms | 4300 | 1280 | 179566 | 230.6 | 1.95578 | 1(Win) | true |
| Glaze | 4031.46 | 0.407447 | 106.244ms | 4300 | 1280 | 21986.9 | 1017.2 | 0.11811 | 2(Loss) | true |
| simdjson (reflection) | 416.735 | 0.173665 | 990.073ms | 4300 | 2560 | 747617 | 9840.3 | 0.151648 | 3(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2441.89 | 0.309431 | 9453.96ms | 466906 | 40 | 1.27348e+07 | 182349 | 0.0280702 | 1(Win) | true |
| Glaze | 1676.46 | 0.101893 | 6837.49ms | 466906 | 1280 | 9.37497e+07 | 265604 | 0.166887 | 2(Loss) | true |
| simdjson (ondemand) | 1237.18 | 0.152564 | 9608.8ms | 466906 | 80 | 2.41209e+07 | 359914 | 0.0506532 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2472.13 | 0.109582 | 9349.67ms | 466906 | 320 | 1.24665e+07 | 180118 | 0.0257675 | 1(Win) | true |
| Glaze | 1676.47 | 0.100301 | 6786.66ms | 466906 | 1280 | 9.08426e+07 | 265603 | 0.111095 | 2(Loss) | true |
| simdjson (ondemand) | 1236.92 | 0.101275 | 9242.3ms | 466906 | 160 | 2.12665e+07 | 359987 | 0.268283 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3291.65 | 0.121998 | 5167.55ms | 699405 | 1280 | 7.82252e+07 | 202636 | 0.273154 | 1(Win) | true |
| Glaze | 2385.42 | 0.219484 | 7160.55ms | 699405 | 320 | 1.20527e+08 | 279617 | 0.0317477 | 2(Loss) | true |
| simdjson (ondemand) | 1652.33 | 0.215201 | 5690.06ms | 767297 | 80 | 7.26633e+07 | 442861 | 0.0202362 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3323.63 | 0.0743635 | 5210.17ms | 699405 | 1280 | 2.85077e+07 | 200686 | 0.207357 | 1(Win) | true |
| Glaze | 2383.55 | 0.264211 | 7121.39ms | 699405 | 160 | 8.74646e+07 | 279837 | 0 | 2(Loss) | true |
| simdjson (ondemand) | 1658.79 | 0.167767 | 5626.4ms | 767297 | 160 | 8.76354e+07 | 441136 | 0.113291 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2319.83 | 0.218756 | 6760.32ms | 631514 | 320 | 1.0321e+08 | 259613 | 0.343222 | 1(Win) | true |
| Glaze | 2029.64 | 0.247341 | 7630.44ms | 631514 | 320 | 1.72373e+08 | 296732 | 0.0379997 | 2(Loss) | true |
