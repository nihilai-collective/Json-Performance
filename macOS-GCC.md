# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Just a bit of performance profiling of some JSON libraries (compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest results: (Nov 28, 2026)
#### Here are the commits we used:
----
| Jsonifier: [5f487ec](https://github.com/nihilai-collective/Jsonifier/commit/5f487ec)  
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
*Generated with BenchmarkSuite commit: [23af44c](https://github.com/nihilai-collective/benchmarksuite/commit/23af44c)*

----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 1851.3 | 2.17568 | 47.85ms | 905 | 2560 | 263375 | 466.2 | 6.97568 | -(Win) | false |
| Glaze | 1482.69 | 1.68626 | 64.3489ms | 905 | 2560 | 246651 | 582.1 | 1.6723 | 2(Loss) | true |
| simdjson (reflection) | 902.421 | 0.854585 | 101.752ms | 905 | 1280 | 85506.6 | 956.4 | 2.28852 | 3(Loss) | true |
| simdjson (ondemand) | 426.378 | 0.846015 | 229.253ms | 905 | 1280 | 375381 | 2024.2 | 0.606362 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1656.89 | 1.42246 | 51.924ms | 905 | 4890 | 268472 | 520.9 | 0.0959349 | 1(Win) | true |
| Glaze | 1508.35 | 2.43167 | 59.4281ms | 905 | 1280 | 247808 | 572.2 | 0.452331 | 2(Loss) | true |
| simdjson (reflection) | 933.155 | 0.776763 | 97.4769ms | 905 | 2560 | 132132 | 924.9 | 0.226537 | 3(Loss) | true |
| simdjson (ondemand) | 368.866 | 0.368681 | 227.448ms | 905 | 4890 | 363891 | 2339.81 | 0.0388468 | 4(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1762.1 | 2.0284 | 51.7251ms | 905 | 2560 | 252687 | 489.8 | 1.15655 | 1(Win) | true |
| simdjson (reflection) | 213.042 | 0.983323 | 421.966ms | 905 | 40 | 63477.5 | 4051.2 | 0.582627 | 2(Loss) | true |
| Glaze | 125.93 | 0.274251 | 710.621ms | 905 | 1280 | 452213 | 6853.6 | 0.302572 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3345.25 | 3.36625 | 37.335ms | 905 | 2560 | 193095 | 258 | 1.14943 | 1(Win) | true |
| simdjson (reflection) | 2579.42 | 2.87598 | 46.306ms | 905 | 2560 | 237063 | 334.6 | 0.416667 | 2(Loss) | true |
| Glaze | 864.458 | 1.42843 | 126.863ms | 905 | 30 | 6101.63 | 998.4 | 0 | 3(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 891.363 | 0.451431 | 197.502ms | 1811 | 2560 | 195863 | 1937.6 | 0.431655 | 1(Win) | true |
| Glaze | 814.979 | 0.631184 | 213.205ms | 1811 | 640 | 114508 | 2119.2 | 1.8063 | 2(Loss) | true |
| simdjson (ondemand) | 281.178 | 0.175921 | 624.753ms | 1811 | 4890 | 570974 | 6142.38 | 0.579288 | 3(Loss) | true |
| simdjson (reflection) | 232.638 | 1.42546 | 694.048ms | 1811 | 80 | 895935 | 7424 | 1.69492 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 995.162 | 1.01795 | 173.057ms | 1811 | 2560 | 798989 | 1735.5 | 1.6268 | 1(Win) | true |
| Glaze | 947.085 | 1.08106 | 184.335ms | 1811 | 640 | 248734 | 1823.6 | 0.2407 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 288.335 | 0.242995 | 598.255ms | 1811 | 4890 | 1.03597e+06 | 5989.93 | 0.771493 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 286.971 | 0.206238 | 628.317ms | 1811 | 320 | 49300.3 | 6018.4 | 1.94213 | 3(Tie) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 335.604 | 0.381653 | 587.625ms | 1997 | 640 | 300205 | 5674.8 | 0.190678 | 1(Win) | true |
| simdjson (reflection) | 324.776 | 0.317447 | 634.45ms | 1997 | 640 | 221774 | 5864 | 0.163979 | 2(Loss) | true |
| Glaze | 205.069 | 0.492232 | 828.675ms | 1798 | 640 | 1.08417e+06 | 8361.6 | 0.124224 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1058.05 | 1.81176 | 209.361ms | 1997 | 160 | 170164 | 1800 | 0.446429 | 1(Win) | true |
| simdjson (reflection) | 1002.15 | 0.807487 | 202.03ms | 1997 | 1280 | 301419 | 1900.4 | 0.606695 | 2(Loss) | true |
| Glaze | 645.543 | 0.337049 | 272.846ms | 1798 | 4890 | 391945 | 2656.22 | 1.56473 | 3(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1170.15 | 0.568232 | 110.894ms | 1313 | 2560 | 94654.2 | 1070.1 | 0.667921 | 1(Win) | true |
| Glaze | 738.049 | 0.83432 | 198.263ms | 1313 | 1280 | 256469 | 1696.6 | 2.4494 | 2(Loss) | true |
| simdjson (reflection) | 663.628 | 0.336482 | 197.644ms | 1313 | 4890 | 197111 | 1886.86 | 0.738527 | 3(Loss) | true |
| simdjson (ondemand) | 268.943 | 0.264769 | 444.365ms | 1313 | 4890 | 743105 | 4655.9 | 2.75434 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1524.07 | 1.96951 | 93.3842ms | 1313 | 640 | 167578 | 821.6 | 3.02172 | 1(Win) | true |
| Glaze | 886.307 | 1.99056 | 149.532ms | 1313 | 320 | 253081 | 1412.8 | 2.3175 | 2(Loss) | true |
| simdjson (reflection) | 782.596 | 0.557161 | 168.969ms | 1313 | 4890 | 388620 | 1600.03 | 2.43743 | 3(Loss) | true |
| simdjson (ondemand) | 263.327 | 2.17991 | 432.327ms | 1313 | 40 | 429807 | 4755.2 | 2.43566 | 4(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 307.629 | 1.39334 | 425.008ms | 1313 | 30 | 96496.1 | 4070.4 | 0.625 | 1(Win) | true |
| simdjson (reflection) | 277.582 | 0.345209 | 463.999ms | 1313 | 2560 | 620798 | 4511 | 0.289017 | 2(Loss) | true |
| Glaze | 178.719 | 0.173321 | 730.419ms | 1313 | 160 | 23594.5 | 7006.4 | 0.0685558 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 2653.48 | 1.52022 | 62.6742ms | 1313 | 4890 | 251662 | 471.899 | 0.632013 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 2630.62 | 2.08452 | 55.2369ms | 1313 | 2560 | 252038 | 476 | 2.32158 | 1(Tie) | true |
| Glaze | 854.377 | 2.01897 | 145.516ms | 1313 | 320 | 280182 | 1465.6 | 0.659341 | 3(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 759.129 | 0.808536 | 465.452ms | 4215 | 320 | 586562 | 5295.2 | 0.316265 | 1(Win) | true |
| Glaze | 646.926 | 0.368448 | 658.896ms | 4215 | 640 | 335443 | 6213.6 | 0.374774 | 2(Loss) | true |
| simdjson (reflection) | 573.756 | 0.517965 | 699.723ms | 4215 | 2560 | 3.37117e+06 | 7006 | 1.11224 | 3(Loss) | true |
| simdjson (ondemand) | 486.229 | 0.231021 | 833.118ms | 4215 | 4890 | 1.78373e+06 | 8267.18 | 0.412684 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1884.25 | 3.11614 | 328.003ms | 4215 | 30 | 132579 | 2133.33 | 0 | 1(Win) | true |
| Glaze | 835.618 | 0.304132 | 569.904ms | 4215 | 4890 | 1.04668e+06 | 4810.5 | 0.675914 | 2(Loss) | true |
| simdjson (reflection) | 828.728 | 0.268696 | 587.651ms | 4215 | 4890 | 830619 | 4850.49 | 1.37508 | 3(Loss) | true |
| simdjson (ondemand) | 655.22 | 0.259206 | 715.736ms | 4215 | 4890 | 1.23658e+06 | 6134.94 | 0.445555 | 4(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 825.611 | 0.89854 | 499.725ms | 4215 | 160 | 306224 | 4868.8 | 0.429043 | 1(Win) | true |
| simdjson (reflection) | 763.048 | 0.313517 | 543.53ms | 4215 | 1280 | 349159 | 5268 | 0.958222 | 2(Loss) | true |
| Glaze | 502.735 | 0.251463 | 836.826ms | 4215 | 30 | 12127.9 | 7995.73 | 0.752688 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6122.05 | 2.04244 | 79.9409ms | 4215 | 1280 | 230202 | 656.6 | 1.11446 | 1(Win) | true |
| simdjson (reflection) | 5066.53 | 0.97254 | 90.028ms | 4215 | 4890 | 291137 | 793.391 | 0.114492 | 2(Loss) | true |
| Glaze | 2453.45 | 1.16912 | 195.803ms | 4215 | 640 | 234822 | 1638.4 | 0.53424 | 3(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1166.14 | 0.513624 | 103.13ms | 1213 | 640 | 16614.8 | 992 | 0.879297 | 1(Win) | true |
| Glaze | 795.713 | 0.979265 | 151.03ms | 1213 | 1280 | 259430 | 1453.8 | 0.805131 | 2(Loss) | true |
| simdjson (reflection) | 614.408 | 0.78969 | 191.485ms | 1213 | 2560 | 565928 | 1882.8 | 1.87209 | 3(Loss) | true |
| simdjson (ondemand) | 233.944 | 0.704192 | 499.622ms | 1213 | 640 | 775996 | 4944.8 | 0.993112 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1645.76 | 1.29758 | 73.4651ms | 1213 | 2560 | 212959 | 702.9 | 0.15625 | 1(Win) | true |
| Glaze | 935.625 | 0.759979 | 126.98ms | 1213 | 2560 | 226027 | 1236.4 | 0.7386 | 2(Loss) | true |
| simdjson (reflection) | 756.034 | 0.68013 | 160.758ms | 1213 | 2560 | 277245 | 1530.1 | 0.591216 | 3(Loss) | true |
| simdjson (ondemand) | 255.981 | 0.270328 | 462.22ms | 1213 | 4890 | 729789 | 4519.11 | 1.44145 | 4(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 238.789 | 0.250668 | 503.133ms | 1213 | 4890 | 721104 | 4844.47 | 2.51001 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 235.737 | 1.37311 | 497.704ms | 1213 | 160 | 726437 | 4907.2 | 0.163292 | 1(Tie) | true |
| Glaze | 146.654 | 1.52432 | 781.824ms | 1213 | 80 | 1.15658e+06 | 7888 | 0.524617 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2340.76 | 1.45464 | 61.728ms | 1213 | 4890 | 252712 | 494.2 | 0.406422 | 1(Win) | true |
| simdjson (reflection) | 2121.43 | 1.32909 | 69.5729ms | 1213 | 4890 | 256853 | 545.296 | 1.0173 | 2(Loss) | true |
| Glaze | 830.801 | 0.535857 | 161.092ms | 1213 | 4890 | 272229 | 1392.4 | 1.29729 | 3(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 7501.56 | 0.0752713 | 6140.19ms | 466906 | 4890 | 9.76166e+06 | 59357.8 | 0.0597469 | 1(Win) | true |
| Jsonifier | 6321.64 | 0.773157 | 6523.49ms | 466906 | 160 | 4.74521e+07 | 70436.8 | 0.389948 | 2(Loss) | true |
| Glaze | 1640.71 | 0.791717 | 6954.6ms | 466906 | 160 | 7.38676e+08 | 271392 | 0.988331 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 7442.76 | 0.151497 | 6092.87ms | 466906 | 640 | 5.25753e+06 | 59826.8 | 0.10776 | 1(Win) | true |
| Jsonifier | 6886.25 | 0.496776 | 6794.71ms | 466906 | 320 | 3.3019e+07 | 64661.6 | 1.15007 | 2(Loss) | true |
| Glaze | 1581.35 | 0.744836 | 7134.69ms | 466906 | 1280 | 5.63032e+09 | 281579 | 1.47759 | 3(Loss) | true |
