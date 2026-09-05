# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36256.0 compiler).  

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

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 426.095 | 0.228555 | 2.7022ms | 1811 | 30 | 2574.71 | 4053.33 | 5.4245 | 1(Win) |
| glaze | 156.962 | 0.0686671 | 4.0487ms | 1811 | 30 | 1712.64 | 11003.3 | 14.7785 | 2(Loss) |
| simdjson (ondemand) | 95.5785 | 0.0757488 | 5.8287ms | 1811 | 30 | 5620.69 | 18070 | 24.3439 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 309.702 | 0.186062 | 2.8118ms | 1811 | 30 | 3229.89 | 5576.67 | 7.49796 | 1(Win) |
| glaze | 170.448 | 0.112785 | 3.8966ms | 1798 | 30 | 3862.07 | 10060 | 13.6103 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1028.85 | 0.155177 | 2.4939ms | 3873 | 30 | 931.034 | 3590 | 2.24085 | 1(Win) |
| glaze | 620.422 | 0.192841 | 2.7593ms | 3873 | 30 | 3954.02 | 5953.33 | 3.7272 | 2(Loss) |
| simdjson (ondemand) | 231.482 | 0.0792812 | 11.19ms | 3873 | 32 | 5120.97 | 15956.2 | 10.0516 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1689.14 | 0.362509 | 1.9997ms | 3873 | 30 | 1885.06 | 2186.67 | 1.35692 | 1(Win) |
| glaze | 464.967 | 0.508521 | 6.6006ms | 3873 | 32 | 52217.7 | 7943.75 | 4.98774 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1149.84 | 0.097561 | 4.3317ms | 3862 | 32 | 312.5 | 3203.12 | 2.00668 | 1(Win) |
| glaze | 511.54 | 0.133184 | 3.0944ms | 3862 | 30 | 2758.62 | 7200 | 4.5308 | 2(Loss) |
| simdjson (ondemand) | 235.391 | 0.0666679 | 5.171ms | 3862 | 30 | 3264.37 | 15646.7 | 9.89937 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1596.72 | 0.289017 | 1.9596ms | 3862 | 30 | 1333.33 | 2306.67 | 1.4354 | 1(Win) |
| glaze | 734.659 | 0.184789 | 2.6635ms | 3862 | 30 | 2574.71 | 5013.33 | 3.1474 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 779.887 | 0.60241 | 1.8319ms | 905 | 30 | 1333.33 | 1106.67 | 2.89576 | 1(Win) |
| glaze | 145.544 | 0.143501 | 2.7806ms | 905 | 30 | 2172.41 | 5930 | 15.8722 | 2(Loss) |
| simdjson (ondemand) | 66.957 | 0.204919 | 4.4792ms | 905 | 30 | 20931 | 12890 | 34.7214 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 393.499 | 0.211188 | 1.9462ms | 905 | 30 | 643.678 | 2193.33 | 5.85278 | 1(Win) |
| glaze | 127.485 | 0.144275 | 2.9926ms | 905 | 30 | 2862.07 | 6770 | 18.1769 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1454.51 | 0.160148 | 3.2059ms | 9578 | 30 | 3034.48 | 6280 | 1.59591 | 1(Win) |
| glaze | 863.899 | 0.256251 | 3.9861ms | 9578 | 30 | 22023 | 10573.3 | 2.68441 | 2(Loss) |
| simdjson (ondemand) | 369.622 | 0.0622818 | 16.1142ms | 9578 | 32 | 7580.65 | 24712.5 | 6.30006 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2420.75 | 0.252006 | 2.4167ms | 9578 | 30 | 2712.64 | 3773.33 | 0.955304 | 1(Win) |
| glaze | 1608.15 | 0.213549 | 2.7894ms | 9578 | 30 | 4413.79 | 5680 | 1.44089 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2356.61 | 0.993134 | 24.403ms | 233995 | 30 | 2.65324e+07 | 94693.3 | 0.989071 | 1(Win) |
| simdjson (ondemand) | 1453.43 | 1.01843 | 38.1946ms | 233995 | 30 | 7.33514e+07 | 153537 | 1.60405 | 2(Loss) |
| glaze | 1002.63 | 1.04843 | 55.7944ms | 233995 | 30 | 1.63357e+08 | 222570 | 2.32544 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3013.02 | 1.07887 | 28.1016ms | 346753 | 30 | 4.20626e+07 | 109753 | 0.773741 | 1(Win) |
| simdjson (ondemand) | 1896.66 | 0.825369 | 43.4731ms | 346753 | 30 | 6.21267e+07 | 174353 | 1.22925 | 2(Loss) |
| glaze | 1252.15 | 0.69585 | 66.0799ms | 346753 | 30 | 1.01316e+08 | 264097 | 1.86205 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 878.494 | 0.801045 | 64.1478ms | 233995 | 30 | 1.24214e+08 | 254020 | 2.65397 | 1(Win) |
| glaze | 640.25 | 1.53372 | 91.69ms | 233995 | 30 | 8.57291e+08 | 348543 | 3.64169 | 2(Loss) |
| simdjson (ondemand) | 433.586 | 0.415528 | 125.071ms | 233995 | 30 | 1.3721e+08 | 514673 | 5.37796 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1228.02 | 2.24629 | 225.994ms | 233995 | 64 | 1.06638e+09 | 181719 | 1.89834 | 1(Win) |
| glaze | 1125.58 | 1.66553 | 1134.01ms | 233995 | 256 | 2.79125e+09 | 198257 | 2.07107 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1021.68 | 0.656234 | 80.0052ms | 346753 | 30 | 1.35348e+08 | 323673 | 2.28221 | 1(Win) |
| glaze | 867.246 | 1.01849 | 93.4749ms | 346753 | 30 | 4.52473e+08 | 381310 | 2.68871 | 2(Loss) |
| simdjson (ondemand) | 611.844 | 0.456993 | 130.84ms | 346753 | 30 | 1.8302e+08 | 540480 | 3.81116 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1815.88 | 1.56191 | 44.9625ms | 346753 | 30 | 2.42718e+08 | 182110 | 1.28372 | 1(Win) |
| glaze | 1042.32 | 2.22889 | 769.615ms | 346753 | 128 | 6.40068e+09 | 317262 | 2.23679 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2270.5 | 1.55383 | 58.7413ms | 233995 | 32 | 7.46317e+07 | 98284.4 | 1.02623 | 1(Win) |
| glaze | 1030.6 | 0.72723 | 53.8116ms | 233995 | 30 | 7.43877e+07 | 216530 | 2.26233 | 2(Loss) |
| simdjson (ondemand) | 986.698 | 0.888266 | 55.5311ms | 233995 | 30 | 1.21074e+08 | 226163 | 2.36307 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2921.2 | 1.11151 | 28.7287ms | 346753 | 30 | 4.74969e+07 | 113203 | 0.797966 | 1(Win) |
| simdjson (ondemand) | 1319.27 | 0.883354 | 61.3539ms | 346753 | 30 | 1.47082e+08 | 250660 | 1.76719 | 2(Loss) |
| glaze | 1264.6 | 0.840492 | 63.9609ms | 346753 | 30 | 1.44918e+08 | 261497 | 1.84382 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 824.525 | 0.935274 | 66.8002ms | 233995 | 30 | 1.92223e+08 | 270647 | 2.82775 | 1(Win) |
| glaze | 710.783 | 0.851452 | 77.4164ms | 233995 | 30 | 2.14378e+08 | 313957 | 3.28041 | 2(Loss) |
| simdjson (ondemand) | 108.313 | 0.131606 | 496.842ms | 233995 | 30 | 2.20558e+08 | 2.06027e+06 | 21.5301 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1494.51 | 1.98169 | 37.0384ms | 233995 | 30 | 2.62668e+08 | 149317 | 1.55968 | 1(Win) |
| glaze | 1154.86 | 2.46577 | 241.248ms | 233995 | 64 | 1.45292e+09 | 193231 | 2.01849 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 953.261 | 2.02934 | 86.078ms | 346753 | 30 | 1.48679e+09 | 346903 | 2.44598 | 1(Win) |
| glaze | 863.554 | 0.625491 | 106.229ms | 346753 | 30 | 1.72118e+08 | 382940 | 2.69998 | 2(Loss) |
| simdjson (ondemand) | 157.733 | 0.26185 | 505.275ms | 346753 | 30 | 9.04112e+08 | 2.09652e+06 | 14.7843 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1987.52 | 1.34819 | 41.3618ms | 346753 | 30 | 1.50955e+08 | 166383 | 1.17279 | 1(Win) |
| glaze | 1060.5 | 2.12282 | 777.91ms | 346753 | 128 | 5.60863e+09 | 311824 | 2.19846 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 424.336 | 2.45574 | 53.4612ms | 94651 | 30 | 8.18682e+08 | 212723 | 5.49399 | 1(Win) |
| glaze | 368.192 | 2.17954 | 300.367ms | 94651 | 64 | 1.8273e+09 | 245161 | 6.33236 | 2(Loss) |
| simdjson (ondemand) | 322.927 | 1.99196 | 341.478ms | 94651 | 64 | 1.98419e+09 | 279525 | 7.2198 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1678.12 | 2.21407 | 15.0626ms | 94651 | 30 | 4.25506e+07 | 53790 | 1.38772 | 1(Win) |
| jsonifier | 1514.79 | 1.29901 | 15.9644ms | 94651 | 30 | 1.79761e+07 | 59590 | 1.53801 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 541.85 | 1.18261 | 59.0646ms | 136024 | 30 | 2.40478e+08 | 239407 | 4.30259 | 1(Win) |
| glaze | 511.534 | 1.76101 | 325.7ms | 136024 | 64 | 1.2764e+09 | 253595 | 4.55764 | 2(Loss) |
| simdjson (ondemand) | 465.139 | 1.49054 | 68.358ms | 136024 | 30 | 5.18413e+08 | 278890 | 5.01186 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1948.57 | 1.58664 | 17.3076ms | 136024 | 30 | 3.34717e+07 | 66573.3 | 1.19521 | 1(Win) |
| glaze | 1305.44 | 1.24893 | 25.5152ms | 136046 | 30 | 4.62226e+07 | 99386.7 | 1.78573 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 326.065 | 1.19185 | 1540.94ms | 2090234 | 30 | 1.59274e+11 | 6.11351e+06 | 7.15205 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 205.707 | 0.603764 | 2340.35ms | 2090234 | 30 | 1.02695e+11 | 9.69051e+06 | 11.3369 | 2(Tie) |
| glaze STATISTICAL TIE | 201.419 | 1.85816 | 2307.91ms | 2090234 | 30 | 1.01456e+12 | 9.89678e+06 | 11.5781 | 2(Tie) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 548.943 | 0.086891 | 874.427ms | 2090234 | 30 | 2.9868e+08 | 3.63135e+06 | 4.24823 | 1(Win) |
| glaze | 457.253 | 0.131786 | 1052.8ms | 2090234 | 30 | 9.90234e+08 | 4.35951e+06 | 5.09996 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 905.915 | 1.01661 | 1678.27ms | 6661897 | 30 | 1.52494e+11 | 7.01311e+06 | 2.57421 | 1(Win) |
| simdjson (ondemand) | 586.59 | 0.517504 | 2589.2ms | 6661897 | 30 | 9.42486e+10 | 1.08309e+07 | 3.97555 | 2(Loss) |
| glaze | 573.961 | 0.67656 | 2687.12ms | 6661897 | 30 | 1.68254e+11 | 1.10692e+07 | 4.06302 | 3(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 741.637 | 0.455811 | 156.712ms | 500299 | 30 | 2.57969e+08 | 643337 | 3.14415 | 1(Win) |
| glaze | 461.453 | 0.355697 | 250.64ms | 500299 | 30 | 4.05775e+08 | 1.03396e+06 | 5.05352 | 2(Loss) |
| simdjson (ondemand) | 268.04 | 0.0951622 | 431.612ms | 500299 | 30 | 8.60819e+07 | 1.78004e+06 | 8.7003 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1745.44 | 0.619397 | 67.5556ms | 500299 | 30 | 8.60019e+07 | 273353 | 1.33577 | 1(Win) |
| glaze | 1290.18 | 0.532623 | 91.5308ms | 500299 | 30 | 1.16391e+08 | 369810 | 1.80727 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1486.35 | 0.628643 | 223.005ms | 1439562 | 30 | 1.01146e+09 | 923653 | 1.56887 | 1(Win) |
| glaze | 959.62 | 1.26402 | 335.03ms | 1439562 | 30 | 9.81053e+09 | 1.43064e+06 | 2.43004 | 2(Loss) |
| simdjson (ondemand) | 701.308 | 0.163257 | 470.152ms | 1439562 | 30 | 3.06415e+08 | 1.95759e+06 | 3.32522 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1880.57 | 0.567607 | 177.21ms | 1439562 | 30 | 5.15107e+08 | 730030 | 1.23985 | 1(Win) |
| glaze | 849.805 | 0.631453 | 386.957ms | 1439584 | 30 | 3.12204e+09 | 1.61554e+06 | 2.74393 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 679.531 | 1.70795 | 20.9438ms | 56369 | 30 | 5.47692e+07 | 79110 | 3.42853 | 1(Win) |
| glaze | 599.974 | 1.55766 | 22.8978ms | 56369 | 30 | 5.84366e+07 | 89600 | 3.88417 | 2(Loss) |
| simdjson (ondemand) | 289.783 | 0.877088 | 46.2433ms | 56369 | 30 | 7.94223e+07 | 185510 | 8.04614 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1493.55 | 0.438363 | 10.1072ms | 56369 | 30 | 746851 | 35993.3 | 1.55885 | 1(Win) |
| glaze | 1229.12 | 1.9891 | 11.9719ms | 56369 | 30 | 2.27052e+07 | 43736.7 | 1.89559 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 887.382 | 1.46975 | 25.9855ms | 94370 | 30 | 6.66582e+07 | 101420 | 2.62671 | 1(Win) |
| jsonifier | 810.892 | 1.62364 | 28.7797ms | 94370 | 30 | 9.74191e+07 | 110987 | 2.87344 | 2(Loss) |
| simdjson (ondemand) | 469.067 | 0.897976 | 47.6233ms | 94370 | 30 | 8.90533e+07 | 191867 | 4.97024 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2262.4 | 0.631874 | 11.0298ms | 94370 | 30 | 1.89545e+06 | 39780 | 1.0285 | 1(Win) |
| glaze | 1148.96 | 1.16523 | 20.3897ms | 94370 | 30 | 2.49918e+07 | 78330 | 2.02815 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 577.53 | 1.54689 | 23.6069ms | 52708 | 30 | 5.4381e+07 | 87036.7 | 4.03478 | 1(Win) |
| glaze | 486.432 | 2.07591 | 26.8067ms | 52708 | 30 | 1.38053e+08 | 103337 | 4.79224 | 2(Loss) |
| simdjson (ondemand) | 421.956 | 1.46237 | 30.1732ms | 52708 | 30 | 9.10441e+07 | 119127 | 5.52338 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2319.62 | 0.39465 | 6.656ms | 52708 | 30 | 219414 | 21670 | 1.00271 | 1(Win) |
| glaze | 1922.46 | 0.387429 | 17.1076ms | 52708 | 32 | 328377 | 26146.9 | 1.21016 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 600.822 | 1.41888 | 28.6439ms | 70103 | 30 | 7.4782e+07 | 111273 | 3.8785 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 543.305 | 0.952559 | 31.4248ms | 70103 | 30 | 4.12184e+07 | 123053 | 4.2896 | 2(Tie) |
| jsonifier STATISTICAL TIE | 526.926 | 2.27511 | 74.7236ms | 70103 | 32 | 2.66642e+08 | 126878 | 4.41731 | 2(Tie) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2873.85 | 0.426131 | 7.0832ms | 70103 | 30 | 294816 | 23263.3 | 0.809629 | 1(Win) |
| glaze | 1671.11 | 2.49423 | 11.0147ms | 70103 | 30 | 2.98717e+07 | 40006.7 | 1.39346 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 571.721 | 0.0454165 | 6.4419ms | 11812 | 30 | 2402.3 | 19703.3 | 4.07199 | 1(Win) |
| glaze | 379.806 | 1.47715 | 38.6009ms | 11812 | 64 | 1.22844e+07 | 29659.4 | 6.133 | 2(Loss) |
| simdjson (ondemand) | 253.217 | 0.116446 | 12.3822ms | 11812 | 30 | 80505.7 | 44486.7 | 9.20278 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1131.76 | 0.522681 | 3.8056ms | 11812 | 30 | 81195.4 | 9953.33 | 2.0537 | 1(Win) |
| glaze | 922.336 | 0.27685 | 4.3552ms | 11812 | 30 | 34298.9 | 12213.3 | 2.52067 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1154.85 | 0.110011 | 17.0095ms | 31235 | 32 | 25766.1 | 25793.8 | 2.0173 | 1(Win) |
| glaze | 780.2 | 2.03262 | 10.5986ms | 31235 | 30 | 1.80679e+07 | 38180 | 2.9867 | 2(Loss) |
| simdjson (ondemand) | 611.413 | 1.9473 | 13.1443ms | 31235 | 30 | 2.70023e+07 | 48720 | 3.81113 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2559.84 | 0.274806 | 4.2131ms | 31235 | 30 | 30678.2 | 11636.7 | 0.908336 | 1(Win) |
| glaze | 1372.93 | 0.315229 | 6.6575ms | 31235 | 30 | 140333 | 21696.7 | 1.69582 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1245.67 | 2.01064 | 21.7345ms | 108313 | 30 | 8.33956e+07 | 82923.3 | 1.87113 | 1(Win) |
| glaze | 551.389 | 1.46346 | 46.8879ms | 108313 | 30 | 2.25489e+08 | 187337 | 4.22812 | 2(Loss) |
| simdjson (ondemand) | 327.153 | 0.821124 | 77.1193ms | 108313 | 30 | 2.0165e+08 | 315740 | 7.1269 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1704.54 | 1.35652 | 16.0031ms | 108313 | 30 | 2.02731e+07 | 60600 | 1.36694 | 1(Win) |
| glaze | 1298.71 | 1.11536 | 20.6062ms | 108313 | 30 | 2.36093e+07 | 79536.7 | 1.79458 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1221.52 | 1.29142 | 42.2684ms | 213963 | 30 | 1.39614e+08 | 167047 | 1.90871 | 1(Win) |
| glaze | 854.58 | 1.05134 | 60.4211ms | 213963 | 30 | 1.8905e+08 | 238773 | 2.72826 | 2(Loss) |
| simdjson (ondemand) | 615.31 | 0.61947 | 81.3435ms | 213963 | 30 | 1.26605e+08 | 331623 | 3.78921 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2631.11 | 1.27691 | 20.0805ms | 213963 | 30 | 2.94198e+07 | 77553.3 | 0.885641 | 1(Win) |
| glaze | 1288.82 | 0.792792 | 39.6831ms | 213963 | 30 | 4.72639e+07 | 158323 | 1.80878 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 357.301 | 0.121362 | 1207.23ms | 1834197 | 30 | 1.05903e+09 | 4.89566e+06 | 6.52667 | 1(Win) |
| glaze STATISTICAL TIE | 175.565 | 0.549766 | 2422.48ms | 1834197 | 30 | 9.0011e+10 | 9.96343e+06 | 13.2829 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 172.852 | 0.587902 | 2517.66ms | 1834197 | 30 | 1.06187e+11 | 1.01198e+07 | 13.4911 | 2(Tie) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 333.94 | 0.152784 | 1261.24ms | 1834197 | 30 | 1.92145e+09 | 5.23815e+06 | 6.9833 | 1(Win) |
| glaze | 271.044 | 0.29661 | 1551.67ms | 1833577 | 30 | 1.09853e+10 | 6.45148e+06 | 8.60379 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1418.09 | 0.207055 | 1621.39ms | 9930848 | 30 | 5.73667e+09 | 6.67857e+06 | 1.64438 | 1(Win) |
| glaze STATISTICAL TIE | 808.643 | 0.471338 | 2813.25ms | 9930848 | 30 | 9.14206e+10 | 1.1712e+07 | 2.88382 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 801.972 | 0.418082 | 2825.58ms | 9930848 | 30 | 7.31304e+10 | 1.18094e+07 | 2.90774 | 2(Tie) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1099.77 | 1.79397 | 10890.3ms | 9930848 | 64 | 1.52748e+12 | 8.61159e+06 | 2.12034 | 1(Win) |
| glaze | 604.772 | 0.890293 | 3722.98ms | 9930228 | 30 | 5.83073e+11 | 1.56591e+07 | 3.8559 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 682.318 | 0.364344 | 218.601ms | 642697 | 30 | 3.21355e+08 | 898297 | 3.41771 | 1(Win) |
| glaze | 437.812 | 0.236474 | 339.046ms | 642697 | 30 | 3.28795e+08 | 1.39997e+06 | 5.32651 | 2(Loss) |
| simdjson (ondemand) | 427.368 | 0.203782 | 347.381ms | 642697 | 30 | 2.56248e+08 | 1.43418e+06 | 5.45657 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 653.897 | 0.2736 | 226.66ms | 642697 | 30 | 1.97309e+08 | 937340 | 3.56621 | 1(Win) |
| glaze | 384.196 | 0.31241 | 385.325ms | 642692 | 30 | 7.45197e+08 | 1.59533e+06 | 6.0694 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1059.37 | 0.338153 | 274.95ms | 1225964 | 30 | 4.17836e+08 | 1.10364e+06 | 2.20127 | 1(Win) |
| simdjson (ondemand) | 763.103 | 0.245517 | 369.566ms | 1225964 | 30 | 4.24497e+08 | 1.53213e+06 | 3.05583 | 2(Loss) |
| glaze | 725.808 | 0.162764 | 388.54ms | 1225964 | 30 | 2.06228e+08 | 1.61085e+06 | 3.213 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 810.955 | 0.387826 | 346.373ms | 1225964 | 30 | 9.37899e+08 | 1.44172e+06 | 2.87534 | 1(Win) |
| glaze | 669.769 | 0.25409 | 418.751ms | 1225970 | 30 | 5.90209e+08 | 1.74564e+06 | 3.48153 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 459.258 | 0.337224 | 224.968ms | 409725 | 30 | 2.46962e+08 | 850817 | 5.07762 | 1(Win) |
| glaze | 298.556 | 0.203737 | 315.856ms | 409725 | 30 | 2.13302e+08 | 1.30878e+06 | 7.81064 | 2(Loss) |
| simdjson (ondemand) | 256.552 | 0.298457 | 365.652ms | 409725 | 30 | 6.19898e+08 | 1.52306e+06 | 9.08957 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1045.15 | 0.87166 | 92.7371ms | 409725 | 30 | 3.18597e+08 | 373863 | 2.23082 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1029.7 | 0.37436 | 93.3235ms | 409725 | 30 | 6.05427e+07 | 379473 | 2.2645 | 1(Tie) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 668.567 | 0.278214 | 273.303ms | 785750 | 30 | 2.91715e+08 | 1.12083e+06 | 3.48802 | 1(Win) |
| glaze | 506.943 | 0.332485 | 357.277ms | 785750 | 30 | 7.24631e+08 | 1.47817e+06 | 4.60001 | 2(Loss) |
| simdjson (ondemand) | 470.498 | 0.256904 | 380.812ms | 785750 | 30 | 5.02244e+08 | 1.59267e+06 | 4.9564 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1822.98 | 0.563685 | 100.492ms | 785750 | 30 | 1.61064e+08 | 411057 | 1.279 | 1(Win) |
| glaze | 823.108 | 0.472605 | 220.351ms | 785750 | 30 | 5.55357e+08 | 910390 | 2.83277 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 494.569 | 0.852619 | 4521.65ms | 8587914 | 30 | 5.98071e+11 | 1.656e+07 | 4.71516 | 1(Win) |
| glaze STATISTICAL TIE | 345.437 | 0.88651 | 5910.09ms | 8587914 | 30 | 1.32534e+12 | 2.37093e+07 | 6.75098 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 340.382 | 0.759127 | 5815.54ms | 8587914 | 30 | 1.0009e+12 | 2.40614e+07 | 6.85115 | 2(Tie) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1277.83 | 0.838609 | 1615.43ms | 8588126 | 30 | 8.66738e+10 | 6.4095e+06 | 1.82495 | 1(Win) |
| glaze | 676.668 | 0.11664 | 2934.16ms | 8588126 | 30 | 5.9795e+09 | 1.21038e+07 | 3.4462 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 439.157 | 0.46857 | 5125.09ms | 9804437 | 30 | 2.98591e+11 | 2.12913e+07 | 5.31018 | 1(Win) |
| simdjson (ondemand) | 366.443 | 0.9253 | 6085.82ms | 9804437 | 30 | 1.67232e+12 | 2.55162e+07 | 6.36383 | 2(Loss) |
| glaze | 353.865 | 0.822517 | 6245.33ms | 9804437 | 30 | 1.41703e+12 | 2.64232e+07 | 6.5901 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1263.67 | 0.783736 | 2147.09ms | 11078090 | 30 | 1.28803e+11 | 8.36049e+06 | 1.84535 | 1(Win) |
| glaze | 703.383 | 0.456368 | 3637.25ms | 11078090 | 30 | 1.40961e+11 | 1.50201e+07 | 3.3153 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2022.1 | 0.673307 | 84.3237ms | 264040 | 32 | 2.24963e+07 | 124528 | 1.15251 | 1(Win) |
| simdjson (ondemand) | 1340.31 | 2.3857 | 46.9538ms | 264040 | 30 | 6.02676e+08 | 187873 | 1.73934 | 2(Loss) |
| glaze | 686.7 | 2.31629 | 88.6202ms | 264040 | 30 | 2.16428e+09 | 366693 | 3.39539 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2701.01 | 1.27082 | 35.5015ms | 399947 | 30 | 9.66143e+07 | 141213 | 0.862759 | 1(Win) |
| simdjson (ondemand) | 1754.3 | 2.49724 | 52.9201ms | 399947 | 30 | 8.84386e+08 | 217420 | 1.329 | 2(Loss) |
| glaze | 971.026 | 2.13548 | 93.1124ms | 399947 | 30 | 2.11085e+09 | 392800 | 2.40128 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 731.901 | 1.70188 | 209.138ms | 264040 | 32 | 1.09709e+09 | 344047 | 3.18541 | 1(Win) |
| glaze | 486.567 | 0.703246 | 126.115ms | 264040 | 30 | 3.97365e+08 | 517520 | 4.79193 | 2(Loss) |
| simdjson (ondemand) | 409.391 | 0.850877 | 148.548ms | 264040 | 30 | 8.21709e+08 | 615080 | 5.69554 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2123.71 | 0.772277 | 30.2836ms | 264040 | 30 | 2.51546e+07 | 118570 | 1.09773 | 1(Win) |
| glaze | 1581.21 | 1.29462 | 39.8017ms | 263923 | 30 | 1.27404e+08 | 159180 | 1.47424 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 754.693 | 0.933167 | 123.342ms | 399947 | 30 | 6.67275e+08 | 505397 | 3.08928 | 1(Win) |
| glaze | 655.836 | 0.573288 | 142.832ms | 399947 | 30 | 3.33488e+08 | 581577 | 3.55528 | 2(Loss) |
| simdjson (ondemand) | 604.465 | 0.508667 | 153.489ms | 399947 | 30 | 3.09067e+08 | 631003 | 3.85767 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2780.5 | 1.22959 | 34.5018ms | 399947 | 30 | 8.53494e+07 | 137177 | 0.838358 | 1(Win) |
| glaze | 1501.13 | 0.834814 | 62.5833ms | 399830 | 30 | 1.34901e+08 | 254013 | 1.55319 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1151.74 | 0.504343 | 94.3552ms | 466906 | 30 | 1.14058e+08 | 386613 | 2.02448 | 1(Win) |
| glaze | 940.632 | 0.56997 | 114.678ms | 466906 | 30 | 2.18396e+08 | 473380 | 2.47887 | 2(Loss) |
| simdjson (ondemand) | 534.963 | 0.425882 | 201.765ms | 466906 | 30 | 3.76975e+08 | 832350 | 4.35902 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1631.22 | 0.56528 | 100.019ms | 699405 | 30 | 1.60281e+08 | 408900 | 1.42935 | 1(Win) |
| glaze | 1126.39 | 0.611695 | 143.562ms | 699405 | 30 | 3.93617e+08 | 592163 | 2.0701 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1760.61 | 1.81352 | 82.4049ms | 631514 | 30 | 1.15453e+09 | 342073 | 1.32427 | 1(Win) |
| glaze | 1358.17 | 0.542244 | 107.994ms | 631514 | 30 | 1.73447e+08 | 443433 | 1.7169 | 2(Loss) |
