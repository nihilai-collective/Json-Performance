# Json-Performance: Stage-1 Parsing
Just a bit of performance profiling of some JSON libraries (compiled and run on Linux 7.0.0-43-generic using the GCC 16.2.1 compiler).  

Latest results: (Nov 27, 2026)
#### Here are the commits we used:
----
| Jsonifier: [a1328b5](https://github.com/nihilai-collective/Jsonifier/commit/a1328b5)  
| simdjson: [4ba1cb3ae](https://github.com/simdjson/simdjson/commit/4ba1cb3ae)  

#### How We Benchmarked & What We Tested

| Library | Active Implementation |
| :--- | :--- |
| **Jsonifier (stage-1)** | `AVX2` |
| **simdjson (stage-1)** | `haswell` |

> Each library picks its own instruction-set implementation at build or run time, and these are the ones that produced the results below.

> **Sampling (Intel(R) Core(TM) i9-14900KF-AVX2):**  
> Iterations: 100 → 200 → 400 ... (max 100000), doubling per epoch.  
> Window: last `max(iterations/10, 30)` samples (max 100000). Runs for 5s or until the cap.  
> Epoch used: lowest RSE + mean shift (1st epoch is just a fallback).  
> Converged = RSE ≤ 5% and mean shift ≤ 2.5%. Non-converged ones still get ranked.  
> Ties: Welch's t-test (Bessel-corrected).

---

##### A Few Details
* **Stage-1 Only:** Just stage-1 on both sides, structural indexing with no tape or DOM built.
* **No UTF-8 Validation:** Off for both libraries.

---
*Generated with BenchmarkSuite commit: [ff0f871](https://github.com/nihilai-collective/benchmarksuite/commit/ff0f871)*

----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2140.51 | 0.0608121 | 743.925ms | 905 | 640 | 38.4788 | 403.209 | 0.015503 | 2.6469 | 11.589 | 2.71492 | 0.0040953 | 0.000138122 | 3.45304e-06 | 1(Win) | true |
| simdjson (stage-1) | 1073.84 | 0.111923 | 789.45ms | 905 | 640 | 517.883 | 803.727 | 0.0149716 | 5.03651 | 28.1934 | 6.00552 | 0.00110843 | 5.87017e-05 | 3.45304e-06 | 2(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 3058.53 | 0.0759739 | 758.364ms | 1811 | 4890 | 900.013 | 564.684 | 0.0663919 | 1.81755 | 8.79293 | 2.35726 | 0.000810317 | 8.10769e-05 | 6.32355e-06 | 1(Win) | true |
| simdjson (stage-1) | 1340.74 | 0.0526539 | 835.088ms | 1811 | 80 | 36.8044 | 1288.17 | 0.120181 | 3.96404 | 20.8564 | 4.96135 | 0.000938708 | 2.76091e-05 | 0 | 2(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2719.31 | 0.188712 | 750.656ms | 1313 | 40 | 30.2045 | 460.475 | 0.0742538 | 2.06582 | 9.85225 | 2.49276 | 0.000761615 | 1.90404e-05 | 0 | 1(Win) | true |
| simdjson (stage-1) | 1218.11 | 0.139097 | 813.223ms | 1313 | 640 | 1308.48 | 1027.96 | 0.229284 | 4.42936 | 24.92 | 5.68926 | 0.000982959 | 0.000174933 | 3.33206e-05 | 2(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 3039.98 | 0.0733393 | 841.286ms | 4215 | 640 | 601.878 | 1322.29 | 0.105411 | 1.74975 | 8.60047 | 1.09181 | 0.00213115 | 2.81732e-05 | 0 | 1(Win) | true |
| simdjson (stage-1) | 2815.08 | 0.0510176 | 852.438ms | 4215 | 320 | 169.826 | 1427.93 | 0.0284422 | 1.90872 | 9.88422 | 0.932622 | 0.00137233 | 3.03974e-05 | 0 | 2(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2599.08 | 0.0685537 | 750.499ms | 1213 | 1280 | 119.167 | 445.084 | 0.0296556 | 2.16558 | 10.1698 | 2.53339 | 0.000824402 | 0.000122372 | 4.05761e-05 | 1(Win) | true |
| simdjson (stage-1) | 1156.07 | 0.327554 | 805.59ms | 1213 | 320 | 3437.74 | 1000.64 | 0.341884 | 4.63166 | 26.6447 | 5.99341 | 0.000845012 | 0.000141694 | 5.41014e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 16740.5 | 0.0368374 | 1258.8ms | 94653 | 4890 | 19293.8 | 5392.19 | 0.158966 | 0.30971 | 1.66818 | 0.102152 | 3.16299e-05 | 2.43274e-06 | 8.31797e-07 | 1(Win) | true |
| simdjson (stage-1) | 13960.2 | 0.0397547 | 1362.58ms | 94653 | 40 | 264.317 | 6466.12 | 0.0246215 | 0.371369 | 2.01526 | 0.0771661 | 2.11298e-05 | 5.54658e-06 | 2.64123e-07 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 15947.4 | 0.041481 | 1465.76ms | 124597 | 30 | 286.585 | 7451.03 | 0.0429286 | 0.324891 | 1.68016 | 0.0881241 | 2.46127e-05 | 5.35058e-07 | 0 | 1(Win) | true |
| simdjson (stage-1) | 14746.3 | 0.0933757 | 1526.17ms | 124597 | 160 | 9058.1 | 8057.96 | 0.0172996 | 0.350756 | 1.8435 | 0.0692474 | 1.84094e-05 | 4.36407e-06 | 3.11003e-06 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 14348.4 | 0.156687 | 8253.71ms | 2251027 | 40 | 2.19825e+06 | 149615 | 0.584109 | 0.356328 | 1.67877 | 0.110613 | 0.00217623 | 0.02482 | 5.44196e-07 | 1(Win) | true |
| simdjson (stage-1) | 11721.5 | 0.0664548 | 9957.53ms | 2251027 | 40 | 592525 | 183146 | 0.243202 | 0.439057 | 2.1019 | 0.0806473 | 0.00163475 | 0.0245034 | 1.92135e-06 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 18122.6 | 0.118152 | 7667.2ms | 5373214 | 30 | 3.34835e+06 | 282758 | 0.922641 | 0.28435 | 1.36205 | 0.0692391 | 0.00102486 | 0.0195829 | 3.41199e-06 | 1(Win) | true |
| simdjson (stage-1) | 15789.8 | 0.138297 | 8535.07ms | 5373214 | 160 | 3.22298e+07 | 324532 | 0.250184 | 0.321243 | 1.59979 | 0.0578118 | 0.000932248 | 0.0195738 | 2.73928e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 10466.4 | 0.0373374 | 5294.88ms | 500299 | 640 | 185408 | 45585.9 | 0.0425937 | 0.492328 | 2.53185 | 0.173932 | 1.66151e-05 | 1.57406e-06 | 5.43425e-07 | 1(Win) | true |
| simdjson (stage-1) | 9879.96 | 0.11143 | 5525.89ms | 500299 | 30 | 86871.1 | 48291.9 | 0.0667223 | 0.521245 | 2.80238 | 0.112561 | 0.000290426 | 2.33194e-05 | 2.13872e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 14910.3 | 0.0729144 | 8152.79ms | 1151920 | 40 | 115440 | 73677.5 | 0.328507 | 0.339071 | 1.80099 | 0.0980694 | 0.000173037 | 0.000881029 | 4.4925e-06 | 1(Win) | true |
| simdjson (stage-1) | 14122.6 | 0.0388793 | 8692.6ms | 1151920 | 160 | 146343 | 77787.1 | 0.0262025 | 0.364735 | 1.9361 | 0.073131 | 0.000389035 | 0.00500692 | 6.59768e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 11378.4 | 0.0476012 | 1191.74ms | 56369 | 160 | 809.242 | 4724.56 | 0.112186 | 0.456713 | 2.30423 | 0.154092 | 0.000155782 | 3.3263e-06 | 0 | 1(Win) | true |
| simdjson (stage-1) | 10744.3 | 0.044425 | 1220.89ms | 56369 | 40 | 197.625 | 5003.38 | 0.0224798 | 0.483392 | 2.59153 | 0.103035 | 3.45935e-05 | 3.54805e-06 | 1.33052e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 13541.2 | 0.0304672 | 1317.02ms | 83958 | 4890 | 15870.2 | 5912.95 | 0.0896114 | 0.383574 | 2.04176 | 0.117452 | 2.44133e-05 | 3.10312e-06 | 5.94318e-07 | 1(Win) | true |
| simdjson (stage-1) | 12973.2 | 0.0720064 | 1336.85ms | 83958 | 2560 | 50560.9 | 6171.87 | 0.0431839 | 0.400264 | 2.18387 | 0.084447 | 4.04964e-05 | 3.52669e-06 | 8.09557e-07 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 18345.9 | 0.0337228 | 998.331ms | 53331 | 1280 | 1118.76 | 2772.3 | 0.186489 | 0.285489 | 1.45394 | 0.08496 | 3.77653e-05 | 2.22666e-06 | 1.02544e-07 | 1(Win) | true |
| simdjson (stage-1) | 15382.1 | 0.0538516 | 1043.62ms | 53331 | 40 | 126.82 | 3306.47 | 0.0143678 | 0.33899 | 1.74743 | 0.0651966 | 0.00010688 | 1.87508e-06 | 0 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 17111.4 | 0.0987056 | 1070.44ms | 65103 | 30 | 384.8 | 3628.4 | 0.0211251 | 0.304772 | 1.54139 | 0.0770779 | 0.00021402 | 1.02402e-06 | 0 | 1(Win) | true |
| simdjson (stage-1) | 16396.4 | 0.050725 | 1095.64ms | 65103 | 40 | 147.574 | 3786.62 | 0.0037411 | 0.317578 | 1.68504 | 0.0622398 | 3.07206e-05 | 2.30404e-06 | 0 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 10270.4 | 0.046788 | 819.025ms | 11812 | 4890 | 1287.8 | 1096.82 | 0.272795 | 0.522435 | 2.52565 | 0.175669 | 8.50579e-05 | 9.78174e-06 | 1.50621e-06 | 1(Win) | true |
| simdjson (stage-1) | 9731.73 | 0.150133 | 826.094ms | 11812 | 30 | 90.6023 | 1157.53 | 0.121093 | 0.54794 | 2.81519 | 0.117084 | 8.74817e-05 | 1.1288e-05 | 0 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 14656.7 | 0.109946 | 878.425ms | 25388 | 30 | 98.9609 | 1651.93 | 0.0282417 | 0.360153 | 1.85158 | 0.103277 | 4.46405e-05 | 2.62591e-06 | 0 | 1(Win) | true |
| simdjson (stage-1) | 14003.2 | 0.0804574 | 882.937ms | 25388 | 40 | 77.4096 | 1729.03 | 0.101799 | 0.376562 | 1.97822 | 0.0768867 | 0.00012112 | 2.95415e-06 | 9.84717e-07 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 11187.2 | 0.0354897 | 1651.61ms | 108313 | 2560 | 27489.5 | 9233.39 | 0.0691245 | 0.461998 | 2.40686 | 0.163739 | 1.95109e-05 | 1.77437e-06 | 2.38025e-07 | 1(Win) | true |
| simdjson (stage-1) | 10654 | 0.061298 | 1691.92ms | 108313 | 320 | 11302.6 | 9695.47 | 0.0068004 | 0.485103 | 2.67105 | 0.109018 | 5.44718e-05 | 1.99076e-06 | 8.65547e-08 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 13687.3 | 0.0866474 | 1991.86ms | 183677 | 320 | 39349 | 12797.8 | 0.15725 | 0.374135 | 1.98065 | 0.113117 | 2.21346e-05 | 9.35746e-07 | 2.21176e-07 | 1(Win) | true |
| simdjson (stage-1) | 12937.8 | 0.0408806 | 2104.94ms | 183677 | 4890 | 149808 | 13539.3 | 0.035498 | 0.398744 | 2.13402 | 0.0823457 | 3.08657e-05 | 2.15658e-06 | 1.11114e-06 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 7639 | 0.39258 | 6181.79ms | 1834197 | 40 | 3.23247e+07 | 228986 | 0.406246 | 0.669309 | 2.9649 | 0.213713 | 0.00590114 | 0.0377107 | 2.16716e-06 | 1(Win) | true |
| simdjson (stage-1) | 7382.61 | 0.0628084 | 6285.15ms | 1834197 | 640 | 1.41738e+07 | 236939 | 0.0412805 | 0.69607 | 3.30201 | 0.160353 | 0.00399388 | 0.0376738 | 2.50535e-06 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 14196.2 | 0.154494 | 6460.69ms | 7351818 | 160 | 9.31511e+07 | 493882 | 0.364069 | 0.360654 | 1.54566 | 0.0821143 | 0.00229367 | 0.0211532 | 0.000134661 | 1(Win) | true |
| simdjson (stage-1) | 13826.8 | 0.130143 | 6587.74ms | 7351818 | 80 | 3.48398e+07 | 507075 | 0.0210812 | 0.368943 | 1.7809 | 0.0660418 | 0.00106483 | 0.021181 | 4.4018e-05 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 13652.9 | 0.0165609 | 3964.37ms | 461466 | 2560 | 72952.2 | 32234.2 | 0.0763721 | 0.376963 | 2.02795 | 0.131947 | 7.75551e-06 | 1.01325e-05 | 8.6875e-06 | 1(Win) | true |
| simdjson (stage-1) | 12060.3 | 0.0307862 | 4368.29ms | 461466 | 1280 | 161542 | 36490.6 | 0.00637965 | 0.422061 | 2.35067 | 0.0920372 | 3.11914e-05 | 4.50162e-06 | 2.92207e-06 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 14903.4 | 0.0745871 | 5452.56ms | 728486 | 80 | 96713.3 | 46615.9 | 0.243049 | 0.345506 | 1.8134 | 0.0990672 | 0.000153332 | 7.62712e-05 | 3.43177e-07 | 1(Win) | true |
| simdjson (stage-1) | 13548 | 0.0750615 | 5829.79ms | 728486 | 80 | 118527 | 51279.9 | 0.114144 | 0.379978 | 1.97425 | 0.0748896 | 0.000365055 | 7.30968e-06 | 3.68916e-06 | 2(Loss) | true |

----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 16529.8 | 0.139066 | 3483.85ms | 466906 | 30 | 42100.7 | 26937.8 | 0.00433078 | 0.311912 | 1.63035 | 0.0987587 | 3.09841e-05 | 2.35593e-06 | 1.42784e-06 | 1(Win) | true |
| simdjson (stage-1) | 14048.8 | 0.127333 | 3915.67ms | 466906 | 4890 | 7.96473e+06 | 31695.1 | 0.0262699 | 0.364708 | 1.93522 | 0.0728777 | 2.69205e-05 | 4.51565e-06 | 2.33009e-06 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 16794 | 0.0437825 | 4360.09ms | 631514 | 160 | 39443.9 | 35861.6 | 0.0373345 | 0.30692 | 1.63181 | 0.0839744 | 1.75273e-05 | 6.45275e-06 | 5.70059e-06 | 1(Win) | true |
| simdjson (stage-1) | 15465.5 | 0.07044 | 4605.95ms | 631514 | 80 | 60195.7 | 38942 | 0.0237476 | 0.333135 | 1.78296 | 0.0659448 | 0.000154252 | 6.19543e-06 | 4.92863e-06 | 2(Loss) | true |
