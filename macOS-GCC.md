# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest Results: (Oct 03, 2026)
#### Using the following commits:
----
| Jsonifier: [2fb9afb](https://github.com/nihilai-collective/jsonifier/commit/2fb9afb)  
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
| glaze STATISTICAL TIE | 1255.93 | 3.80885 | 102.472ms | 905 | 320 | 219232 | 687.2 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1234.73 | 3.17966 | 81.8629ms | 905 | 1280 | 632303 | 699 | 1(Tie) |
| simdjson (ondemand) | 115.372 | 1.54452 | 678.562ms | 905 | 1280 | 1.7088e+07 | 7480.8 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1548.39 | 6.37443 | 61.0061ms | 905 | 1280 | 1.61594e+06 | 557.4 | 1(Win) |
| glaze | 114.338 | 0.171121 | 992.486ms | 905 | 4890 | 815890 | 7548.44 | 2(Loss) |
| simdjson (reflection) | 101.548 | 1.74738 | 961.562ms | 905 | 30 | 661688 | 8499.2 | 3(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 808.267 | 0.769015 | 245.871ms | 1811 | 640 | 172813 | 2136.8 | 1(Win) |
| glaze | 728.04 | 3.83486 | 280.763ms | 1811 | 30 | 248284 | 2372.27 | 2(Loss) |
| simdjson (ondemand) | 129.616 | 1.22557 | 1436.04ms | 1811 | 80 | 2.13349e+06 | 13324.8 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 245.612 | 0.135597 | 710.646ms | 1811 | 4890 | 444577 | 7031.83 | 1(Win) |
| glaze | 160.649 | 1.93334 | 1035.87ms | 1798 | 320 | 1.36266e+07 | 10673.6 | 2(Loss) |
| simdjson (reflection) | 136.36 | 0.114495 | 1489.77ms | 1997 | 1280 | 327313 | 13966.6 | 3(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2149.1 | 0.399051 | 177.023ms | 3862 | 4890 | 228706 | 1713.79 | 1(Win) |
| glaze | 1276.81 | 0.373975 | 300.524ms | 3862 | 1280 | 148959 | 2884.6 | 2(Loss) |
| simdjson (ondemand) | 415.315 | 0.124875 | 1024.67ms | 3862 | 4890 | 599688 | 8868.18 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 672.391 | 0.665454 | 578.637ms | 3862 | 640 | 850347 | 5477.6 | 1(Win) |
| glaze | 464.847 | 0.155456 | 790.618ms | 3862 | 4890 | 741872 | 7923.23 | 2(Loss) |
| simdjson (reflection) | 266.535 | 0.225771 | 1401.42ms | 3862 | 640 | 622920 | 13818.4 | 3(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1034.6 | 0.309067 | 883.807ms | 9578 | 1280 | 953054 | 8828.8 | 1(Win) |
| glaze | 976.015 | 0.118341 | 936.778ms | 9578 | 4890 | 599814 | 9358.76 | 2(Loss) |
| simdjson (ondemand) | 733.042 | 0.466277 | 1264.59ms | 9578 | 80 | 270066 | 12460.8 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1070.89 | 0.405332 | 867.5ms | 9578 | 640 | 764994 | 8529.6 | 1(Win) |
| jsonifier | 863.42 | 1.07111 | 944.142ms | 9578 | 320 | 4.10888e+06 | 10579.2 | 2(Loss) |
| simdjson (reflection) | 549.2 | 0.964852 | 1543.41ms | 9578 | 320 | 8.24063e+06 | 16632 | 3(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2114.85 | 0.530226 | 181.476ms | 3873 | 2560 | 219532 | 1746.5 | 1(Win) |
| glaze | 1379.1 | 0.298564 | 274.449ms | 3873 | 4890 | 312672 | 2678.26 | 2(Loss) |
| simdjson (ondemand) | 414.855 | 0.154145 | 900.837ms | 3873 | 2560 | 482170 | 8903.3 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 677.274 | 0.347053 | 561.934ms | 3873 | 2560 | 917063 | 5453.6 | 1(Win) |
| glaze | 484.715 | 0.162593 | 770.788ms | 3873 | 4890 | 750646 | 7620.11 | 2(Loss) |
| simdjson (reflection) | 277.358 | 0.191584 | 1353.72ms | 3873 | 4890 | 3.18302e+06 | 13317 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2080.71 | 0.360138 | 6929.44ms | 2090234 | 30 | 3.57128e+08 | 958037 | 1(Win) |
| glaze | 1110.9 | 3.84929 | 5740.63ms | 2090234 | 40 | 1.90836e+11 | 1.7944e+06 | 2(Loss) |
| simdjson (reflection) | 640.312 | 1.6389 | 5003.46ms | 2090326 | 80 | 2.08276e+11 | 3.11331e+06 | 3(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1605.08 | 0.442153 | 7939.93ms | 500299 | 1280 | 2.21117e+09 | 297258 | 1(Win) |
| glaze | 1044.63 | 0.590726 | 5664.1ms | 500299 | 640 | 4.65889e+09 | 456736 | 2(Loss) |
| simdjson (ondemand) | 966.373 | 0.160994 | 7737.07ms | 500299 | 80 | 5.05448e+07 | 493725 | 3(Loss) |
| simdjson (reflection) | 854.519 | 0.873993 | 7184.38ms | 500299 | 80 | 1.90512e+09 | 558352 | 4(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6774.23 | 2.66808 | 7350.8ms | 500299 | 40 | 1.41253e+08 | 70432 | 1(Win) |
| simdjson (reflection) | 4133.59 | 0.26215 | 6736.61ms | 500299 | 640 | 5.85983e+07 | 115426 | 2(Loss) |
| glaze | 1606.82 | 0.440458 | 7296.39ms | 500299 | 640 | 1.09474e+09 | 296936 | 3(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1364.5 | 0.485609 | 4221.56ms | 56369 | 4890 | 1.78986e+08 | 39397.4 | 1(Win) |
| glaze | 1126.92 | 0.507281 | 4698.19ms | 56369 | 4890 | 2.8635e+08 | 47703 | 2(Loss) |
| simdjson (reflection) STATISTICAL TIE | 850.109 | 0.651179 | 6339.2ms | 56369 | 1280 | 2.17041e+08 | 63236.2 | 3(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 834.125 | 1.89631 | 6764.68ms | 56369 | 40 | 5.97445e+07 | 64448 | 3(Tie) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1691.48 | 0.545881 | 5760.29ms | 94370 | 640 | 5.39896e+07 | 53206.8 | 1(Win) |
| glaze | 1495.42 | 0.670482 | 5631.89ms | 94370 | 160 | 2.60515e+07 | 60182.4 | 2(Loss) |
| simdjson (ondemand) STATISTICAL TIE | 1127.05 | 3.71331 | 9251.18ms | 94370 | 80 | 7.03385e+08 | 79852.8 | 3(Tie) |
| simdjson (reflection) STATISTICAL TIE | 1063.83 | 1.0075 | 8512.11ms | 94370 | 1280 | 9.2988e+08 | 84598.4 | 3(Tie) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7114.26 | 1.13741 | 1495.37ms | 94370 | 2560 | 5.30009e+07 | 12650.4 | 1(Win) |
| glaze | 1997.76 | 3.04548 | 5401.62ms | 94370 | 80 | 1.50585e+08 | 45049.6 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1123.73 | 0.957282 | 961.919ms | 11812 | 4890 | 4.50309e+07 | 10024.5 | 1(Win) |
| simdjson (reflection) | 795.237 | 0.485034 | 1539.08ms | 11812 | 30 | 141618 | 14165.3 | 2(Loss) |
| glaze | 699.955 | 1.87948 | 1608.85ms | 11812 | 640 | 5.8555e+07 | 16093.6 | 3(Loss) |
| simdjson (ondemand) | 557.376 | 1.84721 | 1928.43ms | 11812 | 640 | 8.91997e+07 | 20210.4 | 4(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5955.17 | 3.38987 | 181.085ms | 11812 | 640 | 2.6315e+06 | 1891.6 | 1(Win) |
| simdjson (reflection) | 3811.34 | 0.767933 | 308.824ms | 11812 | 640 | 329699 | 2955.6 | 2(Loss) |
| glaze | 1438.45 | 0.842807 | 816.859ms | 11812 | 320 | 1.394e+06 | 7831.2 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2198.99 | 0.399272 | 1447.19ms | 31235 | 1280 | 3.7444e+06 | 13546.2 | 1(Win) |
| simdjson (reflection) | 1694.04 | 0.334164 | 1819.23ms | 31235 | 640 | 2.20971e+06 | 17584 | 2(Loss) |
| glaze | 1424.01 | 1.77649 | 2202.36ms | 31235 | 160 | 2.20954e+07 | 20918.4 | 3(Loss) |
| simdjson (ondemand) | 1264.05 | 0.655214 | 2452.25ms | 31235 | 4890 | 1.16581e+08 | 23565.5 | 4(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9398.04 | 1.55655 | 343.668ms | 31235 | 2560 | 6.23127e+06 | 3169.6 | 1(Win) |
| glaze | 2577.04 | 0.317385 | 1340.8ms | 31235 | 1280 | 1.72276e+06 | 11559 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2266.08 | 0.385503 | 5043.81ms | 108313 | 320 | 9.88132e+06 | 45583.2 | 1(Win) |
| glaze | 1170.8 | 0.549965 | 8626.46ms | 108313 | 320 | 7.53385e+07 | 88226.4 | 2(Loss) |
| simdjson (reflection) | 1133.6 | 0.212011 | 5016.16ms | 108313 | 640 | 2.38859e+07 | 91121.6 | 3(Loss) |
| simdjson (ondemand) | 1089.37 | 0.190916 | 5273.15ms | 108313 | 1280 | 4.19473e+07 | 94821 | 4(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9910.9 | 0.674845 | 1428.62ms | 108313 | 320 | 1.58304e+06 | 10422.4 | 1(Win) |
| simdjson (reflection) | 3722.53 | 0.693885 | 2555.2ms | 108313 | 2560 | 9.49074e+07 | 27748.7 | 2(Loss) |
| glaze | 1452.33 | 0.566455 | 6912.94ms | 108313 | 1280 | 2.07765e+08 | 71124 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2376.25 | 3.42473 | 8522.03ms | 213963 | 30 | 2.59458e+08 | 85870.9 | 1(Win) |
| glaze | 1954.41 | 0.284369 | 6475.87ms | 213963 | 30 | 2.64442e+06 | 104405 | 2(Loss) |
| simdjson (reflection) | 1718.78 | 0.594833 | 6559.22ms | 213963 | 640 | 3.19158e+08 | 118718 | 3(Loss) |
| simdjson (ondemand) | 1663.46 | 0.832449 | 6649.39ms | 213963 | 640 | 6.67343e+08 | 122667 | 4(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 10307.3 | 2.39748 | 2078.03ms | 213963 | 160 | 3.60429e+07 | 19796.8 | 1(Win) |
| glaze | 1939.57 | 0.327087 | 5707.53ms | 213963 | 1280 | 1.51566e+08 | 105204 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 904.926 | 3.09568 | 6030.3ms | 1834197 | 80 | 2.86462e+11 | 1.933e+06 | 1(Win) |
| glaze | 680.766 | 1.68092 | 9023.49ms | 1833577 | 80 | 1.49138e+11 | 2.56863e+06 | 2(Loss) |
| simdjson (reflection) | 481.673 | 1.61828 | 6034.96ms | 1922245 | 80 | 3.03467e+11 | 3.80589e+06 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4307.44 | 0.258588 | 7185.28ms | 9930848 | 40 | 1.29304e+09 | 2.19871e+06 | 1(Win) |
| glaze | 2155.05 | 2.01247 | 6988.55ms | 9930228 | 30 | 2.3463e+11 | 4.39442e+06 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 871.577 | 0.326881 | 9979.13ms | 642697 | 80 | 4.22736e+08 | 703235 | 1(Win) |
| simdjson (reflection) | 841.736 | 0.694789 | 5676.08ms | 642697 | 30 | 7.67872e+08 | 728166 | 2(Loss) |
| jsonifier | 781.786 | 1.06481 | 9623.49ms | 642697 | 320 | 2.23013e+10 | 784005 | 3(Loss) |
| simdjson (ondemand) | 640.268 | 1.447 | 5502.09ms | 642697 | 40 | 7.67515e+09 | 957293 | 4(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2009.26 | 1.28776 | 8373.53ms | 642697 | 40 | 6.17268e+08 | 305050 | 1(Win) |
| glaze | 791.301 | 3.45116 | 8950.26ms | 642692 | 30 | 2.14374e+10 | 774571 | 2(Loss) |
| simdjson (reflection) | 710.366 | 0.937542 | 5570.29ms | 643373 | 30 | 1.96727e+09 | 863735 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3503.9 | 0.40847 | 9135.34ms | 1225964 | 40 | 7.43074e+07 | 333677 | 1(Win) |
| glaze | 1359.62 | 0.194028 | 5408.39ms | 1225970 | 320 | 8.90842e+08 | 859926 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 876.459 | 0.138375 | 5634.89ms | 409725 | 640 | 2.43567e+08 | 445822 | 1(Win) |
| glaze | 726.098 | 0.12054 | 7154.02ms | 409725 | 640 | 2.69301e+08 | 538143 | 2(Loss) |
| simdjson (reflection) | 644.816 | 0.353456 | 7791.78ms | 409725 | 40 | 1.83503e+08 | 605978 | 3(Loss) |
| simdjson (ondemand) | 622.052 | 0.167812 | 8639.13ms | 409725 | 320 | 3.55573e+08 | 628154 | 4(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5542.95 | 0.593659 | 7032.79ms | 409725 | 30 | 5.2541e+06 | 70493.9 | 1(Win) |
| simdjson (reflection) | 4726.37 | 0.0720096 | 8597.71ms | 409725 | 4890 | 1.73308e+07 | 82673.2 | 2(Loss) |
| glaze | 1762.97 | 0.143354 | 5760.12ms | 409725 | 320 | 3.23044e+07 | 221639 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1354.9 | 0.521041 | 7381.55ms | 785750 | 80 | 6.64334e+08 | 553066 | 1(Win) |
| glaze | 1171.58 | 0.123058 | 8317.59ms | 785750 | 160 | 9.91208e+07 | 639606 | 2(Loss) |
| simdjson (reflection) | 1122.36 | 0.260903 | 8488.69ms | 785750 | 320 | 9.70985e+08 | 667656 | 3(Loss) |
| simdjson (ondemand) | 1060.27 | 0.0853971 | 9217.26ms | 785750 | 320 | 1.16565e+08 | 706750 | 4(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7131.56 | 0.259948 | 5493.5ms | 785750 | 40 | 2.98424e+06 | 105075 | 1(Win) |
| glaze | 2258.74 | 0.0676651 | 8431.09ms | 785750 | 1280 | 6.45025e+07 | 331756 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3410.63 | 0.162551 | 7518ms | 264040 | 30 | 432086 | 73830.4 | 1(Win) |
| simdjson (reflection) | 2823.84 | 0.0856629 | 8965.95ms | 264040 | 2560 | 1.49377e+07 | 89172.2 | 2(Loss) |
| simdjson (ondemand) | 2643.88 | 0.535102 | 8994.74ms | 264040 | 640 | 1.6623e+08 | 95242 | 3(Loss) |
| glaze | 2119.77 | 0.175066 | 6707.62ms | 264040 | 320 | 1.38394e+07 | 118790 | 4(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 3666.14 | 1.24396 | 5361.3ms | 399947 | 30 | 5.02485e+07 | 104038 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3579.42 | 0.168561 | 6241.15ms | 399947 | 640 | 2.06477e+07 | 106559 | 1(Tie) |
| simdjson (reflection) | 3067.46 | 0.780986 | 6221.62ms | 399947 | 1280 | 1.2071e+09 | 124344 | 3(Loss) |
| glaze | 2803.98 | 0.0949627 | 7094.45ms | 399947 | 1280 | 2.13585e+07 | 136028 | 4(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1561.15 | 0.50696 | 8365.56ms | 264040 | 2560 | 1.71174e+09 | 161296 | 1(Win) |
| glaze | 1380.18 | 0.136009 | 10296.9ms | 264040 | 640 | 3.94083e+07 | 182446 | 2(Loss) |
| simdjson (reflection) | 1159.97 | 0.195648 | 5667.49ms | 264040 | 160 | 2.88614e+07 | 217082 | 3(Loss) |
| simdjson (ondemand) | 1024.51 | 0.408524 | 6341.54ms | 264040 | 160 | 1.61311e+08 | 245784 | 4(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9676.59 | 0.240328 | 2647.07ms | 264040 | 40 | 156446 | 26022.4 | 1(Win) |
| simdjson (reflection) | 5363.85 | 0.117383 | 4969.04ms | 264040 | 2560 | 7.7738e+06 | 46945.4 | 2(Loss) |
| glaze | 3246.86 | 0.0759367 | 7960.08ms | 263923 | 4890 | 1.6945e+07 | 77520 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2039.95 | 0.432586 | 9973.62ms | 399947 | 160 | 1.04672e+08 | 186974 | 1(Win) |
| glaze | 1705.95 | 0.103962 | 5735.08ms | 399947 | 1280 | 6.9156e+07 | 223581 | 2(Loss) |
| simdjson (reflection) | 1588.06 | 0.270797 | 6406.56ms | 399947 | 640 | 2.70732e+08 | 240180 | 3(Loss) |
| simdjson (ondemand) | 1432.84 | 1.00645 | 6796.37ms | 399947 | 30 | 2.15334e+08 | 266197 | 4(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 10140.9 | 0.152173 | 3848.41ms | 399947 | 2560 | 8.38618e+06 | 37611.9 | 1(Win) |
| glaze | 3368.06 | 0.243646 | 5764ms | 399830 | 320 | 2.43477e+07 | 113213 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1594.41 | 0.411961 | 7208.32ms | 466906 | 80 | 1.05892e+08 | 279274 | 1(Win) |
| glaze | 1379.14 | 0.115151 | 8223ms | 466906 | 640 | 8.8462e+07 | 322865 | 2(Loss) |
| simdjson (ondemand) | 751.559 | 0.808512 | 7282.01ms | 466906 | 320 | 7.3427e+09 | 592470 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2326.52 | 0.1084 | 8124.02ms | 699405 | 320 | 3.09068e+07 | 286697 | 1(Win) |
| glaze | 1974.26 | 0.12356 | 9233.92ms | 699405 | 640 | 1.11527e+08 | 337850 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3301.36 | 0.1245 | 9506.58ms | 631514 | 1280 | 6.60285e+07 | 182427 | 1(Win) |
| glaze | 1717.65 | 0.381987 | 9036.28ms | 631514 | 160 | 2.87022e+08 | 350630 | 2(Loss) |
