# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest Results: (Nov 18, 2026)
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
*Environment generated via BenchmarkSuite commit: [71afc62](https://github.com/nihilai-collective/benchmarksuite/commit/71afc62)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1623.54 | 2.6417 | 57.236ms | 905 | 1280 | 252434 | 531.6 | 0.746826 | 1(Win) | true |
| Glaze | 1338.52 | 2.19577 | 68.3958ms | 905 | 1280 | 256587 | 644.8 | 0.123916 | 2(Loss) | true |
| Jsonifier (two-stage) | 351.072 | 0.873437 | 264.897ms | 905 | 640 | 295086 | 2458.4 | 1.50641 | 3(Loss) | true |
| simdjson (ondemand) | 164.726 | 2.60586 | 533.283ms | 905 | 30 | 559241 | 5239.47 | 0 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1817.77 | 2.0907 | 50.985ms | 905 | 2560 | 252257 | 474.8 | 0.978307 | 1(Win) | true |
| Glaze | 1601.25 | 1.84014 | 59.66ms | 905 | 2560 | 251837 | 539 | 0.22214 | 2(Loss) | true |
| Jsonifier (two-stage) | 344.899 | 3.3066 | 256.519ms | 905 | 40 | 273865 | 2502.4 | 0.0853242 | 3(Loss) | true |
| simdjson (ondemand) | 154.402 | 0.350695 | 537.347ms | 905 | 4890 | 1.87915e+06 | 5589.8 | 1.06541 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1742.53 | 2.0052 | 52.9009ms | 905 | 2560 | 252517 | 495.3 | 0.78125 | 1(Win) | true |
| simdjson (reflection) | 207.191 | 0.791526 | 422.582ms | 905 | 320 | 347885 | 4165.6 | 0.401683 | 2(Loss) | true |
| Glaze | 117.534 | 0.641381 | 760.499ms | 905 | 320 | 709827 | 7343.2 | 1.20176 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3146.46 | 3.2479 | 36.894ms | 905 | 2560 | 203188 | 274.3 | 2.19821 | 1(Win) | true |
| simdjson (reflection) | 2470.2 | 1.96145 | 46.3508ms | 905 | 4890 | 229666 | 349.396 | 1.43992 | 2(Loss) | true |
| Glaze | 808.123 | 0.985364 | 125.611ms | 905 | 640 | 70878.7 | 1068 | 1.52091 | 3(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 905.832 | 0.281507 | 195.128ms | 1811 | 4890 | 140874 | 1906.65 | 0.117853 | 1(Win) | true |
| Glaze | 758.906 | 0.422084 | 219.685ms | 1811 | 4890 | 451200 | 2275.78 | 0.560062 | 2(Loss) | true |
| Jsonifier (two-stage) | 476.785 | 0.767769 | 379.555ms | 1811 | 320 | 247517 | 3622.4 | 0.221337 | 3(Loss) | true |
| simdjson (ondemand) | 137.202 | 0.636889 | 1256.48ms | 1811 | 320 | 2.05679e+06 | 12588 | 0.108156 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1075.47 | 0.646484 | 163.769ms | 1811 | 2560 | 275926 | 1605.9 | 0.180911 | 1(Win) | true |
| Glaze | 814.979 | 1.46934 | 190.797ms | 1811 | 320 | 310268 | 2119.2 | 0.637659 | 2(Loss) | true |
| Jsonifier (two-stage) | 507.733 | 1.66244 | 361.715ms | 1811 | 80 | 255829 | 3401.6 | 0.093985 | 3(Loss) | true |
| simdjson (ondemand) | 139.944 | 0.328376 | 1247.18ms | 1811 | 1280 | 2.10224e+06 | 12341.4 | 0.507884 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 276.494 | 1.28806 | 687.724ms | 1997 | 160 | 1.25944e+06 | 6888 | 2.99043 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 255.791 | 1.89907 | 696.136ms | 1811 | 40 | 657671 | 6752 | 0.094697 | 1(Tie) | true |
| Glaze | 196.903 | 0.203481 | 888.117ms | 1798 | 2560 | 803827 | 8708.4 | 0.214044 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 864.936 | 1.7897 | 229.086ms | 1811 | 40 | 51084.5 | 1996.8 | 1.73913 | 1(Win) | true |
| simdjson (reflection) | 652.065 | 0.297694 | 296.986ms | 1997 | 4890 | 369677 | 2920.7 | 2.25121 | 2(Loss) | true |
| Glaze | 645.505 | 0.316502 | 284.685ms | 1798 | 4890 | 345654 | 2656.38 | 0.184889 | 3(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2395.31 | 0.482809 | 159.969ms | 3862 | 4890 | 269501 | 1537.62 | 0.485094 | 1(Win) | true |
| Glaze | 1133.83 | 0.418309 | 295.495ms | 3862 | 4890 | 902891 | 3248.37 | 0.0515294 | 2(Loss) | true |
| Jsonifier (two-stage) | 830.741 | 0.430118 | 452.882ms | 3862 | 2560 | 930912 | 4433.5 | 1.60023 | 3(Loss) | true |
| simdjson (ondemand) | 406.421 | 0.211946 | 879.324ms | 3862 | 4890 | 1.80398e+06 | 9062.24 | 0.31374 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3114.93 | 0.932051 | 127.12ms | 3862 | 1280 | 155460 | 1182.4 | 0.578428 | 1(Win) | true |
| Glaze | 1431.38 | 0.487463 | 261.086ms | 3862 | 2560 | 402751 | 2573.1 | 0.0116577 | 2(Loss) | true |
| Jsonifier (two-stage) | 886.232 | 0.318728 | 417.36ms | 3862 | 2560 | 449170 | 4155.9 | 0.136967 | 3(Loss) | true |
| simdjson (ondemand) | 440.477 | 1.013 | 873.308ms | 3862 | 80 | 573969 | 8361.6 | 0.114679 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 751.436 | 0.417403 | 502.449ms | 3862 | 1280 | 535749 | 4901.4 | 0.0693198 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 749.022 | 0.385729 | 498.342ms | 3862 | 1280 | 460480 | 4917.2 | 0.236464 | 1(Tie) | true |
| Glaze | 515.991 | 0.247682 | 725.634ms | 3862 | 2560 | 800149 | 7137.9 | 0.163646 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5052.25 | 1.73392 | 85.8301ms | 3862 | 1280 | 204514 | 729 | 0.690608 | 1(Win) | true |
| simdjson (reflection) | 3155.4 | 0.483884 | 127.345ms | 3862 | 4890 | 155994 | 1167.23 | 0.116862 | 2(Loss) | true |
| Glaze | 2252.24 | 0.625951 | 178.082ms | 3862 | 2560 | 268235 | 1635.3 | 0.177653 | 3(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1245.47 | 0.469158 | 756.941ms | 9578 | 640 | 757705 | 7334 | 0.0381638 | 1(Win) | true |
| Glaze | 1099.14 | 0.664278 | 918.385ms | 9578 | 80 | 243800 | 8310.4 | 0.19216 | 2(Loss) | true |
| simdjson (ondemand) | 690.277 | 0.34831 | 1363.29ms | 9578 | 640 | 1.35961e+06 | 13232.8 | 0.451372 | 3(Loss) | true |
| Jsonifier (two-stage) | 677.771 | 0.215463 | 1346.69ms | 9578 | 4890 | 4.12324e+06 | 13477 | 3.30181 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2027.14 | 0.926128 | 716.714ms | 9578 | 640 | 1.11456e+06 | 4506 | 3.18838 | 1(Win) | true |
| Glaze | 1590.83 | 0.205379 | 844.256ms | 9578 | 4890 | 680023 | 5741.83 | 1.37956 | 2(Loss) | true |
| simdjson (ondemand) | 910.398 | 0.225717 | 1293.17ms | 9578 | 2560 | 1.31298e+06 | 10033.3 | 0.260812 | 3(Loss) | true |
| Jsonifier (two-stage) | 898.85 | 0.311431 | 1295.79ms | 9578 | 1280 | 1.28207e+06 | 10162.2 | 0.51632 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1260.59 | 0.246953 | 726.037ms | 9578 | 4890 | 1.56582e+06 | 7246.06 | 0.661387 | 1(Win) | true |
| simdjson (reflection) | 1147.46 | 0.244798 | 791.554ms | 9578 | 4890 | 1.85694e+06 | 7960.45 | 1.46375 | 2(Loss) | true |
| Glaze | 1056.6 | 0.307464 | 880.411ms | 9578 | 1280 | 904336 | 8645 | 0.581903 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 10130.6 | 0.566574 | 103.998ms | 9578 | 4890 | 127615 | 901.654 | 0.384546 | 1(Win) | true |
| Jsonifier | 9040.27 | 1.11048 | 113.254ms | 9578 | 320 | 40286.5 | 1010.4 | 0.394322 | 2(Loss) | true |
| Glaze | 4600.27 | 1.07478 | 213.189ms | 9578 | 640 | 291474 | 1985.6 | 2.39274 | 3(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2356.49 | 0.476096 | 161.844ms | 3873 | 4890 | 272310 | 1567.41 | 0.437589 | 1(Win) | true |
| Glaze | 1438.53 | 0.905407 | 257.419ms | 3873 | 640 | 345878 | 2567.6 | 0.10917 | 2(Loss) | true |
| Jsonifier (two-stage) | 829.049 | 0.839134 | 453.543ms | 3873 | 320 | 447247 | 4455.2 | 0.836895 | 3(Loss) | true |
| simdjson (ondemand) | 413.041 | 0.349193 | 906.018ms | 3873 | 1280 | 1.2481e+06 | 8942.4 | 0.943694 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2813.73 | 0.723208 | 133.543ms | 3873 | 2560 | 230726 | 1312.7 | 2.45863 | 1(Win) | true |
| Glaze | 1519.49 | 0.3712 | 240.677ms | 3873 | 4890 | 398127 | 2430.8 | 0.787624 | 2(Loss) | true |
| Jsonifier (two-stage) | 829.235 | 0.309147 | 455.497ms | 3873 | 2560 | 485412 | 4454.2 | 0.355984 | 3(Loss) | true |
| simdjson (ondemand) | 422.645 | 0.224232 | 887.808ms | 3873 | 2560 | 983055 | 8739.2 | 0.231678 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 750.057 | 0.589988 | 502.018ms | 3873 | 640 | 540223 | 4924.4 | 0.629393 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 743.894 | 0.214324 | 500.863ms | 3873 | 4890 | 553764 | 4965.2 | 0.826397 | 1(Tie) | true |
| Glaze | 514.049 | 0.188986 | 719.535ms | 3873 | 4890 | 901683 | 7185.28 | 0.707855 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5046 | 0.889112 | 85.7971ms | 3873 | 4890 | 207120 | 731.982 | 0.464781 | 1(Win) | true |
| simdjson (reflection) | 3108.48 | 0.481451 | 129.752ms | 3873 | 4890 | 160034 | 1188.23 | 2.12526 | 2(Loss) | true |
| Glaze | 2415.05 | 0.961706 | 165.719ms | 3873 | 1280 | 276909 | 1529.4 | 3.75848 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 985.084 | 0.381577 | 9261.31ms | 94653 | 2560 | 3.12988e+08 | 91635 | 1.69576 | 1(Win) | true |
| Glaze | 927.782 | 0.173873 | 9250.23ms | 94653 | 4890 | 1.39942e+08 | 97294.5 | 0.271117 | 2(Loss) | true |
| Jsonifier (two-stage) | 790.29 | 0.275634 | 5891.78ms | 94653 | 2560 | 2.53747e+08 | 114222 | 0.296175 | 3(Loss) | true |
| simdjson (reflection) | 772.031 | 0.256268 | 6055.31ms | 94653 | 2560 | 2.29842e+08 | 116923 | 0.557732 | 4(Loss) | true |
| simdjson (ondemand) | 628.022 | 0.527942 | 7635.09ms | 94653 | 640 | 3.68528e+08 | 143734 | 1.82923 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1757.54 | 0.291714 | 7571.89ms | 94653 | 2560 | 5.74665e+07 | 51360.6 | 0.152802 | 1(Win) | true |
| Glaze | 1384.37 | 0.212172 | 8823.22ms | 94653 | 4890 | 9.35951e+07 | 65205.3 | 0.300379 | 2(Loss) | true |
| Jsonifier (two-stage) | 1150.54 | 0.400204 | 5032.9ms | 94653 | 1280 | 1.26195e+08 | 78457.4 | 0.155485 | 3(Loss) | true |
| simdjson (reflection) | 979.436 | 0.426579 | 5865.94ms | 94653 | 1280 | 1.97846e+08 | 92163.4 | 0.129285 | 4(Loss) | true |
| simdjson (ondemand) | 757.507 | 0.96138 | 7031.74ms | 94653 | 160 | 2.09994e+08 | 119165 | 2.80576 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10990.9 | 0.632661 | 902.814ms | 94653 | 1280 | 3.45585e+06 | 8213 | 1.31001 | 1(Win) | true |
| simdjson (reflection) | 7970.3 | 0.234193 | 1166.75ms | 94653 | 4890 | 3.44014e+06 | 11325.6 | 1.83692 | 2(Loss) | true |
| Glaze | 4085.44 | 0.323057 | 2195.37ms | 94653 | 4890 | 2.49149e+07 | 22095.1 | 1.23712 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10995.4 | 0.968475 | 839.13ms | 94653 | 320 | 2.02288e+06 | 8209.6 | 0.195274 | 1(Win) | true |
| simdjson (reflection) | 8541.32 | 0.502709 | 1104.11ms | 94653 | 640 | 1.80648e+06 | 10568.4 | 1.45534 | 2(Loss) | true |
| Glaze | 5096.93 | 0.273966 | 1745.52ms | 94653 | 4890 | 1.15121e+07 | 17710.3 | 0.300732 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1216.29 | 0.357756 | 5168.38ms | 124597 | 1280 | 1.5636e+08 | 97694.8 | 0.69179 | 1(Win) | true |
| Glaze | 1198.76 | 0.502957 | 5616.69ms | 124597 | 40 | 9.94198e+06 | 99123.2 | 0.445663 | 2(Loss) | true |
| Jsonifier (two-stage) | 1054.13 | 0.268302 | 5809.7ms | 124597 | 2560 | 2.34159e+08 | 112723 | 0.333695 | 3(Loss) | true |
| simdjson (reflection) | 1006.77 | 0.355609 | 6043.28ms | 124597 | 1280 | 2.25483e+08 | 118026 | 0.712338 | 4(Loss) | true |
| simdjson (ondemand) | 828.379 | 0.410805 | 7466.98ms | 124597 | 1280 | 4.44466e+08 | 143443 | 0.0714383 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1857.14 | 0.341196 | 8790.68ms | 124597 | 1280 | 6.10021e+07 | 63982.8 | 0.926247 | 1(Win) | true |
| Jsonifier (two-stage) | 1558.65 | 0.333673 | 5199.52ms | 124597 | 2560 | 1.65653e+08 | 76235.8 | 1.11986 | 2(Loss) | true |
| Glaze | 1431.38 | 1.41563 | 5082.59ms | 124597 | 40 | 5.52418e+07 | 83014.4 | 1.07273 | 3(Loss) | true |
| simdjson (reflection) | 1241.99 | 0.407768 | 6093.56ms | 124597 | 1280 | 1.94812e+08 | 95673 | 0.822191 | 4(Loss) | true |
| simdjson (ondemand) | 1041.38 | 0.514167 | 7188.52ms | 124597 | 640 | 2.20286e+08 | 114104 | 0.196976 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12330.5 | 0.299863 | 1089.25ms | 136037 | 2560 | 2.54824e+06 | 10521.5 | 0.48709 | 1(Win) | true |
| Glaze | 3616.23 | 0.650831 | 3523.68ms | 136076 | 640 | 3.49113e+07 | 35886 | 0.032335 | 2(Loss) | true |
| simdjson (reflection) | 314.039 | 0.446332 | 5256.6ms | 136037 | 640 | 2.17592e+09 | 413117 | 3.71689 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12524.8 | 0.215934 | 1040.23ms | 136037 | 4890 | 2.44639e+06 | 10358.3 | 0.805729 | 1(Win) | true |
| Glaze | 4578.13 | 0.312607 | 2894.82ms | 136076 | 2560 | 2.01013e+07 | 28346.1 | 2.41161 | 2(Loss) | true |
| simdjson (reflection) | 313.701 | 0.669285 | 5151.43ms | 136037 | 320 | 2.45164e+09 | 413563 | 0.0836363 | 3(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 634.053 | 1.23588 | 5140.63ms | 2251027 | 40 | 7.00369e+10 | 3.38575e+06 | 0.302784 | 1(Win) | true |
| Glaze | 543.334 | 1.70921 | 5730.33ms | 2251027 | 40 | 1.82422e+11 | 3.95106e+06 | 1.32567 | 2(Loss) | true |
| Jsonifier (two-stage) | 519.35 | 1.45711 | 6553.44ms | 2251027 | 30 | 1.08829e+11 | 4.13353e+06 | 0.321015 | 3(Loss) | true |
| simdjson (reflection) | 499.003 | 1.08885 | 6228.7ms | 2251027 | 30 | 6.58285e+10 | 4.30207e+06 | 1.56416 | 4(Loss) | true |
| simdjson (ondemand) | 464.659 | 1.53431 | 6819.23ms | 2251027 | 40 | 2.00993e+11 | 4.62004e+06 | 0.44293 | 5(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 759.585 | 0.950908 | 5219.03ms | 2251027 | 80 | 5.77799e+10 | 2.82621e+06 | 0.436115 | 1(Win) | true |
| simdjson (reflection) | 681.634 | 0.774127 | 5967.64ms | 2251027 | 30 | 1.78322e+10 | 3.14941e+06 | 3.36279 | 2(Loss) | true |
| Glaze | 631.996 | 1.43557 | 6229.62ms | 2251027 | 30 | 7.1335e+10 | 3.39677e+06 | 1.35072 | 3(Loss) | true |
| simdjson (ondemand) | 551.576 | 0.759033 | 6675.45ms | 2251027 | 80 | 6.98172e+10 | 3.89203e+06 | 3.86153 | 4(Loss) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 505.295 | 1.10739 | 6471.4ms | 2251027 | 40 | 8.85386e+10 | 4.24851e+06 | 12.7779 | -(Loss) | false |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2039.76 | 1.03048 | 6100.65ms | 2090234 | 80 | 8.11343e+09 | 977274 | 0.268434 | 1(Win) | true |
| Glaze | 1419.1 | 0.873691 | 8647.19ms | 2090234 | 80 | 1.20495e+10 | 1.40469e+06 | 2.75397 | 2(Loss) | true |
| simdjson (reflection) | 745.51 | 0.613868 | 8736.91ms | 2090326 | 160 | 4.31114e+10 | 2.674e+06 | 3.00174 | 3(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1927.77 | 1.31758 | 5994.55ms | 2090234 | 40 | 7.42498e+09 | 1.03405e+06 | 1.24968 | 1(Win) | true |
| Glaze | 1536.14 | 1.21012 | 8204.72ms | 2090234 | 40 | 9.86383e+09 | 1.29767e+06 | 0.389323 | 2(Loss) | true |
| simdjson (reflection) | 700.758 | 1.15567 | 8602.45ms | 2090326 | 40 | 4.32333e+10 | 2.84476e+06 | 0.415668 | 3(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 1164.88 | 1.01206 | 6822.36ms | 5373214 | 80 | 1.58565e+11 | 4.39898e+06 | 0.839251 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 1098.26 | 1.07802 | 6851.98ms | 5373214 | 40 | 1.01197e+11 | 4.66582e+06 | 0.617035 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1086.59 | 0.659052 | 6650ms | 5373214 | 80 | 7.72806e+10 | 4.71596e+06 | 0.820113 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1012.91 | 1.27826 | 7399.96ms | 5373214 | 30 | 1.25454e+11 | 5.059e+06 | 0.91141 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1012.65 | 1.17407 | 7399.11ms | 5373214 | 40 | 1.41188e+11 | 5.06029e+06 | 1.65985 | 4(Tie) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) DID NOT CONVERGE | 1463.12 | 1.34522 | 6764.17ms | 5373214 | 30 | 6.65915e+10 | 3.50231e+06 | 5.33996 | -(Win) | false |
| Jsonifier (two-stage) | 1339.11 | 1.14998 | 6815.02ms | 5373214 | 30 | 5.80948e+10 | 3.82664e+06 | 0.345564 | 2(Loss) | true |
| Jsonifier | 1268.23 | 0.915098 | 6703.11ms | 5373214 | 80 | 1.0937e+11 | 4.04051e+06 | 1.22351 | 3(Loss) | true |
| Glaze STATISTICAL TIE | 1176.48 | 0.86162 | 7802.11ms | 5373214 | 80 | 1.12674e+11 | 4.35563e+06 | 1.51796 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1149.39 | 1.61165 | 7293.62ms | 5373214 | 40 | 2.06509e+11 | 4.45828e+06 | 0.95383 | 4(Tie) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7284.51 | 0.105005 | 5794.69ms | 6661897 | 80 | 6.70972e+07 | 872163 | 1.63384 | 1(Win) | true |
| Glaze | 3129.3 | 0.966025 | 6416.97ms | 6661897 | 80 | 3.07728e+10 | 2.03025e+06 | 1.89786 | 2(Loss) | true |
| simdjson (reflection) | 269.097 | 1.11347 | 7403.76ms | 6661989 | 30 | 2.07332e+12 | 2.36099e+07 | 4.04585 | 3(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7690.42 | 1.6626 | 6199.69ms | 6661897 | 30 | 5.65969e+09 | 826129 | 2.76082 | 1(Win) | true |
| Glaze | 3287.1 | 1.45319 | 5836.27ms | 6661897 | 30 | 2.36667e+10 | 1.93279e+06 | 1.45148 | 2(Loss) | true |
| simdjson (reflection) | 247.806 | 1.0888 | 7372.22ms | 6661989 | 30 | 2.33778e+12 | 2.56385e+07 | 1.54111 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1825.77 | 0.29897 | 6999.72ms | 500299 | 1280 | 7.81323e+08 | 261326 | 1.88664 | 1(Win) | true |
| Glaze | 1194.59 | 1.22941 | 5355.29ms | 500299 | 30 | 7.23328e+08 | 399403 | 0.766432 | 2(Loss) | true |
| Jsonifier (two-stage) | 1101.38 | 2.01838 | 5052.17ms | 500299 | 40 | 3.05808e+09 | 433203 | 0.182858 | 3(Loss) | true |
| simdjson (ondemand) | 987.16 | 0.489708 | 6072.5ms | 500299 | 640 | 3.58541e+09 | 483328 | 0.499348 | 4(Loss) | true |
| simdjson (reflection) | 885.881 | 0.474089 | 6502.51ms | 500299 | 640 | 4.17262e+09 | 538585 | 1.53081 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2405.01 | 1.24787 | 6683.22ms | 500299 | 40 | 2.45148e+08 | 198387 | 0.736519 | 1(Win) | true |
| Glaze | 1436.49 | 0.203718 | 5188.23ms | 500299 | 80 | 3.66269e+07 | 332144 | 2.86278 | 2(Loss) | true |
| Jsonifier (two-stage) | 1316.84 | 1.97571 | 10102ms | 500299 | 40 | 2.04975e+09 | 362323 | 2.11234 | 3(Loss) | true |
| simdjson (reflection) | 1164.73 | 0.632596 | 6416.01ms | 500299 | 30 | 2.01458e+08 | 409643 | 1.88444 | 4(Loss) | true |
| simdjson (ondemand) | 1047.94 | 0.386488 | 6103.07ms | 500299 | 640 | 1.98169e+09 | 455295 | 0.792536 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6848 | 0.644876 | 6921.36ms | 500299 | 1280 | 2.58401e+08 | 69673.2 | 1.04243 | 1(Win) | true |
| simdjson (reflection) DID NOT CONVERGE | 6285.22 | 0.523192 | 7169.92ms | 500299 | 1280 | 2.01907e+08 | 75911.8 | 6.4019 | -(Loss) | false |
| Glaze | 1732.12 | 0.518989 | 6787.84ms | 500299 | 40 | 8.17486e+07 | 275456 | 2.29729 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7844.62 | 0.693488 | 6547.28ms | 500299 | 320 | 5.69304e+07 | 60821.6 | 0.919903 | 1(Win) | true |
| simdjson (reflection) | 6806.62 | 0.632038 | 7451.38ms | 500299 | 640 | 1.25621e+08 | 70096.8 | 0.107165 | 2(Loss) | true |
| Glaze | 1691.71 | 0.550014 | 6780.1ms | 500299 | 30 | 7.21897e+07 | 282035 | 0.129933 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2725.98 | 0.693357 | 5384.08ms | 1151920 | 40 | 3.12302e+08 | 402995 | 1.3564 | 1(Win) | true |
| Jsonifier (two-stage) | 2303.5 | 0.485764 | 6458.2ms | 1151920 | 640 | 3.43479e+09 | 476908 | 2.3041 | 2(Loss) | true |
| simdjson (ondemand) | 1965.48 | 0.266709 | 7384.71ms | 1151920 | 40 | 8.88877e+07 | 558925 | 0.652217 | 3(Loss) | true |
| simdjson (reflection) | 1887.03 | 1.39832 | 7593.5ms | 1151920 | 30 | 1.98803e+09 | 582161 | 1.5571 | 4(Loss) | true |
| Glaze | 1595.75 | 0.724038 | 8446.43ms | 1151920 | 320 | 7.95041e+09 | 688428 | 0.802653 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3138.53 | 0.266948 | 5107.21ms | 1151920 | 320 | 2.79381e+08 | 350022 | 0.22357 | 1(Win) | true |
| Jsonifier (two-stage) | 2727.97 | 0.343385 | 5863.95ms | 1151920 | 320 | 6.11898e+08 | 402702 | 3.53214 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 2152.83 | 0.395598 | 7520.65ms | 1151920 | 160 | 6.52009e+08 | 510285 | 0.535793 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2137.41 | 0.434397 | 7207.77ms | 1151920 | 160 | 7.97559e+08 | 513966 | 1.03765 | 3(Tie) | true |
| Glaze | 1943.93 | 0.114055 | 7905.28ms | 1151920 | 640 | 2.65883e+08 | 565121 | 0.0398657 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 18240.8 | 0.419033 | 7740.19ms | 1439562 | 80 | 7.95723e+06 | 75264 | 0.213038 | 1(Win) | true |
| Glaze | 3406.75 | 0.41944 | 5344.57ms | 1439584 | 640 | 1.82858e+09 | 402993 | 0.739133 | 2(Loss) | true |
| simdjson (reflection) | 299.97 | 1.89849 | 7222.07ms | 1439562 | 30 | 2.26488e+11 | 4.5767e+06 | 2.72333 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15286.7 | 0.305352 | 8425.58ms | 1439562 | 4890 | 3.67741e+08 | 89808.1 | 0.483349 | 1(Win) | true |
| Glaze | 4085.12 | 0.153521 | 8815.39ms | 1439584 | 1280 | 3.40731e+08 | 336072 | 0.769756 | 2(Loss) | true |
| simdjson (reflection) | 272.449 | 1.01278 | 7241.87ms | 1439562 | 30 | 7.81341e+10 | 5.039e+06 | 0.23686 | 3(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1604.27 | 0.200887 | 3386.56ms | 56369 | 2560 | 1.16003e+07 | 33509.1 | 2.10948 | 1(Win) | true |
| Glaze | 1219.06 | 0.207272 | 4411.96ms | 56369 | 4890 | 4.08525e+07 | 44097.5 | 0.648763 | 2(Loss) | true |
| Jsonifier (two-stage) | 1102.75 | 1.52941 | 5115.92ms | 56369 | 40 | 2.22348e+07 | 48748.8 | 0.370596 | 3(Loss) | true |
| simdjson (reflection) | 1014.82 | 0.619443 | 5556.38ms | 56369 | 80 | 8.61388e+06 | 52972.8 | 0.132722 | 4(Loss) | true |
| simdjson (ondemand) | 881.678 | 0.456564 | 6616.96ms | 56369 | 640 | 4.95958e+07 | 60972 | 1.38209 | 5(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2282.96 | 0.253821 | 2990.88ms | 56369 | 1280 | 4.57249e+06 | 23547.4 | 1.69554 | 1(Win) | true |
| Glaze | 1720.52 | 0.277879 | 3689.1ms | 56369 | 4890 | 3.6862e+07 | 31244.9 | 0.25133 | 2(Loss) | true |
| Jsonifier (two-stage) | 1363.95 | 0.298741 | 4718.21ms | 56369 | 2560 | 3.54909e+07 | 39413.3 | 0.532335 | 3(Loss) | true |
| simdjson (reflection) | 1134.56 | 0.256649 | 5331.71ms | 56369 | 2560 | 3.78569e+07 | 47382 | 0.185801 | 4(Loss) | true |
| simdjson (ondemand) | 1083.54 | 0.147458 | 5600.84ms | 56369 | 2560 | 1.37016e+07 | 49613.2 | 0.244497 | 5(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11813.8 | 0.390788 | 526.638ms | 56369 | 1280 | 404755 | 4550.4 | 0.123218 | 1(Win) | true |
| simdjson (reflection) | 9095.74 | 0.27805 | 603.722ms | 56369 | 2560 | 691336 | 5910.2 | 0.0270792 | 2(Loss) | true |
| Glaze | 2943.11 | 0.285472 | 2220.46ms | 56369 | 80 | 217513 | 18265.6 | 0.210674 | 3(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 10922.8 | 1.99737 | 485.605ms | 56369 | 320 | 3.09227e+06 | 4921.6 | 0.291734 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 10529.2 | 0.521677 | 587.518ms | 56369 | 320 | 227011 | 5105.6 | 1.6242 | 1(Tie) | true |
| Glaze | 2705.48 | 0.228541 | 1938.32ms | 56369 | 4890 | 1.00839e+07 | 19869.9 | 1.30361 | 3(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1780.03 | 0.234481 | 4447.99ms | 83958 | 2560 | 2.84791e+07 | 44981.7 | 1.31835 | 1(Win) | true |
| Glaze | 1641.13 | 0.304727 | 5188.75ms | 83958 | 640 | 1.41463e+07 | 48788.8 | 0.423192 | 2(Loss) | true |
| Jsonifier (two-stage) | 1508.01 | 0.547389 | 5410.21ms | 83958 | 640 | 5.40616e+07 | 53095.6 | 0.680145 | 3(Loss) | true |
| simdjson (ondemand) | 1275.99 | 0.303298 | 7139.69ms | 83958 | 160 | 5.7955e+06 | 62750.4 | 0.0229533 | 4(Loss) | true |
| simdjson (reflection) | 1259.74 | 0.495054 | 6201.7ms | 83958 | 640 | 6.33647e+07 | 63559.6 | 0.850482 | 5(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2168.55 | 0.23961 | 4246.52ms | 83958 | 4890 | 3.82741e+07 | 36922.6 | 1.86791 | 1(Win) | true |
| Jsonifier (two-stage) | 1977.98 | 0.978467 | 4970.23ms | 83958 | 40 | 6.27528e+06 | 40480 | 0.716561 | 2(Loss) | true |
| Glaze | 1901.27 | 0.323887 | 4717.56ms | 83958 | 2560 | 4.76284e+07 | 42113.3 | 1.44971 | 3(Loss) | true |
| simdjson (reflection) | 1611.17 | 0.809086 | 6124.64ms | 83958 | 40 | 6.46685e+06 | 49696 | 1.8083 | 4(Loss) | true |
| simdjson (ondemand) | 1456.68 | 0.194885 | 6215.32ms | 83958 | 2560 | 2.9376e+07 | 54966.6 | 1.57328 | 5(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11173.8 | 0.555522 | 702.396ms | 94370 | 640 | 1.2813e+06 | 8054.4 | 0.962696 | 1(Win) | true |
| Glaze | 2160.51 | 1.09141 | 4406.14ms | 94370 | 160 | 3.30715e+07 | 41656 | 4.95445 | 2(Loss) | true |
| simdjson (reflection) | 309.782 | 0.320742 | 7803.37ms | 94370 | 1280 | 1.11141e+09 | 290521 | 1.06293 | 3(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15433.9 | 0.381105 | 667.25ms | 94370 | 320 | 158036 | 5831.2 | 0.640676 | 1(Win) | true |
| Glaze | 2699.08 | 0.263316 | 3772.32ms | 94370 | 40 | 308355 | 33344 | 3.70872 | 2(Loss) | true |
| simdjson (reflection) | 305.742 | 0.692841 | 7353.57ms | 94370 | 320 | 1.33099e+09 | 294360 | 2.53931 | 3(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1448.73 | 0.290446 | 3522.7ms | 53331 | 2560 | 2.6617e+07 | 35107 | 1.0234 | 1(Win) | true |
| Glaze | 1301.6 | 0.226854 | 4032.6ms | 53331 | 4890 | 3.84243e+07 | 39075.2 | 1.7477 | 2(Loss) | true |
| simdjson (reflection) | 1131.36 | 0.436044 | 5045.2ms | 53331 | 160 | 6.1481e+06 | 44955.2 | 0.210429 | 3(Loss) | true |
| Jsonifier (two-stage) | 1066.85 | 0.710985 | 4341.89ms | 53331 | 160 | 1.83822e+07 | 47673.6 | 0.314486 | 4(Loss) | true |
| simdjson (ondemand) | 789.228 | 0.821819 | 6321.39ms | 53331 | 320 | 8.97545e+07 | 64443.2 | 2.05752 | 5(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1962.72 | 0.258638 | 3358.74ms | 53331 | 4890 | 2.19654e+07 | 25913.3 | 0.825932 | 1(Win) | true |
| Glaze | 1682.2 | 0.43603 | 3801.11ms | 53331 | 1280 | 2.22457e+07 | 30234.4 | 1.01751 | 2(Loss) | true |
| Jsonifier (two-stage) | 1556.14 | 0.243467 | 4123.38ms | 53331 | 4890 | 3.09636e+07 | 32683.7 | 3.14961 | 3(Loss) | true |
| simdjson (reflection) | 1241.98 | 0.231942 | 4827.61ms | 53331 | 4890 | 4.41163e+07 | 40951.1 | 2.03085 | 4(Loss) | true |
| simdjson (ondemand) | 1076.76 | 0.196049 | 5692.43ms | 53331 | 4890 | 4.19331e+07 | 47234.5 | 2.09135 | 5(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12423 | 2.58477 | 465.732ms | 58581 | 30 | 405344 | 4497.07 | 2.3301 | 1(Win) | true |
| simdjson (reflection) | 11120.1 | 0.419083 | 552.567ms | 58581 | 80 | 35464.1 | 5024 | 0 | 2(Loss) | true |
| Glaze | 2920.46 | 0.758151 | 1812.72ms | 58581 | 640 | 1.34618e+07 | 19129.6 | 0.862355 | 3(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15177.6 | 0.36209 | 384.829ms | 58581 | 4890 | 868662 | 3680.9 | 1.58539 | 1(Win) | true |
| simdjson (reflection) | 10790.9 | 0.366495 | 551.699ms | 58581 | 4890 | 1.76055e+06 | 5177.27 | 0.393112 | 2(Loss) | true |
| Glaze | 3754.27 | 0.418634 | 1497.05ms | 58581 | 4890 | 1.89776e+07 | 14881 | 2.28588 | 3(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1595.58 | 0.374016 | 4449.29ms | 65103 | 320 | 6.77794e+06 | 38912 | 2.1997 | 1(Win) | true |
| Glaze | 1523.1 | 0.883884 | 4463.32ms | 65103 | 30 | 3.89457e+06 | 40763.7 | 0.644759 | 2(Loss) | true |
| Jsonifier (two-stage) | 1359.7 | 0.440955 | 4627.95ms | 65103 | 1280 | 5.18939e+07 | 45662.4 | 1.6795 | 3(Loss) | true |
| simdjson (reflection) | 1213.99 | 0.345425 | 5113.54ms | 65103 | 1280 | 3.99471e+07 | 51142.8 | 3.2037 | 4(Loss) | true |
| simdjson (ondemand) | 1130.93 | 0.216928 | 5900.1ms | 65103 | 640 | 9.07703e+06 | 54899.2 | 2.33961 | 5(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2146.02 | 0.709284 | 3804.43ms | 65103 | 160 | 6.73742e+06 | 28931.2 | 0.814005 | 1(Win) | true |
| Glaze | 1928.39 | 0.298968 | 4122.07ms | 65103 | 640 | 5.92986e+06 | 32196.4 | 2.09575 | 2(Loss) | true |
| Jsonifier (two-stage) | 1672.3 | 0.703209 | 4320.91ms | 65103 | 640 | 4.36239e+07 | 37126.8 | 1.14704 | 3(Loss) | true |
| simdjson (reflection) | 1540.13 | 0.709711 | 5108.34ms | 65103 | 640 | 5.23877e+07 | 40312.8 | 0.376479 | 4(Loss) | true |
| simdjson (ondemand) | 1176.51 | 0.262117 | 5931.15ms | 65103 | 4890 | 9.35635e+07 | 52772.1 | 0.335332 | 5(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14555.3 | 1.23515 | 531.486ms | 78778 | 160 | 650321 | 5161.6 | 0 | 1(Win) | true |
| Glaze | 3125.1 | 0.205947 | 2606.39ms | 78778 | 4890 | 1.19868e+07 | 24040.4 | 0.214221 | 2(Loss) | true |
| simdjson (reflection) | 383.257 | 0.462386 | 5183.21ms | 78778 | 640 | 5.25798e+08 | 196026 | 0.295411 | 3(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14109.2 | 1.28507 | 526.737ms | 78778 | 160 | 749171 | 5324.8 | 2.84302 | 1(Win) | true |
| Glaze | 3928 | 0.910159 | 2070.13ms | 78778 | 80 | 2.42432e+06 | 19126.4 | 0.285235 | 2(Loss) | true |
| simdjson (reflection) | 397.724 | 1.08459 | 5251.13ms | 78778 | 40 | 1.67894e+08 | 188896 | 0.582727 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1737.54 | 2.0213 | 682.038ms | 11812 | 40 | 686910 | 6483.2 | 1.84316 | 1(Win) | true |
| Jsonifier (two-stage) | 1195.91 | 0.15551 | 951.053ms | 11812 | 4890 | 1.04924e+06 | 9419.44 | 0.427951 | 2(Loss) | true |
| simdjson (reflection) | 993.194 | 0.41701 | 1178.48ms | 11812 | 640 | 1.4317e+06 | 11342 | 0.123283 | 3(Loss) | true |
| Glaze | 924.011 | 0.520374 | 1263.75ms | 11812 | 640 | 2.57575e+06 | 12191.2 | 0.600739 | 4(Loss) | true |
| simdjson (ondemand) | 644.759 | 0.367205 | 1720.75ms | 11812 | 4890 | 2.0127e+07 | 17471.3 | 0.0392168 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1813.28 | 0.425135 | 736.433ms | 11812 | 2560 | 1.78571e+06 | 6212.4 | 0.329457 | 1(Win) | true |
| Jsonifier (two-stage) | 1313.53 | 1.08226 | 1011.22ms | 11812 | 160 | 1.37832e+06 | 8576 | 0.865638 | 2(Loss) | true |
| simdjson (reflection) | 1068.22 | 0.28168 | 1143.56ms | 11812 | 1280 | 1.1294e+06 | 10545.4 | 0.051181 | 3(Loss) | true |
| Glaze | 1042.23 | 0.223247 | 1208.31ms | 11812 | 4890 | 2.84706e+06 | 10808.3 | 3.4436 | 4(Loss) | true |
| simdjson (ondemand) | 737.569 | 0.135372 | 1636.46ms | 11812 | 4890 | 2.09029e+06 | 15272.9 | 0.181126 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10320.2 | 0.41189 | 113.449ms | 11812 | 4890 | 98842.8 | 1091.53 | 0.843842 | 1(Win) | true |
| simdjson (reflection) | 8535.23 | 0.929214 | 142.496ms | 11812 | 2560 | 385024 | 1319.8 | 0.517898 | 2(Loss) | true |
| Glaze | 1728.95 | 0.339532 | 663.283ms | 11812 | 1280 | 626404 | 6515.4 | 0.0522113 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10541.6 | 0.557545 | 109.093ms | 11812 | 2560 | 90871.9 | 1068.6 | 0.447177 | 1(Win) | true |
| simdjson (reflection) | 8111.86 | 1.12601 | 138.305ms | 11812 | 4890 | 1.19564e+06 | 1388.68 | 0.186293 | 2(Loss) | true |
| Glaze | 1820.43 | 0.569214 | 635.16ms | 11812 | 1280 | 1.58804e+06 | 6188 | 1.93966 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2249.26 | 0.400812 | 1008.39ms | 25388 | 1280 | 2.38271e+06 | 10764.4 | 3.16657 | 1(Win) | true |
| Jsonifier (two-stage) | 2203.48 | 0.515372 | 1122.98ms | 25388 | 320 | 1.02619e+06 | 10988 | 0.814739 | 2(Loss) | true |
| simdjson (reflection) | 1796.27 | 0.226979 | 1375.22ms | 25388 | 4890 | 4.57716e+06 | 13479 | 0.0578192 | 3(Loss) | true |
| Glaze | 1505.36 | 0.217021 | 1589.21ms | 25388 | 2560 | 3.11903e+06 | 16083.8 | 0.0372907 | 4(Loss) | true |
| simdjson (ondemand) | 1311.83 | 0.256571 | 1879.04ms | 25388 | 2560 | 5.74059e+06 | 18456.6 | 0.079042 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2748.01 | 0.279314 | 963.113ms | 25388 | 4890 | 2.96153e+06 | 8810.69 | 0.2742 | 1(Win) | true |
| Jsonifier (two-stage) | 2391.01 | 0.375047 | 1126.35ms | 25388 | 1280 | 1.84618e+06 | 10126.2 | 0.242345 | 2(Loss) | true |
| simdjson (reflection) | 1723.49 | 0.562934 | 1524.9ms | 25388 | 1280 | 8.00509e+06 | 14048.2 | 0.958691 | 3(Loss) | true |
| Glaze | 1667.68 | 0.259752 | 1582.84ms | 25388 | 2560 | 3.64074e+06 | 14518.3 | 0.811727 | 4(Loss) | true |
| simdjson (ondemand) | 1394.19 | 0.224338 | 1831.15ms | 25388 | 4890 | 7.42218e+06 | 17366.3 | 0.339899 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16787.7 | 2.31012 | 191.772ms | 31235 | 160 | 268839 | 1774.4 | 0.805009 | 1(Win) | true |
| Glaze | 2581.51 | 0.456541 | 1236.12ms | 31235 | 1280 | 3.55226e+06 | 11539 | 0.332151 | 2(Loss) | true |
| simdjson (reflection) | 282.226 | 0.432492 | 5201.54ms | 31235 | 640 | 1.3336e+08 | 105547 | 0.125285 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 19138.8 | 0.481114 | 162.18ms | 31235 | 4890 | 274194 | 1556.42 | 2.3824 | 1(Win) | true |
| Glaze | 2677.82 | 0.608994 | 1153.66ms | 31235 | 1280 | 5.87432e+06 | 11124 | 0.411817 | 2(Loss) | true |
| simdjson (reflection) | 285.068 | 0.23618 | 5178.46ms | 31235 | 2560 | 1.55924e+08 | 104494 | 0.515397 | 3(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2444.04 | 0.0861305 | 4247.97ms | 108313 | 4890 | 6.47992e+06 | 42264.2 | 0.00884716 | 1(Win) | true |
| Jsonifier (two-stage) | 1680.51 | 0.0520556 | 6383.61ms | 108313 | 4890 | 5.00637e+06 | 61466.6 | 0.467381 | 2(Loss) | true |
| Glaze | 1405.7 | 0.46838 | 7492.48ms | 108313 | 640 | 7.58147e+07 | 73483.2 | 0.726282 | 3(Loss) | true |
| simdjson (ondemand) | 1215.72 | 0.501539 | 9068.27ms | 108313 | 30 | 5.44785e+06 | 84966.4 | 0.160433 | 4(Loss) | true |
| simdjson (reflection) | 1106.4 | 0.681555 | 8952.13ms | 108313 | 160 | 6.47825e+07 | 93361.6 | 0.482655 | 5(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2870.54 | 0.144162 | 3853.18ms | 108313 | 4890 | 1.31596e+07 | 35984.6 | 0.479009 | 1(Win) | true |
| Jsonifier (two-stage) | 1862.87 | 0.387542 | 6127.96ms | 108313 | 80 | 3.69424e+06 | 55449.6 | 0.253281 | 2(Loss) | true |
| Glaze | 1500.74 | 0.222444 | 6802.99ms | 108313 | 2560 | 6.00105e+07 | 68829.4 | 0.819046 | 3(Loss) | true |
| simdjson (reflection) | 1318.51 | 0.521613 | 8890.48ms | 108313 | 40 | 6.67959e+06 | 78342.4 | 1.90458 | 4(Loss) | true |
| simdjson (ondemand) | 1090.39 | 0.152397 | 9575.14ms | 108313 | 4890 | 1.01919e+08 | 94732 | 0.448782 | 5(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12582.3 | 0.445 | 798.939ms | 108313 | 1280 | 1.70834e+06 | 8209.6 | 1.76013 | 1(Win) | true |
| simdjson (reflection) | 8527.08 | 0.128408 | 1348.49ms | 108313 | 1280 | 309711 | 12113.8 | 0.248682 | 2(Loss) | true |
| Glaze | 1874.01 | 0.523881 | 6030.51ms | 108313 | 160 | 1.33415e+07 | 55120 | 0.231683 | 3(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15470.8 | 0.567817 | 773.708ms | 108313 | 160 | 229971 | 6676.8 | 0.409047 | 1(Win) | true |
| simdjson (reflection) | 8686.7 | 0.205282 | 1263.41ms | 108313 | 640 | 381360 | 11891.2 | 0.107759 | 2(Loss) | true |
| Glaze | 2014.36 | 0.350997 | 5215.94ms | 108313 | 640 | 2.07337e+07 | 51279.6 | 0.802408 | 3(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2891.82 | 0.0469037 | 6243.64ms | 183677 | 4890 | 3.94719e+06 | 60573.5 | 1.59495 | 1(Win) | true |
| Jsonifier (two-stage) | 2201.52 | 0.142131 | 8050.05ms | 183677 | 4890 | 6.25387e+07 | 79566.8 | 0.202112 | 2(Loss) | true |
| Glaze | 1934.91 | 0.146202 | 9363.07ms | 183677 | 2560 | 4.48469e+07 | 90530.2 | 1.08454 | 3(Loss) | true |
| simdjson (reflection) | 1737.95 | 0.341184 | 5255.13ms | 183677 | 1280 | 1.51365e+08 | 100790 | 0.613926 | 4(Loss) | true |
| simdjson (ondemand) | 1535.69 | 1.26788 | 5699.5ms | 183677 | 30 | 6.27459e+07 | 114065 | 1.66985 | 5(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3209.49 | 0.0804828 | 5970.01ms | 183677 | 1280 | 2.46976e+06 | 54578.2 | 0.0692105 | 1(Win) | true |
| Jsonifier (two-stage) | 2477.15 | 0.804355 | 8464.95ms | 183677 | 40 | 1.29408e+07 | 70713.6 | 0.65286 | 2(Loss) | true |
| Glaze | 2029.52 | 0.381592 | 8837.25ms | 183677 | 640 | 6.94227e+07 | 86310 | 0.0848826 | 3(Loss) | true |
| simdjson (reflection) | 1944.87 | 0.100763 | 9576.24ms | 183677 | 4890 | 4.02754e+07 | 90066.9 | 0.556303 | 4(Loss) | true |
| simdjson (ondemand) | 1804.94 | 0.251716 | 5382.53ms | 183677 | 1280 | 7.63866e+07 | 97049.2 | 2.54478 | 5(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 18018.1 | 0.471099 | 1153.74ms | 213963 | 80 | 227706 | 11324.8 | 0.0282646 | 1(Win) | true |
| Glaze | 2286.01 | 0.548234 | 8682.46ms | 213963 | 80 | 1.91577e+07 | 89260.8 | 0.693091 | 2(Loss) | true |
| simdjson (reflection) | 340.571 | 0.38496 | 8113.86ms | 213963 | 160 | 8.51166e+08 | 599144 | 1.54377 | 3(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 18196.4 | 0.160299 | 1128.21ms | 213963 | 1280 | 413598 | 11213.8 | 0.302326 | 1(Win) | true |
| Glaze | 2680.28 | 0.134535 | 7818ms | 213963 | 320 | 3.35687e+06 | 76130.4 | 0.0157649 | 2(Loss) | true |
| simdjson (reflection) | 318.895 | 0.215839 | 8425.64ms | 213963 | 320 | 6.10364e+08 | 639868 | 0.626061 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 590.553 | 0.79903 | 9060.76ms | 1834197 | 80 | 4.48115e+10 | 2.96201e+06 | 2.76728 | 1(Win) | true |
| Jsonifier (two-stage) | 541.911 | 0.523106 | 5062.45ms | 1834197 | 80 | 2.2809e+10 | 3.22789e+06 | 1.33717 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 466.548 | 0.757838 | 5748.35ms | 1834197 | 40 | 3.22933e+10 | 3.7493e+06 | 0.339129 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 458.121 | 0.556548 | 5653.03ms | 1834197 | 80 | 3.61265e+10 | 3.81826e+06 | 3.07371 | 3(Tie) | true |
| Glaze | 447.047 | 0.701245 | 6050.77ms | 1834197 | 80 | 6.02302e+10 | 3.91284e+06 | 1.06703 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 681.968 | 1.09639 | 8982.77ms | 1834197 | 80 | 6.32684e+10 | 2.56497e+06 | 0.45405 | 1(Win) | true |
| Jsonifier (two-stage) | 613.284 | 0.29339 | 10067.1ms | 1834197 | 80 | 5.60208e+09 | 2.85223e+06 | 0.693415 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 518.597 | 0.360946 | 5634.09ms | 1834197 | 30 | 4.44669e+09 | 3.373e+06 | 1.17409 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 514.7 | 0.401867 | 5861.66ms | 1834197 | 40 | 7.46117e+09 | 3.39853e+06 | 1.03985 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 514.5 | 0.947718 | 5670.37ms | 1834197 | 30 | 3.11459e+10 | 3.39986e+06 | 1.56076 | 3(Tie) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1266.35 | 0.531586 | 8970.92ms | 1834197 | 320 | 1.72538e+10 | 1.38132e+06 | 0.804617 | 1(Win) | true |
| Glaze | 752.693 | 0.528547 | 7137.27ms | 1833577 | 160 | 2.41241e+10 | 2.32317e+06 | 1.71438 | 2(Loss) | true |
| simdjson (reflection) | 739.364 | 0.583203 | 7790.87ms | 1922245 | 40 | 8.36374e+09 | 2.47942e+06 | 1.42473 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1287.74 | 0.85823 | 8830.89ms | 1834197 | 40 | 5.43634e+09 | 1.35837e+06 | 1.92745 | 1(Win) | true |
| Glaze | 800.003 | 0.796802 | 6647.3ms | 1833577 | 40 | 1.21332e+10 | 2.18579e+06 | 0.292777 | 2(Loss) | true |
| simdjson (reflection) | 696.739 | 1.3839 | 8164.88ms | 1922245 | 30 | 3.97745e+10 | 2.63111e+06 | 0.047977 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1773.8 | 0.232405 | 5905.21ms | 7351818 | 30 | 2.53158e+09 | 3.95267e+06 | 2.68618 | 1(Win) | true |
| Jsonifier | 1705.24 | 0.465221 | 5999.01ms | 7351818 | 40 | 1.46352e+10 | 4.11158e+06 | 0.912572 | 2(Loss) | true |
| simdjson (reflection) | 1657.03 | 0.436478 | 6490.08ms | 7351818 | 80 | 2.72863e+10 | 4.23121e+06 | 0.250683 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1433.15 | 0.473042 | 7415.78ms | 7351818 | 80 | 4.28448e+10 | 4.8922e+06 | 5.46499 | -(Loss) | false |
| Glaze | 1342.52 | 1.37616 | 7707.26ms | 7351818 | 30 | 1.54956e+11 | 5.22243e+06 | 0.0527496 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2058.91 | 0.233193 | 5682.66ms | 7351818 | 80 | 5.0447e+09 | 3.40531e+06 | 2.04569 | 1(Win) | true |
| Jsonifier (two-stage) | 2003.12 | 0.220847 | 5809.86ms | 7351818 | 80 | 4.78023e+09 | 3.50017e+06 | 0.331499 | 2(Loss) | true |
| simdjson (reflection) | 1843.55 | 0.257923 | 6369.79ms | 7351818 | 80 | 7.6975e+09 | 3.80311e+06 | 0.498573 | 3(Loss) | true |
| Glaze | 1581.49 | 0.624991 | 7387.29ms | 7351818 | 30 | 2.30316e+10 | 4.43331e+06 | 1.52326 | 4(Loss) | true |
| simdjson (ondemand) | 1556.86 | 0.398026 | 7066.16ms | 7351818 | 30 | 9.63908e+09 | 4.50346e+06 | 1.65773 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6519.68 | 0.23716 | 9317.2ms | 9930848 | 40 | 4.74749e+08 | 1.45265e+06 | 0.0905467 | 1(Win) | true |
| Glaze | 3060.64 | 0.200101 | 9796.63ms | 9930228 | 160 | 6.13352e+09 | 3.09419e+06 | 0.0966356 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 255.664 | 1.04444 | 10709.4ms | 10018896 | 30 | 4.57076e+12 | 3.73723e+07 | 7.08361 | -(Loss) | false |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6482.1 | 0.434569 | 9208ms | 9930848 | 30 | 1.20943e+09 | 1.46107e+06 | 0.28348 | 1(Win) | true |
| Glaze | 3190.18 | 0.190093 | 9280.54ms | 9930228 | 160 | 5.09497e+09 | 2.96855e+06 | 0.23568 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 268.162 | 0.624895 | 10100.8ms | 10018896 | 30 | 1.48724e+12 | 3.56305e+07 | 16.2895 | -(Loss) | false |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 611.979 | 0.731641 | 9013.29ms | 1834197 | 80 | 3.4987e+10 | 2.85831e+06 | 1.39638 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 482.786 | 1.07355 | 5461.08ms | 1834197 | 40 | 6.05179e+10 | 3.62319e+06 | 0.795505 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 477.332 | 0.848532 | 6025.06ms | 1834197 | 30 | 2.90074e+10 | 3.66459e+06 | 0.391566 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 419.001 | 1.45277 | 6421.56ms | 1834197 | 40 | 1.47134e+11 | 4.17475e+06 | 0.806609 | 4(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 418.008 | 0.548739 | 6312.19ms | 1834197 | 80 | 4.21837e+10 | 4.18467e+06 | 0.15348 | 4(Tie) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 699.222 | 1.33583 | 8862.29ms | 1834197 | 30 | 3.3503e+10 | 2.50167e+06 | 1.11812 | 1(Win) | true |
| Jsonifier (two-stage) | 580.782 | 0.671658 | 5069.31ms | 1834197 | 40 | 1.6369e+10 | 3.01185e+06 | 2.49845 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 451.169 | 0.874077 | 6132.76ms | 1834197 | 30 | 3.44535e+10 | 3.87709e+06 | 2.08279 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 449.067 | 1.82935 | 6159.8ms | 1834197 | 30 | 1.5233e+11 | 3.89524e+06 | 1.30404 | 3(Tie) | true |
| simdjson (ondemand) | 393.28 | 0.808138 | 7295.81ms | 1834197 | 40 | 5.16797e+10 | 4.44779e+06 | 1.16478 | 5(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1367.23 | 0.620401 | 8860.75ms | 1834197 | 40 | 2.52009e+09 | 1.2794e+06 | 2.30534 | 1(Win) | true |
| Glaze | 773.974 | 1.24142 | 7135.67ms | 1833577 | 30 | 2.35996e+10 | 2.25929e+06 | 1.3797 | 2(Loss) | true |
| simdjson (reflection) | 630.966 | 1.89833 | 8563.21ms | 1922245 | 30 | 9.12576e+10 | 2.90538e+06 | 1.18579 | 3(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1302.5 | 0.269018 | 8665.83ms | 1834197 | 80 | 1.04421e+09 | 1.34298e+06 | 0.512514 | 1(Win) | true |
| Glaze | 862.316 | 1.49638 | 6269.17ms | 1833577 | 30 | 2.76229e+10 | 2.02784e+06 | 2.73216 | 2(Loss) | true |
| simdjson (reflection) | 755.967 | 0.636287 | 7907.21ms | 1922245 | 80 | 1.90462e+10 | 2.42497e+06 | 2.60391 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1730.16 | 0.718833 | 6287.14ms | 7351818 | 30 | 2.54562e+10 | 4.05236e+06 | 0.422728 | 1(Win) | true |
| Jsonifier | 1656.68 | 0.606368 | 5929.02ms | 7351818 | 30 | 1.97563e+10 | 4.2321e+06 | 0.99771 | 2(Loss) | true |
| simdjson (reflection) | 1609.56 | 0.916595 | 6431.02ms | 7351818 | 30 | 4.78247e+10 | 4.356e+06 | 0.109387 | 3(Loss) | true |
| simdjson (ondemand) | 1410.93 | 0.565913 | 7763.59ms | 7351818 | 80 | 6.32654e+10 | 4.96923e+06 | 1.71527 | 4(Loss) | true |
| Glaze | 1331.9 | 0.981261 | 7635.88ms | 7351818 | 80 | 2.13454e+11 | 5.26409e+06 | 2.41579 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1907.62 | 1.02128 | 6156.42ms | 7351818 | 30 | 4.22683e+10 | 3.67539e+06 | 2.68662 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE DID NOT CONVERGE | 1904.34 | 1.79095 | 5714.06ms | 7351818 | 30 | 1.30434e+11 | 3.68172e+06 | 5.406 | -(Tie) | false |
| simdjson (reflection) | 1744.22 | 0.336125 | 6568.3ms | 7351818 | 80 | 1.46042e+10 | 4.0197e+06 | 0.430016 | 3(Loss) | true |
| Glaze STATISTICAL TIE | 1530.18 | 0.785401 | 7816.74ms | 7351818 | 30 | 3.88516e+10 | 4.58197e+06 | 0.298495 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1504.66 | 0.76562 | 7630.98ms | 7351818 | 80 | 1.01819e+11 | 4.65968e+06 | 0.399558 | 4(Tie) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 6125.5 | 1.03643 | 9605.75ms | 9930848 | 40 | 1.02714e+10 | 1.54612e+06 | 6.77933 | -(Win) | false |
| Glaze DID NOT CONVERGE | 2627.33 | 0.582344 | 5654.35ms | 9930228 | 30 | 1.32181e+10 | 3.6045e+06 | 8.42471 | -(Loss) | false |
| simdjson (reflection) DID NOT CONVERGE | 283.982 | 1.67237 | 10675.2ms | 10018896 | 30 | 9.49832e+12 | 3.36457e+07 | 5.32497 | -(Loss) | false |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5681.42 | 0.98726 | 9808.47ms | 9930848 | 30 | 8.12538e+09 | 1.66698e+06 | 1.61355 | 1(Win) | true |
| Glaze | 3067.02 | 0.487347 | 9747.76ms | 9930228 | 80 | 1.81155e+10 | 3.08775e+06 | 4.41358 | 2(Loss) | true |
| simdjson (reflection) | 261.619 | 1.64931 | 11084.1ms | 10018896 | 30 | 1.08851e+13 | 3.65217e+07 | 2.15921 | 3(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 936.036 | 0.279062 | 6005.49ms | 461466 | 160 | 2.75433e+08 | 470162 | 0.586297 | 1(Win) | true |
| Jsonifier (two-stage) | 795.767 | 1.92791 | 7216.89ms | 461466 | 30 | 3.41037e+09 | 553037 | 2.28424 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 727.529 | 0.498455 | 8004.09ms | 461466 | 640 | 5.81849e+09 | 604908 | 3.36943 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 720.636 | 1.24599 | 7898.3ms | 461466 | 40 | 2.316e+09 | 610694 | 0.486879 | 3(Tie) | true |
| simdjson (ondemand) | 579.697 | 0.498918 | 9230.95ms | 461466 | 320 | 4.59078e+09 | 759170 | 2.64181 | 5(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1374.27 | 0.741314 | 5872.1ms | 461466 | 160 | 9.01701e+08 | 320235 | 0.0835084 | 1(Win) | true |
| Jsonifier (two-stage) | 1224.4 | 1.05827 | 6094.89ms | 461466 | 80 | 1.15748e+09 | 359430 | 0.544247 | 2(Loss) | true |
| Glaze | 1003.59 | 0.236903 | 7484.04ms | 461466 | 320 | 3.45348e+08 | 438514 | 0.896938 | 3(Loss) | true |
| simdjson (reflection) | 925.621 | 1.11296 | 8303.59ms | 461466 | 30 | 8.40034e+08 | 475452 | 1.36315 | 4(Loss) | true |
| simdjson (ondemand) | 740.197 | 0.811999 | 8696.4ms | 461466 | 160 | 3.72919e+09 | 594555 | 2.45243 | 5(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10815.6 | 0.191655 | 3972.55ms | 461466 | 4890 | 2.97392e+07 | 40690.2 | 0.296603 | 1(Win) | true |
| simdjson (reflection) | 7340.37 | 0.224529 | 6047.7ms | 461466 | 2560 | 4.63906e+07 | 59954.5 | 0.543852 | 2(Loss) | true |
| Glaze | 1973.62 | 0.423351 | 5592.14ms | 461466 | 640 | 5.70338e+08 | 222985 | 0.900291 | 3(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11920.7 | 0.259906 | 3825.43ms | 461466 | 640 | 5.89235e+06 | 36918 | 2.43864 | 1(Win) | true |
| simdjson (reflection) | 7001.95 | 0.252363 | 6138.45ms | 461466 | 2560 | 6.44068e+07 | 62852.2 | 0.747606 | 2(Loss) | true |
| Glaze | 2039.92 | 0.32638 | 5246.8ms | 461466 | 1280 | 6.34611e+08 | 215738 | 0.211291 | 3(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1135.96 | 0.502321 | 7566.23ms | 728486 | 160 | 1.51007e+09 | 611586 | 2.70993 | 1(Win) | true |
| simdjson (reflection) | 1023.08 | 0.66679 | 8876.58ms | 728486 | 80 | 1.64018e+09 | 679066 | 1.29647 | 2(Loss) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 926.413 | 0.543421 | 8944.89ms | 728486 | 80 | 1.32861e+09 | 749923 | 1.1861 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 921.241 | 1.24913 | 9158.32ms | 728486 | 30 | 2.66215e+09 | 754133 | 4.98836 | 3(Tie) | true |
| simdjson (ondemand) | 844.629 | 1.18858 | 10035.6ms | 728486 | 30 | 2.8674e+09 | 822537 | 0.512963 | 5(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1553.62 | 0.642961 | 7031.68ms | 728486 | 80 | 6.61323e+08 | 447174 | 1.28434 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1546.35 | 0.882055 | 7816.62ms | 728486 | 320 | 5.02534e+09 | 449275 | 0.850848 | 1(Tie) | true |
| Glaze | 1329.8 | 0.357244 | 8778.08ms | 728486 | 640 | 2.22934e+09 | 522437 | 1.17583 | 3(Loss) | true |
| simdjson (reflection) | 1289.29 | 0.47366 | 8308.87ms | 728486 | 40 | 2.60577e+08 | 538854 | 1.86031 | 4(Loss) | true |
| simdjson (ondemand) | 1132.68 | 0.4549 | 9378.46ms | 728486 | 320 | 2.49121e+09 | 613358 | 2.7629 | 5(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14303.5 | 0.143407 | 5580.04ms | 837491 | 4890 | 3.13565e+07 | 55839.2 | 1.50829 | 1(Win) | true |
| Glaze | 2466.52 | 0.342853 | 8508.13ms | 837491 | 160 | 1.97209e+08 | 323814 | 0.115488 | 2(Loss) | true |
| simdjson (reflection) | 299.042 | 0.426728 | 8215.66ms | 837491 | 160 | 2.07835e+10 | 2.67084e+06 | 0.697384 | 3(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14795.9 | 0.587237 | 5653.07ms | 837491 | 160 | 1.60777e+07 | 53980.8 | 0.0770051 | 1(Win) | true |
| Glaze | 2696.19 | 0.273455 | 7644.59ms | 837491 | 320 | 2.09981e+08 | 296230 | 0.412027 | 2(Loss) | true |
| simdjson (reflection) | 311.329 | 0.625829 | 8064.57ms | 837491 | 30 | 7.73311e+09 | 2.56544e+06 | 0.782088 | 3(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4335.6 | 0.455897 | 5170.95ms | 466906 | 640 | 1.40306e+08 | 102702 | 1.534 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4283.08 | 2.13752 | 5461.15ms | 466906 | 30 | 1.48145e+08 | 103962 | 3.44746 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3958.52 | 0.199382 | 6436.49ms | 466906 | 640 | 3.21919e+07 | 112486 | 0.0149375 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 3954.59 | 0.108924 | 5728.87ms | 466906 | 2560 | 3.85074e+07 | 112597 | 0.172771 | 3(Tie) | true |
| Glaze | 2238 | 0.576243 | 5277.55ms | 466906 | 160 | 2.10315e+08 | 198962 | 2.05252 | 5(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4792.95 | 1.03884 | 5121.33ms | 466906 | 40 | 3.72574e+07 | 92902.4 | 0.202485 | 1(Win) | true |
| Jsonifier (two-stage) | 4378.54 | 0.779676 | 9782.37ms | 466906 | 320 | 2.01177e+08 | 101695 | 1.5985 | 2(Loss) | true |
| simdjson (reflection) | 4048.29 | 0.20411 | 6166.43ms | 466906 | 320 | 1.61285e+07 | 109991 | 0.27642 | 3(Loss) | true |
| simdjson (ondemand) | 3711.43 | 0.645372 | 6113.21ms | 466906 | 80 | 4.79609e+07 | 119974 | 0.0639727 | 4(Loss) | true |
| Glaze | 2132.05 | 0.455949 | 5051.71ms | 466906 | 640 | 5.80333e+08 | 208849 | 0.932946 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 4626.79 | 0.531394 | 6732.25ms | 631514 | 640 | 3.0621e+08 | 130168 | 1.15515 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 4569.1 | 1.02469 | 6833.76ms | 631514 | 80 | 1.45941e+08 | 131811 | 0.461553 | 1(Tie) | true |
| simdjson (ondemand) | 4138.11 | 0.247589 | 7440.42ms | 631514 | 1280 | 1.66201e+08 | 145540 | 0.339752 | 3(Loss) | true |
| simdjson (reflection) | 3897.54 | 0.336064 | 7821.05ms | 631514 | 2560 | 6.9035e+08 | 154523 | 1.35221 | 4(Loss) | true |
| Glaze | 2896.08 | 0.341175 | 5255.23ms | 631514 | 320 | 1.61084e+08 | 207957 | 1.06844 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 4845.58 | 0.555952 | 6400.36ms | 631514 | 320 | 1.52792e+08 | 124290 | 0.209626 | 1(Win) | true |
| Jsonifier | 4625.1 | 0.524588 | 6430.27ms | 631514 | 640 | 2.98634e+08 | 130215 | 0.548067 | 2(Loss) | true |
| simdjson (ondemand) | 4342.51 | 0.286093 | 7911.69ms | 631514 | 640 | 1.00758e+08 | 138689 | 1.09002 | 3(Loss) | true |
| simdjson (reflection) | 4285.06 | 0.304619 | 7383.16ms | 631514 | 1280 | 2.34626e+08 | 140548 | 2.50554 | 4(Loss) | true |
| Glaze | 3091.18 | 0.14731 | 5230.95ms | 631514 | 320 | 2.6359e+07 | 194831 | 0.219336 | 5(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1854.08 | 2.20021 | 6085.99ms | 466906 | 80 | 2.23368e+09 | 240160 | 0.308175 | 1(Win) | true |
| Jsonifier (two-stage) | 1713.26 | 0.427363 | 6881.64ms | 466906 | 30 | 3.70106e+07 | 259900 | 0.207278 | 2(Loss) | true |
| Glaze | 1436.28 | 0.267809 | 7992.37ms | 466906 | 1280 | 8.82354e+08 | 310021 | 1.41062 | 3(Loss) | true |
| simdjson (reflection) | 1153.35 | 0.641874 | 9494.73ms | 466906 | 30 | 1.8423e+08 | 386074 | 0.106206 | 4(Loss) | true |
| simdjson (ondemand) | 1042.02 | 0.173822 | 6277.96ms | 466906 | 40 | 2.20688e+07 | 427322 | 0.967547 | 5(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2802.24 | 0.125007 | 5256.91ms | 466906 | 1280 | 5.05042e+07 | 158900 | 1.66945 | 1(Win) | true |
| Jsonifier (two-stage) | 2230.57 | 0.246712 | 6205.84ms | 466906 | 160 | 3.88086e+07 | 199624 | 0.0457068 | 2(Loss) | true |
| Glaze | 1968.09 | 0.237296 | 7112.24ms | 466906 | 640 | 1.84471e+08 | 226248 | 0.606777 | 3(Loss) | true |
| simdjson (reflection) | 1349.74 | 1.54562 | 5055.74ms | 466906 | 30 | 7.79988e+08 | 329899 | 1.76598 | 4(Loss) | true |
| simdjson (ondemand) | 1016.36 | 0.424078 | 5978.5ms | 466906 | 320 | 1.10461e+09 | 438110 | 0.392487 | 5(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14269.8 | 0.29397 | 3154.64ms | 475954 | 1280 | 1.11921e+07 | 31808.8 | 1.26966 | 1(Win) | true |
| simdjson (reflection) | 11300.1 | 0.130974 | 4187.39ms | 475954 | 4890 | 1.35345e+07 | 40168.1 | 0.524734 | 2(Loss) | true |
| Glaze | 3742.23 | 0.969502 | 6559.3ms | 475954 | 40 | 5.53131e+07 | 121293 | 1.64474 | 3(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15576 | 0.866361 | 3149.42ms | 475954 | 30 | 1.91222e+06 | 29141.3 | 0.668994 | 1(Win) | true |
| simdjson (reflection) | 11697.6 | 0.216358 | 4119.72ms | 475954 | 40 | 281931 | 38803.2 | 0.43245 | 2(Loss) | true |
| Glaze | 4037.84 | 0.605064 | 5960.86ms | 475954 | 80 | 3.70104e+07 | 112413 | 0.638859 | 3(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1932.13 | 0.616645 | 7997.11ms | 631514 | 320 | 1.18226e+09 | 311706 | 0.229201 | 1(Win) | true |
| Jsonifier (two-stage) | 1904.42 | 0.394222 | 7899.77ms | 631514 | 320 | 4.9736e+08 | 316242 | 0.758808 | 2(Loss) | true |
| Glaze | 1842.1 | 0.192254 | 8319.7ms | 631514 | 320 | 1.26427e+08 | 326942 | 0.128787 | 3(Loss) | true |
| simdjson (reflection) | 1608.44 | 0.423674 | 9636.98ms | 631514 | 160 | 4.02662e+08 | 374437 | 0.787703 | 4(Loss) | true |
| simdjson (ondemand) | 1262.61 | 0.152888 | 6182.95ms | 631514 | 640 | 3.4037e+08 | 476993 | 1.08965 | 5(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2608.46 | 0.511162 | 7080.33ms | 631514 | 30 | 4.17864e+07 | 230886 | 0.17401 | 1(Win) | true |
| Jsonifier (two-stage) | 2497.5 | 0.158438 | 7340ms | 631514 | 640 | 9.34234e+07 | 241144 | 0.288618 | 2(Loss) | true |
| Glaze | 2235.77 | 0.255177 | 8144.34ms | 631514 | 320 | 1.51197e+08 | 269374 | 0.746352 | 3(Loss) | true |
| simdjson (reflection) | 1715.95 | 1.05781 | 9790.52ms | 631514 | 40 | 5.51353e+08 | 350976 | 0.716924 | 4(Loss) | true |
| simdjson (ondemand) | 1451.67 | 0.342153 | 5893.72ms | 631514 | 30 | 6.04495e+07 | 414874 | 0.154502 | 5(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15723.2 | 0.25448 | 4345.5ms | 716365 | 4890 | 5.97862e+07 | 43450.3 | 0.288903 | 1(Win) | true |
| Glaze | 3755.83 | 0.389411 | 9286.82ms | 716365 | 320 | 1.60555e+08 | 181898 | 1.90476 | 2(Loss) | true |
| simdjson (reflection) | 333.988 | 0.653051 | 6302.57ms | 716365 | 160 | 2.85511e+10 | 2.04552e+06 | 2.28312 | 3(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15680.9 | 0.52638 | 4426.33ms | 716365 | 640 | 3.36593e+07 | 43567.6 | 0.595955 | 1(Win) | true |
| Glaze | 4669.28 | 0.20559 | 8202.43ms | 716365 | 80 | 7.23873e+06 | 146314 | 0.0766065 | 2(Loss) | true |
| simdjson (reflection) | 348.833 | 0.967425 | 5975.26ms | 716365 | 30 | 1.07693e+10 | 1.95847e+06 | 1.63381 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1399.46 | 1.2901 | 194.012ms | 2632 | 320 | 171336 | 1793.6 | 0.358102 | 1(Win) | true |
| Jsonifier | 1166.17 | 0.681972 | 197.392ms | 2632 | 640 | 137899 | 2152.4 | 0.242176 | 2(Loss) | true |
| Glaze | 1107.51 | 0.61647 | 224.97ms | 2632 | 1280 | 249866 | 2266.4 | 0.334213 | 3(Loss) | true |
| simdjson (reflection) | 817.08 | 2.19265 | 271.663ms | 2632 | 40 | 181484 | 3072 | 1.1236 | 4(Loss) | true |
| simdjson (ondemand) | 750.133 | 0.345305 | 328.945ms | 2632 | 4890 | 652845 | 3346.17 | 0.901319 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2166.84 | 3.47149 | 175.775ms | 2632 | 80 | 129371 | 1158.4 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 1819.95 | 2.81704 | 201.998ms | 2632 | 160 | 241525 | 1379.2 | 0.461894 | 2(Loss) | true |
| Glaze | 1697.45 | 0.509087 | 174.367ms | 2632 | 4890 | 277120 | 1478.73 | 1.23415 | 3(Loss) | true |
| simdjson (reflection) | 1157.03 | 0.784375 | 251.704ms | 2632 | 1280 | 370627 | 2169.4 | 0.472397 | 4(Loss) | true |
| simdjson (ondemand) | 1103.38 | 0.425362 | 280.316ms | 2632 | 2560 | 239708 | 2274.9 | 1.19441 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 9174.24 | 12.9358 | 31.4898ms | 2632 | 160 | 200418 | 273.6 | 0.581395 | -(Win) | false |
| simdjson (reflection) | 5152.03 | 5.77254 | 49.056ms | 2632 | 320 | 253104 | 487.2 | 1.45631 | 2(Loss) | true |
| Glaze | 2824.43 | 0.882601 | 93.322ms | 2632 | 2560 | 157499 | 888.7 | 1.72848 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10372.2 | 7.02413 | 30.475ms | 2632 | 640 | 184925 | 242 | 2.10356 | 1(Win) | true |
| simdjson (reflection) | 6172.28 | 1.75965 | 44.044ms | 2632 | 4890 | 250404 | 406.668 | 1.54015 | 2(Loss) | true |
| Glaze | 2830.48 | 3.34447 | 88.085ms | 2632 | 640 | 562971 | 886.8 | 4.84979 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1672.89 | 0.237998 | 199.19ms | 3370 | 4890 | 102230 | 1921.15 | 0.504856 | 1(Win) | true |
| Glaze | 1407.97 | 0.355073 | 255.597ms | 3370 | 4890 | 321232 | 2282.64 | 0.612161 | 2(Loss) | true |
| Jsonifier (two-stage) | 1365.69 | 0.551346 | 209.215ms | 3370 | 2560 | 430967 | 2353.3 | 1.01734 | 3(Loss) | true |
| simdjson (reflection) | 1151.85 | 0.996966 | 264.804ms | 3370 | 1280 | 990470 | 2790.2 | 0.0644699 | 4(Loss) | true |
| simdjson (ondemand) | 1050.12 | 0.150954 | 321.57ms | 3370 | 4890 | 104371 | 3060.48 | 0.22226 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2107.17 | 0.505134 | 192.322ms | 3370 | 4890 | 290258 | 1525.22 | 3.35727 | 1(Win) | true |
| Glaze | 1961.24 | 0.839571 | 187.013ms | 3370 | 2560 | 484567 | 1638.7 | 2.31643 | 2(Loss) | true |
| Jsonifier | 1762.41 | 0.526293 | 201.77ms | 3370 | 4890 | 450409 | 1823.57 | 1.29537 | 3(Loss) | true |
| simdjson (reflection) | 1346.3 | 1.20562 | 244.789ms | 3370 | 320 | 265061 | 2387.2 | 0.336247 | 4(Loss) | true |
| simdjson (ondemand) | 1255.82 | 1.33016 | 311.272ms | 3370 | 320 | 370822 | 2559.2 | 1.32634 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10244.4 | 2.0044 | 39.029ms | 3643 | 4890 | 225955 | 339.135 | 0.98261 | 1(Win) | true |
| Glaze | 4039.38 | 0.816516 | 95.9519ms | 3682 | 2560 | 128976 | 869.3 | 0.334718 | 2(Loss) | true |
| simdjson (reflection) | 301.598 | 0.245952 | 1114.69ms | 3643 | 4890 | 3.92528e+06 | 11519.4 | 1.99596 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9933.14 | 1.95859 | 38.1192ms | 3643 | 4890 | 229477 | 349.762 | 3.32702 | 1(Win) | true |
| Glaze | 4567.42 | 1.55888 | 85.5619ms | 3682 | 1280 | 183849 | 768.8 | 1.18252 | 2(Loss) | true |
| simdjson (reflection) | 307.346 | 0.998877 | 1109.3ms | 3643 | 160 | 2.0399e+06 | 11304 | 0.0424809 | 3(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 646.734 | 0.414446 | 683.805ms | 4630 | 2560 | 2.04968e+06 | 6827.4 | 0.719913 | 1(Win) | true |
| Jsonifier (two-stage) | 571.129 | 0.551842 | 807.447ms | 4630 | 320 | 582469 | 7731.2 | 0.897891 | 2(Loss) | true |
| simdjson (reflection) | 509.663 | 0.34889 | 874.423ms | 4630 | 2560 | 2.33892e+06 | 8663.6 | 0.428906 | 3(Loss) | true |
| Glaze | 482.253 | 0.584279 | 939.192ms | 4630 | 640 | 1.83161e+06 | 9156 | 1.20846 | 4(Loss) | true |
| simdjson (ondemand) | 456.761 | 0.115819 | 1014.43ms | 4630 | 4890 | 612993 | 9667.01 | 2.40469 | 5(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 819.387 | 1.69841 | 710.283ms | 4630 | 80 | 670126 | 5388.8 | 0.236967 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 674.632 | 1.34821 | 831.278ms | 4630 | 30 | 233594 | 6545.07 | 0 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 671.295 | 0.389693 | 871.965ms | 4630 | 640 | 420494 | 6577.6 | 0.207191 | 2(Tie) | true |
| Glaze | 612.449 | 0.73784 | 911.024ms | 4630 | 80 | 226379 | 7209.6 | 0.044405 | 4(Loss) | true |
| simdjson (ondemand) | 526.86 | 0.244726 | 943.592ms | 4630 | 2560 | 1.07689e+06 | 8380.8 | 1.77049 | 5(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2202.91 | 0.489471 | 197.236ms | 4630 | 2560 | 246413 | 2004.4 | 1.97574 | 1(Win) | true |
| Glaze | 1439.59 | 1.6539 | 314.802ms | 4630 | 160 | 411741 | 3067.2 | 0.15674 | 2(Loss) | true |
| simdjson (reflection) | 876.685 | 0.260649 | 512.037ms | 4630 | 1280 | 220596 | 5036.6 | 0.963505 | 3(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2458.12 | 0.479317 | 192.961ms | 4630 | 2560 | 189777 | 1796.3 | 0.921125 | 1(Win) | true |
| Glaze | 1943.7 | 0.462367 | 249.443ms | 4630 | 2560 | 282433 | 2271.7 | 3.17535 | 2(Loss) | true |
| simdjson (reflection) | 882.326 | 0.386164 | 495.405ms | 4630 | 640 | 239017 | 5004.4 | 0.0878454 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1293.71 | 0.452864 | 868.601ms | 11579 | 640 | 956278 | 8535.6 | 0.0140607 | 1(Win) | true |
| Jsonifier (two-stage) | 1223.83 | 0.3889 | 882.434ms | 11579 | 1280 | 1.57612e+06 | 9023 | 0.703125 | 2(Loss) | true |
| simdjson (reflection) | 1192.29 | 0.302128 | 935.039ms | 11579 | 4890 | 3.82884e+06 | 9261.65 | 1.84353 | 3(Loss) | true |
| simdjson (ondemand) | 1075.02 | 0.692294 | 1116.56ms | 11579 | 40 | 202279 | 10272 | 0.269263 | 4(Loss) | true |
| Glaze | 1042.78 | 0.427367 | 1110.65ms | 11579 | 320 | 655406 | 10589.6 | 0.784224 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1557.23 | 0.796032 | 882.623ms | 11579 | 30 | 95592.2 | 7091.2 | 0 | 1(Win) | true |
| Jsonifier | 1518.3 | 0.276656 | 864.994ms | 11579 | 1280 | 518225 | 7273 | 0.194862 | 2(Loss) | true |
| simdjson (reflection) | 1393.52 | 0.268971 | 906.939ms | 11579 | 4890 | 2.22146e+06 | 7924.27 | 0.679661 | 3(Loss) | true |
| simdjson (ondemand) | 1192.61 | 0.990708 | 1125.63ms | 11579 | 160 | 1.34635e+06 | 9259.2 | 0.120815 | 4(Loss) | true |
| Glaze | 1124.62 | 0.279013 | 1115.05ms | 11579 | 1280 | 960713 | 9819 | 0.136657 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7805.72 | 0.68351 | 185.682ms | 14795 | 1280 | 195391 | 1807.6 | 0.0663423 | 1(Win) | true |
| Glaze | 3331.2 | 0.415924 | 438.48ms | 14795 | 640 | 198627 | 4235.6 | 0.236653 | 2(Loss) | true |
| simdjson (reflection) | 242.252 | 0.17445 | 5693.12ms | 14795 | 4890 | 5.04833e+07 | 58243.6 | 0.0755565 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8039.66 | 0.75107 | 188.226ms | 14795 | 1280 | 222395 | 1755 | 0.125513 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 3381.33 | 0.351588 | 413.688ms | 14795 | 1280 | 275507 | 4172.8 | 5.86564 | -(Loss) | false |
| simdjson (reflection) | 243.739 | 0.178139 | 5562.39ms | 14795 | 4890 | 5.20003e+07 | 57888.2 | 0.456217 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1107.64 | 0.663877 | 287.862ms | 3223 | 1280 | 434422 | 2775 | 0.480562 | 1(Win) | true |
| Jsonifier (two-stage) | 802.717 | 0.589198 | 372.6ms | 3223 | 4890 | 2.48902e+06 | 3829.11 | 0.242006 | 2(Loss) | true |
| Glaze | 745.648 | 0.278356 | 402.26ms | 3223 | 4890 | 643817 | 4122.18 | 2.14277 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 672.875 | 1.35768 | 482.091ms | 3223 | 160 | 615418 | 4568 | 1.48378 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 663.406 | 0.530735 | 458.613ms | 3223 | 2560 | 1.54795e+06 | 4633.2 | 2.70066 | 4(Tie) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1580.8 | 0.391789 | 264.97ms | 3223 | 4890 | 283781 | 1944.4 | 0.338498 | 1(Win) | true |
| Jsonifier (two-stage) | 1082.67 | 0.436707 | 350.431ms | 3223 | 2560 | 393506 | 2839 | 0.546486 | 2(Loss) | true |
| Glaze | 1012.3 | 0.309164 | 370.776ms | 3223 | 4890 | 430912 | 3036.35 | 0.963878 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 812.287 | 0.798681 | 449.896ms | 3223 | 320 | 292280 | 3784 | 0.339415 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 798.86 | 0.665546 | 441.54ms | 3223 | 1280 | 839356 | 3847.6 | 1.06115 | 4(Tie) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6842.59 | 2.19995 | 46.2349ms | 3223 | 2560 | 250003 | 449.2 | 0.62724 | 1(Win) | true |
| simdjson (reflection) | 5604.84 | 4.2464 | 51.3879ms | 3223 | 640 | 347070 | 548.4 | 1.40533 | 2(Loss) | true |
| Glaze | 1541.47 | 0.753891 | 194.672ms | 3223 | 1280 | 289252 | 1994 | 0.0601443 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8609.78 | 2.66608 | 39.019ms | 3223 | 2560 | 231912 | 357 | 1.97694 | 1(Win) | true |
| simdjson (reflection) | 6993.73 | 1.64231 | 47.873ms | 3223 | 4890 | 254754 | 439.493 | 0.22864 | 2(Loss) | true |
| Glaze | 2044.9 | 0.687375 | 162.198ms | 3223 | 2560 | 273277 | 1503.1 | 1.42314 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1396.17 | 0.486261 | 403.923ms | 5839 | 1280 | 481445 | 3988.4 | 0.170204 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1375.62 | 2.00647 | 355.702ms | 5839 | 80 | 527762 | 4048 | 0.396825 | 1(Tie) | true |
| simdjson (ondemand) | 1236.65 | 0.288749 | 473.272ms | 5839 | 4890 | 826666 | 4502.88 | 0.048386 | 3(Loss) | true |
| Glaze | 1207.29 | 0.423991 | 509.198ms | 5839 | 1280 | 489528 | 4612.4 | 0.987464 | 4(Loss) | true |
| simdjson (reflection) | 1164.18 | 0.595357 | 460.279ms | 5839 | 2560 | 2.07602e+06 | 4783.2 | 0.366606 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1993.59 | 0.45135 | 355.535ms | 5839 | 2560 | 406884 | 2793.2 | 0.569557 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1988.75 | 1.19881 | 392.501ms | 5839 | 160 | 180276 | 2800 | 0.114416 | 1(Tie) | true |
| simdjson (reflection) | 1447.19 | 0.323734 | 463.554ms | 5839 | 4890 | 758771 | 3847.8 | 3.37986 | 3(Loss) | true |
| simdjson (ondemand) | 1399.26 | 0.827707 | 453.32ms | 5839 | 640 | 694403 | 3979.6 | 0.616909 | 4(Loss) | true |
| Glaze | 1271.12 | 1.25426 | 472.285ms | 5839 | 160 | 483060 | 4380.8 | 4.74369 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13346.1 | 1.76905 | 51.605ms | 6938 | 4890 | 376143 | 495.771 | 1.98281 | 1(Win) | true |
| Glaze | 2487.1 | 1.44725 | 309.903ms | 6960 | 160 | 238691 | 2668.8 | 0.239234 | 2(Loss) | true |
| simdjson (reflection) | 278.823 | 0.787739 | 2235.66ms | 6938 | 320 | 1.11821e+07 | 23730.4 | 0.433002 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14217 | 3.01136 | 43.0351ms | 6938 | 1280 | 251414 | 465.4 | 2.42077 | 1(Win) | true |
| Glaze | 2284.88 | 0.594165 | 290.837ms | 6960 | 1280 | 381343 | 2905 | 1.71569 | 2(Loss) | true |
| simdjson (reflection) | 347.393 | 0.258271 | 2247.14ms | 6938 | 40 | 96791.6 | 19046.4 | 0.0896861 | 3(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1620.94 | 1.01997 | 339.582ms | 4857 | 160 | 135925 | 2857.6 | 0.334821 | 1(Win) | true |
| Glaze | 1109.19 | 0.728633 | 410.652ms | 4857 | 640 | 592542 | 4176 | 1.30021 | 2(Loss) | true |
| Jsonifier (two-stage) | 994.832 | 0.765807 | 432.898ms | 4857 | 4890 | 6.21705e+06 | 4656.06 | 1.59191 | 3(Loss) | true |
| simdjson (reflection) | 969.402 | 0.716253 | 503.449ms | 4857 | 1280 | 1.49924e+06 | 4778.2 | 0.924774 | 4(Loss) | true |
| simdjson (ondemand) | 798.097 | 0.754166 | 572.209ms | 4857 | 1280 | 2.45227e+06 | 5803.8 | 0.259121 | 5(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 2016.02 | 1.8692 | 326.64ms | 4857 | 640 | 1.18043e+06 | 2297.6 | 3.07121 | 1(Tie) | true |
| Glaze STATISTICAL TIE | 1962.71 | 1.17547 | 303.634ms | 4857 | 320 | 246261 | 2360 | 0.545331 | 1(Tie) | true |
| Jsonifier (two-stage) | 1370.41 | 1.06327 | 389.791ms | 4857 | 320 | 413308 | 3380 | 1.14647 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1129.42 | 0.269225 | 479.225ms | 4857 | 1280 | 156050 | 4101.2 | 0.39829 | 4(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1127.79 | 0.309763 | 457.823ms | 4857 | 4890 | 791495 | 4107.15 | 0.987237 | 4(Tie) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11086.1 | 1.73478 | 47.3751ms | 4857 | 4890 | 256905 | 417.819 | 0.258004 | 1(Win) | true |
| simdjson (reflection) | 8431.01 | 2.56833 | 61.4812ms | 4857 | 1280 | 254852 | 549.4 | 0.918442 | 2(Loss) | true |
| Glaze | 2557.42 | 2.42184 | 204.305ms | 4857 | 80 | 153927 | 1811.2 | 0.711744 | 3(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12989.3 | 3.9536 | 41.4131ms | 4857 | 1280 | 254424 | 356.6 | 0.281215 | 1(Win) | true |
| simdjson (reflection) | 7661.79 | 1.54415 | 61.577ms | 4857 | 4890 | 426149 | 604.558 | 2.25945 | 2(Loss) | true |
| Glaze | 2731.94 | 0.564075 | 181.81ms | 4857 | 2560 | 234158 | 1695.5 | 0.00589762 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1627.26 | 0.450799 | 397.821ms | 6701 | 1280 | 401183 | 3927.2 | 1.87818 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1385.4 | 1.63238 | 436.292ms | 6701 | 160 | 907176 | 4612.8 | 0.0346741 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1363.64 | 1.13175 | 495.957ms | 6701 | 160 | 450094 | 4686.4 | 0.577054 | 2(Tie) | true |
| simdjson (reflection) | 1186.05 | 0.406523 | 550.139ms | 6701 | 2560 | 1.22824e+06 | 5388.1 | 2.12472 | 4(Loss) | true |
| simdjson (ondemand) | 1021.67 | 0.775644 | 617.997ms | 6701 | 1280 | 3.01293e+06 | 6255 | 0.833915 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2265.04 | 0.328616 | 353.868ms | 6701 | 2560 | 220063 | 2821.4 | 0.430548 | 1(Win) | true |
| Glaze | 2107.71 | 0.631588 | 364.403ms | 6701 | 640 | 234696 | 3032 | 0.905218 | 2(Loss) | true |
| Jsonifier (two-stage) | 1883.12 | 1.11225 | 430.264ms | 6701 | 1280 | 1.82363e+06 | 3393.6 | 2.90684 | 3(Loss) | true |
| simdjson (reflection) | 1629.58 | 0.344503 | 500.657ms | 6701 | 640 | 116814 | 3921.6 | 2.64151 | 4(Loss) | true |
| simdjson (ondemand) | 1326.79 | 0.253316 | 527.245ms | 6701 | 4890 | 727962 | 4816.57 | 0.570387 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11657.7 | 1.16783 | 64.6948ms | 7376 | 4890 | 242822 | 603.406 | 0.433777 | 1(Win) | true |
| Glaze | 2245.66 | 0.782949 | 327.106ms | 7376 | 640 | 384947 | 3132.4 | 0.655527 | 2(Loss) | true |
| simdjson (reflection) | 289.035 | 0.509843 | 2343.73ms | 7376 | 640 | 9.85359e+06 | 24337.2 | 1.18398 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13292.3 | 2.767 | 57.835ms | 7376 | 1280 | 274453 | 529.2 | 3.68339 | 1(Win) | true |
| Glaze | 2212.6 | 0.839 | 328.029ms | 7376 | 640 | 455344 | 3179.2 | 1.92498 | 2(Loss) | true |
| simdjson (reflection) | 303.197 | 0.36928 | 2318.66ms | 7376 | 1280 | 9.39535e+06 | 23200.4 | 1.68822 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1329.7 | 1.99292 | 124.744ms | 1691 | 320 | 186942 | 1212.8 | 3.41064 | 1(Win) | true |
| Glaze | 1155.7 | 1.00337 | 159.596ms | 1691 | 1280 | 250917 | 1395.4 | 1.5575 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1093.48 | 1.36918 | 160.194ms | 1691 | 640 | 260957 | 1474.8 | 0.682687 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1074.54 | 2.6607 | 164.553ms | 1691 | 160 | 255127 | 1500.8 | 0.845666 | 3(Tie) | true |
| Jsonifier (two-stage) | 1036.68 | 1.28546 | 152.585ms | 1691 | 640 | 255913 | 1555.6 | 0.96054 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1888.59 | 1.05359 | 113.428ms | 1691 | 2560 | 207205 | 853.9 | 0.939675 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1615.25 | 1.42843 | 133.729ms | 1691 | 30 | 6101.63 | 998.4 | 0.847458 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1553.03 | 1.78808 | 130.802ms | 1691 | 320 | 110320 | 1038.4 | 1.66667 | 2(Tie) | true |
| simdjson (ondemand) | 1337.64 | 0.70434 | 148.753ms | 1691 | 2560 | 184591 | 1205.6 | 0.266134 | 4(Loss) | true |
| simdjson (reflection) | 1165.24 | 0.726016 | 174.985ms | 1691 | 4890 | 493690 | 1383.97 | 0.247185 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9371.26 | 2.95753 | 23.5169ms | 1996 | 4890 | 176479 | 203.125 | 0.96307 | 1(Win) | true |
| simdjson (reflection) | 8120.88 | 3.65519 | 25.769ms | 1996 | 2560 | 187920 | 234.4 | 0.509338 | 2(Loss) | true |
| Glaze | 2487.63 | 2.23484 | 76.1321ms | 1996 | 640 | 187165 | 765.2 | 0.468262 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE DID NOT CONVERGE | 11740.5 | 3.51879 | 18.7489ms | 1996 | 4890 | 159163 | 162.133 | 5.14483 | -(Tie) | false |
| simdjson (reflection) STATISTICAL TIE | 10754.4 | 6.04424 | 20.8809ms | 1996 | 1280 | 146501 | 177 | 1.72414 | 1(Tie) | true |
| Glaze | 3005.74 | 2.37701 | 65.5862ms | 1996 | 2560 | 580124 | 633.3 | 0.779758 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1569.58 | 1.41118 | 142.757ms | 2158 | 640 | 219119 | 1311.2 | 3.47468 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1414.36 | 1.56397 | 156.497ms | 2158 | 2560 | 1.32581e+06 | 1455.1 | 1.4427 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1411.35 | 1.03906 | 153.402ms | 2158 | 1280 | 293850 | 1458.2 | 2.17209 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1321.11 | 0.690664 | 162.281ms | 2158 | 2560 | 296345 | 1557.8 | 0.319939 | 4(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1284.66 | 1.25053 | 166.222ms | 2158 | 640 | 256858 | 1602 | 0.273904 | 4(Tie) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2096.84 | 0.800295 | 125.431ms | 2158 | 4890 | 301704 | 981.49 | 3.97144 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1824.12 | 0.489237 | 135.559ms | 2158 | 4890 | 148985 | 1128.23 | 1.66087 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1788.66 | 1.08927 | 143.834ms | 2158 | 2560 | 402126 | 1150.6 | 2.04325 | 2(Tie) | true |
| simdjson (ondemand) | 1572.94 | 1.40844 | 150ms | 2158 | 640 | 217338 | 1308.4 | 1.53522 | 4(Loss) | true |
| simdjson (reflection) | 1496.1 | 0.714445 | 162.317ms | 2158 | 2560 | 247264 | 1375.6 | 0.650007 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13511.6 | 2.85022 | 23.53ms | 2866 | 4890 | 162556 | 202.287 | 0.841035 | 1(Win) | true |
| Glaze | 2737.61 | 1.23176 | 111.295ms | 2866 | 40 | 6049.48 | 998.4 | 0.847458 | 2(Loss) | true |
| simdjson (reflection) | 360.509 | 0.244343 | 773.777ms | 2866 | 4890 | 1.67813e+06 | 7581.58 | 0.686314 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 15176.2 | 4.23237 | 21.142ms | 2866 | 2560 | 148742 | 180.1 | 5.50892 | -(Win) | false |
| Glaze | 3084 | 0.599076 | 94.593ms | 2866 | 4890 | 137847 | 886.263 | 1.11987 | 2(Loss) | true |
| simdjson (reflection) | 365.405 | 0.706257 | 765.137ms | 2866 | 160 | 446528 | 7480 | 1.41291 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1607.15 | 0.43281 | 272.409ms | 4390 | 2560 | 325424 | 2605 | 0.0920457 | 1(Win) | true |
| Jsonifier (two-stage) | 1179.2 | 1.14922 | 372.143ms | 4390 | 160 | 266366 | 3550.4 | 0.316456 | 2(Loss) | true |
| Glaze | 960.501 | 0.603114 | 443.192ms | 4390 | 640 | 442296 | 4358.8 | 0.0642792 | 3(Loss) | true |
| simdjson (reflection) | 944.627 | 0.201031 | 453.915ms | 4390 | 4890 | 388188 | 4432.05 | 0.0958951 | 4(Loss) | true |
| simdjson (ondemand) | 669.338 | 0.369676 | 631.519ms | 4390 | 4890 | 2.6145e+06 | 6254.88 | 1.26782 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2058.83 | 0.301794 | 254.835ms | 4390 | 2560 | 96416.2 | 2033.5 | 0.601232 | 1(Win) | true |
| Jsonifier (two-stage) | 1397.78 | 0.627179 | 370.937ms | 4390 | 40 | 14115.4 | 2995.2 | 0 | 2(Loss) | true |
| Glaze | 1142.58 | 0.253674 | 418.774ms | 4390 | 4890 | 422493 | 3664.2 | 0.468944 | 3(Loss) | true |
| simdjson (reflection) | 1047.15 | 0.336472 | 448.058ms | 4390 | 4890 | 884942 | 3998.1 | 1.07959 | 4(Loss) | true |
| simdjson (ondemand) | 787.39 | 0.232522 | 589.301ms | 4390 | 2560 | 391308 | 5317.1 | 0.855463 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9452.77 | 2.55141 | 46.6501ms | 4390 | 2560 | 326898 | 442.9 | 0.842441 | 1(Win) | true |
| simdjson (reflection) | 6660.25 | 5.25321 | 62.5549ms | 4390 | 1280 | 1.39575e+06 | 628.6 | 2.57833 | 2(Loss) | true |
| Glaze | 1635.2 | 0.385601 | 259.514ms | 4390 | 4890 | 476620 | 2560.31 | 0.951135 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10002.6 | 1.72269 | 45.1789ms | 4390 | 4890 | 254227 | 418.552 | 2.52628 | 1(Win) | true |
| simdjson (reflection) | 7767.96 | 1.33052 | 56.7212ms | 4390 | 4890 | 251457 | 538.961 | 1.97142 | 2(Loss) | true |
| Glaze | 1772.19 | 1.18871 | 246.259ms | 4390 | 320 | 252354 | 2362.4 | 0.579019 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2234.7 | 0.572402 | 446.283ms | 9378 | 30 | 15743.7 | 4002.13 | 0.213675 | 1(Win) | true |
| Jsonifier | 2098.24 | 0.475725 | 406.046ms | 9378 | 1280 | 526297 | 4262.4 | 0.386246 | 2(Loss) | true |
| simdjson (reflection) | 1775.64 | 0.364862 | 521.32ms | 9378 | 160 | 54036.3 | 5036.8 | 0 | 3(Loss) | true |
| Glaze | 1434.69 | 0.41117 | 631.587ms | 9378 | 1280 | 840926 | 6233.8 | 1.75566 | 4(Loss) | true |
| simdjson (ondemand) | 1299.86 | 0.565508 | 672.932ms | 9378 | 640 | 968912 | 6880.4 | 0.437931 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2606.23 | 0.264115 | 395.31ms | 9378 | 4890 | 401689 | 3431.6 | 2.16148 | 1(Win) | true |
| Jsonifier (two-stage) | 2494.87 | 0.239354 | 416.637ms | 9378 | 4890 | 360012 | 3584.79 | 1.44107 | 2(Loss) | true |
| simdjson (reflection) | 1949.46 | 0.264537 | 499.804ms | 9378 | 2560 | 377054 | 4587.7 | 1.58107 | 3(Loss) | true |
| Glaze | 1750.62 | 0.524477 | 591.02ms | 9378 | 160 | 114871 | 5108.8 | 0.343321 | 4(Loss) | true |
| simdjson (ondemand) | 1494.4 | 0.187611 | 656.147ms | 9378 | 2560 | 322730 | 5984.7 | 0.705137 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17887.5 | 1.16783 | 65.247ms | 11521 | 4890 | 251621 | 614.243 | 0.39842 | 1(Win) | true |
| Glaze | 2548.78 | 0.592027 | 424.278ms | 11521 | 640 | 416848 | 4310.8 | 0.305273 | 2(Loss) | true |
| simdjson (reflection) | 303.617 | 0.13921 | 3673.52ms | 11521 | 4890 | 1.24102e+07 | 36187.9 | 0.112677 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 18394.9 | 1.6334 | 62.273ms | 11521 | 2560 | 243673 | 597.3 | 3.48233 | 1(Win) | true |
| Glaze | 2880.47 | 0.707414 | 421.462ms | 11521 | 640 | 465993 | 3814.4 | 1.31747 | 2(Loss) | true |
| simdjson (reflection) | 308.732 | 0.129957 | 3567.48ms | 11521 | 2560 | 5.47591e+06 | 35588.4 | 0.439774 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2672.05 | 1.12981 | 176.698ms | 4669 | 640 | 226858 | 1666.4 | 0.287219 | 1(Win) | true |
| Jsonifier (two-stage) | 1566.28 | 0.477216 | 300.577ms | 4669 | 4890 | 900013 | 2842.86 | 0.785494 | 2(Loss) | true |
| Glaze | 1442.13 | 0.480696 | 329.818ms | 4669 | 640 | 140982 | 3087.6 | 0.0129567 | 3(Loss) | true |
| simdjson (reflection) | 1228.44 | 0.249869 | 378.024ms | 4669 | 4890 | 401119 | 3624.68 | 0.119115 | 4(Loss) | true |
| simdjson (ondemand) | 1027.15 | 0.428944 | 435.781ms | 4669 | 1280 | 442578 | 4335 | 0.626741 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2819.24 | 0.843337 | 190.722ms | 4669 | 2560 | 454179 | 1579.4 | 1.3245 | 1(Win) | true |
| Jsonifier (two-stage) | 1718.4 | 0.614861 | 275.118ms | 4669 | 1280 | 324912 | 2591.2 | 0.0154345 | 2(Loss) | true |
| Glaze | 1600.8 | 0.279123 | 293.803ms | 4669 | 4890 | 294764 | 2781.55 | 0.441943 | 3(Loss) | true |
| simdjson (reflection) | 1271.47 | 0.481023 | 373.771ms | 4669 | 1280 | 363224 | 3502 | 0.297858 | 4(Loss) | true |
| simdjson (ondemand) | 1163.62 | 0.387958 | 400.019ms | 4669 | 1280 | 282102 | 3826.6 | 0.328193 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13316.7 | 2.06375 | 36.2322ms | 4669 | 4890 | 232851 | 334.371 | 0.95659 | 1(Win) | true |
| simdjson (reflection) | 7593.29 | 4.78817 | 65.334ms | 4669 | 320 | 252277 | 586.4 | 2.26667 | 2(Loss) | true |
| Glaze | 1652.15 | 0.47887 | 255.701ms | 4669 | 2560 | 426407 | 2695.1 | 2.99115 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14345.1 | 2.95755 | 33.4441ms | 4669 | 2560 | 215749 | 310.4 | 0.844704 | 1(Win) | true |
| simdjson (reflection) | 7814.51 | 2.44634 | 61.7052ms | 4669 | 1280 | 248706 | 569.8 | 0.869868 | 2(Loss) | true |
| Glaze | 2056.12 | 0.278553 | 217.144ms | 4669 | 4890 | 177941 | 2165.58 | 0.874884 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2685.32 | 0.534768 | 289.136ms | 7932 | 1280 | 290479 | 2817 | 0.564044 | 1(Win) | true |
| Jsonifier (two-stage) | 2332.43 | 1.09486 | 330.358ms | 7932 | 160 | 201737 | 3243.2 | 0.637255 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1846.81 | 0.333452 | 411.784ms | 7932 | 1280 | 238779 | 4096 | 0.311526 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 1826.83 | 0.918675 | 429.238ms | 7932 | 80 | 115766 | 4140.8 | 0.936037 | 3(Tie) | true |
| simdjson (ondemand) | 1613.32 | 0.381152 | 482.122ms | 7932 | 1280 | 408818 | 4688.8 | 0.246788 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2809.38 | 0.647858 | 282.086ms | 7932 | 1280 | 389506 | 2692.6 | 0.485147 | 1(Win) | true |
| Jsonifier (two-stage) | 2467.59 | 0.176568 | 326.827ms | 7932 | 4890 | 143269 | 3065.56 | 0.165357 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 2015.49 | 0.456742 | 394.324ms | 7932 | 1280 | 376145 | 3753.2 | 0.771997 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1979.83 | 1.22003 | 408.712ms | 7932 | 80 | 173836 | 3820.8 | 0 | 3(Tie) | true |
| simdjson (ondemand) | 1722.62 | 0.413614 | 470.753ms | 7932 | 2560 | 844533 | 4391.3 | 0.206799 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15667 | 1.75513 | 59.1959ms | 9249 | 2560 | 249964 | 563 | 0.859907 | 1(Win) | true |
| Glaze | 2193.84 | 0.343113 | 411.19ms | 9249 | 1280 | 243593 | 4020.6 | 0.882556 | 2(Loss) | true |
| simdjson (reflection) | 290.884 | 1.15445 | 2995.77ms | 9249 | 80 | 9.80369e+06 | 30323.2 | 1.78275 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17376.9 | 2.76861 | 54.5661ms | 9249 | 1280 | 252799 | 507.6 | 0.392465 | 1(Win) | true |
| Glaze | 2344.12 | 0.252657 | 387.929ms | 9249 | 4890 | 441978 | 3762.83 | 1.07265 | 2(Loss) | true |
| simdjson (reflection) | 316.587 | 0.990091 | 2912.26ms | 9249 | 30 | 2.28284e+06 | 27861.3 | 0.214856 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 602.64 | 0.22151 | 759.392ms | 4604 | 2560 | 666780 | 7285.8 | 0.286304 | 1(Win) | true |
| Jsonifier (two-stage) | 436.349 | 0.883345 | 934.096ms | 4604 | 640 | 5.05642e+06 | 10062.4 | 2.58543 | 2(Loss) | true |
| simdjson (reflection) | 420.662 | 0.408534 | 1035.57ms | 4604 | 4890 | 8.89138e+06 | 10437.6 | 2.0888 | 3(Loss) | true |
| Glaze STATISTICAL TIE | 351.64 | 1.5818 | 1202.21ms | 4604 | 80 | 3.1208e+06 | 12486.4 | 2.64471 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 345.34 | 0.205814 | 1302.63ms | 4604 | 4890 | 3.3484e+06 | 12714.2 | 0.197847 | 4(Tie) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 696.409 | 0.650288 | 769.11ms | 4604 | 640 | 1.07581e+06 | 6304.8 | 0.780562 | 1(Win) | true |
| Jsonifier (two-stage) | 553.349 | 0.656324 | 917.151ms | 4604 | 1280 | 3.47151e+06 | 7934.8 | 1.53035 | 2(Loss) | true |
| simdjson (reflection) | 520.511 | 0.376862 | 971.129ms | 4604 | 2560 | 2.58712e+06 | 8435.4 | 0.692237 | 3(Loss) | true |
| Glaze | 434.174 | 0.384012 | 1104.75ms | 4604 | 2560 | 3.86076e+06 | 10112.8 | 0.980568 | 4(Loss) | true |
| simdjson (ondemand) | 422.098 | 0.886815 | 1247.04ms | 4604 | 30 | 255289 | 10402.1 | 0.743802 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1673.04 | 0.67656 | 258.477ms | 4604 | 2560 | 807074 | 2624.4 | 0.837624 | 1(Win) | true |
| simdjson (reflection) | 1562.56 | 0.609804 | 306.376ms | 4918 | 40 | 13401.3 | 3001.6 | 0.0710227 | 2(Loss) | true |
| Glaze | 979.178 | 0.251571 | 447.365ms | 4604 | 4890 | 622267 | 4484.08 | 0.142561 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1843.83 | 0.454392 | 242.771ms | 4604 | 2560 | 299729 | 2381.3 | 0.459838 | 1(Win) | true |
| simdjson (reflection) | 1565.9 | 0.627179 | 306.325ms | 4918 | 40 | 14115.4 | 2995.2 | 0 | 2(Loss) | true |
| Glaze | 1051.05 | 0.183871 | 421.78ms | 4604 | 4890 | 288510 | 4177.46 | 0.0177276 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 1734.98 | 0.272479 | 1114.84ms | 18245 | 40 | 29869.3 | 10028.8 | 0.98989 | 1(Win) | true |
| Jsonifier (two-stage) | 1682.11 | 0.718564 | 1047.15ms | 18245 | 160 | 883950 | 10344 | 1.2374 | 2(Loss) | true |
| Jsonifier | 1554.16 | 0.665946 | 1160.96ms | 18245 | 1280 | 7.11512e+06 | 11195.6 | 0.0214416 | 3(Loss) | true |
| simdjson (ondemand) | 1313.67 | 0.237621 | 1371.08ms | 18245 | 640 | 633968 | 13245.2 | 0.063379 | 4(Loss) | true |
| Glaze | 1173.85 | 0.608509 | 1540.57ms | 18245 | 1280 | 1.04137e+07 | 14822.8 | 0.0889728 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2073.38 | 0.329224 | 1026.89ms | 18245 | 640 | 488533 | 8392 | 1.09372 | 1(Win) | true |
| Jsonifier | 1930.91 | 0.394777 | 1139.53ms | 18245 | 30 | 37965.7 | 9011.2 | 0.471254 | 2(Loss) | true |
| simdjson (reflection) | 1837.17 | 0.195382 | 1084.98ms | 18245 | 4890 | 1.67442e+06 | 9470.95 | 0.182826 | 3(Loss) | true |
| simdjson (ondemand) | 1477.36 | 0.522297 | 1433.13ms | 18245 | 320 | 1.21087e+06 | 11777.6 | 1.99707 | 4(Loss) | true |
| Glaze | 1276.24 | 0.738797 | 1533.57ms | 18245 | 640 | 6.49309e+06 | 13633.6 | 0.21664 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8071.75 | 0.313583 | 307.393ms | 24579 | 2560 | 212294 | 2904 | 0.966553 | 1(Win) | true |
| Glaze | 2962.04 | 1.07489 | 845.924ms | 24579 | 160 | 1.15771e+06 | 7913.6 | 3.77432 | 2(Loss) | true |
| simdjson (reflection) | 309.857 | 0.0737105 | 7795.95ms | 24893 | 4890 | 1.55955e+07 | 76615.3 | 0.130739 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8830.76 | 0.754805 | 274.533ms | 24579 | 640 | 256911 | 2654.4 | 0.1207 | 1(Win) | true |
| Glaze | 2895.44 | 1.01197 | 746.273ms | 24579 | 640 | 4.29545e+06 | 8095.6 | 0.163318 | 2(Loss) | true |
| simdjson (reflection) | 313.236 | 0.275616 | 7872.5ms | 24893 | 80 | 3.49066e+06 | 75788.8 | 0.118084 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 704.001 | 1.07871 | 732.041ms | 4604 | 80 | 362097 | 6236.8 | 0.257202 | 1(Win) | true |
| simdjson (reflection) | 513.792 | 0.223349 | 867.632ms | 4604 | 2560 | 932617 | 8545.7 | 0.566648 | 2(Loss) | true |
| Jsonifier (two-stage) | 479.189 | 0.382937 | 907.499ms | 4604 | 1280 | 1.57587e+06 | 9162.8 | 1.02761 | 3(Loss) | true |
| Glaze | 424.257 | 0.165757 | 1067.16ms | 4604 | 2560 | 753349 | 10349.2 | 0.110275 | 4(Loss) | true |
| simdjson (ondemand) | 372.745 | 0.125757 | 1191.66ms | 4604 | 4890 | 1.07305e+06 | 11779.4 | 0.356949 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 930.059 | 0.206643 | 629.23ms | 4604 | 2560 | 243630 | 4720.9 | 1.87687 | 1(Win) | true |
| Jsonifier (two-stage) | 724.7 | 0.793298 | 770.821ms | 4604 | 30 | 69302.4 | 6058.67 | 0.140647 | 2(Loss) | true |
| simdjson (reflection) | 631.894 | 0.289062 | 840.744ms | 4604 | 2560 | 1.03277e+06 | 6948.5 | 2.13932 | 3(Loss) | true |
| Glaze | 505.075 | 0.338949 | 1062.32ms | 4604 | 640 | 555657 | 8693.2 | 0.485482 | 4(Loss) | true |
| simdjson (ondemand) | 409.803 | 0.211282 | 1246.19ms | 4604 | 1280 | 655928 | 10714.2 | 2.53215 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1903.46 | 0.431839 | 234.858ms | 4604 | 2560 | 254018 | 2306.7 | 0.744406 | 1(Win) | true |
| simdjson (reflection) | 1506.45 | 0.484136 | 320.987ms | 4918 | 1280 | 290814 | 3113.4 | 0.238249 | 2(Loss) | true |
| Glaze | 996.798 | 0.355992 | 447.102ms | 4604 | 4890 | 1.20239e+06 | 4404.82 | 3.48705 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1783.68 | 0.573756 | 246.259ms | 4604 | 2560 | 510658 | 2461.6 | 0.33423 | 1(Win) | true |
| simdjson (reflection) | 1677.46 | 0.735288 | 290.057ms | 4918 | 1280 | 541002 | 2796 | 0.667898 | 2(Loss) | true |
| Glaze | 1116.89 | 0.249843 | 402.469ms | 4604 | 2560 | 246960 | 3931.2 | 0.606796 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1950.09 | 0.0909104 | 904.823ms | 18245 | 4890 | 321748 | 8922.57 | 0.242316 | 1(Win) | true |
| Jsonifier | 1887.34 | 0.625286 | 935.358ms | 18245 | 160 | 531697 | 9219.2 | 0.0346981 | 2(Loss) | true |
| simdjson (reflection) | 1733.05 | 0.236857 | 998.924ms | 18245 | 1280 | 723855 | 10040 | 0.00398391 | 3(Loss) | true |
| simdjson (ondemand) | 1339.79 | 0.0901571 | 1313.23ms | 18245 | 2560 | 350960 | 12987 | 0.0738655 | 4(Loss) | true |
| Glaze | 1253.22 | 0.114332 | 1427.45ms | 18245 | 4890 | 1.2322e+06 | 13884.1 | 0.330964 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2349.06 | 0.123301 | 886.212ms | 18245 | 4890 | 407892 | 7407.14 | 0.0181309 | 1(Win) | true |
| Jsonifier | 2275.31 | 0.16007 | 909.479ms | 18245 | 2560 | 383586 | 7647.2 | 0.0392147 | 2(Loss) | true |
| simdjson (reflection) | 2147.62 | 0.117493 | 945.666ms | 18245 | 2560 | 231973 | 8101.9 | 0.00617177 | 3(Loss) | true |
| simdjson (ondemand) | 1508.75 | 0.094313 | 1353.23ms | 18245 | 4890 | 578500 | 11532.6 | 0.210572 | 4(Loss) | true |
| Glaze | 1451.27 | 0.147768 | 1365.66ms | 18245 | 30 | 9416.09 | 11989.3 | 0.42523 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8941.92 | 0.551833 | 290.319ms | 24579 | 1280 | 267850 | 2621.4 | 0.0228938 | 1(Win) | true |
| Glaze | 3259.21 | 0.104043 | 725.343ms | 24579 | 4890 | 273805 | 7192.03 | 0.0184884 | 2(Loss) | true |
| simdjson (reflection) | 322.443 | 0.211131 | 7706.9ms | 24893 | 320 | 7.73222e+06 | 73624.8 | 0.0597268 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9535.27 | 0.313157 | 255.541ms | 24579 | 4890 | 289798 | 2458.28 | 0.191613 | 1(Win) | true |
| Glaze | 3820.44 | 0.107225 | 619.722ms | 24579 | 4890 | 211643 | 6135.52 | 0.0557561 | 2(Loss) | true |
| simdjson (reflection) | 323.212 | 0.356671 | 7924.45ms | 24893 | 80 | 5.49041e+06 | 73449.6 | 0.380478 | 3(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1149.02 | 0.186926 | 419.082ms | 5094 | 4890 | 305432 | 4227.98 | 0.679397 | 1(Win) | true |
| Jsonifier (two-stage) | 975.831 | 0.348293 | 544.57ms | 5094 | 4890 | 1.47016e+06 | 4978.34 | 4.6314 | 2(Loss) | true |
| simdjson (reflection) | 864.724 | 0.217087 | 575.978ms | 5094 | 2560 | 380778 | 5618 | 0.457139 | 3(Loss) | true |
| Glaze | 743.009 | 0.272295 | 648.918ms | 5094 | 2560 | 811424 | 6538.3 | 1.75357 | 4(Loss) | true |
| simdjson (ondemand) | 601.895 | 0.706706 | 755.193ms | 5094 | 320 | 1.04113e+06 | 8071.2 | 1.2342 | 5(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1304.83 | 0.281239 | 491.753ms | 5094 | 4890 | 536129 | 3723.1 | 0.013393 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1289.9 | 0.527853 | 456.905ms | 5094 | 1280 | 505874 | 3766.2 | 0.0903582 | 1(Tie) | true |
| Glaze | 1084.62 | 0.351052 | 562.713ms | 5094 | 1280 | 316457 | 4479 | 0.271642 | 3(Loss) | true |
| simdjson (reflection) | 1033.22 | 0.343899 | 572.082ms | 5094 | 1280 | 334657 | 4701.8 | 0.0553286 | 4(Loss) | true |
| simdjson (ondemand) | 775.979 | 0.368013 | 741.598ms | 5094 | 2560 | 1.35889e+06 | 6260.5 | 0.481656 | 5(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11677.9 | 4.71228 | 46.154ms | 5094 | 640 | 245939 | 416 | 0.952381 | 1(Win) | true |
| simdjson (reflection) | 8045.74 | 1.65458 | 62.1481ms | 5094 | 2560 | 255506 | 603.8 | 0.165344 | 2(Loss) | true |
| Glaze | 1852.08 | 0.627873 | 239.425ms | 5094 | 1280 | 347176 | 2623 | 1.16476 | 3(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 10137.8 | 4.14291 | 53.131ms | 5094 | 640 | 252246 | 479.2 | 0.498339 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 10081 | 1.50795 | 51.9959ms | 5094 | 4890 | 258222 | 481.898 | 0.290895 | 1(Tie) | true |
| Glaze | 2262.28 | 0.625714 | 229.387ms | 5094 | 1280 | 231094 | 2147.4 | 0.913621 | 3(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1515.72 | 0.475987 | 534.664ms | 8051 | 320 | 186038 | 5065.6 | 1.18249 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 1290.9 | 0.174701 | 606.656ms | 8051 | 1280 | 138202 | 5947.8 | 0.32047 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1278.48 | 0.703893 | 587.491ms | 8051 | 320 | 571842 | 6005.6 | 0.200214 | 2(Tie) | true |
| simdjson (ondemand) | 1106.73 | 0.402514 | 727.375ms | 8051 | 80 | 62383.6 | 6937.6 | 0.184162 | 4(Loss) | true |
| Glaze | 1024.28 | 0.80649 | 712.549ms | 8051 | 320 | 1.16952e+06 | 7496 | 3.05763 | 5(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1910.34 | 0.923775 | 512.051ms | 8051 | 30 | 41355.5 | 4019.2 | 0.211864 | 1(Win) | true |
| Jsonifier (two-stage) | 1854.33 | 0.14733 | 557.399ms | 8051 | 4890 | 181977 | 4140.6 | 0.385572 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1454.93 | 0.156902 | 662.944ms | 8051 | 4890 | 335262 | 5277.26 | 1.5399 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1450.33 | 0.403634 | 616.045ms | 8051 | 640 | 292229 | 5294 | 0.022662 | 3(Tie) | true |
| simdjson (ondemand) | 1358.1 | 0.221767 | 666.112ms | 8051 | 2560 | 402409 | 5653.5 | 0.224136 | 5(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 13330.9 | 1.09802 | 66.9169ms | 9255 | 4890 | 258445 | 662.092 | 5.49593 | -(Win) | false |
| Glaze | 2581.46 | 0.312048 | 348.774ms | 9255 | 2560 | 291411 | 3419.1 | 0.049696 | 2(Loss) | true |
| simdjson (reflection) | 318.78 | 0.241644 | 2710.5ms | 9255 | 1280 | 5.72973e+06 | 27687.6 | 0.788316 | 3(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16396.5 | 1.84295 | 56.1001ms | 9255 | 2560 | 251951 | 538.3 | 0.20393 | 1(Win) | true |
| Glaze | 2976.61 | 0.21877 | 320.496ms | 9255 | 2560 | 107727 | 2965.2 | 0.345178 | 2(Loss) | true |
| simdjson (reflection) | 330.958 | 0.35294 | 2920ms | 9255 | 160 | 1.41751e+06 | 26668.8 | 0.542888 | 3(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 3568.87 | 2.19131 | 82.432ms | 2889 | 640 | 183157 | 772 | 2.55048 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 3462.37 | 0.786273 | 83.234ms | 2889 | 4890 | 191428 | 795.746 | 0.556558 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3351.25 | 0.743539 | 85.7661ms | 2889 | 4890 | 182725 | 822.132 | 1.47031 | 3(Tie) | true |
| Jsonifier STATISTICAL TIE | 3262.09 | 1.62342 | 84.011ms | 2889 | 1280 | 240644 | 844.6 | 3 | 3(Tie) | true |
| Glaze | 2381.14 | 0.774394 | 119.221ms | 2889 | 4890 | 392607 | 1157.08 | 0.122735 | 5(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 3944.97 | 2.62335 | 81.303ms | 2889 | 640 | 214832 | 698.4 | 0.344828 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 3917.81 | 1.2744 | 76.6149ms | 2889 | 4890 | 392761 | 703.241 | 0.503551 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 3627.01 | 1.32943 | 82.0549ms | 2889 | 4890 | 498695 | 759.624 | 0.897101 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3567.02 | 2.17601 | 86.4591ms | 2889 | 640 | 180794 | 772.4 | 1.63158 | 3(Tie) | true |
| Glaze | 2425.03 | 0.56785 | 118.465ms | 2889 | 4890 | 203535 | 1136.14 | 0.828667 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 4033.31 | 0.696843 | 94.3529ms | 3808 | 2560 | 100782 | 900.4 | 0.222618 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3971.56 | 1.82621 | 95.4749ms | 3808 | 320 | 89233.1 | 914.4 | 0.439367 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 3909.98 | 1.19919 | 99.2991ms | 3808 | 1280 | 158792 | 928.8 | 0.129366 | 3(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 3909.44 | 0.555384 | 97.2979ms | 3808 | 4890 | 130155 | 928.929 | 1.75259 | 3(Tie) | true |
| Glaze | 2747.29 | 1.04104 | 129.802ms | 3808 | 4890 | 926044 | 1321.88 | 0.0894519 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4335.71 | 1.26249 | 91.765ms | 3808 | 1280 | 143133 | 837.6 | 0.0477327 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4295.56 | 0.671578 | 92.798ms | 3808 | 4890 | 157636 | 845.428 | 1.3042 | 1(Tie) | true |
| simdjson (reflection) | 4200.88 | 0.623679 | 91.8162ms | 3808 | 4890 | 142150 | 864.484 | 0.691068 | 3(Loss) | true |
| simdjson (ondemand) | 4099.34 | 0.639788 | 94.537ms | 3808 | 4890 | 157089 | 885.896 | 1.47952 | 4(Loss) | true |
| Glaze | 2897.62 | 0.658632 | 130.888ms | 3808 | 4890 | 333200 | 1253.3 | 1.12027 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2024.67 | 1.42856 | 148.243ms | 2889 | 640 | 241862 | 1360.8 | 2.63309 | 1(Win) | true |
| Glaze | 1751.31 | 0.891976 | 170.696ms | 2889 | 1280 | 252048 | 1573.2 | 0.177665 | 2(Loss) | true |
| Jsonifier (two-stage) | 1557.96 | 0.605655 | 187.416ms | 2889 | 4890 | 560971 | 1768.44 | 1.26505 | 3(Loss) | true |
| simdjson (reflection) | 1144.46 | 0.627034 | 261.12ms | 2889 | 1280 | 291668 | 2407.4 | 0.223806 | 4(Loss) | true |
| simdjson (ondemand) | 855.854 | 1.83278 | 312.304ms | 2889 | 320 | 1.11395e+06 | 3219.2 | 4.46521 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2348.22 | 0.705862 | 141.566ms | 2889 | 2560 | 175589 | 1173.3 | 0.348225 | 1(Win) | true |
| Glaze | 1904.32 | 1.60891 | 198.872ms | 2889 | 640 | 346787 | 1446.8 | 1.12083 | 2(Loss) | true |
| Jsonifier (two-stage) | 1705.67 | 1.00786 | 183.288ms | 2889 | 2560 | 678495 | 1615.3 | 1.05731 | 3(Loss) | true |
| simdjson (reflection) | 1299.12 | 0.975826 | 235.455ms | 2889 | 320 | 137055 | 2120.8 | 3.80987 | 4(Loss) | true |
| simdjson (ondemand) | 1010.91 | 0.542732 | 309.274ms | 2889 | 4890 | 1.06992e+06 | 2725.43 | 2.74999 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10679.9 | 2.52598 | 30.6051ms | 2963 | 4890 | 218424 | 264.586 | 1.56783 | 1(Win) | true |
| simdjson (reflection) | 8594.09 | 4.0256 | 35.202ms | 2963 | 1280 | 224251 | 328.8 | 0.611995 | 2(Loss) | true |
| Glaze | 3240.52 | 1.84681 | 97.8811ms | 2963 | 640 | 165981 | 872 | 1.35747 | 3(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11038 | 2.79692 | 27.807ms | 2963 | 4890 | 250696 | 256 | 3.7232 | 1(Win) | true |
| simdjson (reflection) | 9060.94 | 2.31113 | 36.4449ms | 2963 | 4890 | 254023 | 311.859 | 0.308557 | 2(Loss) | true |
| Glaze | 3003.55 | 1.01298 | 93.6602ms | 2963 | 1280 | 116253 | 940.8 | 0.341297 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2184.55 | 2.36099 | 188.62ms | 3808 | 160 | 246479 | 1662.4 | 0.0963391 | 1(Win) | true |
| Jsonifier (two-stage) | 2079.6 | 0.4933 | 185.748ms | 3808 | 4890 | 362883 | 1746.3 | 0.749837 | 2(Loss) | true |
| Glaze | 1741.27 | 0.773937 | 214.939ms | 3808 | 1280 | 333490 | 2085.6 | 1.65724 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1315.79 | 1.64651 | 255.144ms | 3808 | 320 | 660843 | 2760 | 2.67857 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1278.32 | 0.611868 | 288.733ms | 3808 | 4890 | 1.47755e+06 | 2840.92 | 0.0626367 | 4(Tie) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2355.81 | 0.858876 | 181.887ms | 3808 | 4890 | 857205 | 1541.55 | 2.55694 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 2217.9 | 1.04867 | 176.641ms | 3808 | 2560 | 754787 | 1637.4 | 2.61687 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 2169.93 | 3.61961 | 193.379ms | 3808 | 80 | 293574 | 1673.6 | 0.191571 | 2(Tie) | true |
| simdjson (reflection) | 1739.93 | 0.771773 | 230.759ms | 3808 | 1280 | 332137 | 2087.2 | 0.928433 | 4(Loss) | true |
| simdjson (ondemand) | 1343.04 | 1.74815 | 291.1ms | 3808 | 160 | 357511 | 2704 | 1.31894 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13463.7 | 2.20699 | 32.961ms | 4300 | 4890 | 220963 | 304.582 | 1.39228 | 1(Win) | true |
| Glaze | 2603.35 | 0.988291 | 144.897ms | 4300 | 1280 | 310207 | 1575.2 | 4.60271 | 2(Loss) | true |
| simdjson (reflection) | 352.06 | 1.1578 | 1127.84ms | 4300 | 160 | 2.90996e+06 | 11648 | 1.16753 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16408 | 2.48589 | 28.4621ms | 4300 | 4890 | 188756 | 249.927 | 1.47267 | 1(Win) | true |
| Glaze | 3503.76 | 1.30003 | 118.886ms | 4300 | 640 | 148168 | 1170.4 | 1.17566 | 2(Loss) | true |
| simdjson (reflection) | 375.972 | 0.604507 | 1144.06ms | 4300 | 640 | 2.78233e+06 | 10907.2 | 1.02253 | 3(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2295.5 | 0.568408 | 10384.2ms | 466906 | 40 | 4.86277e+07 | 193978 | 0.356157 | 1(Win) | true |
| Glaze | 1579.64 | 0.665125 | 7741.09ms | 466906 | 80 | 2.81216e+08 | 281885 | 0.482513 | 2(Loss) | true |
| simdjson (ondemand) | 1229.14 | 0.598842 | 9937.12ms | 466906 | 30 | 1.41189e+08 | 362266 | 0.499503 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 2464.34 | 0.123654 | 5011.06ms | 466906 | 640 | 3.19489e+07 | 180688 | 5.40965 | -(Win) | false |
| Glaze | 1513.61 | 0.329097 | 7582.96ms | 466906 | 640 | 5.99869e+08 | 294181 | 0.700224 | 2(Loss) | true |
| simdjson (ondemand) | 1100.72 | 0.650029 | 5392.74ms | 466906 | 320 | 2.2127e+09 | 404533 | 2.14691 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2804.4 | 0.315625 | 6048.88ms | 699405 | 1280 | 7.21326e+08 | 237842 | 1.88152 | 1(Win) | true |
| Glaze | 2175.98 | 0.197656 | 7797.74ms | 699405 | 640 | 2.34935e+08 | 306531 | 0.308962 | 2(Loss) | true |
| simdjson (ondemand) | 1392.92 | 0.583587 | 6560.12ms | 767297 | 80 | 7.51931e+08 | 525338 | 0.103445 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3008.56 | 0.679222 | 5887.25ms | 699405 | 40 | 9.07035e+07 | 221702 | 1.17254 | 1(Win) | true |
| Glaze | 2145.01 | 0.171403 | 7845.53ms | 699405 | 1280 | 3.6362e+08 | 310957 | 0.282442 | 2(Loss) | true |
| simdjson (ondemand) | 1479.03 | 0.159848 | 6504.21ms | 767297 | 640 | 4.00281e+08 | 494751 | 0.685873 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2095.86 | 0.286172 | 7682.48ms | 631514 | 320 | 2.16393e+08 | 287356 | 0.369124 | 1(Win) | true |
| Glaze | 1636 | 0.566697 | 8696.64ms | 631514 | 160 | 6.96342e+08 | 368130 | 0.329226 | 2(Loss) | true |
