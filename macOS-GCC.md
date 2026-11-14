# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

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
*Environment generated via BenchmarkSuite commit: [27950a9](https://github.com/nihilai-collective/benchmarksuite/commit/27950a9)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1309.28 | 4.17217 | 85.6289ms | 905 | 320 | 242052 | 659.2 | 1.2285 | 1(Tie) | true |
| Glaze STATISTICAL TIE | 1253.5 | 0.998518 | 89.066ms | 905 | 4890 | 231136 | 688.53 | 2.18612 | 1(Tie) | true |
| Jsonifier (two-stage) | 320.274 | 0.651129 | 275.862ms | 905 | 1280 | 394092 | 2694.8 | 2.98099 | 3(Loss) | true |
| simdjson (ondemand) | 150.163 | 0.633937 | 590.899ms | 905 | 640 | 849660 | 5747.6 | 1.01268 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1500.48 | 2.41943 | 61.4572ms | 905 | 1280 | 247899 | 575.2 | 0.621977 | 1(Win) | true |
| Glaze | 1304.53 | 2.85567 | 66.945ms | 905 | 640 | 228447 | 661.6 | 3.16159 | 2(Loss) | true |
| Jsonifier (two-stage) | 328.74 | 0.472077 | 292.211ms | 905 | 2560 | 393240 | 2625.4 | 1.5081 | 3(Loss) | true |
| simdjson (ondemand) | 147.868 | 1.65217 | 548.872ms | 905 | 80 | 743958 | 5836.8 | 2.47191 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1757.95 | 1.48816 | 53.3361ms | 905 | 4890 | 261031 | 490.955 | 1.1169 | 1(Win) | true |
| simdjson (reflection) | 211.663 | 0.624288 | 440.648ms | 905 | 320 | 207362 | 4077.6 | 0.215348 | 2(Loss) | true |
| Glaze | 102.54 | 0.484504 | 769.429ms | 905 | 1280 | 2.12873e+06 | 8417 | 0.550593 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3217.43 | 2.50309 | 38.412ms | 905 | 4890 | 220466 | 268.25 | 3.99058 | 1(Win) | true |
| simdjson (reflection) | 2380.24 | 3.01539 | 46.7932ms | 905 | 2560 | 306042 | 362.6 | 1.79674 | 2(Loss) | true |
| Glaze | 635.362 | 3.03085 | 132.006ms | 905 | 160 | 271209 | 1358.4 | 0.831354 | 3(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 902.19 | 0.399683 | 206.825ms | 1811 | 4890 | 286274 | 1914.35 | 0.951643 | 1(Win) | true |
| Glaze | 791.231 | 0.45055 | 227.627ms | 1811 | 4890 | 472962 | 2182.81 | 0.632507 | 2(Loss) | true |
| Jsonifier (two-stage) | 481.463 | 1.94819 | 396.644ms | 1811 | 80 | 390717 | 3587.2 | 0.44405 | 3(Loss) | true |
| simdjson (ondemand) | 140.229 | 0.395769 | 1278.27ms | 1811 | 2560 | 6.08252e+06 | 12316.3 | 1.17708 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Glaze | 1000.76 | 0.790001 | 191.254ms | 1811 | 1280 | 237928 | 1725.8 | 0.31388 | 1(Win) | true |
| Jsonifier | 902.636 | 1.5953 | 170.639ms | 1811 | 2560 | 2.38527e+06 | 1913.4 | 0.146123 | 2(Loss) | true |
| Jsonifier (two-stage) | 441.015 | 0.594568 | 375.464ms | 1811 | 1280 | 693974 | 3916.2 | 0.51848 | 3(Loss) | true |
| simdjson (ondemand) | 135.014 | 0.304889 | 1288.72ms | 1811 | 2560 | 3.89404e+06 | 12792 | 3.15694 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 258.982 | 0.273164 | 723.903ms | 1997 | 4890 | 1.97321e+06 | 7353.74 | 2.16939 | 1(Win) | true |
| Jsonifier | 251.062 | 0.897201 | 721.993ms | 1811 | 640 | 2.43801e+06 | 6879.2 | 1.08146 | 2(Loss) | true |
| Glaze | 167.334 | 0.909009 | 996.86ms | 1798 | 320 | 2.7765e+06 | 10247.2 | 0.0078064 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 791.052 | 0.820006 | 233.735ms | 1811 | 2560 | 820542 | 2183.3 | 3.79395 | 1(Win) | true |
| simdjson (reflection) | 669.275 | 0.562442 | 321.167ms | 1997 | 1280 | 327879 | 2845.6 | 1.91977 | 2(Loss) | true |
| Glaze | 576.932 | 0.351844 | 316.555ms | 1798 | 4890 | 534737 | 2972.11 | 2.70361 | 3(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2361.78 | 0.632038 | 171.763ms | 3862 | 4890 | 475052 | 1559.45 | 2.08128 | 1(Win) | true |
| Glaze | 1315.62 | 0.423766 | 302.158ms | 3862 | 2560 | 360291 | 2799.5 | 0.628283 | 2(Loss) | true |
| Jsonifier (two-stage) | 861.844 | 0.339264 | 451.166ms | 3862 | 2560 | 538125 | 4273.5 | 2.0318 | 3(Loss) | true |
| simdjson (ondemand) | 386.626 | 0.272086 | 952.883ms | 3862 | 4890 | 3.28523e+06 | 9526.24 | 1.10523 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2904.14 | 0.662251 | 137.929ms | 3862 | 4890 | 344941 | 1268.22 | 1.10985 | 1(Win) | true |
| Glaze | 1179.27 | 1.06373 | 311.517ms | 3862 | 320 | 353196 | 3123.2 | 0.509684 | 2(Loss) | true |
| Jsonifier (two-stage) | 901.128 | 0.856004 | 476.391ms | 3862 | 320 | 391700 | 4087.2 | 3.67289 | 3(Loss) | true |
| simdjson (ondemand) | 406.913 | 0.427013 | 947.267ms | 3862 | 2560 | 3.82422e+06 | 9051.3 | 1.80842 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 651.736 | 3.34144 | 546.836ms | 3862 | 40 | 1.42629e+06 | 5651.2 | 0.263554 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 633.992 | 0.27362 | 535.996ms | 3862 | 4890 | 1.23555e+06 | 5809.37 | 1.80078 | 1(Tie) | true |
| Glaze | 466.93 | 0.253183 | 840.986ms | 3862 | 4890 | 1.95029e+06 | 7887.89 | 0.682742 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5070.33 | 6.9937 | 94.1489ms | 3862 | 80 | 206470 | 726.4 | 0.438596 | 1(Win) | true |
| simdjson (reflection) | 3079.51 | 1.8765 | 143.311ms | 3862 | 320 | 161179 | 1196 | 1.1502 | 2(Loss) | true |
| Glaze | 1977.37 | 0.730058 | 187.391ms | 3862 | 4890 | 904218 | 1862.62 | 1.41203 | 3(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 925.973 | 1.88595 | 848.877ms | 9578 | 30 | 1.03833e+06 | 9864.53 | 0 | 1(Tie) | true |
| Glaze STATISTICAL TIE DID NOT CONVERGE | 922.751 | 0.692333 | 938.263ms | 9578 | 4890 | 2.29678e+07 | 9898.98 | 7.84966 | -(Tie) | false |
| simdjson (ondemand) | 705.994 | 0.216466 | 1368.15ms | 9578 | 4890 | 3.83563e+06 | 12938.2 | 0.94848 | 3(Loss) | true |
| Jsonifier (two-stage) | 673.382 | 0.234473 | 1430.35ms | 9578 | 4890 | 4.94677e+06 | 13564.8 | 4.82423e-05 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1718.52 | 1.13509 | 775.328ms | 9578 | 160 | 582395 | 5315.2 | 0.835821 | 1(Win) | true |
| Glaze | 1650.93 | 1.03296 | 895.15ms | 9578 | 80 | 261304 | 5532.8 | 1.46714 | 2(Loss) | true |
| simdjson (ondemand) | 913.101 | 0.57595 | 1306.32ms | 9578 | 1280 | 4.24905e+06 | 10003.6 | 2.04841 | 3(Loss) | true |
| Jsonifier (two-stage) | 841.931 | 0.308415 | 1405.05ms | 9578 | 4890 | 5.47491e+06 | 10849.2 | 4.93067 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1370.53 | 0.537939 | 719.549ms | 9578 | 640 | 822661 | 6664.8 | 2.06888 | 1(Win) | true |
| simdjson (reflection) | 1124.91 | 1.16677 | 799.098ms | 9578 | 160 | 1.43616e+06 | 8120 | 0.256815 | 2(Loss) | true |
| Glaze DID NOT CONVERGE | 920.202 | 1.96428 | 918.121ms | 9578 | 40 | 1.52073e+06 | 9926.4 | 5.94262 | -(Loss) | false |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9345.5 | 0.895705 | 116.227ms | 9578 | 1280 | 98103.5 | 977.4 | 0.265306 | 1(Win) | true |
| simdjson (reflection) | 8570.55 | 0.529825 | 106.245ms | 9578 | 4890 | 155921 | 1065.78 | 1.41561 | 2(Loss) | true |
| Glaze | 4487.29 | 0.536903 | 223.174ms | 9578 | 4890 | 584094 | 2035.59 | 0.939577 | 3(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1818.66 | 1.99837 | 171.674ms | 3873 | 30 | 49415.7 | 2030.93 | 1.65289 | 1(Win) | true |
| Glaze | 1296.18 | 1.76166 | 273.635ms | 3873 | 160 | 403209 | 2849.6 | 0.735294 | 2(Loss) | true |
| Jsonifier (two-stage) | 670.877 | 1.73745 | 499.818ms | 3873 | 160 | 1.46405e+06 | 5505.6 | 1.85396 | 3(Loss) | true |
| simdjson (ondemand) | 416.244 | 0.902167 | 976.52ms | 3873 | 160 | 1.0254e+06 | 8873.6 | 1.28159 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2969.12 | 1.47933 | 145.828ms | 3873 | 640 | 216745 | 1244 | 0.51713 | 1(Win) | true |
| Glaze | 1240.46 | 1.1207 | 267.329ms | 3873 | 320 | 356337 | 2977.6 | 0.485961 | 2(Loss) | true |
| Jsonifier (two-stage) | 834.18 | 0.489413 | 457.91ms | 3873 | 1280 | 601086 | 4427.8 | 0.00451712 | 3(Loss) | true |
| simdjson (ondemand) | 453.712 | 0.774694 | 918.38ms | 3873 | 30 | 119321 | 8140.8 | 0.845666 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 769.496 | 1.01964 | 498.687ms | 3873 | 80 | 191631 | 4800 | 0.398406 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 762.632 | 0.626899 | 517.442ms | 3873 | 320 | 294992 | 4843.2 | 0.9 | 1(Tie) | true |
| Glaze | 535.643 | 0.4572 | 736.642ms | 3873 | 640 | 636117 | 6895.6 | 0.261719 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5107.27 | 7.00575 | 89.7042ms | 3873 | 80 | 205360 | 723.2 | 0.877193 | 1(Win) | true |
| simdjson (reflection) | 3076.96 | 1.01388 | 130.251ms | 3873 | 2560 | 379194 | 1200.4 | 0.233801 | 2(Loss) | true |
| Glaze | 2100.53 | 1.96669 | 177.392ms | 3873 | 160 | 191350 | 1758.4 | 0.457038 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1059.97 | 0.272428 | 9196.59ms | 94653 | 2560 | 1.37793e+08 | 85161.2 | 0.591777 | 1(Win) | true |
| Glaze | 975.956 | 0.674779 | 9295.19ms | 94653 | 320 | 1.24647e+08 | 92492 | 0.126985 | 2(Loss) | true |
| Jsonifier (two-stage) | 847.534 | 0.397647 | 5648.7ms | 94653 | 1280 | 2.29594e+08 | 106507 | 1.85804 | 3(Loss) | true |
| simdjson (reflection) | 823.602 | 0.539333 | 5841.33ms | 94653 | 320 | 1.11814e+08 | 109602 | 0.508344 | 4(Loss) | true |
| simdjson (ondemand) | 599.097 | 0.798617 | 7304.83ms | 94653 | 160 | 2.31671e+08 | 150674 | 2.99792 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1985.42 | 0.197649 | 7252.39ms | 94653 | 30 | 242257 | 45465.6 | 1.76991 | 1(Win) | true |
| Glaze | 1418.55 | 0.298463 | 8489.75ms | 94653 | 4890 | 1.76388e+08 | 63634.1 | 0.136373 | 2(Loss) | true |
| Jsonifier (two-stage) | 1289.51 | 0.517567 | 9464ms | 94653 | 640 | 8.40106e+07 | 70002 | 0.151195 | 3(Loss) | true |
| simdjson (reflection) | 1017.54 | 0.431474 | 5702.05ms | 94653 | 1280 | 1.87535e+08 | 88711.8 | 0.827926 | 4(Loss) | true |
| simdjson (ondemand) | 879.505 | 0.497109 | 6495.17ms | 94653 | 320 | 8.33001e+07 | 102635 | 1.31534 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13318.6 | 1.02987 | 809.22ms | 94653 | 40 | 194886 | 6777.6 | 3.14024 | 1(Win) | true |
| simdjson (reflection) | 7542.01 | 0.492269 | 1184.65ms | 94653 | 4890 | 1.69749e+07 | 11968.7 | 2.69866 | 2(Loss) | true |
| Glaze | 4574.09 | 0.267505 | 1981.76ms | 94653 | 4890 | 1.3628e+07 | 19734.7 | 0.010294 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9578.54 | 1.84967 | 833.969ms | 94653 | 80 | 2.43079e+06 | 9424 | 0.372124 | 1(Win) | true |
| simdjson (reflection) | 8622.59 | 1.04448 | 1100.24ms | 94653 | 160 | 1.91299e+06 | 10468.8 | 1.69772 | 2(Loss) | true |
| Glaze | 5151.94 | 0.538238 | 1654.87ms | 94653 | 1280 | 1.13838e+07 | 17521.2 | 1.41227 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1179.63 | 0.354326 | 5197.08ms | 124597 | 2560 | 3.26116e+08 | 100731 | 0.222968 | 1(Win) | true |
| Jsonifier (two-stage) | 1165.76 | 0.224436 | 5283.08ms | 124597 | 1280 | 6.69878e+07 | 101930 | 0.405687 | 2(Loss) | true |
| Glaze | 1132.38 | 0.282105 | 5445.14ms | 124597 | 1280 | 1.12166e+08 | 104934 | 1.28061 | 3(Loss) | true |
| simdjson (reflection) | 1074.8 | 0.140913 | 5741.34ms | 124597 | 2560 | 6.21301e+07 | 110556 | 0.193216 | 4(Loss) | true |
| simdjson (ondemand) | 894.012 | 0.699254 | 6933.16ms | 124597 | 80 | 6.91016e+07 | 132912 | 0.0650477 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1811.32 | 0.524063 | 8918.94ms | 124597 | 640 | 7.56433e+07 | 65601.2 | 0.311824 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1676.26 | 0.321365 | 9662.96ms | 124597 | 640 | 3.3213e+07 | 70886.8 | 0.55386 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1663.2 | 0.342262 | 9414.81ms | 124597 | 1280 | 7.65338e+07 | 71443.6 | 1.13302 | 2(Tie) | true |
| simdjson (reflection) | 1302.67 | 0.433423 | 5727.06ms | 124597 | 640 | 1.00035e+08 | 91216.8 | 0.248458 | 4(Loss) | true |
| simdjson (ondemand) | 1136.84 | 0.197147 | 6436.32ms | 124597 | 1280 | 5.43516e+07 | 104523 | 0.389778 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12973.5 | 0.379962 | 1018.82ms | 136037 | 320 | 461988 | 10000 | 0.175691 | 1(Win) | true |
| Glaze | 3979.24 | 0.253571 | 3206.74ms | 136076 | 2560 | 1.75066e+07 | 32612.3 | 0.285882 | 2(Loss) | true |
| simdjson (reflection) | 337.292 | 0.312143 | 10179.8ms | 136037 | 80 | 1.15318e+08 | 384637 | 0.0824313 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13241.9 | 0.158732 | 1021.7ms | 136037 | 4890 | 1.18264e+06 | 9797.31 | 0.564162 | 1(Win) | true |
| Glaze | 4794.3 | 0.529001 | 2701.06ms | 136076 | 320 | 6.56108e+06 | 27068 | 0.0443131 | 2(Loss) | true |
| simdjson (reflection) | 346.932 | 0.226179 | 9732.64ms | 136037 | 640 | 4.57835e+08 | 373949 | 0.705465 | 3(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 842.18 | 0.362632 | 8090.8ms | 2251027 | 30 | 2.56334e+09 | 2.54903e+06 | 0.0217551 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 583.871 | 1.50578 | 5457.82ms | 2251027 | 40 | 1.22607e+11 | 3.67675e+06 | 1.13536 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 571.986 | 0.568573 | 5638.14ms | 2251027 | 80 | 3.64296e+10 | 3.75315e+06 | 0.650383 | 2(Tie) | true |
| simdjson (reflection) | 562.628 | 0.504547 | 5785.1ms | 2251027 | 30 | 1.11184e+10 | 3.81557e+06 | 1.05596 | 4(Loss) | true |
| simdjson (ondemand) | 513.841 | 0.494494 | 6477.3ms | 2251027 | 30 | 1.2804e+10 | 4.17784e+06 | 2.35326 | 5(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 950.854 | 0.734865 | 9093.02ms | 2251027 | 160 | 4.40422e+10 | 2.2577e+06 | 0.825758 | 1(Win) | true |
| Jsonifier (two-stage) | 827.224 | 0.460915 | 5012.04ms | 2251027 | 80 | 1.14458e+10 | 2.59512e+06 | 0.369684 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 690.775 | 0.740049 | 5815.01ms | 2251027 | 40 | 2.11578e+10 | 3.10774e+06 | 1.62372 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 690.135 | 0.590168 | 5546.29ms | 2251027 | 40 | 1.34804e+10 | 3.11062e+06 | 0.639826 | 3(Tie) | true |
| simdjson (ondemand) | 582.427 | 0.779384 | 6281.36ms | 2251027 | 30 | 2.47572e+10 | 3.68586e+06 | 0.472663 | 5(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2199.35 | 0.257411 | 5881.66ms | 2090234 | 320 | 1.74183e+09 | 906362 | 0.033022 | 1(Win) | true |
| Glaze | 1588.73 | 0.967391 | 8325.2ms | 2090234 | 30 | 4.41994e+09 | 1.25472e+06 | 2.39773 | 2(Loss) | true |
| simdjson (reflection) | 768.856 | 0.618189 | 8290.78ms | 2090326 | 30 | 7.70731e+09 | 2.5928e+06 | 0.0167877 | 3(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2225.28 | 0.433798 | 5652.32ms | 2090234 | 320 | 4.8322e+09 | 895798 | 0.283544 | 1(Win) | true |
| Glaze | 1556.38 | 1.20518 | 8044.93ms | 2090234 | 30 | 7.14804e+09 | 1.28079e+06 | 0.197601 | 2(Loss) | true |
| simdjson (reflection) | 723.589 | 0.759882 | 8387.97ms | 2090326 | 30 | 1.31479e+10 | 2.755e+06 | 0.558464 | 3(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1436.69 | 1.36381 | 5316.16ms | 5373214 | 30 | 7.09855e+10 | 3.56673e+06 | 1.13725 | 1(Win) | true |
| Jsonifier (two-stage) | 1318.47 | 0.687625 | 5803.08ms | 5373214 | 30 | 2.14267e+10 | 3.88656e+06 | 0.629909 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1155.34 | 0.445605 | 6864.52ms | 5373214 | 30 | 1.17185e+10 | 4.43533e+06 | 0.657106 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE DID NOT CONVERGE | 1131 | 0.991937 | 6526.47ms | 5373214 | 80 | 1.61585e+11 | 4.53076e+06 | 8.98514 | -(Tie) | false |
| Glaze | 1096.58 | 0.799449 | 7149.56ms | 5373214 | 30 | 4.18685e+10 | 4.67296e+06 | 1.58024 | 5(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1782.53 | 0.877277 | 5319.29ms | 5373214 | 30 | 1.90805e+10 | 2.87473e+06 | 0.475932 | 1(Win) | true |
| Jsonifier (two-stage) | 1606.46 | 1.14778 | 5624.13ms | 5373214 | 80 | 1.07235e+11 | 3.1898e+06 | 2.41465 | 2(Loss) | true |
| simdjson (reflection) | 1442.22 | 0.523587 | 6385.33ms | 5373214 | 80 | 2.76867e+10 | 3.55306e+06 | 0.526202 | 3(Loss) | true |
| Glaze | 1311.76 | 0.743627 | 7099.27ms | 5373214 | 40 | 3.37546e+10 | 3.90644e+06 | 1.79896 | 4(Loss) | true |
| simdjson (ondemand) | 1271.26 | 0.661959 | 6984.83ms | 5373214 | 80 | 5.69576e+10 | 4.03088e+06 | 0.63779 | 5(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6624.93 | 1.00618 | 5988.88ms | 6661897 | 40 | 3.72428e+09 | 958995 | 0.97963 | 1(Win) | true |
| Glaze | 3120.81 | 0.583412 | 6349.16ms | 6661897 | 40 | 5.6425e+09 | 2.03578e+06 | 0.591905 | 2(Loss) | true |
| simdjson (reflection) | 266.976 | 0.828874 | 7403.07ms | 6661989 | 30 | 1.16724e+12 | 2.37975e+07 | 2.13355 | 3(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6796.57 | 0.451475 | 6014.58ms | 6661897 | 320 | 5.69946e+09 | 934778 | 0.85882 | 1(Win) | true |
| Glaze | 3555.22 | 0.868434 | 5665.75ms | 6661897 | 40 | 9.63377e+09 | 1.78703e+06 | 0.180947 | 2(Loss) | true |
| simdjson (reflection) | 274.914 | 1.29307 | 7305.67ms | 6661989 | 30 | 2.67906e+12 | 2.31104e+07 | 3.21982 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1912.86 | 0.961188 | 6717.08ms | 500299 | 30 | 1.72438e+08 | 249429 | 0.0547083 | 1(Win) | true |
| Glaze | 1278.28 | 0.294308 | 5130.22ms | 500299 | 40 | 4.82697e+07 | 373254 | 0.164304 | 2(Loss) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 1097.27 | 0.676184 | 5350.81ms | 500299 | 640 | 5.53278e+09 | 434828 | 8.04459 | -(Loss) | false |
| simdjson (reflection) | 1029.56 | 0.307072 | 5958.9ms | 500299 | 640 | 1.29603e+09 | 463423 | 0.138034 | 4(Loss) | true |
| simdjson (ondemand) | 922.014 | 1.0759 | 6179.7ms | 500299 | 40 | 1.23991e+09 | 517478 | 1.41311 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2356.77 | 0.493415 | 6505.16ms | 500299 | 640 | 6.38602e+08 | 202448 | 1.35556 | 1(Win) | true |
| Jsonifier (two-stage) | 1339.77 | 1.8392 | 5069.66ms | 500299 | 80 | 3.43199e+09 | 356122 | 4.92268 | 2(Loss) | true |
| Glaze | 1268.32 | 1.01932 | 5037.38ms | 500299 | 30 | 4.41106e+08 | 376183 | 0.300328 | 3(Loss) | true |
| simdjson (reflection) | 1163.44 | 0.281749 | 5930.92ms | 500299 | 160 | 2.13607e+08 | 410096 | 0.445898 | 4(Loss) | true |
| simdjson (ondemand) | 1053.13 | 1.30782 | 6075.65ms | 500299 | 30 | 1.0532e+09 | 453052 | 0.0583551 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7642.1 | 0.210513 | 6348.79ms | 500299 | 4890 | 8.44694e+07 | 62433.4 | 0.979453 | 1(Win) | true |
| simdjson (reflection) | 7073.42 | 1.00413 | 6678.49ms | 500299 | 80 | 3.67001e+07 | 67452.8 | 0.337966 | 2(Loss) | true |
| Glaze | 2016.56 | 0.987062 | 6757.78ms | 500299 | 80 | 4.36329e+08 | 236602 | 0.467429 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8008.1 | 0.59635 | 6398.05ms | 500299 | 320 | 4.03974e+07 | 59580 | 0.660936 | 1(Win) | true |
| simdjson (reflection) | 7310.16 | 0.331608 | 6667.52ms | 500299 | 640 | 2.99804e+07 | 65268.4 | 0.463619 | 2(Loss) | true |
| Glaze | 1815.93 | 0.517059 | 6204.92ms | 500299 | 160 | 2.95298e+08 | 262742 | 0.40722 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2764.49 | 0.157529 | 5135.53ms | 1151920 | 640 | 2.50794e+08 | 397382 | 0.208933 | 1(Win) | true |
| Jsonifier (two-stage) | 2405.97 | 0.197752 | 6047.74ms | 1151920 | 640 | 5.21781e+08 | 456596 | 0.372035 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 2041.74 | 0.342608 | 7342.77ms | 1151920 | 40 | 1.35924e+08 | 538048 | 0.331162 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2037.33 | 0.37931 | 6951.68ms | 1151920 | 80 | 3.34656e+08 | 539213 | 0.0106811 | 3(Tie) | true |
| Glaze | 1831.22 | 0.141884 | 7730.46ms | 1151920 | 640 | 4.63674e+08 | 599904 | 0.341349 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3142.71 | 0.334522 | 5156.05ms | 1151920 | 320 | 4.37556e+08 | 349557 | 0.0187631 | 1(Win) | true |
| Jsonifier (two-stage) | 2718.62 | 0.342735 | 5763.52ms | 1151920 | 320 | 6.13783e+08 | 404086 | 1.14743 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 2217.98 | 0.239767 | 7263.65ms | 1151920 | 640 | 9.02588e+08 | 495297 | 0.861488 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2216.03 | 0.235347 | 6836.92ms | 1151920 | 160 | 2.17786e+08 | 495731 | 0.00258198 | 3(Tie) | true |
| Glaze | 2017.77 | 0.149542 | 7515.5ms | 1151920 | 320 | 2.12118e+08 | 544442 | 0.202008 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16617.3 | 0.328924 | 8339.28ms | 1439562 | 2560 | 1.89047e+08 | 82617 | 0.552805 | 1(Win) | true |
| Glaze | 3634.28 | 0.208848 | 5036.4ms | 1439584 | 30 | 1.86732e+07 | 377762 | 0.799217 | 2(Loss) | true |
| simdjson (reflection) | 306.994 | 0.711992 | 6947.17ms | 1439562 | 80 | 8.1104e+10 | 4.47199e+06 | 0.0632159 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17474.6 | 0.255099 | 7837.33ms | 1439562 | 2560 | 1.02826e+08 | 78563.8 | 0.627625 | 1(Win) | true |
| Glaze | 4209.69 | 0.698143 | 8542.61ms | 1439584 | 30 | 1.55519e+08 | 326127 | 0.438885 | 2(Loss) | true |
| simdjson (reflection) | 324.646 | 0.396414 | 6637.64ms | 1439562 | 80 | 2.24816e+10 | 4.22883e+06 | 1.31453 | 3(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1691.59 | 0.0927168 | 3184.52ms | 56369 | 4890 | 4.24538e+06 | 31779.4 | 0.273216 | 1(Win) | true |
| Glaze | 1321.66 | 0.4987 | 4139.57ms | 56369 | 320 | 1.31665e+07 | 40674.4 | 0.369157 | 2(Loss) | true |
| Jsonifier (two-stage) | 1165.08 | 0.0772982 | 4620.46ms | 56369 | 4890 | 6.22036e+06 | 46140.7 | 0.121897 | 3(Loss) | true |
| simdjson (reflection) | 1044.38 | 0.695606 | 5593.81ms | 56369 | 30 | 3.84598e+06 | 51473.1 | 0.987778 | 4(Loss) | true |
| simdjson (ondemand) | 917.852 | 0.253204 | 6232.53ms | 56369 | 1280 | 2.81504e+07 | 58569 | 2.36157 | 5(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2299.5 | 0.118632 | 2925.69ms | 56369 | 4890 | 3.7612e+06 | 23378 | 1.11966 | 1(Win) | true |
| Glaze | 1827.28 | 0.100035 | 3450.37ms | 56369 | 4890 | 4.23525e+06 | 29419.5 | 0.466624 | 2(Loss) | true |
| Jsonifier (two-stage) | 1480.4 | 0.160656 | 4338.88ms | 56369 | 1280 | 4.35639e+06 | 36313 | 0.0599976 | 3(Loss) | true |
| simdjson (reflection) | 1092.03 | 0.738856 | 5635.05ms | 56369 | 160 | 2.11666e+07 | 49227.2 | 0.835737 | 4(Loss) | true |
| simdjson (ondemand) | 989.969 | 0.745477 | 5903.89ms | 56369 | 160 | 2.62197e+07 | 54302.4 | 0.0382893 | 5(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10145.6 | 0.423097 | 513.211ms | 56369 | 2560 | 1.2866e+06 | 5298.6 | 1.93226 | 1(Win) | true |
| simdjson (reflection) | 9312.23 | 0.643161 | 625.165ms | 56369 | 320 | 441125 | 5772.8 | 1.60894 | 2(Loss) | true |
| Glaze | 2476.31 | 0.657824 | 2275.1ms | 56369 | 320 | 6.52591e+06 | 21708.8 | 0.242629 | 3(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12274.9 | 0.232257 | 442.204ms | 56369 | 4890 | 505932 | 4379.48 | 0.0133518 | 1(Win) | true |
| simdjson (reflection) | 9521.71 | 0.397657 | 564.123ms | 56369 | 1280 | 645178 | 5645.8 | 0.26498 | 2(Loss) | true |
| Glaze | 2968.99 | 0.327411 | 1867.73ms | 56369 | 640 | 2.24922e+06 | 18106.4 | 0.0663189 | 3(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1849.73 | 0.076052 | 4342.71ms | 83958 | 4890 | 5.29952e+06 | 43286.6 | 0.0114682 | 1(Win) | true |
| Glaze | 1642.43 | 0.0767967 | 4879.98ms | 83958 | 4890 | 6.85401e+06 | 48750.1 | 1.01909 | 2(Loss) | true |
| Jsonifier (two-stage) | 1601.09 | 0.415859 | 5022.44ms | 83958 | 1280 | 5.53598e+07 | 50008.8 | 0.113709 | 3(Loss) | true |
| simdjson (reflection) | 1432.88 | 0.246925 | 5767.32ms | 83958 | 1280 | 2.43694e+07 | 55879.6 | 0.522669 | 4(Loss) | true |
| simdjson (ondemand) | 1278.77 | 0.116543 | 6299.52ms | 83958 | 1280 | 6.81579e+06 | 62613.6 | 0.125369 | 5(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2292.05 | 0.0867746 | 4030.14ms | 83958 | 4890 | 4.49333e+06 | 34933.1 | 0.240422 | 1(Win) | true |
| Glaze | 2074.15 | 0.12477 | 4358.6ms | 83958 | 2560 | 5.9389e+06 | 38603.1 | 0.0624692 | 2(Loss) | true |
| Jsonifier (two-stage) | 1999.66 | 0.0889897 | 4661.01ms | 83958 | 4890 | 6.20872e+06 | 40041.2 | 0.133995 | 3(Loss) | true |
| simdjson (reflection) | 1605.52 | 0.0673962 | 5617.34ms | 83958 | 4890 | 5.52427e+06 | 49870.9 | 0.143472 | 4(Loss) | true |
| simdjson (ondemand) | 1522.36 | 0.127286 | 5788.26ms | 83958 | 2560 | 1.14734e+07 | 52594.9 | 0.443254 | 5(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13497 | 0.172848 | 673.219ms | 94370 | 4890 | 649585 | 6668.04 | 0.0892883 | 1(Win) | true |
| Glaze | 2282.92 | 0.477286 | 3998.94ms | 94370 | 160 | 5.66453e+06 | 39422.4 | 0.0527341 | 2(Loss) | true |
| simdjson (reflection) | 332.67 | 0.101855 | 7014.77ms | 94370 | 1280 | 9.71897e+07 | 270533 | 0.0401268 | 3(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12441.1 | 0.260883 | 693.057ms | 94370 | 4890 | 1.74162e+06 | 7233.96 | 0.0299122 | 1(Win) | true |
| Glaze | 2527.92 | 0.130755 | 3549.44ms | 94370 | 2560 | 5.5475e+06 | 35601.7 | 0.263884 | 2(Loss) | true |
| simdjson (reflection) | 334.101 | 0.066313 | 6978.25ms | 94370 | 1280 | 4.08432e+07 | 269374 | 0.330145 | 3(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1532.02 | 0.105111 | 3320.39ms | 53331 | 4890 | 5.95434e+06 | 33198.2 | 0.0908061 | 1(Win) | true |
| Glaze | 1374.03 | 0.182256 | 3753.72ms | 53331 | 1280 | 5.82564e+06 | 37015.6 | 0.143517 | 2(Loss) | true |
| Jsonifier (two-stage) | 1334.45 | 0.0862905 | 3902.47ms | 53331 | 4890 | 5.28916e+06 | 38113.3 | 0.435295 | 3(Loss) | true |
| simdjson (reflection) | 1124.31 | 0.365004 | 4542.88ms | 53331 | 160 | 4.36214e+06 | 45236.8 | 0.166513 | 4(Loss) | true |
| simdjson (ondemand) | 952.628 | 0.253221 | 5381.9ms | 53331 | 320 | 5.84875e+06 | 53389.6 | 0.157582 | 5(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2175.06 | 0.153336 | 3035.57ms | 53331 | 2560 | 3.29113e+06 | 23383.4 | 0.28305 | 1(Win) | true |
| Glaze | 1841.54 | 0.189034 | 3496.5ms | 53331 | 1280 | 3.48888e+06 | 27618.4 | 0.210447 | 2(Loss) | true |
| Jsonifier (two-stage) | 1731.03 | 0.186929 | 3587.53ms | 53331 | 1280 | 3.86111e+06 | 29381.6 | 0.062585 | 3(Loss) | true |
| simdjson (reflection) | 1345.44 | 0.161813 | 4510.31ms | 53331 | 1280 | 4.78926e+06 | 37802.2 | 0.120243 | 4(Loss) | true |
| simdjson (ondemand) | 1128.05 | 0.0802771 | 5163.68ms | 53331 | 4890 | 6.40614e+06 | 45087 | 0.0733444 | 5(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14918.3 | 0.248421 | 378.575ms | 58581 | 4890 | 423214 | 3744.88 | 0.229735 | 1(Win) | true |
| simdjson (reflection) | 10962.5 | 0.268299 | 518.75ms | 58581 | 2560 | 478597 | 5096.2 | 0.379232 | 2(Loss) | true |
| Glaze | 3538 | 0.279789 | 1633.98ms | 58581 | 1280 | 2.49844e+06 | 15790.6 | 0.208549 | 3(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16024.2 | 0.240699 | 354.964ms | 58581 | 4890 | 344362 | 3486.42 | 0.336849 | 1(Win) | true |
| simdjson (reflection) | 11463.8 | 0.228219 | 493.134ms | 58581 | 4890 | 604884 | 4873.37 | 0.174124 | 2(Loss) | true |
| Glaze | 4362.97 | 0.128847 | 1293.52ms | 58581 | 4890 | 1.33108e+06 | 12804.9 | 0.0395999 | 3(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1595.03 | 0.085932 | 3929.27ms | 65103 | 4890 | 5.47123e+06 | 38925.4 | 0.0323539 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1514.79 | 0.0897173 | 4118.79ms | 65103 | 4890 | 6.61235e+06 | 40987.1 | 0.162912 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1510.28 | 0.262826 | 4256.21ms | 65103 | 320 | 3.7357e+06 | 41109.6 | 0.0874942 | 2(Tie) | true |
| simdjson (reflection) | 1341.6 | 0.267517 | 4652.33ms | 65103 | 320 | 4.90468e+06 | 46278.4 | 0.211343 | 4(Loss) | true |
| simdjson (ondemand) | 1136.73 | 0.365314 | 5481.4ms | 65103 | 160 | 6.37006e+06 | 54619.2 | 0.190047 | 5(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2172.52 | 0.402917 | 3613.99ms | 65103 | 320 | 4.24283e+06 | 28578.4 | 0.00839725 | 1(Win) | true |
| Glaze | 1973.45 | 0.140366 | 3819.8ms | 65103 | 2560 | 4.99246e+06 | 31461.2 | 0.0687032 | 2(Loss) | true |
| Jsonifier (two-stage) | 1954.41 | 0.205293 | 3879.93ms | 65103 | 1280 | 5.44411e+06 | 31767.6 | 0.0541139 | 3(Loss) | true |
| simdjson (reflection) | 1575.87 | 0.0898951 | 4635.35ms | 65103 | 4890 | 6.13397e+06 | 39398.6 | 0.345119 | 4(Loss) | true |
| simdjson (ondemand) | 1346.9 | 0.147592 | 5248.66ms | 65103 | 1280 | 5.92472e+06 | 46096.4 | 0.517235 | 5(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15255.1 | 1.58891 | 509.781ms | 78778 | 80 | 489850 | 4924.8 | 1.11695 | 1(Win) | true |
| Glaze | 3165.13 | 0.133748 | 2388.29ms | 78778 | 4890 | 4.92845e+06 | 23736.3 | 0.0996192 | 2(Loss) | true |
| simdjson (reflection) | 401.737 | 0.0943202 | 9533.1ms | 78778 | 1280 | 3.98242e+07 | 187009 | 0.18096 | 3(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16200 | 0.213832 | 472.158ms | 78778 | 4890 | 480880 | 4637.58 | 0.127517 | 1(Win) | true |
| Glaze | 3960.47 | 0.217989 | 1950.46ms | 78778 | 30 | 51298.9 | 18969.6 | 0.542741 | 2(Loss) | true |
| simdjson (reflection) | 404.884 | 0.0964937 | 9673.07ms | 78778 | 640 | 2.05176e+07 | 185556 | 0.242786 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1816.79 | 0.324261 | 624.323ms | 11812 | 1280 | 517415 | 6200.4 | 0.10955 | 1(Win) | true |
| Jsonifier (two-stage) | 1206.52 | 0.144425 | 941.295ms | 11812 | 4890 | 889145 | 9336.62 | 0.0757901 | 2(Loss) | true |
| simdjson (reflection) | 1012.34 | 0.514236 | 1206.39ms | 11812 | 30 | 98228.7 | 11127.5 | 0.539707 | 3(Loss) | true |
| Glaze | 965.775 | 0.535322 | 1197.47ms | 11812 | 320 | 1.2476e+06 | 11664 | 0.565595 | 4(Loss) | true |
| simdjson (ondemand) | 685.44 | 0.32393 | 1700.42ms | 11812 | 640 | 1.8138e+06 | 16434.4 | 0.696089 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2036 | 1.42919 | 620.751ms | 11812 | 80 | 500220 | 5532.8 | 0.0578704 | 1(Win) | true |
| Jsonifier (two-stage) | 1383.95 | 0.432182 | 928.707ms | 11812 | 640 | 791989 | 8139.6 | 1.06785 | 2(Loss) | true |
| simdjson (reflection) | 1094.61 | 0.501433 | 1169.67ms | 11812 | 80 | 213033 | 10291.2 | 1.06851 | 3(Loss) | true |
| Glaze | 1062.63 | 0.187168 | 1147.9ms | 11812 | 2560 | 1.00783e+06 | 10600.9 | 0.377805 | 4(Loss) | true |
| simdjson (ondemand) | 745.105 | 0.543252 | 1686.68ms | 11812 | 160 | 1.07928e+06 | 15118.4 | 0.494945 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10220.3 | 0.835329 | 112.485ms | 11812 | 1280 | 108504 | 1102.2 | 0.639153 | 1(Win) | true |
| simdjson (reflection) | 7912.31 | 0.662384 | 144.451ms | 11812 | 4890 | 434879 | 1423.71 | 0.627799 | 2(Loss) | true |
| Glaze | 1727.31 | 0.650562 | 689.022ms | 11812 | 320 | 576018 | 6521.6 | 1.59521 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10632.2 | 0.545233 | 105.993ms | 11812 | 2560 | 85429.1 | 1059.5 | 0.348006 | 1(Win) | true |
| simdjson (reflection) | 8159.23 | 0.51962 | 141.66ms | 11812 | 4890 | 251669 | 1380.62 | 0.888726 | 2(Loss) | true |
| Glaze | 1865.36 | 0.173795 | 614.649ms | 11812 | 4890 | 538648 | 6038.93 | 0.993897 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2433.26 | 0.698038 | 1008.08ms | 25388 | 320 | 1.54379e+06 | 9950.4 | 0.240616 | 1(Win) | true |
| Jsonifier (two-stage) | 2153.47 | 0.821548 | 1130.54ms | 25388 | 160 | 1.3651e+06 | 11243.2 | 0.0711035 | 2(Loss) | true |
| simdjson (reflection) | 1808.98 | 0.144955 | 1348.75ms | 25388 | 4890 | 1.84062e+06 | 13384.3 | 0.00898173 | 3(Loss) | true |
| Glaze | 1536.13 | 0.198033 | 1565.1ms | 25388 | 2560 | 2.4941e+06 | 15761.6 | 0.746842 | 4(Loss) | true |
| simdjson (ondemand) | 1307.37 | 0.16244 | 1870.3ms | 25388 | 2560 | 2.31678e+06 | 18519.5 | 0.356724 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2741.51 | 0.309849 | 962.145ms | 25388 | 1280 | 958496 | 8831.6 | 0.812748 | 1(Win) | true |
| Jsonifier (two-stage) | 2304.31 | 1.26433 | 1176.08ms | 25388 | 160 | 2.82369e+06 | 10507.2 | 0.0456621 | 2(Loss) | true |
| simdjson (reflection) | 1944.04 | 0.973705 | 1403.52ms | 25388 | 80 | 1.1765e+06 | 12454.4 | 0.620476 | 3(Loss) | true |
| Glaze | 1658.23 | 0.146393 | 1536.25ms | 25388 | 4890 | 2.23415e+06 | 14601 | 0.0752498 | 4(Loss) | true |
| simdjson (ondemand) | 1369.3 | 0.413492 | 1887.35ms | 25388 | 640 | 3.42119e+06 | 17682 | 1.20905 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 18379.7 | 0.455979 | 165.204ms | 31235 | 4890 | 267059 | 1620.71 | 0.765053 | 1(Win) | true |
| Glaze | 2720.27 | 1.12131 | 1106.76ms | 31235 | 80 | 1.20615e+06 | 10950.4 | 0 | 2(Loss) | true |
| simdjson (reflection) | 309.222 | 0.0952416 | 9653.57ms | 31235 | 1280 | 1.07747e+07 | 96332.2 | 0.269169 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 20712 | 0.734165 | 148.74ms | 31235 | 2560 | 285407 | 1438.2 | 0.704225 | 1(Win) | true |
| Glaze | 3056.06 | 0.730779 | 1007.57ms | 31235 | 40 | 202952 | 9747.2 | 0.109553 | 2(Loss) | true |
| simdjson (reflection) | 312.182 | 0.104955 | 9653.69ms | 31235 | 640 | 6.41886e+06 | 95418.8 | 0.0012576 | 3(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2407.28 | 0.444949 | 4591.48ms | 108313 | 640 | 2.33297e+07 | 42909.6 | 0.78797 | 1(Win) | true |
| Glaze | 1465.71 | 0.144083 | 7169.84ms | 108313 | 640 | 6.59897e+06 | 70474.8 | 0.0880522 | 2(Loss) | true |
| Jsonifier (two-stage) | 1397.76 | 0.206474 | 7356.89ms | 108313 | 2560 | 5.96029e+07 | 73900.8 | 0.719338 | 3(Loss) | true |
| simdjson (ondemand) | 1113.71 | 0.693439 | 9605.9ms | 108313 | 40 | 1.6546e+07 | 92748.8 | 0.202821 | 4(Loss) | true |
| simdjson (reflection) | 1085.7 | 0.44557 | 5028.68ms | 108313 | 640 | 1.15015e+08 | 95141.6 | 1.50646 | 5(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2575.58 | 1.38769 | 4095.94ms | 108313 | 320 | 9.91162e+07 | 40105.6 | 2.73372 | 1(Win) | true |
| Jsonifier (two-stage) | 1729.71 | 0.101413 | 6292.9ms | 108313 | 4890 | 1.79353e+07 | 59718.3 | 0.85055 | 2(Loss) | true |
| Glaze | 1357.36 | 2.86226 | 7558.81ms | 108313 | 30 | 1.42335e+08 | 76100.3 | 0.0336285 | 3(Loss) | true |
| simdjson (reflection) | 1229.6 | 0.225086 | 9077.37ms | 108313 | 2560 | 9.15308e+07 | 84007 | 0.615894 | 4(Loss) | true |
| simdjson (ondemand) | 1174.94 | 0.354071 | 9578.96ms | 108313 | 640 | 6.20139e+07 | 87915.2 | 0.93779 | 5(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13998.2 | 1.0821 | 774.737ms | 108313 | 40 | 255044 | 7379.2 | 0.202781 | 1(Win) | true |
| simdjson (reflection) | 7760.24 | 0.182822 | 1339.06ms | 108313 | 4890 | 2.89586e+06 | 13310.8 | 0.392506 | 2(Loss) | true |
| Glaze | 1793.44 | 0.230785 | 5796.37ms | 108313 | 2560 | 4.52314e+07 | 57596.1 | 2.25564 | 3(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14302.1 | 0.895491 | 748.54ms | 108313 | 80 | 334638 | 7222.4 | 0.044287 | 1(Win) | true |
| simdjson (reflection) | 7894.96 | 0.187517 | 1315.92ms | 108313 | 2560 | 1.54093e+06 | 13083.7 | 0.139673 | 2(Loss) | true |
| Glaze | 2046.51 | 0.135454 | 5219.58ms | 108313 | 4890 | 2.28575e+07 | 50473.9 | 0.282354 | 3(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2652.61 | 0.138026 | 7076.33ms | 183677 | 640 | 5.31699e+06 | 66036 | 0.524223 | 1(Win) | true |
| Jsonifier (two-stage) | 2039.4 | 0.157859 | 8598.3ms | 183677 | 4890 | 8.98989e+07 | 85891.9 | 0.331208 | 2(Loss) | true |
| Glaze | 1903.76 | 0.0874051 | 9301.03ms | 183677 | 1280 | 8.27885e+06 | 92011.8 | 0.47011 | 3(Loss) | true |
| simdjson (reflection) | 1809.11 | 0.462759 | 9818.1ms | 183677 | 40 | 8.03064e+06 | 96825.6 | 0.0595238 | 4(Loss) | true |
| simdjson (ondemand) | 1695.12 | 0.185411 | 5301.19ms | 183677 | 1280 | 4.69883e+07 | 103337 | 0.241729 | 5(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2786.32 | 1.25267 | 6801.23ms | 183677 | 80 | 4.96145e+07 | 62867.2 | 2.9156 | 1(Win) | true |
| Jsonifier (two-stage) | 2439.53 | 0.130195 | 8042.02ms | 183677 | 4890 | 4.27358e+07 | 71803.9 | 2.1609 | 2(Loss) | true |
| Glaze | 2075.08 | 0.165126 | 8935.43ms | 183677 | 320 | 6.2176e+06 | 84415.2 | 0.141406 | 3(Loss) | true |
| simdjson (ondemand) | 1776.88 | 0.072846 | 5136.38ms | 183677 | 2560 | 1.32021e+07 | 98581.6 | 0.11409 | 4(Loss) | true |
| simdjson (reflection) | 1561.98 | 0.468856 | 5616.87ms | 183677 | 1280 | 3.53871e+08 | 112145 | 0.401626 | 5(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12863 | 0.926825 | 1370.46ms | 213963 | 30 | 648505 | 15863.5 | 0.215633 | 1(Win) | true |
| Glaze | 1882.39 | 0.957324 | 5261.08ms | 213963 | 80 | 8.61522e+07 | 108400 | 2.38469 | 2(Loss) | true |
| simdjson (reflection) | 309.978 | 0.269389 | 8653.98ms | 213963 | 640 | 2.01259e+09 | 658277 | 2.06133 | 3(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16353.1 | 0.322156 | 1349.29ms | 213963 | 1280 | 2.06832e+06 | 12477.8 | 2.03348 | 1(Win) | true |
| Glaze | 2405.54 | 0.231985 | 8731.39ms | 213963 | 1280 | 4.95661e+07 | 84825.6 | 1.67473 | 2(Loss) | true |
| simdjson (reflection) | 290.133 | 0.294641 | 8546.25ms | 213963 | 640 | 2.74821e+09 | 703303 | 0.249793 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 634.39 | 0.418803 | 8705.16ms | 1834197 | 80 | 1.06682e+10 | 2.75734e+06 | 0.0392416 | 1(Win) | true |
| Jsonifier (two-stage) | 503.168 | 0.737205 | 5455.79ms | 1834197 | 30 | 1.97045e+10 | 3.47643e+06 | 1.08079 | 2(Loss) | true |
| simdjson (reflection) | 487.825 | 0.0824801 | 5415.15ms | 1834197 | 30 | 2.62412e+08 | 3.58577e+06 | 0.669442 | 3(Loss) | true |
| Glaze | 482.007 | 0.295616 | 5448.45ms | 1834197 | 40 | 4.60365e+09 | 3.62905e+06 | 0.0528197 | 4(Loss) | true |
| simdjson (ondemand) | 386.64 | 1.99708 | 6460.46ms | 1834197 | 30 | 2.44902e+11 | 4.52417e+06 | 0.195589 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 654.431 | 0.683041 | 9189.51ms | 1834197 | 40 | 1.33327e+10 | 2.6729e+06 | 2.21043 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 543.028 | 1.42309 | 5487.55ms | 1834197 | 30 | 6.30427e+10 | 3.22125e+06 | 0.582562 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 538.307 | 0.184853 | 5451.38ms | 1834197 | 40 | 1.44327e+09 | 3.2495e+06 | 0.0534686 | 2(Tie) | true |
| Glaze | 509.006 | 0.604368 | 5650.25ms | 1834197 | 40 | 1.72548e+10 | 3.43656e+06 | 1.60652 | 4(Loss) | true |
| simdjson (ondemand) | 470.594 | 0.222437 | 6168.07ms | 1834197 | 80 | 5.46893e+09 | 3.71706e+06 | 0.721184 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1161.18 | 0.388288 | 9330.95ms | 1834197 | 160 | 5.47418e+09 | 1.50642e+06 | 0.964809 | 1(Win) | true |
| Glaze | 862.597 | 0.163215 | 6457.42ms | 1833577 | 40 | 4.37887e+08 | 2.02717e+06 | 1.11798 | 2(Loss) | true |
| simdjson (reflection) | 744.355 | 0.825262 | 8262.67ms | 1922245 | 30 | 1.23926e+10 | 2.4628e+06 | 0.998404 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1258.11 | 0.314001 | 8833.07ms | 1834197 | 320 | 6.09916e+09 | 1.39037e+06 | 1.00856 | 1(Win) | true |
| Glaze | 858.184 | 0.20331 | 6715.38ms | 1833577 | 40 | 6.86463e+08 | 2.0376e+06 | 0.516619 | 2(Loss) | true |
| simdjson (reflection) | 720.675 | 0.429176 | 7858.76ms | 1922245 | 160 | 1.90691e+10 | 2.54372e+06 | 4.24706 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1854.11 | 0.944528 | 5774.08ms | 7351818 | 40 | 5.10279e+10 | 3.78145e+06 | 2.10659 | 1(Win) | true |
| Jsonifier (two-stage) | 1763.72 | 0.354918 | 6169.52ms | 7351818 | 30 | 5.97186e+09 | 3.97526e+06 | 0.632656 | 2(Loss) | true |
| simdjson (reflection) | 1618.44 | 0.399733 | 6531.63ms | 7351818 | 40 | 1.19949e+10 | 4.3321e+06 | 0.859156 | 3(Loss) | true |
| Glaze | 1450.04 | 0.25475 | 7361.17ms | 7351818 | 80 | 1.21381e+10 | 4.83521e+06 | 4.02442 | 4(Loss) | true |
| simdjson (ondemand) | 1430.55 | 0.401323 | 7368.76ms | 7351818 | 40 | 1.54751e+10 | 4.90108e+06 | 0.00113171 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2116.59 | 0.228394 | 5876.82ms | 7351818 | 40 | 2.28953e+09 | 3.31251e+06 | 0.19848 | 1(Win) | true |
| Jsonifier (two-stage) | 1857.04 | 0.551845 | 6230.86ms | 7351818 | 30 | 1.30227e+10 | 3.77549e+06 | 1.30364 | 2(Loss) | true |
| simdjson (reflection) | 1810.34 | 0.243525 | 6587.04ms | 7351818 | 30 | 2.66856e+09 | 3.87289e+06 | 0.899614 | 3(Loss) | true |
| simdjson (ondemand) | 1610.55 | 0.255799 | 7236.93ms | 7351818 | 30 | 3.72014e+09 | 4.35331e+06 | 0.973467 | 4(Loss) | true |
| Glaze | 1567.39 | 0.265786 | 7370.37ms | 7351818 | 30 | 4.24052e+09 | 4.47318e+06 | 0.0796769 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6420.73 | 0.196359 | 9483.72ms | 9930848 | 320 | 2.68446e+09 | 1.47503e+06 | 0.905791 | 1(Win) | true |
| Glaze | 2904.38 | 0.873208 | 10295.8ms | 9930228 | 30 | 2.43203e+10 | 3.26066e+06 | 3.1158 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 306.215 | 0.719602 | 10010.4ms | 10018896 | 30 | 1.51249e+12 | 3.12027e+07 | 5.50805 | -(Loss) | false |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6284.68 | 0.330311 | 9288.14ms | 9930848 | 160 | 3.96436e+09 | 1.50697e+06 | 0.331721 | 1(Win) | true |
| Glaze | 2862.47 | 0.445897 | 10038.6ms | 9930228 | 80 | 1.74099e+10 | 3.3084e+06 | 0.668935 | 2(Loss) | true |
| simdjson (reflection) | 302.553 | 0.82639 | 9986.72ms | 10018896 | 30 | 2.04329e+12 | 3.15805e+07 | 4.7265 | 3(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 668.657 | 0.862867 | 8074.8ms | 1834197 | 30 | 1.5286e+10 | 2.61603e+06 | 1.66341 | 1(Win) | true |
| Jsonifier (two-stage) | 534.547 | 0.160842 | 10188.7ms | 1834197 | 40 | 1.1081e+09 | 3.27235e+06 | 0.365887 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 455.772 | 0.611833 | 5443.49ms | 1834197 | 80 | 4.41116e+10 | 3.83794e+06 | 0.855969 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 445.579 | 1.06089 | 6062.51ms | 1834197 | 30 | 5.20361e+10 | 3.92573e+06 | 3.83331 | 3(Tie) | true |
| simdjson (ondemand) | 416.788 | 0.185791 | 6343.55ms | 1834197 | 80 | 4.86407e+09 | 4.19692e+06 | 0.435898 | 5(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 787.334 | 0.081915 | 7939.88ms | 1834197 | 40 | 1.32483e+08 | 2.22171e+06 | 0.474866 | 1(Win) | true |
| Jsonifier (two-stage) | 601.546 | 0.371296 | 5085.82ms | 1834197 | 30 | 3.49716e+09 | 2.90789e+06 | 0.486227 | 2(Loss) | true |
| Glaze | 537.411 | 0.432244 | 5207.02ms | 1834197 | 40 | 7.91767e+09 | 3.25491e+06 | 0.0141551 | 3(Loss) | true |
| simdjson (reflection) | 491.383 | 0.91661 | 5953.36ms | 1834197 | 80 | 8.51747e+10 | 3.5598e+06 | 1.41142 | 4(Loss) | true |
| simdjson (ondemand) | 426.73 | 1.11896 | 6645.77ms | 1834197 | 30 | 6.31158e+10 | 4.09914e+06 | 1.04034 | 5(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1315.48 | 0.28592 | 8732.09ms | 1834197 | 40 | 5.7819e+08 | 1.32972e+06 | 0.606116 | 1(Win) | true |
| Glaze | 792.972 | 1.60895 | 6996.08ms | 1833577 | 30 | 3.77648e+10 | 2.20517e+06 | 0.346296 | 2(Loss) | true |
| simdjson (reflection) | 719.229 | 0.791139 | 8121.97ms | 1922245 | 80 | 3.25296e+10 | 2.54884e+06 | 0.585992 | 3(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1282.49 | 0.520295 | 9047.68ms | 1834197 | 160 | 8.05756e+09 | 1.36393e+06 | 0.470141 | 1(Win) | true |
| Glaze | 846.07 | 1.11554 | 6483.46ms | 1833577 | 30 | 1.59468e+10 | 2.06677e+06 | 0.168326 | 2(Loss) | true |
| simdjson (reflection) | 694.357 | 0.432004 | 7939.6ms | 1922245 | 160 | 2.08136e+10 | 2.64013e+06 | 1.38308 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1985.6 | 0.337796 | 5125.71ms | 7351818 | 40 | 5.69082e+09 | 3.53105e+06 | 0.21227 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 1658.46 | 0.492665 | 6831.14ms | 7351818 | 40 | 1.73517e+10 | 4.22755e+06 | 3.72079 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1623.46 | 1.02814 | 6118.67ms | 7351818 | 30 | 5.91472e+10 | 4.3187e+06 | 0.155944 | 2(Tie) | true |
| simdjson (ondemand) | 1466.14 | 0.32962 | 7350.1ms | 7351818 | 30 | 7.45392e+09 | 4.7821e+06 | 0.249021 | 4(Loss) | true |
| Glaze | 1371.43 | 1.17281 | 7663.17ms | 7351818 | 40 | 1.43801e+11 | 5.11237e+06 | 2.81975 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2191.97 | 0.704721 | 5204.02ms | 7351818 | 40 | 2.03242e+10 | 3.1986e+06 | 0.0891183 | 1(Win) | true |
| Jsonifier (two-stage) | 1865.03 | 0.720014 | 6027.67ms | 7351818 | 30 | 2.19796e+10 | 3.75931e+06 | 2.10133 | 2(Loss) | true |
| simdjson (reflection) | 1609.41 | 0.408955 | 6932.16ms | 7351818 | 80 | 2.5392e+10 | 4.3564e+06 | 0.55022 | 3(Loss) | true |
| Glaze | 1578.92 | 0.148751 | 7296.78ms | 7351818 | 80 | 3.49044e+09 | 4.44053e+06 | 0.812064 | 4(Loss) | true |
| simdjson (ondemand) | 1540.27 | 0.556019 | 7413.78ms | 7351818 | 40 | 2.56234e+10 | 4.55197e+06 | 1.11727 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 6221.7 | 0.965252 | 9851.45ms | 9930848 | 40 | 8.63569e+09 | 1.52222e+06 | 5.22527 | -(Win) | false |
| Glaze | 2557.63 | 0.690173 | 5756.35ms | 9930228 | 30 | 1.95921e+10 | 3.70272e+06 | 2.84254 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 271.537 | 0.685279 | 10610.1ms | 10018896 | 30 | 1.74436e+12 | 3.51877e+07 | 5.44351 | -(Loss) | false |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6010.67 | 1.05015 | 5205.87ms | 9930848 | 30 | 8.21395e+09 | 1.57566e+06 | 3.93804 | 1(Win) | true |
| Glaze | 3132.97 | 0.182593 | 9640.83ms | 9930228 | 160 | 4.87409e+09 | 3.02275e+06 | 0.455459 | 2(Loss) | true |
| simdjson (reflection) | 271.912 | 0.678126 | 10651.5ms | 10018896 | 30 | 1.70343e+12 | 3.51391e+07 | 1.7134 | 3(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 946.436 | 0.217663 | 5981.01ms | 461466 | 160 | 1.63903e+08 | 464995 | 0.196433 | 1(Win) | true |
| Jsonifier (two-stage) | 821.168 | 0.485173 | 7007.99ms | 461466 | 320 | 2.16351e+09 | 535930 | 2.25599 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 727.297 | 0.144347 | 7664.84ms | 461466 | 640 | 4.88259e+08 | 605101 | 0.0168595 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 722.43 | 1.30964 | 7872.08ms | 461466 | 40 | 2.54597e+09 | 609178 | 1.57511 | 3(Tie) | true |
| simdjson (ondemand) | 598.106 | 0.598228 | 9574.54ms | 461466 | 30 | 5.81271e+08 | 735804 | 0.884511 | 5(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1395.76 | 0.185025 | 5637.28ms | 461466 | 320 | 1.08911e+08 | 315305 | 0.881459 | 1(Win) | true |
| Jsonifier (two-stage) | 1172.34 | 0.474868 | 6404.59ms | 461466 | 640 | 2.03374e+09 | 375392 | 1.73818 | 2(Loss) | true |
| Glaze | 928.644 | 0.0794044 | 7522.58ms | 461466 | 640 | 9.06255e+07 | 473904 | 0.231213 | 3(Loss) | true |
| simdjson (reflection) | 894.512 | 0.198304 | 7660.87ms | 461466 | 40 | 3.80744e+07 | 491987 | 0.00130086 | 4(Loss) | true |
| simdjson (ondemand) | 789.552 | 0.108801 | 8630.24ms | 461466 | 640 | 2.35378e+08 | 557390 | 0.384173 | 5(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11451.3 | 0.215939 | 3922.91ms | 461466 | 640 | 4.40768e+06 | 38431.2 | 0.116436 | 1(Win) | true |
| simdjson (reflection) | 7909.31 | 0.210669 | 5827ms | 461466 | 1280 | 1.75878e+07 | 55641.8 | 0.357084 | 2(Loss) | true |
| Glaze | 2170.82 | 0.0888463 | 5218.31ms | 461466 | 1280 | 4.15261e+07 | 202729 | 0.255647 | 3(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11535.6 | 0.395465 | 3894.24ms | 461466 | 160 | 3.64195e+06 | 38150.4 | 0.109161 | 1(Win) | true |
| simdjson (reflection) | 7790.58 | 0.0827779 | 5596.68ms | 461466 | 4890 | 1.06925e+07 | 56489.8 | 0.629138 | 2(Loss) | true |
| Glaze | 2322.08 | 0.198494 | 9763.04ms | 461466 | 80 | 1.13216e+07 | 189523 | 0.0878764 | 3(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1269.86 | 0.230083 | 6995.96ms | 728486 | 40 | 6.3381e+07 | 547098 | 1.01467 | 1(Win) | true |
| Jsonifier (two-stage) | 1100.32 | 0.180713 | 8068.96ms | 728486 | 30 | 3.90576e+07 | 631398 | 0.279186 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1059 | 0.445397 | 8408.83ms | 728486 | 160 | 1.36606e+09 | 656035 | 2.67141 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 1051.79 | 0.222317 | 8493.31ms | 728486 | 30 | 6.46926e+07 | 660531 | 0.130311 | 3(Tie) | true |
| simdjson (ondemand) | 904.562 | 1.04631 | 10057.6ms | 728486 | 40 | 2.58311e+09 | 768038 | 0.470513 | 5(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1749.05 | 0.098768 | 6437.48ms | 728486 | 30 | 4.61735e+06 | 397210 | 0.156582 | 1(Win) | true |
| Jsonifier (two-stage) | 1520.11 | 0.284937 | 8280.73ms | 728486 | 640 | 1.08536e+09 | 457032 | 1.62833 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1305.94 | 0.282579 | 8115.82ms | 728486 | 30 | 6.77956e+07 | 531985 | 0.386461 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1297.63 | 0.207531 | 8173.02ms | 728486 | 640 | 7.90105e+08 | 535390 | 1.2361 | 3(Tie) | true |
| simdjson (ondemand) | 1056.84 | 0.456605 | 9896.24ms | 728486 | 320 | 2.88307e+09 | 657373 | 0.170328 | 5(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14613.7 | 0.122337 | 5503.4ms | 837491 | 2560 | 1.14444e+07 | 54653.6 | 0.467308 | 1(Win) | true |
| Glaze | 2516.16 | 0.145099 | 8257.54ms | 837491 | 640 | 1.35766e+08 | 317426 | 0.668277 | 2(Loss) | true |
| simdjson (reflection) | 319.74 | 0.261848 | 7851.61ms | 837491 | 80 | 3.42259e+09 | 2.49795e+06 | 0.0828154 | 3(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14781.3 | 0.113136 | 5564.22ms | 837491 | 2560 | 9.56689e+06 | 54033.9 | 0.337349 | 1(Win) | true |
| Glaze | 2680.43 | 0.23324 | 7552.69ms | 837491 | 640 | 3.09127e+08 | 297972 | 0.123617 | 2(Loss) | true |
| simdjson (reflection) | 319.291 | 0.516395 | 7997.55ms | 837491 | 30 | 5.0058e+09 | 2.50146e+06 | 0.434781 | 3(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 4840.8 | 0.460343 | 5158.66ms | 466906 | 80 | 1.43442e+07 | 91984 | 0.100785 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 4832.9 | 0.201754 | 5043.48ms | 466906 | 30 | 1.0366e+06 | 92134.4 | 0.184894 | 1(Tie) | true |
| simdjson (reflection) | 3919.44 | 0.227488 | 6030.07ms | 466906 | 640 | 4.27472e+07 | 113607 | 0.100597 | 3(Loss) | true |
| simdjson (ondemand) | 3697.03 | 0.102286 | 6427.23ms | 466906 | 2560 | 3.88532e+07 | 120442 | 2.12337 | 4(Loss) | true |
| Glaze | 2308.72 | 0.154237 | 5215.75ms | 466906 | 1280 | 1.13267e+08 | 192867 | 0.407011 | 5(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5338.38 | 0.191109 | 5216.24ms | 466906 | 320 | 8.13116e+06 | 83410.4 | 0.000959122 | 1(Win) | true |
| Jsonifier (two-stage) | 4736.01 | 0.558383 | 5104.64ms | 466906 | 640 | 1.76392e+08 | 94019.2 | 1.39421 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 3830.77 | 0.247541 | 6048.06ms | 466906 | 1280 | 1.05972e+08 | 116237 | 0.515411 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3815.8 | 0.24146 | 6167.76ms | 466906 | 320 | 2.54056e+07 | 116693 | 0.315729 | 3(Tie) | true |
| Glaze | 2389.01 | 0.553605 | 5013.45ms | 466906 | 30 | 3.19406e+07 | 186385 | 0.155421 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4873.04 | 0.412258 | 6523.92ms | 631514 | 640 | 1.66144e+08 | 123590 | 0.631522 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4786.76 | 1.20909 | 6597.34ms | 631514 | 160 | 3.70273e+08 | 125818 | 2.65412 | 1(Tie) | true |
| simdjson (reflection) | 4353.76 | 0.0610994 | 7225ms | 631514 | 2560 | 1.82873e+07 | 138331 | 1.25407 | 3(Loss) | true |
| simdjson (ondemand) | 4040.65 | 0.252691 | 7702.52ms | 631514 | 2560 | 3.63147e+08 | 149050 | 1.47809 | 4(Loss) | true |
| Glaze | 2772.44 | 0.28921 | 6251.71ms | 631514 | 320 | 1.26304e+08 | 217230 | 0.617804 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 5191.31 | 0.416282 | 6565.09ms | 631514 | 40 | 9.32926e+06 | 116013 | 0.2037 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 5162.26 | 0.218661 | 6211.75ms | 631514 | 160 | 1.04124e+07 | 116666 | 0.856607 | 1(Tie) | true |
| simdjson (ondemand) | 4579.37 | 0.923249 | 7676.17ms | 631514 | 30 | 4.42297e+07 | 131516 | 0.0129786 | 3(Loss) | true |
| simdjson (reflection) | 4413.13 | 0.0603674 | 7045.6ms | 631514 | 2560 | 1.73747e+07 | 136470 | 0.121787 | 4(Loss) | true |
| Glaze | 2633.28 | 1.88021 | 6077.91ms | 631514 | 30 | 5.54763e+08 | 228710 | 0.792123 | 5(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1712.94 | 0.253905 | 6496.1ms | 466906 | 1280 | 5.57603e+08 | 259948 | 2.01632 | 1(Win) | true |
| Glaze | 1521.09 | 0.0660653 | 7565.67ms | 466906 | 1280 | 4.7875e+07 | 292736 | 0.227273 | 2(Loss) | true |
| Jsonifier (two-stage) | 1383.66 | 1.58304 | 8128.2ms | 466906 | 40 | 1.03812e+09 | 321811 | 0.136082 | 3(Loss) | true |
| simdjson (reflection) | 1207.91 | 0.076221 | 9416.77ms | 466906 | 640 | 5.05264e+07 | 368633 | 0.109388 | 4(Loss) | true |
| simdjson (ondemand) | 940.786 | 0.106875 | 6053.31ms | 466906 | 640 | 1.6376e+08 | 473302 | 0.712924 | 5(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2285.96 | 1.2593 | 5922.99ms | 466906 | 80 | 4.81356e+08 | 194787 | 0.296469 | 1(Win) | true |
| Glaze | 1888.88 | 0.1601 | 7071.52ms | 466906 | 160 | 2.27905e+07 | 235736 | 0.391796 | 2(Loss) | true |
| Jsonifier (two-stage) | 1730.1 | 1.35822 | 7257.66ms | 466906 | 80 | 9.77568e+08 | 257370 | 2.33351 | 3(Loss) | true |
| simdjson (reflection) | 1346.98 | 0.168326 | 9462.85ms | 466906 | 30 | 9.28871e+06 | 330573 | 0.177798 | 4(Loss) | true |
| simdjson (ondemand) | 1060.83 | 0.143954 | 5741.7ms | 466906 | 320 | 1.16832e+08 | 419742 | 1.03562 | 5(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16338.1 | 0.124499 | 2863.86ms | 475954 | 1280 | 1.53132e+06 | 27782 | 0.0806928 | 1(Win) | true |
| simdjson (reflection) | 12108.5 | 0.141812 | 3868.52ms | 475954 | 640 | 1.80865e+06 | 37486.4 | 0.0085357 | 2(Loss) | true |
| Glaze | 3734.84 | 0.0555458 | 6293.61ms | 475954 | 2560 | 1.16662e+07 | 121533 | 0.163884 | 3(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16458.5 | 0.126953 | 2765.76ms | 475954 | 1280 | 1.5691e+06 | 27578.8 | 0.135068 | 1(Win) | true |
| simdjson (reflection) | 12229.1 | 0.226269 | 3799.01ms | 475954 | 160 | 1.12853e+06 | 37116.8 | 0.326545 | 2(Loss) | true |
| Glaze | 4110.27 | 0.148471 | 5648.09ms | 475954 | 320 | 8.60247e+06 | 110432 | 0.112883 | 3(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2178.75 | 0.199499 | 8017.53ms | 631514 | 160 | 4.86579e+07 | 276424 | 0.0584951 | 1(Win) | true |
| Glaze | 1939.57 | 0.349051 | 8061.05ms | 631514 | 80 | 9.39775e+07 | 310512 | 0.924635 | 2(Loss) | true |
| Jsonifier (two-stage) | 1899.11 | 0.494327 | 8161.62ms | 631514 | 80 | 1.966e+08 | 317126 | 1.66602 | 3(Loss) | true |
| simdjson (reflection) | 1622.91 | 0.329191 | 9493.56ms | 631514 | 30 | 4.47706e+07 | 371098 | 0.0666406 | 4(Loss) | true |
| simdjson (ondemand) | 1275.07 | 0.108871 | 6074.52ms | 631514 | 640 | 1.6924e+08 | 472334 | 0.445903 | 5(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2655.04 | 0.123899 | 6813.99ms | 631514 | 640 | 5.05524e+07 | 226836 | 0.236439 | 1(Win) | true |
| Jsonifier (two-stage) | 2513.4 | 0.311327 | 7257.39ms | 631514 | 160 | 8.90424e+07 | 239619 | 1.11978 | 2(Loss) | true |
| Glaze | 2367.93 | 0.100369 | 7439.63ms | 631514 | 1280 | 8.34131e+07 | 254340 | 0.0897242 | 3(Loss) | true |
| simdjson (reflection) | 1756.72 | 0.220198 | 9771.15ms | 631514 | 640 | 3.64727e+08 | 342831 | 0.51664 | 4(Loss) | true |
| simdjson (ondemand) | 1437.48 | 0.174618 | 5780.27ms | 631514 | 160 | 8.56364e+07 | 418968 | 0.0630517 | 5(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17645.5 | 0.120844 | 4103.1ms | 716365 | 640 | 1.40096e+06 | 38716.8 | 0.084646 | 1(Win) | true |
| Glaze | 3513.68 | 0.385883 | 9595ms | 716365 | 640 | 3.60277e+08 | 194434 | 0.868574 | 2(Loss) | true |
| simdjson (reflection) | 419.817 | 0.11273 | 5062.67ms | 716365 | 160 | 5.38452e+08 | 1.62733e+06 | 0.803749 | 3(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17835.7 | 0.190975 | 4073.85ms | 716365 | 40 | 214042 | 38304 | 0.0167112 | 1(Win) | true |
| Glaze | 4641.97 | 0.313321 | 7847.53ms | 716365 | 40 | 8.50556e+06 | 147174 | 0.375462 | 2(Loss) | true |
| simdjson (reflection) | 395.576 | 0.46777 | 5425.73ms | 716365 | 160 | 1.04422e+10 | 1.72705e+06 | 1.75214 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1517.58 | 0.867763 | 174.28ms | 2632 | 1280 | 263684 | 1654 | 1.05288 | 1(Win) | true |
| Jsonifier (two-stage) | 1380.22 | 0.683101 | 186.651ms | 2632 | 1280 | 197540 | 1818.6 | 1.73979 | 2(Loss) | true |
| Glaze | 1165.52 | 0.9713 | 216.918ms | 2632 | 320 | 140019 | 2153.6 | 0.074239 | 3(Loss) | true |
| simdjson (reflection) | 1077.28 | 0.608215 | 239.509ms | 2632 | 1280 | 257061 | 2330 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 852.06 | 0.209768 | 299.037ms | 2632 | 4890 | 186732 | 2945.88 | 0.0480215 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2041.74 | 0.503368 | 155.012ms | 2632 | 4890 | 187262 | 1229.38 | 0.0794423 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1802.95 | 1.02139 | 169.263ms | 2632 | 1280 | 258820 | 1392.2 | 0.302594 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1795.14 | 0.517376 | 171.761ms | 2632 | 4890 | 255916 | 1398.26 | 0.174015 | 2(Tie) | true |
| simdjson (reflection) | 1345.16 | 0.54915 | 226.62ms | 2632 | 1280 | 134405 | 1866 | 0.0856714 | 4(Loss) | true |
| simdjson (ondemand) | 1117.77 | 1.24748 | 252.747ms | 2632 | 320 | 251121 | 2245.6 | 0.177809 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9338.97 | 2.36919 | 29.7032ms | 2632 | 4890 | 198281 | 268.774 | 0.711554 | 1(Win) | true |
| simdjson (reflection) | 6000.79 | 1.7464 | 43.275ms | 2632 | 4890 | 260948 | 418.29 | 1.33004 | 2(Loss) | true |
| Glaze | 2873.62 | 0.617142 | 90.9719ms | 2632 | 4890 | 142100 | 873.489 | 0.694776 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10631.1 | 2.64011 | 28.6641ms | 2632 | 4890 | 190006 | 236.106 | 3.55133 | 1(Win) | true |
| simdjson (reflection) | 6943.49 | 3.01926 | 37.2099ms | 2632 | 2560 | 304970 | 361.5 | 0.696379 | 2(Loss) | true |
| Glaze | 3096.3 | 0.740091 | 84.5571ms | 2632 | 4890 | 176020 | 810.667 | 0.72896 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1673.37 | 0.354431 | 195.353ms | 3370 | 2560 | 118625 | 1920.6 | 0.290728 | 1(Win) | true |
| Jsonifier | 1523.48 | 0.247259 | 214.871ms | 3370 | 4890 | 133045 | 2109.57 | 0.0600315 | 2(Loss) | true |
| Glaze | 1408.61 | 1.58674 | 250.343ms | 3370 | 160 | 209705 | 2281.6 | 0.140056 | 3(Loss) | true |
| simdjson (reflection) | 1284.99 | 0.431107 | 248.939ms | 3370 | 2560 | 297626 | 2501.1 | 1.6129 | 4(Loss) | true |
| simdjson (ondemand) | 979.364 | 0.320535 | 336.998ms | 3370 | 2560 | 283244 | 3281.6 | 0.635863 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2124.37 | 0.483349 | 182.833ms | 3370 | 4890 | 261474 | 1512.86 | 0.0701503 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1980.94 | 1.23348 | 196.766ms | 3370 | 640 | 256308 | 1622.4 | 0.245942 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 1924.02 | 1.66151 | 194.694ms | 3370 | 320 | 246489 | 1670.4 | 0.384615 | 2(Tie) | true |
| simdjson (reflection) | 1582.14 | 0.22198 | 232.487ms | 3370 | 4890 | 99427.6 | 2031.35 | 0.636718 | 4(Loss) | true |
| simdjson (ondemand) | 1411.11 | 0.29117 | 262.136ms | 3370 | 4890 | 215051 | 2277.56 | 0.146329 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10386.4 | 3.02465 | 36.61ms | 3643 | 2560 | 262049 | 334.5 | 0.505651 | 1(Win) | true |
| Glaze | 3672.46 | 0.535469 | 97.3949ms | 3682 | 4890 | 128184 | 956.152 | 0.488928 | 2(Loss) | true |
| simdjson (reflection) | 345.036 | 0.172017 | 1033.4ms | 3643 | 640 | 192004 | 10069.2 | 0.0833532 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11869.7 | 2.2345 | 31.532ms | 3643 | 4890 | 209175 | 292.699 | 2.44962 | 1(Win) | true |
| Glaze | 4420.23 | 1.09072 | 82.825ms | 3682 | 2560 | 192197 | 794.4 | 2.11927 | 2(Loss) | true |
| simdjson (reflection) | 349.106 | 0.137185 | 1026.21ms | 3643 | 2560 | 477153 | 9951.8 | 0.0662757 | 3(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 754.763 | 0.279124 | 592.481ms | 4630 | 2560 | 682614 | 5850.2 | 1.17572 | 1(Win) | true |
| Jsonifier (two-stage) | 622.534 | 0.79707 | 726.827ms | 4630 | 320 | 1.02277e+06 | 7092.8 | 0.795816 | 2(Loss) | true |
| simdjson (reflection) | 574.557 | 0.121778 | 775.54ms | 4630 | 4890 | 428297 | 7685.08 | 0.0361626 | 3(Loss) | true |
| Glaze | 515.686 | 0.420487 | 883.66ms | 4630 | 320 | 414807 | 8562.4 | 0.0093423 | 4(Loss) | true |
| simdjson (ondemand) | 411.434 | 0.403029 | 1047.06ms | 4630 | 1280 | 2.39466e+06 | 10732 | 0.138096 | 5(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1001.34 | 1.85329 | 607.776ms | 4630 | 40 | 267143 | 4409.6 | 0.433526 | 1(Win) | true |
| Jsonifier (two-stage) | 800.84 | 1.0511 | 714.968ms | 4630 | 80 | 268687 | 5513.6 | 0.173812 | 2(Loss) | true |
| simdjson (reflection) | 670.175 | 0.300932 | 775.246ms | 4630 | 1280 | 503191 | 6588.6 | 0.887538 | 3(Loss) | true |
| Glaze | 596.132 | 1.31461 | 929.36ms | 4630 | 30 | 284441 | 7406.93 | 0.686499 | 4(Loss) | true |
| simdjson (ondemand) | 525.156 | 0.467236 | 993.31ms | 4630 | 160 | 246932 | 8408 | 0.095057 | 5(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2083.78 | 0.357617 | 209.041ms | 4630 | 4890 | 280803 | 2118.99 | 4.07097 | 1(Win) | true |
| Glaze | 1657.75 | 0.281676 | 269.736ms | 4630 | 4890 | 275253 | 2663.55 | 0.606298 | 2(Loss) | true |
| simdjson (reflection) | 910.922 | 0.200417 | 494.96ms | 4630 | 2560 | 241607 | 4847.3 | 0.0556701 | 3(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2098.83 | 0.79274 | 209.652ms | 4630 | 1280 | 356025 | 2103.8 | 3.30024 | 1(Win) | true |
| Glaze | 1933.74 | 0.565742 | 233.468ms | 4630 | 1280 | 213605 | 2283.4 | 0.253364 | 2(Loss) | true |
| simdjson (reflection) | 913.598 | 0.206301 | 491.596ms | 4630 | 2560 | 254505 | 4833.1 | 0.134309 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1584.35 | 0.176676 | 697.175ms | 11579 | 2560 | 388184 | 6969.8 | 0.641501 | 1(Win) | true |
| Jsonifier (two-stage) | 1529.11 | 0.339987 | 768.784ms | 11579 | 320 | 192904 | 7221.6 | 0.210924 | 2(Loss) | true |
| simdjson (reflection) | 1210.1 | 0.217171 | 929.132ms | 11579 | 4890 | 1.92048e+06 | 9125.33 | 1.60206 | 3(Loss) | true |
| Glaze | 1048.93 | 0.141374 | 1072.68ms | 11579 | 2560 | 567063 | 10527.5 | 0.0484211 | 4(Loss) | true |
| simdjson (ondemand) | 965.411 | 0.283095 | 1165.57ms | 11579 | 4890 | 5.12732e+06 | 11438.2 | 2.95711 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1919.38 | 0.376994 | 719.041ms | 11579 | 640 | 301071 | 5753.2 | 0.188075 | 1(Win) | true |
| Jsonifier (two-stage) | 1687.33 | 0.739039 | 807.392ms | 11579 | 640 | 1.49711e+06 | 6544.4 | 1.02238 | 2(Loss) | true |
| simdjson (reflection) | 1399.64 | 1.40985 | 923.989ms | 11579 | 320 | 3.95917e+06 | 7889.6 | 0.584677 | 3(Loss) | true |
| Glaze | 1166.62 | 0.173235 | 1090.39ms | 11579 | 2560 | 688329 | 9465.5 | 0.265879 | 4(Loss) | true |
| simdjson (ondemand) | 1033.69 | 0.432723 | 1173.52ms | 11579 | 4890 | 1.04495e+07 | 10682.7 | 1.89369 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7194.57 | 0.27878 | 196.551ms | 14795 | 4890 | 146168 | 1961.15 | 0.742203 | 1(Win) | true |
| Glaze | 2885.87 | 0.448341 | 488.111ms | 14795 | 2560 | 1.23008e+06 | 4889.2 | 0.638134 | 2(Loss) | true |
| simdjson (reflection) | 286.878 | 0.0881026 | 4944.69ms | 14795 | 2560 | 4.80678e+06 | 49183.4 | 0.043898 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7346.46 | 0.473187 | 192.471ms | 14795 | 2560 | 211436 | 1920.6 | 0.528278 | 1(Win) | true |
| Glaze | 3688.21 | 0.84588 | 422.403ms | 14795 | 160 | 167547 | 3825.6 | 0.716091 | 2(Loss) | true |
| simdjson (reflection) | 261.832 | 1.11546 | 5106.89ms | 14795 | 80 | 2.89055e+07 | 53888 | 1.21409 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1166.4 | 0.669416 | 274.152ms | 3223 | 1280 | 398317 | 2635.2 | 2.34581 | 1(Win) | true |
| Jsonifier (two-stage) | 988.834 | 0.240969 | 316.198ms | 3223 | 2560 | 143627 | 3108.4 | 0.0514469 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 887.735 | 1.62146 | 363.4ms | 3223 | 80 | 252148 | 3462.4 | 0.368324 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 850.026 | 1.55462 | 378.506ms | 3223 | 80 | 252811 | 3616 | 0.35524 | 3(Tie) | true |
| simdjson (ondemand) | 824.311 | 0.375084 | 381.441ms | 3223 | 1280 | 250384 | 3728.8 | 0.182032 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1800.11 | 0.418066 | 232.39ms | 3223 | 4890 | 249185 | 1707.5 | 0.163463 | 1(Win) | true |
| Jsonifier (two-stage) | 1289.25 | 0.436195 | 298.48ms | 3223 | 2560 | 276854 | 2384.1 | 0.45083 | 2(Loss) | true |
| Glaze | 1132.15 | 0.331772 | 343.145ms | 3223 | 4890 | 396734 | 2714.91 | 0.34472 | 3(Loss) | true |
| simdjson (reflection) | 1062.24 | 0.636037 | 385.387ms | 3223 | 320 | 108391 | 2893.6 | 0.57724 | 4(Loss) | true |
| simdjson (ondemand) | 1032.41 | 0.511165 | 353.258ms | 3223 | 640 | 148224 | 2977.2 | 0.120773 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8531.29 | 1.9132 | 38.604ms | 3223 | 4890 | 232339 | 360.285 | 0.198154 | 1(Win) | true |
| simdjson (reflection) | 7424.38 | 3.34213 | 44.15ms | 3223 | 1280 | 245051 | 414 | 0.0965251 | 2(Loss) | true |
| Glaze | 1850.73 | 3.23278 | 190.361ms | 3223 | 80 | 230610 | 1660.8 | 0.581395 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9469.73 | 2.07171 | 34.6092ms | 3223 | 4890 | 221113 | 324.581 | 0.334089 | 1(Win) | true |
| simdjson (reflection) | 8157.36 | 3.62594 | 41.002ms | 3223 | 1280 | 238932 | 376.8 | 1.15425 | 2(Loss) | true |
| Glaze | 2076.82 | 0.731919 | 150.032ms | 3223 | 2560 | 300393 | 1480 | 0.31178 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1699.79 | 0.312109 | 329.205ms | 5839 | 2560 | 267634 | 3276 | 0.429185 | 1(Win) | true |
| Jsonifier (two-stage) | 1589.23 | 0.319073 | 355.026ms | 5839 | 2560 | 319981 | 3503.9 | 0.248913 | 2(Loss) | true |
| simdjson (reflection) | 1367.24 | 0.400472 | 415.335ms | 5839 | 320 | 85129.4 | 4072.8 | 0.644028 | 3(Loss) | true |
| simdjson (ondemand) | 1306.72 | 0.326653 | 437.544ms | 5839 | 4890 | 947530 | 4261.43 | 0.7931 | 4(Loss) | true |
| Glaze | 1168.06 | 0.341443 | 473.945ms | 5839 | 2560 | 678300 | 4767.3 | 0.56322 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2217.47 | 0.584263 | 315.179ms | 5839 | 1280 | 275543 | 2511.2 | 0.96494 | 1(Win) | true |
| Jsonifier (two-stage) | 2071 | 0.963776 | 342.997ms | 5839 | 320 | 214892 | 2688.8 | 0.508373 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1676.45 | 0.814398 | 405.181ms | 5839 | 320 | 234163 | 3321.6 | 0.727802 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1649.05 | 0.434494 | 396.119ms | 5839 | 1280 | 275543 | 3376.8 | 0.31881 | 3(Tie) | true |
| Glaze | 1586.17 | 0.231272 | 412.845ms | 5839 | 4890 | 322353 | 3510.66 | 0.189932 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15935.9 | 4.71396 | 44.7109ms | 6938 | 640 | 245170 | 415.2 | 0.581395 | 1(Win) | true |
| Glaze | 2446.94 | 0.439327 | 282.294ms | 6960 | 2560 | 363569 | 2712.6 | 0.579094 | 2(Loss) | true |
| simdjson (reflection) | 323.886 | 0.502056 | 2126.74ms | 6938 | 40 | 420775 | 20428.8 | 0.0417537 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17341.8 | 1.82825 | 40.9001ms | 6938 | 4890 | 237936 | 381.539 | 1.69042 | 1(Win) | true |
| Glaze | 2755.32 | 0.582191 | 250.919ms | 6960 | 1280 | 251777 | 2409 | 0.157991 | 2(Loss) | true |
| simdjson (reflection) | 315.052 | 0.40541 | 2065.5ms | 6938 | 320 | 2.31976e+06 | 21001.6 | 0.432375 | 3(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1496.7 | 0.613006 | 302.786ms | 4857 | 640 | 230342 | 3094.8 | 0.373423 | 1(Win) | true |
| Jsonifier (two-stage) | 1261.57 | 0.66195 | 389.431ms | 4857 | 640 | 378043 | 3671.6 | 1.02437 | 2(Loss) | true |
| Glaze | 1183.4 | 0.203031 | 390.387ms | 4857 | 4890 | 308819 | 3914.13 | 0.713515 | 3(Loss) | true |
| simdjson (reflection) | 997.931 | 0.39696 | 479.4ms | 4857 | 2560 | 869099 | 4641.6 | 0.527196 | 4(Loss) | true |
| simdjson (ondemand) | 887.628 | 0.898424 | 563.728ms | 4857 | 320 | 703376 | 5218.4 | 0.229428 | 5(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2320.41 | 0.176641 | 258.927ms | 4857 | 1280 | 15914.8 | 1996.2 | 0.533844 | 1(Win) | true |
| Glaze | 1904.07 | 0.329837 | 288.693ms | 4857 | 4890 | 314831 | 2432.68 | 0.324999 | 2(Loss) | true |
| Jsonifier (two-stage) | 1498.45 | 0.564883 | 356.819ms | 4857 | 1280 | 390285 | 3091.2 | 0.604502 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1123.23 | 0.529444 | 446.425ms | 4857 | 1280 | 610161 | 4123.8 | 0.521646 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1108.35 | 1.60258 | 472.799ms | 4857 | 40 | 179426 | 4179.2 | 0.358607 | 4(Tie) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10007.7 | 1.76768 | 47.8318ms | 4857 | 4890 | 327327 | 462.842 | 0.924928 | 1(Win) | true |
| simdjson (reflection) | 6936.2 | 1.56009 | 66.335ms | 4857 | 2560 | 277864 | 667.8 | 1.82299 | 2(Loss) | true |
| Glaze | 2598.74 | 1.05417 | 197.353ms | 4857 | 640 | 225950 | 1782.4 | 0.768883 | 3(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11434.3 | 1.79597 | 44.1452ms | 4857 | 4890 | 258837 | 405.098 | 0.929873 | 1(Win) | true |
| simdjson (reflection) | 9039.81 | 2.04316 | 55.69ms | 4857 | 2560 | 280583 | 512.4 | 0.543478 | 2(Loss) | true |
| Glaze | 2290.12 | 0.629696 | 196.206ms | 4857 | 2560 | 415261 | 2022.6 | 1.89173 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1634.25 | 0.916819 | 410.43ms | 6701 | 80 | 102825 | 3910.4 | 0.328407 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1606.48 | 0.701759 | 392.017ms | 6701 | 640 | 498753 | 3978 | 1.31971 | 1(Tie) | true |
| Glaze | 1478.2 | 1.30295 | 463.2ms | 6701 | 80 | 253838 | 4323.2 | 0.661765 | 3(Loss) | true |
| simdjson (reflection) | 1356.72 | 0.168285 | 492.356ms | 6701 | 4890 | 307254 | 4710.3 | 0.948494 | 4(Loss) | true |
| simdjson (ondemand) | 1191.85 | 0.209381 | 551.081ms | 6701 | 2560 | 322666 | 5361.9 | 0.0205109 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2242.54 | 0.350362 | 349.238ms | 6701 | 2560 | 255194 | 2849.7 | 1.83603 | 1(Win) | true |
| Jsonifier (two-stage) | 2091.84 | 0.190755 | 359.844ms | 6701 | 2560 | 86938.6 | 3055 | 0.0327225 | 2(Loss) | true |
| Glaze | 2067.68 | 0.339831 | 361.715ms | 6701 | 2560 | 282410 | 3090.7 | 2.90671 | 3(Loss) | true |
| simdjson (ondemand) | 1491.8 | 0.383902 | 486.127ms | 6701 | 1280 | 346186 | 4283.8 | 0.0793058 | 4(Loss) | true |
| simdjson (reflection) | 1377.28 | 1.63165 | 480.832ms | 6701 | 80 | 458545 | 4640 | 0.820793 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12396.5 | 1.25661 | 60.3259ms | 7376 | 4890 | 248627 | 567.44 | 1.004 | 1(Win) | true |
| Glaze | 2270.89 | 1.95533 | 347.294ms | 7376 | 30 | 110055 | 3097.6 | 0 | 2(Loss) | true |
| simdjson (reflection) | 270.829 | 0.715027 | 2340.43ms | 7376 | 640 | 2.20737e+07 | 25973.2 | 2.84727 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13965.3 | 2.22897 | 56.585ms | 7376 | 2560 | 322694 | 503.7 | 0.138779 | 1(Win) | true |
| Glaze | 2428.3 | 1.02645 | 319.478ms | 7376 | 320 | 282919 | 2896.8 | 0.95733 | 2(Loss) | true |
| simdjson (reflection) | 332.145 | 0.509157 | 2105.65ms | 7376 | 320 | 3.72083e+06 | 21178.4 | 0.162166 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1391.66 | 0.493974 | 113.757ms | 1691 | 4890 | 160228 | 1158.81 | 0.40774 | 1(Win) | true |
| Glaze | 1365.68 | 0.520076 | 122.064ms | 1691 | 4890 | 184429 | 1180.85 | 0.258601 | 2(Loss) | true |
| simdjson (ondemand) | 1127.82 | 0.705243 | 145.785ms | 1691 | 2560 | 260332 | 1429.9 | 0.527278 | 3(Loss) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1101.47 | 0.770324 | 148.647ms | 1691 | 2560 | 325633 | 1464.1 | 2.04068 | 4(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1085.53 | 1.41389 | 158.513ms | 1691 | 640 | 282368 | 1485.6 | 1.11821 | 4(Tie) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1966.18 | 1.5029 | 118.755ms | 1691 | 1280 | 194496 | 820.2 | 2.26933 | 1(Win) | true |
| Glaze | 1894.35 | 0.903832 | 110.257ms | 1691 | 2560 | 151559 | 851.3 | 0.688287 | 2(Loss) | true |
| Jsonifier (two-stage) | 1615.25 | 1.23176 | 119.265ms | 1691 | 40 | 6049.48 | 998.4 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 1454.16 | 0.80317 | 133.457ms | 1691 | 1280 | 101552 | 1109 | 0.341481 | 4(Loss) | true |
| simdjson (reflection) | 1325 | 0.694224 | 147.165ms | 1691 | 2560 | 182765 | 1217.1 | 0.449861 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11201.6 | 3.17141 | 19.6019ms | 1996 | 4890 | 142028 | 169.934 | 0.612044 | 1(Win) | true |
| simdjson (reflection) | 9972.7 | 2.95527 | 21.898ms | 1996 | 4890 | 155596 | 190.874 | 2.01518 | 2(Loss) | true |
| Glaze | 2944.82 | 1.47333 | 67.6029ms | 1996 | 2560 | 232191 | 646.4 | 1.1923 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14292.6 | 3.7013 | 15.742ms | 1996 | 4890 | 118827 | 133.183 | 1.58873 | 1(Win) | true |
| simdjson (reflection) | 11323.7 | 3.31739 | 19.338ms | 1996 | 4890 | 152071 | 168.101 | 0.539134 | 2(Loss) | true |
| Glaze | 3614.76 | 2.66688 | 55.808ms | 1996 | 1280 | 252451 | 526.6 | 0.649847 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Glaze | 1515.54 | 0.526279 | 136.809ms | 2158 | 4890 | 249753 | 1357.95 | 2.31266 | 1(Win) | true |
| simdjson (ondemand) | 1401.93 | 0.696406 | 151.831ms | 2158 | 2560 | 267557 | 1468 | 0.0136258 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1353.38 | 0.483738 | 156.147ms | 2158 | 4890 | 264603 | 1520.66 | 0.979297 | 3(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1348.02 | 0.703215 | 155.405ms | 2158 | 2560 | 295069 | 1526.7 | 0.0852235 | 3(Tie) | true |
| Jsonifier | 1248.05 | 0.892494 | 162.851ms | 2158 | 2560 | 554488 | 1649 | 0.506818 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2145.57 | 0.665521 | 120.536ms | 2158 | 1280 | 52161.7 | 959.2 | 0.502934 | 1(Win) | true |
| Glaze | 2051.46 | 0.904247 | 147.354ms | 2158 | 160 | 13166.5 | 1003.2 | 0.480769 | 2(Loss) | true |
| Jsonifier (two-stage) | 1983.83 | 0.385532 | 128.617ms | 2158 | 2560 | 40950 | 1037.4 | 0.425944 | 3(Loss) | true |
| simdjson (ondemand) | 1726.31 | 0.490826 | 138.665ms | 2158 | 4890 | 167428 | 1192.15 | 0.739715 | 4(Loss) | true |
| simdjson (reflection) | 1594.34 | 0.531053 | 152.046ms | 2158 | 4890 | 229788 | 1290.84 | 0.422966 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14164.1 | 2.93427 | 22.39ms | 2866 | 4890 | 156776 | 192.969 | 0.347638 | 1(Win) | true |
| Glaze | 2757.5 | 1.18126 | 99.7588ms | 2866 | 640 | 87739.7 | 991.2 | 0.88 | 2(Loss) | true |
| simdjson (reflection) | 376.946 | 0.124224 | 729.674ms | 2866 | 4890 | 396745 | 7250.98 | 0.523727 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16163.8 | 3.18248 | 19.55ms | 2866 | 4890 | 141615 | 169.096 | 1.51653 | 1(Win) | true |
| Glaze | 3255.4 | 1.24508 | 86.8009ms | 2866 | 1280 | 139879 | 839.6 | 0.709555 | 2(Loss) | true |
| simdjson (reflection) | 382.934 | 0.183258 | 725.423ms | 2866 | 1280 | 218997 | 7137.6 | 0.123443 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1700.32 | 0.31073 | 249.89ms | 4390 | 4890 | 286248 | 2462.26 | 0.00165274 | 1(Win) | true |
| Jsonifier (two-stage) | 1200.16 | 0.6887 | 349.585ms | 4390 | 640 | 369396 | 3488.4 | 0.681136 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 994.098 | 0.176371 | 419.238ms | 4390 | 4890 | 269796 | 4211.49 | 0.85251 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 962.001 | 1.78719 | 459.723ms | 4390 | 40 | 241979 | 4352 | 0.970874 | 3(Tie) | true |
| simdjson (ondemand) | 722.355 | 0.152379 | 586.914ms | 4390 | 4890 | 381404 | 5795.81 | 0.521634 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2157.71 | 0.22414 | 237.858ms | 4390 | 4890 | 92489.2 | 1940.31 | 0.128038 | 1(Win) | true |
| Jsonifier (two-stage) | 1441.23 | 0.292652 | 338.965ms | 4390 | 2560 | 185014 | 2904.9 | 0.243819 | 2(Loss) | true |
| Glaze | 1213.09 | 0.611553 | 398.766ms | 4390 | 640 | 285094 | 3451.2 | 0.300439 | 3(Loss) | true |
| simdjson (reflection) | 1095.75 | 0.372966 | 424.891ms | 4390 | 1280 | 259930 | 3820.8 | 0.293994 | 4(Loss) | true |
| simdjson (ondemand) | 689.044 | 0.388926 | 622.895ms | 4390 | 2560 | 1.42959e+06 | 6076 | 0.341163 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10083.4 | 1.70501 | 45.013ms | 4390 | 4890 | 245064 | 415.202 | 2.28251 | 1(Win) | true |
| simdjson (reflection) | 8046.57 | 1.95005 | 55.1918ms | 4390 | 2560 | 263535 | 520.3 | 1.15881 | 2(Loss) | true |
| Glaze | 1766.93 | 0.330586 | 240.255ms | 4390 | 4890 | 300032 | 2369.44 | 0.677275 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10774.9 | 1.82369 | 42.3549ms | 4390 | 4890 | 245535 | 388.555 | 0.268326 | 1(Win) | true |
| simdjson (reflection) | 8436.67 | 1.46098 | 52.5399ms | 4390 | 4890 | 257030 | 496.242 | 0.492856 | 2(Loss) | true |
| Glaze | 1922.59 | 1.03026 | 233.716ms | 4390 | 320 | 161064 | 2177.6 | 0.438917 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2420.58 | 0.585776 | 371.37ms | 9378 | 640 | 299795 | 3694.8 | 0.0108272 | 1(Win) | true |
| Jsonifier (two-stage) | 2214.54 | 0.129791 | 410.687ms | 9378 | 4890 | 134355 | 4038.57 | 0.25495 | 2(Loss) | true |
| simdjson (reflection) | 1806.23 | 0.192778 | 536.794ms | 9378 | 2560 | 233254 | 4951.5 | 0.832892 | 3(Loss) | true |
| Glaze | 1581.18 | 0.170333 | 572.169ms | 9378 | 4890 | 453902 | 5656.24 | 0.293697 | 4(Loss) | true |
| simdjson (ondemand) | 1359.04 | 0.669354 | 655.388ms | 9378 | 160 | 310448 | 6580.8 | 0.0729927 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2806.44 | 0.389287 | 362.264ms | 9378 | 1280 | 196997 | 3186.8 | 0.40005 | 1(Win) | true |
| Jsonifier (two-stage) | 2595.04 | 0.827726 | 421.067ms | 9378 | 320 | 260408 | 3446.4 | 0.185357 | 2(Loss) | true |
| simdjson (reflection) | 2007.44 | 0.25707 | 518.835ms | 9378 | 2560 | 335798 | 4455.2 | 0.496256 | 3(Loss) | true |
| Glaze | 1802.01 | 0.160658 | 549.435ms | 9378 | 2560 | 162761 | 4963.1 | 0.309228 | 4(Loss) | true |
| simdjson (ondemand) | 1539.55 | 0.196048 | 631.792ms | 9378 | 2560 | 332045 | 5809.2 | 0.0482227 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 19847 | 2.52839 | 57.611ms | 11521 | 1280 | 250779 | 553.6 | 1.54072 | 1(Win) | true |
| Glaze | 2704.76 | 0.184211 | 409.562ms | 11521 | 2560 | 143349 | 4062.2 | 0.338567 | 2(Loss) | true |
| simdjson (reflection) | 308.389 | 0.610643 | 3552.15ms | 11521 | 320 | 1.51463e+07 | 35628 | 2.51084 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 21252 | 2.71741 | 56.5929ms | 11521 | 1280 | 252640 | 517 | 0.0386997 | 1(Win) | true |
| Glaze | 3042.89 | 0.615077 | 366.508ms | 11521 | 640 | 315679 | 3610.8 | 0.389235 | 2(Loss) | true |
| simdjson (reflection) | 311.643 | 0.669453 | 3560.93ms | 11521 | 160 | 8.91304e+06 | 35256 | 0.823656 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2619.21 | 0.413149 | 174.286ms | 4669 | 4890 | 241229 | 1700.02 | 0.29013 | 1(Win) | true |
| Jsonifier (two-stage) | 1613.65 | 0.512217 | 280.122ms | 4669 | 1280 | 255710 | 2759.4 | 0.741007 | 2(Loss) | true |
| simdjson (reflection) | 1186.91 | 0.342563 | 371.451ms | 4669 | 2560 | 422797 | 3751.5 | 1.30975 | 3(Loss) | true |
| Glaze | 1155.08 | 0.574683 | 398.817ms | 4669 | 2560 | 1.25638e+06 | 3854.9 | 0.697456 | 4(Loss) | true |
| simdjson (ondemand) | 1072.28 | 0.161612 | 420.073ms | 4669 | 4890 | 220234 | 4152.54 | 0.237523 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3044.81 | 0.503042 | 160.104ms | 4669 | 4890 | 264634 | 1462.39 | 0.14384 | 1(Win) | true |
| Jsonifier (two-stage) | 1788.23 | 0.311166 | 265.938ms | 4669 | 4890 | 293557 | 2490.01 | 0.0399147 | 2(Loss) | true |
| Glaze | 1569.62 | 0.983268 | 310.686ms | 4669 | 320 | 248973 | 2836.8 | 2.72306 | 3(Loss) | true |
| simdjson (reflection) | 1319.91 | 0.3111 | 353.168ms | 4669 | 2560 | 281969 | 3373.5 | 0.0266714 | 4(Loss) | true |
| simdjson (ondemand) | 1159.8 | 0.366586 | 384.291ms | 4669 | 2560 | 507077 | 3839.2 | 1.30885 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14023.7 | 2.13506 | 34.2321ms | 4669 | 4890 | 224727 | 317.513 | 0.130335 | 1(Win) | true |
| simdjson (reflection) | 7672.17 | 1.2981 | 60.418ms | 4669 | 4890 | 277549 | 580.371 | 1.41475 | 2(Loss) | true |
| Glaze | 1910.7 | 0.429469 | 236.85ms | 4669 | 2560 | 256427 | 2330.4 | 0.0514668 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15256.3 | 2.2375 | 31.638ms | 4669 | 4890 | 208539 | 291.861 | 0.88522 | 1(Win) | true |
| simdjson (reflection) | 8350.87 | 1.36801 | 57.8202ms | 4669 | 4890 | 260180 | 533.202 | 0.817996 | 2(Loss) | true |
| Glaze | 2181.42 | 0.22869 | 209.363ms | 4669 | 2560 | 55783.6 | 2041.2 | 0.787402 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2697.46 | 0.264239 | 283.125ms | 7932 | 4890 | 268509 | 2804.33 | 0.0347356 | 1(Win) | true |
| Jsonifier (two-stage) | 2356.83 | 0.207275 | 324.445ms | 7932 | 4890 | 216428 | 3209.63 | 1.40892 | 2(Loss) | true |
| simdjson (reflection) | 1917.16 | 0.150462 | 399.644ms | 7932 | 4890 | 172351 | 3945.7 | 0.0051152 | 3(Loss) | true |
| Glaze | 1864.8 | 0.184942 | 409.177ms | 7932 | 2560 | 144083 | 4056.5 | 0.101175 | 4(Loss) | true |
| simdjson (ondemand) | 1525.77 | 0.237958 | 523.665ms | 7932 | 4890 | 680609 | 4957.87 | 0.564247 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2959.38 | 0.299142 | 270.214ms | 7932 | 4890 | 285909 | 2556.13 | 0.52802 | 1(Win) | true |
| Jsonifier (two-stage) | 2582.46 | 0.226997 | 330.39ms | 7932 | 2560 | 113182 | 2929.2 | 0.55001 | 2(Loss) | true |
| Glaze | 2125.29 | 0.313362 | 380.192ms | 7932 | 2560 | 318465 | 3559.3 | 0.109692 | 3(Loss) | true |
| simdjson (reflection) | 2031.33 | 0.205626 | 389.033ms | 7932 | 4890 | 286727 | 3723.94 | 0.410874 | 4(Loss) | true |
| simdjson (ondemand) | 1835.81 | 0.156014 | 418.862ms | 7932 | 4890 | 202091 | 4120.55 | 0.0835847 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 15667 | 2.47804 | 57.3361ms | 9249 | 1280 | 249139 | 563 | 5.03731 | -(Win) | false |
| Glaze | 2312.92 | 0.610242 | 418.462ms | 9249 | 320 | 173310 | 3813.6 | 0.188442 | 2(Loss) | true |
| simdjson (reflection) | 330.446 | 0.136924 | 2698.26ms | 9249 | 1280 | 1.70986e+06 | 26692.8 | 0.756979 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17997.4 | 2.0269 | 53.8801ms | 9249 | 2560 | 252624 | 490.1 | 0.0611746 | 1(Win) | true |
| Glaze | 2299.27 | 0.336343 | 374.714ms | 9249 | 4890 | 814112 | 3836.23 | 2.89744 | 2(Loss) | true |
| simdjson (reflection) | 328.353 | 0.25413 | 2738.39ms | 9249 | 30 | 139810 | 26862.9 | 0.0317561 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 638.919 | 0.163054 | 693.115ms | 4604 | 2560 | 321426 | 6872.1 | 0.205599 | 1(Win) | true |
| Jsonifier (two-stage) | 528.815 | 1.03146 | 927.802ms | 4604 | 30 | 220035 | 8302.93 | 0.412797 | 2(Loss) | true |
| simdjson (reflection) | 458.13 | 1.51299 | 979.65ms | 4604 | 80 | 1.68211e+06 | 9584 | 1.11411 | 3(Loss) | true |
| Glaze | 426.431 | 0.235115 | 1109.02ms | 4604 | 4890 | 2.86579e+06 | 10296.4 | 0.739027 | 4(Loss) | true |
| simdjson (ondemand) | 339.595 | 0.193866 | 1298.76ms | 4604 | 4890 | 3.07227e+06 | 12929.3 | 0.899457 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 821.801 | 0.288241 | 678.46ms | 4604 | 1280 | 303570 | 5342.8 | 0.0897599 | 1(Win) | true |
| Jsonifier (two-stage) | 633.666 | 0.637053 | 909.221ms | 4604 | 30 | 58455.1 | 6929.07 | 0.2457 | 2(Loss) | true |
| simdjson (reflection) | 616.239 | 0.1149 | 862.562ms | 4604 | 4890 | 327736 | 7125.02 | 1.12791 | 3(Loss) | true |
| Glaze | 510.808 | 0.108572 | 1007.02ms | 4604 | 4890 | 425893 | 8595.63 | 0.147161 | 4(Loss) | true |
| simdjson (ondemand) | 427.379 | 0.401431 | 1193.48ms | 4604 | 160 | 272137 | 10273.6 | 0.108899 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1899.1 | 0.613558 | 235.157ms | 4604 | 1280 | 257571 | 2312 | 0.653145 | 1(Win) | true |
| simdjson (reflection) | 1607.87 | 0.275922 | 296.096ms | 4918 | 2560 | 165838 | 2917 | 0.484443 | 2(Loss) | true |
| Glaze | 1029.14 | 0.232384 | 430.145ms | 4604 | 2560 | 251638 | 4266.4 | 0.00937471 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1930.61 | 0.302048 | 231.183ms | 4604 | 4890 | 230750 | 2274.26 | 0.196679 | 1(Win) | true |
| simdjson (reflection) | 1621.65 | 0.187522 | 296.06ms | 4918 | 4890 | 143840 | 2892.22 | 0.590358 | 2(Loss) | true |
| Glaze | 1080.96 | 1.11984 | 447.854ms | 4604 | 30 | 62070.9 | 4061.87 | 0.833333 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1801.84 | 0.108584 | 1037.34ms | 18245 | 4890 | 537648 | 9656.7 | 0.627752 | 1(Win) | true |
| simdjson (reflection) | 1761.97 | 0.57134 | 1016.08ms | 18245 | 40 | 127333 | 9875.2 | 0.237069 | 2(Loss) | true |
| Jsonifier | 1707.87 | 0.364653 | 1021.69ms | 18245 | 320 | 441659 | 10188 | 0.370429 | 3(Loss) | true |
| simdjson (ondemand) | 1318.66 | 0.0860785 | 1326.91ms | 18245 | 4890 | 630847 | 13195.1 | 0.260036 | 4(Loss) | true |
| Glaze | 1268.76 | 0.304485 | 1382.64ms | 18245 | 640 | 1.11594e+06 | 13714 | 0.0320737 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2111.38 | 0.216989 | 958.449ms | 18245 | 4890 | 1.56364e+06 | 8240.95 | 0.0455115 | 1(Win) | true |
| Jsonifier | 2008.1 | 0.313036 | 1012.67ms | 18245 | 640 | 470853 | 8664.8 | 0.12017 | 2(Loss) | true |
| simdjson (reflection) | 1908.65 | 0.253261 | 1060.7ms | 18245 | 2560 | 1.36462e+06 | 9116.3 | 1.10542 | 3(Loss) | true |
| simdjson (ondemand) | 1491.61 | 0.749102 | 1358.06ms | 18245 | 30 | 229075 | 11665.1 | 0.29347 | 4(Loss) | true |
| Glaze | 1434.58 | 0.126074 | 1361.56ms | 18245 | 1280 | 299292 | 12128.8 | 0.337525 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7698.49 | 0.682246 | 352.093ms | 24579 | 640 | 276172 | 3044.8 | 1.08898 | 1(Win) | true |
| Glaze | 2960.43 | 0.286679 | 791.762ms | 24579 | 2560 | 1.31902e+06 | 7917.9 | 0.208824 | 2(Loss) | true |
| simdjson (reflection) | 288.2 | 0.460033 | 7809.48ms | 24893 | 320 | 4.5951e+07 | 82372.8 | 1.41836 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7046.77 | 1.61695 | 291.133ms | 24579 | 160 | 462871 | 3326.4 | 0.431034 | 1(Win) | true |
| Glaze | 3137.43 | 0.781063 | 706.399ms | 24579 | 320 | 1.08969e+06 | 7471.2 | 1.31265 | 2(Loss) | true |
| simdjson (reflection) | 305.236 | 0.268041 | 8005.29ms | 24893 | 640 | 2.7814e+07 | 77775.2 | 0.389294 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 691.451 | 0.24772 | 645.283ms | 4604 | 1280 | 316723 | 6350 | 0.432765 | 1(Win) | true |
| Jsonifier (two-stage) | 586.367 | 0.763257 | 828.754ms | 4604 | 80 | 261314 | 7488 | 0.170648 | 2(Loss) | true |
| simdjson (reflection) | 510.252 | 0.254447 | 893.812ms | 4604 | 1280 | 613629 | 8605 | 0.109358 | 3(Loss) | true |
| Glaze | 428.513 | 0.219961 | 1034.27ms | 4604 | 1280 | 650195 | 10246.4 | 0.070318 | 4(Loss) | true |
| simdjson (ondemand) | 360.699 | 0.445653 | 1288.49ms | 4604 | 80 | 235432 | 12172.8 | 0.262192 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 914.733 | 0.525756 | 656.389ms | 4604 | 320 | 203798 | 4800 | 0.662252 | 1(Win) | true |
| Jsonifier (two-stage) | 694.734 | 0.832861 | 805.6ms | 4604 | 80 | 221651 | 6320 | 0.252525 | 2(Loss) | true |
| simdjson (reflection) | 609.822 | 0.995844 | 868.841ms | 4604 | 40 | 205640 | 7200 | 0.088968 | 3(Loss) | true |
| Glaze | 500.31 | 0.272998 | 1014.23ms | 4604 | 1280 | 734718 | 8776 | 0.559171 | 4(Loss) | true |
| simdjson (ondemand) | 390.649 | 0.210465 | 1259.04ms | 4604 | 4890 | 2.73632e+06 | 11239.6 | 0.43273 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1885.3 | 0.418524 | 240.143ms | 4604 | 4890 | 464579 | 2328.92 | 0.155654 | 1(Win) | true |
| simdjson (reflection) | 1718.26 | 1.3354 | 315.727ms | 4918 | 160 | 212590 | 2729.6 | 0.117371 | 2(Loss) | true |
| Glaze | 994.117 | 0.279448 | 444.354ms | 4604 | 2560 | 389976 | 4416.7 | 1.94263 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1889.86 | 0.435439 | 239.544ms | 4604 | 2560 | 262002 | 2323.3 | 4.32007 | 1(Win) | true |
| simdjson (reflection) | 1574.36 | 0.393771 | 297.994ms | 4918 | 2560 | 352288 | 2979.1 | 2.59315 | 2(Loss) | true |
| Glaze | 1090.7 | 0.851593 | 410.901ms | 4604 | 40 | 47009.5 | 4025.6 | 0.892857 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1972.77 | 0.287647 | 953.421ms | 18245 | 640 | 411943 | 8820 | 0.37327 | 1(Win) | true |
| Jsonifier (two-stage) | 1832.02 | 1.13833 | 949.58ms | 18245 | 80 | 935091 | 9497.6 | 1.0211 | 2(Loss) | true |
| simdjson (reflection) | 1649.28 | 0.317836 | 1095.92ms | 18245 | 2560 | 2.87835e+06 | 10549.9 | 0.410211 | 3(Loss) | true |
| Glaze | 1243.32 | 0.16013 | 1441.41ms | 18245 | 30 | 15065.7 | 13994.7 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 1233.08 | 0.309806 | 1432.12ms | 18245 | 640 | 1.22311e+06 | 14110.8 | 0.929566 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2382.75 | 1.00409 | 952.718ms | 18245 | 40 | 215051 | 7302.4 | 0.145858 | 1(Win) | true |
| Jsonifier (two-stage) | 2287.7 | 0.266866 | 921.779ms | 18245 | 1280 | 527335 | 7605.8 | 0.301489 | 2(Loss) | true |
| simdjson (reflection) | 1839.18 | 0.408416 | 1103.62ms | 18245 | 1280 | 1.91097e+06 | 9460.6 | 1.87321 | 3(Loss) | true |
| simdjson (ondemand) | 1440.95 | 0.27317 | 1420.39ms | 18245 | 640 | 696361 | 12075.2 | 0.781198 | 4(Loss) | true |
| Glaze | 1408.19 | 0.253017 | 1407.5ms | 18245 | 2560 | 2.50209e+06 | 12356.1 | 3.11373 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7125.6 | 2.32929 | 316.06ms | 24579 | 80 | 469702 | 3289.6 | 0.390625 | 1(Win) | true |
| Glaze | 2960.61 | 0.290385 | 810.141ms | 24579 | 4890 | 2.58478e+06 | 7917.42 | 0.763804 | 2(Loss) | true |
| simdjson (reflection) | 265.394 | 0.663117 | 8714.94ms | 24893 | 160 | 5.62954e+07 | 89451.2 | 0.280037 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7921.09 | 0.442487 | 298.709ms | 24579 | 4890 | 838432 | 2959.23 | 0.389311 | 1(Win) | true |
| Glaze | 3554.48 | 0.484626 | 681.203ms | 24579 | 2560 | 2.61475e+06 | 6594.6 | 0.970086 | 2(Loss) | true |
| simdjson (reflection) | 287.804 | 0.408777 | 8319.19ms | 24893 | 640 | 7.27635e+07 | 82486 | 0.44848 | 3(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1142.96 | 0.507292 | 444.385ms | 5094 | 640 | 297547 | 4250.4 | 1.43184 | 1(Win) | true |
| Jsonifier (two-stage) | 1035.05 | 0.279834 | 471.259ms | 5094 | 4890 | 843532 | 4693.49 | 0.883208 | 2(Loss) | true |
| simdjson (reflection) | 779.54 | 0.172683 | 623.198ms | 5094 | 4890 | 566305 | 6231.9 | 0.738718 | 3(Loss) | true |
| Glaze | 695.831 | 0.876994 | 666.211ms | 5094 | 320 | 1.19965e+06 | 6981.6 | 0.913506 | 4(Loss) | true |
| simdjson (ondemand) | 658.387 | 0.206995 | 741.031ms | 5094 | 4890 | 1.14073e+06 | 7378.66 | 2.44767 | 5(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1434.1 | 0.354567 | 426.47ms | 5094 | 2560 | 369314 | 3387.5 | 0.150781 | 1(Win) | true |
| Jsonifier (two-stage) | 1246.03 | 0.283837 | 470.255ms | 5094 | 4890 | 598833 | 3898.79 | 0.321411 | 2(Loss) | true |
| Glaze | 992.242 | 1.47767 | 597.939ms | 5094 | 80 | 418725 | 4896 | 1.0568 | 3(Loss) | true |
| simdjson (reflection) | 947.832 | 0.311032 | 619.498ms | 5094 | 1280 | 325294 | 5125.4 | 0.369334 | 4(Loss) | true |
| simdjson (ondemand) | 812.54 | 0.404977 | 710.656ms | 5094 | 1280 | 750409 | 5978.8 | 0.707452 | 5(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12123.8 | 2.42844 | 44.6892ms | 5094 | 2560 | 242401 | 400.7 | 2.88415 | 1(Win) | true |
| simdjson (reflection) | 8673.31 | 1.2754 | 58.562ms | 5094 | 4890 | 249547 | 560.111 | 1.47559 | 2(Loss) | true |
| Glaze | 1949.08 | 0.326547 | 247.776ms | 5094 | 4890 | 323936 | 2492.47 | 1.05334 | 3(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12286.3 | 2.45603 | 42.1059ms | 5094 | 2560 | 241424 | 395.4 | 1.28074 | 1(Win) | true |
| simdjson (reflection) DID NOT CONVERGE | 8225.84 | 1.22645 | 60.0399ms | 5094 | 4890 | 256544 | 590.58 | 5.78183 | -(Loss) | false |
| Glaze | 2303.31 | 0.247704 | 214.789ms | 5094 | 4890 | 133472 | 2109.15 | 1.74934 | 3(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1550.99 | 0.414921 | 536.395ms | 8051 | 160 | 67504.1 | 4950.4 | 0.0646831 | 1(Win) | true |
| Jsonifier (two-stage) | 1184.11 | 0.406841 | 622.805ms | 8051 | 1280 | 890784 | 6484.2 | 0.07717 | 2(Loss) | true |
| simdjson (reflection) | 1128.06 | 0.916566 | 693.476ms | 8051 | 160 | 622705 | 6806.4 | 0.424929 | 3(Loss) | true |
| Glaze | 1041.68 | 0.274502 | 731.521ms | 8051 | 2560 | 1.048e+06 | 7370.8 | 1.07902 | 4(Loss) | true |
| simdjson (ondemand) | 916.627 | 0.521398 | 839.111ms | 8051 | 640 | 1.22077e+06 | 8376.4 | 0.290449 | 5(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1619.9 | 0.290579 | 639.991ms | 8051 | 4890 | 927603 | 4739.82 | 2.19105 | 1(Win) | true |
| Jsonifier | 1574.4 | 0.908738 | 556.841ms | 8051 | 320 | 628488 | 4876.8 | 0.229133 | 2(Loss) | true |
| simdjson (reflection) | 1473.82 | 1.25098 | 663.509ms | 8051 | 40 | 169889 | 5209.6 | 0.570033 | 3(Loss) | true |
| Glaze | 1347.97 | 1.67993 | 671.85ms | 8051 | 80 | 732510 | 5696 | 1.33038 | 4(Loss) | true |
| simdjson (ondemand) | 1159.89 | 0.279802 | 783.139ms | 8051 | 2560 | 878224 | 6619.6 | 0.310232 | 5(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13171.6 | 1.39817 | 70.198ms | 9255 | 2560 | 224718 | 670.1 | 1.28167 | 1(Win) | true |
| Glaze | 2458.29 | 0.913562 | 385.256ms | 9255 | 320 | 344280 | 3590.4 | 0.990099 | 2(Loss) | true |
| simdjson (reflection) | 307.107 | 0.329628 | 2820.36ms | 9255 | 1280 | 1.14877e+07 | 28740 | 0.501302 | 3(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14261.2 | 1.59826 | 64.234ms | 9255 | 2560 | 250481 | 618.9 | 4.2247 | 1(Win) | true |
| Glaze | 2745.17 | 0.309258 | 334.408ms | 9255 | 2560 | 253103 | 3215.2 | 1.36192 | 2(Loss) | true |
| simdjson (reflection) | 301.839 | 0.492244 | 2860.21ms | 9255 | 640 | 1.326e+07 | 29241.6 | 1.0316 | 3(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 3890.38 | 2.34427 | 78.11ms | 2889 | 2560 | 705615 | 708.2 | 0.283206 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 3574.54 | 0.791831 | 80.2409ms | 2889 | 4890 | 182150 | 770.775 | 0.979254 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 3572.84 | 0.817099 | 80.3231ms | 2889 | 4890 | 194145 | 771.141 | 0.0572342 | 2(Tie) | true |
| simdjson (ondemand) | 3383.06 | 1.51084 | 84.885ms | 2889 | 1280 | 193787 | 814.4 | 1.9019 | 4(Loss) | true |
| Glaze | 2543.31 | 0.55594 | 116.748ms | 2889 | 2560 | 92852.6 | 1083.3 | 0.0646592 | 5(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 3837.28 | 1.35392 | 76.4298ms | 2889 | 2560 | 241921 | 718 | 0.746475 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 3558.11 | 0.81773 | 83.6641ms | 2889 | 4890 | 196058 | 774.335 | 0.840753 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 3503.52 | 1.12377 | 84.4982ms | 2889 | 2560 | 199932 | 786.4 | 1.00705 | 2(Tie) | true |
| simdjson (reflection) | 3295.43 | 0.678837 | 88.14ms | 2889 | 4890 | 157512 | 836.057 | 1.38508 | 4(Loss) | true |
| Glaze | 2532.32 | 1.46551 | 114.854ms | 2889 | 320 | 81355 | 1088 | 0.147275 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4204.95 | 0.619675 | 92.9331ms | 3808 | 4890 | 140059 | 863.647 | 0.658115 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 4154.66 | 0.855157 | 91.221ms | 3808 | 2560 | 143039 | 874.1 | 0.828228 | 1(Tie) | true |
| Jsonifier | 4019.03 | 1.37795 | 100.352ms | 3808 | 640 | 99220.5 | 903.6 | 0.758252 | 3(Loss) | true |
| simdjson (ondemand) | 3159 | 1.98851 | 99.4399ms | 3808 | 320 | 167224 | 1149.6 | 2.7897 | 4(Loss) | true |
| Glaze | 2977.34 | 0.52862 | 125.871ms | 3808 | 4890 | 203298 | 1219.74 | 0.3722 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4479.76 | 0.738737 | 88.3011ms | 3808 | 4890 | 175377 | 810.667 | 0.0411015 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 4432.01 | 1.33236 | 88.6372ms | 3808 | 1280 | 152562 | 819.4 | 0.367467 | 1(Tie) | true |
| Jsonifier | 3970.69 | 1.14786 | 94.443ms | 3808 | 1280 | 141076 | 914.6 | 1.35195 | 3(Loss) | true |
| simdjson (ondemand) | 3512.52 | 0.94653 | 99.626ms | 3808 | 2560 | 245169 | 1033.9 | 0.758303 | 4(Loss) | true |
| Glaze | 2481.95 | 2.23723 | 129.806ms | 3808 | 320 | 342908 | 1463.2 | 1.13514 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2140.27 | 0.782195 | 133.2ms | 2889 | 2560 | 259555 | 1287.3 | 1.67278 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1763.91 | 0.698067 | 161.989ms | 2889 | 4890 | 581361 | 1561.97 | 0.308497 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1744.33 | 0.670365 | 159.782ms | 2889 | 2560 | 287013 | 1579.5 | 0.643558 | 2(Tie) | true |
| simdjson (reflection) | 1205.13 | 0.661702 | 221.866ms | 2889 | 1280 | 292930 | 2286.2 | 1.20138 | 4(Loss) | true |
| simdjson (ondemand) | 1055.3 | 0.775763 | 273.182ms | 2889 | 640 | 262534 | 2610.8 | 0.291948 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2792.59 | 0.38674 | 119.931ms | 2889 | 1280 | 18635 | 986.6 | 0.509372 | 1(Win) | true |
| Glaze | 2208.73 | 1.03057 | 146.647ms | 2889 | 1280 | 211531 | 1247.4 | 0.112108 | 2(Loss) | true |
| Jsonifier (two-stage) | 2108.65 | 0.74211 | 151.042ms | 2889 | 2560 | 240692 | 1306.6 | 0.476776 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1197.48 | 2.66654 | 212.166ms | 2889 | 80 | 301123 | 2300.8 | 1.50685 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1154.87 | 0.449753 | 264.348ms | 2889 | 2560 | 294727 | 2385.7 | 1.47597 | 4(Tie) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12350.2 | 7.29987 | 26.4489ms | 2963 | 640 | 178534 | 228.8 | 2.14286 | 1(Win) | true |
| simdjson (reflection) | 9439.66 | 2.19738 | 35.158ms | 2963 | 4890 | 211578 | 299.347 | 4.66648 | 2(Loss) | true |
| Glaze | 3165.03 | 2.80802 | 91.2172ms | 2963 | 160 | 100561 | 892.8 | 0.722022 | 3(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11092.5 | 2.45397 | 26.722ms | 2963 | 4890 | 191097 | 254.744 | 4.06191 | 1(Win) | true |
| simdjson (reflection) | 9748.24 | 2.28223 | 32.4188ms | 2963 | 4890 | 214013 | 289.872 | 0.421994 | 2(Loss) | true |
| Glaze DID NOT CONVERGE | 3208.15 | 2.22617 | 88.6372ms | 2963 | 320 | 123033 | 880.8 | 6.8932 | -(Loss) | false |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 2101.84 | 0.571333 | 172.883ms | 3808 | 4890 | 476522 | 1727.82 | 0.250465 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2088.08 | 1.1136 | 180.895ms | 3808 | 640 | 240070 | 1739.2 | 0.95672 | 1(Tie) | true |
| Glaze STATISTICAL TIE | 2033.82 | 2.71084 | 179.457ms | 3808 | 80 | 187441 | 1785.6 | 0.722022 | 1(Tie) | true |
| simdjson (reflection) | 1600.03 | 0.490852 | 231.39ms | 3808 | 2560 | 317744 | 2269.7 | 0.518158 | 4(Loss) | true |
| simdjson (ondemand) | 1355.27 | 0.498127 | 266.887ms | 3808 | 1280 | 228050 | 2679.6 | 0.119278 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2673.43 | 2.82091 | 159.434ms | 3808 | 160 | 234938 | 1358.4 | 1.31265 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2469.29 | 0.716718 | 169.816ms | 3808 | 2560 | 284436 | 1470.7 | 0.526316 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 2435.51 | 0.73057 | 168.536ms | 3808 | 2560 | 303792 | 1491.1 | 0.981986 | 2(Tie) | true |
| simdjson (reflection) | 1820.35 | 0.438318 | 216.291ms | 3808 | 1280 | 97875.5 | 1995 | 0.574713 | 4(Loss) | true |
| simdjson (ondemand) | 1484.52 | 0.433006 | 266.028ms | 3808 | 2560 | 287242 | 2446.3 | 0.208044 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 11756.9 | 5.43172 | 35.3421ms | 4300 | 640 | 229725 | 348.8 | 6.83761 | -(Win) | false |
| Glaze | 2984.57 | 0.723668 | 141.731ms | 4300 | 2560 | 253100 | 1374 | 2.39976 | 2(Loss) | true |
| simdjson (reflection) | 360.833 | 0.48425 | 1200.57ms | 4300 | 1280 | 3.8768e+06 | 11364.8 | 0.292986 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14557.1 | 2.29214 | 30.1501ms | 4300 | 4890 | 203883 | 281.705 | 0.143869 | 1(Win) | true |
| Glaze | 3498.68 | 0.685342 | 121.188ms | 4300 | 2560 | 165190 | 1172.1 | 0.713181 | 2(Loss) | true |
| simdjson (reflection) | 332.6 | 0.237991 | 1232.41ms | 4300 | 4890 | 4.21037e+06 | 12329.5 | 0.161784 | 3(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2039.26 | 0.521801 | 5259.77ms | 466906 | 160 | 2.07704e+08 | 218352 | 1.11286 | 1(Win) | true |
| Glaze | 1425.3 | 0.698937 | 7888.79ms | 466906 | 160 | 7.62852e+08 | 312408 | 3.97961 | 2(Loss) | true |
| simdjson (ondemand) | 1106.9 | 0.525304 | 5230.11ms | 466906 | 80 | 3.57233e+08 | 402272 | 0.266569 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2109.57 | 0.388085 | 5364.85ms | 466906 | 640 | 4.29443e+08 | 211074 | 0.500899 | 1(Win) | true |
| Glaze | 1303.03 | 0.854451 | 8147.62ms | 466906 | 80 | 6.82052e+08 | 341725 | 0.320166 | 2(Loss) | true |
| simdjson (ondemand) | 999.952 | 0.365303 | 5786.05ms | 466906 | 640 | 1.6935e+09 | 445298 | 2.03138 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2663.33 | 0.782092 | 6140.49ms | 699405 | 320 | 1.22764e+09 | 250440 | 1.42359 | 1(Win) | true |
| Glaze | 2087.54 | 0.24936 | 8194.92ms | 699405 | 1280 | 8.12555e+08 | 319518 | 0.854682 | 2(Loss) | true |
| simdjson (ondemand) | 1651.25 | 0.262415 | 5767.88ms | 767297 | 40 | 5.40922e+07 | 443149 | 0.199699 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2837.09 | 1.6269 | 6022.64ms | 699405 | 30 | 4.3889e+08 | 235102 | 1.61546 | 1(Win) | true |
| Glaze | 2194.91 | 0.408763 | 7585.39ms | 699405 | 160 | 2.4688e+08 | 303886 | 0.605487 | 2(Loss) | true |
| simdjson (ondemand) | 1644.01 | 0.233585 | 5808.24ms | 767297 | 40 | 4.32383e+07 | 445101 | 0.00814863 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2244.07 | 0.210858 | 7124.62ms | 631514 | 80 | 2.56189e+07 | 268378 | 0.0357577 | 1(Win) | true |
| Glaze | 1736.35 | 0.274413 | 8453.72ms | 631514 | 1280 | 1.15961e+09 | 346853 | 0.797786 | 2(Loss) | true |
