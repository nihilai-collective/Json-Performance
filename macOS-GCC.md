# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest Results: (Oct 03, 2026)
#### Using the following commits:
----
| Jsonifier: [701dfa9](https://github.com/nihilai-collective/jsonifier/commit/701dfa9)  
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

> Adaptive sampling on (Apple M2 Pro (Virtual)-NEON): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 10% AND mean shift < 5%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

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
| jsonifier | 1595.92 | 5.19186 | 57.4738ms | 905 | 320 | 252273 | 540.8 | 1(Win) |
| glaze | 1392.64 | 1.1313 | 65.406ms | 905 | 4890 | 240373 | 619.74 | 2(Loss) |
| simdjson (ondemand) | 224.012 | 0.229914 | 400.041ms | 905 | 2560 | 200875 | 3852.8 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2269.46 | 2.53404 | 40.8312ms | 905 | 2560 | 237750 | 380.3 | 1(Win) |
| glaze | 141.578 | 0.101534 | 615.797ms | 905 | 4890 | 187342 | 6096.1 | 2(Loss) |
| simdjson (reflection) | 124.456 | 0.151664 | 692.723ms | 905 | 2560 | 283188 | 6934.8 | 3(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1030.31 | 0.424953 | 170.954ms | 1811 | 4890 | 248139 | 1676.3 | 1(Win) |
| glaze | 931.827 | 0.30393 | 191.538ms | 1811 | 4890 | 155176 | 1853.46 | 2(Loss) |
| simdjson (ondemand) | 163.576 | 0.34635 | 1049.55ms | 1811 | 320 | 427933 | 10558.4 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 301.173 | 0.241858 | 611.018ms | 1811 | 1280 | 246229 | 5734.6 | 1(Win) |
| glaze | 231.61 | 0.121777 | 744.581ms | 1798 | 4890 | 397471 | 7403.43 | 2(Loss) |
| simdjson (reflection) | 140.168 | 0.730438 | 1258.66ms | 1997 | 320 | 3.15193e+06 | 13587.2 | 3(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2624.42 | 0.517498 | 143.147ms | 3862 | 4890 | 257920 | 1403.39 | 1(Win) |
| glaze | 1386.29 | 0.479015 | 258.913ms | 3862 | 2560 | 414625 | 2656.8 | 2(Loss) |
| simdjson (ondemand) | 508.104 | 0.141542 | 728.967ms | 3862 | 2560 | 269484 | 7248.7 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 860.542 | 0.173472 | 433.037ms | 3862 | 4890 | 269554 | 4279.96 | 1(Win) |
| glaze | 519.177 | 0.284805 | 677.645ms | 3862 | 2560 | 1.04503e+06 | 7094.1 | 2(Loss) |
| simdjson (reflection) | 334.513 | 0.0837066 | 1136.49ms | 3862 | 2560 | 217449 | 11010.3 | 3(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1312.54 | 0.163016 | 703.945ms | 9578 | 4890 | 629358 | 6959.27 | 1(Win) |
| glaze | 1171.92 | 0.160537 | 779.562ms | 9578 | 2560 | 400814 | 7794.3 | 2(Loss) |
| simdjson (ondemand) | 895.774 | 0.112449 | 1031.74ms | 9578 | 2560 | 336595 | 10197.1 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1328.04 | 0.198736 | 692.165ms | 9578 | 1280 | 239159 | 6878 | 1(Win) |
| jsonifier | 1221.64 | 0.168488 | 754.862ms | 9578 | 2560 | 406299 | 7477.1 | 2(Loss) |
| simdjson (reflection) | 730.589 | 0.0856157 | 1331.44ms | 9578 | 4890 | 560298 | 12502.6 | 3(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2582.57 | 0.51655 | 145.69ms | 3873 | 4890 | 266886 | 1430.2 | 1(Win) |
| glaze | 1628.5 | 0.30567 | 229.716ms | 3873 | 4890 | 235036 | 2268.09 | 2(Loss) |
| simdjson (ondemand) | 418.413 | 0.27195 | 835.929ms | 3873 | 2560 | 1.47537e+06 | 8827.6 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 866.8 | 0.182765 | 429.326ms | 3873 | 4890 | 296586 | 4261.17 | 1(Win) |
| glaze | 592.172 | 0.124666 | 627.41ms | 3873 | 4890 | 295668 | 6237.34 | 2(Loss) |
| simdjson (reflection) | 340.206 | 0.116462 | 1091.24ms | 3873 | 2560 | 409277 | 10856.9 | 3(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 770.959 | 0.0735217 | 8085.58ms | 2090234 | 80 | 2.891e+08 | 2.58561e+06 | 1(Win) |
| glaze | 577.304 | 0.109095 | 5324.22ms | 2090234 | 40 | 5.67615e+08 | 3.45295e+06 | 2(Loss) |
| simdjson (ondemand) | 529.343 | 0.0532017 | 5846.62ms | 2090234 | 40 | 1.60556e+08 | 3.7658e+06 | 3(Loss) |
| simdjson (reflection) | 524.199 | 0.313065 | 5714.8ms | 2090234 | 80 | 1.13385e+10 | 3.80276e+06 | 4(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2647.29 | 0.156778 | 5078.28ms | 2090234 | 30 | 4.18102e+07 | 752998 | 1(Win) |
| glaze | 1804.19 | 0.0917886 | 7047.86ms | 2090234 | 320 | 3.29118e+08 | 1.10487e+06 | 2(Loss) |
| simdjson (reflection) | 817.578 | 0.195541 | 7574.24ms | 2090326 | 160 | 3.63718e+09 | 2.43829e+06 | 3(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1515.27 | 1.67239 | 6138.14ms | 6661897 | 30 | 1.47506e+11 | 4.19284e+06 | 1(Win) |
| glaze | 1429.12 | 0.0501803 | 7036.06ms | 6661897 | 30 | 1.49294e+08 | 4.44558e+06 | 2(Loss) |
| simdjson (ondemand) STATISTICAL TIE | 1219.79 | 1.04981 | 7831.4ms | 6661897 | 30 | 8.96943e+10 | 5.20848e+06 | 3(Tie) |
| simdjson (reflection) STATISTICAL TIE | 1217.98 | 1.62492 | 7940.65ms | 6661897 | 30 | 2.15526e+11 | 5.21623e+06 | 3(Tie) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5978.37 | 0.519536 | 6606.82ms | 6661897 | 80 | 2.43866e+09 | 1.06271e+06 | 1(Win) |
| glaze | 2995.67 | 0.755401 | 6697.25ms | 6661897 | 160 | 4.10661e+10 | 2.12082e+06 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3595.08 | 0.107697 | 9874.91ms | 1439562 | 160 | 2.70625e+07 | 381875 | 1(Win) |
| simdjson (ondemand) | 2645.2 | 0.196697 | 6792.72ms | 1439562 | 30 | 3.12651e+07 | 519006 | 2(Loss) |
| simdjson (reflection) | 2528.78 | 0.194095 | 6929.29ms | 1439562 | 30 | 3.3311e+07 | 542899 | 3(Loss) |
| glaze | 2262.06 | 0.0852234 | 7808.66ms | 1439562 | 160 | 4.28045e+07 | 606912 | 4(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 19278.5 | 0.146686 | 7247.63ms | 1439562 | 320 | 3.49173e+06 | 71212.8 | 1(Win) |
| glaze | 4044.78 | 0.162665 | 8925.13ms | 1439584 | 40 | 1.21937e+07 | 339424 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1634.41 | 0.163514 | 3344.69ms | 56369 | 640 | 1.85119e+06 | 32891.2 | 1(Win) |
| glaze | 1541.77 | 0.14295 | 3499.28ms | 56369 | 640 | 1.58999e+06 | 34867.6 | 2(Loss) |
| simdjson (reflection) | 1133 | 0.116852 | 4831.59ms | 56369 | 1280 | 3.93458e+06 | 47447 | 3(Loss) |
| simdjson (ondemand) | 1043.87 | 0.0489687 | 5190.72ms | 56369 | 4890 | 3.10982e+06 | 51498.5 | 4(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9584.18 | 0.309797 | 592.171ms | 56369 | 1280 | 386487 | 5609 | 1(Win) |
| simdjson (reflection) | 5819.13 | 0.1223 | 929.965ms | 56369 | 2560 | 326782 | 9238.1 | 2(Loss) |
| glaze | 2679.84 | 0.201622 | 2064.98ms | 56369 | 4890 | 7.9992e+06 | 20060 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2136.22 | 0.0814716 | 4321.33ms | 94370 | 2560 | 3.01598e+06 | 42129.7 | 1(Win) |
| glaze | 2028.45 | 0.064682 | 4457.32ms | 94370 | 2560 | 2.10837e+06 | 44368 | 2(Loss) |
| simdjson (reflection) | 1734.85 | 0.208758 | 5315.57ms | 94370 | 160 | 1.87651e+06 | 51876.8 | 3(Loss) |
| simdjson (ondemand) | 1602.1 | 0.0851625 | 5636.47ms | 94370 | 1280 | 2.92952e+06 | 56175.2 | 4(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 10422.7 | 0.422722 | 870.398ms | 94370 | 1280 | 1.70539e+06 | 8634.8 | 1(Win) |
| glaze | 2607.13 | 0.116813 | 3534.2ms | 94370 | 1280 | 2.08131e+06 | 34520 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1444.35 | 0.296623 | 831.067ms | 11812 | 320 | 171261 | 7799.2 | 1(Win) |
| glaze | 1044.27 | 0.210774 | 1136.19ms | 11812 | 640 | 330849 | 10787.2 | 2(Loss) |
| simdjson (reflection) | 926.721 | 0.066629 | 1224.1ms | 11812 | 4890 | 320763 | 12155.6 | 3(Loss) |
| simdjson (ondemand) | 797.429 | 0.171602 | 1424.87ms | 11812 | 640 | 376086 | 14126.4 | 4(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8516.52 | 0.719115 | 136.607ms | 11812 | 2560 | 231611 | 1322.7 | 1(Win) |
| simdjson (reflection) | 5124.09 | 2.09924 | 228.353ms | 11812 | 80 | 170383 | 2198.4 | 2(Loss) |
| glaze | 1870.92 | 0.247681 | 605.89ms | 11812 | 1280 | 284665 | 6021 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2591.16 | 0.336232 | 1163.5ms | 31235 | 320 | 478102 | 11496 | 1(Win) |
| simdjson (reflection) | 2051.26 | 0.159815 | 1463.96ms | 31235 | 1280 | 689422 | 14521.8 | 2(Loss) |
| glaze | 1895.01 | 0.217159 | 1582.89ms | 31235 | 320 | 372877 | 15719.2 | 3(Loss) |
| simdjson (ondemand) | 1807.28 | 0.134172 | 1781.62ms | 31235 | 1280 | 625982 | 16482.2 | 4(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 13405.2 | 0.287181 | 225.27ms | 31235 | 4890 | 199139 | 2222.12 | 1(Win) |
| glaze | 2993.65 | 0.362673 | 1004.3ms | 31235 | 320 | 416737 | 9950.4 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2510.6 | 0.127142 | 4177.95ms | 108313 | 640 | 1.7513e+06 | 41143.6 | 1(Win) |
| glaze | 1565.66 | 0.0761421 | 6650.96ms | 108313 | 2560 | 6.46036e+06 | 65975.6 | 2(Loss) |
| simdjson (reflection) | 1386.4 | 0.0733458 | 7521.34ms | 108313 | 1280 | 3.8225e+06 | 74506.4 | 3(Loss) |
| simdjson (ondemand) | 1305.51 | 0.0958284 | 8047.85ms | 108313 | 640 | 3.67932e+06 | 79122.4 | 4(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 12746.6 | 0.0828772 | 816.315ms | 108313 | 4890 | 220572 | 8103.73 | 1(Win) |
| simdjson (reflection) | 5653.88 | 0.184285 | 1819.19ms | 108313 | 1280 | 1.45097e+06 | 18269.8 | 2(Loss) |
| glaze | 2071.99 | 0.079355 | 5177.02ms | 108313 | 4890 | 7.65325e+06 | 49853.3 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3236.93 | 0.122249 | 6455.28ms | 213963 | 640 | 3.80088e+06 | 63038.4 | 1(Win) |
| simdjson (reflection) | 2324.68 | 0.0752477 | 8960.78ms | 213963 | 1280 | 5.58404e+06 | 87776 | 2(Loss) |
| glaze | 2311.98 | 0.0561259 | 8962.83ms | 213963 | 2560 | 6.28169e+06 | 88258.2 | 3(Loss) |
| simdjson (ondemand) | 2208.55 | 0.0495843 | 9379.91ms | 213963 | 2560 | 5.37267e+06 | 92391.2 | 4(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 14490.6 | 0.247632 | 1467.07ms | 213963 | 320 | 389105 | 14081.6 | 1(Win) |
| glaze | 2433.81 | 0.270611 | 8476.38ms | 213963 | 80 | 4.11798e+06 | 83840 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 651.172 | 0.0612016 | 8362.95ms | 1834197 | 80 | 2.1623e+08 | 2.68628e+06 | 1(Win) |
| glaze | 542.719 | 0.0574228 | 10101.3ms | 1834197 | 40 | 1.37016e+08 | 3.22308e+06 | 2(Loss) |
| simdjson (ondemand) | 490.374 | 0.172006 | 5422.96ms | 1834197 | 80 | 3.01172e+09 | 3.56713e+06 | 3(Loss) |
| simdjson (reflection) | 488.365 | 0.0532669 | 5452.4ms | 1834197 | 30 | 1.09204e+08 | 3.5818e+06 | 4(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1411.17 | 0.134216 | 7980.8ms | 1834197 | 80 | 2.21429e+08 | 1.23956e+06 | 1(Win) |
| glaze | 949.36 | 0.155884 | 5813.74ms | 1833577 | 80 | 6.5952e+08 | 1.84191e+06 | 2(Loss) |
| simdjson (reflection) | 732.999 | 0.0747948 | 7883.48ms | 1922245 | 40 | 1.39963e+08 | 2.50095e+06 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2520.29 | 0.514836 | 5595.89ms | 9930848 | 30 | 1.12288e+10 | 3.75782e+06 | 1(Win) |
| simdjson (ondemand) | 2137.51 | 0.0544493 | 6726.62ms | 9930848 | 30 | 1.74607e+08 | 4.43076e+06 | 2(Loss) |
| simdjson (reflection) | 2124.13 | 0.0586522 | 6768.15ms | 9930848 | 30 | 2.05165e+08 | 4.45868e+06 | 3(Loss) |
| glaze | 2047.58 | 0.0605384 | 7026.67ms | 9930848 | 30 | 2.3522e+08 | 4.62537e+06 | 4(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5267.74 | 0.0571759 | 5652.42ms | 9930848 | 80 | 8.45356e+07 | 1.79788e+06 | 1(Win) |
| glaze | 3317.51 | 0.0669901 | 8984.78ms | 9930228 | 30 | 1.09708e+08 | 2.85461e+06 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 681.041 | 0.0440804 | 8089.8ms | 1834197 | 80 | 1.02548e+08 | 2.56846e+06 | 1(Win) |
| glaze | 546.017 | 0.04158 | 10067.2ms | 1834197 | 80 | 1.41951e+08 | 3.20361e+06 | 2(Loss) |
| simdjson (ondemand) | 491.628 | 0.0345689 | 5415.16ms | 1834197 | 80 | 1.21026e+08 | 3.55803e+06 | 3(Loss) |
| simdjson (reflection) | 488.096 | 0.0710438 | 5414.01ms | 1834197 | 40 | 2.59295e+08 | 3.58378e+06 | 4(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1407.94 | 0.161666 | 7979.84ms | 1834197 | 80 | 3.22738e+08 | 1.2424e+06 | 1(Win) |
| glaze | 923.251 | 0.240419 | 6043.82ms | 1833577 | 160 | 3.31753e+09 | 1.894e+06 | 2(Loss) |
| simdjson (reflection) | 742.495 | 0.0979011 | 7774.37ms | 1922245 | 30 | 1.75278e+08 | 2.46897e+06 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2594.62 | 0.5906 | 5397.7ms | 9930848 | 30 | 1.39423e+10 | 3.65017e+06 | 1(Win) |
| simdjson (ondemand) | 2133.16 | 0.0730504 | 6748.62ms | 9930848 | 30 | 3.15567e+08 | 4.43979e+06 | 2(Loss) |
| simdjson (reflection) | 2119.69 | 0.0940193 | 6777.62ms | 9930848 | 80 | 1.41173e+09 | 4.46801e+06 | 3(Loss) |
| glaze | 2031.2 | 0.202629 | 7057.36ms | 9930848 | 30 | 2.6779e+09 | 4.66266e+06 | 4(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5289.47 | 0.130204 | 5687.15ms | 9930848 | 30 | 1.63048e+08 | 1.7905e+06 | 1(Win) |
| glaze | 2998.71 | 0.0511916 | 9968.12ms | 9930228 | 80 | 2.09092e+08 | 3.15809e+06 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1086.09 | 0.0909342 | 7246.66ms | 642697 | 320 | 8.42726e+07 | 564340 | 1(Win) |
| jsonifier | 1040.65 | 0.0661702 | 7635.99ms | 642697 | 320 | 4.86045e+07 | 588980 | 2(Loss) |
| simdjson (reflection) | 976.94 | 0.0744156 | 8094.32ms | 642697 | 320 | 6.97518e+07 | 627391 | 3(Loss) |
| simdjson (ondemand) | 973.394 | 0.152755 | 8122.55ms | 642697 | 40 | 3.70073e+07 | 629677 | 4(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2663 | 0.286808 | 5893.62ms | 642697 | 80 | 3.48615e+07 | 230163 | 1(Win) |
| glaze | 1250.43 | 0.069578 | 6283.37ms | 642692 | 640 | 7.44414e+07 | 490168 | 2(Loss) |
| simdjson (reflection) | 951.759 | 0.0560468 | 8313.57ms | 643373 | 640 | 8.35514e+07 | 644668 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 1734.85 | 0.10848 | 8650.77ms | 1225964 | 640 | 3.42065e+08 | 673931 | 1(Win) |
| simdjson (reflection) | 1719.4 | 0.271495 | 8732ms | 1225964 | 80 | 2.72657e+08 | 679987 | 2(Loss) |
| glaze | 1640.72 | 0.0602621 | 9178.24ms | 1225964 | 320 | 5.90099e+07 | 712596 | 3(Loss) |
| jsonifier | 1390.51 | 0.0725558 | 5393.04ms | 1225964 | 320 | 1.19098e+08 | 840822 | 4(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4153.51 | 0.0917548 | 7242.6ms | 1225964 | 320 | 2.13468e+07 | 281490 | 1(Win) |
| glaze | 1794.37 | 0.148492 | 8417.95ms | 1225970 | 30 | 2.80841e+07 | 651580 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1027.66 | 0.103778 | 9828.25ms | 409725 | 160 | 2.49121e+07 | 380226 | 1(Win) |
| glaze | 860.24 | 0.384894 | 5824.19ms | 409725 | 40 | 1.22261e+08 | 454227 | 2(Loss) |
| simdjson (reflection) | 765.366 | 0.123888 | 6526.9ms | 409725 | 320 | 1.28013e+08 | 510533 | 3(Loss) |
| simdjson (ondemand) | 714.246 | 0.0800428 | 7057.87ms | 409725 | 320 | 6.13598e+07 | 547072 | 4(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6602.56 | 0.0448252 | 6004.32ms | 409725 | 4890 | 3.44123e+06 | 59180.7 | 1(Win) |
| simdjson (reflection) | 5715.04 | 0.105198 | 6865.88ms | 409725 | 1280 | 6.62179e+06 | 68371.2 | 2(Loss) |
| glaze | 2120 | 0.0837525 | 9616.97ms | 409725 | 1280 | 3.05014e+07 | 184313 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1609.08 | 0.184684 | 5966.59ms | 785750 | 80 | 5.91778e+07 | 465699 | 1(Win) |
| glaze | 1415.65 | 0.213334 | 6760.36ms | 785750 | 30 | 3.82556e+07 | 529331 | 2(Loss) |
| simdjson (reflection) | 1359.26 | 0.070787 | 7066.61ms | 785750 | 320 | 4.87325e+07 | 551290 | 3(Loss) |
| simdjson (ondemand) | 1271.51 | 0.10455 | 7586.3ms | 785750 | 80 | 3.03715e+07 | 589338 | 4(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8471.44 | 0.124614 | 8969.63ms | 785750 | 320 | 3.88813e+06 | 88456 | 1(Win) |
| glaze | 2586.55 | 0.05779 | 7456.24ms | 785750 | 1280 | 3.58791e+07 | 289710 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3735.96 | 0.0506316 | 6872.07ms | 264040 | 4890 | 5.69493e+06 | 67401.2 | 1(Win) |
| simdjson (reflection) STATISTICAL TIE | 3372.41 | 0.177641 | 7633.7ms | 264040 | 160 | 2.81493e+06 | 74667.2 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3371.14 | 0.0447126 | 7561.93ms | 264040 | 4890 | 5.4545e+06 | 74695.3 | 2(Tie) |
| glaze | 2490.63 | 0.167529 | 5232.5ms | 264040 | 160 | 4.59009e+06 | 101102 | 4(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4536.56 | 0.177825 | 8475.03ms | 399947 | 160 | 3.57649e+06 | 84076.8 | 1(Win) |
| simdjson (reflection) | 4251.19 | 0.065587 | 9088.47ms | 399947 | 1280 | 4.43231e+06 | 89720.6 | 2(Loss) |
| simdjson (ondemand) | 4231.05 | 0.0523005 | 9062.39ms | 399947 | 4890 | 1.087e+07 | 90147.7 | 3(Loss) |
| glaze | 3323.21 | 0.199101 | 5923.69ms | 399947 | 80 | 4.17762e+06 | 114774 | 4(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1922.18 | 0.227532 | 6750.9ms | 264040 | 80 | 7.10771e+06 | 131002 | 1(Win) |
| glaze | 1605.23 | 0.199572 | 8064.45ms | 264040 | 320 | 3.13628e+07 | 156867 | 2(Loss) |
| simdjson (reflection) | 1397.06 | 0.143167 | 9323.82ms | 264040 | 160 | 1.0654e+07 | 180242 | 3(Loss) |
| simdjson (ondemand) | 1233.82 | 0.0682811 | 5322.11ms | 264040 | 640 | 1.24285e+07 | 204089 | 4(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11493.6 | 0.112561 | 2265.18ms | 264040 | 1280 | 778424 | 21908.6 | 1(Win) |
| simdjson (reflection) | 6637.92 | 0.162632 | 3758.38ms | 264040 | 1280 | 4.87186e+06 | 37934.8 | 2(Loss) |
| glaze | 3748.04 | 0.044802 | 6852.15ms | 263923 | 4890 | 4.42639e+06 | 67154.2 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2106.82 | 0.345503 | 8918.93ms | 399947 | 80 | 3.12998e+07 | 181040 | 1(Win) |
| glaze | 2022.94 | 0.210245 | 9821.89ms | 399947 | 80 | 1.25713e+07 | 188547 | 2(Loss) |
| simdjson (reflection) | 1943.59 | 0.229617 | 5116.3ms | 399947 | 160 | 3.24881e+07 | 196245 | 3(Loss) |
| simdjson (ondemand) | 1737.19 | 0.148659 | 5664.22ms | 399947 | 80 | 8.5229e+06 | 219562 | 4(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11798.2 | 0.0811858 | 3305.87ms | 399947 | 4890 | 3.36853e+06 | 32328.5 | 1(Win) |
| glaze | 3696.98 | 0.096126 | 5631.93ms | 399830 | 640 | 6.291e+06 | 103140 | 2(Loss) |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 812.57 | 0.153694 | 548.234ms | 4630 | 4890 | 341084 | 5434.01 | 1(Win) |
| glaze | 513.253 | 0.15504 | 866.341ms | 4630 | 2560 | 455436 | 8603 | 2(Loss) |
| simdjson (ondemand) STATISTICAL TIE | 479.85 | 0.0835788 | 923.045ms | 4630 | 4890 | 289236 | 9201.87 | 3(Tie) |
| simdjson (reflection) STATISTICAL TIE | 477.415 | 0.337285 | 970.448ms | 4630 | 320 | 311398 | 9248.8 | 3(Tie) |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2536.05 | 0.521015 | 177.046ms | 4630 | 2560 | 210663 | 1741.1 | 1(Win) |
| glaze | 1723.12 | 0.316474 | 268.137ms | 4630 | 4890 | 321601 | 2562.51 | 2(Loss) |
| simdjson (reflection) | 873.66 | 0.093047 | 508.161ms | 4630 | 4890 | 108141 | 5054.04 | 3(Loss) |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1964.11 | 0.139032 | 731.883ms | 14795 | 2560 | 255367 | 7183.7 | 1(Win) |
| simdjson (ondemand) | 1375.25 | 0.111178 | 1052.91ms | 14795 | 2560 | 333080 | 10259.7 | 2(Loss) |
| simdjson (reflection) | 1363.91 | 0.168714 | 1039.28ms | 14795 | 1280 | 389920 | 10345 | 3(Loss) |
| glaze | 1283.81 | 0.077612 | 1106.18ms | 14795 | 160 | 11641.4 | 10990.4 | 4(Loss) |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7640.03 | 0.421833 | 189.292ms | 14795 | 2560 | 155368 | 1846.8 | 1(Win) |
| glaze | 3289.3 | 0.173905 | 435.495ms | 14795 | 4890 | 272116 | 4289.54 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1389.17 | 0.302727 | 352.183ms | 5092 | 2560 | 286689 | 3495.7 | 1(Win) |
| glaze | 1044.05 | 0.182324 | 471.095ms | 5092 | 4890 | 351668 | 4651.24 | 2(Loss) |
| simdjson (ondemand) | 928.354 | 0.149552 | 527.768ms | 5092 | 4890 | 299257 | 5230.88 | 3(Loss) |
| simdjson (reflection) | 890.811 | 0.158783 | 550.675ms | 5092 | 4890 | 366373 | 5451.33 | 4(Loss) |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7879.65 | 1.14601 | 64.0128ms | 5092 | 4890 | 243921 | 616.285 | 1(Win) |
| simdjson (reflection) | 4586.43 | 0.905167 | 111.202ms | 5092 | 640 | 58784.8 | 1058.8 | 2(Loss) |
| glaze | 1751.21 | 0.438648 | 261.152ms | 5092 | 2560 | 378766 | 2773 | 3(Loss) |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2334.94 | 0.153888 | 484.433ms | 11724 | 4890 | 265532 | 4788.51 | 1(Win) |
| simdjson (ondemand) | 1880.09 | 0.138403 | 599.682ms | 11724 | 2560 | 173432 | 5947 | 2(Loss) |
| simdjson (reflection) | 1812.49 | 0.361359 | 665.806ms | 11724 | 320 | 159011 | 6168.8 | 3(Loss) |
| glaze | 1706.51 | 0.192951 | 665.374ms | 11724 | 2560 | 409137 | 6551.9 | 4(Loss) |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 12142.4 | 0.54646 | 92.4349ms | 11724 | 4890 | 123814 | 920.815 | 1(Win) |
| glaze | 2871.66 | 0.156848 | 393.508ms | 11746 | 4890 | 183054 | 3900.83 | 2(Loss) |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1397.37 | 0.438532 | 331.937ms | 4857 | 1280 | 270475 | 3314.8 | 1(Win) |
| glaze | 1157.13 | 0.496613 | 382.871ms | 4857 | 1280 | 505845 | 4003 | 2(Loss) |
| simdjson (reflection) | 1041.74 | 0.571605 | 447.392ms | 4857 | 640 | 413418 | 4446.4 | 3(Loss) |
| simdjson (ondemand) | 950.914 | 0.213042 | 491.326ms | 4857 | 2560 | 275692 | 4871.1 | 4(Loss) |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8517.83 | 2.57686 | 57.2122ms | 4857 | 1280 | 251345 | 543.8 | 1(Win) |
| simdjson (reflection) | 5177.15 | 0.743889 | 90.6519ms | 4857 | 2560 | 113399 | 894.7 | 2(Loss) |
| glaze | 2773.48 | 0.577187 | 171.37ms | 4857 | 2560 | 237880 | 1670.1 | 3(Loss) |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1743.93 | 0.197414 | 408.579ms | 7376 | 1280 | 81161.6 | 4033.6 | 1(Win) |
| glaze | 1664.47 | 0.165056 | 426.239ms | 7376 | 4890 | 237937 | 4226.15 | 2(Loss) |
| simdjson (reflection) | 1509.38 | 0.177078 | 469.635ms | 7376 | 4890 | 333030 | 4660.4 | 3(Loss) |
| simdjson (ondemand) | 1376.68 | 0.357751 | 560.341ms | 7376 | 320 | 106927 | 5109.6 | 4(Loss) |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9518.71 | 0.867233 | 76.4239ms | 7376 | 4890 | 200847 | 738.997 | 1(Win) |
| glaze | 2465.41 | 0.420685 | 284.899ms | 7376 | 1280 | 184411 | 2853.2 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1384.65 | 0.228525 | 302.617ms | 4390 | 2560 | 122224 | 3023.6 | 1(Win) |
| glaze | 1054.88 | 0.119302 | 403.353ms | 4390 | 4890 | 109630 | 3968.84 | 2(Loss) |
| simdjson (reflection) | 953.24 | 0.898939 | 490.674ms | 4390 | 160 | 249405 | 4392 | 3(Loss) |
| simdjson (ondemand) | 803.252 | 0.192126 | 525.756ms | 4390 | 2560 | 256706 | 5212.1 | 4(Loss) |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8344.89 | 1.9815 | 53.3171ms | 4390 | 2560 | 252998 | 501.7 | 1(Win) |
| simdjson (reflection) | 4609.81 | 0.913946 | 95.4921ms | 4390 | 1280 | 88188.9 | 908.2 | 2(Loss) |
| glaze | 1858.76 | 0.293214 | 227.818ms | 4390 | 4890 | 213286 | 2252.38 | 3(Loss) |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2465.92 | 0.215478 | 446.947ms | 11521 | 4890 | 450753 | 4455.66 | 1(Win) |
| simdjson (reflection) | 2081.95 | 0.279553 | 536.261ms | 11521 | 1280 | 278598 | 5277.4 | 2(Loss) |
| glaze STATISTICAL TIE | 1830.85 | 0.179593 | 602.348ms | 11521 | 1280 | 148684 | 6001.2 | 3(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1830.26 | 0.100878 | 605.785ms | 11521 | 4890 | 179331 | 6003.12 | 3(Tie) |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 13715.5 | 0.750626 | 84.5519ms | 11521 | 4890 | 176813 | 801.086 | 1(Win) |
| glaze | 2817.67 | 0.159071 | 392.195ms | 11521 | 4890 | 188144 | 3899.42 | 2(Loss) |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2305.19 | 0.543519 | 195.031ms | 4669 | 1280 | 141083 | 1931.6 | 1(Win) |
| glaze | 1463.84 | 0.289478 | 307.288ms | 4669 | 2560 | 198487 | 3041.8 | 2(Loss) |
| simdjson (reflection) | 1284.45 | 0.273138 | 350.56ms | 4669 | 4890 | 438418 | 3466.63 | 3(Loss) |
| simdjson (ondemand) | 1209.4 | 0.218686 | 392.361ms | 4669 | 4890 | 316999 | 3681.74 | 4(Loss) |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11935.7 | 1.87757 | 39.8999ms | 4669 | 4890 | 239913 | 373.058 | 1(Win) |
| simdjson (reflection) | 4914.69 | 0.6708 | 93.353ms | 4669 | 2560 | 94554.5 | 906 | 2(Loss) |
| glaze | 2033.2 | 0.387002 | 224.435ms | 4669 | 2560 | 183889 | 2190 | 3(Loss) |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3070.47 | 0.299133 | 291.228ms | 9249 | 2560 | 189038 | 2872.7 | 1(Win) |
| glaze | 2173.62 | 0.422795 | 406.349ms | 9249 | 640 | 188393 | 4058 | 2(Loss) |
| simdjson (ondemand) | 2114.22 | 0.564784 | 421.704ms | 9249 | 320 | 177666 | 4172 | 3(Loss) |
| simdjson (reflection) | 1922.76 | 0.260064 | 452.229ms | 9249 | 4890 | 695995 | 4587.43 | 4(Loss) |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 13743.9 | 1.09161 | 66.6301ms | 9249 | 4890 | 240003 | 641.78 | 1(Win) |
| glaze | 2396.3 | 0.207047 | 373.216ms | 9249 | 4890 | 284025 | 3680.9 | 2(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 634.069 | 0.105583 | 697.687ms | 4604 | 4890 | 261394 | 6924.67 | 1(Win) |
| glaze | 457.748 | 0.188271 | 964.363ms | 4604 | 1280 | 417440 | 9592 | 2(Loss) |
| simdjson (ondemand) | 406.934 | 0.0863288 | 1085.76ms | 4604 | 4890 | 424271 | 10789.7 | 3(Loss) |
| simdjson (reflection) | 404.428 | 0.105608 | 1092.31ms | 4604 | 2560 | 336531 | 10856.6 | 4(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1871.96 | 0.310884 | 238.784ms | 4604 | 4890 | 260005 | 2345.51 | 1(Win) |
| simdjson (reflection) | 1244.47 | 0.629333 | 384.745ms | 4918 | 640 | 360037 | 3768.8 | 2(Loss) |
| glaze | 1096.8 | 0.34587 | 452.191ms | 4604 | 80 | 15336.7 | 4003.2 | 3(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2219.39 | 0.424638 | 1084.08ms | 24579 | 320 | 643647 | 10561.6 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1820.35 | 0.0829015 | 1299.52ms | 24579 | 4890 | 557254 | 12876.9 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 1819.47 | 0.0991231 | 1297.04ms | 24579 | 2560 | 417475 | 12883.1 | 2(Tie) |
| glaze | 1666.75 | 0.0662747 | 1413.24ms | 24579 | 4890 | 424807 | 14063.5 | 4(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6044.45 | 0.284175 | 393.26ms | 24579 | 1280 | 155452 | 3878 | 1(Win) |
| glaze | 3321.29 | 0.290565 | 725.416ms | 24579 | 160 | 67285.2 | 7057.6 | 2(Loss) |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 630.615 | 0.404649 | 664.687ms | 4604 | 1280 | 1.01604e+06 | 6962.6 | 1(Win) |
| glaze | 460.238 | 0.157959 | 955.301ms | 4604 | 2560 | 581343 | 9540.1 | 2(Loss) |
| simdjson (ondemand) STATISTICAL TIE | 403.484 | 0.162818 | 1094.06ms | 4604 | 1280 | 401820 | 10882 | 3(Tie) |
| simdjson (reflection) STATISTICAL TIE | 402.32 | 0.110526 | 1097.41ms | 4604 | 2560 | 372476 | 10913.5 | 3(Tie) |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1780.21 | 1.14868 | 246.437ms | 4604 | 320 | 256848 | 2466.4 | 1(Win) |
| simdjson (reflection) | 1206.03 | 0.15004 | 404.602ms | 4918 | 4890 | 166490 | 3888.95 | 2(Loss) |
| glaze | 1073.76 | 0.16023 | 416.39ms | 4604 | 2560 | 109896 | 4089.1 | 3(Loss) |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2588.06 | 0.0933184 | 912.302ms | 24579 | 4890 | 349320 | 9057.11 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1808.03 | 0.116858 | 1304ms | 24579 | 2560 | 587588 | 12964.6 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 1804.06 | 0.0813061 | 1346.6ms | 24579 | 4890 | 545736 | 12993.1 | 2(Tie) |
| glaze | 1660.19 | 0.0899674 | 1419.38ms | 24579 | 2560 | 413071 | 14119.1 | 4(Loss) |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6045.07 | 0.494244 | 392.62ms | 24579 | 320 | 117533 | 3877.6 | 1(Win) |
| glaze | 3255.2 | 0.146251 | 736.536ms | 24579 | 2560 | 283931 | 7200.9 | 2(Loss) |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 899.305 | 0.987276 | 128.764ms | 1181 | 1280 | 195692 | 1252.4 | 1(Win) |
| glaze | 627.04 | 0.5353 | 181.228ms | 1181 | 2560 | 236670 | 1796.2 | 2(Loss) |
| simdjson (reflection) | 575.592 | 0.206043 | 199.304ms | 1181 | 4890 | 79486.7 | 1956.75 | 3(Loss) |
| simdjson (ondemand) | 560.65 | 0.228987 | 202.791ms | 1181 | 2560 | 54172.4 | 2008.9 | 4(Loss) |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2499.29 | 1.58687 | 48.3351ms | 1181 | 4890 | 250068 | 450.644 | 1(Win) |
| glaze | 1154.86 | 0.298798 | 99.647ms | 1181 | 4890 | 41524.7 | 975.261 | 2(Loss) |
| simdjson (reflection) | 900.853 | 0.994379 | 126.253ms | 1187 | 1280 | 199852 | 1256.6 | 3(Loss) |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1362.39 | 1.42843 | 178.255ms | 2496 | 320 | 199320 | 1747.2 | 1(Win) |
| simdjson (reflection) | 1156.26 | 0.21681 | 208.842ms | 2496 | 4890 | 97419.1 | 2058.68 | 2(Loss) |
| simdjson (ondemand) | 1131.41 | 0.370414 | 213.204ms | 2496 | 2560 | 155477 | 2103.9 | 3(Loss) |
| glaze | 1104.76 | 0.271749 | 224.908ms | 2496 | 4890 | 167646 | 2154.64 | 4(Loss) |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4021.3 | 1.2321 | 61.8381ms | 2496 | 4890 | 260109 | 591.941 | 1(Win) |
| glaze | 1537.89 | 0.479626 | 158.418ms | 2507 | 4890 | 271877 | 1554.64 | 2(Loss) |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1241.36 | 0.249436 | 383.509ms | 4926 | 2560 | 228115 | 3784.4 | 1(Win) |
| glaze | 887.555 | 0.158361 | 530.747ms | 4926 | 4890 | 343559 | 5292.97 | 2(Loss) |
| simdjson (reflection) | 830.866 | 0.200823 | 569.104ms | 4926 | 2560 | 330060 | 5654.1 | 3(Loss) |
| simdjson (ondemand) | 758.297 | 1.09928 | 668.133ms | 4926 | 40 | 185517 | 6195.2 | 4(Loss) |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7024.22 | 3.97338 | 74.9788ms | 4926 | 320 | 225976 | 668.8 | 1(Win) |
| simdjson (reflection) | 4953.39 | 1.3879 | 95.968ms | 4926 | 640 | 110887 | 948.4 | 2(Loss) |
| glaze | 2013.29 | 0.41955 | 239.898ms | 4926 | 2560 | 245350 | 2333.4 | 3(Loss) |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1911.35 | 0.553279 | 486.687ms | 9463 | 320 | 218382 | 4721.6 | 1(Win) |
| simdjson (reflection) | 1463.8 | 0.318534 | 622.09ms | 9463 | 640 | 246823 | 6165.2 | 2(Loss) |
| glaze | 1425.95 | 0.125799 | 638.366ms | 9463 | 4890 | 309963 | 6328.85 | 3(Loss) |
| simdjson (ondemand) | 1338.65 | 0.16693 | 683.097ms | 9463 | 2560 | 324217 | 6741.6 | 4(Loss) |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8061.3 | 0.616968 | 117.642ms | 9463 | 2560 | 122127 | 1119.5 | 1(Win) |
| glaze | 2405.67 | 0.396962 | 393.714ms | 9463 | 1280 | 283853 | 3751.4 | 2(Loss) |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (reflection) STATISTICAL TIE | 3373.86 | 1.00942 | 83.2791ms | 2821 | 2560 | 165856 | 797.4 | 1(Tie) |
| jsonifier STATISTICAL TIE | 3304.35 | 0.710029 | 83.903ms | 2821 | 4890 | 163417 | 814.174 | 1(Tie) |
| simdjson (ondemand) | 3292.7 | 0.70072 | 83.596ms | 2821 | 4890 | 160287 | 817.054 | 3(Loss) |
| glaze | 2574.96 | 0.571794 | 108.211ms | 2821 | 1280 | 45683 | 1044.8 | 4(Loss) |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 4180.2 | 0.495629 | 99.3541ms | 4147 | 2560 | 56289.6 | 946.1 | 1(Tie) |
| simdjson (reflection) STATISTICAL TIE | 4178.35 | 0.434572 | 97.131ms | 4147 | 4890 | 82735.2 | 946.519 | 1(Tie) |
| jsonifier | 4069.19 | 0.291525 | 100.292ms | 4147 | 4890 | 39256.5 | 971.91 | 3(Loss) |
| glaze | 3452.2 | 0.480145 | 117.246ms | 4147 | 4890 | 147955 | 1145.61 | 4(Loss) |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2064.99 | 0.520843 | 134.983ms | 2821 | 4890 | 225162 | 1302.83 | 1(Win) |
| glaze | 1847.74 | 0.509591 | 148.542ms | 2821 | 4890 | 269202 | 1456.01 | 2(Loss) |
| simdjson (reflection) | 1590.06 | 0.440657 | 171.323ms | 2821 | 4890 | 271825 | 1691.96 | 3(Loss) |
| simdjson (ondemand) | 1376.4 | 0.207853 | 198.094ms | 2821 | 4890 | 80712.2 | 1954.6 | 4(Loss) |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9699.74 | 2.31579 | 30.38ms | 2821 | 4890 | 201741 | 277.36 | 1(Win) |
| simdjson (reflection) | 5181.93 | 1.38463 | 54.5239ms | 2821 | 4890 | 252696 | 519.172 | 2(Loss) |
| glaze | 3470.26 | 1.2279 | 80.5302ms | 2819 | 2560 | 231649 | 774.7 | 3(Loss) |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 2279.14 | 0.388416 | 176.047ms | 4147 | 4890 | 222140 | 1735.25 | 1(Win) |
| jsonifier STATISTICAL TIE | 2188.89 | 0.536693 | 185.05ms | 4147 | 2560 | 240720 | 1806.8 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 2164.1 | 0.325549 | 185.731ms | 4147 | 4890 | 173083 | 1827.49 | 2(Tie) |
| simdjson (ondemand) | 1893.82 | 0.224033 | 224.17ms | 4147 | 4890 | 107034 | 2088.31 | 4(Loss) |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 10391.3 | 1.83276 | 40.3082ms | 4147 | 4890 | 237930 | 380.597 | 1(Win) |
| glaze | 3167.96 | 0.695726 | 129.666ms | 4145 | 2560 | 192933 | 1247.8 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1848.35 | 0.742859 | 6101.43ms | 466906 | 30 | 9.6078e+07 | 240905 | 1(Win) |
| glaze | 1602.57 | 0.108201 | 7195.13ms | 466906 | 1280 | 1.15692e+08 | 277852 | 2(Loss) |
| simdjson (ondemand) | 951.13 | 0.0921171 | 5999.04ms | 466906 | 160 | 2.97564e+07 | 468155 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2622.53 | 0.103086 | 6578.95ms | 699405 | 160 | 1.09985e+07 | 254336 | 1(Win) |
| glaze | 2413.49 | 0.100131 | 7120.58ms | 699405 | 320 | 2.4505e+07 | 276365 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4003.67 | 0.0872502 | 7810.03ms | 631514 | 2560 | 4.40984e+07 | 150427 | 1(Win) |
| glaze | 2039.66 | 0.0494757 | 7588.46ms | 631514 | 1280 | 2.73177e+07 | 295274 | 2(Loss) |
