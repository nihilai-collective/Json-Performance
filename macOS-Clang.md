# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the Clang 23.1.3 compiler).  

Latest Results: (Oct 23, 2026)
#### Using the following commits:
----
| Jsonifier: [b975cd7](https://github.com/nihilai-collective/jsonifier/commit/b975cd7)  
| Glaze: [1f8adf7](https://github.com/stephenberry/glaze/commit/1f8adf7)  
| Simdjson: [957ddbc](https://github.com/simdjson/simdjson/commit/957ddbc)  

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
*Environment generated via BenchmarkSuite commit: [ab75024](https://github.com/nihilai-collective/benchmarksuite/commit/ab75024)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| glaze STATISTICAL TIE | 1214.91 | 0.205032 | 92.4902ms | 905 | 40 | 84.8615 | 710.4 | 0.285407 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 1212.71 | 0.307087 | 86.9382ms | 905 | 160 | 764.239 | 711.694 | 0.111405 | 1(Tie) | true |
| jsonifier (two-stage) | 246.297 | 0.229836 | 375.632ms | 905 | 30 | 1945.96 | 3504.2 | 1.32627 | 3(Loss) | true |
| simdjson (ondemand) | 171.926 | 0.347287 | 495.86ms | 905 | 2560 | 778089 | 5020.03 | 0.502313 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| glaze | 1270.78 | 0.291956 | 78.1654ms | 905 | 160 | 629.085 | 679.169 | 0.235944 | 1(Win) | true |
| jsonifier | 1129.89 | 0.346379 | 82.052ms | 905 | 2560 | 17921.3 | 763.861 | 2.88666 | 2(Loss) | true |
| jsonifier (two-stage) | 256.438 | 0.100772 | 377.046ms | 905 | 80 | 920.237 | 3365.62 | 0.309531 | 3(Loss) | true |
| simdjson (ondemand) | 183.916 | 0.449414 | 487.946ms | 905 | 2560 | 1.13865e+06 | 4692.76 | 0.542561 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2029.35 | 0.122701 | 53.1577ms | 905 | 1280 | 348.567 | 425.296 | 0.148094 | 1(Win) | true |
| glaze | 117.309 | 0.859474 | 745.682ms | 905 | 160 | 639766 | 7357.29 | 0.950619 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2903.37 | 0.882089 | 43.1355ms | 905 | 30 | 206.271 | 297.267 | 0.011212 | 1(Win) | true |
| glaze | 719.229 | 0.306694 | 146.223ms | 905 | 30 | 406.345 | 1200 | 0.464499 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 953.964 | 0.216802 | 204.654ms | 1811 | 40 | 616.254 | 1810.45 | 0.350122 | 1(Win) | true |
| glaze | 793.688 | 0.769569 | 221.277ms | 1811 | 80 | 22434.8 | 2176.05 | 1.13919 | 2(Loss) | true |
| jsonifier (two-stage) | 326.218 | 0.199574 | 545.294ms | 1811 | 4890 | 545932 | 5294.33 | 0.694838 | 3(Loss) | true |
| simdjson (ondemand) | 197.948 | 0.0865974 | 922.226ms | 1811 | 40 | 2283.51 | 8725.02 | 0.125248 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1140.83 | 0.27463 | 180.742ms | 1811 | 30 | 518.576 | 1513.9 | 0.184611 | 1(Win) | true |
| glaze | 1007.45 | 0.178607 | 178.606ms | 1811 | 160 | 1500.06 | 1714.33 | 0.289212 | 2(Loss) | true |
| jsonifier (two-stage) | 354.201 | 0.099755 | 514.012ms | 1811 | 80 | 1892.77 | 4876.06 | 2.24926 | 3(Loss) | true |
| simdjson (ondemand) | 187.355 | 0.38309 | 895.263ms | 1811 | 1280 | 1.59631e+06 | 9218.34 | 1.10441 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 277.803 | 0.264783 | 629.482ms | 1811 | 4890 | 1.32511e+06 | 6217.01 | 0.035413 | 1(Win) | true |
| glaze | 208.646 | 0.324267 | 849.177ms | 1798 | 2560 | 1.81805e+06 | 8218.26 | 0.0641214 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 777.815 | 0.735283 | 227.495ms | 1811 | 320 | 85299 | 2220.46 | 1.32457 | 1(Win) | true |
| glaze | 620.827 | 0.711377 | 298.289ms | 1798 | 640 | 247069 | 2761.97 | 0.554235 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1670.48 | 0.326762 | 202.464ms | 3862 | 320 | 16609.4 | 2204.81 | 0.301956 | 1(Win) | true |
| glaze | 1352.15 | 0.444396 | 304.023ms | 3862 | 40 | 5861.04 | 2723.88 | 0.318266 | 2(Loss) | true |
| simdjson (ondemand) | 498.512 | 0.37878 | 830.686ms | 3862 | 320 | 250610 | 7388.17 | 1.10007 | 3(Loss) | true |
| jsonifier (two-stage) | 462.683 | 0.318492 | 658.731ms | 3862 | 320 | 205686 | 7960.29 | 1.10062 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2042.13 | 0.364692 | 163.905ms | 3862 | 1280 | 55375.7 | 1803.55 | 1.25557 | 1(Win) | true |
| glaze | 1188.86 | 0.23252 | 294.15ms | 3862 | 4890 | 253741 | 3098 | 0.541979 | 2(Loss) | true |
| jsonifier (two-stage) | 577.608 | 0.783463 | 590.014ms | 3862 | 320 | 798630 | 6376.45 | 0.901029 | 3(Loss) | true |
| simdjson (ondemand) | 460.406 | 0.315848 | 815.588ms | 3862 | 1280 | 817161 | 7999.65 | 0.0597453 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3249.88 | 0.562335 | 136.019ms | 3862 | 40 | 1624.57 | 1133.3 | 0.123381 | 1(Win) | true |
| glaze | 560.214 | 0.065484 | 761.653ms | 3862 | 80 | 1482.78 | 6574.44 | 0.244857 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3105.25 | 0.19368 | 129.919ms | 3862 | 4890 | 25805.3 | 1186.08 | 0.763053 | 1(Win) | true |
| glaze | 2237.91 | 0.202162 | 186.912ms | 3862 | 40 | 442.794 | 1645.78 | 0.179431 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1234.35 | 1.65145 | 782.581ms | 9578 | 40 | 597396 | 7400.07 | 0.297644 | 1(Win) | true |
| glaze | 1058.51 | 0.220807 | 914.661ms | 9578 | 4890 | 1.77539e+06 | 8629.37 | 0.378474 | 2(Loss) | true |
| simdjson (ondemand) | 884.399 | 0.309293 | 1150.01ms | 9578 | 640 | 653091 | 10328.2 | 0.50593 | 3(Loss) | true |
| jsonifier (two-stage) | 622.794 | 1.35864 | 1460.16ms | 9578 | 80 | 3.17659e+06 | 14666.6 | 0.600086 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2415.04 | 0.127794 | 704.362ms | 9578 | 40 | 934.5 | 3782.25 | 0.196477 | 1(Win) | true |
| glaze | 1587.39 | 0.501558 | 869.781ms | 9578 | 640 | 533093 | 5754.27 | 1.15109 | 2(Loss) | true |
| simdjson (ondemand) | 1031.97 | 0.81895 | 1107.65ms | 9578 | 320 | 1.68145e+06 | 8851.35 | 0.090723 | 3(Loss) | true |
| jsonifier (two-stage) | 861.87 | 0.237182 | 1356.7ms | 9578 | 1280 | 808796 | 10598.2 | 2.03876 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| glaze | 1167.64 | 0.0869065 | 913.021ms | 9578 | 40 | 1848.83 | 7822.88 | 0.994621 | 1(Win) | true |
| jsonifier DID NOT CONVERGE | 1139.5 | 0.229534 | 854.452ms | 9578 | 4890 | 1.65549e+06 | 8016.07 | 5.69817 | -(Loss) | false |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8200.97 | 0.167936 | 142.883ms | 9578 | 160 | 559.792 | 1113.81 | 3.92942 | 1(Win) | true |
| glaze | 3958.43 | 0.909482 | 230.902ms | 9578 | 160 | 70471.4 | 2307.56 | 3.72848 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2339.72 | 0.0993887 | 184.106ms | 3873 | 160 | 393.879 | 1578.64 | 0.428509 | 1(Win) | true |
| glaze | 1533.01 | 0.245763 | 264.217ms | 3873 | 640 | 22439.7 | 2409.37 | 1.72021 | 2(Loss) | true |
| jsonifier (two-stage) | 650.919 | 0.184082 | 591.178ms | 3873 | 640 | 69830.2 | 5674.4 | 0.303234 | 3(Loss) | true |
| simdjson (ondemand) | 385.95 | 1.10845 | 917.924ms | 3873 | 160 | 1.80046e+06 | 9570.09 | 2.20977 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2817.08 | 0.0672421 | 138.226ms | 3873 | 640 | 497.462 | 1311.14 | 0.113085 | 1(Win) | true |
| glaze | 1451.27 | 0.309072 | 248.589ms | 3873 | 2560 | 158400 | 2545.06 | 3.99979 | 2(Loss) | true |
| jsonifier (two-stage) | 650.986 | 0.256617 | 579.781ms | 3873 | 640 | 135676 | 5673.83 | 0.199889 | 3(Loss) | true |
| simdjson (ondemand) | 501.249 | 0.10207 | 905.298ms | 3873 | 40 | 2262.81 | 7368.75 | 0.0648717 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3439.29 | 0.229275 | 110.367ms | 3873 | 80 | 485.021 | 1073.94 | 0.0943682 | 1(Win) | true |
| glaze | 488.812 | 0.192658 | 755.901ms | 3873 | 4890 | 1.03633e+06 | 7556.23 | 1.00639 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3692.85 | 0.378421 | 112.992ms | 3873 | 640 | 9168.55 | 1000.2 | 2.28335 | 1(Win) | true |
| glaze | 1871.53 | 1.03876 | 203.722ms | 3873 | 30 | 12608.3 | 1973.57 | 1.52846 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 646.566 | 0.824373 | 9208.54ms | 2090234 | 40 | 2.58388e+10 | 3.08306e+06 | 2.70751 | 1(Win) | true |
| jsonifier (two-stage) | 562.492 | 0.725867 | 5121.88ms | 2090234 | 30 | 1.98515e+10 | 3.54388e+06 | 2.72035 | 2(Loss) | true |
| glaze DID NOT CONVERGE | 494.933 | 1.06843 | 5870.45ms | 2090234 | 80 | 1.48143e+11 | 4.02762e+06 | 8.05452 | -(Loss) | false |
| simdjson (ondemand) | 453.436 | 0.589845 | 6877.94ms | 2090234 | 80 | 5.37926e+10 | 4.39621e+06 | 2.41262 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 865.733 | 1.55305 | 8618.41ms | 2090234 | 30 | 3.83633e+10 | 2.30256e+06 | 1.66083 | 1(Win) | true |
| jsonifier (two-stage) | 731.308 | 0.656022 | 5080.17ms | 2090234 | 80 | 2.55809e+10 | 2.72581e+06 | 0.253941 | 2(Loss) | true |
| glaze | 575.508 | 0.963752 | 6165.78ms | 2090234 | 80 | 8.91472e+10 | 3.46373e+06 | 2.6744 | 3(Loss) | true |
| simdjson (ondemand) | 495.625 | 1.06997 | 7018.39ms | 2090234 | 30 | 5.55585e+10 | 4.022e+06 | 0.6729 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2678.56 | 0.754285 | 9119.09ms | 2090234 | 80 | 2.52086e+09 | 744206 | 3.03027 | 1(Win) | true |
| glaze | 1675.22 | 1.21688 | 6928.55ms | 2090234 | 30 | 6.29017e+09 | 1.18994e+06 | 0.365733 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2704.92 | 0.169713 | 9466.27ms | 2090234 | 640 | 1.00113e+09 | 736954 | 1.22485 | 1(Win) | true |
| glaze | 1984.93 | 0.135714 | 6534.54ms | 2090234 | 30 | 5.5728e+07 | 1.00427e+06 | 0.142507 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 1760.12 | 0.49309 | 5428.82ms | 6661897 | 80 | 2.53427e+10 | 3.60957e+06 | 0.578818 | 1(Tie) | true |
| jsonifier STATISTICAL TIE DID NOT CONVERGE | 1751.86 | 1.56467 | 5409.26ms | 6661897 | 30 | 9.6597e+10 | 3.6266e+06 | 5.95364 | -(Tie) | false |
| glaze | 1343.92 | 0.284541 | 7820.47ms | 6661897 | 30 | 5.42826e+09 | 4.72742e+06 | 2.25031 | 3(Loss) | true |
| simdjson (ondemand) | 1247.24 | 0.591413 | 7572.35ms | 6661897 | 80 | 7.2605e+10 | 5.09387e+06 | 1.05264 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2098.51 | 0.941227 | 5385.35ms | 6661897 | 30 | 2.43605e+10 | 3.02753e+06 | 1.56834 | 1(Win) | true |
| jsonifier (two-stage) | 1736.24 | 0.855804 | 5964.86ms | 6661897 | 40 | 3.92269e+10 | 3.65921e+06 | 1.18959 | 2(Loss) | true |
| simdjson (ondemand) | 1427.21 | 0.999144 | 7593.42ms | 6661897 | 40 | 7.91287e+10 | 4.45153e+06 | 0.103351 | 3(Loss) | true |
| glaze | 1391.87 | 0.735555 | 7520.09ms | 6661897 | 40 | 4.50912e+10 | 4.56458e+06 | 3.97208 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6769.01 | 2.10373 | 5545.23ms | 6661897 | 40 | 1.5595e+10 | 938583 | 3.93386 | 1(Win) | true |
| glaze | 3307.73 | 0.509273 | 6536.5ms | 6661897 | 40 | 3.82734e+09 | 1.92074e+06 | 2.36315 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 6448.37 | 1.05842 | 5767.66ms | 6661897 | 320 | 3.47987e+10 | 985254 | 5.34362 | -(Win) | false |
| glaze | 3556.42 | 0.674428 | 5657.57ms | 6661897 | 160 | 2.32253e+10 | 1.78643e+06 | 1.08119 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2005.87 | 0.400752 | 6304.44ms | 500299 | 1280 | 1.1631e+09 | 237863 | 2.5309 | 1(Win) | true |
| jsonifier (two-stage) | 1398.99 | 1.94868 | 8936.52ms | 500299 | 30 | 1.32505e+09 | 341049 | 0.136207 | 2(Loss) | true |
| glaze | 1087.74 | 0.803147 | 5702.54ms | 500299 | 160 | 1.98571e+09 | 438635 | 2.39042 | 3(Loss) | true |
| simdjson (ondemand) | 958.007 | 0.429149 | 6318.47ms | 500299 | 640 | 2.92361e+09 | 498036 | 4.71568 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2617.49 | 0.625082 | 5959.55ms | 500299 | 320 | 4.15445e+08 | 182283 | 0.669265 | 1(Win) | true |
| jsonifier (two-stage) | 1755.79 | 0.156474 | 8393.76ms | 500299 | 320 | 5.78559e+07 | 271743 | 0.252504 | 2(Loss) | true |
| glaze | 1069.78 | 0.971789 | 5728.39ms | 500299 | 640 | 1.20225e+10 | 446000 | 2.41497 | 3(Loss) | true |
| simdjson (ondemand) | 974.477 | 0.90286 | 6685.01ms | 500299 | 640 | 1.25065e+10 | 489619 | 0.432893 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7190.35 | 0.991905 | 6510.77ms | 500299 | 640 | 2.77255e+08 | 66355.9 | 0.652887 | 1(Win) | true |
| glaze | 1775.39 | 0.74109 | 7167.19ms | 500299 | 320 | 1.26929e+09 | 268742 | 1.66098 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7425.15 | 0.217938 | 6453.02ms | 500299 | 2560 | 5.02058e+07 | 64257.6 | 2.59464 | 1(Win) | true |
| glaze | 1829.17 | 0.821369 | 6463.89ms | 500299 | 160 | 7.34424e+08 | 260841 | 1.74762 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3511.86 | 0.980988 | 9850.02ms | 1439562 | 30 | 4.412e+08 | 390925 | 0.174137 | 1(Win) | true |
| jsonifier (two-stage) | 2926.57 | 1.12433 | 6354.65ms | 1439562 | 40 | 1.11274e+09 | 469106 | 0.115205 | 2(Loss) | true |
| glaze | 2107.18 | 0.298643 | 8518.22ms | 1439562 | 640 | 2.42294e+09 | 651522 | 3.57264 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1873.04 | 1.56881 | 8651.68ms | 1439562 | 80 | 1.05779e+10 | 732965 | 7.29492 | -(Loss) | false |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4152.3 | 0.508859 | 10099.7ms | 1439562 | 30 | 8.49178e+07 | 330629 | 4.50136 | 1(Win) | true |
| jsonifier (two-stage) | 3732.58 | 1.40115 | 5992.25ms | 1439562 | 40 | 1.06236e+09 | 367808 | 1.4696 | 2(Loss) | true |
| glaze | 2302.09 | 0.347446 | 8073.78ms | 1439562 | 640 | 2.74772e+09 | 596360 | 0.372072 | 3(Loss) | true |
| simdjson (ondemand) | 2183.81 | 0.879019 | 7770.13ms | 1439562 | 160 | 4.88595e+09 | 628661 | 0.202366 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 18747.8 | 0.757259 | 7720.96ms | 1439562 | 160 | 4.92007e+07 | 73228.6 | 0.371861 | 1(Win) | true |
| glaze | 2809 | 0.434679 | 6274.97ms | 1439584 | 640 | 2.88862e+09 | 488749 | 1.19351 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 17610 | 0.267897 | 7828.06ms | 1439562 | 1280 | 5.58326e+07 | 77959.9 | 0.181157 | 1(Win) | true |
| glaze | 3111.42 | 1.17092 | 5455.59ms | 1439584 | 80 | 2.1355e+09 | 441243 | 0.0346118 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2196.59 | 1.00508 | 2469.32ms | 56369 | 160 | 9.68063e+06 | 24473.2 | 0.761476 | 1(Win) | true |
| glaze | 1380.7 | 0.47513 | 3896.47ms | 56369 | 640 | 2.19022e+07 | 38935.1 | 0.140409 | 2(Loss) | true |
| simdjson (ondemand) | 1241.05 | 0.292213 | 4359.37ms | 56369 | 640 | 1.02538e+07 | 43316.4 | 1.89905 | 3(Loss) | true |
| jsonifier (two-stage) | 1198.41 | 1.24586 | 4827.05ms | 56369 | 40 | 1.2493e+07 | 44857.3 | 0.745834 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2804.27 | 0.729373 | 2063.16ms | 56369 | 1280 | 2.50236e+07 | 19169.9 | 1.14874 | 1(Win) | true |
| glaze | 1615.06 | 0.326552 | 3659.75ms | 56369 | 4890 | 5.77719e+07 | 33285.2 | 0.429554 | 2(Loss) | true |
| simdjson (ondemand) | 1492.89 | 0.226308 | 3761.01ms | 56369 | 4890 | 3.2474e+07 | 36009.1 | 0.0273052 | 3(Loss) | true |
| jsonifier (two-stage) | 1181.04 | 0.289918 | 5223.83ms | 56369 | 2560 | 4.45801e+07 | 45517.1 | 0.460776 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10843.2 | 0.515845 | 526.96ms | 56369 | 2560 | 1.67433e+06 | 4957.72 | 2.3346 | 1(Win) | true |
| glaze | 2511.88 | 1.54501 | 2395.25ms | 56369 | 30 | 3.27997e+06 | 21401.4 | 1.02163 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12851.2 | 0.634517 | 439.133ms | 56369 | 1280 | 901753 | 4183.07 | 0.0575464 | 1(Win) | true |
| glaze | 2711.78 | 0.761025 | 2101.86ms | 56369 | 160 | 3.64158e+06 | 19823.7 | 3.5125 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 2186.86 | 0.0406796 | 4496.12ms | 94370 | 30 | 8408.16 | 41154.1 | 0.239256 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 2176.63 | 1.16975 | 3599.16ms | 94370 | 320 | 7.48569e+07 | 41347.4 | 1.60573 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 2019.55 | 0.492786 | 4773.45ms | 94370 | 80 | 3.85803e+06 | 44563.5 | 0.180095 | 3(Tie) | true |
| glaze STATISTICAL TIE | 1971.98 | 1.09717 | 4579.5ms | 94370 | 80 | 2.00588e+07 | 45638.6 | 0.817149 | 3(Tie) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2868.99 | 0.323955 | 3260.3ms | 94370 | 2560 | 2.64375e+07 | 31369.3 | 1.22748 | 1(Win) | true |
| simdjson (ondemand) | 2375.27 | 0.164906 | 3955.51ms | 94370 | 4890 | 1.90908e+07 | 37889.7 | 0.1087 | 2(Loss) | true |
| glaze | 2212.76 | 0.206599 | 4194.95ms | 94370 | 4890 | 3.45273e+07 | 40672.3 | 1.88094 | 3(Loss) | true |
| jsonifier (two-stage) | 1847.52 | 0.113124 | 5360.55ms | 94370 | 4890 | 1.48493e+07 | 48713 | 0.106032 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 17955.6 | 0.0753811 | 522.934ms | 94370 | 160 | 2284.08 | 5012.26 | 0.140333 | 1(Win) | true |
| glaze | 2389.95 | 0.242015 | 3726.57ms | 94370 | 4890 | 4.06145e+07 | 37656.9 | 0.973988 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 18552.1 | 0.17068 | 515.333ms | 94370 | 40 | 2742.25 | 4851.1 | 0.033658 | 1(Win) | true |
| glaze | 2822.65 | 0.162532 | 3369.44ms | 94370 | 40 | 107422 | 31884.3 | 0.397009 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2253.91 | 0.101602 | 528.045ms | 11812 | 80 | 2062.85 | 4997.9 | 0.00100041 | 1(Win) | true |
| jsonifier (two-stage) | 1045.59 | 1.17295 | 1161.78ms | 11812 | 160 | 2.55504e+06 | 10773.6 | 2.08454 | 2(Loss) | true |
| glaze | 981.802 | 0.389343 | 1212.59ms | 11812 | 30 | 59866.8 | 11473.6 | 0.80596 | 3(Loss) | true |
| simdjson (ondemand) | 808.833 | 0.522368 | 1253.45ms | 11812 | 640 | 3.38737e+06 | 13927.2 | 0.0382647 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2381.45 | 0.220484 | 569.571ms | 11812 | 40 | 4350.9 | 4730.23 | 0.0816342 | 1(Win) | true |
| jsonifier (two-stage) | 1280.43 | 0.376757 | 1017.39ms | 11812 | 2560 | 2.81253e+06 | 8797.67 | 0.0416707 | 2(Loss) | true |
| simdjson (ondemand) | 1114.46 | 0.0490814 | 1104.73ms | 11812 | 80 | 1969 | 10107.9 | 0.219149 | 3(Loss) | true |
| glaze | 1034.1 | 0.328069 | 1150.28ms | 11812 | 2560 | 3.26957e+06 | 10893.3 | 0.0447184 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9250.28 | 0.589925 | 122.208ms | 11812 | 640 | 33030.1 | 1217.78 | 0.362494 | 1(Win) | true |
| glaze | 1826.72 | 0.0601226 | 654.026ms | 11812 | 80 | 1099.69 | 6166.69 | 0.235188 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10887 | 0.278615 | 119.414ms | 11812 | 30 | 249.321 | 1034.7 | 0.132258 | 1(Win) | true |
| glaze | 1979.37 | 0.0412413 | 602.038ms | 11812 | 160 | 881.406 | 5691.09 | 0.019654 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3748.41 | 0.0647695 | 862.826ms | 31235 | 40 | 1059.72 | 7946.85 | 0.101401 | 1(Win) | true |
| jsonifier (two-stage) | 2345.1 | 0.270828 | 1423.67ms | 31235 | 320 | 378700 | 12702.2 | 0.2199 | 2(Loss) | true |
| glaze | 2154.83 | 0.0843693 | 1392.37ms | 31235 | 4890 | 665171 | 13823.8 | 0.111721 | 3(Loss) | true |
| simdjson (ondemand) | 1931.19 | 0.507231 | 1512.63ms | 31235 | 4890 | 2.99332e+07 | 15424.7 | 2.01168 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3881.14 | 0.110034 | 825.524ms | 31235 | 4890 | 348760 | 7675.06 | 0.316719 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 2344.74 | 0.564759 | 1545.47ms | 31235 | 4890 | 2.51727e+07 | 12704.2 | 4.38673 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2294.82 | 1.80071 | 1390.16ms | 31235 | 30 | 1.63907e+06 | 12980.6 | 0.805696 | 2(Tie) | true |
| glaze | 2094.98 | 0.202995 | 1416.44ms | 31235 | 2560 | 2.13274e+06 | 14218.8 | 1.3351 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 19938.2 | 0.345423 | 156.038ms | 31235 | 4890 | 130233 | 1494.01 | 1.96195 | 1(Win) | true |
| glaze | 2543.33 | 0.27522 | 1153.5ms | 31235 | 4890 | 5.08097e+06 | 11712.2 | 0.389394 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 23291.9 | 0.352579 | 141.779ms | 31235 | 640 | 13012.7 | 1278.9 | 2.28815 | 1(Win) | true |
| glaze | 3099.21 | 1.31339 | 1084.8ms | 31235 | 40 | 637426 | 9611.5 | 4.49464 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2326.07 | 1.25536 | 4153.02ms | 108313 | 80 | 2.48626e+07 | 44407.7 | 0.012612 | 1(Win) | true |
| jsonifier (two-stage) | 1572.07 | 0.343312 | 6865.2ms | 108313 | 1280 | 6.51339e+07 | 65706.6 | 0.402312 | 2(Loss) | true |
| glaze | 1407.24 | 2.01481 | 7284.61ms | 108313 | 30 | 6.56164e+07 | 73402.7 | 0.00599397 | 3(Loss) | true |
| simdjson (ondemand) | 1051.32 | 0.430587 | 9104.61ms | 108313 | 2560 | 4.58201e+08 | 98253.3 | 0.675559 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3052.55 | 0.890731 | 3936.59ms | 108313 | 80 | 7.26806e+06 | 33839 | 1.22401 | 1(Win) | true |
| jsonifier (two-stage) | 1673.02 | 0.310193 | 6078.17ms | 108313 | 4890 | 1.79363e+08 | 61741.9 | 0.237184 | 2(Loss) | true |
| glaze | 1473.38 | 0.473324 | 6776.65ms | 108313 | 1280 | 1.40949e+08 | 70107.9 | 1.39044 | 3(Loss) | true |
| simdjson (ondemand) | 1317.71 | 0.206628 | 7729.4ms | 108313 | 2560 | 6.71644e+07 | 78389.9 | 0.235073 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10688.6 | 1.13551 | 935.255ms | 108313 | 1280 | 1.54136e+07 | 9664.03 | 0.146885 | 1(Win) | true |
| glaze | 2074.55 | 0.610927 | 5388.53ms | 108313 | 30 | 2.77596e+06 | 49791.7 | 0.47459 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13573.9 | 1.02827 | 822.855ms | 108313 | 640 | 3.91872e+06 | 7609.82 | 0.544249 | 1(Win) | true |
| glaze | 2225.29 | 0.314462 | 5420.01ms | 108313 | 320 | 6.81829e+06 | 46418.9 | 0.211253 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3000.44 | 0.158404 | 6738.05ms | 213963 | 4890 | 5.67475e+07 | 68007.1 | 0.212679 | 1(Win) | true |
| jsonifier (two-stage) | 2572.75 | 0.60458 | 8020.92ms | 213963 | 320 | 7.35768e+07 | 79312.5 | 0.630016 | 2(Loss) | true |
| glaze STATISTICAL TIE | 2361.59 | 0.907767 | 9429.55ms | 213963 | 30 | 1.8456e+07 | 86404 | 0.139882 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2354.82 | 0.196147 | 5016.27ms | 213963 | 1280 | 3.69775e+07 | 86652.5 | 1.79665 | 3(Tie) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3408.27 | 0.364171 | 6538.33ms | 213963 | 640 | 3.04228e+07 | 59869.3 | 0.182201 | 1(Win) | true |
| jsonifier (two-stage) | 2954.67 | 0.647143 | 7859.07ms | 213963 | 320 | 6.39159e+07 | 69060.4 | 0.441364 | 2(Loss) | true |
| glaze | 2522.13 | 1.38064 | 8844.88ms | 213963 | 30 | 3.74302e+07 | 80904.1 | 0.154389 | 3(Loss) | true |
| simdjson (ondemand) | 2133.62 | 0.745402 | 9676.97ms | 213963 | 160 | 8.131e+07 | 95635.9 | 0.20649 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 23129 | 0.459208 | 950.404ms | 213963 | 1280 | 2.10084e+06 | 8822.3 | 2.62594 | 1(Win) | true |
| glaze | 2190.93 | 0.865352 | 5209.32ms | 213963 | 30 | 1.94863e+07 | 93134.6 | 0.12079 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 22243.4 | 0.38924 | 970.573ms | 213963 | 2560 | 3.26401e+06 | 9173.56 | 3.85385 | 1(Win) | true |
| glaze | 2377.74 | 0.577966 | 8973.84ms | 213963 | 160 | 3.93616e+07 | 85817.1 | 0.923104 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 580.432 | 1.24776 | 8962.56ms | 1834197 | 30 | 4.24204e+10 | 3.01366e+06 | 0.635247 | 1(Win) | true |
| jsonifier (two-stage) | 526.652 | 0.8196 | 5090.89ms | 1834197 | 40 | 2.96421e+10 | 3.32141e+06 | 4.18627 | 2(Loss) | true |
| glaze | 451.92 | 0.535185 | 5968ms | 1834197 | 80 | 3.43294e+10 | 3.87065e+06 | 2.49671 | 3(Loss) | true |
| simdjson (ondemand) | 393.486 | 0.660424 | 6812.98ms | 1834197 | 80 | 6.89554e+10 | 4.44546e+06 | 1.39289 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 768.293 | 1.02652 | 8451.61ms | 1834197 | 30 | 1.63868e+10 | 2.27677e+06 | 0.467992 | 1(Win) | true |
| jsonifier (two-stage) | 583.025 | 1.18605 | 5114.1ms | 1834197 | 30 | 3.7988e+10 | 3.00026e+06 | 0.371152 | 2(Loss) | true |
| glaze | 491.188 | 1.17691 | 6248.07ms | 1834197 | 30 | 5.26991e+10 | 3.56122e+06 | 1.05605 | 3(Loss) | true |
| simdjson (ondemand) | 444.113 | 0.622593 | 6871.11ms | 1834197 | 40 | 2.40533e+10 | 3.9387e+06 | 4.39464 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1184.99 | 0.964416 | 8714.01ms | 1834197 | 160 | 3.24275e+10 | 1.47616e+06 | 3.87355 | 1(Win) | true |
| glaze | 890.607 | 0.510912 | 6388.84ms | 1833577 | 30 | 3.01883e+09 | 1.96342e+06 | 1.12654 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1221.74 | 1.79202 | 8521.91ms | 1834197 | 40 | 2.63319e+10 | 1.43175e+06 | 2.30082 | 1(Win) | true |
| glaze | 855.383 | 0.627918 | 6589.44ms | 1833577 | 160 | 2.63635e+10 | 2.04427e+06 | 0.146312 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2463.71 | 0.862171 | 5860.76ms | 9930848 | 30 | 3.29536e+10 | 3.84412e+06 | 1.33448 | 1(Win) | true |
| jsonifier (two-stage) | 2365.18 | 0.389834 | 6278.16ms | 9930848 | 30 | 7.31012e+09 | 4.00426e+06 | 2.04921 | 2(Loss) | true |
| simdjson (ondemand) | 1749.26 | 0.54618 | 8031.08ms | 9930848 | 80 | 6.99561e+10 | 5.41418e+06 | 3.48284 | 3(Loss) | true |
| glaze DID NOT CONVERGE | 1699.05 | 1.19592 | 8310.77ms | 9930848 | 80 | 3.55509e+11 | 5.57416e+06 | 6.09856 | -(Loss) | false |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 2436.41 | 0.828466 | 6340.64ms | 9930848 | 80 | 8.29683e+10 | 3.88719e+06 | 0.541527 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 2353.61 | 2.75657 | 6052.25ms | 9930848 | 40 | 4.92153e+11 | 4.02394e+06 | 3.61649 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1896.75 | 0.594271 | 7957.84ms | 9930848 | 80 | 7.04389e+10 | 4.99317e+06 | 1.71977 | 3(Tie) | true |
| glaze STATISTICAL TIE | 1872.74 | 0.996971 | 8170.71ms | 9930848 | 30 | 7.62615e+10 | 5.05719e+06 | 0.220471 | 3(Tie) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6807.59 | 0.450009 | 8976.9ms | 9930848 | 320 | 1.25424e+10 | 1.39121e+06 | 1.09994 | 1(Win) | true |
| glaze DID NOT CONVERGE | 2841.36 | 0.673424 | 10410.7ms | 9930228 | 40 | 2.01513e+10 | 3.33298e+06 | 7.48726 | -(Loss) | false |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6543.01 | 0.386019 | 9052.66ms | 9930848 | 160 | 4.99524e+09 | 1.44747e+06 | 1.02022 | 1(Win) | true |
| glaze | 3152.6 | 0.418785 | 9552.19ms | 9930228 | 160 | 2.53211e+10 | 3.00393e+06 | 1.34298 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 681.112 | 0.589684 | 8015.82ms | 1834197 | 80 | 1.83478e+10 | 2.56819e+06 | 0.162932 | 1(Win) | true |
| jsonifier (two-stage) | 546.013 | 0.340635 | 9797.31ms | 1834197 | 160 | 1.90539e+10 | 3.20364e+06 | 0.35459 | 2(Loss) | true |
| glaze | 472.187 | 0.473899 | 5537.38ms | 1834197 | 80 | 2.46562e+10 | 3.70452e+06 | 0.14023 | 3(Loss) | true |
| simdjson (ondemand) | 407.328 | 0.494069 | 6496.81ms | 1834197 | 80 | 3.60137e+10 | 4.29439e+06 | 3.10619 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 784.159 | 0.470003 | 8346.87ms | 1834197 | 80 | 8.79377e+09 | 2.2307e+06 | 0.635307 | 1(Win) | true |
| jsonifier (two-stage) | 640.712 | 0.411255 | 9840.69ms | 1834197 | 160 | 2.01701e+10 | 2.73013e+06 | 2.545 | 2(Loss) | true |
| glaze | 532.953 | 0.618662 | 5634.59ms | 1834197 | 80 | 3.29845e+10 | 3.28214e+06 | 0.428579 | 3(Loss) | true |
| simdjson (ondemand) | 453.12 | 1.08809 | 6437.46ms | 1834197 | 30 | 5.2932e+10 | 3.86041e+06 | 0.229766 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1420.08 | 1.03068 | 7739.67ms | 1834197 | 30 | 4.83542e+09 | 1.23178e+06 | 0.452125 | 1(Win) | true |
| glaze | 822.398 | 0.460345 | 6739.54ms | 1833577 | 160 | 1.53293e+10 | 2.12626e+06 | 4.17612 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1418.13 | 0.303554 | 7823.37ms | 1834197 | 320 | 4.48623e+09 | 1.23347e+06 | 1.19315 | 1(Win) | true |
| glaze | 889.99 | 0.858253 | 6337.92ms | 1833577 | 30 | 8.53062e+09 | 1.96478e+06 | 1.18904 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2613.31 | 0.655537 | 5310.94ms | 9930848 | 80 | 4.51519e+10 | 3.62407e+06 | 1.35451 | 1(Win) | true |
| jsonifier (two-stage) | 2560.49 | 0.607841 | 5779.71ms | 9930848 | 40 | 2.02193e+10 | 3.69881e+06 | 1.41947 | 2(Loss) | true |
| glaze | 1919.96 | 0.494088 | 7568.18ms | 9930848 | 80 | 4.75211e+10 | 4.93281e+06 | 0.140964 | 3(Loss) | true |
| simdjson (ondemand) | 1810.19 | 0.360013 | 8042.77ms | 9930848 | 80 | 2.83826e+10 | 5.23194e+06 | 0.15278 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2977.93 | 0.886465 | 5329.79ms | 9930848 | 30 | 2.38445e+10 | 3.18033e+06 | 1.13669 | 1(Win) | true |
| jsonifier (two-stage) | 2651.51 | 0.79164 | 5918.62ms | 9930848 | 30 | 2.39862e+10 | 3.57184e+06 | 0.331863 | 2(Loss) | true |
| glaze STATISTICAL TIE | 1922.92 | 1.70085 | 7694.64ms | 9930848 | 30 | 2.10526e+11 | 4.92521e+06 | 2.67867 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1906.07 | 1.42145 | 8200.61ms | 9930848 | 30 | 1.49652e+11 | 4.96876e+06 | 3.64069 | 3(Tie) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6760.32 | 0.848249 | 9014.21ms | 9930848 | 40 | 5.64866e+09 | 1.40094e+06 | 0.484932 | 1(Win) | true |
| glaze | 2572.09 | 0.794536 | 5379.75ms | 9930228 | 80 | 6.84643e+10 | 3.68191e+06 | 0.693618 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6112.98 | 0.7614 | 9313.43ms | 9930848 | 40 | 5.56612e+09 | 1.54929e+06 | 1.37167 | 1(Win) | true |
| glaze | 2876.56 | 0.727175 | 9214.94ms | 9930228 | 30 | 1.71938e+10 | 3.2922e+06 | 4.09223 | 2(Loss) | true |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| glaze STATISTICAL TIE | 1109.64 | 0.686041 | 7134.53ms | 642697 | 160 | 2.29758e+09 | 552364 | 1.55853 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 1097.03 | 0.824478 | 6846.95ms | 642697 | 30 | 6.36585e+08 | 558712 | 0.387063 | 1(Tie) | true |
| jsonifier (two-stage) | 990.064 | 0.17861 | 8013.05ms | 642697 | 80 | 9.7811e+07 | 619074 | 0.00612772 | 3(Loss) | true |
| simdjson (ondemand) | 836.411 | 0.288824 | 9897.44ms | 642697 | 320 | 1.43347e+09 | 732802 | 0.762425 | 4(Loss) | true |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1293.59 | 0.14376 | 6540.49ms | 642697 | 40 | 1.85592e+07 | 473817 | 0.105334 | 1(Win) | true |
| glaze | 1151.81 | 0.845303 | 6801.42ms | 642697 | 160 | 3.2374e+09 | 532140 | 1.89232 | 2(Loss) | true |
| jsonifier (two-stage) | 962.594 | 0.52375 | 8716.87ms | 642697 | 40 | 4.44872e+08 | 636742 | 0.760004 | 3(Loss) | true |
| simdjson (ondemand) | 875.301 | 0.414295 | 9109.07ms | 642697 | 640 | 5.38637e+09 | 700243 | 1.96172 | 4(Loss) | true |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2535.04 | 0.284523 | 6052.04ms | 642697 | 640 | 3.02871e+08 | 241781 | 0.349366 | 1(Win) | true |
| glaze | 1275.62 | 0.457388 | 6306.44ms | 642692 | 320 | 1.54556e+09 | 480489 | 0.313755 | 2(Loss) | true |

----
### Mesh Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2810.8 | 0.129539 | 5651.9ms | 642697 | 320 | 2.55332e+07 | 218060 | 0.57956 | 1(Win) | true |
| glaze | 1351.84 | 0.223598 | 5977.46ms | 642692 | 640 | 6.57766e+08 | 453397 | 3.9536 | 2(Loss) | true |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 1712.76 | 0.60827 | 5037.59ms | 1225964 | 30 | 5.17223e+08 | 682625 | 3.30061 | 1(Tie) | true |
| glaze STATISTICAL TIE | 1704.12 | 0.134386 | 8683.6ms | 1225964 | 80 | 6.80064e+07 | 686084 | 0.631481 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 1377.46 | 0.652937 | 5185.76ms | 1225964 | 320 | 9.82853e+09 | 848786 | 0.325787 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1330.84 | 2.34679 | 9766.59ms | 1225964 | 30 | 1.27519e+10 | 878522 | 1.11695 | 3(Tie) | true |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| glaze | 1937.14 | 0.442832 | 8358.13ms | 1225964 | 320 | 2.28593e+09 | 603556 | 0.0327576 | 1(Win) | true |
| simdjson (ondemand) | 1643.42 | 0.255345 | 9512.55ms | 1225964 | 640 | 2.112e+09 | 711427 | 0.93209 | 2(Loss) | true |
| jsonifier (two-stage) | 1580.16 | 1.4579 | 5108.31ms | 1225964 | 30 | 3.49083e+09 | 739906 | 0.199942 | 3(Loss) | true |
| jsonifier | 1494.49 | 0.809243 | 9966.72ms | 1225964 | 30 | 1.2024e+09 | 782321 | 0.114719 | 4(Loss) | true |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4615.17 | 0.302803 | 6420.52ms | 1225964 | 640 | 3.766e+08 | 253332 | 0.103976 | 1(Win) | true |
| glaze | 1760.99 | 0.584201 | 8489.92ms | 1225970 | 160 | 2.40708e+09 | 663931 | 0.416502 | 2(Loss) | true |

----
### Mesh Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4717.99 | 0.27367 | 6528.96ms | 1225964 | 640 | 2.94357e+08 | 247811 | 2.73467 | 1(Win) | true |
| glaze | 1883.14 | 0.215734 | 8164.69ms | 1225970 | 640 | 1.14819e+09 | 620866 | 0.799375 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1820.74 | 0.231861 | 5544.76ms | 409725 | 1280 | 3.16925e+08 | 214608 | 1.98539 | 1(Win) | true |
| glaze | 1036.81 | 0.402841 | 5076.43ms | 409725 | 80 | 1.84394e+08 | 376873 | 0.0799515 | 2(Loss) | true |
| jsonifier (two-stage) | 904.039 | 0.348715 | 5473.84ms | 409725 | 320 | 7.26943e+08 | 432220 | 0.591999 | 3(Loss) | true |
| simdjson (ondemand) | 857.033 | 0.353474 | 5877.23ms | 409725 | 320 | 8.31101e+08 | 455927 | 1.77312 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2397.45 | 0.1705 | 9954.72ms | 409725 | 2560 | 1.97685e+08 | 162983 | 0.944079 | 1(Win) | true |
| jsonifier (two-stage) | 1182.89 | 0.467389 | 5264.07ms | 409725 | 640 | 1.52558e+09 | 330331 | 0.421143 | 2(Loss) | true |
| glaze | 1091.35 | 0.451866 | 9894.89ms | 409725 | 320 | 8.37584e+08 | 358038 | 0.549929 | 3(Loss) | true |
| simdjson (ondemand) | 896.934 | 0.578949 | 5706.01ms | 409725 | 160 | 1.0178e+09 | 435645 | 1.40025 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8294.48 | 0.251859 | 4590.46ms | 409725 | 2560 | 3.6038e+07 | 47108.9 | 0.183421 | 1(Win) | true |
| glaze | 1825.85 | 0.500482 | 5580.09ms | 409725 | 320 | 3.67099e+08 | 214007 | 3.33138 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8397.09 | 0.312684 | 4632.09ms | 409725 | 1280 | 2.70987e+07 | 46533.3 | 0.0314427 | 1(Win) | true |
| glaze | 2078.4 | 0.648295 | 5269.14ms | 409725 | 40 | 5.94197e+07 | 188002 | 0.561256 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2309.93 | 0.253601 | 8043.77ms | 785750 | 640 | 4.33164e+08 | 324404 | 1.09809 | 1(Win) | true |
| simdjson (ondemand) | 1519.39 | 0.823269 | 6362.53ms | 785750 | 40 | 6.59437e+08 | 493191 | 2.32022 | 2(Loss) | true |
| glaze | 1469.15 | 0.308828 | 6256.28ms | 785750 | 640 | 1.588e+09 | 510056 | 0.571325 | 3(Loss) | true |
| jsonifier (two-stage) | 1352.61 | 0.26074 | 7161.97ms | 785750 | 640 | 1.33542e+09 | 554001 | 0.0999696 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3045.38 | 0.499225 | 7603.48ms | 785750 | 80 | 1.20717e+08 | 246061 | 2.70563 | 1(Win) | true |
| jsonifier (two-stage) | 1845.19 | 0.258989 | 7037.52ms | 785750 | 640 | 7.07992e+08 | 406109 | 1.16655 | 2(Loss) | true |
| glaze | 1735.62 | 0.370704 | 6080.08ms | 785750 | 80 | 2.04928e+08 | 431746 | 0.611329 | 3(Loss) | true |
| simdjson (ondemand) | 1632.73 | 0.426161 | 6136ms | 785750 | 320 | 1.22415e+09 | 458954 | 0.738042 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12243.9 | 0.1383 | 6315.71ms | 785750 | 4890 | 3.50334e+07 | 61202 | 1.81482 | 1(Win) | true |
| glaze | 2139.19 | 0.232171 | 8821.01ms | 785750 | 1280 | 8.4664e+08 | 350297 | 1.65182 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14723.3 | 0.20978 | 5097.25ms | 785750 | 2560 | 2.91827e+07 | 50895.4 | 0.130554 | 1(Win) | true |
| glaze | 2364.22 | 0.535074 | 8097.85ms | 785750 | 160 | 4.60194e+08 | 316954 | 0.0441726 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3832.96 | 0.157048 | 6600.61ms | 264040 | 4890 | 5.2053e+07 | 65695.4 | 0.0317022 | 1(Win) | true |
| jsonifier (two-stage) | 3697.45 | 0.283394 | 6735.23ms | 264040 | 1280 | 4.76787e+07 | 68103.2 | 0.500442 | 2(Loss) | true |
| simdjson (ondemand) | 3015.43 | 1.10606 | 7938.77ms | 264040 | 160 | 1.36494e+08 | 83506.5 | 1.19035 | 3(Loss) | true |
| glaze | 2004.12 | 0.365747 | 6482.82ms | 264040 | 640 | 1.35156e+08 | 125645 | 0.621123 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 4272.16 | 0.666642 | 6726.23ms | 264040 | 30 | 4.63183e+06 | 58941.7 | 0.977595 | 1(Win) | true |
| jsonifier | 3834.09 | 0.210391 | 6581.15ms | 264040 | 2560 | 4.88779e+07 | 65676.2 | 0.44921 | 2(Loss) | true |
| simdjson (ondemand) | 3604.61 | 0.570001 | 7866.69ms | 264040 | 40 | 6.34212e+06 | 69857.3 | 0.391669 | 3(Loss) | true |
| glaze | 2117.34 | 0.581273 | 6295.14ms | 264040 | 320 | 1.52921e+08 | 118926 | 0.43604 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4822.94 | 0.235104 | 8186.6ms | 399947 | 1280 | 4.42498e+07 | 79084.4 | 0.189204 | 1(Win) | true |
| jsonifier (two-stage) | 4766.92 | 0.507198 | 8219.4ms | 399947 | 160 | 2.63514e+07 | 80013.8 | 0.698365 | 2(Loss) | true |
| simdjson (ondemand) | 4258.11 | 0.245698 | 9139.2ms | 399947 | 1280 | 6.1999e+07 | 89574.8 | 0.658787 | 3(Loss) | true |
| glaze | 3013.93 | 0.408558 | 6933.88ms | 399947 | 640 | 1.7109e+08 | 126552 | 2.11138 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 4550.26 | 0.154596 | 8233.41ms | 399947 | 4890 | 8.21177e+07 | 83823.5 | 0.0119661 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 4536.65 | 0.656258 | 8099.17ms | 399947 | 320 | 9.74165e+07 | 84075 | 0.665813 | 1(Tie) | true |
| simdjson (ondemand) | 4281.99 | 0.204337 | 9126.89ms | 399947 | 4890 | 1.62e+08 | 89075.3 | 0.34062 | 3(Loss) | true |
| glaze | 3050.06 | 0.233672 | 6841.75ms | 399947 | 2560 | 2.18595e+08 | 125053 | 0.533318 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2019.29 | 0.663225 | 6540.47ms | 264040 | 80 | 5.47208e+07 | 124701 | 1.06776 | 1(Win) | true |
| simdjson (ondemand) | 1548.11 | 0.156602 | 8578.69ms | 264040 | 1280 | 8.30502e+07 | 162655 | 0.650843 | 2(Loss) | true |
| jsonifier (two-stage) | 1416.77 | 1.65022 | 8263.41ms | 264040 | 80 | 6.882e+08 | 177734 | 0.0687775 | 3(Loss) | true |
| glaze | 1343.33 | 0.207885 | 9370.71ms | 264040 | 1280 | 1.9437e+08 | 187451 | 2.28988 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2594.4 | 0.706118 | 5632.82ms | 264040 | 160 | 7.51519e+07 | 97058.3 | 2.10138 | 1(Win) | true |
| jsonifier (two-stage) | 2061.58 | 0.1681 | 7795.82ms | 264040 | 1280 | 5.39619e+07 | 122143 | 1.31679 | 2(Loss) | true |
| simdjson (ondemand) | 1796.19 | 0.295079 | 8082.11ms | 264040 | 320 | 5.47599e+07 | 140190 | 0.0777137 | 3(Loss) | true |
| glaze | 1771.96 | 0.375314 | 8390.32ms | 264040 | 640 | 1.82053e+08 | 142107 | 2.00461 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10904.7 | 0.874656 | 2002.14ms | 264040 | 30 | 1.22379e+06 | 23091.7 | 0.294044 | 1(Win) | true |
| glaze | 3179.14 | 0.219391 | 7856.27ms | 263923 | 2560 | 7.72351e+07 | 79171.3 | 2.51712 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13221.6 | 0.238892 | 1881.03ms | 264040 | 4890 | 1.01224e+07 | 19045.2 | 1.53835 | 1(Win) | true |
| glaze | 4011.19 | 0.977182 | 6382.94ms | 263923 | 30 | 1.12793e+07 | 62748.6 | 0.281647 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2260.69 | 0.812725 | 9569.08ms | 399947 | 80 | 1.50417e+08 | 168718 | 1.95818 | 1(Win) | true |
| simdjson (ondemand) | 2080 | 0.41414 | 10100.2ms | 399947 | 640 | 3.69107e+08 | 183374 | 0.182721 | 2(Loss) | true |
| jsonifier (two-stage) | 2026.08 | 0.614723 | 8789.79ms | 399947 | 160 | 2.14274e+08 | 188254 | 2.77592 | 3(Loss) | true |
| glaze | 1874.62 | 0.609252 | 5457.28ms | 399947 | 160 | 2.45864e+08 | 203465 | 1.09578 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 2624.51 | 0.188317 | 8583.52ms | 399947 | 2560 | 1.91747e+08 | 145330 | 1.61294 | 1(Win) | true |
| jsonifier | 2506.38 | 0.983771 | 8749.84ms | 399947 | 80 | 1.79303e+08 | 152179 | 1.85389 | 2(Loss) | true |
| simdjson (ondemand) | 2210.57 | 1.0606 | 9304.45ms | 399947 | 160 | 5.35824e+08 | 172544 | 3.03124 | 3(Loss) | true |
| glaze | 1953.54 | 0.328805 | 5474.11ms | 399947 | 1280 | 5.27531e+08 | 195245 | 4.22862 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 20326.5 | 0.126347 | 1888.77ms | 399947 | 1280 | 719483 | 18764.6 | 0.140671 | 1(Win) | true |
| glaze | 3262.4 | 0.411528 | 6121.67ms | 399830 | 640 | 1.48066e+08 | 116879 | 0.234659 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 20671.4 | 0.0589116 | 1893.16ms | 399947 | 4890 | 577798 | 18451.5 | 0.222759 | 1(Win) | true |
| glaze | 3749.18 | 1.0741 | 9401.79ms | 399830 | 80 | 9.54674e+07 | 101704 | 0.348282 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 783.1 | 0.122314 | 570.991ms | 4630 | 40 | 1902.56 | 5638.5 | 0.11719 | 1(Win) | true |
| jsonifier (two-stage) | 698.795 | 0.101675 | 666.967ms | 4630 | 40 | 1651.01 | 6318.75 | 0.121215 | 2(Loss) | true |
| glaze | 504.975 | 0.0377358 | 885.333ms | 4630 | 160 | 1742.01 | 8744.02 | 0.08062 | 3(Loss) | true |
| simdjson (ondemand) | 472.527 | 0.0739178 | 950.266ms | 4630 | 30 | 1431.29 | 9344.47 | 0.208758 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 970.442 | 0.0596613 | 570.449ms | 4630 | 80 | 589.519 | 4550 | 0.137001 | 1(Win) | true |
| jsonifier (two-stage) | 841.709 | 0.0734326 | 655.516ms | 4630 | 4890 | 72564.7 | 5245.89 | 0.112714 | 2(Loss) | true |
| glaze | 568.906 | 0.0974093 | 884.914ms | 4630 | 4890 | 279506 | 7761.41 | 0.0190951 | 3(Loss) | true |
| simdjson (ondemand) | 532.223 | 0.0455454 | 943.499ms | 4630 | 80 | 1142.23 | 8296.36 | 0.0453306 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2729.8 | 0.0616361 | 166.394ms | 4630 | 640 | 636.137 | 1617.52 | 0.156919 | 1(Win) | true |
| glaze | 1619.85 | 0.0329654 | 277.448ms | 4630 | 640 | 516.787 | 2725.88 | 0.128349 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2839.88 | 0.0365519 | 159.175ms | 4630 | 1280 | 413.418 | 1554.82 | 0.0927916 | 1(Win) | true |
| glaze | 1895.77 | 0.0684276 | 236.711ms | 4630 | 80 | 203.209 | 2329.14 | 0.0445642 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1591.75 | 0.106802 | 704.863ms | 11579 | 30 | 1646.94 | 6937.4 | 0.0192232 | 1(Win) | true |
| jsonifier (two-stage) | 1402.71 | 0.147876 | 764.952ms | 11579 | 80 | 10841.6 | 7872.34 | 0.3907 | 2(Loss) | true |
| glaze | 1087.11 | 0.0298011 | 1025.83ms | 11579 | 80 | 733.081 | 10157.8 | 0.0357971 | 3(Loss) | true |
| simdjson (ondemand) | 941.34 | 0.710527 | 1155.47ms | 11579 | 320 | 2.22311e+06 | 11730.7 | 0.201785 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1893.51 | 0.0465326 | 711.895ms | 11579 | 80 | 589.134 | 5831.82 | 0.00986066 | 1(Win) | true |
| jsonifier (two-stage) | 1491.07 | 0.416719 | 832.006ms | 11579 | 1280 | 1.21911e+06 | 7405.81 | 0.0683223 | 2(Loss) | true |
| glaze | 1205.71 | 0.096425 | 1031.51ms | 11579 | 4890 | 381371 | 9158.61 | 0.251816 | 3(Loss) | true |
| simdjson (ondemand) | 1184.26 | 0.0447666 | 1133.28ms | 11579 | 80 | 1393.95 | 9324.46 | 0.31886 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7475.68 | 0.154599 | 194.737ms | 14795 | 2560 | 21796.3 | 1887.4 | 0.268032 | 1(Win) | true |
| glaze | 3080.29 | 0.269504 | 466.286ms | 14795 | 4890 | 745222 | 4580.61 | 0.0716237 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7586.22 | 0.374755 | 187.169ms | 14795 | 80 | 3886.55 | 1859.9 | 0.706609 | 1(Win) | true |
| glaze | 3552.32 | 0.240696 | 399.254ms | 14795 | 4890 | 446945 | 3971.94 | 0.0852683 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1344.25 | 0.210972 | 371.493ms | 5092 | 1280 | 74348.5 | 3612.49 | 1.29765 | 1(Win) | true |
| jsonifier (two-stage) | 1015.43 | 0.283202 | 500.492ms | 5092 | 40 | 7337.14 | 4782.3 | 0.0800925 | 2(Loss) | true |
| glaze | 933.874 | 0.126917 | 553.301ms | 5092 | 80 | 3484.39 | 5199.96 | 0.0406418 | 3(Loss) | true |
| simdjson (ondemand) | 741.143 | 0.592631 | 643.015ms | 5092 | 2560 | 3.85996e+06 | 6552.19 | 0.919742 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1898.72 | 0.554293 | 330.092ms | 5092 | 4890 | 982749 | 2557.57 | 0.0118834 | 1(Win) | true |
| jsonifier (two-stage) | 1382.49 | 0.213229 | 451.652ms | 5092 | 40 | 2243.89 | 3512.57 | 0.704594 | 2(Loss) | true |
| glaze | 1183.07 | 0.132546 | 497.141ms | 5092 | 160 | 4736 | 4104.68 | 0.038204 | 3(Loss) | true |
| simdjson (ondemand) | 1049.57 | 0.170272 | 534.278ms | 5092 | 4890 | 303495 | 4626.76 | 0.265999 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7039.62 | 0.508663 | 72.0444ms | 5092 | 2560 | 31519.5 | 689.826 | 0.195545 | 1(Win) | true |
| glaze | 1487.13 | 0.681869 | 318.353ms | 5092 | 2560 | 1.26918e+06 | 3265.43 | 0.543593 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8103.08 | 0.416542 | 68.7113ms | 5092 | 1280 | 7976.36 | 599.292 | 0.0968223 | 1(Win) | true |
| glaze | 1770.24 | 0.319277 | 283.998ms | 5092 | 4890 | 375107 | 2743.19 | 2.48282 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1969.26 | 0.147834 | 569.066ms | 9739 | 160 | 7778.47 | 4716.42 | 0.170522 | 1(Win) | true |
| jsonifier (two-stage) | 1736.54 | 0.137314 | 598.869ms | 9739 | 30 | 1618.12 | 5348.47 | 0.232381 | 2(Loss) | true |
| simdjson (ondemand) | 1433.18 | 2.19878 | 659.303ms | 9739 | 30 | 609130 | 6480.57 | 0.828398 | 3(Loss) | true |
| glaze | 1293.43 | 0.550871 | 737.257ms | 9739 | 640 | 1.00144e+06 | 7180.8 | 0.337326 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2419.38 | 0.219374 | 510.488ms | 9739 | 30 | 2127.72 | 3838.93 | 0.14393 | 1(Win) | true |
| jsonifier (two-stage) | 1976.4 | 0.642713 | 565.775ms | 9739 | 2560 | 2.33535e+06 | 4699.37 | 0.715366 | 2(Loss) | true |
| simdjson (ondemand) | 1779.33 | 0.499751 | 606.553ms | 9739 | 640 | 435517 | 5219.86 | 0.459429 | 3(Loss) | true |
| glaze | 1407.93 | 1.08805 | 722.885ms | 9739 | 80 | 412154 | 6596.81 | 0.0794575 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16913.7 | 0.306614 | 74.0469ms | 11724 | 320 | 1314.64 | 661.053 | 0.0949286 | 1(Win) | true |
| glaze | 2103.82 | 0.687425 | 531.516ms | 11746 | 1280 | 1.71484e+06 | 5324.53 | 0.860318 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 18699.4 | 0.143362 | 67.4177ms | 11724 | 1280 | 940.529 | 597.927 | 0.466532 | 1(Win) | true |
| glaze | 2692 | 0.248774 | 423.404ms | 11746 | 4890 | 524021 | 4161.17 | 0.158354 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1896.58 | 0.336496 | 251.242ms | 4857 | 4890 | 330267 | 2442.29 | 3.58369 | 1(Win) | true |
| glaze | 1270.23 | 0.21568 | 392.169ms | 4857 | 160 | 9897.13 | 3646.57 | 0.974349 | 2(Loss) | true |
| simdjson (ondemand) | 1249.08 | 0.309477 | 398.134ms | 4857 | 30 | 3951.26 | 3708.33 | 0.337314 | 3(Loss) | true |
| jsonifier (two-stage) | 1189.32 | 0.294451 | 406.212ms | 4857 | 40 | 5260.44 | 3894.65 | 0.6678 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2618.78 | 0.15628 | 200.151ms | 4857 | 80 | 611.272 | 1768.76 | 0.176281 | 1(Win) | true |
| glaze | 1660 | 0.616297 | 290.841ms | 4857 | 320 | 94635.1 | 2790.37 | 0.0485163 | 2(Loss) | true |
| simdjson (ondemand) | 1515.07 | 0.252769 | 342.538ms | 4857 | 2560 | 152883 | 3057.29 | 0.0272732 | 3(Loss) | true |
| jsonifier (two-stage) | 1452.27 | 0.446107 | 393.355ms | 4857 | 2560 | 518277 | 3189.49 | 2.1725 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10223.5 | 0.818826 | 51.0286ms | 4857 | 40 | 550.533 | 453.075 | 0.683333 | 1(Win) | true |
| glaze | 2509.41 | 0.24554 | 213.929ms | 4857 | 40 | 821.669 | 1845.85 | 0.149205 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12125.8 | 0.139627 | 41.8801ms | 4857 | 2560 | 728.275 | 381.996 | 0.228027 | 1(Win) | true |
| glaze | 2437.16 | 0.396177 | 182.675ms | 4857 | 1280 | 72570 | 1900.57 | 0.300524 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1854.58 | 0.407622 | 355.933ms | 6701 | 4890 | 964745 | 3445.84 | 3.40792 | 1(Win) | true |
| simdjson (ondemand) | 1611.19 | 0.58353 | 406.081ms | 6701 | 1280 | 685682 | 3966.37 | 1.56471 | 2(Loss) | true |
| jsonifier (two-stage) | 1559.01 | 0.144146 | 450.848ms | 6701 | 40 | 1396.52 | 4099.12 | 0.116217 | 3(Loss) | true |
| glaze | 1322.8 | 0.297311 | 451.081ms | 6701 | 4890 | 1.00885e+06 | 4831.11 | 0.331541 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| glaze STATISTICAL TIE | 2084 | 0.63314 | 353.977ms | 6701 | 30 | 11308.5 | 3066.5 | 0.137861 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 2079.03 | 0.491613 | 345.691ms | 6701 | 1280 | 292291 | 3073.83 | 1.27184 | 1(Tie) | true |
| simdjson (ondemand) | 2020.76 | 0.600481 | 369.941ms | 6701 | 30 | 10818.6 | 3162.47 | 0.786397 | 3(Loss) | true |
| jsonifier (two-stage) | 1693.16 | 0.258417 | 445.606ms | 6701 | 4890 | 465196 | 3774.35 | 0.19049 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 15055.7 | 0.203991 | 53.8158ms | 7376 | 640 | 581.354 | 467.219 | 0.163601 | 1(Win) | true |
| glaze | 1947.63 | 1.04286 | 313.33ms | 7376 | 160 | 226989 | 3611.72 | 0.437274 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 15515.4 | 0.996058 | 48.6934ms | 7376 | 160 | 3262.9 | 453.375 | 2.89654 | 1(Win) | true |
| glaze | 2392.45 | 0.272868 | 307.837ms | 7376 | 4890 | 314753 | 2940.21 | 0.44098 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1934.88 | 0.485282 | 210.805ms | 4390 | 2560 | 282259 | 2163.76 | 0.174269 | 1(Win) | true |
| jsonifier (two-stage) | 1146.68 | 0.264225 | 411.085ms | 4390 | 40 | 3722.64 | 3651.07 | 0.529806 | 2(Loss) | true |
| glaze | 989.332 | 0.315405 | 446.95ms | 4390 | 80 | 14251.9 | 4231.77 | 0.433129 | 3(Loss) | true |
| simdjson (ondemand) | 934.108 | 0.452756 | 466.608ms | 4390 | 320 | 131769 | 4481.96 | 0.0366614 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2574.34 | 0.0698552 | 193.469ms | 4390 | 160 | 206.498 | 1626.29 | 0.0149903 | 1(Win) | true |
| jsonifier (two-stage) | 1248.74 | 0.523947 | 378.493ms | 4390 | 640 | 197486 | 3352.68 | 0.803113 | 2(Loss) | true |
| simdjson (ondemand) | 1084.33 | 0.139946 | 428.429ms | 4390 | 30 | 875.895 | 3861.03 | 0.106938 | 3(Loss) | true |
| glaze | 1019.04 | 0.274654 | 436.313ms | 4390 | 4890 | 622630 | 4108.42 | 0.206909 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8539.07 | 0.151691 | 52.4455ms | 4390 | 4890 | 2704.82 | 490.291 | 0.590841 | 1(Win) | true |
| glaze | 1394.35 | 1.35375 | 283.221ms | 4390 | 160 | 264352 | 3002.57 | 2.17945 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9369.21 | 0.263552 | 48.9714ms | 4390 | 4890 | 6782.12 | 446.85 | 0.0744471 | 1(Win) | true |
| glaze | 1639.51 | 0.324841 | 266.393ms | 4390 | 2560 | 176151 | 2553.59 | 1.08339 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2814.48 | 0.217184 | 334.463ms | 9378 | 30 | 1428.91 | 3177.7 | 0.178009 | 1(Win) | true |
| simdjson (ondemand) | 1828.14 | 0.275734 | 523.041ms | 9378 | 4890 | 889796 | 4892.16 | 3.06903 | 2(Loss) | true |
| jsonifier (two-stage) | 1766.49 | 0.528502 | 515.256ms | 9378 | 2560 | 1.83287e+06 | 5062.9 | 0.0181732 | 3(Loss) | true |
| glaze | 1721.46 | 0.317552 | 561.617ms | 9378 | 2560 | 696781 | 5195.32 | 1.15631 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 2539.28 | 0.298209 | 411.424ms | 9378 | 1280 | 141205 | 3522.08 | 0.838964 | 1(Win) | true |
| jsonifier | 2460.33 | 0.293565 | 379.331ms | 9378 | 2560 | 291530 | 3635.11 | 1.22694 | 2(Loss) | true |
| simdjson (ondemand) | 2016.9 | 0.624353 | 453.073ms | 9378 | 320 | 245279 | 4434.3 | 0.054587 | 3(Loss) | true |
| glaze | 1847.69 | 0.601618 | 524.55ms | 9378 | 1280 | 1.08546e+06 | 4840.41 | 0.0214618 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 20824.5 | 0.443553 | 59.574ms | 11521 | 80 | 438.139 | 527.612 | 0.301792 | 1(Win) | true |
| glaze | 2584.83 | 0.264281 | 452.189ms | 11521 | 4890 | 617099 | 4250.67 | 2.873 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 20361 | 1.70413 | 56.6655ms | 11521 | 40 | 3382.6 | 539.625 | 0.124931 | 1(Win) | true |
| glaze | 3015.97 | 0.236832 | 373.829ms | 11521 | 30 | 2233.21 | 3643.03 | 0.078751 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2745.93 | 0.125954 | 170.353ms | 4669 | 4890 | 20398.7 | 1621.57 | 1.06434 | 1(Win) | true |
| jsonifier (two-stage) | 1481.16 | 0.657155 | 301.548ms | 4669 | 1280 | 499559 | 3006.22 | 1.75638 | 2(Loss) | true |
| glaze | 1086.7 | 1.38317 | 359.669ms | 4669 | 80 | 256961 | 4097.44 | 3.68432 | 3(Loss) | true |
| simdjson (ondemand) | 1036.7 | 0.308336 | 394.324ms | 4669 | 2560 | 448982 | 4295.07 | 4.45703 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2549.92 | 1.25626 | 186.683ms | 4669 | 640 | 307989 | 1746.21 | 0.682885 | 1(Win) | true |
| jsonifier (two-stage) | 1868.24 | 0.167693 | 262.386ms | 4669 | 40 | 638.958 | 2383.38 | 0.176883 | 2(Loss) | true |
| glaze | 1621.9 | 0.129412 | 293.863ms | 4669 | 80 | 1009.8 | 2745.36 | 0.0979883 | 3(Loss) | true |
| simdjson (ondemand) | 1534.04 | 0.0953849 | 350.021ms | 4669 | 80 | 613.23 | 2902.6 | 0.0542323 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13636 | 0.114285 | 37.0781ms | 4669 | 2560 | 356.53 | 326.541 | 0.120488 | 1(Win) | true |
| glaze | 1902.88 | 0.599914 | 251.504ms | 4669 | 1280 | 252240 | 2339.99 | 3.8223 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 15449 | 0.26436 | 32.008ms | 4669 | 640 | 371.552 | 288.22 | 0.155347 | 1(Win) | true |
| glaze | 2207.06 | 0.334746 | 213.788ms | 4669 | 2560 | 116759 | 2017.48 | 0.570404 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2790.05 | 0.15357 | 278.462ms | 7932 | 2560 | 44380.5 | 2711.26 | 0.0011238 | 1(Win) | true |
| jsonifier (two-stage) | 2630.19 | 0.089366 | 294.12ms | 7932 | 80 | 528.478 | 2876.05 | 0.0373916 | 2(Loss) | true |
| simdjson (ondemand) | 2074.55 | 0.114159 | 375.528ms | 7932 | 2560 | 44358.3 | 3646.35 | 0.149946 | 3(Loss) | true |
| glaze | 1963.36 | 0.0736688 | 431.064ms | 7932 | 160 | 1289 | 3852.85 | 0.0753257 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3015.14 | 0.105679 | 264.387ms | 7932 | 160 | 1124.73 | 2508.86 | 0.0206725 | 1(Win) | true |
| jsonifier (two-stage) | 2856.51 | 0.0500018 | 281.18ms | 7932 | 320 | 561.066 | 2648.18 | 0.0288017 | 2(Loss) | true |
| simdjson (ondemand) | 2422.98 | 0.0798909 | 325.274ms | 7932 | 4890 | 30420.7 | 3122 | 0.0332775 | 3(Loss) | true |
| glaze | 2287.86 | 0.121123 | 348.623ms | 7932 | 2560 | 41058.3 | 3306.38 | 0.11724 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 20311.5 | 1.94013 | 43.4201ms | 9249 | 2560 | 181723 | 434.264 | 0.372158 | 1(Win) | true |
| glaze | 2294.07 | 0.327565 | 398.636ms | 9249 | 320 | 50759.7 | 3844.92 | 0.32074 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 27749.8 | 0.0923332 | 34.8267ms | 9249 | 4890 | 421.205 | 317.859 | 0.00917965 | 1(Win) | true |
| glaze | 2410.51 | 0.637794 | 370.246ms | 9249 | 1280 | 697175 | 3659.2 | 0.849338 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 676.122 | 0.0780452 | 699.181ms | 4604 | 160 | 4109.92 | 6493.98 | 0.0609809 | 1(Win) | true |
| jsonifier (two-stage) | 566.491 | 0.028682 | 789.741ms | 4604 | 320 | 1581.44 | 7750.73 | 0.0277719 | 2(Loss) | true |
| glaze | 405.223 | 0.164039 | 1185.29ms | 4604 | 4890 | 1.54484e+06 | 10835.3 | 0.00226224 | 3(Loss) | true |
| simdjson (ondemand) | 379.454 | 0.157618 | 1351.86ms | 4604 | 640 | 212884 | 11571.2 | 0.499148 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 869.715 | 0.183039 | 650.472ms | 4604 | 1280 | 109299 | 5048.45 | 0.0942078 | 1(Win) | true |
| jsonifier (two-stage) | 695.465 | 0.128524 | 774.15ms | 4604 | 2560 | 168551 | 6313.35 | 0.00295142 | 2(Loss) | true |
| glaze | 474.277 | 0.276302 | 1162.32ms | 4604 | 320 | 209376 | 9257.7 | 0.0163066 | 3(Loss) | true |
| simdjson (ondemand) | 440.056 | 0.193057 | 1166.85ms | 4604 | 640 | 237469 | 9977.63 | 0.172838 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1337.49 | 2.1837 | 267.904ms | 4604 | 80 | 411118 | 3282.81 | 1.16837 | 1(Win) | true |
| glaze | 1099.2 | 0.109207 | 426.13ms | 4604 | 30 | 570.878 | 3994.47 | 0.0308665 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2085.71 | 0.208426 | 241.44ms | 4604 | 80 | 1540.12 | 2105.14 | 0.00296884 | 1(Win) | true |
| glaze | 1172.92 | 0.247785 | 403.073ms | 4604 | 640 | 55063.8 | 3743.42 | 0.306016 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 1798.44 | 0.154458 | 1003.53ms | 18245 | 40 | 8932.66 | 9674.95 | 0.0563628 | 1(Win) | true |
| jsonifier | 1739.98 | 0.145384 | 1030.42ms | 18245 | 40 | 8454.59 | 9999.98 | 0.27953 | 2(Loss) | true |
| simdjson (ondemand) | 1285.85 | 0.151303 | 1495.02ms | 18245 | 80 | 33534.8 | 13531.8 | 0.00360276 | 3(Loss) | true |
| glaze | 1260.86 | 0.0509291 | 1524.95ms | 18245 | 40 | 1975.81 | 13799.9 | 0.0302446 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 2174.62 | 0.175727 | 993.619ms | 18245 | 30 | 5930.91 | 8001.3 | 0.121499 | 1(Win) | true |
| jsonifier | 2077.95 | 0.157323 | 1016.1ms | 18245 | 30 | 5206.26 | 8373.53 | 0.165077 | 2(Loss) | true |
| simdjson (ondemand) | 1430.25 | 1.24497 | 1544.77ms | 18245 | 40 | 917577 | 12165.5 | 0.90181 | 3(Loss) | true |
| glaze | 1344.84 | 0.212907 | 1458.16ms | 18245 | 4890 | 3.71053e+06 | 12938.2 | 0.00857111 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6559.54 | 1.2982 | 335.162ms | 24579 | 80 | 172168 | 3573.47 | 0.689631 | 1(Win) | true |
| glaze | 2730.39 | 0.488805 | 903.769ms | 24579 | 2560 | 4.50808e+06 | 8585 | 2.04059 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7521.12 | 0.373535 | 310.754ms | 24579 | 4890 | 662727 | 3116.61 | 2.82012 | 1(Win) | true |
| glaze | 3157.32 | 0.341478 | 734.481ms | 24579 | 4890 | 3.14286e+06 | 7424.13 | 1.6671 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 608.817 | 1.48882 | 723.228ms | 4604 | 80 | 922298 | 7211.89 | 0.413348 | 1(Win) | true |
| jsonifier (two-stage) | 536.686 | 1.31894 | 834.684ms | 4604 | 160 | 1.86293e+06 | 8181.16 | 1.96533 | 2(Loss) | true |
| simdjson (ondemand) | 350.119 | 0.201708 | 1269.24ms | 4604 | 4890 | 3.12893e+06 | 12540.6 | 1.6622 | 3(Loss) | true |
| glaze | 321.412 | 0.778948 | 1343.92ms | 4604 | 1280 | 1.44935e+07 | 13660.7 | 0.305008 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 846.256 | 0.259716 | 711.616ms | 4604 | 4890 | 887918 | 5188.4 | 1.20458 | 1(Win) | true |
| jsonifier (two-stage) | 704.273 | 0.134985 | 811.039ms | 4604 | 40 | 2832.81 | 6234.4 | 0.00534639 | 2(Loss) | true |
| glaze STATISTICAL TIE | 406.012 | 0.218443 | 1281.14ms | 4604 | 4890 | 2.72884e+06 | 10814.3 | 2.40012 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 403.469 | 0.606009 | 1287.16ms | 4604 | 320 | 1.39174e+06 | 10882.4 | 0.044271 | 3(Tie) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1545.7 | 0.461144 | 272.473ms | 4604 | 2560 | 439273 | 2840.61 | 2.77119 | 1(Win) | true |
| glaze | 966.536 | 0.202189 | 471.617ms | 4604 | 4890 | 412534 | 4542.74 | 2.8419 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1951.41 | 0.162423 | 247.927ms | 4604 | 40 | 534.23 | 2250.03 | 0.548451 | 1(Win) | true |
| glaze | 1076.08 | 0.445262 | 455.743ms | 4604 | 1280 | 422499 | 4080.3 | 1.51304 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 1822.23 | 0.186925 | 1004.18ms | 18245 | 4890 | 1.55785e+06 | 9548.62 | 0.428178 | 1(Win) | true |
| jsonifier | 1629.37 | 0.271755 | 1017.27ms | 18245 | 4890 | 4.11826e+06 | 10678.9 | 1.14994 | 2(Loss) | true |
| simdjson (ondemand) | 1333 | 0.0677068 | 1368.5ms | 18245 | 40 | 3124.3 | 13053.1 | 0.357255 | 3(Loss) | true |
| glaze | 1093.53 | 0.37072 | 1587.33ms | 18245 | 2560 | 8.90753e+06 | 15911.5 | 0.261042 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 2333.1 | 0.593497 | 975.934ms | 18245 | 80 | 156728 | 7457.79 | 1.37126 | 1(Win) | true |
| jsonifier | 2238.09 | 0.266531 | 945.217ms | 18245 | 2560 | 1.09918e+06 | 7774.38 | 1.62445 | 2(Loss) | true |
| simdjson (ondemand) | 1583.89 | 0.0375467 | 1239.37ms | 18245 | 80 | 1361.04 | 10985.5 | 0.0394996 | 3(Loss) | true |
| glaze | 1260.69 | 0.987549 | 1612.79ms | 18245 | 160 | 2.9724e+06 | 13801.8 | 0.50629 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8670.06 | 0.113132 | 274.718ms | 24579 | 80 | 748.42 | 2703.6 | 0.0971871 | 1(Win) | true |
| glaze | 3300.63 | 0.0362948 | 718.782ms | 24579 | 160 | 1063.02 | 7101.79 | 0.0685156 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9318.99 | 0.185744 | 255.242ms | 24579 | 30 | 654.851 | 2515.33 | 0.0596698 | 1(Win) | true |
| glaze | 3853.15 | 0.0796366 | 642.476ms | 24579 | 4890 | 114771 | 6083.43 | 0.171993 | 2(Loss) | true |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 863.082 | 0.0912862 | 134.241ms | 1181 | 320 | 454.105 | 1304.96 | 0.061342 | 1(Win) | true |
| jsonifier (two-stage) | 744.988 | 0.0378025 | 155.118ms | 1181 | 1280 | 418.073 | 1511.82 | 0.0189687 | 2(Loss) | true |
| glaze | 599.926 | 0.1007 | 191.559ms | 1181 | 160 | 571.847 | 1877.38 | 0.0136475 | 3(Loss) | true |
| simdjson (ondemand) | 521.956 | 0.0609104 | 223.564ms | 1181 | 320 | 552.797 | 2157.82 | 0.024336 | 4(Loss) | true |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 1072.65 | 0.105383 | 121.101ms | 1181 | 4890 | 5987.25 | 1050 | 0.066812 | 1(Tie) | true |
| glaze STATISTICAL TIE | 1070.8 | 0.134919 | 121.639ms | 1181 | 160 | 322.221 | 1051.83 | 0.0249629 | 1(Tie) | true |
| jsonifier (two-stage) | 895.009 | 0.0321242 | 143.327ms | 1181 | 2560 | 418.359 | 1258.41 | 0.0822335 | 3(Loss) | true |
| simdjson (ondemand) | 787.939 | 0.112802 | 159.982ms | 1181 | 160 | 415.98 | 1429.41 | 0.0209832 | 4(Loss) | true |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2533.26 | 0.13338 | 48.8766ms | 1181 | 1280 | 450.123 | 444.6 | 0.000702884 | 1(Win) | true |
| glaze | 1234.39 | 0.03965 | 94.9192ms | 1181 | 2560 | 335.057 | 912.424 | 0.050022 | 2(Loss) | true |

----
### Mesh Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2867.07 | 0.208952 | 42.8089ms | 1181 | 640 | 431.217 | 392.836 | 0.0997354 | 1(Win) | true |
| glaze | 1403.86 | 0.0865886 | 83.7611ms | 1181 | 1280 | 617.712 | 802.282 | 1.37604 | 2(Loss) | true |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 1213.48 | 0.0441381 | 170.606ms | 2119 | 640 | 345.786 | 1665.33 | 0.00168883 | 1(Win) | true |
| jsonifier | 1164.32 | 0.0775725 | 178.395ms | 2119 | 320 | 580.07 | 1735.63 | 0.0580097 | 2(Loss) | true |
| glaze | 950.745 | 0.0442316 | 213.795ms | 2119 | 320 | 282.846 | 2125.53 | 0.0492282 | 3(Loss) | true |
| simdjson (ondemand) | 925.453 | 0.0761675 | 223.564ms | 2119 | 160 | 442.602 | 2183.62 | 0.0609282 | 4(Loss) | true |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| glaze | 1536.1 | 0.110165 | 147.618ms | 2119 | 4890 | 10271 | 1315.56 | 0.0198319 | 1(Win) | true |
| jsonifier (two-stage) | 1434.24 | 0.0627965 | 158.247ms | 2119 | 640 | 501.034 | 1408.99 | 0.0253885 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1370.06 | 0.123092 | 163.632ms | 2119 | 160 | 527.428 | 1474.99 | 0.0708131 | 3(Tie) | true |
| jsonifier STATISTICAL TIE | 1369.54 | 0.0636376 | 165.897ms | 2119 | 640 | 564.316 | 1475.56 | 0.0403286 | 3(Tie) | true |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4924.9 | 0.248454 | 51.5037ms | 2496 | 320 | 461.465 | 483.334 | 0.221276 | 1(Win) | true |
| glaze | 1658.27 | 0.0889566 | 148.393ms | 2507 | 320 | 526.389 | 1441.78 | 0.133986 | 2(Loss) | true |

----
### Mesh Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5756.64 | 0.340771 | 43.9851ms | 2496 | 160 | 317.686 | 413.5 | 0.133188 | 1(Win) | true |
| glaze | 1977.76 | 0.175632 | 125.002ms | 2507 | 160 | 721.255 | 1208.88 | 0.0475875 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2303.85 | 0.0757079 | 216.371ms | 4926 | 80 | 190.658 | 2039.11 | 0.0300466 | 1(Win) | true |
| jsonifier (two-stage) | 1169.52 | 0.140364 | 404.49ms | 4926 | 2560 | 81381.8 | 4016.87 | 0.0403506 | 2(Loss) | true |
| glaze | 1114.95 | 0.0871074 | 465.31ms | 4926 | 160 | 2155.31 | 4213.47 | 0.148108 | 3(Loss) | true |
| simdjson (ondemand) | 1040.95 | 0.0626174 | 457.848ms | 4926 | 80 | 638.86 | 4512.98 | 0.125352 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2632.74 | 0.108091 | 206.796ms | 4926 | 80 | 297.604 | 1784.38 | 0.00140107 | 1(Win) | true |
| jsonifier (two-stage) | 1491.36 | 0.103782 | 400.522ms | 4926 | 40 | 427.487 | 3150 | 0.00105819 | 2(Loss) | true |
| glaze | 1290.23 | 0.0587951 | 397.668ms | 4926 | 640 | 2933.05 | 3641.07 | 0.140954 | 3(Loss) | true |
| simdjson (ondemand) | 1200.71 | 0.0817188 | 424.193ms | 4926 | 80 | 817.797 | 3912.51 | 0.106914 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9796.11 | 0.176055 | 51.2214ms | 4926 | 640 | 456.203 | 479.558 | 0.0289897 | 1(Win) | true |
| glaze | 1946.31 | 0.141778 | 248.818ms | 4926 | 30 | 351.321 | 2413.7 | 0.234221 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10638 | 0.0674412 | 47.241ms | 4926 | 4890 | 433.741 | 441.607 | 0.0135959 | 1(Win) | true |
| glaze | 2215.07 | 0.0894176 | 216.583ms | 4926 | 80 | 287.707 | 2120.84 | 0.0477634 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2520.77 | 0.0913022 | 335.316ms | 8150 | 30 | 237.757 | 3083.37 | 0.0465076 | 1(Win) | true |
| simdjson (ondemand) | 1619.83 | 0.0928687 | 513.09ms | 8150 | 640 | 12708.5 | 4798.3 | 0.219257 | 2(Loss) | true |
| glaze | 1601.57 | 0.144175 | 492.524ms | 8150 | 40 | 1958.23 | 4853.02 | 0.0214597 | 3(Loss) | true |
| jsonifier (two-stage) | 1466.92 | 0.0492615 | 536.956ms | 8150 | 80 | 545.011 | 5298.46 | 0.0294984 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2788.96 | 0.176903 | 317.889ms | 8150 | 2560 | 62221.4 | 2786.87 | 0.11149 | 1(Win) | true |
| glaze | 1840.44 | 0.0669846 | 461.458ms | 8150 | 160 | 1280.39 | 4223.14 | 0.00547608 | 2(Loss) | true |
| jsonifier (two-stage) | 1813.09 | 0.221277 | 575.538ms | 8150 | 320 | 28793.8 | 4286.85 | 0.504949 | 3(Loss) | true |
| simdjson (ondemand) | 1529.32 | 0.650936 | 503.965ms | 8150 | 640 | 700447 | 5082.29 | 0.782297 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13408.3 | 0.0460881 | 71.1678ms | 9463 | 2560 | 246.336 | 673.063 | 0.0115507 | 1(Win) | true |
| glaze | 2377.93 | 0.0481759 | 388.167ms | 9463 | 320 | 1069.72 | 3795.16 | 0.133902 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 14564.5 | 1.15598 | 65.6458ms | 9463 | 160 | 8208.9 | 619.631 | 5.75491 | -(Win) | false |
| glaze | 2513.38 | 0.480652 | 376.126ms | 9463 | 1280 | 381253 | 3590.63 | 0.409985 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3464.39 | 0.305779 | 89.424ms | 2821 | 80 | 451.085 | 776.562 | 0.0723822 | 1(Win) | true |
| simdjson (ondemand) | 3265.14 | 0.383252 | 89.1478ms | 2821 | 40 | 398.869 | 823.95 | 0.296467 | 2(Loss) | true |
| jsonifier (two-stage) | 3231.55 | 0.290291 | 86.3474ms | 2821 | 1280 | 7475.91 | 832.516 | 0.445353 | 3(Loss) | true |
| glaze | 2357.55 | 0.21064 | 137.117ms | 2821 | 80 | 462.23 | 1141.15 | 0.323084 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3786.64 | 0.20465 | 80.7351ms | 2821 | 40 | 84.5635 | 710.475 | 0.113903 | 1(Win) | true |
| jsonifier (two-stage) | 3692.11 | 0.0935345 | 81.5062ms | 2821 | 1280 | 594.579 | 728.666 | 0.309112 | 2(Loss) | true |
| simdjson (ondemand) | 3398.91 | 0.209088 | 85.7739ms | 2821 | 320 | 876.463 | 791.522 | 0.115545 | 3(Loss) | true |
| glaze | 1931.27 | 0.496625 | 137.189ms | 2821 | 2560 | 122523 | 1393.03 | 0.901079 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 3922.06 | 0.229362 | 97.6352ms | 3770 | 40 | 176.831 | 916.7 | 0.302721 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 3904.31 | 0.397508 | 96.4844ms | 3770 | 30 | 401.982 | 920.867 | 0.148191 | 1(Tie) | true |
| simdjson (ondemand) | 3843.58 | 0.263988 | 97.9922ms | 3770 | 160 | 975.666 | 935.419 | 0.616471 | 3(Loss) | true |
| glaze | 2702.92 | 0.530968 | 139.515ms | 3770 | 40 | 1995.33 | 1330.17 | 0.173838 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 4250.66 | 0.419283 | 92.692ms | 3770 | 30 | 377.316 | 845.833 | 0 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 4224.03 | 0.168095 | 92.406ms | 3770 | 320 | 655.073 | 851.166 | 0.289041 | 1(Tie) | true |
| simdjson (ondemand) | 4027.33 | 0.421925 | 95.3392ms | 3770 | 80 | 1135.03 | 892.737 | 0.823028 | 3(Loss) | true |
| glaze | 2823.32 | 0.231953 | 139.563ms | 3770 | 80 | 697.997 | 1273.45 | 0.203754 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2342.05 | 0.135475 | 122.727ms | 2821 | 320 | 774.969 | 1148.7 | 0.338365 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1741.03 | 0.104533 | 161.522ms | 2821 | 640 | 1669.87 | 1545.24 | 0.22143 | 2(Tie) | true |
| glaze STATISTICAL TIE | 1725 | 0.580741 | 164.477ms | 2821 | 30 | 2461.01 | 1559.6 | 0.805631 | 2(Tie) | true |
| simdjson (ondemand) | 1618.99 | 0.275278 | 170.897ms | 2821 | 2560 | 53567.5 | 1661.72 | 3.24955 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2883.01 | 0.205592 | 113.647ms | 2821 | 320 | 1177.82 | 933.163 | 0.289505 | 1(Win) | true |
| jsonifier (two-stage) | 2099.8 | 0.65599 | 154.314ms | 2821 | 40 | 2825.56 | 1281.22 | 0.265423 | 2(Loss) | true |
| glaze | 2004.46 | 0.290859 | 152.216ms | 2821 | 640 | 9753.42 | 1342.17 | 0.56547 | 3(Loss) | true |
| simdjson (ondemand) | 1821.21 | 0.194779 | 162.127ms | 2821 | 320 | 2649.24 | 1477.22 | 0.523768 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9687.85 | 1.49316 | 34.2677ms | 2821 | 30 | 515.803 | 277.7 | 0.0120019 | 1(Win) | true |
| glaze | 2996.98 | 0.0879874 | 94.3375ms | 2819 | 1280 | 797.395 | 897.039 | 0.0334545 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9223.94 | 0.682818 | 27.797ms | 2821 | 30 | 118.989 | 291.667 | 0 | 1(Win) | true |
| glaze | 3699.98 | 0.277072 | 78.0227ms | 2819 | 160 | 648.481 | 726.6 | 0.225874 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 2239.4 | 0.322843 | 164.185ms | 3770 | 30 | 805.983 | 1605.5 | 0.260918 | 1(Win) | true |
| jsonifier (two-stage) | 2083.69 | 0.273502 | 176.611ms | 3770 | 2560 | 57013.5 | 1725.47 | 0.0944048 | 2(Loss) | true |
| jsonifier DID NOT CONVERGE | 1908.78 | 0.295402 | 197.854ms | 3770 | 4890 | 151394 | 1883.59 | 5.27698 | -(Loss) | false |
| glaze | 1769.99 | 0.435786 | 203.412ms | 3770 | 4890 | 383174 | 2031.28 | 0.749736 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 2742.7 | 0.175963 | 151.613ms | 3770 | 2560 | 13620.9 | 1310.88 | 0.260641 | 1(Win) | true |
| jsonifier | 2562.39 | 0.375099 | 177.771ms | 3770 | 40 | 1108.01 | 1403.12 | 0.864911 | 2(Loss) | true |
| simdjson (ondemand) | 2490.24 | 0.351344 | 157.684ms | 3770 | 40 | 1029.26 | 1443.78 | 0.238962 | 3(Loss) | true |
| glaze | 2095.85 | 0.323704 | 195.808ms | 3770 | 2560 | 78940.3 | 1715.46 | 0.37386 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13614.1 | 0.565856 | 36.7112ms | 4147 | 320 | 864.677 | 290.5 | 0.651918 | 1(Win) | true |
| glaze | 2905.32 | 0.311382 | 147.621ms | 4145 | 2560 | 45950 | 1360.6 | 1.06484 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13048.1 | 1.09492 | 30.282ms | 4147 | 40 | 440.554 | 303.1 | 2.9873 | 1(Win) | true |
| glaze | 3903.99 | 0.535041 | 115.301ms | 4145 | 40 | 1174 | 1012.55 | 1.68206 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2478.39 | 0.338652 | 9140.75ms | 466906 | 1280 | 4.73846e+08 | 179664 | 2.32556 | 1(Win) | true |
| glaze | 1490.65 | 0.516234 | 7290.27ms | 466906 | 320 | 7.60942e+08 | 298713 | 0.407902 | 2(Loss) | true |
| simdjson (ondemand) | 912.385 | 0.0839686 | 6272.35ms | 466906 | 160 | 2.68693e+07 | 488035 | 0.00448078 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2804.51 | 0.0735153 | 8414.79ms | 466906 | 2560 | 3.48772e+07 | 158772 | 0.271821 | 1(Win) | true |
| glaze | 1645.06 | 0.267656 | 7022.92ms | 466906 | 1280 | 6.7183e+08 | 270675 | 0.224201 | 2(Loss) | true |
| simdjson (ondemand) | 908.639 | 0.0996497 | 6545.18ms | 466906 | 160 | 3.81547e+07 | 490047 | 0.0191106 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3476.5 | 0.21584 | 9836.8ms | 699405 | 1280 | 2.19506e+08 | 191861 | 0.488745 | 1(Win) | true |
| glaze | 2085.05 | 0.327678 | 8183.63ms | 699405 | 640 | 7.03236e+08 | 319899 | 0.75996 | 2(Loss) | true |
| simdjson (ondemand) | 602.772 | 1.33286 | 7002.49ms | 767297 | 30 | 7.85442e+09 | 1.21398e+06 | 0.112143 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3046.79 | 0.361669 | 5392.41ms | 699405 | 640 | 4.01214e+08 | 218920 | 1.07906 | 1(Win) | true |
| glaze | 2141.6 | 0.624277 | 8305.03ms | 699405 | 160 | 6.04863e+08 | 311452 | 1.0706 | 2(Loss) | true |
| simdjson (ondemand) | 629.595 | 0.856868 | 7395.54ms | 767297 | 30 | 2.97546e+09 | 1.16226e+06 | 0.508026 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1884.28 | 0.437493 | 7468.41ms | 631514 | 640 | 1.25141e+09 | 319623 | 0.907019 | 1(Win) | true |
| glaze | 1730.66 | 0.132736 | 8748.36ms | 631514 | 1280 | 2.73104e+08 | 347993 | 0.0687584 | 2(Loss) | true |
