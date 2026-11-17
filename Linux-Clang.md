# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-43-generic using the Clang 24.0.0 compiler).  

Latest Results: (Nov 17, 2026)
#### Using the following commits:
----
| Jsonifier: [79b3e67](https://github.com/nihilai-collective/Jsonifier/commit/79b3e67)  
| Glaze: [a53ddd59](https://github.com/stephenberry/glaze/commit/a53ddd59)  
| simdjson: [36c5b3cfc](https://github.com/simdjson/simdjson/commit/36c5b3cfc)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `AVX2` |
| **simdjson (ondemand)** | `haswell` |
| **Glaze** | utf8: `AVX2`, escape: `AVX2`, float: `SSE4.1`, struct-skip: `AVX2` |

> **Adaptive Sampling & Convergence (Intel(R) Core(TM) i9-14900KF-AVX2):**  
> Iterations scale geometrically (100 → 200 → 400 ...) up to a maximum of 100000.  
> Scores evaluate a trailing window of `max(iterations/10, 30)` (cap: 100000) over at most 5s.  
> Canonical epochs are chosen by minimum (RSE + epoch-over-epoch mean shift).  
> Converged: RSE ≤ 5% and mean shift ≤ 2.5%. Tie detection: Welch's t-test with Bessel-corrected variance.

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

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2045.35 | 0.430147 | 783.434ms | 905 | 160 | 527.125 | 421.969 | 0.0133286 | 2.76147 | 13.5039 | 2.2895 | 0.00121547 | 0.000103591 | 0 | 1(Win) | true |
| Glaze | 1585.58 | 0.103655 | 770.087ms | 905 | 4890 | 1556.73 | 544.329 | 0.0238519 | 3.4918 | 17.5934 | 2.2895 | 0.00112282 | 0.000115468 | 1.58176e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 633.101 | 0.0987574 | 854.851ms | 905 | 4890 | 8863.37 | 1363.25 | 0.0111538 | 8.33069 | 42.2243 | 5.0663 | 0.00118519 | 0.000133998 | 1.288e-05 | 3(Loss) | true |
| simdjson (ondemand) | 287.495 | 0.092232 | 1024.82ms | 905 | 1280 | 9813.2 | 3002.06 | 0.184301 | 18.0634 | 88.9459 | 9.47735 | 0.0230741 | 0.000152797 | 5.17956e-06 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2212.02 | 0.132106 | 754.348ms | 905 | 4890 | 1299.19 | 390.176 | 0.0182468 | 2.56468 | 12.842 | 2.17127 | 0.00111311 | 0.000147556 | 1.51397e-05 | 1(Win) | true |
| Glaze | 1645.81 | 0.0825688 | 766.742ms | 905 | 4890 | 916.804 | 524.406 | 0.0568845 | 3.39313 | 16.9249 | 2.17127 | 0.00114226 | 9.8973e-05 | 1.22021e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 642.509 | 0.207272 | 851.701ms | 905 | 640 | 4961.36 | 1343.29 | 0.169422 | 8.11372 | 41.6022 | 4.94807 | 0.00116195 | 0.000117403 | 2.24448e-05 | 3(Loss) | true |
| simdjson (ondemand) | 290.057 | 0.235426 | 1019.2ms | 905 | 1280 | 62813.2 | 2975.54 | 0.235252 | 17.8128 | 88.3271 | 9.35912 | 0.020821 | 0.000132079 | 1.46754e-05 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2197.35 | 0.222492 | 755.126ms | 905 | 4890 | 3734.54 | 392.78 | 0.0421326 | 2.58924 | 9.3105 | 0.950277 | 0.00348078 | 0.000192523 | 0.000123151 | 1(Win) | true |
| Glaze | 221.043 | 0.144062 | 1121.15ms | 905 | 80 | 2531.24 | 3904.55 | 0.10809 | 23.5519 | 112.617 | 22.8608 | 0.0787155 | 8.28729e-05 | 0 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4259.48 | 0.221572 | 743.597ms | 905 | 4890 | 985.646 | 202.625 | 0.114803 | 1.44764 | 5.79779 | 0.272929 | 0.0022165 | 7.41168e-05 | 2.21446e-05 | 1(Win) | true |
| Glaze | 902.859 | 0.25114 | 826.922ms | 905 | 640 | 3688.65 | 955.936 | 0.0341732 | 5.87234 | 24.0597 | 3.14917 | 0.00121547 | 8.6326e-05 | 1.72652e-05 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1292.24 | 0.191909 | 878.669ms | 1811 | 320 | 2105.19 | 1336.52 | 0.0378639 | 4.10939 | 20.1242 | 4.12314 | 0.000607399 | 0.000141496 | 4.48647e-05 | 1(Win) | true |
| Glaze | 920.488 | 0.0617161 | 914.023ms | 1811 | 4890 | 6557.02 | 1876.29 | 0.0396037 | 5.66849 | 30.0745 | 4.68526 | 0.000581089 | 0.000123196 | 2.86818e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 736.037 | 0.158342 | 962.67ms | 1811 | 640 | 8835.08 | 2346.49 | 0.223772 | 7.12019 | 34.1005 | 5.59028 | 0.00159529 | 8.02388e-05 | 6.03948e-06 | 3(Loss) | true |
| simdjson (ondemand) | 359.891 | 0.0736554 | 1245ms | 1811 | 2560 | 31984.8 | 4798.96 | 0.146456 | 14.167 | 71.2479 | 9.26671 | 0.000635655 | 0.000200166 | 7.41993e-05 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1390.06 | 0.0992853 | 843.085ms | 1811 | 2560 | 3895.67 | 1242.47 | 0.109718 | 3.81516 | 19.2093 | 3.92159 | 0.000870764 | 8.73568e-05 | 2.11382e-05 | 1(Win) | true |
| Glaze | 974.849 | 0.217573 | 898.759ms | 1811 | 320 | 4754.7 | 1771.66 | 0.0208095 | 5.30839 | 29.0337 | 4.45334 | 0.00111644 | 5.52181e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 782.47 | 0.071742 | 949.998ms | 1811 | 4890 | 12261.9 | 2207.25 | 0.26272 | 6.68971 | 33.0939 | 5.37217 | 0.00125963 | 0.000173898 | 7.45275e-05 | 3(Loss) | true |
| simdjson (ondemand) | 370.141 | 0.100611 | 1200.18ms | 1811 | 30 | 661.168 | 4666.07 | 0.131985 | 13.7832 | 70.2253 | 9.04362 | 0.000717835 | 5.52181e-05 | 0 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 335.723 | 0.0504423 | 1244.1ms | 1811 | 4890 | 32928.6 | 5144.44 | 0.0163073 | 15.2728 | 64.0276 | 11.3992 | 0.0181285 | 0.00010016 | 2.04386e-05 | 1(Win) | true |
| Glaze | 300.781 | 0.124294 | 1304.11ms | 1798 | 1280 | 64267 | 5700.85 | 0.495797 | 16.9886 | 71.2742 | 12.1413 | 0.0206379 | 0.000176846 | 8.64676e-05 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 897.276 | 0.19121 | 919.928ms | 1811 | 640 | 8669.32 | 1924.83 | 0.0861346 | 5.86613 | 19.6096 | 1.14025 | 0.000574613 | 9.83573e-05 | 1.63929e-05 | 1(Win) | true |
| Glaze | 614.634 | 0.128766 | 1020.93ms | 1798 | 1280 | 16518.1 | 2789.8 | 0.0648986 | 8.39799 | 26.4321 | 2.17242 | 0.00128789 | 0.000109931 | 2.25945e-05 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3141.23 | 0.105134 | 867.779ms | 3862 | 4890 | 7430.52 | 1172.5 | 0.287781 | 1.6895 | 8.62869 | 1.02745 | 0.000274925 | 8.86939e-05 | 3.76486e-05 | 1(Win) | true |
| Glaze | 1712.09 | 0.109561 | 937.87ms | 3862 | 2560 | 14220.8 | 2151.22 | 0.110361 | 3.04229 | 15.6911 | 1.98628 | 0.000277544 | 4.06606e-05 | 6.57448e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1677.84 | 0.111478 | 946.565ms | 3862 | 2560 | 15330 | 2195.14 | 0.485904 | 3.08599 | 14.4516 | 1.73278 | 0.00027451 | 9.94263e-05 | 4.75385e-05 | 3(Loss) | true |
| simdjson (ondemand) | 788.936 | 0.0844798 | 1193.13ms | 3862 | 1280 | 19909.3 | 4668.42 | 0.0421727 | 6.56501 | 28.2848 | 3.49948 | 0.0137053 | 0.000100741 | 4.18744e-05 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3444.96 | 0.182713 | 830.152ms | 3862 | 640 | 2442.18 | 1069.12 | 0.0169502 | 1.52537 | 8.13827 | 0.92232 | 0.000264193 | 4.20766e-05 | 6.47333e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1763 | 0.132705 | 930.415ms | 3862 | 30 | 230.576 | 2089.1 | 0.0303069 | 2.92393 | 13.9612 | 1.62765 | 0.000837217 | 1.72622e-05 | 0 | 2(Loss) | true |
| Glaze | 1743.88 | 0.107257 | 923.762ms | 3862 | 80 | 410.519 | 2112.01 | 0.0041428 | 3.0125 | 15.2165 | 1.88011 | 0.00413646 | 9.06266e-05 | 4.855e-05 | 3(Loss) | true |
| simdjson (ondemand) | 802.382 | 0.0607632 | 1183.41ms | 3862 | 2560 | 19915.1 | 4590.2 | 0.0638997 | 6.4358 | 27.7962 | 3.39203 | 0.0158734 | 5.80577e-05 | 1.24409e-05 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 934.881 | 0.0752055 | 1128.99ms | 3862 | 2560 | 22472.5 | 3939.63 | 0.189982 | 5.51928 | 26.4037 | 5.40963 | 0.00714939 | 0.000154854 | 8.44567e-05 | 1(Win) | true |
| Glaze | 882.093 | 0.184121 | 1146.14ms | 3862 | 320 | 18912.6 | 4175.4 | 0.258802 | 5.78433 | 29.5873 | 5.69575 | 0.00796786 | 1.942e-05 | 0 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5154.16 | 0.240609 | 816.494ms | 3862 | 640 | 1891.96 | 714.586 | 0.0391551 | 1.05768 | 5.36665 | 0.628949 | 0.000270666 | 3.07483e-05 | 1.21375e-06 | 1(Win) | true |
| Glaze | 2208.23 | 0.0539204 | 918.663ms | 3862 | 4890 | 3955.06 | 1667.9 | 0.229787 | 2.38372 | 8.65251 | 1.04868 | 0.00528695 | 9.13415e-05 | 4.75505e-05 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1846.42 | 0.0497411 | 1223.94ms | 9578 | 4890 | 29609.3 | 4947.03 | 0.151086 | 2.77816 | 14.0799 | 2.70854 | 0.00123568 | 3.89227e-05 | 1.3387e-05 | 1(Win) | true |
| simdjson (ondemand) | 1421.08 | 0.0431934 | 1381.04ms | 9578 | 4890 | 37692.8 | 6427.73 | 0.182362 | 3.59271 | 17.5818 | 2.96628 | 0.0039105 | 2.40625e-05 | 6.02096e-06 | 2(Loss) | true |
| Glaze | 1416.51 | 0.0356216 | 1381.59ms | 9578 | 4890 | 25801.7 | 6448.47 | 0.320544 | 3.62322 | 17.8633 | 3.53947 | 0.00133003 | 2.10733e-05 | 2.90372e-06 | 3(Loss) | true |
| Jsonifier (two-stage) | 1368.21 | 0.0670554 | 1398.7ms | 9578 | 4890 | 97998.5 | 6676.08 | 0.196422 | 3.75827 | 18.2534 | 3.09835 | 0.00165916 | 3.36917e-05 | 1.11452e-05 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2870 | 0.0881526 | 1179.88ms | 9578 | 1280 | 10075.5 | 3182.68 | 0.0530422 | 1.7842 | 9.85467 | 1.77427 | 0.000206773 | 1.77816e-05 | 2.52858e-06 | 1(Win) | true |
| Glaze | 2015.47 | 0.239163 | 1331.68ms | 9578 | 80 | 9398.87 | 4532.09 | 0.00965246 | 2.58358 | 13.4357 | 2.53978 | 0.000606859 | 2.21863e-05 | 6.52537e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1971.77 | 0.0876637 | 1336.95ms | 9578 | 2560 | 42220.1 | 4632.54 | 0.0999792 | 2.57933 | 13.3494 | 2.03248 | 0.00241015 | 1.92906e-05 | 2.44701e-06 | 3(Loss) | true |
| Jsonifier (two-stage) | 1819.97 | 0.100084 | 1363.69ms | 9578 | 1280 | 32296.5 | 5018.92 | 0.274669 | 2.80606 | 14.0902 | 2.17739 | 0.000306203 | 1.95761e-05 | 5.54657e-06 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4301.98 | 0.111613 | 942.597ms | 9578 | 640 | 3594.37 | 2123.28 | 0.505227 | 1.20709 | 5.06786 | 1.0023 | 0.001547 | 1.41927e-05 | 9.78806e-07 | 1(Win) | true |
| Glaze | 1919.12 | 0.326122 | 1200.21ms | 9578 | 30 | 7228.17 | 4759.63 | 0.305808 | 2.65809 | 13.3883 | 2.61067 | 0.0018097 | 1.04406e-05 | 0 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11624.5 | 0.228888 | 827.86ms | 9578 | 2560 | 8281.12 | 785.78 | 0.396876 | 0.463765 | 1.88557 | 0.21539 | 0.000822768 | 1.99024e-05 | 8.48298e-06 | 1(Win) | true |
| Glaze | 4540.91 | 0.0517092 | 950.799ms | 9578 | 4890 | 5290.63 | 2011.55 | 0.0567063 | 1.14695 | 4.99374 | 0.731781 | 0.000216071 | 3.25601e-05 | 1.01844e-05 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3267.94 | 0.17405 | 834.713ms | 3873 | 2560 | 9906.8 | 1130.25 | 0.247306 | 1.61907 | 7.96282 | 1.03305 | 0.000269393 | 6.14228e-05 | 2.18863e-05 | 1(Win) | true |
| Glaze | 1869.16 | 0.0730863 | 925.515ms | 3873 | 4890 | 10199.7 | 1976.07 | 0.0705899 | 2.78199 | 14.7798 | 1.89078 | 0.000814141 | 4.27162e-05 | 8.44819e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1625.5 | 0.19095 | 952.146ms | 3873 | 4890 | 92059.8 | 2272.27 | 0.0461438 | 3.2081 | 14.2523 | 1.68319 | 0.000473943 | 8.96564e-05 | 3.83337e-05 | 3(Loss) | true |
| simdjson (ondemand) | 738.619 | 0.122263 | 1233.31ms | 3873 | 640 | 23923.5 | 5000.66 | 0.10207 | 7.01566 | 27.8567 | 3.5528 | 0.0146741 | 3.18713e-05 | 4.03434e-07 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3593.23 | 0.121749 | 821.173ms | 3873 | 2560 | 4009.56 | 1027.93 | 0.0283949 | 1.48925 | 7.51975 | 0.938807 | 0.000356636 | 3.89314e-05 | 5.3455e-06 | 1(Win) | true |
| Glaze | 1976.32 | 0.10043 | 909.583ms | 3873 | 2560 | 9018.82 | 1868.92 | 0.193122 | 2.64638 | 14.3085 | 1.78492 | 0.00133708 | 5.5573e-05 | 1.60365e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1676.31 | 0.143238 | 943.996ms | 3873 | 320 | 3187.5 | 2203.39 | 0.14345 | 3.0729 | 13.8136 | 1.58895 | 0.000798799 | 5.56739e-05 | 2.58198e-05 | 3(Loss) | true |
| simdjson (ondemand) | 733.601 | 0.0468631 | 1228.33ms | 3873 | 4890 | 27223.7 | 5034.86 | 0.0290526 | 7.00801 | 27.4216 | 3.45624 | 0.0178619 | 7.41857e-05 | 2.67174e-05 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 953.959 | 0.103248 | 1114.82ms | 3873 | 1280 | 20455.3 | 3871.84 | 0.148324 | 5.36429 | 25.5391 | 5.18487 | 0.00621349 | 7.92748e-05 | 2.54163e-05 | 1(Win) | true |
| Glaze | 885.344 | 0.0789346 | 1149.13ms | 3873 | 2560 | 27761.7 | 4171.92 | 0.0954229 | 5.84667 | 29.5293 | 5.73974 | 0.0066849 | 0.000125266 | 6.64658e-05 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4502.96 | 0.124777 | 825.893ms | 3873 | 2560 | 2681.67 | 820.256 | 0.145275 | 1.18671 | 5.12962 | 0.557708 | 0.00662066 | 6.47512e-05 | 1.89614e-05 | 1(Win) | true |
| Glaze | 2226.07 | 0.0690954 | 917.748ms | 3873 | 2560 | 3364.76 | 1659.24 | 0.03556 | 2.36848 | 8.51175 | 1.0457 | 0.00427731 | 4.61932e-05 | 6.65666e-06 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1715.67 | 0.0216738 | 6024.89ms | 94653 | 4890 | 635887 | 52614 | 0.013878 | 2.94674 | 13.5427 | 2.52189 | 0.00849822 | 1.3823e-05 | 7.73896e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1494.72 | 0.0331508 | 6802.07ms | 94653 | 2560 | 1.02607e+06 | 60391.4 | 0.0585341 | 3.37235 | 15.1324 | 2.84929 | 0.0113402 | 2.22853e-05 | 1.55048e-05 | 2(Loss) | true |
| Glaze | 1407.52 | 0.0219355 | 7172.96ms | 94653 | 4890 | 967756 | 64132.9 | 0.218569 | 3.59532 | 15.8336 | 3.11426 | 0.0154384 | 2.19594e-05 | 1.55103e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1221.65 | 0.0448766 | 8214.5ms | 94653 | 1280 | 1.40742e+06 | 73890.2 | 0.0638803 | 4.13314 | 16.8629 | 3.14903 | 0.0112726 | 3.97174e-05 | 1.10766e-05 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2795.4 | 0.0488602 | 5244.32ms | 94653 | 2560 | 637281 | 32291.7 | 0.0187066 | 1.80585 | 9.4442 | 1.60825 | 0.00537997 | 1.83648e-05 | 1.21455e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2295.58 | 0.0285108 | 5939.55ms | 94653 | 4890 | 614627 | 39322.6 | 0.122692 | 2.18489 | 11.0724 | 1.94418 | 0.00601021 | 1.14702e-05 | 6.44265e-06 | 2(Loss) | true |
| Glaze | 2066.94 | 0.0614326 | 6359.03ms | 94653 | 640 | 460672 | 43672.4 | 0.0411883 | 2.44638 | 11.9412 | 2.23915 | 0.00925165 | 3.48312e-06 | 5.94276e-07 | 3(Loss) | true |
| simdjson (ondemand) | 1683.26 | 0.0390513 | 7403.72ms | 94653 | 2560 | 1.12274e+06 | 53627 | 0.0536173 | 2.99969 | 12.9087 | 2.25941 | 0.00712914 | 1.2715e-05 | 5.71165e-06 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16396.7 | 0.204823 | 1287.45ms | 94653 | 160 | 20343.9 | 5505.26 | 0.0675035 | 0.310797 | 1.3301 | 0.183903 | 0.00020595 | 1.22157e-05 | 8.51796e-06 | 1(Win) | true |
| Glaze | 5704.39 | 0.13439 | 2369.92ms | 94653 | 320 | 144722 | 15824.3 | 0.250498 | 0.886696 | 4.37627 | 0.666677 | 7.98971e-05 | 5.67864e-06 | 2.41012e-06 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16776.1 | 0.0453065 | 1277.57ms | 94653 | 2560 | 15214.1 | 5380.75 | 0.00167696 | 0.303509 | 1.32453 | 0.182678 | 0.000142399 | 4.81198e-06 | 2.1006e-06 | 1(Win) | true |
| Glaze | 6318.86 | 0.0689355 | 2177.05ms | 94653 | 1280 | 124133 | 14285.5 | 0.0156159 | 0.797669 | 4.32645 | 0.655341 | 5.71826e-05 | 6.28942e-06 | 3.49962e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1902.35 | 0.0525376 | 7009.02ms | 124597 | 1280 | 1.37843e+06 | 62462.2 | 0.0688505 | 2.64963 | 11.8992 | 2.17477 | 0.00878639 | 5.12465e-05 | 3.84113e-05 | 1(Win) | true |
| Jsonifier | 1756.29 | 0.0356388 | 7518.96ms | 124597 | 1280 | 744179 | 67656.6 | 0.0110208 | 2.8691 | 12.8326 | 2.56221 | 0.00980082 | 3.60976e-05 | 2.68992e-05 | 2(Loss) | true |
| Glaze | 1626.16 | 0.0615373 | 8100.65ms | 124597 | 320 | 647015 | 73070.7 | 0.0505716 | 3.1081 | 13.9579 | 2.77552 | 0.0145376 | 9.38024e-06 | 5.1165e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1573.1 | 0.0256719 | 8323.85ms | 124597 | 2560 | 962630 | 75535.7 | 0.00481894 | 3.21438 | 13.0986 | 2.40356 | 0.00893263 | 1.73027e-05 | 9.28932e-06 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2868.11 | 0.0344517 | 6179.98ms | 124597 | 4890 | 996213 | 41429.7 | 0.177035 | 1.7566 | 8.82096 | 1.49136 | 0.00483658 | 1.03467e-05 | 6.38131e-06 | 1(Win) | true |
| Jsonifier | 2504.81 | 0.0701003 | 6804.71ms | 124597 | 640 | 707762 | 47438.8 | 0.00998755 | 2.00614 | 9.71164 | 1.87017 | 0.00791567 | 5.09141e-06 | 1.85598e-06 | 2(Loss) | true |
| Glaze | 2227.21 | 0.0603504 | 7476.28ms | 124597 | 640 | 663489 | 53351.5 | 0.04909 | 2.26684 | 11.0249 | 2.11922 | 0.0103865 | 1.60768e-05 | 9.49311e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2131.9 | 0.0293497 | 7584.51ms | 124597 | 4890 | 1.30857e+06 | 55736.6 | 0.0914502 | 2.36014 | 10.112 | 1.73242 | 0.00571676 | 1.38902e-05 | 3.98339e-06 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19040.6 | 0.0404838 | 1425.06ms | 136037 | 4890 | 37207.2 | 6813.61 | 0.00760588 | 0.266248 | 1.27855 | 0.214993 | 0.000175758 | 3.98214e-06 | 1.73627e-06 | 1(Win) | true |
| Glaze | 5312.8 | 0.0936838 | 3197.77ms | 136076 | 640 | 335139 | 24426.3 | 0.0577196 | 0.952023 | 4.09562 | 0.69046 | 0.00144909 | 1.14596e-05 | 3.8811e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18980.9 | 0.0468032 | 1427.23ms | 136037 | 4890 | 50042.5 | 6835.02 | 0.0235318 | 0.266577 | 1.27457 | 0.214104 | 0.000172943 | 4.00769e-06 | 1.68515e-06 | 1(Win) | true |
| Glaze | 5795.65 | 0.122313 | 2979.79ms | 136076 | 320 | 240023 | 22391.3 | 0.278335 | 0.869832 | 4.06236 | 0.682685 | 0.00140923 | 4.98343e-06 | 1.69942e-06 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 950.027 | 0.127701 | 7040.75ms | 2251027 | 80 | 6.66144e+08 | 2.25967e+06 | 0.121557 | 5.29738 | 29.7605 | 5.98432 | 0.00737916 | 0.0645824 | 0.000132106 | 1(Win) | true |
| Jsonifier (two-stage) | 865.639 | 0.0918624 | 7780.32ms | 2251027 | 30 | 1.55699e+08 | 2.47996e+06 | 0.190106 | 5.81706 | 32.2818 | 6.3719 | 0.0101852 | 0.10257 | 0.000117694 | 2(Loss) | true |
| Glaze | 830.778 | 0.0699154 | 8084.35ms | 2251027 | 160 | 5.22225e+08 | 2.58402e+06 | 0.219185 | 6.05397 | 31.7479 | 5.90113 | 0.0101364 | 0.0635369 | 0.000534395 | 3(Loss) | true |
| simdjson (ondemand) | 795.104 | 0.173373 | 8379.64ms | 2251027 | 40 | 8.76466e+08 | 2.69996e+06 | 0.228246 | 6.31254 | 31.2886 | 5.42074 | 0.0148189 | 0.108696 | 0.00201238 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1138.58 | 0.104605 | 7067.04ms | 2251027 | 80 | 3.11192e+08 | 1.88546e+06 | 0.0121461 | 4.43531 | 24.8216 | 4.78686 | 0.0069403 | 0.041726 | 7.99524e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1012.79 | 0.0886261 | 7793.35ms | 2251027 | 80 | 2.82315e+08 | 2.11963e+06 | 0.0160425 | 4.94952 | 27.3939 | 5.18988 | 0.0096088 | 0.0787657 | 0.000421463 | 2(Loss) | true |
| Glaze | 975.629 | 0.124563 | 8032.76ms | 2251027 | 160 | 1.20196e+09 | 2.20037e+06 | 0.073439 | 5.15339 | 26.7582 | 4.69635 | 0.00926039 | 0.0401139 | 0.000107448 | 3(Loss) | true |
| simdjson (ondemand) | 959.062 | 0.18005 | 8215.21ms | 2251027 | 30 | 4.87277e+08 | 2.23838e+06 | 0.0118924 | 5.24594 | 26.3445 | 4.22817 | 0.0111418 | 0.0754971 | 0.000629416 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1964.18 | 0.123277 | 6464.58ms | 2090234 | 30 | 4.69586e+07 | 1.01488e+06 | 0.101215 | 2.56516 | 7.7332 | 0.405686 | 0.000241855 | 0.05061 | 0.000102126 | 1(Win) | true |
| Glaze | 947.214 | 0.375535 | 6522.24ms | 2090234 | 40 | 2.49836e+09 | 2.10449e+06 | 0.177141 | 5.27938 | 9.3422 | 0.534101 | 0.000241349 | 0.0694281 | 0.00122356 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1966.79 | 0.071763 | 6445.78ms | 2090234 | 160 | 8.46436e+07 | 1.01353e+06 | 0.0379931 | 2.56259 | 7.73281 | 0.405653 | 0.000246109 | 0.0504478 | 0.000503356 | 1(Win) | true |
| Glaze | 996.161 | 0.0783827 | 6229.9ms | 2090234 | 160 | 3.93632e+08 | 2.00108e+06 | 0.028675 | 5.07415 | 9.33809 | 0.533136 | 0.000234095 | 0.0431842 | 0.000197547 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1862.79 | 0.115777 | 8593.53ms | 5373214 | 160 | 1.62295e+09 | 2.75087e+06 | 0.0421285 | 2.68279 | 14.3202 | 2.70056 | 0.00458096 | 0.0624249 | 0.00113462 | 1(Win) | true |
| simdjson (ondemand) | 1801.49 | 0.0768182 | 8917.35ms | 5373214 | 160 | 7.63931e+08 | 2.84448e+06 | 0.118888 | 2.80219 | 13.7965 | 2.30358 | 0.00641135 | 0.0650309 | 0.000882912 | 2(Loss) | true |
| Jsonifier | 1771.07 | 0.0908244 | 9061.62ms | 5373214 | 160 | 1.1049e+09 | 2.89334e+06 | 0.523043 | 2.85062 | 15.2522 | 3.24726 | 0.00320161 | 0.0381593 | 0.00151652 | 3(Loss) | true |
| Glaze | 1615.01 | 0.072694 | 9898.85ms | 5373214 | 160 | 8.51204e+08 | 3.17292e+06 | 0.0304174 | 3.11997 | 16.0017 | 2.99619 | 0.00493304 | 0.0406137 | 0.00688521 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2168.9 | 0.159041 | 8633.44ms | 5373214 | 40 | 5.64765e+08 | 2.36262e+06 | 0.425969 | 2.30498 | 12.2774 | 2.2067 | 0.00424294 | 0.0522987 | 0.000569571 | 1(Win) | true |
| simdjson (ondemand) | 2124.16 | 0.162701 | 8738.46ms | 5373214 | 160 | 2.46486e+09 | 2.41238e+06 | 0.0244141 | 2.37169 | 11.7271 | 1.80434 | 0.00491651 | 0.0509396 | 0.000746404 | 2(Loss) | true |
| Jsonifier | 2036.59 | 0.180336 | 9044.78ms | 5373214 | 80 | 1.64707e+09 | 2.51611e+06 | 0.00628291 | 2.47873 | 13.2081 | 2.75286 | 0.00293708 | 0.0279726 | 0.00108571 | 3(Loss) | true |
| Glaze | 1845.15 | 0.138932 | 9916.92ms | 5373214 | 40 | 5.95477e+08 | 2.77716e+06 | 0.166602 | 2.73571 | 13.9468 | 2.50129 | 0.00447688 | 0.029671 | 0.00654851 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5182.84 | 0.121742 | 7856.58ms | 6661897 | 30 | 6.68138e+07 | 1.22583e+06 | 0.0799717 | 0.97671 | 2.94099 | 0.261245 | 7.64747e-05 | 0.0279538 | 0.000140621 | 1(Win) | true |
| Glaze | 3230.27 | 0.319708 | 6155.16ms | 6661897 | 30 | 1.18617e+09 | 1.96679e+06 | 0.327093 | 1.55871 | 4.23031 | 0.469317 | 7.72403e-05 | 0.0630812 | 0.00534841 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5107.08 | 0.107145 | 7900.34ms | 6661897 | 160 | 2.84257e+08 | 1.24401e+06 | 0.13589 | 0.981355 | 2.94094 | 0.261234 | 7.57254e-05 | 0.0279372 | 0.000230702 | 1(Win) | true |
| Glaze | 3952.2 | 0.083696 | 5062.68ms | 6661897 | 160 | 2.89632e+08 | 1.60753e+06 | 0.136605 | 1.28664 | 4.22891 | 0.468988 | 8.303e-05 | 0.0244543 | 0.000395246 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2256.24 | 0.167214 | 5563.97ms | 500299 | 320 | 4.00116e+07 | 211468 | 0.00536843 | 2.22342 | 9.95813 | 1.92721 | 0.0108359 | 0.0064238 | 0.000169617 | 1(Win) | true |
| Glaze | 1795.85 | 0.0971262 | 7051.67ms | 500299 | 80 | 5.32697e+06 | 265680 | 0.026933 | 2.80995 | 12.5367 | 2.36647 | 0.0143075 | 0.00541591 | 5.13693e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1665.27 | 0.252303 | 7542.96ms | 500299 | 30 | 1.56768e+07 | 286514 | 0.00688787 | 3.02718 | 13.2996 | 2.30624 | 0.0155173 | 0.0358063 | 0.000111667 | 3(Loss) | true |
| simdjson (ondemand) | 1129.33 | 0.267028 | 5470.9ms | 500299 | 30 | 3.81811e+07 | 422481 | 0.0132962 | 4.44562 | 18.928 | 2.86647 | 0.0163998 | 0.0336231 | 0.000525086 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2799.5 | 0.0996574 | 5352.57ms | 500299 | 160 | 4.61569e+06 | 170431 | 0.119976 | 1.80152 | 8.80504 | 1.64787 | 0.00761034 | 0.0032026 | 2.70963e-05 | 1(Win) | true |
| Glaze | 2138.22 | 0.0387904 | 6814.09ms | 500299 | 1280 | 9.58986e+06 | 223140 | 0.127347 | 2.35274 | 11.3989 | 2.0915 | 0.00950959 | 0.00175153 | 3.54554e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1945.29 | 0.0461945 | 7394.1ms | 500299 | 1280 | 1.64316e+07 | 245270 | 0.107225 | 2.59251 | 12.1486 | 2.02831 | 0.0114918 | 0.0257227 | 0.000196503 | 3(Loss) | true |
| simdjson (ondemand) | 1294.85 | 0.0855718 | 5175.91ms | 500299 | 640 | 6.36303e+07 | 368478 | 0.159858 | 3.87297 | 17.7699 | 2.58181 | 0.00874268 | 0.0206846 | 6.36088e-05 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10386.2 | 0.0428227 | 5374.62ms | 500299 | 1280 | 495339 | 45938 | 0.0765782 | 0.484956 | 2.16603 | 0.353759 | 0.00210543 | 0.00193238 | 6.1635e-06 | 1(Win) | true |
| Glaze | 5055.17 | 0.0782802 | 5257.32ms | 500299 | 2560 | 1.39744e+07 | 94383.1 | 0.155578 | 0.995489 | 4.19185 | 0.585246 | 0.00112071 | 0.0252637 | 1.6651e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10473.1 | 0.108495 | 5348.51ms | 500299 | 320 | 781759 | 45556.8 | 0.0374124 | 0.482639 | 2.16498 | 0.353521 | 0.00204124 | 0.00183909 | 5.53419e-06 | 1(Win) | true |
| Glaze | 5739.64 | 0.044829 | 9083.7ms | 500299 | 4890 | 6.79073e+06 | 83127.6 | 0.202894 | 0.872765 | 4.17823 | 0.582038 | 0.00110896 | 0.000828914 | 2.40621e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3449.43 | 0.221958 | 8393.95ms | 1151920 | 80 | 3.99743e+07 | 318475 | 0.00255521 | 1.45818 | 6.59617 | 1.04633 | 0.00625789 | 0.0549414 | 0.000159234 | 1(Win) | true |
| Jsonifier | 2900.18 | 0.157957 | 9945.56ms | 1151920 | 160 | 5.72787e+07 | 378790 | 0.118973 | 1.74305 | 7.48619 | 1.65172 | 0.00477962 | 0.0192471 | 7.84071e-05 | 2(Loss) | true |
| Glaze | 2564.34 | 0.0951333 | 5553.37ms | 1151920 | 160 | 2.65754e+07 | 428398 | 0.0608697 | 1.96429 | 8.62597 | 1.67904 | 0.00759814 | 0.0137861 | 0.000185896 | 3(Loss) | true |
| simdjson (ondemand) | 2386.86 | 0.063156 | 5960.24ms | 1151920 | 640 | 5.40755e+07 | 460252 | 0.194508 | 2.10247 | 8.90783 | 1.27864 | 0.00720599 | 0.051008 | 0.00012099 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4008.73 | 0.174938 | 8122.64ms | 1151920 | 40 | 9.19298e+06 | 274041 | 0.0748142 | 1.25993 | 6.09497 | 0.925311 | 0.0047726 | 0.0470471 | 6.13975e-05 | 1(Win) | true |
| Jsonifier | 3251.23 | 0.0999643 | 9694.61ms | 1151920 | 80 | 9.12705e+06 | 337890 | 0.225109 | 1.55704 | 6.98687 | 1.53083 | 0.00362685 | 0.0127777 | 4.62706e-05 | 2(Loss) | true |
| Glaze | 2880.65 | 0.049541 | 5433.41ms | 1151920 | 640 | 2.2844e+07 | 381357 | 0.0226332 | 1.75263 | 8.12575 | 1.5582 | 0.00543803 | 0.00923357 | 3.25923e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2713.65 | 0.157246 | 5645.82ms | 1151920 | 160 | 6.48366e+07 | 404827 | 0.100435 | 1.84251 | 8.40381 | 1.15461 | 0.00423407 | 0.0375394 | 6.53691e-05 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15327.5 | 0.0238341 | 9788.68ms | 1439562 | 4890 | 2.22856e+06 | 89569.4 | 0.122595 | 0.32854 | 1.34917 | 0.258045 | 0.000823013 | 0.0181772 | 1.56657e-05 | 1(Win) | true |
| Glaze | 5286.66 | 0.100902 | 6842.33ms | 1439584 | 640 | 4.3943e+07 | 259690 | 0.132625 | 0.947054 | 3.07289 | 0.528478 | 0.0010116 | 0.0630969 | 1.42695e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14900.1 | 0.237319 | 5113.87ms | 1439562 | 40 | 1.91254e+06 | 92138.7 | 0.288721 | 0.334344 | 1.34878 | 0.257958 | 0.000807694 | 0.0179202 | 6.85973e-06 | 1(Win) | true |
| Glaze | 7093.37 | 0.10934 | 5165.48ms | 1439584 | 320 | 1.43309e+07 | 193546 | 0.0556815 | 0.712282 | 3.06771 | 0.527269 | 0.00101149 | 0.0182938 | 1.57967e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2221.28 | 0.0984658 | 3177.5ms | 56369 | 1280 | 726867 | 24201.2 | 0.0397672 | 2.28111 | 9.3505 | 1.89418 | 0.00518682 | 7.21668e-05 | 4.63464e-05 | 1(Win) | true |
| Glaze | 1864.94 | 0.155632 | 3650.78ms | 56369 | 640 | 1.28803e+06 | 28825.4 | 0.0446347 | 2.71309 | 11.633 | 2.33826 | 0.00587025 | 0.000103476 | 6.198e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1723.49 | 0.182512 | 3849.3ms | 56369 | 320 | 1.03704e+06 | 31191.1 | 0.012522 | 2.92555 | 12.2764 | 2.27964 | 0.00827954 | 8.44325e-05 | 5.38306e-05 | 3(Loss) | true |
| simdjson (ondemand) | 964.684 | 0.0693255 | 6358.88ms | 56369 | 2560 | 3.82064e+06 | 55725.7 | 0.0548061 | 5.20229 | 21.9236 | 3.62652 | 0.0115303 | 0.000101438 | 6.27423e-05 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3173.55 | 0.0509012 | 2805.08ms | 56369 | 4890 | 363541 | 16939.3 | 0.0172006 | 1.59384 | 7.22392 | 1.40743 | 0.0036271 | 2.24492e-05 | 1.24037e-05 | 1(Win) | true |
| Glaze | 2620.57 | 0.124009 | 3169.6ms | 56369 | 1280 | 828341 | 20513.7 | 0.210819 | 1.93183 | 9.19944 | 1.77892 | 0.00259588 | 1.59246e-05 | 7.37329e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2417.65 | 0.0479123 | 3326.97ms | 56369 | 4890 | 555003 | 22235.5 | 0.0843087 | 2.08778 | 10.1417 | 1.79114 | 0.00255733 | 2.11867e-05 | 1.06115e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1120.29 | 0.0732013 | 5948.63ms | 56369 | 2560 | 3.15863e+06 | 47985.6 | 0.0946531 | 4.43953 | 19.5775 | 3.09401 | 0.00940056 | 3.39767e-05 | 1.72067e-05 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14612.4 | 0.108466 | 1124.76ms | 56369 | 40 | 636.913 | 3678.9 | 0.0298913 | 0.350025 | 1.42142 | 0.238677 | 0.000172524 | 5.32207e-06 | 4.43506e-07 | 1(Win) | true |
| Glaze | 4957.68 | 0.11903 | 1840.61ms | 56369 | 2560 | 426457 | 10843.3 | 0.209919 | 1.01298 | 3.48779 | 0.484203 | 0.000138734 | 1.91816e-05 | 9.50073e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14802.7 | 0.0875723 | 1113.86ms | 56369 | 2560 | 25892.3 | 3631.61 | 0.0925679 | 0.342336 | 1.41182 | 0.236478 | 0.0001466 | 1.11639e-05 | 5.55076e-06 | 1(Win) | true |
| Glaze | 5531.94 | 0.0575813 | 1720.23ms | 56369 | 4890 | 153108 | 9717.69 | 0.35874 | 0.912113 | 3.41113 | 0.467048 | 0.000123957 | 1.24762e-05 | 5.51798e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2542.98 | 0.0545074 | 3902.32ms | 83958 | 2560 | 754034 | 31486.2 | 0.0235279 | 1.98324 | 8.75913 | 1.54904 | 0.00391585 | 2.90231e-05 | 1.71263e-05 | 1(Win) | true |
| Glaze | 2184.66 | 0.0420872 | 4416.63ms | 83958 | 4890 | 1.1635e+06 | 36650.4 | 0.12543 | 2.31517 | 10.5709 | 2.16641 | 0.00685506 | 3.73958e-05 | 1.7905e-05 | 2(Loss) | true |
| Jsonifier | 1738.81 | 0.143832 | 5372.6ms | 83958 | 1280 | 5.61492e+06 | 46047.9 | 0.0242369 | 2.914 | 9.80381 | 2.1723 | 0.00876306 | 3.49133e-05 | 2.1765e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1395.98 | 0.110854 | 6504.18ms | 83958 | 2560 | 1.03494e+07 | 57356.7 | 0.0750244 | 3.60384 | 15.1338 | 2.45409 | 0.00828261 | 0.000143668 | 6.10145e-05 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3384.39 | 0.0495175 | 3474.34ms | 83958 | 4890 | 671101 | 23658.2 | 0.231789 | 1.49425 | 7.33266 | 1.22247 | 0.00166383 | 1.52087e-05 | 8.34481e-06 | 1(Win) | true |
| Glaze | 2948.1 | 0.0747014 | 3814.13ms | 83958 | 2560 | 1.05375e+06 | 27159.3 | 0.156237 | 1.70608 | 8.94217 | 1.79286 | 0.0033286 | 1.24225e-05 | 5.72273e-06 | 2(Loss) | true |
| Jsonifier | 2129.68 | 0.313567 | 4868.18ms | 83958 | 320 | 4.44741e+06 | 37596.5 | 0.00686519 | 2.37473 | 8.37883 | 1.84644 | 0.00521507 | 1.48512e-05 | 7.48142e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1628.9 | 0.14883 | 6077.62ms | 83958 | 640 | 3.42528e+06 | 49155.1 | 0.313745 | 3.06067 | 13.5627 | 2.09733 | 0.00649854 | 2.21465e-05 | 1.15571e-05 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16494.9 | 0.206624 | 1297.04ms | 94370 | 320 | 40670.2 | 5456.12 | 0.0293735 | 0.308525 | 1.28166 | 0.241708 | 0.000232529 | 3.17898e-06 | 7.6163e-07 | 1(Win) | true |
| Glaze | 4073.24 | 0.0721194 | 2969.35ms | 94370 | 2560 | 650028 | 22095 | 0.155649 | 1.23533 | 4.17651 | 0.677853 | 0.00193001 | 1.5721e-05 | 8.0592e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16538.4 | 0.0801024 | 1293.5ms | 94370 | 2560 | 48642 | 5441.77 | 0.0532983 | 0.306934 | 1.27585 | 0.240384 | 0.000236205 | 5.97714e-06 | 2.52083e-06 | 1(Win) | true |
| Glaze | 4557.24 | 0.181254 | 2739.63ms | 94370 | 640 | 820012 | 19748.4 | 0.00208091 | 1.10613 | 4.12562 | 0.666091 | 0.0018926 | 1.08284e-05 | 5.21551e-06 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1788.68 | 0.123829 | 3640.84ms | 53331 | 2560 | 3.17379e+06 | 28434.7 | 0.304287 | 2.82532 | 10.6192 | 1.88423 | 0.00175396 | 0.000233045 | 0.000140228 | 1(Win) | true |
| Jsonifier | 1600.11 | 0.118065 | 3927.44ms | 53331 | 2560 | 3.6053e+06 | 31785.5 | 0.233244 | 3.15629 | 9.89229 | 1.7817 | 0.0138464 | 0.000415221 | 0.000193075 | 2(Loss) | true |
| Glaze | 1428.04 | 0.0594984 | 4320.11ms | 53331 | 4890 | 2.19581e+06 | 35615.4 | 0.163775 | 3.52164 | 11.6956 | 2.24687 | 0.0214922 | 0.000206317 | 0.00011359 | 3(Loss) | true |
| simdjson (ondemand) | 974.958 | 0.138229 | 5814.19ms | 53331 | 640 | 3.32785e+06 | 52166.8 | 0.0897839 | 5.20435 | 15.3902 | 2.7677 | 0.0146101 | 0.000135123 | 6.19363e-05 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2194.26 | 0.0895435 | 3663.4ms | 53331 | 4890 | 2.10649e+06 | 23178.8 | 0.391582 | 2.2972 | 7.62668 | 1.26677 | 0.00985683 | 0.000114284 | 7.86001e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2083.23 | 0.197075 | 3544.83ms | 53331 | 1280 | 2.96318e+06 | 24414.2 | 0.1131 | 2.43369 | 8.41381 | 1.38311 | 0.00874978 | 0.000152424 | 0.000102119 | 2(Loss) | true |
| Glaze | 1895.99 | 0.0882148 | 4036.55ms | 53331 | 2560 | 1.43354e+06 | 26825.2 | 0.0275653 | 2.6632 | 9.42793 | 1.73162 | 0.0175186 | 7.94713e-05 | 4.6672e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1141.99 | 0.104481 | 5770.45ms | 53331 | 1280 | 2.77154e+06 | 44536.8 | 0.256753 | 4.42366 | 13.4214 | 2.32271 | 0.0108977 | 3.01332e-05 | 1.22027e-05 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16106.8 | 0.235295 | 1093.13ms | 58581 | 4890 | 325709 | 3468.55 | 0.134321 | 0.316523 | 1.077 | 0.164456 | 4.69174e-05 | 2.21671e-05 | 1.26963e-05 | 1(Win) | true |
| Glaze | 5341.8 | 0.326935 | 1803.24ms | 58581 | 640 | 748241 | 10458.5 | 0.0684381 | 0.943417 | 2.62659 | 0.382599 | 6.73747e-05 | 6.30804e-05 | 3.27271e-05 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16449.4 | 0.229491 | 1085.64ms | 58581 | 4890 | 297068 | 3396.31 | 0.676376 | 0.310419 | 1.06791 | 0.16234 | 3.51112e-05 | 1.36389e-05 | 6.72692e-06 | 1(Win) | true |
| Glaze | 6040.34 | 0.181389 | 1676.15ms | 58581 | 2560 | 720528 | 9249.02 | 0.16539 | 0.840194 | 2.55385 | 0.36587 | 5.27181e-05 | 2.90797e-05 | 1.519e-05 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1908.77 | 0.107991 | 4007.48ms | 65103 | 2560 | 3.1587e+06 | 32527.3 | 0.128996 | 2.65232 | 9.08906 | 1.55637 | 0.00797078 | 0.000145347 | 7.31173e-05 | 1(Win) | true |
| Jsonifier | 1536.64 | 0.1698 | 4811.49ms | 65103 | 1280 | 6.02485e+06 | 40404.6 | 0.125952 | 3.28835 | 9.70233 | 1.84918 | 0.0108103 | 0.000207412 | 9.92658e-05 | 2(Loss) | true |
| Glaze | 1493.3 | 0.100658 | 4908.61ms | 65103 | 1280 | 2.24191e+06 | 41577.2 | 0.16172 | 3.38742 | 10.9298 | 2.10766 | 0.0229243 | 7.59014e-05 | 3.04085e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1276.58 | 0.0486926 | 5631.93ms | 65103 | 4890 | 2.74246e+06 | 48635.4 | 0.0997859 | 3.96382 | 12.8391 | 2.27454 | 0.00310729 | 0.000122367 | 7.33367e-05 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2510.65 | 0.0843366 | 3804.1ms | 65103 | 4890 | 2.12701e+06 | 24729.5 | 0.151289 | 2.01345 | 7.28399 | 1.14731 | 0.00606038 | 3.87996e-05 | 1.91014e-05 | 1(Win) | true |
| Jsonifier | 1946.7 | 0.146966 | 4547.84ms | 65103 | 2560 | 5.6244e+06 | 31893.5 | 0.312314 | 2.59906 | 7.85458 | 1.4294 | 0.00792926 | 6.16331e-05 | 3.43686e-05 | 2(Loss) | true |
| Glaze | 1923.93 | 0.0562332 | 4620.33ms | 65103 | 4890 | 1.61034e+06 | 32270.9 | 0.085611 | 2.62682 | 9.08225 | 1.68838 | 0.0181701 | 4.28203e-05 | 2.11463e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1366.69 | 0.0989659 | 5838.1ms | 65103 | 1280 | 2.58728e+06 | 45428.8 | 0.0385585 | 3.70009 | 11.2419 | 1.91534 | 0.00931278 | 6.92892e-05 | 4.11367e-05 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16606.9 | 0.0822921 | 1208.31ms | 78778 | 40 | 554.379 | 4523.93 | 0.183621 | 0.307313 | 1.09159 | 0.183579 | 4.66501e-05 | 8.56838e-06 | 1.58674e-06 | 1(Win) | true |
| Glaze | 4544.55 | 0.208241 | 2404.11ms | 78778 | 1280 | 1.51695e+06 | 16531.6 | 0.0839496 | 1.11306 | 3.01834 | 0.488297 | 0.000360051 | 3.48983e-05 | 1.91599e-05 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16400.5 | 0.377265 | 1206.55ms | 78778 | 1280 | 382296 | 4580.87 | 0.0787349 | 0.309116 | 1.08476 | 0.182069 | 2.60423e-05 | 1.22179e-05 | 6.56513e-06 | 1(Win) | true |
| Glaze | 5126.98 | 0.120229 | 2214.21ms | 78778 | 4890 | 1.5178e+06 | 14653.6 | 0.300373 | 0.984571 | 2.95713 | 0.474155 | 0.000366825 | 2.78617e-05 | 1.51185e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2482.41 | 0.0679695 | 1195.83ms | 11812 | 2560 | 24353.8 | 4537.85 | 0.0725915 | 2.05499 | 9.98112 | 1.74729 | 0.00366943 | 4.27267e-05 | 1.71634e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1824.93 | 0.0532568 | 1364.42ms | 11812 | 4890 | 52846.4 | 6172.74 | 0.173262 | 2.78711 | 13.4227 | 2.2914 | 0.00516504 | 4.03562e-05 | 1.64645e-05 | 2(Loss) | true |
| Glaze | 1792.26 | 0.0602143 | 1368.95ms | 11812 | 4890 | 70041.2 | 6285.25 | 0.00460887 | 2.84032 | 13.6889 | 2.65442 | 0.00105215 | 3.98887e-05 | 1.45428e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1054.31 | 0.0919939 | 1818.46ms | 11812 | 1280 | 123664 | 10684.6 | 0.0703938 | 4.81888 | 20.5064 | 3.40835 | 0.00796376 | 4.55707e-05 | 1.87839e-05 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2825.76 | 0.184351 | 1185.72ms | 11812 | 640 | 34566.1 | 3986.47 | 0.116034 | 1.8078 | 9.06231 | 1.53242 | 0.00306508 | 2.38105e-05 | 5.68807e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2007.65 | 0.076773 | 1356.02ms | 11812 | 2560 | 47503.7 | 5610.94 | 0.0148588 | 2.53639 | 12.5033 | 2.07653 | 0.00460836 | 4.4744e-05 | 2.10326e-05 | 2(Loss) | true |
| Glaze | 2000.83 | 0.106617 | 1355.48ms | 11812 | 1280 | 46119.4 | 5630.05 | 0.0600794 | 2.54521 | 12.6057 | 2.41246 | 0.00109165 | 2.91679e-05 | 9.45807e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1119.71 | 0.0498383 | 1846.54ms | 11812 | 4890 | 122934 | 10060.5 | 0.0470121 | 4.53122 | 19.6591 | 3.21851 | 0.00732232 | 2.63501e-05 | 8.39672e-06 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11542 | 0.10827 | 834.498ms | 11812 | 4890 | 5460.27 | 975.984 | 0.202817 | 0.453465 | 2.09118 | 0.342618 | 0.000133863 | 1.83689e-05 | 3.86076e-06 | 1(Win) | true |
| Glaze | 3863.56 | 0.123613 | 1032.63ms | 11812 | 2560 | 33253.4 | 2915.65 | 0.187668 | 1.32576 | 5.63989 | 0.823576 | 0.000353421 | 2.46704e-05 | 8.4329e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12369.3 | 0.178648 | 830.73ms | 11812 | 640 | 1694.09 | 910.708 | 0.0519587 | 0.427452 | 2.04462 | 0.332035 | 8.46597e-05 | 8.99509e-06 | 9.25965e-07 | 1(Win) | true |
| Glaze | 4367.23 | 0.101133 | 997.826ms | 11812 | 4890 | 33275.7 | 2579.39 | 0.226108 | 1.17806 | 5.37437 | 0.765324 | 0.000406436 | 2.51555e-05 | 1.03184e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3429.02 | 0.0569598 | 1447.32ms | 25388 | 4890 | 79097.6 | 7060.88 | 0.170914 | 1.48155 | 7.13321 | 1.13475 | 0.00293068 | 2.31177e-05 | 1.17119e-05 | 1(Win) | true |
| Jsonifier | 2867.41 | 0.0582323 | 1627.19ms | 25388 | 4890 | 118227 | 8443.82 | 0.0686141 | 1.77038 | 7.8389 | 1.64377 | 0.00425242 | 2.15953e-05 | 1.03506e-05 | 2(Loss) | true |
| Glaze | 2457.4 | 0.0948035 | 1725.84ms | 25388 | 1280 | 111677 | 9852.63 | 0.0176318 | 2.06492 | 9.60627 | 1.88735 | 0.00467458 | 1.59401e-05 | 5.56981e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2146.8 | 0.04948 | 1870.67ms | 25388 | 4890 | 152280 | 11278.1 | 0.150648 | 2.36485 | 10.1945 | 1.62021 | 0.00365289 | 2.2143e-05 | 1.04634e-05 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3709.27 | 0.0569523 | 1459.16ms | 25388 | 4890 | 67579.1 | 6527.4 | 0.195093 | 1.37701 | 6.73732 | 1.04171 | 0.00297399 | 1.3347e-05 | 5.88817e-06 | 1(Win) | true |
| Jsonifier | 3069.63 | 0.129018 | 1603.33ms | 25388 | 40 | 4142.31 | 7887.55 | 0.00612743 | 1.65628 | 7.443 | 1.55073 | 0.00432291 | 2.56026e-05 | 1.47708e-05 | 2(Loss) | true |
| Glaze | 2614.99 | 0.0544318 | 1714.48ms | 25388 | 4890 | 124203 | 9258.89 | 0.0330495 | 1.94092 | 9.10391 | 1.77568 | 0.00476465 | 2.13456e-05 | 9.76259e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2281.03 | 0.210224 | 1856.26ms | 25388 | 320 | 159335 | 10614.5 | 0.0519314 | 2.22296 | 9.75808 | 1.52328 | 0.00318581 | 5.53903e-06 | 7.38538e-07 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15682 | 0.121494 | 933.055ms | 31235 | 2560 | 13634.2 | 1899.51 | 0.0357745 | 0.329044 | 1.41972 | 0.26307 | 6.59567e-05 | 1.38316e-05 | 5.8403e-06 | 1(Win) | true |
| Glaze | 5243.95 | 0.0716324 | 1313.38ms | 31235 | 2560 | 42386.2 | 5680.45 | 0.0374568 | 0.971478 | 3.70312 | 0.653946 | 0.00226555 | 2.05599e-05 | 1.02049e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16239.5 | 0.0833389 | 920.286ms | 31235 | 4890 | 11427.3 | 1834.29 | 0.0434795 | 0.317867 | 1.40173 | 0.258844 | 6.34939e-05 | 6.76971e-06 | 2.154e-06 | 1(Win) | true |
| Glaze | 5647 | 0.0919102 | 1268.51ms | 31235 | 1280 | 30087.3 | 5275.01 | 0.0836004 | 0.902999 | 3.58447 | 0.627565 | 0.00229718 | 1.36566e-05 | 5.45262e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2433.88 | 0.106311 | 5010.37ms | 108313 | 320 | 651430 | 42440.6 | 0.00184084 | 2.07526 | 8.73898 | 1.75646 | 0.00298764 | 1.43104e-05 | 9.54987e-06 | 1(Win) | true |
| Glaze | 2261.45 | 0.0729084 | 5316.95ms | 108313 | 4890 | 5.42316e+06 | 45676.7 | 0.0126487 | 2.22407 | 10.5346 | 1.88219 | 0.00284379 | 1.93543e-05 | 1.15586e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1909.8 | 0.067122 | 6174.06ms | 108313 | 4890 | 6.44501e+06 | 54086.9 | 0.181795 | 2.65102 | 11.8155 | 2.07091 | 0.00305074 | 3.64712e-05 | 2.4924e-05 | 3(Loss) | true |
| simdjson (ondemand) | 760.529 | 0.0955068 | 7341.62ms | 108313 | 1280 | 2.15382e+07 | 135820 | 0.120288 | 6.58685 | 28.4797 | 4.48486 | 0.00425269 | 7.16745e-05 | 4.57802e-05 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2855.99 | 0.0301456 | 4550.51ms | 108313 | 4890 | 581309 | 36168 | 0.00659327 | 1.77075 | 7.95652 | 1.57473 | 0.00252325 | 1.13943e-05 | 6.60058e-06 | 1(Win) | true |
| Glaze | 2572.86 | 0.202243 | 4992.46ms | 108313 | 640 | 4.21946e+06 | 40148.1 | 0.241119 | 1.95901 | 9.81131 | 1.71501 | 0.00248712 | 1.82053e-05 | 9.89609e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2146.8 | 0.0821905 | 5746.92ms | 108313 | 4890 | 7.64768e+06 | 48115.9 | 0.106553 | 2.34931 | 11.0341 | 1.88943 | 0.00267418 | 1.33937e-05 | 7.6711e-06 | 3(Loss) | true |
| simdjson (ondemand) | 790.111 | 0.185619 | 7160ms | 108313 | 320 | 1.88442e+07 | 130735 | 0.0648151 | 6.30837 | 27.7974 | 4.32845 | 0.0036458 | 3.10731e-05 | 1.67339e-05 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18189.2 | 0.1654 | 1312.71ms | 108313 | 640 | 56466.2 | 5678.95 | 0.0868267 | 0.278931 | 1.2473 | 0.328252 | 0.000206015 | 6.56373e-06 | 3.57759e-06 | 1(Win) | true |
| Glaze | 4692.18 | 0.0993827 | 2946.48ms | 108313 | 2560 | 1.22539e+06 | 22014.3 | 0.123582 | 1.07932 | 3.26353 | 0.411382 | 0.000277321 | 2.66444e-05 | 1.73867e-05 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18581.7 | 0.0729144 | 1302ms | 108313 | 2560 | 42058.8 | 5558.98 | 0.102053 | 0.273624 | 1.2424 | 0.327145 | 0.00020569 | 7.83681e-06 | 4.46478e-06 | 1(Win) | true |
| Glaze | 5298.11 | 0.116874 | 2700.88ms | 108313 | 2560 | 1.32922e+06 | 19496.6 | 0.124604 | 0.957266 | 3.21806 | 0.400866 | 0.000274934 | 8.45712e-06 | 4.6451e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2816.16 | 0.0939177 | 6965.61ms | 183677 | 2560 | 8.73635e+06 | 62201 | 0.196665 | 1.79574 | 7.75 | 1.28315 | 0.00188951 | 2.06332e-05 | 1.25688e-05 | 1(Win) | true |
| Glaze | 2570.97 | 0.158832 | 7589.94ms | 183677 | 640 | 7.49496e+06 | 68133.1 | 0.135884 | 1.96895 | 9.22145 | 1.7258 | 0.00320376 | 3.42483e-05 | 1.98974e-05 | 2(Loss) | true |
| Jsonifier | 2167.52 | 0.181941 | 8848.02ms | 183677 | 640 | 1.38365e+07 | 80815 | 0.0615939 | 2.3315 | 8.42061 | 1.88919 | 0.00245034 | 2.28832e-05 | 1.6299e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1259.29 | 0.174871 | 7509ms | 183677 | 320 | 1.89343e+07 | 139101 | 0.0502283 | 3.98425 | 17.312 | 2.66702 | 0.00250327 | 2.23218e-05 | 1.24369e-05 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3128.55 | 0.0797486 | 6539.21ms | 183677 | 4890 | 9.74943e+06 | 55990.2 | 0.133185 | 1.61758 | 7.28992 | 1.17634 | 0.0016703 | 1.18306e-05 | 7.21013e-06 | 1(Win) | true |
| Glaze | 2789.16 | 0.182978 | 7211.24ms | 183677 | 640 | 8.45159e+06 | 62803.1 | 0.0048587 | 1.81264 | 8.80643 | 1.62996 | 0.00287077 | 1.77537e-05 | 1.17819e-05 | 2(Loss) | true |
| Jsonifier | 2347.92 | 0.094779 | 8409.3ms | 183677 | 2560 | 1.27999e+07 | 74605.7 | 0.0559519 | 2.15407 | 7.95927 | 1.78205 | 0.00218091 | 3.04755e-05 | 2.18752e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1313.06 | 0.0913001 | 7313.73ms | 183677 | 1280 | 1.89887e+07 | 133405 | 0.117556 | 3.83015 | 16.9149 | 2.57606 | 0.00217783 | 1.19223e-05 | 5.28271e-06 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20217.4 | 0.316283 | 1743.01ms | 213963 | 160 | 163042 | 10092.8 | 0.000495403 | 0.250844 | 1.119 | 0.27523 | 0.000144476 | 2.42448e-06 | 1.34369e-06 | 1(Win) | true |
| Glaze | 4880.11 | 0.0497971 | 4962.99ms | 213963 | 4890 | 2.11999e+06 | 41812.8 | 0.101602 | 1.03226 | 3.64005 | 0.598024 | 0.000650071 | 3.13989e-05 | 8.42318e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20616.5 | 0.0992513 | 1734.41ms | 213963 | 640 | 61759.1 | 9897.47 | 0.0417073 | 0.246337 | 1.11647 | 0.274664 | 0.000139693 | 4.19903e-06 | 2.4756e-06 | 1(Win) | true |
| Glaze | 5591.76 | 0.0810025 | 4431ms | 213963 | 2560 | 2.23675e+06 | 36491.4 | 0.0354897 | 0.900112 | 3.61276 | 0.591747 | 0.000664186 | 6.34054e-06 | 3.13832e-06 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 844.725 | 0.144644 | 6498.43ms | 1834197 | 30 | 2.69143e+08 | 2.07076e+06 | 0.107967 | 5.94954 | 26.9356 | 5.92682 | 0.0306336 | 0.081915 | 0.000186203 | 1(Win) | true |
| Jsonifier (two-stage) | 721.781 | 0.147575 | 7572.56ms | 1834197 | 40 | 5.11644e+08 | 2.42349e+06 | 0.0298647 | 6.9056 | 31.5926 | 6.61453 | 0.0335859 | 0.145026 | 0.000242068 | 2(Loss) | true |
| Glaze | 670.639 | 0.138812 | 8144.71ms | 1834197 | 30 | 3.93271e+08 | 2.6083e+06 | 0.153742 | 7.50786 | 32.0054 | 6.49715 | 0.0362476 | 0.0821553 | 0.00034362 | 3(Loss) | true |
| simdjson (ondemand) | 579.075 | 0.166314 | 9410.47ms | 1834197 | 30 | 7.5718e+08 | 3.02072e+06 | 0.110068 | 8.67286 | 37.2666 | 6.30541 | 0.045975 | 0.147261 | 0.000569023 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 937.613 | 0.0802131 | 6474.61ms | 1834197 | 160 | 3.58307e+08 | 1.86562e+06 | 0.0101437 | 5.3558 | 23.9289 | 5.22083 | 0.029942 | 0.055453 | 0.000525666 | 1(Win) | true |
| Jsonifier (two-stage) | 796.261 | 0.15896 | 7567.49ms | 1834197 | 30 | 3.65826e+08 | 2.1968e+06 | 0.00870433 | 6.32838 | 28.5836 | 5.90845 | 0.0326513 | 0.118954 | 0.000844257 | 2(Loss) | true |
| Glaze | 735.303 | 0.0637571 | 8145.44ms | 1834197 | 160 | 3.68075e+08 | 2.37892e+06 | 0.181983 | 6.85445 | 28.9905 | 5.79182 | 0.034832 | 0.0586832 | 0.000206276 | 3(Loss) | true |
| simdjson (ondemand) | 635.733 | 0.0985709 | 9286.78ms | 1834197 | 80 | 5.88478e+08 | 2.75151e+06 | 0.181647 | 7.92477 | 34.2442 | 5.59991 | 0.0410692 | 0.118457 | 0.00821519 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1164.6 | 0.0204159 | 9503.36ms | 1834197 | 320 | 3.009e+07 | 1.502e+06 | 0.00729206 | 4.33772 | 12.5783 | 0.909542 | 0.00132829 | 0.0593593 | 8.22584e-05 | 1(Win) | true |
| Glaze | 643.267 | 0.117703 | 8433.64ms | 1833577 | 160 | 1.638e+09 | 2.71837e+06 | 0.109838 | 7.86827 | 16.012 | 0.996538 | 0.00113379 | 0.0494162 | 0.000446624 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1167.74 | 0.141101 | 9513.92ms | 1834197 | 40 | 1.78698e+08 | 1.49796e+06 | 0.156118 | 4.34847 | 12.5781 | 0.909502 | 0.00139556 | 0.0591163 | 0.000890076 | 1(Win) | true |
| Glaze | 651.024 | 0.137172 | 8380.67ms | 1833577 | 160 | 2.172e+09 | 2.68598e+06 | 0.0650211 | 7.82778 | 16.0113 | 0.996381 | 0.00118723 | 0.0493036 | 0.00186368 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2507 | 0.088376 | 8734.46ms | 7351818 | 160 | 9.77395e+08 | 2.79667e+06 | 0.0508374 | 2.00385 | 8.81563 | 1.68859 | 0.00986932 | 0.0607929 | 0.0033769 | 1(Win) | true |
| Jsonifier | 2446.14 | 0.0762484 | 8919.43ms | 7351818 | 160 | 7.64206e+08 | 2.86625e+06 | 0.699858 | 2.0502 | 9.61495 | 2.27645 | 0.00677641 | 0.0336663 | 0.00049809 | 2(Loss) | true |
| simdjson (ondemand) | 2125.81 | 0.131828 | 10290.4ms | 7351818 | 30 | 5.67124e+08 | 3.29814e+06 | 0.00579653 | 2.36812 | 10.2109 | 1.61272 | 0.0110348 | 0.0609432 | 0.00221768 | 3(Loss) | true |
| Glaze | 2101.45 | 0.127617 | 5022.05ms | 7351818 | 80 | 1.45031e+09 | 3.33638e+06 | 0.211317 | 2.39211 | 11.0334 | 2.24385 | 0.00918008 | 0.0332305 | 0.000482335 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2726.9 | 0.0678911 | 8692.8ms | 7351818 | 160 | 4.87525e+08 | 2.57114e+06 | 0.0337936 | 1.84475 | 8.0654 | 1.51252 | 0.00959089 | 0.0541928 | 0.00224531 | 1(Win) | true |
| Jsonifier | 2639.94 | 0.0688551 | 8928.89ms | 7351818 | 160 | 5.35052e+08 | 2.65584e+06 | 0.40169 | 1.89018 | 8.86404 | 2.10027 | 0.00666903 | 0.0271144 | 0.000529907 | 2(Loss) | true |
| simdjson (ondemand) | 2322.86 | 0.0664067 | 10085.8ms | 7351818 | 160 | 6.42816e+08 | 3.01836e+06 | 0.083569 | 2.1666 | 9.45645 | 1.4366 | 0.0098263 | 0.0536423 | 0.000998854 | 3(Loss) | true |
| Glaze | 2255.31 | 0.103387 | 5014.71ms | 7351818 | 80 | 8.26421e+08 | 3.10876e+06 | 0.174772 | 2.22926 | 10.2813 | 2.06793 | 0.00882154 | 0.0273407 | 0.000408477 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5019.95 | 0.170141 | 5862.53ms | 9930848 | 30 | 3.09112e+08 | 1.88663e+06 | 0.384207 | 0.999003 | 3.39349 | 0.427912 | 0.000356307 | 0.0247486 | 0.000464388 | 1(Win) | true |
| Glaze | 3605.4 | 0.150537 | 8169.96ms | 9930228 | 160 | 2.5016e+09 | 2.62667e+06 | 0.377463 | 1.40008 | 4.21673 | 0.484712 | 0.00106741 | 0.0413034 | 0.00284833 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5051.15 | 0.129776 | 5848.78ms | 9930848 | 30 | 1.77624e+08 | 1.87498e+06 | 0.126934 | 1.00088 | 3.39345 | 0.427905 | 0.000360691 | 0.0247207 | 0.00130519 | 1(Win) | true |
| Glaze | 3990.94 | 0.17148 | 7391.26ms | 9930228 | 30 | 4.96724e+08 | 2.37292e+06 | 0.000240211 | 1.26143 | 4.21647 | 0.484654 | 0.00106339 | 0.0220178 | 0.000345162 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 856.042 | 0.0550408 | 6387.49ms | 1834197 | 160 | 2.02391e+08 | 2.04339e+06 | 0.230066 | 5.87342 | 26.5235 | 5.79902 | 0.0313253 | 0.0826507 | 0.000262448 | 1(Win) | true |
| Jsonifier (two-stage) | 734.011 | 0.110576 | 7425.17ms | 1834197 | 80 | 5.55517e+08 | 2.38311e+06 | 0.105931 | 6.82001 | 31.1661 | 6.51347 | 0.0339763 | 0.146052 | 0.00122468 | 2(Loss) | true |
| Glaze | 667.159 | 0.10022 | 8145.28ms | 1834197 | 80 | 5.52371e+08 | 2.6219e+06 | 0.244577 | 7.53254 | 31.9798 | 6.48941 | 0.0361718 | 0.0827063 | 0.000247479 | 3(Loss) | true |
| simdjson (ondemand) | 579.311 | 0.099957 | 9434.31ms | 1834197 | 80 | 7.28761e+08 | 3.0195e+06 | 0.0353702 | 8.65982 | 37.2161 | 6.29552 | 0.0463075 | 0.147463 | 0.000955507 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 962.356 | 0.172841 | 6401.93ms | 1834197 | 30 | 2.96097e+08 | 1.81765e+06 | 0.191126 | 5.23221 | 23.5421 | 5.10383 | 0.030377 | 0.0565749 | 0.000332825 | 1(Win) | true |
| Jsonifier (two-stage) | 813.15 | 0.0731641 | 7450.22ms | 1834197 | 160 | 3.96339e+08 | 2.15117e+06 | 0.061151 | 6.17654 | 28.1861 | 5.81846 | 0.0329617 | 0.119431 | 0.000237205 | 2(Loss) | true |
| Glaze | 734.908 | 0.0967455 | 8141.14ms | 1834197 | 80 | 4.24206e+08 | 2.3802e+06 | 0.0677051 | 6.86694 | 28.993 | 5.79232 | 0.0349009 | 0.0593351 | 0.000324379 | 3(Loss) | true |
| simdjson (ondemand) | 638.884 | 0.0717391 | 9246.51ms | 1834197 | 160 | 6.17277e+08 | 2.73794e+06 | 0.131385 | 7.86001 | 34.223 | 5.59902 | 0.041349 | 0.119145 | 0.00231829 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1161.5 | 0.0740843 | 9595.04ms | 1834197 | 40 | 4.97928e+07 | 1.50601e+06 | 0.0398951 | 4.34633 | 12.5611 | 0.909544 | 0.00118095 | 0.0604085 | 0.000364955 | 1(Win) | true |
| Glaze | 635.953 | 0.101866 | 8574.14ms | 1833577 | 160 | 1.25523e+09 | 2.74963e+06 | 0.0495442 | 7.90487 | 16.0115 | 0.996585 | 0.00110517 | 0.0822615 | 0.00072787 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1159.49 | 0.109393 | 9524.62ms | 1834197 | 40 | 1.08942e+08 | 1.50862e+06 | 0.0650845 | 4.34436 | 12.5609 | 0.909504 | 0.00117149 | 0.0602953 | 0.00105599 | 1(Win) | true |
| Glaze | 657.829 | 0.116442 | 8267.48ms | 1833577 | 80 | 7.66441e+08 | 2.65819e+06 | 0.121609 | 7.68291 | 16.0106 | 0.996384 | 0.00126873 | 0.0492953 | 0.000509387 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2542.53 | 0.150221 | 8773.51ms | 7351818 | 40 | 6.86401e+08 | 2.75758e+06 | 0.383528 | 1.97391 | 8.70937 | 1.66341 | 0.00991554 | 0.0609903 | 0.00292447 | 1(Win) | true |
| Jsonifier | 2486.88 | 0.095911 | 8781.7ms | 7351818 | 80 | 5.84936e+08 | 2.8193e+06 | 0.0379826 | 2.01487 | 9.47474 | 2.25109 | 0.0069067 | 0.0339058 | 0.00179411 | 2(Loss) | true |
| simdjson (ondemand) | 2098.33 | 0.150814 | 5032.58ms | 7351818 | 80 | 2.03148e+09 | 3.34134e+06 | 0.230707 | 2.39022 | 10.1985 | 1.61033 | 0.0111461 | 0.0610155 | 0.00444872 | 3(Loss) | true |
| Glaze | 2088.81 | 0.162357 | 5122.65ms | 7351818 | 30 | 8.90954e+08 | 3.35656e+06 | 0.640193 | 2.40714 | 11.0264 | 2.24172 | 0.00924686 | 0.0333502 | 0.00135087 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2772 | 0.148496 | 8679.46ms | 7351818 | 40 | 5.64276e+08 | 2.52931e+06 | 0.18844 | 1.80582 | 7.96592 | 1.48998 | 0.00959917 | 0.0544113 | 0.00186654 | 1(Win) | true |
| Jsonifier | 2709.87 | 0.134935 | 8827.06ms | 7351818 | 40 | 4.87528e+08 | 2.58729e+06 | 1.66207 | 1.85737 | 8.73079 | 2.07759 | 0.00671972 | 0.0274603 | 0.00252835 | 2(Loss) | true |
| simdjson (ondemand) | 2305.63 | 0.0842984 | 10228.4ms | 7351818 | 160 | 1.05141e+09 | 3.04093e+06 | 0.0603268 | 2.17968 | 9.45137 | 1.43645 | 0.00990936 | 0.0536755 | 0.00303372 | 3(Loss) | true |
| Glaze | 2248.26 | 0.0958293 | 5066.7ms | 7351818 | 40 | 3.57234e+08 | 3.11852e+06 | 0.179205 | 2.23359 | 10.2817 | 2.06801 | 0.0089472 | 0.0274698 | 0.00103952 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5049.42 | 0.0620756 | 5862.17ms | 9930848 | 40 | 5.42241e+07 | 1.87562e+06 | 0.0950195 | 0.998533 | 3.40486 | 0.427912 | 0.000506452 | 0.0247348 | 0.000810034 | 1(Win) | true |
| Glaze | 2890.3 | 0.46527 | 10167.5ms | 9930228 | 40 | 9.29612e+09 | 3.27654e+06 | 0.13559 | 1.73817 | 4.21669 | 0.484737 | 0.00104552 | 0.0752967 | 0.0198649 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5034.67 | 0.143134 | 5865.6ms | 9930848 | 40 | 2.89985e+08 | 1.88112e+06 | 0.0373495 | 1.0006 | 3.40482 | 0.427905 | 0.000499655 | 0.0247206 | 0.00178387 | 1(Win) | true |
| Glaze | 4033.05 | 0.0927759 | 7289.6ms | 9930228 | 160 | 7.59352e+08 | 2.34815e+06 | 0.0551135 | 1.25085 | 4.21632 | 0.484654 | 0.00103996 | 0.0220181 | 0.00170947 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1269.61 | 0.153444 | 9072.68ms | 461466 | 40 | 1.1316e+07 | 346632 | 0.0154126 | 3.97833 | 17.369 | 3.29552 | 0.0190257 | 0.0412135 | 7.21072e-05 | 1(Win) | true |
| Glaze | 1184.72 | 0.0709715 | 9694.95ms | 461466 | 640 | 4.44833e+07 | 371471 | 0.0698511 | 4.24863 | 19.1627 | 3.79018 | 0.0132607 | 0.031469 | 0.000103366 | 2(Loss) | true |
| Jsonifier (two-stage) | 1100.14 | 0.0512307 | 5191.24ms | 461466 | 640 | 2.68797e+07 | 400030 | 0.0375617 | 4.58515 | 18.8407 | 3.5557 | 0.0244441 | 0.0857891 | 0.000150126 | 3(Loss) | true |
| simdjson (ondemand) | 828.403 | 0.169192 | 6896.42ms | 461466 | 160 | 1.29263e+08 | 531249 | 0.158692 | 6.06037 | 25.2962 | 4.4775 | 0.0105948 | 0.0854267 | 0.000184764 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1794.12 | 0.0339683 | 8198.53ms | 461466 | 1280 | 8.88652e+06 | 245294 | 0.0428387 | 2.81229 | 12.9823 | 2.32282 | 0.0168799 | 0.00355081 | 1.73547e-05 | 1(Win) | true |
| Glaze | 1554.21 | 0.182534 | 9201.22ms | 461466 | 160 | 4.27431e+07 | 283158 | 0.0929754 | 3.25073 | 15.2241 | 2.90371 | 0.0114955 | 0.00660101 | 2.78867e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1494.25 | 0.0520696 | 9528.67ms | 461466 | 640 | 1.50515e+07 | 294521 | 0.049877 | 3.37643 | 14.4709 | 2.58716 | 0.0216019 | 0.0282127 | 0.000136745 | 3(Loss) | true |
| simdjson (ondemand) | 1027.9 | 0.149095 | 6351.41ms | 461466 | 320 | 1.30392e+08 | 428143 | 0.0180456 | 4.83998 | 21.197 | 3.54847 | 0.00346641 | 0.0316331 | 4.81888e-05 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14574.7 | 0.0567766 | 3796.96ms | 461466 | 2560 | 752416 | 30195.3 | 0.0203141 | 0.345723 | 1.61351 | 0.264043 | 0.000485046 | 0.00819822 | 1.84433e-05 | 1(Win) | true |
| Glaze | 3571.5 | 0.158956 | 6759.23ms | 461466 | 2560 | 9.82142e+07 | 123222 | 0.191447 | 1.40824 | 5.3694 | 0.791601 | 0.0099999 | 0.0426753 | 3.79421e-05 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14774.1 | 0.330342 | 3781.27ms | 461466 | 30 | 290489 | 29787.9 | 0.046909 | 0.343589 | 1.61236 | 0.263785 | 0.000521454 | 0.00765849 | 4.0523e-05 | 1(Win) | true |
| Glaze | 3923.14 | 0.345362 | 6165.13ms | 461466 | 640 | 9.60595e+07 | 112177 | 0.187174 | 1.27436 | 5.35474 | 0.788156 | 0.00998161 | 0.00877836 | 3.91145e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1686.69 | 0.067283 | 5348.11ms | 728486 | 320 | 2.45773e+07 | 411895 | 0.0830125 | 2.98439 | 12.4962 | 2.27471 | 0.0154814 | 0.071427 | 0.000284215 | 1(Win) | true |
| Glaze | 1557.96 | 0.0995252 | 5778.45ms | 728486 | 640 | 1.2606e+08 | 445928 | 0.334402 | 3.22885 | 14.81 | 2.94403 | 0.010732 | 0.0294245 | 0.000306638 | 2(Loss) | true |
| Jsonifier | 1415.32 | 0.226216 | 6356.69ms | 728486 | 80 | 9.8644e+07 | 490870 | 0.0953299 | 3.56569 | 13.9447 | 2.85958 | 0.0128893 | 0.0387485 | 0.000168329 | 3(Loss) | true |
| simdjson (ondemand) | 1253.87 | 0.12471 | 7151.23ms | 728486 | 320 | 1.52787e+08 | 554074 | 0.0865338 | 3.97686 | 16.5298 | 2.85889 | 0.00728439 | 0.0727059 | 0.000860977 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2260.2 | 0.0487656 | 9832.59ms | 728486 | 1280 | 2.87598e+07 | 307380 | 0.058487 | 2.22151 | 9.72359 | 1.66029 | 0.0138736 | 0.0329691 | 9.25046e-05 | 1(Win) | true |
| Glaze | 1958.02 | 0.105479 | 5509.5ms | 728486 | 320 | 4.48219e+07 | 354816 | 0.0929301 | 2.57183 | 12.312 | 2.38192 | 0.00899919 | 0.00983774 | 4.01732e-05 | 2(Loss) | true |
| Jsonifier | 1790.64 | 0.0726214 | 5894.02ms | 728486 | 640 | 5.08084e+07 | 387984 | 0.111646 | 2.81632 | 11.1708 | 2.24471 | 0.0113823 | 0.0087301 | 5.40762e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1559.04 | 0.103774 | 6564.95ms | 728486 | 640 | 1.36863e+08 | 445621 | 0.0984548 | 3.19583 | 13.9356 | 2.27086 | 0.00265535 | 0.0338856 | 6.3342e-05 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15798.6 | 0.129413 | 5853.5ms | 837491 | 160 | 684856 | 50554.8 | 0.148091 | 0.319284 | 1.35607 | 0.257744 | 0.000462833 | 0.0166646 | 6.00006e-06 | 1(Win) | true |
| Glaze | 3918.21 | 0.119991 | 5443.57ms | 837491 | 640 | 3.82882e+07 | 203842 | 0.162913 | 1.28578 | 4.56914 | 0.770723 | 0.00620305 | 0.0572316 | 3.27354e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15935.1 | 0.0328267 | 5815.05ms | 837491 | 2560 | 693019 | 50121.6 | 0.000749744 | 0.317569 | 1.35544 | 0.257602 | 0.00046231 | 0.0163356 | 1.73295e-05 | 1(Win) | true |
| Glaze | 4493.39 | 0.0862794 | 9540.03ms | 837491 | 1280 | 3.01048e+07 | 177748 | 0.114019 | 1.12437 | 4.56028 | 0.768648 | 0.00620543 | 0.0163803 | 2.76682e-05 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8176.22 | 0.0775996 | 6200.97ms | 466906 | 1280 | 2.28603e+06 | 54459.9 | 0.00301675 | 0.615284 | 3.05574 | 0.390944 | 0.00106632 | 8.32943e-06 | 5.17871e-06 | 1(Win) | true |
| Jsonifier | 8146.48 | 0.0622742 | 6225.45ms | 466906 | 2560 | 2.96603e+06 | 54658.7 | 0.00824073 | 0.617997 | 3.06665 | 0.393769 | 0.00109965 | 6.26966e-06 | 3.79995e-06 | 2(Loss) | true |
| simdjson (ondemand) | 6884.05 | 0.0840203 | 7230.28ms | 466906 | 1280 | 3.78051e+06 | 64682.3 | 0.0209771 | 0.730928 | 3.47925 | 0.380335 | 0.000865071 | 1.71324e-05 | 1.1005e-05 | 3(Loss) | true |
| Glaze | 3400.23 | 0.0231485 | 7078.28ms | 466906 | 2560 | 2.35249e+06 | 130955 | 0.039746 | 1.48905 | 5.74337 | 0.996749 | 0.00175512 | 2.4621e-05 | 1.81213e-05 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8232.13 | 0.0543311 | 6220.41ms | 466906 | 2560 | 2.21091e+06 | 54090.1 | 0.0544969 | 0.614258 | 3.02526 | 0.38415 | 0.00110656 | 1.80669e-05 | 1.58256e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 8187.54 | 0.0760861 | 6236.62ms | 466906 | 1280 | 2.19166e+06 | 54384.6 | 0.110534 | 0.613743 | 3.02392 | 0.383833 | 0.00111285 | 1.74185e-06 | 1.04578e-06 | 2(Loss) | true |
| simdjson (ondemand) | 7008.29 | 0.0300275 | 7198.38ms | 466906 | 4890 | 1.77985e+06 | 63535.7 | 0.071681 | 0.719972 | 3.43081 | 0.369827 | 0.00083059 | 9.09262e-06 | 7.13044e-06 | 3(Loss) | true |
| Glaze | 3432.39 | 0.0396104 | 7100.19ms | 466906 | 640 | 1.68992e+06 | 129728 | 0.0292931 | 1.4731 | 5.69145 | 0.985458 | 0.00170351 | 6.41524e-06 | 3.94887e-06 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9369.41 | 0.0815427 | 7188.29ms | 631514 | 1280 | 3.51659e+06 | 64279.3 | 0.09196 | 0.537036 | 2.70393 | 0.303616 | 0.000608353 | 5.54595e-06 | 2.27628e-06 | 1(Win) | true |
| Jsonifier | 9343.17 | 0.0737514 | 7193.41ms | 631514 | 2560 | 5.78573e+06 | 64459.8 | 0.260395 | 0.537422 | 2.70451 | 0.303765 | 0.000600841 | 1.45094e-05 | 5.9678e-06 | 2(Loss) | true |
| simdjson (ondemand) | 8279.04 | 0.0296934 | 8035.72ms | 631514 | 4890 | 2.28157e+06 | 72745 | 0.0548643 | 0.608704 | 2.90635 | 0.296634 | 0.000619398 | 8.14092e-06 | 3.18772e-06 | 3(Loss) | true |
| Glaze | 4064.43 | 0.0382024 | 7975.07ms | 631514 | 640 | 2.05083e+06 | 148178 | 0.0073249 | 1.24376 | 5.34889 | 0.944944 | 0.00122265 | 7.47707e-06 | 4.50802e-06 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9340.31 | 0.0471099 | 7268.68ms | 631514 | 2560 | 2.36216e+06 | 64479.5 | 0.0883145 | 0.536645 | 2.6823 | 0.298926 | 0.000617421 | 4.71894e-06 | 3.15833e-06 | 1(Win) | true |
| Jsonifier | 9327.72 | 0.0461907 | 7281.79ms | 631514 | 2560 | 2.27701e+06 | 64566.6 | 0.22016 | 0.537252 | 2.68276 | 0.299054 | 0.000633018 | 5.52739e-06 | 3.29008e-06 | 2(Loss) | true |
| simdjson (ondemand) | 8306.59 | 0.042627 | 8062.69ms | 631514 | 2560 | 2.44529e+06 | 72503.7 | 0.221383 | 0.605801 | 2.87319 | 0.289481 | 0.000615272 | 2.36634e-05 | 1.43801e-05 | 3(Loss) | true |
| Glaze | 4065.35 | 0.031597 | 7970.71ms | 631514 | 1280 | 2.8046e+06 | 148144 | 0.0321363 | 1.24177 | 5.31388 | 0.937515 | 0.00122872 | 1.97888e-05 | 1.21707e-05 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Glaze | 1917.4 | 0.07643 | 6136.91ms | 466906 | 640 | 2.01624e+07 | 232230 | 0.0241966 | 2.63789 | 10.0403 | 1.7982 | 0.0103339 | 0.00755563 | 2.24316e-05 | 1(Win) | true |
| Jsonifier | 1889.77 | 0.0687495 | 6208.5ms | 466906 | 1280 | 3.35885e+07 | 235625 | 0.0735319 | 2.67035 | 8.29876 | 1.47148 | 0.0108222 | 0.00929959 | 3.53993e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1756.2 | 0.199195 | 6692.01ms | 466906 | 160 | 4.08123e+07 | 253546 | 0.16404 | 2.87491 | 9.22493 | 1.5301 | 0.0151684 | 0.0256547 | 6.99418e-05 | 3(Loss) | true |
| simdjson (ondemand) | 933.973 | 0.0870075 | 6161.81ms | 466906 | 640 | 1.10124e+08 | 476755 | 0.107543 | 5.31813 | 18.181 | 3.17146 | 0.0124896 | 0.0284879 | 7.95965e-05 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Glaze | 2415.34 | 0.0620524 | 5584.75ms | 466906 | 1280 | 1.67506e+07 | 184353 | 0.168573 | 2.09183 | 8.54733 | 1.45179 | 0.00723451 | 0.000320513 | 1.8548e-05 | 1(Win) | true |
| Jsonifier | 2394.93 | 0.247286 | 5664.78ms | 466906 | 160 | 3.38214e+07 | 185924 | 0.0644764 | 2.10833 | 6.81342 | 1.12718 | 0.00764558 | 0.00181035 | 1.36002e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2324.37 | 0.100275 | 5831.45ms | 466906 | 1280 | 4.72326e+07 | 191569 | 0.164183 | 2.16509 | 7.74474 | 1.18658 | 0.00804072 | 0.00751021 | 1.9818e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1043.87 | 0.161631 | 5855.23ms | 466906 | 320 | 1.52112e+08 | 426562 | 0.10479 | 4.77728 | 16.7747 | 2.84496 | 0.00948912 | 0.0124243 | 4.65163e-05 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19611.2 | 0.219262 | 3074.81ms | 475954 | 2560 | 6.5931e+06 | 23145.2 | 0.0583304 | 0.256779 | 1.01939 | 0.152775 | 0.000284155 | 0.000110544 | 4.61081e-06 | 1(Win) | true |
| Glaze | 6307.5 | 0.268075 | 7961.95ms | 475954 | 1280 | 4.76363e+07 | 71962.8 | 0.191514 | 0.795977 | 2.36354 | 0.337169 | 0.000356243 | 0.0104559 | 1.0236e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19735.2 | 0.155085 | 3061.77ms | 475954 | 4890 | 6.22148e+06 | 22999.8 | 0.0407736 | 0.255983 | 1.01863 | 0.15262 | 0.000276962 | 9.86674e-05 | 6.1897e-06 | 1(Win) | true |
| Glaze | 7020.13 | 0.156711 | 7233.41ms | 475954 | 4890 | 5.02052e+07 | 64657.7 | 0.210126 | 0.717855 | 2.35134 | 0.334375 | 0.000346381 | 0.000484715 | 2.91985e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2193.61 | 0.12014 | 7233.47ms | 631514 | 640 | 6.96309e+07 | 274551 | 0.0766975 | 2.30362 | 7.29787 | 1.15148 | 0.0121835 | 0.0326418 | 0.00028016 | 1(Win) | true |
| Glaze | 2012.1 | 0.073868 | 7844.52ms | 631514 | 1280 | 6.25736e+07 | 299319 | 0.0525372 | 2.51133 | 9.08986 | 1.66399 | 0.0107692 | 0.0148292 | 0.000156449 | 2(Loss) | true |
| Jsonifier | 1576.27 | 0.121186 | 5006.09ms | 631514 | 320 | 6.86054e+07 | 382078 | 0.0382743 | 3.20448 | 7.96941 | 1.53312 | 0.0104958 | 0.0233714 | 0.000271288 | 3(Loss) | true |
| simdjson (ondemand) | 1221.3 | 0.094821 | 6384.14ms | 631514 | 640 | 1.39929e+08 | 493127 | 0.247084 | 4.10437 | 13.7961 | 2.36414 | 0.010406 | 0.0411905 | 0.000504153 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2736.11 | 0.124245 | 6494.81ms | 631514 | 640 | 4.78672e+07 | 220115 | 0.320029 | 1.83994 | 6.2087 | 0.902191 | 0.00947114 | 0.00843407 | 8.80325e-05 | 1(Win) | true |
| Glaze | 2435.33 | 0.162114 | 7096.05ms | 631514 | 160 | 2.57165e+07 | 247300 | 0.0666255 | 2.07295 | 7.99393 | 1.41306 | 0.00851164 | 0.00191189 | 3.83305e-05 | 2(Loss) | true |
| Jsonifier | 1816.18 | 0.124632 | 9391.32ms | 631514 | 640 | 1.09316e+08 | 331607 | 0.0178495 | 2.78441 | 6.87234 | 1.28186 | 0.00813461 | 0.00531975 | 0.000234377 | 3(Loss) | true |
| simdjson (ondemand) | 1381.37 | 0.109717 | 6039.54ms | 631514 | 320 | 7.32226e+07 | 435986 | 0.00241903 | 3.64294 | 12.7536 | 2.12372 | 0.0076407 | 0.012341 | 6.63188e-05 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18169.7 | 0.174686 | 4530.02ms | 716365 | 2560 | 1.1044e+07 | 37599.8 | 0.238727 | 0.277778 | 1.02706 | 0.178553 | 0.000210653 | 0.00400607 | 1.60756e-05 | 1(Win) | true |
| Glaze | 4706.29 | 0.104761 | 7856.94ms | 716365 | 2560 | 5.92041e+07 | 145163 | 0.18875 | 1.06905 | 2.81727 | 0.463483 | 0.000592644 | 0.047295 | 6.6903e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18310.6 | 0.127395 | 4494.83ms | 716365 | 4890 | 1.10478e+07 | 37310.5 | 0.0785245 | 0.275749 | 1.02629 | 0.17838 | 0.000201902 | 0.00372329 | 9.2737e-06 | 1(Win) | true |
| Glaze | 5819.17 | 0.186951 | 6378.38ms | 716365 | 1280 | 6.16613e+07 | 117401 | 0.174006 | 0.86019 | 2.80754 | 0.461218 | 0.00058373 | 0.00350076 | 5.39693e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2524.76 | 0.118509 | 830.942ms | 2632 | 4890 | 6788.05 | 994.182 | 0.0658879 | 2.08425 | 7.97113 | 1.38032 | 0.000770601 | 5.53981e-05 | 1.11884e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2171.12 | 0.113104 | 852.415ms | 2632 | 4890 | 8361.23 | 1156.12 | 0.0266647 | 2.41815 | 9.68503 | 1.69871 | 0.00103578 | 4.78615e-05 | 7.14814e-06 | 2(Loss) | true |
| Glaze | 1924.29 | 0.132865 | 871.347ms | 2632 | 2560 | 7689.37 | 1304.41 | 0.343053 | 2.70824 | 11.4096 | 2.14514 | 0.00118271 | 6.85672e-05 | 9.64689e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1369.5 | 0.0867732 | 940.935ms | 2632 | 4890 | 12368.8 | 1832.84 | 0.0296737 | 3.77566 | 12.9058 | 2.2405 | 0.00553686 | 8.80309e-05 | 1.49956e-05 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2940.43 | 0.124435 | 827.283ms | 2632 | 2560 | 2888.51 | 853.642 | 0.0658965 | 1.80421 | 7.01406 | 1.13336 | 0.000763292 | 3.93296e-05 | 3.2651e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2480.52 | 0.133339 | 844.978ms | 2632 | 4890 | 8902.43 | 1011.91 | 0.556024 | 2.14186 | 8.72683 | 1.45175 | 0.00137423 | 5.23679e-05 | 1.12661e-05 | 2(Loss) | true |
| Glaze | 2461.52 | 0.124567 | 841.195ms | 2632 | 2560 | 4130.61 | 1019.73 | 0.328396 | 2.13985 | 9.47948 | 1.69947 | 0.00158461 | 4.68987e-05 | 2.52303e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1635.04 | 0.214515 | 903.428ms | 2632 | 1280 | 13881.6 | 1535.17 | 0.0317146 | 3.17107 | 11.4688 | 1.8997 | 0.00140874 | 5.63972e-05 | 1.48414e-06 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10405.6 | 0.260417 | 757.66ms | 2632 | 4890 | 1929.67 | 241.223 | 0.0410968 | 0.569407 | 1.87804 | 0.301672 | 0.0005459 | 4.45982e-05 | 5.98268e-06 | 1(Win) | true |
| Glaze | 3456.72 | 0.185049 | 806.096ms | 2632 | 2560 | 4622.27 | 726.143 | 0.0238253 | 1.55463 | 4.77014 | 0.742781 | 0.000389438 | 6.60441e-05 | 1.00921e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11971.4 | 0.354277 | 751.911ms | 2632 | 2560 | 1412.58 | 209.673 | 0.00391219 | 0.506198 | 1.67819 | 0.255699 | 0.000381423 | 3.6955e-05 | 4.15559e-06 | 1(Win) | true |
| Glaze | 3657.25 | 0.118583 | 801.838ms | 2632 | 4890 | 3239.06 | 686.328 | 0.0561341 | 1.46576 | 4.30509 | 0.647417 | 0.000383824 | 4.70845e-05 | 6.60426e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2626.31 | 0.160447 | 875.345ms | 3370 | 80 | 308.404 | 1223.72 | 0.110441 | 1.99037 | 8.20593 | 1.38546 | 0.000619436 | 4.45104e-05 | 0 | 1(Win) | true |
| Jsonifier | 2165.29 | 0.169255 | 917.641ms | 3370 | 2560 | 16156.6 | 1484.28 | 0.17704 | 2.41082 | 8.75579 | 1.72878 | 0.00161953 | 4.26558e-05 | 7.76614e-06 | 2(Loss) | true |
| Glaze | 2093 | 0.0965295 | 888.914ms | 3370 | 4890 | 10743.6 | 1535.54 | 0.213579 | 2.48295 | 10.8083 | 2.07092 | 0.00132269 | 5.03662e-05 | 6.97845e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1752.01 | 0.181285 | 928.826ms | 3370 | 1280 | 14155.4 | 1834.4 | 0.00302372 | 2.95044 | 10.4371 | 1.77834 | 0.00345489 | 6.60701e-05 | 7.88205e-06 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3038.09 | 0.130717 | 866.751ms | 3370 | 4890 | 9350.36 | 1057.86 | 0.250135 | 1.73202 | 7.24392 | 1.15163 | 0.000617077 | 5.04876e-05 | 5.58276e-06 | 1(Win) | true |
| Glaze | 2540.64 | 0.104042 | 864.916ms | 3370 | 4890 | 8470.35 | 1264.99 | 0.00113132 | 2.05414 | 9.29733 | 1.72285 | 0.00109762 | 3.92007e-05 | 5.52208e-06 | 2(Loss) | true |
| Jsonifier | 2367.71 | 0.189906 | 896.449ms | 3370 | 2560 | 17010.6 | 1357.38 | 0.0846789 | 2.20276 | 8.00445 | 1.53591 | 0.00181299 | 0.000104089 | 2.10961e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2058.99 | 0.0998902 | 908.474ms | 3370 | 4890 | 11887.9 | 1560.9 | 0.050649 | 2.51688 | 9.23858 | 1.49674 | 0.0010938 | 5.03662e-05 | 4.55116e-06 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10280.8 | 0.253075 | 764.618ms | 3643 | 4890 | 3576.64 | 337.936 | 0.00209133 | 0.555974 | 1.77436 | 0.307713 | 0.000415959 | 4.50201e-05 | 1.29671e-05 | 1(Win) | true |
| Glaze | 3640.6 | 0.118555 | 832.971ms | 3682 | 4890 | 6393.96 | 964.519 | 0.0777497 | 1.45288 | 4.48588 | 0.746605 | 0.000278812 | 5.29298e-05 | 1.04416e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13282.2 | 0.343235 | 756.384ms | 3643 | 2560 | 2063.5 | 261.571 | 0.0353805 | 0.442643 | 1.6146 | 0.266813 | 0.000274606 | 3.05595e-05 | 5.14686e-06 | 1(Win) | true |
| Glaze | 3867.25 | 0.124445 | 823.65ms | 3682 | 4890 | 6243.45 | 907.991 | 0.300821 | 1.36914 | 4.19772 | 0.680608 | 0.000276923 | 4.421e-05 | 6.2205e-06 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 860.682 | 0.139163 | 1255.84ms | 4630 | 40 | 2038.86 | 5130.25 | 0.0639585 | 5.92302 | 27.1175 | 5.65227 | 0.00840713 | 0.00012419 | 5.39957e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 780.041 | 0.180903 | 1307.89ms | 4630 | 320 | 33555.9 | 5660.62 | 0.113356 | 6.52114 | 29.8994 | 6.08056 | 0.00882357 | 5.46706e-05 | 1.48488e-05 | 2(Loss) | true |
| simdjson (ondemand) | 771.999 | 0.0657278 | 1315.02ms | 4630 | 4890 | 69109.1 | 5719.58 | 0.0383006 | 6.59566 | 31.5847 | 5.51922 | 0.00237108 | 9.88485e-05 | 3.35679e-05 | 3(Loss) | true |
| Glaze | 729.371 | 0.0513806 | 1345.07ms | 4630 | 4890 | 47312 | 6053.86 | 0.075794 | 6.97568 | 30.5523 | 5.92333 | 0.00238972 | 7.23918e-05 | 1.96107e-05 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1038.49 | 0.104277 | 1251.57ms | 4630 | 1280 | 25161.6 | 4251.84 | 0.0300698 | 4.91747 | 22.7313 | 4.63391 | 0.00567208 | 5.36582e-05 | 1.11366e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 937.808 | 0.0775522 | 1305.12ms | 4630 | 2560 | 34132 | 4708.33 | 0.013397 | 5.4423 | 25.5099 | 5.0622 | 0.00584824 | 7.71126e-05 | 2.18514e-05 | 2(Loss) | true |
| simdjson (ondemand) | 878.755 | 0.159289 | 1339.6ms | 4630 | 1280 | 81998.9 | 5024.74 | 0.0600983 | 5.79611 | 28.308 | 4.76199 | 0.00208103 | 7.74501e-05 | 2.46355e-05 | 3(Loss) | true |
| Glaze | 859.833 | 0.152705 | 1342.43ms | 4630 | 640 | 39356.8 | 5135.31 | 0.168817 | 5.92417 | 26.0533 | 4.8797 | 0.00170188 | 4.15092e-05 | 6.74946e-06 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1651.37 | 0.0845223 | 1003.1ms | 4630 | 4890 | 24976.1 | 2673.85 | 0.249745 | 3.09428 | 7.82657 | 0.457884 | 0.00029151 | 3.97956e-05 | 5.16768e-06 | 1(Win) | true |
| Glaze | 971.099 | 0.0277064 | 1192.78ms | 4630 | 4890 | 7760.78 | 4546.92 | 0.00479944 | 5.2425 | 9.81166 | 0.68661 | 0.000230117 | 5.76396e-05 | 9.14283e-06 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1671.16 | 0.0824917 | 1001.58ms | 4630 | 4890 | 23230.3 | 2642.18 | 0.117938 | 3.05284 | 7.71728 | 0.433262 | 0.000229189 | 6.32048e-05 | 1.93457e-05 | 1(Win) | true |
| Glaze | 1010.93 | 0.0369032 | 1175.38ms | 4630 | 40 | 103.922 | 4367.77 | 0.00209866 | 5.05109 | 9.27775 | 0.568035 | 0.000215983 | 0.000151188 | 1.07991e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1781.82 | 0.17538 | 1359.4ms | 11579 | 640 | 75606.1 | 6197.38 | 0.0118007 | 2.85475 | 13.2427 | 2.58194 | 0.00513402 | 4.33166e-05 | 2.06462e-05 | 1(Win) | true |
| simdjson (ondemand) | 1739.99 | 0.0791922 | 1378.93ms | 11579 | 2560 | 64662.2 | 6346.34 | 0.0445248 | 2.93012 | 13.6366 | 2.32714 | 0.00200923 | 5.22565e-05 | 3.15766e-05 | 2(Loss) | true |
| Jsonifier | 1631.55 | 0.0629813 | 1418.19ms | 11579 | 4890 | 88853.4 | 6768.16 | 0.0550347 | 3.10358 | 14.1801 | 3.15053 | 0.00544966 | 2.68627e-05 | 8.81294e-06 | 3(Loss) | true |
| Glaze | 1414.72 | 0.0625131 | 1516.95ms | 11579 | 2560 | 60951.3 | 7805.5 | 0.0338889 | 3.57425 | 15.4425 | 3.02591 | 0.00585674 | 2.82705e-05 | 8.2315e-06 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2166.08 | 0.129998 | 1343.16ms | 11579 | 30 | 1317.62 | 5097.97 | 0.0196118 | 2.35418 | 10.9678 | 2.04379 | 0.00268302 | 5.75755e-05 | 8.63632e-06 | 1(Win) | true |
| simdjson (ondemand) | 2098.15 | 0.114676 | 1371.78ms | 11579 | 2560 | 93250.4 | 5263.01 | 0.026036 | 2.42723 | 11.9661 | 1.92305 | 0.000498647 | 2.54367e-05 | 5.63385e-06 | 2(Loss) | true |
| Jsonifier | 1965.23 | 0.0615145 | 1393.86ms | 11579 | 4890 | 58422.5 | 5618.99 | 0.0204094 | 2.5986 | 11.9049 | 2.60938 | 0.00494838 | 2.76751e-05 | 6.97617e-06 | 3(Loss) | true |
| Glaze | 1662.21 | 0.0753232 | 1497.86ms | 11579 | 2560 | 64101.3 | 6643.31 | 0.0568093 | 3.05867 | 13.2138 | 2.4908 | 0.0039414 | 3.7008e-05 | 1.21111e-05 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5326.18 | 0.103728 | 1006.42ms | 14795 | 2560 | 19329.8 | 2649.1 | 0.0599914 | 0.95389 | 2.97046 | 0.275701 | 0.000286758 | 7.65673e-06 | 7.12868e-07 | 1(Win) | true |
| Glaze | 3274.18 | 0.131917 | 1171.87ms | 14795 | 1280 | 41365.4 | 4309.36 | 0.216112 | 1.55897 | 4.4613 | 0.536195 | 0.000951705 | 2.83035e-05 | 1.20395e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4853.67 | 0.0804105 | 1025.53ms | 14795 | 4890 | 26719.3 | 2907 | 0.327315 | 1.05283 | 2.94829 | 0.270903 | 0.000280369 | 1.49556e-05 | 1.86599e-06 | 1(Win) | true |
| Glaze | 4028.09 | 0.0918233 | 1088.56ms | 14795 | 4890 | 50587.8 | 3502.8 | 0.0677759 | 1.26883 | 4.24475 | 0.486786 | 0.00097315 | 1.14171e-05 | 6.63464e-07 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1631.51 | 0.13505 | 926.541ms | 3223 | 4890 | 31654.8 | 1883.96 | 0.0857789 | 3.17032 | 12.1654 | 2.29879 | 0.00113207 | 0.000180705 | 7.60764e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1372.76 | 0.172587 | 968.957ms | 3223 | 30 | 447.995 | 2239.07 | 0.129351 | 3.75123 | 14.9113 | 2.63326 | 0.00123074 | 2.06847e-05 | 0 | 2(Loss) | true |
| Glaze | 1322.62 | 0.160773 | 970.431ms | 3223 | 2560 | 35736.7 | 2323.93 | 0.069418 | 3.89044 | 15.3185 | 2.91315 | 0.00150517 | 6.77503e-05 | 1.76951e-05 | 3(Loss) | true |
| simdjson (ondemand) | 983.948 | 0.103115 | 1054.85ms | 3223 | 4890 | 50737.5 | 3123.84 | 0.253474 | 5.20185 | 19.7136 | 3.2234 | 0.00156429 | 7.54419e-05 | 1.75756e-05 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2036.43 | 0.17605 | 906.881ms | 3223 | 2560 | 18075.6 | 1509.35 | 0.175673 | 2.55717 | 10.3317 | 1.84642 | 0.00115151 | 5.18733e-05 | 3.51478e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1620.21 | 0.119931 | 953.426ms | 3223 | 4890 | 25313.3 | 1897.1 | 0.273681 | 3.18861 | 13.0773 | 2.18089 | 0.00111583 | 6.22443e-05 | 1.02154e-05 | 2(Loss) | true |
| Glaze | 1595.57 | 0.130504 | 952.364ms | 3223 | 4890 | 30906.2 | 1926.39 | 0.126171 | 3.23741 | 13.4353 | 2.45206 | 0.00126665 | 5.07599e-05 | 7.55054e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1119.25 | 0.116738 | 1039.56ms | 3223 | 4890 | 50257.5 | 2746.2 | 0.0114574 | 4.58512 | 17.7062 | 2.73999 | 0.00207862 | 6.54803e-05 | 1.29438e-05 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7420.3 | 0.253054 | 776.912ms | 3223 | 4890 | 5372.95 | 414.227 | 0.676462 | 0.752612 | 2.3503 | 0.408936 | 0.000492688 | 7.86144e-05 | 3.74989e-05 | 1(Win) | true |
| Glaze | 2931.99 | 0.591358 | 842.982ms | 3223 | 320 | 12298.3 | 1048.33 | 0.0759562 | 1.7956 | 5.17778 | 0.77009 | 0.000325783 | 3.78141e-05 | 5.81756e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8698.1 | 0.117155 | 771.077ms | 3223 | 40 | 6.85577 | 353.375 | 0.324122 | 0.649721 | 2.19516 | 0.372014 | 0.00031027 | 0 | 0 | 1(Win) | true |
| Glaze | 3263.65 | 0.256857 | 829.41ms | 3223 | 2560 | 14980.8 | 941.795 | 0.137058 | 1.62257 | 4.65109 | 0.652527 | 0.000329783 | 3.51478e-05 | 1.33319e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2330.8 | 0.0952231 | 984.424ms | 5839 | 80 | 414.041 | 2389.1 | 0.230743 | 2.20687 | 8.85186 | 1.47902 | 0.000640092 | 8.13495e-05 | 4.28156e-06 | 1(Win) | true |
| Jsonifier | 1773.7 | 0.219175 | 1054.93ms | 5839 | 4890 | 231531 | 3139.49 | 0.0773429 | 2.88635 | 9.89193 | 2.08889 | 0.00135612 | 5.68072e-05 | 1.54451e-05 | 2(Loss) | true |
| Glaze | 1758.65 | 0.206613 | 1057.68ms | 5839 | 1280 | 54782.3 | 3166.34 | 0.00584798 | 2.91184 | 11.3055 | 2.18359 | 0.00167462 | 5.12449e-05 | 1.25771e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1723.26 | 0.138248 | 1065.72ms | 5839 | 2560 | 51089.4 | 3231.37 | 0.00372313 | 2.97002 | 11.3244 | 1.78712 | 0.000833498 | 7.7068e-05 | 3.50552e-05 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2716.7 | 0.307752 | 970.589ms | 5839 | 640 | 25467 | 2049.73 | 0.320578 | 1.92165 | 7.92619 | 1.24645 | 0.000632065 | 3.79988e-05 | 1.09715e-05 | 1(Win) | true |
| Glaze STATISTICAL TIE | 2019.02 | 0.117133 | 1040.32ms | 5839 | 40 | 417.461 | 2758.03 | 0.0558663 | 2.54388 | 10.3523 | 1.94622 | 0.00143004 | 3.8534e-05 | 0 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 2009.26 | 0.282627 | 1041.42ms | 5839 | 2560 | 157062 | 2771.42 | 0.115106 | 2.55273 | 8.96695 | 1.85631 | 0.00136234 | 4.20797e-05 | 8.42931e-06 | 2(Tie) | true |
| simdjson (ondemand) | 1950.5 | 0.147509 | 1051.44ms | 5839 | 2560 | 45400.6 | 2854.92 | 0.00731962 | 2.63082 | 10.3281 | 1.54342 | 0.000620625 | 3.39848e-05 | 6.15474e-06 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9914.66 | 0.274824 | 803.953ms | 6938 | 4890 | 16448.7 | 667.355 | 0.0135908 | 0.542019 | 1.73595 | 0.316086 | 0.00024205 | 2.95931e-05 | 5.62976e-06 | 1(Win) | true |
| Glaze | 3422.98 | 0.260035 | 939.161ms | 6960 | 2560 | 65089.9 | 1939.12 | 0.153928 | 1.50875 | 4.22256 | 0.720259 | 0.000434963 | 6.43184e-05 | 2.2562e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11053.1 | 0.231696 | 799.216ms | 6938 | 4890 | 9406.92 | 598.62 | 0.305429 | 0.488662 | 1.66388 | 0.29951 | 0.000144812 | 2.9711e-05 | 5.86557e-06 | 1(Win) | true |
| Glaze | 3554.27 | 0.202887 | 927.936ms | 6960 | 4890 | 70200 | 1867.49 | 0.327567 | 1.45558 | 3.8717 | 0.645259 | 0.000296847 | 3.14094e-05 | 9.25534e-06 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1952.02 | 0.163674 | 977.027ms | 4857 | 2560 | 38616.1 | 2372.93 | 0.0806139 | 2.63539 | 9.66481 | 1.83354 | 0.00115233 | 5.107e-05 | 1.12595e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1743.58 | 0.125717 | 1007.83ms | 4857 | 4890 | 54544.1 | 2656.6 | 0.0453326 | 2.94461 | 11.7049 | 2.07556 | 0.00167376 | 5.0609e-05 | 1.19996e-05 | 2(Loss) | true |
| Glaze | 1682.19 | 0.18278 | 1019.52ms | 4857 | 1280 | 32422.8 | 2753.55 | 0.0773969 | 3.04924 | 12.0139 | 2.30101 | 0.000820497 | 5.11504e-05 | 9.00762e-06 | 3(Loss) | true |
| simdjson (ondemand) | 765.196 | 0.16709 | 1349.53ms | 4857 | 1280 | 130948 | 6053.34 | 0.175572 | 6.64835 | 22.6718 | 3.92931 | 0.00354916 | 5.6941e-05 | 1.44765e-05 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2669.07 | 0.396373 | 938.222ms | 4857 | 640 | 30283.3 | 1735.43 | 0.197747 | 1.9405 | 7.34486 | 1.29977 | 0.000420141 | 4.27862e-05 | 5.14721e-06 | 1(Win) | true |
| Glaze | 2305.58 | 0.109998 | 967.131ms | 4857 | 4890 | 23881.2 | 2009.04 | 0.138078 | 2.2379 | 9.26127 | 1.68067 | 0.00143629 | 6.27349e-05 | 1.75995e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2163.22 | 0.126288 | 980.116ms | 4857 | 4890 | 35757.4 | 2141.25 | 0.0481236 | 2.38103 | 9.75911 | 1.62034 | 0.000730167 | 5.03985e-05 | 9.34708e-06 | 3(Loss) | true |
| simdjson (ondemand) | 878.82 | 0.15818 | 1293.69ms | 4857 | 1280 | 88971 | 5270.7 | 0.162738 | 5.80091 | 20.4206 | 3.42598 | 0.00339861 | 4.85768e-05 | 4.82551e-06 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9569.98 | 0.279694 | 790.634ms | 4857 | 4890 | 8961.66 | 484.013 | 0.24904 | 0.573205 | 1.69261 | 0.292362 | 0.000304117 | 4.05461e-05 | 6.23139e-06 | 1(Win) | true |
| Glaze | 2727.96 | 0.221872 | 912.378ms | 4857 | 2560 | 36333.4 | 1697.97 | 0.0787545 | 1.88698 | 4.15751 | 0.632284 | 0.000214735 | 5.13917e-05 | 1.38331e-05 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11564 | 0.237619 | 774.45ms | 4857 | 4890 | 4429.85 | 400.552 | 0.757805 | 0.4853 | 1.57175 | 0.261684 | 0.000206562 | 3.322e-05 | 5.51562e-06 | 1(Win) | true |
| Glaze | 2969.65 | 0.174405 | 894.54ms | 4857 | 4890 | 36187 | 1559.78 | 0.0252928 | 1.7432 | 3.68581 | 0.525428 | 0.000210941 | 2.57255e-05 | 3.1999e-06 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2298.81 | 0.127902 | 1019.46ms | 6701 | 4890 | 61820.5 | 2779.94 | 0.0165388 | 2.23059 | 8.9365 | 1.5153 | 0.00108783 | 5.79226e-05 | 2.20948e-05 | 1(Win) | true |
| Glaze | 1899.31 | 0.146602 | 1078.99ms | 6701 | 2560 | 62288.7 | 3364.68 | 0.125261 | 2.70719 | 11.117 | 2.18251 | 0.00145955 | 3.36354e-05 | 7.05352e-06 | 2(Loss) | true |
| Jsonifier | 1612.28 | 0.228045 | 1140.05ms | 6701 | 4890 | 399530 | 3963.69 | 0.647104 | 3.17278 | 10.083 | 2.1164 | 0.00241746 | 5.61525e-05 | 1.88904e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1042.76 | 0.0791314 | 1357.38ms | 6701 | 4890 | 115005 | 6128.51 | 0.016138 | 4.88302 | 16.8379 | 2.87062 | 0.00284333 | 8.29165e-05 | 3.44239e-05 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2840.41 | 0.155386 | 995.844ms | 6701 | 80 | 977.756 | 2249.88 | 0.0400182 | 1.81387 | 7.49963 | 1.18102 | 0.000654753 | 5.96926e-05 | 2.42501e-05 | 1(Win) | true |
| Glaze | 2585.5 | 0.133283 | 1013.39ms | 6701 | 2560 | 27782.8 | 2471.7 | 0.0502501 | 1.98858 | 8.86703 | 1.67975 | 0.00120825 | 2.73397e-05 | 3.26444e-06 | 2(Loss) | true |
| Jsonifier | 1935.17 | 0.269579 | 1097.57ms | 6701 | 4890 | 387545 | 3302.33 | 0.30007 | 2.6472 | 8.42337 | 1.73556 | 0.00150293 | 5.08119e-05 | 1.5503e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1200.88 | 0.197154 | 1300.31ms | 6701 | 30 | 3302.25 | 5321.57 | 0.00375815 | 4.24646 | 15.2274 | 2.51022 | 0.00247724 | 2.98463e-05 | 2.48719e-05 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10906.3 | 0.229848 | 803.205ms | 7376 | 4890 | 10746.6 | 644.973 | 0.162724 | 0.492226 | 1.54745 | 0.281453 | 0.000171229 | 3.13014e-05 | 7.2362e-06 | 1(Win) | true |
| Glaze | 2780.36 | 0.325565 | 996.5ms | 7376 | 1280 | 86840.9 | 2530 | 0.505614 | 1.84737 | 4.54759 | 0.733731 | 0.00156663 | 3.47411e-05 | 6.67282e-06 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12497 | 0.25057 | 796.485ms | 7376 | 4890 | 9727.5 | 562.881 | 0.475773 | 0.431846 | 1.46204 | 0.26166 | 0.000136379 | 2.21522e-05 | 1.82984e-06 | 1(Win) | true |
| Glaze | 3008.54 | 0.16683 | 977.344ms | 7376 | 4890 | 74402.7 | 2338.11 | 1.29212 | 1.71647 | 4.25231 | 0.667029 | 0.00125588 | 4.82136e-05 | 1.92134e-05 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2043.76 | 0.211185 | 819.86ms | 1691 | 30 | 83.3057 | 789.067 | 0.105722 | 2.60422 | 8.78001 | 1.51508 | 0.00212892 | 7.88488e-05 | 0 | 1(Win) | true |
| Glaze | 1901.65 | 0.13495 | 820.911ms | 1691 | 4890 | 6404.4 | 848.033 | 0.0188343 | 2.79551 | 10.1928 | 1.93318 | 0.00137429 | 0.000109082 | 1.12468e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1792.88 | 0.39171 | 827.535ms | 1691 | 2560 | 31780 | 899.481 | 0.525222 | 2.94621 | 9.945 | 1.70136 | 0.000606843 | 0.000135598 | 2.70273e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1359.38 | 0.266734 | 857.379ms | 1691 | 2560 | 25633.1 | 1186.32 | 0.0501234 | 3.84576 | 12.4808 | 2.09225 | 0.000623706 | 0.00014738 | 3.18783e-05 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2510.36 | 0.213525 | 807.602ms | 1691 | 4890 | 9200.75 | 642.403 | 0.355602 | 2.15222 | 7.22176 | 1.12892 | 0.00238578 | 9.14259e-05 | 2.24937e-05 | 1(Win) | true |
| Glaze | 2310.95 | 0.156485 | 813.145ms | 1691 | 4890 | 5831.23 | 697.835 | 0.155999 | 2.33048 | 8.78238 | 1.57836 | 0.00157105 | 8.7556e-05 | 8.82816e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2193.77 | 0.274967 | 818.439ms | 1691 | 4890 | 19979.1 | 735.112 | 0.328961 | 2.4355 | 8.45713 | 1.3288 | 0.000602492 | 8.48955e-05 | 6.28856e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1577.87 | 0.246753 | 851.655ms | 1691 | 2560 | 16282.2 | 1022.05 | 0.0440478 | 3.33999 | 11.0591 | 1.73921 | 0.000604071 | 9.14769e-05 | 1.36291e-05 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9579.94 | 0.47601 | 753.24ms | 1996 | 30 | 26.8379 | 198.7 | 0.251004 | 0.630244 | 1.52856 | 0.25 | 0.001002 | 6.68003e-05 | 0 | 1(Win) | true |
| Glaze | 3772.06 | 0.395275 | 785.637ms | 1996 | 1280 | 5093 | 504.641 | 0.596782 | 1.45145 | 3.81012 | 0.599699 | 0.000512744 | 5.67541e-05 | 7.04534e-06 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11973.8 | 0.428643 | 750.197ms | 1996 | 4890 | 2270.68 | 158.975 | 0.234577 | 0.534167 | 1.35671 | 0.20992 | 0.000501617 | 4.07769e-05 | 6.55708e-06 | 1(Win) | true |
| Glaze | 3894.42 | 0.351577 | 781.066ms | 1996 | 1280 | 3779.96 | 488.785 | 0.0878265 | 1.40757 | 3.25601 | 0.480462 | 0.000507656 | 3.91408e-05 | 1.17422e-06 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2201.92 | 0.281745 | 831.38ms | 2158 | 4890 | 33909.4 | 934.651 | 0.156944 | 2.39861 | 8.25626 | 1.36237 | 0.000478838 | 0.00010585 | 2.07531e-05 | 1(Win) | true |
| Glaze | 1990.25 | 0.161155 | 842.576ms | 2158 | 4890 | 13579.6 | 1034.06 | 0.330817 | 2.64799 | 9.8772 | 1.8962 | 0.000477038 | 0.000207247 | 8.72769e-05 | 2(Loss) | true |
| Jsonifier | 1806.03 | 0.461374 | 851.674ms | 2158 | 2560 | 70761.6 | 1139.53 | 0.320068 | 2.89848 | 8.92586 | 1.70621 | 0.00170785 | 0.000103177 | 1.3938e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1721.46 | 0.25094 | 856.92ms | 2158 | 2560 | 23040.5 | 1195.52 | 0.140074 | 3.03975 | 9.91242 | 1.62929 | 0.000633906 | 0.000104082 | 1.70152e-05 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2717.53 | 0.26441 | 818.679ms | 2158 | 4890 | 19607.4 | 757.317 | 0.21671 | 1.96662 | 7.02873 | 1.05839 | 0.000471163 | 7.15462e-05 | 3.31671e-06 | 1(Win) | true |
| Glaze | 2409.87 | 0.368057 | 832.919ms | 2158 | 80 | 790.38 | 854 | 1.10304 | 2.20415 | 8.59314 | 1.58248 | 0.000463392 | 3.47544e-05 | 0 | 2(Loss) | true |
| Jsonifier | 2176.15 | 0.33469 | 841.644ms | 2158 | 4890 | 48991.3 | 945.721 | 0.188823 | 2.41651 | 7.761 | 1.4143 | 0.000875896 | 0.000114948 | 3.14614e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1999.4 | 0.405304 | 848.577ms | 2158 | 640 | 11139 | 1029.33 | 0.214183 | 2.63464 | 8.85403 | 1.3633 | 0.000474253 | 5.50278e-05 | 3.62025e-06 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10442.5 | 0.501843 | 759.673ms | 2866 | 2560 | 4416.93 | 261.741 | 0.275059 | 0.559706 | 1.44382 | 0.248081 | 0.000553635 | 3.65274e-05 | 6.13333e-06 | 1(Win) | true |
| Glaze | 3483.42 | 0.344483 | 813.017ms | 2866 | 2560 | 18703.3 | 784.641 | 0.0652241 | 1.52832 | 4.17655 | 0.718772 | 0.000360367 | 4.15704e-05 | 1.90815e-06 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12734.9 | 0.44129 | 755.214ms | 2866 | 40 | 35.8814 | 214.625 | 0.0116496 | 0.481185 | 1.32275 | 0.220167 | 0.000348918 | 0 | 0 | 1(Win) | true |
| Glaze | 3962.36 | 0.298142 | 805.299ms | 2866 | 2560 | 10827.5 | 689.798 | 0.170289 | 1.35433 | 3.57397 | 0.584438 | 0.000354234 | 3.35289e-05 | 6.40592e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2220.82 | 0.186177 | 924.437ms | 4390 | 640 | 7883.83 | 1885.18 | 0.0349061 | 2.31538 | 10.5394 | 1.87198 | 0.00205901 | 3.2389e-05 | 0 | 1(Win) | true |
| Glaze | 1701.27 | 0.0792585 | 981.688ms | 4390 | 4890 | 18603.1 | 2460.89 | 0.0617728 | 3.02084 | 13.8198 | 2.66287 | 0.000625795 | 5.87876e-05 | 1.35556e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1681.02 | 0.0768961 | 987.061ms | 4390 | 4890 | 17935.1 | 2490.53 | 0.184686 | 3.05712 | 13.977 | 2.41503 | 0.00270954 | 5.61324e-05 | 1.0947e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1064.71 | 0.0879287 | 1133.06ms | 4390 | 2560 | 30603.5 | 3932.19 | 0.0464134 | 4.79144 | 20.461 | 3.39658 | 0.00301796 | 6.60236e-05 | 1.63724e-05 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2634.17 | 0.103797 | 920.321ms | 4390 | 2560 | 6967.08 | 1589.35 | 0.215621 | 1.97497 | 9.31458 | 1.58861 | 0.00174616 | 4.33336e-05 | 9.87685e-06 | 1(Win) | true |
| Glaze | 1973.33 | 0.0797765 | 973.317ms | 4390 | 4890 | 14008.4 | 2121.61 | 0.0732761 | 2.60966 | 12.2756 | 2.32369 | 0.000614475 | 3.85706e-05 | 3.5403e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1872.31 | 0.0837182 | 988.772ms | 4390 | 4890 | 17136.5 | 2236.08 | 0.195515 | 2.75054 | 12.7506 | 2.13166 | 0.00255284 | 5.10083e-05 | 7.91909e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1142.27 | 0.0706183 | 1125.85ms | 4390 | 4890 | 32759.6 | 3665.2 | 0.000848531 | 4.47658 | 19.2276 | 3.11754 | 0.0032063 | 8.13338e-05 | 2.34778e-05 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10411.9 | 0.226466 | 774.077ms | 4390 | 40 | 33.1692 | 402.1 | 0.14944 | 0.53627 | 2.25535 | 0.37221 | 0.000455581 | 2.84738e-05 | 0 | 1(Win) | true |
| Glaze | 3674.59 | 0.137287 | 850.083ms | 4390 | 4890 | 11964 | 1139.35 | 0.254816 | 1.42923 | 5.77927 | 0.860365 | 0.000543483 | 0.000138025 | 6.57285e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11379.8 | 0.206181 | 767.774ms | 4390 | 40 | 23.0154 | 367.9 | 0.190632 | 0.494499 | 2.14055 | 0.346014 | 0.00022779 | 1.13895e-05 | 0 | 1(Win) | true |
| Glaze | 4037.45 | 0.142993 | 835.853ms | 4390 | 4890 | 10751.1 | 1036.95 | 0.313728 | 1.30285 | 5.37927 | 0.771071 | 0.000530905 | 5.03095e-05 | 1.43941e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3188.97 | 0.101621 | 1023.12ms | 9378 | 2560 | 20793.4 | 2804.53 | 0.048564 | 1.60339 | 7.46129 | 1.20633 | 0.00149173 | 2.12432e-05 | 3.33227e-06 | 1(Win) | true |
| Jsonifier | 2600.9 | 0.112781 | 1085.93ms | 9378 | 2560 | 38502.5 | 3438.64 | 0.0481663 | 1.96719 | 8.21753 | 1.7283 | 0.00303965 | 4.31529e-05 | 1.5495e-05 | 2(Loss) | true |
| Glaze | 2398.2 | 0.0991249 | 1113.84ms | 9378 | 2560 | 34982.9 | 3729.28 | 0.321815 | 2.11902 | 9.73363 | 1.90499 | 0.00274258 | 4.61102e-05 | 1.72028e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2156.93 | 0.0676298 | 1154.73ms | 9378 | 4890 | 38453.4 | 4146.43 | 0.240471 | 2.37146 | 10.2052 | 1.62039 | 0.00139935 | 5.20515e-05 | 1.99091e-05 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3537.59 | 0.179015 | 1016.64ms | 9378 | 640 | 13108.9 | 2528.15 | 0.0348696 | 1.44755 | 6.88718 | 1.07368 | 0.00142021 | 1.9827e-05 | 1.99936e-06 | 1(Win) | true |
| Jsonifier | 2825.01 | 0.0872231 | 1085.02ms | 9378 | 4890 | 37286.5 | 3165.85 | 0.300386 | 1.80842 | 7.64342 | 1.59565 | 0.00302259 | 3.44757e-05 | 9.59475e-06 | 2(Loss) | true |
| Glaze | 2646.01 | 0.0696556 | 1097.75ms | 9378 | 4890 | 27105.5 | 3380.02 | 0.0820918 | 1.93142 | 9.00812 | 1.74579 | 0.00298961 | 3.32327e-05 | 8.0247e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2317.69 | 0.227488 | 1147.33ms | 9378 | 320 | 24659 | 3858.83 | 0.040589 | 2.20528 | 9.61356 | 1.48688 | 0.00140922 | 3.36559e-05 | 1.26626e-05 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15566.1 | 0.193842 | 803.625ms | 11521 | 2560 | 4792.4 | 705.845 | 0.215367 | 0.343846 | 1.51011 | 0.27732 | 0.000130468 | 4.06527e-05 | 1.94278e-05 | 1(Win) | true |
| Glaze | 4767.56 | 0.0834495 | 969.667ms | 11521 | 4890 | 18086.1 | 2304.59 | 0.354703 | 1.07817 | 3.86946 | 0.688048 | 0.00116723 | 3.17727e-05 | 1.15731e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17581.7 | 0.329411 | 795.686ms | 11521 | 320 | 1356.09 | 624.928 | 0.107628 | 0.31117 | 1.46012 | 0.265255 | 8.76118e-05 | 3.2278e-05 | 1.87158e-05 | 1(Win) | true |
| Glaze | 5469.6 | 0.0700879 | 933.562ms | 11521 | 4890 | 9693.15 | 2008.79 | 0.0691472 | 0.945164 | 3.62026 | 0.633279 | 0.00115557 | 2.72109e-05 | 1.02596e-05 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2492.85 | 0.177706 | 915.795ms | 4669 | 2560 | 25793.1 | 1786.19 | 0.134293 | 2.08367 | 8.21632 | 1.63611 | 0.00109825 | 4.71026e-05 | 1.8908e-05 | 1(Win) | true |
| Glaze | 2053.9 | 0.396725 | 952.756ms | 4669 | 1280 | 94684.5 | 2167.93 | 0.21762 | 2.53181 | 10.133 | 1.8066 | 0.000871439 | 6.0907e-05 | 2.32585e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1864.57 | 0.27736 | 976.997ms | 4669 | 4890 | 214530 | 2388.06 | 0.0727017 | 2.76164 | 11.1955 | 1.92268 | 0.00132686 | 5.57127e-05 | 1.2439e-05 | 3(Loss) | true |
| simdjson (ondemand) | 662.095 | 0.172927 | 1412.75ms | 4669 | 1280 | 173119 | 6725.17 | 0.0257826 | 7.6725 | 28.9546 | 4.58942 | 0.00281444 | 0.000105583 | 4.43417e-05 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2678.6 | 0.135203 | 907.555ms | 4669 | 4890 | 24701.1 | 1662.33 | 0.11802 | 1.93514 | 7.75027 | 1.52195 | 0.00129107 | 2.72432e-05 | 6.1319e-06 | 1(Win) | true |
| Glaze | 2315.74 | 0.305736 | 934.346ms | 4669 | 2560 | 88471.5 | 1922.8 | 0.435667 | 2.2695 | 9.35875 | 1.63097 | 0.000788027 | 5.51343e-05 | 2.82783e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1975.41 | 0.389381 | 968.349ms | 4669 | 2560 | 197207 | 2254.07 | 0.137116 | 2.60762 | 10.7278 | 1.80853 | 0.00132021 | 5.23734e-05 | 1.14619e-05 | 3(Loss) | true |
| simdjson (ondemand) | 690.793 | 0.0852982 | 1389.97ms | 4669 | 4890 | 147822 | 6445.79 | 0.0825406 | 7.3417 | 28.1803 | 4.41251 | 0.00279238 | 9.0358e-05 | 3.60906e-05 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11878.3 | 0.221323 | 773.587ms | 4669 | 4890 | 3365.89 | 374.86 | 0.149436 | 0.473529 | 1.40801 | 0.361963 | 0.000345095 | 3.7098e-05 | 7.40208e-06 | 1(Win) | true |
| Glaze | 2466 | 0.192207 | 918.538ms | 4669 | 4890 | 58898.9 | 1805.64 | 0.0842261 | 2.10518 | 3.68452 | 0.508461 | 0.000221274 | 7.90578e-05 | 3.10975e-05 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13690.9 | 0.233943 | 767.586ms | 4669 | 4890 | 2830.83 | 325.232 | 0.203269 | 0.417659 | 1.29964 | 0.336689 | 0.000214617 | 3.20611e-05 | 8.67226e-06 | 1(Win) | true |
| Glaze | 2751.17 | 1.46118 | 899.331ms | 4669 | 80 | 44741.5 | 1618.47 | 0.216722 | 1.88472 | 3.1949 | 0.397516 | 0.000214179 | 5.88991e-05 | 2.94496e-05 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2832.44 | 0.327213 | 1005.13ms | 7932 | 2560 | 195500 | 2670.68 | 0.220966 | 1.80828 | 7.31493 | 1.18079 | 0.000664043 | 3.12717e-05 | 6.64831e-06 | 1(Win) | true |
| Glaze | 2386.37 | 0.156754 | 1057.11ms | 7932 | 4890 | 120736 | 3169.89 | 0.218281 | 2.15233 | 8.9589 | 1.6707 | 0.00147465 | 4.07348e-05 | 1.57009e-05 | 2(Loss) | true |
| Jsonifier | 2098.12 | 0.371264 | 1099.25ms | 7932 | 2560 | 458682 | 3605.4 | 0.0582229 | 2.43998 | 7.95386 | 1.78366 | 0.00136079 | 3.85109e-05 | 1.27057e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1096.56 | 0.139137 | 1429.39ms | 7932 | 2560 | 235844 | 6898.41 | 0.014062 | 4.63031 | 17.5596 | 2.72491 | 0.00172748 | 3.3931e-05 | 9.60311e-06 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3035.78 | 0.126003 | 997.621ms | 7932 | 40 | 394.318 | 2491.8 | 0.326671 | 1.69409 | 7.09002 | 1.12468 | 0.000712305 | 2.20625e-05 | 3.15179e-06 | 1(Win) | true |
| Glaze | 2574.64 | 0.197699 | 1040.04ms | 7932 | 2560 | 86373.6 | 2938.09 | 0.0477126 | 1.99724 | 8.50282 | 1.56733 | 0.00146012 | 3.4325e-05 | 1.38876e-05 | 2(Loss) | true |
| Jsonifier | 2170.22 | 0.265288 | 1092.93ms | 7932 | 4890 | 418120 | 3485.61 | 0.263711 | 2.36102 | 7.72882 | 1.72756 | 0.00141164 | 5.59975e-05 | 2.9262e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1147.65 | 0.177831 | 1405.19ms | 7932 | 1280 | 175861 | 6591.32 | 0.0103226 | 4.42933 | 17.1039 | 2.62078 | 0.00170738 | 2.9548e-05 | 7.38701e-06 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14030.9 | 0.195532 | 797.752ms | 9249 | 40 | 60.4385 | 628.65 | 0.00265125 | 0.383804 | 1.22889 | 0.293221 | 0.00021624 | 1.6218e-05 | 0 | 1(Win) | true |
| Glaze | 2817.69 | 0.171949 | 1052.28ms | 9249 | 2560 | 74172.6 | 3130.41 | 0.124081 | 1.82279 | 3.89242 | 0.651206 | 0.000482865 | 2.8846e-05 | 9.29155e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15781.7 | 0.30258 | 786.47ms | 9249 | 2560 | 7321.55 | 558.909 | 0.303311 | 0.345425 | 1.16791 | 0.2783 | 0.000108711 | 8.15122e-06 | 8.8692e-07 | 1(Win) | true |
| Glaze | 2681.52 | 0.378214 | 1070.65ms | 9249 | 320 | 49528.5 | 3289.38 | 0.0458652 | 1.90823 | 3.62255 | 0.590443 | 0.00038146 | 1.65558e-05 | 2.02725e-06 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 756.362 | 0.137232 | 1322.87ms | 4604 | 2560 | 162466 | 5805.05 | 0.00568573 | 6.74619 | 26.1755 | 5.74609 | 0.00527471 | 0.000154842 | 8.64567e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 663.18 | 0.11065 | 1407.72ms | 4604 | 4890 | 262433 | 6620.7 | 0.0881486 | 7.65384 | 30.3189 | 6.2765 | 0.00689624 | 0.000392741 | 0.000235725 | 2(Loss) | true |
| Glaze | 621.076 | 0.055157 | 1449.47ms | 4604 | 4890 | 74351.8 | 7069.54 | 0.0869804 | 8.17509 | 34.0867 | 6.94983 | 0.00473568 | 7.82195e-05 | 2.68283e-05 | 3(Loss) | true |
| simdjson (ondemand) | 508.37 | 0.298911 | 1608.57ms | 4604 | 320 | 213277 | 8636.85 | 0.0905736 | 9.98739 | 40.5563 | 7.26542 | 0.00577283 | 0.000397073 | 0.000266752 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 937.906 | 0.113632 | 1305.64ms | 4604 | 4890 | 138376 | 4681.4 | 0.374414 | 5.44936 | 20.9603 | 4.56494 | 0.00551015 | 0.000151686 | 8.15509e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 795.045 | 0.111512 | 1392.43ms | 4604 | 4890 | 185455 | 5522.6 | 0.165595 | 6.41116 | 25.8008 | 5.24696 | 0.00576821 | 7.37333e-05 | 2.65618e-05 | 2(Loss) | true |
| Glaze | 718.798 | 0.0607924 | 1441.46ms | 4604 | 4890 | 67431.9 | 6108.42 | 0.0319959 | 7.07998 | 29.4028 | 5.87337 | 0.006815 | 7.57766e-05 | 2.7761e-05 | 3(Loss) | true |
| simdjson (ondemand) | 566.308 | 0.0702098 | 1617.71ms | 4604 | 4890 | 144900 | 7753.22 | 0.120833 | 8.99907 | 37.068 | 6.46981 | 0.00669166 | 0.000335309 | 0.000198858 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1470.45 | 0.109788 | 1041.04ms | 4604 | 4890 | 52551.8 | 2985.96 | 0.00749607 | 3.48832 | 9.36143 | 0.661599 | 0.000515156 | 0.000208985 | 0.000123037 | 1(Win) | true |
| Glaze | 828.375 | 0.0557994 | 1274.64ms | 4604 | 4890 | 42774.4 | 5300.4 | 0.147854 | 6.1559 | 12.9944 | 1.08775 | 0.00154462 | 0.000108823 | 4.57502e-05 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1519.91 | 0.322539 | 1027.09ms | 4604 | 320 | 27781.3 | 2888.81 | 0.0149261 | 3.389 | 9.23653 | 0.631408 | 0.000498887 | 2.85078e-05 | 1.22176e-05 | 1(Win) | true |
| Glaze | 855.281 | 0.075424 | 1255.2ms | 4604 | 2560 | 38380.6 | 5133.65 | 0.00849865 | 5.96392 | 12.4472 | 0.970678 | 0.000890191 | 0.00014466 | 7.1015e-05 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2360 | 0.109693 | 1483.66ms | 18245 | 4890 | 319840 | 7372.8 | 0.119182 | 2.15405 | 8.6028 | 1.62477 | 0.00167277 | 3.95772e-05 | 2.02874e-05 | 1(Win) | true |
| Jsonifier | 2043.76 | 0.180167 | 1596.23ms | 18245 | 2560 | 602305 | 8513.62 | 0.0396489 | 2.47807 | 9.43322 | 2.16711 | 0.00208257 | 2.56277e-05 | 1.0812e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1865.88 | 0.0662859 | 1675.85ms | 18245 | 4890 | 186840 | 9325.23 | 0.226564 | 2.72079 | 11.0894 | 1.85881 | 0.00158318 | 0.000107792 | 7.21939e-05 | 3(Loss) | true |
| Glaze | 1783.35 | 0.0746727 | 1724.06ms | 18245 | 2560 | 135887 | 9756.8 | 0.0262386 | 2.84304 | 11.8345 | 2.39178 | 0.00389441 | 6.07187e-05 | 3.2586e-05 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2747.06 | 0.10711 | 1471.78ms | 18245 | 4890 | 225073 | 6333.98 | 0.154615 | 1.85342 | 7.50918 | 1.37501 | 0.00139212 | 3.85908e-05 | 2.18005e-05 | 1(Win) | true |
| Jsonifier | 2337.65 | 0.159987 | 1587.82ms | 18245 | 4890 | 693435 | 7443.29 | 0.274735 | 2.17773 | 8.26969 | 1.90222 | 0.00199929 | 2.46811e-05 | 1.15672e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2079.01 | 0.067124 | 1685.9ms | 18245 | 4890 | 154325 | 8369.25 | 0.00206081 | 2.44314 | 10.3271 | 1.68278 | 0.00100952 | 3.05768e-05 | 1.44141e-05 | 3(Loss) | true |
| Glaze | 1976.97 | 0.0862353 | 1713.26ms | 18245 | 2560 | 147468 | 8801.25 | 0.0299495 | 2.57112 | 10.7313 | 2.13763 | 0.00354018 | 4.33552e-05 | 2.19452e-05 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5382.86 | 0.103354 | 1183.38ms | 24579 | 4890 | 99053 | 4354.63 | 0.200404 | 0.947747 | 2.97587 | 0.388584 | 0.00014506 | 1.41524e-05 | 5.70757e-06 | 1(Win) | true |
| Glaze | 3537.16 | 0.0894253 | 1411.65ms | 24579 | 4890 | 171731 | 6626.89 | 0.0487155 | 1.43834 | 3.74348 | 0.481183 | 0.000322012 | 1.58497e-05 | 5.40804e-06 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5475.54 | 0.101569 | 1169.47ms | 24579 | 4890 | 92450.4 | 4280.92 | 0.102826 | 0.931229 | 2.95594 | 0.383946 | 0.000126174 | 1.30126e-05 | 4.2682e-06 | 1(Win) | true |
| Glaze | 3881.49 | 0.0882327 | 1352.48ms | 24579 | 4890 | 138835 | 6039.02 | 0.154343 | 1.31059 | 3.59514 | 0.447659 | 0.000235258 | 9.58472e-06 | 2.51266e-06 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 836.932 | 0.140725 | 1267.03ms | 4604 | 1280 | 69765.5 | 5246.2 | 0.0166666 | 6.08565 | 24.3034 | 5.30017 | 0.00681557 | 4.29314e-05 | 6.10882e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 728.462 | 0.0810377 | 1347.35ms | 4604 | 4890 | 116665 | 6027.38 | 0.139974 | 6.96875 | 29.2083 | 6.06234 | 0.00601735 | 7.80419e-05 | 3.01152e-05 | 2(Loss) | true |
| Glaze | 631.48 | 0.0850848 | 1443.16ms | 4604 | 2560 | 89597.6 | 6953.06 | 0.0299351 | 8.04339 | 33.1649 | 6.74664 | 0.00693079 | 8.56931e-05 | 2.94411e-05 | 3(Loss) | true |
| simdjson (ondemand) | 512.28 | 0.0954689 | 1605.01ms | 4604 | 2560 | 171404 | 8570.93 | 0.0102373 | 9.91408 | 39.9543 | 7.13879 | 0.00771722 | 0.000218051 | 0.000107838 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1030.8 | 0.0968146 | 1260.79ms | 4604 | 2560 | 43535.9 | 4259.54 | 0.105762 | 4.95189 | 19.9064 | 4.29673 | 0.00599877 | 6.76212e-05 | 1.26419e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 868.985 | 0.089668 | 1347.72ms | 4604 | 4890 | 100376 | 5052.7 | 0.0330679 | 5.86582 | 24.9372 | 5.08384 | 0.00524466 | 9.77189e-05 | 3.95761e-05 | 2(Loss) | true |
| Glaze | 733.946 | 0.0837383 | 1432.18ms | 4604 | 2560 | 64243.8 | 5982.35 | 0.0178749 | 6.93535 | 28.8627 | 5.75587 | 0.00611612 | 5.5743e-05 | 1.46781e-05 | 3(Loss) | true |
| simdjson (ondemand) | 561.034 | 0.0760734 | 1622.27ms | 4604 | 4890 | 173327 | 7826.11 | 0.071717 | 9.05561 | 37.2691 | 6.51716 | 0.00696052 | 0.000112954 | 3.56674e-05 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1377.87 | 0.0821723 | 1063.07ms | 4604 | 4890 | 33528.6 | 3186.6 | 0.00337174 | 3.71499 | 9.34904 | 0.661816 | 0.000694604 | 0.000182601 | 9.15448e-05 | 1(Win) | true |
| Glaze | 806.953 | 0.0853759 | 1287.17ms | 4604 | 2560 | 55244 | 5441.1 | 0.109498 | 6.30862 | 12.9225 | 1.08015 | 0.00181296 | 0.000121328 | 5.33673e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1511.52 | 0.117135 | 1034.11ms | 4604 | 2560 | 29638.3 | 2904.83 | 0.083157 | 3.38295 | 9.22415 | 0.631625 | 0.000519504 | 6.95727e-05 | 2.42656e-05 | 1(Win) | true |
| Glaze | 854.675 | 0.0574044 | 1255.76ms | 4604 | 4890 | 42527.4 | 5137.29 | 0.126834 | 5.953 | 12.437 | 0.970896 | 0.000990559 | 9.02123e-05 | 3.87766e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2524.66 | 0.0736326 | 1436.25ms | 18245 | 4890 | 125931 | 6891.93 | 0.0768696 | 2.01343 | 8.35528 | 1.57764 | 0.00158439 | 2.94783e-05 | 1.42124e-05 | 1(Win) | true |
| Jsonifier | 2147.42 | 0.178866 | 1556.33ms | 18245 | 2560 | 537710 | 8102.64 | 0.0413809 | 2.36495 | 9.06029 | 2.1083 | 0.00199661 | 2.93103e-05 | 1.4259e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1889.28 | 0.0671938 | 1668.33ms | 18245 | 4890 | 187267 | 9209.74 | 0.287309 | 2.68874 | 10.9202 | 1.82346 | 0.00206445 | 9.9991e-05 | 6.10078e-05 | 3(Loss) | true |
| Glaze | 1812.93 | 0.0596172 | 1709.6ms | 18245 | 4890 | 160095 | 9597.6 | 0.0310265 | 2.79926 | 11.6241 | 2.3444 | 0.00384032 | 7.36062e-05 | 4.24129e-05 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2968.26 | 0.109153 | 1428.31ms | 18245 | 2560 | 104808 | 5861.95 | 0.00557057 | 1.71118 | 7.27893 | 1.33149 | 0.00121208 | 1.67854e-05 | 4.62455e-06 | 1(Win) | true |
| Jsonifier | 2448.11 | 0.193029 | 1555.46ms | 18245 | 2560 | 481846 | 7107.42 | 0.104047 | 2.08256 | 7.95977 | 1.85695 | 0.00201091 | 5.20691e-05 | 2.98241e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2060.19 | 0.0742787 | 1692.86ms | 18245 | 4890 | 192447 | 8445.72 | 0.0136314 | 2.46744 | 10.3985 | 1.69923 | 0.001249 | 5.04943e-05 | 2.92542e-05 | 3(Loss) | true |
| Glaze | 1986.72 | 0.114021 | 1709.13ms | 18245 | 1280 | 127643 | 8758.07 | 0.298677 | 2.55517 | 10.6005 | 2.10924 | 0.00348139 | 2.08533e-05 | 7.27939e-06 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5248.43 | 0.102589 | 1191.81ms | 24579 | 4890 | 102655 | 4466.16 | 0.130071 | 0.972136 | 2.97128 | 0.388625 | 0.00012639 | 1.91195e-05 | 7.97895e-06 | 1(Win) | true |
| Glaze | 3269.26 | 0.116299 | 1466.41ms | 24579 | 2560 | 177999 | 7169.92 | 0.0487298 | 1.55797 | 3.74138 | 0.481592 | 0.000586104 | 4.60568e-05 | 2.7971e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5376.62 | 0.142588 | 1179.45ms | 24579 | 2560 | 98926.7 | 4359.68 | 0.0292717 | 0.949261 | 2.95134 | 0.383987 | 0.000125965 | 2.24086e-05 | 1.01872e-05 | 1(Win) | true |
| Glaze | 3636.08 | 0.112084 | 1394.05ms | 24579 | 2560 | 133655 | 6446.59 | 0.500732 | 1.41734 | 3.59408 | 0.447374 | 0.000408774 | 3.61716e-05 | 2.0136e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1714.74 | 0.168724 | 1019.58ms | 5094 | 1280 | 29247 | 2833.09 | 0.0786532 | 2.99121 | 13.4572 | 2.44582 | 0.000778489 | 0.000101222 | 4.96908e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1530.34 | 0.118421 | 1057.87ms | 5094 | 2560 | 36177.7 | 3174.47 | 0.14835 | 3.33217 | 14.5024 | 2.60954 | 0.00184868 | 6.5871e-05 | 2.84495e-05 | 2(Loss) | true |
| Glaze | 1265.83 | 0.108348 | 1126.51ms | 5094 | 2560 | 44263.7 | 3837.82 | 0.028487 | 4.03523 | 16.4772 | 3.17491 | 0.00382098 | 0.000100992 | 4.14857e-05 | 3(Loss) | true |
| simdjson (ondemand) | 842.552 | 0.0742074 | 1321.72ms | 5094 | 4890 | 89521.6 | 5765.84 | 0.133467 | 6.04118 | 22.4358 | 3.82391 | 0.00603232 | 0.000194543 | 0.000100162 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2147.02 | 0.13381 | 1021.94ms | 5094 | 2560 | 23467.1 | 2262.68 | 0.0583168 | 2.39762 | 10.9613 | 1.87809 | 0.0005979 | 7.57632e-05 | 3.02899e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1879.22 | 0.129145 | 1060.09ms | 5094 | 2560 | 28533.8 | 2585.12 | 0.157505 | 2.73582 | 12.2419 | 2.08697 | 0.00122594 | 0.000148152 | 8.18978e-05 | 2(Loss) | true |
| Glaze | 1640.14 | 0.0772277 | 1097.01ms | 5094 | 4890 | 25586.5 | 2961.95 | 0.0423225 | 3.12734 | 13.126 | 2.43502 | 0.00414984 | 4.72909e-05 | 9.23337e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1006.07 | 0.181818 | 1287.28ms | 5094 | 320 | 24665.5 | 4828.72 | 0.102407 | 5.07236 | 19.7689 | 3.22183 | 0.00382926 | 3.80349e-05 | 8.58854e-06 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12911 | 0.376138 | 771.849ms | 5094 | 160 | 320.487 | 376.269 | 0.246885 | 0.440375 | 1.79721 | 0.302513 | 0.000236798 | 3.6808e-05 | 1.59501e-05 | 1(Win) | true |
| Glaze | 3220.16 | 0.171685 | 889.137ms | 5094 | 4890 | 32804.7 | 1508.63 | 0.317122 | 1.6098 | 5.89223 | 0.905968 | 0.000205543 | 4.87763e-05 | 1.12005e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14196.3 | 0.239524 | 766.046ms | 5094 | 4890 | 3285.29 | 342.203 | 0.164578 | 0.399231 | 1.68728 | 0.277582 | 0.000197273 | 2.15579e-05 | 4.29552e-06 | 1(Win) | true |
| Glaze | 3494.64 | 0.277058 | 875.742ms | 5094 | 2560 | 37974.7 | 1390.13 | 0.0384819 | 1.49022 | 5.4413 | 0.804083 | 0.000250908 | 5.0611e-05 | 1.38797e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2309 | 0.11348 | 1074ms | 8051 | 2560 | 36452.9 | 3325.26 | 0.167785 | 2.2205 | 9.74413 | 1.67706 | 0.000980759 | 4.81792e-05 | 1.89223e-05 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 1672.11 | 0.229709 | 1198.06ms | 8051 | 1280 | 142409 | 4591.84 | 0.0959653 | 3.04994 | 11.5796 | 2.34617 | 0.00397612 | 5.06536e-05 | 2.29979e-05 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1664.56 | 0.0972464 | 1201.29ms | 8051 | 2560 | 51509.4 | 4612.64 | 0.0769284 | 3.05876 | 13.2225 | 2.5772 | 0.00331413 | 3.85725e-05 | 1.1693e-05 | 2(Tie) | true |
| simdjson (ondemand) | 1291.2 | 0.0885483 | 1338.55ms | 8051 | 2560 | 70976.7 | 5946.45 | 0.0566507 | 3.93551 | 14.6793 | 2.44305 | 0.00376254 | 4.80821e-05 | 2.01353e-05 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2802.53 | 0.237399 | 1076.2ms | 8051 | 640 | 27073.1 | 2739.68 | 0.0608904 | 1.82352 | 8.32878 | 1.34927 | 0.000514494 | 2.46476e-05 | 6.98671e-06 | 1(Win) | true |
| Glaze | 2093.59 | 0.0705451 | 1166.28ms | 8051 | 4890 | 32731 | 3667.4 | 0.1013 | 2.44264 | 11.1102 | 2.11055 | 0.00307952 | 3.05567e-05 | 7.74714e-06 | 2(Loss) | true |
| Jsonifier | 1961.27 | 0.274198 | 1201.24ms | 8051 | 320 | 36872.7 | 3914.83 | 0.0114136 | 2.65448 | 10.0007 | 1.98696 | 0.00370451 | 3.72625e-05 | 1.82431e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1503.92 | 0.143433 | 1317.96ms | 8051 | 640 | 34318.5 | 5105.33 | 0.121111 | 3.39092 | 13.1701 | 2.09949 | 0.0025451 | 2.71705e-05 | 6.79263e-06 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14899.9 | 0.15484 | 795.712ms | 9255 | 4890 | 4114 | 592.37 | 0.181876 | 0.362042 | 1.46818 | 0.280065 | 0.000324613 | 1.99085e-05 | 5.56821e-06 | 1(Win) | true |
| Glaze | 3838.95 | 0.160836 | 972.707ms | 9255 | 2560 | 35005.2 | 2299.13 | 0.208187 | 1.34049 | 4.94165 | 0.853269 | 0.000296799 | 6.09468e-05 | 2.66326e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17125 | 0.14104 | 786.395ms | 9255 | 4890 | 2583.94 | 515.402 | 0.0260171 | 0.319237 | 1.40249 | 0.265478 | 0.000280045 | 1.46276e-05 | 4.90532e-06 | 1(Win) | true |
| Glaze | 4578.43 | 0.103766 | 928.9ms | 9255 | 4890 | 19567.5 | 1927.79 | 0.0690303 | 1.12692 | 4.61632 | 0.778498 | 0.000281239 | 3.14427e-05 | 1.01421e-05 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 5657.75 | 0.329108 | 774.333ms | 2889 | 1280 | 3287.73 | 486.972 | 0.0115523 | 0.979802 | 3.75389 | 0.514365 | 0.000349926 | 3.10986e-05 | 3.78591e-06 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 5552.81 | 0.29089 | 772.857ms | 2889 | 40 | 83.3276 | 496.175 | 0.0218385 | 1.00031 | 3.78435 | 0.434406 | 0.00102111 | 0 | 0 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 5547.5 | 0.193658 | 772.911ms | 2889 | 40 | 37.0026 | 496.65 | 0.31779 | 0.986033 | 3.75389 | 0.514365 | 0.000917272 | 3.46141e-05 | 0 | 2(Tie) | true |
| Glaze | 3151.28 | 0.121721 | 815.634ms | 2889 | 4890 | 5538.05 | 874.299 | 0.042297 | 1.70314 | 6.80547 | 1.23365 | 0.00035867 | 4.24004e-05 | 1.91121e-05 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5736.43 | 0.204166 | 781.038ms | 2889 | 4890 | 4702.06 | 480.293 | 0.0724393 | 0.957123 | 3.67809 | 0.496366 | 0.000437595 | 2.65445e-05 | 4.24712e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 5690.48 | 0.187536 | 782.529ms | 2889 | 4890 | 4031.58 | 484.171 | 0.124042 | 0.961589 | 3.67809 | 0.496366 | 0.000497975 | 2.89512e-05 | 7.57404e-06 | 2(Loss) | true |
| simdjson (ondemand) | 5578.16 | 0.170989 | 784.284ms | 2889 | 4890 | 3487.86 | 493.92 | 0.146311 | 0.981165 | 3.70751 | 0.416754 | 0.0010724 | 3.51803e-05 | 7.92796e-06 | 3(Loss) | true |
| Glaze | 3181.97 | 0.211346 | 822.858ms | 2889 | 30 | 100.464 | 865.867 | 0.0616333 | 1.66542 | 6.72897 | 1.21634 | 0.000369217 | 4.61521e-05 | 0 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6543.26 | 0.136853 | 787.245ms | 3808 | 640 | 369.23 | 555.013 | 0.123156 | 0.832453 | 3.18724 | 0.345326 | 0.000779198 | 2.01057e-05 | 1.23096e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 6333.02 | 0.199094 | 787.649ms | 3808 | 80 | 104.275 | 573.438 | 0.317079 | 0.854605 | 3.28624 | 0.405987 | 0.000265888 | 3.93908e-05 | 3.28256e-06 | 2(Loss) | true |
| Jsonifier | 6228.08 | 0.183543 | 789.366ms | 3808 | 4890 | 5601.06 | 583.1 | 0.152039 | 0.869687 | 3.28624 | 0.405987 | 0.000267814 | 2.57235e-05 | 5.79987e-06 | 3(Loss) | true |
| Glaze | 3378.06 | 0.15476 | 841.304ms | 3808 | 640 | 1771.55 | 1075.05 | 0.0353306 | 1.55388 | 6.48057 | 1.20746 | 0.000267939 | 9.43737e-06 | 0 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6708.94 | 0.129147 | 787.159ms | 3808 | 4890 | 2389.82 | 541.306 | 0.507341 | 0.813359 | 3.12894 | 0.331933 | 0.00103264 | 1.22442e-05 | 3.70547e-06 | 1(Win) | true |
| Jsonifier | 6513.48 | 0.122683 | 785.295ms | 3808 | 40 | 18.7154 | 557.55 | 0.0328711 | 0.846245 | 3.22873 | 0.392332 | 0.00052521 | 1.31303e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 6457.89 | 0.102099 | 787.04ms | 3808 | 160 | 52.7447 | 562.35 | 0.285332 | 0.838014 | 3.22873 | 0.392332 | 0.000262605 | 2.13367e-05 | 0 | 3(Loss) | true |
| Glaze | 3413.15 | 0.0856343 | 840.29ms | 3808 | 4890 | 4059.65 | 1064 | 0.217687 | 1.53784 | 6.42227 | 1.19433 | 0.000337896 | 1.6057e-05 | 4.88692e-06 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Glaze STATISTICAL TIE | 2390.84 | 0.486995 | 845.902ms | 2889 | 640 | 20156.9 | 1152.39 | 0.110382 | 2.22821 | 8.75597 | 1.50294 | 0.000702557 | 1.94704e-05 | 1.08169e-06 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 2374.21 | 0.280051 | 844.283ms | 2889 | 4890 | 51646.5 | 1160.46 | 0.0816445 | 2.22777 | 6.70682 | 1.13361 | 0.00141082 | 5.21688e-05 | 1.38032e-05 | 1(Tie) | true |
| Jsonifier (two-stage) | 2152.15 | 0.253191 | 859.035ms | 2889 | 4890 | 51375.3 | 1280.19 | 0.0453548 | 2.43443 | 8.06127 | 1.25961 | 0.000707217 | 7.80055e-05 | 2.6049e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1005.2 | 0.113681 | 1009.59ms | 2889 | 4890 | 47476.3 | 2740.92 | 0.232927 | 5.15355 | 16.9031 | 2.86812 | 0.000367447 | 0.000163656 | 9.09592e-05 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2641.31 | 0.273601 | 849.264ms | 2889 | 4890 | 39829 | 1043.1 | 0.206559 | 1.98192 | 6.15403 | 0.991001 | 0.0013932 | 5.98844e-05 | 1.50065e-05 | 1(Win) | true |
| Glaze | 2616.22 | 0.183114 | 853.359ms | 2889 | 4890 | 18184.3 | 1053.11 | 0.0300329 | 2.00766 | 8.16476 | 1.34995 | 0.000396186 | 6.08046e-05 | 1.1538e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2352.6 | 0.52448 | 864.259ms | 2889 | 1280 | 48291 | 1171.11 | 0.237788 | 2.22654 | 7.55002 | 1.12565 | 0.000958647 | 3.48845e-05 | 4.32676e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1047.29 | 0.104024 | 1009.73ms | 2889 | 4890 | 36621.5 | 2630.76 | 0.0826849 | 4.89353 | 16.4946 | 2.76428 | 0.000526289 | 6.25035e-05 | 1.33784e-05 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8462.46 | 0.496773 | 761.162ms | 2963 | 2560 | 7044.11 | 333.914 | 0.551791 | 0.682025 | 1.42592 | 0.226122 | 0.000416069 | 5.26019e-05 | 2.80807e-05 | 1(Win) | true |
| Glaze | 4231.06 | 0.223675 | 794.183ms | 2963 | 4890 | 10912.1 | 667.856 | 0.328394 | 1.27537 | 3.22545 | 0.484645 | 0.000346537 | 5.87339e-05 | 2.05672e-05 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10512.4 | 0.128597 | 757.048ms | 2963 | 40 | 4.77949 | 268.8 | 0.0372162 | 0.554151 | 1.30948 | 0.201822 | 0.000337496 | 8.43739e-06 | 0 | 1(Win) | true |
| Glaze | 4419.57 | 0.437191 | 799.767ms | 2963 | 1280 | 10001.3 | 639.369 | 0.176265 | 1.21915 | 2.73068 | 0.379345 | 0.000339869 | 3.40132e-05 | 4.74603e-06 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2639.26 | 0.263268 | 876.18ms | 3808 | 4890 | 64170.4 | 1375.99 | 0.302188 | 1.97422 | 6.81749 | 1.02521 | 0.000531547 | 7.22835e-05 | 3.37788e-05 | 1(Win) | true |
| Glaze | 2570.83 | 0.347236 | 879.017ms | 3808 | 640 | 15398.5 | 1412.62 | 0.265862 | 2.03521 | 8.31276 | 1.47269 | 0.000304047 | 4.88281e-05 | 3.28256e-06 | 2(Loss) | true |
| Jsonifier | 1790.44 | 0.313623 | 942.006ms | 3808 | 4890 | 197879 | 2028.33 | 0.145255 | 2.88768 | 7.09743 | 1.35084 | 0.000536702 | 6.82558e-05 | 3.11474e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1302.62 | 0.112064 | 1024.84ms | 3808 | 4890 | 47731.1 | 2787.91 | 0.440049 | 3.93256 | 13.1762 | 2.19958 | 0.000412059 | 5.27358e-05 | 1.53589e-05 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2982.78 | 0.257158 | 864.819ms | 3808 | 4890 | 47935.9 | 1217.52 | 0.331696 | 1.75052 | 6.17463 | 0.871586 | 0.000532675 | 5.00507e-05 | 1.81514e-05 | 1(Win) | true |
| Glaze | 2717.14 | 0.183251 | 878.781ms | 3808 | 4890 | 29334 | 1336.55 | 0.119876 | 1.92899 | 7.88524 | 1.36371 | 0.000467373 | 4.02768e-05 | 6.12208e-06 | 2(Loss) | true |
| Jsonifier | 1903.84 | 0.598811 | 938.577ms | 3808 | 1280 | 167002 | 1907.51 | 0.716098 | 2.68347 | 6.6415 | 1.23481 | 0.000536289 | 4.2263e-05 | 1.27199e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1351.96 | 0.142704 | 1046.27ms | 3808 | 2560 | 37616.6 | 2686.17 | 0.249611 | 3.78441 | 12.8301 | 2.11292 | 0.000511157 | 6.89338e-05 | 2.86198e-05 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9645.25 | 0.295725 | 778.859ms | 4300 | 80 | 126.467 | 425.163 | 0.0851889 | 0.567238 | 1.38419 | 0.23907 | 0.000235465 | 2.03488e-05 | 8.72093e-06 | 1(Win) | true |
| Glaze | 3131.08 | 0.262067 | 870.566ms | 4300 | 2560 | 30158.6 | 1309.71 | 1.26406 | 1.66447 | 3.75256 | 0.630465 | 0.000240643 | 6.37718e-05 | 2.36192e-05 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11507.8 | 0.0607463 | 774.013ms | 4300 | 40 | 1.87436 | 356.35 | 0.352014 | 0.499058 | 1.26814 | 0.212326 | 0.000232558 | 0 | 0 | 1(Win) | true |
| Glaze | 3575.73 | 0.18191 | 858.41ms | 4300 | 4890 | 21282.8 | 1146.84 | 0.120455 | 1.46265 | 3.20907 | 0.507209 | 0.000237029 | 2.24949e-05 | 6.3252e-06 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3683.03 | 0.106832 | 6564.83ms | 466906 | 640 | 1.06766e+07 | 120899 | 0.0739047 | 1.36386 | 6.67782 | 0.888273 | 0.00194665 | 0.00133511 | 1.47614e-05 | 1(Win) | true |
| Glaze | 2647.64 | 0.0282442 | 9081.96ms | 466906 | 2560 | 5.77616e+06 | 168178 | 0.0114861 | 1.90203 | 7.7472 | 1.47693 | 0.00255937 | 0.000865839 | 1.69626e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1749.91 | 0.146611 | 6706.22ms | 466906 | 640 | 8.90727e+07 | 254457 | 0.0792577 | 2.86126 | 12.571 | 1.66787 | 0.00406015 | 0.0824364 | 1.70839e-05 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3707.28 | 0.0798467 | 6513.39ms | 466906 | 1280 | 1.17726e+07 | 120109 | 0.317693 | 1.35454 | 6.67669 | 0.888018 | 0.00193927 | 0.00127074 | 1.7703e-06 | 1(Win) | true |
| Glaze | 2648.96 | 0.0732269 | 9039.5ms | 466906 | 320 | 4.84843e+06 | 168095 | 0.0116131 | 1.90066 | 7.74607 | 1.47668 | 0.00261375 | 0.00082526 | 8.78121e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1618.3 | 0.0808662 | 7243.24ms | 466906 | 640 | 3.16851e+07 | 275151 | 0.0619123 | 3.08771 | 12.5711 | 1.66791 | 0.00376087 | 0.10476 | 2.82511e-05 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4598.28 | 0.123692 | 7796.58ms | 699405 | 320 | 1.03015e+07 | 145055 | 0.334143 | 1.08733 | 4.43454 | 0.719483 | 0.00282578 | 0.00124399 | 3.63255e-06 | 1(Win) | true |
| Glaze | 3511.37 | 0.05964 | 5053.23ms | 699405 | 640 | 8.21411e+06 | 189956 | 0.129691 | 1.4339 | 5.22155 | 1.16244 | 0.0022027 | 0.00125834 | 4.90596e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2305.02 | 0.0830728 | 8291.25ms | 767297 | 1280 | 8.90233e+07 | 317459 | 0.160921 | 2.16696 | 8.67119 | 1.1824 | 0.00357856 | 0.0835488 | 4.48266e-05 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4606.01 | 0.059905 | 7778.97ms | 699405 | 1280 | 9.6326e+06 | 144812 | 0.0219719 | 1.08753 | 4.43374 | 0.719304 | 0.00285298 | 0.0011256 | 1.16729e-06 | 1(Win) | true |
| Glaze | 3514.3 | 0.176125 | 5043.57ms | 699405 | 80 | 8.93949e+06 | 189797 | 0.023333 | 1.43087 | 5.2208 | 1.16228 | 0.00221494 | 0.00109557 | 1.68536e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2281.98 | 0.264997 | 8385.99ms | 767297 | 80 | 5.77665e+07 | 320666 | 0.152656 | 2.18903 | 8.67078 | 1.18229 | 0.00370807 | 0.0927822 | 1.35215e-05 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3579.48 | 0.0546476 | 8991.11ms | 631514 | 2560 | 2.16426e+07 | 168253 | 0.0874699 | 1.40353 | 7.07843 | 1.22888 | 0.0043336 | 2.43691e-05 | 2.03151e-05 | 1(Win) | true |
| Glaze | 2616.18 | 0.0498894 | 6040.85ms | 631514 | 640 | 8.44166e+06 | 230205 | 0.0182256 | 1.93298 | 8.44884 | 1.51664 | 0.00230413 | 1.6456e-05 | 1.48007e-05 | 2(Loss) | true |
