# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.18.33.2-microsoft-standard-WSL2 using the GCC 16.1.0 compiler).  

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

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.500000% AND mean shift < 1.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [c0b7b4a](https://github.com/realtimechris/benchmarksuite/commit/c0b7b4a).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1147.68 | 0.124491 | 1.71734ms | 1811 | 30 | 105.292 | 1504.87 | 2.60834 | 1(Win) |
| glaze | 868.401 | 0.168721 | 0.785843ms | 1811 | 30 | 337.799 | 1988.83 | 3.45413 | 2(Loss) |
| simdjson (ondemand) | 242.77 | 0.0449892 | 2.02808ms | 1811 | 30 | 307.316 | 7114.17 | 12.4719 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 703.342 | 0.0655106 | 1.05788ms | 1811 | 30 | 77.6333 | 2455.57 | 4.2573 | 1(Win) |
| glaze | 482.174 | 0.276063 | 1.14979ms | 1798 | 30 | 2891.41 | 3556.2 | 6.23784 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2009.97 | 0.0355344 | 0.830731ms | 3873 | 30 | 12.792 | 1837.63 | 1.4899 | 1(Win) |
| glaze | 1877.87 | 0.0372372 | 0.744334ms | 3873 | 30 | 16.0931 | 1966.9 | 1.59657 | 2(Loss) |
| simdjson (ondemand) | 445.484 | 0.474956 | 5.26287ms | 3873 | 32 | 49623.4 | 8291.16 | 6.80228 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3015.91 | 0.0729431 | 0.665017ms | 3873 | 30 | 23.9414 | 1224.7 | 0.98159 | 1(Win) |
| glaze | 1372.89 | 0.185467 | 0.939552ms | 3873 | 30 | 746.93 | 2690.37 | 2.19259 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1708.06 | 0.0424313 | 0.790782ms | 3862 | 30 | 25.1138 | 2156.3 | 1.75743 | 1(Win) |
| jsonifier | 1622.58 | 0.0590434 | 0.949797ms | 3862 | 30 | 53.8862 | 2269.9 | 1.84581 | 2(Loss) |
| simdjson (ondemand) | 457.884 | 2.20854 | 5.3687ms | 3862 | 32 | 1.00989e+06 | 8043.72 | 6.6118 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2906.02 | 0.311053 | 0.912452ms | 3862 | 30 | 466.248 | 1267.4 | 1.01914 | 1(Win) |
| glaze | 1403.83 | 0.222315 | 1.01787ms | 3862 | 30 | 1020.59 | 2623.6 | 2.12753 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1730.88 | 0.0402056 | 0.495057ms | 905 | 30 | 1.20575 | 498.633 | 1.68917 | 1(Win) |
| glaze | 646.983 | 0.0362994 | 0.617876ms | 905 | 30 | 7.03448 | 1334 | 4.63193 | 2(Loss) |
| simdjson (ondemand) | 192.773 | 0.0898706 | 2.8931ms | 905 | 32 | 518.072 | 4477.16 | 15.6884 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1289.07 | 0.12664 | 0.524422ms | 905 | 30 | 21.5678 | 669.533 | 2.2923 | 1(Win) |
| glaze | 350.587 | 0.106878 | 0.911493ms | 905 | 30 | 207.683 | 2461.8 | 8.59057 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4007.5 | 0.0659239 | 0.976581ms | 9578 | 30 | 67.7345 | 2279.3 | 0.751034 | 1(Win) |
| glaze | 2930.38 | 0.238641 | 1.04723ms | 9578 | 30 | 1660.02 | 3117.1 | 1.02921 | 2(Loss) |
| simdjson (ondemand) | 1464.19 | 0.068964 | 1.90693ms | 9578 | 30 | 555.292 | 6238.47 | 2.06891 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5716.44 | 0.166535 | 0.767816ms | 9578 | 30 | 212.438 | 1597.9 | 0.520878 | 1(Win) |
| glaze | 2955.44 | 0.114634 | 1.00006ms | 9578 | 30 | 376.575 | 3090.67 | 1.01573 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5463.41 | 0.542515 | 10.3335ms | 233995 | 30 | 1.4731e+06 | 40845.4 | 0.555798 | 1(Win) |
| simdjson (ondemand) | 4322.38 | 0.461364 | 13.2284ms | 233995 | 30 | 1.70206e+06 | 51627.8 | 0.70278 | 2(Loss) |
| glaze | 2110.33 | 1.1097 | 26.1868ms | 233995 | 30 | 4.13093e+07 | 105744 | 1.43976 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6933.36 | 0.818054 | 12.9075ms | 346753 | 30 | 4.56708e+06 | 47695.4 | 0.438082 | 1(Win) |
| simdjson (ondemand) | 5522.65 | 0.727134 | 15.2098ms | 346753 | 30 | 5.68717e+06 | 59878.8 | 0.550017 | 2(Loss) |
| glaze | 2690.49 | 0.533687 | 30.5077ms | 346753 | 30 | 1.29084e+07 | 122910 | 1.12929 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1747.63 | 0.774642 | 32.0915ms | 233995 | 30 | 2.93519e+07 | 127690 | 1.7386 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1723.24 | 0.688239 | 32.642ms | 233995 | 30 | 2.38298e+07 | 129497 | 1.76334 | 1(Tie) |
| simdjson (ondemand) | 1657.47 | 0.501786 | 34.2153ms | 233995 | 30 | 1.36925e+07 | 134636 | 1.83324 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4417.51 | 0.491414 | 12.8688ms | 233995 | 30 | 1.84874e+06 | 50516.1 | 0.687004 | 1(Win) |
| glaze | 4211.69 | 0.377333 | 13.7732ms | 233995 | 30 | 1.19914e+06 | 52984.6 | 0.721061 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 2116.22 | 1.67692 | 36.77ms | 346753 | 30 | 2.05999e+08 | 156264 | 1.43561 | 1(Tie) |
| glaze STATISTICAL TIE | 2105.52 | 0.625632 | 39.8135ms | 346753 | 30 | 2.89655e+07 | 157058 | 1.44318 | 1(Tie) |
| jsonifier | 1658.3 | 0.770211 | 50.3986ms | 346753 | 30 | 7.07707e+07 | 199414 | 1.83239 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4746.45 | 1.85923 | 17.5388ms | 346753 | 30 | 5.03373e+07 | 69670.9 | 0.63956 | 1(Win) |
| glaze | 4227.18 | 1.60487 | 46.595ms | 346753 | 32 | 5.04395e+07 | 78229.4 | 0.718573 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5200.23 | 0.652888 | 11.097ms | 233995 | 30 | 2.35487e+06 | 42912.5 | 0.584058 | 1(Win) |
| simdjson (ondemand) | 3041.54 | 1.48449 | 18.3422ms | 233995 | 30 | 3.5588e+07 | 73369.1 | 0.998785 | 2(Loss) |
| glaze | 2121.26 | 0.744399 | 26.6391ms | 233995 | 30 | 1.83976e+07 | 105200 | 1.43216 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6793.73 | 0.409173 | 12.4647ms | 346753 | 30 | 1.19003e+06 | 48675.7 | 0.447129 | 1(Win) |
| simdjson (ondemand) | 4285.31 | 0.554332 | 99.4909ms | 346753 | 64 | 1.17111e+07 | 77168.1 | 0.708865 | 2(Loss) |
| glaze | 2746.72 | 0.482063 | 31.1164ms | 346753 | 30 | 1.01051e+07 | 120394 | 1.10615 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1850.89 | 0.673954 | 74.1238ms | 233995 | 32 | 2.11282e+07 | 120566 | 1.64168 | 1(Win) |
| jsonifier | 1556.77 | 0.782242 | 179.492ms | 233995 | 64 | 8.0469e+07 | 143345 | 1.95181 | 2(Loss) |
| simdjson (ondemand) | 236.949 | 0.640807 | 230.156ms | 233995 | 30 | 1.09264e+09 | 941783 | 12.8255 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4782.94 | 1.71887 | 12.4931ms | 233995 | 30 | 1.92945e+07 | 46656.5 | 0.63456 | 1(Win) |
| glaze | 4322.42 | 0.406508 | 31.0675ms | 233995 | 32 | 1.40945e+06 | 51627.4 | 0.702669 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1941.54 | 1.864 | 91.6364ms | 346753 | 32 | 3.22544e+08 | 170323 | 1.56458 | 1(Win) |
| jsonifier | 1641.27 | 0.747704 | 49.6909ms | 346753 | 30 | 6.80867e+07 | 201484 | 1.8514 | 2(Loss) |
| simdjson (ondemand) | 345.784 | 0.604529 | 232.536ms | 346753 | 30 | 1.00274e+09 | 956348 | 8.78851 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5013.28 | 0.372132 | 17.371ms | 346753 | 30 | 1.80764e+06 | 65962.6 | 0.605637 | 1(Win) |
| glaze | 4235.69 | 0.627 | 99.087ms | 346753 | 64 | 1.53358e+07 | 78072.1 | 0.717175 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1305.07 | 1.10806 | 18.2859ms | 94651 | 30 | 1.76209e+07 | 69165.6 | 2.32785 | 1(Tie) |
| glaze STATISTICAL TIE | 1263.17 | 1.60152 | 41.1586ms | 94651 | 32 | 4.19125e+07 | 71460.1 | 2.40505 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1246.7 | 0.539388 | 18.0165ms | 94651 | 30 | 4.57563e+06 | 72404.1 | 2.43697 | 1(Tie) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 5809.46 | 0.110697 | 4.15728ms | 94651 | 30 | 8875.13 | 15537.8 | 0.522166 | 1(Win) |
| jsonifier | 5639.03 | 0.27309 | 4.35848ms | 94651 | 30 | 57329.1 | 16007.4 | 0.537565 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1686.32 | 0.772924 | 18.7087ms | 136024 | 30 | 1.06059e+07 | 76926.6 | 1.80159 | 1(Win) |
| glaze | 1415.67 | 2.42214 | 21.1019ms | 136024 | 30 | 1.47783e+08 | 91633.2 | 2.14503 | 2(Loss) |
| jsonifier | 1194.64 | 0.716233 | 27.8235ms | 136024 | 30 | 1.81462e+07 | 108587 | 2.54332 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7110.5 | 0.0724597 | 5.0088ms | 136024 | 30 | 5242.58 | 18243.8 | 0.425862 | 1(Win) |
| glaze | 5612.64 | 0.103809 | 6.10533ms | 136046 | 30 | 17275.5 | 23116.3 | 0.540786 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 759.169 | 1.56038 | 625.627ms | 2090234 | 30 | 5.03611e+10 | 2.62577e+06 | 4.00284 | 1(Win) |
| simdjson (ondemand) | 726.492 | 1.17493 | 659.35ms | 2090234 | 30 | 3.118e+10 | 2.74387e+06 | 4.18271 | 2(Loss) |
| glaze | 696.978 | 0.697892 | 701.557ms | 2090234 | 30 | 1.19523e+10 | 2.86007e+06 | 4.36008 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1558.01 | 0.844683 | 309.136ms | 2090234 | 30 | 3.50394e+09 | 1.27945e+06 | 1.9502 | 1(Win) |
| glaze | 1327.5 | 1.27333 | 358.755ms | 2090234 | 30 | 1.09679e+10 | 1.50162e+06 | 2.28888 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2148.19 | 1.08792 | 715.379ms | 6661897 | 30 | 3.10572e+10 | 2.9575e+06 | 1.41459 | 1(Win) |
| jsonifier | 1958.19 | 0.72137 | 790.68ms | 6661897 | 30 | 1.64332e+10 | 3.24446e+06 | 1.55189 | 2(Loss) |
| glaze | 1719.66 | 0.916428 | 896.42ms | 6661897 | 30 | 3.43899e+10 | 3.69451e+06 | 1.76707 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2987.61 | 0.653539 | 517.113ms | 6661897 | 30 | 5.79447e+09 | 2.12655e+06 | 1.01701 | 1(Win) |
| glaze | 2689.6 | 1.40121 | 545.162ms | 6661897 | 30 | 3.28662e+10 | 2.36216e+06 | 1.12959 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1866.56 | 0.607324 | 65.656ms | 500299 | 30 | 7.23001e+07 | 255616 | 1.62802 | 1(Win) |
| glaze | 1812.3 | 0.410898 | 66.4131ms | 500299 | 30 | 3.51064e+07 | 263268 | 1.67678 | 2(Loss) |
| simdjson (ondemand) | 1124.46 | 0.840852 | 106.002ms | 500299 | 30 | 3.81884e+08 | 424312 | 2.702 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 5320.3 | 0.736077 | 22.8541ms | 500299 | 30 | 1.30724e+07 | 89679.6 | 0.570966 | 1(Tie) |
| jsonifier STATISTICAL TIE | 5187.75 | 2.13301 | 22.983ms | 500299 | 30 | 1.15454e+08 | 91971 | 0.585327 | 1(Tie) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 2751.93 | 1.47978 | 124.433ms | 1439562 | 30 | 1.63495e+09 | 498876 | 1.10395 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2740.33 | 2.33431 | 119.571ms | 1439562 | 30 | 4.10291e+09 | 500988 | 1.10875 | 1(Tie) |
| glaze STATISTICAL TIE | 2675.12 | 0.438011 | 300.912ms | 1439562 | 32 | 1.61694e+08 | 513201 | 1.13595 | 1(Tie) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6974.91 | 0.482786 | 48.6667ms | 1439562 | 30 | 2.70903e+07 | 196830 | 0.435477 | 1(Win) |
| glaze | 4633.72 | 1.50529 | 70.8465ms | 1439584 | 30 | 5.9673e+08 | 296284 | 0.655446 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1779.52 | 2.15868 | 7.91698ms | 56369 | 30 | 1.27577e+07 | 30209 | 1.70641 | 1(Tie) |
| glaze STATISTICAL TIE | 1742.61 | 0.680955 | 8.35664ms | 56369 | 30 | 1.32385e+06 | 30849 | 1.74255 | 1(Tie) |
| simdjson (ondemand) | 1283.25 | 1.38972 | 11.0744ms | 56369 | 30 | 1.0168e+07 | 41891.7 | 2.36643 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6541.75 | 0.125682 | 2.54017ms | 56369 | 30 | 3200.1 | 8217.63 | 0.46286 | 1(Win) |
| jsonifier | 5459.5 | 0.190841 | 2.85566ms | 56369 | 30 | 10593.6 | 9846.63 | 0.552674 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2363.16 | 0.987454 | 10.888ms | 94370 | 30 | 4.24266e+06 | 38083.9 | 1.28515 | 1(Win) |
| simdjson (ondemand) | 2041.54 | 0.603348 | 11.8421ms | 94370 | 30 | 2.12231e+06 | 44083.5 | 1.48774 | 2(Loss) |
| jsonifier | 1848.04 | 0.606301 | 12.5667ms | 94370 | 30 | 2.61543e+06 | 48699.3 | 1.64373 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6912.15 | 0.572028 | 3.51297ms | 94370 | 30 | 166417 | 13020.3 | 0.438688 | 1(Win) |
| glaze | 5519.3 | 0.288303 | 4.42661ms | 94370 | 30 | 66301 | 16306.1 | 0.549613 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1606.98 | 1.72016 | 8.0819ms | 52708 | 30 | 8.68547e+06 | 31280 | 1.88931 | 1(Win) |
| jsonifier | 1457.13 | 0.862912 | 46.3093ms | 52708 | 64 | 5.67116e+06 | 34496.8 | 2.08374 | 2(Loss) |
| glaze | 1307.03 | 1.31645 | 10.7429ms | 52708 | 30 | 7.68972e+06 | 38458.3 | 2.32324 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6831.98 | 0.540379 | 4.8702ms | 52708 | 32 | 50583.4 | 7357.5 | 0.443002 | 1(Win) |
| jsonifier | 6447.11 | 0.363088 | 5.32309ms | 52708 | 32 | 25644.7 | 7796.72 | 0.467 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2113.7 | 0.920391 | 8.42619ms | 70103 | 30 | 2.54245e+06 | 31629.6 | 1.43643 | 1(Win) |
| jsonifier STATISTICAL TIE | 1458.02 | 1.61754 | 12.9615ms | 70103 | 30 | 1.65036e+07 | 45853.6 | 2.08268 | 2(Tie) |
| glaze STATISTICAL TIE | 1413.95 | 1.51985 | 11.7948ms | 70103 | 30 | 1.54929e+07 | 47282.9 | 2.14798 | 2(Tie) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6289.06 | 2.15381 | 6.42035ms | 70103 | 32 | 1.67751e+06 | 10630.4 | 0.480159 | 1(Win) |
| glaze | 5307.14 | 2.44043 | 9.54506ms | 70103 | 32 | 3.02436e+06 | 12597.2 | 0.571167 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1519.39 | 0.0662872 | 2.21666ms | 11812 | 30 | 724.585 | 7414.03 | 1.99368 | 1(Win) |
| glaze | 1338.69 | 1.12303 | 2.43275ms | 11812 | 30 | 267909 | 8414.77 | 2.26309 | 2(Loss) |
| simdjson (ondemand) | 1093.49 | 0.198093 | 2.85823ms | 11812 | 30 | 12493.4 | 10301.7 | 2.77256 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5910.49 | 0.155064 | 0.768808ms | 11812 | 30 | 262.024 | 1905.9 | 0.502735 | 1(Win) |
| glaze | 3502.52 | 0.358399 | 1.09704ms | 11812 | 30 | 3986.03 | 3216.2 | 0.859798 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2735.6 | 0.201039 | 3.18038ms | 31235 | 30 | 14376.8 | 10889 | 1.10816 | 1(Win) |
| simdjson (ondemand) | 2550.06 | 2.1468 | 6.79422ms | 31235 | 32 | 2.0124e+06 | 11681.3 | 1.18913 | 2(Loss) |
| glaze | 2207.18 | 1.24434 | 4.27829ms | 31235 | 30 | 846074 | 13495.9 | 1.37432 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8344.45 | 0.097145 | 1.24382ms | 31235 | 30 | 360.786 | 3569.8 | 0.358062 | 1(Win) |
| glaze | 6640.27 | 0.169801 | 1.47312ms | 31235 | 30 | 1740.65 | 4485.97 | 0.454721 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3572.16 | 1.37414 | 7.6051ms | 108313 | 30 | 4.73675e+06 | 28916.7 | 0.849976 | 1(Win) |
| glaze | 2053.33 | 1.25168 | 12.3508ms | 108313 | 30 | 1.18947e+07 | 50306.3 | 1.4793 | 2(Loss) |
| simdjson (ondemand) | 1646.68 | 0.759845 | 36.971ms | 108313 | 32 | 7.27012e+06 | 62729.3 | 1.84473 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6376.09 | 0.141415 | 10.757ms | 108313 | 32 | 16795.5 | 16200.4 | 0.474567 | 1(Win) |
| glaze | 5270.56 | 2.04701 | 4.7162ms | 108313 | 30 | 4.82847e+06 | 19598.6 | 0.575419 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2940.13 | 0.690913 | 18.1867ms | 213963 | 30 | 6.89782e+06 | 69402 | 1.033 | 1(Win) |
| glaze | 2819.21 | 1.40924 | 17.9342ms | 213963 | 30 | 3.12113e+07 | 72378.7 | 1.07754 | 2(Loss) |
| jsonifier | 2236.42 | 1.39567 | 22.9774ms | 213963 | 30 | 4.86473e+07 | 91239.9 | 1.35836 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7936.79 | 2.19449 | 6.64642ms | 213963 | 30 | 9.54935e+06 | 25709.5 | 0.382151 | 1(Win) |
| glaze | 5601.31 | 0.869346 | 9.5455ms | 213963 | 30 | 3.00887e+06 | 36429.1 | 0.542097 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 774.862 | 0.760281 | 546.629ms | 1834197 | 30 | 8.83716e+09 | 2.25747e+06 | 3.92177 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 581.899 | 0.375593 | 737.165ms | 1834197 | 30 | 3.82432e+09 | 3.00606e+06 | 5.22196 | 2(Tie) |
| glaze STATISTICAL TIE | 580.403 | 1.12824 | 1707.44ms | 1834197 | 32 | 3.69986e+10 | 3.01381e+06 | 5.23568 | 2(Tie) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 978.38 | 1.07197 | 439.289ms | 1834197 | 30 | 1.10195e+10 | 1.78788e+06 | 3.10576 | 1(Win) |
| glaze | 858.844 | 1.2459 | 487.162ms | 1833577 | 30 | 1.93044e+10 | 2.03603e+06 | 3.53808 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2487.83 | 1.69393 | 947.403ms | 9930848 | 30 | 1.2475e+11 | 3.80684e+06 | 1.22144 | 1(Win) |
| glaze | 2293.53 | 0.852291 | 1001.89ms | 9930848 | 30 | 3.71589e+10 | 4.12936e+06 | 1.32492 | 2(Loss) |
| jsonifier | 2173.44 | 0.801907 | 1036.96ms | 9930848 | 30 | 3.66307e+10 | 4.35751e+06 | 1.39798 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2618.63 | 1.51255 | 895.232ms | 9930848 | 30 | 8.97772e+10 | 3.6167e+06 | 1.16035 | 1(Win) |
| glaze | 1912.81 | 1.47575 | 1189.77ms | 9930228 | 30 | 1.60148e+11 | 4.95094e+06 | 1.5884 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1321 | 2.4219 | 109.848ms | 642697 | 30 | 3.78823e+09 | 463983 | 2.29997 | 1(Win) |
| simdjson (ondemand) | 1171.77 | 0.573165 | 128.127ms | 642697 | 30 | 2.69656e+08 | 523076 | 2.59308 | 2(Loss) |
| glaze | 1027.65 | 0.980901 | 341.071ms | 642697 | 32 | 1.09528e+09 | 596435 | 2.95663 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1575.75 | 1.1138 | 93.9751ms | 642697 | 30 | 5.63089e+08 | 388973 | 1.928 | 1(Win) |
| glaze | 1391.47 | 1.52385 | 112.07ms | 642692 | 30 | 1.35164e+09 | 440482 | 2.18334 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2116.02 | 1.70694 | 137.339ms | 1225964 | 30 | 2.66854e+09 | 552532 | 1.43562 | 1(Win) |
| glaze STATISTICAL TIE | 1658.62 | 1.97057 | 173.239ms | 1225964 | 30 | 5.78854e+09 | 704906 | 1.83158 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1658.25 | 0.77139 | 172.129ms | 1225964 | 30 | 8.87412e+08 | 705063 | 1.83241 | 2(Tie) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2492.29 | 0.795931 | 118.857ms | 1225964 | 30 | 4.18246e+08 | 469116 | 1.21907 | 1(Win) |
| glaze | 2130.64 | 0.416304 | 141.75ms | 1225970 | 30 | 1.56561e+08 | 548744 | 1.4261 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1058.54 | 1.11795 | 219.448ms | 409725 | 32 | 5.4496e+08 | 369135 | 2.86994 | 1(Win) |
| simdjson (ondemand) | 970.985 | 0.485435 | 101.871ms | 409725 | 30 | 1.14484e+08 | 402420 | 3.12938 | 2(Loss) |
| glaze | 858.797 | 0.993038 | 110.395ms | 409725 | 30 | 6.12431e+08 | 454990 | 3.53777 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4422.1 | 1.83962 | 22.9953ms | 409725 | 30 | 7.92697e+07 | 88361.7 | 0.686836 | 1(Win) |
| glaze | 3578.14 | 1.50391 | 28.8512ms | 409725 | 30 | 8.09157e+07 | 109203 | 0.848888 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1681.03 | 1.5007 | 106.624ms | 785750 | 30 | 1.34254e+09 | 445767 | 1.80729 | 1(Win) |
| glaze | 1400.22 | 0.477422 | 312.839ms | 785750 | 32 | 2.08898e+08 | 535167 | 2.17029 | 2(Loss) |
| jsonifier | 1142.93 | 1.6741 | 162.107ms | 785750 | 30 | 3.61425e+09 | 655641 | 2.65865 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5388.33 | 0.451527 | 34.9089ms | 785750 | 30 | 1.1829e+07 | 139069 | 0.563725 | 1(Win) |
| glaze | 3801.63 | 1.67584 | 117.822ms | 785750 | 32 | 3.49177e+08 | 197113 | 0.799135 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1137.99 | 0.859559 | 1774.63ms | 8587914 | 30 | 1.14809e+11 | 7.197e+06 | 2.67041 | 1(Win) |
| glaze STATISTICAL TIE | 1056.56 | 0.963215 | 1923.17ms | 8587914 | 30 | 1.67247e+11 | 7.75166e+06 | 2.87628 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1041.17 | 1.56983 | 1927.39ms | 8587914 | 30 | 4.5747e+11 | 7.86625e+06 | 2.91875 | 2(Tie) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2607.92 | 2.17466 | 762.715ms | 8588126 | 30 | 1.39931e+11 | 3.14054e+06 | 1.16496 | 1(Win) |
| glaze | 2084.3 | 2.19675 | 913.158ms | 8588126 | 30 | 2.23541e+11 | 3.9295e+06 | 1.45763 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1121.39 | 1.43553 | 2013.18ms | 9804437 | 30 | 4.29813e+11 | 8.33809e+06 | 2.70995 | 1(Win) |
| glaze | 1073.21 | 1.16541 | 2102.49ms | 9804437 | 30 | 3.09285e+11 | 8.71244e+06 | 2.8316 | 2(Loss) |
| jsonifier | 1029.22 | 1.2601 | 2190.24ms | 9804437 | 30 | 3.9315e+11 | 9.08479e+06 | 2.95266 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2856.04 | 1.98824 | 1025.25ms | 11078090 | 30 | 1.62279e+11 | 3.69914e+06 | 1.06378 | 1(Win) |
| glaze | 2214.11 | 1.81947 | 1122.05ms | 11078090 | 30 | 2.26122e+11 | 4.77162e+06 | 1.37233 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5354.11 | 0.521955 | 12.7902ms | 264040 | 30 | 1.80781e+06 | 47030.8 | 0.56733 | 1(Win) |
| simdjson (ondemand) | 5201.65 | 0.275686 | 12.0486ms | 264040 | 30 | 534330 | 48409.3 | 0.583993 | 2(Loss) |
| glaze | 1956.41 | 1.02441 | 32.4623ms | 264040 | 30 | 5.21537e+07 | 128709 | 1.553 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6908.16 | 0.422532 | 34.1668ms | 399947 | 32 | 1.74161e+06 | 55212.8 | 0.439754 | 1(Win) |
| simdjson (ondemand) | 6593.35 | 0.832807 | 15.2629ms | 399947 | 30 | 6.96311e+06 | 57849.1 | 0.460586 | 2(Loss) |
| glaze | 2500.36 | 1.11928 | 37.6308ms | 399947 | 30 | 8.74576e+07 | 152546 | 1.21514 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1629.82 | 2.35656 | 38.4038ms | 264040 | 30 | 3.97685e+08 | 154501 | 1.86411 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1543.76 | 1.17531 | 207.377ms | 264040 | 64 | 2.35213e+08 | 163113 | 1.96815 | 2(Tie) |
| glaze STATISTICAL TIE | 1525.43 | 1.03254 | 97.0927ms | 264040 | 32 | 9.29652e+07 | 165073 | 1.99193 | 2(Tie) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6353.92 | 0.563947 | 52.4271ms | 263923 | 64 | 3.19395e+06 | 39612.8 | 0.477792 | 1(Win) |
| jsonifier | 5320.22 | 2.2062 | 11.2574ms | 264040 | 30 | 3.27108e+07 | 47330.4 | 0.57061 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2244.64 | 1.03055 | 104.094ms | 399947 | 32 | 9.8129e+07 | 169925 | 1.35364 | 1(Win) |
| glaze | 1801.66 | 1.40146 | 53.1969ms | 399947 | 30 | 2.64086e+08 | 211705 | 1.68616 | 2(Loss) |
| jsonifier | 1299.92 | 2.04711 | 356.947ms | 399947 | 64 | 2.30905e+09 | 293417 | 2.33742 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6608.38 | 1.02461 | 34.7644ms | 399947 | 32 | 1.11914e+07 | 57717.5 | 0.459404 | 1(Win) |
| glaze | 5347.64 | 1.65726 | 42.9049ms | 399830 | 32 | 4.46845e+07 | 71304 | 0.567943 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2316.34 | 1.17913 | 48.116ms | 466906 | 30 | 1.54134e+08 | 192233 | 1.31175 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2257.32 | 1.02083 | 51.5109ms | 466906 | 30 | 1.21647e+08 | 197259 | 1.34611 | 1(Tie) |
| simdjson (ondemand) | 1282.44 | 1.33498 | 204.466ms | 466906 | 32 | 6.87516e+08 | 347209 | 2.36909 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 3586.26 | 1.18553 | 45.7455ms | 699405 | 30 | 1.45854e+08 | 185989 | 0.847192 | 1(Tie) |
| jsonifier STATISTICAL TIE | 3583.78 | 0.747561 | 47.449ms | 699405 | 30 | 5.80752e+07 | 186118 | 0.847787 | 1(Tie) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3907.47 | 1.10291 | 92.1424ms | 631514 | 32 | 9.24704e+07 | 154130 | 0.777563 | 1(Win) |
| glaze | 2382.98 | 1.56549 | 59.7722ms | 631514 | 30 | 4.6962e+08 | 252734 | 1.27466 | 2(Loss) |
