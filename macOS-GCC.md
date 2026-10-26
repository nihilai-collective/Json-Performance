# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest Results: (Oct 28, 2026)
#### Using the following commits:
----
| Jsonifier: [9f4382a](https://github.com/nihilai-collective/jsonifier/commit/9f4382a)  
| Glaze: [8ae6d0d](https://github.com/stephenberry/glaze/commit/8ae6d0d)  
| Simdjson: [ab504c9](https://github.com/simdjson/simdjson/commit/ab504c9)  

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
*Environment generated via BenchmarkSuite commit: [35ec835](https://github.com/nihilai-collective/benchmarksuite/commit/35ec835)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1364.29 | 1.12211 | 62.7622ms | 905 | 4890 | 246413 | 632.618 | 0.76574 | 1(Win) | true |
| glaze | 1257.23 | 1.18996 | 78.912ms | 905 | 4890 | 326316 | 686.488 | 2.00024 | 2(Loss) | true |
| jsonifier (two-stage) | 398.391 | 1.02734 | 245.6ms | 905 | 320 | 158509 | 2166.4 | 0.514328 | 3(Loss) | true |
| simdjson (ondemand) | 162.129 | 0.393024 | 613.228ms | 905 | 1280 | 560308 | 5323.4 | 0.929016 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| glaze STATISTICAL TIE DID NOT CONVERGE | 1747.12 | 4.02723 | 60.7639ms | 905 | 640 | 253307 | 494 | 5.14593 | -(Tie) | false |
| jsonifier STATISTICAL TIE | 1697.15 | 1.41424 | 52.063ms | 905 | 4890 | 252936 | 508.545 | 1.08057 | 1(Tie) | true |
| jsonifier (two-stage) | 406.191 | 1.7901 | 229.99ms | 905 | 160 | 231478 | 2124.8 | 1.84049 | 3(Loss) | true |
| simdjson (ondemand) | 127.012 | 1.02656 | 635.732ms | 905 | 640 | 3.11422e+06 | 6795.2 | 1.83751 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2168.53 | 4.88423 | 50.209ms | 905 | 640 | 241846 | 398 | 1.87377 | 1(Win) | true |
| simdjson (reflection) | 196.6 | 0.606304 | 460.793ms | 905 | 640 | 453408 | 4390 | 1.42806 | 2(Loss) | true |
| glaze | 93.2611 | 1.58646 | 835.062ms | 905 | 40 | 862219 | 9254.4 | 0.602968 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3446.79 | 6.85333 | 39.596ms | 905 | 640 | 188474 | 250.4 | 1.62338 | 1(Win) | true |
| simdjson (reflection) | 2532.5 | 7.82207 | 50.3962ms | 905 | 320 | 227401 | 340.8 | 2.40385 | 2(Loss) | true |
| glaze | 660.854 | 1.05483 | 138.808ms | 905 | 1280 | 242919 | 1306 | 0.647349 | 3(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 885.513 | 1.42657 | 204.338ms | 1811 | 640 | 495466 | 1950.4 | 0.1229 | 1(Win) | true |
| glaze | 709.807 | 0.315559 | 234.453ms | 1811 | 4890 | 288289 | 2433.2 | 2.50249 | 2(Loss) | true |
| jsonifier (two-stage) | 463.244 | 0.212822 | 385.365ms | 1811 | 4890 | 307864 | 3728.28 | 0.306207 | 3(Loss) | true |
| simdjson (ondemand) | 135.032 | 0.19072 | 1250.93ms | 1811 | 4890 | 2.9098e+06 | 12790.3 | 1.37366 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1092.48 | 0.667652 | 167.8ms | 1811 | 2560 | 285199 | 1580.9 | 2.12358 | 1(Win) | true |
| glaze | 903.055 | 0.486188 | 199.883ms | 1811 | 4890 | 422791 | 1912.51 | 1.0547 | 2(Loss) | true |
| jsonifier (two-stage) | 515.985 | 1.6257 | 399.227ms | 1811 | 80 | 236884 | 3347.2 | 0.759013 | 3(Loss) | true |
| simdjson (ondemand) | 164.549 | 0.905831 | 1249.36ms | 1811 | 30 | 271183 | 10496 | 0 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 284.286 | 0.728005 | 692.845ms | 1997 | 320 | 761140 | 6699.2 | 3.3572 | 1(Win) | true |
| jsonifier | 242.806 | 0.317709 | 702.935ms | 1811 | 2560 | 1.30742e+06 | 7113.1 | 1.15203 | 2(Loss) | true |
| glaze | 182.587 | 1.27144 | 894.864ms | 1798 | 320 | 4.56228e+06 | 9391.2 | 0.819534 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 753.273 | 0.591178 | 242.024ms | 1811 | 1280 | 235169 | 2292.8 | 0.702741 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 653.177 | 0.296297 | 307.436ms | 1997 | 4890 | 364970 | 2915.73 | 2.07456 | 2(Tie) | true |
| glaze STATISTICAL TIE | 599.548 | 1.13093 | 301.482ms | 1798 | 320 | 334777 | 2860 | 0.140056 | 2(Tie) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2363.45 | 0.546659 | 160.206ms | 3862 | 4890 | 354874 | 1558.35 | 1.46977 | 1(Win) | true |
| glaze | 1054.48 | 0.967135 | 333.785ms | 3862 | 320 | 365150 | 3492.8 | 0.182899 | 2(Loss) | true |
| jsonifier (two-stage) | 968.419 | 0.496247 | 387.658ms | 3862 | 640 | 227968 | 3803.2 | 0.188957 | 3(Loss) | true |
| simdjson (ondemand) | 436.013 | 0.435194 | 843.068ms | 3862 | 320 | 432455 | 8447.2 | 0.273895 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3024.88 | 2.76346 | 128.351ms | 3862 | 160 | 181149 | 1217.6 | 0.395778 | 1(Win) | true |
| glaze | 1436.3 | 0.323302 | 267.67ms | 3862 | 4890 | 336093 | 2564.29 | 0.0937841 | 2(Loss) | true |
| jsonifier (two-stage) | 1024.79 | 0.613523 | 384.392ms | 3862 | 640 | 311170 | 3594 | 0.255329 | 3(Loss) | true |
| simdjson (ondemand) | 440.983 | 0.954804 | 824.567ms | 3862 | 40 | 254372 | 8352 | 0.533537 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 779.523 | 1.07514 | 505.182ms | 3862 | 160 | 412874 | 4724.8 | 0.236486 | 1(Win) | true |
| simdjson (reflection) | 653.923 | 0.398675 | 532.552ms | 3862 | 2560 | 1.29077e+06 | 5632.3 | 1.56706 | 2(Loss) | true |
| glaze | 579.12 | 0.244567 | 641.776ms | 3862 | 1280 | 309666 | 6359.8 | 0.274344 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5333.17 | 1.89094 | 81.0652ms | 3862 | 1280 | 218282 | 690.6 | 0.202312 | 1(Win) | true |
| simdjson (reflection) | 3182.52 | 0.511214 | 127.689ms | 3862 | 4890 | 171158 | 1157.29 | 1.47194 | 2(Loss) | true |
| glaze | 2485.17 | 0.50515 | 182.388ms | 3862 | 4890 | 274069 | 1482.03 | 0.408222 | 3(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1314.1 | 0.290073 | 700.492ms | 9578 | 2560 | 1.04075e+06 | 6951 | 0.677298 | 1(Win) | true |
| glaze | 971.113 | 0.740758 | 913.54ms | 9578 | 640 | 3.10701e+06 | 9406 | 0.511931 | 2(Loss) | true |
| jsonifier (two-stage) | 764.453 | 0.436573 | 1222.92ms | 9578 | 40 | 108849 | 11948.8 | 0.0893495 | 3(Loss) | true |
| simdjson (ondemand) | 717.03 | 0.27348 | 1272.35ms | 9578 | 4890 | 5.9352e+06 | 12739.1 | 0.164825 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2153.35 | 0.510643 | 658.595ms | 9578 | 2560 | 1.20115e+06 | 4241.9 | 0.305037 | 1(Win) | true |
| glaze | 1580.64 | 0.292043 | 806.771ms | 9578 | 4890 | 1.39278e+06 | 5778.85 | 0.0251436 | 2(Loss) | true |
| jsonifier (two-stage) | 1004.15 | 0.629046 | 1177.1ms | 9578 | 30 | 98228.7 | 9096.53 | 0.559701 | 3(Loss) | true |
| simdjson (ondemand) | 926.117 | 0.275519 | 1240.88ms | 9578 | 2560 | 1.89043e+06 | 9863 | 0.556553 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1235.67 | 1.11385 | 750.049ms | 9578 | 1280 | 8.67777e+06 | 7392.2 | 1.30047 | 1(Win) | true |
| simdjson (reflection) | 1093.87 | 0.577485 | 859.74ms | 9578 | 640 | 1.48825e+06 | 8350.4 | 0.268972 | 2(Loss) | true |
| glaze | 881.961 | 0.288667 | 1031.79ms | 9578 | 4890 | 4.37073e+06 | 10356.8 | 0.0647021 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 10364.7 | 0.605931 | 98.453ms | 9578 | 4890 | 139441 | 881.289 | 1.9067 | 1(Win) | true |
| jsonifier | 8432.69 | 1.14611 | 122.03ms | 9578 | 640 | 98639.9 | 1083.2 | 0.587372 | 2(Loss) | true |
| glaze | 4104.14 | 0.712205 | 231.569ms | 9578 | 4890 | 1.22864e+06 | 2225.63 | 1.61224 | 3(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2206.7 | 1.41164 | 173.928ms | 3873 | 1280 | 714600 | 1673.8 | 2.68712 | 1(Win) | true |
| glaze | 1114.94 | 0.483748 | 341.31ms | 3873 | 1280 | 328730 | 3312.8 | 0.0723938 | 2(Loss) | true |
| jsonifier (two-stage) | 815.634 | 0.327606 | 457.37ms | 3873 | 4890 | 1.07626e+06 | 4528.48 | 0.897413 | 3(Loss) | true |
| simdjson (ondemand) | 398.427 | 0.787975 | 942.802ms | 3873 | 320 | 1.70754e+06 | 9270.4 | 0.433351 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2716.72 | 0.538967 | 142.379ms | 3873 | 4890 | 262567 | 1359.57 | 0.986009 | 1(Win) | true |
| glaze | 1400.61 | 0.334451 | 270.171ms | 3873 | 4890 | 380392 | 2637.11 | 0.0384701 | 2(Loss) | true |
| jsonifier (two-stage) | 841.286 | 1.1328 | 429.623ms | 3873 | 320 | 791527 | 4390.4 | 0.365764 | 3(Loss) | true |
| simdjson (ondemand) | 410.029 | 0.312889 | 909.802ms | 3873 | 2560 | 2.03371e+06 | 9008.1 | 0.883618 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 804.071 | 0.884272 | 486.302ms | 3873 | 160 | 263996 | 4593.6 | 1.2044 | 1(Win) | true |
| simdjson (reflection) DID NOT CONVERGE | 671.98 | 0.293377 | 518.406ms | 3873 | 4890 | 1.27158e+06 | 5496.57 | 5.22563 | -(Loss) | false |
| glaze | 512.314 | 1.11906 | 723.794ms | 3873 | 1280 | 8.33184e+06 | 7209.6 | 1.11373 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5215.45 | 1.81057 | 84.705ms | 3873 | 1280 | 210451 | 708.2 | 1.63889 | 1(Win) | true |
| simdjson (reflection) | 3291.65 | 0.65143 | 134.774ms | 3873 | 4890 | 261284 | 1122.11 | 3.7809 | 2(Loss) | true |
| glaze | 2825.57 | 1.98278 | 169.545ms | 3873 | 320 | 214972 | 1307.2 | 3.08422 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1157.36 | 0.558693 | 7607.11ms | 94653 | 30 | 5.69636e+06 | 77994.7 | 0.417491 | 1(Win) | true |
| glaze | 1051.15 | 1.04963 | 9376.68ms | 94653 | 40 | 3.2499e+07 | 85875.2 | 0.262636 | 2(Loss) | true |
| jsonifier (two-stage) | 888.993 | 0.204105 | 5100.99ms | 94653 | 2560 | 1.09956e+08 | 101540 | 3.52478 | 3(Loss) | true |
| simdjson (reflection) | 760.386 | 0.719947 | 6211.39ms | 94653 | 160 | 1.16875e+08 | 118714 | 0.755024 | 4(Loss) | true |
| simdjson (ondemand) | 629.65 | 0.184644 | 7210.66ms | 94653 | 2560 | 1.79383e+08 | 143362 | 0.372969 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2171.69 | 0.242581 | 7122.72ms | 94653 | 30 | 305006 | 41565.9 | 0.0821862 | 1(Win) | true |
| glaze | 1505.83 | 1.21119 | 7953.05ms | 94653 | 80 | 4.21727e+07 | 59945.6 | 0.0694444 | 2(Loss) | true |
| jsonifier (two-stage) | 1286 | 0.507705 | 9277.67ms | 94653 | 640 | 8.12807e+07 | 70192.8 | 0.236501 | 3(Loss) | true |
| simdjson (reflection) | 893.18 | 0.301959 | 6364.52ms | 94653 | 1280 | 1.19206e+08 | 101064 | 0.740733 | 4(Loss) | true |
| simdjson (ondemand) | 809.864 | 0.771423 | 6675.01ms | 94653 | 160 | 1.1829e+08 | 111461 | 0.736038 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12878.5 | 0.465344 | 753.364ms | 94653 | 640 | 680870 | 7009.2 | 0.35824 | 1(Win) | true |
| simdjson (reflection) | 9539.67 | 0.590313 | 1008.7ms | 94653 | 80 | 249607 | 9462.4 | 0.101557 | 2(Loss) | true |
| glaze | 5099.58 | 0.225982 | 2036.15ms | 94653 | 2560 | 4.09625e+06 | 17701.1 | 1.20235 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11994.8 | 0.737079 | 784.683ms | 94653 | 320 | 984601 | 7525.6 | 0.916368 | 1(Win) | true |
| simdjson (reflection) | 8092.24 | 0.364657 | 1081.02ms | 94653 | 2560 | 4.23584e+06 | 11154.9 | 1.67389 | 2(Loss) | true |
| glaze | 6188.85 | 0.730224 | 1620.41ms | 94653 | 80 | 907508 | 14585.6 | 0.349803 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 1141.33 | 0.225636 | 5421.17ms | 124597 | 1280 | 7.06357e+07 | 104111 | 0.441605 | 1(Win) | true |
| glaze | 1108.51 | 0.724959 | 5365.58ms | 124597 | 160 | 9.66239e+07 | 107194 | 1.79132 | 2(Loss) | true |
| jsonifier | 1054.33 | 0.206501 | 5670.05ms | 124597 | 2560 | 1.38659e+08 | 112702 | 0.533159 | 3(Loss) | true |
| simdjson (reflection) | 992.643 | 0.725555 | 6363.43ms | 124597 | 160 | 1.20695e+08 | 119706 | 1.60524 | 4(Loss) | true |
| simdjson (ondemand) | 884.148 | 0.183413 | 7426.48ms | 124597 | 2560 | 1.55548e+08 | 134395 | 2.4588 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 1570.58 | 0.575534 | 8952.39ms | 124597 | 320 | 6.06719e+07 | 75656.8 | 1.19524 | 1(Tie) | true |
| glaze STATISTICAL TIE | 1567.15 | 0.358563 | 9541.44ms | 124597 | 640 | 4.7305e+07 | 75822.4 | 0.048558 | 1(Tie) | true |
| jsonifier (two-stage) | 1481.08 | 0.395699 | 5270.33ms | 124597 | 1280 | 1.29003e+08 | 80228.8 | 0.393923 | 3(Loss) | true |
| simdjson (reflection) | 1201.1 | 0.280565 | 6068.84ms | 124597 | 640 | 4.93069e+07 | 98930.4 | 0.276512 | 4(Loss) | true |
| simdjson (ondemand) | 1121.93 | 0.310058 | 6750.25ms | 124597 | 1280 | 1.3803e+08 | 105911 | 0.58961 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14480.4 | 0.104906 | 901.456ms | 136037 | 4890 | 431982 | 8959.37 | 0.0872984 | 1(Win) | true |
| glaze | 4713.64 | 0.365084 | 2740.64ms | 136076 | 160 | 1.61643e+06 | 27531.2 | 0.260839 | 2(Loss) | true |
| simdjson (reflection) | 388.117 | 0.287048 | 8994.37ms | 136037 | 30 | 2.76197e+07 | 334268 | 0.189268 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14901.4 | 0.22137 | 918.82ms | 136037 | 1280 | 475451 | 8706.2 | 0.0849247 | 1(Win) | true |
| glaze | 5531.07 | 0.233446 | 2413.51ms | 136076 | 320 | 959989 | 23462.4 | 0.0545256 | 2(Loss) | true |
| simdjson (reflection) | 385.734 | 0.792797 | 8725.92ms | 136037 | 30 | 2.13297e+08 | 336333 | 0.406822 | 3(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 788.387 | 0.534659 | 8910.97ms | 2251027 | 30 | 6.35855e+09 | 2.72296e+06 | 1.63865 | 1(Win) | true |
| jsonifier (two-stage) DID NOT CONVERGE | 694.91 | 0.41955 | 9831.3ms | 2251027 | 160 | 2.68776e+10 | 3.08924e+06 | 6.92063 | -(Loss) | false |
| glaze | 592.317 | 0.640864 | 5699.01ms | 2251027 | 40 | 2.15797e+10 | 3.62432e+06 | 4.73564 | 3(Loss) | true |
| simdjson (ondemand) | 520.014 | 0.709637 | 5944.33ms | 2251027 | 40 | 3.43292e+10 | 4.12825e+06 | 0.560885 | 4(Loss) | true |
| simdjson (reflection) | 362.9 | 0.676207 | 8982.62ms | 2251027 | 80 | 1.28008e+11 | 5.91554e+06 | 0.927376 | 5(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 984.915 | 0.525384 | 8598.15ms | 2251027 | 160 | 2.09815e+10 | 2.17963e+06 | 0.318719 | 1(Win) | true |
| jsonifier (two-stage) | 883.204 | 1.43783 | 9258.46ms | 2251027 | 30 | 3.66417e+10 | 2.43063e+06 | 0.516904 | 2(Loss) | true |
| simdjson (reflection) | 778.248 | 0.168099 | 5207.97ms | 2251027 | 80 | 1.72006e+09 | 2.75844e+06 | 1.43309 | 3(Loss) | true |
| simdjson (ondemand) | 682.679 | 0.373394 | 5994.68ms | 2251027 | 80 | 1.10294e+10 | 3.14459e+06 | 1.09158 | 4(Loss) | true |
| glaze | 658.244 | 0.359732 | 5803.95ms | 2251027 | 40 | 5.50561e+09 | 3.26132e+06 | 0.222243 | 5(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2093.23 | 0.341886 | 5827.97ms | 2090234 | 320 | 3.3921e+09 | 952310 | 0.601469 | 1(Win) | true |
| glaze | 1482.61 | 1.42354 | 7970.49ms | 2090234 | 320 | 1.17226e+11 | 1.34452e+06 | 0.0116635 | 2(Loss) | true |
| simdjson (reflection) | 735.179 | 0.486353 | 8622.03ms | 2090326 | 160 | 2.78269e+10 | 2.71157e+06 | 0.583357 | 3(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2130.93 | 0.579183 | 5764.05ms | 2090234 | 160 | 4.69681e+09 | 935461 | 0.46019 | 1(Win) | true |
| glaze | 1472.65 | 0.527715 | 7759.99ms | 2090234 | 160 | 8.16417e+09 | 1.35362e+06 | 3.16943 | 2(Loss) | true |
| simdjson (reflection) | 715.917 | 0.394685 | 8679.91ms | 2090326 | 160 | 1.93252e+10 | 2.78453e+06 | 0.881476 | 3(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 1441.68 | 0.671183 | 5134.11ms | 5373214 | 80 | 4.55302e+10 | 3.55438e+06 | 0.77408 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1431.57 | 1.25611 | 5358.83ms | 5373214 | 40 | 8.08652e+10 | 3.5795e+06 | 0.332938 | 1(Tie) | true |
| simdjson (ondemand) | 1053.25 | 0.654374 | 7348.73ms | 5373214 | 80 | 8.10868e+10 | 4.86524e+06 | 3.72744 | 3(Loss) | true |
| glaze | 996.164 | 0.821858 | 7725.98ms | 5373214 | 30 | 5.36194e+10 | 5.14403e+06 | 3.09534 | 4(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 684.155 | 0.861406 | 5155.14ms | 5373214 | 30 | 1.24881e+11 | 7.48996e+06 | 5.64432 | -(Loss) | false |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 1708.99 | 0.899085 | 5227.53ms | 5373214 | 30 | 2.18028e+10 | 2.99843e+06 | 8.9723 | -(Win) | false |
| jsonifier (two-stage) | 1651.67 | 0.997325 | 5412.51ms | 5373214 | 40 | 3.82962e+10 | 3.1025e+06 | 0.29759 | 2(Loss) | true |
| simdjson (reflection) | 1298.27 | 0.865524 | 6693.47ms | 5373214 | 30 | 3.50123e+10 | 3.94703e+06 | 0.147013 | 3(Loss) | true |
| simdjson (ondemand) | 1232.79 | 0.668788 | 7236.82ms | 5373214 | 80 | 6.18239e+10 | 4.15666e+06 | 1.34536 | 4(Loss) | true |
| glaze | 1144.71 | 0.758782 | 7420.57ms | 5373214 | 40 | 4.61498e+10 | 4.47649e+06 | 0.0659999 | 5(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7284.43 | 0.902167 | 6125.32ms | 6661897 | 40 | 2.4765e+09 | 872173 | 0.948917 | 1(Win) | true |
| glaze DID NOT CONVERGE | 3159.32 | 0.607452 | 6454.49ms | 6661897 | 160 | 2.38755e+10 | 2.01097e+06 | 6.82931 | -(Loss) | false |
| simdjson (reflection) | 253.613 | 0.728919 | 7479.29ms | 6661989 | 30 | 1.00033e+12 | 2.50514e+07 | 2.86648 | 3(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6541.03 | 0.505304 | 6082.9ms | 6661897 | 320 | 7.70832e+09 | 971297 | 3.28103 | 1(Win) | true |
| glaze | 3817.08 | 0.547476 | 5440.6ms | 6661897 | 160 | 1.32857e+10 | 1.66443e+06 | 0.580799 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 287.412 | 0.5805 | 7236.66ms | 6661989 | 30 | 4.93998e+11 | 2.21055e+07 | 11.5789 | -(Loss) | false |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2033.03 | 0.291704 | 6441.21ms | 500299 | 160 | 7.49851e+07 | 234685 | 0.0354644 | 1(Win) | true |
| jsonifier (two-stage) | 1383.63 | 0.359629 | 9417.33ms | 500299 | 320 | 4.92131e+08 | 344834 | 0.315674 | 2(Loss) | true |
| glaze | 1256.35 | 0.85373 | 9779.72ms | 500299 | 30 | 3.15354e+08 | 379767 | 0.364923 | 3(Loss) | true |
| simdjson (ondemand) | 991.994 | 1.48715 | 5892.02ms | 500299 | 40 | 2.04648e+09 | 480973 | 0.116959 | 4(Loss) | true |
| simdjson (reflection) | 695.744 | 1.7091 | 9009.11ms | 500299 | 30 | 4.12112e+09 | 685773 | 0.215735 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2682.29 | 0.165579 | 5947.2ms | 500299 | 160 | 1.38795e+07 | 177878 | 0.907373 | 1(Win) | true |
| jsonifier (two-stage) | 1436.13 | 0.488698 | 10186.1ms | 500299 | 320 | 8.4353e+08 | 332227 | 1.44574 | 2(Loss) | true |
| glaze | 1256.48 | 0.559068 | 5063.9ms | 500299 | 160 | 7.21098e+08 | 379728 | 3.0277 | 3(Loss) | true |
| simdjson (reflection) | 1222.58 | 0.227086 | 5610.33ms | 500299 | 320 | 2.51326e+08 | 390260 | 0.463989 | 4(Loss) | true |
| simdjson (ondemand) | 1113.85 | 0.357195 | 5965.67ms | 500299 | 640 | 1.4983e+09 | 428356 | 4.00656 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8518.7 | 0.173835 | 5839.99ms | 500299 | 1280 | 1.21338e+07 | 56008.8 | 0.0771903 | 1(Win) | true |
| simdjson (reflection) | 7574.81 | 0.343258 | 6525.57ms | 500299 | 320 | 1.49591e+07 | 62988 | 0.151369 | 2(Loss) | true |
| glaze | 2225.38 | 0.309769 | 5881.55ms | 500299 | 30 | 1.32326e+07 | 214400 | 0.589539 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8287.4 | 0.224637 | 5812.33ms | 500299 | 640 | 1.07045e+07 | 57572 | 0.987918 | 1(Win) | true |
| simdjson (reflection) | 8031.71 | 0.665817 | 6532.6ms | 500299 | 40 | 6.25768e+06 | 59404.8 | 0.0646831 | 2(Loss) | true |
| glaze | 2158.94 | 1.25312 | 5401.22ms | 500299 | 40 | 3.06776e+08 | 220998 | 1.32496 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2459.54 | 0.467199 | 5630.99ms | 1151920 | 320 | 1.39344e+09 | 446650 | 1.4069 | 1(Win) | true |
| jsonifier (two-stage) | 2312.74 | 0.525984 | 6206.94ms | 1151920 | 320 | 1.9975e+09 | 475002 | 0.448837 | 2(Loss) | true |
| simdjson (ondemand) | 1930.75 | 1.09987 | 6705.61ms | 1151920 | 40 | 1.56652e+09 | 568979 | 1.44112 | 3(Loss) | true |
| glaze | 1776.34 | 0.363793 | 7682.58ms | 1151920 | 640 | 3.23952e+09 | 618437 | 0.41904 | 4(Loss) | true |
| simdjson (reflection) | 1594.73 | 0.0778239 | 9133.1ms | 1151920 | 160 | 4.59853e+07 | 688869 | 0.13708 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3017.91 | 0.778395 | 5129.63ms | 1151920 | 80 | 6.42279e+08 | 364013 | 0.121462 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 2450.72 | 0.41486 | 6343.49ms | 1151920 | 80 | 2.76664e+08 | 448259 | 0.109103 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 2442.69 | 0.0815965 | 6524.21ms | 1151920 | 160 | 2.15463e+07 | 449733 | 0.70826 | 2(Tie) | true |
| jsonifier (two-stage) | 2359.55 | 0.95395 | 5936.97ms | 1151920 | 30 | 5.91778e+08 | 465579 | 2.73018 | 4(Loss) | true |
| glaze | 1940.98 | 0.508708 | 8107.24ms | 1151920 | 80 | 6.63179e+08 | 565981 | 0.359177 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 18885.4 | 0.214276 | 7391.36ms | 1439562 | 2560 | 6.2115e+07 | 72694.9 | 1.73949 | 1(Win) | true |
| glaze | 4046.91 | 0.227027 | 5008.16ms | 1439584 | 40 | 2.3727e+07 | 339245 | 0.41994 | 2(Loss) | true |
| simdjson (reflection) | 317.031 | 0.95155 | 6796.98ms | 1439562 | 30 | 5.09379e+10 | 4.3304e+06 | 1.94063 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 18586.9 | 1.09905 | 7508.64ms | 1439562 | 80 | 5.27191e+07 | 73862.4 | 0.250648 | 1(Win) | true |
| glaze | 3767.39 | 0.21879 | 9370.94ms | 1439584 | 1280 | 8.13689e+08 | 364415 | 0.347235 | 2(Loss) | true |
| simdjson (reflection) | 319.604 | 1.0965 | 6777.01ms | 1439562 | 80 | 1.77477e+11 | 4.29554e+06 | 3.27007 | 3(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1695.53 | 0.504919 | 3403.87ms | 56369 | 160 | 4.10049e+06 | 31705.6 | 0.442122 | 1(Win) | true |
| glaze | 1345.8 | 0.190211 | 4226.43ms | 56369 | 4890 | 2.82294e+07 | 39944.7 | 0.525577 | 2(Loss) | true |
| jsonifier (two-stage) | 1177.95 | 0.326176 | 5282.07ms | 56369 | 160 | 3.54531e+06 | 45636.8 | 0.0525615 | 3(Loss) | true |
| simdjson (reflection) | 996.954 | 0.129319 | 5527.4ms | 56369 | 4890 | 2.37774e+07 | 53921.9 | 0.901405 | 4(Loss) | true |
| simdjson (ondemand) | 896.519 | 0.177179 | 6180.63ms | 56369 | 4890 | 5.51946e+07 | 59962.7 | 2.55262 | 5(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2308.86 | 0.524068 | 2994.03ms | 56369 | 160 | 2.38221e+06 | 23283.2 | 0.34478 | 1(Win) | true |
| glaze | 1806.99 | 0.0757192 | 3605.19ms | 56369 | 4890 | 2.48137e+06 | 29749.9 | 0.724233 | 2(Loss) | true |
| jsonifier (two-stage) | 1315.02 | 0.469778 | 4651.1ms | 56369 | 1280 | 4.72073e+07 | 40879.6 | 0.40378 | 3(Loss) | true |
| simdjson (reflection) | 1018.68 | 0.240574 | 5374.24ms | 56369 | 2560 | 4.12615e+07 | 52772 | 1.39098 | 4(Loss) | true |
| simdjson (ondemand) | 1006.79 | 0.38921 | 5710.44ms | 56369 | 1280 | 5.52813e+07 | 53395 | 0.15371 | 5(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12488.4 | 0.363708 | 450.411ms | 56369 | 1280 | 313749 | 4304.6 | 0.060437 | 1(Win) | true |
| simdjson (reflection) | 9720.39 | 0.689459 | 571.41ms | 56369 | 320 | 465243 | 5530.4 | 0.216513 | 2(Loss) | true |
| glaze | 2923.39 | 0.26757 | 1935.96ms | 56369 | 320 | 774699 | 18388.8 | 0.0869338 | 3(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14054.2 | 0.178812 | 386.604ms | 56369 | 4890 | 228756 | 3825.03 | 0.121124 | 1(Win) | true |
| simdjson (reflection) | 10002.5 | 0.717786 | 612.418ms | 56369 | 320 | 476212 | 5374.4 | 0.71964 | 2(Loss) | true |
| glaze | 3237.27 | 0.531642 | 1760.77ms | 56369 | 30 | 233820 | 16605.9 | 0.257599 | 3(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1830.47 | 0.195927 | 4654.35ms | 83958 | 1280 | 9.40149e+06 | 43742 | 1.01918 | 1(Win) | true |
| jsonifier (two-stage) | 1676.82 | 0.411756 | 5026.95ms | 83958 | 80 | 3.09259e+06 | 47750.4 | 0.0536409 | 2(Loss) | true |
| glaze | 1459.5 | 0.455633 | 4848.34ms | 83958 | 640 | 3.99878e+07 | 54860.4 | 0.0912236 | 3(Loss) | true |
| simdjson (reflection) | 1349.64 | 0.157288 | 5900.11ms | 83958 | 4890 | 4.25777e+07 | 59325.7 | 0.00568142 | 4(Loss) | true |
| simdjson (ondemand) | 1232.54 | 0.721764 | 6638.89ms | 83958 | 320 | 7.035e+07 | 64962.4 | 1.45028 | 5(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 2186.09 | 0.321552 | 4187.87ms | 83958 | 640 | 8.87707e+06 | 36626.4 | 0.249622 | 1(Tie) | true |
| glaze STATISTICAL TIE | 2140.41 | 1.0151 | 4551.01ms | 83958 | 40 | 5.7678e+06 | 37408 | 0.142369 | 1(Tie) | true |
| jsonifier (two-stage) | 1639.67 | 1.09931 | 5198.51ms | 83958 | 40 | 1.15268e+07 | 48832 | 0.429975 | 3(Loss) | true |
| simdjson (ondemand) | 1595.3 | 0.414325 | 5894.14ms | 83958 | 160 | 6.91899e+06 | 50190.4 | 0.232174 | 4(Loss) | true |
| simdjson (reflection) | 1574.82 | 0.132297 | 5889.48ms | 83958 | 4890 | 2.21246e+07 | 50843.1 | 0.280307 | 5(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13987.6 | 1.76636 | 701.085ms | 94370 | 30 | 387491 | 6434.13 | 0 | 1(Win) | true |
| glaze | 2410.65 | 0.285373 | 4088.91ms | 94370 | 320 | 3.63226e+06 | 37333.6 | 0.30549 | 2(Loss) | true |
| simdjson (reflection) | 361.776 | 0.229934 | 6645.09ms | 94370 | 320 | 1.047e+08 | 248768 | 0.438001 | 3(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14202.7 | 0.33171 | 640.269ms | 94370 | 2560 | 1.13105e+06 | 6336.7 | 1.64742 | 1(Win) | true |
| glaze | 2324.41 | 0.285529 | 3741.37ms | 94370 | 2560 | 3.12883e+07 | 38718.7 | 0.133349 | 2(Loss) | true |
| simdjson (reflection) | 343.931 | 0.289786 | 6776.56ms | 94370 | 1280 | 7.36023e+08 | 261675 | 2.06545 | 3(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1561.97 | 0.398533 | 3385.26ms | 53331 | 160 | 2.69439e+06 | 32561.6 | 0.132496 | 1(Win) | true |
| glaze | 1478.71 | 0.208933 | 3901.32ms | 53331 | 160 | 826287 | 34395.2 | 0.0605101 | 2(Loss) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1100.37 | 1.10625 | 4548.8ms | 53331 | 1280 | 3.34656e+08 | 46221 | 0.765206 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1080.91 | 0.331428 | 4616.68ms | 53331 | 2560 | 6.22586e+07 | 47053.4 | 0.921418 | 3(Tie) | true |
| simdjson (ondemand) | 876.547 | 0.251923 | 5798.9ms | 53331 | 4890 | 1.04485e+08 | 58023.6 | 0.245198 | 5(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2214.87 | 0.26806 | 3400.77ms | 53331 | 30 | 113671 | 22963.2 | 1.32013 | 1(Win) | true |
| glaze | 1745.35 | 0.349941 | 3690.03ms | 53331 | 1280 | 1.33105e+07 | 29140.6 | 1.1003 | 2(Loss) | true |
| jsonifier (two-stage) | 1572.25 | 0.274014 | 3826.23ms | 53331 | 4890 | 3.8421e+07 | 32348.7 | 2.06381 | 3(Loss) | true |
| simdjson (reflection) | 1418.76 | 0.20738 | 4355.18ms | 53331 | 2560 | 1.41487e+07 | 35848.6 | 1.70656 | 4(Loss) | true |
| simdjson (ondemand) | 1074.68 | 0.370426 | 5528.2ms | 53331 | 1280 | 3.93384e+07 | 47326.2 | 0.660632 | 5(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16437.3 | 0.457354 | 344.412ms | 58581 | 1280 | 309290 | 3398.8 | 0.398546 | 1(Win) | true |
| simdjson (reflection) | 11759.5 | 0.168389 | 479.493ms | 58581 | 4890 | 312950 | 4750.82 | 0.0677298 | 2(Loss) | true |
| glaze | 3957.72 | 0.0957398 | 1430.64ms | 58581 | 2560 | 467571 | 14116 | 0.0538106 | 3(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14681 | 0.588858 | 374.082ms | 58581 | 1280 | 642735 | 3805.4 | 1.81133 | 1(Win) | true |
| simdjson (reflection) | 12498 | 0.256332 | 455.754ms | 58581 | 2560 | 336110 | 4470.1 | 0.34555 | 2(Loss) | true |
| glaze | 4864.57 | 0.128192 | 1150.47ms | 58581 | 2560 | 554860 | 11484.5 | 0.0217732 | 3(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| glaze STATISTICAL TIE | 1627.1 | 0.141148 | 3970.39ms | 65103 | 1280 | 3.71307e+06 | 38158 | 0.741343 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1626.34 | 0.171785 | 4154.56ms | 65103 | 40 | 172032 | 38176 | 0.0391324 | 1(Tie) | true |
| jsonifier | 1427.08 | 0.723916 | 3824.39ms | 65103 | 640 | 6.34838e+07 | 43506.4 | 0.0955268 | 3(Loss) | true |
| simdjson (reflection) | 1300.05 | 0.421255 | 5191.12ms | 65103 | 640 | 2.59033e+07 | 47757.6 | 0.223964 | 4(Loss) | true |
| simdjson (ondemand) | 937.837 | 0.400379 | 6229.43ms | 65103 | 640 | 4.49646e+07 | 66202.4 | 0.14239 | 5(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2241.43 | 0.0880297 | 3566.96ms | 65103 | 2560 | 1.52212e+06 | 27699.7 | 0.0357532 | 1(Win) | true |
| glaze | 1990.45 | 0.13258 | 3798.44ms | 65103 | 4890 | 8.36308e+06 | 31192.5 | 0.343365 | 2(Loss) | true |
| jsonifier (two-stage) | 1942.63 | 0.204374 | 4024.2ms | 65103 | 2560 | 1.09223e+07 | 31960.3 | 1.49088 | 3(Loss) | true |
| simdjson (reflection) | 1469.15 | 0.280723 | 4884.39ms | 65103 | 4890 | 6.88235e+07 | 42260.6 | 2.22412 | 4(Loss) | true |
| simdjson (ondemand) | 1223.34 | 0.357642 | 5728.3ms | 65103 | 1280 | 4.21713e+07 | 50752.2 | 1.43213 | 5(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14942.6 | 0.331082 | 522.806ms | 78778 | 4890 | 1.35499e+06 | 5027.81 | 1.44064 | 1(Win) | true |
| glaze | 3125.36 | 1.65966 | 2534.4ms | 78778 | 80 | 1.27332e+07 | 24038.4 | 1.76104 | 2(Loss) | true |
| simdjson (reflection) | 420.521 | 0.501231 | 9741.46ms | 78778 | 160 | 1.28301e+08 | 178656 | 0.121947 | 3(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 15990.9 | 0.309737 | 485.863ms | 78778 | 4890 | 1.03552e+06 | 4698.2 | 2.37742 | 1(Win) | true |
| glaze | 3624.92 | 0.59269 | 2152.74ms | 78778 | 640 | 9.65717e+06 | 20725.6 | 1.83024 | 2(Loss) | true |
| simdjson (reflection) | 408.753 | 1.37525 | 9480.35ms | 78778 | 30 | 1.91679e+08 | 183799 | 0.595348 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1696.61 | 0.608629 | 670.706ms | 11812 | 640 | 1.04513e+06 | 6639.6 | 0.29433 | 1(Win) | true |
| jsonifier (two-stage) | 1090.37 | 1.119 | 1011.88ms | 11812 | 320 | 4.27677e+06 | 10331.2 | 3.22242 | 2(Loss) | true |
| glaze | 984.066 | 0.337645 | 1210.31ms | 11812 | 640 | 956092 | 11447.2 | 1.84342 | 3(Loss) | true |
| simdjson (reflection) | 776.583 | 1.52513 | 1306.87ms | 11812 | 320 | 1.56616e+07 | 14505.6 | 0.296932 | 4(Loss) | true |
| simdjson (ondemand) | 683.631 | 0.38275 | 1649.7ms | 11812 | 2560 | 1.0183e+07 | 16477.9 | 0.275672 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2202.91 | 0.958163 | 640.895ms | 11812 | 160 | 384107 | 5113.6 | 0.188088 | 1(Win) | true |
| jsonifier (two-stage) | 1233.71 | 0.267477 | 1016.65ms | 11812 | 4890 | 2.91677e+06 | 9130.82 | 1.06271 | 2(Loss) | true |
| glaze | 1016.7 | 0.234013 | 1202.09ms | 11812 | 4890 | 3.28737e+06 | 11079.7 | 0.144815 | 3(Loss) | true |
| simdjson (reflection) | 917.426 | 0.358736 | 1316.24ms | 11812 | 2560 | 4.967e+06 | 12278.7 | 1.83877 | 4(Loss) | true |
| simdjson (ondemand) | 652.019 | 0.482182 | 1752.1ms | 11812 | 1280 | 8.88296e+06 | 17276.8 | 0.451184 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11159.9 | 1.79216 | 113.783ms | 11812 | 1280 | 418879 | 1009.4 | 0.618022 | 1(Win) | true |
| simdjson (reflection) | 7722.9 | 0.607814 | 143.593ms | 11812 | 4890 | 384359 | 1458.62 | 2.25195 | 2(Loss) | true |
| glaze DID NOT CONVERGE | 1558.68 | 0.372748 | 766.679ms | 11812 | 4890 | 3.54874e+06 | 7227.16 | 6.63552 | -(Loss) | false |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10746.8 | 0.708967 | 108.825ms | 11812 | 1280 | 70688.8 | 1048.2 | 1.59594 | 1(Win) | true |
| simdjson (reflection) | 9318.99 | 1.91912 | 136.954ms | 11812 | 320 | 172211 | 1208.8 | 0.867824 | 2(Loss) | true |
| glaze | 1660.54 | 0.431192 | 660.691ms | 11812 | 2560 | 2.19042e+06 | 6783.8 | 0.456094 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2612.64 | 0.882548 | 1040.04ms | 25388 | 30 | 200676 | 9267.2 | 0 | 1(Win) | true |
| jsonifier (two-stage) | 1990.59 | 1.05334 | 1212.53ms | 25388 | 160 | 2.62638e+06 | 12163.2 | 1.29836 | 2(Loss) | true |
| simdjson (reflection) | 1599.12 | 0.745693 | 1461.2ms | 25388 | 320 | 4.07913e+06 | 15140.8 | 0.221426 | 3(Loss) | true |
| glaze | 1390.65 | 0.392509 | 1694.61ms | 25388 | 2560 | 1.19553e+07 | 17410.5 | 4.6 | 4(Loss) | true |
| simdjson (ondemand) | 1367.27 | 0.199224 | 1853.63ms | 25388 | 4890 | 6.08606e+06 | 17708.1 | 0.928644 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2743.71 | 0.242966 | 983.346ms | 25388 | 2560 | 1.17683e+06 | 8824.5 | 1.38461 | 1(Win) | true |
| jsonifier (two-stage) | 2297.32 | 0.330573 | 1179.6ms | 25388 | 2560 | 3.10734e+06 | 10539.2 | 0.276295 | 2(Loss) | true |
| simdjson (reflection) | 1791.32 | 0.253392 | 1430.82ms | 25388 | 2560 | 3.00285e+06 | 13516.2 | 1.16613 | 3(Loss) | true |
| glaze | 1637.2 | 0.172729 | 1588.79ms | 25388 | 4890 | 3.19076e+06 | 14788.6 | 0.361933 | 4(Loss) | true |
| simdjson (ondemand) | 1351.65 | 0.693381 | 1836.03ms | 25388 | 320 | 4.93651e+06 | 17912.8 | 1.40851 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 17634.4 | 0.688461 | 160.416ms | 31235 | 2560 | 346227 | 1689.2 | 0.177284 | 1(Win) | true |
| glaze | 2775.83 | 0.728733 | 1215.05ms | 31235 | 160 | 978483 | 10731.2 | 3.63506 | 2(Loss) | true |
| simdjson (reflection) | 351.168 | 0.0840858 | 9481.89ms | 31235 | 40 | 203498 | 84825.6 | 0.365841 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 23646.9 | 0.819351 | 135.686ms | 31235 | 2560 | 272718 | 1259.7 | 0.872838 | 1(Win) | true |
| glaze | 2946.65 | 0.318442 | 1095.53ms | 31235 | 2560 | 2.65293e+06 | 10109.1 | 0.000989218 | 2(Loss) | true |
| simdjson (reflection) | 351.885 | 0.0908446 | 9154.68ms | 31235 | 40 | 236560 | 84652.8 | 0.0881257 | 3(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2476.08 | 0.523956 | 4163.67ms | 108313 | 640 | 3.05773e+07 | 41717.2 | 1.36162 | 1(Win) | true |
| jsonifier (two-stage) | 1695.46 | 0.269561 | 6892.92ms | 108313 | 80 | 2.1577e+06 | 60924.8 | 0.204424 | 2(Loss) | true |
| glaze | 1418.59 | 0.118963 | 7538.02ms | 108313 | 4890 | 3.66925e+07 | 72815.4 | 0.522006 | 3(Loss) | true |
| simdjson (reflection) | 1207.88 | 0.282078 | 8631.77ms | 108313 | 640 | 3.72417e+07 | 85517.6 | 0.140125 | 4(Loss) | true |
| simdjson (ondemand) | 1195.74 | 0.12548 | 9019.87ms | 108313 | 2560 | 3.00804e+07 | 86386.4 | 0.600404 | 5(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2917.29 | 1.22406 | 3856.54ms | 108313 | 80 | 1.50278e+07 | 35408 | 3.53095 | 1(Win) | true |
| jsonifier (two-stage) | 1710.64 | 0.739341 | 6285.62ms | 108313 | 80 | 1.5945e+07 | 60384 | 0.274812 | 2(Loss) | true |
| glaze | 1555.91 | 0.118427 | 6905.2ms | 108313 | 4890 | 3.02275e+07 | 66388.8 | 0.267236 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1277.98 | 0.211238 | 8803.68ms | 108313 | 640 | 1.86569e+07 | 80827.2 | 0.252034 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1272.45 | 0.132779 | 8422.07ms | 108313 | 2560 | 2.97427e+07 | 81178.3 | 0.130038 | 4(Tie) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14531.9 | 0.193976 | 737.937ms | 108313 | 1280 | 243347 | 7108.2 | 0.0140663 | 1(Win) | true |
| simdjson (reflection) | 7937.73 | 0.356642 | 1337.11ms | 108313 | 640 | 1.37852e+06 | 13013.2 | 0.826119 | 2(Loss) | true |
| glaze | 1932.57 | 0.409678 | 5466.09ms | 108313 | 160 | 7.67174e+06 | 53449.6 | 1.11302 | 3(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14417.1 | 0.445505 | 703.337ms | 108313 | 640 | 652068 | 7164.8 | 0 | 1(Win) | true |
| simdjson (reflection) | 8313.11 | 0.326721 | 1313.32ms | 108313 | 160 | 263700 | 12425.6 | 2.0681 | 2(Loss) | true |
| glaze | 2080.25 | 0.12401 | 5061.26ms | 108313 | 4890 | 1.85421e+07 | 49655.4 | 1.01197 | 3(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2474.91 | 1.9499 | 7314.86ms | 183677 | 40 | 7.61864e+07 | 70777.6 | 0.160005 | 1(Win) | true |
| jsonifier (two-stage) | 2082.77 | 0.729347 | 8156.09ms | 183677 | 320 | 1.20405e+08 | 84103.2 | 0.715641 | 2(Loss) | true |
| glaze | 1935.64 | 0.686624 | 9459.51ms | 183677 | 30 | 1.15829e+07 | 90496 | 0.141643 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1694.42 | 0.668147 | 5740.1ms | 183677 | 320 | 1.52672e+08 | 103379 | 2.99195 | 4(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1674.17 | 0.302549 | 5473.7ms | 183677 | 1280 | 1.28267e+08 | 104630 | 0.803207 | 4(Tie) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2739.46 | 0.339401 | 6546.26ms | 183677 | 1280 | 6.0286e+07 | 63942.6 | 0.987725 | 1(Win) | true |
| jsonifier (two-stage) | 2296.51 | 0.379474 | 8149.97ms | 183677 | 2560 | 2.14475e+08 | 76275.7 | 1.99604 | 2(Loss) | true |
| glaze | 1858.49 | 0.603329 | 9274.23ms | 183677 | 320 | 1.03478e+08 | 94252.8 | 1.31176 | 3(Loss) | true |
| simdjson (reflection) | 1769.3 | 0.38795 | 5117.15ms | 183677 | 640 | 9.4414e+07 | 99004 | 1.61427 | 4(Loss) | true |
| simdjson (ondemand) | 1725.36 | 0.324365 | 5343.57ms | 183677 | 1280 | 1.38812e+08 | 101526 | 0.486171 | 5(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16520.2 | 0.496193 | 1307.71ms | 213963 | 640 | 2.40396e+06 | 12351.6 | 0.269516 | 1(Win) | true |
| glaze | 2032.21 | 0.231279 | 5056.19ms | 213963 | 2560 | 1.38056e+08 | 100409 | 0.781492 | 2(Loss) | true |
| simdjson (reflection) | 332.563 | 0.178849 | 7798.03ms | 213963 | 640 | 7.70695e+08 | 613571 | 0.270855 | 3(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 17072.8 | 0.33788 | 1211.47ms | 213963 | 1280 | 2.08738e+06 | 11951.8 | 0.0752458 | 1(Win) | true |
| glaze | 2211.49 | 0.134946 | 8730.76ms | 213963 | 4890 | 7.58111e+07 | 92268.5 | 1.03262 | 2(Loss) | true |
| simdjson (reflection) | 286.756 | 0.635637 | 8712.44ms | 213963 | 80 | 1.63667e+09 | 711584 | 0.670919 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 612.186 | 1.11584 | 9096.39ms | 1834197 | 30 | 3.04963e+10 | 2.85734e+06 | 0.356502 | 1(Win) | true |
| jsonifier (two-stage) | 527.532 | 0.707802 | 10391.5ms | 1834197 | 30 | 1.65249e+10 | 3.31587e+06 | 1.1262 | 2(Loss) | true |
| glaze | 479.53 | 0.42785 | 5590.15ms | 1834197 | 30 | 7.30743e+09 | 3.6478e+06 | 4.84505 | 3(Loss) | true |
| simdjson (reflection) | 457.505 | 0.800327 | 5677.2ms | 1834197 | 40 | 3.74538e+10 | 3.8234e+06 | 0.425086 | 4(Loss) | true |
| simdjson (ondemand) | 432.574 | 0.673288 | 6046.84ms | 1834197 | 80 | 5.9301e+10 | 4.04376e+06 | 1.16729 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 711.518 | 0.298372 | 8617.75ms | 1834197 | 160 | 8.60906e+09 | 2.45844e+06 | 2.13289 | 1(Win) | true |
| jsonifier (two-stage) | 580.827 | 0.887215 | 5257.83ms | 1834197 | 40 | 2.85573e+10 | 3.01162e+06 | 0.445202 | 2(Loss) | true |
| glaze | 531.147 | 1.12908 | 5661.81ms | 1834197 | 40 | 5.53057e+10 | 3.2933e+06 | 1.04701 | 3(Loss) | true |
| simdjson (reflection) | 516.531 | 0.495212 | 5697.08ms | 1834197 | 30 | 8.43728e+09 | 3.38649e+06 | 1.36965 | 4(Loss) | true |
| simdjson (ondemand) | 475.951 | 0.470904 | 6225.29ms | 1834197 | 40 | 1.1981e+10 | 3.67523e+06 | 0.612102 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1255.26 | 0.325148 | 9224.75ms | 1834197 | 320 | 6.56955e+09 | 1.39352e+06 | 1.21509 | 1(Win) | true |
| glaze | 840.993 | 0.910234 | 6556.32ms | 1833577 | 80 | 2.86556e+10 | 2.07925e+06 | 1.46192 | 2(Loss) | true |
| simdjson (reflection) | 726.822 | 0.422951 | 7895.16ms | 1922245 | 40 | 4.552e+09 | 2.52221e+06 | 0.155979 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1195.35 | 1.03875 | 8879.95ms | 1834197 | 30 | 6.93186e+09 | 1.46336e+06 | 0.471046 | 1(Win) | true |
| glaze | 806.141 | 0.580842 | 6678.86ms | 1833577 | 160 | 2.53987e+10 | 2.16914e+06 | 1.13518 | 2(Loss) | true |
| simdjson (reflection) | 724.405 | 0.473049 | 7935.34ms | 1922245 | 40 | 5.73229e+09 | 2.53062e+06 | 0.98743 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 1866.46 | 0.299189 | 5761.08ms | 7351818 | 40 | 5.05248e+09 | 3.75644e+06 | 0.405655 | 1(Win) | true |
| jsonifier STATISTICAL TIE | 1694.07 | 0.769344 | 6116.09ms | 7351818 | 40 | 4.05534e+10 | 4.13869e+06 | 0.637911 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1690.13 | 0.475995 | 6456.53ms | 7351818 | 40 | 1.55961e+10 | 4.14835e+06 | 0.411559 | 2(Tie) | true |
| simdjson (ondemand) | 1492.35 | 1.01823 | 7120.38ms | 7351818 | 80 | 1.83076e+11 | 4.69812e+06 | 0.252995 | 4(Loss) | true |
| glaze | 1424.74 | 0.456406 | 7476.84ms | 7351818 | 80 | 4.03562e+10 | 4.92107e+06 | 3.95877 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2042.07 | 0.496347 | 5748.28ms | 7351818 | 80 | 2.32332e+10 | 3.4334e+06 | 0.620923 | 1(Win) | true |
| jsonifier (two-stage) | 2002.04 | 0.788461 | 5950.37ms | 7351818 | 40 | 3.04974e+10 | 3.50204e+06 | 3.8222 | 2(Loss) | true |
| simdjson (ondemand) | 1698.59 | 0.687979 | 6788.79ms | 7351818 | 30 | 2.41927e+10 | 4.12768e+06 | 1.07804 | 3(Loss) | true |
| simdjson (reflection) | 1632.31 | 0.567033 | 6915.12ms | 7351818 | 80 | 4.74559e+10 | 4.29529e+06 | 1.36162 | 4(Loss) | true |
| glaze | 1539.73 | 0.934966 | 7638.67ms | 7351818 | 30 | 5.43768e+10 | 4.55355e+06 | 0.068167 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6676.78 | 0.357174 | 9341.97ms | 9930848 | 80 | 2.05347e+09 | 1.41847e+06 | 0.849301 | 1(Win) | true |
| glaze | 2664.38 | 0.890346 | 5039.84ms | 9930228 | 30 | 3.00445e+10 | 3.55437e+06 | 1.64078 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 290.543 | 0.746258 | 10179ms | 10018896 | 30 | 1.80684e+12 | 3.28859e+07 | 7.47073 | -(Loss) | false |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6393.72 | 0.263447 | 9337.5ms | 9930848 | 320 | 4.87307e+09 | 1.48126e+06 | 0.36605 | 1(Win) | true |
| glaze | 2952.67 | 0.546331 | 9765.4ms | 9930228 | 80 | 2.45635e+10 | 3.20733e+06 | 1.01895 | 2(Loss) | true |
| simdjson (reflection) | 292.396 | 0.406965 | 10109.8ms | 10018896 | 30 | 5.30556e+11 | 3.26774e+07 | 4.78186 | 3(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 685.838 | 0.438924 | 8050.14ms | 1834197 | 40 | 5.01288e+09 | 2.5505e+06 | 2.70725 | 1(Win) | true |
| jsonifier (two-stage) | 575.342 | 0.160582 | 9591.25ms | 1834197 | 40 | 9.53438e+08 | 3.04033e+06 | 0.444216 | 2(Loss) | true |
| glaze | 496.07 | 0.302471 | 5450.15ms | 1834197 | 30 | 3.41268e+09 | 3.52617e+06 | 0.346549 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 485.654 | 0.466483 | 5465.72ms | 1834197 | 40 | 1.1292e+10 | 3.6018e+06 | 0.191025 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 484.802 | 0.303598 | 5420.35ms | 1834197 | 80 | 9.59955e+09 | 3.60813e+06 | 0.351373 | 4(Tie) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 791.823 | 0.575077 | 8077.56ms | 1834197 | 40 | 6.45577e+09 | 2.20911e+06 | 0.281033 | 1(Win) | true |
| jsonifier (two-stage) | 647.862 | 0.246818 | 9383.95ms | 1834197 | 30 | 1.3323e+09 | 2.7e+06 | 0.238679 | 2(Loss) | true |
| glaze | 548.616 | 0.278736 | 5203.44ms | 1834197 | 30 | 2.36954e+09 | 3.18844e+06 | 1.27878 | 3(Loss) | true |
| simdjson (reflection) | 516.083 | 0.78869 | 5669.83ms | 1834197 | 30 | 2.14382e+10 | 3.38943e+06 | 1.36285 | 4(Loss) | true |
| simdjson (ondemand) | 491.038 | 0.590276 | 5833.41ms | 1834197 | 80 | 3.53722e+10 | 3.56231e+06 | 0.616094 | 5(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1456.55 | 0.173395 | 8304.54ms | 1834197 | 30 | 1.30087e+08 | 1.20094e+06 | 0.552584 | 1(Win) | true |
| glaze | 845.022 | 0.431266 | 6626.14ms | 1833577 | 160 | 1.2743e+10 | 2.06934e+06 | 1.49051 | 2(Loss) | true |
| simdjson (reflection) | 633.163 | 0.924997 | 8875.25ms | 1922245 | 30 | 2.15174e+10 | 2.8953e+06 | 0.382565 | 3(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1286.99 | 0.26709 | 8565.71ms | 1834197 | 160 | 2.10853e+09 | 1.35916e+06 | 0.17181 | 1(Win) | true |
| glaze | 829.061 | 0.335516 | 6061.59ms | 1833577 | 30 | 1.50236e+09 | 2.10918e+06 | 1.48594 | 2(Loss) | true |
| simdjson (reflection) | 444.005 | 0.907418 | 5992.8ms | 1922245 | 80 | 1.12291e+11 | 4.12877e+06 | 0.264447 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2070.67 | 0.515958 | 5382.14ms | 7351818 | 40 | 1.22084e+10 | 3.38598e+06 | 0.875841 | 1(Win) | true |
| jsonifier (two-stage) | 2029.75 | 0.744542 | 5277.14ms | 7351818 | 40 | 2.64571e+10 | 3.45423e+06 | 4.16197 | 2(Loss) | true |
| simdjson (reflection) | 1541.02 | 1.22479 | 7015.8ms | 7351818 | 30 | 9.31571e+10 | 4.54973e+06 | 3.88296 | 3(Loss) | true |
| simdjson (ondemand) | 1371.94 | 1.14028 | 7301.88ms | 7351818 | 30 | 1.01875e+11 | 5.11047e+06 | 0.566068 | 4(Loss) | true |
| glaze | 1317.54 | 0.820476 | 7657.27ms | 7351818 | 80 | 1.52505e+11 | 5.32145e+06 | 1.61079 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2339.79 | 0.227654 | 5152.02ms | 7351818 | 80 | 3.72287e+09 | 2.99653e+06 | 0.103052 | 1(Win) | true |
| jsonifier (two-stage) | 2049.15 | 0.415146 | 5788.44ms | 7351818 | 40 | 8.07054e+09 | 3.42153e+06 | 0.821107 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1747.28 | 1.23808 | 7431.84ms | 7351818 | 30 | 7.40427e+10 | 4.01265e+06 | 1.53063 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1710.25 | 1.37436 | 6659.17ms | 7351818 | 30 | 9.52342e+10 | 4.09955e+06 | 0.00874166 | 3(Tie) | true |
| glaze | 1557.98 | 0.826384 | 7402.08ms | 7351818 | 30 | 4.14905e+10 | 4.5002e+06 | 1.50571 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6124.54 | 1.01842 | 9386.21ms | 9930848 | 40 | 9.9207e+09 | 1.54637e+06 | 2.70805 | 1(Win) | true |
| glaze | 2592.84 | 1.0621 | 5255.46ms | 9930228 | 30 | 4.51464e+10 | 3.65245e+06 | 2.42824 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 258.249 | 0.877377 | 10810.2ms | 10018896 | 30 | 3.16123e+12 | 3.69983e+07 | 5.50887 | -(Loss) | false |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6352.1 | 0.566885 | 9469.61ms | 9930848 | 160 | 1.143e+10 | 1.49097e+06 | 1.26134 | 1(Win) | true |
| glaze | 2874.55 | 1.05965 | 9868.98ms | 9930228 | 40 | 4.87485e+10 | 3.2945e+06 | 0.713598 | 2(Loss) | true |
| simdjson (reflection) | 269.061 | 0.786275 | 10629.1ms | 10018896 | 30 | 2.33888e+12 | 3.55115e+07 | 1.28074 | 3(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 844.536 | 0.884933 | 6680.86ms | 461466 | 80 | 1.7012e+09 | 521101 | 1.23124 | 1(Win) | true |
| jsonifier (two-stage) | 821.781 | 0.349886 | 6811.83ms | 461466 | 640 | 2.24698e+09 | 535530 | 0.548577 | 2(Loss) | true |
| glaze | 713.513 | 0.580059 | 7978.78ms | 461466 | 160 | 2.04804e+09 | 616790 | 2.85027 | 3(Loss) | true |
| simdjson (reflection) | 695.706 | 0.331287 | 8399.99ms | 461466 | 320 | 1.40535e+09 | 632578 | 1.10783 | 4(Loss) | true |
| simdjson (ondemand) | 575.269 | 1.29041 | 8866.11ms | 461466 | 30 | 2.92357e+09 | 765013 | 0.196705 | 5(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 1155.36 | 1.04367 | 5976.69ms | 461466 | 40 | 6.32165e+08 | 380909 | 4.33281 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1147.69 | 0.436202 | 6215.29ms | 461466 | 320 | 8.95272e+08 | 383455 | 0.515243 | 1(Tie) | true |
| glaze | 892.328 | 0.341135 | 7751.58ms | 461466 | 640 | 1.8116e+09 | 493191 | 0.41209 | 3(Loss) | true |
| simdjson (reflection) | 804.163 | 0.265925 | 8201.84ms | 461466 | 640 | 1.35547e+09 | 547263 | 2.78656 | 4(Loss) | true |
| simdjson (ondemand) | 788.485 | 0.298929 | 8538.17ms | 461466 | 640 | 1.7816e+09 | 558144 | 0.424336 | 5(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10898.9 | 0.834151 | 3995.3ms | 461466 | 160 | 1.8152e+07 | 40379.2 | 1.08568 | 1(Win) | true |
| simdjson (reflection) | 7786.42 | 0.379201 | 5678.41ms | 461466 | 640 | 2.93984e+07 | 56520 | 0.808693 | 2(Loss) | true |
| glaze | 2051.1 | 0.473279 | 5477.19ms | 461466 | 320 | 3.29982e+08 | 214562 | 1.08685 | 3(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10912 | 0.325724 | 3960.46ms | 461466 | 1280 | 2.20894e+07 | 40330.8 | 2.30012 | 1(Win) | true |
| simdjson (reflection) | 8055.17 | 0.193383 | 5630.73ms | 461466 | 4890 | 5.45854e+07 | 54634.3 | 2.75796 | 2(Loss) | true |
| glaze | 2131.21 | 0.421304 | 5093.45ms | 461466 | 320 | 2.42196e+08 | 206497 | 0.871859 | 3(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1184.87 | 0.268579 | 7800.57ms | 728486 | 160 | 3.96794e+08 | 586341 | 0.0494155 | 1(Win) | true |
| jsonifier (two-stage) | 1155.31 | 0.528281 | 8298.3ms | 728486 | 40 | 4.03678e+08 | 601344 | 1.62905 | 2(Loss) | true |
| simdjson (reflection) | 1053.17 | 0.223994 | 8547.27ms | 728486 | 640 | 1.39734e+09 | 659666 | 3.93098 | 3(Loss) | true |
| simdjson (ondemand) | 980.613 | 0.536256 | 8863.3ms | 728486 | 80 | 1.15473e+09 | 708474 | 0.177371 | 4(Loss) | true |
| glaze | 943.397 | 0.418158 | 8639.48ms | 728486 | 80 | 7.5862e+08 | 736422 | 1.57214 | 5(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 1622.13 | 0.269789 | 7766.21ms | 728486 | 640 | 8.54474e+08 | 428288 | 0.228389 | 1(Win) | true |
| jsonifier STATISTICAL TIE | 1411.44 | 0.553013 | 7522.27ms | 728486 | 160 | 1.18552e+09 | 492219 | 2.32737 | 2(Tie) | true |
| glaze STATISTICAL TIE | 1396.64 | 0.352777 | 8249.7ms | 728486 | 160 | 4.92715e+08 | 497437 | 4.87703 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1255.04 | 0.893978 | 8860.62ms | 728486 | 30 | 7.34683e+08 | 553557 | 0.606748 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1225.46 | 1.36656 | 8691.59ms | 728486 | 30 | 1.80063e+09 | 566921 | 1.10747 | 4(Tie) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14381.8 | 0.382352 | 5577.13ms | 837491 | 640 | 2.88565e+07 | 55535.2 | 0.319373 | 1(Win) | true |
| glaze | 2259.99 | 0.29012 | 8650.62ms | 837491 | 640 | 6.72795e+08 | 353406 | 0.395667 | 2(Loss) | true |
| simdjson (reflection) | 358.222 | 0.332293 | 7641.41ms | 837491 | 160 | 8.78249e+09 | 2.22961e+06 | 0.401027 | 3(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14525 | 0.259883 | 5657.5ms | 837491 | 1280 | 2.61394e+07 | 54987.6 | 1.00957 | 1(Win) | true |
| glaze | 2541.56 | 2.09592 | 7789.17ms | 837491 | 40 | 1.73527e+09 | 314253 | 1.24031 | 2(Loss) | true |
| simdjson (reflection) | 321.918 | 0.621281 | 7752.18ms | 837491 | 40 | 9.50401e+09 | 2.48105e+06 | 1.0196 | 3(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) DID NOT CONVERGE | 4717.36 | 0.209914 | 9625.02ms | 466906 | 4890 | 1.91978e+08 | 94391 | 8.03981 | -(Win) | false |
| jsonifier | 4285.43 | 0.889832 | 5356.25ms | 466906 | 320 | 2.73551e+08 | 103905 | 0.55815 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 3966.85 | 0.299387 | 5773.28ms | 466906 | 1280 | 1.44558e+08 | 112249 | 0.454763 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 3942.12 | 0.494852 | 5793.09ms | 466906 | 40 | 1.24972e+07 | 112954 | 1.86277 | 3(Tie) | true |
| glaze | 2559.25 | 0.123776 | 9562.28ms | 466906 | 160 | 7.4204e+06 | 173987 | 0.00183918 | 5(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 4890.31 | 0.873148 | 9430.93ms | 466906 | 80 | 5.05652e+07 | 91052.8 | 0.822586 | 1(Win) | true |
| jsonifier | 4516.08 | 0.477583 | 5068.25ms | 466906 | 1280 | 2.8382e+08 | 98598 | 2.24996 | 2(Loss) | true |
| simdjson (ondemand) | 3855.34 | 0.549061 | 6067.02ms | 466906 | 640 | 2.57368e+08 | 115496 | 0.268034 | 3(Loss) | true |
| simdjson (reflection) | 3743.99 | 0.206182 | 6099.46ms | 466906 | 1280 | 7.69664e+07 | 118931 | 0.898775 | 4(Loss) | true |
| glaze | 2266.9 | 0.449279 | 5164.87ms | 466906 | 320 | 2.49217e+08 | 196426 | 0.0856018 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5659.59 | 0.0687402 | 5723.45ms | 631514 | 1280 | 6.849e+06 | 106414 | 0.126703 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 4628.66 | 0.723749 | 6363.27ms | 631514 | 320 | 2.8378e+08 | 130115 | 0.88702 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 4552.19 | 0.865918 | 7540.65ms | 631514 | 30 | 3.93731e+07 | 132301 | 0.304069 | 2(Tie) | true |
| simdjson (reflection) | 4298.8 | 0.70687 | 7420.72ms | 631514 | 80 | 7.84586e+07 | 140099 | 0.551972 | 4(Loss) | true |
| glaze | 2534.01 | 1.09083 | 5409.49ms | 631514 | 40 | 2.68858e+08 | 237670 | 0.197863 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5716.6 | 0.383718 | 6404.04ms | 631514 | 30 | 4.9027e+06 | 105353 | 0.0243053 | 1(Win) | true |
| jsonifier (two-stage) | 4859.59 | 0.405622 | 6365.33ms | 631514 | 640 | 1.6173e+08 | 123932 | 3.9662 | 2(Loss) | true |
| simdjson (ondemand) | 4761.63 | 0.2266 | 6928.8ms | 631514 | 1280 | 1.05144e+08 | 126482 | 0.0148616 | 3(Loss) | true |
| simdjson (reflection) | 3706.02 | 0.423974 | 8285.74ms | 631514 | 640 | 3.03814e+08 | 162508 | 1.54754 | 4(Loss) | true |
| glaze | 2614.94 | 1.66009 | 5331.01ms | 631514 | 30 | 4.38559e+08 | 230315 | 0.538031 | 5(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1898.59 | 0.214816 | 6121.5ms | 466906 | 1280 | 3.24892e+08 | 234530 | 0.224201 | 1(Win) | true |
| jsonifier (two-stage) | 1625.91 | 0.465797 | 8345.86ms | 466906 | 80 | 1.30181e+08 | 273862 | 0.130698 | 2(Loss) | true |
| glaze | 1228.63 | 0.784074 | 8293.37ms | 466906 | 80 | 6.4598e+08 | 362416 | 0.0185457 | 3(Loss) | true |
| simdjson (reflection) | 1191.66 | 0.348478 | 9478.04ms | 466906 | 1280 | 2.17027e+09 | 373660 | 1.77373 | 4(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 887.412 | 0.686114 | 6105.79ms | 466906 | 320 | 3.79272e+09 | 501770 | 6.91162 | -(Loss) | false |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2645.42 | 0.462337 | 5460.27ms | 466906 | 160 | 9.68968e+07 | 168320 | 0.180283 | 1(Win) | true |
| jsonifier (two-stage) | 1660.69 | 0.713785 | 7412.5ms | 466906 | 80 | 2.93028e+08 | 268128 | 0.423074 | 2(Loss) | true |
| simdjson (reflection) | 1285.2 | 0.28792 | 9416.35ms | 466906 | 1280 | 1.27371e+09 | 346465 | 0.351007 | 3(Loss) | true |
| glaze | 1152.44 | 0.658873 | 5646.36ms | 466906 | 320 | 2.07385e+09 | 386378 | 2.61483 | 4(Loss) | true |
| simdjson (ondemand) | 1075.47 | 0.538373 | 5518.48ms | 466906 | 160 | 7.94969e+08 | 414030 | 2.12765 | 5(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14166.3 | 0.18614 | 3269.81ms | 475954 | 4890 | 1.73941e+07 | 32041.1 | 2.11647 | 1(Win) | true |
| simdjson (reflection) | 11290.8 | 0.146112 | 4207.3ms | 475954 | 4890 | 1.6872e+07 | 40201.5 | 0.422629 | 2(Loss) | true |
| glaze | 3636.19 | 0.369616 | 6504.75ms | 475954 | 1280 | 2.72489e+08 | 124830 | 0.584669 | 3(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 15949.6 | 0.361067 | 3186.01ms | 475954 | 30 | 316757 | 28458.7 | 0.388292 | 1(Win) | true |
| simdjson (reflection) | 9645.19 | 0.246556 | 4280.28ms | 475954 | 4890 | 6.58337e+07 | 47060.2 | 0.228599 | 2(Loss) | true |
| glaze | 3704.18 | 1.67815 | 5919.36ms | 475954 | 30 | 1.26861e+08 | 122539 | 0.0836353 | 3(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| glaze | 1914.8 | 0.280646 | 9016.08ms | 631514 | 40 | 3.11672e+07 | 314528 | 4.21572 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1663.44 | 0.549131 | 8840.94ms | 631514 | 640 | 2.5298e+09 | 362057 | 2.68318 | 2(Tie) | true |
| jsonifier STATISTICAL TIE | 1659.62 | 0.415106 | 9528.1ms | 631514 | 1280 | 2.90454e+09 | 362890 | 0.0908538 | 2(Tie) | true |
| simdjson (reflection) | 1327.36 | 2.03472 | 5876.42ms | 631514 | 40 | 3.40926e+09 | 453728 | 3.44802 | 4(Loss) | true |
| simdjson (ondemand) | 1206.41 | 0.702705 | 6340.8ms | 631514 | 160 | 1.969e+09 | 499218 | 0.27328 | 5(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 2451.2 | 0.178062 | 7441.02ms | 631514 | 640 | 1.22498e+08 | 245699 | 0.057273 | 1(Win) | true |
| jsonifier | 2207.47 | 1.84391 | 8386.56ms | 631514 | 30 | 7.59237e+08 | 272828 | 2.90975 | 2(Loss) | true |
| glaze | 2022.17 | 0.366295 | 8679.07ms | 631514 | 640 | 7.61678e+08 | 297827 | 0.0933897 | 3(Loss) | true |
| simdjson (reflection) | 1637.67 | 0.62122 | 5366.62ms | 631514 | 30 | 1.56576e+08 | 367753 | 0.42974 | 4(Loss) | true |
| simdjson (ondemand) | 1189.63 | 1.29966 | 6766.46ms | 631514 | 30 | 1.29875e+09 | 506257 | 1.84637 | 5(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16837 | 0.480278 | 4506.72ms | 716365 | 40 | 1.51909e+06 | 40576 | 0.146997 | 1(Win) | true |
| glaze | 3206.24 | 0.43094 | 5494.53ms | 716365 | 640 | 5.39624e+08 | 213078 | 1.65691 | 2(Loss) | true |
| simdjson (reflection) | 436.225 | 0.621577 | 9987.85ms | 716365 | 320 | 3.0324e+10 | 1.56612e+06 | 1.70551 | 3(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 17517.1 | 0.121164 | 4138.24ms | 716365 | 2560 | 5.7165e+06 | 39000.6 | 0.15048 | 1(Win) | true |
| glaze | 4148.98 | 0.493298 | 8687.61ms | 716365 | 640 | 4.22266e+08 | 164662 | 2.57576 | 2(Loss) | true |
| simdjson (reflection) | 452.808 | 0.782435 | 5029.59ms | 716365 | 80 | 1.11488e+10 | 1.50876e+06 | 3.01921 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 1393.22 | 0.438859 | 178.313ms | 2632 | 4890 | 305697 | 1801.63 | 1.24793 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1391.39 | 1.343 | 193.575ms | 2632 | 320 | 187835 | 1804 | 0.132861 | 1(Tie) | true |
| glaze | 1199.84 | 0.813878 | 223.142ms | 2632 | 320 | 92766.7 | 2092 | 2.71577 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 867.216 | 1.16794 | 271.434ms | 2632 | 320 | 365684 | 2894.4 | 0.611791 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 858.203 | 2.63865 | 306.232ms | 2632 | 40 | 238240 | 2924.8 | 1.10619 | 4(Tie) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2216.59 | 1.2874 | 160.019ms | 2632 | 640 | 136020 | 1132.4 | 0.604122 | 1(Win) | true |
| glaze | 1759.72 | 1.95749 | 175.077ms | 2632 | 320 | 249478 | 1426.4 | 0.507328 | 2(Loss) | true |
| jsonifier (two-stage) | 1606.75 | 0.952895 | 181.51ms | 2632 | 1280 | 283644 | 1562.2 | 2.33808 | 3(Loss) | true |
| simdjson (reflection) | 1325 | 1.94705 | 236.24ms | 2632 | 80 | 108840 | 1894.4 | 0.3367 | 4(Loss) | true |
| simdjson (ondemand) | 1089.54 | 0.458023 | 254.916ms | 2632 | 2560 | 285039 | 2303.8 | 0.138708 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8869.51 | 4.97148 | 32.437ms | 2632 | 1280 | 253370 | 283 | 1.32497 | 1(Win) | true |
| simdjson (reflection) | 6850.63 | 2.6109 | 38.528ms | 2632 | 2560 | 234278 | 366.4 | 2.00445 | 2(Loss) | true |
| glaze | 2638.76 | 0.581642 | 96.1029ms | 2632 | 4890 | 149690 | 951.231 | 2.54778 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9680.25 | 2.42623 | 28.898ms | 2632 | 4890 | 193541 | 259.298 | 3.28304 | 1(Win) | true |
| simdjson (reflection) | 7399.12 | 2.0043 | 36.9792ms | 2632 | 4890 | 226072 | 339.239 | 3.10218 | 2(Loss) | true |
| glaze | 3142.78 | 0.767628 | 87.831ms | 2632 | 4890 | 183803 | 798.678 | 0.277423 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 1601.91 | 0.308946 | 205.834ms | 3370 | 4890 | 187869 | 2006.28 | 0.836513 | 1(Win) | true |
| jsonifier | 1513.75 | 0.254372 | 212.163ms | 3370 | 4890 | 142625 | 2123.12 | 0.154028 | 2(Loss) | true |
| glaze | 1348.05 | 0.457003 | 249.165ms | 3370 | 2560 | 303898 | 2384.1 | 0.844285 | 3(Loss) | true |
| simdjson (reflection) | 1252.76 | 0.369366 | 266.004ms | 3370 | 4890 | 439084 | 2565.44 | 1.8988 | 4(Loss) | true |
| simdjson (ondemand) | 990.548 | 0.23825 | 325.733ms | 3370 | 4890 | 292203 | 3244.55 | 0.409732 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 2021.31 | 0.638856 | 191.644ms | 3370 | 2560 | 264144 | 1590 | 2.68087 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 2007.92 | 0.971121 | 196.698ms | 3370 | 1280 | 309259 | 1600.6 | 1.02247 | 1(Tie) | true |
| glaze | 1739.87 | 0.602974 | 205.45ms | 3370 | 2560 | 317589 | 1847.2 | 1.9637 | 3(Loss) | true |
| simdjson (reflection) | 1586.63 | 0.763209 | 236.294ms | 3370 | 160 | 38239.6 | 2025.6 | 0.158228 | 4(Loss) | true |
| simdjson (ondemand) | 1522.3 | 0.690724 | 261.65ms | 3370 | 640 | 136097 | 2111.2 | 0.0378788 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10067.3 | 1.97821 | 37.12ms | 3643 | 4890 | 227903 | 345.103 | 3.41704 | 1(Win) | true |
| glaze | 3680.32 | 0.553739 | 100.547ms | 3682 | 4890 | 136495 | 954.11 | 1.6092 | 2(Loss) | true |
| simdjson (reflection) | 351.333 | 0.254712 | 1038.1ms | 3643 | 4890 | 3.10233e+06 | 9888.72 | 0.982098 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12997.1 | 2.37594 | 29.666ms | 3643 | 4890 | 197244 | 267.308 | 2.90302 | 1(Win) | true |
| glaze | 4649.67 | 3.21672 | 86.7389ms | 3682 | 320 | 188842 | 755.2 | 0 | 2(Loss) | true |
| simdjson (reflection) | 304.16 | 0.768859 | 997.14ms | 3643 | 320 | 2.46807e+06 | 11422.4 | 0.691114 | 3(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 848.369 | 0.13966 | 544.587ms | 4630 | 4890 | 258372 | 5204.71 | 0.584396 | 1(Win) | true |
| jsonifier (two-stage) | 690.76 | 0.366426 | 645.123ms | 4630 | 4890 | 2.6828e+06 | 6392.25 | 0.180331 | 2(Loss) | true |
| glaze | 491.071 | 0.21907 | 980.01ms | 4630 | 640 | 248324 | 8991.6 | 0.084452 | 3(Loss) | true |
| simdjson (ondemand) | 451.007 | 0.221572 | 995.309ms | 4630 | 4890 | 2.3011e+06 | 9790.35 | 0.123241 | 4(Loss) | true |
| simdjson (reflection) | 331.361 | 0.208134 | 1393.15ms | 4630 | 2560 | 1.96918e+06 | 13325.4 | 1.25992 | 5(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1105.65 | 0.952284 | 538.205ms | 4630 | 30 | 43389.4 | 3993.6 | 0 | 1(Win) | true |
| jsonifier (two-stage) | 872.803 | 0.185303 | 634.821ms | 4630 | 2560 | 224975 | 5059 | 0.0276658 | 2(Loss) | true |
| simdjson (reflection) | 602.378 | 4.11695 | 847.765ms | 4630 | 30 | 2.7321e+06 | 7330.13 | 0.11655 | 3(Loss) | true |
| glaze | 543.555 | 0.472425 | 946.346ms | 4630 | 1280 | 1.88518e+06 | 8123.4 | 2.9416 | 4(Loss) | true |
| simdjson (ondemand) | 457.253 | 0.455351 | 1107.81ms | 4630 | 1280 | 2.47486e+06 | 9656.6 | 0.577011 | 5(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2378.02 | 0.778823 | 190.246ms | 4630 | 640 | 133840 | 1856.8 | 0.563258 | 1(Win) | true |
| glaze | 1665.23 | 0.870021 | 305.433ms | 4630 | 640 | 340609 | 2651.6 | 1.67606 | 2(Loss) | true |
| simdjson (reflection) | 842.673 | 0.308195 | 528.956ms | 4630 | 4890 | 1.27527e+06 | 5239.89 | 1.79757 | 3(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2310.01 | 2.99359 | 199.213ms | 4630 | 30 | 98228.7 | 1911.47 | 2.28311 | 1(Win) | true |
| glaze | 1850.75 | 0.465865 | 252.998ms | 4630 | 2560 | 316248 | 2385.8 | 0.242515 | 2(Loss) | true |
| simdjson (reflection) | 936.76 | 1.12958 | 530.641ms | 4630 | 80 | 226794 | 4713.6 | 0.340599 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1617.77 | 0.364595 | 733.804ms | 11579 | 2560 | 1.58551e+06 | 6825.8 | 2.64434 | 1(Win) | true |
| jsonifier (two-stage) | 1369.73 | 0.338393 | 774.212ms | 11579 | 2560 | 1.90528e+06 | 8061.9 | 0.22648 | 2(Loss) | true |
| simdjson (reflection) | 1260.74 | 0.54985 | 924.693ms | 11579 | 640 | 1.48442e+06 | 8758.8 | 0.882672 | 3(Loss) | true |
| glaze | 919.305 | 0.193375 | 1218.78ms | 11579 | 4890 | 2.63835e+06 | 12011.9 | 3.1622 | 4(Loss) | true |
| simdjson (ondemand) | 899.586 | 0.831552 | 1160.06ms | 11579 | 320 | 3.33416e+06 | 12275.2 | 2.1054 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1848.65 | 0.804631 | 781.86ms | 11579 | 30 | 69302.4 | 5973.33 | 0.286533 | 1(Win) | true |
| jsonifier (two-stage) | 1697.3 | 0.247187 | 776.619ms | 11579 | 4890 | 1.26469e+06 | 6505.96 | 2.23228 | 2(Loss) | true |
| simdjson (reflection) | 1342.58 | 0.284244 | 940.096ms | 11579 | 4890 | 2.67273e+06 | 8224.93 | 1.05467 | 3(Loss) | true |
| simdjson (ondemand) | 1093.67 | 0.578877 | 1109.49ms | 11579 | 640 | 2.18635e+06 | 10096.8 | 1.35721 | 4(Loss) | true |
| glaze | 1014.12 | 0.519153 | 1194.61ms | 11579 | 640 | 2.04518e+06 | 10888.8 | 0.658187 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6971.15 | 2.6224 | 208.51ms | 14795 | 160 | 450753 | 2024 | 0.0789889 | 1(Win) | true |
| glaze | 2745.9 | 0.324527 | 497ms | 14795 | 4890 | 1.35979e+06 | 5138.43 | 0.166237 | 2(Loss) | true |
| simdjson (reflection) | 254.33 | 0.703497 | 5280.23ms | 14795 | 320 | 4.87428e+07 | 55477.6 | 0.194295 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7182.66 | 0.471269 | 195.739ms | 14795 | 2560 | 219401 | 1964.4 | 0.112119 | 1(Win) | true |
| glaze | 3503.49 | 0.341905 | 425.299ms | 14795 | 2560 | 485377 | 4027.3 | 0.082008 | 2(Loss) | true |
| simdjson (reflection) | 275.123 | 0.100958 | 5176.9ms | 14795 | 4890 | 1.31089e+07 | 51284.8 | 0.816517 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1237.2 | 0.919601 | 250.22ms | 3223 | 640 | 334058 | 2484.4 | 1.13021 | 1(Win) | true |
| jsonifier (two-stage) | 990.842 | 0.228254 | 317.779ms | 3223 | 2560 | 128347 | 3102.1 | 0.196255 | 2(Loss) | true |
| glaze | 848.922 | 0.328119 | 366.083ms | 3223 | 2560 | 361316 | 3620.7 | 1.92058 | 3(Loss) | true |
| simdjson (ondemand) | 827.819 | 0.390291 | 386.681ms | 3223 | 1280 | 268804 | 3713 | 0.188883 | 4(Loss) | true |
| simdjson (reflection) | 794.811 | 0.566291 | 378.985ms | 3223 | 640 | 306940 | 3867.2 | 2.61091 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1745.36 | 0.426314 | 237.657ms | 3223 | 4890 | 275623 | 1761.06 | 0.369986 | 1(Win) | true |
| jsonifier (two-stage) | 1207.05 | 0.674451 | 323.993ms | 3223 | 4890 | 1.44237e+06 | 2546.44 | 2.59569 | 2(Loss) | true |
| glaze | 1153.94 | 0.280017 | 330.812ms | 3223 | 4890 | 272041 | 2663.66 | 0.34116 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1009.64 | 0.208806 | 361.506ms | 3223 | 4890 | 197600 | 3044.36 | 0.199397 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1007.17 | 0.545023 | 364.497ms | 3223 | 1280 | 354121 | 3051.8 | 0.0196567 | 4(Tie) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8129.65 | 1.877 | 40.916ms | 3223 | 4890 | 246271 | 378.084 | 0.420784 | 1(Win) | true |
| simdjson (reflection) | 6963.04 | 1.61761 | 47.2568ms | 3223 | 4890 | 249334 | 441.43 | 2.98245 | 2(Loss) | true |
| glaze | 1765.89 | 0.502173 | 177.546ms | 3223 | 4890 | 373602 | 1740.59 | 1.71708 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9623.33 | 2.89675 | 35.8922ms | 3223 | 2560 | 219144 | 319.4 | 1.66256 | 1(Win) | true |
| simdjson (reflection) | 7092.05 | 3.2118 | 44.5481ms | 3223 | 1280 | 248019 | 433.4 | 2.65049 | 2(Loss) | true |
| glaze | 1947.84 | 1.01145 | 154.779ms | 3223 | 1280 | 326068 | 1578 | 1.2837 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1687.83 | 0.80693 | 339.295ms | 5839 | 320 | 226798 | 3299.2 | 0.0968992 | 1(Win) | true |
| jsonifier (two-stage) | 1591.68 | 0.31647 | 360.815ms | 5839 | 2560 | 313811 | 3498.5 | 0.356024 | 2(Loss) | true |
| simdjson (ondemand) | 1338.94 | 0.228007 | 418.618ms | 5839 | 2560 | 230194 | 4158.9 | 0.0696814 | 3(Loss) | true |
| simdjson (reflection) | 1257.65 | 0.315972 | 431.302ms | 5839 | 2560 | 501064 | 4427.7 | 0.11079 | 4(Loss) | true |
| glaze | 1223.74 | 0.620544 | 450.095ms | 5839 | 640 | 510299 | 4550.4 | 0.406002 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 2085.89 | 0.79187 | 320.201ms | 5839 | 640 | 286009 | 2669.6 | 0.328554 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 2060.73 | 0.401806 | 344.862ms | 5839 | 2560 | 301791 | 2702.2 | 0.371443 | 1(Tie) | true |
| simdjson (ondemand) | 1724.74 | 0.408537 | 387.962ms | 5839 | 1280 | 222690 | 3228.6 | 0.00619502 | 3(Loss) | true |
| simdjson (reflection) | 1654.44 | 0.340875 | 397.315ms | 5839 | 2560 | 336981 | 3365.8 | 0.420118 | 4(Loss) | true |
| glaze | 1493.06 | 0.881218 | 422.585ms | 5839 | 320 | 345654 | 3729.6 | 0.681721 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 15210.9 | 2.00421 | 45.5729ms | 6938 | 4890 | 371668 | 434.991 | 1.46736 | 1(Win) | true |
| glaze | 2409.81 | 0.935553 | 278.74ms | 6960 | 1280 | 849964 | 2754.4 | 0.563177 | 2(Loss) | true |
| simdjson (reflection) | 333.041 | 0.442654 | 2002.01ms | 6938 | 160 | 1.23743e+06 | 19867.2 | 0.184887 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16746.7 | 1.81878 | 42.5569ms | 6938 | 4890 | 252510 | 395.099 | 0.278824 | 1(Win) | true |
| glaze | 2162.5 | 0.253035 | 309.459ms | 6960 | 2560 | 154422 | 3069.4 | 0.655867 | 2(Loss) | true |
| simdjson (reflection) | 327.628 | 0.207832 | 2000.41ms | 6938 | 4890 | 8.6147e+06 | 20195.5 | 0.656853 | 3(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1548.75 | 0.464698 | 296.758ms | 4857 | 1280 | 247245 | 2990.8 | 0.389366 | 1(Win) | true |
| jsonifier (two-stage) | 1233.49 | 0.949439 | 392.221ms | 4857 | 160 | 203386 | 3755.2 | 0.12766 | 2(Loss) | true |
| glaze | 1174.56 | 0.530399 | 396.252ms | 4857 | 640 | 280009 | 3943.6 | 0.634953 | 3(Loss) | true |
| simdjson (reflection) | 1029.24 | 0.50002 | 471.23ms | 4857 | 640 | 324084 | 4500.4 | 0.204009 | 4(Loss) | true |
| simdjson (ondemand) | 903.152 | 0.17064 | 528.142ms | 4857 | 2560 | 196071 | 5128.7 | 0.871293 | 5(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2315.53 | 0.292893 | 250.778ms | 4857 | 2560 | 87880.6 | 2000.4 | 0.970297 | 1(Win) | true |
| glaze | 1855.32 | 0.97615 | 299.902ms | 4857 | 1280 | 760222 | 2496.6 | 0.406893 | 2(Loss) | true |
| jsonifier (two-stage) | 1536.7 | 0.63801 | 358.153ms | 4857 | 4890 | 1.80852e+06 | 3014.26 | 0.140599 | 3(Loss) | true |
| simdjson (reflection) | 1228.78 | 1.80314 | 430.841ms | 4857 | 40 | 184803 | 3769.6 | 0.397727 | 4(Loss) | true |
| simdjson (ondemand) | 1150.63 | 0.390445 | 459.033ms | 4857 | 160 | 39527.7 | 4025.6 | 0.0794281 | 5(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11102.6 | 2.45484 | 43.263ms | 4857 | 2560 | 268519 | 417.2 | 3.06324 | 1(Win) | true |
| simdjson (reflection) | 7986.85 | 1.25423 | 60.778ms | 4857 | 4890 | 258732 | 579.953 | 1.1604 | 2(Loss) | true |
| glaze | 2565.92 | 0.980575 | 192.73ms | 4857 | 640 | 200536 | 1805.2 | 3.15451 | 3(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13154.7 | 1.95 | 39.5699ms | 4857 | 4890 | 230544 | 352.118 | 1.09051 | 1(Win) | true |
| simdjson (reflection) | 8962.84 | 2.72095 | 55.616ms | 4857 | 1280 | 253103 | 516.8 | 0.232739 | 2(Loss) | true |
| glaze | 2614.45 | 0.502379 | 184.524ms | 4857 | 4890 | 387388 | 1771.69 | 0.282307 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1649.09 | 1.00231 | 409.102ms | 6701 | 80 | 120692 | 3875.2 | 0.737705 | 1(Win) | true |
| jsonifier (two-stage) | 1549.45 | 0.298184 | 420.497ms | 6701 | 1280 | 193597 | 4124.4 | 0.357557 | 2(Loss) | true |
| simdjson (reflection) | 1314.15 | 0.286835 | 504.357ms | 6701 | 4890 | 951403 | 4862.9 | 1.17663 | 3(Loss) | true |
| glaze | 1289.64 | 0.347976 | 477.701ms | 6701 | 2560 | 761165 | 4955.3 | 0.78303 | 4(Loss) | true |
| simdjson (ondemand) | 1180.29 | 0.977628 | 549.761ms | 6701 | 80 | 224150 | 5414.4 | 0.235849 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2108.22 | 0.486388 | 359.902ms | 6701 | 4890 | 1.06298e+06 | 3031.27 | 1.00868 | 1(Win) | true |
| glaze | 2078.1 | 0.3849 | 358.896ms | 6701 | 1280 | 179330 | 3075.2 | 0.684666 | 2(Loss) | true |
| jsonifier (two-stage) | 1968.65 | 0.436361 | 379.491ms | 6701 | 4890 | 981169 | 3246.17 | 0.369092 | 3(Loss) | true |
| simdjson (reflection) | 1649.09 | 1.15588 | 454.874ms | 6701 | 80 | 160511 | 3875.2 | 0.0825083 | 4(Loss) | true |
| simdjson (ondemand) | 1372.22 | 0.304572 | 511.325ms | 6701 | 4890 | 983832 | 4657.11 | 1.35549 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12845.7 | 3.61297 | 58.4499ms | 7376 | 640 | 250516 | 547.6 | 0.0729927 | 1(Win) | true |
| glaze | 2244.23 | 0.260179 | 318.75ms | 7376 | 2560 | 170253 | 3134.4 | 0.0510204 | 2(Loss) | true |
| simdjson (reflection) | 347.627 | 0.443228 | 2058.62ms | 7376 | 320 | 2.57406e+06 | 20235.2 | 0.102686 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14262.6 | 4.0482 | 53.749ms | 7376 | 640 | 255124 | 493.2 | 0.0811688 | 1(Win) | true |
| glaze | 2457.4 | 0.305023 | 289.652ms | 7376 | 2560 | 195162 | 2862.5 | 1.34073 | 2(Loss) | true |
| simdjson (reflection) | 349.294 | 0.122138 | 2025.36ms | 7376 | 4890 | 2.9585e+06 | 20138.6 | 0.0626767 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1417.23 | 0.70265 | 116.883ms | 1691 | 2560 | 163654 | 1137.9 | 0.308533 | 1(Win) | true |
| glaze | 1305.27 | 0.706751 | 128.605ms | 1691 | 2560 | 195190 | 1235.5 | 0.00809454 | 2(Loss) | true |
| jsonifier (two-stage) | 1221.34 | 1.6057 | 135.995ms | 1691 | 640 | 287688 | 1320.4 | 0.572289 | 3(Loss) | true |
| simdjson (ondemand) | 1082.98 | 0.749367 | 156.33ms | 1691 | 2560 | 318770 | 1489.1 | 1.78736 | 4(Loss) | true |
| simdjson (reflection) | 1057.14 | 0.82348 | 154.604ms | 1691 | 2560 | 403990 | 1525.5 | 0.0327654 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2101.11 | 0.802478 | 103.087ms | 1691 | 4890 | 185509 | 767.529 | 2.11932 | 1(Win) | true |
| glaze STATISTICAL TIE | 1673.7 | 0.474653 | 119.518ms | 1691 | 4890 | 102281 | 963.534 | 0.0866046 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1655.71 | 0.500799 | 123.224ms | 1691 | 2560 | 60909.4 | 974 | 0.976007 | 2(Tie) | true |
| simdjson (ondemand) | 1428.18 | 0.630797 | 136.148ms | 1691 | 4890 | 248091 | 1129.17 | 1.31318 | 4(Loss) | true |
| simdjson (reflection) | 1276.85 | 0.993018 | 150.022ms | 1691 | 1280 | 201340 | 1263 | 1.33184 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10385.7 | 3.24807 | 20.746ms | 1996 | 4890 | 173303 | 183.283 | 0.605512 | 1(Win) | true |
| simdjson (reflection) | 9471.34 | 2.86267 | 23.1762ms | 1996 | 4890 | 161864 | 200.978 | 4.25044 | 2(Loss) | true |
| glaze | 2867.55 | 1.0517 | 68.7711ms | 1996 | 4890 | 238339 | 663.82 | 0.578794 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13684.8 | 3.60548 | 16.6001ms | 1996 | 4890 | 122993 | 139.099 | 3.20211 | 1(Win) | true |
| simdjson (reflection) | 10223.1 | 4.3572 | 20.8008ms | 1996 | 2560 | 168506 | 186.2 | 2.98673 | 2(Loss) | true |
| glaze | 3511.73 | 1.32279 | 56.938ms | 1996 | 4890 | 251402 | 542.05 | 0.23112 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1592.16 | 0.99256 | 138.818ms | 2158 | 1280 | 210694 | 1292.6 | 0.0463965 | 1(Win) | true |
| glaze | 1530.82 | 1.00288 | 142.734ms | 2158 | 1280 | 232681 | 1344.4 | 0.328358 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1393.57 | 1.35582 | 158.719ms | 2158 | 640 | 256583 | 1476.8 | 1.38889 | 3(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1369.65 | 0.949908 | 150.527ms | 2158 | 1280 | 260771 | 1502.6 | 0.173333 | 3(Tie) | true |
| simdjson (reflection) | 1268.51 | 1.21659 | 164.886ms | 2158 | 640 | 249334 | 1622.4 | 1.98163 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2233.1 | 2.35208 | 122.762ms | 2158 | 160 | 75180.9 | 921.6 | 0.689655 | 1(Win) | true |
| glaze | 1995.76 | 0.410819 | 128.207ms | 2158 | 2560 | 45943.7 | 1031.2 | 0.36715 | 2(Loss) | true |
| jsonifier (two-stage) | 1828.22 | 0.642619 | 134.909ms | 2158 | 2560 | 133965 | 1125.7 | 1.18504 | 3(Loss) | true |
| simdjson (ondemand) | 1629.09 | 0.734824 | 154.459ms | 2158 | 2560 | 220607 | 1263.3 | 1.9177 | 4(Loss) | true |
| simdjson (reflection) | 1440.19 | 1.07175 | 157.679ms | 2158 | 1280 | 300235 | 1429 | 0.69053 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13895.4 | 4.00695 | 22.7612ms | 2866 | 2560 | 159029 | 196.7 | 0.0508647 | 1(Win) | true |
| glaze | 2667.35 | 0.365346 | 107.319ms | 2866 | 2560 | 35879.1 | 1024.7 | 0.0292683 | 2(Loss) | true |
| simdjson (reflection) | 399.502 | 0.716838 | 709.849ms | 2866 | 80 | 192419 | 6841.6 | 0.926784 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14478.4 | 2.97507 | 20.9779ms | 2866 | 4890 | 154247 | 188.78 | 4.70348 | 1(Win) | true |
| glaze | 3080.04 | 1.11339 | 93.537ms | 2866 | 1280 | 124952 | 887.4 | 0.067659 | 2(Loss) | true |
| simdjson (reflection) | 390.819 | 0.741634 | 704.916ms | 2866 | 1280 | 3.44343e+06 | 6993.6 | 0.125671 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1729.44 | 1.64515 | 246.651ms | 4390 | 160 | 253774 | 2420.8 | 0.866667 | 1(Win) | true |
| jsonifier (two-stage) | 1163.47 | 1.26355 | 368.535ms | 4390 | 160 | 330769 | 3598.4 | 0.312221 | 2(Loss) | true |
| glaze | 936.189 | 0.221873 | 436.437ms | 4390 | 4890 | 481416 | 4471.99 | 1.07791 | 3(Loss) | true |
| simdjson (reflection) | 906.864 | 0.27707 | 460.748ms | 4390 | 2560 | 418854 | 4616.6 | 0.22908 | 4(Loss) | true |
| simdjson (ondemand) | 747.604 | 0.15321 | 574.422ms | 4390 | 4890 | 359971 | 5600.07 | 0.132582 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2213.74 | 1.37364 | 230.837ms | 4390 | 160 | 107980 | 1891.2 | 0.505051 | 1(Win) | true |
| jsonifier (two-stage) | 1367.54 | 0.241218 | 349.454ms | 4390 | 4890 | 266670 | 3061.42 | 0.21687 | 2(Loss) | true |
| glaze | 1145.14 | 1.05941 | 413.364ms | 4390 | 160 | 240028 | 3656 | 0.131464 | 3(Loss) | true |
| simdjson (reflection) | 980.751 | 1.05485 | 466.672ms | 4390 | 160 | 324424 | 4268.8 | 0.596125 | 4(Loss) | true |
| simdjson (ondemand) | 820.699 | 0.182367 | 562.914ms | 4390 | 2560 | 221561 | 5101.3 | 1.28057 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10035.1 | 3.39058 | 45.8611ms | 4390 | 1280 | 256122 | 417.2 | 0.192123 | 1(Win) | true |
| simdjson (reflection) | 7781.84 | 1.84207 | 57.7439ms | 4390 | 2560 | 251429 | 538 | 1.5861 | 2(Loss) | true |
| glaze | 1662.15 | 0.701468 | 251.021ms | 4390 | 2560 | 799178 | 2518.8 | 1.26236 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10511.5 | 1.79603 | 42.6941ms | 4390 | 4890 | 250231 | 398.292 | 0.705948 | 1(Win) | true |
| simdjson (reflection) | 7628.7 | 1.90093 | 54.6081ms | 4390 | 2560 | 278614 | 548.8 | 2.6178 | 2(Loss) | true |
| glaze | 1816.45 | 0.319321 | 231.548ms | 4390 | 4890 | 264878 | 2304.84 | 0.271366 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2331.72 | 0.515202 | 386.779ms | 9378 | 640 | 249920 | 3835.6 | 1.59992 | 1(Win) | true |
| jsonifier (two-stage) | 2076.12 | 0.215911 | 425.405ms | 9378 | 4890 | 423033 | 4307.82 | 0.228365 | 2(Loss) | true |
| simdjson (reflection) | 1774.3 | 0.284517 | 527.875ms | 9378 | 1280 | 263265 | 5040.6 | 0.378365 | 3(Loss) | true |
| glaze | 1497.18 | 0.293082 | 602.741ms | 9378 | 1280 | 392339 | 5973.6 | 0.086974 | 4(Loss) | true |
| simdjson (ondemand) | 1442.88 | 0.755338 | 645.427ms | 9378 | 80 | 175361 | 6198.4 | 0.0515996 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2670.76 | 0.340212 | 380.195ms | 9378 | 2560 | 332271 | 3348.7 | 0.206476 | 1(Win) | true |
| jsonifier (two-stage) | 2493.88 | 0.496789 | 416.242ms | 9378 | 1280 | 406277 | 3586.2 | 0.714286 | 2(Loss) | true |
| simdjson (reflection) | 1826.11 | 0.78809 | 520.388ms | 9378 | 320 | 476726 | 4897.6 | 1.2262 | 3(Loss) | true |
| glaze | 1663.48 | 0.589626 | 600.717ms | 9378 | 640 | 643155 | 5376.4 | 0.350903 | 4(Loss) | true |
| simdjson (ondemand) | 1538.87 | 0.239303 | 626.458ms | 9378 | 4890 | 945848 | 5811.78 | 0.22204 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 19745.4 | 1.41906 | 58.4701ms | 11521 | 4890 | 304900 | 556.447 | 1.74559 | 1(Win) | true |
| glaze | 2634.33 | 0.426043 | 434.723ms | 11521 | 640 | 202081 | 4170.8 | 0.978158 | 2(Loss) | true |
| simdjson (reflection) | 316.622 | 0.259447 | 3474.75ms | 11521 | 640 | 5.18772e+06 | 34701.6 | 0.968014 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 21775.7 | 1.44179 | 54.2141ms | 11521 | 4890 | 258791 | 504.566 | 0.171938 | 1(Win) | true |
| glaze | 2896.88 | 0.625507 | 381.345ms | 11521 | 640 | 360217 | 3792.8 | 0.0633179 | 2(Loss) | true |
| simdjson (reflection) | 314.488 | 0.149793 | 3465.52ms | 11521 | 2560 | 7.01125e+06 | 34937 | 0.199039 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2538.6 | 0.789787 | 173.73ms | 4669 | 1280 | 245634 | 1754 | 0.527281 | 1(Win) | true |
| jsonifier (two-stage) | 1549.63 | 1.09017 | 285.313ms | 4669 | 2560 | 2.51202e+06 | 2873.4 | 0.461506 | 2(Loss) | true |
| glaze | 1323.63 | 0.294865 | 340.299ms | 4669 | 4890 | 481141 | 3364.02 | 0.215026 | 3(Loss) | true |
| simdjson (reflection) | 1211.39 | 0.308513 | 377.865ms | 4669 | 2560 | 329205 | 3675.7 | 0.122576 | 4(Loss) | true |
| simdjson (ondemand) | 1110.22 | 0.558751 | 406.798ms | 4669 | 30 | 15065.7 | 4010.67 | 0.21322 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2729.04 | 0.960518 | 175.014ms | 4669 | 2560 | 628751 | 1631.6 | 1.63974 | 1(Win) | true |
| jsonifier (two-stage) | 1711.79 | 0.649708 | 276.041ms | 4669 | 1280 | 365590 | 2601.2 | 0.107527 | 2(Loss) | true |
| glaze | 1542.12 | 0.499367 | 305.681ms | 4669 | 1280 | 266112 | 2887.4 | 0.480234 | 3(Loss) | true |
| simdjson (ondemand) | 1235.76 | 0.340329 | 373.424ms | 4669 | 2560 | 384959 | 3603.2 | 0.0444247 | 4(Loss) | true |
| simdjson (reflection) | 1168.51 | 0.531842 | 389.047ms | 4669 | 1280 | 525729 | 3810.6 | 0.765625 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13103.9 | 2.7687 | 35.4931ms | 4669 | 2560 | 226589 | 339.8 | 1.07079 | 1(Win) | true |
| simdjson (reflection) | 3203.39 | 1.51323 | 141.837ms | 4669 | 640 | 283152 | 1390 | 0.900116 | 2(Loss) | true |
| glaze | 1836.92 | 0.821651 | 245.883ms | 4669 | 640 | 253875 | 2424 | 0.198413 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 15753.6 | 2.28738 | 30.9501ms | 4669 | 4890 | 204396 | 282.647 | 1.24143 | 1(Win) | true |
| simdjson (reflection) | 7844.79 | 1.83562 | 59.0999ms | 4669 | 2560 | 277900 | 567.6 | 0.318134 | 2(Loss) | true |
| glaze | 2147.33 | 0.659097 | 213.677ms | 4669 | 640 | 119544 | 2073.6 | 1.01325 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2552.91 | 0.227241 | 301.245ms | 7932 | 4890 | 221705 | 2963.11 | 0.0840172 | 1(Win) | true |
| jsonifier (two-stage) | 2301.21 | 0.45562 | 339.776ms | 7932 | 1280 | 287123 | 3287.2 | 0.399952 | 2(Loss) | true |
| simdjson (reflection) | 1797.49 | 0.402044 | 418.76ms | 7932 | 1280 | 366430 | 4208.4 | 0.151846 | 3(Loss) | true |
| glaze | 1770.2 | 0.254568 | 430.686ms | 7932 | 4890 | 578677 | 4273.26 | 0.0951697 | 4(Loss) | true |
| simdjson (ondemand) | 1708.81 | 0.69191 | 476.687ms | 7932 | 640 | 600425 | 4426.8 | 1.34605 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2811.26 | 0.400614 | 285.301ms | 7932 | 2560 | 297478 | 2690.8 | 1.06671 | 1(Win) | true |
| jsonifier (two-stage) | 2479.85 | 0.330234 | 328.115ms | 7932 | 1280 | 129888 | 3050.4 | 0.495825 | 2(Loss) | true |
| glaze | 1984 | 0.213694 | 397.461ms | 7932 | 4890 | 324620 | 3812.78 | 0.141228 | 3(Loss) | true |
| simdjson (reflection) | 1883.41 | 0.733715 | 410.033ms | 7932 | 640 | 555787 | 4016.4 | 0.289652 | 4(Loss) | true |
| simdjson (ondemand) | 1728.01 | 2.40389 | 437.745ms | 7932 | 40 | 442956 | 4377.6 | 0.391389 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16740.4 | 1.92936 | 55.8008ms | 9249 | 2560 | 264560 | 526.9 | 2.07284 | 1(Win) | true |
| glaze | 2187.85 | 0.166354 | 404.182ms | 9249 | 4890 | 219954 | 4031.61 | 0.486213 | 2(Loss) | true |
| simdjson (reflection) | 350.868 | 0.325338 | 2615.8ms | 9249 | 30 | 200676 | 25139.2 | 0.306435 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 17740.4 | 2.8254 | 52.8041ms | 9249 | 1280 | 252599 | 497.2 | 0.32077 | 1(Win) | true |
| glaze | 2377.12 | 0.466405 | 388.887ms | 9249 | 1280 | 383376 | 3710.6 | 0.0917134 | 2(Loss) | true |
| simdjson (reflection) | 335.11 | 0.140914 | 2601.68ms | 9249 | 2560 | 3.52178e+06 | 26321.3 | 0.0626476 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 593.02 | 0.528065 | 755.006ms | 4604 | 320 | 489167 | 7404 | 0.183348 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 494.506 | 0.283308 | 889.926ms | 4604 | 1280 | 809944 | 8879 | 0.00675706 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 492.807 | 0.354585 | 901.847ms | 4604 | 320 | 319380 | 8909.6 | 0.116864 | 2(Tie) | true |
| glaze | 417.02 | 0.461636 | 1059.39ms | 4604 | 320 | 755975 | 10528.8 | 0.0986792 | 4(Loss) | true |
| simdjson (ondemand) | 369.955 | 0.276435 | 1188.09ms | 4604 | 4890 | 5.2634e+06 | 11868.2 | 0.57578 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 702.683 | 0.400316 | 775.12ms | 4604 | 2560 | 1.60176e+06 | 6248.5 | 1.82349 | 1(Win) | true |
| jsonifier (two-stage) | 621.703 | 0.332236 | 926.846ms | 4604 | 320 | 176177 | 7062.4 | 0.473506 | 2(Loss) | true |
| simdjson (reflection) | 609.01 | 0.507782 | 899.779ms | 4604 | 320 | 428870 | 7209.6 | 1.16749 | 3(Loss) | true |
| glaze | 490.858 | 0.252531 | 1036.39ms | 4604 | 4890 | 2.49514e+06 | 8944.98 | 0.194423 | 4(Loss) | true |
| simdjson (ondemand) | 434.499 | 0.141055 | 1148.19ms | 4604 | 4890 | 993524 | 10105.2 | 0.12729 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1798.81 | 0.559069 | 247.233ms | 4604 | 2560 | 476728 | 2440.9 | 0.863636 | 1(Win) | true |
| simdjson (reflection) | 1415.43 | 0.35656 | 324.099ms | 4918 | 2560 | 357359 | 3313.6 | 0.790419 | 2(Loss) | true |
| glaze | 1009.3 | 0.336252 | 450.193ms | 4604 | 4890 | 1.04633e+06 | 4350.27 | 0.0983063 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1931.85 | 0.867974 | 240.883ms | 4604 | 640 | 249067 | 2272.8 | 0.176305 | 1(Win) | true |
| simdjson (reflection) | 1521.4 | 0.343409 | 317.564ms | 4918 | 1280 | 143458 | 3082.8 | 0.0518739 | 2(Loss) | true |
| glaze | 993.735 | 0.856599 | 419.003ms | 4604 | 640 | 916780 | 4418.4 | 0.198771 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 1665.61 | 0.237811 | 1093.76ms | 18245 | 4890 | 3.01794e+06 | 10446.5 | 1.02912 | 1(Win) | true |
| simdjson (reflection) | 1635.75 | 0.879205 | 1088.43ms | 18245 | 640 | 5.59777e+06 | 10637.2 | 0.258795 | 2(Loss) | true |
| jsonifier | 1456 | 0.355017 | 1199.53ms | 18245 | 2560 | 4.6079e+06 | 11950.4 | 0.594286 | 3(Loss) | true |
| glaze STATISTICAL TIE | 1194.97 | 0.154159 | 1473.22ms | 18245 | 4890 | 2.46389e+06 | 14560.9 | 1.47359 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1169.84 | 2.13111 | 1418.27ms | 18245 | 40 | 4.01887e+06 | 14873.6 | 0.171821 | 4(Tie) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 2019.29 | 0.709138 | 1081.09ms | 18245 | 320 | 1.19482e+06 | 8616.8 | 0.764695 | 1(Win) | true |
| simdjson (reflection) | 1885.05 | 0.746076 | 1095.39ms | 18245 | 320 | 1.5176e+06 | 9230.4 | 0.500172 | 2(Loss) | true |
| jsonifier | 1823.19 | 0.480927 | 1136.42ms | 18245 | 1280 | 2.69645e+06 | 9543.6 | 0.0712012 | 3(Loss) | true |
| simdjson (ondemand) | 1399.78 | 0.941387 | 1347.65ms | 18245 | 160 | 2.19092e+06 | 12430.4 | 0.473994 | 4(Loss) | true |
| glaze | 1356.18 | 0.216695 | 1442.16ms | 18245 | 2560 | 1.97875e+06 | 12830 | 0.91899 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8050.99 | 0.388887 | 313.499ms | 24579 | 4890 | 626883 | 2911.49 | 0.918183 | 1(Win) | true |
| glaze | 2847.05 | 0.464787 | 800.326ms | 24579 | 2560 | 3.74873e+06 | 8233.2 | 0.223986 | 2(Loss) | true |
| simdjson (reflection) | 265.646 | 0.923123 | 8295.89ms | 24893 | 80 | 5.4445e+07 | 89366.4 | 0.017907 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7702.54 | 2.1478 | 299.866ms | 24579 | 80 | 341772 | 3043.2 | 3.82096 | 1(Win) | true |
| glaze | 3431.17 | 0.303093 | 701.835ms | 24579 | 2560 | 1.09758e+06 | 6831.6 | 1.43982 | 2(Loss) | true |
| simdjson (reflection) | 275.664 | 0.483633 | 8437.07ms | 24893 | 640 | 1.11021e+08 | 86118.8 | 1.17625 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 689.714 | 0.389454 | 715.159ms | 4604 | 640 | 393391 | 6366 | 0.842732 | 1(Win) | true |
| jsonifier (two-stage) | 497.475 | 1.33021 | 940.993ms | 4604 | 640 | 8.82158e+06 | 8826 | 1.70077 | 2(Loss) | true |
| simdjson (reflection) | 442.831 | 0.413067 | 1007.64ms | 4604 | 2560 | 4.29412e+06 | 9915.1 | 0.0655136 | 3(Loss) | true |
| glaze | 408.203 | 0.222533 | 1114.9ms | 4604 | 2560 | 1.46672e+06 | 10756.2 | 1.72319 | 4(Loss) | true |
| simdjson (ondemand) | 354.914 | 0.663614 | 1350.85ms | 4604 | 320 | 2.15677e+06 | 12371.2 | 0.992685 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 851.706 | 0.517417 | 717.056ms | 4604 | 640 | 455357 | 5155.2 | 0.3582 | 1(Win) | true |
| jsonifier (two-stage) | 561.343 | 1.1349 | 910.789ms | 4604 | 1280 | 1.00864e+07 | 7821.8 | 0.257587 | 2(Loss) | true |
| simdjson (reflection) | 506.567 | 0.784085 | 964.637ms | 4604 | 640 | 2.956e+06 | 8667.6 | 1.26219 | 3(Loss) | true |
| glaze | 451.052 | 0.910862 | 1127.26ms | 4604 | 640 | 5.03156e+06 | 9734.4 | 0.39604 | 4(Loss) | true |
| simdjson (ondemand) | 378.484 | 0.824356 | 1301.87ms | 4604 | 320 | 2.92655e+06 | 11600.8 | 0.117371 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1748.81 | 0.473855 | 253.614ms | 4604 | 4890 | 692123 | 2510.68 | 0.728138 | 1(Win) | true |
| simdjson (reflection) | 1451.17 | 1.09872 | 323.76ms | 4918 | 160 | 201760 | 3232 | 3.16395 | 2(Loss) | true |
| glaze | 909.352 | 0.460636 | 493.494ms | 4604 | 2560 | 1.26638e+06 | 4828.4 | 2.95974 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1786.13 | 0.451247 | 253.324ms | 4604 | 4890 | 601703 | 2458.23 | 1.94542 | 1(Win) | true |
| simdjson (reflection) | 1589.67 | 1.28049 | 347.024ms | 4918 | 40 | 57091.9 | 2950.4 | 1.69118 | 2(Loss) | true |
| glaze | 1008.05 | 0.327784 | 444.062ms | 4604 | 4890 | 996766 | 4355.66 | 1.25214 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1804.46 | 1.26866 | 1034.88ms | 18245 | 30 | 448959 | 9642.67 | 0.444444 | 1(Win) | true |
| jsonifier (two-stage) | 1692.66 | 0.401875 | 1041.16ms | 18245 | 4890 | 8.34521e+06 | 10279.5 | 0.274358 | 2(Loss) | true |
| simdjson (reflection) | 1406.38 | 0.873772 | 1186.63ms | 18245 | 640 | 7.47922e+06 | 12372 | 0.4808 | 3(Loss) | true |
| glaze | 1161.45 | 0.262425 | 1499.03ms | 18245 | 4890 | 7.558e+06 | 14981.1 | 0.363307 | 4(Loss) | true |
| simdjson (ondemand) | 1098.56 | 0.428758 | 1534.25ms | 18245 | 4890 | 2.25513e+07 | 15838.7 | 0.887965 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2115.53 | 0.839827 | 982.257ms | 18245 | 320 | 1.52679e+06 | 8224.8 | 0.532121 | 1(Win) | true |
| jsonifier (two-stage) | 1933.93 | 0.457866 | 1043ms | 18245 | 4890 | 8.29837e+06 | 8997.12 | 0.934701 | 2(Loss) | true |
| simdjson (reflection) | 1786.98 | 0.754871 | 1155.44ms | 18245 | 1280 | 6.91522e+06 | 9737 | 1.89223 | 3(Loss) | true |
| glaze STATISTICAL TIE | 1270.41 | 0.33221 | 1497.86ms | 18245 | 4890 | 1.01235e+07 | 13696.2 | 1.27297 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1263.5 | 0.30491 | 1478.02ms | 18245 | 4890 | 8.62168e+06 | 13771.1 | 2.22338 | 4(Tie) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8039.64 | 0.646308 | 318.77ms | 24579 | 1280 | 454512 | 2915.6 | 2.76147 | 1(Win) | true |
| glaze | 3010.11 | 0.671346 | 872.873ms | 24579 | 160 | 437296 | 7787.2 | 0.102838 | 2(Loss) | true |
| simdjson (reflection) | 278.637 | 0.31939 | 8894.23ms | 24893 | 1280 | 9.47831e+07 | 85199.8 | 0.704626 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8918.56 | 3.19939 | 286.681ms | 24579 | 30 | 212126 | 2628.27 | 0 | 1(Win) | true |
| glaze | 2909.82 | 0.864264 | 791.034ms | 24579 | 1280 | 6.20438e+06 | 8055.6 | 1.23153 | 2(Loss) | true |
| simdjson (reflection) | 289.357 | 0.529041 | 8780.04ms | 24893 | 320 | 6.02857e+07 | 82043.2 | 0.649074 | 3(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1098.65 | 0.468353 | 448.552ms | 5094 | 1280 | 548978 | 4421.8 | 1.45748 | 1(Win) | true |
| jsonifier (two-stage) | 896.71 | 1.06398 | 537.48ms | 5094 | 160 | 531614 | 5417.6 | 1.43799 | 2(Loss) | true |
| simdjson (reflection) | 710.652 | 0.432177 | 711.983ms | 5094 | 2560 | 2.23443e+06 | 6836 | 0.0878477 | 3(Loss) | true |
| glaze | 690.353 | 0.527339 | 727.339ms | 5094 | 1280 | 1.76265e+06 | 7037 | 1.93701 | 4(Loss) | true |
| simdjson (ondemand) | 621.484 | 0.761857 | 796.962ms | 5094 | 640 | 2.26979e+06 | 7816.8 | 0.509113 | 5(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1483.36 | 0.366589 | 433.067ms | 5094 | 2560 | 368996 | 3275 | 0.274056 | 1(Win) | true |
| jsonifier (two-stage) | 1090.02 | 0.814904 | 542.62ms | 5094 | 2560 | 3.37676e+06 | 4456.8 | 1.19891 | 2(Loss) | true |
| glaze | 923.718 | 0.997111 | 653.189ms | 5094 | 320 | 879988 | 5259.2 | 1.45062 | 3(Loss) | true |
| simdjson (reflection) | 836.45 | 0.283239 | 685.577ms | 5094 | 2560 | 692760 | 5807.9 | 0.132754 | 4(Loss) | true |
| simdjson (ondemand) | 764.897 | 0.318028 | 767.832ms | 5094 | 4890 | 1.99504e+06 | 6351.21 | 1.23222 | 5(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11261 | 3.22662 | 47.8661ms | 5094 | 1280 | 248008 | 431.4 | 3.79126 | 1(Win) | true |
| simdjson (reflection) | 7713.59 | 2.16025 | 65.8519ms | 5094 | 1280 | 236932 | 629.8 | 0.912524 | 2(Loss) | true |
| glaze | 1822.35 | 0.568052 | 265.324ms | 5094 | 1280 | 293522 | 2665.8 | 0.0974367 | 3(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 10362.7 | 4.23334 | 46.8349ms | 5094 | 640 | 252070 | 468.8 | 5.58559 | -(Win) | false |
| simdjson (reflection) | 8318.52 | 3.35905 | 58.5321ms | 5094 | 640 | 246286 | 584 | 3.84068 | 2(Loss) | true |
| glaze | 1793.42 | 1.47649 | 252.816ms | 5094 | 160 | 255938 | 2708.8 | 1.37725 | 3(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1332.85 | 0.645196 | 599.896ms | 8051 | 1280 | 1.76819e+06 | 5760.6 | 0.287336 | 1(Win) | true |
| glaze | 1067.1 | 0.416966 | 740.929ms | 8051 | 640 | 576058 | 7195.2 | 0.357063 | 2(Loss) | true |
| simdjson (reflection) | 975.508 | 0.479007 | 749.444ms | 8051 | 2560 | 3.63882e+06 | 7870.8 | 2.93471 | 3(Loss) | true |
| simdjson (ondemand) | 871.236 | 1.45187 | 884.266ms | 8051 | 160 | 2.61942e+06 | 8812.8 | 2.18924 | 4(Loss) | true |
| jsonifier (two-stage) | 777.632 | 0.986019 | 920.429ms | 8051 | 160 | 1.5165e+06 | 9873.6 | 0.883392 | 5(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 1492.99 | 0.372058 | 696.284ms | 8051 | 4890 | 1.79026e+06 | 5142.72 | 0.255783 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 1480.84 | 0.478236 | 592.28ms | 8051 | 2560 | 1.574e+06 | 5184.9 | 4.77509 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1228.35 | 0.268904 | 718.459ms | 8051 | 4890 | 1.38153e+06 | 6250.69 | 0.602792 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1223.05 | 0.705801 | 781.006ms | 8051 | 1280 | 2.51298e+06 | 6277.8 | 1.62038 | 3(Tie) | true |
| glaze | 1130.36 | 1.67316 | 748.916ms | 8051 | 30 | 387491 | 6792.53 | 1.24069 | 5(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16200.9 | 5.15751 | 68.0932ms | 9255 | 320 | 252642 | 544.8 | 0.147059 | 1(Win) | true |
| glaze | 2246.74 | 0.336753 | 403.016ms | 9255 | 4890 | 855814 | 3928.47 | 2.11361 | 2(Loss) | true |
| simdjson (reflection) | 330.443 | 0.305747 | 2801.92ms | 9255 | 1280 | 8.5368e+06 | 26710.4 | 1.11508 | 3(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13538.5 | 1.30607 | 68.8069ms | 9255 | 4890 | 354528 | 651.936 | 4.57608 | 1(Win) | true |
| glaze | 2476.5 | 1.45195 | 372.528ms | 9255 | 640 | 1.71379e+06 | 3564 | 1.24141 | 2(Loss) | true |
| simdjson (reflection) | 281.034 | 0.825512 | 2932.12ms | 9255 | 160 | 1.07548e+07 | 31406.4 | 1.81017 | 3(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 3792.9 | 6.9937 | 85.271ms | 2889 | 80 | 206470 | 726.4 | 2.99145 | 1(Win) | true |
| jsonifier | 3312.64 | 0.73833 | 85.63ms | 2889 | 4890 | 184398 | 831.712 | 4.1854 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 2875.96 | 0.710399 | 93.897ms | 2889 | 2560 | 118570 | 958 | 2.94434 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2822.92 | 2.72448 | 92.607ms | 2889 | 80 | 56566.3 | 976 | 0.328947 | 3(Tie) | true |
| glaze | 2186.18 | 0.533293 | 129.684ms | 2889 | 4890 | 220883 | 1260.26 | 0.307497 | 5(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3729.24 | 1.28852 | 82.1629ms | 2889 | 2560 | 231993 | 738.8 | 1.39995 | 1(Win) | true |
| jsonifier (two-stage) | 3374.77 | 1.41555 | 88.0819ms | 2889 | 1280 | 170949 | 816.4 | 3.04038 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 3229.5 | 0.86825 | 92.4869ms | 2889 | 4890 | 268301 | 853.124 | 0.254422 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 3219.62 | 0.643606 | 89.0701ms | 2889 | 4890 | 148332 | 855.742 | 2.71774 | 3(Tie) | true |
| glaze | 2037 | 0.529363 | 131.257ms | 2889 | 4890 | 250685 | 1352.56 | 2.84035 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 4205.18 | 1.60156 | 103.667ms | 3808 | 640 | 122431 | 863.6 | 0.598527 | 1(Win) | true |
| simdjson (ondemand) | 3855.19 | 1.8505 | 98.9722ms | 3808 | 1280 | 388946 | 942 | 0.842105 | 2(Loss) | true |
| jsonifier | 3521.71 | 1.05899 | 102.868ms | 3808 | 1280 | 152643 | 1031.2 | 0.270793 | 3(Loss) | true |
| simdjson (reflection) | 3149.69 | 0.882435 | 100.521ms | 3808 | 2560 | 265011 | 1153 | 0.69869 | 4(Loss) | true |
| glaze | 2408.38 | 1.08357 | 148.918ms | 3808 | 2560 | 683433 | 1507.9 | 1.52841 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 3933.7 | 2.18945 | 100.874ms | 3808 | 320 | 130741 | 923.2 | 2.12389 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 3804.71 | 0.915215 | 109.477ms | 3808 | 2560 | 195361 | 954.5 | 0.136012 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3598.13 | 0.749128 | 105.69ms | 3808 | 2560 | 146350 | 1009.3 | 0.0297324 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 3513.54 | 3.75011 | 105.523ms | 3808 | 80 | 120194 | 1033.6 | 0.9375 | 3(Tie) | true |
| glaze | 2498.34 | 1.37137 | 159.093ms | 3808 | 640 | 254318 | 1453.6 | 1.88985 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1685.94 | 0.871647 | 163.167ms | 2889 | 1280 | 259718 | 1634.2 | 1.0762 | 1(Win) | true |
| glaze | 1508.6 | 0.818916 | 196.842ms | 2889 | 2560 | 572615 | 1826.3 | 3.42621 | 2(Loss) | true |
| jsonifier (two-stage) | 1408.78 | 0.663109 | 193.143ms | 2889 | 4890 | 822402 | 1955.7 | 0.68536 | 3(Loss) | true |
| simdjson (reflection) | 1083.53 | 0.433522 | 280.19ms | 2889 | 4890 | 594219 | 2542.78 | 3.00062 | 4(Loss) | true |
| simdjson (ondemand) | 734.632 | 2.909 | 310.47ms | 2889 | 160 | 1.90442e+06 | 3750.4 | 0.687285 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1799.8 | 0.932926 | 170.762ms | 2889 | 4890 | 997356 | 1530.82 | 0.311463 | 1(Win) | true |
| jsonifier (two-stage) | 1691.29 | 0.65292 | 189.578ms | 2889 | 4890 | 553205 | 1629.03 | 1.18821 | 2(Loss) | true |
| simdjson (reflection) | 1469.89 | 1.5471 | 245.258ms | 2889 | 320 | 269098 | 1874.4 | 2.49344 | 3(Loss) | true |
| simdjson (ondemand) | 1064.39 | 0.526402 | 292.275ms | 2889 | 2560 | 475303 | 2588.5 | 0.508659 | 4(Loss) | true |
| glaze | 1013.67 | 0.488867 | 291.737ms | 2889 | 1280 | 225990 | 2718 | 1.25168 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11101.6 | 2.45736 | 32.352ms | 2963 | 4890 | 191311 | 254.534 | 3.21742 | 1(Win) | true |
| simdjson (reflection) DID NOT CONVERGE | 7583.03 | 1.89991 | 39.4529ms | 2963 | 4890 | 245105 | 372.64 | 5.38452 | -(Loss) | false |
| glaze | 2535.66 | 2.40096 | 104.955ms | 2963 | 320 | 229088 | 1114.4 | 1.23547 | 3(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12275.6 | 2.66742 | 26.8452ms | 2963 | 4890 | 184360 | 230.191 | 3.80669 | 1(Win) | true |
| simdjson (reflection) | 8276.91 | 2.75906 | 36.47ms | 2963 | 2560 | 227138 | 341.4 | 1.04348 | 2(Loss) | true |
| glaze | 3406.14 | 1.8215 | 94.6721ms | 2963 | 640 | 146143 | 829.6 | 0.288462 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 1863.12 | 0.495449 | 209.191ms | 3808 | 2560 | 238754 | 1949.2 | 1.10604 | 1(Win) | true |
| jsonifier STATISTICAL TIE | 1649.52 | 4.18008 | 223.613ms | 3808 | 40 | 338771 | 2201.6 | 1.14943 | 2(Tie) | true |
| glaze STATISTICAL TIE | 1638.61 | 0.370616 | 242.589ms | 3808 | 4890 | 329913 | 2216.26 | 0.0154071 | 2(Tie) | true |
| simdjson (reflection) | 1278.73 | 0.904529 | 310.409ms | 3808 | 1280 | 844679 | 2840 | 2.61598 | 4(Loss) | true |
| simdjson (ondemand) | 1169.07 | 1.04686 | 317.348ms | 3808 | 320 | 338409 | 3106.4 | 1.59655 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 2223.2 | 0.683524 | 197.263ms | 3808 | 2560 | 319143 | 1633.5 | 1.53707 | 1(Win) | true |
| jsonifier | 2045.28 | 0.956612 | 214.568ms | 3808 | 640 | 184647 | 1775.6 | 1.99908 | 2(Loss) | true |
| glaze | 1846.82 | 1.11553 | 204.638ms | 3808 | 320 | 153976 | 1966.4 | 0.244698 | 3(Loss) | true |
| simdjson (reflection) | 1373.52 | 2.01167 | 283.285ms | 3808 | 320 | 905290 | 2644 | 0.273058 | 4(Loss) | true |
| simdjson (ondemand) | 1113.17 | 1.2567 | 312.646ms | 3808 | 160 | 268942 | 3262.4 | 0.147348 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10518.6 | 2.22826 | 41.034ms | 4300 | 4890 | 369033 | 389.863 | 0.350938 | 1(Win) | true |
| glaze | 2403.19 | 0.826511 | 166.489ms | 4300 | 1280 | 254606 | 1706.4 | 2.53598 | 2(Loss) | true |
| simdjson (reflection) | 328.666 | 0.39056 | 1207.2ms | 4300 | 2560 | 6.07915e+06 | 12477.1 | 3.99317 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11352.4 | 1.94438 | 38.0751ms | 4300 | 4890 | 241230 | 361.227 | 0.648368 | 1(Win) | true |
| glaze | 2862.79 | 0.526254 | 138.693ms | 4300 | 4890 | 277880 | 1432.45 | 1.9246 | 2(Loss) | true |
| simdjson (reflection) | 337.051 | 0.320355 | 1239.73ms | 4300 | 2560 | 3.88909e+06 | 12166.7 | 2.53541 | 3(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1873.17 | 0.615773 | 6038.76ms | 466906 | 320 | 6.8564e+08 | 237713 | 1.05531 | 1(Win) | true |
| glaze | 1359.75 | 0.70277 | 8524.94ms | 466906 | 160 | 8.47395e+08 | 327469 | 0.00488572 | 2(Loss) | true |
| simdjson (ondemand) | 782.74 | 0.584645 | 7485.92ms | 466906 | 160 | 1.76982e+09 | 568869 | 0.190776 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1852.24 | 0.395489 | 6037.36ms | 466906 | 1280 | 1.15703e+09 | 240399 | 0.474611 | 1(Win) | true |
| glaze | 1262.73 | 0.453303 | 8675.29ms | 466906 | 160 | 4.08821e+08 | 352629 | 0.42245 | 2(Loss) | true |
| simdjson (ondemand) | 732.275 | 0.443074 | 7504.27ms | 466906 | 320 | 2.32281e+09 | 608073 | 1.61264 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2820.91 | 0.446134 | 6167.82ms | 699405 | 640 | 7.1218e+08 | 236450 | 1.73235 | 1(Win) | true |
| glaze | 2008.83 | 0.61338 | 8364.71ms | 699405 | 320 | 1.32733e+09 | 332036 | 0.201739 | 2(Loss) | true |
| simdjson (ondemand) | 644.59 | 0.601028 | 7375.38ms | 767297 | 160 | 7.44849e+09 | 1.13522e+06 | 2.92705 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2590.12 | 0.597453 | 6215.49ms | 699405 | 320 | 7.57484e+08 | 257518 | 2.65718 | 1(Win) | true |
| glaze | 2044.17 | 0.51483 | 8441.38ms | 699405 | 320 | 9.03029e+08 | 326296 | 0.492815 | 2(Loss) | true |
| simdjson (ondemand) | 610.765 | 0.893363 | 7411.44ms | 767297 | 80 | 9.16483e+09 | 1.19809e+06 | 2.18693 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1987.13 | 0.250746 | 7575.52ms | 631514 | 1280 | 7.39248e+08 | 303080 | 0.928867 | 1(Win) | true |
| glaze | 1822.51 | 0.276475 | 8485.51ms | 631514 | 640 | 5.34218e+08 | 330456 | 0.0219043 | 2(Loss) | true |
