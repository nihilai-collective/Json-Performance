# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36257.0 compiler).  

Latest Results: (Sep 26, 2026)
#### Using the following commits:
----
| Jsonifier: [b01e9de](https://github.com/nihilai-collective/jsonifier/commit/b01e9de)  
| Glaze: [2d38174](https://github.com/stephenberry/glaze/commit/2d38174)  
| Simdjson: [645e5c8](https://github.com/simdjson/simdjson/commit/645e5c8)  

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

> Adaptive sampling on (AMD EPYC 9V45 96-Core Processor-AVX512): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 5.000000% AND mean shift < 2.500000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [49d7727](https://github.com/nihilai-collective/benchmarksuite/commit/49d7727).
  
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1881.47 | 0.1437 | 221.565ms | 1439562 | 30 | 3.29837e+07 | 729680 | 1.31582 | 1(Win) |
| glaze | 1677.8 | 0.255837 | 573.893ms | 1439562 | 40 | 1.75294e+08 | 818258 | 1.47556 | 2(Loss) |
| simdjson (ondemand) | 1159.68 | 0.112919 | 843.518ms | 1439562 | 40 | 7.14787e+07 | 1.18384e+06 | 2.13488 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1585.03 | 0.682072 | 17.3523ms | 94370 | 30 | 4.49959e+06 | 56780 | 1.56103 | 1(Win) |
| jsonifier | 1236.35 | 0.725964 | 22.4269ms | 94370 | 30 | 8.37789e+06 | 72793.3 | 2.00204 | 2(Loss) |
| simdjson (ondemand) | 835.018 | 0.504167 | 32.6554ms | 94370 | 30 | 8.85821e+06 | 107780 | 2.96401 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1447.19 | 2.08451 | 6.2582ms | 31235 | 30 | 5.52282e+06 | 20583.3 | 1.7085 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1427.08 | 1.79181 | 6.4679ms | 31235 | 30 | 4.19651e+06 | 20873.3 | 1.73422 | 1(Tie) |
| simdjson (ondemand) | 1042.91 | 1.15444 | 20.0024ms | 31235 | 40 | 4.34907e+06 | 28562.5 | 2.37154 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1736.95 | 0.444449 | 35.6283ms | 213963 | 30 | 8.1784e+06 | 117477 | 1.42495 | 1(Win) |
| jsonifier | 1667.54 | 0.557719 | 37.445ms | 213963 | 30 | 1.39726e+07 | 122367 | 1.48449 | 2(Loss) |
| simdjson (ondemand) | 975.263 | 0.337215 | 62.9584ms | 213963 | 30 | 1.49337e+07 | 209227 | 2.53833 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1379.92 | 0.466312 | 4775.1ms | 9930848 | 40 | 4.0971e+10 | 6.86328e+06 | 1.79419 | 1(Win) |
| simdjson (ondemand) | 1066.29 | 0.348697 | 13630.5ms | 9930848 | 80 | 7.67372e+10 | 8.88197e+06 | 2.32188 | 2(Loss) |
| glaze | 1013.73 | 0.485161 | 2841.07ms | 9930848 | 30 | 6.16342e+10 | 9.34252e+06 | 2.4423 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1025.69 | 0.23426 | 343.913ms | 1225964 | 30 | 2.13917e+08 | 1.13989e+06 | 2.41373 | 1(Win) |
| jsonifier | 962.847 | 0.18119 | 836.259ms | 1225964 | 40 | 1.93628e+08 | 1.21428e+06 | 2.57126 | 2(Loss) |
| glaze | 883.524 | 0.233732 | 394.967ms | 1225964 | 30 | 2.86996e+08 | 1.3233e+06 | 2.80208 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1072.6 | 0.287462 | 210.653ms | 785750 | 30 | 1.20997e+08 | 698627 | 2.30811 | 1(Win) |
| glaze | 888.195 | 1.32313 | 250.135ms | 785750 | 30 | 3.73833e+09 | 843677 | 2.78731 | 2(Loss) |
| simdjson (ondemand) | 831.222 | 0.239518 | 271.332ms | 785750 | 30 | 1.39872e+08 | 901503 | 2.97838 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6194.55 | 3.28008 | 18.4128ms | 399947 | 30 | 1.2237e+08 | 61573.3 | 0.39948 | 1(Win) |
| glaze STATISTICAL TIE | 3324.01 | 0.541278 | 34.8566ms | 399947 | 30 | 1.15729e+07 | 114747 | 0.744684 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3285.83 | 0.734111 | 34.9124ms | 399947 | 30 | 2.17851e+07 | 116080 | 0.753289 | 2(Tie) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1496.02 | 0.455973 | 77.6353ms | 399947 | 30 | 4.05446e+07 | 254957 | 1.6547 | 1(Win) |
| glaze | 1450.61 | 0.4489 | 80.4495ms | 399947 | 30 | 4.17948e+07 | 262937 | 1.70641 | 2(Loss) |
| simdjson (ondemand) | 943.515 | 0.301225 | 122.693ms | 399947 | 30 | 4.44846e+07 | 404253 | 2.62367 | 3(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2961.2 | 0.667933 | 45.2852ms | 466906 | 30 | 3.02629e+07 | 150370 | 0.835889 | 1(Win) |
| glaze | 1928.17 | 0.315322 | 161.983ms | 466906 | 40 | 2.12099e+07 | 230932 | 1.28381 | 2(Loss) |
| simdjson (ondemand) | 1123.55 | 0.345692 | 122.829ms | 466906 | 30 | 5.63088e+07 | 396313 | 2.20324 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4761.34 | 0.81795 | 97.4415ms | 699405 | 40 | 5.25186e+07 | 140088 | 0.519755 | 1(Win) |
| glaze | 2336.76 | 0.409916 | 86.8111ms | 699405 | 30 | 4.10714e+07 | 285440 | 1.05936 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2705.28 | 0.353591 | 67.1818ms | 631514 | 30 | 1.85894e+07 | 222623 | 0.915108 | 1(Win) |
| jsonifier | 1598.37 | 0.250129 | 113.486ms | 631514 | 30 | 2.66479e+07 | 376797 | 1.54882 | 2(Loss) |
