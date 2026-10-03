# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest Results: (Oct 03, 2026)
#### Using the following commits:
----
| Jsonifier: [f5d1ca8](https://github.com/nihilai-collective/jsonifier/commit/f5d1ca8)  
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
| glaze STATISTICAL TIE | 1402 | 1.15267 | 77.4259ms | 905 | 4890 | 246220 | 615.604 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1341.85 | 2.98215 | 68.3489ms | 905 | 640 | 235468 | 643.2 | 1(Tie) |
| simdjson (ondemand) | 178.705 | 0.564644 | 514.185ms | 905 | 1280 | 951880 | 4829.6 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1880.34 | 3.04947 | 50.4791ms | 905 | 1280 | 250776 | 459 | 1(Win) |
| glaze | 102.649 | 0.928133 | 829.718ms | 905 | 2560 | 1.559e+07 | 8408 | 2(Loss) |
| simdjson (reflection) | 97.0194 | 0.275814 | 924.06ms | 905 | 2560 | 1.54117e+06 | 8895.9 | 3(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 888.977 | 0.561621 | 218.453ms | 1811 | 640 | 76194.4 | 1942.8 | 1(Win) |
| glaze | 736.508 | 0.473271 | 271.675ms | 1811 | 4890 | 602299 | 2344.99 | 2(Loss) |
| simdjson (ondemand) | 123.49 | 0.600694 | 1445.11ms | 1811 | 2560 | 1.80685e+07 | 13985.8 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 230.477 | 1.82097 | 838.894ms | 1811 | 320 | 5.95851e+06 | 7493.6 | 1(Win) |
| glaze | 163.422 | 0.451178 | 1046.4ms | 1798 | 4890 | 1.09588e+07 | 10492.5 | 2(Loss) |
| simdjson (reflection) | 119.587 | 0.844691 | 1638.31ms | 1997 | 320 | 5.79079e+06 | 15925.6 | 3(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2131.42 | 4.23535 | 195.65ms | 3862 | 40 | 214252 | 1728 | 1(Win) |
| glaze | 1016.92 | 2.59183 | 328.856ms | 3862 | 1280 | 1.1279e+07 | 3621.8 | 2(Loss) |
| simdjson (ondemand) | 386.944 | 1.26071 | 1002.48ms | 3862 | 320 | 4.60796e+06 | 9518.4 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 653.494 | 0.571949 | 590.621ms | 3862 | 2560 | 2.6601e+06 | 5636 | 1(Win) |
| glaze | 407.604 | 0.253989 | 910.234ms | 3862 | 4890 | 2.57566e+06 | 9035.96 | 2(Loss) |
| simdjson (reflection) | 248.481 | 1.21151 | 1550.8ms | 3862 | 40 | 1.28988e+06 | 14822.4 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 922.06 | 0.658762 | 1226.85ms | 9578 | 320 | 1.36282e+06 | 9906.4 | 1(Tie) |
| glaze STATISTICAL TIE | 903.312 | 1.91058 | 1199.22ms | 9578 | 30 | 1.11976e+06 | 10112 | 1(Tie) |
| simdjson (reflection) | 495.89 | 0.60904 | 2022.27ms | 9578 | 4890 | 6.15432e+07 | 18420 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 602.031 | 1.05281 | 633.926ms | 3873 | 640 | 2.67018e+06 | 6135.2 | 1(Win) |
| glaze | 409.729 | 0.551234 | 883.894ms | 3873 | 2560 | 6.32142e+06 | 9014.7 | 2(Loss) |
| simdjson (reflection) | 243.033 | 1.7406 | 1595.03ms | 3873 | 30 | 2.09934e+06 | 15197.9 | 3(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1280.58 | 2.14785 | 7804.37ms | 6661897 | 80 | 9.08414e+11 | 4.96126e+06 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 783.656 | 4.03922 | 10871.6ms | 6661897 | 80 | 8.57885e+12 | 8.10723e+06 | 2(Tie) |
| glaze STATISTICAL TIE | 755.739 | 5.29761 | 5620.43ms | 6661897 | 40 | 7.93364e+12 | 8.40671e+06 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 691.512 | 4.76292 | 5536.21ms | 6661897 | 40 | 7.65955e+12 | 9.18751e+06 | 2(Tie) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5788.65 | 0.778425 | 8538.46ms | 6661897 | 30 | 2.18976e+09 | 1.09754e+06 | 1(Win) |
| glaze | 2602.32 | 1.95775 | 7924.3ms | 6661897 | 30 | 6.8535e+10 | 2.4414e+06 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2804.55 | 1.04553 | 6191.5ms | 1439562 | 320 | 8.38217e+09 | 489516 | 1(Win) |
| simdjson (reflection) | 2107.03 | 0.584379 | 8189.9ms | 1439562 | 80 | 1.15984e+09 | 651568 | 2(Loss) |
| simdjson (ondemand) | 1975.63 | 0.94996 | 8887.72ms | 1439562 | 640 | 2.78895e+10 | 694904 | 3(Loss) |
| glaze | 1542.18 | 1.13622 | 5378.06ms | 1439562 | 320 | 3.27388e+10 | 890215 | 4(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 16599 | 0.148594 | 8541.7ms | 1439562 | 640 | 9.66672e+06 | 82708 | 1(Win) |
| glaze | 3699.55 | 0.221966 | 5042.78ms | 1439584 | 30 | 2.0355e+07 | 371098 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1581.89 | 0.269846 | 3443ms | 56369 | 320 | 2.69098e+06 | 33983.2 | 1(Win) |
| glaze | 1310.14 | 0.0827713 | 4545.83ms | 56369 | 2560 | 2.95286e+06 | 41031.9 | 2(Loss) |
| simdjson (reflection) | 992.461 | 0.0965053 | 5515.61ms | 56369 | 640 | 1.74878e+06 | 54166 | 3(Loss) |
| simdjson (ondemand) | 905.426 | 0.478939 | 6382.83ms | 56369 | 40 | 3.23441e+06 | 59372.8 | 4(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8001.06 | 0.157367 | 696.597ms | 56369 | 4890 | 546668 | 6718.82 | 1(Win) |
| simdjson (reflection) | 5372.76 | 0.349679 | 1033.26ms | 56369 | 320 | 391721 | 10005.6 | 2(Loss) |
| glaze | 2710.11 | 0.243703 | 2002.09ms | 56369 | 320 | 747793 | 19836 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1828.4 | 0.225772 | 5464.23ms | 94370 | 40 | 493999 | 49222.4 | 1(Win) |
| glaze | 1721.62 | 0.295092 | 5499.62ms | 94370 | 80 | 1.9037e+06 | 52275.2 | 2(Loss) |
| simdjson (reflection) | 1512.44 | 0.102803 | 6011.75ms | 94370 | 640 | 2.39497e+06 | 59505.2 | 3(Loss) |
| simdjson (ondemand) | 1382.29 | 0.194084 | 6661.77ms | 94370 | 640 | 1.02194e+07 | 65108 | 4(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9043.5 | 0.106128 | 1002.81ms | 94370 | 2560 | 285558 | 9951.7 | 1(Win) |
| glaze | 2414.72 | 0.059562 | 3917.37ms | 94370 | 4890 | 2.40981e+06 | 37270.7 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1450.58 | 0.104106 | 788.093ms | 11812 | 4890 | 319610 | 7765.7 | 1(Win) |
| glaze | 893.552 | 0.115255 | 1297.5ms | 11812 | 4890 | 1.03237e+06 | 12606.8 | 2(Loss) |
| simdjson (ondemand) | 694.329 | 0.358783 | 1681.73ms | 11812 | 80 | 271062 | 16224 | 3(Loss) |
| simdjson (reflection) | 592.685 | 1.7971 | 1657.05ms | 11812 | 640 | 7.46665e+07 | 19006.4 | 4(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6383.51 | 0.767154 | 194.196ms | 11812 | 4890 | 896194 | 1764.67 | 1(Win) |
| simdjson (reflection) | 4458.11 | 0.301297 | 258.836ms | 11812 | 4890 | 283428 | 2526.81 | 2(Loss) |
| glaze | 1616.37 | 0.383047 | 757.675ms | 11812 | 640 | 456090 | 6969.2 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2314.25 | 0.0815409 | 1294.98ms | 31235 | 4890 | 538669 | 12871.6 | 1(Win) |
| simdjson (reflection) | 1781.67 | 0.288038 | 1722.08ms | 31235 | 320 | 742133 | 16719.2 | 2(Loss) |
| glaze | 1618.88 | 0.172944 | 2032.69ms | 31235 | 640 | 648104 | 18400.4 | 3(Loss) |
| simdjson (ondemand) | 1571.31 | 0.074248 | 1958.56ms | 31235 | 4890 | 968811 | 18957.5 | 4(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11113.3 | 0.899249 | 265.902ms | 31235 | 640 | 371826 | 2680.4 | 1(Win) |
| glaze | 2847.08 | 0.090414 | 1051.76ms | 31235 | 4890 | 437586 | 10462.7 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2472.6 | 0.210377 | 4419.34ms | 108313 | 160 | 1.23586e+06 | 41776 | 1(Win) |
| glaze | 1376.48 | 0.0785212 | 7696.04ms | 108313 | 2560 | 8.88866e+06 | 75043.2 | 2(Loss) |
| simdjson (reflection) | 1257.17 | 0.136442 | 9454.32ms | 108313 | 160 | 2.01088e+06 | 82164.8 | 3(Loss) |
| simdjson (ondemand) | 1193.79 | 0.0536842 | 8981.04ms | 108313 | 2560 | 5.52377e+06 | 86527 | 4(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11637.1 | 0.174414 | 907.963ms | 108313 | 2560 | 613590 | 8876.4 | 1(Win) |
| simdjson (reflection) | 5184.26 | 0.194066 | 2011.88ms | 108313 | 320 | 478451 | 19924.8 | 2(Loss) |
| glaze | 1766.05 | 0.512047 | 6108.91ms | 108313 | 80 | 7.17574e+06 | 58489.6 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2976.57 | 0.0929177 | 7199.97ms | 213963 | 640 | 2.5967e+06 | 68552.4 | 1(Win) |
| glaze STATISTICAL TIE | 2116.22 | 0.243398 | 5505.23ms | 213963 | 40 | 2.20319e+06 | 96422.4 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 2108.52 | 0.251937 | 5298.26ms | 213963 | 40 | 2.37774e+06 | 96774.4 | 2(Tie) |
| simdjson (ondemand) | 2001.07 | 0.257155 | 5780.53ms | 213963 | 40 | 2.75045e+06 | 101971 | 4(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 12987 | 0.141274 | 1576.58ms | 213963 | 1280 | 630662 | 15712 | 1(Win) |
| glaze | 2220.39 | 0.0520767 | 9421.19ms | 213963 | 4890 | 1.11999e+07 | 91898.8 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 617.599 | 0.0842954 | 9028.41ms | 1834197 | 40 | 2.28006e+08 | 2.8323e+06 | 1(Win) |
| glaze | 493.741 | 0.155439 | 5439.9ms | 1834197 | 30 | 9.09779e+08 | 3.5428e+06 | 2(Loss) |
| simdjson (ondemand) | 446.365 | 0.0710759 | 6144.78ms | 1834197 | 80 | 6.20648e+08 | 3.91882e+06 | 3(Loss) |
| simdjson (reflection) | 430.572 | 0.0780471 | 6331.75ms | 1834197 | 80 | 8.04274e+08 | 4.06256e+06 | 4(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1256.61 | 0.083539 | 9311.75ms | 1834197 | 320 | 4.32734e+08 | 1.39202e+06 | 1(Win) |
| glaze | 821.574 | 0.0808619 | 6646.59ms | 1833577 | 40 | 1.18482e+08 | 2.1284e+06 | 2(Loss) |
| simdjson (reflection) | 653.756 | 0.17629 | 8817.54ms | 1922245 | 160 | 3.90985e+09 | 2.8041e+06 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2392.86 | 0.339324 | 6019.31ms | 9930848 | 80 | 1.44298e+10 | 3.95794e+06 | 1(Win) |
| simdjson (ondemand) | 1931.98 | 0.220117 | 7567.87ms | 9930848 | 30 | 3.49298e+09 | 4.90212e+06 | 2(Loss) |
| glaze | 1905.71 | 0.256946 | 7970.3ms | 9930848 | 30 | 4.89175e+09 | 4.96969e+06 | 3(Loss) |
| simdjson (reflection) | 1864.45 | 0.656044 | 7825.74ms | 9930848 | 40 | 4.4422e+10 | 5.07967e+06 | 4(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 651.348 | 0.289017 | 8577.18ms | 1834197 | 80 | 4.81952e+09 | 2.68555e+06 | 1(Win) |
| glaze | 494.966 | 0.447144 | 5545.45ms | 1834197 | 30 | 7.49131e+09 | 3.53404e+06 | 2(Loss) |
| simdjson (ondemand) | 445.626 | 0.182849 | 6166.83ms | 1834197 | 30 | 1.54545e+09 | 3.92532e+06 | 3(Loss) |
| simdjson (reflection) | 429.953 | 0.240219 | 6303.03ms | 1834197 | 40 | 3.82054e+09 | 4.06842e+06 | 4(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1267.03 | 0.176887 | 8901.26ms | 1834197 | 160 | 9.54168e+08 | 1.38057e+06 | 1(Win) |
| glaze | 800.693 | 0.097155 | 7020.77ms | 1833577 | 30 | 1.35057e+08 | 2.1839e+06 | 2(Loss) |
| simdjson (reflection) | 664.013 | 0.20582 | 9143.56ms | 1922245 | 40 | 1.29151e+09 | 2.76078e+06 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4640.82 | 0.293004 | 6536.78ms | 9930848 | 160 | 5.72071e+09 | 2.04076e+06 | 1(Win) |
| glaze | 2558.5 | 0.309574 | 5587.26ms | 9930228 | 80 | 1.05043e+10 | 3.70147e+06 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 987.353 | 0.0998723 | 8608.67ms | 642697 | 40 | 1.53751e+07 | 620774 | 1(Win) |
| glaze | 947.315 | 0.0696738 | 8505.53ms | 642697 | 160 | 3.25149e+07 | 647011 | 2(Loss) |
| simdjson (reflection) | 757.567 | 0.892629 | 5196.41ms | 642697 | 40 | 2.08628e+09 | 809069 | 3(Loss) |
| simdjson (ondemand) | 742.278 | 0.481865 | 5222.83ms | 642697 | 160 | 2.53309e+09 | 825733 | 4(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1898.1 | 0.8239 | 9256.65ms | 642697 | 1280 | 9.06009e+09 | 322914 | 1(Win) |
| glaze | 847.681 | 1.15411 | 9055.66ms | 642692 | 640 | 4.45669e+10 | 723054 | 2(Loss) |
| simdjson (reflection) | 747.726 | 0.418843 | 5608.47ms | 643373 | 320 | 3.78001e+09 | 820579 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (reflection) | 1460.01 | 0.589206 | 5246.09ms | 1225964 | 80 | 1.78102e+09 | 800797 | 1(Win) |
| simdjson (ondemand) | 1395.07 | 0.537765 | 5625.26ms | 1225964 | 320 | 6.49981e+09 | 838074 | 2(Loss) |
| glaze | 1342.94 | 0.337827 | 5585.88ms | 1225964 | 320 | 2.7681e+09 | 870606 | 3(Loss) |
| jsonifier | 1223.66 | 1.04481 | 6248.57ms | 1225964 | 320 | 3.18902e+10 | 955472 | 4(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3294.29 | 0.427334 | 9058.25ms | 1225964 | 1280 | 2.94426e+09 | 354908 | 1(Win) |
| glaze | 1212.26 | 1.84219 | 5914.79ms | 1225970 | 320 | 1.01015e+11 | 964462 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 714.798 | 3.09811 | 6936.98ms | 409725 | 40 | 1.14729e+10 | 546650 | 1(Tie) |
| glaze STATISTICAL TIE | 704.143 | 1.36769 | 7208.43ms | 409725 | 80 | 4.60816e+09 | 554922 | 1(Tie) |
| simdjson (reflection) | 610.481 | 0.313686 | 8396.93ms | 409725 | 640 | 2.57996e+09 | 640060 | 3(Loss) |
| simdjson (ondemand) | 566.893 | 0.586193 | 9479.84ms | 409725 | 40 | 6.53017e+08 | 689274 | 4(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5114.45 | 0.265998 | 7540.61ms | 409725 | 1280 | 5.28634e+07 | 76400 | 1(Win) |
| simdjson (reflection) | 4559.87 | 0.398899 | 8765.5ms | 409725 | 640 | 7.47803e+07 | 85692 | 2(Loss) |
| glaze | 1685.73 | 0.267333 | 5996.19ms | 409725 | 1280 | 4.91499e+08 | 231795 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1278.11 | 0.388163 | 7579.88ms | 785750 | 640 | 3.3147e+09 | 586297 | 1(Win) |
| glaze | 1123.39 | 0.631428 | 8751.58ms | 785750 | 160 | 2.83841e+09 | 667043 | 2(Loss) |
| simdjson (reflection) | 1081.58 | 0.287027 | 8800.56ms | 785750 | 640 | 2.53089e+09 | 692826 | 3(Loss) |
| simdjson (ondemand) | 1010.67 | 0.440777 | 9761.19ms | 785750 | 320 | 3.41772e+09 | 741438 | 4(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6532.52 | 0.164331 | 5867.88ms | 785750 | 2560 | 9.09671e+07 | 114711 | 1(Win) |
| glaze | 2149.41 | 0.344052 | 8945.91ms | 785750 | 640 | 9.20786e+08 | 348630 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3184.64 | 0.557873 | 7897.12ms | 264040 | 320 | 6.22644e+07 | 79069.6 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 2714.72 | 0.145671 | 9525.17ms | 264040 | 4890 | 8.92788e+07 | 92756.8 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 2681.82 | 0.738255 | 9563.84ms | 264040 | 160 | 7.68799e+07 | 93894.4 | 2(Tie) |
| glaze | 2072.35 | 0.455958 | 6598.58ms | 264040 | 320 | 9.82233e+07 | 121509 | 4(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3805.06 | 0.536144 | 5331.67ms | 399947 | 320 | 9.2426e+07 | 100240 | 1(Win) |
| simdjson (reflection) STATISTICAL TIE | 3444.1 | 0.567241 | 5834.83ms | 399947 | 320 | 1.26281e+08 | 110746 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3402.1 | 0.384264 | 5686.16ms | 399947 | 640 | 1.18782e+08 | 112113 | 2(Tie) |
| glaze | 2633.67 | 0.376501 | 7495.86ms | 399947 | 640 | 1.9028e+08 | 144824 | 4(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1563.18 | 0.573118 | 8393.44ms | 264040 | 320 | 2.72747e+08 | 161087 | 1(Win) |
| glaze | 1305.06 | 1.20062 | 5118.08ms | 264040 | 40 | 2.1466e+08 | 192947 | 2(Loss) |
| simdjson (reflection) | 1087.44 | 0.330819 | 5939.87ms | 264040 | 1280 | 7.51135e+08 | 231560 | 3(Loss) |
| simdjson (ondemand) | 1002.33 | 1.12402 | 6708.67ms | 264040 | 80 | 6.37901e+08 | 251222 | 4(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9101.23 | 0.228594 | 3093.36ms | 264040 | 2560 | 1.02403e+07 | 27667.5 | 1(Win) |
| simdjson (reflection) | 5119.72 | 0.488569 | 4927.53ms | 264040 | 640 | 3.69555e+07 | 49184 | 2(Loss) |
| glaze | 3095.99 | 0.240667 | 8399.52ms | 263923 | 2560 | 9.80006e+07 | 81297.5 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1908.42 | 0.290256 | 5191.37ms | 399947 | 1280 | 4.30753e+08 | 199861 | 1(Win) |
| glaze | 1620.31 | 0.396091 | 6199.18ms | 399947 | 640 | 5.56392e+08 | 235400 | 2(Loss) |
| simdjson (reflection) | 1583.37 | 0.71612 | 6506.92ms | 399947 | 160 | 4.76139e+08 | 240891 | 3(Loss) |
| simdjson (ondemand) | 1384.98 | 1.65339 | 7189.8ms | 399947 | 30 | 6.21994e+08 | 275396 | 4(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9477.1 | 0.61151 | 4128.98ms | 399947 | 320 | 1.93825e+07 | 40246.4 | 1(Win) |
| glaze | 3331.99 | 0.769078 | 6112.12ms | 399830 | 160 | 1.23938e+08 | 114438 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1507.84 | 0.757217 | 7480.54ms | 466906 | 160 | 8.00035e+08 | 295307 | 1(Win) |
| glaze | 1351.27 | 1.12252 | 8432.35ms | 466906 | 80 | 1.09459e+09 | 329523 | 2(Loss) |
| simdjson (ondemand) | 754.664 | 0.376481 | 7823.29ms | 466906 | 640 | 3.15804e+09 | 590033 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1948.69 | 0.367901 | 8798.32ms | 699405 | 640 | 1.01488e+09 | 342284 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1934.99 | 0.44287 | 8470.49ms | 699405 | 640 | 1.49153e+09 | 344707 | 1(Tie) |
