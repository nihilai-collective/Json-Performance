# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.18.40.1-microsoft-standard-WSL2 using the GCC 16.1.0 compiler).  

Latest Results: (Oct 03, 2026)
#### Using the following commits:
----
| Jsonifier: [2fb9afb](https://github.com/nihilai-collective/jsonifier/commit/2fb9afb)  
| Glaze: [52971fe](https://github.com/stephenberry/glaze/commit/52971fe)  
| Simdjson: [2a690bc](https://github.com/simdjson/simdjson/commit/2a690bc)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX2` |
| simdjson (ondemand) | `haswell` |
| simdjson (reflection) | `haswell` |
| Glaze (utf8-validation) | `AVX2` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |
| Glaze (structural-skip) | `AVX2` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 5% AND mean shift < 2.5%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

Every iteration constructs a new object to parse into, or a new string to serialize into, and destroys it again inside the timed region, so allocation and deallocation are part of each measurement. Parser instances are reused.

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

`simdjson (reflection)` is simdjson 5's C++26 static-reflection API (`document.get<T>()` for reads, `simdjson::to_json` into a `std::string` for writes). Its single-pass writer emits minified JSON only (pretty output is a second FracturedJson reformatting pass), so it is absent from the prettified write tests.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [4e7c701](https://github.com/nihilai-collective/benchmarksuite/commit/4e7c701).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2123.77 | 0.607079 | 353.019ms | 905 | 80 | 486.924 | 406.387 | 1.35517 | 1(Win) |
| glaze | 753.087 | 0.179896 | 418.866ms | 905 | 80 | 340.048 | 1146.05 | 3.97081 | 2(Loss) |
| simdjson (ondemand) | 181.861 | 1.01748 | 784.552ms | 905 | 640 | 1.49227e+06 | 4745.78 | 16.628 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1919.4 | 0.262579 | 344.093ms | 905 | 2560 | 3568.81 | 449.658 | 1.51334 | 1(Win) |
| simdjson (reflection) | 334.901 | 0.244702 | 562.771ms | 905 | 1280 | 50903.6 | 2577.1 | 9.00222 | 2(Loss) |
| glaze | 220.9 | 0.474194 | 705.804ms | 905 | 1280 | 439366 | 3907.08 | 13.6851 | 3(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1285.74 | 0.37477 | 436.838ms | 1811 | 160 | 4054.93 | 1343.28 | 2.32737 | 1(Win) |
| glaze | 987.001 | 0.197325 | 495.808ms | 1811 | 40 | 476.9 | 1749.85 | 3.04562 | 2(Loss) |
| simdjson (ondemand) | 217.724 | 1.1751 | 1136.16ms | 1811 | 160 | 1.39026e+06 | 7932.56 | 13.9162 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 399.322 | 0.791169 | 789.941ms | 1997 | 640 | 911233 | 4769.31 | 7.57958 | 1(Win) |
| jsonifier | 343.867 | 0.182157 | 844.098ms | 1811 | 30 | 2511.14 | 5022.6 | 8.80307 | 2(Loss) |
| glaze | 296.452 | 0.405207 | 889.177ms | 1798 | 320 | 175782 | 5784.09 | 10.2123 | 3(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3336.53 | 0.4035 | 422.083ms | 3862 | 2560 | 50787.9 | 1103.87 | 0.893583 | 1(Win) |
| glaze | 1757.14 | 0.139832 | 521.692ms | 3862 | 30 | 257.72 | 2096.07 | 1.711 | 2(Loss) |
| simdjson (ondemand) | 566.936 | 0.170026 | 975.729ms | 3862 | 160 | 19521.2 | 6496.48 | 5.34159 | 3(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1811.26 | 0.17863 | 829.947ms | 9578 | 30 | 2434.55 | 5043.07 | 1.67053 | 1(Win) |
| glaze | 1390.44 | 0.166013 | 1016.85ms | 9578 | 30 | 3568.24 | 6569.37 | 2.17837 | 2(Loss) |
| simdjson (ondemand) | 1055.55 | 0.209623 | 1213.87ms | 9578 | 160 | 52648.7 | 8653.56 | 2.87161 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3481.23 | 0.304996 | 582.83ms | 9578 | 30 | 1921.29 | 2623.87 | 0.865024 | 1(Win) |
| glaze | 2203.62 | 1.10996 | 713.147ms | 9578 | 4890 | 1.03514e+07 | 4145.13 | 1.3705 | 2(Loss) |
| simdjson (reflection) | 1602.46 | 1.25889 | 868.847ms | 9578 | 320 | 1.64776e+06 | 5700.15 | 1.88854 | 3(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3484.92 | 0.297339 | 406.911ms | 3873 | 80 | 794.516 | 1059.88 | 0.853912 | 1(Win) |
| glaze | 1874.04 | 0.541461 | 496.25ms | 3873 | 2560 | 291550 | 1970.92 | 1.60029 | 2(Loss) |
| simdjson (ondemand) | 586.436 | 0.280269 | 946.93ms | 3873 | 80 | 24928.3 | 6298.35 | 5.16338 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 968.16 | 0.692344 | 698.502ms | 3873 | 80 | 55812.8 | 3815.05 | 3.1213 | 1(Win) |
| glaze | 805.64 | 0.245116 | 766.39ms | 3873 | 160 | 20205.8 | 4584.66 | 3.75075 | 2(Loss) |
| simdjson (reflection) | 620.379 | 0.214242 | 922.978ms | 3873 | 40 | 6508.04 | 5953.75 | 4.88332 | 3(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 890.468 | 0.260509 | 6992.55ms | 2090234 | 160 | 5.44152e+09 | 2.2386e+06 | 3.4125 | 1(Win) |
| simdjson (ondemand) | 739.471 | 0.366868 | 8416.21ms | 2090234 | 160 | 1.5649e+10 | 2.69571e+06 | 4.10941 | 2(Loss) |
| glaze | 711.347 | 0.300792 | 8789.42ms | 2090234 | 40 | 2.84197e+09 | 2.80229e+06 | 4.27206 | 3(Loss) |
| simdjson (reflection) | 610.907 | 0.695734 | 10032ms | 2090234 | 80 | 4.12303e+10 | 3.26302e+06 | 4.97436 | 4(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1880.84 | 0.220117 | 6696.61ms | 2090234 | 320 | 1.74159e+09 | 1.05985e+06 | 1.61549 | 1(Win) |
| glaze | 1398.16 | 0.177133 | 9037.88ms | 2090234 | 320 | 2.0409e+09 | 1.42573e+06 | 2.17321 | 2(Loss) |
| simdjson (reflection) | 920.46 | 0.173824 | 6763.93ms | 2090326 | 160 | 2.26755e+09 | 2.16575e+06 | 3.30131 | 3(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2314.09 | 0.397689 | 8544.91ms | 6661897 | 30 | 3.57639e+09 | 2.74548e+06 | 1.31311 | 1(Win) |
| simdjson (ondemand) | 2106.94 | 0.888561 | 9295.94ms | 6661897 | 30 | 2.15371e+10 | 3.01541e+06 | 1.44219 | 2(Loss) |
| simdjson (reflection) | 1828.13 | 0.435324 | 5220.43ms | 6661897 | 80 | 1.83105e+10 | 3.4753e+06 | 1.66226 | 3(Loss) |
| glaze | 1745.73 | 0.37095 | 5465.22ms | 6661897 | 80 | 1.45801e+10 | 3.63932e+06 | 1.74079 | 4(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5484.09 | 0.141666 | 7369.66ms | 6661897 | 320 | 8.61921e+08 | 1.15849e+06 | 0.55406 | 1(Win) |
| glaze | 3054.46 | 0.459575 | 6674.91ms | 6661897 | 30 | 2.74133e+09 | 2.08e+06 | 0.994799 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1830.36 | 0.340271 | 6830.17ms | 500299 | 80 | 6.29396e+07 | 260671 | 1.66019 | 1(Win) |
| jsonifier | 1763.5 | 0.190283 | 6994.32ms | 500299 | 1280 | 3.39247e+08 | 270554 | 1.72309 | 2(Loss) |
| simdjson (ondemand) | 1329.09 | 0.167648 | 9306.82ms | 500299 | 1280 | 4.6361e+08 | 358983 | 2.28611 | 3(Loss) |
| simdjson (reflection) | 1257.74 | 0.64128 | 9566.02ms | 500299 | 640 | 3.78752e+09 | 379350 | 2.41554 | 4(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9949.06 | 0.669887 | 5046.87ms | 500299 | 4890 | 5.04669e+08 | 47956.5 | 0.30514 | 1(Win) |
| simdjson (reflection) | 6543.51 | 0.415211 | 8103.06ms | 500299 | 320 | 2.93309e+07 | 72915.3 | 0.463792 | 2(Loss) |
| glaze | 5395.24 | 0.402999 | 9258.92ms | 500299 | 2560 | 3.25151e+08 | 88434 | 0.562821 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3533 | 0.808946 | 5022.7ms | 1439562 | 160 | 1.581e+09 | 388586 | 0.859944 | 1(Win) |
| simdjson (reflection) STATISTICAL TIE | 3196.21 | 0.366065 | 5560.83ms | 1439562 | 640 | 1.58229e+09 | 429531 | 0.950536 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3162.91 | 0.733122 | 5581.38ms | 1439562 | 160 | 1.62017e+09 | 434054 | 0.960527 | 2(Tie) |
| glaze | 2672.6 | 0.443618 | 6556.21ms | 1439562 | 640 | 3.32346e+09 | 513684 | 1.13683 | 4(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 17335 | 0.608836 | 8192.11ms | 1439562 | 2560 | 5.95187e+08 | 79196.5 | 0.175136 | 1(Win) |
| glaze | 6108.76 | 0.618457 | 5812.05ms | 1439584 | 640 | 1.23643e+09 | 224742 | 0.497172 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2022.7 | 0.635296 | 3204.95ms | 56369 | 40 | 1.14033e+06 | 26577.2 | 1.50093 | 1(Win) |
| jsonifier | 1825.17 | 0.537964 | 3283.68ms | 56369 | 4890 | 1.22769e+08 | 29453.5 | 1.66328 | 2(Loss) |
| simdjson (reflection) | 1520.21 | 0.787869 | 3899.13ms | 56369 | 1280 | 9.93554e+07 | 35362 | 1.99751 | 3(Loss) |
| simdjson (ondemand) | 1449.52 | 0.601143 | 4207.7ms | 56369 | 80 | 3.9763e+06 | 37086.6 | 2.09501 | 4(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10269.5 | 0.230939 | 870.789ms | 56369 | 40 | 5845.66 | 5234.68 | 0.294321 | 1(Win) |
| simdjson (reflection) | 8881.75 | 0.120618 | 945.083ms | 56369 | 30 | 1598.94 | 6052.6 | 0.339444 | 2(Loss) |
| glaze | 6235.88 | 0.584236 | 1190.68ms | 56369 | 30 | 76099.7 | 8620.7 | 0.485813 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2405.14 | 0.466127 | 4034.27ms | 94370 | 4890 | 1.48766e+08 | 37419.1 | 1.2625 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2374.34 | 0.81214 | 4269.24ms | 94370 | 30 | 2.84292e+06 | 37904.5 | 1.27908 | 1(Tie) |
| simdjson (reflection) | 2344.04 | 0.451933 | 4072.04ms | 94370 | 4890 | 1.4723e+08 | 38394.6 | 1.29548 | 3(Loss) |
| simdjson (ondemand) | 2259.15 | 0.394904 | 4303.37ms | 94370 | 4890 | 1.21024e+08 | 39837.3 | 1.34414 | 4(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 14841.2 | 0.204029 | 930.255ms | 94370 | 30 | 4592.37 | 6064.1 | 0.203797 | 1(Win) |
| glaze | 6219.19 | 1.02004 | 1809.07ms | 94370 | 80 | 1.7431e+06 | 14471.1 | 0.48767 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1916.38 | 0.208184 | 914.405ms | 11812 | 30 | 4492.63 | 5878.17 | 1.57809 | 1(Win) |
| jsonifier | 1572.8 | 0.108768 | 1030.11ms | 11812 | 40 | 2427.53 | 7162.25 | 1.92499 | 2(Loss) |
| simdjson (reflection) | 1246.27 | 1.0129 | 1208.8ms | 11812 | 320 | 2.6823e+06 | 9038.84 | 2.43088 | 3(Loss) |
| simdjson (ondemand) | 1037.64 | 1.72283 | 1362.54ms | 11812 | 4890 | 1.71059e+08 | 10856.2 | 2.92098 | 4(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7741.67 | 0.18079 | 458.441ms | 11812 | 80 | 553.625 | 1455.09 | 0.385727 | 1(Win) |
| simdjson (reflection) | 6251.8 | 0.184363 | 492.726ms | 11812 | 40 | 441.413 | 1801.85 | 0.471243 | 2(Loss) |
| glaze | 3595.36 | 0.840971 | 624.44ms | 11812 | 1280 | 888660 | 3133.15 | 0.833981 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 15563.3 | 0.183438 | 506.042ms | 31235 | 160 | 1972.32 | 1913.99 | 0.192409 | 1(Win) |
| glaze | 6020.1 | 1.17497 | 875.852ms | 31235 | 1280 | 4.32652e+06 | 4948.09 | 0.50177 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2245.48 | 0.543549 | 4972.73ms | 108313 | 2560 | 1.60052e+08 | 46001.4 | 1.35247 | 1(Win) |
| glaze | 1951.46 | 0.581425 | 5610.21ms | 108313 | 4890 | 4.63169e+08 | 52932.4 | 1.55631 | 2(Loss) |
| simdjson (reflection) | 1744.96 | 0.299983 | 6232.38ms | 108313 | 4890 | 1.54203e+08 | 59196.5 | 1.74066 | 3(Loss) |
| simdjson (ondemand) | 1334.01 | 0.376329 | 8536.51ms | 108313 | 80 | 6.79313e+06 | 77432.4 | 2.27748 | 4(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 13948.5 | 0.515032 | 1059.57ms | 108313 | 30 | 43641 | 7405.47 | 0.216832 | 1(Win) |
| simdjson (reflection) | 8446.98 | 1.51366 | 1502.97ms | 108313 | 4890 | 1.67542e+08 | 12228.7 | 0.357885 | 2(Loss) |
| glaze | 5470.05 | 0.734263 | 2183.79ms | 108313 | 4890 | 9.40136e+07 | 18883.8 | 0.554613 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 3247.16 | 0.549228 | 6771.69ms | 213963 | 160 | 1.90587e+07 | 62839.8 | 0.935451 | 1(Win) |
| jsonifier STATISTICAL TIE | 2741.31 | 0.24791 | 7708.76ms | 213963 | 4890 | 1.66517e+08 | 74435.6 | 1.10807 | 2(Tie) |
| glaze STATISTICAL TIE | 2725.23 | 0.471578 | 7784.89ms | 213963 | 1280 | 1.59583e+08 | 74874.7 | 1.11462 | 2(Tie) |
| simdjson (ondemand) | 2378.11 | 0.556618 | 8851.93ms | 213963 | 1280 | 2.9197e+08 | 85803.9 | 1.27739 | 4(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 18800.8 | 0.455087 | 1413.52ms | 213963 | 160 | 390330 | 10853.3 | 0.161047 | 1(Win) |
| glaze | 5675.4 | 0.428361 | 3912.44ms | 213963 | 4890 | 1.15988e+08 | 35953.6 | 0.534868 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 745.247 | 0.627543 | 7260.05ms | 1834197 | 30 | 6.50877e+09 | 2.34718e+06 | 4.07754 | 1(Win) |
| glaze | 619.559 | 0.309987 | 8837.47ms | 1834197 | 160 | 1.22556e+10 | 2.82334e+06 | 4.90476 | 2(Loss) |
| simdjson (reflection) | 592.008 | 0.23976 | 9189.23ms | 1834197 | 160 | 8.02992e+09 | 2.95474e+06 | 5.13316 | 3(Loss) |
| simdjson (ondemand) | 582.391 | 0.436275 | 9355.47ms | 1834197 | 30 | 5.15117e+09 | 3.00353e+06 | 5.21765 | 4(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1197.92 | 0.388838 | 9346ms | 1834197 | 40 | 1.28954e+09 | 1.46022e+06 | 2.53648 | 1(Win) |
| glaze | 954.748 | 0.246615 | 5714.55ms | 1833577 | 160 | 3.26422e+09 | 1.83151e+06 | 3.18276 | 2(Loss) |
| simdjson (reflection) | 682.038 | 0.225841 | 8442.22ms | 1922245 | 160 | 5.89559e+09 | 2.68782e+06 | 4.45547 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5698.85 | 0.294431 | 5328.22ms | 9930848 | 30 | 7.1827e+08 | 1.66188e+06 | 0.533175 | 1(Win) |
| glaze | 3384.57 | 0.293549 | 8954.98ms | 9930228 | 160 | 1.07942e+10 | 2.79805e+06 | 0.897783 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 766.992 | 0.253211 | 7103.1ms | 1834197 | 160 | 5.33574e+09 | 2.28063e+06 | 3.96199 | 1(Win) |
| glaze | 623.296 | 0.142381 | 8830.47ms | 1834197 | 160 | 2.55462e+09 | 2.80641e+06 | 4.87553 | 2(Loss) |
| simdjson (ondemand) | 583.515 | 0.202326 | 9331.93ms | 1834197 | 160 | 5.8859e+09 | 2.99774e+06 | 5.20786 | 3(Loss) |
| simdjson (reflection) | 574.172 | 0.699597 | 9371.45ms | 1834197 | 40 | 1.81704e+10 | 3.04652e+06 | 5.2924 | 4(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1180.41 | 0.197989 | 9402.79ms | 1834197 | 320 | 2.75461e+09 | 1.48188e+06 | 2.57425 | 1(Win) |
| glaze | 936.243 | 0.841508 | 5919.79ms | 1833577 | 30 | 7.4107e+09 | 1.86771e+06 | 3.24561 | 2(Loss) |
| simdjson (reflection) | 694.768 | 0.226473 | 8302.08ms | 1922245 | 80 | 2.85667e+09 | 2.63857e+06 | 4.3738 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3054.26 | 0.59096 | 9572.04ms | 9930848 | 80 | 2.68637e+10 | 3.10085e+06 | 0.994943 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 2658.05 | 0.584533 | 5481.67ms | 9930848 | 80 | 3.4702e+10 | 3.56306e+06 | 1.14316 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 2646.26 | 0.866152 | 5463.63ms | 9930848 | 40 | 3.84375e+10 | 3.57893e+06 | 1.14815 | 2(Tie) |
| glaze | 2352.56 | 1.37883 | 6083.04ms | 9930848 | 30 | 9.24339e+10 | 4.02573e+06 | 1.29172 | 4(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) STATISTICAL TIE | 1138.12 | 0.530546 | 6871.55ms | 642697 | 320 | 2.61236e+09 | 538540 | 2.66941 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1124.91 | 0.470703 | 7085.5ms | 642697 | 320 | 2.10484e+09 | 544864 | 2.70078 | 1(Tie) |
| glaze | 1096.36 | 1.32228 | 7156.53ms | 642697 | 30 | 1.63935e+09 | 559051 | 2.77132 | 3(Loss) |
| jsonifier | 1066.05 | 0.436154 | 7628.26ms | 642697 | 30 | 1.8865e+08 | 574947 | 2.85065 | 4(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2177.02 | 0.286713 | 7327.79ms | 642697 | 640 | 4.17027e+08 | 281543 | 1.39564 | 1(Win) |
| glaze | 1484.02 | 0.515926 | 5301.16ms | 642692 | 640 | 2.90589e+09 | 413011 | 2.04726 | 2(Loss) |
| simdjson (reflection) | 1068.43 | 0.655563 | 7288.05ms | 643373 | 320 | 4.5354e+09 | 574273 | 2.84362 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 2180.67 | 0.791855 | 6897.95ms | 1225964 | 30 | 5.4074e+08 | 536152 | 1.39333 | 1(Win) |
| simdjson (ondemand) | 2125.78 | 0.310553 | 7076.77ms | 1225964 | 320 | 9.33558e+08 | 549996 | 1.42936 | 2(Loss) |
| glaze STATISTICAL TIE | 1689.62 | 0.589328 | 8757.72ms | 1225964 | 80 | 1.3304e+09 | 691972 | 1.79819 | 3(Tie) |
| jsonifier STATISTICAL TIE | 1684.83 | 0.236273 | 9024ms | 1225964 | 320 | 8.60247e+08 | 693940 | 1.80349 | 3(Tie) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4140.6 | 0.331106 | 7443.09ms | 1225964 | 320 | 2.79713e+08 | 282367 | 0.733772 | 1(Win) |
| glaze | 2530.4 | 0.339034 | 5957.6ms | 1225970 | 160 | 3.92633e+08 | 462052 | 1.20069 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1321.6 | 0.214644 | 7633.08ms | 409725 | 1280 | 5.15505e+08 | 295661 | 2.29908 | 1(Win) |
| glaze | 1156.56 | 0.752951 | 8897.01ms | 409725 | 160 | 1.03538e+09 | 337850 | 2.62709 | 2(Loss) |
| simdjson (reflection) | 1114.32 | 0.243225 | 9024.5ms | 409725 | 1280 | 9.31091e+08 | 350658 | 2.72654 | 3(Loss) |
| simdjson (ondemand) | 1049.33 | 0.349999 | 9533.57ms | 409725 | 1280 | 2.17424e+09 | 372376 | 2.89535 | 4(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6399.82 | 0.300727 | 6431.09ms | 409725 | 1280 | 4.31523e+07 | 61055.5 | 0.474606 | 1(Win) |
| simdjson (reflection) | 5746.2 | 0.217422 | 7160.64ms | 409725 | 4890 | 1.06891e+08 | 68000.5 | 0.528082 | 2(Loss) |
| glaze | 3601.32 | 0.41779 | 5779.91ms | 409725 | 1280 | 2.63019e+08 | 108500 | 0.84337 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 2012.48 | 0.19256 | 9639.31ms | 785750 | 640 | 3.29016e+08 | 372351 | 1.50974 | 1(Win) |
| simdjson (ondemand) | 1900.13 | 0.406317 | 5052.14ms | 785750 | 320 | 8.21642e+08 | 394367 | 1.59896 | 2(Loss) |
| jsonifier | 1832.89 | 0.31719 | 5223.13ms | 785750 | 640 | 1.07625e+09 | 408834 | 1.65774 | 3(Loss) |
| glaze | 1761.24 | 0.217696 | 5464.05ms | 785750 | 640 | 5.4905e+08 | 425466 | 1.72519 | 4(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11146.9 | 0.407664 | 7080.88ms | 785750 | 1280 | 9.61334e+07 | 67224.9 | 0.27239 | 1(Win) |
| glaze | 4340.74 | 0.263224 | 9163.5ms | 785750 | 1280 | 2.64303e+08 | 172632 | 0.699787 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5522.06 | 0.398554 | 4919.28ms | 264040 | 2560 | 8.45576e+07 | 45600.4 | 0.55 | 1(Win) |
| simdjson (reflection) | 5287.56 | 0.277222 | 5100.4ms | 264040 | 4890 | 8.52299e+07 | 47622.7 | 0.574325 | 2(Loss) |
| simdjson (ondemand) | 5235.77 | 0.326585 | 5192.11ms | 264040 | 2560 | 6.31554e+07 | 48093.8 | 0.580085 | 3(Loss) |
| glaze | 2450.85 | 0.240336 | 5411.96ms | 264040 | 2560 | 1.56094e+08 | 102743 | 1.2396 | 4(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7162.61 | 1.10896 | 5854.19ms | 399947 | 320 | 1.11595e+08 | 53251.4 | 0.424033 | 1(Win) |
| simdjson (reflection) STATISTICAL TIE | 6873.69 | 0.318933 | 5830.68ms | 399947 | 4890 | 1.53156e+08 | 55489.8 | 0.441879 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 6855.91 | 0.402595 | 5869.72ms | 399947 | 1280 | 6.42128e+07 | 55633.6 | 0.443047 | 2(Tie) |
| glaze | 3178.66 | 0.148927 | 6322.13ms | 399947 | 2560 | 8.17534e+07 | 119994 | 0.955841 | 4(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1737.56 | 0.237764 | 7590.95ms | 264040 | 2560 | 3.03943e+08 | 144920 | 1.74862 | 1(Win) |
| simdjson (reflection) | 1687.44 | 0.261012 | 7753.46ms | 264040 | 2560 | 3.88368e+08 | 149225 | 1.80056 | 2(Loss) |
| jsonifier | 1537.28 | 0.192881 | 8529.18ms | 264040 | 2560 | 2.55538e+08 | 163801 | 1.97641 | 3(Loss) |
| simdjson (ondemand) | 1156.11 | 0.431131 | 5698.54ms | 264040 | 320 | 2.8217e+08 | 217806 | 2.62826 | 4(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10465.5 | 0.731173 | 2742.43ms | 264040 | 320 | 9.90393e+06 | 24060.7 | 0.290008 | 1(Win) |
| simdjson (reflection) | 7561.86 | 0.519812 | 3694.32ms | 264040 | 4890 | 1.46516e+08 | 33299.8 | 0.40134 | 2(Loss) |
| glaze | 6305.73 | 0.391383 | 4297.37ms | 263923 | 4890 | 1.19343e+08 | 39915.5 | 0.481118 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (reflection) | 2389.57 | 0.42198 | 8309.69ms | 399947 | 2560 | 1.16142e+09 | 159619 | 1.27138 | 1(Win) |
| glaze | 1931.52 | 0.380237 | 5230.13ms | 399947 | 1280 | 7.21645e+08 | 197471 | 1.57304 | 2(Loss) |
| simdjson (ondemand) | 1652.27 | 0.3268 | 6025.05ms | 399947 | 1280 | 7.2848e+08 | 230846 | 1.83899 | 3(Loss) |
| jsonifier | 1535.2 | 0.282225 | 6414.38ms | 399947 | 1280 | 6.29329e+08 | 248449 | 1.97919 | 4(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 15315.9 | 0.155484 | 3028.31ms | 399947 | 30 | 44979 | 24903.4 | 0.198233 | 1(Win) |
| glaze | 5074.3 | 0.395091 | 7997.75ms | 399830 | 1280 | 1.12824e+08 | 75144.9 | 0.598564 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2249.59 | 1.04067 | 5173.26ms | 466906 | 320 | 1.35778e+09 | 197937 | 1.35063 | 1(Tie) |
| glaze STATISTICAL TIE | 2237.46 | 0.530363 | 5178.84ms | 466906 | 1280 | 1.42596e+09 | 199010 | 1.35793 | 1(Tie) |
| simdjson (ondemand) | 1202 | 0.437705 | 9568.48ms | 466906 | 1280 | 3.3653e+09 | 370447 | 2.52726 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3353.34 | 0.488711 | 5210.27ms | 699405 | 1280 | 1.20953e+09 | 198908 | 0.905812 | 1(Win) |
| glaze | 3118.8 | 0.422818 | 5596.45ms | 699405 | 1280 | 1.04665e+09 | 213866 | 0.974175 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3937.36 | 0.521012 | 7925.71ms | 631514 | 2560 | 1.62589e+09 | 152960 | 0.771545 | 1(Win) |
| glaze | 2334.91 | 0.385287 | 6727.05ms | 631514 | 640 | 6.32083e+08 | 257936 | 1.30123 | 2(Loss) |
