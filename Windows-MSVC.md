# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36260.0 compiler).  

Latest Results: (Oct 03, 2026)
#### Using the following commits:
----
| Jsonifier: [3ca767b](https://github.com/nihilai-collective/jsonifier/commit/3ca767b)  
| Glaze: [52971fe](https://github.com/stephenberry/glaze/commit/52971fe)  
| Simdjson: [2a690bc](https://github.com/simdjson/simdjson/commit/2a690bc)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX512` |
| simdjson (ondemand) | `icelake` |
| Glaze (utf8-validation) | `AVX512BW` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |
| Glaze (structural-skip) | `AVX512BW` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (AMD EPYC 9V45 96-Core Processor-AVX512): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 5.000000% AND mean shift < 2.500000%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

Every iteration constructs a new object to parse into, or a new string to serialize into, and destroys it again inside the timed region, so allocation and deallocation are part of each measurement. Parser instances are reused.

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

`simdjson (reflection)` (simdjson 5's C++26 static-reflection API) is absent from these results because this compiler does not provide P2996 reflection.

`simdjson (ondemand)` extracts each field with an individual `find_field` lookup (`find_field_unordered` for the reverse-order tests) on MSVC/Windows, rather than the `object::for_each` API used on the other platforms, because instantiating `for_each` across these test structures drives MSVC compile times to intractable levels.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [4e7c701](https://github.com/nihilai-collective/benchmarksuite/commit/4e7c701).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 469.431 | 0.396812 | 187.298ms | 905 | 2560 | 136258 | 1838.55 | 5.19726 | 1(Win) |
| glaze | 326.035 | 0.27035 | 269.599ms | 905 | 1280 | 65558.9 | 2647.19 | 7.5055 | 2(Loss) |
| simdjson (ondemand) | 96.7963 | 0.172514 | 909.449ms | 905 | 2560 | 605717 | 8916.41 | 25.4985 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 941.999 | 0.363547 | 93.7543ms | 905 | 4890 | 54253.2 | 916.217 | 2.54923 | 1(Win) |
| glaze | 78.9106 | 0.395934 | 1167.96ms | 905 | 2560 | 4.80079e+06 | 10937.4 | 31.2771 | 2(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 650.52 | 0.241806 | 278.104ms | 1811 | 2560 | 105509 | 2654.96 | 3.76768 | 1(Win) |
| glaze | 308.136 | 0.109721 | 534.474ms | 1811 | 40 | 1512.82 | 5605 | 7.99804 | 2(Loss) |
| simdjson (ondemand) | 138.427 | 0.0629498 | 1307.02ms | 1811 | 30 | 1850.57 | 12476.7 | 17.8347 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 199.041 | 0.165361 | 874.606ms | 1811 | 2560 | 527063 | 8677.15 | 12.3751 | 1(Win) |
| glaze | 136.821 | 0.411314 | 1271.83ms | 1798 | 2560 | 6.80236e+06 | 12532.5 | 18.0507 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1935.92 | 0.13345 | 195.017ms | 3862 | 320 | 2062.7 | 1902.5 | 1.26073 | 1(Win) |
| glaze | 805.687 | 0.22971 | 466.827ms | 3862 | 2560 | 282287 | 4571.37 | 3.05178 | 2(Loss) |
| simdjson (ondemand) | 318.619 | 0.148406 | 1174.45ms | 3862 | 2560 | 753399 | 11559.5 | 7.75222 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 451.083 | 0.0976783 | 836.773ms | 3862 | 80 | 5088.61 | 8165 | 5.46959 | 1(Win) |
| glaze | 327.289 | 0.351178 | 1146.09ms | 3862 | 4890 | 7.63703e+06 | 11253.3 | 7.54382 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 978.237 | 0.0838584 | 953.783ms | 9578 | 80 | 4905.06 | 9337.5 | 2.51618 | 1(Win) |
| glaze | 712.833 | 0.172083 | 1304.42ms | 9578 | 2560 | 1.24477e+06 | 12814.1 | 3.4603 | 2(Loss) |
| simdjson (ondemand) | 553.817 | 0.145157 | 1675.71ms | 9578 | 30 | 17195.4 | 16493.3 | 4.45656 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1167.02 | 0.231227 | 788.231ms | 9578 | 2560 | 838519 | 7827.03 | 2.11422 | 1(Win) |
| glaze | 842.064 | 0.0912709 | 1123.71ms | 9578 | 80 | 7841.77 | 10847.5 | 2.93285 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1837.6 | 0.298082 | 204.036ms | 3873 | 40 | 1435.9 | 2010 | 1.33572 | 1(Win) |
| glaze | 888.681 | 0.134287 | 423.509ms | 3873 | 80 | 2492.09 | 4156.25 | 2.76921 | 2(Loss) |
| simdjson (ondemand) | 321.329 | 0.3504 | 1163.37ms | 3873 | 640 | 1.03825e+06 | 11494.7 | 7.68727 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 428.018 | 0.255028 | 859.227ms | 3873 | 2560 | 1.2399e+06 | 8629.49 | 5.75397 | 1(Win) |
| glaze | 339.068 | 0.0977608 | 1126.01ms | 3873 | 30 | 3402.3 | 10893.3 | 7.27835 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 570.504 | 1.1251 | 5397.24ms | 2090234 | 80 | 1.23636e+11 | 3.49411e+06 | 4.33969 | 1(Win) |
| simdjson (ondemand) | 190.676 | 0.569302 | 7537.11ms | 2090234 | 30 | 1.06269e+11 | 1.04544e+07 | 12.9846 | 2(Loss) |
| glaze | 185.866 | 0.625664 | 7540.18ms | 2090234 | 30 | 1.3508e+11 | 1.07249e+07 | 13.3205 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1003.17 | 0.0709089 | 6239.99ms | 2090234 | 160 | 3.17659e+08 | 1.9871e+06 | 2.46786 | 1(Win) |
| glaze | 786.533 | 0.11152 | 7895.53ms | 2090234 | 40 | 3.19539e+08 | 2.53442e+06 | 3.14764 | 2(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2131.82 | 0.322092 | 9177.63ms | 6661897 | 30 | 2.76425e+09 | 2.98022e+06 | 1.16134 | 1(Win) |
| glaze | 1374.87 | 0.064605 | 6925.97ms | 6661897 | 80 | 7.13011e+08 | 4.62101e+06 | 1.80075 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1156.35 | 0.530036 | 5462.58ms | 500299 | 80 | 3.82633e+08 | 412611 | 2.14088 | 1(Win) |
| glaze | 761.419 | 0.20168 | 7779.31ms | 500299 | 160 | 2.55539e+08 | 626622 | 3.25138 | 2(Loss) |
| simdjson (ondemand) | 427.405 | 0.143056 | 7228.22ms | 500299 | 40 | 1.02012e+08 | 1.11632e+06 | 5.79254 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7767.89 | 0.105056 | 6175.81ms | 500299 | 2560 | 1.06595e+07 | 61422.4 | 0.318567 | 1(Win) |
| glaze | 3469.37 | 0.254991 | 7005.89ms | 500299 | 160 | 1.96757e+07 | 137524 | 0.713423 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2329.48 | 0.210444 | 7435.97ms | 1439562 | 40 | 6.15282e+07 | 589348 | 1.06275 | 1(Win) |
| glaze | 1748.55 | 0.170027 | 5021.2ms | 1439562 | 160 | 2.85141e+08 | 785151 | 1.41586 | 2(Loss) |
| simdjson (ondemand) | 1059.55 | 0.061241 | 8295.25ms | 1439562 | 320 | 2.01491e+08 | 1.29572e+06 | 2.33662 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4301.97 | 0.307206 | 8203.22ms | 1439562 | 160 | 1.53782e+08 | 319127 | 0.57536 | 1(Win) |
| glaze | 1939.58 | 0.721377 | 9000.27ms | 1439584 | 320 | 8.34324e+09 | 707831 | 1.27625 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1133.96 | 0.0751821 | 4802.81ms | 56369 | 4890 | 6.21193e+06 | 47407.2 | 2.18203 | 1(Win) |
| jsonifier | 833.495 | 0.0559423 | 6453.76ms | 56369 | 4890 | 6.36596e+06 | 64496.7 | 2.96909 | 2(Loss) |
| simdjson (ondemand) | 436.532 | 0.0935984 | 6283.46ms | 56369 | 1280 | 1.70058e+07 | 123147 | 5.6704 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7908.45 | 0.0942673 | 714.138ms | 56369 | 80 | 3284.81 | 6797.5 | 0.311142 | 1(Win) |
| glaze | 3219.35 | 0.361323 | 1655.88ms | 56369 | 640 | 2.32978e+06 | 16698.3 | 0.767582 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1753.26 | 0.346511 | 5213.69ms | 94370 | 160 | 5.06206e+06 | 51331.9 | 1.41134 | 1(Win) |
| jsonifier | 1181.9 | 0.231259 | 7817.54ms | 94370 | 320 | 9.92331e+06 | 76147.2 | 2.09397 | 2(Loss) |
| simdjson (ondemand) | 699.841 | 0.057097 | 6586.82ms | 94370 | 2560 | 1.38018e+07 | 128598 | 3.53686 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11060.6 | 0.13769 | 853.306ms | 94370 | 4890 | 613789 | 8136.81 | 0.222915 | 1(Win) |
| glaze | 3045.16 | 0.111478 | 2951.57ms | 94370 | 4890 | 5.30807e+06 | 29554.5 | 0.812121 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1170.98 | 0.126087 | 990.783ms | 11812 | 30 | 4413.79 | 9620 | 2.1076 | 1(Win) |
| glaze | 953.599 | 0.185101 | 1211.46ms | 11812 | 2560 | 1.22397e+06 | 11812.9 | 2.58972 | 2(Loss) |
| simdjson (ondemand) | 400.566 | 0.0914906 | 2817.4ms | 11812 | 4890 | 3.23713e+06 | 28122.2 | 6.17429 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5707.31 | 0.26651 | 202.487ms | 11812 | 80 | 2213.61 | 1973.75 | 0.427569 | 1(Win) |
| glaze | 2683.69 | 0.126965 | 419.868ms | 11812 | 80 | 2272.15 | 4197.5 | 0.916172 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2299.12 | 0.0724504 | 1307.18ms | 31235 | 80 | 7049.05 | 12956.2 | 1.07464 | 1(Win) |
| glaze | 1891.6 | 0.377127 | 1610.97ms | 31235 | 640 | 2.25724e+06 | 15747.5 | 1.30623 | 2(Loss) |
| simdjson (ondemand) | 983.364 | 0.0817829 | 3030ms | 31235 | 4890 | 3.00116e+06 | 30292 | 2.5152 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 12245.8 | 0.308325 | 261.798ms | 31235 | 40 | 2250 | 2432.5 | 0.199649 | 1(Win) |
| glaze | 3644.61 | 0.140971 | 822.832ms | 31235 | 4890 | 649155 | 8173.17 | 0.676579 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1123.61 | 0.0579612 | 9291.53ms | 108313 | 4890 | 1.38839e+07 | 91931.3 | 2.20271 | 1(Win) |
| glaze | 1000.45 | 0.0910895 | 5318.1ms | 108313 | 2560 | 2.26436e+07 | 103249 | 2.47389 | 2(Loss) |
| simdjson (ondemand) | 479.498 | 0.099252 | 5488.27ms | 108313 | 640 | 2.92581e+07 | 215424 | 5.16263 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10136.9 | 0.0981354 | 1061.48ms | 108313 | 30 | 3000 | 10190 | 0.243277 | 1(Win) |
| glaze | 3404.94 | 0.273804 | 3036.08ms | 108313 | 320 | 2.20785e+06 | 30336.9 | 0.726325 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1585.67 | 0.134503 | 6734.47ms | 213963 | 640 | 1.91731e+07 | 128684 | 1.56097 | 1(Win) |
| jsonifier | 1511.17 | 0.128524 | 6921.76ms | 213963 | 640 | 1.92753e+07 | 135028 | 1.63799 | 2(Loss) |
| simdjson (ondemand) | 886.248 | 0.103876 | 5876.98ms | 213963 | 1280 | 7.32168e+07 | 230242 | 2.79322 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 17008.1 | 0.228766 | 1217.91ms | 213963 | 2560 | 1.92836e+06 | 11997.3 | 0.145192 | 1(Win) |
| glaze | 3652 | 0.473988 | 5629.47ms | 213963 | 640 | 4.4888e+07 | 55873.8 | 0.677639 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 480.955 | 0.207226 | 5492.95ms | 1834197 | 80 | 4.54424e+09 | 3.63699e+06 | 5.14772 | 1(Win) |
| glaze | 193.697 | 0.445816 | 6321.58ms | 1834197 | 30 | 4.86271e+10 | 9.03073e+06 | 12.782 | 2(Loss) |
| simdjson (ondemand) | 84.4029 | 3.02023 | 6218.34ms | 1834197 | 30 | 1.17538e+13 | 2.07247e+07 | 29.3329 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1826.48 | 0.179315 | 7594.29ms | 9930848 | 30 | 2.59358e+09 | 5.18528e+06 | 1.35532 | 1(Win) |
| glaze | 896.977 | 0.528154 | 7477.62ms | 9930848 | 40 | 1.24392e+11 | 1.05586e+07 | 2.76012 | 2(Loss) |
| simdjson (ondemand) | 436.597 | 0.245405 | 6630.08ms | 9930848 | 30 | 8.50157e+10 | 2.16923e+07 | 5.67076 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2377.42 | 0.0845349 | 6035.31ms | 9930848 | 30 | 3.40217e+08 | 3.98365e+06 | 1.04138 | 1(Win) |
| glaze | 1611.09 | 0.112551 | 8970.22ms | 9930228 | 30 | 1.31309e+09 | 5.87814e+06 | 1.53672 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 490.219 | 0.312459 | 5341.59ms | 1834197 | 80 | 9.94463e+09 | 3.56826e+06 | 5.05042 | 1(Win) |
| simdjson (ondemand) | 210.33 | 0.328791 | 5855.13ms | 1834197 | 40 | 2.9908e+10 | 8.31657e+06 | 11.7711 | 2(Loss) |
| glaze | 199.084 | 0.072307 | 6316.07ms | 1834197 | 40 | 1.6145e+09 | 8.78635e+06 | 12.4361 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 701.599 | 0.0631178 | 7761.26ms | 1834197 | 80 | 1.98111e+08 | 2.4932e+06 | 3.52874 | 1(Win) |
| glaze | 585.235 | 0.10491 | 9443.82ms | 1833577 | 160 | 1.57215e+09 | 2.98792e+06 | 4.23032 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1977.36 | 0.165383 | 7212.5ms | 9930848 | 80 | 5.01967e+09 | 4.78963e+06 | 1.25209 | 1(Win) |
| simdjson (ondemand) | 1015.09 | 0.421784 | 6568.9ms | 9930848 | 30 | 4.64589e+10 | 9.33005e+06 | 2.43903 | 2(Loss) |
| glaze | 953.365 | 0.098992 | 7053.16ms | 9930848 | 40 | 3.86825e+09 | 9.93407e+06 | 2.59695 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2380.15 | 0.128373 | 5967.09ms | 9930848 | 80 | 2.08737e+09 | 3.97907e+06 | 1.04018 | 1(Win) |
| glaze | 1229.33 | 0.0792906 | 5380.07ms | 9930228 | 40 | 1.49239e+09 | 7.70353e+06 | 2.01387 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 862.725 | 0.144445 | 9101.5ms | 642697 | 160 | 1.68497e+08 | 710451 | 2.86966 | 1(Win) |
| simdjson (ondemand) | 527.527 | 0.191516 | 7425.68ms | 642697 | 30 | 1.48544e+08 | 1.16188e+06 | 4.69315 | 2(Loss) |
| glaze | 497.425 | 0.121373 | 7819.85ms | 642697 | 40 | 8.94674e+07 | 1.23219e+06 | 4.97711 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1081.02 | 0.0981884 | 7269.71ms | 642697 | 320 | 9.91774e+07 | 566984 | 2.29004 | 1(Win) |
| glaze | 1004.27 | 0.14471 | 7859.08ms | 642692 | 160 | 1.24802e+08 | 610312 | 2.46477 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1139.74 | 0.178804 | 6505.32ms | 1225964 | 30 | 1.0093e+08 | 1.02582e+06 | 2.17223 | 1(Win) |
| simdjson (ondemand) | 962.398 | 0.109956 | 7668.67ms | 1225964 | 80 | 1.4275e+08 | 1.21485e+06 | 2.5725 | 2(Loss) |
| glaze | 857.156 | 0.195888 | 8679.22ms | 1225964 | 160 | 1.14227e+09 | 1.36401e+06 | 2.88835 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1698.87 | 0.185151 | 8742.58ms | 1225964 | 640 | 1.03913e+09 | 688207 | 1.45717 | 1(Win) |
| glaze | 1541.97 | 0.210059 | 9786.74ms | 1225970 | 320 | 8.11779e+08 | 758235 | 1.60542 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 809.361 | 0.219139 | 6251.15ms | 409725 | 80 | 8.95426e+07 | 482781 | 3.05881 | 1(Win) |
| glaze | 715.725 | 0.107668 | 6929.34ms | 409725 | 320 | 1.10565e+08 | 545942 | 3.45895 | 2(Loss) |
| simdjson (ondemand) | 425.595 | 0.0737059 | 5856.14ms | 409725 | 320 | 1.46536e+08 | 918112 | 5.81706 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2320.48 | 0.0831084 | 8711.5ms | 409725 | 2560 | 5.0137e+07 | 168389 | 1.06663 | 1(Win) |
| jsonifier | 2147.88 | 0.141375 | 9364.27ms | 409725 | 640 | 4.23343e+07 | 181921 | 1.15208 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1316.23 | 0.108027 | 7238.85ms | 785750 | 640 | 2.42077e+08 | 569317 | 1.88089 | 1(Win) |
| glaze | 1230.54 | 0.255666 | 7768.94ms | 785750 | 40 | 9.69569e+07 | 608958 | 2.01183 | 2(Loss) |
| simdjson (ondemand) | 784.309 | 0.0630648 | 6152.44ms | 785750 | 320 | 1.16177e+08 | 955427 | 3.15658 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3128.71 | 0.105992 | 6119.25ms | 785750 | 1280 | 8.24888e+07 | 239507 | 0.790993 | 1(Win) |
| glaze | 2001.01 | 0.2878 | 9553.88ms | 785750 | 80 | 9.29269e+07 | 374485 | 1.23693 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4823.95 | 0.157037 | 5229.73ms | 264040 | 4890 | 3.28585e+07 | 52199.6 | 0.512883 | 1(Win) |
| glaze | 2451.01 | 0.414609 | 5295.68ms | 264040 | 320 | 5.80601e+07 | 102737 | 1.0098 | 2(Loss) |
| simdjson (ondemand) | 2380.05 | 0.209223 | 5418.34ms | 264040 | 160 | 7.83981e+06 | 105799 | 1.03994 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6524.45 | 0.048243 | 5964.71ms | 399947 | 30 | 23862.1 | 58460 | 0.379291 | 1(Win) |
| glaze | 3300.44 | 0.109011 | 5948.35ms | 399947 | 1280 | 2.03148e+07 | 115566 | 0.749967 | 2(Loss) |
| simdjson (ondemand) | 3104.85 | 0.339983 | 6303.8ms | 399947 | 80 | 1.39549e+07 | 122846 | 0.797203 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1090.82 | 0.106827 | 5904.51ms | 264040 | 1280 | 7.78412e+07 | 230844 | 2.26926 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1086.66 | 0.179406 | 5962.51ms | 264040 | 320 | 5.53068e+07 | 231727 | 2.27807 | 1(Tie) |
| simdjson (ondemand) | 625.002 | 0.0984506 | 5209.09ms | 264040 | 640 | 1.00692e+08 | 402892 | 3.96092 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6454.09 | 0.248812 | 3925.35ms | 264040 | 320 | 3.01553e+06 | 39015.3 | 0.383298 | 1(Win) |
| glaze | 4202.52 | 0.369413 | 5981.34ms | 263923 | 1280 | 6.26572e+07 | 59891.9 | 0.58879 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1450.47 | 0.214889 | 6914.02ms | 399947 | 160 | 5.109e+07 | 262962 | 1.70657 | 1(Win) |
| jsonifier | 1312.61 | 0.0876546 | 7407.42ms | 399947 | 1280 | 8.30411e+07 | 290581 | 1.886 | 2(Loss) |
| simdjson (ondemand) | 908.857 | 0.119839 | 5425.78ms | 399947 | 320 | 8.094e+07 | 419669 | 2.7238 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8266.06 | 0.268697 | 4641.11ms | 399947 | 320 | 4.91907e+06 | 46142.8 | 0.299349 | 1(Win) |
| glaze | 4064.71 | 0.428641 | 9430.04ms | 399830 | 640 | 1.0348e+08 | 93809.2 | 0.608812 | 2(Loss) |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 518.862 | 0.124814 | 889.47ms | 4630 | 40 | 4512.82 | 8510 | 4.75678 | 1(Win) |
| simdjson (ondemand) | 167.092 | 0.0923767 | 2684.74ms | 4630 | 4890 | 2.91396e+06 | 26425.6 | 14.801 | 2(Loss) |
| glaze | 164.206 | 0.101518 | 2716.18ms | 4630 | 4890 | 3.644e+06 | 26890.1 | 15.0608 | 3(Loss) |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1617.4 | 0.188857 | 274.301ms | 4630 | 80 | 2126.58 | 2730 | 1.51491 | 1(Win) |
| glaze | 972.003 | 0.260982 | 459.577ms | 4630 | 2560 | 359822 | 4542.7 | 2.52816 | 2(Loss) |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1352.43 | 0.16371 | 1046ms | 14795 | 2560 | 746778 | 10432.8 | 1.82558 | 1(Win) |
| simdjson (ondemand) | 499.085 | 0.0851649 | 2823.65ms | 14795 | 4890 | 2.83473e+06 | 28271 | 4.95594 | 2(Loss) |
| glaze | 482.655 | 0.0412756 | 2941.73ms | 14795 | 30 | 4367.82 | 29233.3 | 5.12496 | 3(Loss) |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4359.86 | 0.167124 | 329.284ms | 14795 | 80 | 2340.19 | 3236.25 | 0.563221 | 1(Win) |
| glaze | 2543.76 | 0.214766 | 559.957ms | 14795 | 2560 | 363288 | 5546.76 | 0.968457 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 763.539 | 0.193674 | 645.428ms | 5092 | 30 | 4551.72 | 6360 | 3.22514 | 1(Win) |
| glaze | 530.204 | 0.190342 | 929.451ms | 5092 | 2560 | 778036 | 9158.95 | 4.65525 | 2(Loss) |
| simdjson (ondemand) | 341.803 | 0.276061 | 1412.95ms | 5092 | 1280 | 1.969e+06 | 14207.3 | 7.22889 | 3(Loss) |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5676.2 | 0.409367 | 89.4631ms | 5092 | 4890 | 59978.7 | 855.521 | 0.422156 | 1(Win) |
| glaze | 2698.72 | 0.39733 | 183.361ms | 5092 | 2560 | 130859 | 1799.41 | 0.899987 | 2(Loss) |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1340.24 | 0.158841 | 842.673ms | 11724 | 4890 | 858660 | 8342.47 | 1.84061 | 1(Win) |
| glaze | 1042.28 | 0.140559 | 1098.42ms | 11724 | 4890 | 1.11175e+06 | 10727.3 | 2.36879 | 2(Loss) |
| simdjson (ondemand) | 749.398 | 0.121296 | 1499.75ms | 11724 | 4890 | 1.60151e+06 | 14919.8 | 3.29735 | 3(Loss) |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9840.16 | 0.476 | 119.118ms | 11724 | 80 | 2340.19 | 1136.25 | 0.24615 | 1(Win) |
| glaze | 3766.91 | 0.221771 | 297.581ms | 11746 | 80 | 3479.43 | 2973.75 | 0.650326 | 2(Loss) |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 951.984 | 0.123657 | 497.81ms | 4857 | 160 | 5792.06 | 4865.62 | 2.58561 | 1(Win) |
| jsonifier | 750.425 | 0.141115 | 637.841ms | 4857 | 80 | 6069.62 | 6172.5 | 3.28332 | 2(Loss) |
| simdjson (ondemand) | 498.6 | 0.153907 | 956.204ms | 4857 | 80 | 16354.4 | 9290 | 4.95008 | 3(Loss) |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4915.14 | 0.375669 | 97.5148ms | 4857 | 4890 | 61289 | 942.393 | 0.488756 | 1(Win) |
| glaze | 2903.22 | 0.16391 | 164.222ms | 4857 | 640 | 4376.93 | 1595.47 | 0.83393 | 2(Loss) |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1272.7 | 0.247965 | 569.534ms | 7376 | 2560 | 480850 | 5527.07 | 1.93288 | 1(Win) |
| jsonifier | 851.775 | 0.147074 | 838.334ms | 7376 | 4890 | 721399 | 8258.4 | 2.89606 | 2(Loss) |
| simdjson (ondemand) | 722.561 | 0.177682 | 981.853ms | 7376 | 2560 | 765987 | 9735.23 | 3.41549 | 3(Loss) |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7145.96 | 0.211358 | 102.922ms | 7376 | 320 | 1385.19 | 984.375 | 0.336143 | 1(Win) |
| glaze | 2758.55 | 0.525384 | 240.185ms | 7376 | 40 | 7179.49 | 2550 | 0.887134 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1026.13 | 0.297293 | 425.024ms | 4390 | 30 | 4413.79 | 4080 | 2.39547 | 1(Win) |
| glaze | 904.484 | 0.11555 | 482.611ms | 4390 | 160 | 4577.04 | 4628.75 | 2.71838 | 2(Loss) |
| simdjson (ondemand) | 401.692 | 0.0835726 | 1069.83ms | 4390 | 80 | 6069.62 | 10422.5 | 6.14767 | 3(Loss) |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3232.92 | 0.597197 | 108.486ms | 4390 | 80 | 4784.81 | 1295 | 0.750222 | 1(Win) |
| glaze | 2668.77 | 0.351234 | 161.034ms | 4390 | 80 | 2428.8 | 1568.75 | 0.913622 | 2(Loss) |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2064.79 | 0.114319 | 566.336ms | 11521 | 80 | 2960.44 | 5321.25 | 1.19263 | 1(Win) |
| glaze STATISTICAL TIE | 962.39 | 0.210334 | 636.399ms | 11521 | 30 | 17298.9 | 11416.7 | 2.5687 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 956.768 | 0.398406 | 1212.08ms | 11521 | 640 | 1.33967e+06 | 11483.8 | 2.58101 | 2(Tie) |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11619.1 | 0.417718 | 102.751ms | 11521 | 160 | 2496.46 | 945.625 | 0.207258 | 1(Win) |
| glaze | 3532.18 | 0.103783 | 326.521ms | 11521 | 320 | 3335.03 | 3110.62 | 0.694807 | 2(Loss) |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1112.73 | 0.188858 | 425.994ms | 4669 | 4890 | 279288 | 4001.62 | 2.20893 | 1(Win) |
| glaze | 954.833 | 0.217701 | 512.916ms | 4669 | 30 | 3091.95 | 4663.33 | 2.57234 | 2(Loss) |
| simdjson (ondemand) | 473.524 | 0.213199 | 963.814ms | 4669 | 30 | 12057.5 | 9403.33 | 5.20407 | 3(Loss) |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7272.51 | 0.635742 | 64.7115ms | 4669 | 2560 | 38786.6 | 612.266 | 0.324777 | 1(Win) |
| glaze | 2986.36 | 0.422663 | 154.448ms | 4669 | 2560 | 101670 | 1491.02 | 0.809906 | 2(Loss) |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1489.33 | 0.165431 | 604.432ms | 9249 | 40 | 3839.74 | 5922.5 | 1.65265 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1488.28 | 0.160445 | 599.903ms | 9249 | 30 | 2712.64 | 5926.67 | 1.65696 | 1(Tie) |
| simdjson (ondemand) | 892.88 | 0.084382 | 1008.58ms | 9249 | 160 | 11117.9 | 9878.75 | 2.76509 | 3(Loss) |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 12127 | 0.244323 | 77.2557ms | 9249 | 640 | 2021.1 | 727.344 | 0.19635 | 1(Win) |
| glaze | 3617.29 | 0.191467 | 249.029ms | 9249 | 640 | 13950.6 | 2438.44 | 0.675636 | 2(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 393.433 | 0.0921446 | 1133.97ms | 4604 | 30 | 3172.41 | 11160 | 6.27354 | 1(Win) |
| glaze | 160.597 | 0.0622504 | 2814.84ms | 4604 | 30 | 8689.66 | 27340 | 15.3995 | 2(Loss) |
| simdjson (ondemand) | 63.8117 | 0.120773 | 6813.52ms | 4604 | 1280 | 8.83932e+06 | 68807.3 | 38.7822 | 3(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1181.89 | 0.153909 | 384.539ms | 4604 | 40 | 1307.69 | 3715 | 2.08551 | 1(Win) |
| glaze | 845.995 | 0.130968 | 520.627ms | 4604 | 80 | 3696.2 | 5190 | 2.9096 | 2(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1592.87 | 0.135633 | 1480.65ms | 24579 | 4890 | 1.94809e+06 | 14715.8 | 1.5513 | 1(Win) |
| glaze | 743.006 | 0.121588 | 3191.8ms | 24579 | 2560 | 3.76673e+06 | 31548 | 3.3292 | 2(Loss) |
| simdjson (ondemand) | 329.686 | 0.0685089 | 7104.65ms | 24579 | 4890 | 1.16019e+07 | 71099 | 7.50669 | 3(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5574.82 | 0.248816 | 424.583ms | 24579 | 2560 | 280197 | 4204.69 | 0.440988 | 1(Win) |
| glaze | 3191.64 | 0.192409 | 740.304ms | 24579 | 2560 | 511198 | 7344.3 | 0.772878 | 2(Loss) |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 410.962 | 0.121789 | 1072.03ms | 4604 | 4890 | 827926 | 10684 | 6.00878 | 1(Win) |
| glaze | 157.719 | 0.10884 | 2798ms | 4604 | 4890 | 4.48944e+06 | 27838.9 | 15.6807 | 2(Loss) |
| simdjson (ondemand) | 143.07 | 0.2175 | 3058.41ms | 4604 | 640 | 2.85148e+06 | 30689.2 | 17.2885 | 3(Loss) |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1184.28 | 0.0561254 | 377.757ms | 4604 | 320 | 1385.58 | 3707.5 | 2.07482 | 1(Win) |
| glaze | 829.917 | 0.224055 | 532.036ms | 4604 | 2560 | 359707 | 5290.55 | 2.96597 | 2(Loss) |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1625.17 | 0.203155 | 1443.59ms | 24579 | 2560 | 2.198e+06 | 14423.3 | 1.52038 | 1(Win) |
| glaze | 753.79 | 0.06067 | 3200.85ms | 24579 | 30 | 10678.2 | 31096.7 | 3.28264 | 2(Loss) |
| simdjson (ondemand) | 717.674 | 0.206177 | 3290.95ms | 24579 | 640 | 2.90224e+06 | 32661.6 | 3.44712 | 3(Loss) |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5675.63 | 0.206044 | 424.316ms | 24579 | 30 | 2172.41 | 4130 | 0.433381 | 1(Win) |
| glaze | 3200.55 | 0.168317 | 736.985ms | 24579 | 4890 | 743098 | 7323.87 | 0.770185 | 2(Loss) |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 532.21 | 0.196128 | 257.999ms | 1181 | 80 | 1378.16 | 2116.25 | 4.59649 | 1(Win) |
| glaze | 185.715 | 0.398 | 627.425ms | 1181 | 1280 | 745729 | 6064.61 | 13.2676 | 2(Loss) |
| simdjson (ondemand) | 181.094 | 0.0950987 | 650.603ms | 1181 | 160 | 5597.09 | 6219.38 | 13.6019 | 3(Loss) |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1716.66 | 0.752178 | 69.6641ms | 1181 | 2560 | 62346.6 | 656.094 | 1.38046 | 1(Win) |
| glaze | 957.186 | 0.667482 | 127.986ms | 1181 | 30 | 1850.57 | 1176.67 | 2.49862 | 2(Loss) |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 835.218 | 0.197384 | 355.69ms | 2496 | 80 | 2531.65 | 2850 | 2.93903 | 1(Win) |
| simdjson (ondemand) | 373.685 | 0.170493 | 728.945ms | 2496 | 40 | 4717.95 | 6370 | 6.58745 | 2(Loss) |
| glaze | 371.136 | 0.1065 | 664.526ms | 2496 | 80 | 3732.59 | 6413.75 | 6.64296 | 3(Loss) |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3071.45 | 0.628616 | 80.0799ms | 2496 | 80 | 1898.73 | 775 | 0.773543 | 1(Win) |
| glaze | 1815.73 | 0.350187 | 145.727ms | 2507 | 4890 | 103972 | 1316.75 | 1.33004 | 2(Loss) |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 808.028 | 0.186882 | 589.571ms | 4926 | 4890 | 577270 | 5813.91 | 3.0371 | 1(Win) |
| glaze | 734.031 | 0.211895 | 675.109ms | 4926 | 30 | 5517.24 | 6400 | 3.35178 | 2(Loss) |
| simdjson (ondemand) | 414.897 | 0.351149 | 1143.18ms | 4926 | 640 | 1.01175e+06 | 11322.8 | 5.94083 | 3(Loss) |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4382.84 | 0.284008 | 110.771ms | 4926 | 4890 | 45315.6 | 1071.86 | 0.550266 | 1(Win) |
| glaze | 2404.5 | 0.180926 | 201.155ms | 4926 | 320 | 3998.43 | 1953.75 | 1.01332 | 2(Loss) |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1309.36 | 0.294314 | 695.763ms | 9463 | 2560 | 1.05342e+06 | 6892.38 | 1.87736 | 1(Win) |
| glaze | 1241.35 | 0.28097 | 751.851ms | 9463 | 30 | 12517.2 | 7270 | 1.97997 | 2(Loss) |
| simdjson (ondemand) | 762 | 0.132323 | 1203.32ms | 9463 | 30 | 7367.82 | 11843.3 | 3.23403 | 3(Loss) |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7535.54 | 0.300766 | 123.149ms | 9463 | 4890 | 63444.9 | 1197.61 | 0.320684 | 1(Win) |
| glaze | 2973.52 | 0.115207 | 311.629ms | 9463 | 320 | 3912.23 | 3035 | 0.825823 | 2(Loss) |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3764.74 | 0.140775 | 76.6564ms | 2821 | 1280 | 1295.39 | 714.609 | 0.630666 | 1(Win) |
| glaze | 2600.03 | 0.287387 | 107.442ms | 2821 | 4890 | 43240.7 | 1034.72 | 0.922861 | 2(Loss) |
| simdjson (ondemand) | 2429.18 | 0.267574 | 115.622ms | 2821 | 80 | 702.532 | 1107.5 | 0.994692 | 3(Loss) |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5159.25 | 0.344579 | 81.3746ms | 4147 | 320 | 2232.66 | 766.562 | 0.464201 | 1(Win) |
| glaze | 3571 | 0.188608 | 117.731ms | 4147 | 160 | 698.113 | 1107.5 | 0.675809 | 2(Loss) |
| simdjson (ondemand) | 3138.02 | 0.153568 | 130.588ms | 4147 | 640 | 2397.4 | 1260.31 | 0.77025 | 3(Loss) |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1365.06 | 0.256859 | 201.21ms | 2821 | 4890 | 125314 | 1970.84 | 1.7854 | 1(Win) |
| jsonifier | 1192.71 | 0.174678 | 242.459ms | 2821 | 160 | 2483.88 | 2255.62 | 2.05189 | 2(Loss) |
| simdjson (ondemand) | 739.606 | 0.246352 | 373.73ms | 2821 | 80 | 6424.05 | 3637.5 | 3.32211 | 3(Loss) |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4719.85 | 0.318042 | 61.0036ms | 2821 | 640 | 2103.29 | 570 | 0.500677 | 1(Win) |
| glaze | 3679.6 | 0.2514 | 77.1477ms | 2819 | 640 | 2159.23 | 730.625 | 0.64242 | 2(Loss) |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1753.83 | 0.128116 | 242.246ms | 4147 | 320 | 2670.85 | 2255 | 1.39212 | 1(Win) |
| jsonifier | 1357.08 | 0.212141 | 304.81ms | 4147 | 2560 | 97846.7 | 2914.26 | 1.80526 | 2(Loss) |
| simdjson (ondemand) | 1039.73 | 0.249424 | 387.254ms | 4147 | 80 | 7200.95 | 3803.75 | 2.36002 | 3(Loss) |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6774.97 | 0.18072 | 62.326ms | 4147 | 1280 | 1424.55 | 583.75 | 0.34745 | 1(Win) |
| glaze | 3189.2 | 0.291746 | 127.97ms | 4145 | 4890 | 63944.5 | 1239.49 | 0.755814 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3257.21 | 0.110634 | 7146.42ms | 466906 | 1280 | 2.92788e+07 | 136705 | 0.759918 | 1(Win) |
| glaze | 1817.04 | 0.244618 | 6368.66ms | 466906 | 80 | 2.87473e+07 | 245056 | 1.36237 | 2(Loss) |
| simdjson (ondemand) | 1060.39 | 0.245384 | 5395.26ms | 466906 | 80 | 8.49388e+07 | 419916 | 2.33461 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2273.49 | 0.474475 | 7572.9ms | 699405 | 30 | 5.81325e+07 | 293383 | 1.08874 | 1(Win) |
| glaze | 2159.59 | 0.451633 | 7855.87ms | 699405 | 40 | 7.78302e+07 | 308858 | 1.1463 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2537.16 | 0.10449 | 6076.95ms | 631514 | 640 | 3.93732e+07 | 237375 | 0.975716 | 1(Win) |
| jsonifier | 1630.14 | 0.100366 | 9562.09ms | 631514 | 1280 | 1.75994e+08 | 369453 | 1.51864 | 2(Loss) |
