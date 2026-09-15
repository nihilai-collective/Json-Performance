# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 15, 2026)
#### Using the following commits:
----
| Jsonifier: [57ce61b](https://github.com/nihilai-collective/jsonifier/commit/57ce61b)  
| Glaze: [29f478d](https://github.com/stephenberry/glaze/commit/29f478d)  
| Simdjson: [f9c973a](https://github.com/simdjson/simdjson/commit/f9c973a)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX512` |
| simdjson (ondemand) | `icelake` |
| Glaze (utf8-validation) | `AVX512BW` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Intel(R) Xeon(R) Platinum 8370C CPU @ 2.80GHz-AVX512): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.500000% AND mean shift < 1.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [43ba991](https://github.com/realtimechris/benchmarksuite/commit/43ba991).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 651.238 | 0.220783 | 2.06058ms | 1811 | 30 | 1028.52 | 2652.03 | 4.04734 | 1(Win) |
| glaze | 459.302 | 0.164236 | 2.72742ms | 1811 | 32 | 1220.47 | 3760.28 | 5.76229 | 2(Loss) |
| simdjson (ondemand) | 145.281 | 1.63617 | 3.37274ms | 1811 | 30 | 1.13501e+06 | 11888 | 18.2962 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 360.376 | 0.544823 | 1.70017ms | 1811 | 30 | 20452.9 | 4792.5 | 7.32535 | 1(Win) |
| glaze | 273.369 | 0.541374 | 1.99041ms | 1798 | 30 | 34593.7 | 6272.5 | 9.68009 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1277.38 | 0.104789 | 1.24866ms | 3873 | 30 | 275.43 | 2891.53 | 2.0681 | 1(Win) |
| glaze | 1111.42 | 0.098478 | 1.23806ms | 3873 | 30 | 321.321 | 3323.3 | 2.38 | 2(Loss) |
| simdjson (ondemand) | 322.964 | 0.118412 | 3.23855ms | 3873 | 30 | 5501.71 | 11436.5 | 8.23014 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1867.52 | 0.4582 | 1.01179ms | 3873 | 30 | 2463.75 | 1977.8 | 1.4011 | 1(Win) |
| glaze | 896.718 | 0.212316 | 1.427ms | 3873 | 30 | 2294.41 | 4119 | 2.94721 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1313.97 | 0.121729 | 1.20994ms | 3862 | 30 | 349.275 | 2803.03 | 2.01006 | 1(Win) |
| glaze | 918.996 | 0.168417 | 1.41673ms | 3862 | 30 | 1366.75 | 4007.73 | 2.88177 | 2(Loss) |
| simdjson (ondemand) | 314.501 | 0.126421 | 3.36341ms | 3862 | 30 | 6575.68 | 11710.9 | 8.45356 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1831.44 | 0.452749 | 0.973541ms | 3862 | 30 | 2487 | 2011.03 | 1.42805 | 1(Win) |
| glaze | 888.741 | 0.13288 | 1.48198ms | 3862 | 30 | 909.73 | 4144.17 | 2.97424 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 930.907 | 0.238546 | 0.763052ms | 905 | 30 | 146.74 | 927.133 | 2.78836 | 1(Win) |
| glaze | 407.438 | 0.0652933 | 0.980665ms | 905 | 30 | 57.3897 | 2118.3 | 6.4439 | 2(Loss) |
| simdjson (ondemand) | 118.094 | 0.121959 | 2.41446ms | 905 | 30 | 2383.34 | 7308.37 | 22.4827 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 955.152 | 0.0532204 | 0.753705ms | 905 | 30 | 6.93793 | 903.6 | 2.71381 | 1(Win) |
| glaze | 226.694 | 0.12609 | 1.37277ms | 905 | 30 | 691.357 | 3807.23 | 11.6351 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1732.96 | 0.0859639 | 1.87233ms | 9578 | 30 | 615.926 | 5270.93 | 1.52758 | 1(Win) |
| glaze | 1374.13 | 0.256818 | 2.0619ms | 9578 | 30 | 8743.13 | 6647.33 | 1.93003 | 2(Loss) |
| simdjson (ondemand) | 758.421 | 1.25633 | 3.39409ms | 9578 | 30 | 686847 | 12043.8 | 3.50416 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3309.41 | 0.181538 | 1.2739ms | 9578 | 30 | 753.197 | 2760.1 | 0.794731 | 1(Win) |
| glaze | 1899.52 | 0.192483 | 1.61835ms | 9578 | 30 | 2570.2 | 4808.73 | 1.39036 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3722.63 | 0.5057 | 15.0548ms | 233995 | 30 | 2.75689e+06 | 59945.5 | 0.715205 | 1(Win) |
| simdjson (ondemand) | 3260.53 | 0.700814 | 17.0555ms | 233995 | 30 | 6.90182e+06 | 68441.4 | 0.816651 | 2(Loss) |
| glaze | 1258.97 | 0.556104 | 43.1055ms | 233995 | 30 | 2.91486e+07 | 177253 | 2.11561 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4700.85 | 1.05437 | 17.5039ms | 346753 | 30 | 1.65042e+07 | 70346.8 | 0.566417 | 1(Win) |
| simdjson (ondemand) | 4111.39 | 0.684437 | 19.908ms | 346753 | 30 | 9.09181e+06 | 80432.4 | 0.647689 | 2(Loss) |
| glaze | 1526.2 | 0.329101 | 52.5241ms | 346753 | 30 | 1.52544e+07 | 216675 | 1.74527 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 994.316 | 0.631763 | 54.7871ms | 233995 | 30 | 6.03106e+07 | 224431 | 2.67871 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 976.021 | 0.195395 | 55.7546ms | 233995 | 30 | 5.98748e+06 | 228638 | 2.72907 | 2(Tie) |
| glaze STATISTICAL TIE | 968.869 | 0.447188 | 56.0505ms | 233995 | 30 | 3.18262e+07 | 230325 | 2.74917 | 2(Tie) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2263.88 | 0.38531 | 24.6894ms | 233995 | 30 | 4.32761e+06 | 98571.9 | 1.17625 | 1(Win) |
| jsonifier | 1954.03 | 0.536055 | 28.1654ms | 233995 | 30 | 1.12433e+07 | 114203 | 1.36292 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1349.96 | 0.935262 | 58.7185ms | 346753 | 30 | 1.57466e+08 | 244963 | 1.97303 | 1(Win) |
| glaze | 1161.37 | 0.176766 | 69.8533ms | 346753 | 30 | 7.60006e+06 | 284740 | 2.29356 | 2(Loss) |
| jsonifier | 964.353 | 0.231135 | 84.096ms | 346753 | 30 | 1.8846e+07 | 342913 | 2.76211 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2230.82 | 0.435064 | 36.2691ms | 346753 | 30 | 1.24778e+07 | 148237 | 1.19375 | 1(Win) |
| glaze | 2098.47 | 0.467965 | 38.6943ms | 346753 | 30 | 1.63148e+07 | 157586 | 1.26901 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3645.64 | 0.295703 | 15.4067ms | 233995 | 30 | 982875 | 61211.4 | 0.730323 | 1(Win) |
| simdjson (ondemand) | 2037.9 | 0.726463 | 26.8048ms | 233995 | 30 | 1.89844e+07 | 109503 | 1.30679 | 2(Loss) |
| glaze | 1250.17 | 0.463496 | 43.558ms | 233995 | 30 | 2.05348e+07 | 178500 | 2.13047 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4614.69 | 0.36921 | 17.915ms | 346753 | 30 | 2.10003e+06 | 71660.2 | 0.57701 | 1(Win) |
| simdjson (ondemand) | 2755.75 | 0.511417 | 29.4655ms | 346753 | 30 | 1.12988e+07 | 120000 | 0.966463 | 2(Loss) |
| glaze | 1522.81 | 0.321413 | 52.8192ms | 346753 | 30 | 1.4615e+07 | 217158 | 1.74915 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1011.14 | 0.76853 | 53.8352ms | 233995 | 30 | 8.63046e+07 | 220697 | 2.63424 | 1(Win) |
| jsonifier | 861.895 | 0.380863 | 63.544ms | 233995 | 30 | 2.91718e+07 | 258912 | 3.09025 | 2(Loss) |
| simdjson (ondemand) | 175.079 | 0.225956 | 307.029ms | 233995 | 30 | 2.48836e+08 | 1.2746e+06 | 15.2156 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2354.97 | 0.551389 | 23.5872ms | 233995 | 30 | 8.18994e+06 | 94759.3 | 1.13079 | 1(Win) |
| jsonifier | 2167.92 | 0.344729 | 25.9573ms | 233995 | 30 | 3.77751e+06 | 102935 | 1.22817 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1180.13 | 0.197039 | 68.6193ms | 346753 | 30 | 9.14545e+06 | 280214 | 2.25708 | 1(Win) |
| jsonifier | 949.074 | 0.332977 | 84.3828ms | 346753 | 30 | 4.03822e+07 | 348434 | 2.80666 | 2(Loss) |
| simdjson (ondemand) | 256.422 | 0.226726 | 310.288ms | 346753 | 30 | 2.5648e+08 | 1.28963e+06 | 10.3887 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2600.18 | 0.403884 | 31.399ms | 346753 | 30 | 7.91529e+06 | 127179 | 1.02426 | 1(Win) |
| glaze | 2148.57 | 0.735759 | 37.8051ms | 346753 | 30 | 3.84709e+07 | 153911 | 1.23937 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 715.106 | 0.548436 | 31.1259ms | 94651 | 30 | 1.43775e+07 | 126228 | 3.72409 | 1(Win) |
| glaze | 655.497 | 0.444387 | 33.9255ms | 94651 | 30 | 1.12345e+07 | 137706 | 4.06295 | 2(Loss) |
| jsonifier | 562.686 | 0.462823 | 39.2924ms | 94651 | 30 | 1.65375e+07 | 160420 | 4.73322 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2994.65 | 0.558666 | 7.80916ms | 94651 | 30 | 850717 | 30142.5 | 0.888449 | 1(Win) |
| jsonifier | 2318.75 | 0.699426 | 9.93057ms | 94651 | 30 | 2.22408e+06 | 38928.9 | 1.14724 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 983.49 | 0.572212 | 32.5104ms | 136024 | 30 | 1.70894e+07 | 131900 | 2.70763 | 1(Win) |
| glaze | 821.669 | 0.361878 | 38.9289ms | 136024 | 30 | 9.79225e+06 | 157877 | 3.24145 | 2(Loss) |
| jsonifier | 698.884 | 0.393655 | 46.0036ms | 136024 | 30 | 1.60167e+07 | 185614 | 3.81095 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3175.91 | 0.543075 | 10.5117ms | 136024 | 30 | 1.47617e+06 | 40845.8 | 0.838001 | 1(Win) |
| glaze | 2665.42 | 0.80892 | 12.2379ms | 136046 | 30 | 4.65127e+06 | 48676.5 | 0.998658 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 473.13 | 1.02221 | 1008.06ms | 2090234 | 30 | 5.56458e+10 | 4.21322e+06 | 5.63044 | 1(Win) |
| glaze | 383.272 | 0.0997729 | 1252.48ms | 2090234 | 30 | 8.07837e+08 | 5.20102e+06 | 6.95062 | 2(Loss) |
| simdjson (ondemand) | 364.729 | 0.354597 | 1313.14ms | 2090234 | 30 | 1.12678e+10 | 5.46543e+06 | 7.30394 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 853.202 | 0.125378 | 562.021ms | 2090234 | 30 | 2.57426e+08 | 2.33638e+06 | 3.12214 | 1(Win) |
| glaze | 789.905 | 0.138996 | 607.36ms | 2090234 | 30 | 3.69119e+08 | 2.5236e+06 | 3.3724 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1037.1 | 0.373232 | 1467.69ms | 6661897 | 30 | 1.56831e+10 | 6.12599e+06 | 2.56855 | 1(Win) |
| jsonifier | 881.537 | 0.200129 | 1745.04ms | 6661897 | 30 | 6.24104e+09 | 7.20705e+06 | 3.02192 | 2(Loss) |
| glaze | 751.201 | 0.061636 | 2039.05ms | 6661897 | 30 | 8.1522e+08 | 8.4575e+06 | 3.54628 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1894.98 | 0.246793 | 812.479ms | 6661897 | 30 | 2.05387e+09 | 3.35269e+06 | 1.40575 | 1(Win) |
| glaze | 1611.62 | 0.480986 | 946.436ms | 6661897 | 30 | 1.07859e+10 | 3.94216e+06 | 1.65272 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 981.963 | 0.376421 | 117.178ms | 500299 | 30 | 1.00355e+08 | 485886 | 2.71262 | 1(Win) |
| glaze | 900.431 | 0.264616 | 127.707ms | 500299 | 30 | 5.89811e+07 | 529882 | 2.95827 | 2(Loss) |
| simdjson (ondemand) | 712.727 | 0.136191 | 162.659ms | 500299 | 30 | 2.49363e+07 | 669432 | 3.73733 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2072.63 | 0.368374 | 56.5182ms | 500299 | 30 | 2.15733e+07 | 230202 | 1.28479 | 1(Win) |
| jsonifier | 1562.93 | 0.571104 | 74.4618ms | 500299 | 30 | 9.11874e+07 | 305275 | 1.70392 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1797.61 | 0.293047 | 183.925ms | 1439562 | 30 | 1.50267e+08 | 763720 | 1.48176 | 1(Win) |
| glaze | 1276.01 | 1.31454 | 259.893ms | 1439562 | 30 | 6.00093e+09 | 1.07591e+06 | 2.0876 | 2(Loss) |
| jsonifier | 1084.57 | 1.06347 | 301.811ms | 1439562 | 30 | 5.43649e+09 | 1.26583e+06 | 2.45609 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2359.13 | 0.22861 | 140.069ms | 1439562 | 30 | 5.30969e+07 | 581940 | 1.12895 | 1(Win) |
| glaze | 2265.5 | 0.298568 | 147.076ms | 1439584 | 30 | 9.82097e+07 | 606002 | 1.17568 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 991.933 | 0.385426 | 14.0381ms | 56369 | 30 | 1.30894e+06 | 54194.8 | 2.68311 | 1(Win) |
| glaze | 895.42 | 1.09869 | 15.1675ms | 56369 | 30 | 1.30527e+07 | 60036.3 | 2.97334 | 2(Loss) |
| simdjson (ondemand) | 795.652 | 0.354374 | 39.5424ms | 56369 | 32 | 1.83446e+06 | 67564.3 | 3.34635 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2792.47 | 0.81166 | 5.1416ms | 56369 | 30 | 732442 | 19250.9 | 0.951801 | 1(Win) |
| jsonifier | 2024.62 | 0.298872 | 6.92704ms | 56369 | 30 | 188923 | 26552 | 1.31357 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1234.04 | 0.628533 | 18.3058ms | 94370 | 30 | 6.30361e+06 | 72929.9 | 2.15768 | 1(Win) |
| glaze | 1153.86 | 0.772634 | 19.6825ms | 94370 | 30 | 1.08952e+07 | 77997.7 | 2.30774 | 2(Loss) |
| jsonifier | 986.734 | 0.85495 | 22.842ms | 94370 | 30 | 1.82419e+07 | 91208.2 | 2.69845 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3050.52 | 0.619284 | 7.73498ms | 94370 | 30 | 1.00143e+06 | 29502.6 | 0.872254 | 1(Win) |
| glaze | 2517.63 | 0.887702 | 9.13967ms | 94370 | 30 | 3.02094e+06 | 35747.3 | 1.0567 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 944.771 | 0.809587 | 13.6414ms | 52708 | 30 | 5.56606e+06 | 53204.7 | 2.81753 | 1(Win) |
| jsonifier | 770.163 | 0.546329 | 17.1712ms | 52708 | 30 | 3.81433e+06 | 65267.1 | 3.45714 | 2(Loss) |
| glaze | 703.293 | 1.06508 | 18.0048ms | 52708 | 30 | 1.73846e+07 | 71472.7 | 3.78632 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3635.16 | 1.1694 | 3.85749ms | 52708 | 30 | 784425 | 13827.8 | 0.730824 | 1(Win) |
| jsonifier | 2802.01 | 1.61061 | 4.81566ms | 52708 | 30 | 2.50448e+06 | 17939.4 | 0.948943 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1171.52 | 0.632089 | 14.4061ms | 70103 | 30 | 3.90349e+06 | 57067.4 | 2.27261 | 1(Win) |
| glaze | 810.071 | 0.656288 | 20.8397ms | 70103 | 30 | 8.8011e+06 | 82530.3 | 3.28687 | 2(Loss) |
| jsonifier | 670.253 | 1.36512 | 25.2308ms | 70103 | 30 | 5.56238e+07 | 99746.5 | 3.95796 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3315.9 | 0.150514 | 5.47192ms | 70103 | 30 | 27627.8 | 20162.1 | 0.802163 | 1(Win) |
| glaze | 3231.13 | 0.549324 | 5.69146ms | 70103 | 30 | 387563 | 20691 | 0.822963 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 746.81 | 0.0769529 | 4.32509ms | 11812 | 30 | 4042.02 | 15083.9 | 3.55983 | 1(Win) |
| glaze | 700.057 | 2.20044 | 4.4811ms | 11812 | 30 | 3.76114e+06 | 16091.3 | 3.79788 | 2(Loss) |
| simdjson (ondemand) | 645.871 | 1.93106 | 4.68829ms | 11812 | 30 | 3.40306e+06 | 17441.3 | 4.1168 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2101.35 | 0.205834 | 1.75604ms | 11812 | 30 | 3652.62 | 5360.73 | 1.26049 | 1(Win) |
| glaze | 1892.57 | 0.184811 | 1.89964ms | 11812 | 30 | 3630.12 | 5952.13 | 1.39973 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1515.92 | 0.871919 | 5.28765ms | 31235 | 30 | 880649 | 19650.1 | 1.75452 | 1(Win) |
| glaze | 1064.59 | 1.56166 | 7.30237ms | 31235 | 30 | 5.7282e+06 | 27980.9 | 2.49923 | 2(Loss) |
| jsonifier | 1013.86 | 1.46671 | 7.69152ms | 31235 | 30 | 5.57103e+06 | 29380.7 | 2.62328 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2996.49 | 0.344277 | 6.27895ms | 31235 | 32 | 37482.2 | 9940.97 | 0.886678 | 1(Win) |
| glaze | 2837.33 | 0.200371 | 3.04662ms | 31235 | 30 | 13275.6 | 10498.6 | 0.93567 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1602.22 | 0.917199 | 16.1946ms | 108313 | 30 | 1.04898e+07 | 64470.3 | 1.66156 | 1(Win) |
| glaze | 1103.1 | 0.856047 | 23.1154ms | 108313 | 30 | 1.92773e+07 | 93640.7 | 2.41414 | 2(Loss) |
| simdjson (ondemand) | 1065.82 | 0.27459 | 24.134ms | 108313 | 30 | 2.12463e+06 | 96916.3 | 2.49854 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2403.62 | 1.18355 | 10.9046ms | 108313 | 30 | 7.76105e+06 | 42974.8 | 1.10743 | 1(Tie) |
| glaze STATISTICAL TIE | 2361.99 | 0.416439 | 11.0753ms | 108313 | 30 | 995015 | 43732.4 | 1.12703 | 1(Tie) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1866.86 | 1.52244 | 26.5822ms | 213963 | 30 | 8.30716e+07 | 109302 | 1.42656 | 1(Win) |
| glaze | 1478.39 | 0.424955 | 34.085ms | 213963 | 30 | 1.03206e+07 | 138023 | 1.80156 | 2(Loss) |
| jsonifier | 1113.4 | 0.492473 | 45.0608ms | 213963 | 30 | 2.44376e+07 | 183268 | 2.39221 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3666.22 | 0.578266 | 13.9552ms | 213963 | 30 | 3.10755e+06 | 55657.1 | 0.726266 | 1(Win) |
| glaze | 2443.67 | 0.40531 | 20.6073ms | 213963 | 30 | 3.43627e+06 | 83501.9 | 1.08969 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 427.043 | 0.0722399 | 988.819ms | 1834197 | 30 | 2.62679e+08 | 4.09614e+06 | 6.23815 | 1(Win) |
| glaze | 347.9 | 0.123895 | 1212.3ms | 1834197 | 30 | 1.16416e+09 | 5.02795e+06 | 7.65724 | 2(Loss) |
| simdjson (ondemand) | 328.27 | 0.847999 | 1290.93ms | 1834197 | 30 | 6.1255e+10 | 5.32862e+06 | 8.11505 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 508.769 | 0.0881109 | 826.776ms | 1834197 | 30 | 2.75316e+08 | 3.43816e+06 | 5.23596 | 1(Win) |
| glaze | 502.44 | 0.208064 | 835.362ms | 1833577 | 30 | 1.57307e+09 | 3.48029e+06 | 5.30182 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1435.95 | 1.00837 | 1572.1ms | 9930848 | 30 | 1.32696e+11 | 6.59551e+06 | 1.85506 | 1(Win) |
| glaze | 1279.69 | 0.0711074 | 1790.43ms | 9930848 | 30 | 8.30833e+08 | 7.40085e+06 | 2.08167 | 2(Loss) |
| jsonifier | 1238.85 | 1.07516 | 1855.99ms | 9930848 | 30 | 2.02674e+11 | 7.64483e+06 | 2.15019 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1638.85 | 0.67554 | 1406.37ms | 9930848 | 30 | 4.57211e+10 | 5.77892e+06 | 1.62542 | 1(Win) |
| glaze | 1179 | 0.57186 | 1908.86ms | 9930228 | 30 | 6.32981e+10 | 8.0324e+06 | 2.25932 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 778.682 | 0.861355 | 191.04ms | 642697 | 30 | 1.37904e+09 | 787130 | 3.42089 | 1(Win) |
| glaze | 667.788 | 0.201907 | 220.676ms | 642697 | 30 | 1.03029e+08 | 917841 | 3.98894 | 2(Loss) |
| simdjson (ondemand) | 576.914 | 0.774181 | 258.79ms | 642697 | 30 | 2.02954e+09 | 1.06242e+06 | 4.61731 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 837.951 | 0.179439 | 176.495ms | 642697 | 30 | 5.1681e+07 | 731455 | 3.17856 | 1(Win) |
| glaze | 717.301 | 0.152353 | 205.719ms | 642692 | 30 | 5.08425e+07 | 854480 | 3.71328 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1005.9 | 0.169672 | 279.802ms | 1225964 | 30 | 1.16677e+08 | 1.16231e+06 | 2.64816 | 1(Win) |
| simdjson (ondemand) | 953.63 | 2.29319 | 289.741ms | 1225964 | 30 | 2.37135e+10 | 1.22602e+06 | 2.7934 | 2(Loss) |
| jsonifier | 884.674 | 0.199898 | 318.878ms | 1225964 | 30 | 2.09375e+08 | 1.32158e+06 | 3.01105 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1415.42 | 0.225383 | 199.23ms | 1225964 | 30 | 1.03981e+08 | 826026 | 1.88196 | 1(Win) |
| glaze | 1134.32 | 0.155702 | 247.828ms | 1225970 | 30 | 7.72671e+07 | 1.03073e+06 | 2.34835 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 584.907 | 0.331773 | 160.881ms | 409725 | 30 | 1.47372e+08 | 668045 | 4.55414 | 1(Win) |
| jsonifier | 527.928 | 0.189654 | 179.7ms | 409725 | 30 | 5.9113e+07 | 740147 | 5.04507 | 2(Loss) |
| glaze | 454.421 | 0.231546 | 206.73ms | 409725 | 30 | 1.18923e+08 | 859872 | 5.86179 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1698.52 | 0.485142 | 56.0447ms | 409725 | 30 | 3.73681e+07 | 230049 | 1.56767 | 1(Win) |
| jsonifier | 1574.64 | 0.389099 | 60.5863ms | 409725 | 30 | 2.79683e+07 | 248149 | 1.69154 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1047.41 | 0.24636 | 172.336ms | 785750 | 30 | 9.31956e+07 | 715430 | 2.54321 | 1(Win) |
| glaze | 713.084 | 0.108135 | 253.403ms | 785750 | 30 | 3.87385e+07 | 1.05086e+06 | 3.7357 | 2(Loss) |
| jsonifier | 628.066 | 0.572705 | 286.654ms | 785750 | 30 | 1.40069e+09 | 1.19311e+06 | 4.24132 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2136.06 | 0.26739 | 85.0647ms | 785750 | 30 | 2.63969e+07 | 350809 | 1.24702 | 1(Win) |
| glaze | 1849.08 | 0.271138 | 98.2022ms | 785750 | 30 | 3.62206e+07 | 405254 | 1.44028 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 649.797 | 0.574759 | 3003.85ms | 8587914 | 30 | 1.57439e+11 | 1.2604e+07 | 4.09948 | 1(Win) |
| jsonifier | 610.724 | 0.350063 | 3191.2ms | 8587914 | 30 | 6.61149e+10 | 1.34104e+07 | 4.3617 | 2(Loss) |
| glaze | 556.64 | 0.362367 | 3598.6ms | 8587914 | 30 | 8.52797e+10 | 1.47134e+07 | 4.78575 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1633.23 | 0.82344 | 1212.11ms | 8588126 | 30 | 5.11547e+10 | 5.01476e+06 | 1.63094 | 1(Win) |
| jsonifier | 1572.66 | 0.696665 | 1209.58ms | 8588126 | 30 | 3.94908e+10 | 5.20791e+06 | 1.69368 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 731.137 | 0.459059 | 3092.1ms | 9804437 | 30 | 1.03397e+11 | 1.27886e+07 | 3.64338 | 1(Win) |
| glaze | 558.126 | 0.575243 | 4014.81ms | 9804437 | 30 | 2.78615e+11 | 1.67529e+07 | 4.77283 | 2(Loss) |
| jsonifier | 533.411 | 0.348482 | 4255.16ms | 9804437 | 30 | 1.11945e+11 | 1.75291e+07 | 4.99396 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1800.82 | 0.708987 | 1444.26ms | 11078090 | 30 | 5.19023e+10 | 5.8667e+06 | 1.47918 | 1(Win) |
| glaze | 1643.75 | 0.436661 | 1569.25ms | 11078090 | 30 | 2.36302e+10 | 6.42731e+06 | 1.6205 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3614.88 | 0.962344 | 17.4888ms | 264040 | 30 | 1.34813e+07 | 69658.7 | 0.736576 | 1(Win) |
| simdjson (ondemand) | 3416.17 | 0.835349 | 18.406ms | 264040 | 30 | 1.13741e+07 | 73710.6 | 0.779436 | 2(Loss) |
| glaze | 1180 | 0.311242 | 52.0307ms | 264040 | 30 | 1.3234e+07 | 213396 | 2.25725 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4590.07 | 0.338994 | 20.8112ms | 399947 | 30 | 2.38052e+06 | 83096.7 | 0.580144 | 1(Win) |
| simdjson (ondemand) | 4408.15 | 0.357118 | 21.468ms | 399947 | 30 | 2.86443e+06 | 86525.9 | 0.604092 | 2(Loss) |
| glaze | 1461.48 | 0.371548 | 63.3386ms | 399947 | 30 | 2.82077e+07 | 260981 | 1.82256 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1076.19 | 1.02469 | 57.4376ms | 264040 | 30 | 1.72452e+08 | 233981 | 2.4749 | 1(Win) |
| jsonifier | 891.077 | 0.755855 | 69.4476ms | 264040 | 30 | 1.3687e+08 | 282589 | 2.98916 | 2(Loss) |
| glaze | 837.063 | 0.458028 | 73.4233ms | 264040 | 30 | 5.69545e+07 | 300823 | 3.18197 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3036.21 | 0.882011 | 20.6815ms | 263923 | 30 | 1.60383e+07 | 82898.2 | 0.8766 | 1(Win) |
| jsonifier | 2333.32 | 0.643519 | 26.4184ms | 264040 | 30 | 1.44689e+07 | 107918 | 1.14131 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1523.5 | 0.266505 | 62.6052ms | 399947 | 30 | 1.33553e+07 | 250357 | 1.74819 | 1(Win) |
| glaze | 1016.37 | 0.32709 | 91.5422ms | 399947 | 30 | 4.52021e+07 | 375277 | 2.62059 | 2(Loss) |
| jsonifier | 823.949 | 0.770478 | 113.687ms | 399947 | 30 | 3.81633e+08 | 462916 | 3.22937 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3519.31 | 0.589976 | 26.8528ms | 399947 | 30 | 1.22654e+07 | 108379 | 0.756652 | 1(Win) |
| glaze | 2383.47 | 0.502628 | 38.9759ms | 399830 | 30 | 1.93975e+07 | 159980 | 1.11697 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1599.84 | 0.344322 | 67.7521ms | 466906 | 30 | 2.75522e+07 | 278325 | 1.66466 | 1(Win) |
| glaze | 1546.77 | 0.261137 | 69.7557ms | 466906 | 30 | 1.69537e+07 | 287874 | 1.72203 | 2(Loss) |
| simdjson (ondemand) | 775.989 | 0.251309 | 139.084ms | 466906 | 30 | 6.23855e+07 | 573817 | 3.43235 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2382.9 | 0.235843 | 67.8631ms | 699405 | 30 | 1.30741e+07 | 279913 | 1.1175 | 1(Win) |
| glaze | 2140.65 | 0.299635 | 75.7965ms | 699405 | 30 | 2.615e+07 | 311590 | 1.24426 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1699.59 | 0.365316 | 85.6598ms | 631514 | 30 | 5.02732e+07 | 354355 | 1.56723 | 1(Win) |
| glaze | 1540.56 | 0.307574 | 95.0375ms | 631514 | 30 | 4.33743e+07 | 390936 | 1.72904 | 2(Loss) |
