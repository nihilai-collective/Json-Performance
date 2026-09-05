# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 05, 2026)
#### Using the following commits:
----
| Jsonifier: [5656577](https://github.com/nihilai-collective/jsonifier/commit/5656577)  
| Glaze: [a5f515c](https://github.com/stephenberry/glaze/commit/a5f515c)  
| Simdjson: [a346223](https://github.com/simdjson/simdjson/commit/a346223)  

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
  This is the commit of BenchmarkSuite that was used to generate these results: [c0b7b4a](https://github.com/realtimechris/benchmarksuite/commit/c0b7b4a).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 383.71 | 2.02168 | 1.3734ms | 1811 | 30 | 248414 | 4501.07 | 6.02509 | 1(Win) |
| jsonifier | 321.953 | 0.505173 | 6.04417ms | 1811 | 32 | 23500.8 | 5364.47 | 7.18279 | 2(Loss) |
| simdjson (ondemand) | 139.541 | 0.08546 | 3.30743ms | 1811 | 30 | 3356.45 | 12377 | 16.6634 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 399.66 | 0.0751246 | 1.35908ms | 1811 | 30 | 316.185 | 4321.43 | 5.78782 | 1(Win) |
| glaze | 265.857 | 0.287099 | 1.79974ms | 1798 | 30 | 10286.5 | 6449.73 | 8.72481 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1277.97 | 0.0550804 | 0.990318ms | 3873 | 30 | 76.0276 | 2890.2 | 1.80138 | 1(Win) |
| glaze | 1091.84 | 0.0914069 | 1.09627ms | 3873 | 30 | 286.852 | 3382.9 | 2.11307 | 2(Loss) |
| simdjson (ondemand) | 298.13 | 2.24911 | 3.2318ms | 3873 | 30 | 2.32931e+06 | 12389.2 | 7.79956 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1727.88 | 0.111077 | 0.81927ms | 3873 | 30 | 169.137 | 2137.63 | 1.32634 | 1(Win) |
| glaze | 1005.9 | 0.21031 | 1.16835ms | 3873 | 30 | 1789.06 | 3671.9 | 2.29631 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1302.84 | 0.134901 | 1.023ms | 3862 | 30 | 436.309 | 2826.97 | 1.76697 | 1(Win) |
| glaze | 958.755 | 0.0918416 | 1.1903ms | 3862 | 30 | 373.43 | 3841.53 | 2.4098 | 2(Loss) |
| simdjson (ondemand) | 299.355 | 0.0741655 | 3.24465ms | 3862 | 30 | 2497.9 | 12303.4 | 7.76808 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1632.58 | 0.104009 | 0.83053ms | 3862 | 30 | 165.172 | 2256 | 1.40493 | 1(Win) |
| glaze | 971.587 | 0.388208 | 1.2295ms | 3862 | 30 | 6496.99 | 3790.8 | 2.37727 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 767.587 | 0.215524 | 0.568882ms | 905 | 30 | 176.179 | 1124.4 | 2.94092 | 1(Win) |
| glaze | 465.211 | 0.172083 | 0.71288ms | 905 | 30 | 305.771 | 1855.23 | 4.91179 | 2(Loss) |
| simdjson (ondemand) | 98.621 | 0.0744681 | 11.0918ms | 905 | 64 | 2718.19 | 8751.44 | 23.5508 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 744.801 | 0.129421 | 0.55758ms | 905 | 30 | 67.4759 | 1158.8 | 3.03573 | 1(Win) |
| glaze | 317.65 | 0.164953 | 0.901002ms | 905 | 30 | 602.616 | 2717.07 | 7.24715 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1969.6 | 0.0816514 | 1.46828ms | 9578 | 30 | 430.171 | 4637.63 | 1.17436 | 1(Win) |
| glaze | 1359.09 | 0.0743737 | 1.91179ms | 9578 | 30 | 749.568 | 6720.87 | 1.70633 | 2(Loss) |
| simdjson (ondemand) | 701.257 | 0.254428 | 3.44987ms | 9578 | 30 | 32949.4 | 13025.6 | 3.31646 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3099.14 | 0.213696 | 1.03898ms | 9578 | 30 | 1190.1 | 2947.37 | 0.742911 | 1(Win) |
| glaze | 2237.96 | 0.207395 | 1.27096ms | 9578 | 30 | 2149.64 | 4081.53 | 1.03247 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2545.89 | 0.692704 | 21.4232ms | 233995 | 30 | 1.10599e+07 | 87653.1 | 0.915496 | 1(Win) |
| simdjson (ondemand) | 2471.5 | 0.625213 | 22.1622ms | 233995 | 30 | 9.56026e+06 | 90291.4 | 0.943186 | 2(Loss) |
| glaze | 1274.4 | 0.426219 | 42.4439ms | 233995 | 30 | 1.67105e+07 | 175106 | 1.82961 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3094.25 | 0.922739 | 25.7901ms | 346753 | 30 | 2.91748e+07 | 106872 | 0.753284 | 1(Win) |
| jsonifier | 2766.75 | 0.5375 | 29.0888ms | 346753 | 30 | 1.23816e+07 | 119523 | 0.842482 | 2(Loss) |
| glaze | 1590.03 | 0.417164 | 50.2281ms | 346753 | 30 | 2.25821e+07 | 207977 | 1.4664 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1079.6 | 0.418669 | 50.117ms | 233995 | 30 | 2.24674e+07 | 206703 | 2.15961 | 1(Win) |
| glaze | 989.301 | 0.528292 | 54.1988ms | 233995 | 30 | 4.26015e+07 | 225568 | 2.3568 | 2(Loss) |
| simdjson (ondemand) | 874.012 | 0.680162 | 60.9436ms | 233995 | 30 | 9.04741e+07 | 255322 | 2.66765 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2067.49 | 0.711174 | 26.5407ms | 233995 | 30 | 1.76766e+07 | 107935 | 1.12739 | 1(Win) |
| glaze | 1862.87 | 0.635322 | 29.0885ms | 233995 | 30 | 1.73764e+07 | 119791 | 1.25119 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1229.65 | 0.428835 | 65.3473ms | 346753 | 30 | 3.99006e+07 | 268930 | 1.89613 | 1(Tie) |
| glaze STATISTICAL TIE | 1217.44 | 0.385349 | 65.556ms | 346753 | 30 | 3.28684e+07 | 271628 | 1.91529 | 1(Tie) |
| jsonifier | 940.568 | 0.360887 | 84.853ms | 346753 | 30 | 4.82974e+07 | 351585 | 2.47905 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1691.32 | 0.812982 | 46.7937ms | 346753 | 30 | 7.58004e+07 | 195521 | 1.37839 | 1(Win) |
| jsonifier | 1317.99 | 0.540871 | 60.2964ms | 346753 | 30 | 5.5249e+07 | 250904 | 1.76899 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2492.51 | 0.88002 | 21.7329ms | 233995 | 30 | 1.86228e+07 | 89530.1 | 0.935118 | 1(Win) |
| simdjson (ondemand) | 1686.58 | 0.511874 | 32.1559ms | 233995 | 30 | 1.37609e+07 | 132312 | 1.38229 | 2(Loss) |
| glaze | 1277.33 | 0.424871 | 42.2296ms | 233995 | 30 | 1.65288e+07 | 174704 | 1.82535 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2726.35 | 0.593704 | 29.3508ms | 346753 | 30 | 1.55575e+07 | 121294 | 0.854898 | 1(Win) |
| simdjson (ondemand) | 2205.77 | 1.21431 | 36.2276ms | 346753 | 30 | 9.94266e+07 | 149920 | 1.05675 | 2(Loss) |
| glaze | 1582.89 | 0.487901 | 50.5513ms | 346753 | 30 | 3.1169e+07 | 208915 | 1.4729 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1027.35 | 0.378017 | 53.0275ms | 233995 | 30 | 2.02265e+07 | 217214 | 2.26955 | 1(Win) |
| jsonifier | 901.295 | 0.596709 | 59.4531ms | 233995 | 30 | 6.54825e+07 | 247594 | 2.58698 | 2(Loss) |
| simdjson (ondemand) | 187.453 | 0.319106 | 286.787ms | 233995 | 30 | 4.32932e+08 | 1.19046e+06 | 12.4405 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2264.4 | 0.713559 | 24.1587ms | 233995 | 30 | 1.48351e+07 | 98549.5 | 1.02929 | 1(Win) |
| glaze | 1879.87 | 0.832614 | 28.8396ms | 233995 | 30 | 2.93067e+07 | 118708 | 1.23997 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1215.45 | 0.396389 | 65.8456ms | 346753 | 30 | 3.48927e+07 | 272073 | 1.91834 | 1(Win) |
| jsonifier | 864.943 | 0.242889 | 92.4042ms | 346753 | 30 | 2.58704e+07 | 382325 | 2.6958 | 2(Loss) |
| simdjson (ondemand) | 271.047 | 0.32828 | 292.913ms | 346753 | 30 | 4.81241e+08 | 1.22005e+06 | 8.60364 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1666.98 | 0.505445 | 48.0903ms | 346753 | 30 | 3.01613e+07 | 198377 | 1.39858 | 1(Win) |
| jsonifier | 1449.05 | 0.405736 | 55.7453ms | 346753 | 30 | 2.57207e+07 | 228211 | 1.609 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 669.391 | 0.537406 | 32.9119ms | 94651 | 30 | 1.5755e+07 | 134848 | 3.48276 | 1(Win) |
| glaze | 643.172 | 0.466586 | 34.7918ms | 94651 | 30 | 1.28641e+07 | 140345 | 3.62474 | 2(Loss) |
| jsonifier | 599.237 | 0.526736 | 36.5175ms | 94651 | 30 | 1.88869e+07 | 150635 | 3.89069 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2844.08 | 0.0894604 | 8.0027ms | 94651 | 30 | 24185.2 | 31738.2 | 0.818876 | 1(Win) |
| glaze | 2634.23 | 1.55547 | 8.49199ms | 94651 | 30 | 8.52286e+06 | 34266.7 | 0.88389 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 925.251 | 0.675479 | 33.9954ms | 136024 | 30 | 2.69065e+07 | 140203 | 2.51969 | 1(Win) |
| glaze | 814.162 | 0.505815 | 38.8403ms | 136024 | 30 | 1.94857e+07 | 159333 | 2.86348 | 2(Loss) |
| jsonifier | 665.1 | 0.399132 | 47.1292ms | 136024 | 30 | 1.81807e+07 | 195042 | 3.50528 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1813.39 | 0.813122 | 18.0385ms | 136024 | 30 | 1.01504e+07 | 71536.1 | 1.28531 | 1(Win) |
| glaze | 1665.13 | 0.958664 | 18.8277ms | 136046 | 30 | 1.6739e+07 | 77917.9 | 1.39953 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 381.86 | 0.249219 | 1248.27ms | 2090234 | 30 | 5.0777e+09 | 5.22025e+06 | 6.10718 | 1(Win) |
| glaze | 358.406 | 0.145579 | 1337.54ms | 2090234 | 30 | 1.96679e+09 | 5.56185e+06 | 6.50689 | 2(Loss) |
| simdjson (ondemand) | 356.419 | 0.101611 | 1341.46ms | 2090234 | 30 | 9.68887e+08 | 5.59286e+06 | 6.54316 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 900.055 | 0.543894 | 529.094ms | 2090234 | 30 | 4.35313e+09 | 2.21476e+06 | 2.591 | 1(Win) |
| glaze | 731.33 | 0.198064 | 658.926ms | 2090234 | 30 | 8.74368e+08 | 2.72572e+06 | 3.18882 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1056.75 | 0.134009 | 1444.32ms | 6661897 | 30 | 1.94736e+09 | 6.01211e+06 | 2.20687 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1054.18 | 0.870009 | 1438.24ms | 6661897 | 30 | 8.24778e+10 | 6.02676e+06 | 2.21218 | 1(Tie) |
| glaze | 863.783 | 0.124241 | 1769.15ms | 6661897 | 30 | 2.50517e+09 | 7.35518e+06 | 2.69988 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1629.85 | 0.150184 | 969.699ms | 6661897 | 30 | 1.02818e+09 | 3.89808e+06 | 1.43086 | 1(Win) |
| jsonifier | 1031.36 | 0.124297 | 1477.85ms | 6661897 | 30 | 1.75879e+09 | 6.1601e+06 | 2.26119 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 906.392 | 0.591561 | 127.249ms | 500299 | 30 | 2.90903e+08 | 526397 | 2.57266 | 1(Win) |
| jsonifier | 859.262 | 0.302078 | 133.696ms | 500299 | 30 | 8.4405e+07 | 555270 | 2.71382 | 2(Loss) |
| simdjson (ondemand) | 577.789 | 0.232916 | 200.898ms | 500299 | 30 | 1.1098e+08 | 825773 | 4.03588 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1852.74 | 0.638653 | 61.8558ms | 500299 | 30 | 8.11488e+07 | 257523 | 1.25843 | 1(Win) |
| jsonifier | 1809.86 | 0.475739 | 63.4955ms | 500299 | 30 | 4.71879e+07 | 263625 | 1.28831 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1598.83 | 0.0998014 | 206.855ms | 1439562 | 30 | 2.20318e+07 | 858672 | 1.45851 | 1(Win) |
| simdjson (ondemand) | 1498.14 | 0.115735 | 221.108ms | 1439562 | 30 | 3.37448e+07 | 916384 | 1.55659 | 2(Loss) |
| glaze | 1472.37 | 0.0933466 | 224.683ms | 1439562 | 30 | 2.27272e+07 | 932424 | 1.58384 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1913.04 | 0.297687 | 175.993ms | 1439584 | 30 | 1.3692e+08 | 717651 | 1.21897 | 1(Win) |
| jsonifier | 1741.33 | 0.259656 | 189.316ms | 1439562 | 30 | 1.25723e+08 | 788406 | 1.33919 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 830.317 | 0.851655 | 16.2638ms | 56369 | 30 | 9.12099e+06 | 64743.5 | 2.80695 | 1(Tie) |
| glaze STATISTICAL TIE | 821.826 | 0.965229 | 16.2096ms | 56369 | 30 | 1.19592e+07 | 65412.5 | 2.83572 | 1(Tie) |
| simdjson (ondemand) | 680.775 | 0.741895 | 19.3649ms | 56369 | 30 | 1.02963e+07 | 78965.4 | 3.42367 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1873.19 | 0.280635 | 7.28383ms | 56369 | 30 | 194592 | 28698.5 | 1.24331 | 1(Win) |
| jsonifier | 1762.51 | 1.04515 | 7.65354ms | 56369 | 30 | 3.0486e+06 | 30500.7 | 1.3216 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1101.29 | 0.688568 | 46.7175ms | 94370 | 32 | 1.01323e+07 | 81720.7 | 2.1162 | 1(Win) |
| simdjson (ondemand) | 1074.8 | 0.834621 | 20.6972ms | 94370 | 30 | 1.46525e+07 | 83734.9 | 2.16858 | 2(Loss) |
| jsonifier | 888.352 | 1.11177 | 25.459ms | 94370 | 30 | 3.80582e+07 | 101309 | 2.62374 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1688.3 | 0.832114 | 13.276ms | 94370 | 30 | 5.90278e+06 | 53307.1 | 1.38021 | 1(Win) |
| jsonifier | 1421.83 | 0.618935 | 15.5994ms | 94370 | 30 | 4.60451e+06 | 63297.5 | 1.63926 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 833.725 | 1.02541 | 15.1358ms | 52708 | 30 | 1.14664e+07 | 60291.2 | 2.79451 | 1(Win) |
| glaze | 694.277 | 1.00166 | 18.1379ms | 52708 | 30 | 1.5778e+07 | 72400.9 | 3.3557 | 2(Loss) |
| jsonifier | 631.444 | 1.26951 | 19.7707ms | 52708 | 30 | 3.06394e+07 | 79605.3 | 3.68975 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2819.36 | 2.22194 | 10.3834ms | 52708 | 32 | 5.02189e+06 | 17829 | 0.825397 | 1(Tie) |
| glaze STATISTICAL TIE | 2723.62 | 1.73012 | 10.8439ms | 52708 | 32 | 3.26258e+06 | 18455.7 | 0.854495 | 1(Tie) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1059.73 | 0.88664 | 15.8203ms | 70103 | 30 | 9.38632e+06 | 63087 | 2.19813 | 1(Win) |
| glaze | 759.209 | 1.63949 | 21.4318ms | 70103 | 30 | 6.25303e+07 | 88059.3 | 3.06907 | 2(Loss) |
| jsonifier | 469.422 | 1.19699 | 35.7353ms | 70103 | 30 | 8.71862e+07 | 142421 | 4.9629 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2215.96 | 1.40943 | 7.53127ms | 70103 | 30 | 5.42451e+06 | 30170 | 1.05024 | 1(Win) |
| jsonifier | 2040.48 | 1.04904 | 8.25277ms | 70103 | 30 | 3.54413e+06 | 32764.5 | 1.14163 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 729.099 | 0.0431314 | 9.23974ms | 11812 | 32 | 1421.06 | 15450.3 | 3.19109 | 1(Win) |
| glaze | 636.701 | 1.64893 | 10.4264ms | 11812 | 32 | 2.72351e+06 | 17692.4 | 3.65507 | 2(Loss) |
| simdjson (ondemand) | 557.553 | 1.51825 | 5.10338ms | 11812 | 30 | 2.8228e+06 | 20204 | 4.17522 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2529.33 | 0.099681 | 1.35303ms | 11812 | 30 | 591.264 | 4453.67 | 0.914779 | 1(Win) |
| glaze | 1221.25 | 1.62897 | 11.3569ms | 11812 | 64 | 1.44492e+06 | 9223.98 | 1.90145 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1355.75 | 1.62691 | 5.53659ms | 31235 | 30 | 3.83329e+06 | 21971.6 | 1.71737 | 1(Win) |
| jsonifier | 1265.46 | 1.28998 | 5.99918ms | 31235 | 30 | 2.76618e+06 | 23539.4 | 1.84007 | 2(Loss) |
| glaze | 1114.1 | 1.12916 | 6.69965ms | 31235 | 30 | 2.73442e+06 | 26737.3 | 2.09036 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1853.44 | 2.14416 | 9.27931ms | 31235 | 32 | 3.80009e+06 | 16071.8 | 1.25542 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1827.47 | 0.0733345 | 4.23112ms | 31235 | 30 | 4286.67 | 16300.1 | 1.2733 | 1(Tie) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1759.84 | 0.888287 | 14.6289ms | 108313 | 30 | 8.15534e+06 | 58695.8 | 1.32411 | 1(Win) |
| glaze | 944.174 | 0.670767 | 26.8306ms | 108313 | 30 | 1.61556e+07 | 109403 | 2.46889 | 2(Loss) |
| simdjson (ondemand) | 833.821 | 0.60227 | 30.1807ms | 108313 | 30 | 1.67001e+07 | 123882 | 2.79584 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1950.39 | 0.653402 | 13.0906ms | 108313 | 30 | 3.59253e+06 | 52961.3 | 1.19482 | 1(Win) |
| glaze | 1683.51 | 1.18205 | 14.985ms | 108313 | 30 | 1.57806e+07 | 61357 | 1.38402 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1489.01 | 0.491875 | 33.3292ms | 213963 | 30 | 1.36305e+07 | 137038 | 1.56573 | 1(Win) |
| glaze | 1322.45 | 0.495342 | 38.2346ms | 213963 | 30 | 1.75247e+07 | 154298 | 1.7629 | 2(Loss) |
| jsonifier | 1129.75 | 0.577588 | 44.346ms | 213963 | 30 | 3.26493e+07 | 180617 | 2.06324 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1670.9 | 0.816545 | 29.5334ms | 213963 | 30 | 2.98302e+07 | 122120 | 1.39497 | 1(Win) |
| jsonifier | 1504.58 | 0.784228 | 32.8663ms | 213963 | 30 | 3.39355e+07 | 135620 | 1.54936 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 436.498 | 0.0718247 | 963.696ms | 1834197 | 30 | 2.4854e+08 | 4.00741e+06 | 5.34272 | 1(Win) |
| glaze | 338.012 | 0.0554806 | 1244.46ms | 1834197 | 30 | 2.47304e+08 | 5.17504e+06 | 6.89949 | 2(Loss) |
| simdjson (ondemand) | 296.302 | 0.119184 | 1414.15ms | 1834197 | 30 | 1.48519e+09 | 5.90353e+06 | 7.87064 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 550.67 | 0.230118 | 761.328ms | 1834197 | 30 | 1.60299e+09 | 3.17654e+06 | 4.235 | 1(Win) |
| glaze | 354.994 | 0.061049 | 1183.92ms | 1833577 | 30 | 2.71291e+08 | 4.92581e+06 | 6.56941 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1404.85 | 0.13703 | 1617.67ms | 9930848 | 30 | 2.56018e+09 | 6.74152e+06 | 1.66003 | 1(Win) |
| jsonifier | 1380.07 | 0.09064 | 1649.5ms | 9930848 | 30 | 1.16073e+09 | 6.86255e+06 | 1.68983 | 2(Loss) |
| glaze | 1283.01 | 0.0904917 | 1774.52ms | 9930848 | 30 | 1.33861e+09 | 7.38172e+06 | 1.81768 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1240.86 | 0.111461 | 1837.81ms | 9930228 | 30 | 2.17091e+09 | 7.63198e+06 | 1.87937 | 1(Win) |
| jsonifier | 1010.34 | 0.0756388 | 2257.82ms | 9930848 | 30 | 1.50816e+09 | 9.37385e+06 | 2.30824 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 798.935 | 0.164694 | 184.017ms | 642697 | 30 | 4.78926e+07 | 767176 | 2.91879 | 1(Win) |
| glaze | 637.319 | 0.155785 | 229.838ms | 642697 | 30 | 6.73399e+07 | 961722 | 3.65904 | 2(Loss) |
| simdjson (ondemand) | 603.042 | 0.0852721 | 244.642ms | 642697 | 30 | 2.25347e+07 | 1.01639e+06 | 3.86708 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 870.074 | 0.214524 | 168.955ms | 642697 | 30 | 6.85133e+07 | 704450 | 2.68015 | 1(Win) |
| glaze | 607.274 | 0.0937955 | 243.12ms | 642692 | 30 | 2.68858e+07 | 1.0093e+06 | 3.84009 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1113.26 | 0.0833496 | 253.851ms | 1225964 | 30 | 2.29874e+07 | 1.05022e+06 | 2.09476 | 1(Win) |
| jsonifier | 988.36 | 0.16139 | 283.509ms | 1225964 | 30 | 1.09346e+08 | 1.18294e+06 | 2.35946 | 2(Loss) |
| glaze | 976.372 | 0.0919421 | 288.952ms | 1225964 | 30 | 3.63643e+07 | 1.19746e+06 | 2.38844 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 979.369 | 0.0964433 | 287.584ms | 1225970 | 30 | 3.97679e+07 | 1.19381e+06 | 2.38115 | 1(Win) |
| jsonifier | 689.389 | 0.0743326 | 407.846ms | 1225964 | 30 | 4.76768e+07 | 1.69595e+06 | 3.38275 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 533.368 | 0.136863 | 177.159ms | 409725 | 30 | 3.01597e+07 | 732598 | 4.37212 | 1(Win) |
| simdjson (ondemand) | 515.422 | 0.240865 | 182.253ms | 409725 | 30 | 1.0003e+08 | 758105 | 4.52435 | 2(Loss) |
| glaze | 393.727 | 0.174273 | 239.206ms | 409725 | 30 | 8.9738e+07 | 992425 | 5.9229 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1400.82 | 0.428073 | 67.5066ms | 409725 | 30 | 4.27738e+07 | 278940 | 1.66449 | 1(Win) |
| jsonifier | 1356.23 | 0.525008 | 69.6373ms | 409725 | 30 | 6.86391e+07 | 288110 | 1.71915 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 944.609 | 0.119901 | 190.648ms | 785750 | 30 | 2.71415e+07 | 793290 | 2.4687 | 1(Win) |
| glaze | 654.927 | 0.313826 | 276.088ms | 785750 | 30 | 3.86796e+08 | 1.14417e+06 | 3.56073 | 2(Loss) |
| jsonifier | 626.672 | 0.141046 | 287.628ms | 785750 | 30 | 8.53356e+07 | 1.19576e+06 | 3.72126 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1521.55 | 0.311246 | 119.146ms | 785750 | 30 | 7.049e+07 | 492492 | 1.53255 | 1(Win) |
| jsonifier | 1301.94 | 0.193679 | 138.999ms | 785750 | 30 | 3.72796e+07 | 575563 | 1.79109 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 698.262 | 0.242109 | 2797.13ms | 8587914 | 30 | 2.41925e+10 | 1.17292e+07 | 3.33981 | 1(Win) |
| jsonifier | 656.646 | 0.62813 | 2956.04ms | 8587914 | 30 | 1.84134e+11 | 1.24726e+07 | 3.55151 | 2(Loss) |
| glaze | 608.513 | 0.540663 | 3222.98ms | 8587914 | 30 | 1.58859e+11 | 1.34592e+07 | 3.83244 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2194.52 | 0.125234 | 906.606ms | 8588126 | 30 | 6.55362e+08 | 3.73215e+06 | 1.06262 | 1(Win) |
| jsonifier | 2144.48 | 0.845144 | 899.191ms | 8588126 | 30 | 3.12562e+10 | 3.81924e+06 | 1.08739 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 782.804 | 0.434172 | 2857.54ms | 9804437 | 30 | 8.06832e+10 | 1.19445e+07 | 2.97908 | 1(Win) |
| glaze | 645.123 | 0.169635 | 3510.89ms | 9804437 | 30 | 1.81347e+10 | 1.44937e+07 | 3.61496 | 2(Loss) |
| jsonifier | 614.114 | 0.28212 | 3647.34ms | 9804437 | 30 | 5.53523e+10 | 1.52256e+07 | 3.7975 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1913.59 | 0.148161 | 1336.09ms | 11078090 | 30 | 2.00734e+09 | 5.52098e+06 | 1.21865 | 1(Win) |
| jsonifier | 1663.77 | 0.134127 | 1536.31ms | 11078090 | 30 | 2.17621e+09 | 6.34998e+06 | 1.40162 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2618.01 | 0.66107 | 23.522ms | 264040 | 30 | 1.21286e+07 | 96182.9 | 0.890171 | 1(Win) |
| jsonifier | 2379.76 | 1.88217 | 25.3129ms | 264040 | 30 | 1.18991e+08 | 105812 | 0.979384 | 2(Loss) |
| glaze | 1025.57 | 0.364334 | 61.8589ms | 264040 | 30 | 2.40066e+07 | 245531 | 2.27351 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3475.28 | 0.567852 | 27.0614ms | 399947 | 30 | 1.16525e+07 | 109752 | 0.670648 | 1(Win) |
| jsonifier | 2817.56 | 0.659262 | 32.9141ms | 399947 | 30 | 2.38943e+07 | 135372 | 0.827297 | 2(Loss) |
| glaze | 1296.72 | 0.951206 | 164.191ms | 399947 | 32 | 2.50501e+08 | 294141 | 1.79805 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 885.48 | 0.433128 | 70.3782ms | 264040 | 30 | 4.55129e+07 | 284375 | 2.63243 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 884.025 | 0.47498 | 70.4687ms | 264040 | 30 | 5.4914e+07 | 284843 | 2.63754 | 1(Tie) |
| glaze | 781.243 | 0.377202 | 78.2264ms | 264040 | 30 | 4.43441e+07 | 322317 | 2.9846 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2354.93 | 0.683497 | 26.4075ms | 263923 | 30 | 1.60101e+07 | 106881 | 0.989761 | 1(Win) |
| jsonifier | 2298.58 | 0.614306 | 26.8154ms | 264040 | 30 | 1.35866e+07 | 109550 | 1.01409 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1221.34 | 0.537697 | 75.6483ms | 399947 | 30 | 8.45925e+07 | 312297 | 1.90914 | 1(Win) |
| glaze | 957.323 | 0.346866 | 97.1445ms | 399947 | 30 | 5.72971e+07 | 398423 | 2.43571 | 2(Loss) |
| jsonifier | 631.703 | 0.32546 | 147.599ms | 399947 | 30 | 1.1585e+08 | 603795 | 3.69107 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2046.2 | 0.768313 | 44.9121ms | 399830 | 30 | 6.14966e+07 | 186349 | 1.13932 | 1(Win) |
| jsonifier | 1883.86 | 0.41877 | 49.3055ms | 399947 | 30 | 2.15666e+07 | 202467 | 1.23757 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1386.52 | 0.3748 | 78.1468ms | 466906 | 30 | 4.34639e+07 | 321147 | 1.68165 | 1(Win) |
| glaze | 1324.53 | 0.286408 | 79.7748ms | 466906 | 30 | 2.78117e+07 | 336176 | 1.76048 | 2(Loss) |
| simdjson (ondemand) | 672.508 | 0.220923 | 160.517ms | 466906 | 30 | 6.41901e+07 | 662113 | 3.46743 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1792.46 | 0.335867 | 89.2768ms | 699405 | 30 | 4.68611e+07 | 372117 | 1.30089 | 1(Win) |
| jsonifier | 1597.12 | 0.227833 | 100.871ms | 699405 | 30 | 2.71606e+07 | 417630 | 1.45998 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1864.92 | 0.344764 | 78.3465ms | 631514 | 30 | 3.71884e+07 | 322940 | 1.25031 | 1(Win) |
| glaze | 1549.83 | 0.25878 | 222.537ms | 631514 | 32 | 3.23601e+07 | 388597 | 1.50458 | 2(Loss) |
