# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest Results: (Oct 03, 2026)
#### Using the following commits:
----
| Jsonifier: [3ca767b](https://github.com/nihilai-collective/jsonifier/commit/3ca767b)  
| Glaze: [52971fe](https://github.com/stephenberry/glaze/commit/52971fe)  
| Simdjson: [2a690bc](https://github.com/simdjson/simdjson/commit/2a690bc)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `NEON` |
| simdjson (ondemand) | `arm64` |
| simdjson (reflection) | `arm64` |
| Glaze (utf8-validation) | `NEON64` |
| Glaze (string-escape) | `NEON` |
| Glaze (float-write) | `NEON` |
| Glaze (structural-skip) | `NEON64` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Apple M1 (Virtual)-NEON): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 10% AND mean shift < 5%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

Every iteration constructs a new object to parse into, or a new string to serialize into, and destroys it again inside the timed region, so allocation and deallocation are part of each measurement. Parser instances are reused.

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

`simdjson (reflection)` is simdjson 5's C++26 static-reflection API (`document.get<T>()` for reads, `simdjson::to_json` into a `std::string` for writes). Its single-pass writer emits minified JSON only (pretty output is a second FracturedJson reformatting pass), so it is absent from the prettified write tests.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [4e7c701](https://github.com/nihilai-collective/benchmarksuite/commit/4e7c701).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1448.82 | 1.19667 | 82.2868ms | 905 | 4890 | 248500 | 595.71 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1398.43 | 1.59098 | 62.6051ms | 905 | 4890 | 471468 | 617.175 | 1(Tie) |
| simdjson (ondemand) | 202.348 | 0.227248 | 440.366ms | 905 | 2560 | 240513 | 4265.3 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1985.08 | 1.63871 | 45.8181ms | 905 | 4890 | 248231 | 434.781 | 1(Win) |
| glaze | 126.328 | 0.461783 | 693.164ms | 905 | 160 | 159255 | 6832 | 2(Loss) |
| simdjson (reflection) | 112.697 | 0.141796 | 776.332ms | 905 | 2560 | 301885 | 7658.4 | 3(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 949.428 | 0.447978 | 188.556ms | 1811 | 2560 | 170007 | 1819.1 | 1(Win) |
| glaze | 827.76 | 0.218047 | 211.545ms | 1811 | 4890 | 101213 | 2086.48 | 2(Loss) |
| simdjson (ondemand) | 160.162 | 0.109055 | 1090.61ms | 1811 | 2560 | 354039 | 10783.5 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 265.864 | 0.246476 | 698.149ms | 1811 | 1280 | 328154 | 6496.2 | 1(Win) |
| glaze | 179.093 | 0.868547 | 881.479ms | 1798 | 160 | 1.10645e+06 | 9574.4 | 2(Loss) |
| simdjson (reflection) | 142.652 | 0.200791 | 1349.26ms | 1997 | 4890 | 3.51396e+06 | 13350.6 | 3(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2304.91 | 0.475143 | 162.811ms | 3862 | 4890 | 281887 | 1597.93 | 1(Win) |
| glaze | 1334.26 | 0.244341 | 279.446ms | 3862 | 4890 | 222457 | 2760.4 | 2(Loss) |
| simdjson (ondemand) | 449.519 | 0.220303 | 818.321ms | 3862 | 1280 | 417041 | 8193.4 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 759.397 | 0.129049 | 489.358ms | 3862 | 4890 | 191560 | 4850.02 | 1(Win) |
| glaze | 506.141 | 0.302537 | 815.35ms | 3862 | 640 | 310183 | 7276.8 | 2(Loss) |
| simdjson (reflection) | 288.517 | 0.202899 | 1299.18ms | 3862 | 640 | 429363 | 12765.6 | 3(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1120.5 | 0.19807 | 827.649ms | 9578 | 1280 | 333714 | 8152 | 1(Win) |
| glaze | 1052.3 | 0.0965585 | 873.705ms | 9578 | 4890 | 343525 | 8680.28 | 2(Loss) |
| simdjson (ondemand) | 783.979 | 0.460812 | 1216.63ms | 9578 | 80 | 230610 | 11651.2 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1123.25 | 0.292526 | 812.22ms | 9578 | 320 | 181081 | 8132 | 1(Win) |
| jsonifier | 1080.52 | 0.206133 | 853.807ms | 9578 | 1280 | 388675 | 8453.6 | 2(Loss) |
| simdjson (reflection) | 642.97 | 0.195051 | 1477.12ms | 9578 | 320 | 245706 | 14206.4 | 3(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2277.08 | 0.523793 | 164.665ms | 3873 | 4890 | 352992 | 1622.07 | 1(Win) |
| glaze | 1496.16 | 0.417902 | 250.298ms | 3873 | 2560 | 272475 | 2468.7 | 2(Loss) |
| simdjson (ondemand) | 441.626 | 0.255497 | 847.625ms | 3873 | 640 | 292239 | 8363.6 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 775.229 | 0.206009 | 492.31ms | 3873 | 2560 | 246631 | 4764.5 | 1(Win) |
| glaze | 522.519 | 0.248138 | 721.483ms | 3873 | 640 | 196905 | 7068.8 | 2(Loss) |
| simdjson (reflection) | 301.996 | 0.0785495 | 1248.78ms | 3873 | 4890 | 451324 | 12230.6 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2257.22 | 0.1917 | 5746.57ms | 2090234 | 80 | 2.29285e+08 | 883123 | 1(Win) |
| glaze | 1511.61 | 0.199498 | 8349.98ms | 2090234 | 320 | 2.21481e+09 | 1.31873e+06 | 2(Loss) |
| simdjson (reflection) | 717.462 | 0.490061 | 8912.3ms | 2090326 | 30 | 5.56227e+09 | 2.77853e+06 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5625.15 | 0.207108 | 6992.8ms | 6661897 | 160 | 8.75466e+08 | 1.12944e+06 | 1(Win) |
| glaze | 3215.44 | 0.146753 | 6232.48ms | 6661897 | 30 | 2.5224e+08 | 1.97587e+06 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1440.7 | 0.440921 | 7391.94ms | 500299 | 40 | 8.52894e+07 | 331174 | 1(Win) |
| glaze | 1153.96 | 0.242629 | 5443.1ms | 500299 | 160 | 1.61021e+08 | 413464 | 2(Loss) |
| simdjson (reflection) | 1048.34 | 0.0727261 | 5901.3ms | 500299 | 160 | 1.75289e+07 | 455122 | 3(Loss) |
| simdjson (ondemand) | 1031.13 | 0.180299 | 6256.74ms | 500299 | 640 | 4.45446e+08 | 462716 | 4(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8039.4 | 0.053509 | 5982.38ms | 500299 | 1280 | 1.29085e+06 | 59348 | 1(Win) |
| simdjson (reflection) | 4707.65 | 0.228407 | 5434.45ms | 500299 | 40 | 2.14353e+06 | 101350 | 2(Loss) |
| glaze | 1970.14 | 0.0921437 | 6282.57ms | 500299 | 640 | 3.18695e+07 | 242176 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 15931 | 0.925067 | 9062.5ms | 1439562 | 40 | 2.54202e+07 | 86176 | 1(Win) |
| glaze | 3429.94 | 0.702736 | 5745.91ms | 1439584 | 160 | 1.26591e+09 | 400267 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1450.55 | 0.736632 | 3969.37ms | 56369 | 30 | 2.23583e+06 | 37060.3 | 1(Win) |
| glaze | 1276.76 | 0.204469 | 4335.88ms | 56369 | 2560 | 1.89737e+07 | 42104.6 | 2(Loss) |
| simdjson (reflection) | 901.815 | 0.236585 | 6178.79ms | 56369 | 2560 | 5.09167e+07 | 59610.5 | 3(Loss) |
| simdjson (ondemand) | 886.78 | 0.230685 | 6440.56ms | 56369 | 640 | 1.2516e+07 | 60621.2 | 4(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7486.88 | 0.530601 | 710.545ms | 56369 | 4890 | 7.09782e+06 | 7180.25 | 1(Win) |
| simdjson (reflection) | 4378.84 | 0.883719 | 1261.07ms | 56369 | 2560 | 3.01323e+07 | 12276.7 | 2(Loss) |
| glaze | 2662.33 | 1.03927 | 2141.77ms | 56369 | 80 | 3.52297e+06 | 20192 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8086.97 | 0.571569 | 1095.21ms | 94370 | 2560 | 1.0358e+07 | 11128.8 | 1(Win) |
| glaze | 2251.64 | 1.49363 | 4618.52ms | 94370 | 30 | 1.06925e+07 | 39970.1 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1249.97 | 0.445514 | 1028.57ms | 11812 | 4890 | 7.88285e+06 | 9012.09 | 1(Win) |
| glaze | 822.368 | 0.751863 | 1519.37ms | 11812 | 640 | 6.78846e+06 | 13698 | 2(Loss) |
| simdjson (reflection) | 774.192 | 0.820616 | 1691.1ms | 11812 | 80 | 1.14056e+06 | 14550.4 | 3(Loss) |
| simdjson (ondemand) | 588.277 | 1.7234 | 2092.55ms | 11812 | 40 | 4.3563e+06 | 19148.8 | 4(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2286.04 | 0.402239 | 1530.02ms | 31235 | 160 | 439545 | 13030.4 | 1(Win) |
| glaze | 1512.14 | 1.65465 | 2225.91ms | 31235 | 80 | 8.4996e+06 | 19699.2 | 2(Loss) |
| simdjson (ondemand) | 1461.16 | 0.340365 | 2246.5ms | 31235 | 1280 | 6.16298e+06 | 20386.6 | 3(Loss) |
| simdjson (reflection) | 1288.89 | 2.30947 | 2232.96ms | 31235 | 1280 | 3.64658e+08 | 23111.4 | 4(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9737.19 | 1.92892 | 341.087ms | 31235 | 80 | 278569 | 3059.2 | 1(Win) |
| glaze | 2506.99 | 0.643371 | 1439.89ms | 31235 | 640 | 3.74009e+06 | 11882 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2076.74 | 0.613028 | 5272.46ms | 108313 | 4890 | 4.54637e+08 | 49739.1 | 1(Win) |
| glaze | 1240.55 | 0.884325 | 9628.18ms | 108313 | 640 | 3.47008e+08 | 83266 | 2(Loss) |
| simdjson (reflection) | 1075.35 | 0.28913 | 5252.89ms | 108313 | 1280 | 9.87324e+07 | 96057.6 | 3(Loss) |
| simdjson (ondemand) | 992.438 | 0.412947 | 6265.35ms | 108313 | 640 | 1.18229e+08 | 104082 | 4(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9802.55 | 1.18783 | 1154.85ms | 108313 | 80 | 1.25339e+06 | 10537.6 | 1(Win) |
| simdjson (reflection) | 4611.4 | 1.35972 | 2724.61ms | 108313 | 30 | 2.78302e+06 | 22400 | 2(Loss) |
| glaze | 1583.58 | 0.83153 | 6978.01ms | 108313 | 80 | 2.35356e+07 | 65228.8 | 3(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 887.129 | 0.336341 | 9313.72ms | 642697 | 640 | 3.45604e+09 | 690907 | 1(Win) |
| jsonifier STATISTICAL TIE | 837.243 | 1.37822 | 9193.86ms | 642697 | 80 | 8.14394e+09 | 732074 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 826.876 | 0.359244 | 9882.26ms | 642697 | 640 | 4.53828e+09 | 741252 | 2(Tie) |
| simdjson (reflection) | 761.518 | 0.479037 | 9950.28ms | 642697 | 320 | 4.75709e+09 | 804871 | 4(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2063.46 | 0.495697 | 7808.99ms | 642697 | 320 | 6.9375e+08 | 297037 | 1(Win) |
| glaze | 1041.4 | 0.715222 | 8409.21ms | 642692 | 40 | 7.08775e+08 | 588550 | 2(Loss) |
| simdjson (reflection) | 825.761 | 0.408075 | 10100.8ms | 643373 | 40 | 3.67754e+08 | 743034 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1326.49 | 0.155998 | 6086.97ms | 1225964 | 30 | 5.67157e+07 | 881399 | 1(Win) |
| simdjson (reflection) STATISTICAL TIE | 1312.78 | 0.456727 | 5469.66ms | 1225964 | 160 | 2.64733e+09 | 890610 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1302.85 | 0.547021 | 6332.04ms | 1225964 | 80 | 1.92781e+09 | 897392 | 2(Tie) |
| glaze | 1241.38 | 0.868988 | 5778.72ms | 1225964 | 40 | 2.67937e+09 | 941830 | 4(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3115.25 | 1.35325 | 9287.38ms | 1225964 | 80 | 2.06355e+09 | 375306 | 1(Win) |
| glaze | 1317.17 | 0.784797 | 5680.96ms | 1225970 | 320 | 1.55288e+10 | 887641 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 788.415 | 1.71841 | 6255.49ms | 409725 | 640 | 4.64204e+10 | 495607 | 1(Win) |
| glaze | 671.546 | 0.708437 | 7555.86ms | 409725 | 320 | 5.43733e+09 | 581858 | 2(Loss) |
| simdjson (reflection) | 643.62 | 0.932948 | 8764.47ms | 409725 | 80 | 2.56644e+09 | 607104 | 3(Loss) |
| simdjson (ondemand) | 566.849 | 0.39925 | 9017.57ms | 409725 | 160 | 1.21188e+09 | 689326 | 4(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5540.33 | 0.243532 | 7373.04ms | 409725 | 320 | 9.44006e+06 | 70527.2 | 1(Win) |
| simdjson (reflection) | 4654.91 | 1.06826 | 8776.58ms | 409725 | 30 | 2.41233e+07 | 83942.4 | 2(Loss) |
| glaze | 1759.01 | 0.402123 | 5890.55ms | 409725 | 320 | 2.5534e+08 | 222139 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1217.28 | 1.06415 | 7535.26ms | 785750 | 30 | 1.2874e+09 | 615595 | 1(Win) |
| glaze | 1154.94 | 0.562492 | 8801.66ms | 785750 | 30 | 3.99583e+08 | 648823 | 2(Loss) |
| simdjson (reflection) | 1138.83 | 0.282712 | 8852.48ms | 785750 | 30 | 1.03814e+08 | 657997 | 3(Loss) |
| simdjson (ondemand) | 1054.39 | 0.349532 | 9767.47ms | 785750 | 40 | 2.46831e+08 | 710694 | 4(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6918.03 | 0.744233 | 5614.37ms | 785750 | 160 | 1.03978e+08 | 108318 | 1(Win) |
| glaze | 2224.4 | 0.657129 | 8926.36ms | 785750 | 40 | 1.96021e+08 | 336877 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3210.95 | 0.199257 | 8355.79ms | 264040 | 640 | 1.56272e+07 | 78421.6 | 1(Win) |
| simdjson (ondemand) | 2863.85 | 0.332407 | 9468.72ms | 264040 | 80 | 6.8339e+06 | 87926.4 | 2(Loss) |
| simdjson (reflection) | 2820.23 | 0.384109 | 9924.55ms | 264040 | 160 | 1.88191e+07 | 89286.4 | 3(Loss) |
| glaze | 2112.17 | 0.22385 | 6490.55ms | 264040 | 320 | 2.27901e+07 | 119218 | 4(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3864.02 | 0.413051 | 5768.66ms | 399947 | 80 | 1.32992e+07 | 98710.4 | 1(Win) |
| simdjson (reflection) | 3591 | 0.126193 | 5607.67ms | 399947 | 1280 | 2.29961e+07 | 106215 | 2(Loss) |
| simdjson (ondemand) | 3381.38 | 0.837306 | 5958.47ms | 399947 | 160 | 1.42727e+08 | 112800 | 3(Loss) |
| glaze | 2684.36 | 1.76395 | 7994.78ms | 399947 | 160 | 1.00512e+09 | 142090 | 4(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1660.69 | 0.63586 | 8122.82ms | 264040 | 30 | 2.78874e+07 | 151629 | 1(Win) |
| glaze | 1349.98 | 0.0993182 | 5100.36ms | 264040 | 640 | 2.19647e+07 | 186528 | 2(Loss) |
| simdjson (reflection) | 1136.58 | 0.521064 | 5846.19ms | 264040 | 320 | 4.26457e+08 | 221550 | 3(Loss) |
| simdjson (ondemand) | 1024.43 | 0.202597 | 6359.06ms | 264040 | 1280 | 3.17428e+08 | 245802 | 4(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9286.3 | 0.298737 | 3024.24ms | 264040 | 2560 | 1.67986e+07 | 27116.1 | 1(Win) |
| simdjson (reflection) | 5113.35 | 0.155419 | 5235.15ms | 264040 | 4890 | 2.86447e+07 | 49245.3 | 2(Loss) |
| glaze | 3206.03 | 0.364547 | 8179.36ms | 263923 | 320 | 2.62105e+07 | 78507.2 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 10103.3 | 0.561999 | 3989.53ms | 399947 | 160 | 7.2023e+06 | 37752 | 1(Win) |
| glaze | 3453.47 | 0.489962 | 6082.22ms | 399830 | 80 | 2.34128e+07 | 110413 | 2(Loss) |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 770.112 | 0.483814 | 593.403ms | 4630 | 320 | 246242 | 5733.6 | 1(Win) |
| glaze | 420.413 | 0.307541 | 1076.31ms | 4630 | 640 | 667723 | 10502.8 | 2(Loss) |
| simdjson (ondemand) | 406.156 | 0.526345 | 1099.07ms | 4630 | 30 | 98228.7 | 10871.5 | 3(Loss) |
| simdjson (reflection) | 356.896 | 0.645251 | 1211.55ms | 4630 | 320 | 2.03933e+06 | 12372 | 4(Loss) |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1956.19 | 0.592195 | 235.885ms | 4630 | 4890 | 873731 | 2257.2 | 1(Win) |
| glaze | 1413.42 | 0.262543 | 323.981ms | 4630 | 2560 | 172211 | 3124 | 2(Loss) |
| simdjson (reflection) | 702.861 | 0.587728 | 619.143ms | 4630 | 2560 | 3.48992e+06 | 6282.2 | 3(Loss) |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1679.88 | 0.590177 | 985.955ms | 14795 | 320 | 786303 | 8399.2 | 1(Win) |
| simdjson (reflection) | 1155.69 | 0.30006 | 1245.46ms | 14795 | 320 | 429450 | 12208.8 | 2(Loss) |
| simdjson (ondemand) | 1122.2 | 0.272345 | 1268.38ms | 14795 | 2560 | 3.00172e+06 | 12573.2 | 3(Loss) |
| glaze | 1105.26 | 0.635845 | 1457.67ms | 14795 | 30 | 197663 | 12765.9 | 4(Loss) |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6166.79 | 2.29841 | 234.902ms | 14795 | 80 | 221236 | 2288 | 1(Win) |
| glaze | 2829.26 | 0.111091 | 509.416ms | 14795 | 4890 | 150089 | 4987.03 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1213.3 | 0.551248 | 445.062ms | 5092 | 320 | 155771 | 4002.4 | 1(Win) |
| glaze | 865.586 | 0.324902 | 715.751ms | 5092 | 1280 | 425278 | 5610.2 | 2(Loss) |
| simdjson (ondemand) | 763.095 | 0.218574 | 646.137ms | 5092 | 2560 | 495285 | 6363.7 | 3(Loss) |
| simdjson (reflection) | 748.741 | 0.204823 | 663.037ms | 5092 | 2560 | 451763 | 6485.7 | 4(Loss) |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6106.78 | 3.17779 | 81.836ms | 5092 | 640 | 408680 | 795.2 | 1(Win) |
| simdjson (reflection) | 3790.87 | 0.998753 | 133.274ms | 5092 | 1280 | 209519 | 1281 | 2(Loss) |
| glaze | 1563.91 | 0.356459 | 317.765ms | 5092 | 2560 | 313625 | 3105.1 | 3(Loss) |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1770.92 | 3.68568 | 682.506ms | 11724 | 80 | 4.33192e+06 | 6313.6 | 1(Win) |
| simdjson (reflection) | 1495.89 | 0.283902 | 784.482ms | 11724 | 1280 | 576368 | 7474.4 | 2(Loss) |
| glaze | 1351.18 | 0.276624 | 855.388ms | 11724 | 2560 | 1.34136e+06 | 8274.9 | 3(Loss) |
| simdjson (ondemand) | 1310.6 | 0.93327 | 1066.62ms | 11724 | 4890 | 3.09982e+07 | 8531.13 | 4(Loss) |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11834.1 | 0.682056 | 99.2248ms | 11724 | 2560 | 106306 | 944.8 | 1(Win) |
| glaze | 2589.19 | 1.74454 | 466.431ms | 11746 | 40 | 227864 | 4326.4 | 2(Loss) |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1201.12 | 0.69296 | 433.571ms | 4857 | 640 | 457047 | 3856.4 | 1(Win) |
| glaze | 1108.16 | 0.596137 | 432.38ms | 4857 | 2560 | 1.58951e+06 | 4179.9 | 2(Loss) |
| simdjson (reflection) | 897.952 | 0.934409 | 596.244ms | 4857 | 320 | 743454 | 5158.4 | 3(Loss) |
| simdjson (ondemand) | 826.316 | 0.779975 | 597.843ms | 4857 | 320 | 611723 | 5605.6 | 4(Loss) |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7065.28 | 1.44463 | 71.746ms | 4857 | 2560 | 229632 | 655.6 | 1(Win) |
| simdjson (reflection) | 4460.71 | 0.553077 | 112.431ms | 4857 | 1280 | 42219.2 | 1038.4 | 2(Loss) |
| glaze | 2273.93 | 1.26331 | 213.58ms | 4857 | 1280 | 847645 | 2037 | 3(Loss) |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1447.57 | 0.35938 | 496.975ms | 7376 | 1280 | 390377 | 4859.4 | 1(Win) |
| glaze | 1407.31 | 0.409546 | 549.382ms | 7376 | 40 | 16762.1 | 4998.4 | 2(Loss) |
| simdjson (reflection) | 1292.9 | 0.239999 | 696.978ms | 7376 | 2560 | 436484 | 5440.7 | 3(Loss) |
| simdjson (ondemand) | 1106.28 | 0.784656 | 692.542ms | 7376 | 4890 | 1.21726e+07 | 6358.54 | 4(Loss) |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7608.76 | 1.68871 | 96.7478ms | 7376 | 2560 | 623969 | 924.5 | 1(Win) |
| glaze | 2276.18 | 0.611793 | 313.047ms | 7376 | 640 | 228781 | 3090.4 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1329.26 | 0.668054 | 329.89ms | 4390 | 320 | 141672 | 3149.6 | 1(Win) |
| glaze | 822.553 | 0.340469 | 492.898ms | 4390 | 2560 | 768771 | 5089.8 | 2(Loss) |
| simdjson (ondemand) STATISTICAL TIE | 715.712 | 1.0459 | 614.101ms | 4390 | 40 | 149725 | 5849.6 | 3(Tie) |
| simdjson (reflection) STATISTICAL TIE | 705.093 | 0.320984 | 563.626ms | 4390 | 2560 | 929912 | 5937.7 | 3(Tie) |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6132.76 | 1.07894 | 71.07ms | 4390 | 4890 | 265290 | 682.667 | 1(Win) |
| simdjson (reflection) | 3720.79 | 1.18583 | 125.266ms | 4390 | 640 | 113943 | 1125.2 | 2(Loss) |
| glaze | 1456.17 | 0.298143 | 325.603ms | 4390 | 4890 | 359306 | 2875.11 | 3(Loss) |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2225.41 | 0.239796 | 503.75ms | 11521 | 640 | 89706.7 | 4937.2 | 1(Win) |
| simdjson (reflection) STATISTICAL TIE | 1648.62 | 1.97918 | 643.437ms | 11521 | 30 | 521953 | 6664.53 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1614.09 | 0.132194 | 685.916ms | 11521 | 4890 | 395960 | 6807.09 | 2(Tie) |
| glaze | 1477.5 | 0.253767 | 745.091ms | 11521 | 2560 | 911665 | 7436.4 | 4(Loss) |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11206.9 | 0.675887 | 104.524ms | 11521 | 1280 | 56203.7 | 980.4 | 1(Win) |
| glaze | 2436.85 | 0.391603 | 458.079ms | 11521 | 1280 | 399047 | 4508.8 | 2(Loss) |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2178.63 | 0.191269 | 210.249ms | 4669 | 4890 | 74727.5 | 2043.81 | 1(Win) |
| glaze | 1244.61 | 0.614461 | 362.507ms | 4669 | 640 | 309281 | 3577.6 | 2(Loss) |
| simdjson (reflection) STATISTICAL TIE | 1022.2 | 0.533478 | 481.453ms | 4669 | 640 | 345612 | 4356 | 3(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1014.77 | 0.249582 | 443.137ms | 4669 | 2560 | 307030 | 4387.9 | 3(Tie) |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9311.39 | 2.07619 | 50.5121ms | 4669 | 2560 | 252345 | 478.2 | 1(Win) |
| simdjson (reflection) | 4427.91 | 0.62408 | 106.703ms | 4669 | 320 | 12603.2 | 1005.6 | 2(Loss) |
| glaze | 1622 | 0.37878 | 284.044ms | 4669 | 2560 | 276798 | 2745.2 | 3(Loss) |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2660.31 | 0.356652 | 347.332ms | 9249 | 2560 | 357976 | 3315.6 | 1(Win) |
| simdjson (reflection) STATISTICAL TIE | 1916.84 | 1.85251 | 475.06ms | 9249 | 40 | 290669 | 4601.6 | 2(Tie) |
| glaze STATISTICAL TIE | 1862.05 | 0.333594 | 529.427ms | 9249 | 1280 | 319634 | 4737 | 2(Tie) |
| simdjson (ondemand) | 1762.06 | 0.266056 | 505.333ms | 9249 | 2560 | 454080 | 5005.8 | 4(Loss) |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11012.2 | 0.761083 | 83.5031ms | 9249 | 4890 | 181726 | 800.982 | 1(Win) |
| glaze | 2036.6 | 0.415935 | 441.315ms | 9249 | 1280 | 415372 | 4331 | 2(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 546.456 | 0.130586 | 826.965ms | 4604 | 2560 | 281836 | 8034.9 | 1(Win) |
| glaze | 382.177 | 0.110142 | 1162.21ms | 4604 | 4890 | 782985 | 11488.7 | 2(Loss) |
| simdjson (ondemand) | 340.749 | 0.105762 | 1418.48ms | 4604 | 4890 | 908170 | 12885.5 | 3(Loss) |
| simdjson (reflection) | 328.182 | 0.321501 | 1345.5ms | 4604 | 2560 | 4.73637e+06 | 13378.9 | 4(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1554.79 | 0.695515 | 293.492ms | 4604 | 640 | 246901 | 2824 | 1(Win) |
| simdjson (reflection) | 1066.72 | 1.5724 | 493.861ms | 4918 | 40 | 191189 | 4396.8 | 2(Loss) |
| glaze | 895.626 | 1.03345 | 523.196ms | 4604 | 40 | 102673 | 4902.4 | 3(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2002.69 | 0.121021 | 1222.7ms | 24579 | 4890 | 981135 | 11704.4 | 1(Win) |
| simdjson (ondemand) | 1529.85 | 0.176773 | 1550.2ms | 24579 | 1280 | 939014 | 15322 | 2(Loss) |
| simdjson (reflection) | 1486.61 | 0.134852 | 1621.01ms | 24579 | 4890 | 2.21084e+06 | 15767.6 | 3(Loss) |
| glaze | 1423.68 | 0.18878 | 1927.31ms | 24579 | 2560 | 2.47316e+06 | 16464.6 | 4(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4995.6 | 0.290174 | 489.101ms | 24579 | 2560 | 474581 | 4692.2 | 1(Win) |
| glaze | 2742.86 | 0.154844 | 864.588ms | 24579 | 4890 | 856286 | 8545.95 | 2(Loss) |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 616.674 | 0.211617 | 724.375ms | 4604 | 1280 | 290582 | 7120 | 1(Win) |
| glaze | 387.106 | 0.431535 | 1179.13ms | 4604 | 160 | 383321 | 11342.4 | 2(Loss) |
| simdjson (ondemand) | 351.426 | 0.168574 | 1284.9ms | 4604 | 1280 | 567800 | 12494 | 3(Loss) |
| simdjson (reflection) | 342.143 | 0.176072 | 1294.17ms | 4604 | 1280 | 653502 | 12833 | 4(Loss) |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1443.93 | 0.817326 | 332.903ms | 4604 | 640 | 395318 | 3040.8 | 1(Win) |
| simdjson (reflection) | 1016.42 | 1.4803 | 468.83ms | 4918 | 80 | 373265 | 4614.4 | 2(Loss) |
| glaze | 917.178 | 1.05246 | 493.658ms | 4604 | 80 | 203079 | 4787.2 | 3(Loss) |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2119.02 | 0.739959 | 1301.09ms | 24579 | 2560 | 1.7152e+07 | 11061.9 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1471.3 | 1.54602 | 1670.5ms | 24579 | 30 | 1.82002e+06 | 15931.7 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 1468.6 | 0.147061 | 1749.53ms | 24579 | 4890 | 2.69417e+06 | 15961.1 | 2(Tie) |
| glaze | 1339.53 | 0.442183 | 1874.7ms | 24579 | 4890 | 2.92777e+07 | 17498.9 | 4(Loss) |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4886.26 | 0.264304 | 500.545ms | 24579 | 4890 | 786124 | 4797.2 | 1(Win) |
| glaze | 2540.82 | 0.831046 | 978.96ms | 24579 | 2560 | 1.50477e+07 | 9225.5 | 2(Loss) |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 650.241 | 1.47241 | 169.064ms | 1181 | 4890 | 3.18064e+06 | 1732.11 | 1(Win) |
| simdjson (reflection) STATISTICAL TIE | 462.542 | 0.629633 | 250.099ms | 1181 | 1280 | 300872 | 2435 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 460.123 | 0.640438 | 247.945ms | 1181 | 1280 | 314569 | 2447.8 | 2(Tie) |
| glaze STATISTICAL TIE | 460.123 | 0.60437 | 251.254ms | 1181 | 1280 | 280136 | 2447.8 | 2(Tie) |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1887.02 | 1.90767 | 59.6659ms | 1181 | 4890 | 633961 | 596.862 | 1(Win) |
| simdjson (reflection) | 881.08 | 1.97398 | 134.947ms | 1187 | 320 | 205830 | 1284.8 | 2(Loss) |
| glaze | 749.062 | 1.74882 | 166.254ms | 1181 | 640 | 442522 | 1503.6 | 3(Loss) |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1221.96 | 0.698243 | 211.052ms | 2496 | 320 | 59202.6 | 1948 | 1(Win) |
| simdjson (reflection) | 954.899 | 1.62245 | 267.457ms | 2496 | 160 | 261722 | 2492.8 | 2(Loss) |
| glaze STATISTICAL TIE | 917.221 | 0.853819 | 280.746ms | 2496 | 640 | 314234 | 2595.2 | 3(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 912.859 | 0.839571 | 270.491ms | 2496 | 640 | 306745 | 2607.6 | 3(Tie) |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3342.8 | 0.917833 | 79.3359ms | 2496 | 4890 | 208883 | 712.088 | 1(Win) |
| glaze | 1237.28 | 0.419413 | 197.246ms | 2507 | 4890 | 321194 | 1932.36 | 2(Loss) |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1150.35 | 0.155984 | 416.516ms | 4926 | 2560 | 103879 | 4083.8 | 1(Win) |
| glaze | 714.559 | 0.678732 | 765.457ms | 4926 | 320 | 637176 | 6574.4 | 2(Loss) |
| simdjson (reflection) | 694.817 | 0.267606 | 676.651ms | 4926 | 1280 | 419033 | 6761.2 | 3(Loss) |
| simdjson (ondemand) | 643.252 | 0.413101 | 759.964ms | 4926 | 320 | 291265 | 7303.2 | 4(Loss) |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5723.65 | 1.2469 | 84.6029ms | 4926 | 4890 | 512173 | 820.771 | 1(Win) |
| simdjson (reflection) | 4268.44 | 0.426433 | 125.087ms | 4926 | 4890 | 107711 | 1100.59 | 2(Loss) |
| glaze | 1675.92 | 0.497258 | 284.242ms | 4926 | 4890 | 950073 | 2803.12 | 3(Loss) |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1771.69 | 0.138722 | 539.519ms | 9463 | 2560 | 127824 | 5093.8 | 1(Win) |
| simdjson (reflection) | 1242.92 | 0.606579 | 737.879ms | 9463 | 160 | 310358 | 7260.8 | 2(Loss) |
| glaze | 1199.25 | 0.377018 | 766.742ms | 9463 | 640 | 515159 | 7525.2 | 3(Loss) |
| simdjson (ondemand) | 1145.8 | 0.819944 | 838.689ms | 9463 | 30 | 125121 | 7876.27 | 4(Loss) |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7399.74 | 0.510376 | 128.281ms | 9463 | 4890 | 189459 | 1219.59 | 1(Win) |
| glaze | 2239.14 | 0.426112 | 417.429ms | 9463 | 160 | 47191.6 | 4030.4 | 2(Loss) |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 2809.44 | 0.588236 | 108.149ms | 2821 | 2560 | 81229.2 | 957.6 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2776.96 | 0.771094 | 103.286ms | 2821 | 640 | 35716 | 968.8 | 1(Tie) |
| simdjson (reflection) STATISTICAL TIE | 2774.2 | 0.333886 | 100.653ms | 2821 | 4890 | 51266.8 | 969.764 | 1(Tie) |
| glaze | 2121.42 | 0.525667 | 130.391ms | 2821 | 4890 | 217312 | 1268.17 | 4(Loss) |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 3512.33 | 1.24756 | 118.323ms | 4147 | 640 | 126293 | 1126 | 1(Tie) |
| simdjson (reflection) STATISTICAL TIE | 3500.84 | 0.442001 | 117.244ms | 4147 | 4890 | 121922 | 1129.7 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3492.48 | 1.19685 | 118.875ms | 4147 | 640 | 117560 | 1132.4 | 1(Tie) |
| glaze | 2883.83 | 1.05143 | 140.862ms | 4147 | 1280 | 266132 | 1371.4 | 4(Loss) |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1817.74 | 0.503767 | 154.221ms | 2821 | 4890 | 271840 | 1480.04 | 1(Win) |
| glaze | 1581.24 | 0.810875 | 178.669ms | 2821 | 1280 | 243630 | 1701.4 | 2(Loss) |
| simdjson (reflection) | 1295.39 | 0.225018 | 210.228ms | 2821 | 4890 | 106795 | 2076.85 | 3(Loss) |
| simdjson (ondemand) | 1171.79 | 0.422023 | 240.942ms | 2821 | 2560 | 240335 | 2295.9 | 4(Loss) |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7866.42 | 5.50856 | 38.7069ms | 2821 | 640 | 227148 | 342 | 1(Win) |
| simdjson (reflection) | 4199.68 | 2.4747 | 67.6621ms | 2821 | 1280 | 321685 | 640.6 | 2(Loss) |
| glaze | 3000.12 | 0.772012 | 92.5409ms | 2819 | 2560 | 122518 | 896.1 | 3(Loss) |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1946.62 | 0.16364 | 211.175ms | 4147 | 4890 | 54049.3 | 2031.67 | 1(Win) |
| jsonifier STATISTICAL TIE | 1802.92 | 1.62501 | 316.228ms | 4147 | 160 | 203303 | 2193.6 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 1794.71 | 0.293151 | 229.214ms | 4147 | 4890 | 204068 | 2203.64 | 2(Tie) |
| simdjson (ondemand) | 1626.19 | 3.70016 | 259.803ms | 4147 | 30 | 242935 | 2432 | 4(Loss) |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8389.66 | 3.53755 | 48.7708ms | 4147 | 1280 | 355955 | 471.4 | 1(Win) |
| glaze | 2596.2 | 0.975548 | 173.123ms | 4145 | 1280 | 282409 | 1522.6 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1553.59 | 0.577109 | 7352.13ms | 466906 | 80 | 2.18873e+08 | 286611 | 1(Win) |
| glaze | 1399.42 | 0.424403 | 8308.02ms | 466906 | 1280 | 2.33418e+09 | 318187 | 2(Loss) |
| simdjson (ondemand) | 822.378 | 0.228248 | 7693.72ms | 466906 | 320 | 4.8874e+08 | 541450 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2193.17 | 0.806198 | 8614.86ms | 699405 | 30 | 1.80351e+08 | 304128 | 1(Win) |
| glaze | 1906.83 | 0.701278 | 8611.99ms | 699405 | 30 | 1.80525e+08 | 349798 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3316.87 | 0.518518 | 9729.71ms | 631514 | 40 | 3.54566e+07 | 181574 | 1(Win) |
| glaze | 1849.61 | 0.172052 | 9323.72ms | 631514 | 160 | 5.02163e+07 | 325614 | 2(Loss) |
