# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36256.0 compiler).  

Latest Results: (Sep 14, 2026)
#### Using the following commits:
----
| Jsonifier: [fde86fb](https://github.com/nihilai-collective/jsonifier/commit/fde86fb)  
| Glaze: [b91062d](https://github.com/stephenberry/glaze/commit/b91062d)  
| Simdjson: [f9c973a](https://github.com/simdjson/simdjson/commit/f9c973a)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX2` |
| simdjson (ondemand) | `haswell` |
| Glaze (utf8-validation) | `AVX2` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (AMD EPYC 7763 64-Core Processor-AVX2): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.500000% AND mean shift < 1.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [43ba991](https://github.com/realtimechris/benchmarksuite/commit/43ba991).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 423.656 | 0.22572 | 2.8931ms | 1811 | 30 | 2540.23 | 4076.67 | 5.45516 | 1(Win) |
| glaze | 163.259 | 0.0723785 | 31.7877ms | 1811 | 128 | 7504.31 | 10578.9 | 14.214 | 2(Loss) |
| simdjson (ondemand) | 93.1524 | 1.61837 | 26.1636ms | 1811 | 64 | 5.76213e+06 | 18540.6 | 24.9748 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 304.797 | 2.2747 | 34.0735ms | 1811 | 256 | 4.25306e+06 | 5666.41 | 7.60266 | 1(Win) |
| glaze | 167.903 | 2.40986 | 30.2276ms | 1798 | 128 | 7.75276e+06 | 10212.5 | 13.8436 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1026.95 | 0.162358 | 2.7664ms | 3873 | 30 | 1022.99 | 3596.67 | 2.2402 | 1(Win) |
| glaze | 621.096 | 0.112158 | 10.7413ms | 3873 | 64 | 2847.22 | 5946.88 | 3.72652 | 2(Loss) |
| simdjson (ondemand) | 217.389 | 1.85959 | 46.9372ms | 3873 | 128 | 1.2778e+07 | 16990.6 | 10.7065 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1663.78 | 0.334586 | 2.077ms | 3873 | 30 | 1655.17 | 2220 | 1.37903 | 1(Win) |
| glaze | 718.945 | 0.169248 | 5.5328ms | 3873 | 32 | 2419.35 | 5137.5 | 3.23605 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1130.94 | 0.350981 | 2.6593ms | 3862 | 30 | 3919.54 | 3256.67 | 2.04275 | 1(Win) |
| glaze | 479.272 | 1.19511 | 85.7912ms | 3862 | 512 | 4.31867e+06 | 7684.77 | 4.83887 | 2(Loss) |
| simdjson (ondemand) | 218.045 | 1.74838 | 46.5076ms | 3862 | 128 | 1.11638e+07 | 16891.4 | 10.6719 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1326.44 | 1.47214 | 2.2044ms | 3862 | 30 | 50126.4 | 2776.67 | 1.73062 | 1(Win) |
| glaze | 705.123 | 0.54059 | 2.932ms | 3862 | 30 | 23919.5 | 5223.33 | 3.28697 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 766.043 | 0.728854 | 2.2972ms | 905 | 30 | 2022.99 | 1126.67 | 2.91746 | 1(Win) |
| glaze | 129.591 | 0.136594 | 3.2088ms | 905 | 30 | 2482.76 | 6660 | 17.8215 | 2(Loss) |
| simdjson (ondemand) | 63.1134 | 2.46697 | 10.086ms | 905 | 32 | 3.64194e+06 | 13675 | 36.8624 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 379.896 | 0.355443 | 3.6897ms | 905 | 32 | 2086.69 | 2271.88 | 6.03785 | 1(Win) |
| glaze | 118.027 | 0.133826 | 6.5816ms | 905 | 32 | 3064.52 | 7312.5 | 19.5998 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1094.59 | 1.79236 | 47.3837ms | 9578 | 256 | 5.72711e+06 | 8344.92 | 2.1206 | 1(Win) |
| glaze | 840.75 | 1.90658 | 60.6177ms | 9578 | 256 | 1.09842e+07 | 10864.5 | 2.7469 | 2(Loss) |
| simdjson (ondemand) | 367.6 | 2.35851 | 32.9726ms | 9578 | 64 | 2.19813e+07 | 24848.4 | 6.33339 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2462.49 | 0.141133 | 4.2753ms | 9578 | 32 | 877.016 | 3709.38 | 0.936923 | 1(Win) |
| glaze | 1565.6 | 0.127859 | 10.6235ms | 9578 | 64 | 3561.51 | 5834.38 | 1.47869 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2152.14 | 2.34006 | 26.3404ms | 233995 | 30 | 1.76624e+08 | 103690 | 1.08265 | 1(Win) |
| simdjson (ondemand) | 1382.99 | 1.66651 | 41.0027ms | 233995 | 30 | 2.16926e+08 | 161357 | 1.68508 | 2(Loss) |
| glaze | 953.287 | 0.853135 | 58.449ms | 233995 | 30 | 1.19653e+08 | 234090 | 2.44532 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2903.93 | 1.88848 | 30.0926ms | 346753 | 30 | 1.38745e+08 | 113877 | 0.802547 | 1(Win) |
| simdjson (ondemand) | 1832.35 | 1.34914 | 45.6203ms | 346753 | 30 | 1.77852e+08 | 180473 | 1.2721 | 2(Loss) |
| glaze | 1233.15 | 0.958138 | 67.1652ms | 346753 | 30 | 1.98055e+08 | 268167 | 1.89043 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 716.81 | 0.91358 | 77.6813ms | 233995 | 30 | 2.42672e+08 | 311317 | 3.25212 | 1(Win) |
| glaze | 634.095 | 1.72561 | 98.7971ms | 233995 | 30 | 1.1064e+09 | 351927 | 3.67642 | 2(Loss) |
| simdjson (ondemand) | 419.722 | 0.696836 | 129.768ms | 233995 | 30 | 4.11787e+08 | 531673 | 5.55457 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1232.6 | 2.03486 | 220.213ms | 233995 | 64 | 8.68595e+08 | 181044 | 1.89077 | 1(Win) |
| glaze | 1008.3 | 1.73807 | 1214.52ms | 233995 | 256 | 3.78794e+09 | 221317 | 2.31092 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 847.567 | 0.933213 | 94.0838ms | 346753 | 30 | 3.97718e+08 | 390163 | 2.75028 | 1(Tie) |
| glaze STATISTICAL TIE | 846.605 | 0.721524 | 108.17ms | 346753 | 30 | 2.38288e+08 | 390607 | 2.74924 | 1(Tie) |
| simdjson (ondemand) | 616.954 | 0.375488 | 130.896ms | 346753 | 30 | 1.2152e+08 | 536003 | 3.779 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1836.52 | 0.661126 | 46.0288ms | 346753 | 30 | 4.25148e+07 | 180063 | 1.26929 | 1(Win) |
| glaze | 1082.55 | 1.62016 | 1650.83ms | 346753 | 256 | 6.27043e+09 | 305472 | 2.15364 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2259.49 | 1.37427 | 25.458ms | 233995 | 30 | 5.52659e+07 | 98763.3 | 1.03138 | 1(Win) |
| glaze | 1036.56 | 0.752703 | 56.3861ms | 233995 | 30 | 7.87752e+07 | 215283 | 2.24926 | 2(Loss) |
| simdjson (ondemand) | 563.96 | 0.687465 | 79.1983ms | 233995 | 30 | 2.21993e+08 | 395693 | 4.13402 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2906.2 | 2.13749 | 79.5062ms | 346753 | 32 | 1.89299e+08 | 113788 | 0.801933 | 1(Win) |
| glaze | 1348.96 | 1.0008 | 60.5701ms | 346753 | 30 | 1.80574e+08 | 245143 | 1.72814 | 2(Loss) |
| simdjson (ondemand) | 1312.31 | 0.883785 | 62.2722ms | 346753 | 30 | 1.48793e+08 | 251990 | 1.77668 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 776.534 | 0.564914 | 72.0872ms | 233995 | 30 | 7.90641e+07 | 287373 | 3.00219 | 1(Win) |
| glaze | 738.924 | 0.681689 | 74.5314ms | 233995 | 30 | 1.27148e+08 | 302000 | 3.15505 | 2(Loss) |
| simdjson (ondemand) | 108.065 | 0.150039 | 524.211ms | 233995 | 30 | 2.87986e+08 | 2.06501e+06 | 21.5791 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1524.49 | 0.737762 | 37.3398ms | 233995 | 30 | 3.49879e+07 | 146380 | 1.52914 | 1(Win) |
| glaze | 1109.3 | 2.01016 | 499.209ms | 233995 | 128 | 2.09308e+09 | 201167 | 2.10128 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 951.643 | 0.791798 | 86.7493ms | 346753 | 30 | 2.27114e+08 | 347493 | 2.44984 | 1(Win) |
| glaze | 911.76 | 0.609211 | 88.7441ms | 346753 | 30 | 1.46465e+08 | 362693 | 2.55708 | 2(Loss) |
| simdjson (ondemand) | 156.67 | 0.172719 | 516.731ms | 346753 | 30 | 3.98721e+08 | 2.11074e+06 | 14.8843 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1892.32 | 2.2286 | 100.689ms | 346753 | 32 | 4.85361e+08 | 174753 | 1.23176 | 1(Win) |
| glaze | 1070.84 | 1.96955 | 778.49ms | 346753 | 128 | 4.73522e+09 | 308814 | 2.17707 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 432.724 | 2.20277 | 53.4291ms | 94651 | 30 | 6.33417e+08 | 208600 | 5.38604 | 1(Win) |
| glaze | 354.408 | 2.46815 | 611.333ms | 94651 | 128 | 5.05822e+09 | 254696 | 6.57612 | 2(Loss) |
| simdjson (ondemand) | 307.195 | 2.42686 | 349.462ms | 94651 | 64 | 3.25456e+09 | 293841 | 7.58952 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1706.68 | 0.318881 | 14.9553ms | 94651 | 30 | 853345 | 52890 | 1.36495 | 1(Win) |
| jsonifier | 1503.69 | 1.40677 | 16.3358ms | 94651 | 30 | 2.13946e+07 | 60030 | 1.54982 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 547.908 | 1.40186 | 59.6144ms | 136024 | 30 | 3.3048e+08 | 236760 | 4.25471 | 1(Tie) |
| glaze STATISTICAL TIE | 526.021 | 2.08532 | 302.753ms | 136024 | 64 | 1.69258e+09 | 246611 | 4.43157 | 1(Tie) |
| simdjson (ondemand) | 474.919 | 2.02153 | 67.6175ms | 136024 | 30 | 9.14693e+08 | 273147 | 4.90855 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1874.06 | 1.35195 | 18.5202ms | 136024 | 30 | 2.62727e+07 | 69220 | 1.24343 | 1(Win) |
| glaze | 1271.04 | 0.866109 | 26.6174ms | 136046 | 30 | 2.34487e+07 | 102077 | 1.83379 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 319.439 | 1.13278 | 1544.87ms | 2090234 | 30 | 1.4991e+11 | 6.24033e+06 | 7.29963 | 1(Win) |
| glaze | 207.164 | 0.972996 | 2323.36ms | 2090234 | 30 | 2.6297e+11 | 9.62236e+06 | 11.2564 | 2(Loss) |
| simdjson (ondemand) | 193.885 | 0.918586 | 2444.84ms | 2090234 | 30 | 2.67585e+11 | 1.02814e+07 | 12.0267 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 512.421 | 0.651585 | 913.822ms | 2090234 | 30 | 1.92752e+10 | 3.89016e+06 | 4.55049 | 1(Win) |
| glaze | 442.251 | 0.27274 | 1104.2ms | 2090234 | 30 | 4.53389e+09 | 4.5074e+06 | 5.2726 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 818.485 | 1.20495 | 1850.03ms | 6661897 | 30 | 2.62442e+11 | 7.76224e+06 | 2.84883 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 555.777 | 1.18788 | 2771.46ms | 6661897 | 30 | 5.53176e+11 | 1.14314e+07 | 4.19558 | 2(Tie) |
| glaze STATISTICAL TIE | 553.002 | 0.666866 | 2774.84ms | 6661897 | 30 | 1.76092e+11 | 1.14887e+07 | 4.21662 | 2(Tie) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1105.86 | 0.956019 | 1435.13ms | 6661897 | 30 | 9.05002e+10 | 5.7451e+06 | 2.10837 | 1(Win) |
| glaze | 644.194 | 0.987848 | 2369.83ms | 6661897 | 30 | 2.8475e+11 | 9.86238e+06 | 3.61955 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 711.302 | 1.84145 | 187.63ms | 500299 | 30 | 4.57712e+09 | 670773 | 3.27778 | 1(Win) |
| glaze | 448.499 | 0.858857 | 258.829ms | 500299 | 30 | 2.50438e+09 | 1.06382e+06 | 5.19902 | 2(Loss) |
| simdjson (ondemand) | 264.303 | 0.443137 | 440.795ms | 500299 | 30 | 1.91979e+09 | 1.80521e+06 | 8.82256 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1705.9 | 0.766966 | 71.561ms | 500299 | 30 | 1.38047e+08 | 279690 | 1.3667 | 1(Win) |
| glaze | 1305.56 | 0.746608 | 90.4216ms | 500299 | 30 | 2.23342e+08 | 365453 | 1.7859 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1339.73 | 0.734059 | 263.074ms | 1439562 | 30 | 1.69749e+09 | 1.02474e+06 | 1.74044 | 1(Win) |
| glaze | 997.43 | 0.271702 | 345.614ms | 1439562 | 30 | 4.19569e+08 | 1.37641e+06 | 2.33782 | 2(Loss) |
| simdjson (ondemand) | 681.271 | 1.53277 | 472.956ms | 1439562 | 30 | 2.86219e+10 | 2.01516e+06 | 3.42259 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1913.51 | 0.556159 | 176.232ms | 1439562 | 30 | 4.7766e+08 | 717463 | 1.21836 | 1(Win) |
| glaze | 826.351 | 0.598167 | 398.26ms | 1439584 | 30 | 2.96286e+09 | 1.66139e+06 | 2.82113 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 652.325 | 1.06724 | 105.442ms | 56369 | 64 | 4.95059e+07 | 82409.4 | 3.57139 | 1(Win) |
| glaze | 595.257 | 2.00208 | 23.3076ms | 56369 | 30 | 9.8074e+07 | 90310 | 3.91333 | 2(Loss) |
| simdjson (ondemand) | 277.192 | 0.862458 | 48.5824ms | 56369 | 30 | 8.393e+07 | 193937 | 8.40878 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1397.88 | 1.77884 | 10.7353ms | 56369 | 30 | 1.40391e+07 | 38456.7 | 1.66644 | 1(Win) |
| glaze | 1240.47 | 1.49374 | 12.0105ms | 56369 | 30 | 1.25714e+07 | 43336.7 | 1.87751 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 887.323 | 1.93501 | 26.1873ms | 94370 | 30 | 1.15556e+08 | 101427 | 2.62609 | 1(Win) |
| jsonifier | 704.69 | 2.07366 | 33.129ms | 94370 | 30 | 2.10411e+08 | 127713 | 3.30654 | 2(Loss) |
| simdjson (ondemand) | 448.109 | 1.16367 | 49.9534ms | 94370 | 30 | 1.63862e+08 | 200840 | 5.20225 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2276.13 | 1.58469 | 11.608ms | 94370 | 30 | 1.17783e+07 | 39540 | 1.02331 | 1(Win) |
| glaze | 1154.56 | 0.867273 | 20.6256ms | 94370 | 30 | 1.37109e+07 | 77950 | 2.01791 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 574.338 | 2.20984 | 107.619ms | 52708 | 64 | 2.39398e+08 | 87520.3 | 4.05444 | 1(Win) |
| glaze | 497.39 | 1.41602 | 26.7619ms | 52708 | 30 | 6.14356e+07 | 101060 | 4.68359 | 2(Loss) |
| simdjson (ondemand) | 408.425 | 1.74332 | 31.207ms | 52708 | 30 | 1.38103e+08 | 123073 | 5.70577 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2341.6 | 0.324694 | 6.8423ms | 52708 | 30 | 145747 | 21466.7 | 0.993952 | 1(Win) |
| glaze | 1885.46 | 1.53844 | 8.0952ms | 52708 | 30 | 5.04662e+06 | 26660 | 1.23492 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 597.421 | 1.75752 | 28.9375ms | 70103 | 30 | 1.16048e+08 | 111907 | 3.89942 | 1(Win) |
| simdjson (ondemand) | 538.737 | 1.68814 | 31.4513ms | 70103 | 30 | 1.31662e+08 | 124097 | 4.32497 | 2(Loss) |
| jsonifier | 512.449 | 1.69217 | 165.365ms | 70103 | 64 | 3.11916e+08 | 130462 | 4.545 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2839.68 | 0.557976 | 7.2827ms | 70103 | 30 | 517713 | 23543.3 | 0.819579 | 1(Win) |
| glaze | 1691.74 | 0.958489 | 26.402ms | 70103 | 32 | 4.59125e+06 | 39518.8 | 1.37679 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 381.255 | 2.36828 | 8.6897ms | 11812 | 30 | 1.46895e+07 | 29546.7 | 6.10696 | 1(Win) |
| jsonifier | 330.165 | 1.29252 | 35.5729ms | 11812 | 64 | 1.24463e+07 | 34118.8 | 7.05234 | 2(Loss) |
| simdjson (ondemand) | 245.521 | 1.9781 | 27.8708ms | 11812 | 32 | 2.63583e+07 | 45881.2 | 9.48949 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1126.1 | 0.539048 | 3.8895ms | 11812 | 30 | 87229.9 | 10003.3 | 2.06365 | 1(Win) |
| glaze | 966.158 | 1.73976 | 8.7187ms | 11812 | 32 | 1.31668e+06 | 11659.4 | 2.40656 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 970.399 | 1.99241 | 9.3289ms | 31235 | 30 | 1.12217e+07 | 30696.7 | 2.39974 | 1(Win) |
| glaze | 799.075 | 0.077813 | 23.8873ms | 31235 | 32 | 26925.4 | 37278.1 | 2.91565 | 2(Loss) |
| simdjson (ondemand) | 630.879 | 0.0773902 | 13.0979ms | 31235 | 30 | 40057.5 | 47216.7 | 3.69326 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2510.93 | 0.12446 | 4.3517ms | 31235 | 30 | 6540.23 | 11863.3 | 0.925354 | 1(Win) |
| glaze | 1400.55 | 2.4403 | 13.9675ms | 31235 | 32 | 8.62028e+06 | 21268.8 | 1.66045 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1204.98 | 1.54039 | 23.4177ms | 108313 | 30 | 5.23094e+07 | 85723.3 | 1.93453 | 1(Win) |
| glaze | 553.813 | 0.900734 | 47.4855ms | 108313 | 30 | 8.46739e+07 | 186517 | 4.20871 | 2(Loss) |
| simdjson (ondemand) | 329.554 | 0.862883 | 76.9547ms | 108313 | 30 | 2.19449e+08 | 313440 | 7.07446 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1640.13 | 2.01429 | 16.7213ms | 108313 | 30 | 4.82803e+07 | 62980 | 1.41999 | 1(Win) |
| glaze | 1304.07 | 1.083 | 20.9294ms | 108313 | 30 | 2.20768e+07 | 79210 | 1.78714 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1029.4 | 1.14476 | 50.7158ms | 213963 | 30 | 1.54474e+08 | 198223 | 2.26423 | 1(Win) |
| glaze | 859.886 | 1.37632 | 58.8689ms | 213963 | 30 | 3.20003e+08 | 237300 | 2.7108 | 2(Loss) |
| simdjson (ondemand) | 615.217 | 1.02986 | 81.0836ms | 213963 | 30 | 3.50023e+08 | 331673 | 3.78941 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2867.76 | 1.79649 | 18.5865ms | 213963 | 30 | 4.90184e+07 | 71153.3 | 0.812639 | 1(Win) |
| glaze | 1264.83 | 1.10326 | 40.8445ms | 213963 | 30 | 9.50358e+07 | 161327 | 1.84296 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 323.675 | 0.826742 | 1283.69ms | 1834197 | 30 | 5.98875e+10 | 5.40428e+06 | 7.20358 | 1(Win) |
| glaze | 174.69 | 0.981109 | 2391.78ms | 1834197 | 30 | 2.89541e+11 | 1.00133e+07 | 13.3477 | 2(Loss) |
| simdjson (ondemand) | 165.673 | 0.739387 | 2569.71ms | 1834197 | 30 | 1.82832e+11 | 1.05583e+07 | 14.0743 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 326.644 | 0.269921 | 1305.69ms | 1834197 | 30 | 6.26812e+09 | 5.35515e+06 | 7.13865 | 1(Win) |
| glaze | 262.161 | 0.327726 | 1625.43ms | 1833577 | 30 | 1.43352e+10 | 6.67008e+06 | 8.89453 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1229.24 | 0.551284 | 1896.29ms | 9930848 | 30 | 5.4122e+10 | 7.70462e+06 | 1.89684 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 779.009 | 0.860098 | 2929.7ms | 9930848 | 30 | 3.28023e+11 | 1.21575e+07 | 2.99331 | 2(Tie) |
| glaze STATISTICAL TIE | 776.734 | 0.597617 | 2956.96ms | 9930848 | 30 | 1.59293e+11 | 1.21931e+07 | 3.00201 | 2(Tie) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1047.76 | 1.77357 | 5269.82ms | 9930848 | 32 | 8.22421e+11 | 9.03906e+06 | 2.22542 | 1(Win) |
| glaze | 585.411 | 0.14109 | 3865.65ms | 9930228 | 30 | 1.56283e+10 | 1.6177e+07 | 3.98329 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 666.208 | 0.437613 | 535.197ms | 642697 | 32 | 5.18709e+08 | 920019 | 3.50006 | 1(Win) |
| glaze | 429.164 | 0.203573 | 346.543ms | 642697 | 30 | 2.53588e+08 | 1.42818e+06 | 5.43334 | 2(Loss) |
| simdjson (ondemand) | 414.39 | 0.987372 | 354.75ms | 642697 | 30 | 6.39849e+09 | 1.4791e+06 | 5.62681 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 627.259 | 0.380674 | 241.776ms | 642697 | 30 | 4.15094e+08 | 977147 | 3.71757 | 1(Win) |
| glaze | 384.439 | 0.245271 | 384.905ms | 642692 | 30 | 4.58738e+08 | 1.59432e+06 | 6.06456 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 970.368 | 0.251943 | 316.326ms | 1225964 | 30 | 2.76444e+08 | 1.20487e+06 | 2.40314 | 1(Win) |
| simdjson (ondemand) | 761.698 | 0.16921 | 372.487ms | 1225964 | 30 | 2.02378e+08 | 1.53495e+06 | 3.06151 | 2(Loss) |
| glaze | 737.462 | 0.162875 | 383.416ms | 1225964 | 30 | 2.00036e+08 | 1.5854e+06 | 3.16207 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 891.079 | 0.332791 | 315.748ms | 1225964 | 30 | 5.71987e+08 | 1.31208e+06 | 2.61655 | 1(Win) |
| glaze | 673.649 | 0.248792 | 419.449ms | 1225970 | 30 | 5.59356e+08 | 1.73559e+06 | 3.46121 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 457.241 | 0.477298 | 208.229ms | 409725 | 30 | 4.9911e+08 | 854570 | 5.09965 | 1(Win) |
| glaze | 300.881 | 0.325417 | 313.601ms | 409725 | 30 | 5.35794e+08 | 1.29867e+06 | 7.7498 | 2(Loss) |
| simdjson (ondemand) | 262.619 | 0.348732 | 365.947ms | 409725 | 30 | 8.07678e+08 | 1.48788e+06 | 8.87914 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1041.97 | 0.804404 | 94.2929ms | 409725 | 30 | 2.7299e+08 | 375007 | 2.23767 | 1(Win) |
| glaze | 987.185 | 0.78043 | 100.725ms | 409725 | 30 | 2.86271e+08 | 395817 | 2.36186 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 594.272 | 0.347677 | 312.395ms | 785750 | 30 | 5.76596e+08 | 1.26095e+06 | 3.92389 | 1(Win) |
| glaze | 515.828 | 0.225155 | 353.091ms | 785750 | 30 | 3.20956e+08 | 1.45271e+06 | 4.5206 | 2(Loss) |
| simdjson (ondemand) | 488.005 | 0.210578 | 371.48ms | 785750 | 30 | 3.13667e+08 | 1.53554e+06 | 4.77835 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1634.35 | 0.406133 | 115.214ms | 785750 | 30 | 1.04025e+08 | 458500 | 1.42668 | 1(Win) |
| glaze | 808.334 | 0.487636 | 228.177ms | 785750 | 30 | 6.13057e+08 | 927030 | 2.88433 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 377.08 | 1.53986 | 5254.67ms | 8587914 | 30 | 3.35574e+12 | 2.17197e+07 | 6.18409 | 1(Win) |
| simdjson (ondemand) | 308.653 | 0.481017 | 6580.55ms | 8587914 | 30 | 4.88739e+11 | 2.65349e+07 | 7.55512 | 2(Loss) |
| glaze | 291.693 | 1.02119 | 6671.31ms | 8587914 | 30 | 2.46635e+12 | 2.80777e+07 | 7.99448 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 863.541 | 1.07473 | 2209.61ms | 8588126 | 30 | 3.1171e+11 | 9.48452e+06 | 2.69999 | 1(Win) |
| glaze | 618.893 | 0.35323 | 3161.45ms | 8588126 | 30 | 6.55547e+10 | 1.32338e+07 | 3.76766 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 403.861 | 0.537583 | 5569.16ms | 9804437 | 30 | 4.64723e+11 | 2.31521e+07 | 5.77398 | 1(Win) |
| simdjson (ondemand) | 353.335 | 0.608871 | 6385.48ms | 9804437 | 30 | 7.78832e+11 | 2.64628e+07 | 6.59977 | 2(Loss) |
| glaze | 317.004 | 1.78642 | 6794.7ms | 9804437 | 30 | 8.32917e+12 | 2.94956e+07 | 7.35618 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1056.16 | 0.368403 | 5912.78ms | 11078090 | 32 | 4.3458e+10 | 1.00031e+07 | 2.20773 | 1(Win) |
| glaze | 654.395 | 0.221005 | 3867.21ms | 11078090 | 30 | 3.81924e+10 | 1.61445e+07 | 3.56337 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2081.35 | 0.771301 | 31.2823ms | 264040 | 30 | 2.61228e+07 | 120983 | 1.11961 | 1(Win) |
| simdjson (ondemand) | 1371.53 | 1.05572 | 45.4692ms | 264040 | 30 | 1.12706e+08 | 183597 | 1.69942 | 2(Loss) |
| glaze | 746.725 | 0.707748 | 83.6444ms | 264040 | 30 | 1.70882e+08 | 337217 | 3.12239 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2743.69 | 1.22281 | 35.5282ms | 399947 | 30 | 8.66911e+07 | 139017 | 0.849485 | 1(Win) |
| simdjson (ondemand) | 1831.19 | 0.878945 | 51.8283ms | 399947 | 30 | 1.0055e+08 | 208290 | 1.273 | 2(Loss) |
| glaze | 1033.88 | 0.502765 | 92.2383ms | 399947 | 30 | 1.03209e+08 | 368920 | 2.25509 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 778.62 | 1.50787 | 91.5503ms | 264040 | 30 | 7.13409e+08 | 323403 | 2.99427 | 1(Win) |
| glaze | 487.912 | 0.859052 | 135.631ms | 264040 | 30 | 5.89681e+08 | 516093 | 4.77854 | 2(Loss) |
| simdjson (ondemand) | 413.388 | 0.59696 | 157.069ms | 264040 | 30 | 3.96677e+08 | 609133 | 5.64017 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2078.14 | 1.35925 | 30.3196ms | 264040 | 30 | 8.1378e+07 | 121170 | 1.12168 | 1(Win) |
| glaze | 1535.61 | 1.58922 | 41.5936ms | 263923 | 30 | 2.03557e+08 | 163907 | 1.5179 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 714.799 | 1.45713 | 141.873ms | 399947 | 30 | 1.81367e+09 | 533603 | 3.26126 | 1(Win) |
| simdjson (ondemand) | 596.527 | 0.747245 | 156.425ms | 399947 | 30 | 6.84845e+08 | 639400 | 3.90883 | 2(Loss) |
| glaze | 400.947 | 0.793459 | 157.156ms | 399947 | 30 | 1.70924e+09 | 951297 | 5.81511 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2706.76 | 0.805517 | 40.4452ms | 399947 | 30 | 3.86522e+07 | 140913 | 0.860989 | 1(Win) |
| glaze | 1276.54 | 1.68577 | 70.6704ms | 399830 | 30 | 7.60673e+08 | 298703 | 1.82604 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1111.4 | 0.555464 | 109.731ms | 466906 | 30 | 1.48576e+08 | 400643 | 2.09799 | 1(Win) |
| glaze | 893.125 | 0.501718 | 126.058ms | 466906 | 30 | 1.87705e+08 | 498560 | 2.61067 | 2(Loss) |
| simdjson (ondemand) | 525.625 | 0.328682 | 205.604ms | 466906 | 30 | 2.32584e+08 | 847137 | 4.43629 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1595.11 | 0.8007 | 103.453ms | 699405 | 30 | 3.36309e+08 | 418157 | 1.46178 | 1(Win) |
| glaze | 1102.1 | 1.66686 | 149.564ms | 699405 | 30 | 3.05307e+09 | 605213 | 2.11569 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1492.08 | 0.663626 | 98.8755ms | 631514 | 30 | 2.15253e+08 | 403637 | 1.56275 | 1(Win) |
| jsonifier | 1126.14 | 0.6168 | 301.562ms | 631514 | 32 | 3.48191e+08 | 534797 | 2.07046 | 2(Loss) |
