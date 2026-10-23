# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest Results: (Oct 23, 2026)
#### Using the following commits:
----
| Jsonifier: [b975cd7](https://github.com/nihilai-collective/jsonifier/commit/b975cd7)  
| Glaze: [628bec1](https://github.com/stephenberry/glaze/commit/628bec1)  
| Simdjson: [2cc1e70](https://github.com/simdjson/simdjson/commit/2cc1e70)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `NEON` |
| **simdjson (ondemand)** | `arm64` |
| **simdjson (reflection)** | `arm64` |
| **Glaze** | utf8: `NEON64`, escape: `NEON`, float: `NEON`, struct-skip: `NEON64` |

> **Adaptive Sampling & Convergence (Apple M1 (Virtual)-NEON):**  
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
*Environment generated via BenchmarkSuite commit: [ab75024](https://github.com/nihilai-collective/benchmarksuite/commit/ab75024)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1516.24 | 1.26808 | 60.5819ms | 905 | 4890 | 254781 | 569.22 | 2.36356 | 1(Win) | true |
| glaze | 1358.1 | 1.5768 | 89.0939ms | 905 | 2560 | 257053 | 635.5 | 0.521987 | 2(Loss) | true |
| jsonifier (two-stage) | 217.813 | 0.177876 | 402.5ms | 905 | 4890 | 242924 | 3962.45 | 0.526441 | 3(Loss) | true |
| simdjson (ondemand) | 183.649 | 0.504585 | 503.403ms | 905 | 640 | 359890 | 4699.6 | 0.00851209 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 1518.96 | 1.75099 | 59.1181ms | 905 | 2560 | 253401 | 568.2 | 0.52521 | 1(Tie) | true |
| glaze STATISTICAL TIE | 1471.05 | 1.24336 | 64.9859ms | 905 | 4890 | 260221 | 586.706 | 0.994612 | 1(Tie) | true |
| jsonifier (two-stage) | 220.364 | 0.219754 | 394.291ms | 905 | 4890 | 362242 | 3916.59 | 0.0610749 | 3(Loss) | true |
| simdjson (ondemand) | 189.854 | 0.564498 | 480.514ms | 905 | 640 | 421467 | 4546 | 0.149359 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1861.28 | 2.13704 | 49.355ms | 905 | 2560 | 251385 | 463.7 | 0.021561 | 1(Win) | true |
| simdjson (reflection) | 197.193 | 0.51577 | 470.576ms | 905 | 640 | 326141 | 4376.8 | 1.42751 | 2(Loss) | true |
| glaze | 109.963 | 0.113768 | 807.008ms | 905 | 4890 | 389897 | 7848.78 | 0.264202 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3069.46 | 2.29641 | 39.0218ms | 905 | 4890 | 203883 | 281.181 | 1.33993 | 1(Win) | true |
| simdjson (reflection) | 2590.52 | 2.06086 | 44.405ms | 905 | 4890 | 230531 | 333.166 | 1.23563 | 2(Loss) | true |
| glaze | 732.032 | 0.63582 | 149.58ms | 905 | 4890 | 274799 | 1179.01 | 0.36225 | 3(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 886.013 | 0.283579 | 200.32ms | 1811 | 2560 | 78224.9 | 1949.3 | 0.097376 | 1(Win) | true |
| glaze | 770.822 | 0.602504 | 227.299ms | 1811 | 1280 | 233270 | 2240.6 | 0.151515 | 2(Loss) | true |
| jsonifier (two-stage) | 272.371 | 0.157305 | 639.674ms | 1811 | 4890 | 486530 | 6341 | 0.675121 | 3(Loss) | true |
| simdjson (ondemand) | 142.519 | 0.179694 | 1255.33ms | 1811 | 640 | 303486 | 12118.4 | 0.237092 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1060.35 | 0.613196 | 165.57ms | 1811 | 2560 | 255373 | 1628.8 | 0.357363 | 1(Win) | true |
| glaze | 920.876 | 0.375251 | 190.61ms | 1811 | 4890 | 242208 | 1875.5 | 0.0694175 | 2(Loss) | true |
| jsonifier (two-stage) | 314.431 | 0.157699 | 554.528ms | 1811 | 4890 | 366904 | 5492.8 | 0.40391 | 3(Loss) | true |
| simdjson (ondemand) | 146.206 | 0.21214 | 1197.28ms | 1811 | 640 | 401911 | 11812.8 | 0.175771 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 252.96 | 0.386276 | 738.17ms | 1997 | 320 | 270644 | 7528.8 | 0.391617 | 1(Win) | true |
| jsonifier | 245.418 | 0.13213 | 710.404ms | 1811 | 1280 | 110672 | 7037.4 | 0.0483367 | 2(Loss) | true |
| glaze | 187.06 | 0.163648 | 924.99ms | 1798 | 1280 | 288037 | 9166.6 | 0.159528 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 756.123 | 0.304365 | 239.463ms | 1811 | 4890 | 236348 | 2284.16 | 0.632597 | 1(Win) | true |
| simdjson (reflection) | 623.97 | 0.157337 | 318.553ms | 1997 | 4890 | 112772 | 3052.21 | 0.199096 | 2(Loss) | true |
| glaze | 434.248 | 0.145168 | 413.526ms | 1798 | 4890 | 160679 | 3948.68 | 0.182456 | 3(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2145.88 | 0.407169 | 174.988ms | 3862 | 4890 | 238820 | 1716.35 | 0.518403 | 1(Win) | true |
| glaze | 1228.19 | 0.371545 | 305.396ms | 3862 | 640 | 79450.7 | 2998.8 | 0.120192 | 2(Loss) | true |
| jsonifier (two-stage) | 580.248 | 0.127107 | 639.201ms | 3862 | 4890 | 318308 | 6347.44 | 0.0261635 | 3(Loss) | true |
| simdjson (ondemand) | 433.458 | 0.20641 | 851.566ms | 3862 | 1280 | 393734 | 8497 | 0.228838 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2697.99 | 0.54969 | 144.062ms | 3862 | 4890 | 275352 | 1365.12 | 0.660462 | 1(Win) | true |
| glaze | 1381.19 | 0.583367 | 268.364ms | 3862 | 1280 | 309749 | 2666.6 | 0.127666 | 2(Loss) | true |
| jsonifier (two-stage) | 610.389 | 0.194764 | 613.713ms | 3862 | 4890 | 675364 | 6034.01 | 0.478163 | 3(Loss) | true |
| simdjson (ondemand) | 416.866 | 1.28963 | 936.472ms | 3862 | 80 | 1.03861e+06 | 8835.2 | 1.60371 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 705.033 | 0.478481 | 651.141ms | 3862 | 320 | 199934 | 5224 | 0.245625 | 1(Win) | true |
| simdjson (reflection) | 690.701 | 0.161919 | 544.637ms | 3862 | 4890 | 364545 | 5332.39 | 0.385757 | 2(Loss) | true |
| glaze | 468.539 | 0.263671 | 801.264ms | 3862 | 640 | 274941 | 7860.8 | 0.081483 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4685.87 | 2.08369 | 96.8591ms | 3862 | 640 | 171669 | 786 | 0.357508 | 1(Win) | true |
| simdjson (reflection) | 2810.4 | 0.523797 | 144.595ms | 3862 | 4890 | 230421 | 1310.52 | 0.620227 | 2(Loss) | true |
| glaze | 1950.99 | 0.295721 | 207.872ms | 3862 | 4890 | 152401 | 1887.8 | 0.324371 | 3(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1122.97 | 0.0914576 | 826.911ms | 9578 | 4890 | 270621 | 8134.05 | 0.212888 | 1(Win) | true |
| glaze | 980.298 | 0.101658 | 946.551ms | 9578 | 4890 | 438760 | 9317.88 | 1.03263 | 2(Loss) | true |
| simdjson (ondemand) | 736.274 | 0.132519 | 1350.65ms | 9578 | 2560 | 691935 | 12406.1 | 0.103873 | 3(Loss) | true |
| jsonifier (two-stage) | 600.83 | 0.57521 | 1518.36ms | 9578 | 1280 | 9.78835e+06 | 15202.8 | 1.64074 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1770.01 | 0.340239 | 809.65ms | 9578 | 2560 | 789239 | 5160.6 | 0.00775044 | 1(Win) | true |
| glaze | 1494.78 | 0.239824 | 891.723ms | 9578 | 640 | 137455 | 6110.8 | 0.0327397 | 2(Loss) | true |
| simdjson (ondemand) | 1008.65 | 0.416973 | 1247.94ms | 9578 | 320 | 456287 | 9056 | 0.194725 | 3(Loss) | true |
| jsonifier (two-stage) | 860.751 | 0.372911 | 1397.84ms | 9578 | 320 | 501134 | 10612 | 0.416351 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 1133.62 | 0.210862 | 868.162ms | 9578 | 1280 | 369502 | 8057.6 | 0.323721 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1129.89 | 0.11098 | 820.906ms | 9578 | 4890 | 393619 | 8084.21 | 0.0802431 | 1(Tie) | true |
| glaze | 971.919 | 0.159704 | 963.723ms | 9578 | 2560 | 576718 | 9398.2 | 0.0319108 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 9335.95 | 0.553041 | 117.06ms | 9578 | 1280 | 37476.3 | 978.4 | 0.609508 | 1(Win) | true |
| jsonifier | 8045 | 0.932828 | 142.161ms | 9578 | 2560 | 287171 | 1135.4 | 1.42934 | 2(Loss) | true |
| glaze | 4021.65 | 0.306677 | 248.079ms | 9578 | 4890 | 237253 | 2271.28 | 0.228594 | 3(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2104.18 | 0.462578 | 177.235ms | 3873 | 4890 | 322409 | 1755.35 | 1.02756 | 1(Win) | true |
| glaze | 1374.5 | 0.313758 | 273.93ms | 3873 | 4890 | 347619 | 2687.21 | 0.418206 | 2(Loss) | true |
| jsonifier (two-stage) | 571.196 | 0.317142 | 647.857ms | 3873 | 1280 | 538322 | 6466.4 | 0.0927013 | 3(Loss) | true |
| simdjson (ondemand) | 415.618 | 0.109892 | 914.367ms | 3873 | 4890 | 466393 | 8886.97 | 0.0543273 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2644.52 | 0.520036 | 151.311ms | 3873 | 4890 | 257975 | 1396.69 | 0.236258 | 1(Win) | true |
| glaze | 1552.06 | 0.630427 | 243.454ms | 3873 | 1280 | 288111 | 2379.8 | 0.804812 | 2(Loss) | true |
| jsonifier (two-stage) | 596.817 | 0.325848 | 629.249ms | 3873 | 1280 | 520537 | 6188.8 | 0.233221 | 3(Loss) | true |
| simdjson (ondemand) | 426.747 | 0.246002 | 876.789ms | 3873 | 2560 | 1.16057e+06 | 8655.2 | 0.646542 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 706.527 | 0.280876 | 527.412ms | 3873 | 1280 | 275980 | 5227.8 | 0.195492 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 703.593 | 0.611285 | 595.658ms | 3873 | 320 | 329526 | 5249.6 | 0.243235 | 1(Tie) | true |
| glaze | 473.038 | 0.147562 | 801.435ms | 3873 | 4890 | 649174 | 7808.21 | 0.0129292 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4557.7 | 0.744845 | 91.669ms | 3873 | 4890 | 178174 | 810.405 | 2.16905 | 1(Win) | true |
| simdjson (reflection) | 2871.98 | 0.517288 | 146.962ms | 3873 | 4890 | 216424 | 1286.07 | 0.458761 | 2(Loss) | true |
| glaze | 2148.78 | 0.490532 | 201.349ms | 3873 | 4890 | 347659 | 1718.92 | 0.745339 | 3(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 618.859 | 1.61557 | 5173.23ms | 2090234 | 80 | 2.16644e+11 | 3.22109e+06 | 1.22697 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 599.875 | 0.384321 | 5068.19ms | 2090234 | 40 | 6.52405e+09 | 3.32303e+06 | 0.526403 | 1(Tie) | true |
| simdjson (reflection) DID NOT CONVERGE | 496.702 | 0.289042 | 6319.35ms | 2090234 | 80 | 1.07649e+10 | 4.01327e+06 | 9.0542 | -(Loss) | false |
| glaze | 476.768 | 0.381335 | 6588.96ms | 2090234 | 40 | 1.01683e+10 | 4.18108e+06 | 3.87906 | 4(Loss) | true |
| simdjson (ondemand) | 436.468 | 0.905947 | 7110.98ms | 2090234 | 40 | 6.84778e+10 | 4.56712e+06 | 2.52037 | 5(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 797.451 | 0.904597 | 9887.76ms | 2090234 | 80 | 4.09056e+10 | 2.49972e+06 | 0.00204827 | 1(Win) | true |
| jsonifier (two-stage) | 735.865 | 0.124856 | 5324.78ms | 2090234 | 30 | 3.43187e+08 | 2.70892e+06 | 1.62292 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 575.115 | 2.16909 | 6582.65ms | 2090234 | 30 | 1.69573e+11 | 3.46609e+06 | 0.183258 | 3(Tie) | true |
| glaze STATISTICAL TIE | 557.936 | 0.149592 | 6467.51ms | 2090234 | 80 | 2.28523e+09 | 3.57282e+06 | 0.281397 | 3(Tie) | true |
| simdjson (ondemand) | 512.016 | 0.0755685 | 7069.29ms | 2090234 | 40 | 3.4623e+08 | 3.89324e+06 | 0.700121 | 5(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2037.23 | 0.698337 | 6256.34ms | 2090234 | 320 | 1.49413e+10 | 978486 | 0.818761 | 1(Win) | true |
| glaze | 1435.82 | 0.227925 | 9185.19ms | 2090234 | 40 | 4.00525e+08 | 1.38833e+06 | 0.0839823 | 2(Loss) | true |
| simdjson (reflection) | 697.191 | 0.797943 | 9081.5ms | 2090326 | 40 | 2.08223e+10 | 2.85932e+06 | 2.62872 | 3(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2075.93 | 0.469238 | 6513.95ms | 2090234 | 30 | 6.0908e+08 | 960247 | 0.375377 | 1(Win) | true |
| glaze | 1405.1 | 1.90772 | 9071.55ms | 2090234 | 160 | 1.17198e+11 | 1.41869e+06 | 0.0413733 | 2(Loss) | true |
| simdjson (reflection) | 696.484 | 0.906214 | 9136.11ms | 2090326 | 40 | 2.69109e+10 | 2.86222e+06 | 4.8936 | 3(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 1629.62 | 1.44439 | 5821.27ms | 6661897 | 80 | 2.53678e+11 | 3.89863e+06 | 1.61803 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE DID NOT CONVERGE | 1588.56 | 0.245069 | 6364.01ms | 6661897 | 40 | 3.84259e+09 | 3.99939e+06 | 6.29292 | -(Tie) | false |
| simdjson (reflection) DID NOT CONVERGE | 1356.72 | 0.568734 | 7295.9ms | 6661897 | 80 | 5.67445e+10 | 4.68282e+06 | 5.02731 | -(Loss) | false |
| simdjson (ondemand) STATISTICAL TIE DID NOT CONVERGE | 1137.23 | 2.81641 | 8021.89ms | 6661897 | 80 | 1.98051e+12 | 5.58661e+06 | 7.54582 | -(Tie) | false |
| glaze STATISTICAL TIE | 1122.69 | 0.403153 | 8750.67ms | 6661897 | 80 | 4.16396e+10 | 5.65899e+06 | 0.0239703 | 4(Tie) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1967.4 | 0.815573 | 6295.28ms | 6661897 | 80 | 5.54914e+10 | 3.22927e+06 | 0.208059 | 1(Win) | true |
| jsonifier (two-stage) | 1829.14 | 0.379838 | 6195.03ms | 6661897 | 80 | 1.39249e+10 | 3.47338e+06 | 2.25666 | 2(Loss) | true |
| simdjson (reflection) | 1597.36 | 1.11653 | 7118.35ms | 6661897 | 40 | 7.8885e+10 | 3.97737e+06 | 0.475758 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1356.91 | 1.25141 | 8011.25ms | 6661897 | 30 | 1.02994e+11 | 4.68215e+06 | 0.391398 | 4(Tie) | true |
| glaze STATISTICAL TIE | 1353 | 0.420106 | 8191.63ms | 6661897 | 40 | 1.5566e+10 | 4.69569e+06 | 0.724573 | 4(Tie) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5632.68 | 1.31263 | 7449.95ms | 6661897 | 320 | 7.01453e+10 | 1.12793e+06 | 2.81616 | 1(Win) | true |
| glaze DID NOT CONVERGE | 2911.13 | 0.312212 | 7271.43ms | 6661897 | 160 | 7.42831e+09 | 2.18241e+06 | 7.16785 | -(Loss) | false |
| simdjson (reflection) | 227.945 | 1.48761 | 8645.82ms | 6661989 | 30 | 5.15763e+12 | 2.78724e+07 | 2.73601 | 3(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 5699.99 | 1.921 | 7816.34ms | 6661897 | 160 | 7.33535e+10 | 1.11461e+06 | 5.55537 | -(Win) | false |
| glaze | 3224.3 | 0.186223 | 6359.94ms | 6661897 | 40 | 5.3858e+08 | 1.97044e+06 | 0.291762 | 2(Loss) | true |
| simdjson (reflection) | 232.036 | 1.38412 | 8275.52ms | 6661989 | 30 | 4.30888e+12 | 2.7381e+07 | 2.95048 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1751.24 | 0.36703 | 7319.84ms | 500299 | 80 | 7.99946e+07 | 272448 | 0.110285 | 1(Win) | true |
| jsonifier (two-stage) | 1154.29 | 0.53319 | 5927.89ms | 500299 | 30 | 1.45718e+08 | 413346 | 0.0866319 | 2(Loss) | true |
| glaze DID NOT CONVERGE | 1069.84 | 0.763136 | 6157.93ms | 500299 | 640 | 7.41323e+09 | 445976 | 6.66147 | -(Loss) | false |
| simdjson (ondemand) | 977.235 | 0.273757 | 7019.98ms | 500299 | 80 | 1.42916e+08 | 488237 | 2.39637 | 4(Loss) | true |
| simdjson (reflection) | 929.909 | 1.12872 | 6868.26ms | 500299 | 80 | 2.6831e+09 | 513085 | 1.81805 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2249.05 | 0.290401 | 7436.34ms | 500299 | 80 | 3.03632e+07 | 212144 | 0.185191 | 1(Win) | true |
| jsonifier (two-stage) | 1336 | 0.367583 | 5664.06ms | 500299 | 30 | 5.16988e+07 | 357129 | 1.22492 | 2(Loss) | true |
| glaze | 1294.1 | 0.426123 | 5624.64ms | 500299 | 30 | 7.40484e+07 | 368691 | 0.043956 | 3(Loss) | true |
| simdjson (ondemand) | 1096.52 | 0.377472 | 6597.74ms | 500299 | 30 | 8.09309e+07 | 435123 | 0.648819 | 4(Loss) | true |
| simdjson (reflection) | 1065.19 | 0.144396 | 6671.52ms | 500299 | 640 | 2.67729e+08 | 447923 | 3.26235 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7747.86 | 0.152491 | 6253.53ms | 500299 | 1280 | 1.12874e+07 | 61581.2 | 0.228513 | 1(Win) | true |
| simdjson (reflection) | 6674.59 | 0.10303 | 7405.54ms | 500299 | 1280 | 6.94303e+06 | 71483.4 | 0.237541 | 2(Loss) | true |
| glaze | 1800.47 | 0.285383 | 7271.95ms | 500299 | 80 | 4.57542e+07 | 264998 | 0.925992 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7851.81 | 0.688994 | 6280.38ms | 500299 | 30 | 5.25862e+06 | 60765.9 | 0.11247 | 1(Win) | true |
| simdjson (reflection) | 6174.77 | 0.58037 | 7876.91ms | 500299 | 640 | 1.28708e+08 | 77269.6 | 0.881527 | 2(Loss) | true |
| glaze | 1826.3 | 0.222133 | 6692.84ms | 500299 | 1280 | 4.31075e+08 | 261251 | 0.406158 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2935.02 | 0.309977 | 6061.59ms | 1439562 | 320 | 6.72743e+08 | 467757 | 0.0900423 | 1(Win) | true |
| jsonifier (two-stage) | 2575.74 | 0.312222 | 7186.64ms | 1439562 | 640 | 1.77241e+09 | 533002 | 0.680697 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 2102.43 | 1.89551 | 9067.4ms | 1439562 | 160 | 2.45126e+10 | 652994 | 2.68073 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE DID NOT CONVERGE | 1962.8 | 2.89101 | 9071.17ms | 1439562 | 640 | 2.61691e+11 | 699447 | 9.13528 | -(Tie) | false |
| glaze | 1717.15 | 0.158526 | 5173.88ms | 1439562 | 160 | 2.57021e+08 | 799509 | 0.079512 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3442.3 | 0.166266 | 5860.52ms | 1439562 | 160 | 7.03542e+07 | 398824 | 0.169411 | 1(Win) | true |
| jsonifier (two-stage) | 2904.06 | 0.655208 | 7123.99ms | 1439562 | 40 | 3.83767e+08 | 472742 | 0.764837 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 2363.6 | 0.141069 | 8519.93ms | 1439562 | 320 | 2.14847e+08 | 580841 | 0.40562 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2343.68 | 0.48311 | 8863.77ms | 1439562 | 640 | 5.12552e+09 | 585778 | 2.66513 | 3(Tie) | true |
| glaze | 1817.46 | 0.29393 | 5439.41ms | 1439562 | 40 | 1.97187e+08 | 755379 | 0 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 17591.6 | 0.350342 | 8739.52ms | 1439562 | 160 | 1.19607e+07 | 78041.6 | 0.42413 | 1(Win) | true |
| glaze | 3070.85 | 0.664133 | 7350.54ms | 1439584 | 160 | 1.41055e+09 | 447074 | 2.95921 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 277.283 | 0.700177 | 9247.02ms | 1439562 | 80 | 9.61436e+10 | 4.95116e+06 | 8.05229 | -(Loss) | false |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16257.6 | 2.73725 | 5245.89ms | 1439562 | 160 | 8.54857e+08 | 84444.8 | 3.08851 | 1(Win) | true |
| glaze | 3025.36 | 2.01704 | 5402.47ms | 1439584 | 320 | 2.68102e+10 | 453795 | 1.09643 | 2(Loss) | true |
| simdjson (reflection) | 208.159 | 3.51172 | 8852.57ms | 1439562 | 30 | 1.60928e+12 | 6.5953e+06 | 3.70898 | 3(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1490.42 | 0.430114 | 3865.85ms | 56369 | 640 | 1.54032e+07 | 36068.8 | 1.31002 | 1(Win) | true |
| glaze | 1223.81 | 0.703129 | 4962.1ms | 56369 | 80 | 7.63153e+06 | 43926.4 | 0.557809 | 2(Loss) | true |
| jsonifier (two-stage) | 1039.24 | 0.141692 | 5558.69ms | 56369 | 2560 | 1.37525e+07 | 51727.9 | 0.350032 | 3(Loss) | true |
| simdjson (ondemand) | 818.508 | 0.401714 | 7197.25ms | 56369 | 320 | 2.22751e+07 | 65677.6 | 0.59211 | 4(Loss) | true |
| simdjson (reflection) | 765.364 | 0.760511 | 6951.63ms | 56369 | 2560 | 7.30458e+08 | 70238 | 0.877533 | 5(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1997.54 | 1.03187 | 3566.85ms | 56369 | 80 | 6.1693e+06 | 26912 | 0.646242 | 1(Win) | true |
| glaze | 1578.58 | 0.845769 | 4269.94ms | 56369 | 80 | 6.63652e+06 | 34054.4 | 0.560643 | 2(Loss) | true |
| jsonifier (two-stage) | 1312.6 | 0.474776 | 5223.42ms | 56369 | 320 | 1.20989e+07 | 40955.2 | 0.229966 | 3(Loss) | true |
| simdjson (reflection) | 901.829 | 1.98917 | 7228.34ms | 56369 | 160 | 2.24954e+08 | 59609.6 | 0.883261 | 4(Loss) | true |
| simdjson (ondemand) | 733.448 | 2.26665 | 7344.07ms | 56369 | 640 | 1.76641e+09 | 73294.4 | 2.36762 | 5(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10385.1 | 1.16238 | 599.001ms | 56369 | 1280 | 4.63404e+06 | 5176.4 | 1.57771 | 1(Win) | true |
| simdjson (reflection) | 7950.44 | 0.872691 | 708.295ms | 56369 | 1280 | 4.45687e+06 | 6761.6 | 1.69807 | 2(Loss) | true |
| glaze | 2533.92 | 0.314354 | 2320.5ms | 56369 | 320 | 1.42325e+06 | 21215.2 | 0.519293 | 3(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10838.7 | 0.90814 | 526.005ms | 56369 | 1280 | 2.59683e+06 | 4959.8 | 0.261422 | 1(Win) | true |
| simdjson (reflection) | 8507.58 | 0.380254 | 689.648ms | 56369 | 640 | 369485 | 6318.8 | 1.25641 | 2(Loss) | true |
| glaze | 2802.1 | 0.525875 | 2111.39ms | 56369 | 1280 | 1.30284e+07 | 19184.8 | 0.226748 | 3(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1904.29 | 0.554926 | 5814.01ms | 94370 | 80 | 5.50252e+06 | 47260.8 | 1.58894 | 1(Win) | true |
| jsonifier (two-stage) | 1608.95 | 0.190983 | 6149.55ms | 94370 | 30 | 342369 | 55936 | 0.306044 | 2(Loss) | true |
| glaze | 1521.63 | 0.669456 | 6557.58ms | 94370 | 1280 | 2.00679e+08 | 59145.8 | 0.987925 | 3(Loss) | true |
| simdjson (reflection) | 1359.88 | 0.446369 | 6776.23ms | 94370 | 1280 | 1.11703e+08 | 66181.2 | 0.59659 | 4(Loss) | true |
| simdjson (ondemand) | 1302 | 0.195388 | 7848.49ms | 94370 | 2560 | 4.66961e+07 | 69122.9 | 0.104776 | 5(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2122.31 | 0.428471 | 5379.91ms | 94370 | 4890 | 1.61437e+08 | 42405.7 | 0.871359 | 1(Win) | true |
| jsonifier (two-stage) | 2017.34 | 0.62312 | 6032.96ms | 94370 | 30 | 2.31832e+06 | 44612.3 | 1.59985 | 2(Loss) | true |
| glaze | 1835.16 | 2.10056 | 5375.96ms | 94370 | 30 | 3.18355e+07 | 49041.1 | 0.104293 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1562.88 | 0.558275 | 6713.08ms | 94370 | 640 | 6.61444e+07 | 57584.8 | 0.328943 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1546.76 | 0.139053 | 6843.62ms | 94370 | 4890 | 3.20104e+07 | 58185.1 | 0.652861 | 4(Tie) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12818.8 | 0.430794 | 737.259ms | 94370 | 40 | 36590.9 | 7020.8 | 0.151699 | 1(Win) | true |
| glaze | 2242.99 | 0.181495 | 4180.31ms | 94370 | 4890 | 2.5933e+07 | 40124.2 | 0.0026223 | 2(Loss) | true |
| simdjson (reflection) | 308.068 | 0.576065 | 7747.75ms | 94370 | 160 | 4.53146e+08 | 292138 | 1.71077 | 3(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13191.6 | 0.93616 | 724.302ms | 94370 | 40 | 163168 | 6822.4 | 0.559701 | 1(Win) | true |
| glaze | 2555.84 | 0.601609 | 3783.31ms | 94370 | 80 | 3.59021e+06 | 35212.8 | 0.677036 | 2(Loss) | true |
| simdjson (reflection) | 298.85 | 0.394828 | 7771.3ms | 94370 | 160 | 2.26203e+08 | 301149 | 0.671276 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1678.51 | 0.552833 | 670.566ms | 11812 | 320 | 440493 | 6711.2 | 0.659947 | 1(Win) | true |
| glaze | 868.983 | 0.272665 | 1341.11ms | 11812 | 160 | 199895 | 12963.2 | 1.57974 | 2(Loss) | true |
| simdjson (reflection) | 797.581 | 0.469783 | 1460.58ms | 11812 | 2560 | 1.12702e+07 | 14123.7 | 0.795814 | 3(Loss) | true |
| jsonifier (two-stage) | 761.202 | 0.291582 | 1533.7ms | 11812 | 2560 | 4.76659e+06 | 14798.7 | 0.649194 | 4(Loss) | true |
| simdjson (ondemand) | 649.186 | 0.346359 | 2013.85ms | 11812 | 1280 | 4.6235e+06 | 17352.2 | 0.727936 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1970.61 | 0.469947 | 723.761ms | 11812 | 640 | 461874 | 5716.4 | 1.91489 | 1(Win) | true |
| jsonifier (two-stage) | 1132.28 | 0.941386 | 1226.2ms | 11812 | 160 | 1.40345e+06 | 9948.8 | 0.614887 | 2(Loss) | true |
| glaze | 1012.34 | 0.559561 | 1308.84ms | 11812 | 30 | 116308 | 11127.5 | 0 | 3(Loss) | true |
| simdjson (reflection) | 941.023 | 0.243278 | 1406.55ms | 11812 | 640 | 542792 | 11970.8 | 0.244523 | 4(Loss) | true |
| simdjson (ondemand) | 656.044 | 0.46733 | 2022.46ms | 11812 | 1280 | 8.24212e+06 | 17170.8 | 0.447588 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9706.02 | 0.639186 | 119.758ms | 11812 | 2560 | 140883 | 1160.6 | 0.66758 | 1(Win) | true |
| simdjson (reflection) | 7508.87 | 0.938322 | 162.967ms | 11812 | 1280 | 253637 | 1500.2 | 0.0133333 | 2(Loss) | true |
| glaze | 1407.35 | 2.0282 | 863.095ms | 11812 | 30 | 790650 | 8004.27 | 4.9217 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10112.9 | 0.742147 | 147.81ms | 11812 | 2560 | 174950 | 1113.9 | 0.651088 | 1(Win) | true |
| simdjson (reflection) | 7830.39 | 1.05642 | 149.782ms | 11812 | 1280 | 295640 | 1438.6 | 1.19584 | 2(Loss) | true |
| glaze | 1760.13 | 1.35613 | 718.234ms | 11812 | 30 | 225986 | 6400 | 0.401606 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2668.03 | 0.346857 | 1265.69ms | 31235 | 320 | 479902 | 11164.8 | 0.143102 | 1(Win) | true |
| jsonifier (two-stage) | 1977.43 | 0.548804 | 1644.82ms | 31235 | 160 | 1.09354e+06 | 15064 | 1.53734 | 2(Loss) | true |
| simdjson (reflection) | 1879.23 | 0.621048 | 1881.78ms | 31235 | 160 | 1.55058e+06 | 15851.2 | 0.232699 | 3(Loss) | true |
| glaze | 1551.85 | 0.257806 | 2102.07ms | 31235 | 640 | 1.5673e+06 | 19195.2 | 0.849025 | 4(Loss) | true |
| simdjson (ondemand) | 1492.03 | 0.45402 | 2229.98ms | 31235 | 320 | 2.62924e+06 | 19964.8 | 0.556048 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2840.64 | 0.19833 | 1131.6ms | 31235 | 4890 | 2.11513e+06 | 10486.4 | 0.0641633 | 1(Win) | true |
| jsonifier (two-stage) | 2420.06 | 0.380602 | 1698.01ms | 31235 | 160 | 351151 | 12308.8 | 0.378392 | 2(Loss) | true |
| simdjson (reflection) | 1898.39 | 0.436746 | 1753.17ms | 31235 | 2560 | 1.2023e+07 | 15691.2 | 0.444251 | 3(Loss) | true |
| glaze | 1676.91 | 0.242256 | 2009.5ms | 31235 | 640 | 1.1852e+06 | 17763.6 | 0.593186 | 4(Loss) | true |
| simdjson (ondemand) | 1601.99 | 0.333121 | 2360.96ms | 31235 | 640 | 2.45554e+06 | 18594.4 | 0.0516018 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 17291.5 | 0.693162 | 207.114ms | 31235 | 2560 | 365030 | 1722.7 | 1.4427 | 1(Win) | true |
| glaze | 2509.61 | 0.675728 | 1501.84ms | 31235 | 320 | 2.05857e+06 | 11869.6 | 0.658073 | 2(Loss) | true |
| simdjson (reflection) | 278.472 | 0.30256 | 5952.21ms | 31235 | 320 | 3.35193e+07 | 106970 | 0.277438 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 20110.7 | 1.35877 | 163.6ms | 31235 | 640 | 259239 | 1481.2 | 3.06283 | 1(Win) | true |
| glaze | 2811.46 | 0.355836 | 1081.51ms | 31235 | 640 | 909699 | 10595.2 | 0.218489 | 2(Loss) | true |
| simdjson (reflection) | 209.249 | 1.22262 | 6265.4ms | 31235 | 1280 | 3.87745e+09 | 142357 | 1.67466 | 3(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2354.47 | 0.464698 | 4737.3ms | 108313 | 40 | 1.66256e+06 | 43872 | 0.00486287 | 1(Win) | true |
| jsonifier (two-stage) | 1395.82 | 0.484713 | 8295.69ms | 108313 | 40 | 5.14672e+06 | 74003.2 | 0.661512 | 2(Loss) | true |
| glaze | 1162.65 | 0.743686 | 5128.48ms | 108313 | 80 | 3.49247e+07 | 88844.8 | 3.0663 | 3(Loss) | true |
| simdjson (ondemand) | 1079.35 | 0.865806 | 5115.86ms | 108313 | 30 | 2.05968e+07 | 95701.3 | 0.0712822 | 4(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 599.456 | 4.59209 | 7024.08ms | 108313 | 160 | 1.00181e+10 | 172315 | 10.8382 | -(Loss) | false |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2767.95 | 0.538005 | 4478.31ms | 108313 | 160 | 6.44969e+06 | 37318.4 | 0.119904 | 1(Win) | true |
| jsonifier (two-stage) | 1533.1 | 0.290609 | 7528.08ms | 108313 | 320 | 1.22685e+07 | 67376.8 | 0.247542 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1180.31 | 0.317338 | 6899.47ms | 108313 | 160 | 1.23404e+07 | 87515.2 | 0.14787 | 3(Tie) | true |
| glaze STATISTICAL TIE | 1137.53 | 4.04224 | 9280.41ms | 108313 | 160 | 2.15575e+09 | 90806.4 | 3.06084 | 3(Tie) | true |
| simdjson (reflection) | 1132.23 | 0.667417 | 8059.43ms | 108313 | 40 | 1.48303e+07 | 91232 | 0.988609 | 5(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12748.7 | 0.60448 | 925.055ms | 108313 | 40 | 95951.4 | 8102.4 | 0.367261 | 1(Win) | true |
| simdjson (reflection) | 7032.68 | 0.280435 | 1555.91ms | 108313 | 2560 | 4.34335e+06 | 14687.9 | 0.0768749 | 2(Loss) | true |
| glaze | 1611.41 | 1.21549 | 7027.26ms | 108313 | 30 | 1.82127e+07 | 64102.4 | 0.683554 | 3(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12913.9 | 0.929069 | 885.968ms | 108313 | 640 | 3.53448e+06 | 7998.8 | 0.447056 | 1(Win) | true |
| simdjson (reflection) | 7068.63 | 0.283675 | 1547ms | 108313 | 1280 | 2.19959e+06 | 14613.2 | 0.22221 | 2(Loss) | true |
| glaze | 1788.36 | 0.254947 | 6056.34ms | 108313 | 2560 | 5.55125e+07 | 57759.8 | 0.0828251 | 3(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2738.15 | 0.642664 | 7697.31ms | 213963 | 80 | 1.83494e+07 | 74521.6 | 0.0945586 | 1(Win) | true |
| jsonifier (two-stage) | 2299.15 | 0.158061 | 9379.15ms | 213963 | 1280 | 2.51886e+07 | 88750.8 | 1.6507 | 2(Loss) | true |
| glaze | 1943.37 | 0.751561 | 5641.1ms | 213963 | 40 | 2.49089e+07 | 104998 | 0.028453 | 3(Loss) | true |
| simdjson (ondemand) | 1832.76 | 0.133464 | 6144.85ms | 213963 | 1280 | 2.82623e+07 | 111336 | 0.0427353 | 4(Loss) | true |
| simdjson (reflection) | 1796.74 | 0.399408 | 6051.75ms | 213963 | 1280 | 2.63362e+08 | 113568 | 0.406692 | 5(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3046.77 | 0.342689 | 7439.05ms | 213963 | 320 | 1.68557e+07 | 66972.8 | 0.323856 | 1(Win) | true |
| jsonifier (two-stage) | 2533.01 | 0.399289 | 5029.8ms | 213963 | 40 | 4.13847e+06 | 80556.8 | 0.0397078 | 2(Loss) | true |
| glaze | 2092.13 | 0.299847 | 5626.69ms | 213963 | 160 | 1.36842e+07 | 97532.8 | 0.240084 | 3(Loss) | true |
| simdjson (ondemand) | 1978.01 | 0.094164 | 5801.79ms | 213963 | 2560 | 2.41564e+07 | 103160 | 0.139781 | 4(Loss) | true |
| simdjson (reflection) | 1915.76 | 0.509504 | 5988.12ms | 213963 | 80 | 2.35603e+07 | 106512 | 0.419357 | 5(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 15207.7 | 0.741816 | 1441.3ms | 213963 | 80 | 792560 | 13417.6 | 0.0238436 | 1(Win) | true |
| glaze | 2032.09 | 0.228116 | 5635.29ms | 213963 | 320 | 1.67902e+07 | 100414 | 0.446543 | 2(Loss) | true |
| simdjson (reflection) | 301.924 | 0.467831 | 9343.07ms | 213963 | 640 | 6.39794e+09 | 675835 | 1.47853 | 3(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 15584.1 | 0.400227 | 1361.94ms | 213963 | 4890 | 1.34287e+07 | 13093.5 | 0.10808 | 1(Win) | true |
| glaze | 2259.76 | 0.599176 | 9634.76ms | 213963 | 40 | 1.17091e+07 | 90297.6 | 0.0354509 | 2(Loss) | true |
| simdjson (reflection) | 299.371 | 0.575791 | 9445.42ms | 213963 | 30 | 4.62073e+08 | 681600 | 4.769 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 529.724 | 2.81134 | 5018.88ms | 1834197 | 80 | 6.89458e+11 | 3.30214e+06 | 7.69157 | -(Win) | false |
| jsonifier (two-stage) | 464.195 | 0.139945 | 5719.58ms | 1834197 | 40 | 1.11241e+09 | 3.7683e+06 | 0.647337 | 2(Loss) | true |
| glaze | 447.341 | 0.350647 | 6305.09ms | 1834197 | 40 | 7.51992e+09 | 3.91027e+06 | 1.08513 | 3(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 435.164 | 0.470138 | 6251.24ms | 1834197 | 80 | 2.85711e+10 | 4.0197e+06 | 11.2357 | -(Loss) | false |
| simdjson (ondemand) | 405.315 | 0.178206 | 6881.05ms | 1834197 | 80 | 4.73193e+09 | 4.31572e+06 | 0.13595 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 657.89 | 0.202799 | 10029.3ms | 1834197 | 30 | 8.72245e+08 | 2.65884e+06 | 0.868246 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 515.751 | 1.61487 | 5686.8ms | 1834197 | 80 | 2.39983e+11 | 3.39161e+06 | 0.526239 | 2(Tie) | true |
| glaze STATISTICAL TIE | 501.215 | 0.507455 | 5987.73ms | 1834197 | 30 | 9.40937e+09 | 3.48997e+06 | 0.201147 | 2(Tie) | true |
| simdjson (reflection) | 467.629 | 1.4914 | 6880.01ms | 1834197 | 80 | 2.48982e+11 | 3.74063e+06 | 2.86522 | 4(Loss) | true |
| simdjson (ondemand) | 433.888 | 2.36442 | 6699.63ms | 1834197 | 80 | 7.26902e+11 | 4.03152e+06 | 0.0590991 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 995.081 | 3.26154 | 5399.85ms | 1834197 | 160 | 5.25945e+11 | 1.75787e+06 | 1.34929 | 1(Win) | true |
| glaze | 751.469 | 0.271389 | 8843.72ms | 1833577 | 40 | 1.59522e+09 | 2.32696e+06 | 0.884241 | 2(Loss) | true |
| simdjson (reflection) | 390.891 | 1.19441 | 7366.15ms | 1922245 | 80 | 2.51019e+11 | 4.68979e+06 | 2.33142 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 946.348 | 3.15142 | 5829.94ms | 1834197 | 80 | 2.71452e+11 | 1.8484e+06 | 1.17602 | 1(Win) | true |
| glaze | 753.868 | 0.244481 | 7942.29ms | 1833577 | 40 | 1.28635e+09 | 2.31955e+06 | 0.463768 | 2(Loss) | true |
| simdjson (reflection) | 396.089 | 2.8047 | 7127.92ms | 1922245 | 30 | 5.05504e+11 | 4.62824e+06 | 0.583615 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE DID NOT CONVERGE | 1732.5 | 4.91197 | 8451.64ms | 9930848 | 40 | 2.88403e+12 | 5.46656e+06 | 9.29085 | -(Tie) | false |
| simdjson (reflection) STATISTICAL TIE | 1632.91 | 3.11148 | 9867.63ms | 9930848 | 40 | 1.3027e+12 | 5.79996e+06 | 0.871281 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1532.54 | 2.90513 | 9772.83ms | 9930848 | 80 | 2.5785e+12 | 6.17979e+06 | 1.24322 | 3(Tie) | true |
| jsonifier STATISTICAL TIE | 1525.75 | 6.13073 | 8440.26ms | 9930848 | 40 | 5.7928e+12 | 6.20729e+06 | 4.36246 | 3(Tie) | true |
| glaze STATISTICAL TIE DID NOT CONVERGE | 1469.35 | 2.61676 | 9464.54ms | 9930848 | 80 | 2.27583e+12 | 6.44557e+06 | 12.7584 | -(Tie) | false |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 2064.79 | 5.03699 | 7208.18ms | 9930848 | 40 | 2.13513e+12 | 4.58682e+06 | 0.82732 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1921.48 | 3.15403 | 7990.31ms | 9930848 | 80 | 1.93341e+12 | 4.92892e+06 | 2.43354 | 1(Tie) | true |
| glaze STATISTICAL TIE DID NOT CONVERGE | 1787.72 | 1.70645 | 10659ms | 9930848 | 30 | 2.45177e+11 | 5.29768e+06 | 6.53959 | -(Tie) | false |
| simdjson (ondemand) STATISTICAL TIE DID NOT CONVERGE | 1702.57 | 4.45123 | 9705.06ms | 9930848 | 40 | 2.45235e+12 | 5.56265e+06 | 5.85448 | -(Tie) | false |
| simdjson (reflection) STATISTICAL TIE | 1674.4 | 3.3858 | 9776.68ms | 9930848 | 80 | 2.93406e+12 | 5.65625e+06 | 2.91762 | 3(Tie) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4910.58 | 4.11946 | 6158.99ms | 9930848 | 80 | 5.04986e+11 | 1.92865e+06 | 1.89348 | 1(Win) | true |
| glaze | 2297.96 | 2.55866 | 6312.91ms | 9930228 | 40 | 4.44755e+11 | 4.12114e+06 | 1.11173 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 216.526 | 1.38563 | 13504.1ms | 10018896 | 30 | 1.12158e+13 | 4.41275e+07 | 7.42341 | -(Loss) | false |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 4523.16 | 7.37842 | 6567.32ms | 9930848 | 40 | 9.54717e+11 | 2.09384e+06 | 8.18659 | -(Win) | false |
| glaze DID NOT CONVERGE | 2301.65 | 3.79149 | 6238.8ms | 9930228 | 30 | 7.30101e+11 | 4.11453e+06 | 7.93389 | -(Loss) | false |
| simdjson (reflection) DID NOT CONVERGE | 210.029 | 2.00842 | 13424.2ms | 10018896 | 30 | 2.50444e+13 | 4.54926e+07 | 5.94313 | -(Loss) | false |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 507.995 | 5.1515 | 10503ms | 1834197 | 40 | 1.25864e+12 | 3.44339e+06 | 2.76377 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 434.074 | 5.56677 | 6102.27ms | 1834197 | 40 | 2.01295e+12 | 4.02979e+06 | 4.61726 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 433.797 | 0.101332 | 6999.01ms | 1834197 | 30 | 5.00879e+08 | 4.03236e+06 | 0.329093 | 2(Tie) | true |
| glaze STATISTICAL TIE | 407.191 | 2.42395 | 6896.85ms | 1834197 | 80 | 8.67427e+11 | 4.29584e+06 | 2.22099 | 2(Tie) | true |
| simdjson (ondemand) | 385.872 | 2.42109 | 7146.72ms | 1834197 | 30 | 3.61368e+11 | 4.53318e+06 | 3.40765 | 5(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 656.457 | 1.9295 | 9956.54ms | 1834197 | 160 | 4.22952e+11 | 2.66465e+06 | 1.85322 | 1(Win) | true |
| jsonifier (two-stage) | 529.211 | 1.46767 | 5632.31ms | 1834197 | 80 | 1.88269e+11 | 3.30535e+06 | 4.56973 | 2(Loss) | true |
| glaze DID NOT CONVERGE | 470.101 | 4.11081 | 6632.03ms | 1834197 | 30 | 7.01917e+11 | 3.72096e+06 | 7.00556 | -(Loss) | false |
| simdjson (reflection) | 417.432 | 3.02164 | 6899.37ms | 1834197 | 80 | 1.28261e+12 | 4.19045e+06 | 3.73521 | 4(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 329.609 | 4.31338 | 8088.12ms | 1834197 | 80 | 4.192e+12 | 5.30698e+06 | 8.94575 | -(Loss) | false |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1159.43 | 0.776089 | 9943.36ms | 1834197 | 30 | 4.11289e+09 | 1.50869e+06 | 1.15053 | 1(Win) | true |
| glaze | 682.301 | 2.22572 | 8503.94ms | 1833577 | 160 | 5.20603e+11 | 2.56285e+06 | 0.618619 | 2(Loss) | true |
| simdjson (reflection) | 568.688 | 0.446616 | 9312.24ms | 1922245 | 40 | 8.29084e+09 | 3.22355e+06 | 2.73919 | 3(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1203.22 | 0.319789 | 10132.6ms | 1834197 | 80 | 1.72909e+09 | 1.45379e+06 | 2.57068 | 1(Win) | true |
| glaze | 757.587 | 0.12377 | 7617.13ms | 1833577 | 30 | 2.44842e+08 | 2.30816e+06 | 0.612884 | 2(Loss) | true |
| simdjson (reflection) | 719.346 | 0.699515 | 8075.24ms | 1922245 | 30 | 9.53362e+09 | 2.54842e+06 | 2.41319 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2291.02 | 0.578634 | 6935.55ms | 9930848 | 30 | 1.7165e+10 | 4.13387e+06 | 2.61907 | 1(Win) | true |
| jsonifier (two-stage) | 2164.73 | 0.489512 | 6681.58ms | 9930848 | 80 | 3.6693e+10 | 4.37505e+06 | 2.59304 | 2(Loss) | true |
| simdjson (reflection) | 1944.64 | 0.600445 | 7381.52ms | 9930848 | 40 | 3.42059e+10 | 4.87021e+06 | 1.04162 | 3(Loss) | true |
| simdjson (ondemand) | 1869.45 | 0.554036 | 8524.34ms | 9930848 | 30 | 2.36344e+10 | 5.06609e+06 | 3.6476 | 4(Loss) | true |
| glaze | 1843.33 | 0.362522 | 8018.24ms | 9930848 | 40 | 1.3877e+10 | 5.13786e+06 | 1.09416 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 2513.6 | 0.247985 | 6451.86ms | 9930848 | 80 | 6.98432e+09 | 3.76783e+06 | 0.0247933 | 1(Tie) | true |
| jsonifier STATISTICAL TIE DID NOT CONVERGE | 2430.09 | 1.62955 | 6776.27ms | 9930848 | 40 | 1.61333e+11 | 3.89731e+06 | 8.22667 | -(Tie) | false |
| glaze | 1869.66 | 0.33305 | 8321.9ms | 9930848 | 80 | 2.27696e+10 | 5.06552e+06 | 2.22793 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1792.42 | 0.989627 | 8376.43ms | 9930848 | 40 | 1.0937e+11 | 5.28381e+06 | 2.57945 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1771.02 | 0.905236 | 9154.69ms | 9930848 | 30 | 7.03027e+10 | 5.34766e+06 | 1.876 | 4(Tie) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4089.91 | 6.32124 | 7842.23ms | 9930848 | 40 | 8.57057e+11 | 2.31565e+06 | 1.04474 | 1(Win) | true |
| glaze | 1904.66 | 1.2711 | 7558.19ms | 9930228 | 80 | 3.19546e+11 | 4.97212e+06 | 1.52854 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 214.361 | 2.36712 | 13091.5ms | 10018896 | 30 | 3.33971e+13 | 4.45731e+07 | 12.4882 | -(Loss) | false |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 4239.55 | 3.2929 | 6974.63ms | 9930848 | 160 | 8.65785e+11 | 2.23392e+06 | 12.6501 | -(Win) | false |
| glaze | 2215.12 | 1.83112 | 6789.47ms | 9930228 | 80 | 4.90286e+11 | 4.27526e+06 | 0.318748 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 266.603 | 0.320154 | 12438.9ms | 10018896 | 30 | 3.94956e+11 | 3.58389e+07 | 16.4881 | -(Loss) | false |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| glaze | 986.978 | 0.250636 | 8118.45ms | 642697 | 640 | 1.55047e+09 | 621010 | 0.878358 | 1(Win) | true |
| jsonifier | 822.74 | 1.38084 | 8964.19ms | 642697 | 320 | 3.38629e+10 | 744978 | 0.212969 | 2(Loss) | true |
| jsonifier (two-stage) DID NOT CONVERGE | 724.704 | 0.500979 | 5256.28ms | 642697 | 320 | 5.74487e+09 | 845757 | 5.50669 | -(Loss) | false |
| simdjson (ondemand) | 696.129 | 0.753535 | 5347.45ms | 642697 | 80 | 3.52152e+09 | 880474 | 0.100209 | 4(Loss) | true |
| simdjson (reflection) | 549.739 | 1.66416 | 6814.46ms | 642697 | 160 | 5.50821e+10 | 1.11494e+06 | 0.18561 | 5(Loss) | true |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| glaze | 1127.25 | 0.355777 | 7669.62ms | 642697 | 80 | 2.99377e+08 | 543734 | 0.255354 | 1(Win) | true |
| jsonifier | 882.585 | 1.23367 | 8963.69ms | 642697 | 640 | 4.69762e+10 | 694464 | 3.2546 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 779.606 | 0.414797 | 5294.27ms | 642697 | 320 | 3.40317e+09 | 786197 | 0.299445 | 3(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 747.436 | 3.249 | 5248.65ms | 642697 | 80 | 5.67879e+10 | 820035 | 0.33331 | 3(Tie) | true |
| simdjson (reflection) | 560.637 | 0.444624 | 7438.4ms | 642697 | 320 | 7.56109e+09 | 1.09326e+06 | 1.11019 | 5(Loss) | true |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2034.35 | 0.409608 | 7828.75ms | 642697 | 640 | 9.74714e+08 | 301287 | 1.0629 | 1(Win) | true |
| glaze | 984.435 | 0.444486 | 8343.39ms | 642692 | 160 | 1.22537e+09 | 622610 | 0.206444 | 2(Loss) | true |
| simdjson (reflection) | 686.727 | 2.45639 | 5297.44ms | 643373 | 160 | 7.70679e+10 | 893467 | 1.1933 | 3(Loss) | true |

----
### Mesh Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1986.68 | 2.32459 | 8586.94ms | 642697 | 320 | 1.64588e+10 | 308516 | 2.85775 | 1(Win) | true |
| glaze | 933.537 | 0.929129 | 8005.1ms | 642692 | 160 | 5.95408e+09 | 656555 | 1.0301 | 2(Loss) | true |
| simdjson (reflection) | 674.381 | 4.24262 | 6222.73ms | 643373 | 80 | 1.19199e+11 | 909824 | 3.96829 | 3(Loss) | true |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 1361.25 | 0.896542 | 5504.52ms | 1225964 | 30 | 1.77887e+09 | 858897 | 3.88006 | 1(Win) | true |
| glaze STATISTICAL TIE DID NOT CONVERGE | 1238.19 | 1.48312 | 6523.1ms | 1225964 | 320 | 6.27599e+10 | 944259 | 11.9416 | -(Tie) | false |
| simdjson (ondemand) STATISTICAL TIE | 1226.62 | 1.36434 | 5732.83ms | 1225964 | 320 | 5.41164e+10 | 953166 | 0.576977 | 2(Tie) | true |
| jsonifier STATISTICAL TIE | 1213.08 | 0.393482 | 6449.6ms | 1225964 | 320 | 4.60233e+09 | 963804 | 0.214361 | 2(Tie) | true |
| simdjson (reflection) | 902.579 | 0.978867 | 8971.82ms | 1225964 | 40 | 6.43121e+09 | 1.29537e+06 | 0.159509 | 5(Loss) | true |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1475.25 | 1.01912 | 6153.72ms | 1225964 | 40 | 2.60937e+09 | 792525 | 0.239535 | 1(Tie) | true |
| glaze STATISTICAL TIE | 1441.68 | 0.975493 | 5687.44ms | 1225964 | 80 | 5.00673e+09 | 810976 | 1.00313 | 1(Tie) | true |
| jsonifier | 1348.36 | 0.437537 | 5820.33ms | 1225964 | 160 | 2.30298e+09 | 867102 | 1.83154 | 3(Loss) | true |
| jsonifier (two-stage) | 1284.67 | 0.777038 | 5405.05ms | 1225964 | 320 | 1.60033e+10 | 910095 | 1.46936 | 4(Loss) | true |
| simdjson (reflection) | 999.987 | 1.4299 | 9556.56ms | 1225964 | 30 | 8.38497e+09 | 1.16919e+06 | 1.09649 | 5(Loss) | true |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4018.5 | 0.779292 | 7868.67ms | 1225964 | 640 | 3.2901e+09 | 290947 | 1.50152 | 1(Win) | true |
| glaze | 1411.33 | 0.495185 | 5939.74ms | 1225970 | 40 | 6.7313e+08 | 828422 | 2.7627 | 2(Loss) | true |
| simdjson (reflection) | 200.867 | 0.275456 | 8957.1ms | 1226640 | 80 | 2.05879e+10 | 5.82382e+06 | 0.333237 | 3(Loss) | true |

----
### Mesh Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4188.34 | 0.449804 | 7767.27ms | 1225964 | 160 | 2.52254e+08 | 279149 | 2.56308 | 1(Win) | true |
| glaze | 1377.01 | 1.11389 | 5787.54ms | 1225970 | 320 | 2.86238e+10 | 849071 | 0.492645 | 2(Loss) | true |
| simdjson (reflection) | 192.322 | 1.00544 | 9055.4ms | 1226640 | 80 | 2.99213e+11 | 6.08258e+06 | 2.0824 | 3(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 981.347 | 0.488017 | 9883.16ms | 409725 | 160 | 6.04128e+08 | 398171 | 1.25976 | 1(Win) | true |
| jsonifier (two-stage) | 761.267 | 0.335395 | 6470.07ms | 409725 | 640 | 1.89672e+09 | 513281 | 4.15017 | 2(Loss) | true |
| glaze | 683.521 | 1.19949 | 7654.89ms | 409725 | 160 | 7.52312e+09 | 571664 | 1.03669 | 3(Loss) | true |
| simdjson (reflection) | 584.56 | 1.98207 | 8379.57ms | 409725 | 30 | 5.26607e+09 | 668442 | 1.12181 | 4(Loss) | true |
| simdjson (ondemand) | 537.485 | 0.725419 | 8883.76ms | 409725 | 80 | 2.22494e+09 | 726986 | 1.6688 | 5(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1629.47 | 0.519808 | 8164.58ms | 409725 | 320 | 4.97197e+08 | 239798 | 0.309964 | 1(Win) | true |
| jsonifier (two-stage) | 1115.65 | 1.19815 | 5645.46ms | 409725 | 40 | 7.04388e+08 | 350240 | 1.84443 | 2(Loss) | true |
| glaze | 800.244 | 0.988489 | 7546.57ms | 409725 | 40 | 9.31846e+08 | 488282 | 0.30941 | 3(Loss) | true |
| simdjson (reflection) | 738.282 | 1.4161 | 8212.06ms | 409725 | 320 | 1.79754e+10 | 529262 | 0.175484 | 4(Loss) | true |
| simdjson (ondemand) | 702.933 | 0.387699 | 8413.08ms | 409725 | 160 | 7.43132e+08 | 555877 | 0.34225 | 5(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10756.1 | 0.0759949 | 3800.09ms | 409725 | 2560 | 1.95112e+06 | 36327.7 | 0.0662966 | 1(Win) | true |
| simdjson (reflection) | 7204.94 | 0.723619 | 6158.57ms | 409725 | 640 | 9.85652e+07 | 54232.8 | 2.91578 | 2(Loss) | true |
| glaze | 1785.06 | 1.49041 | 6768.45ms | 409725 | 30 | 3.19309e+08 | 218897 | 1.35743 | 3(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10194.8 | 0.204047 | 4205.71ms | 409725 | 1280 | 7.82882e+06 | 38327.8 | 1.47361 | 1(Win) | true |
| simdjson (reflection) | 5963.61 | 0.823184 | 6583.28ms | 409725 | 2560 | 7.44733e+08 | 65521.4 | 2.3564 | 2(Loss) | true |
| glaze | 1756.17 | 0.70012 | 5604.46ms | 409725 | 30 | 7.2798e+07 | 222498 | 0.772539 | 3(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1398.2 | 1.01996 | 7090.46ms | 785750 | 320 | 9.562e+09 | 535938 | 0.350154 | 1(Win) | true |
| jsonifier (two-stage) DID NOT CONVERGE | 1089.55 | 1.21691 | 9608.16ms | 785750 | 640 | 4.48305e+10 | 687764 | 16.1126 | -(Loss) | false |
| simdjson (ondemand) | 972.904 | 0.580502 | 5466.85ms | 785750 | 320 | 6.39715e+09 | 770219 | 2.64487 | 3(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 875.336 | 1.94733 | 5270.18ms | 785750 | 320 | 8.89297e+10 | 856071 | 14.3304 | -(Loss) | false |
| glaze | 772.858 | 4.4655 | 5741.63ms | 785750 | 30 | 5.62381e+10 | 969583 | 3.98029 | 5(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1785.32 | 2.27682 | 6537.25ms | 785750 | 80 | 7.30605e+09 | 419728 | 2.26653 | 1(Win) | true |
| jsonifier (two-stage) DID NOT CONVERGE | 1666.64 | 0.883471 | 8394.78ms | 785750 | 80 | 1.26229e+09 | 449616 | 7.54669 | -(Loss) | false |
| simdjson (reflection) | 1365.39 | 0.609826 | 8823.76ms | 785750 | 40 | 4.48054e+08 | 548819 | 0.475457 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1150.04 | 1.26931 | 5455.95ms | 785750 | 40 | 2.73615e+09 | 651584 | 1.25109 | 4(Tie) | true |
| glaze STATISTICAL TIE DID NOT CONVERGE | 1045.01 | 5.84515 | 5235.89ms | 785750 | 30 | 5.27035e+10 | 717073 | 11.7876 | -(Tie) | false |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9015.6 | 1.2253 | 9289ms | 785750 | 2560 | 2.65524e+09 | 83117 | 0.176067 | 1(Win) | true |
| glaze | 2137 | 1.32599 | 10090.8ms | 785750 | 160 | 3.45907e+09 | 350654 | 1.89461 | 2(Loss) | true |
| simdjson (reflection) | 279.316 | 1.56237 | 8814.2ms | 785750 | 80 | 1.40552e+11 | 2.6828e+06 | 0.264217 | 3(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11445.5 | 0.401283 | 6803.33ms | 785750 | 2560 | 1.76702e+08 | 65471.1 | 0.325038 | 1(Win) | true |
| glaze | 2251.78 | 1.44214 | 5311.33ms | 785750 | 40 | 9.2128e+08 | 332781 | 0.602156 | 2(Loss) | true |
| simdjson (reflection) | 274.304 | 1.13895 | 8949.28ms | 785750 | 80 | 7.74463e+10 | 2.73182e+06 | 0.951103 | 3(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3311.54 | 0.938366 | 7623.88ms | 264040 | 1280 | 6.5168e+08 | 76039.6 | 1.08638 | 1(Win) | true |
| simdjson (reflection) | 2922.19 | 0.0872215 | 9175.89ms | 264040 | 4890 | 2.76235e+07 | 86171 | 0.328364 | 2(Loss) | true |
| simdjson (ondemand) | 2805.6 | 0.863305 | 5022.93ms | 264040 | 160 | 9.60587e+07 | 89752 | 4.06847 | 3(Loss) | true |
| jsonifier (two-stage) | 2727.33 | 0.750394 | 9390.49ms | 264040 | 4890 | 2.34721e+09 | 92327.7 | 0.659196 | 4(Loss) | true |
| glaze | 2047.19 | 1.32449 | 6846.49ms | 264040 | 40 | 1.06165e+08 | 123002 | 0.433446 | 5(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3950.3 | 0.12479 | 8904.92ms | 264040 | 30 | 189828 | 63744 | 1.64582 | 1(Win) | true |
| jsonifier (two-stage) | 3307.05 | 3.13462 | 7649.85ms | 264040 | 30 | 1.70903e+08 | 76142.9 | 2.32074 | 2(Loss) | true |
| simdjson (reflection) | 3080.99 | 0.0529092 | 8741.86ms | 264040 | 2560 | 4.78698e+06 | 81729.7 | 0.326403 | 3(Loss) | true |
| simdjson (ondemand) | 3017.66 | 0.280179 | 9791.27ms | 264040 | 320 | 1.74912e+07 | 83444.8 | 0.811861 | 4(Loss) | true |
| glaze | 2254.21 | 0.582928 | 6166.59ms | 264040 | 40 | 1.69605e+07 | 111706 | 0.711648 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 4764.69 | 0.0563291 | 9338.79ms | 399947 | 40 | 81331.9 | 80051.2 | 0.0213242 | 1(Win) | true |
| jsonifier | 4165.68 | 0.587331 | 9004.39ms | 399947 | 4890 | 1.41419e+09 | 91562.2 | 1.23405 | 2(Loss) | true |
| simdjson (reflection) | 3836.04 | 0.207535 | 5444.53ms | 399947 | 40 | 1.70326e+06 | 99430.4 | 0.404998 | 3(Loss) | true |
| simdjson (ondemand) | 3241.43 | 0.739319 | 5816.06ms | 399947 | 640 | 4.84367e+08 | 117670 | 3.92967 | 4(Loss) | true |
| glaze | 2996.32 | 0.248895 | 7479.65ms | 399947 | 40 | 4.01534e+06 | 127296 | 0.083724 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 4266.05 | 1.19345 | 8921.37ms | 399947 | 160 | 1.82172e+08 | 89408 | 3.36663 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 4216.5 | 0.575105 | 5017.53ms | 399947 | 640 | 1.73211e+08 | 90458.8 | 2.23274 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 3713.19 | 0.477201 | 5401.03ms | 399947 | 40 | 9.61111e+06 | 102720 | 0.672498 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3708.5 | 0.217038 | 5692.35ms | 399947 | 2560 | 1.27561e+08 | 102850 | 1.57904 | 3(Tie) | true |
| glaze | 3092.83 | 0.25217 | 7265.64ms | 399947 | 30 | 2.90136e+06 | 123324 | 0.0276702 | 5(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1593.7 | 0.962035 | 7989.6ms | 264040 | 640 | 1.47873e+09 | 158002 | 1.29346 | 1(Win) | true |
| jsonifier (two-stage) | 1474.89 | 0.47497 | 9738.22ms | 264040 | 320 | 2.10429e+08 | 170730 | 0.268274 | 2(Loss) | true |
| glaze | 1254.57 | 2.15734 | 5088.59ms | 264040 | 160 | 2.99987e+09 | 200712 | 0.179684 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1091.02 | 0.424307 | 6082.48ms | 264040 | 30 | 2.87711e+07 | 230801 | 0.174074 | 4(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1062.49 | 1.54377 | 7336.04ms | 264040 | 40 | 5.35448e+08 | 236998 | 0.436458 | 4(Tie) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2335.85 | 0.657207 | 7181.14ms | 264040 | 80 | 4.01555e+07 | 107802 | 0.601912 | 1(Win) | true |
| jsonifier (two-stage) | 1684.22 | 2.18479 | 8930.73ms | 264040 | 40 | 4.26799e+08 | 149510 | 1.28043 | 2(Loss) | true |
| glaze | 1466.31 | 0.862593 | 9688.98ms | 264040 | 320 | 7.02179e+08 | 171729 | 1.82078 | 3(Loss) | true |
| simdjson (ondemand) | 1078.54 | 0.616485 | 6057.44ms | 264040 | 1280 | 2.65169e+09 | 233471 | 2.10971 | 4(Loss) | true |
| simdjson (reflection) | 965.51 | 1.55679 | 7973.49ms | 264040 | 640 | 1.05503e+10 | 260803 | 0.0481821 | 5(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14038 | 0.278713 | 2080.09ms | 264040 | 160 | 399911 | 17937.6 | 0.0623997 | 1(Win) | true |
| simdjson (reflection) | 8104.02 | 1.2089 | 2956.9ms | 264040 | 80 | 1.12877e+07 | 31072 | 0.64262 | 2(Loss) | true |
| glaze | 2966.78 | 0.75303 | 10348.8ms | 263923 | 80 | 3.26512e+07 | 84838.4 | 0.978561 | 3(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12208.8 | 1.75299 | 2090.99ms | 264040 | 30 | 3.92169e+06 | 20625.1 | 0.698439 | 1(Win) | true |
| simdjson (reflection) | 8956.87 | 0.404269 | 3079.77ms | 264040 | 4890 | 6.3165e+07 | 28113.4 | 3.60036 | 2(Loss) | true |
| glaze | 3432.48 | 0.945437 | 7104.53ms | 263923 | 640 | 3.07599e+08 | 73328 | 1.08135 | 3(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2015.53 | 0.250242 | 5000.55ms | 399947 | 1280 | 2.8705e+08 | 189240 | 1.21561 | 1(Win) | true |
| jsonifier (two-stage) | 1750.93 | 1.86331 | 5663.34ms | 399947 | 320 | 5.27217e+09 | 217838 | 3.52869 | 2(Loss) | true |
| glaze | 1660.43 | 0.625187 | 6058.04ms | 399947 | 160 | 3.2999e+08 | 229710 | 2.43755 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1373.9 | 0.723924 | 7592.47ms | 399947 | 1280 | 5.16997e+09 | 277617 | 0.285619 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1367.73 | 0.945559 | 7703ms | 399947 | 320 | 2.22501e+09 | 278870 | 0.201214 | 4(Tie) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2554.26 | 0.384986 | 9552.68ms | 399947 | 160 | 5.28789e+07 | 149326 | 0.626429 | 1(Win) | true |
| jsonifier (two-stage) DID NOT CONVERGE | 2121.49 | 1.86303 | 5720.82ms | 399947 | 320 | 3.59014e+09 | 179788 | 15.8712 | -(Loss) | false |
| glaze | 2009.56 | 0.570699 | 5842.66ms | 399947 | 640 | 7.50923e+08 | 189802 | 0.485926 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1557.76 | 1.34567 | 7168.37ms | 399947 | 80 | 8.68509e+08 | 244851 | 0.486409 | 4(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1498.11 | 2.37359 | 7782.1ms | 399947 | 30 | 1.0956e+09 | 254601 | 2.33228 | 4(Tie) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16637.8 | 0.255099 | 3342.86ms | 399947 | 160 | 547205 | 22924.8 | 1.34949 | 1(Win) | true |
| glaze | 2951.61 | 0.511689 | 6891.26ms | 399830 | 2560 | 1.11862e+09 | 129186 | 1.15978 | 2(Loss) | true |
| simdjson (reflection) | 349.61 | 0.416647 | 8073.66ms | 399947 | 320 | 6.61187e+09 | 1.09099e+06 | 2.14639 | 3(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16142.1 | 0.38925 | 2657.13ms | 399947 | 30 | 253783 | 23628.8 | 3.55277 | 1(Win) | true |
| glaze | 3522.59 | 0.543949 | 5762.95ms | 399830 | 640 | 2.21883e+08 | 108246 | 1.32698 | 2(Loss) | true |
| simdjson (reflection) | 349.216 | 2.56569 | 6953.85ms | 399947 | 30 | 2.35584e+10 | 1.09222e+06 | 0.467825 | 3(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 723.57 | 0.472 | 636.599ms | 4630 | 640 | 530965 | 6102.4 | 0.104987 | 1(Win) | true |
| jsonifier (two-stage) | 631.798 | 0.443867 | 754.164ms | 4630 | 80 | 76984.1 | 6988.8 | 0.817439 | 2(Loss) | true |
| simdjson (reflection) | 480.922 | 0.36455 | 900.835ms | 4630 | 4890 | 5.47817e+06 | 9181.34 | 0.290579 | 3(Loss) | true |
| simdjson (ondemand) | 421.07 | 0.541448 | 1107.45ms | 4630 | 80 | 257903 | 10486.4 | 0.0914634 | 4(Loss) | true |
| glaze | 402.679 | 0.838283 | 1133.8ms | 4630 | 30 | 253481 | 10965.3 | 0.618716 | 5(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 918.291 | 0.795026 | 615.215ms | 4630 | 2560 | 3.74114e+06 | 4808.4 | 1.01681 | 1(Win) | true |
| jsonifier (two-stage) | 794.786 | 0.326119 | 809.889ms | 4630 | 1280 | 420168 | 5555.6 | 1.03295 | 2(Loss) | true |
| simdjson (reflection) | 584.929 | 0.53788 | 943.165ms | 4630 | 160 | 263782 | 7548.8 | 0.127334 | 3(Loss) | true |
| glaze | 476.405 | 0.330523 | 1122.95ms | 4630 | 640 | 600612 | 9268.4 | 0.021574 | 4(Loss) | true |
| simdjson (ondemand) | 429.859 | 1.30292 | 1215.59ms | 4630 | 40 | 716485 | 10272 | 2.05452 | 5(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1998.87 | 0.691854 | 230.035ms | 4630 | 1280 | 298972 | 2209 | 0.710176 | 1(Win) | true |
| glaze | 1492.13 | 0.428866 | 328.67ms | 4630 | 320 | 51539.6 | 2959.2 | 0.0810373 | 2(Loss) | true |
| simdjson (reflection) | 768.289 | 0.427017 | 575.772ms | 4630 | 640 | 385462 | 5747.2 | 0.181286 | 3(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2058.71 | 0.677651 | 218.66ms | 4630 | 1280 | 270393 | 2144.8 | 0.355605 | 1(Win) | true |
| glaze | 1576.97 | 0.972424 | 356.688ms | 4630 | 320 | 237234 | 2800 | 1.7406 | 2(Loss) | true |
| simdjson (reflection) | 783.114 | 0.972494 | 562.462ms | 4630 | 80 | 240534 | 5638.4 | 0.227531 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 1762.76 | 0.212327 | 829.51ms | 14795 | 4890 | 1.41241e+06 | 8004.27 | 0.26012 | 1(Win) | true |
| jsonifier | 1687.43 | 0.643212 | 912.413ms | 14795 | 320 | 925629 | 8361.6 | 0.888031 | 2(Loss) | true |
| simdjson (reflection) | 1487.1 | 0.60398 | 1004.11ms | 14795 | 80 | 262714 | 9488 | 1.23251 | 3(Loss) | true |
| simdjson (ondemand) | 1192.74 | 0.119092 | 1293.54ms | 14795 | 2560 | 508097 | 11829.6 | 0.94951 | 4(Loss) | true |
| glaze | 1111.2 | 0.707711 | 1378.31ms | 14795 | 30 | 242257 | 12697.6 | 0.268097 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2145.88 | 0.539651 | 831.516ms | 14795 | 320 | 402897 | 6575.2 | 0.109383 | 1(Win) | true |
| jsonifier (two-stage) | 2002.39 | 0.910475 | 866.699ms | 14795 | 40 | 164638 | 7046.4 | 0.151149 | 2(Loss) | true |
| simdjson (reflection) | 1706.37 | 0.609319 | 1066.25ms | 14795 | 80 | 203079 | 8268.8 | 0.308642 | 3(Loss) | true |
| simdjson (ondemand) | 1329.79 | 0.181068 | 1437.06ms | 14795 | 1280 | 472453 | 10610.4 | 0.300684 | 4(Loss) | true |
| glaze | 1248.46 | 0.195096 | 1302.42ms | 14795 | 1280 | 622279 | 11301.6 | 0.0212314 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5942.39 | 1.64457 | 233.61ms | 14795 | 160 | 243967 | 2374.4 | 0.536193 | 1(Win) | true |
| glaze | 2770.28 | 0.186259 | 524.64ms | 14795 | 2560 | 230386 | 5093.2 | 0.0863151 | 2(Loss) | true |
| simdjson (reflection) | 220.395 | 0.932894 | 6143.95ms | 14795 | 640 | 2.28282e+08 | 64019.6 | 3.20593 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6132.75 | 0.472615 | 258.726ms | 14795 | 2560 | 302674 | 2300.7 | 1.0231 | 1(Win) | true |
| glaze | 2896.3 | 0.794676 | 480.658ms | 14795 | 640 | 959188 | 4871.6 | 0.519974 | 2(Loss) | true |
| simdjson (reflection) | 234.822 | 0.830053 | 6300.06ms | 14795 | 80 | 1.99e+07 | 60086.4 | 0.616225 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1213.38 | 0.572402 | 425.33ms | 5092 | 30 | 15743.7 | 4002.13 | 0 | 1(Win) | true |
| jsonifier (two-stage) | 861.955 | 0.196617 | 561.016ms | 5092 | 4890 | 600008 | 5633.83 | 1.17325 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 815.221 | 0.308915 | 618.795ms | 5092 | 160 | 54178 | 5956.8 | 0.0805153 | 3(Tie) | true |
| glaze STATISTICAL TIE | 806.984 | 0.73723 | 592.812ms | 5092 | 160 | 314900 | 6017.6 | 0.346852 | 3(Tie) | true |
| simdjson (reflection) | 486.078 | 0.421773 | 989.186ms | 5092 | 640 | 1.13633e+06 | 9990.4 | 0.498954 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1765.09 | 0.8903 | 419.144ms | 5092 | 320 | 191985 | 2751.2 | 0.376593 | 1(Win) | true |
| jsonifier (two-stage) | 1147.04 | 0.61651 | 526.108ms | 5092 | 640 | 435994 | 4233.6 | 1.16613 | 2(Loss) | true |
| glaze STATISTICAL TIE | 932.146 | 1.54185 | 613.489ms | 5092 | 80 | 516158 | 5209.6 | 2.77778 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 918.326 | 0.790378 | 705.589ms | 5092 | 160 | 279494 | 5288 | 0.691106 | 3(Tie) | true |
| simdjson (ondemand) | 893.368 | 0.442357 | 634.09ms | 5092 | 4890 | 2.82729e+06 | 5435.73 | 0.365978 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7938.32 | 1.1473 | 65.911ms | 5092 | 4890 | 240869 | 611.73 | 0.300059 | 1(Win) | true |
| simdjson (reflection) | 6656.57 | 0.926976 | 74.391ms | 5092 | 4890 | 223626 | 729.521 | 2.73503 | 2(Loss) | true |
| glaze | 1645.69 | 0.318833 | 325.812ms | 5092 | 1280 | 113297 | 2950.8 | 0.846774 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE DID NOT CONVERGE | 7295.84 | 13.2467 | 93.7132ms | 5092 | 30 | 233218 | 665.6 | 1.26582 | -(Tie) | false |
| simdjson (reflection) STATISTICAL TIE | 6509.42 | 1.77541 | 77.2552ms | 5092 | 4890 | 857825 | 746.012 | 2.0397 | 1(Tie) | true |
| glaze | 1801.49 | 0.565218 | 301.556ms | 5092 | 1280 | 297134 | 2695.6 | 0.751105 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1879.64 | 0.537681 | 597.971ms | 11724 | 640 | 654680 | 5948.4 | 0.661323 | 1(Win) | true |
| jsonifier (two-stage) | 1801.51 | 0.622538 | 857.898ms | 11724 | 160 | 238853 | 6206.4 | 0.129066 | 2(Loss) | true |
| simdjson (ondemand) | 1634.06 | 0.252039 | 699.512ms | 11724 | 1280 | 380682 | 6842.4 | 0.0877655 | 3(Loss) | true |
| glaze | 1377.23 | 0.328908 | 874.308ms | 11724 | 160 | 114080 | 8118.4 | 0.23706 | 4(Loss) | true |
| simdjson (reflection) | 1083.84 | 0.472504 | 1087.43ms | 11724 | 320 | 760299 | 10316 | 0.224389 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 2362.77 | 0.225293 | 591.85ms | 11724 | 2560 | 290966 | 4732.1 | 1.35293 | 1(Win) | true |
| jsonifier | 2298.9 | 0.59201 | 607.895ms | 11724 | 4890 | 4.05396e+06 | 4863.58 | 0.164371 | 2(Loss) | true |
| simdjson (ondemand) | 1960.84 | 0.146287 | 669.711ms | 11724 | 4890 | 340245 | 5702.1 | 0.136623 | 3(Loss) | true |
| simdjson (reflection) | 1746.9 | 0.355983 | 749.537ms | 11724 | 1280 | 664481 | 6400.4 | 0.622563 | 4(Loss) | true |
| glaze | 1395.43 | 0.432933 | 899.48ms | 11724 | 4890 | 5.88417e+06 | 8012.49 | 0.687199 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 15451.7 | 2.47022 | 80.1541ms | 11724 | 640 | 204479 | 723.6 | 0.930997 | 1(Win) | true |
| glaze | 2653.71 | 0.497487 | 468.097ms | 11746 | 640 | 282238 | 4221.2 | 2.98768 | 2(Loss) | true |
| simdjson (reflection) | 286.149 | 0.651549 | 3990.16ms | 11724 | 160 | 1.037e+07 | 39073.6 | 0.0286721 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14789.5 | 7.72666 | 98.903ms | 11724 | 640 | 2.18377e+06 | 756 | 4.25532 | 1(Win) | true |
| glaze | 2522.03 | 0.534848 | 557.433ms | 11746 | 640 | 361176 | 4441.6 | 0.0540054 | 2(Loss) | true |
| simdjson (reflection) | 210.486 | 1.05615 | 4387.65ms | 11724 | 2560 | 8.05742e+08 | 53119.3 | 1.11747 | 3(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1352.33 | 0.906103 | 330.283ms | 4857 | 640 | 616463 | 3425.2 | 3.76489 | 1(Win) | true |
| glaze STATISTICAL TIE | 1133.52 | 0.251676 | 448.783ms | 4857 | 1280 | 135386 | 4086.4 | 0.0587659 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1127.14 | 0.146999 | 420.585ms | 4857 | 4890 | 178450 | 4109.51 | 0.0363233 | 2(Tie) | true |
| simdjson (reflection) | 898.586 | 0.236883 | 556.52ms | 4857 | 4890 | 729111 | 5154.76 | 0.502272 | 4(Loss) | true |
| simdjson (ondemand) | 771.896 | 0.727294 | 695.026ms | 4857 | 320 | 609520 | 6000.8 | 3.92075 | 5(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2193.6 | 0.605908 | 269.415ms | 4857 | 640 | 104765 | 2111.6 | 0.320997 | 1(Win) | true |
| glaze | 1751.35 | 0.287851 | 317.099ms | 4857 | 4890 | 283422 | 2644.81 | 0.503731 | 2(Loss) | true |
| jsonifier (two-stage) | 1492.75 | 0.33169 | 382.627ms | 4857 | 1280 | 135593 | 3103 | 0.0193324 | 3(Loss) | true |
| simdjson (reflection) | 1133.29 | 0.471883 | 517.99ms | 4857 | 640 | 238067 | 4087.2 | 0.214844 | 4(Loss) | true |
| simdjson (ondemand) | 1066.05 | 0.361177 | 543.113ms | 4857 | 1280 | 315231 | 4345 | 0.28915 | 5(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9314.49 | 3.96829 | 57.8278ms | 4857 | 4890 | 1.9043e+06 | 497.289 | 2.30182 | 1(Win) | true |
| simdjson (reflection) | 6861.2 | 1.7322 | 74.3611ms | 4857 | 2560 | 350086 | 675.1 | 0.851509 | 2(Loss) | true |
| glaze | 2268.81 | 0.361418 | 208.241ms | 4857 | 2560 | 139380 | 2041.6 | 1.19956 | 3(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11737.6 | 1.79411 | 43.362ms | 4857 | 4890 | 245121 | 394.627 | 1.23843 | 1(Win) | true |
| simdjson (reflection) | 8327.93 | 2.51314 | 61.504ms | 4857 | 1280 | 250095 | 556.2 | 1.20087 | 2(Loss) | true |
| glaze | 2773.88 | 0.466723 | 179.295ms | 4857 | 4890 | 297022 | 1669.86 | 0.0337504 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1562.98 | 0.261131 | 457.953ms | 7376 | 4890 | 675399 | 4500.57 | 3.21346 | 1(Win) | true |
| jsonifier (two-stage) | 1424.64 | 0.924441 | 503.875ms | 7376 | 160 | 333358 | 4937.6 | 2.40354 | 2(Loss) | true |
| simdjson (reflection) | 1322.24 | 0.771153 | 578.451ms | 7376 | 160 | 269293 | 5320 | 1.45228 | 3(Loss) | true |
| glaze | 1299.18 | 0.352813 | 582.211ms | 7376 | 4890 | 1.78444e+06 | 5414.43 | 0.347057 | 4(Loss) | true |
| simdjson (ondemand) | 1118.43 | 0.66688 | 639.739ms | 7376 | 4890 | 8.60255e+06 | 6289.43 | 0.847146 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 2075.51 | 0.714015 | 421.62ms | 7376 | 1280 | 749583 | 3389.2 | 0.900585 | 1(Tie) | true |
| glaze STATISTICAL TIE | 2030.69 | 1.18297 | 425.001ms | 7376 | 160 | 268674 | 3464 | 0.230415 | 1(Tie) | true |
| jsonifier (two-stage) | 1834.33 | 0.928816 | 482.661ms | 7376 | 640 | 811942 | 3834.8 | 0.673436 | 3(Loss) | true |
| simdjson (reflection) | 1509.38 | 0.464978 | 541.968ms | 7376 | 1280 | 601065 | 4660.4 | 0.717497 | 4(Loss) | true |
| simdjson (ondemand) | 1416.15 | 0.589253 | 544.604ms | 7376 | 640 | 548286 | 4967.2 | 0.814696 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11342 | 2.30528 | 66.4031ms | 7376 | 1280 | 261649 | 620.2 | 3.45579 | 1(Win) | true |
| glaze | 2188.92 | 0.447768 | 334.062ms | 7376 | 1280 | 265033 | 3213.6 | 0.544689 | 2(Loss) | true |
| simdjson (reflection) | 305.491 | 0.263995 | 2427.78ms | 7376 | 4890 | 1.80695e+07 | 23026.2 | 0.197734 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12525.5 | 7.0412 | 68.567ms | 7376 | 160 | 250188 | 561.6 | 0.285714 | 1(Win) | true |
| glaze | 2424.95 | 1.09617 | 303.59ms | 7376 | 320 | 323548 | 2900.8 | 0.110193 | 2(Loss) | true |
| simdjson (reflection) | 310.83 | 0.144323 | 2333.03ms | 7376 | 2560 | 2.73092e+06 | 22630.7 | 1.56285 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1489.8 | 0.590227 | 342.168ms | 4390 | 2560 | 704293 | 2810.2 | 2.42 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 854.74 | 1.11318 | 563.478ms | 4390 | 30 | 89189.2 | 4898.13 | 0.525394 | 2(Tie) | true |
| glaze STATISTICAL TIE | 848.217 | 0.264915 | 492.323ms | 4390 | 2560 | 437691 | 4935.8 | 0.0971542 | 2(Tie) | true |
| jsonifier (two-stage) | 756.529 | 0.340858 | 563.17ms | 4390 | 1280 | 455443 | 5534 | 0.446139 | 4(Loss) | true |
| simdjson (ondemand) | 677.286 | 0.146041 | 622.326ms | 4390 | 4890 | 398513 | 6181.48 | 0.205613 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1993.05 | 0.247401 | 260.08ms | 4390 | 4890 | 132070 | 2100.61 | 1.27343 | 1(Win) | true |
| jsonifier (two-stage) | 1214.5 | 0.334878 | 410.991ms | 4390 | 2560 | 341150 | 3447.2 | 0.22576 | 2(Loss) | true |
| glaze | 1048.86 | 0.1373 | 457.133ms | 4390 | 4890 | 146875 | 3991.61 | 0.351733 | 3(Loss) | true |
| simdjson (reflection) | 918.85 | 0.225829 | 499.631ms | 4390 | 4890 | 517736 | 4556.38 | 0.753625 | 4(Loss) | true |
| simdjson (ondemand) | 756.901 | 0.277402 | 607.752ms | 4390 | 4890 | 1.15127e+06 | 5531.28 | 0.387943 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8747.66 | 3.24068 | 72.2209ms | 4390 | 1280 | 307912 | 478.6 | 2.35244 | 1(Win) | true |
| simdjson (reflection) | 7025.73 | 1.63855 | 64.032ms | 4390 | 2560 | 244064 | 595.9 | 0.760906 | 2(Loss) | true |
| glaze | 1285.19 | 2.85486 | 281.645ms | 4390 | 640 | 5.53534e+06 | 3257.6 | 1.49976 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9780.01 | 1.66128 | 46.2789ms | 4390 | 4890 | 247312 | 428.08 | 0.792546 | 1(Win) | true |
| simdjson (reflection) | 7462.09 | 1.30951 | 58.475ms | 4390 | 4890 | 263960 | 561.054 | 0.349415 | 2(Loss) | true |
| glaze | 1730.38 | 0.313879 | 245.593ms | 4390 | 4890 | 282021 | 2419.49 | 0.0170282 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2539.59 | 1.74454 | 757.848ms | 11521 | 40 | 227864 | 4326.4 | 0.595238 | 1(Win) | true |
| simdjson (reflection) | 1966.51 | 0.283258 | 624.728ms | 11521 | 1280 | 320599 | 5587.2 | 0.366458 | 2(Loss) | true |
| jsonifier (two-stage) | 1913.09 | 0.573979 | 626.532ms | 11521 | 320 | 347736 | 5743.2 | 1.11268 | 3(Loss) | true |
| simdjson (ondemand) | 1525.33 | 0.551481 | 739.831ms | 11521 | 320 | 504966 | 7203.2 | 1.89584 | 4(Loss) | true |
| glaze | 1504.49 | 0.195997 | 747.615ms | 11521 | 2560 | 524495 | 7303 | 0.371068 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2995.12 | 0.284418 | 431.377ms | 11521 | 2560 | 278681 | 3668.4 | 0.212176 | 1(Win) | true |
| jsonifier (two-stage) | 2266.77 | 0.466887 | 643.635ms | 11521 | 2560 | 1.31107e+06 | 4847.1 | 0.817422 | 2(Loss) | true |
| simdjson (ondemand) | 1803.32 | 0.609065 | 672.064ms | 11521 | 80 | 110167 | 6092.8 | 0.210526 | 3(Loss) | true |
| glaze | 1670.84 | 0.262249 | 717.382ms | 11521 | 4890 | 1.45428e+06 | 6575.9 | 0.176063 | 4(Loss) | true |
| simdjson (reflection) | 698.723 | 3.96337 | 712.955ms | 11521 | 40 | 1.55367e+07 | 15724.8 | 3.87542 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 17976.6 | 1.62952 | 64.513ms | 11521 | 2560 | 253939 | 611.2 | 0.130719 | 1(Win) | true |
| glaze | 2519.56 | 0.524876 | 454.093ms | 11521 | 640 | 335294 | 4360.8 | 0.565487 | 2(Loss) | true |
| simdjson (reflection) | 282.766 | 0.190738 | 4121.03ms | 11521 | 640 | 3.51544e+06 | 38856.4 | 0.0894804 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 18813.8 | 2.37724 | 60.288ms | 11521 | 1280 | 246708 | 584 | 0.205903 | 1(Win) | true |
| glaze | 2940.29 | 0.38162 | 421.212ms | 11521 | 1280 | 260299 | 3736.8 | 1.49726 | 2(Loss) | true |
| simdjson (reflection) | 296.949 | 0.161609 | 3818.03ms | 11521 | 30 | 107268 | 37000.5 | 0 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2499.27 | 1.31772 | 185.591ms | 4669 | 320 | 176366 | 1781.6 | 0.0449236 | 1(Win) | true |
| jsonifier (two-stage) | 1381.86 | 1.04889 | 330.836ms | 4669 | 4890 | 5.58585e+06 | 3222.25 | 3.04359 | 2(Loss) | true |
| glaze | 1211.23 | 0.286982 | 378.995ms | 4669 | 2560 | 284935 | 3676.2 | 0.125286 | 3(Loss) | true |
| simdjson (reflection) | 1142.42 | 1.233 | 433.358ms | 4669 | 40 | 92380.6 | 3897.6 | 0.921909 | 4(Loss) | true |
| simdjson (ondemand) | 1017.9 | 1.30526 | 466.774ms | 4669 | 80 | 260806 | 4374.4 | 0.811209 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2831.79 | 1.57681 | 172.45ms | 4669 | 640 | 393427 | 1572.4 | 1.00206 | 1(Win) | true |
| jsonifier (two-stage) | 1483.32 | 0.43318 | 332.535ms | 4669 | 4890 | 826845 | 3001.85 | 0.443307 | 2(Loss) | true |
| glaze | 1403.41 | 0.209134 | 337.06ms | 4669 | 4890 | 215297 | 3172.78 | 0.236221 | 3(Loss) | true |
| simdjson (reflection) | 1123.97 | 0.890248 | 417.749ms | 4669 | 80 | 99506.9 | 3961.6 | 1.64204 | 4(Loss) | true |
| simdjson (ondemand) | 1048.58 | 0.875641 | 423.822ms | 4669 | 320 | 442430 | 4246.4 | 0.226586 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12165.9 | 3.69863 | 46.4172ms | 4669 | 1280 | 234560 | 366 | 0 | 1(Win) | true |
| simdjson (reflection) | 7362.28 | 2.27947 | 64.438ms | 4669 | 1280 | 243277 | 604.8 | 0.1321 | 2(Loss) | true |
| glaze | 1516.3 | 0.3161 | 307.743ms | 4669 | 4890 | 421344 | 2936.57 | 0.684566 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 13165.9 | 3.29536 | 41.954ms | 4669 | 2560 | 317975 | 338.2 | 5 | -(Win) | false |
| simdjson (reflection) | 6771.15 | 2.03327 | 70.1609ms | 4669 | 1280 | 228835 | 657.6 | 2.17526 | 2(Loss) | true |
| glaze | 1903.52 | 2.34223 | 244.149ms | 4669 | 80 | 240150 | 2339.2 | 0.679348 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2986.16 | 0.332536 | 301.401ms | 9249 | 1280 | 123495 | 2953.8 | 0.00677048 | 1(Win) | true |
| jsonifier (two-stage) | 2489.43 | 0.803625 | 365.598ms | 9249 | 320 | 259447 | 3543.2 | 0.0225836 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1895.75 | 1.64694 | 480.897ms | 9249 | 40 | 234879 | 4652.8 | 0.319927 | 3(Tie) | true |
| glaze STATISTICAL TIE | 1837.61 | 0.983693 | 482.361ms | 9249 | 80 | 178357 | 4800 | 0.536193 | 3(Tie) | true |
| simdjson (ondemand) | 1776.04 | 1.25047 | 510.9ms | 9249 | 30 | 115705 | 4966.4 | 1.21739 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3246.66 | 0.357384 | 291.294ms | 9249 | 2560 | 241338 | 2716.8 | 0.0441501 | 1(Win) | true |
| jsonifier (two-stage) | 2623.91 | 1.19101 | 357.924ms | 9249 | 160 | 256474 | 3361.6 | 0.520833 | 2(Loss) | true |
| glaze | 2211.77 | 0.315532 | 416.421ms | 9249 | 640 | 101339 | 3988 | 0.564858 | 3(Loss) | true |
| simdjson (ondemand) | 2042.6 | 0.184457 | 459.599ms | 9249 | 4890 | 310256 | 4318.29 | 0.176022 | 4(Loss) | true |
| simdjson (reflection) | 1873.98 | 0.609259 | 537.105ms | 9249 | 4890 | 4.02134e+06 | 4706.84 | 1.00242 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14563.6 | 1.97747 | 64.705ms | 9249 | 4890 | 701426 | 605.657 | 2.58422 | 1(Win) | true |
| glaze | 1874.32 | 0.607824 | 473.351ms | 9249 | 4890 | 4.001e+06 | 4706 | 0.695463 | 2(Loss) | true |
| simdjson (reflection) | 227.407 | 2.15734 | 3622.83ms | 9249 | 2560 | 1.7925e+09 | 38787.4 | 2.95207 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 13694.4 | 13.5163 | 95.9962ms | 9249 | 2560 | 1.94028e+07 | 644.1 | 0.295858 | -(Win) | false |
| glaze | 1813.43 | 4.93302 | 564.807ms | 9249 | 80 | 4.60577e+06 | 4864 | 4.16141 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 258.712 | 0.597064 | 3712.01ms | 9249 | 4890 | 2.02631e+08 | 34094 | 7.87083 | -(Loss) | false |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 448.985 | 0.683668 | 1382.36ms | 4604 | 40 | 178796 | 9779.2 | 0.0873362 | 1(Tie) | true |
| jsonifier STATISTICAL TIE DID NOT CONVERGE | 437.951 | 5.0221 | 1248.87ms | 4604 | 160 | 4.05613e+07 | 10025.6 | 5.48822 | -(Tie) | false |
| simdjson (reflection) | 378.931 | 0.554207 | 1044.13ms | 4604 | 2560 | 1.05568e+07 | 11587.1 | 1.07027 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 333.145 | 0.268413 | 1460.75ms | 4604 | 1280 | 1.60185e+06 | 13179.6 | 0.696203 | 4(Tie) | true |
| glaze STATISTICAL TIE DID NOT CONVERGE | 327.392 | 1.50084 | 1642.14ms | 4604 | 80 | 3.24112e+06 | 13411.2 | 10.5634 | -(Tie) | false |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 593.212 | 1.37324 | 1112.08ms | 4604 | 2560 | 2.64476e+07 | 7401.6 | 1.43625 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 494.896 | 0.896566 | 1276.66ms | 4604 | 160 | 1.01234e+06 | 8872 | 1.37112 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 494.673 | 2.09015 | 1151.2ms | 4604 | 640 | 2.20278e+07 | 8876 | 2.51296 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 356.204 | 1.84946 | 1391.69ms | 4604 | 40 | 2.07884e+06 | 12326.4 | 0.872905 | 4(Tie) | true |
| glaze STATISTICAL TIE | 356.204 | 1.62334 | 1434.23ms | 4604 | 40 | 1.6016e+06 | 12326.4 | 0.310559 | 4(Tie) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1695.98 | 0.749165 | 280.333ms | 4604 | 2560 | 962997 | 2588.9 | 0.350269 | 1(Win) | true |
| glaze | 879.128 | 0.196323 | 547.751ms | 4604 | 640 | 61530.4 | 4994.4 | 0.778767 | 2(Loss) | true |
| simdjson (reflection) | 687.466 | 1.34724 | 740.256ms | 4918 | 40 | 337931 | 6822.4 | 0.313676 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1775.03 | 0.564937 | 302.165ms | 4604 | 1280 | 249959 | 2473.6 | 2.74132 | 1(Win) | true |
| glaze | 878.161 | 0.291717 | 529.441ms | 4604 | 2560 | 544611 | 4999.9 | 1.05086 | 2(Loss) | true |
| simdjson (reflection) | 691.704 | 0.442314 | 699.77ms | 4918 | 1280 | 1.15135e+06 | 6780.6 | 1.7646 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2008.27 | 0.387127 | 1210.22ms | 24579 | 2560 | 5.22674e+06 | 11671.9 | 1.48243 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 1909.57 | 0.620056 | 1358.12ms | 24579 | 40 | 231729 | 12275.2 | 1.16034 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1905.22 | 0.548676 | 1433.4ms | 24579 | 320 | 1.4582e+06 | 12303.2 | 0.690947 | 2(Tie) | true |
| simdjson (ondemand) | 1619.53 | 0.541283 | 1666.37ms | 24579 | 80 | 491012 | 14473.6 | 0.505939 | 4(Loss) | true |
| glaze | 1482.88 | 0.197334 | 1735.56ms | 24579 | 4890 | 4.75807e+06 | 15807.3 | 0.0281316 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2412.17 | 0.213562 | 1179.35ms | 24579 | 4890 | 2.10605e+06 | 9717.53 | 1.86891 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 2066.61 | 0.865159 | 1517.18ms | 24579 | 160 | 1.54071e+06 | 11342.4 | 0.89667 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 2052.8 | 0.568499 | 1266.69ms | 24579 | 4890 | 2.06065e+07 | 11418.8 | 0.111519 | 2(Tie) | true |
| glaze | 1726.81 | 0.417644 | 1639.03ms | 24579 | 80 | 257125 | 13574.4 | 0.426136 | 4(Loss) | true |
| simdjson (ondemand) | 1627.51 | 0.520221 | 1632.76ms | 24579 | 4890 | 2.74515e+07 | 14402.6 | 0.333629 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6161.87 | 0.337679 | 361.475ms | 24579 | 2560 | 422428 | 3804.1 | 0.665866 | 1(Win) | true |
| glaze | 2689.1 | 0.315571 | 1016.15ms | 24579 | 2560 | 1.93708e+06 | 8716.8 | 1.14765 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 237.224 | 0.825071 | 6403.28ms | 24893 | 80 | 5.45395e+07 | 100074 | 5.2161 | -(Loss) | false |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7803.74 | 0.699866 | 319.209ms | 24579 | 30 | 13257.9 | 3003.73 | 1.44092 | 1(Win) | true |
| glaze | 2725.5 | 0.543176 | 803.573ms | 24579 | 640 | 1.39668e+06 | 8600.4 | 0.0139548 | 2(Loss) | true |
| simdjson (reflection) | 269.193 | 0.488806 | 9729.24ms | 24893 | 80 | 1.48659e+07 | 88188.8 | 0.408355 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 617.784 | 0.452211 | 773.929ms | 4604 | 160 | 165272 | 7107.2 | 0.403587 | 1(Win) | true |
| jsonifier (two-stage) | 497.769 | 0.628902 | 915.838ms | 4604 | 320 | 984763 | 8820.8 | 0.738207 | 2(Loss) | true |
| simdjson (reflection) | 422.9 | 0.798788 | 1205.06ms | 4604 | 640 | 4.40188e+06 | 10382.4 | 0.253632 | 3(Loss) | true |
| glaze | 372.701 | 0.212907 | 1269.79ms | 4604 | 1280 | 805265 | 11780.8 | 0.491333 | 4(Loss) | true |
| simdjson (ondemand) | 341.999 | 0.338567 | 1374.11ms | 4604 | 80 | 151148 | 12838.4 | 0.298211 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 832.584 | 1.5717 | 781.731ms | 4604 | 30 | 206099 | 5273.6 | 1.90476 | 1(Win) | true |
| jsonifier (two-stage) | 621.211 | 0.339723 | 887.887ms | 4604 | 1280 | 737994 | 7068 | 0.323625 | 2(Loss) | true |
| simdjson (reflection) | 540.409 | 0.487817 | 1055.46ms | 4604 | 80 | 125669 | 8124.8 | 0.587314 | 3(Loss) | true |
| glaze | 441.03 | 0.299533 | 1443.52ms | 4604 | 640 | 569119 | 9955.6 | 0.204491 | 4(Loss) | true |
| simdjson (ondemand) | 378.912 | 0.537477 | 1355.76ms | 4604 | 2560 | 9.93012e+06 | 11587.7 | 2.79527 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1653.35 | 0.318111 | 270.456ms | 4604 | 4890 | 348986 | 2655.65 | 0.00552159 | 1(Win) | true |
| simdjson (reflection) | 1365.92 | 0.345696 | 348.201ms | 4918 | 2560 | 360706 | 3433.7 | 0.0378457 | 2(Loss) | true |
| glaze | 866.395 | 0.218101 | 539.144ms | 4604 | 1280 | 156373 | 5067.8 | 0.479816 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1684.26 | 0.320072 | 266.132ms | 4604 | 4890 | 340452 | 2606.91 | 0.465536 | 1(Win) | true |
| simdjson (reflection) | 1390.59 | 1.73846 | 408.039ms | 4918 | 80 | 275044 | 3372.8 | 0 | 2(Loss) | true |
| glaze | 919.214 | 0.410233 | 486.557ms | 4604 | 1280 | 491484 | 4776.6 | 0.857264 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2270.3 | 0.45679 | 1054.92ms | 24579 | 160 | 355891 | 10324.8 | 1.78082 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1940.94 | 2.116 | 1471.24ms | 24579 | 80 | 5.22426e+06 | 12076.8 | 0.15873 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1856.03 | 1.4459 | 1665.64ms | 24579 | 30 | 1.00037e+06 | 12629.3 | 0.271003 | 2(Tie) | true |
| glaze | 1412.78 | 0.248526 | 1717.21ms | 24579 | 640 | 1.08818e+06 | 16591.6 | 0.0747925 | 4(Loss) | true |
| simdjson (ondemand) | 1347.31 | 0.874295 | 2000.26ms | 24579 | 4890 | 1.13141e+08 | 17397.9 | 0.377303 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2738.7 | 0.227725 | 1039.76ms | 24579 | 4890 | 1.85767e+06 | 8558.93 | 0.136105 | 1(Win) | true |
| jsonifier (two-stage) | 2592.78 | 0.182919 | 1126.1ms | 24579 | 4890 | 1.33728e+06 | 9040.62 | 1.27279 | 2(Loss) | true |
| simdjson (reflection) | 2123.49 | 0.542389 | 1339.89ms | 24579 | 1280 | 4.58838e+06 | 11038.6 | 0.993596 | 3(Loss) | true |
| simdjson (ondemand) | 1713.18 | 0.353207 | 1633.69ms | 24579 | 640 | 1.49473e+06 | 13682.4 | 0.575514 | 4(Loss) | true |
| glaze | 1594.15 | 0.377248 | 1677.97ms | 24579 | 320 | 984632 | 14704 | 0.0652458 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6594.32 | 0.511576 | 372.511ms | 24579 | 4890 | 1.61703e+06 | 3554.63 | 0.348098 | 1(Win) | true |
| glaze | 2752.77 | 0.581261 | 1027.48ms | 24579 | 160 | 391969 | 8515.2 | 0.037594 | 2(Loss) | true |
| simdjson (reflection) | 247.589 | 0.36277 | 9601.56ms | 24893 | 1280 | 1.54869e+08 | 95883.8 | 0.715738 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7039.17 | 0.732876 | 366.541ms | 24579 | 4890 | 2.91243e+06 | 3329.99 | 0.988335 | 1(Win) | true |
| glaze | 2955.51 | 0.301262 | 807.896ms | 24579 | 4890 | 2.79166e+06 | 7931.08 | 0.927425 | 2(Loss) | true |
| simdjson (reflection) | 278.951 | 0.601566 | 5015.35ms | 24893 | 80 | 2.09679e+07 | 85104 | 0.0864077 | 3(Loss) | true |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 774.856 | 0.633605 | 151.398ms | 1181 | 4890 | 414767 | 1453.55 | 0.216907 | 1(Win) | true |
| jsonifier (two-stage) | 642.551 | 0.425617 | 192.058ms | 1181 | 4890 | 272165 | 1752.84 | 0.406767 | 2(Loss) | true |
| glaze | 515.784 | 0.666603 | 233.146ms | 1181 | 4890 | 1.03611e+06 | 2183.64 | 0.162612 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 447.793 | 1.15486 | 267.525ms | 1181 | 320 | 269992 | 2515.2 | 0.319081 | 4(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 442.168 | 3.1567 | 246.672ms | 1181 | 40 | 258615 | 2547.2 | 0.830565 | 4(Tie) | true |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 966.96 | 0.533574 | 138.478ms | 1181 | 4890 | 188878 | 1164.77 | 1.04744 | 1(Win) | true |
| glaze | 880.602 | 0.998601 | 160.662ms | 1181 | 1280 | 208802 | 1279 | 0.803909 | 2(Loss) | true |
| jsonifier (two-stage) | 764.156 | 0.747401 | 219.579ms | 1181 | 2560 | 310659 | 1473.9 | 4.24246 | 3(Loss) | true |
| simdjson (ondemand) | 590.794 | 3.70841 | 258.27ms | 1181 | 320 | 1.59939e+06 | 1906.4 | 3.75606 | 4(Loss) | true |
| simdjson (reflection) | 549.249 | 0.437944 | 228.192ms | 1181 | 2560 | 206461 | 2050.6 | 0.283646 | 5(Loss) | true |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1994.84 | 2.47019 | 59.456ms | 1181 | 1280 | 248973 | 564.6 | 2.52072 | 1(Win) | true |
| simdjson (reflection) | 991.48 | 0.468927 | 145.343ms | 1187 | 4890 | 140169 | 1141.74 | 2.21478 | 2(Loss) | true |
| glaze | 910.059 | 1.97037 | 144.105ms | 1181 | 320 | 190285 | 1237.6 | 0.0645995 | 3(Loss) | true |

----
### Mesh Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2149.82 | 1.99643 | 55.7942ms | 1181 | 2560 | 280057 | 523.9 | 1.92607 | 1(Win) | true |
| simdjson (reflection) | 1051.27 | 2.06641 | 116.141ms | 1187 | 160 | 79217.7 | 1076.8 | 0.14881 | 2(Loss) | true |
| glaze | 968.102 | 0.679064 | 120.583ms | 1181 | 2560 | 159779 | 1163.4 | 0.62273 | 3(Loss) | true |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 1232.59 | 1.18616 | 204.258ms | 2496 | 160 | 83957.7 | 1931.2 | 0.247934 | 1(Win) | true |
| jsonifier | 1190.47 | 0.326677 | 214.724ms | 2496 | 4890 | 208641 | 1999.52 | 3.06286 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 928.962 | 1.54997 | 262.396ms | 2496 | 320 | 504765 | 2562.4 | 1.20296 | 3(Tie) | true |
| glaze STATISTICAL TIE | 928.788 | 0.309096 | 274.874ms | 2496 | 4890 | 306867 | 2562.88 | 1.57535 | 3(Tie) | true |
| simdjson (ondemand) | 893.13 | 0.859286 | 288.701ms | 2496 | 640 | 335672 | 2665.2 | 0.492832 | 5(Loss) | true |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 1434.13 | 0.586826 | 190.575ms | 2496 | 2560 | 242868 | 1659.8 | 1.34327 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1420.19 | 0.450424 | 188.829ms | 2496 | 4890 | 278707 | 1676.09 | 0.860107 | 1(Tie) | true |
| glaze | 1373.08 | 1.57575 | 208.513ms | 2496 | 320 | 238795 | 1733.6 | 1.58946 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1192.09 | 0.82117 | 237.243ms | 2496 | 40 | 10754.6 | 1996.8 | 0 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1159.21 | 1.26723 | 304.215ms | 2496 | 4890 | 3.31119e+06 | 2053.44 | 2.57415 | 4(Tie) | true |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3764.03 | 2.14646 | 62.0329ms | 2496 | 1280 | 235851 | 632.4 | 3.71498 | 1(Win) | true |
| glaze | 1266.35 | 1.37472 | 198.302ms | 2507 | 160 | 107784 | 1888 | 0.682594 | 2(Loss) | true |
| simdjson (reflection) | 185.923 | 0.307919 | 1383.38ms | 2502 | 1280 | 1.99891e+06 | 12833.8 | 0.336179 | 3(Loss) | true |

----
### Mesh Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4318.53 | 2.53727 | 57.7869ms | 2496 | 1280 | 250358 | 551.2 | 0.577201 | 1(Win) | true |
| glaze | 1505.96 | 0.918691 | 171.781ms | 2507 | 1280 | 272289 | 1587.6 | 1.1457 | 2(Loss) | true |
| simdjson (reflection) | 193.509 | 0.704458 | 1674.28ms | 2502 | 30 | 226363 | 12330.7 | 0.0691563 | 3(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1419.1 | 0.756243 | 361.523ms | 4926 | 640 | 401111 | 3310.4 | 0.337187 | 1(Win) | true |
| jsonifier (two-stage) | 949.472 | 0.226224 | 521.906ms | 4926 | 2560 | 320732 | 4947.8 | 0.32635 | 2(Loss) | true |
| simdjson (reflection) | 736.586 | 0.942497 | 650.68ms | 4926 | 1280 | 4.625e+06 | 6377.8 | 0.191655 | 3(Loss) | true |
| simdjson (ondemand) | 621.655 | 0.140945 | 876.08ms | 4926 | 4890 | 554753 | 7556.92 | 0.689136 | 4(Loss) | true |
| glaze | 456.807 | 2.4316 | 844.707ms | 4926 | 640 | 4.0021e+07 | 10284 | 3.61086 | 5(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1885.39 | 0.320062 | 346.284ms | 4926 | 4890 | 311001 | 2491.68 | 0.432328 | 1(Win) | true |
| jsonifier (two-stage) | 1208.41 | 0.340987 | 500.564ms | 4926 | 1280 | 224931 | 3887.6 | 0.0617729 | 2(Loss) | true |
| glaze STATISTICAL TIE | 949.178 | 0.757647 | 610.008ms | 4926 | 30 | 42184.1 | 4949.33 | 0.172712 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 945.916 | 0.481736 | 609.403ms | 4926 | 80 | 45792.2 | 4966.4 | 0.258398 | 3(Tie) | true |
| simdjson (ondemand) | 755.176 | 0.430901 | 789.006ms | 4926 | 320 | 229931 | 6220.8 | 0.0772201 | 5(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9830.09 | 2.07646 | 51.489ms | 4926 | 2560 | 252094 | 477.9 | 0.271285 | 1(Win) | true |
| simdjson (reflection) | 7671.13 | 3.1692 | 69.9981ms | 4926 | 640 | 241074 | 612.4 | 0.459318 | 2(Loss) | true |
| glaze | 1641.49 | 0.294681 | 302.141ms | 4926 | 4890 | 347797 | 2861.91 | 0.71078 | 3(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10085.4 | 3.01084 | 64.1329ms | 4926 | 1280 | 251758 | 465.8 | 0.555081 | 1(Win) | true |
| simdjson (reflection) | 8008.52 | 2.50789 | 63.551ms | 4926 | 1280 | 277019 | 586.6 | 0.170184 | 2(Loss) | true |
| glaze | 1821.21 | 0.888121 | 255.747ms | 4926 | 2560 | 1.34356e+06 | 2579.5 | 0.135501 | 3(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1890.21 | 2.40215 | 528.105ms | 9463 | 40 | 526136 | 4774.4 | 0.810811 | 1(Win) | true |
| simdjson (reflection) | 1455.91 | 0.179909 | 643.438ms | 9463 | 2560 | 318372 | 6198.6 | 0.219887 | 2(Loss) | true |
| jsonifier (two-stage) | 1428.13 | 0.496797 | 643.421ms | 9463 | 320 | 315379 | 6319.2 | 0.598574 | 3(Loss) | true |
| simdjson (ondemand) | 1181.02 | 0.117149 | 818.018ms | 9463 | 4890 | 391857 | 7641.36 | 1.48184 | 4(Loss) | true |
| glaze | 1102.5 | 0.929241 | 918.376ms | 9463 | 80 | 462858 | 8185.6 | 0.708661 | 5(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2238.8 | 0.401352 | 467.881ms | 9463 | 1280 | 335032 | 4031 | 0.193127 | 1(Win) | true |
| jsonifier (two-stage) | 1845.64 | 0.248125 | 646.939ms | 9463 | 4890 | 719806 | 4889.7 | 0.0389685 | 2(Loss) | true |
| simdjson (reflection) | 1514.25 | 0.386352 | 669.881ms | 9463 | 1280 | 678639 | 5959.8 | 0.84264 | 3(Loss) | true |
| simdjson (ondemand) | 1458.97 | 0.522688 | 807.491ms | 9463 | 160 | 167251 | 6185.6 | 0.887265 | 4(Loss) | true |
| glaze | 1371.44 | 0.352574 | 763.138ms | 9463 | 1280 | 688993 | 6580.4 | 0.109536 | 5(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13236.5 | 1.92608 | 76.2931ms | 9463 | 1280 | 220736 | 681.8 | 0.501179 | 1(Win) | true |
| glaze | 2373.9 | 1.2045 | 398.795ms | 9463 | 80 | 167739 | 3801.6 | 0 | 2(Loss) | true |
| simdjson (reflection) | 307.949 | 0.27622 | 3165.94ms | 9463 | 40 | 262102 | 29305.6 | 1.00173 | 3(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14698.1 | 3.15882 | 67.0482ms | 9463 | 640 | 240750 | 614 | 0.854139 | 1(Win) | true |
| glaze | 2363.46 | 0.888969 | 434.873ms | 9463 | 320 | 368711 | 3818.4 | 2.24936 | 2(Loss) | true |
| simdjson (reflection) | 269.901 | 0.721272 | 3342.48ms | 9463 | 160 | 9.3061e+06 | 33436.8 | 0.0765038 | 3(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 3201.23 | 1.77323 | 86.8541ms | 2821 | 640 | 142129 | 840.4 | 0.71908 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 3166.57 | 1.69295 | 85.877ms | 2821 | 640 | 132403 | 849.6 | 1.52964 | 1(Tie) | true |
| simdjson (reflection) | 2918.52 | 0.514229 | 95.8418ms | 2821 | 4890 | 109876 | 921.809 | 0.447794 | 3(Loss) | true |
| simdjson (ondemand) | 2646.75 | 0.431565 | 110.713ms | 2821 | 4890 | 94098.4 | 1016.46 | 2.88895 | 4(Loss) | true |
| glaze | 2162.63 | 1.95435 | 162.077ms | 2821 | 320 | 189145 | 1244 | 2.70806 | 5(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 3751.31 | 0.958354 | 78.8649ms | 2821 | 4890 | 230994 | 717.166 | 0.51387 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 3693.08 | 0.896084 | 78.8081ms | 2821 | 4890 | 208370 | 728.474 | 1.20512 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3094.25 | 0.580408 | 92.63ms | 2821 | 4890 | 124530 | 869.458 | 0.451378 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 3057.18 | 2.10553 | 97.3581ms | 2821 | 320 | 109860 | 880 | 2.80374 | 3(Tie) | true |
| glaze | 2050.07 | 0.569973 | 137.097ms | 2821 | 4890 | 273580 | 1312.3 | 2.40351 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 4015.93 | 0.810118 | 106.456ms | 4147 | 1280 | 81471 | 984.8 | 0.736498 | 1(Win) | true |
| simdjson (reflection) | 3571.33 | 0.803775 | 116.409ms | 4147 | 1280 | 101412 | 1107.4 | 1.51192 | 2(Loss) | true |
| jsonifier | 3466.78 | 0.819421 | 119.668ms | 4147 | 4890 | 427306 | 1140.8 | 1.10757 | 3(Loss) | true |
| simdjson (ondemand) | 3340.56 | 0.695345 | 134.291ms | 4147 | 2560 | 173489 | 1183.9 | 0.671769 | 4(Loss) | true |
| glaze DID NOT CONVERGE | 2666.59 | 0.733883 | 173.998ms | 4147 | 4890 | 579320 | 1483.12 | 5.68836 | -(Loss) | false |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4274.09 | 0.508691 | 100.427ms | 4147 | 4890 | 108342 | 925.317 | 0.0559011 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 3854.67 | 0.973829 | 103.344ms | 4147 | 640 | 63891 | 1026 | 3.49887 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3810.1 | 0.556711 | 111.528ms | 4147 | 1280 | 42743 | 1038 | 1.06748 | 2(Tie) | true |
| simdjson (reflection) | 3659.57 | 0.384209 | 114.081ms | 4147 | 4890 | 84304.6 | 1080.7 | 0.45519 | 4(Loss) | true |
| glaze | 3004.83 | 0.527758 | 143.571ms | 4147 | 4890 | 235942 | 1316.18 | 0.493305 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2107.08 | 2.86097 | 134.19ms | 2821 | 160 | 213497 | 1276.8 | 0 | 1(Win) | true |
| glaze STATISTICAL TIE | 1553.06 | 4.89287 | 266.437ms | 2821 | 30 | 215516 | 1732.27 | 0 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1510.06 | 1.4687 | 182.966ms | 2821 | 320 | 219098 | 1781.6 | 0.669045 | 2(Tie) | true |
| simdjson (reflection) | 1261.09 | 3.11614 | 225.506ms | 2821 | 30 | 132579 | 2133.33 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 1132.47 | 0.333758 | 242.986ms | 2821 | 4890 | 307416 | 2375.62 | 0.245471 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2547.43 | 0.398655 | 128.977ms | 2821 | 4890 | 86677.4 | 1056.09 | 0.791336 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1828.28 | 0.706197 | 170.458ms | 2821 | 2560 | 276447 | 1471.5 | 0.773867 | 2(Tie) | true |
| glaze STATISTICAL TIE | 1791.63 | 1.89501 | 169.351ms | 2821 | 320 | 259108 | 1501.6 | 0.160085 | 2(Tie) | true |
| simdjson (reflection) | 1330.26 | 0.996913 | 234.915ms | 2821 | 80 | 32519.1 | 2022.4 | 1.28205 | 4(Loss) | true |
| simdjson (ondemand) | 1272.86 | 0.891465 | 239.683ms | 2821 | 320 | 113607 | 2113.6 | 0.685976 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10710.6 | 2.48721 | 29.3251ms | 2821 | 4890 | 190861 | 251.184 | 4.74644 | 1(Win) | true |
| simdjson (reflection) | 7649.46 | 2.69424 | 38.8698ms | 2821 | 2560 | 229856 | 351.7 | 1.17952 | 2(Loss) | true |
| glaze | 2840.67 | 1.24848 | 94.07ms | 2819 | 640 | 89349.8 | 946.4 | 0.339271 | 3(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11289.6 | 3.76318 | 25.6271ms | 2821 | 2560 | 205873 | 238.3 | 4.3345 | 1(Win) | true |
| simdjson (reflection) | 7677.84 | 2.94546 | 38.1601ms | 2821 | 2560 | 272693 | 350.4 | 1.38889 | 2(Loss) | true |
| glaze | 3498.25 | 1.09735 | 83.6109ms | 2819 | 2560 | 182061 | 768.5 | 1.54598 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2310.1 | 1.51855 | 192.744ms | 4147 | 320 | 216279 | 1712 | 0.742115 | 1(Win) | true |
| glaze | 2048.74 | 0.81281 | 219.271ms | 4147 | 320 | 78781.2 | 1930.4 | 1.75081 | 2(Loss) | true |
| jsonifier (two-stage) | 1919.1 | 1.08194 | 210.176ms | 4147 | 1280 | 636340 | 2060.8 | 0.605351 | 3(Loss) | true |
| simdjson (ondemand) | 1675.8 | 1.16166 | 277.45ms | 4147 | 320 | 240508 | 2360 | 0.337838 | 4(Loss) | true |
| simdjson (reflection) | 1471.31 | 2.00462 | 283.934ms | 4147 | 80 | 232279 | 2688 | 2.32558 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 2618.44 | 3.78515 | 224.213ms | 4147 | 80 | 261480 | 1510.4 | 0.425532 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 2512 | 0.897096 | 183.675ms | 4147 | 1280 | 255339 | 1574.4 | 0.025413 | 1(Tie) | true |
| glaze | 2260.97 | 0.713424 | 200.808ms | 4147 | 1280 | 199335 | 1749.2 | 0.928863 | 3(Loss) | true |
| simdjson (reflection) | 1823.2 | 0.703582 | 245.497ms | 4147 | 640 | 149076 | 2169.2 | 0.463134 | 4(Loss) | true |
| simdjson (ondemand) | 1658.68 | 0.344232 | 259.31ms | 4147 | 4890 | 329425 | 2384.36 | 1.23381 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 11770.5 | 3.94227 | 42.367ms | 4147 | 1280 | 224585 | 336 | 6.04027 | -(Win) | false |
| glaze | 2826.79 | 2.79208 | 193.881ms | 4145 | 160 | 243916 | 1398.4 | 0.907029 | 2(Loss) | true |
| simdjson (reflection) | 359.588 | 1.13051 | 1175.94ms | 4147 | 80 | 1.23679e+06 | 10998.4 | 0.43834 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13925.7 | 4.04984 | 30.6911ms | 4147 | 2560 | 338651 | 284 | 3.72881 | 1(Win) | true |
| glaze | 3572.83 | 1.6764 | 131.604ms | 4145 | 320 | 110085 | 1106.4 | 1.63585 | 2(Loss) | true |
| simdjson (reflection) | 332.539 | 0.337571 | 1189.32ms | 4147 | 1280 | 2.06311e+06 | 11893 | 0.112545 | 3(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1783.62 | 5.07678 | 6317.64ms | 466906 | 80 | 1.28506e+10 | 249648 | 0.376708 | 1(Win) | true |
| glaze | 1372.31 | 1.72076 | 8582.67ms | 466906 | 30 | 9.35225e+08 | 324471 | 3.90774 | 2(Loss) | true |
| simdjson (ondemand) | 769.684 | 0.587361 | 7885.9ms | 466906 | 80 | 9.23707e+08 | 578518 | 0.11768 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2017.7 | 0.286143 | 6021.13ms | 466906 | 320 | 1.27603e+08 | 220685 | 1.0098 | 1(Win) | true |
| glaze DID NOT CONVERGE | 1441.5 | 0.575103 | 8666.74ms | 466906 | 30 | 9.46768e+07 | 308898 | 5.69002 | -(Loss) | false |
| simdjson (ondemand) | 808.01 | 0.237569 | 7335.85ms | 466906 | 640 | 1.09694e+09 | 551078 | 0.0294609 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2868.45 | 0.321971 | 6088.7ms | 699405 | 320 | 1.79369e+08 | 232531 | 0.171039 | 1(Win) | true |
| glaze | 2030.07 | 0.146987 | 8644.84ms | 699405 | 640 | 1.4927e+08 | 328562 | 1.08429 | 2(Loss) | true |
| simdjson (ondemand) | 662.179 | 0.209611 | 7165.72ms | 767297 | 30 | 1.60962e+08 | 1.10507e+06 | 0.157778 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2939.04 | 0.170961 | 5947.72ms | 699405 | 1280 | 1.92688e+08 | 226947 | 1.83988 | 1(Win) | true |
| glaze | 2016.73 | 0.987955 | 8855.77ms | 699405 | 30 | 3.20299e+08 | 330735 | 2.97159 | 2(Loss) | true |
| simdjson (ondemand) | 662.893 | 0.133274 | 7288.88ms | 767297 | 80 | 1.73149e+08 | 1.10388e+06 | 0.194894 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1995.24 | 0.257105 | 8280.9ms | 631514 | 160 | 9.6365e+07 | 301848 | 1.18479 | 1(Win) | true |
| glaze | 1764.82 | 0.0953479 | 8874.81ms | 631514 | 1280 | 1.35519e+08 | 341258 | 0.606395 | 2(Loss) | true |
