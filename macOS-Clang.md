# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the Clang 23.1.5 compiler).  

Latest Results: (Nov 17, 2026)
#### Using the following commits:
----
| Jsonifier: [79b3e67](https://github.com/nihilai-collective/Jsonifier/commit/79b3e67)  
| Glaze: [a53ddd59](https://github.com/stephenberry/glaze/commit/a53ddd59)  
| simdjson: [36c5b3cfc](https://github.com/simdjson/simdjson/commit/36c5b3cfc)  

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
| Jsonifier | 1172.78 | 0.4509 | 85.135ms | 905 | 80 | 880.88 | 735.925 | 0.0611102 | 1(Win) | true |
| Glaze | 1047.75 | 0.582209 | 95.666ms | 905 | 4890 | 112472 | 823.739 | 1.81933 | 2(Loss) | true |
| Jsonifier (two-stage) | 290.578 | 0.677635 | 298.401ms | 905 | 320 | 129633 | 2970.2 | 0.355931 | 3(Loss) | true |
| simdjson (ondemand) | 163.431 | 0.395156 | 537.748ms | 905 | 1280 | 557412 | 5280.98 | 0.0096168 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1249.66 | 0.712647 | 81.7219ms | 905 | 40 | 969.003 | 690.65 | 0.249177 | 1(Win) | true |
| Glaze | 1141.06 | 0.362545 | 79.6934ms | 905 | 1280 | 9625.34 | 756.382 | 0.451642 | 2(Loss) | true |
| Jsonifier (two-stage) | 297.922 | 0.354959 | 315.922ms | 905 | 1280 | 135350 | 2896.98 | 0.500314 | 3(Loss) | true |
| simdjson (ondemand) | 146.049 | 0.340678 | 565.014ms | 905 | 2560 | 1.0376e+06 | 5909.49 | 0.194902 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 889.493 | 0.665835 | 109.702ms | 905 | 80 | 3339.15 | 970.3 | 0.703147 | 1(Win) | true |
| Glaze | 119.952 | 0.266637 | 776.596ms | 905 | 1280 | 471123 | 7195.18 | 0.938714 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1264.9 | 0.520635 | 100.036ms | 905 | 40 | 504.789 | 682.325 | 0.555043 | 1(Win) | true |
| Glaze | 672.732 | 3.90656 | 140.487ms | 905 | 320 | 803807 | 1282.94 | 0.910686 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 729.306 | 0.422692 | 239.51ms | 1811 | 4890 | 489975 | 2368.15 | 1.11899 | 1(Win) | true |
| Glaze | 605.048 | 0.899607 | 277.88ms | 1811 | 640 | 422030 | 2854.49 | 0.635973 | 2(Loss) | true |
| Jsonifier (two-stage) | 301.142 | 0.299928 | 552.636ms | 1811 | 2560 | 757477 | 5735.19 | 0.794699 | 3(Loss) | true |
| simdjson (ondemand) | 198.138 | 0.138126 | 1011.16ms | 1811 | 30 | 4348.85 | 8716.67 | 0.459447 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 902.354 | 0.342887 | 198.277ms | 1811 | 1280 | 55130.8 | 1914 | 0.045655 | 1(Win) | true |
| Glaze | 873.6 | 0.212225 | 206.821ms | 1811 | 2560 | 45065.8 | 1977 | 0.00410994 | 2(Loss) | true |
| Jsonifier (two-stage) | 334.753 | 1.21256 | 500.459ms | 1811 | 80 | 313102 | 5159.34 | 0.281943 | 3(Loss) | true |
| simdjson (ondemand) | 206.895 | 0.195048 | 935.972ms | 1811 | 640 | 169667 | 8347.73 | 0.469329 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 243.97 | 1.52681 | 675.832ms | 1811 | 80 | 934591 | 7079.16 | 0.205639 | 1(Win) | true |
| Glaze | 202.757 | 0.263921 | 913.102ms | 1798 | 640 | 318829 | 8456.96 | 0.403963 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 661.983 | 1.42183 | 264.185ms | 1811 | 4890 | 6.72894e+06 | 2608.99 | 0.136762 | 1(Win) | true |
| Glaze | 592.779 | 0.549976 | 294.319ms | 1798 | 640 | 161980 | 2892.66 | 0.45479 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2054.63 | 0.236439 | 183.42ms | 3862 | 2560 | 45986.9 | 1792.58 | 0.208976 | 1(Win) | true |
| Glaze | 1130.47 | 0.45934 | 320.379ms | 3862 | 640 | 143336 | 3258.01 | 2.44582 | 2(Loss) | true |
| Jsonifier (two-stage) | 820.976 | 0.128537 | 495.14ms | 3862 | 30 | 997.564 | 4486.23 | 0.0349338 | 3(Loss) | true |
| simdjson (ondemand) | 429.199 | 0.178227 | 849.358ms | 3862 | 4890 | 1.14383e+06 | 8581.31 | 0.32404 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2559.66 | 0.33237 | 147.923ms | 3862 | 30 | 686.162 | 1438.9 | 0.197298 | 1(Win) | true |
| Glaze | 1389.07 | 0.277575 | 274.403ms | 3862 | 640 | 34667.3 | 2651.49 | 0.0805621 | 2(Loss) | true |
| Jsonifier (two-stage) | 827.078 | 0.847217 | 445.191ms | 3862 | 160 | 227741 | 4453.14 | 1.27011 | 3(Loss) | true |
| simdjson (ondemand) | 437.651 | 0.231446 | 854.038ms | 3862 | 2560 | 971201 | 8415.58 | 1.67628 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2991.28 | 0.224183 | 145.885ms | 3862 | 80 | 609.544 | 1231.28 | 0.342277 | 1(Win) | true |
| Glaze | 487.95 | 0.372093 | 770.3ms | 3862 | 2560 | 2.01938e+06 | 7548.09 | 0.615698 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3399.98 | 0.318215 | 137.212ms | 3862 | 30 | 356.478 | 1083.27 | 0.129072 | 1(Win) | true |
| Glaze | 2047.3 | 0.273572 | 214.15ms | 3862 | 40 | 968.872 | 1799 | 0.0982992 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1298.02 | 0.906843 | 723.537ms | 9578 | 80 | 325791 | 7037.07 | 0.440681 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 1079.56 | 0.49882 | 861.171ms | 9578 | 1280 | 2.28008e+06 | 8461.09 | 5.33327 | -(Loss) | false |
| simdjson (ondemand) | 782.08 | 0.3062 | 1157.73ms | 9578 | 2560 | 3.27414e+06 | 11679.5 | 1.26158 | 3(Loss) | true |
| Jsonifier (two-stage) | 611.57 | 0.420173 | 1475.25ms | 9578 | 2560 | 1.00822e+07 | 14935.8 | 0.226812 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2144.86 | 0.16097 | 690.925ms | 9578 | 4890 | 229800 | 4258.69 | 1.23626 | 1(Win) | true |
| Glaze | 1609.57 | 1.03906 | 799.978ms | 9578 | 160 | 556325 | 5674.98 | 0.15597 | 2(Loss) | true |
| simdjson (ondemand) | 1064.2 | 0.20639 | 1115.14ms | 9578 | 4890 | 1.53458e+06 | 8583.23 | 0.95652 | 3(Loss) | true |
| Jsonifier (two-stage) | 889.881 | 0.58144 | 1399.99ms | 9578 | 160 | 569922 | 10264.6 | 0.163021 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1273.19 | 0.344303 | 720.004ms | 9578 | 320 | 195252 | 7174.35 | 1.05461 | 1(Win) | true |
| Glaze | 1028.16 | 0.315569 | 906.083ms | 9578 | 1280 | 1.00607e+06 | 8884.12 | 0.113285 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7623.51 | 0.0776794 | 140.369ms | 9578 | 640 | 554.41 | 1198.17 | 0.0858643 | 1(Win) | true |
| Glaze | 3993.42 | 0.341356 | 253.615ms | 9578 | 30 | 1828.92 | 2287.33 | 0.418533 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2154.8 | 0.0998587 | 180.425ms | 3873 | 160 | 468.785 | 1714.12 | 0.568833 | 1(Win) | true |
| Glaze | 1148.69 | 0.433866 | 332.495ms | 3873 | 640 | 124562 | 3215.48 | 1.72706 | 2(Loss) | true |
| Jsonifier (two-stage) | 768.824 | 0.391624 | 534.348ms | 3873 | 1280 | 453095 | 4804.19 | 1.31893 | 3(Loss) | true |
| simdjson (ondemand) | 475.911 | 0.108792 | 863.773ms | 3873 | 30 | 2138.75 | 7761.07 | 1.25409 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2426.72 | 0.408512 | 152.201ms | 3873 | 1280 | 49485.3 | 1522.05 | 0.578986 | 1(Win) | true |
| Glaze | 1210.19 | 1.59198 | 284.612ms | 3873 | 80 | 188867 | 3052.07 | 0.813266 | 2(Loss) | true |
| Jsonifier (two-stage) | 841.54 | 0.123133 | 468.76ms | 3873 | 80 | 2336.6 | 4389.07 | 1.06897 | 3(Loss) | true |
| simdjson (ondemand) | 444.959 | 0.279736 | 847.378ms | 3873 | 2560 | 1.38035e+06 | 8300.94 | 0.846219 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2887.56 | 0.543713 | 139.342ms | 3873 | 30 | 1451.09 | 1279.13 | 0.104346 | 1(Win) | true |
| Glaze | 502.125 | 0.478883 | 730.657ms | 3873 | 1280 | 1.58833e+06 | 7355.9 | 0.326396 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3103.58 | 0.195502 | 128.888ms | 3873 | 4890 | 26471.7 | 1190.1 | 0.563268 | 1(Win) | true |
| Glaze | 2237.22 | 0.101653 | 199.914ms | 3873 | 160 | 450.647 | 1650.97 | 0.00567816 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1557.22 | 0.0804021 | 6244.62ms | 94653 | 1280 | 2.78044e+06 | 57967.5 | 0.0456418 | 1(Win) | true |
| Glaze | 1131.16 | 0.0914735 | 8235.87ms | 94653 | 4890 | 2.60568e+07 | 79801.5 | 0.165361 | 2(Loss) | true |
| Jsonifier (two-stage) | 1099.23 | 0.492304 | 8416.27ms | 94653 | 30 | 4.9032e+06 | 82119.5 | 0.223833 | 3(Loss) | true |
| simdjson (ondemand) | 788.784 | 0.308542 | 5479ms | 94653 | 160 | 1.99481e+07 | 114440 | 0.0040795 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2314.16 | 0.0470062 | 5966.28ms | 94653 | 30 | 10085.9 | 39006.9 | 0.372303 | 1(Win) | true |
| Jsonifier (two-stage) | 1500.49 | 0.126647 | 8155.53ms | 94653 | 640 | 3.71512e+06 | 60159 | 0.0860544 | 2(Loss) | true |
| Glaze | 1293.34 | 0.165924 | 8057.94ms | 94653 | 4890 | 6.55802e+07 | 69794.7 | 0.127933 | 3(Loss) | true |
| simdjson (ondemand) | 1099.29 | 0.25883 | 5105.67ms | 94653 | 30 | 1.35518e+06 | 82115.2 | 0.0610557 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11026.9 | 0.501582 | 837.401ms | 94653 | 1280 | 2.15803e+06 | 8186.2 | 1.1267 | 1(Win) | true |
| Glaze | 3471.43 | 0.452727 | 2675.69ms | 94653 | 40 | 554349 | 26003.1 | 0.0942907 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12408 | 0.057244 | 731.799ms | 94653 | 40 | 693.717 | 7274.98 | 0.0941324 | 1(Win) | true |
| Glaze | 4262.95 | 0.0702092 | 2289.05ms | 94653 | 40 | 8840.9 | 21175 | 0.105384 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1627.22 | 0.410643 | 7638.92ms | 124597 | 80 | 7.19355e+06 | 73023.5 | 0.719204 | 1(Win) | true |
| Jsonifier (two-stage) | 1391.37 | 0.0889973 | 9135.88ms | 124597 | 640 | 3.69714e+06 | 85401.6 | 0.176461 | 2(Loss) | true |
| Glaze | 1362.56 | 0.10823 | 8944.47ms | 124597 | 640 | 5.70142e+06 | 87207.4 | 0.123335 | 3(Loss) | true |
| simdjson (ondemand) | 1113.65 | 0.116565 | 5608.12ms | 124597 | 1280 | 1.97997e+07 | 106698 | 0.439325 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2044.37 | 0.617965 | 7296.32ms | 124597 | 160 | 2.06416e+07 | 58122.9 | 0.0169977 | 1(Win) | true |
| Jsonifier (two-stage) | 1843.62 | 0.160701 | 8759.22ms | 124597 | 320 | 3.43288e+06 | 64451.8 | 0.00156127 | 2(Loss) | true |
| Glaze | 1739.82 | 0.135521 | 8446.56ms | 124597 | 320 | 2.74139e+06 | 68297.3 | 0.423164 | 3(Loss) | true |
| simdjson (ondemand) | 1396.7 | 0.0857123 | 5299.33ms | 124597 | 640 | 3.40309e+06 | 85075.3 | 0.148986 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10979.2 | 0.158707 | 1200.65ms | 136037 | 4890 | 1.7198e+06 | 11816.4 | 0.0562918 | 1(Win) | true |
| Glaze | 3508.14 | 0.0496353 | 3951.69ms | 136076 | 30 | 10113.7 | 36991.7 | 0.552728 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11265.2 | 0.208175 | 1166.1ms | 136037 | 2560 | 1.47141e+06 | 11516.4 | 0.163413 | 1(Win) | true |
| Glaze | 3456.12 | 0.16929 | 3817.38ms | 136076 | 4890 | 1.97587e+07 | 37548.6 | 2.37421 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 636.788 | 0.682849 | 5168.32ms | 2251027 | 80 | 4.23947e+10 | 3.37121e+06 | 0.720616 | 1(Win) | true |
| Glaze STATISTICAL TIE | 511.901 | 1.73464 | 6383.75ms | 2251027 | 40 | 2.11674e+11 | 4.19367e+06 | 0.529327 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE DID NOT CONVERGE | 505.59 | 0.451851 | 6842.45ms | 2251027 | 80 | 2.94473e+10 | 4.24602e+06 | 6.35221 | -(Tie) | false |
| Jsonifier (two-stage) STATISTICAL TIE DID NOT CONVERGE | 501.681 | 1.12669 | 5766.45ms | 2251027 | 30 | 6.97331e+10 | 4.2791e+06 | 9.53401 | -(Tie) | false |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 778.619 | 1.1675 | 5106.56ms | 2251027 | 40 | 4.14464e+10 | 2.75712e+06 | 0.501113 | 1(Win) | true |
| Jsonifier (two-stage) | 709.171 | 0.525068 | 5652.6ms | 2251027 | 40 | 1.01053e+10 | 3.02712e+06 | 1.59172 | 2(Loss) | true |
| simdjson (ondemand) | 610.996 | 0.313568 | 6201.22ms | 2251027 | 40 | 4.85521e+09 | 3.51352e+06 | 0.587302 | 3(Loss) | true |
| Glaze | 558.379 | 0.962436 | 6871.02ms | 2251027 | 80 | 1.09531e+11 | 3.84461e+06 | 0.780794 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2666.83 | 0.477486 | 5225.57ms | 2090234 | 40 | 5.09542e+08 | 747479 | 0.0160142 | 1(Win) | true |
| Glaze | 1810.75 | 0.301244 | 7079.27ms | 2090234 | 160 | 1.75967e+09 | 1.10087e+06 | 0.262945 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2118.01 | 2.41381 | 5516.37ms | 2090234 | 80 | 4.12883e+10 | 941166 | 1.11901 | 1(Win) | true |
| Glaze | 1790.52 | 0.191662 | 7178.15ms | 2090234 | 160 | 7.28486e+08 | 1.11331e+06 | 0.0277289 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1259.18 | 0.924199 | 6030.23ms | 5373214 | 30 | 4.24372e+10 | 4.06956e+06 | 0.733651 | 1(Win) | true |
| Jsonifier (two-stage) | 1151.67 | 1.21627 | 6260.88ms | 5373214 | 40 | 1.17147e+11 | 4.44946e+06 | 1.62111 | 2(Loss) | true |
| Glaze | 1040.83 | 0.873269 | 7795.56ms | 5373214 | 40 | 7.39373e+10 | 4.92327e+06 | 1.03987 | 3(Loss) | true |
| simdjson (ondemand) | 962.374 | 0.99646 | 8238.58ms | 5373214 | 40 | 1.12606e+11 | 5.32464e+06 | 1.5462 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1596.35 | 0.795003 | 5857.61ms | 5373214 | 40 | 2.60503e+10 | 3.21002e+06 | 1.34867 | 1(Win) | true |
| Jsonifier (two-stage) | 1401.27 | 0.474608 | 6673.62ms | 5373214 | 80 | 2.40981e+10 | 3.65688e+06 | 2.29426 | 2(Loss) | true |
| simdjson (ondemand) | 1174.03 | 0.54813 | 7648.84ms | 5373214 | 80 | 4.57897e+10 | 4.36471e+06 | 1.81558 | 3(Loss) | true |
| Glaze DID NOT CONVERGE | 1116.76 | 1.40239 | 7648.71ms | 5373214 | 30 | 1.24226e+11 | 4.58855e+06 | 5.33116 | -(Loss) | false |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6583.73 | 0.375086 | 6223.58ms | 6661897 | 320 | 4.19241e+09 | 964998 | 2.10238 | 1(Win) | true |
| Glaze | 3220.22 | 0.606758 | 6343.91ms | 6661897 | 160 | 2.29285e+10 | 1.97293e+06 | 3.45201 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6579.24 | 0.54248 | 6312.44ms | 6661897 | 80 | 2.19534e+09 | 965656 | 1.78502 | 1(Win) | true |
| Glaze | 3471.73 | 0.493716 | 5438.72ms | 6661897 | 160 | 1.3061e+10 | 1.83e+06 | 3.7838 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2030.87 | 0.169894 | 6117.48ms | 500299 | 320 | 5.09802e+07 | 234935 | 0.0589846 | 1(Win) | true |
| Jsonifier (two-stage) | 1365.32 | 0.114843 | 9214.22ms | 500299 | 1280 | 2.06164e+08 | 349459 | 0.644181 | 2(Loss) | true |
| Glaze | 1157.09 | 0.7789 | 5226.99ms | 500299 | 80 | 8.25243e+08 | 412348 | 2.63752 | 3(Loss) | true |
| simdjson (ondemand) | 801.597 | 0.177169 | 7805.73ms | 500299 | 640 | 7.11709e+08 | 595215 | 1.18061 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2446.45 | 0.464777 | 6102.85ms | 500299 | 30 | 2.46488e+07 | 195026 | 0.961391 | 1(Win) | true |
| Jsonifier (two-stage) | 1592.3 | 0.373242 | 9137.96ms | 500299 | 30 | 3.75242e+07 | 299643 | 1.18397 | 2(Loss) | true |
| Glaze | 1343.43 | 0.252607 | 5051.75ms | 500299 | 80 | 6.43892e+07 | 355153 | 0.0468909 | 3(Loss) | true |
| simdjson (ondemand) | 861.007 | 0.43509 | 7739.72ms | 500299 | 30 | 1.74392e+08 | 554144 | 0.3991 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7170.25 | 0.222576 | 6688.88ms | 500299 | 4890 | 1.07265e+08 | 66542 | 0.679126 | 1(Win) | true |
| Glaze | 1852.26 | 0.766105 | 6259.92ms | 500299 | 80 | 3.11546e+08 | 257589 | 0.1327 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7025.3 | 0.218079 | 6780.57ms | 500299 | 4890 | 1.07267e+08 | 67914.8 | 1.32419 | 1(Win) | true |
| Glaze | 2222.95 | 0.199291 | 5742.23ms | 500299 | 160 | 2.92749e+07 | 214635 | 0.152978 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2479.54 | 0.498142 | 5490.59ms | 1151920 | 320 | 1.55868e+09 | 443048 | 0.291598 | 1(Win) | true |
| Jsonifier (two-stage) | 2216.88 | 1.37888 | 5852.51ms | 1151920 | 30 | 1.40067e+09 | 495542 | 0.654228 | 2(Loss) | true |
| Glaze | 1788.96 | 1.14637 | 7768.9ms | 1151920 | 80 | 3.96441e+09 | 614074 | 0.683065 | 3(Loss) | true |
| simdjson (ondemand) | 1545.4 | 0.845602 | 9198.97ms | 1151920 | 80 | 2.89057e+09 | 710855 | 0.0198753 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2908.87 | 0.305729 | 5398.01ms | 1151920 | 640 | 8.53196e+08 | 377658 | 0.21586 | 1(Win) | true |
| Jsonifier (two-stage) | 2798.15 | 0.328787 | 5562.69ms | 1151920 | 640 | 1.06638e+09 | 392601 | 1.96049 | 2(Loss) | true |
| Glaze | 2005.15 | 1.017 | 7732.43ms | 1151920 | 40 | 1.2418e+09 | 547868 | 1.29894 | 3(Loss) | true |
| simdjson (ondemand) | 1684.84 | 0.541889 | 8940.94ms | 1151920 | 160 | 1.99742e+09 | 652026 | 0.172403 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13652.2 | 0.494942 | 5561.45ms | 1439562 | 40 | 9.90882e+06 | 100560 | 0.214402 | 1(Win) | true |
| Glaze | 3893.93 | 0.80152 | 9486.42ms | 1439584 | 40 | 3.19438e+08 | 352573 | 0.813915 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13388.7 | 0.358441 | 5717.98ms | 1439562 | 640 | 8.64565e+07 | 102539 | 3.43367 | 1(Win) | true |
| Glaze | 4581.07 | 0.229553 | 8088.28ms | 1439584 | 160 | 7.57226e+07 | 299689 | 3.79083 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2180.24 | 0.986556 | 2544.38ms | 56369 | 160 | 9.46753e+06 | 24656.8 | 0.244263 | 1(Win) | true |
| Glaze | 1270 | 1.30037 | 4213.04ms | 56369 | 80 | 2.42378e+07 | 42328.8 | 1.36362 | 2(Loss) | true |
| Jsonifier (two-stage) | 1026.02 | 1.72448 | 4929.97ms | 56369 | 30 | 2.44912e+07 | 52394.5 | 1.95129 | 3(Loss) | true |
| simdjson (ondemand) | 657.565 | 0.201365 | 8665.12ms | 56369 | 4890 | 1.3252e+08 | 81752.6 | 1.25883 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2864.76 | 1.07631 | 2164.63ms | 56369 | 80 | 3.26338e+06 | 18765.1 | 0.337262 | 1(Win) | true |
| Glaze | 1596.28 | 0.277425 | 3599.48ms | 56369 | 4890 | 4.26838e+07 | 33676.9 | 2.17452 | 2(Loss) | true |
| Jsonifier (two-stage) | 1417.04 | 1.27965 | 4653.78ms | 56369 | 80 | 1.88534e+07 | 37936.5 | 0.0384672 | 3(Loss) | true |
| simdjson (ondemand) | 728.799 | 0.789921 | 7935.38ms | 56369 | 160 | 5.43191e+07 | 73762 | 0.0402654 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11264.3 | 2.4033 | 491.048ms | 56369 | 80 | 1.05239e+06 | 4772.38 | 1.02914 | 1(Win) | true |
| Glaze | 3376.33 | 0.146912 | 2045.49ms | 56369 | 40 | 21886 | 15921.9 | 0.0600686 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10699.5 | 1.07959 | 501.137ms | 56369 | 640 | 1.88299e+06 | 5024.29 | 3.46962 | 1(Win) | true |
| Glaze | 3335.22 | 0.323057 | 1617.04ms | 56369 | 2560 | 6.94116e+06 | 16118.2 | 0.927872 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2016.81 | 0.432359 | 3997.48ms | 83958 | 1280 | 3.77131e+07 | 39700.6 | 3.08223 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1526.25 | 1.04189 | 5292.52ms | 83958 | 80 | 2.39004e+07 | 52460.9 | 1.43088 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1504.92 | 0.245949 | 5016.34ms | 83958 | 4890 | 8.37333e+07 | 53204.7 | 0.132573 | 2(Tie) | true |
| simdjson (ondemand) | 946.397 | 1.20459 | 8426.13ms | 83958 | 80 | 8.30889e+07 | 84603.6 | 3.33807 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2459.49 | 0.705302 | 3675.69ms | 83958 | 160 | 8.43537e+06 | 32554.9 | 2.45305 | 1(Win) | true |
| Glaze | 2001.09 | 0.806246 | 4505.94ms | 83958 | 30 | 3.12211e+06 | 40012.5 | 0.093892 | 2(Loss) | true |
| Jsonifier (two-stage) | 1910.95 | 0.734534 | 4886.49ms | 83958 | 320 | 3.0311e+07 | 41899.9 | 1.02149 | 3(Loss) | true |
| simdjson (ondemand) | 985.087 | 0.891566 | 7832.54ms | 83958 | 160 | 8.40238e+07 | 81280.7 | 0.391727 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12322.1 | 0.221829 | 802.719ms | 94370 | 640 | 168001 | 7303.78 | 0.629756 | 1(Win) | true |
| Glaze | 2322.66 | 1.24246 | 3816.45ms | 94370 | 80 | 1.85418e+07 | 38747.9 | 1.24241 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13787.3 | 0.0599133 | 745.902ms | 94370 | 80 | 1223.63 | 6527.64 | 0.0400382 | 1(Win) | true |
| Glaze | 3058.71 | 0.649567 | 3139.38ms | 94370 | 320 | 1.16893e+07 | 29423.6 | 0.333335 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1592.32 | 0.301247 | 3200.5ms | 53331 | 2560 | 2.37019e+07 | 31941 | 2.01197 | 1(Win) | true |
| Jsonifier (two-stage) | 1485.58 | 1.24158 | 3886.78ms | 53331 | 30 | 5.42048e+06 | 34236.1 | 2.02382 | 2(Loss) | true |
| Glaze | 1244.54 | 0.211943 | 3949.44ms | 53331 | 4890 | 3.66847e+07 | 40866.7 | 0.525874 | 3(Loss) | true |
| simdjson (ondemand) | 882.482 | 0.0511183 | 6725.85ms | 53331 | 30 | 26038.9 | 57633.4 | 0.00485806 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2107.17 | 0.36768 | 2889ms | 53331 | 2560 | 2.01623e+07 | 24136.8 | 0.509707 | 1(Win) | true |
| Glaze | 1852.57 | 0.514581 | 3572.35ms | 53331 | 320 | 6.38662e+06 | 27454 | 2.26547 | 2(Loss) | true |
| Jsonifier (two-stage) | 1772.69 | 0.244439 | 3612.9ms | 53331 | 2560 | 1.25915e+07 | 28691.2 | 0.357317 | 3(Loss) | true |
| simdjson (ondemand) | 890.523 | 0.267054 | 6481.9ms | 53331 | 2560 | 5.95533e+07 | 57113 | 1.0693 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11849 | 1.31719 | 461.485ms | 58581 | 320 | 1.23424e+06 | 4714.94 | 1.43181 | 1(Win) | true |
| Glaze | 4797.21 | 0.257234 | 1314.95ms | 58581 | 30 | 26922.3 | 11645.8 | 2.51298 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12745.2 | 0.310867 | 418.386ms | 58581 | 2560 | 475347 | 4383.4 | 1.43861 | 1(Win) | true |
| Glaze | 6184.59 | 0.0481271 | 1122.55ms | 58581 | 80 | 1512.03 | 9033.29 | 0.0222837 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1634.27 | 1.85742 | 4151.37ms | 65103 | 160 | 7.96697e+07 | 37990.7 | 1.91589 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE DID NOT CONVERGE | 1582.3 | 0.285157 | 4085.84ms | 65103 | 4890 | 6.12213e+07 | 39238.6 | 5.21306 | -(Tie) | false |
| Glaze | 1341.6 | 0.957264 | 4210.72ms | 65103 | 640 | 1.25603e+08 | 46278.4 | 0.702276 | 3(Loss) | true |
| simdjson (ondemand) | 1054.61 | 0.543835 | 6824.85ms | 65103 | 40 | 4.10026e+06 | 58872 | 0.664792 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2065.07 | 0.77025 | 3803.62ms | 65103 | 640 | 3.43222e+07 | 30065.3 | 1.13603 | 1(Win) | true |
| Jsonifier | 1911.47 | 0.511501 | 3482.73ms | 65103 | 640 | 1.76661e+07 | 32481.3 | 0.536474 | 2(Loss) | true |
| Glaze | 1801.17 | 0.626083 | 4029.31ms | 65103 | 320 | 1.49042e+07 | 34470.4 | 1.03293 | 3(Loss) | true |
| simdjson (ondemand) | 974.378 | 0.639307 | 6468.98ms | 65103 | 320 | 5.31027e+07 | 63719.7 | 2.59658 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11647.5 | 0.816241 | 625.075ms | 78778 | 2560 | 7.09608e+06 | 6450.16 | 1.51624 | 1(Win) | true |
| Glaze | 3915.65 | 0.449195 | 2199.61ms | 78778 | 1280 | 9.50785e+06 | 19186.7 | 1.27755 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13460.9 | 0.871354 | 572.629ms | 78778 | 160 | 378416 | 5581.23 | 0.870412 | 1(Win) | true |
| Glaze | 4398.52 | 0.335705 | 1735.58ms | 78778 | 2560 | 8.41693e+06 | 17080.4 | 1.53104 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2167.13 | 0.344785 | 576.764ms | 11812 | 1280 | 411133 | 5198.02 | 0.580159 | 1(Win) | true |
| Jsonifier (two-stage) | 1197.21 | 0.126452 | 1036.23ms | 11812 | 4890 | 692263 | 9409.24 | 0.140014 | 2(Loss) | true |
| Glaze | 880.627 | 0.744756 | 1235.18ms | 11812 | 320 | 2.9043e+06 | 12791.8 | 0.234925 | 3(Loss) | true |
| simdjson (ondemand) | 640.507 | 0.362592 | 1677.69ms | 11812 | 2560 | 1.04106e+07 | 17587.3 | 1.7976 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2179.63 | 0.0384173 | 602.256ms | 11812 | 160 | 630.747 | 5168.21 | 0.23141 | 1(Win) | true |
| Jsonifier (two-stage) | 1233.1 | 0.195679 | 1074.28ms | 11812 | 40 | 12782 | 9135.35 | 0.356492 | 2(Loss) | true |
| Glaze | 1130.69 | 0.10453 | 1152.26ms | 11812 | 160 | 17352.3 | 9962.76 | 0.206156 | 3(Loss) | true |
| simdjson (ondemand) | 848.687 | 0.375787 | 1568.73ms | 11812 | 160 | 398066 | 13273.2 | 0.697629 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9695.11 | 0.25093 | 131.071ms | 11812 | 2560 | 21761.4 | 1161.91 | 0.328156 | 1(Win) | true |
| Glaze | 2348.2 | 0.0805075 | 593.518ms | 11812 | 30 | 447.476 | 4797.2 | 0.0583333 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10240.7 | 0.150995 | 126.81ms | 11812 | 160 | 441.402 | 1100.01 | 0.143543 | 1(Win) | true |
| Glaze | 2620.7 | 0.0502057 | 511.691ms | 11812 | 80 | 372.572 | 4298.4 | 0.061032 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2547.93 | 0.890051 | 1080.65ms | 25388 | 160 | 1.14455e+06 | 9502.59 | 0.474841 | 1(Win) | true |
| Jsonifier (two-stage) | 1794.22 | 0.6529 | 1280.25ms | 25388 | 640 | 4.96798e+06 | 13494.4 | 2.27241 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1485.56 | 0.435236 | 1568.04ms | 25388 | 160 | 805098 | 16298.2 | 0.142896 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 1483.03 | 0.299875 | 1647.7ms | 25388 | 2560 | 6.13594e+06 | 16326 | 0.558944 | 3(Tie) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2291.03 | 0.302786 | 1045.65ms | 25388 | 1280 | 1.31063e+06 | 10568.1 | 0.316087 | 1(Win) | true |
| Jsonifier (two-stage) | 1959.64 | 1.09061 | 1247.1ms | 25388 | 40 | 726278 | 12355.2 | 1.48638 | 2(Loss) | true |
| simdjson (ondemand) | 1627.3 | 0.0790901 | 1619.44ms | 25388 | 80 | 11077.9 | 14878.6 | 0.0596139 | 3(Loss) | true |
| Glaze | 1358.1 | 0.301148 | 1577.19ms | 25388 | 640 | 1.84474e+06 | 17827.8 | 0.327135 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12942.6 | 0.213684 | 240.782ms | 31235 | 320 | 7739.94 | 2301.55 | 0.0799093 | 1(Win) | true |
| Glaze | 3185.63 | 0.440379 | 910.75ms | 31235 | 1280 | 2.17047e+06 | 9350.74 | 1.57459 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14435.3 | 0.161434 | 216.003ms | 31235 | 40 | 443.895 | 2063.55 | 0.0509091 | 1(Win) | true |
| Glaze | 4014.86 | 0.176887 | 779.477ms | 31235 | 1280 | 220468 | 7419.44 | 1.95669 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2414.84 | 0.246302 | 4294.12ms | 108313 | 2560 | 2.84157e+07 | 42775.2 | 0.738884 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1418.16 | 0.783614 | 6853.68ms | 108313 | 640 | 2.08495e+08 | 72837.6 | 0.713147 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1406.59 | 0.335511 | 7617.71ms | 108313 | 80 | 4.85661e+06 | 73436.9 | 0.228584 | 2(Tie) | true |
| simdjson (ondemand) | 618.574 | 0.866661 | 8167.66ms | 108313 | 160 | 3.35117e+08 | 166989 | 0.275076 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2541.71 | 1.22701 | 3955.82ms | 108313 | 80 | 1.98928e+07 | 40640.1 | 0.044794 | 1(Win) | true |
| Jsonifier (two-stage) | 1642.9 | 2.46891 | 6117.59ms | 108313 | 30 | 7.22883e+07 | 62873.6 | 3.28063 | 2(Loss) | true |
| Glaze | 1345.38 | 0.759811 | 7989.95ms | 108313 | 320 | 1.089e+08 | 76777.6 | 0.750118 | 3(Loss) | true |
| simdjson (ondemand) | 708.089 | 0.0718479 | 8027.58ms | 108313 | 1280 | 1.40613e+07 | 145879 | 0.336658 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11222.3 | 0.304234 | 920.6ms | 108313 | 4890 | 3.83459e+06 | 9204.43 | 0.480692 | 1(Win) | true |
| Glaze | 2087.16 | 0.298128 | 5057.52ms | 108313 | 320 | 6.96637e+06 | 49490.9 | 0.0664136 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11963.8 | 0.257093 | 870.751ms | 108313 | 4890 | 2.40943e+06 | 8634 | 1.63436 | 1(Win) | true |
| Glaze | 1985.67 | 0.557025 | 4601.33ms | 108313 | 320 | 2.68687e+07 | 52020.4 | 0.1393 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2708.4 | 0.131549 | 6803.12ms | 183677 | 1280 | 9.26546e+06 | 64675.9 | 0.364627 | 1(Win) | true |
| Jsonifier (two-stage) | 2382.46 | 0.623974 | 8010.21ms | 183677 | 160 | 3.36752e+07 | 73523.9 | 0.356748 | 2(Loss) | true |
| Glaze | 1568.56 | 0.416106 | 5866.49ms | 183677 | 640 | 1.38197e+08 | 111675 | 1.08724 | 3(Loss) | true |
| simdjson (ondemand) | 998.677 | 0.231517 | 9020.86ms | 183677 | 1280 | 2.11075e+08 | 175400 | 0.823738 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2589.88 | 0.167206 | 6652.13ms | 183677 | 4890 | 6.25404e+07 | 67635.5 | 0.0236789 | 1(Win) | true |
| Jsonifier (two-stage) | 2471.42 | 0.283561 | 7382.44ms | 183677 | 1280 | 5.17035e+07 | 70877.4 | 0.178757 | 2(Loss) | true |
| Glaze | 1729.49 | 0.275296 | 5248.74ms | 183677 | 1280 | 9.95146e+07 | 101283 | 0.396107 | 3(Loss) | true |
| simdjson (ondemand) | 1055.07 | 0.555156 | 8805.08ms | 183677 | 80 | 6.79617e+07 | 166024 | 0.99323 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15247.9 | 0.43554 | 1410.31ms | 213963 | 160 | 543543 | 13382.2 | 1.234 | 1(Win) | true |
| Glaze | 2841.35 | 0.133818 | 7235.69ms | 213963 | 4890 | 4.51617e+07 | 71814.9 | 0.341005 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14338.9 | 2.00529 | 1472.19ms | 213963 | 30 | 2.44298e+06 | 14230.6 | 0.668503 | 1(Win) | true |
| Glaze | 3284.72 | 0.132794 | 6303.1ms | 213963 | 4890 | 3.32773e+07 | 62121.3 | 1.095 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 623.529 | 0.521914 | 8871.34ms | 1834197 | 40 | 8.57504e+09 | 2.80537e+06 | 4.08848 | 1(Win) | true |
| Jsonifier (two-stage) | 538.25 | 0.212668 | 10311.7ms | 1834197 | 30 | 1.43301e+09 | 3.24984e+06 | 0.380906 | 2(Loss) | true |
| Glaze | 425.463 | 0.902668 | 6112.58ms | 1834197 | 40 | 5.50914e+10 | 4.11135e+06 | 1.16859 | 3(Loss) | true |
| simdjson (ondemand) | 390.479 | 0.298822 | 7024.11ms | 1834197 | 40 | 7.16775e+09 | 4.47969e+06 | 0.163114 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 718.203 | 0.281531 | 8872.4ms | 1834197 | 160 | 7.52262e+09 | 2.43556e+06 | 1.09209 | 1(Win) | true |
| Jsonifier (two-stage) | 600.109 | 0.38071 | 10338.1ms | 1834197 | 80 | 9.85168e+09 | 2.91485e+06 | 0.565197 | 2(Loss) | true |
| Glaze | 483.942 | 0.563363 | 6021.07ms | 1834197 | 40 | 1.6586e+10 | 3.61454e+06 | 0.393698 | 3(Loss) | true |
| simdjson (ondemand) | 412.329 | 0.479415 | 7059.55ms | 1834197 | 80 | 3.30917e+10 | 4.24231e+06 | 0.888054 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1284.55 | 0.60758 | 8783.88ms | 1834197 | 160 | 1.09527e+10 | 1.36175e+06 | 0.0213756 | 1(Win) | true |
| Glaze | 774.482 | 0.704854 | 7286.72ms | 1833577 | 40 | 1.01306e+10 | 2.25781e+06 | 0.707355 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1206.27 | 0.46563 | 8597ms | 1834197 | 160 | 7.29473e+09 | 1.45012e+06 | 1.30982 | 1(Win) | true |
| Glaze | 734.059 | 1.32844 | 7238ms | 1833577 | 40 | 4.0057e+10 | 2.38214e+06 | 0.360888 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1938.53 | 0.936354 | 5428.65ms | 7351818 | 40 | 4.58758e+10 | 3.61678e+06 | 0.0319872 | 1(Win) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 1795.4 | 1.34288 | 5983.47ms | 7351818 | 30 | 8.25019e+10 | 3.90512e+06 | 5.6051 | -(Loss) | false |
| Glaze | 1357.32 | 0.587991 | 7790.18ms | 7351818 | 80 | 7.37994e+10 | 5.16548e+06 | 1.95246 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1235.21 | 0.994277 | 8388.25ms | 7351818 | 30 | 9.55534e+10 | 5.67616e+06 | 8.46708 | -(Loss) | false |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2301.45 | 0.152293 | 5360.68ms | 7351818 | 30 | 6.45759e+08 | 3.04645e+06 | 1.37676 | 1(Win) | true |
| Jsonifier (two-stage) | 2005.33 | 1.22777 | 5999.91ms | 7351818 | 30 | 5.5281e+10 | 3.49631e+06 | 2.47257 | 2(Loss) | true |
| Glaze | 1515.45 | 0.751037 | 7633.57ms | 7351818 | 30 | 3.62201e+10 | 4.6265e+06 | 2.61084 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1377.19 | 1.52354 | 8360.96ms | 7351818 | 30 | 1.80483e+11 | 5.09099e+06 | 9.7734 | -(Loss) | false |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4897.56 | 0.64746 | 6302.98ms | 9930848 | 40 | 6.27045e+09 | 1.93378e+06 | 0.403229 | 1(Win) | true |
| Glaze | 2942.25 | 0.423034 | 9877.82ms | 9930228 | 30 | 5.56199e+09 | 3.21869e+06 | 4.89573 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5242.83 | 0.575147 | 5895.14ms | 9930848 | 80 | 8.63553e+09 | 1.80643e+06 | 1.05395 | 1(Win) | true |
| Glaze | 3152.7 | 0.347422 | 10107.7ms | 9930228 | 30 | 3.2673e+09 | 3.00384e+06 | 0.4147 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 655.724 | 0.535407 | 8031.2ms | 1834197 | 40 | 8.15976e+09 | 2.66763e+06 | 1.1001 | 1(Win) | true |
| Jsonifier (two-stage) | 580.743 | 0.784641 | 10126ms | 1834197 | 80 | 4.46844e+10 | 3.01205e+06 | 1.54862 | 2(Loss) | true |
| Glaze | 421.411 | 1.00506 | 6310.32ms | 1834197 | 30 | 5.2214e+10 | 4.15088e+06 | 0.631944 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 390.169 | 1.51613 | 7495.68ms | 1834197 | 30 | 1.38605e+11 | 4.48325e+06 | 7.42148 | -(Loss) | false |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 811.833 | 0.0693567 | 7901.93ms | 1834197 | 80 | 1.78659e+08 | 2.15466e+06 | 0.113498 | 1(Win) | true |
| Jsonifier (two-stage) | 643.747 | 0.253161 | 10397ms | 1834197 | 30 | 1.41963e+09 | 2.71726e+06 | 0.370224 | 2(Loss) | true |
| Glaze | 504.275 | 0.376336 | 6006.76ms | 1834197 | 80 | 1.36332e+10 | 3.4688e+06 | 0.124213 | 3(Loss) | true |
| simdjson (ondemand) | 380.932 | 0.612574 | 7368.04ms | 1834197 | 40 | 3.165e+10 | 4.59196e+06 | 1.14139 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1427.26 | 0.254532 | 8148.5ms | 1834197 | 320 | 3.114e+09 | 1.22558e+06 | 0.29899 | 1(Win) | true |
| Glaze | 829.402 | 0.463017 | 6996.72ms | 1833577 | 160 | 1.52469e+10 | 2.10831e+06 | 3.57685 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1391.19 | 0.317232 | 7998.34ms | 1834197 | 320 | 5.09122e+09 | 1.25736e+06 | 3.21559 | 1(Win) | true |
| Glaze | 825.874 | 0.576591 | 6636.35ms | 1833577 | 80 | 1.19233e+10 | 2.11732e+06 | 0.826381 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2005.14 | 0.437656 | 5271.4ms | 7351818 | 30 | 7.02567e+09 | 3.49664e+06 | 0.108957 | 1(Win) | true |
| Jsonifier (two-stage) | 1819.28 | 0.764378 | 5743.39ms | 7351818 | 30 | 2.60331e+10 | 3.85385e+06 | 0.607439 | 2(Loss) | true |
| Glaze | 1403.9 | 0.309044 | 7586.95ms | 7351818 | 30 | 7.14628e+09 | 4.99412e+06 | 1.41183 | 3(Loss) | true |
| simdjson (ondemand) | 1322.7 | 0.503319 | 8053.89ms | 7351818 | 30 | 2.13538e+10 | 5.30071e+06 | 0.442134 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2191.42 | 0.379853 | 5421.35ms | 7351818 | 80 | 1.18157e+10 | 3.1994e+06 | 0.24647 | 1(Win) | true |
| Jsonifier (two-stage) | 2053.41 | 0.380996 | 5764.19ms | 7351818 | 40 | 6.76924e+09 | 3.41444e+06 | 0.242565 | 2(Loss) | true |
| Glaze | 1500.46 | 0.3473 | 7590.67ms | 7351818 | 80 | 2.10688e+10 | 4.67273e+06 | 1.43585 | 3(Loss) | true |
| simdjson (ondemand) | 1428.97 | 0.880854 | 8084.61ms | 7351818 | 40 | 7.47153e+10 | 4.90649e+06 | 0.354705 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5176.07 | 0.463388 | 5741.52ms | 9930848 | 160 | 1.15022e+10 | 1.82973e+06 | 1.65511 | 1(Win) | true |
| Glaze | 2693.21 | 0.994692 | 5401.41ms | 9930228 | 30 | 3.6701e+10 | 3.51633e+06 | 2.01151 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5181.59 | 0.195961 | 5779.14ms | 9930848 | 160 | 2.05262e+09 | 1.82778e+06 | 2.36866 | 1(Win) | true |
| Glaze | 3183.88 | 0.274568 | 9421.73ms | 9930228 | 30 | 2.0009e+09 | 2.97442e+06 | 0.307243 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 984.235 | 0.363711 | 5075.91ms | 461466 | 40 | 1.05792e+08 | 447138 | 0.133063 | 1(Win) | true |
| Jsonifier (two-stage) | 832.905 | 2.01454 | 6260.16ms | 461466 | 30 | 3.39909e+09 | 528378 | 0.650257 | 2(Loss) | true |
| Glaze | 792.246 | 0.114844 | 7075.03ms | 461466 | 640 | 2.60471e+08 | 555495 | 0.414806 | 3(Loss) | true |
| simdjson (ondemand) | 575.747 | 0.467534 | 9660.93ms | 461466 | 320 | 4.08689e+09 | 764378 | 3.54433 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1546.09 | 0.569511 | 9309.18ms | 461466 | 320 | 8.40934e+08 | 284645 | 0.0432939 | 1(Win) | true |
| Jsonifier (two-stage) | 1228.51 | 0.756619 | 6080.11ms | 461466 | 640 | 4.70175e+09 | 358230 | 0.603918 | 2(Loss) | true |
| Glaze | 959.73 | 0.536914 | 7334.64ms | 461466 | 30 | 1.8185e+08 | 458554 | 1.70062 | 3(Loss) | true |
| simdjson (ondemand) | 646.029 | 1.01999 | 9692.93ms | 461466 | 30 | 1.44839e+09 | 681221 | 2.37803 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10653.4 | 0.755883 | 4665.15ms | 461466 | 40 | 3.90004e+06 | 41309.5 | 0.0643304 | 1(Win) | true |
| Glaze | 2468.97 | 0.239924 | 9235.29ms | 461466 | 1280 | 2.34101e+08 | 178248 | 0.260695 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10151.8 | 0.26441 | 4412.09ms | 461466 | 1280 | 1.68173e+07 | 43350.6 | 0.358215 | 1(Win) | true |
| Glaze | 2734.61 | 0.198951 | 8434.29ms | 461466 | 1280 | 1.31218e+08 | 160933 | 0.826569 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1625.33 | 0.080954 | 5542.85ms | 728486 | 320 | 3.83167e+07 | 427446 | 0.00155139 | 1(Win) | true |
| Jsonifier (two-stage) | 1248.25 | 0.0687269 | 7357.85ms | 728486 | 160 | 2.34107e+07 | 556570 | 0.106884 | 2(Loss) | true |
| Glaze | 1070.85 | 1.18061 | 8306.79ms | 728486 | 40 | 2.34669e+09 | 648772 | 1.69858 | 3(Loss) | true |
| simdjson (ondemand) | 992.151 | 0.13856 | 9149.47ms | 728486 | 640 | 6.02481e+08 | 700235 | 0.172578 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2053.37 | 0.232953 | 5445.76ms | 728486 | 30 | 1.86365e+07 | 338340 | 0.133219 | 1(Win) | true |
| Jsonifier (two-stage) | 1789.89 | 0.183797 | 7145.9ms | 728486 | 40 | 2.03575e+07 | 388146 | 0.431092 | 2(Loss) | true |
| Glaze | 1345.06 | 0.362927 | 7669ms | 728486 | 640 | 2.24892e+09 | 516510 | 0.156915 | 3(Loss) | true |
| simdjson (ondemand) | 1142.76 | 0.0709305 | 8900.46ms | 728486 | 320 | 5.95039e+07 | 607946 | 0.108071 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11675.6 | 0.0581599 | 7383.99ms | 837491 | 2560 | 4.05216e+06 | 68406.8 | 0.33913 | 1(Win) | true |
| Glaze | 3292.34 | 0.088061 | 6372.61ms | 837491 | 1280 | 5.84155e+07 | 242591 | 0.359184 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12803.6 | 0.124116 | 6461.43ms | 837491 | 2560 | 1.53459e+07 | 62380.6 | 1.65975 | 1(Win) | true |
| Glaze | 3627.47 | 0.16541 | 5851.62ms | 837491 | 160 | 2.12225e+07 | 220179 | 0.101449 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 4998.14 | 0.100309 | 10108.1ms | 466906 | 640 | 5.11091e+06 | 89088.4 | 0.0147663 | 1(Win) | true |
| Jsonifier | 4962.98 | 0.179137 | 9619.16ms | 466906 | 640 | 1.65319e+07 | 89719.5 | 0.504125 | 2(Loss) | true |
| simdjson (ondemand) | 3320.99 | 0.304427 | 6519.18ms | 466906 | 2560 | 4.2651e+08 | 134079 | 0.214248 | 3(Loss) | true |
| Glaze | 1922.46 | 0.99708 | 5363.83ms | 466906 | 40 | 2.13335e+08 | 231618 | 0.0537309 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5100.87 | 0.0788378 | 9234.79ms | 466906 | 1280 | 6.06247e+06 | 87294.1 | 0.103593 | 1(Win) | true |
| Jsonifier (two-stage) | 4166.77 | 1.38052 | 5415.54ms | 466906 | 40 | 8.70574e+07 | 106864 | 1.00396 | 2(Loss) | true |
| simdjson (ondemand) | 3967.82 | 0.361636 | 6751.25ms | 466906 | 80 | 1.31761e+07 | 112222 | 0.393854 | 3(Loss) | true |
| Glaze | 2037.8 | 0.814206 | 5740.94ms | 466906 | 160 | 5.06434e+08 | 218508 | 0.614115 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4996.73 | 0.418806 | 6592.91ms | 631514 | 30 | 7.64437e+06 | 120531 | 2.19986 | 1(Win) | true |
| Jsonifier (two-stage) | 4849.96 | 0.195009 | 6471.26ms | 631514 | 1280 | 7.50599e+07 | 124178 | 2.50171 | 2(Loss) | true |
| simdjson (ondemand) | 4226.46 | 1.261 | 7209.66ms | 631514 | 30 | 9.68647e+07 | 142497 | 1.44961 | 3(Loss) | true |
| Glaze | 2403.33 | 0.601299 | 6334.94ms | 631514 | 80 | 1.81639e+08 | 250593 | 1.24853 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 5280.46 | 0.377651 | 6645.76ms | 631514 | 30 | 5.56578e+06 | 114054 | 0.336104 | 1(Win) | true |
| Jsonifier | 5208.1 | 0.447726 | 6510.54ms | 631514 | 30 | 8.04182e+06 | 115639 | 0.912793 | 2(Loss) | true |
| simdjson (ondemand) | 4073.61 | 0.647278 | 7532.8ms | 631514 | 640 | 5.86096e+08 | 147844 | 1.46717 | 3(Loss) | true |
| Glaze | 2671.31 | 0.38909 | 5863.16ms | 631514 | 30 | 2.30854e+07 | 225454 | 0.017331 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1777.3 | 3.1287 | 5992.23ms | 466906 | 160 | 9.83071e+09 | 250535 | 0.086602 | 1(Win) | true |
| Jsonifier (two-stage) | 1636.97 | 0.760629 | 7052.81ms | 466906 | 80 | 3.42464e+08 | 272013 | 2.42737 | 2(Loss) | true |
| Glaze | 1353.5 | 0.98101 | 8166.9ms | 466906 | 30 | 3.1247e+08 | 328981 | 0.931065 | 3(Loss) | true |
| simdjson (ondemand) | 811.133 | 0.0866537 | 7472.21ms | 466906 | 640 | 1.4482e+08 | 548956 | 0.428692 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2647.3 | 0.283517 | 5094.42ms | 466906 | 1280 | 2.91085e+08 | 168200 | 0.524297 | 1(Win) | true |
| Jsonifier (two-stage) | 2152.43 | 0.164585 | 6455.64ms | 466906 | 80 | 9.27414e+06 | 206871 | 0.0849376 | 2(Loss) | true |
| Glaze | 1896.95 | 0.48788 | 7001.54ms | 466906 | 640 | 8.39371e+08 | 234733 | 0.680456 | 3(Loss) | true |
| simdjson (ondemand) | 873.571 | 0.267329 | 7067.63ms | 466906 | 30 | 5.57028e+07 | 509719 | 0.0950338 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14941.4 | 0.0379873 | 3561.91ms | 475954 | 30 | 3995.27 | 30379 | 0.141305 | 1(Win) | true |
| Glaze | 4352.26 | 0.111512 | 6016.95ms | 475954 | 640 | 8.65613e+06 | 104292 | 0.107503 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12614 | 0.255139 | 3523.61ms | 475954 | 4890 | 4.12176e+07 | 35984.1 | 1.25542 | 1(Win) | true |
| Glaze | 4781.09 | 0.130091 | 5036.72ms | 475954 | 2560 | 3.90491e+07 | 94937.5 | 1.18933 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) DID NOT CONVERGE | 2047.19 | 0.838435 | 8287.09ms | 631514 | 40 | 2.43359e+08 | 294187 | 5.71418 | -(Win) | false |
| Jsonifier | 1838.2 | 0.426605 | 8300.2ms | 631514 | 1280 | 2.5006e+09 | 327636 | 1.18282 | 2(Loss) | true |
| Glaze | 1608.16 | 0.843907 | 9637.29ms | 631514 | 80 | 7.99077e+08 | 374503 | 3.66102 | 3(Loss) | true |
| simdjson (ondemand) | 954.585 | 0.581263 | 8359.12ms | 631514 | 320 | 4.30361e+09 | 630912 | 0.477479 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2563.09 | 0.243942 | 8230.47ms | 631514 | 40 | 1.31423e+07 | 234974 | 0.445457 | 1(Win) | true |
| Jsonifier | 2155.61 | 0.818788 | 7904.27ms | 631514 | 320 | 1.67463e+09 | 279392 | 0.0373652 | 2(Loss) | true |
| Glaze | 1870.53 | 0.527353 | 9007.79ms | 631514 | 1280 | 3.69021e+09 | 321973 | 3.9464 | 3(Loss) | true |
| simdjson (ondemand) | 892.044 | 1.91502 | 8324.59ms | 631514 | 80 | 1.3373e+10 | 675145 | 1.50882 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12452.8 | 0.340049 | 5322.46ms | 716365 | 1280 | 4.45479e+07 | 54861.5 | 1.33129 | 1(Win) | true |
| Glaze | 3590.91 | 0.161231 | 9885.56ms | 716365 | 2560 | 2.40878e+08 | 190252 | 0.563612 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11520.2 | 1.45316 | 5638.07ms | 716365 | 160 | 1.18823e+08 | 59302.9 | 0.0919328 | 1(Win) | true |
| Glaze | 4266.17 | 0.167011 | 8545.64ms | 716365 | 2560 | 1.83115e+08 | 160139 | 0.730157 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1326.9 | 1.66618 | 200.614ms | 2632 | 80 | 79475.6 | 1891.69 | 0.821165 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1025.88 | 0.760604 | 245.5ms | 2632 | 1280 | 443310 | 2446.75 | 1.62016 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1016.32 | 0.918524 | 283.672ms | 2632 | 640 | 329361 | 2469.77 | 1.02491 | 2(Tie) | true |
| simdjson (ondemand) | 749.057 | 0.413281 | 343.698ms | 2632 | 1280 | 245496 | 3350.97 | 1.60594 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1690.99 | 0.21386 | 180.035ms | 2632 | 4890 | 49278.4 | 1484.38 | 1.56789 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 1398.42 | 0.272693 | 221.501ms | 2632 | 4890 | 117153 | 1794.93 | 5.46287 | -(Loss) | false |
| Jsonifier (two-stage) | 1362.86 | 0.388569 | 227.093ms | 2632 | 1280 | 65556.2 | 1841.76 | 1.99078 | 3(Loss) | true |
| simdjson (ondemand) | 1175.52 | 0.0833648 | 240.326ms | 2632 | 640 | 2027.95 | 2135.29 | 0.066414 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7256.67 | 0.663492 | 38.7872ms | 2632 | 640 | 3370.92 | 345.898 | 1.06322 | 1(Win) | true |
| Glaze | 3034.81 | 0.125032 | 86.6561ms | 2632 | 320 | 342.217 | 827.094 | 0.0604161 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 10118.1 | 0.14644 | 32.1766ms | 2632 | 1280 | 168.931 | 248.078 | 5.39719 | -(Win) | false |
| Glaze | 3268.06 | 0.344861 | 79.0492ms | 2632 | 1280 | 8980.33 | 768.062 | 0.438073 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1530.1 | 0.416116 | 219.389ms | 3370 | 640 | 48891.2 | 2100.44 | 0.574608 | 1(Win) | true |
| Jsonifier (two-stage) | 1367.3 | 0.323189 | 228.145ms | 3370 | 2560 | 147736 | 2350.53 | 0.269226 | 2(Loss) | true |
| Glaze | 1274.15 | 0.153126 | 255.025ms | 3370 | 2560 | 38190.7 | 2522.38 | 0.151857 | 3(Loss) | true |
| simdjson (ondemand) | 991.188 | 0.808024 | 347.853ms | 3370 | 160 | 109829 | 3242.46 | 0.214077 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2060.02 | 0.144143 | 188.548ms | 3370 | 4890 | 24729.5 | 1560.12 | 0.0167639 | 1(Win) | true |
| Jsonifier (two-stage) | 1975.73 | 0.118542 | 213.388ms | 3370 | 320 | 1189.87 | 1626.68 | 0.00825999 | 2(Loss) | true |
| Glaze | 1919.35 | 0.280634 | 239.326ms | 3370 | 80 | 1766.53 | 1674.46 | 0.402236 | 3(Loss) | true |
| simdjson (ondemand) | 1460.87 | 0.116079 | 261.081ms | 3370 | 160 | 1043.43 | 2199.97 | 0.306051 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9085.46 | 0.135587 | 43.3776ms | 3643 | 2560 | 688.178 | 382.395 | 0.497952 | 1(Win) | true |
| Glaze | 3042.37 | 0.225713 | 119.24ms | 3682 | 80 | 542.931 | 1154.17 | 0.273669 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10347.7 | 0.342633 | 37.6245ms | 3643 | 640 | 846.977 | 335.75 | 0.517597 | 1(Win) | true |
| Glaze | 3701.79 | 0.119061 | 102.76ms | 3682 | 640 | 816.32 | 948.577 | 0.107776 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 587.589 | 0.315363 | 831.493ms | 4630 | 40 | 22464.5 | 7514.62 | 1.69722 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 585.376 | 0.530313 | 728.857ms | 4630 | 640 | 1.02408e+06 | 7543.03 | 0.0933764 | 1(Tie) | true |
| Glaze | 441.231 | 0.17238 | 982.744ms | 4630 | 40 | 11903.2 | 10007.2 | 0.190996 | 3(Loss) | true |
| simdjson (ondemand) | 409.816 | 0.240371 | 1092.14ms | 4630 | 4890 | 3.27987e+06 | 10774.4 | 0.0153589 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 716.586 | 0.318633 | 778.123ms | 4630 | 2560 | 986842 | 6161.87 | 0.920243 | 1(Win) | true |
| Jsonifier (two-stage) | 648.894 | 0.684281 | 794.402ms | 4630 | 1280 | 2.77519e+06 | 6804.67 | 0.138763 | 2(Loss) | true |
| Glaze | 554.058 | 0.132779 | 995.891ms | 4630 | 30 | 3359.14 | 7969.4 | 0.209946 | 3(Loss) | true |
| simdjson (ondemand) | 454.805 | 0.312505 | 1088.86ms | 4630 | 4890 | 4.50125e+06 | 9708.58 | 0.0143121 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2572.97 | 0.348666 | 180.849ms | 4630 | 80 | 2864.18 | 1716.11 | 0.151005 | 1(Win) | true |
| Glaze | 1500.28 | 0.219007 | 313.149ms | 4630 | 30 | 1246.4 | 2943.13 | 0.696186 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2617.27 | 0.136571 | 174.127ms | 4630 | 4890 | 25959.3 | 1687.07 | 1.02007 | 1(Win) | true |
| Glaze | 1737.24 | 0.362451 | 265.812ms | 4630 | 40 | 3394.69 | 2541.68 | 0.702891 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1158.07 | 0.760929 | 1022.83ms | 11579 | 320 | 1.68467e+06 | 9535.38 | 2.37385 | 1(Win) | true |
| Jsonifier (two-stage) | 1091.45 | 0.251134 | 1001.74ms | 11579 | 4890 | 3.15688e+06 | 10117.4 | 1.95703 | 2(Loss) | true |
| Glaze | 960.101 | 0.302895 | 1178.23ms | 11579 | 640 | 776735 | 11501.5 | 0.0287923 | 3(Loss) | true |
| simdjson (ondemand) | 830.528 | 0.528466 | 1308.3ms | 11579 | 640 | 3.15972e+06 | 13295.9 | 0.642718 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1327.25 | 0.212298 | 980.084ms | 11579 | 4890 | 1.52559e+06 | 8319.91 | 1.00704 | 1(Win) | true |
| Jsonifier | 1279.71 | 0.285624 | 1000.05ms | 11579 | 4890 | 2.97041e+06 | 8628.98 | 1.47037 | 2(Loss) | true |
| Glaze | 1072.31 | 0.234023 | 1265.97ms | 11579 | 640 | 371708 | 10298 | 0.350626 | 3(Loss) | true |
| simdjson (ondemand) | 1005.79 | 0.348331 | 1243.29ms | 11579 | 2560 | 3.74417e+06 | 10979.1 | 0.103261 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6523.17 | 0.444035 | 231.525ms | 14795 | 2560 | 236149 | 2163 | 1.19682 | 1(Win) | true |
| Glaze | 3171.5 | 0.251363 | 487.965ms | 14795 | 640 | 80035.7 | 4448.88 | 4.36238 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6826.9 | 0.47855 | 248.337ms | 14795 | 30 | 2934.67 | 2066.77 | 0.613387 | 1(Win) | true |
| Glaze | 3602.45 | 0.239465 | 421.066ms | 14795 | 30 | 2638.99 | 3916.67 | 0.0348814 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1073.85 | 0.679771 | 300.118ms | 3223 | 4890 | 1.85128e+06 | 2862.32 | 2.54449 | 1(Win) | true |
| Jsonifier (two-stage) | 894.155 | 0.165624 | 386.353ms | 3223 | 80 | 2593.16 | 3437.54 | 0.0577841 | 2(Loss) | true |
| Glaze | 679.823 | 0.249355 | 420.522ms | 3223 | 4890 | 621550 | 4521.32 | 2.23971 | 3(Loss) | true |
| simdjson (ondemand) | 657.662 | 0.234522 | 519.825ms | 3223 | 30 | 3604.16 | 4673.67 | 0.619489 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1856.13 | 0.225845 | 237.712ms | 3223 | 320 | 4475.85 | 1655.97 | 0.442209 | 1(Win) | true |
| Jsonifier (two-stage) | 1242.43 | 0.415074 | 334.887ms | 3223 | 640 | 67485.6 | 2473.95 | 1.0262 | 2(Loss) | true |
| Glaze | 971.395 | 0.779267 | 391.036ms | 3223 | 640 | 389118 | 3164.2 | 0.471824 | 3(Loss) | true |
| simdjson (ondemand) | 770.298 | 0.395761 | 461.4ms | 3223 | 4890 | 1.21949e+06 | 3990.26 | 0.561793 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7747.54 | 0.377426 | 47.4773ms | 3223 | 320 | 717.476 | 396.731 | 0.557624 | 1(Win) | true |
| Glaze | 1845.66 | 0.281814 | 182.503ms | 3223 | 30 | 660.792 | 1665.37 | 0.408643 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9108.14 | 0.688852 | 39.4843ms | 3223 | 30 | 162.12 | 337.467 | 0.0296238 | 1(Win) | true |
| Glaze | 2028.53 | 0.38375 | 163.932ms | 3223 | 30 | 1014.32 | 1515.23 | 0.0902766 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1447.55 | 0.933424 | 412.911ms | 5839 | 160 | 206294 | 3846.84 | 1.60015 | 1(Win) | true |
| Jsonifier (two-stage) | 1245.73 | 0.277172 | 433.854ms | 5839 | 2560 | 392976 | 4470.06 | 0.593698 | 2(Loss) | true |
| Glaze | 1204.7 | 0.143461 | 516.471ms | 5839 | 30 | 1319.18 | 4622.3 | 0.0339052 | 3(Loss) | true |
| simdjson (ondemand) | 1129.41 | 0.266848 | 543.362ms | 5839 | 30 | 5193.01 | 4930.43 | 0.336461 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2094.09 | 0.270498 | 353.069ms | 5839 | 2560 | 132450 | 2659.15 | 2.11523 | 1(Win) | true |
| Jsonifier (two-stage) | 1969.53 | 0.386804 | 349.622ms | 5839 | 1280 | 153088 | 2827.32 | 0.998889 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1437.03 | 0.663165 | 460.308ms | 5839 | 40 | 26414.7 | 3875 | 0.360001 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 1427.35 | 0.816156 | 482.706ms | 5839 | 160 | 162211 | 3901.28 | 0.420045 | 3(Tie) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11485.9 | 0.130767 | 66.2143ms | 6938 | 2560 | 1452.7 | 576.061 | 0.389108 | 1(Win) | true |
| Glaze | 2723.03 | 0.47597 | 279.446ms | 6960 | 30 | 4038.25 | 2437.57 | 0.0602055 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12555.2 | 0.602126 | 57.6281ms | 6938 | 40 | 402.769 | 527 | 1.43392 | 1(Win) | true |
| Glaze | 2332.79 | 1.97793 | 249.186ms | 6960 | 80 | 253385 | 2845.34 | 2.30433 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2075.39 | 0.319793 | 240.817ms | 4857 | 30 | 1528.26 | 2231.87 | 0.876849 | 1(Win) | true |
| Glaze | 1291.52 | 0.312413 | 390.698ms | 4857 | 40 | 5021.74 | 3586.47 | 0.304615 | 2(Loss) | true |
| Jsonifier (two-stage) | 1158.74 | 0.204014 | 402.013ms | 4857 | 2560 | 170264 | 3997.43 | 0.0060289 | 3(Loss) | true |
| simdjson (ondemand) | 620.139 | 0.106356 | 783.537ms | 4857 | 80 | 5048.66 | 7469.29 | 0.0349643 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2503.89 | 0.244385 | 211.971ms | 4857 | 2560 | 52322.9 | 1849.92 | 0.957385 | 1(Win) | true |
| Jsonifier (two-stage) | 1705.85 | 0.105966 | 357.853ms | 4857 | 30 | 248.378 | 2715.37 | 0.30784 | 2(Loss) | true |
| Glaze | 1557.43 | 1.20907 | 307.644ms | 4857 | 1280 | 1.65512e+06 | 2974.13 | 1.90309 | 3(Loss) | true |
| simdjson (ondemand) | 685.927 | 0.464771 | 717.163ms | 4857 | 320 | 315216 | 6752.9 | 0.303161 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11854 | 0.207277 | 42.621ms | 4857 | 640 | 419.847 | 390.755 | 0.402682 | 1(Win) | true |
| Glaze | 2976.35 | 0.0951738 | 160.764ms | 4857 | 320 | 702.028 | 1556.27 | 0.656889 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10922.1 | 0.830326 | 44.3815ms | 4857 | 320 | 3967.99 | 424.094 | 0.821433 | 1(Win) | true |
| Glaze | 3333.42 | 0.404509 | 134.847ms | 4857 | 1280 | 40440.9 | 1389.56 | 1.65066 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2115.51 | 0.130716 | 307.852ms | 6701 | 40 | 623.687 | 3020.82 | 0.000827595 | 1(Win) | true |
| Jsonifier (two-stage) | 1640.87 | 0.0686445 | 393.788ms | 6701 | 4890 | 34950.4 | 3894.63 | 0.0201883 | 2(Loss) | true |
| Glaze | 1545.79 | 0.122815 | 427.252ms | 6701 | 160 | 4124.78 | 4134.17 | 0.0170803 | 3(Loss) | true |
| simdjson (ondemand) | 871.267 | 0.138311 | 747.435ms | 6701 | 1280 | 131734 | 7334.8 | 0.0370908 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2508.18 | 0.0879004 | 280.61ms | 6701 | 80 | 401.266 | 2547.89 | 0.00147179 | 1(Win) | true |
| Jsonifier (two-stage) | 2158.8 | 0.0789891 | 352.777ms | 6701 | 80 | 437.399 | 2960.24 | 0.00295593 | 2(Loss) | true |
| Glaze | 1925.16 | 1.0938 | 365.571ms | 6701 | 160 | 210931 | 3319.5 | 0.664704 | 3(Loss) | true |
| simdjson (ondemand) | 994.515 | 0.0787048 | 661.165ms | 6701 | 4890 | 125074 | 6425.82 | 0.0830382 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12300.6 | 0.19057 | 61.568ms | 7376 | 320 | 380.054 | 571.866 | 0.0464704 | 1(Win) | true |
| Glaze | 3086.3 | 0.16324 | 234.619ms | 7376 | 40 | 553.703 | 2279.2 | 0.246305 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13266.3 | 0.395233 | 57.8165ms | 7376 | 80 | 351.348 | 530.237 | 0.778911 | 1(Win) | true |
| Glaze | 3565.19 | 0.0661509 | 206.966ms | 7376 | 320 | 545.129 | 1973.05 | 0.00110868 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1655.09 | 0.0890036 | 100.175ms | 1691 | 640 | 481.324 | 974.364 | 0.321915 | 1(Win) | true |
| Glaze | 1378.04 | 0.184933 | 120.295ms | 1691 | 160 | 749.402 | 1170.26 | 0.0427437 | 2(Loss) | true |
| Jsonifier (two-stage) | 1209.88 | 0.146564 | 142.267ms | 1691 | 160 | 610.626 | 1332.91 | 0.923104 | 3(Loss) | true |
| simdjson (ondemand) | 889.915 | 0.342674 | 176.793ms | 1691 | 2560 | 98717.1 | 1812.15 | 0.931861 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2206.88 | 0.24161 | 90.605ms | 1691 | 160 | 498.745 | 730.744 | 0.209109 | 1(Win) | true |
| Jsonifier (two-stage) | 1781.38 | 0.173367 | 122.925ms | 1691 | 160 | 394.118 | 905.288 | 0.258874 | 2(Loss) | true |
| Glaze | 1744.69 | 0.224546 | 107.062ms | 1691 | 1280 | 5514.04 | 924.327 | 0.0321283 | 3(Loss) | true |
| simdjson (ondemand) | 1306.66 | 0.0932818 | 141.205ms | 1691 | 640 | 848.276 | 1234.19 | 0.0881633 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9959.14 | 0.721043 | 27.6166ms | 1996 | 320 | 607.784 | 191.134 | 1.75565 | 1(Win) | true |
| Glaze | 3504.51 | 0.253247 | 57.8612ms | 1996 | 30 | 56.7644 | 543.167 | 0.0184139 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11630.4 | 0.485301 | 20.252ms | 1996 | 1280 | 807.54 | 163.669 | 1.52857 | 1(Win) | true |
| Glaze | 4718.91 | 0.195901 | 43.8404ms | 1996 | 640 | 399.661 | 403.384 | 0.0673531 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1646.04 | 0.458492 | 127.797ms | 2158 | 320 | 10515.6 | 1250.29 | 0.0651923 | 1(Win) | true |
| Jsonifier (two-stage) | 1467.09 | 0.260264 | 149.602ms | 2158 | 30 | 399.89 | 1402.8 | 0.392899 | 2(Loss) | true |
| Glaze | 1361.85 | 0.643776 | 149.798ms | 2158 | 160 | 15143.8 | 1511.2 | 0.0917302 | 3(Loss) | true |
| simdjson (ondemand) | 1285.4 | 0.244044 | 179.524ms | 2158 | 40 | 610.687 | 1601.08 | 1.21855 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2093.98 | 0.939128 | 112.772ms | 2158 | 160 | 13631 | 982.831 | 0.216042 | 1(Win) | true |
| Jsonifier (two-stage) | 1982.07 | 0.100211 | 132.474ms | 2158 | 1280 | 1385.82 | 1038.32 | 0.754357 | 2(Loss) | true |
| Glaze | 1839.68 | 0.58182 | 143.922ms | 2158 | 80 | 3389.1 | 1118.69 | 0.642121 | 3(Loss) | true |
| simdjson (ondemand) | 1306.35 | 0.755712 | 160.048ms | 2158 | 640 | 90714.4 | 1575.4 | 0.683635 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11472 | 0.229139 | 29.7306ms | 2866 | 1280 | 381.488 | 238.252 | 0.396177 | 1(Win) | true |
| Glaze | 3164.34 | 0.327032 | 93.9567ms | 2866 | 320 | 2553.39 | 863.759 | 0.724083 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13738.3 | 1.42463 | 23.8796ms | 2866 | 40 | 321.331 | 198.95 | 0.2267 | 1(Win) | true |
| Glaze | 3873.66 | 0.731462 | 74.4912ms | 2866 | 320 | 8523.98 | 705.594 | 0.426989 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1993.57 | 0.1172 | 212.423ms | 4390 | 4890 | 29622.9 | 2100.06 | 0.109088 | 1(Win) | true |
| Jsonifier (two-stage) | 1145.39 | 0.0607811 | 394.77ms | 4390 | 80 | 394.863 | 3655.19 | 0.000341979 | 2(Loss) | true |
| Glaze | 1028.34 | 0.195351 | 464.279ms | 4390 | 80 | 5060.29 | 4071.25 | 0.725433 | 3(Loss) | true |
| simdjson (ondemand) | 717.898 | 0.660861 | 609.482ms | 4390 | 320 | 475307 | 5831.79 | 0.26924 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2207.77 | 0.129483 | 207.206ms | 4390 | 80 | 482.319 | 1896.31 | 0.0257144 | 1(Win) | true |
| Jsonifier (two-stage) | 1390.98 | 0.234922 | 375.402ms | 4390 | 1280 | 63995.2 | 3009.85 | 4.35843 | 2(Loss) | true |
| Glaze | 1095.73 | 0.217956 | 409.541ms | 4390 | 40 | 2774.08 | 3820.85 | 0.107626 | 3(Loss) | true |
| simdjson (ondemand) | 732.972 | 0.290368 | 581.459ms | 4390 | 2560 | 704193 | 5711.85 | 0.55549 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 7646.55 | 3.046 | 62.4391ms | 4390 | 320 | 89003.9 | 547.519 | 10.43 | -(Win) | false |
| Glaze | 2297.95 | 0.163873 | 200.901ms | 4390 | 40 | 356.554 | 1821.9 | 0.395451 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9899.81 | 0.561223 | 51.3785ms | 4390 | 40 | 225.323 | 422.9 | 2.72943 | 1(Win) | true |
| Glaze | 2340.55 | 0.236496 | 177.483ms | 4390 | 1280 | 22906 | 1788.74 | 0.6773 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2466.62 | 0.536613 | 365.368ms | 9378 | 4890 | 1.85118e+06 | 3625.84 | 1.94403 | 1(Win) | true |
| Jsonifier (two-stage) | 1882.11 | 0.683098 | 455.96ms | 9378 | 1280 | 1.34867e+06 | 4751.87 | 0.469426 | 2(Loss) | true |
| Glaze | 1448.17 | 0.315679 | 619.507ms | 9378 | 2560 | 972996 | 6175.75 | 0.0147144 | 3(Loss) | true |
| simdjson (ondemand) | 1230.23 | 0.534929 | 697.212ms | 9378 | 160 | 241968 | 7269.81 | 0.209247 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2958.73 | 0.0402771 | 357.152ms | 9378 | 320 | 474.327 | 3022.77 | 0.0476818 | 1(Win) | true |
| Jsonifier (two-stage) | 2405.34 | 0.45575 | 445.184ms | 9378 | 1280 | 367563 | 3718.21 | 2.93727 | 2(Loss) | true |
| Glaze | 1621.14 | 0.514873 | 565.738ms | 9378 | 640 | 516370 | 5516.84 | 1.59449 | 3(Loss) | true |
| simdjson (ondemand) | 1453.98 | 2.19463 | 600.946ms | 9378 | 40 | 728928 | 6151.07 | 3.21752 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10316.2 | 1.29557 | 105.669ms | 11521 | 80 | 15231.7 | 1065.05 | 2.96307 | 1(Win) | true |
| Glaze | 2912.08 | 0.365429 | 385.964ms | 11521 | 2560 | 486653 | 3773 | 3.09704 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11275.4 | 0.776519 | 96.3421ms | 11521 | 320 | 18321.8 | 974.444 | 1.43258 | 1(Win) | true |
| Glaze | 3259.69 | 0.291253 | 340.137ms | 11521 | 4890 | 471280 | 3370.66 | 1.69589 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2712.27 | 0.275742 | 182.008ms | 4669 | 2560 | 52460.1 | 1641.69 | 0.0384127 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1388.22 | 0.0952391 | 413.076ms | 4669 | 160 | 1493.08 | 3207.5 | 0.201105 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1381.13 | 0.71251 | 346.877ms | 4669 | 320 | 168854 | 3223.97 | 0.522713 | 2(Tie) | true |
| simdjson (ondemand) | 508.367 | 0.673571 | 898.641ms | 4669 | 2560 | 8.91047e+06 | 8758.85 | 2.1359 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 2499.76 | 2.32097 | 196.734ms | 4669 | 40 | 68367.5 | 1781.25 | 5.12571 | -(Win) | false |
| Jsonifier (two-stage) | 1606.64 | 0.838824 | 309.763ms | 4669 | 2560 | 1.38355e+06 | 2771.45 | 0.706957 | 2(Loss) | true |
| Glaze | 1223.77 | 1.16577 | 350.023ms | 4669 | 4890 | 8.79797e+06 | 3638.52 | 0.797377 | 3(Loss) | true |
| simdjson (ondemand) | 497.548 | 0.377126 | 902.505ms | 4669 | 2560 | 2.91603e+06 | 8949.31 | 1.1495 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10608.3 | 0.838956 | 39.431ms | 4669 | 160 | 1984.06 | 419.738 | 0.238813 | 1(Win) | true |
| Glaze | 1502.96 | 0.462405 | 300.085ms | 4669 | 2560 | 480442 | 2962.63 | 0.0125274 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15376.4 | 0.279545 | 37.0619ms | 4669 | 160 | 104.849 | 289.581 | 0.183119 | 1(Win) | true |
| Glaze | 1653.54 | 1.10034 | 246.43ms | 4669 | 40 | 35117.8 | 2692.82 | 0.0151615 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2847.68 | 0.766126 | 281.927ms | 7932 | 640 | 265071 | 2656.39 | 0.119312 | 1(Win) | true |
| Jsonifier (two-stage) | 2497.87 | 0.534544 | 321.482ms | 7932 | 640 | 167715 | 3028.39 | 0.996739 | 2(Loss) | true |
| Glaze | 1653.99 | 0.355431 | 507.243ms | 7932 | 1280 | 338236 | 4573.51 | 2.58949 | 3(Loss) | true |
| simdjson (ondemand) | 821.421 | 0.456976 | 824.31ms | 7932 | 1280 | 2.26689e+06 | 9209.09 | 0.205654 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3116.7 | 0.133718 | 279.101ms | 7932 | 40 | 421.323 | 2427.1 | 0.0879737 | 1(Win) | true |
| Jsonifier (two-stage) | 2779.7 | 0.100562 | 319.492ms | 7932 | 80 | 599.142 | 2721.35 | 0.134305 | 2(Loss) | true |
| Glaze | 1758.38 | 0.378502 | 464.068ms | 7932 | 1280 | 339379 | 4301.99 | 2.24129 | 3(Loss) | true |
| simdjson (ondemand) | 1047.58 | 0.68907 | 841.233ms | 7932 | 640 | 1.58452e+06 | 7220.96 | 2.22998 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14411.6 | 0.550249 | 62.0924ms | 9249 | 2560 | 29035.3 | 612.046 | 0.271792 | 1(Win) | true |
| Glaze | 2581.82 | 0.853027 | 332.355ms | 9249 | 1280 | 1.08711e+06 | 3416.4 | 1.72389 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16570 | 0.118047 | 61.3298ms | 9249 | 4890 | 1930.92 | 532.32 | 0.908222 | 1(Win) | true |
| Glaze | 3038.67 | 0.321392 | 288.818ms | 9249 | 2560 | 222809 | 2902.76 | 0.558731 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 493.324 | 0.786915 | 892.002ms | 4604 | 320 | 1.56968e+06 | 8900.27 | 1.50315 | 1(Win) | true |
| Jsonifier (two-stage) | 439.617 | 0.285825 | 996.173ms | 4604 | 4890 | 3.98502e+06 | 9987.59 | 1.83288 | 2(Loss) | true |
| Glaze | 387.989 | 0.108038 | 1229.4ms | 4604 | 30 | 4484.46 | 11316.6 | 0.17231 | 3(Loss) | true |
| simdjson (ondemand) | 315.44 | 0.162207 | 1501.69ms | 4604 | 4890 | 2.49281e+06 | 13919.4 | 1.85362 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 661.397 | 0.459875 | 831.726ms | 4604 | 1280 | 1.19299e+06 | 6638.55 | 1.04964 | 1(Win) | true |
| Jsonifier (two-stage) | 561.347 | 0.404901 | 968.112ms | 4604 | 1280 | 1.28385e+06 | 7821.75 | 1.94699 | 2(Loss) | true |
| Glaze | 380.706 | 0.921483 | 1334.77ms | 4604 | 640 | 7.22845e+06 | 11533.1 | 0.71657 | 3(Loss) | true |
| simdjson (ondemand) | 358.779 | 0.152 | 1385.07ms | 4604 | 4890 | 1.69205e+06 | 12238 | 3.68441 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1898.69 | 0.248496 | 245.302ms | 4604 | 640 | 21133.9 | 2312.5 | 1.05245 | 1(Win) | true |
| Glaze | 1061.2 | 0.22181 | 479.259ms | 4604 | 30 | 2526.74 | 4137.5 | 0.101614 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1840.13 | 0.241196 | 246.246ms | 4604 | 4890 | 161965 | 2386.09 | 0.455151 | 1(Win) | true |
| Glaze | 996.988 | 0.320058 | 441.105ms | 4604 | 1280 | 254307 | 4403.98 | 1.78897 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1483.46 | 2.16379 | 1084.92ms | 18245 | 40 | 2.57649e+06 | 11729.2 | 0.188064 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1435.19 | 0.33005 | 1086.86ms | 18245 | 2560 | 4.09894e+06 | 12123.7 | 0.0113852 | 1(Tie) | true |
| Glaze | 1134.81 | 0.734356 | 1602.9ms | 18245 | 160 | 2.0285e+06 | 15332.8 | 2.65863 | 3(Loss) | true |
| simdjson (ondemand) | 1081.22 | 0.766923 | 1605.71ms | 18245 | 640 | 9.74861e+06 | 16092.7 | 1.51401 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2233.93 | 0.583597 | 1065.87ms | 18245 | 30 | 61986.3 | 7788.87 | 0.338651 | 1(Win) | true |
| Jsonifier (two-stage) | 1923.8 | 0.335748 | 1048.81ms | 18245 | 2560 | 2.36067e+06 | 9044.49 | 1.50547 | 2(Loss) | true |
| Glaze | 1296.95 | 0.193059 | 1572.73ms | 18245 | 1280 | 858678 | 13415.9 | 0.398757 | 3(Loss) | true |
| simdjson (ondemand) | 1249.13 | 0.171218 | 1561.77ms | 18245 | 2560 | 1.45618e+06 | 13929.6 | 0.315579 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5405.86 | 0.189826 | 452.683ms | 24579 | 30 | 2032.51 | 4336.1 | 0.000768746 | 1(Win) | true |
| Glaze | 3065.77 | 0.0730449 | 799.746ms | 24579 | 30 | 935.73 | 7645.83 | 0.380887 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5236.34 | 0.603674 | 460.858ms | 24579 | 640 | 467368 | 4476.48 | 1.379 | 1(Win) | true |
| Glaze | 3501.59 | 0.31892 | 668.332ms | 24579 | 1280 | 583405 | 6694.2 | 0.273345 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 676.088 | 0.412548 | 704.459ms | 4604 | 160 | 114851 | 6494.3 | 0.105396 | 1(Win) | true |
| Jsonifier (two-stage) | 441.022 | 0.626096 | 953.782ms | 4604 | 320 | 1.24332e+06 | 9955.78 | 1.64859 | 2(Loss) | true |
| Glaze | 350.731 | 0.505987 | 1269.96ms | 4604 | 320 | 1.28396e+06 | 12518.8 | 0.638271 | 3(Loss) | true |
| simdjson (ondemand) | 288.587 | 0.156068 | 1569.81ms | 4604 | 4890 | 2.75711e+06 | 15214.5 | 4.36298 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 887.847 | 0.179793 | 693.387ms | 4604 | 1280 | 101192 | 4945.35 | 1.06735 | 1(Win) | true |
| Jsonifier (two-stage) | 541.42 | 0.516062 | 951.924ms | 4604 | 1280 | 2.2419e+06 | 8109.63 | 0.201487 | 2(Loss) | true |
| Glaze | 375.342 | 0.233282 | 1265.47ms | 4604 | 4890 | 3.64155e+06 | 11697.9 | 0.0289854 | 3(Loss) | true |
| simdjson (ondemand) | 343.963 | 0.621338 | 1576.35ms | 4604 | 80 | 503262 | 12765.1 | 0.973867 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1854.11 | 0.170594 | 281.187ms | 4604 | 30 | 489.61 | 2368.1 | 0.172835 | 1(Win) | true |
| Glaze | 965.852 | 0.22705 | 515.855ms | 4604 | 1280 | 136364 | 4545.95 | 0.183552 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1905.52 | 0.61363 | 238.038ms | 4604 | 640 | 127950 | 2304.21 | 1.16123 | 1(Win) | true |
| Glaze | 891.884 | 0.257698 | 487.451ms | 4604 | 4890 | 787017 | 4922.97 | 2.05179 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1682 | 0.383905 | 1019.32ms | 18245 | 2560 | 4.0376e+06 | 10344.7 | 2.98645 | 1(Win) | true |
| Jsonifier (two-stage) | 1661.93 | 0.346415 | 1113.87ms | 18245 | 1280 | 1.68371e+06 | 10469.6 | 1.66674 | 2(Loss) | true |
| Glaze | 1109.17 | 0.601329 | 1580.45ms | 18245 | 160 | 1.42375e+06 | 15687.2 | 0.854954 | 3(Loss) | true |
| simdjson (ondemand) | 1071.68 | 0.193615 | 1623.41ms | 18245 | 4890 | 4.83219e+06 | 16236 | 1.22847 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2231.15 | 0.13575 | 977.033ms | 18245 | 30 | 3362.25 | 7798.57 | 0.57346 | 1(Win) | true |
| Jsonifier (two-stage) | 2149.47 | 0.328502 | 1055ms | 18245 | 640 | 452563 | 8094.91 | 0.494389 | 2(Loss) | true |
| simdjson (ondemand) | 1275 | 0.0810371 | 1637.12ms | 18245 | 40 | 4892.12 | 13646.9 | 0.306878 | 3(Loss) | true |
| Glaze | 1164.8 | 0.651454 | 1669.76ms | 18245 | 640 | 6.06081e+06 | 14938 | 1.49183 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4586.68 | 0.88229 | 486.799ms | 24579 | 640 | 1.30117e+06 | 5110.53 | 0.363181 | 1(Win) | true |
| Glaze | 3324.87 | 0.197177 | 768.263ms | 24579 | 30 | 5797.1 | 7050 | 0.138726 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5384.81 | 0.45919 | 444.373ms | 24579 | 2560 | 1.02285e+06 | 4353.06 | 1.5594 | 1(Win) | true |
| Glaze | 3929.21 | 0.152007 | 707.447ms | 24579 | 40 | 3289.3 | 5965.68 | 0.0532495 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1148.34 | 1.36947 | 407.809ms | 5094 | 160 | 537028 | 4230.46 | 0.699075 | 1(Win) | true |
| Jsonifier (two-stage) | 1036.21 | 0.133373 | 489.405ms | 5094 | 4890 | 191192 | 4688.26 | 0.714013 | 2(Loss) | true |
| Glaze | 799.686 | 0.181827 | 622.558ms | 5094 | 4890 | 596632 | 6074.91 | 2.05595 | 3(Loss) | true |
| simdjson (ondemand) | 639.406 | 0.334634 | 812.037ms | 5094 | 160 | 103425 | 7597.7 | 0.541135 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1895.83 | 0.458691 | 381.376ms | 5094 | 40 | 5526.1 | 2562.47 | 0.0523857 | 1(Win) | true |
| Jsonifier (two-stage) | 1355.15 | 0.328008 | 481.334ms | 5094 | 2560 | 353958 | 3584.85 | 0.367009 | 2(Loss) | true |
| Glaze | 861.51 | 0.383538 | 576.667ms | 5094 | 1280 | 598721 | 5638.96 | 0.101202 | 3(Loss) | true |
| simdjson (ondemand) | 716.24 | 0.226908 | 769.481ms | 5094 | 4890 | 1.15827e+06 | 6782.67 | 1.22237 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7227.04 | 1.14214 | 59.4812ms | 5094 | 30 | 1768.3 | 672.2 | 0.203727 | 1(Win) | true |
| Glaze | 2516.72 | 0.136257 | 196.189ms | 5094 | 4890 | 33827.6 | 1930.3 | 0.123049 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10851.8 | 0.352119 | 50.2707ms | 5094 | 160 | 397.569 | 447.669 | 0.183227 | 1(Win) | true |
| Glaze | 3151.15 | 0.220092 | 165.858ms | 5094 | 80 | 921.037 | 1541.66 | 0.207186 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1329.04 | 0.0680877 | 621.794ms | 8051 | 80 | 1237.8 | 5777.11 | 0.108086 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1316.62 | 0.484842 | 515.87ms | 8051 | 320 | 255818 | 5831.63 | 1.79754 | 1(Tie) | true |
| Glaze | 1215.32 | 0.31806 | 661.629ms | 8051 | 320 | 129207 | 6317.7 | 0.144942 | 3(Loss) | true |
| simdjson (ondemand) | 966.233 | 0.357196 | 842.012ms | 8051 | 640 | 515621 | 7946.36 | 2.73474 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2016.75 | 0.139787 | 473.226ms | 8051 | 4890 | 138496 | 3807.13 | 0.213362 | 1(Win) | true |
| Jsonifier (two-stage) | 1575.24 | 0.435652 | 657.301ms | 8051 | 2560 | 1.15432e+06 | 4874.2 | 0.756443 | 2(Loss) | true |
| Glaze | 1528.43 | 0.291087 | 640.571ms | 8051 | 30 | 6414.67 | 5023.47 | 0.163501 | 3(Loss) | true |
| simdjson (ondemand) | 1070.11 | 1.27865 | 803.319ms | 8051 | 160 | 1.34668e+06 | 7174.98 | 0.383196 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8448.2 | 1.4314 | 97.8495ms | 9255 | 80 | 17891 | 1044.75 | 3.29486 | 1(Win) | true |
| Glaze | 2324.67 | 3.63553 | 334.44ms | 9255 | 320 | 6.09702e+06 | 3796.78 | 0.46557 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12736.8 | 0.242021 | 81.8391ms | 9255 | 160 | 450.05 | 692.975 | 0.260871 | 1(Win) | true |
| Glaze | 3494.6 | 0.338258 | 258.915ms | 9255 | 4890 | 356913 | 2525.68 | 0.45222 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 3557.99 | 0.200563 | 80.4701ms | 2889 | 320 | 771.855 | 774.359 | 0.0181635 | 1(Win) | true |
| simdjson (ondemand) | 3420.16 | 0.453816 | 88.8623ms | 2889 | 30 | 400.944 | 805.567 | 0.686283 | 2(Loss) | true |
| Jsonifier | 2984.16 | 0.604003 | 86.5612ms | 2889 | 4890 | 152069 | 923.264 | 1.05182 | 3(Loss) | true |
| Glaze | 1882.11 | 0.311524 | 145.763ms | 2889 | 2560 | 53238.5 | 1463.87 | 0.33341 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 3883.93 | 0.147218 | 79.7122ms | 2889 | 40 | 43.625 | 709.375 | 0.335926 | 1(Win) | true |
| Jsonifier | 3854.12 | 0.2226 | 79.8002ms | 2889 | 160 | 405.151 | 714.862 | 0.0244742 | 2(Loss) | true |
| simdjson (ondemand) | 3633.34 | 0.402776 | 84.8604ms | 2889 | 40 | 373.138 | 758.3 | 0.19742 | 3(Loss) | true |
| Glaze | 2082.75 | 0.271599 | 146.805ms | 2889 | 80 | 1032.69 | 1322.85 | 3.32949 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 4118.56 | 0.0819002 | 94.4063ms | 3808 | 640 | 333.774 | 881.763 | 0.0138198 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 3987.75 | 0.156556 | 101.315ms | 3808 | 320 | 650.473 | 910.688 | 0.567077 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 3970.53 | 0.324049 | 96.2695ms | 3808 | 80 | 702.766 | 914.638 | 0.227713 | 2(Tie) | true |
| Glaze | 2122.24 | 0.475932 | 161.441ms | 3808 | 1280 | 84899 | 1711.2 | 1.57552 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4261.06 | 0.0728322 | 95.4401ms | 3808 | 1280 | 493.19 | 852.273 | 0.03647 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4258.06 | 0.197922 | 94.5893ms | 3808 | 160 | 455.909 | 852.875 | 0.0953569 | 1(Tie) | true |
| simdjson (ondemand) | 4177.28 | 0.678837 | 104.083ms | 3808 | 30 | 1044.86 | 869.367 | 0.79224 | 3(Loss) | true |
| Glaze | 2502.67 | 0.273719 | 155.248ms | 3808 | 80 | 1262.08 | 1451.09 | 0.583118 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2138.62 | 0.33942 | 136.682ms | 2889 | 640 | 12237.2 | 1288.29 | 0.119928 | 1(Win) | true |
| Glaze | 1652.49 | 0.390228 | 170.006ms | 2889 | 4890 | 206998 | 1667.28 | 0.521246 | 2(Loss) | true |
| Jsonifier (two-stage) | 1580.54 | 0.577236 | 189.659ms | 2889 | 4890 | 495108 | 1743.18 | 0.942107 | 3(Loss) | true |
| simdjson (ondemand) | 792.519 | 0.158465 | 363.356ms | 2889 | 30 | 910.464 | 3476.47 | 0.277289 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2934.36 | 0.412485 | 129.973ms | 2889 | 30 | 449.995 | 938.933 | 0.131182 | 1(Win) | true |
| Jsonifier (two-stage) | 2116.81 | 0.190455 | 163.418ms | 2889 | 80 | 491.591 | 1301.56 | 0.284118 | 2(Loss) | true |
| Glaze | 2064 | 0.380307 | 163.403ms | 2889 | 30 | 773.154 | 1334.87 | 1.02079 | 3(Loss) | true |
| simdjson (ondemand) | 872.499 | 0.157009 | 355.618ms | 2889 | 80 | 1966.55 | 3157.79 | 0.513663 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9810.74 | 0.641975 | 32.138ms | 2963 | 80 | 273.518 | 288.025 | 0.190592 | 1(Win) | true |
| Glaze | 3412.21 | 0.574845 | 89.8607ms | 2963 | 40 | 906.471 | 828.125 | 0.047318 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13385.8 | 0.235732 | 25.7582ms | 2963 | 1280 | 316.974 | 211.1 | 0.105732 | 1(Win) | true |
| Glaze | 4279.15 | 0.945594 | 70.0838ms | 2963 | 40 | 1559.62 | 660.35 | 0.0783026 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2168.42 | 0.0869988 | 184.041ms | 3808 | 160 | 339.667 | 1674.76 | 0.0500321 | 1(Win) | true |
| Glaze | 2005.35 | 0.178416 | 196.133ms | 3808 | 80 | 835.162 | 1810.95 | 0.0855172 | 2(Loss) | true |
| Jsonifier | 1806.85 | 4.64818 | 180.526ms | 3808 | 160 | 1.39648e+06 | 2009.9 | 0.618078 | 3(Loss) | true |
| simdjson (ondemand) | 1058.15 | 0.179579 | 378.746ms | 3808 | 30 | 1139.55 | 3432.03 | 0.0388346 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2354.81 | 0.199317 | 175.542ms | 3808 | 4890 | 46204 | 1542.2 | 0.833859 | 1(Win) | true |
| Glaze | 2206.49 | 0.337493 | 188.096ms | 3808 | 30 | 925.637 | 1645.87 | 0 | 2(Loss) | true |
| Jsonifier | 2020.15 | 0.51597 | 186.131ms | 3808 | 1280 | 110125 | 1797.68 | 0.973873 | 3(Loss) | true |
| simdjson (ondemand) | 1116.69 | 0.199916 | 372.842ms | 3808 | 40 | 1690.76 | 3252.1 | 0.952275 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11136.3 | 0.469102 | 51.0079ms | 4300 | 80 | 238.715 | 368.238 | 2.3437 | 1(Win) | true |
| Glaze | 3316.52 | 0.304334 | 147.503ms | 4300 | 40 | 566.41 | 1236.47 | 0.0195486 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13210.3 | 1.17141 | 38.9123ms | 4300 | 40 | 528.917 | 310.425 | 0.667495 | 1(Win) | true |
| Glaze | 3483.69 | 1.21244 | 115.552ms | 4300 | 640 | 130365 | 1177.14 | 1.78557 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2602.93 | 0.65557 | 9537.16ms | 466906 | 80 | 1.00615e+08 | 171067 | 0.319631 | 1(Win) | true |
| Glaze | 1659.53 | 0.341576 | 7093.86ms | 466906 | 30 | 2.51992e+07 | 268315 | 0.153538 | 2(Loss) | true |
| simdjson (ondemand) | 1199.29 | 0.661171 | 5274.13ms | 466906 | 40 | 2.41047e+08 | 371284 | 0.00455829 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2520.97 | 0.328458 | 9476.32ms | 466906 | 320 | 1.07704e+08 | 176629 | 0.435814 | 1(Win) | true |
| Glaze | 1645.57 | 0.618429 | 7297.25ms | 466906 | 40 | 1.12012e+08 | 270591 | 1.0332 | 2(Loss) | true |
| simdjson (ondemand) | 1070.12 | 0.464843 | 5228.81ms | 466906 | 640 | 2.39436e+09 | 416101 | 1.29733 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3053.47 | 0.723112 | 5654.73ms | 699405 | 80 | 1.99604e+08 | 218441 | 1.43194 | 1(Win) | true |
| Glaze | 2143.01 | 0.265156 | 7766.08ms | 699405 | 1280 | 8.71805e+08 | 311246 | 0.683666 | 2(Loss) | true |
| simdjson (ondemand) | 1320.69 | 1.09322 | 6734.29ms | 767297 | 80 | 2.93514e+09 | 554068 | 0.159578 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2792.56 | 0.504568 | 5815.86ms | 699405 | 640 | 9.29549e+08 | 238851 | 0.852514 | 1(Win) | true |
| Glaze | 2335.84 | 0.19766 | 7671.59ms | 699405 | 320 | 1.01943e+08 | 285552 | 1.48386 | 2(Loss) | true |
| simdjson (ondemand) | 1430.41 | 0.575579 | 6605.47ms | 767297 | 160 | 1.3872e+09 | 511568 | 0.853731 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2258.67 | 1.29138 | 6843.4ms | 631514 | 30 | 3.55704e+08 | 266643 | 0.463508 | 1(Win) | true |
| Glaze | 1796.28 | 0.288512 | 8492.39ms | 631514 | 640 | 5.98858e+08 | 335280 | 0.511968 | 2(Loss) | true |
