# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest Results: (Sep 19, 2026)
#### Using the following commits:
----
| Jsonifier: [3240669](https://github.com/nihilai-collective/jsonifier/commit/3240669)  
| Glaze: [a5fcd46](https://github.com/stephenberry/glaze/commit/a5fcd46)  
| Simdjson: [a683f0a](https://github.com/simdjson/simdjson/commit/a683f0a)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `NEON` |
| simdjson (ondemand) | `arm64` |
| Glaze (utf8-validation) | `NEON64` |
| Glaze (string-escape) | `NEON` |
| Glaze (float-write) | `NEON` |
| Glaze (structural-skip) | `NEON64` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Apple M1 (Virtual)-NEON-NEON): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 10.000000% AND mean shift < 5.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [4972187](https://github.com/realtimechris/benchmarksuite/commit/4972187).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1082.33 | 5.73981 | 15.052ms | 1811 | 30 | 251673 | 1595.73 | 1(Tie) |
| glaze STATISTICAL TIE | 1037.92 | 5.35739 | 0.570112ms | 1811 | 30 | 238415 | 1664 | 1(Tie) |
| simdjson (ondemand) | 188.45 | 0.762333 | 2.8329ms | 1811 | 30 | 146439 | 9164.8 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 997.02 | 4.89287 | 0.557824ms | 1811 | 30 | 215516 | 1732.27 | 1(Win) |
| glaze | 755.422 | 3.73599 | 0.735232ms | 1798 | 30 | 215741 | 2269.87 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1849.75 | 0.952284 | 0.633856ms | 3873 | 30 | 10847.3 | 1996.8 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1788.6 | 2.29689 | 0.66688ms | 3873 | 30 | 67494.5 | 2065.07 | 1(Tie) |
| simdjson (ondemand) | 385.262 | 0.911107 | 14.569ms | 3873 | 80 | 610397 | 9587.2 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4911.68 | 6.56007 | 1.17811ms | 3873 | 80 | 194690 | 752 | 1(Win) |
| glaze | 3005.84 | 6.34899 | 0.408832ms | 3873 | 30 | 182597 | 1228.8 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1606.79 | 0.614876 | 59.072ms | 3862 | 1280 | 254267 | 2292.2 | 1(Tie) |
| glaze STATISTICAL TIE | 1530.54 | 3.59226 | 0.74624ms | 3862 | 30 | 224178 | 2406.4 | 1(Tie) |
| simdjson (ondemand) | 339.852 | 0.653901 | 3.30214ms | 3862 | 30 | 150657 | 10837.3 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5340.91 | 5.38845 | 2.35699ms | 3862 | 160 | 220924 | 689.6 | 1(Win) |
| glaze | 2509.37 | 6.31003 | 0.48ms | 3862 | 30 | 257323 | 1467.73 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1758.51 | 2.99821 | 13.1832ms | 905 | 1280 | 277169 | 490.8 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1644.58 | 7.58817 | 1.69702ms | 905 | 160 | 253736 | 524.8 | 1(Tie) |
| simdjson (ondemand) | 203.915 | 1.87343 | 1.30893ms | 905 | 30 | 188623 | 4232.53 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2824.2 | 8.46345 | 2.06285ms | 905 | 320 | 214068 | 305.6 | 1(Win) |
| glaze | 984.347 | 7.45758 | 0.66688ms | 905 | 40 | 171024 | 876.8 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3095.95 | 1.42329 | 2.26202ms | 9578 | 40 | 70535.2 | 2950.4 | 1(Win) |
| glaze | 2449.48 | 2.3433 | 1.18682ms | 9578 | 30 | 229075 | 3729.07 | 2(Loss) |
| simdjson (ondemand) | 779.057 | 0.305363 | 39.5172ms | 9578 | 160 | 205099 | 11724.8 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 5754.97 | 5.80769 | 0.547072ms | 9578 | 30 | 254912 | 1587.2 | 1(Tie) |
| jsonifier STATISTICAL TIE | 5693.75 | 5.56652 | 0.507136ms | 9578 | 30 | 239244 | 1604.27 | 1(Tie) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1836.12 | 0.114243 | 328.506ms | 2090234 | 30 | 4.61497e+07 | 1.08566e+06 | 1(Win) |
| glaze | 1557.23 | 0.109341 | 390.678ms | 2090234 | 30 | 5.87722e+07 | 1.28009e+06 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1397.26 | 0.476694 | 1375.27ms | 6661897 | 30 | 1.40942e+10 | 4.54695e+06 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1332.72 | 1.09146 | 7141.54ms | 6661897 | 80 | 2.16585e+11 | 4.76715e+06 | 2(Tie) |
| glaze STATISTICAL TIE | 1299.91 | 0.712793 | 1469.23ms | 6661897 | 30 | 3.64099e+10 | 4.88748e+06 | 2(Tie) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 3168.42 | 0.72422 | 608.957ms | 6661897 | 30 | 6.32664e+09 | 2.00519e+06 | 1(Win) |
| jsonifier | 2927.1 | 0.153631 | 654.689ms | 6661897 | 30 | 3.33582e+08 | 2.1705e+06 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1449.94 | 0.16453 | 100.057ms | 500299 | 30 | 8.79358e+06 | 329062 | 1(Win) |
| glaze | 1108.49 | 2.49763 | 301.359ms | 500299 | 40 | 4.62289e+09 | 430426 | 2(Loss) |
| simdjson (ondemand) | 791.293 | 0.17855 | 181.786ms | 500299 | 30 | 3.47717e+07 | 602965 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5342.84 | 0.10565 | 27.083ms | 500299 | 30 | 267040 | 89301.3 | 1(Win) |
| glaze | 1979.28 | 0.272614 | 72.4739ms | 500299 | 30 | 1.29557e+07 | 241058 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2476.16 | 0.789212 | 165.038ms | 1439562 | 30 | 5.74397e+08 | 554436 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1900.7 | 0.275748 | 529.133ms | 1439562 | 40 | 1.58678e+08 | 722298 | 2(Tie) |
| glaze STATISTICAL TIE | 1894.67 | 0.156088 | 217.954ms | 1439562 | 30 | 3.83758e+07 | 724599 | 2(Tie) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4689.94 | 0.133635 | 88.1098ms | 1439562 | 30 | 4.59083e+06 | 292727 | 1(Win) |
| glaze | 3746.33 | 0.825299 | 109.311ms | 1439584 | 30 | 2.74414e+08 | 366464 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1318.76 | 0.7008 | 12.201ms | 56369 | 30 | 2.44826e+06 | 40763.7 | 1(Win) |
| jsonifier | 1140.63 | 1.01505 | 33.5721ms | 56369 | 40 | 9.1542e+06 | 47129.6 | 2(Loss) |
| simdjson (ondemand) | 727.178 | 3.47351 | 54.4031ms | 56369 | 40 | 2.63752e+08 | 73926.4 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6619.1 | 0.657977 | 5.8921ms | 56369 | 40 | 114226 | 8121.6 | 1(Win) |
| glaze | 2798.63 | 0.401521 | 5.91693ms | 56369 | 30 | 178454 | 19208.5 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1757.78 | 0.143839 | 15.615ms | 94370 | 30 | 162710 | 51200 | 1(Win) |
| jsonifier | 1404.91 | 1.36319 | 20.8289ms | 94370 | 30 | 2.28774e+07 | 64059.7 | 2(Loss) |
| simdjson (ondemand) | 1206.02 | 1.0284 | 111.985ms | 94370 | 80 | 4.71162e+07 | 74624 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3896.07 | 0.731818 | 7.02592ms | 94370 | 30 | 857316 | 23099.7 | 1(Win) |
| glaze | 2532.82 | 0.811882 | 10.7451ms | 94370 | 30 | 2.4967e+06 | 35532.8 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 873.656 | 2.13177 | 3.95008ms | 11812 | 30 | 2.26657e+06 | 12893.9 | 1(Win) |
| glaze | 815.88 | 0.554701 | 4.22605ms | 11812 | 30 | 175968 | 13806.9 | 2(Loss) |
| simdjson (ondemand) | 615.428 | 0.982689 | 5.52397ms | 11812 | 30 | 970611 | 18304 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4177.51 | 3.27397 | 0.866048ms | 11812 | 30 | 233820 | 2696.53 | 1(Win) |
| glaze | 1788.75 | 1.34469 | 2.0119ms | 11812 | 30 | 215139 | 6297.6 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1587.44 | 1.01366 | 6.40998ms | 31235 | 30 | 1.08541e+06 | 18764.8 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1360.4 | 1.12354 | 6.67981ms | 31235 | 30 | 1.81572e+06 | 21896.5 | 2(Tie) |
| glaze STATISTICAL TIE | 1306.43 | 1.6997 | 6.75098ms | 31235 | 30 | 4.50586e+06 | 22801.1 | 2(Tie) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3802.6 | 0.852471 | 2.51085ms | 31235 | 30 | 133784 | 7833.6 | 1(Win) |
| glaze | 2244.88 | 1.84326 | 3.7481ms | 31235 | 30 | 1.79471e+06 | 13269.3 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1855.37 | 1.26422 | 48.5942ms | 108313 | 40 | 1.98154e+07 | 55673.6 | 1(Win) |
| glaze | 1183.62 | 1.41693 | 28.0451ms | 108313 | 30 | 4.58723e+07 | 87270.4 | 2(Loss) |
| simdjson (ondemand) | 978.175 | 1.37788 | 32.084ms | 108313 | 30 | 6.35146e+07 | 105600 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2576.47 | 0.447167 | 24.6799ms | 213963 | 30 | 3.7626e+06 | 79197.9 | 1(Win) |
| glaze | 2086.76 | 0.408965 | 29.6602ms | 213963 | 30 | 4.79761e+06 | 97783.5 | 2(Loss) |
| simdjson (ondemand) | 1807.83 | 0.711467 | 32.982ms | 213963 | 30 | 1.9346e+07 | 112870 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3361.29 | 0.199887 | 18.3721ms | 213963 | 30 | 441728 | 60706.1 | 1(Win) |
| glaze | 2248.61 | 0.225864 | 64.618ms | 213963 | 40 | 1.68037e+06 | 90745.6 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 501.232 | 0.38712 | 5403.25ms | 1834197 | 80 | 1.46014e+10 | 3.48985e+06 | 1(Win) |
| glaze | 496.015 | 0.0831658 | 1071.9ms | 1834197 | 30 | 2.58056e+08 | 3.52656e+06 | 2(Loss) |
| simdjson (ondemand) | 112.86 | 1.02756 | 4610.57ms | 1834197 | 30 | 7.60932e+11 | 1.5499e+07 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 821.922 | 0.105753 | 641.478ms | 1833577 | 30 | 1.51862e+08 | 2.1275e+06 | 1(Win) |
| jsonifier | 700.616 | 0.0930395 | 793.243ms | 1834197 | 30 | 1.61878e+08 | 2.4967e+06 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1981.83 | 0.220112 | 1442.95ms | 9930848 | 30 | 3.31931e+09 | 4.7788e+06 | 1(Win) |
| glaze | 1850.77 | 0.413702 | 1518.85ms | 9930848 | 30 | 1.34451e+10 | 5.11721e+06 | 2(Loss) |
| simdjson (ondemand) | 578.81 | 0.115243 | 11672.5ms | 9930848 | 40 | 1.42229e+10 | 1.63625e+07 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3116.28 | 0.656245 | 4739.43ms | 9930848 | 80 | 3.18216e+10 | 3.03913e+06 | 1(Win) |
| glaze | 2834 | 0.366433 | 1025.61ms | 9930228 | 30 | 4.4981e+09 | 3.34164e+06 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 523.121 | 0.561009 | 1016.55ms | 1834197 | 30 | 1.05572e+10 | 3.34383e+06 | 1(Win) |
| glaze | 469.562 | 1.32705 | 2694.8ms | 1834197 | 40 | 9.77555e+10 | 3.72523e+06 | 2(Loss) |
| simdjson (ondemand) | 423.064 | 0.114747 | 1248.98ms | 1834197 | 30 | 6.75281e+08 | 4.13466e+06 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 794.922 | 0.199905 | 660.744ms | 1833577 | 30 | 5.80122e+08 | 2.19976e+06 | 1(Win) |
| jsonifier | 681.502 | 0.0981501 | 776.53ms | 1834197 | 30 | 1.90398e+08 | 2.56672e+06 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2005.56 | 0.856406 | 1458.25ms | 9930848 | 30 | 4.90664e+10 | 4.72228e+06 | 1(Win) |
| glaze | 1904 | 0.184418 | 8220.75ms | 9930848 | 80 | 6.73181e+09 | 4.97415e+06 | 2(Loss) |
| simdjson (ondemand) | 1842.78 | 0.195846 | 1570.7ms | 9930848 | 30 | 3.03933e+09 | 5.13941e+06 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2984.95 | 0.486769 | 2173.49ms | 9930848 | 40 | 9.54127e+09 | 3.17285e+06 | 1(Win) |
| glaze | 2545.07 | 0.463836 | 1126.06ms | 9930228 | 30 | 8.93655e+09 | 3.721e+06 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 839.198 | 0.55207 | 219.711ms | 642697 | 30 | 4.87746e+08 | 730368 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 835.722 | 0.131691 | 221.02ms | 642697 | 30 | 2.79849e+07 | 733406 | 1(Tie) |
| jsonifier | 819.307 | 0.208255 | 226.318ms | 642697 | 30 | 7.2817e+07 | 748100 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1078.03 | 0.146577 | 171.151ms | 642697 | 30 | 2.08356e+07 | 568559 | 1(Win) |
| glaze | 1060.97 | 0.129649 | 173.45ms | 642692 | 30 | 1.68291e+07 | 577698 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1481.94 | 0.108443 | 572.794ms | 1225964 | 40 | 2.92791e+07 | 788947 | 1(Win) |
| simdjson (ondemand) | 1278.47 | 1.18009 | 269.5ms | 1225964 | 30 | 3.49402e+09 | 914509 | 2(Loss) |
| jsonifier | 1199.65 | 0.201185 | 294.32ms | 1225964 | 30 | 1.15334e+08 | 974592 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2865.58 | 0.213036 | 122.328ms | 1225964 | 30 | 2.2665e+07 | 408004 | 1(Win) |
| glaze | 1512.47 | 0.40397 | 233.521ms | 1225970 | 30 | 2.92555e+08 | 773026 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 675.792 | 0.180586 | 175.744ms | 409725 | 30 | 3.27074e+07 | 578202 | 1(Win) |
| glaze | 642.861 | 0.143544 | 432.749ms | 409725 | 40 | 3.04497e+07 | 607821 | 2(Loss) |
| simdjson (ondemand) | 567.414 | 0.26615 | 206.408ms | 409725 | 30 | 1.00776e+08 | 688640 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4179.09 | 0.67485 | 28.041ms | 409725 | 30 | 1.19442e+07 | 93499.7 | 1(Win) |
| glaze | 1918.96 | 0.203554 | 306.7ms | 409725 | 80 | 1.37436e+07 | 203622 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1043.82 | 1.59608 | 211.705ms | 785750 | 30 | 3.93865e+09 | 717892 | 1(Win) |
| jsonifier | 1003.04 | 0.433688 | 515.183ms | 785750 | 40 | 4.19901e+08 | 747078 | 2(Loss) |
| simdjson (ondemand) | 886.871 | 1.23614 | 256.362ms | 785750 | 30 | 3.27269e+09 | 844937 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3211.47 | 0.205607 | 70.1361ms | 785750 | 30 | 6.90493e+06 | 233335 | 1(Win) |
| glaze | 2497 | 0.14684 | 90.335ms | 785750 | 30 | 5.82562e+06 | 300100 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3556.56 | 0.39177 | 21.516ms | 264040 | 30 | 2.30815e+06 | 70801.1 | 1(Win) |
| simdjson (ondemand) | 2961.54 | 0.409769 | 25.44ms | 264040 | 30 | 3.64169e+06 | 85026.1 | 2(Loss) |
| glaze | 2259.13 | 0.0835753 | 34.0239ms | 264040 | 30 | 260336 | 111462 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4282.2 | 0.625137 | 27.0382ms | 399947 | 30 | 9.30129e+06 | 89070.9 | 1(Win) |
| simdjson (ondemand) | 3716.2 | 0.705779 | 152.964ms | 399947 | 80 | 4.19792e+07 | 102637 | 2(Loss) |
| glaze | 3030.34 | 0.237538 | 37.9592ms | 399947 | 30 | 2.6817e+06 | 125867 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1442.76 | 1.09348 | 52.8712ms | 264040 | 30 | 1.09267e+08 | 174532 | 1(Win) |
| glaze | 1399.18 | 0.163544 | 54.6271ms | 264040 | 30 | 2.59884e+06 | 179968 | 2(Loss) |
| simdjson (ondemand) | 1222.96 | 0.158747 | 62.1681ms | 264040 | 30 | 3.20516e+06 | 205901 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 3482.78 | 0.333751 | 21.8232ms | 263923 | 30 | 1.74529e+06 | 72268.8 | 1(Win) |
| jsonifier | 2950.88 | 1.10179 | 25.9469ms | 264040 | 30 | 2.65187e+07 | 85333.3 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1884.78 | 0.227004 | 64.33ms | 399947 | 30 | 6.331e+06 | 202368 | 1(Win) |
| glaze | 1793.14 | 0.346866 | 64.0709ms | 399947 | 30 | 1.63313e+07 | 212710 | 2(Loss) |
| simdjson (ondemand) | 1696.43 | 0.0797466 | 1498.54ms | 399947 | 320 | 1.02875e+07 | 224837 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4909.12 | 0.949545 | 24.2299ms | 399947 | 30 | 1.63286e+07 | 77696 | 1(Win) |
| glaze | 3444.69 | 1.21653 | 34.2799ms | 399830 | 30 | 5.44021e+07 | 110694 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1609.83 | 0.20336 | 417.104ms | 466906 | 80 | 2.53117e+07 | 276598 | 1(Win) |
| glaze | 1564.17 | 0.156415 | 85.5718ms | 466906 | 30 | 5.94796e+06 | 284672 | 2(Loss) |
| simdjson (ondemand) | 761.497 | 1.1413 | 176.117ms | 466906 | 30 | 1.33611e+09 | 584738 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2473.41 | 0.226008 | 80.789ms | 699405 | 30 | 1.11438e+07 | 269670 | 1(Win) |
| glaze | 2069.32 | 0.139465 | 96.8778ms | 699405 | 30 | 6.06253e+06 | 322330 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2593.32 | 0.461611 | 69.2859ms | 631514 | 30 | 3.44768e+07 | 232235 | 1(Win) |
| glaze | 1877.95 | 0.12372 | 96.662ms | 631514 | 30 | 4.72281e+06 | 320700 | 2(Loss) |
