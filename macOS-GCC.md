# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Just a bit of performance profiling of some JSON libraries (compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest results: (Nov 28, 2026)
#### Here are the commits we used:
----
| Jsonifier: [a1328b5](https://github.com/nihilai-collective/Jsonifier/commit/a1328b5)  
| Glaze: [283c9664](https://github.com/stephenberry/glaze/commit/283c9664)  
| simdjson: [4ba1cb3ae](https://github.com/simdjson/simdjson/commit/4ba1cb3ae)  

#### How We Benchmarked & What We Tested

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `NEON` |
| **simdjson (ondemand)** | `arm64` |
| **simdjson (reflection)** | `arm64` |
| **Glaze** | utf8: `NEON64`, escape: `NEON`, float: `NEON`, struct-skip: `NEON64` |

> **How the sampling/convergence works (Apple M2 Pro (Virtual)-NEON):**  
> The iterations grow geometrically (100 → 200 → 400 ...) up to a max of 100000.  
> Scores come from a trailing window of `max(iterations/10, 30)` (capped at 100000) over at most 5s.  
> The epoch that counts is whichever one has the lowest (RSE + epoch-over-epoch mean shift).  
> Converged means RSE ≤ 10% and mean shift ≤ 5%. Ties get called using Welch's t-test with Bessel-corrected variance.

---

##### The Test Variants
* **Standard vs. (Reused):** Standard builds, parses/serializes, and tears everything down every iteration. `(Reused)` keeps the buffer/object around across iterations and clears it outside the timed region, so you just see the raw parse/format throughput.
* **Document Sizes:** "Small" tests cap minified payloads at 5 KiB (via `GenerateSmallJson.py`), so dispatch/setup/small-alloc latency dominates instead of bulk SIMD throughput.
* **Key Traversal Order:** Standard tests go in key order, `Reverse` tests go backwards, which hits single-pass forward-only decoders (simdjson On Demand) with an $O(N^2)$ penalty that hash/DOM-indexed ones dodge.

##### A Few Details
* **simdjson (ondemand):** Includes the harness mapping layer (`include/common.hpp`). On MSVC it uses `find_field` / `find_field_unordered` instead, because of some pretty severe compiler overhead when instantiating `object::for_each`.
* **simdjson (reflection):** The C++26 static reflection API (P2996). Minified serialization only, for now.
* **Jsonifier:** We test both the fused scalar structural iteration and the two-stage indexing. The Partial tests always use two-stage parsing.
* **Summary Rows:** `*(combined)` rows are the best rank across each library's variants, they don't sum with the per-test rows.

---
*Generated with BenchmarkSuite commit: [ff0f871](https://github.com/nihilai-collective/benchmarksuite/commit/ff0f871)*

----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1653.4 | 3.80827 | 59.6562ms | 905 | 640 | 252916 | 522 | 1.31988 | 1(Win) | true |
| Glaze | 1279.39 | 1.96256 | 81.887ms | 905 | 1280 | 224361 | 674.6 | 0.207962 | 2(Loss) | true |
| simdjson (reflection) | 864.458 | 2.72155 | 111.915ms | 905 | 80 | 59065.4 | 998.4 | 0.636943 | 3(Loss) | true |
| simdjson (ondemand) | 381.093 | 0.343345 | 235.514ms | 905 | 4890 | 295669 | 2264.74 | 0.542963 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1778.82 | 1.48093 | 51.7888ms | 905 | 4890 | 252471 | 485.196 | 1.06143 | 1(Win) | true |
| Glaze | 1459.87 | 4.69171 | 60.33ms | 905 | 320 | 246196 | 591.2 | 0.407609 | 2(Loss) | true |
| simdjson (reflection) | 813.608 | 1.26898 | 101.31ms | 905 | 640 | 115973 | 1060.8 | 3.27103 | 3(Loss) | true |
| simdjson (ondemand) | 353.506 | 0.420952 | 238.498ms | 905 | 4890 | 516511 | 2441.48 | 1.76632 | 4(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1600.36 | 1.83765 | 55.4291ms | 905 | 2560 | 251436 | 539.3 | 0.12963 | 1(Win) | true |
| simdjson (reflection) | 198.582 | 0.298609 | 441.982ms | 905 | 2560 | 431188 | 4346.2 | 3.40709 | 2(Loss) | true |
| Glaze | 117.595 | 0.193277 | 734.348ms | 905 | 4890 | 983991 | 7339.4 | 0.893539 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 2745.15 | 5.86901 | 44.6039ms | 905 | 640 | 217909 | 314.4 | 5.08021 | -(Win) | false |
| simdjson (reflection) | 2441.3 | 1.96681 | 47.1278ms | 905 | 4890 | 236423 | 353.531 | 0.577891 | 2(Loss) | true |
| Glaze | 706.05 | 2.79119 | 132.404ms | 905 | 160 | 186262 | 1222.4 | 0.791557 | 3(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 794.948 | 0.624126 | 231.75ms | 1811 | 2560 | 470700 | 2172.6 | 0.676602 | 1(Win) | true |
| Glaze | 775.569 | 0.314449 | 231.443ms | 1811 | 4890 | 239775 | 2226.89 | 0.604739 | 2(Loss) | true |
| simdjson (reflection) | 268.415 | 0.16983 | 682.804ms | 1811 | 4890 | 583932 | 6434.45 | 4.38589 | 3(Loss) | true |
| simdjson (ondemand) | 247.217 | 1.21411 | 666.548ms | 1811 | 1280 | 9.20883e+06 | 6986.2 | 2.70458 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 991.221 | 2.29919 | 193.347ms | 1811 | 160 | 256783 | 1742.4 | 3.28597 | 1(Win) | true |
| Glaze | 921.614 | 1.00905 | 198.266ms | 1811 | 640 | 228846 | 1874 | 0.530786 | 2(Loss) | true |
| simdjson (ondemand) | 277.402 | 0.38961 | 624.286ms | 1811 | 1280 | 753160 | 6226 | 0.384 | 3(Loss) | true |
| simdjson (reflection) | 272.453 | 0.226042 | 657.032ms | 1811 | 2560 | 525623 | 6339.1 | 0.631721 | 4(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 303.872 | 0.257312 | 638.101ms | 1997 | 2560 | 665788 | 6267.4 | 0.697151 | 1(Win) | true |
| Jsonifier | 289.828 | 0.247592 | 683.479ms | 1997 | 2560 | 677626 | 6571.1 | 0.755926 | 2(Loss) | true |
| Glaze | 160.818 | 1.42571 | 913.984ms | 1798 | 160 | 3.69738e+06 | 10662.4 | 3.41403 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 1003.63 | 1.0077 | 208.028ms | 1997 | 320 | 117009 | 1897.6 | 0.508475 | 1(Win) | true |
| Jsonifier | 849.459 | 0.416442 | 238.527ms | 1997 | 2560 | 223162 | 2242 | 1.25958 | 2(Loss) | true |
| Glaze | 582.182 | 0.300702 | 316.53ms | 1798 | 4890 | 383570 | 2945.31 | 0.182709 | 3(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1046.71 | 0.700974 | 116.969ms | 1313 | 2560 | 180021 | 1196.3 | 0.868465 | 1(Win) | true |
| Glaze | 721.299 | 1.45274 | 173.132ms | 1313 | 320 | 203529 | 1736 | 1.40187 | 2(Loss) | true |
| simdjson (reflection) | 579.174 | 0.766722 | 219.361ms | 1313 | 1280 | 351720 | 2162 | 0.259692 | 3(Loss) | true |
| simdjson (ondemand) | 268.592 | 0.345207 | 466.921ms | 1313 | 2560 | 663045 | 4662 | 1.41262 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1494.96 | 1.92522 | 85.6719ms | 1313 | 640 | 166424 | 837.6 | 0.0956023 | 1(Win) | true |
| Glaze | 849.167 | 0.503532 | 152.636ms | 1313 | 4890 | 269592 | 1474.59 | 0.634002 | 2(Loss) | true |
| simdjson (reflection) | 746.147 | 0.506547 | 178.576ms | 1313 | 4890 | 353370 | 1678.19 | 0.19627 | 3(Loss) | true |
| simdjson (ondemand) | 304.591 | 0.282573 | 425.333ms | 1313 | 2560 | 345459 | 4111 | 0.371112 | 4(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 247.446 | 0.521611 | 506.719ms | 1313 | 1280 | 891813 | 5060.4 | 1.26434 | 1(Win) | true |
| simdjson (reflection) | 233.484 | 0.483551 | 495.528ms | 1313 | 1280 | 860817 | 5363 | 3.27177 | 2(Loss) | true |
| Glaze | 161.105 | 0.59957 | 757.341ms | 1313 | 640 | 1.38986e+06 | 7772.4 | 0.99358 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 2506.92 | 1.5113 | 59.0651ms | 1313 | 4890 | 278650 | 499.488 | 3.75736 | 1(Win) | true |
| Jsonifier | 2141.93 | 2.37365 | 68.393ms | 1313 | 1280 | 246467 | 584.6 | 1.56359 | 2(Loss) | true |
| Glaze | 1140.71 | 0.467684 | 124.135ms | 1313 | 4890 | 128881 | 1097.71 | 0.357583 | 3(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 916.242 | 1.29395 | 438.658ms | 4215 | 160 | 515622 | 4387.2 | 0.808824 | 1(Win) | true |
| simdjson (reflection) | 682.723 | 0.230551 | 593.895ms | 4215 | 1280 | 235858 | 5887.8 | 0.0101895 | 2(Loss) | true |
| Glaze | 649.451 | 0.144579 | 628.631ms | 4215 | 4890 | 391580 | 6189.44 | 0.605333 | 3(Loss) | true |
| simdjson (ondemand) | 474.216 | 0.288032 | 847.158ms | 4215 | 1280 | 763017 | 8476.6 | 0.345638 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1814.31 | 0.291496 | 322.292ms | 4215 | 4890 | 203962 | 2215.58 | 0.463726 | 1(Win) | true |
| simdjson (reflection) | 1015.09 | 0.232148 | 492.093ms | 4215 | 640 | 54087.7 | 3960 | 0.202429 | 2(Loss) | true |
| Glaze | 980.232 | 0.192406 | 511.619ms | 4215 | 2560 | 159374 | 4100.8 | 0.687785 | 3(Loss) | true |
| simdjson (ondemand) | 672.557 | 0.447147 | 692.235ms | 4215 | 320 | 228554 | 5976.8 | 0.0937835 | 4(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 859.97 | 0.188765 | 470.48ms | 4215 | 4890 | 380699 | 4674.28 | 0.125895 | 1(Win) | true |
| simdjson (reflection) | 831.125 | 0.203208 | 498.434ms | 4215 | 2560 | 247276 | 4836.5 | 0.307128 | 2(Loss) | true |
| Glaze | 554.844 | 0.496174 | 788.508ms | 4215 | 160 | 206748 | 7244.8 | 0.132685 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6520.32 | 1.14954 | 72.4838ms | 4215 | 4890 | 245593 | 616.494 | 0.242938 | 1(Win) | true |
| simdjson (reflection) | 5613.37 | 1.2561 | 81.8949ms | 4215 | 2560 | 207128 | 716.1 | 0.431034 | 2(Loss) | true |
| Glaze | 2575.93 | 0.47557 | 171.159ms | 4215 | 4890 | 269318 | 1560.5 | 0.34481 | 3(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1215.39 | 0.956673 | 96.4239ms | 1213 | 1280 | 106128 | 951.8 | 1.04034 | 1(Win) | true |
| Glaze | 856.387 | 0.72125 | 139.313ms | 1213 | 2560 | 242993 | 1350.8 | 0.670741 | 2(Loss) | true |
| simdjson (reflection) | 730.215 | 0.889255 | 160.204ms | 1213 | 1280 | 254029 | 1584.2 | 0.215081 | 3(Loss) | true |
| simdjson (ondemand) | 293.695 | 0.184005 | 396.621ms | 1213 | 2560 | 134470 | 3938.8 | 0.116923 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1727.12 | 1.02519 | 69.942ms | 1213 | 4890 | 230566 | 669.788 | 0.874924 | 1(Win) | true |
| Glaze | 1026.33 | 0.440883 | 115.469ms | 1213 | 4890 | 120755 | 1127.13 | 0.54417 | 2(Loss) | true |
| simdjson (reflection) | 876.51 | 0.517456 | 135.882ms | 1213 | 4890 | 228067 | 1319.79 | 0.341163 | 3(Loss) | true |
| simdjson (ondemand) | 311.948 | 0.237688 | 375.062ms | 1213 | 4890 | 379912 | 3708.34 | 0.336464 | 4(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 284.865 | 0.151726 | 411.186ms | 1213 | 2560 | 97186.8 | 4060.9 | 0.288946 | 1(Win) | true |
| simdjson (reflection) | 282.093 | 0.247993 | 414.367ms | 1213 | 1280 | 132381 | 4100.8 | 0.0292711 | 2(Loss) | true |
| Glaze | 180.819 | 0.444739 | 661.892ms | 1213 | 320 | 259057 | 6397.6 | 0.0375 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 2808.08 | 1.72437 | 50.3212ms | 1213 | 4890 | 246758 | 411.956 | 3.1695 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 2796.92 | 3.34273 | 51.1649ms | 1213 | 1280 | 244665 | 413.6 | 0.289296 | 1(Tie) | true |
| Glaze | 1092.6 | 0.345941 | 123.087ms | 1213 | 4890 | 65600.8 | 1058.76 | 0.370607 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1159.53 | 0.0829929 | 7897.13ms | 94653 | 1280 | 5.34319e+06 | 77849.2 | 0.208686 | 1(Tie) | true |
| Glaze STATISTICAL TIE | 1153.4 | 0.312558 | 7966.64ms | 94653 | 80 | 4.78694e+06 | 78262.4 | 0.0939542 | 1(Tie) | true |
| Jsonifier (two-stage) | 1056.27 | 0.0446815 | 8943.75ms | 94653 | 4890 | 7.12995e+06 | 85459.6 | 0.367644 | 3(Loss) | true |
| simdjson (reflection) | 936.679 | 0.145847 | 5059.91ms | 94653 | 320 | 6.32168e+06 | 96370.4 | 0.227766 | 4(Loss) | true |
| simdjson (ondemand) | 767.17 | 0.0624183 | 6167.39ms | 94653 | 1280 | 6.9043e+06 | 117664 | 0.232157 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1874.77 | 0.298008 | 7011.08ms | 94653 | 640 | 1.31767e+07 | 48148.8 | 0.128101 | 1(Win) | true |
| Glaze | 1716.59 | 0.170734 | 7172.35ms | 94653 | 320 | 2.57944e+06 | 52585.6 | 0.00304257 | 2(Loss) | true |
| Jsonifier (two-stage) | 1647.64 | 0.145392 | 7506.59ms | 94653 | 320 | 2.03038e+06 | 54786.4 | 0.0014602 | 3(Loss) | true |
| simdjson (reflection) | 1165.64 | 0.0398018 | 9695.44ms | 94653 | 4890 | 4.64573e+06 | 77440.7 | 0.0280718 | 4(Loss) | true |
| simdjson (ondemand) | 978.539 | 0.0522008 | 5751.38ms | 94653 | 2560 | 5.93617e+06 | 92247.9 | 0.414867 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12789.5 | 0.146634 | 709.441ms | 94653 | 1280 | 137102 | 7058 | 0.0509799 | 1(Win) | true |
| simdjson (reflection) | 10258.5 | 0.101457 | 896.321ms | 94653 | 4890 | 389746 | 8799.38 | 0.0217597 | 2(Loss) | true |
| Glaze | 5172.54 | 0.112985 | 1791.59ms | 94653 | 2560 | 995267 | 17451.4 | 0.145336 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13257.6 | 0.27312 | 690.045ms | 94653 | 640 | 221324 | 6808.8 | 0.140795 | 1(Win) | true |
| simdjson (reflection) | 10556.1 | 0.143919 | 859.524ms | 94653 | 2560 | 387740 | 8551.3 | 0.0198761 | 2(Loss) | true |
| Glaze | 5842.41 | 0.230637 | 1472.44ms | 94653 | 2560 | 3.25076e+06 | 15450.5 | 0.204751 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1340.61 | 0.200814 | 9036.52ms | 124597 | 320 | 1.01379e+07 | 88635.2 | 0.0252785 | 1(Win) | true |
| Glaze | 1309.19 | 0.0444592 | 9182.58ms | 124597 | 4890 | 7.96242e+06 | 90762.4 | 0.326032 | 2(Loss) | true |
| Jsonifier (two-stage) | 1259.08 | 0.249059 | 5063.36ms | 124597 | 40 | 2.20991e+06 | 94374.4 | 0.23904 | 3(Loss) | true |
| simdjson (reflection) | 1189.63 | 0.0772722 | 5313.68ms | 124597 | 1280 | 7.62514e+06 | 99884 | 0.200634 | 4(Loss) | true |
| simdjson (ondemand) | 948.869 | 0.240891 | 6364.2ms | 124597 | 320 | 2.91201e+07 | 125228 | 0.237571 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2018.69 | 0.0591155 | 7911.68ms | 124597 | 2560 | 3.09971e+06 | 58862.5 | 0.0926745 | 1(Win) | true |
| Jsonifier (two-stage) | 1842.49 | 0.124422 | 8545.79ms | 124597 | 640 | 4.12076e+06 | 64491.6 | 0.0974719 | 2(Loss) | true |
| Glaze | 1833.77 | 0.0559847 | 8372.48ms | 124597 | 4890 | 6.4354e+06 | 64798.3 | 0.0474182 | 3(Loss) | true |
| simdjson (reflection) | 1471.8 | 0.119312 | 5127.02ms | 124597 | 640 | 5.93834e+06 | 80734.4 | 0.0564496 | 4(Loss) | true |
| simdjson (ondemand) | 1241.65 | 0.123855 | 6094.63ms | 124597 | 640 | 8.99129e+06 | 95699.2 | 0.0694322 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14107.8 | 0.17187 | 926.693ms | 136037 | 1280 | 319747 | 9196 | 0.0260915 | 1(Win) | true |
| Glaze | 4396.55 | 0.258252 | 2827.83ms | 136076 | 160 | 929704 | 29516.8 | 0.141136 | 2(Loss) | true |
| simdjson (reflection) | 392.215 | 0.073326 | 8535.48ms | 136037 | 1280 | 7.52996e+07 | 330775 | 0.0866906 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14472.7 | 0.0870518 | 899.111ms | 136037 | 4890 | 297770 | 8964.14 | 0.0865392 | 1(Win) | true |
| Glaze | 5323.51 | 0.163622 | 2475.76ms | 136076 | 4890 | 7.7796e+06 | 24377.2 | 0.290737 | 2(Loss) | true |
| simdjson (reflection) | 392.345 | 0.108127 | 8645.48ms | 136037 | 320 | 4.09071e+07 | 330666 | 0.135668 | 3(Loss) | true |

----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 757.271 | 0.194187 | 8868.32ms | 2251027 | 160 | 4.84862e+09 | 2.83484e+06 | 0.300941 | 1(Win) | true |
| Glaze | 651.639 | 0.072995 | 10404.9ms | 2251027 | 40 | 2.3131e+08 | 3.29438e+06 | 0.505064 | 2(Loss) | true |
| simdjson (reflection) | 641.636 | 0.296789 | 5118.66ms | 2251027 | 80 | 7.88803e+09 | 3.34574e+06 | 0.405543 | 3(Loss) | true |
| Jsonifier (two-stage) | 624.568 | 0.0796616 | 5254.61ms | 2251027 | 40 | 2.99889e+08 | 3.43717e+06 | 0.171134 | 4(Loss) | true |
| simdjson (ondemand) | 575.082 | 0.598782 | 5712.52ms | 2251027 | 80 | 3.99696e+10 | 3.73294e+06 | 2.26814 | 5(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 921.858 | 0.211465 | 9196.61ms | 2251027 | 160 | 3.88e+09 | 2.32872e+06 | 0.457685 | 1(Win) | true |
| Glaze | 771.429 | 0.0570329 | 5134.19ms | 2251027 | 80 | 2.01517e+08 | 2.78282e+06 | 0.0736551 | 2(Loss) | true |
| simdjson (reflection) | 760.475 | 0.0963832 | 5128.61ms | 2251027 | 30 | 2.22083e+08 | 2.8229e+06 | 0.00423223 | 3(Loss) | true |
| simdjson (ondemand) | 685.165 | 0.0657268 | 5542.83ms | 2251027 | 80 | 3.39271e+08 | 3.13318e+06 | 0.0950736 | 4(Loss) | true |
| Jsonifier (two-stage) | 650.376 | 0.400405 | 5529.88ms | 2251027 | 30 | 5.24026e+09 | 3.30078e+06 | 3.16411 | 5(Loss) | true |

----
### Canada Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2398.01 | 0.0863919 | 5357.12ms | 2090326 | 320 | 1.65052e+08 | 831309 | 0.05392 | 1(Win) | true |
| simdjson (reflection) | 2140.4 | 0.0930095 | 5916.36ms | 2090326 | 160 | 1.20064e+08 | 931363 | 0.0188935 | 2(Loss) | true |
| Glaze | 1788.53 | 0.275563 | 7123.26ms | 2090234 | 160 | 1.50925e+09 | 1.11455e+06 | 0.0547247 | 3(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2394.16 | 0.311351 | 5370.48ms | 2090326 | 40 | 2.68832e+08 | 832646 | 0.094118 | 1(Win) | true |
| simdjson (reflection) | 2149.85 | 0.188711 | 5947.36ms | 2090326 | 40 | 1.2248e+08 | 927270 | 0.0253137 | 2(Loss) | true |
| Glaze | 1884.37 | 0.136051 | 6850.56ms | 2090234 | 30 | 6.21414e+07 | 1.05786e+06 | 0.315214 | 3(Loss) | true |

----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1421.51 | 0.66924 | 5319.2ms | 5373214 | 30 | 1.74604e+10 | 3.60483e+06 | 0.275351 | 1(Win) | true |
| Glaze | 1277.75 | 0.108485 | 6063.8ms | 5373214 | 30 | 5.67856e+08 | 4.0104e+06 | 0.214943 | 2(Loss) | true |
| Jsonifier (two-stage) | 1258.79 | 0.402699 | 6211.46ms | 5373214 | 40 | 1.07493e+10 | 4.0708e+06 | 0.00953876 | 3(Loss) | true |
| simdjson (reflection) | 1225.69 | 0.846468 | 6132.23ms | 5373214 | 30 | 3.75705e+10 | 4.18073e+06 | 3.03167 | 4(Loss) | true |
| simdjson (ondemand) | 1069.12 | 1.28598 | 7022.12ms | 5373214 | 40 | 1.51964e+11 | 4.79299e+06 | 0.813974 | 5(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1535.83 | 0.56231 | 5873.35ms | 5373214 | 80 | 2.81596e+10 | 3.33651e+06 | 2.68102 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1528.18 | 0.38497 | 6086.87ms | 5373214 | 80 | 1.33309e+10 | 3.35319e+06 | 0.234876 | 1(Tie) | true |
| Glaze | 1467.58 | 0.125216 | 6179.09ms | 5373214 | 30 | 5.73469e+08 | 3.49167e+06 | 0.41932 | 3(Loss) | true |
| Jsonifier (two-stage) | 1317.86 | 0.51948 | 6787.66ms | 5373214 | 80 | 3.26408e+10 | 3.88836e+06 | 1.55791 | 4(Loss) | true |
| simdjson (ondemand) | 1210.52 | 1.06765 | 7132.7ms | 5373214 | 30 | 6.12779e+10 | 4.23315e+06 | 3.22554 | 5(Loss) | true |

----
### Canada Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7390.66 | 0.186825 | 5849.19ms | 6661989 | 40 | 1.03174e+08 | 859648 | 0.195936 | 1(Win) | true |
| Glaze | 3616.86 | 0.0503391 | 5555.24ms | 6661897 | 160 | 1.25102e+08 | 1.75657e+06 | 0.264632 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 343.636 | 0.653491 | 6359.24ms | 6661989 | 30 | 4.37936e+11 | 1.84886e+07 | 18.2445 | -(Loss) | false |

----
### Canada Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5791.3 | 0.4173 | 6506.82ms | 6661989 | 320 | 6.70661e+09 | 1.09705e+06 | 1.15471 | 1(Win) | true |
| Glaze | 4121.14 | 0.101504 | 9857.57ms | 6661897 | 30 | 7.34591e+07 | 1.54163e+06 | 0.0088572 | 2(Loss) | true |
| simdjson (reflection) | 303.543 | 0.787486 | 6423.61ms | 6661989 | 30 | 8.15034e+11 | 2.09307e+07 | 4.30719 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2082.62 | 0.0868233 | 5980.85ms | 500299 | 640 | 2.53216e+07 | 229097 | 0.0289918 | 1(Win) | true |
| Jsonifier (two-stage) | 1327.34 | 0.261477 | 5038.71ms | 500299 | 30 | 2.65025e+07 | 359458 | 0.0569422 | 2(Loss) | true |
| Glaze | 1091 | 0.97765 | 5155.93ms | 500299 | 40 | 7.31198e+08 | 437325 | 1.02107 | 3(Loss) | true |
| simdjson (reflection) | 1049.55 | 0.839845 | 6081.92ms | 500299 | 160 | 2.33224e+09 | 454598 | 2.76253 | 4(Loss) | true |
| simdjson (ondemand) | 915.506 | 0.638212 | 6320.7ms | 500299 | 160 | 1.77006e+09 | 521157 | 0.222699 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2609.23 | 0.150657 | 5832.72ms | 500299 | 160 | 1.21432e+07 | 182859 | 0.0113736 | 1(Win) | true |
| Jsonifier (two-stage) | 1393.67 | 0.421044 | 10272.2ms | 500299 | 320 | 6.64883e+08 | 342350 | 0.496686 | 2(Loss) | true |
| Glaze | 1317.12 | 0.540125 | 9462.78ms | 500299 | 320 | 1.22503e+09 | 362246 | 0.298571 | 3(Loss) | true |
| simdjson (reflection) | 1159.96 | 0.295266 | 5817.59ms | 500299 | 640 | 9.44012e+08 | 411325 | 0.0278048 | 4(Loss) | true |
| simdjson (ondemand) | 1094.25 | 0.601595 | 5993.07ms | 500299 | 160 | 1.10092e+09 | 436027 | 1.88923 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8773.99 | 0.143976 | 5659.14ms | 500299 | 320 | 1.96154e+06 | 54379.2 | 0.0264877 | 1(Win) | true |
| simdjson (reflection) | 7810.82 | 0.435032 | 5847.27ms | 500299 | 640 | 4.51948e+07 | 61084.8 | 0.209107 | 2(Loss) | true |
| Glaze | 2078.54 | 0.348034 | 5964.27ms | 500299 | 320 | 2.04237e+08 | 229546 | 0.515305 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 8949.74 | 0.2013 | 6009.7ms | 500299 | 2560 | 2.94828e+07 | 53311.3 | 4.23934 | 1(Win) | true |
| Jsonifier | 8839.96 | 0.10442 | 5515.86ms | 500299 | 30 | 95290.9 | 53973.3 | 0.0791139 | 2(Loss) | true |
| Glaze | 2357.49 | 0.149778 | 5187.76ms | 500299 | 160 | 1.4702e+07 | 202386 | 0.120811 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2757.03 | 0.475289 | 9762.85ms | 1151920 | 160 | 5.73848e+08 | 398456 | 1.27491 | 1(Win) | true |
| Jsonifier (two-stage) | 2658.96 | 0.141367 | 5285.95ms | 1151920 | 80 | 2.72901e+07 | 413152 | 0.00619665 | 2(Loss) | true |
| simdjson (reflection) | 2260.51 | 0.154222 | 6618.72ms | 1151920 | 40 | 2.24689e+07 | 485978 | 0.0517726 | 3(Loss) | true |
| simdjson (ondemand) | 2125.46 | 0.22863 | 6404.49ms | 1151920 | 640 | 8.93683e+08 | 516856 | 1.30105 | 4(Loss) | true |
| Glaze | 1623.42 | 0.383828 | 8328.71ms | 1151920 | 320 | 2.15876e+09 | 676691 | 0.368552 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3690.63 | 0.180865 | 8680.89ms | 1151920 | 640 | 1.85495e+08 | 297661 | 0.0485351 | 1(Win) | true |
| Jsonifier (two-stage) | 2999.89 | 0.273695 | 5241.47ms | 1151920 | 30 | 3.01363e+07 | 366199 | 0.0349414 | 2(Loss) | true |
| simdjson (ondemand) | 2450.87 | 0.152844 | 6580.96ms | 1151920 | 30 | 1.40805e+07 | 448230 | 0.550949 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 2204.53 | 0.830955 | 7128.04ms | 1151920 | 80 | 1.37169e+09 | 498317 | 2.67615 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 2194.56 | 0.226973 | 8303.35ms | 1151920 | 30 | 3.87277e+07 | 500582 | 0.667163 | 4(Tie) | true |

----
### CitmCatalog Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17201.4 | 0.174235 | 8189.72ms | 1439562 | 4890 | 9.45615e+07 | 79811.6 | 1.02125 | 1(Win) | true |
| Glaze | 3573.21 | 0.256445 | 10048.6ms | 1439584 | 640 | 6.21332e+08 | 384218 | 1.00209 | 2(Loss) | true |
| simdjson (reflection) | 318.438 | 1.18457 | 6776.09ms | 1439562 | 30 | 7.82453e+10 | 4.31128e+06 | 2.48616 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 18501.9 | 1.0526 | 8030.12ms | 1439562 | 40 | 2.44014e+07 | 74201.6 | 0.280963 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 3483.68 | 0.516053 | 9228.77ms | 1439584 | 160 | 6.61769e+08 | 394093 | 5.96627 | -(Loss) | false |
| simdjson (reflection) | 276.246 | 1.21006 | 6850.78ms | 1439562 | 30 | 1.08493e+11 | 4.96975e+06 | 0.912116 | 3(Loss) | true |

----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1737.71 | 0.559199 | 3178.66ms | 56369 | 160 | 4.78829e+06 | 30936 | 0.818646 | 1(Win) | true |
| Glaze | 1403.57 | 0.599894 | 4022.08ms | 56369 | 80 | 4.22333e+06 | 38300.8 | 0.0584502 | 2(Loss) | true |
| Jsonifier (two-stage) | 1285.72 | 0.223689 | 4566.59ms | 56369 | 80 | 699783 | 41811.2 | 1.44818 | 3(Loss) | true |
| simdjson (ondemand) | 972.968 | 0.322502 | 5862.88ms | 56369 | 40 | 1.27001e+06 | 55251.2 | 0.921959 | 4(Loss) | true |
| simdjson (reflection) | 610.527 | 1.61119 | 8054.05ms | 56369 | 40 | 8.05049e+07 | 88051.2 | 1.28671 | 5(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2380.51 | 0.317226 | 2852.25ms | 56369 | 320 | 1.64221e+06 | 22582.4 | 0.355518 | 1(Win) | true |
| Glaze | 1889.36 | 0.345488 | 3528.85ms | 56369 | 320 | 3.09219e+06 | 28452.8 | 0.135143 | 2(Loss) | true |
| Jsonifier (two-stage) | 1575.99 | 0.113736 | 4053.42ms | 56369 | 2560 | 3.85314e+06 | 34110.5 | 0.237734 | 3(Loss) | true |
| simdjson (reflection) | 1212.59 | 0.183385 | 5156.87ms | 56369 | 2560 | 1.69208e+07 | 44333 | 0.142355 | 4(Loss) | true |
| simdjson (ondemand) | 1161.23 | 0.135751 | 5296.13ms | 56369 | 1280 | 5.05525e+06 | 46293.8 | 0.0660559 | 5(Loss) | true |

----
### Discord Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11321.2 | 0.400734 | 486.406ms | 56369 | 1280 | 463466 | 4748.4 | 0.270293 | 1(Win) | true |
| simdjson (reflection) | 9879.31 | 0.168794 | 569.557ms | 56369 | 4890 | 412525 | 5441.44 | 0.789799 | 2(Loss) | true |
| Glaze | 2662.32 | 0.154955 | 2062.57ms | 56369 | 4890 | 4.78717e+06 | 20192.1 | 0.234628 | 3(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12217.7 | 1.29311 | 464.737ms | 56369 | 80 | 258981 | 4400 | 0.0726744 | 1(Win) | true |
| simdjson (reflection) | 10509.4 | 0.379153 | 562.984ms | 56369 | 320 | 120366 | 5115.2 | 0.188029 | 2(Loss) | true |
| Glaze | 3072.29 | 0.398123 | 1819.18ms | 56369 | 320 | 1.5529e+06 | 17497.6 | 0.348688 | 3(Loss) | true |

----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1748.9 | 0.139837 | 4701.39ms | 83958 | 1280 | 5.2462e+06 | 45782.2 | 0.031026 | 1(Win) | true |
| Jsonifier | 1657.73 | 0.603629 | 4708ms | 83958 | 640 | 5.4402e+07 | 48300 | 0.785499 | 2(Loss) | true |
| Glaze | 1584.17 | 0.337049 | 5069.14ms | 83958 | 1280 | 3.71465e+07 | 50543 | 0.0605059 | 3(Loss) | true |
| simdjson (ondemand) | 1415.76 | 0.10263 | 5990.68ms | 83958 | 1280 | 4.31218e+06 | 56555 | 0.593726 | 4(Loss) | true |
| simdjson (reflection) | 1011.59 | 0.173581 | 8106.67ms | 83958 | 320 | 6.04043e+06 | 79151.2 | 0.0252745 | 5(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2378.29 | 0.177742 | 3907.89ms | 83958 | 2560 | 9.16679e+06 | 33666.5 | 0.811094 | 1(Win) | true |
| Jsonifier (two-stage) | 2144.82 | 0.60662 | 4300.78ms | 83958 | 80 | 4.10268e+06 | 37331.2 | 0.256498 | 2(Loss) | true |
| Glaze | 2067.03 | 0.318762 | 4807.61ms | 83958 | 1280 | 1.95152e+07 | 38736 | 0.945452 | 3(Loss) | true |
| simdjson (ondemand) | 1626.44 | 0.0601066 | 5409.19ms | 83958 | 4890 | 4.28157e+06 | 49229.5 | 0.0268455 | 4(Loss) | true |
| simdjson (reflection) | 1544.62 | 0.243979 | 5458.72ms | 83958 | 2560 | 4.09474e+07 | 51837.2 | 2.35363 | 5(Loss) | true |

----
### Discord Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14090.4 | 0.867102 | 696.312ms | 94370 | 80 | 245387 | 6387.2 | 0.1001 | 1(Win) | true |
| Glaze | 2351.54 | 1.35527 | 3968.22ms | 94370 | 30 | 8.0711e+06 | 38272 | 0.0892658 | 2(Loss) | true |
| simdjson (reflection) | 302.742 | 0.235931 | 7138.26ms | 94370 | 80 | 3.93535e+07 | 297277 | 0.279577 | 3(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14006.2 | 0.884072 | 656.289ms | 94370 | 80 | 258162 | 6425.6 | 0 | 1(Win) | true |
| Glaze | 2797.34 | 0.235609 | 3554.26ms | 94370 | 40 | 229838 | 32172.8 | 0.0728863 | 2(Loss) | true |
| simdjson (reflection) | 343.803 | 0.224948 | 7134.55ms | 94370 | 40 | 1.38699e+07 | 261773 | 0.226046 | 3(Loss) | true |

----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1546.34 | 0.191355 | 3264.88ms | 53331 | 2560 | 1.01408e+07 | 32890.9 | 1.08178 | 1(Win) | true |
| Glaze | 1505.9 | 0.0974073 | 3570.15ms | 53331 | 2560 | 2.77071e+06 | 33774.1 | 0.978569 | 2(Loss) | true |
| Jsonifier (two-stage) | 1454.42 | 0.108753 | 3627.18ms | 53331 | 30 | 43389.4 | 34969.6 | 0.0732601 | 3(Loss) | true |
| simdjson (reflection) | 1035.99 | 0.227328 | 5070.61ms | 53331 | 4890 | 6.09067e+07 | 49093.5 | 1.97352 | 4(Loss) | true |
| simdjson (ondemand) | 911.722 | 0.382785 | 5577.48ms | 53331 | 1280 | 5.83653e+07 | 55785 | 0.35973 | 5(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2314.11 | 0.192291 | 2903.59ms | 53331 | 320 | 571560 | 21978.4 | 0.0254861 | 1(Win) | true |
| Glaze | 1895.74 | 0.993866 | 3443.46ms | 53331 | 40 | 2.84393e+06 | 26828.8 | 0.575816 | 2(Loss) | true |
| Jsonifier (two-stage) | 1708.38 | 0.946323 | 3790.59ms | 53331 | 160 | 1.26996e+07 | 29771.2 | 0.861882 | 3(Loss) | true |
| simdjson (reflection) | 1321.61 | 0.427968 | 4601.65ms | 53331 | 1280 | 3.47203e+07 | 38483.6 | 1.08005 | 4(Loss) | true |
| simdjson (ondemand) | 1089.33 | 0.779257 | 5828.66ms | 53331 | 320 | 4.23596e+07 | 46689.6 | 0.263176 | 5(Loss) | true |

----
### Github Events Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14416.6 | 1.00231 | 401.695ms | 58581 | 80 | 120692 | 3875.2 | 1.42379 | 1(Win) | true |
| simdjson (reflection) | 9198.37 | 1.7294 | 564.388ms | 58581 | 80 | 882621 | 6073.6 | 2.4666 | 2(Loss) | true |
| Glaze | 3308.24 | 0.324077 | 1708.04ms | 58581 | 2560 | 7.66753e+06 | 16887.3 | 2.61297 | 3(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13191.5 | 0.443551 | 405.26ms | 58581 | 2560 | 903346 | 4235.1 | 0.719677 | 1(Win) | true |
| simdjson (reflection) | 11715.1 | 0.46073 | 532.101ms | 58581 | 1280 | 617903 | 4768.8 | 0.100756 | 2(Loss) | true |
| Glaze | 4027.97 | 0.375284 | 1331.41ms | 58581 | 1280 | 3.46793e+06 | 13869.8 | 0.166103 | 3(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1643.32 | 0.0605195 | 3890.49ms | 65103 | 4890 | 2.55656e+06 | 37781.5 | 0.019148 | 1(Win) | true |
| Jsonifier | 1609.41 | 0.285699 | 3862.6ms | 65103 | 1280 | 1.55488e+07 | 38577.6 | 0.648989 | 2(Loss) | true |
| simdjson (reflection) | 1481.9 | 0.220254 | 4612.32ms | 65103 | 320 | 2.72496e+06 | 41896.8 | 0.30837 | 3(Loss) | true |
| Glaze | 1446.12 | 0.303132 | 4323.91ms | 65103 | 2560 | 4.33607e+07 | 42933.5 | 1.57382 | 4(Loss) | true |
| simdjson (ondemand) | 1223.73 | 0.325134 | 5126.35ms | 65103 | 80 | 2.17695e+06 | 50736 | 0.47081 | 5(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2369.66 | 0.0813675 | 3268.11ms | 65103 | 2560 | 1.16351e+06 | 26200.8 | 0.132997 | 1(Win) | true |
| Jsonifier (two-stage) | 2157.72 | 0.252445 | 3635.27ms | 65103 | 40 | 211060 | 28774.4 | 0.0592768 | 2(Loss) | true |
| Glaze | 2075.1 | 0.134196 | 3764.51ms | 65103 | 40 | 64485.7 | 29920 | 0.106838 | 3(Loss) | true |
| simdjson (reflection) | 1734.51 | 0.428386 | 5067.69ms | 65103 | 80 | 1.88109e+06 | 35795.2 | 0.30303 | 4(Loss) | true |
| simdjson (ondemand) | 1453.31 | 0.137523 | 5276.97ms | 65103 | 640 | 2.20912e+06 | 42721.2 | 0.0834005 | 5(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15568.7 | 1.03853 | 523.041ms | 78778 | 80 | 200922 | 4825.6 | 0.919842 | 1(Win) | true |
| Glaze | 2775.14 | 1.91826 | 2591.74ms | 78778 | 40 | 1.07874e+07 | 27072 | 0.517404 | 2(Loss) | true |
| simdjson (reflection) | 393.716 | 0.206316 | 5132.28ms | 78778 | 1280 | 1.9839e+08 | 190819 | 0.631468 | 3(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15377.5 | 0.510742 | 496.079ms | 78778 | 640 | 398492 | 4885.6 | 1.46204 | 1(Win) | true |
| Glaze | 3979.27 | 0.540086 | 2105.63ms | 78778 | 40 | 415902 | 18880 | 0.292925 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 397.401 | 0.587369 | 9736.73ms | 78778 | 80 | 9.86424e+07 | 189050 | 5.04677 | -(Loss) | false |

----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1805.81 | 0.169086 | 627.733ms | 11812 | 2560 | 284812 | 6238.1 | 0.0080159 | 1(Win) | true |
| Jsonifier (two-stage) | 1304.15 | 0.117925 | 868.755ms | 11812 | 4890 | 507354 | 8637.67 | 0.00197219 | 2(Loss) | true |
| simdjson (reflection) | 1191.6 | 0.101559 | 951.527ms | 11812 | 4890 | 450743 | 9453.52 | 0.0118471 | 3(Loss) | true |
| Glaze | 966.106 | 0.539745 | 1160.17ms | 11812 | 320 | 1.26743e+06 | 11660 | 0.185593 | 4(Loss) | true |
| simdjson (ondemand) | 761.3 | 0.230709 | 1551.62ms | 11812 | 320 | 372918 | 14796.8 | 0.0216216 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2087.81 | 0.204571 | 616.487ms | 11812 | 2560 | 311882 | 5395.5 | 0.0870338 | 1(Win) | true |
| Jsonifier (two-stage) | 1436.7 | 0.123657 | 858.923ms | 11812 | 4890 | 459685 | 7840.72 | 0.0532851 | 2(Loss) | true |
| simdjson (reflection) | 1296.73 | 0.139489 | 946.637ms | 11812 | 2560 | 375900 | 8687.1 | 0.0587422 | 3(Loss) | true |
| Glaze | 1154.07 | 0.09788 | 1097.43ms | 11812 | 4890 | 446354 | 9760.93 | 0.131686 | 4(Loss) | true |
| simdjson (ondemand) | 816.701 | 0.0793367 | 1479.53ms | 11812 | 4890 | 585569 | 13793.1 | 0.0896915 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9965.97 | 0.448266 | 115.798ms | 11812 | 4890 | 125542 | 1130.33 | 1.93247 | 1(Win) | true |
| simdjson (reflection) | 9088.91 | 0.980463 | 126.72ms | 11812 | 1280 | 189015 | 1239.4 | 0.0161394 | 2(Loss) | true |
| Glaze | 1886.31 | 0.103888 | 603.437ms | 11812 | 4890 | 188219 | 5971.87 | 0.0815734 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10308.2 | 0.556964 | 112.409ms | 11812 | 2560 | 94836.4 | 1092.8 | 0.459643 | 1(Win) | true |
| simdjson (reflection) | 9322.62 | 0.504712 | 124.067ms | 11812 | 4890 | 181873 | 1208.33 | 0.068776 | 2(Loss) | true |
| Glaze | 2011.98 | 0.160427 | 564.448ms | 11812 | 4890 | 394517 | 5598.86 | 0.163897 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2316.57 | 0.236161 | 1049.96ms | 25388 | 640 | 389908 | 10451.6 | 0.17252 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 2133.26 | 0.089233 | 1142.31ms | 25388 | 4890 | 501567 | 11349.7 | 0.160102 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 2114.65 | 1.56002 | 982.866ms | 25388 | 320 | 1.02092e+07 | 11449.6 | 1.91886 | 2(Tie) | true |
| Glaze | 1708.77 | 0.161886 | 1431.44ms | 25388 | 640 | 336736 | 14169.2 | 0.171908 | 4(Loss) | true |
| simdjson (ondemand) | 1449.2 | 0.0750442 | 1695.8ms | 25388 | 4890 | 768676 | 16707.1 | 0.214045 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2929.52 | 0.273834 | 906.087ms | 25388 | 640 | 327808 | 8264.8 | 0.0290304 | 1(Win) | true |
| Jsonifier (two-stage) | 2520.81 | 0.358025 | 1127.97ms | 25388 | 320 | 378401 | 9604.8 | 0.183578 | 2(Loss) | true |
| simdjson (reflection) | 2289.67 | 0.3334 | 1255.81ms | 25388 | 320 | 397733 | 10574.4 | 0.501825 | 3(Loss) | true |
| Glaze | 1830.35 | 0.340962 | 1420.64ms | 25388 | 320 | 650953 | 13228 | 0.030248 | 4(Loss) | true |
| simdjson (ondemand) | 1550.65 | 0.179228 | 1644.2ms | 25388 | 640 | 501208 | 15614 | 0.00256174 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 19040.8 | 0.497129 | 158.67ms | 31235 | 4890 | 295773 | 1564.43 | 0.0720907 | 1(Win) | true |
| Glaze | 2961.48 | 0.100998 | 1030.21ms | 31235 | 2560 | 264198 | 10058.5 | 0.215274 | 2(Loss) | true |
| simdjson (reflection) | 342.061 | 0.136879 | 9028.46ms | 31235 | 320 | 4.54675e+06 | 87084 | 0.0395177 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 21107.6 | 0.519792 | 142.705ms | 31235 | 4890 | 263132 | 1411.25 | 0.420138 | 1(Win) | true |
| Glaze | 3317.45 | 0.116416 | 913.244ms | 31235 | 320 | 34966.2 | 8979.2 | 0.0534855 | 2(Loss) | true |
| simdjson (reflection) | 340.108 | 0.205403 | 9370.23ms | 31235 | 320 | 1.03565e+07 | 87584 | 0.0949044 | 3(Loss) | true |

----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2682.83 | 0.228998 | 3892.55ms | 108313 | 30 | 233218 | 38502.4 | 0.088574 | 1(Win) | true |
| Jsonifier (two-stage) | 1640.12 | 0.0439608 | 6431.3ms | 108313 | 4890 | 3.74843e+06 | 62980.2 | 0.1344 | 2(Loss) | true |
| Glaze | 1613.89 | 0.0427031 | 6432.91ms | 108313 | 4890 | 3.65294e+06 | 64004 | 0.102964 | 3(Loss) | true |
| simdjson (reflection) | 1375.04 | 0.0849106 | 7623.75ms | 108313 | 1280 | 5.20794e+06 | 75121.8 | 0.0183668 | 4(Loss) | true |
| simdjson (ondemand) | 1220.24 | 0.141836 | 8889.88ms | 108313 | 1280 | 1.84524e+07 | 84651.4 | 0.270305 | 5(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3149.66 | 0.0660746 | 3590.41ms | 108313 | 4890 | 2.29621e+06 | 32795.7 | 0.0256246 | 1(Win) | true |
| Jsonifier (two-stage) | 1814.48 | 0.0592515 | 6026.22ms | 108313 | 2560 | 2.91269e+06 | 56928.2 | 0.115801 | 2(Loss) | true |
| Glaze | 1770.93 | 0.106611 | 6196.37ms | 108313 | 1280 | 4.94965e+06 | 58328.4 | 0.0541467 | 3(Loss) | true |
| simdjson (reflection) | 1431.76 | 0.168399 | 7610.43ms | 108313 | 160 | 2.36166e+06 | 72145.6 | 0.27204 | 4(Loss) | true |
| simdjson (ondemand) | 1318.84 | 0.07915 | 8278.92ms | 108313 | 2560 | 9.83827e+06 | 78322.8 | 0.0909886 | 5(Loss) | true |

----
### Instruments Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13495.1 | 0.155587 | 772.557ms | 108313 | 2560 | 363078 | 7654.3 | 0.0326507 | 1(Win) | true |
| simdjson (reflection) | 9440.26 | 0.294206 | 1109.8ms | 108313 | 2560 | 2.65299e+06 | 10942 | 0.113197 | 2(Loss) | true |
| Glaze | 2079.05 | 0.138433 | 5166.25ms | 108313 | 1280 | 6.0551e+06 | 49683.8 | 0.144723 | 3(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13981.5 | 0.328758 | 781.986ms | 108313 | 640 | 377560 | 7388 | 0.0541712 | 1(Win) | true |
| simdjson (reflection) | 9677.92 | 0.124846 | 1081.99ms | 108313 | 2560 | 454553 | 10673.3 | 0.316609 | 2(Loss) | true |
| Glaze | 2259.59 | 0.0710676 | 4588.75ms | 108313 | 2560 | 2.70199e+06 | 45714.1 | 0.0574984 | 3(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2489.29 | 0.0642829 | 7355.74ms | 183677 | 2560 | 5.23829e+06 | 70368.7 | 0.14958 | 1(Win) | true |
| Jsonifier (two-stage) | 2417.94 | 0.076135 | 7471.33ms | 183677 | 4890 | 1.48763e+07 | 72445.1 | 0.677791 | 2(Loss) | true |
| Glaze | 2103.53 | 0.0580255 | 8466.34ms | 183677 | 2560 | 5.97712e+06 | 83273.5 | 0.110238 | 3(Loss) | true |
| simdjson (reflection) | 2088.68 | 0.0966395 | 8905.97ms | 183677 | 30 | 197060 | 83865.6 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 1781.5 | 0.252587 | 9533.89ms | 183677 | 80 | 4.9346e+06 | 98326.4 | 0.0553566 | 5(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 2656.32 | 0.167409 | 6906.88ms | 183677 | 320 | 3.89994e+06 | 65944 | 0.106871 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 2650.59 | 0.262211 | 6776.41ms | 183677 | 160 | 4.80449e+06 | 66086.4 | 0.501241 | 1(Tie) | true |
| Glaze | 2271.52 | 0.11603 | 8023.89ms | 183677 | 640 | 5.12383e+06 | 77114.8 | 0.0150448 | 3(Loss) | true |
| simdjson (reflection) | 2062.91 | 0.293798 | 8708.44ms | 183677 | 1280 | 7.96629e+07 | 84913 | 0.672609 | 4(Loss) | true |
| simdjson (ondemand) | 1993.26 | 0.078962 | 9173.84ms | 183677 | 1280 | 6.16352e+06 | 87880.2 | 0.137952 | 5(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 20556.2 | 0.12542 | 1006.07ms | 213963 | 2560 | 396798 | 9926.5 | 0.0754983 | 1(Win) | true |
| Glaze | 2424.4 | 0.15873 | 8583.08ms | 213963 | 320 | 5.71136e+06 | 84165.6 | 0.143321 | 2(Loss) | true |
| simdjson (reflection) | 355.492 | 0.203398 | 7504.61ms | 213963 | 40 | 5.45222e+07 | 573997 | 0.0464795 | 3(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 20989.9 | 0.131325 | 978.328ms | 213963 | 2560 | 417246 | 9721.4 | 0.0698999 | 1(Win) | true |
| Glaze | 2677.24 | 0.0589188 | 7772.2ms | 213963 | 2560 | 5.16239e+06 | 76217 | 0.0849482 | 2(Loss) | true |
| simdjson (reflection) | 320.843 | 0.301585 | 7668.11ms | 213963 | 80 | 2.94307e+08 | 635984 | 1.53827 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 617.736 | 0.235596 | 9333.49ms | 1834197 | 80 | 3.56051e+09 | 2.83167e+06 | 1.78887 | 1(Win) | true |
| simdjson (reflection) | 562.21 | 0.15051 | 9410.24ms | 1834197 | 80 | 1.75434e+09 | 3.11134e+06 | 3.03009 | 2(Loss) | true |
| Glaze | 536.03 | 0.0558131 | 10440.7ms | 1834197 | 30 | 9.95195e+07 | 3.2633e+06 | 1.25389 | 3(Loss) | true |
| Jsonifier (two-stage) | 475.32 | 0.789019 | 5734.15ms | 1834197 | 40 | 3.37252e+10 | 3.6801e+06 | 2.92555 | 4(Loss) | true |
| simdjson (ondemand) | 390.898 | 0.923312 | 6139.35ms | 1834197 | 30 | 5.12133e+10 | 4.47489e+06 | 0.612924 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 683.42 | 0.717593 | 9353.93ms | 1834197 | 40 | 1.34938e+10 | 2.55952e+06 | 10.8027 | -(Win) | false |
| simdjson (reflection) | 659.623 | 0.0707705 | 9724.73ms | 1834197 | 40 | 1.40885e+08 | 2.65186e+06 | 0.104287 | 2(Loss) | true |
| Glaze | 537.394 | 0.212953 | 5644.85ms | 1834197 | 80 | 3.84383e+09 | 3.25502e+06 | 0.881568 | 3(Loss) | true |
| simdjson (ondemand) | 523.13 | 0.0958402 | 5767.05ms | 1834197 | 80 | 8.21597e+08 | 3.34377e+06 | 0.270767 | 4(Loss) | true |
| Jsonifier (two-stage) | 500.986 | 1.05542 | 5606.79ms | 1834197 | 40 | 5.43187e+10 | 3.49157e+06 | 0.532554 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1264.16 | 0.986408 | 9069.75ms | 1922245 | 30 | 6.13829e+09 | 1.45013e+06 | 1.51917 | 1(Win) | true |
| simdjson (reflection) | 1201.89 | 0.412004 | 9099.98ms | 1922245 | 30 | 1.18472e+09 | 1.52527e+06 | 0.657754 | 2(Loss) | true |
| Glaze | 944.267 | 0.125495 | 6776.38ms | 1833577 | 30 | 1.62026e+08 | 1.85184e+06 | 0.450926 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 1306.35 | 0.0849535 | 9064.4ms | 1922245 | 30 | 4.26367e+07 | 1.4033e+06 | 0.0783823 | 1(Win) | true |
| Jsonifier | 1220.3 | 0.766348 | 8726.55ms | 1922245 | 40 | 5.30144e+09 | 1.50225e+06 | 1.40287 | 2(Loss) | true |
| Glaze | 818.28 | 0.524853 | 6795.63ms | 1833577 | 160 | 2.01275e+10 | 2.13696e+06 | 1.82245 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1946.96 | 0.135091 | 5348.15ms | 7351818 | 40 | 9.4665e+08 | 3.60112e+06 | 0.114973 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1946.07 | 0.57668 | 5469.67ms | 7351818 | 40 | 1.72665e+10 | 3.60278e+06 | 3.8226 | 1(Tie) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 1728.78 | 0.655773 | 6020.54ms | 7351818 | 30 | 2.12196e+10 | 4.05559e+06 | 7.04445 | -(Loss) | false |
| simdjson (ondemand) | 1645.2 | 0.169914 | 6542.42ms | 7351818 | 30 | 1.57302e+09 | 4.26163e+06 | 0.352371 | 4(Loss) | true |
| Glaze | 1601.26 | 0.0688583 | 6662.75ms | 7351818 | 40 | 3.63611e+08 | 4.37857e+06 | 0.0376276 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 2163.07 | 0.285674 | 5450.62ms | 7351818 | 30 | 2.57223e+09 | 3.24134e+06 | 0.19229 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 2127.71 | 0.81781 | 5512.16ms | 7351818 | 40 | 2.90488e+10 | 3.2952e+06 | 2.10048 | 1(Tie) | true |
| Jsonifier (two-stage) | 2087.9 | 0.260353 | 5517.71ms | 7351818 | 80 | 6.11487e+09 | 3.35804e+06 | 0.0131488 | 3(Loss) | true |
| simdjson (ondemand) | 1790.79 | 0.0621705 | 6485.1ms | 7351818 | 40 | 2.36988e+08 | 3.91516e+06 | 0.14359 | 4(Loss) | true |
| Glaze | 1729.14 | 0.0712441 | 6732.15ms | 7351818 | 30 | 2.50352e+08 | 4.05477e+06 | 0.123688 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6184.42 | 0.685221 | 9707.32ms | 10018896 | 160 | 1.79318e+10 | 1.54497e+06 | 0.129595 | 1(Win) | true |
| Glaze | 3300.64 | 0.40871 | 9165.63ms | 9930228 | 30 | 4.12548e+09 | 2.86921e+06 | 0.201753 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 290.094 | 0.468564 | 10018.3ms | 10018896 | 30 | 7.14533e+11 | 3.29368e+07 | 7.76898 | -(Loss) | false |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6339.18 | 0.432247 | 9502.71ms | 10018896 | 160 | 6.79139e+09 | 1.50726e+06 | 2.32326 | 1(Win) | true |
| Glaze | 2969.62 | 0.701388 | 9591.42ms | 9930228 | 30 | 1.50091e+10 | 3.18903e+06 | 1.49893 | 2(Loss) | true |
| simdjson (reflection) | 289.452 | 0.563125 | 10091.3ms | 10018896 | 30 | 1.03662e+12 | 3.30099e+07 | 1.85328 | 3(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 601.047 | 0.44058 | 9034.95ms | 1834197 | 160 | 2.63054e+10 | 2.9103e+06 | 3.91016 | 1(Win) | true |
| Glaze | 473.1 | 0.329462 | 5524.26ms | 1834197 | 30 | 4.45162e+09 | 3.69737e+06 | 0.281008 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 452.301 | 1.10795 | 5521.17ms | 1834197 | 40 | 7.34405e+10 | 3.8674e+06 | 0.013954 | 3(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 442.949 | 0.801263 | 5971.7ms | 1834197 | 40 | 4.00492e+10 | 3.94904e+06 | 0.353574 | 3(Tie) | true |
| simdjson (ondemand) | 383.504 | 0.598352 | 6987.81ms | 1834197 | 80 | 5.95876e+10 | 4.56117e+06 | 2.99046 | 5(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 663.488 | 0.876939 | 9378.13ms | 1834197 | 40 | 2.13808e+10 | 2.63641e+06 | 2.76518 | 1(Win) | true |
| Glaze | 567.598 | 0.162913 | 5313.18ms | 1834197 | 30 | 7.56209e+08 | 3.0818e+06 | 1.01195 | 2(Loss) | true |
| simdjson (reflection) | 499.205 | 1.37811 | 5687ms | 1834197 | 80 | 1.86548e+11 | 3.50402e+06 | 3.05832 | 3(Loss) | true |
| Jsonifier (two-stage) | 463.548 | 1.27604 | 5583.74ms | 1834197 | 30 | 6.95584e+10 | 3.77356e+06 | 4.32823 | 4(Loss) | true |
| simdjson (ondemand) | 399.076 | 1.06564 | 7095.25ms | 1834197 | 40 | 8.72697e+10 | 4.38319e+06 | 0.116188 | 5(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1235.67 | 0.330001 | 9631.83ms | 1922245 | 320 | 7.66992e+09 | 1.48356e+06 | 0.764527 | 1(Win) | true |
| simdjson (reflection) | 1056.71 | 0.655554 | 5426.93ms | 1922245 | 40 | 5.17352e+09 | 1.73482e+06 | 1.72596 | 2(Loss) | true |
| Glaze | 748.28 | 0.450365 | 7287.6ms | 1833577 | 160 | 1.77223e+10 | 2.33687e+06 | 0.853293 | 3(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 1202.35 | 0.490443 | 9504.06ms | 1922245 | 160 | 8.94652e+09 | 1.52468e+06 | 5.5616 | -(Win) | false |
| simdjson (reflection) | 1083.11 | 0.480161 | 5347.52ms | 1922245 | 80 | 5.28372e+09 | 1.69253e+06 | 0.485026 | 2(Loss) | true |
| Glaze | 756.393 | 1.23291 | 7117.87ms | 1833577 | 30 | 2.43718e+10 | 2.31181e+06 | 2.66676 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 1899.02 | 0.407877 | 5616.19ms | 7351818 | 80 | 1.81418e+10 | 3.69204e+06 | 2.38871 | 1(Win) | true |
| Jsonifier | 1699.23 | 1.04628 | 6068.02ms | 7351818 | 40 | 7.45482e+10 | 4.12612e+06 | 0.473662 | 2(Loss) | true |
| Jsonifier (two-stage) | 1644.47 | 0.624867 | 6301.73ms | 7351818 | 80 | 5.67808e+10 | 4.26352e+06 | 2.30031 | 3(Loss) | true |
| simdjson (ondemand) | 1593.76 | 0.173043 | 7184ms | 7351818 | 80 | 4.63599e+09 | 4.39919e+06 | 0.387164 | 4(Loss) | true |
| Glaze | 1394.33 | 1.14071 | 7957.57ms | 7351818 | 40 | 1.31604e+11 | 5.0284e+06 | 1.18358 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2044.43 | 0.603275 | 5313.14ms | 7351818 | 30 | 1.28409e+10 | 3.42944e+06 | 0.0438126 | 1(Win) | true |
| simdjson (reflection) | 1921.96 | 0.284925 | 6029.68ms | 7351818 | 80 | 8.6428e+09 | 3.64797e+06 | 2.68464 | 2(Loss) | true |
| Jsonifier (two-stage) | 1824.72 | 0.970783 | 6220.26ms | 7351818 | 30 | 4.17408e+10 | 3.84236e+06 | 1.04302 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1506.85 | 1.04733 | 7131.76ms | 7351818 | 80 | 1.89977e+11 | 4.6529e+06 | 14.4433 | -(Loss) | false |
| Glaze | 1415.65 | 0.630008 | 8063.03ms | 7351818 | 80 | 7.7886e+10 | 4.95267e+06 | 4.77918 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6755.26 | 0.641905 | 9594.64ms | 10018896 | 40 | 3.2973e+09 | 1.41442e+06 | 0.396888 | 1(Win) | true |
| Glaze | 2709.99 | 0.248056 | 5291.87ms | 9930228 | 40 | 3.00569e+09 | 3.49455e+06 | 0.420671 | 2(Loss) | true |
| simdjson (reflection) | 324.178 | 0.277395 | 9081ms | 10018896 | 30 | 2.00536e+11 | 2.94738e+07 | 0.643232 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6636.59 | 0.231708 | 9475.54ms | 10018896 | 320 | 3.56109e+09 | 1.43971e+06 | 1.21242 | 1(Win) | true |
| Glaze | 3065.15 | 0.532493 | 10196.8ms | 9930228 | 160 | 4.33074e+10 | 3.08964e+06 | 3.29059 | 2(Loss) | true |
| simdjson (reflection) | 326.186 | 0.0934611 | 9048.28ms | 10018896 | 30 | 2.2485e+10 | 2.92924e+07 | 1.65739 | 3(Loss) | true |

----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1072.99 | 0.608905 | 5699.83ms | 461466 | 40 | 2.49486e+08 | 410150 | 0.633644 | 1(Win) | true |
| Jsonifier (two-stage) | 902.269 | 0.242469 | 6607.31ms | 461466 | 640 | 8.95157e+08 | 487757 | 0.598256 | 2(Loss) | true |
| simdjson (reflection) | 817.935 | 0.152554 | 7052.99ms | 461466 | 40 | 2.69496e+07 | 538048 | 0.0468083 | 3(Loss) | true |
| Glaze | 798.929 | 0.277468 | 7409.89ms | 461466 | 40 | 9.34434e+07 | 550848 | 0.100019 | 4(Loss) | true |
| simdjson (ondemand) | 709.413 | 0.0635382 | 8007.86ms | 461466 | 640 | 9.94332e+07 | 620355 | 0.0121236 | 5(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1634.16 | 0.92065 | 10026.8ms | 461466 | 40 | 2.45889e+08 | 269306 | 2.38532 | 1(Win) | true |
| Jsonifier (two-stage) | 1367.37 | 0.162548 | 5595.17ms | 461466 | 40 | 1.09478e+07 | 321850 | 0.0774917 | 2(Loss) | true |
| Glaze | 1035.61 | 0.182531 | 7613.82ms | 461466 | 80 | 4.81332e+07 | 424954 | 0.0874271 | 3(Loss) | true |
| simdjson (reflection) | 986.653 | 0.113066 | 6961.2ms | 461466 | 640 | 1.62776e+08 | 446042 | 0.231905 | 4(Loss) | true |
| simdjson (ondemand) | 878.355 | 0.117989 | 7642.52ms | 461466 | 320 | 1.11833e+08 | 501037 | 0.010537 | 5(Loss) | true |

----
### Random Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12245.6 | 0.0850266 | 3632.96ms | 461466 | 2560 | 2.39038e+06 | 35938.4 | 0.118677 | 1(Win) | true |
| simdjson (reflection) | 8987.26 | 0.109219 | 5030.47ms | 461466 | 640 | 1.83064e+06 | 48968 | 0.434309 | 2(Loss) | true |
| Glaze | 2390.65 | 0.0937154 | 9845.51ms | 461466 | 640 | 1.9048e+07 | 184087 | 0.0269365 | 3(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12378.7 | 0.193578 | 3636.25ms | 461466 | 80 | 378906 | 35552 | 0.018005 | 1(Win) | true |
| simdjson (reflection) | 8776.29 | 0.0867685 | 4987.94ms | 461466 | 4890 | 9.25744e+06 | 50145.1 | 0.0375301 | 2(Loss) | true |
| Glaze | 2286.78 | 0.523653 | 9248.82ms | 461466 | 640 | 6.49978e+08 | 192449 | 0.190647 | 3(Loss) | true |

----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1542.75 | 0.0899287 | 5827.5ms | 728486 | 640 | 1.0496e+08 | 450324 | 0.248884 | 1(Win) | true |
| Jsonifier (two-stage) | 1367.63 | 0.13332 | 6693.35ms | 728486 | 80 | 3.66932e+07 | 507987 | 0.174816 | 2(Loss) | true |
| simdjson (reflection) | 1205.77 | 0.116083 | 7358.63ms | 728486 | 640 | 2.86309e+08 | 576178 | 0.241562 | 3(Loss) | true |
| Glaze | 1144.76 | 0.0876341 | 7802.31ms | 728486 | 640 | 1.81024e+08 | 606883 | 0.00935842 | 4(Loss) | true |
| simdjson (ondemand) | 1059.35 | 0.0955706 | 8550.91ms | 728486 | 320 | 1.25708e+08 | 655817 | 0.0386544 | 5(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2204.51 | 0.235289 | 5296.94ms | 728486 | 30 | 1.64947e+07 | 315145 | 0.280815 | 1(Win) | true |
| Jsonifier (two-stage) | 1873.6 | 0.12335 | 6047.08ms | 728486 | 640 | 1.3389e+08 | 370804 | 0.30178 | 2(Loss) | true |
| Glaze | 1462.09 | 0.143156 | 7491.11ms | 728486 | 40 | 1.85087e+07 | 475168 | 0.235152 | 3(Loss) | true |
| simdjson (reflection) | 1453.7 | 0.173947 | 7369.82ms | 728486 | 30 | 2.07324e+07 | 477909 | 0.019645 | 4(Loss) | true |
| simdjson (ondemand) | 1293.14 | 0.103122 | 8182.49ms | 728486 | 640 | 1.9644e+08 | 537247 | 0.0537266 | 5(Loss) | true |

----
### Random Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 18604 | 0.0935557 | 4447.79ms | 837491 | 40 | 64527.8 | 42931.2 | 0.158762 | 1(Win) | true |
| Glaze | 2737.29 | 0.151098 | 7582.11ms | 837491 | 160 | 3.10995e+07 | 291782 | 0.00329023 | 2(Loss) | true |
| simdjson (reflection) | 356.822 | 0.12863 | 6992.88ms | 837491 | 160 | 1.32636e+09 | 2.23836e+06 | 0.519669 | 3(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 18581 | 0.127263 | 4409.53ms | 837491 | 640 | 1.91517e+06 | 42984.4 | 0.0512076 | 1(Win) | true |
| Glaze | 2966.9 | 0.262862 | 7300.67ms | 837491 | 30 | 1.50221e+07 | 269201 | 0.136119 | 2(Loss) | true |
| simdjson (reflection) | 356.702 | 0.128112 | 7059.09ms | 837491 | 160 | 1.31658e+09 | 2.23911e+06 | 1.23087 | 3(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 4361.31 | 0.727299 | 5129.39ms | 466906 | 320 | 1.76441e+08 | 102097 | 0.046252 | 1(Win) | true |
| Jsonifier | 4210.58 | 0.227867 | 10299.5ms | 466906 | 4890 | 2.83953e+08 | 105752 | 0.28565 | 2(Loss) | true |
| simdjson (reflection) | 4018.03 | 0.130138 | 5736.86ms | 466906 | 640 | 1.33114e+07 | 110820 | 0.292861 | 3(Loss) | true |
| simdjson (ondemand) | 3495.06 | 0.759564 | 6607.73ms | 466906 | 80 | 7.4915e+07 | 127402 | 2.76444 | 4(Loss) | true |
| Glaze | 2543.98 | 0.110165 | 9247.28ms | 466906 | 320 | 1.18978e+07 | 175031 | 0.0718102 | 5(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 4341.89 | 1.08401 | 5018.82ms | 466906 | 80 | 9.88691e+07 | 102554 | 2.60743 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 4175.13 | 1.28461 | 5368.36ms | 466906 | 30 | 5.63094e+07 | 106650 | 0.809524 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 4087.56 | 0.349276 | 5819.66ms | 466906 | 40 | 5.79065e+06 | 108934 | 0.00979087 | 2(Tie) | true |
| simdjson (ondemand) | 3943.23 | 0.652487 | 5942ms | 466906 | 30 | 1.62861e+07 | 112922 | 0.0831947 | 4(Loss) | true |
| Glaze | 2579.12 | 0.216318 | 9167.59ms | 466906 | 160 | 2.23162e+07 | 172646 | 0.0666815 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 4834.91 | 0.0596687 | 6482.64ms | 631514 | 2560 | 1.41424e+07 | 124565 | 0.163023 | 1(Win) | true |
| Jsonifier | 4770.99 | 0.348346 | 6603.98ms | 631514 | 1280 | 2.47502e+08 | 126233 | 0.594542 | 2(Loss) | true |
| Jsonifier (two-stage) | 4226.49 | 0.349272 | 7168.45ms | 631514 | 2560 | 6.34126e+08 | 142496 | 0.380045 | 3(Loss) | true |
| simdjson (ondemand) | 4100.12 | 0.876422 | 7658.76ms | 631514 | 160 | 2.65167e+08 | 146888 | 0.389523 | 4(Loss) | true |
| Glaze | 2891.32 | 0.574805 | 5331.1ms | 631514 | 30 | 4.30067e+07 | 208299 | 0.0777764 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 4899.22 | 0.154822 | 6503.78ms | 631514 | 160 | 5.79561e+06 | 122930 | 0.0924961 | 1(Win) | true |
| Jsonifier (two-stage) | 4743.86 | 0.297697 | 6615.12ms | 631514 | 2560 | 3.65671e+08 | 126956 | 0.79129 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 4506.63 | 0.583309 | 7436.83ms | 631514 | 80 | 4.86127e+07 | 133638 | 0.370121 | 3(Tie) | true |
| Jsonifier STATISTICAL TIE | 4466.31 | 1.69501 | 6717.59ms | 631514 | 80 | 4.17932e+08 | 134845 | 1.51041 | 3(Tie) | true |
| Glaze | 3076.87 | 0.22152 | 5227.47ms | 631514 | 640 | 1.20325e+08 | 195738 | 1.45503 | 5(Loss) | true |

----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2203.3 | 0.281727 | 6319.8ms | 466906 | 30 | 9.72502e+06 | 202095 | 0.0506436 | 1(Win) | true |
| Glaze | 1669.69 | 0.0785018 | 6992.5ms | 466906 | 640 | 2.80497e+07 | 266682 | 0.0979981 | 2(Loss) | true |
| Jsonifier (two-stage) | 1455.8 | 0.347229 | 7873.31ms | 466906 | 1280 | 1.44377e+09 | 305864 | 1.46642 | 3(Loss) | true |
| simdjson (reflection) | 1351.54 | 0.0925815 | 8679.38ms | 466906 | 640 | 5.95427e+07 | 329458 | 0.214317 | 4(Loss) | true |
| simdjson (ondemand) | 974.793 | 0.480204 | 5673.56ms | 466906 | 80 | 3.84925e+08 | 456790 | 0.20568 | 5(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2650.86 | 0.960989 | 5226.56ms | 466906 | 40 | 1.04228e+08 | 167974 | 0.190869 | 1(Win) | true |
| Glaze | 2108.44 | 0.240016 | 6973.36ms | 466906 | 40 | 1.02772e+07 | 211187 | 0.20447 | 2(Loss) | true |
| Jsonifier (two-stage) | 1856.18 | 1.3804 | 6968.34ms | 466906 | 30 | 3.28968e+08 | 239889 | 0.797516 | 3(Loss) | true |
| simdjson (reflection) | 1498.33 | 0.0969158 | 8587.41ms | 466906 | 320 | 2.6545e+07 | 297182 | 0.18245 | 4(Loss) | true |
| simdjson (ondemand) | 1073.4 | 0.139246 | 5779.29ms | 466906 | 640 | 2.13542e+08 | 414829 | 0.234476 | 5(Loss) | true |

----
### Twitter Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13318.8 | 0.294697 | 3288.69ms | 475954 | 2560 | 2.58221e+07 | 34080.1 | 0.0419776 | 1(Win) | true |
| simdjson (reflection) | 11356.7 | 0.647125 | 3949.47ms | 475954 | 40 | 2.67584e+06 | 39968 | 1.06147 | 2(Loss) | true |
| Glaze | 3922.71 | 0.370287 | 5728.13ms | 475954 | 80 | 1.46867e+07 | 115712 | 0.0996567 | 3(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14977.8 | 0.171166 | 3329.05ms | 475954 | 640 | 1.72206e+06 | 30305.2 | 0.0171617 | 1(Win) | true |
| simdjson (reflection) | 12236.8 | 0.149039 | 3698.29ms | 475954 | 2560 | 7.82415e+06 | 37093.5 | 0.0773122 | 2(Loss) | true |
| Glaze | 4527.68 | 0.157194 | 5255.63ms | 475954 | 160 | 3.97346e+06 | 100251 | 0.103632 | 3(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2388.76 | 0.157034 | 6532.58ms | 631514 | 80 | 1.25399e+07 | 252122 | 0.162198 | 1(Win) | true |
| Jsonifier (two-stage) | 2020.53 | 0.263911 | 7616.1ms | 631514 | 30 | 1.8564e+07 | 298069 | 0.631543 | 2(Loss) | true |
| Glaze | 1951.11 | 0.171447 | 8007.74ms | 631514 | 80 | 2.24054e+07 | 308675 | 0.154706 | 3(Loss) | true |
| simdjson (reflection) | 1718.8 | 0.31351 | 9101.64ms | 631514 | 30 | 3.62027e+07 | 350396 | 0.153191 | 4(Loss) | true |
| simdjson (ondemand) | 1339.29 | 0.200203 | 5765.09ms | 631514 | 160 | 1.29682e+08 | 449686 | 0.301203 | 5(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3064.33 | 0.112656 | 5975.73ms | 631514 | 640 | 3.13749e+07 | 196538 | 0.0854065 | 1(Win) | true |
| Jsonifier (two-stage) | 2586.81 | 0.267951 | 7048.09ms | 631514 | 40 | 1.55672e+07 | 232819 | 0.111914 | 2(Loss) | true |
| Glaze | 2377.69 | 0.0655463 | 7380.45ms | 631514 | 1280 | 3.52828e+07 | 253296 | 0.220465 | 3(Loss) | true |
| simdjson (reflection) | 1905.26 | 0.164427 | 9086.12ms | 631514 | 80 | 2.16119e+07 | 316102 | 0.137867 | 4(Loss) | true |
| simdjson (ondemand) | 1396.77 | 0.157215 | 6018.45ms | 631514 | 40 | 1.8381e+07 | 431181 | 0.0296771 | 5(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16748.5 | 0.114915 | 4165.33ms | 716365 | 80 | 175775 | 40790.4 | 0.0235294 | 1(Win) | true |
| Glaze | 4018.61 | 0.0607556 | 9049.5ms | 716365 | 2560 | 2.73104e+07 | 170004 | 0.0912089 | 2(Loss) | true |
| simdjson (reflection) | 433.417 | 0.183667 | 5045.49ms | 716365 | 160 | 1.34103e+09 | 1.57626e+06 | 0.437899 | 3(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16878.3 | 0.148408 | 4237.23ms | 716365 | 80 | 288680 | 40476.8 | 0.00790639 | 1(Win) | true |
| Glaze | 4642.38 | 0.0622908 | 7673.98ms | 716365 | 2560 | 2.15117e+07 | 147161 | 0.0490859 | 2(Loss) | true |
| simdjson (reflection) | 437.13 | 0.0853606 | 9997.9ms | 716365 | 40 | 7.11905e+07 | 1.56287e+06 | 0.176456 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1591.52 | 0.471772 | 161.71ms | 2632 | 4890 | 270719 | 1577.15 | 0.0792913 | 1(Win) | true |
| Jsonifier (two-stage) | 1429.18 | 0.379045 | 177.743ms | 2632 | 4890 | 216714 | 1756.3 | 0.34831 | 2(Loss) | true |
| Glaze | 1268.39 | 0.214795 | 201.735ms | 2632 | 4890 | 88353.9 | 1978.95 | 0.438921 | 3(Loss) | true |
| simdjson (reflection) | 1001.51 | 0.424586 | 266.784ms | 2632 | 4890 | 553735 | 2506.29 | 0.355855 | 4(Loss) | true |
| simdjson (ondemand) | 893.303 | 0.253084 | 283.954ms | 2632 | 4890 | 247294 | 2809.87 | 0.241691 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2056.54 | 0.513979 | 148.917ms | 2632 | 4890 | 192440 | 1220.53 | 1.1879 | 1(Win) | true |
| Glaze | 1912.87 | 0.724136 | 158.126ms | 2632 | 2560 | 231143 | 1312.2 | 0.0304925 | 2(Loss) | true |
| Jsonifier (two-stage) | 1848.77 | 0.710782 | 166.441ms | 2632 | 2560 | 238408 | 1357.7 | 0.0221011 | 3(Loss) | true |
| simdjson (reflection) | 1283.27 | 0.76886 | 230.892ms | 2632 | 640 | 144748 | 1956 | 0.741656 | 4(Loss) | true |
| simdjson (ondemand) | 1186.35 | 0.490204 | 240.543ms | 2632 | 1280 | 137693 | 2115.8 | 0.122734 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8526.81 | 2.22339 | 32.32ms | 2632 | 4890 | 209478 | 294.374 | 0.77844 | 1(Win) | true |
| simdjson (reflection) DID NOT CONVERGE | 6728.36 | 1.95587 | 38.986ms | 2632 | 4890 | 260342 | 373.058 | 6.40573 | -(Loss) | false |
| Glaze | 2808 | 0.844747 | 87.7819ms | 2632 | 2560 | 145973 | 893.9 | 1.97353 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9450.57 | 4.66697 | 30.817ms | 2632 | 1280 | 196669 | 265.6 | 3.90738 | 1(Win) | true |
| simdjson (reflection) | 7759.11 | 2.87071 | 35.6989ms | 2632 | 2560 | 220784 | 323.5 | 0.949173 | 2(Loss) | true |
| Glaze | 3126.18 | 0.742461 | 83.5891ms | 2632 | 4890 | 173780 | 802.919 | 0.327203 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1666.61 | 0.32246 | 196.171ms | 3370 | 2560 | 98988.9 | 1928.4 | 0.577439 | 1(Win) | true |
| Jsonifier | 1637.06 | 0.609324 | 212.629ms | 3370 | 320 | 45790.5 | 1963.2 | 0.327065 | 2(Loss) | true |
| Glaze | 1473.72 | 1.02605 | 226.511ms | 3370 | 320 | 160222 | 2180.8 | 1.16026 | 3(Loss) | true |
| simdjson (reflection) | 1290.3 | 0.91287 | 247.446ms | 3370 | 640 | 330884 | 2490.8 | 0.176963 | 4(Loss) | true |
| simdjson (ondemand) | 1109.03 | 0.203927 | 293.553ms | 3370 | 4890 | 170779 | 2897.93 | 0.418183 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 2156.54 | 0.508785 | 179.66ms | 3370 | 4890 | 281141 | 1490.3 | 0.214978 | 1(Tie) | true |
| Glaze STATISTICAL TIE | 2127.25 | 0.505315 | 181.92ms | 3370 | 4890 | 285008 | 1510.82 | 0.0384535 | 1(Tie) | true |
| Jsonifier (two-stage) | 2073.01 | 0.502757 | 185.855ms | 3370 | 4890 | 297086 | 1550.34 | 0.222663 | 3(Loss) | true |
| simdjson (reflection) | 1723.08 | 0.384701 | 217.831ms | 3370 | 2560 | 131807 | 1865.2 | 0.723866 | 4(Loss) | true |
| simdjson (ondemand) | 1334.23 | 0.756087 | 277.06ms | 3370 | 2560 | 849150 | 2408.8 | 0.429894 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10349.2 | 2.79128 | 36.3351ms | 3643 | 2560 | 224776 | 335.7 | 0.326603 | 1(Win) | true |
| Glaze | 3901.23 | 0.504741 | 92.6182ms | 3682 | 4890 | 100928 | 900.083 | 0.664007 | 2(Loss) | true |
| simdjson (reflection) | 369.497 | 0.149348 | 941.2ms | 3643 | 2560 | 504821 | 9402.6 | 0.253764 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11593.9 | 2.21749 | 32.716ms | 3643 | 4890 | 215921 | 299.661 | 2.29496 | 1(Win) | true |
| Glaze | 4610.52 | 0.821926 | 80.6602ms | 3682 | 4890 | 191621 | 761.613 | 0.207929 | 2(Loss) | true |
| simdjson (reflection) | 374.5 | 0.184904 | 949.487ms | 3643 | 1280 | 376631 | 9277 | 0.139935 | 3(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 743.978 | 0.133632 | 599.733ms | 4630 | 2560 | 161028 | 5935 | 0.131251 | 1(Win) | true |
| Jsonifier (two-stage) | 613.807 | 0.114189 | 723.355ms | 4630 | 4890 | 329957 | 7193.65 | 0.156666 | 2(Loss) | true |
| simdjson (reflection) | 592.32 | 0.212469 | 754.015ms | 4630 | 1280 | 321107 | 7454.6 | 0.00804937 | 3(Loss) | true |
| Glaze | 532.118 | 0.201221 | 848.19ms | 4630 | 1280 | 356864 | 8298 | 0.0963159 | 4(Loss) | true |
| simdjson (ondemand) | 482.802 | 0.633786 | 1009.95ms | 4630 | 40 | 134391 | 9145.6 | 0.163551 | 5(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 912.598 | 0.641871 | 600.646ms | 4630 | 160 | 154319 | 4838.4 | 0.19802 | 1(Win) | true |
| Jsonifier (two-stage) | 729.692 | 0.43392 | 745.713ms | 4630 | 80 | 55156 | 6051.2 | 0.473684 | 2(Loss) | true |
| simdjson (reflection) | 688.74 | 0.329936 | 750.27ms | 4630 | 1280 | 572691 | 6411 | 0.334919 | 3(Loss) | true |
| Glaze | 611.027 | 0.10535 | 833.778ms | 4630 | 4890 | 283414 | 7226.37 | 0.122012 | 4(Loss) | true |
| simdjson (ondemand) | 540.401 | 0.123 | 928.443ms | 4630 | 2560 | 258570 | 8170.8 | 0.390711 | 5(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2356.7 | 0.396763 | 190.58ms | 4630 | 2560 | 141467 | 1873.6 | 0.159864 | 1(Win) | true |
| simdjson (reflection) | 2114.91 | 0.287764 | 212.477ms | 4630 | 2560 | 92404.1 | 2087.8 | 0.230437 | 2(Loss) | true |
| Glaze | 1492.69 | 0.435274 | 291.694ms | 4630 | 2560 | 424415 | 2958.1 | 0.986618 | 3(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2386.42 | 0.318988 | 187.028ms | 4630 | 4890 | 170344 | 1850.27 | 0.453678 | 1(Win) | true |
| simdjson (reflection) | 2143.45 | 0.61715 | 209.564ms | 4630 | 640 | 103442 | 2060 | 0.232468 | 2(Loss) | true |
| Glaze | 1986.7 | 0.288295 | 225.654ms | 4630 | 4890 | 200762 | 2222.54 | 0.272533 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1540.54 | 0.306535 | 756.27ms | 11579 | 320 | 154492 | 7168 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 1426.32 | 0.119296 | 782.517ms | 11579 | 4890 | 417128 | 7742.04 | 0.0224385 | 2(Loss) | true |
| simdjson (reflection) | 1139.81 | 0.23965 | 925.101ms | 11579 | 4890 | 2.63599e+06 | 9688.11 | 1.05088 | 3(Loss) | true |
| simdjson (ondemand) | 1114.6 | 0.165588 | 1028.93ms | 11579 | 320 | 86121.3 | 9907.2 | 0.0484262 | 4(Loss) | true |
| Glaze | 1093.58 | 0.0961365 | 1020.78ms | 11579 | 2560 | 241247 | 10097.7 | 0.03267 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1796.91 | 0.112019 | 729.282ms | 11579 | 4890 | 231727 | 6145.31 | 0.297185 | 1(Win) | true |
| Jsonifier (two-stage) | 1671.3 | 0.434777 | 779.521ms | 11579 | 320 | 264069 | 6607.2 | 0.0121065 | 2(Loss) | true |
| simdjson (reflection) | 1394.72 | 0.367428 | 914.616ms | 11579 | 1280 | 1.08323e+06 | 7917.4 | 0.0782473 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1231.55 | 0.614352 | 1134.62ms | 11579 | 160 | 485502 | 8966.4 | 0.250447 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 1219.83 | 0.161472 | 1015.41ms | 11579 | 1280 | 273495 | 9052.6 | 0.24903 | 4(Tie) | true |

----
### Canada Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7374.1 | 0.333333 | 200.102ms | 14795 | 2560 | 104138 | 1913.4 | 0.48887 | 1(Win) | true |
| Glaze | 3101.15 | 0.462656 | 482.469ms | 14795 | 1280 | 567168 | 4549.8 | 1.22364 | 2(Loss) | true |
| simdjson (reflection) | 337.341 | 0.162641 | 4249.68ms | 14795 | 640 | 2.96165e+06 | 41826 | 0.159455 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6730.32 | 0.321444 | 202.481ms | 14795 | 4890 | 222064 | 2096.43 | 0.393151 | 1(Win) | true |
| Glaze | 3682.01 | 0.181235 | 404.234ms | 14795 | 4890 | 235861 | 3832.04 | 0.644584 | 2(Loss) | true |
| simdjson (reflection) | 337.015 | 0.197371 | 4262.9ms | 14795 | 320 | 2.18497e+06 | 41866.4 | 0.0554451 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1163.75 | 0.443608 | 268.268ms | 3223 | 2560 | 351432 | 2641.2 | 0.997076 | 1(Win) | true |
| Jsonifier (two-stage) | 1018.59 | 0.211882 | 308.462ms | 3223 | 640 | 26163.1 | 3017.6 | 0.0795967 | 2(Loss) | true |
| Glaze | 946.567 | 0.787723 | 337.259ms | 3223 | 320 | 209370 | 3247.2 | 0.0739645 | 3(Loss) | true |
| simdjson (reflection) | 886.813 | 0.638796 | 351.378ms | 3223 | 640 | 313734 | 3466 | 0.266142 | 4(Loss) | true |
| simdjson (ondemand) | 849.133 | 0.405721 | 385.915ms | 3223 | 1280 | 276080 | 3619.8 | 0.55 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1885.92 | 0.452983 | 219.571ms | 3223 | 4890 | 266531 | 1629.81 | 0.786242 | 1(Win) | true |
| Jsonifier (two-stage) | 1301.42 | 0.694644 | 289.9ms | 3223 | 1280 | 344525 | 2361.8 | 0.24618 | 2(Loss) | true |
| Glaze | 1241.9 | 0.440096 | 306.229ms | 3223 | 2560 | 303729 | 2475 | 0.373104 | 3(Loss) | true |
| simdjson (reflection) | 1103.41 | 0.240311 | 333.814ms | 3223 | 4890 | 219131 | 2785.64 | 0.238791 | 4(Loss) | true |
| simdjson (ondemand) | 1031.11 | 0.219938 | 367.608ms | 3223 | 4890 | 210195 | 2980.96 | 1.11806 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8942.95 | 2.74298 | 37.1661ms | 3223 | 2560 | 227534 | 343.7 | 0.555881 | 1(Win) | true |
| simdjson (reflection) | 6773.23 | 2.2962 | 44.8771ms | 3223 | 2560 | 277963 | 453.8 | 3.24094 | 2(Loss) | true |
| Glaze | 1956.77 | 1.26018 | 173.597ms | 3223 | 640 | 250778 | 1570.8 | 3.03704 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 9475.01 | 4.05314 | 36.108ms | 3223 | 1280 | 221286 | 324.4 | 2.75779 | 1(Win) | true |
| Jsonifier | 8581.16 | 1.97395 | 39.6119ms | 3223 | 4890 | 244460 | 358.191 | 0.086306 | 2(Loss) | true |
| Glaze | 2176.71 | 0.518683 | 144.668ms | 3223 | 4890 | 262322 | 1412.08 | 0.425534 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1862.87 | 0.230079 | 301.456ms | 5839 | 2560 | 121089 | 2989.2 | 0.201126 | 1(Win) | true |
| Jsonifier (two-stage) | 1663.47 | 0.231736 | 346.062ms | 5839 | 4890 | 294269 | 3347.53 | 0.0725598 | 2(Loss) | true |
| simdjson (reflection) | 1489.7 | 0.542211 | 377.225ms | 5839 | 640 | 262903 | 3738 | 0.0107021 | 3(Loss) | true |
| simdjson (ondemand) | 1403.71 | 0.291655 | 402.852ms | 5839 | 1280 | 171346 | 3967 | 1.08552 | 4(Loss) | true |
| Glaze | 1354.18 | 0.148408 | 415.227ms | 5839 | 4890 | 182114 | 4112.07 | 0.18516 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2473.54 | 0.306326 | 282.265ms | 5839 | 4890 | 232549 | 2251.23 | 0.174852 | 1(Win) | true |
| Jsonifier (two-stage) | 2107.21 | 0.552948 | 324.36ms | 5839 | 1280 | 273301 | 2642.6 | 0.773506 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1803.04 | 0.23294 | 362.504ms | 5839 | 2560 | 132493 | 3088.4 | 0.416179 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1781.12 | 0.626487 | 399.94ms | 5839 | 320 | 122762 | 3126.4 | 0.256542 | 3(Tie) | true |
| Glaze | 1670.05 | 0.225929 | 390.713ms | 5839 | 4890 | 277506 | 3334.33 | 0.106817 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16135.2 | 1.7236 | 43.5981ms | 6938 | 4890 | 244286 | 410.071 | 0.395636 | 1(Win) | true |
| Glaze | 2669.11 | 0.31224 | 254.486ms | 6960 | 4890 | 294829 | 2486.81 | 0.376081 | 2(Loss) | true |
| simdjson (reflection) | 346.949 | 0.10577 | 1921.03ms | 6938 | 1280 | 520802 | 19070.8 | 0.00419507 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17988.5 | 1.92237 | 40.7831ms | 6938 | 4890 | 244490 | 367.823 | 0.388459 | 1(Win) | true |
| Glaze | 2879.19 | 0.316343 | 234.007ms | 6960 | 4890 | 260078 | 2305.36 | 0.386244 | 2(Loss) | true |
| simdjson (reflection) | 343.902 | 0.0766235 | 2016.4ms | 6938 | 4890 | 1.06276e+06 | 19239.8 | 0.518729 | 3(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1763.15 | 0.281182 | 266.122ms | 4857 | 4890 | 266834 | 2627.11 | 0.0564967 | 1(Win) | true |
| Jsonifier (two-stage) | 1376.44 | 0.351018 | 344.177ms | 4857 | 2560 | 357207 | 3365.2 | 0.260818 | 2(Loss) | true |
| Glaze | 1296.97 | 0.443529 | 359.584ms | 4857 | 1280 | 321167 | 3571.4 | 0.128967 | 3(Loss) | true |
| simdjson (reflection) | 1078.29 | 0.181132 | 434.496ms | 4857 | 4890 | 296048 | 4295.67 | 0.0924932 | 4(Loss) | true |
| simdjson (ondemand) | 903.205 | 0.373564 | 520.577ms | 4857 | 640 | 234895 | 5128.4 | 0.352223 | 5(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2545.61 | 0.610151 | 227.486ms | 4857 | 1280 | 157774 | 1819.6 | 0.437733 | 1(Win) | true |
| Glaze | 2083.76 | 0.291952 | 264.851ms | 4857 | 4890 | 205955 | 2222.91 | 0.24384 | 2(Loss) | true |
| Jsonifier (two-stage) | 1787.04 | 3.06641 | 324.134ms | 4857 | 40 | 252692 | 2592 | 0.409836 | 3(Loss) | true |
| simdjson (reflection) | 1313.59 | 0.220345 | 397.147ms | 4857 | 4890 | 295210 | 3526.2 | 0.246013 | 4(Loss) | true |
| simdjson (ondemand) | 1185.85 | 0.155743 | 430.31ms | 4857 | 4890 | 180969 | 3906.07 | 0.405313 | 5(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11496.7 | 1.76771 | 42.8022ms | 4857 | 4890 | 248040 | 402.899 | 0.373437 | 1(Win) | true |
| simdjson (reflection) | 9257.96 | 1.48895 | 52.7631ms | 4857 | 4890 | 271378 | 500.326 | 1.15761 | 2(Loss) | true |
| Glaze | 2735.88 | 0.425318 | 173.633ms | 4857 | 4890 | 253558 | 1693.06 | 1.16248 | 3(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12813.7 | 1.92632 | 38.4251ms | 4857 | 4890 | 237113 | 361.489 | 2.9296 | 1(Win) | true |
| simdjson (reflection) | 10284.6 | 1.58756 | 47.87ms | 4857 | 4890 | 249995 | 450.382 | 1.44814 | 2(Loss) | true |
| Glaze | 2956.34 | 0.909038 | 162.083ms | 4857 | 1280 | 259657 | 1566.8 | 0.457433 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1886.82 | 0.227732 | 356.658ms | 6701 | 4890 | 290920 | 3386.95 | 0.208529 | 1(Win) | true |
| Jsonifier (two-stage) | 1761.36 | 0.294566 | 368.235ms | 6701 | 2560 | 292407 | 3628.2 | 0.640815 | 2(Loss) | true |
| Glaze | 1546.13 | 0.145845 | 418.161ms | 6701 | 4890 | 177698 | 4133.27 | 0.254007 | 3(Loss) | true |
| simdjson (reflection) | 1423.54 | 0.339143 | 457.088ms | 6701 | 1280 | 296698 | 4489.2 | 0.0445712 | 4(Loss) | true |
| simdjson (ondemand) | 1249.3 | 0.128458 | 517.132ms | 6701 | 4890 | 211144 | 5115.34 | 0.126068 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2510.54 | 0.406917 | 304.111ms | 6701 | 2560 | 274662 | 2545.5 | 0.0431948 | 1(Win) | true |
| Glaze | 2311.07 | 0.354459 | 337.398ms | 6701 | 2560 | 245938 | 2765.2 | 0.144865 | 2(Loss) | true |
| Jsonifier (two-stage) | 2239.48 | 0.738686 | 328.639ms | 6701 | 320 | 142186 | 2853.6 | 0.196629 | 3(Loss) | true |
| simdjson (ondemand) | 1558.17 | 0.131258 | 449.949ms | 6701 | 4890 | 141714 | 4101.34 | 0.0355884 | 4(Loss) | true |
| simdjson (reflection) | 1455.71 | 0.651521 | 465.114ms | 6701 | 640 | 523560 | 4390 | 1.09048 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13440.6 | 1.38451 | 55.1421ms | 7376 | 4890 | 256747 | 523.36 | 0.549535 | 1(Win) | true |
| Glaze | 2175.05 | 0.249837 | 315.393ms | 7376 | 4890 | 319246 | 3234.08 | 0.413211 | 2(Loss) | true |
| simdjson (reflection) | 357.841 | 0.190222 | 2078.05ms | 7376 | 160 | 223719 | 19657.6 | 0.0975768 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14121.5 | 1.45561 | 52.5412ms | 7376 | 4890 | 257086 | 498.127 | 0.354713 | 1(Win) | true |
| Glaze | 2368.93 | 0.412959 | 295.367ms | 7376 | 2560 | 384939 | 2969.4 | 0.442567 | 2(Loss) | true |
| simdjson (reflection) | 358.732 | 0.286121 | 2178.77ms | 7376 | 320 | 1.00728e+06 | 19608.8 | 0.158859 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Glaze STATISTICAL TIE | 1337.87 | 0.687082 | 124.856ms | 1691 | 2560 | 175598 | 1205.4 | 0.166196 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1305.59 | 1.03221 | 121.534ms | 1691 | 1280 | 208076 | 1235.2 | 0.0972447 | 1(Tie) | true |
| Jsonifier (two-stage) | 1272.33 | 0.518529 | 131.58ms | 1691 | 4890 | 211223 | 1267.49 | 0.915577 | 3(Loss) | true |
| simdjson (ondemand) | 1177.58 | 0.520059 | 138.83ms | 1691 | 4890 | 248038 | 1369.47 | 1.26962 | 4(Loss) | true |
| simdjson (reflection) | 963.129 | 0.823882 | 156.587ms | 1691 | 1280 | 243589 | 1674.4 | 0.191479 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2098.73 | 1.5549 | 100.302ms | 1691 | 1280 | 182722 | 768.4 | 0.259605 | 1(Win) | true |
| Glaze | 1760.74 | 0.811091 | 115.686ms | 1691 | 2560 | 141278 | 915.9 | 0.427632 | 2(Loss) | true |
| Jsonifier (two-stage) | 1702.37 | 0.430751 | 118.23ms | 1691 | 4890 | 81422 | 947.305 | 0.350075 | 3(Loss) | true |
| simdjson (reflection) | 1369.22 | 0.952661 | 143.481ms | 1691 | 1280 | 161150 | 1177.8 | 0.0169779 | 4(Loss) | true |
| simdjson (ondemand) | 1310.49 | 0.508531 | 146.7ms | 1691 | 4890 | 191498 | 1230.58 | 0.751677 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 11418.9 | 4.43328 | 20.2821ms | 1996 | 2560 | 139818 | 166.7 | 2.74212 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 10400.6 | 3.03027 | 20.779ms | 1996 | 4890 | 150410 | 183.022 | 1.00534 | 1(Tie) | true |
| Glaze | 2662.29 | 1.87718 | 70.402ms | 1996 | 1280 | 230587 | 715 | 1.27479 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14170.1 | 3.76741 | 15.9232ms | 1996 | 4890 | 125248 | 134.335 | 1.07912 | 1(Win) | true |
| simdjson (reflection) | 12071.9 | 3.31853 | 18.3539ms | 1996 | 4890 | 133897 | 157.683 | 0.389491 | 2(Loss) | true |
| Glaze | 3733.87 | 1.42105 | 53.0662ms | 1996 | 4890 | 256643 | 509.801 | 0.572347 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1683.6 | 1.35325 | 128.611ms | 2158 | 640 | 175132 | 1222.4 | 0.0654879 | 1(Win) | true |
| Glaze | 1594.14 | 0.526989 | 130.791ms | 2158 | 4890 | 226340 | 1290.99 | 0.062404 | 2(Loss) | true |
| Jsonifier (two-stage) | 1505.29 | 1.03474 | 142.323ms | 2158 | 1280 | 256174 | 1367.2 | 0.116891 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1409.52 | 0.518752 | 149.269ms | 2158 | 4890 | 280536 | 1460.09 | 0.267132 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1392.91 | 0.697073 | 149.486ms | 2158 | 2560 | 271551 | 1477.5 | 0.114927 | 4(Tie) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2303.37 | 0.519847 | 112.666ms | 2158 | 4890 | 105496 | 893.487 | 0.424929 | 1(Win) | true |
| Glaze | 2146.53 | 0.349517 | 119.033ms | 2158 | 4890 | 54912.9 | 958.77 | 0.174458 | 2(Loss) | true |
| Jsonifier (two-stage) | 2014.52 | 0.911193 | 130.082ms | 2158 | 320 | 27728.9 | 1021.6 | 0.551181 | 3(Loss) | true |
| simdjson (ondemand) | 1808.46 | 0.868496 | 132.145ms | 2158 | 1280 | 125034 | 1138 | 0.601132 | 4(Loss) | true |
| simdjson (reflection) | 1664.8 | 0.982831 | 145.372ms | 2158 | 1280 | 188949 | 1236.2 | 0.722775 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13200.8 | 2.81064 | 24.6331ms | 2866 | 4890 | 165606 | 207.051 | 0.0730424 | 1(Win) | true |
| Glaze | 2883.2 | 0.387588 | 96.9311ms | 2866 | 4890 | 66016.6 | 947.985 | 0.536641 | 2(Loss) | true |
| simdjson (reflection) | 395.843 | 0.101243 | 695.38ms | 2866 | 4890 | 238969 | 6904.83 | 0.129772 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 14583.5 | 2.98888 | 21.525ms | 2866 | 4890 | 153445 | 187.419 | 7.67526 | -(Win) | false |
| Glaze | 3403.35 | 0.992503 | 83.5269ms | 2866 | 2560 | 162646 | 803.1 | 0.563486 | 2(Loss) | true |
| simdjson (reflection) | 401.426 | 0.334299 | 717.358ms | 2866 | 320 | 165791 | 6808.8 | 0.0352361 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1663.28 | 0.420322 | 256.709ms | 4390 | 2560 | 286553 | 2517.1 | 0.0198602 | 1(Win) | true |
| Jsonifier (two-stage) | 1213.73 | 0.238894 | 369.179ms | 4390 | 4890 | 332053 | 3449.4 | 0.167756 | 2(Loss) | true |
| simdjson (reflection) | 1067.99 | 0.143199 | 398.846ms | 4390 | 4890 | 154092 | 3920.1 | 0.201167 | 3(Loss) | true |
| Glaze | 1049.07 | 0.160785 | 405.821ms | 4390 | 2560 | 105403 | 3990.8 | 0.18009 | 4(Loss) | true |
| simdjson (ondemand) | 729.48 | 0.369598 | 565.074ms | 4390 | 640 | 287966 | 5739.2 | 0.0696476 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2046.92 | 0.181486 | 246.107ms | 4390 | 4890 | 67378.7 | 2045.33 | 0.0993521 | 1(Win) | true |
| Jsonifier (two-stage) | 1408.54 | 0.141563 | 341.597ms | 4390 | 4890 | 86576.8 | 2972.32 | 0.133646 | 2(Loss) | true |
| Glaze | 1236.75 | 0.443006 | 390.371ms | 4390 | 1280 | 287871 | 3385.2 | 0.0472422 | 3(Loss) | true |
| simdjson (reflection) | 1209.03 | 0.588053 | 398.41ms | 4390 | 640 | 265380 | 3462.8 | 0.127226 | 4(Loss) | true |
| simdjson (ondemand) | 869.028 | 0.597593 | 534.642ms | 4390 | 160 | 132615 | 4817.6 | 0.0995355 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9502.28 | 1.61926 | 46.5882ms | 4390 | 4890 | 248894 | 440.592 | 0.500052 | 1(Win) | true |
| simdjson (reflection) | 8699.14 | 1.49246 | 50.9811ms | 4390 | 4890 | 252285 | 481.27 | 0.296348 | 2(Loss) | true |
| Glaze | 1765.69 | 0.434362 | 238.855ms | 4390 | 2560 | 271546 | 2371.1 | 0.105325 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10177 | 1.71919 | 43.9652ms | 4390 | 4890 | 244591 | 411.38 | 0.824504 | 1(Win) | true |
| simdjson (reflection) | 9073.2 | 1.56647 | 49.1059ms | 4390 | 4890 | 255484 | 461.428 | 0.201568 | 2(Loss) | true |
| Glaze | 1977.53 | 0.242456 | 214.069ms | 4390 | 4890 | 128843 | 2117.1 | 0.0285516 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2287.82 | 0.295103 | 394.039ms | 9378 | 1280 | 170346 | 3909.2 | 0.0409458 | 1(Win) | true |
| Jsonifier (two-stage) | 2176.05 | 0.274785 | 415.178ms | 9378 | 1280 | 163260 | 4110 | 0.0194609 | 2(Loss) | true |
| simdjson (reflection) | 1966.14 | 0.993273 | 464.799ms | 9378 | 160 | 326626 | 4548.8 | 0.0351617 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1465.24 | 0.174853 | 649.482ms | 9378 | 1280 | 145800 | 6103.8 | 0.212529 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 1458.7 | 0.305739 | 601.797ms | 9378 | 2560 | 899567 | 6131.2 | 0.182339 | 4(Tie) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2834.55 | 0.279492 | 358.459ms | 9378 | 2560 | 199082 | 3155.2 | 0.228717 | 1(Win) | true |
| Jsonifier (two-stage) | 2463.79 | 0.299021 | 406.782ms | 9378 | 2560 | 301618 | 3630 | 0.0385526 | 2(Loss) | true |
| simdjson (reflection) | 2188.94 | 0.176491 | 453.584ms | 9378 | 2560 | 133119 | 4085.8 | 0.235513 | 3(Loss) | true |
| Glaze | 1850.75 | 0.19052 | 530.647ms | 9378 | 2560 | 216993 | 4832.4 | 0.0455468 | 4(Loss) | true |
| simdjson (ondemand) | 1632.12 | 0.154357 | 595.819ms | 9378 | 4890 | 349844 | 5479.71 | 0.12378 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16862 | 2.91587 | 69.6041ms | 11521 | 640 | 231036 | 651.6 | 4.95916 | 1(Win) | true |
| Glaze | 2833.89 | 0.230815 | 390.728ms | 11521 | 2560 | 205014 | 3877.1 | 0.27522 | 2(Loss) | true |
| simdjson (reflection) | 335.033 | 0.114982 | 3375.57ms | 11521 | 1280 | 1.82e+06 | 32794.6 | 0.0554662 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 21088.8 | 1.90732 | 61.238ms | 11521 | 2560 | 252792 | 521 | 4.5088 | 1(Win) | true |
| Glaze | 3176.06 | 0.231149 | 351.2ms | 11521 | 4890 | 312675 | 3459.4 | 0.342729 | 2(Loss) | true |
| simdjson (reflection) | 334.127 | 0.0682039 | 3324.04ms | 11521 | 4890 | 2.45971e+06 | 32883.5 | 0.264053 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2754.19 | 0.639072 | 165.589ms | 4669 | 2560 | 273274 | 1616.7 | 0.424982 | 1(Win) | true |
| Jsonifier (two-stage) | 1685.67 | 0.397228 | 268.567ms | 4669 | 2560 | 281852 | 2641.5 | 0.208649 | 2(Loss) | true |
| Glaze | 1500.34 | 0.287682 | 323.612ms | 4669 | 1280 | 93304.9 | 2967.8 | 0.0336836 | 3(Loss) | true |
| simdjson (reflection) | 1342.47 | 0.437227 | 335.865ms | 4669 | 1280 | 269192 | 3316.8 | 0.278147 | 4(Loss) | true |
| simdjson (ondemand) | 1130.39 | 0.137568 | 399.227ms | 4669 | 4890 | 143595 | 3939.1 | 0.479982 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3122.04 | 0.516793 | 155.721ms | 4669 | 4890 | 265652 | 1426.22 | 0.0687777 | 1(Win) | true |
| Jsonifier (two-stage) | 1828.48 | 0.59858 | 257.649ms | 4669 | 1280 | 271972 | 2435.2 | 0.346135 | 2(Loss) | true |
| Glaze | 1495.7 | 1.82846 | 290.322ms | 4669 | 2560 | 7.58526e+06 | 2977 | 0.574444 | 3(Loss) | true |
| simdjson (reflection) | 1426.78 | 0.61371 | 328.711ms | 4669 | 320 | 117384 | 3120.8 | 0.0768443 | 4(Loss) | true |
| simdjson (ondemand) | 1273.29 | 0.415707 | 373.781ms | 4669 | 1280 | 270505 | 3497 | 0.393073 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13308.3 | 2.02541 | 36.416ms | 4669 | 4890 | 224561 | 334.58 | 0.203642 | 1(Win) | true |
| simdjson (reflection) | 9141.62 | 1.47501 | 50.9261ms | 4669 | 4890 | 252408 | 487.081 | 0.636482 | 2(Loss) | true |
| Glaze | 1679.63 | 0.620497 | 251.468ms | 4669 | 1280 | 346345 | 2651 | 1.24504 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14377.5 | 2.96282 | 33.2649ms | 4669 | 2560 | 215543 | 309.7 | 0.0969619 | 1(Win) | true |
| simdjson (reflection) | 9629.08 | 1.60855 | 49.1978ms | 4669 | 4890 | 270557 | 462.423 | 0.703693 | 2(Loss) | true |
| Glaze | 2258.34 | 0.191107 | 200.979ms | 4669 | 4890 | 69427.2 | 1971.67 | 0.232381 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2491.72 | 0.136197 | 315.273ms | 7932 | 4890 | 83600.8 | 3035.88 | 0.956632 | 1(Win) | true |
| Jsonifier | 2387.95 | 0.21697 | 315.804ms | 7932 | 4890 | 231007 | 3167.8 | 0.0664523 | 2(Loss) | true |
| simdjson (reflection) | 2066.45 | 0.227281 | 370.067ms | 7932 | 4890 | 338494 | 3660.64 | 0.173575 | 3(Loss) | true |
| Glaze | 1971.06 | 0.231668 | 390.362ms | 7932 | 2560 | 202365 | 3837.8 | 0.378985 | 4(Loss) | true |
| simdjson (ondemand) | 1743.79 | 0.634061 | 442.588ms | 7932 | 640 | 484196 | 4338 | 0.21253 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2737.6 | 0.877803 | 331.24ms | 7932 | 320 | 188264 | 2763.2 | 0.0579374 | 1(Win) | true |
| Jsonifier (two-stage) | 2667.05 | 0.32063 | 298.857ms | 7932 | 2560 | 211715 | 2836.3 | 0.010576 | 2(Loss) | true |
| Glaze | 2219.38 | 0.306869 | 358.508ms | 7932 | 2560 | 280058 | 3408.4 | 0.432344 | 3(Loss) | true |
| simdjson (reflection) | 2192.1 | 0.229823 | 361.126ms | 7932 | 4890 | 307566 | 3450.82 | 0.0671938 | 4(Loss) | true |
| simdjson (ondemand) | 1965.16 | 0.182827 | 401.198ms | 7932 | 4890 | 242191 | 3849.32 | 0.224402 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 20831.6 | 1.69122 | 44.4941ms | 9249 | 4890 | 250757 | 423.421 | 0.301187 | 1(Win) | true |
| Glaze | 2392.32 | 0.204544 | 372.601ms | 9249 | 4890 | 278122 | 3687.03 | 0.425942 | 2(Loss) | true |
| simdjson (reflection) | 345.189 | 0.150331 | 2632.65ms | 9249 | 640 | 944400 | 25552.8 | 0.109457 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 22509.8 | 1.83075 | 41.857ms | 9249 | 4890 | 251660 | 391.853 | 0.037561 | 1(Win) | true |
| Glaze | 2607.23 | 0.303125 | 345.829ms | 9249 | 2560 | 269223 | 3383.1 | 0.0679388 | 2(Loss) | true |
| simdjson (reflection) | 345.113 | 0.19627 | 2613.81ms | 9249 | 320 | 805240 | 25558.4 | 0.119085 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 645.736 | 0.114533 | 686.068ms | 4604 | 4890 | 296574 | 6799.55 | 0.520132 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 533.009 | 0.247872 | 845.683ms | 4604 | 640 | 266830 | 8237.6 | 0.145886 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 531.435 | 0.183125 | 873.716ms | 4604 | 1280 | 293006 | 8262 | 0.390625 | 2(Tie) | true |
| Glaze | 449.059 | 0.168592 | 987.588ms | 4604 | 1280 | 347815 | 9777.6 | 0.0735835 | 4(Loss) | true |
| simdjson (ondemand) | 387.783 | 0.182016 | 1151.1ms | 4604 | 1280 | 543653 | 11322.6 | 0.0583245 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 829.981 | 0.143893 | 667.1ms | 4604 | 4890 | 283350 | 5290.14 | 0.0426432 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 640.009 | 0.151147 | 817.833ms | 4604 | 2560 | 275256 | 6860.4 | 0.131016 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 636.803 | 0.888905 | 882.249ms | 4604 | 30 | 112692 | 6894.93 | 0.372671 | 2(Tie) | true |
| Glaze | 530.485 | 0.373792 | 976.456ms | 4604 | 320 | 306291 | 8276.8 | 0.0580271 | 4(Loss) | true |
| simdjson (ondemand) | 445.965 | 0.0988562 | 1122.66ms | 4604 | 4890 | 463218 | 9845.42 | 0.178318 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2111.26 | 0.387231 | 227.295ms | 4918 | 2560 | 189441 | 2221.5 | 0.139351 | 1(Win) | true |
| simdjson (reflection) | 2076.4 | 0.585555 | 227.82ms | 4918 | 1280 | 223924 | 2258.8 | 0.0354296 | 2(Loss) | true |
| Glaze | 1093.74 | 0.277636 | 411.607ms | 4604 | 320 | 39750.5 | 4014.4 | 0.0796495 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2134.32 | 0.394276 | 224.785ms | 4918 | 2560 | 192176 | 2197.5 | 0.502581 | 1(Win) | true |
| simdjson (reflection) | 2113.06 | 0.297482 | 225.035ms | 4918 | 4890 | 213198 | 2219.61 | 0.031122 | 2(Loss) | true |
| Glaze | 1153.93 | 0.330273 | 392.508ms | 4604 | 1280 | 202146 | 3805 | 0.298711 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1885.52 | 0.13646 | 961.337ms | 18245 | 2560 | 405951 | 9228.1 | 0.192174 | 1(Win) | true |
| simdjson (reflection) | 1803.46 | 0.159973 | 974.858ms | 18245 | 2560 | 609825 | 9648 | 0.0726066 | 2(Loss) | true |
| Jsonifier | 1747 | 0.114751 | 998.996ms | 18245 | 4890 | 638743 | 9959.81 | 0.551362 | 3(Loss) | true |
| simdjson (ondemand) | 1367.26 | 0.273498 | 1279ms | 18245 | 640 | 775307 | 12726 | 0.255247 | 4(Loss) | true |
| Glaze | 1337.29 | 0.139016 | 1336.49ms | 18245 | 80 | 26172.9 | 13011.2 | 0.0982801 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2213.52 | 0.130255 | 939.252ms | 18245 | 2560 | 268380 | 7860.7 | 0.151616 | 1(Win) | true |
| Jsonifier | 2085.91 | 0.321405 | 992.262ms | 18245 | 640 | 460028 | 8341.6 | 0.182552 | 2(Loss) | true |
| simdjson (reflection) | 2047.23 | 0.652733 | 1071.4ms | 18245 | 80 | 246216 | 8499.2 | 0.0752445 | 3(Loss) | true |
| simdjson (ondemand) | 1556.46 | 0.0835448 | 1258.64ms | 18245 | 4890 | 426540 | 11179.1 | 0.00702683 | 4(Loss) | true |
| Glaze | 1499.26 | 0.347761 | 1427.47ms | 18245 | 320 | 521252 | 11605.6 | 1.90019 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8858.52 | 0.269962 | 271.441ms | 24893 | 4890 | 255945 | 2679.89 | 0.164457 | 1(Win) | true |
| Glaze | 3314.53 | 0.361317 | 718.669ms | 24579 | 320 | 208935 | 7072 | 0.0679194 | 2(Loss) | true |
| simdjson (reflection) | 325.371 | 0.129029 | 7453.18ms | 24893 | 320 | 2.83612e+06 | 72962.4 | 0.204618 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9524.5 | 0.413788 | 267.207ms | 24893 | 2560 | 272312 | 2492.5 | 0.228164 | 1(Win) | true |
| Glaze | 3774.8 | 0.116839 | 628.025ms | 24579 | 4890 | 257411 | 6209.7 | 0.59229 | 2(Loss) | true |
| simdjson (reflection) | 323.845 | 0.0744042 | 7556.29ms | 24893 | 2560 | 7.61581e+06 | 73306.2 | 0.218602 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 705.284 | 0.138528 | 629.543ms | 4604 | 4890 | 363684 | 6225.46 | 0.226628 | 1(Win) | true |
| Jsonifier (two-stage) | 568.039 | 0.206299 | 838.647ms | 4604 | 1280 | 325474 | 7729.6 | 0.441811 | 2(Loss) | true |
| simdjson (reflection) | 535.418 | 0.891591 | 848.234ms | 4604 | 30 | 160375 | 8200.53 | 0.313152 | 3(Loss) | true |
| Glaze | 449.905 | 0.251139 | 991.422ms | 4604 | 640 | 384446 | 9759.2 | 0.31868 | 4(Loss) | true |
| simdjson (ondemand) | 371.883 | 0.105571 | 1190.52ms | 4604 | 2560 | 397728 | 11806.7 | 0.0703485 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 919.975 | 0.156241 | 615.136ms | 4604 | 4890 | 271907 | 4772.65 | 0.4535 | 1(Win) | true |
| Jsonifier (two-stage) | 697.599 | 0.127955 | 778.501ms | 4604 | 4890 | 317161 | 6294.04 | 0.0327174 | 2(Loss) | true |
| simdjson (reflection) | 642.632 | 0.22913 | 816.907ms | 4604 | 1280 | 313704 | 6832.4 | 0.411498 | 3(Loss) | true |
| Glaze | 532.35 | 0.185163 | 1059.85ms | 4604 | 1280 | 298534 | 8247.8 | 0.0218192 | 4(Loss) | true |
| simdjson (ondemand) | 425.457 | 0.365526 | 1194.21ms | 4604 | 160 | 227676 | 10320 | 0.216584 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 2080.04 | 0.296676 | 229.216ms | 4918 | 4890 | 218829 | 2254.84 | 0.33559 | 1(Win) | true |
| Jsonifier | 1830.38 | 0.651222 | 260.516ms | 4918 | 1280 | 356420 | 2562.4 | 1.85384 | 2(Loss) | true |
| Glaze | 1066.8 | 0.300899 | 415.634ms | 4604 | 1280 | 196318 | 4115.8 | 0.131374 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2155.05 | 0.268864 | 221.955ms | 4918 | 4890 | 167432 | 2176.37 | 0.0674266 | 1(Win) | true |
| simdjson (reflection) | 2119.66 | 0.384657 | 225.314ms | 4918 | 2560 | 185452 | 2212.7 | 0.193956 | 2(Loss) | true |
| Glaze | 1165.48 | 0.2837 | 382.812ms | 4604 | 2560 | 292429 | 3767.3 | 0.461333 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2006.16 | 0.262547 | 878.285ms | 18245 | 640 | 331858 | 8673.2 | 0.179541 | 1(Win) | true |
| Jsonifier (two-stage) | 1956.73 | 0.128354 | 899.351ms | 18245 | 2560 | 333493 | 8892.3 | 0.0258584 | 2(Loss) | true |
| simdjson (reflection) | 1528.85 | 0.394598 | 1086.81ms | 18245 | 1280 | 2.58156e+06 | 11381 | 0.549528 | 3(Loss) | true |
| Glaze | 1337.29 | 0.120105 | 1348.43ms | 18245 | 80 | 19536.4 | 13011.2 | 0.0982801 | 4(Loss) | true |
| simdjson (ondemand) | 1324.75 | 0.167823 | 1370.71ms | 18245 | 640 | 310960 | 13134.4 | 0.0060905 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2402.46 | 0.119311 | 863.335ms | 18245 | 4890 | 365132 | 7242.5 | 0.873267 | 1(Win) | true |
| Jsonifier (two-stage) | 2339.59 | 0.187629 | 885.251ms | 18245 | 2560 | 498481 | 7437.1 | 0.127901 | 2(Loss) | true |
| simdjson (reflection) | 2011.61 | 0.253461 | 1026.21ms | 18245 | 2560 | 1.23045e+06 | 8649.7 | 1.08977 | 3(Loss) | true |
| Glaze | 1507.13 | 0.0957987 | 1297.69ms | 18245 | 4890 | 598155 | 11545 | 0.107535 | 4(Loss) | true |
| simdjson (ondemand) | 1490.83 | 0.179383 | 1359.37ms | 18245 | 1280 | 561052 | 11671.2 | 0.178535 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9084.61 | 0.325979 | 265.974ms | 24893 | 4890 | 354837 | 2613.19 | 0.0187303 | 1(Win) | true |
| Glaze | 3130.39 | 1.1239 | 786.067ms | 24579 | 80 | 566596 | 7488 | 0.510204 | 2(Loss) | true |
| simdjson (reflection) | 324.428 | 0.161174 | 7614.02ms | 24893 | 320 | 4.45101e+06 | 73174.4 | 0.124789 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9848.5 | 0.421559 | 245.731ms | 24893 | 2560 | 264345 | 2410.5 | 0.53231 | 1(Win) | true |
| Glaze | 3801.67 | 0.228758 | 639.566ms | 24579 | 1280 | 254649 | 6165.8 | 0.00973204 | 2(Loss) | true |
| simdjson (reflection) | 290.046 | 0.127438 | 8295.9ms | 24893 | 4890 | 5.32024e+07 | 81848.5 | 0.0248692 | 3(Loss) | true |

----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1227.48 | 0.392946 | 402.506ms | 5094 | 2560 | 619144 | 3957.7 | 0.0328582 | 1(Win) | true |
| Jsonifier (two-stage) | 924.984 | 1.11233 | 579.038ms | 5094 | 320 | 1.09211e+06 | 5252 | 3.51264 | 2(Loss) | true |
| Glaze | 765.355 | 0.273981 | 648.856ms | 5094 | 1280 | 387116 | 6347.4 | 0.160954 | 3(Loss) | true |
| simdjson (reflection) | 714.302 | 2.8115 | 714.736ms | 5094 | 30 | 1.09686e+06 | 6801.07 | 1.48331 | 4(Loss) | true |
| simdjson (ondemand) | 588.622 | 0.605706 | 840.388ms | 5094 | 640 | 1.59937e+06 | 8253.2 | 1.00352 | 5(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1691.27 | 0.522171 | 396.153ms | 5094 | 2560 | 575911 | 2872.4 | 1.19786 | 1(Win) | true |
| Jsonifier (two-stage) | 1133.99 | 0.680335 | 567.628ms | 5094 | 640 | 543656 | 4284 | 1.5625 | 2(Loss) | true |
| Glaze | 991.937 | 0.249162 | 604.152ms | 5094 | 4890 | 728151 | 4897.51 | 0.451143 | 3(Loss) | true |
| simdjson (reflection) | 883.054 | 0.450935 | 661.373ms | 5094 | 4890 | 3.0094e+06 | 5501.38 | 1.89821 | 4(Loss) | true |
| simdjson (ondemand) | 795.772 | 0.260621 | 754.22ms | 5094 | 4890 | 1.23786e+06 | 6104.79 | 0.728689 | 5(Loss) | true |

----
### Random Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12196.9 | 2.44035 | 45.355ms | 5094 | 2560 | 241861 | 398.3 | 2.23368 | 1(Win) | true |
| simdjson (reflection) | 8532.94 | 1.3644 | 61.3379ms | 5094 | 4890 | 295063 | 569.325 | 0.640826 | 2(Loss) | true |
| Glaze | 1878.73 | 0.47063 | 263.383ms | 5094 | 2560 | 379130 | 2585.8 | 1.12632 | 3(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11020.9 | 4.47903 | 47.9101ms | 5094 | 640 | 249477 | 440.8 | 1.9573 | 1(Win) | true |
| simdjson (reflection) | 7640.79 | 2.13191 | 60.5599ms | 5094 | 1280 | 235174 | 635.8 | 2.28443 | 2(Loss) | true |
| Glaze | 2151.85 | 2.60417 | 236.072ms | 5094 | 160 | 553035 | 2257.6 | 0.355619 | 3(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1551.97 | 0.32893 | 496.313ms | 8051 | 4890 | 1.29495e+06 | 4947.29 | 0.878668 | 1(Win) | true |
| Jsonifier (two-stage) | 1428.63 | 0.535047 | 567.756ms | 8051 | 1280 | 1.05841e+06 | 5374.4 | 1.24945 | 2(Loss) | true |
| simdjson (reflection) | 1097.75 | 0.303735 | 696.251ms | 8051 | 4890 | 2.20695e+06 | 6994.35 | 1.54766 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 978.742 | 0.688307 | 807.728ms | 8051 | 320 | 932992 | 7844.8 | 3.44624 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 974.747 | 0.304155 | 788.906ms | 8051 | 4890 | 2.80683e+06 | 7876.95 | 2.32991 | 4(Tie) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2070.22 | 0.391544 | 493.137ms | 8051 | 1280 | 269922 | 3708.8 | 0.311794 | 1(Win) | true |
| Jsonifier (two-stage) | 1815.05 | 0.337114 | 533.93ms | 8051 | 2560 | 520613 | 4230.2 | 1.22517 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1377.87 | 0.563752 | 692.072ms | 8051 | 640 | 631598 | 5572.4 | 0.663149 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1375.89 | 0.539596 | 662.414ms | 8051 | 1280 | 1.16059e+06 | 5580.4 | 0.128857 | 3(Tie) | true |
| simdjson (ondemand) | 1105.26 | 0.335657 | 775.249ms | 8051 | 4890 | 2.65871e+06 | 6946.81 | 0.321215 | 5(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16180.1 | 1.81596 | 55.7591ms | 9255 | 2560 | 251213 | 545.5 | 1.96262 | 1(Win) | true |
| Glaze | 2000.15 | 1.14844 | 414.779ms | 9255 | 160 | 410929 | 4412.8 | 1.77122 | 2(Loss) | true |
| simdjson (reflection) | 297.981 | 0.213052 | 2937.88ms | 9255 | 4890 | 1.9474e+07 | 29620.2 | 0.756568 | 3(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14809.2 | 5.20751 | 53.193ms | 9255 | 640 | 616499 | 596 | 4.36457 | 1(Win) | true |
| Glaze | 2723.31 | 0.790168 | 353.403ms | 9255 | 1280 | 839474 | 3241 | 3.23062 | 2(Loss) | true |
| simdjson (reflection) | 281.651 | 0.828697 | 2950.53ms | 9255 | 640 | 4.31622e+07 | 31337.6 | 2.86649 | 3(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 3805.9 | 0.892995 | 74.6419ms | 2889 | 4890 | 204356 | 723.92 | 3.47625 | 1(Win) | true |
| Jsonifier | 3647.78 | 1.18818 | 77.4459ms | 2889 | 2560 | 206178 | 755.3 | 1.16528 | 2(Loss) | true |
| simdjson (reflection) | 3354.23 | 1.37344 | 81.8381ms | 2889 | 1280 | 162908 | 821.4 | 0.218659 | 3(Loss) | true |
| simdjson (ondemand) | 3121.1 | 0.65633 | 91.8341ms | 2889 | 4890 | 164147 | 882.755 | 0.814044 | 4(Loss) | true |
| Glaze | 2102.7 | 0.745067 | 132.165ms | 2889 | 2560 | 243990 | 1310.3 | 1.33283 | 5(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3973.99 | 1.36215 | 76.738ms | 2889 | 2560 | 228314 | 693.3 | 1.53779 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 3776.27 | 1.86299 | 75.8989ms | 2889 | 1280 | 236483 | 729.6 | 0.551268 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3753.12 | 1.24039 | 81.5322ms | 2889 | 2560 | 212259 | 734.1 | 3.24895 | 2(Tie) | true |
| simdjson (reflection) | 3548.64 | 1.52122 | 80.7731ms | 2889 | 1280 | 178552 | 776.4 | 4.52342 | 4(Loss) | true |
| Glaze | 2309.36 | 0.513117 | 128.595ms | 2889 | 4890 | 183254 | 1193.04 | 0.422021 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 4415.85 | 2.64595 | 86.004ms | 3808 | 320 | 151524 | 822.4 | 0.587084 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 4350.25 | 0.687816 | 85.8959ms | 3808 | 4890 | 161220 | 834.801 | 0.0960213 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4207.13 | 2.2789 | 89.0729ms | 3808 | 320 | 123830 | 863.2 | 0.644567 | 1(Tie) | true |
| Jsonifier (two-stage) | 4149.92 | 0.803563 | 91.424ms | 3808 | 2560 | 126589 | 875.1 | 0.0342936 | 4(Loss) | true |
| Glaze | 2935.64 | 0.508489 | 128.667ms | 3808 | 4890 | 193491 | 1237.07 | 1.88367 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4569.76 | 1.07763 | 83.604ms | 3808 | 2560 | 187751 | 794.7 | 0.62041 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 4486.71 | 0.774365 | 85.758ms | 3808 | 4890 | 192105 | 809.41 | 0.159094 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4482.36 | 0.713933 | 84.3389ms | 3808 | 4890 | 163607 | 810.196 | 1.2871 | 1(Tie) | true |
| simdjson (reflection) | 4347.8 | 0.694147 | 86.187ms | 3808 | 4890 | 164387 | 835.272 | 2.82802 | 4(Loss) | true |
| Glaze | 3000 | 0.519033 | 128.764ms | 3808 | 4890 | 193041 | 1210.53 | 2.77885 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2389.98 | 0.649036 | 117.76ms | 2889 | 2560 | 143313 | 1152.8 | 0.121591 | 1(Win) | true |
| Glaze | 1945.58 | 0.524299 | 145.068ms | 2889 | 4890 | 269565 | 1416.11 | 0.0151507 | 2(Loss) | true |
| Jsonifier (two-stage) | 1860.59 | 1.35174 | 153.442ms | 2889 | 640 | 256426 | 1480.8 | 0.0539957 | 3(Loss) | true |
| simdjson (reflection) | 1396.43 | 0.403744 | 200.948ms | 2889 | 1280 | 81222.5 | 1973 | 0.19223 | 4(Loss) | true |
| simdjson (ondemand) | 1133.1 | 0.317388 | 247.438ms | 2889 | 4890 | 291239 | 2431.53 | 0.393428 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2961.27 | 1.11904 | 108.864ms | 2889 | 640 | 69376.2 | 930.4 | 0 | 1(Win) | true |
| Glaze | 2238.88 | 1.00242 | 135.583ms | 2889 | 1280 | 194781 | 1230.6 | 1.43422 | 2(Loss) | true |
| Jsonifier (two-stage) | 2180.06 | 0.7163 | 141.865ms | 2889 | 2560 | 209791 | 1263.8 | 0.253847 | 3(Loss) | true |
| simdjson (reflection) | 1555.57 | 0.391339 | 192.992ms | 2889 | 4890 | 234927 | 1771.16 | 0.725888 | 4(Loss) | true |
| simdjson (ondemand) | 1214.8 | 0.593273 | 241.125ms | 2889 | 1280 | 231743 | 2268 | 0.212089 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11865.5 | 2.58596 | 26.1901ms | 2963 | 4890 | 185458 | 238.148 | 1.99668 | 1(Win) | true |
| simdjson (reflection) | 9258.64 | 3.05208 | 32.5061ms | 2963 | 2560 | 222127 | 305.2 | 1.19363 | 2(Loss) | true |
| Glaze | 3048.97 | 0.630396 | 94.4571ms | 2963 | 4890 | 166914 | 926.783 | 0.506407 | 3(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13278.2 | 2.75988 | 23.9401ms | 2963 | 4890 | 168683 | 212.81 | 0.0892883 | 1(Win) | true |
| simdjson (reflection) | 10407.9 | 3.25309 | 30.3519ms | 2963 | 2560 | 199697 | 271.5 | 1.84382 | 2(Loss) | true |
| Glaze | 3334.99 | 0.985895 | 81.7638ms | 2963 | 2560 | 178639 | 847.3 | 0.201041 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2517.92 | 0.720879 | 147.086ms | 3808 | 2560 | 276743 | 1442.3 | 0.312978 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2195.85 | 0.469826 | 167.815ms | 3808 | 4890 | 295238 | 1653.84 | 0.500958 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 2184.99 | 0.433692 | 168.386ms | 3808 | 4890 | 254077 | 1662.06 | 0.232963 | 2(Tie) | true |
| simdjson (reflection) | 1744.78 | 0.215198 | 211.43ms | 3808 | 4890 | 98106.4 | 2081.4 | 0.0815895 | 4(Loss) | true |
| simdjson (ondemand) | 1381.88 | 0.751331 | 258.829ms | 3808 | 640 | 249513 | 2628 | 0 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2970.87 | 0.703595 | 137.376ms | 3808 | 2560 | 189371 | 1222.4 | 0.131062 | 1(Win) | true |
| Jsonifier (two-stage) | 2572.68 | 0.7108 | 159.686ms | 3808 | 2560 | 257726 | 1411.6 | 0.703433 | 2(Loss) | true |
| Glaze | 2413.34 | 0.711724 | 161.998ms | 3808 | 2560 | 293644 | 1504.8 | 0.857909 | 3(Loss) | true |
| simdjson (reflection) | 1933.96 | 0.453417 | 202.698ms | 3808 | 2560 | 185581 | 1877.8 | 0.286746 | 4(Loss) | true |
| simdjson (ondemand) | 1534.91 | 0.583854 | 250.112ms | 3808 | 1280 | 244257 | 2366 | 0.471143 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13601.3 | 3.0205 | 32.4442ms | 4300 | 2560 | 212310 | 301.5 | 0.567045 | 1(Win) | true |
| Glaze | 3272.26 | 1.40041 | 129.301ms | 4300 | 640 | 197119 | 1253.2 | 0.288092 | 2(Loss) | true |
| simdjson (reflection) | 416.093 | 0.114711 | 992.365ms | 4300 | 4890 | 624991 | 9855.48 | 0.138042 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14328.1 | 2.46282 | 30.337ms | 4300 | 4890 | 242961 | 286.207 | 3.40636 | 1(Win) | true |
| Glaze | 4046.18 | 0.329192 | 104.555ms | 4300 | 2560 | 28496.1 | 1013.5 | 0.0691153 | 2(Loss) | true |
| simdjson (reflection) | 424.478 | 0.572978 | 998.735ms | 4300 | 80 | 245127 | 9660.8 | 0.099272 | 3(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 6733.63 | 0.433049 | 6975.09ms | 466906 | 320 | 2.62412e+07 | 66127.2 | 0.446826 | 1(Win) | true |
| Jsonifier | 6636.42 | 0.151695 | 6751.74ms | 466906 | 4890 | 5.06574e+07 | 67095.8 | 0.618661 | 2(Loss) | true |
| Glaze | 1712.39 | 0.223466 | 6832.45ms | 466906 | 40 | 1.35063e+07 | 260032 | 0.1818 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 7623.76 | 0.171602 | 6431.52ms | 466906 | 320 | 3.21451e+06 | 58406.4 | 0.10399 | 1(Win) | true |
| Jsonifier | 6474.78 | 0.245503 | 6632.62ms | 466906 | 2560 | 7.2973e+07 | 68770.9 | 3.94562 | 2(Loss) | true |
| Glaze | 1286.72 | 0.554987 | 7596.26ms | 466906 | 40 | 1.47542e+08 | 346054 | 0.969151 | 3(Loss) | true |

----
### Prettify Test Write Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2942.28 | 0.694538 | 5488.29ms | 699405 | 30 | 7.43709e+07 | 226697 | 0.51837 | 1(Win) | true |
| Glaze | 2465.36 | 0.202105 | 7111.49ms | 699405 | 80 | 2.39189e+07 | 270550 | 0.0650949 | 2(Loss) | true |
| simdjson (ondemand) | 1644.96 | 0.115135 | 5692.52ms | 767297 | 160 | 4.19715e+07 | 444845 | 0.286915 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3220.84 | 0.0927665 | 5419.79ms | 699405 | 320 | 1.18101e+07 | 207090 | 0.0528958 | 1(Win) | true |
| Glaze | 2469.28 | 0.077934 | 7042.31ms | 699405 | 320 | 1.41814e+07 | 270121 | 0.142252 | 2(Loss) | true |
| simdjson (ondemand) | 1658.54 | 0.152399 | 5772.74ms | 767297 | 40 | 1.80844e+07 | 441203 | 0.0764556 | 3(Loss) | true |

----
### Validate Test Read Results [(Here is the data we used for this test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2312.28 | 0.156413 | 6787.16ms | 631514 | 640 | 1.06221e+08 | 260461 | 0.160227 | 1(Win) | true |
| Glaze | 1859.81 | 0.482707 | 8084.41ms | 631514 | 40 | 9.77359e+07 | 323827 | 0.655776 | 2(Loss) | true |
