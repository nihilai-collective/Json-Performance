# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the Clang 23.1.0 compiler).  

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

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 941.406 | 0.171188 | 0.6225ms | 1811 | 30 | 295.903 | 1834.6 | 1(Win) |
| jsonifier | 909.641 | 0.431135 | 38.6968ms | 1811 | 30 | 2010.23 | 1898.67 | 2(Loss) |
| simdjson (ondemand) | 178.128 | 0.222143 | 3.05446ms | 1811 | 30 | 13917.4 | 9695.87 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1024.34 | 0.226728 | 0.535417ms | 1811 | 30 | 438.409 | 1686.07 | 1(Win) |
| glaze | 670.252 | 1.95717 | 0.831792ms | 1798 | 30 | 75211 | 2558.3 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1468.73 | 1.33446 | 7.96079ms | 3873 | 160 | 180196 | 2514.82 | 1(Win) |
| glaze | 1219.37 | 2.54322 | 2.13471ms | 3873 | 40 | 237385 | 3029.1 | 2(Loss) |
| simdjson (ondemand) | 393.454 | 2.13927 | 6.43554ms | 3873 | 40 | 1.61323e+06 | 9387.58 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4207.77 | 0.599922 | 0.280583ms | 3873 | 30 | 831.959 | 877.8 | 1(Win) |
| glaze | 2376.57 | 0.22821 | 0.626083ms | 3873 | 30 | 377.385 | 1554.17 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1639.94 | 0.269096 | 3.54046ms | 3862 | 80 | 2921.94 | 2245.86 | 1(Win) |
| glaze | 1319.36 | 1.53034 | 0.889458ms | 3862 | 30 | 54751.2 | 2791.57 | 2(Loss) |
| simdjson (ondemand) | 355.176 | 2.64181 | 7.24488ms | 3862 | 40 | 3.00194e+06 | 10369.8 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4073.31 | 0.392659 | 0.340709ms | 3862 | 30 | 378.166 | 904.2 | 1(Win) |
| glaze | 2290.1 | 0.505705 | 0.595125ms | 3862 | 30 | 1984.41 | 1608.27 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1806.1 | 1.23234 | 0.155375ms | 905 | 30 | 1040.4 | 477.867 | 1(Win) |
| jsonifier | 1542.12 | 0.683873 | 0.186583ms | 905 | 30 | 439.471 | 559.667 | 2(Loss) |
| simdjson (ondemand) | 194.072 | 0.109473 | 1.357ms | 905 | 30 | 711.062 | 4447.2 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1497.44 | 0.498255 | 0.186792ms | 905 | 30 | 247.413 | 576.367 | 1(Win) |
| glaze | 1155.43 | 0.645451 | 0.592541ms | 905 | 40 | 929.82 | 746.975 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 2407.29 | 0.400605 | 1.20958ms | 9578 | 30 | 6931.84 | 3794.43 | 1(Win) |
| jsonifier | 2246.14 | 2.30815 | 1.35337ms | 9578 | 30 | 264318 | 4066.67 | 2(Loss) |
| simdjson (ondemand) | 679.471 | 0.147309 | 4.18883ms | 9578 | 30 | 11764.8 | 13443.2 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 4369.92 | 0.359012 | 0.65175ms | 9578 | 30 | 1689.44 | 2090.27 | 1(Win) |
| jsonifier | 4298.15 | 0.449982 | 0.781583ms | 9578 | 30 | 2743.45 | 2125.17 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 549.223 | 0.120628 | 1092.91ms | 2090234 | 30 | 5.75056e+08 | 3.6295e+06 | 1(Win) |
| glaze | 501.421 | 0.15805 | 1247.17ms | 2090234 | 30 | 1.18438e+09 | 3.9755e+06 | 2(Loss) |
| simdjson (ondemand) | 371.794 | 0.168716 | 1562.63ms | 2090234 | 30 | 2.45481e+09 | 5.36158e+06 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1653.64 | 0.16473 | 364.211ms | 2090234 | 30 | 1.18298e+08 | 1.20547e+06 | 1(Win) |
| glaze | 1454.91 | 0.503455 | 402.153ms | 2090234 | 30 | 1.42746e+09 | 1.37013e+06 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1323.46 | 0.403635 | 6909.66ms | 6661897 | 80 | 3.0036e+10 | 4.80051e+06 | 1(Win) |
| glaze | 1215.73 | 0.244708 | 1557.33ms | 6661897 | 30 | 4.90611e+09 | 5.22588e+06 | 2(Loss) |
| simdjson (ondemand) | 1124.61 | 0.269794 | 4057.43ms | 6661897 | 40 | 9.29213e+09 | 5.64932e+06 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3317.61 | 0.193657 | 574.949ms | 6661897 | 30 | 4.12604e+08 | 1.91502e+06 | 1(Win) |
| glaze | 2640.34 | 0.371391 | 705.184ms | 6661897 | 30 | 2.39586e+09 | 2.40624e+06 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1391.08 | 0.477852 | 103.481ms | 500299 | 30 | 8.05869e+07 | 342987 | 1(Win) |
| glaze | 992.476 | 0.897172 | 354.22ms | 500299 | 40 | 7.441e+08 | 480740 | 2(Loss) |
| simdjson (ondemand) | 715.46 | 0.171921 | 9330.59ms | 500299 | 640 | 8.41252e+08 | 666875 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2402.46 | 0.836094 | 58.9653ms | 500299 | 30 | 8.27136e+07 | 198597 | 1(Win) |
| glaze | 1812.51 | 0.319434 | 80.6965ms | 500299 | 30 | 2.12121e+07 | 263239 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 2044.11 | 0.245696 | 203.873ms | 1439562 | 30 | 8.16901e+07 | 671625 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2037.23 | 2.4231 | 195.167ms | 1439562 | 30 | 7.99917e+09 | 673892 | 1(Tie) |
| simdjson (ondemand) | 1848.05 | 0.200492 | 226.331ms | 1439562 | 30 | 6.65503e+07 | 742876 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6044.53 | 0.36354 | 68.5279ms | 1439562 | 30 | 2.04532e+07 | 227126 | 1(Win) |
| glaze | 2664.27 | 0.367041 | 154.849ms | 1439584 | 30 | 1.07317e+08 | 515299 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1420.34 | 1.82513 | 12.8758ms | 56369 | 30 | 1.43155e+07 | 37848.5 | 1(Win) |
| glaze | 1201.74 | 0.725763 | 13.7152ms | 56369 | 30 | 3.16207e+06 | 44733.2 | 2(Loss) |
| simdjson (ondemand) | 1043.92 | 0.0175275 | 15.6665ms | 56369 | 30 | 2444.03 | 51495.8 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2738.26 | 1.06462 | 5.89321ms | 56369 | 30 | 1.31051e+06 | 19632 | 1(Win) |
| glaze | 2481.6 | 0.296362 | 6.7005ms | 56369 | 30 | 123646 | 21662.5 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1738.16 | 1.29122 | 16.6194ms | 94370 | 30 | 1.34095e+07 | 51777.8 | 1(Win) |
| simdjson (ondemand) | 1610.81 | 0.417162 | 84.3918ms | 94370 | 80 | 4.34587e+06 | 55871.3 | 2(Loss) |
| glaze | 1528.29 | 0.865504 | 188.489ms | 94370 | 160 | 4.15638e+07 | 58888.3 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5250.27 | 0.172254 | 5.36475ms | 94370 | 30 | 26155.5 | 17141.6 | 1(Win) |
| glaze | 2518.02 | 0.253282 | 10.927ms | 94370 | 30 | 245856 | 35741.7 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 948.729 | 1.39063 | 3.69671ms | 11812 | 30 | 817915 | 11873.6 | 1(Win) |
| glaze | 783.153 | 1.44791 | 22.2697ms | 11812 | 80 | 3.46996e+06 | 14383.9 | 2(Loss) |
| simdjson (ondemand) | 732.738 | 0.186801 | 4.73733ms | 11812 | 30 | 24741.8 | 15373.6 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2441.53 | 0.283867 | 1.46025ms | 11812 | 30 | 5146.07 | 4613.83 | 1(Win) |
| glaze | 1547.53 | 0.0829471 | 2.24208ms | 11812 | 30 | 1093.68 | 7279.2 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1784.89 | 1.09803 | 5.10267ms | 31235 | 30 | 1.00742e+06 | 16689 | 1(Win) |
| glaze STATISTICAL TIE | 1728.36 | 0.224425 | 5.3865ms | 31235 | 30 | 44882.4 | 17234.8 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1718.68 | 0.228719 | 5.32042ms | 31235 | 30 | 47143.1 | 17331.9 | 2(Tie) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5745.52 | 0.558531 | 69.1315ms | 31235 | 640 | 536660 | 5184.56 | 1(Win) |
| glaze | 2541.47 | 0.386728 | 3.62087ms | 31235 | 30 | 61637.8 | 11720.8 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2183.78 | 0.316359 | 14.9781ms | 108313 | 30 | 671779 | 47301.2 | 1(Win) |
| glaze | 1294.33 | 0.741585 | 56.0297ms | 108313 | 40 | 1.40106e+07 | 79806.2 | 2(Loss) |
| simdjson (ondemand) | 938.646 | 1.75028 | 32.7362ms | 108313 | 30 | 1.11299e+08 | 110047 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2398.26 | 0.452869 | 13.0479ms | 108313 | 30 | 1.14139e+06 | 43071 | 1(Win) |
| glaze | 1660.92 | 1.34698 | 43.5682ms | 108313 | 40 | 2.80703e+07 | 62191.6 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2402.02 | 0.60258 | 26.4255ms | 213963 | 30 | 7.86098e+06 | 84949.9 | 1(Win) |
| glaze | 2167.33 | 0.507501 | 28.992ms | 213963 | 30 | 6.84892e+06 | 94148.6 | 2(Loss) |
| simdjson (ondemand) | 1841.55 | 0.368333 | 33.8631ms | 213963 | 30 | 4.99705e+06 | 110804 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5050.43 | 0.52068 | 12.2311ms | 213963 | 30 | 1.32765e+06 | 40402.7 | 1(Win) |
| glaze | 1891.23 | 1.37836 | 33.5443ms | 213963 | 30 | 6.6349e+07 | 107893 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 501.628 | 0.251187 | 1054.26ms | 1834197 | 30 | 2.30168e+09 | 3.4871e+06 | 1(Win) |
| glaze | 412.853 | 0.647271 | 1283.96ms | 1834197 | 30 | 2.25629e+10 | 4.23692e+06 | 2(Loss) |
| simdjson (ondemand) | 121.065 | 0.189371 | 4298.23ms | 1834197 | 30 | 2.24597e+10 | 1.44487e+07 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 757.887 | 0.151368 | 689.677ms | 1833577 | 30 | 3.65915e+08 | 2.30725e+06 | 1(Tie) |
| jsonifier STATISTICAL TIE | 752.859 | 0.651654 | 686.128ms | 1834197 | 30 | 6.87733e+09 | 2.32344e+06 | 1(Tie) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1978.01 | 0.136741 | 1497.95ms | 9930848 | 30 | 1.28599e+09 | 4.78805e+06 | 1(Win) |
| glaze | 1757.58 | 0.157876 | 1610.25ms | 9930848 | 30 | 2.17117e+09 | 5.38853e+06 | 2(Loss) |
| simdjson (ondemand) | 580.599 | 2.01568 | 4796.15ms | 9930848 | 30 | 3.24328e+12 | 1.63121e+07 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2936.13 | 0.182076 | 10635.8ms | 9930848 | 160 | 5.51885e+09 | 3.22561e+06 | 1(Win) |
| glaze | 2790.3 | 0.759864 | 1060.41ms | 9930228 | 30 | 1.99531e+10 | 3.39397e+06 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 508.824 | 0.666561 | 1020.52ms | 1834197 | 30 | 1.57528e+10 | 3.43778e+06 | 1(Win) |
| glaze | 437.098 | 0.239643 | 2842.99ms | 1834197 | 40 | 3.67894e+09 | 4.00191e+06 | 2(Loss) |
| simdjson (ondemand) | 355.33 | 0.337907 | 3622.03ms | 1834197 | 40 | 1.10684e+10 | 4.92283e+06 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 803.41 | 0.178464 | 650.55ms | 1834197 | 30 | 4.52938e+08 | 2.17725e+06 | 1(Win) |
| glaze | 740.884 | 0.17017 | 703.902ms | 1833577 | 30 | 4.8393e+08 | 2.3602e+06 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2080.66 | 0.429793 | 1408.77ms | 9930848 | 30 | 1.14817e+10 | 4.55181e+06 | 1(Win) |
| glaze | 1771.74 | 0.156615 | 8181.78ms | 9930848 | 80 | 5.60697e+09 | 5.34548e+06 | 2(Loss) |
| simdjson (ondemand) | 1599.17 | 0.19478 | 19090.9ms | 9930848 | 160 | 2.12908e+10 | 5.92231e+06 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 2475.29 | 0.41926 | 1152.09ms | 9930228 | 30 | 7.71887e+09 | 3.8259e+06 | 1(Win) |
| jsonifier | 2134.93 | 0.126765 | 1327.59ms | 9930848 | 30 | 9.48687e+08 | 4.43612e+06 | 2(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1238.66 | 0.420297 | 145.914ms | 642697 | 30 | 1.2976e+08 | 494826 | 1(Win) |
| glaze | 1102.05 | 0.365808 | 168.167ms | 642692 | 30 | 1.24175e+08 | 556164 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1375.85 | 1.37284 | 257.682ms | 1225964 | 30 | 4.08295e+09 | 849779 | 1(Win) |
| simdjson (ondemand) | 1270.01 | 0.190792 | 1374.87ms | 1225964 | 80 | 2.46803e+08 | 920596 | 2(Loss) |
| jsonifier | 1232.66 | 0.73797 | 282.875ms | 1225964 | 30 | 1.46983e+09 | 948493 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2220.52 | 0.234316 | 158.59ms | 1225964 | 30 | 4.56635e+07 | 526529 | 1(Win) |
| glaze | 1696.66 | 0.180603 | 211.061ms | 1225970 | 30 | 4.64665e+07 | 689104 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 799.602 | 0.531059 | 148.857ms | 409725 | 30 | 2.02044e+08 | 488674 | 1(Win) |
| jsonifier | 776.148 | 0.240894 | 352.73ms | 409725 | 40 | 5.88313e+07 | 503441 | 2(Loss) |
| simdjson (ondemand) | 754.83 | 0.310618 | 156.861ms | 409725 | 30 | 7.7564e+07 | 517658 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2527.75 | 0.359821 | 46.9908ms | 409725 | 30 | 9.28139e+06 | 154582 | 1(Win) |
| glaze | 1675.08 | 0.482381 | 70.8354ms | 409725 | 30 | 3.79855e+07 | 233269 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1309.47 | 0.26136 | 173.251ms | 785750 | 30 | 6.71087e+07 | 572255 | 1(Win) |
| simdjson (ondemand) | 1257.57 | 0.292405 | 181.778ms | 785750 | 30 | 9.10735e+07 | 595870 | 2(Loss) |
| jsonifier | 1058.16 | 1.73546 | 215.942ms | 785750 | 30 | 4.53118e+09 | 708160 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4322.69 | 0.355302 | 52.555ms | 785750 | 30 | 1.1381e+07 | 173353 | 1(Win) |
| glaze | 2307.58 | 0.234237 | 98.4342ms | 785750 | 30 | 1.73575e+07 | 324733 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3471.75 | 0.711026 | 22.2403ms | 264040 | 30 | 7.97873e+06 | 72530.6 | 1(Win) |
| simdjson (ondemand) | 3056.75 | 0.742134 | 25.0361ms | 264040 | 30 | 1.12126e+07 | 82377.8 | 2(Loss) |
| glaze | 1916.39 | 0.424148 | 199.546ms | 264040 | 80 | 2.48482e+07 | 131397 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4196.7 | 0.901736 | 64.0368ms | 399947 | 40 | 2.68663e+07 | 90885.4 | 1(Win) |
| simdjson (ondemand) | 3878.84 | 0.774955 | 29.7413ms | 399947 | 30 | 1.74211e+07 | 98333.3 | 2(Loss) |
| glaze | 2769.31 | 0.202926 | 42.5684ms | 399947 | 30 | 2.34346e+06 | 137731 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1601.71 | 0.262567 | 117.81ms | 264040 | 40 | 6.81574e+06 | 157212 | 1(Win) |
| glaze | 1389.45 | 0.36599 | 55.9735ms | 264040 | 30 | 1.31982e+07 | 181229 | 2(Loss) |
| simdjson (ondemand) | 1365.12 | 0.606211 | 56.1521ms | 264040 | 30 | 3.75115e+07 | 184458 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4348.39 | 0.934301 | 17.4517ms | 264040 | 30 | 8.78167e+06 | 57908.3 | 1(Win) |
| glaze | 3125.74 | 1.33045 | 23.762ms | 263923 | 30 | 3.44322e+07 | 80523.7 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1899.67 | 0.70293 | 62.6591ms | 399947 | 30 | 5.97578e+07 | 200782 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1883.27 | 1.03439 | 144.047ms | 399947 | 40 | 1.75552e+08 | 202530 | 1(Tie) |
| glaze | 1712.45 | 0.711818 | 66.56ms | 399947 | 30 | 7.54099e+07 | 222733 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6912.56 | 1.64754 | 16.2497ms | 399947 | 30 | 2.47926e+07 | 55177.7 | 1(Win) |
| glaze | 3521.03 | 0.820451 | 32.6068ms | 399830 | 30 | 2.36831e+07 | 108294 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1429.17 | 0.593039 | 93.2276ms | 466906 | 30 | 1.02419e+08 | 311564 | 1(Win) |
| glaze | 1362.12 | 1.47594 | 2039.63ms | 466906 | 320 | 7.44935e+09 | 326900 | 2(Loss) |
| simdjson (ondemand) | 752.03 | 0.282878 | 931.97ms | 466906 | 80 | 2.24427e+08 | 592099 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2781.03 | 0.209473 | 172.171ms | 699405 | 40 | 1.00963e+07 | 239841 | 1(Win) |
| glaze | 2003.3 | 0.811308 | 99.8811ms | 699405 | 30 | 2.18906e+08 | 332953 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2381.89 | 0.898361 | 76.5563ms | 631514 | 30 | 1.5479e+08 | 252849 | 1(Win) |
| glaze | 1710.94 | 0.458844 | 109.088ms | 631514 | 30 | 7.82618e+07 | 352005 | 2(Loss) |
