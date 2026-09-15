# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 15, 2026)
#### Using the following commits:
----
| Jsonifier: [d6b5beb](https://github.com/nihilai-collective/jsonifier/commit/d6b5beb)  
| Glaze: [2518e75](https://github.com/stephenberry/glaze/commit/2518e75)  
| Simdjson: [9572dd0](https://github.com/simdjson/simdjson/commit/9572dd0)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX512` |
| simdjson (ondemand) | `icelake` |
| Glaze (utf8-validation) | `AVX512BW` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (AMD EPYC 9V74 80-Core Processor-AVX512): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.500000% AND mean shift < 1.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [43ba991](https://github.com/realtimechris/benchmarksuite/commit/43ba991).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 834.296 | 0.0527508 | 1.54423ms | 1811 | 30 | 35.7747 | 2070.13 | 2.92398 | 1(Win) |
| glaze | 581.295 | 0.0711462 | 0.850091ms | 1811 | 30 | 134.051 | 2971.13 | 4.21465 | 2(Loss) |
| simdjson (ondemand) | 132.143 | 0.0585642 | 3.32516ms | 1811 | 30 | 1757.65 | 13069.9 | 18.6934 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 378.541 | 0.584753 | 1.29109ms | 1811 | 30 | 21354 | 4562.53 | 6.48631 | 1(Win) |
| glaze | 342.357 | 1.5525 | 1.31718ms | 1798 | 30 | 181387 | 5008.53 | 7.18396 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1404.94 | 0.0515834 | 0.824342ms | 3873 | 30 | 55.1724 | 2629 | 1.74271 | 1(Win) |
| glaze | 1257.42 | 0.0612841 | 0.829359ms | 3873 | 30 | 97.2195 | 2937.43 | 1.94972 | 2(Loss) |
| simdjson (ondemand) | 304.511 | 2.3568 | 2.99076ms | 3873 | 30 | 2.45165e+06 | 12129.6 | 8.11103 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2078.98 | 0.0589708 | 0.600314ms | 3873 | 30 | 32.9299 | 1776.63 | 1.17099 | 1(Win) |
| glaze | 981.813 | 0.65188 | 1.05808ms | 3873 | 30 | 18042.4 | 3762 | 2.50109 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1427.26 | 0.101116 | 0.782509ms | 3862 | 30 | 204.257 | 2580.53 | 1.71515 | 1(Win) |
| glaze | 1114.62 | 0.0839124 | 0.916691ms | 3862 | 30 | 230.644 | 3304.33 | 2.20144 | 2(Loss) |
| simdjson (ondemand) | 295.354 | 1.8049 | 3.107ms | 3862 | 30 | 1.51973e+06 | 12470.1 | 8.36281 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2051.56 | 0.0659039 | 0.597129ms | 3862 | 30 | 41.9954 | 1795.27 | 1.18397 | 1(Win) |
| glaze | 1073.53 | 0.432286 | 1.01554ms | 3862 | 30 | 6598.76 | 3430.83 | 2.28515 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1090.8 | 0.1216 | 0.344609ms | 905 | 30 | 27.7713 | 791.233 | 2.18722 | 1(Win) |
| glaze | 645.712 | 0.692121 | 0.966796ms | 905 | 32 | 2738.63 | 1336.62 | 3.74917 | 2(Loss) |
| simdjson (ondemand) | 91.039 | 2.47083 | 5.35488ms | 905 | 32 | 1.75581e+06 | 9480.28 | 27.1132 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 963.612 | 0.104123 | 0.390758ms | 905 | 30 | 26.092 | 895.667 | 2.48597 | 1(Win) |
| glaze | 324.871 | 0.591355 | 0.756369ms | 905 | 30 | 7404.44 | 2656.67 | 7.5347 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1907.19 | 0.0478119 | 2.91564ms | 9578 | 32 | 167.797 | 4789.41 | 1.29009 | 1(Win) |
| jsonifier | 1397.14 | 0.218184 | 1.7942ms | 9578 | 30 | 6104.28 | 6537.83 | 1.76111 | 2(Loss) |
| simdjson (ondemand) | 672.046 | 1.81213 | 3.40172ms | 9578 | 30 | 1.81991e+06 | 13591.8 | 3.67496 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3939.18 | 0.0846766 | 0.760145ms | 9578 | 30 | 115.661 | 2318.83 | 0.620631 | 1(Win) |
| glaze | 2196.83 | 0.417662 | 1.14277ms | 9578 | 30 | 9047.44 | 4157.93 | 1.11903 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 3986.93 | 0.547374 | 13.5029ms | 233995 | 30 | 2.81596e+06 | 55971.7 | 0.620535 | 1(Tie) |
| jsonifier STATISTICAL TIE | 3980.24 | 0.647941 | 13.7013ms | 233995 | 30 | 3.95902e+06 | 56065.7 | 0.621691 | 1(Tie) |
| glaze | 1737.1 | 0.423258 | 31.1447ms | 233995 | 30 | 8.8694e+06 | 128464 | 1.42469 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 5107.68 | 0.614903 | 15.6891ms | 346753 | 30 | 4.75475e+06 | 64743.6 | 0.484422 | 1(Win) |
| jsonifier | 4979.36 | 0.55983 | 16.1649ms | 346753 | 30 | 4.14693e+06 | 66412 | 0.496989 | 2(Loss) |
| glaze | 2187.85 | 0.931695 | 36.6484ms | 346753 | 30 | 5.94943e+07 | 151148 | 1.13134 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1516.48 | 0.608619 | 36.1136ms | 233995 | 30 | 2.40631e+07 | 147153 | 1.63216 | 1(Tie) |
| glaze STATISTICAL TIE | 1506.1 | 1.6036 | 35.927ms | 233995 | 30 | 1.69363e+08 | 148167 | 1.64349 | 1(Tie) |
| jsonifier | 1272.68 | 0.3575 | 42.9211ms | 233995 | 30 | 1.17882e+07 | 175343 | 1.94493 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3132.1 | 1.38656 | 17.1767ms | 233995 | 30 | 2.92781e+07 | 71247.7 | 0.789987 | 1(Win) |
| glaze | 2773.56 | 0.686511 | 19.4631ms | 233995 | 30 | 9.15282e+06 | 80458.1 | 0.892138 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2052.62 | 0.672649 | 39.5073ms | 346753 | 30 | 3.52306e+07 | 161106 | 1.20571 | 1(Win) |
| glaze | 1652.94 | 0.709275 | 49.0616ms | 346753 | 30 | 6.04058e+07 | 200062 | 1.49755 | 2(Loss) |
| jsonifier | 1335.58 | 0.335205 | 60.5777ms | 346753 | 30 | 2.06655e+07 | 247600 | 1.85331 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3192.32 | 0.705281 | 25.1164ms | 346753 | 30 | 1.6013e+07 | 103589 | 0.775222 | 1(Win) |
| glaze | 2716.52 | 0.438284 | 29.7703ms | 346753 | 30 | 8.5398e+06 | 121733 | 0.910921 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3907.59 | 0.487521 | 13.9922ms | 233995 | 30 | 2.32542e+06 | 57108 | 0.63321 | 1(Win) |
| simdjson (ondemand) | 2540.65 | 0.505696 | 21.362ms | 233995 | 30 | 5.9187e+06 | 87834 | 0.97408 | 2(Loss) |
| glaze | 1740.86 | 0.464294 | 31.0901ms | 233995 | 30 | 1.06266e+07 | 128187 | 1.42182 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4911.47 | 0.525356 | 16.4351ms | 346753 | 30 | 3.75359e+06 | 67330.1 | 0.503837 | 1(Win) |
| simdjson (ondemand) | 3420.72 | 0.442485 | 23.4288ms | 346753 | 30 | 5.48938e+06 | 96672.4 | 0.723542 | 2(Loss) |
| glaze | 2198.44 | 0.351283 | 36.6114ms | 346753 | 30 | 8.37617e+06 | 150420 | 1.12591 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1665.42 | 1.76862 | 32.3163ms | 233995 | 30 | 1.68483e+08 | 133993 | 1.48624 | 1(Win) |
| jsonifier | 1234.23 | 0.32949 | 44.2765ms | 233995 | 30 | 1.06469e+07 | 180805 | 2.00554 | 2(Loss) |
| simdjson (ondemand) | 236.293 | 0.0774298 | 227.543ms | 233995 | 30 | 1.60417e+07 | 944401 | 10.4772 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3384.64 | 0.530453 | 16.2337ms | 233995 | 30 | 3.66947e+06 | 65931.7 | 0.731027 | 1(Win) |
| glaze | 2776.57 | 0.45135 | 19.5746ms | 233995 | 30 | 3.9477e+06 | 80370.7 | 0.89116 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2049.29 | 0.350197 | 40.7524ms | 346753 | 30 | 9.5803e+06 | 161368 | 1.20781 | 1(Win) |
| jsonifier | 1310.17 | 0.272211 | 61.2735ms | 346753 | 30 | 1.41618e+07 | 252402 | 1.88931 | 2(Loss) |
| simdjson (ondemand) | 346.113 | 0.0733457 | 229.354ms | 346753 | 30 | 1.47325e+07 | 955438 | 7.15261 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3748.94 | 0.828625 | 21.4235ms | 346753 | 30 | 1.60273e+07 | 88208.8 | 0.660128 | 1(Win) |
| glaze | 2815.81 | 0.548523 | 28.6243ms | 346753 | 30 | 1.24493e+07 | 117440 | 0.878833 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 959.956 | 0.490176 | 22.8941ms | 94651 | 30 | 6.37344e+06 | 94031.6 | 2.57812 | 1(Win) |
| glaze | 860.048 | 0.576624 | 25.1926ms | 94651 | 30 | 1.09878e+07 | 104955 | 2.87786 | 2(Loss) |
| jsonifier | 592.893 | 0.355043 | 37.1776ms | 94651 | 30 | 8.76557e+06 | 152247 | 4.17472 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4179.39 | 1.64713 | 5.31724ms | 94651 | 30 | 3.79666e+06 | 21597.9 | 0.591588 | 1(Win) |
| glaze | 3889.7 | 0.0509914 | 5.82729ms | 94651 | 30 | 4200.81 | 23206.5 | 0.635512 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1315.88 | 0.549296 | 24.0285ms | 136024 | 30 | 8.79694e+06 | 98582.2 | 1.88086 | 1(Win) |
| glaze | 1157.35 | 0.665942 | 27.8207ms | 136024 | 30 | 1.67146e+07 | 112086 | 2.13857 | 2(Loss) |
| jsonifier | 738.21 | 0.317812 | 42.5749ms | 136024 | 30 | 9.35694e+06 | 175726 | 3.35302 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4618.82 | 0.802084 | 6.97959ms | 136024 | 30 | 1.5224e+06 | 28085.6 | 0.535461 | 1(Win) |
| glaze | 3480.42 | 0.812003 | 9.08421ms | 136046 | 30 | 2.74881e+06 | 37278.1 | 0.710783 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 536.027 | 0.0710443 | 893.454ms | 2090234 | 30 | 2.0941e+08 | 3.71885e+06 | 4.61864 | 1(Win) |
| simdjson (ondemand) | 461.471 | 0.160789 | 1034.83ms | 2090234 | 30 | 1.44721e+09 | 4.31967e+06 | 5.36485 | 2(Loss) |
| glaze | 438.98 | 0.102308 | 1092.43ms | 2090234 | 30 | 6.47507e+08 | 4.54099e+06 | 5.6397 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1161.38 | 0.123987 | 413.217ms | 2090234 | 30 | 1.35868e+08 | 1.7164e+06 | 2.13167 | 1(Win) |
| glaze | 925.422 | 0.118659 | 517.761ms | 2090234 | 30 | 1.95989e+08 | 2.15405e+06 | 2.67519 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1357.79 | 0.346073 | 1118.11ms | 6661897 | 30 | 7.86658e+09 | 4.67913e+06 | 1.82331 | 1(Win) |
| jsonifier | 1264.51 | 0.10201 | 1208.03ms | 6661897 | 30 | 7.88051e+08 | 5.0243e+06 | 1.95785 | 2(Loss) |
| glaze | 1122.62 | 0.0806358 | 1358.57ms | 6661897 | 30 | 6.24755e+08 | 5.65935e+06 | 2.20532 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2861.08 | 0.136981 | 535.238ms | 6661897 | 30 | 2.77575e+08 | 2.22059e+06 | 0.86531 | 1(Win) |
| glaze | 2233.11 | 0.223225 | 684.523ms | 6661897 | 30 | 1.20999e+09 | 2.84504e+06 | 1.10862 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1163.59 | 0.22219 | 98.4593ms | 500299 | 30 | 2.49018e+07 | 410043 | 2.12728 | 1(Win) |
| jsonifier | 1059.18 | 0.267011 | 108.162ms | 500299 | 30 | 4.3401e+07 | 450464 | 2.33705 | 2(Loss) |
| simdjson (ondemand) | 876.459 | 1.15102 | 128.138ms | 500299 | 30 | 1.17782e+09 | 544375 | 2.82417 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3419.3 | 0.403596 | 34.0262ms | 500299 | 30 | 9.51477e+06 | 139538 | 0.723837 | 1(Win) |
| glaze | 2702.54 | 0.386942 | 42.7448ms | 500299 | 30 | 1.4e+07 | 176546 | 0.915758 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2303.98 | 0.19757 | 143.354ms | 1439562 | 30 | 4.15782e+07 | 595870 | 1.07438 | 1(Win) |
| glaze | 2044.36 | 0.107881 | 161.399ms | 1439562 | 30 | 1.57456e+07 | 671543 | 1.21084 | 2(Loss) |
| jsonifier | 1819.92 | 0.102106 | 181.473ms | 1439562 | 30 | 1.77984e+07 | 754359 | 1.36018 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5199.28 | 0.326549 | 63.5907ms | 1439562 | 30 | 2.23045e+07 | 264050 | 0.476091 | 1(Win) |
| glaze | 3468.17 | 0.230274 | 95.7157ms | 1439584 | 30 | 2.49278e+07 | 395856 | 0.713737 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1107.33 | 0.736116 | 12.0587ms | 56369 | 30 | 3.83125e+06 | 48547.1 | 2.2344 | 1(Win) |
| simdjson (ondemand) | 1067.81 | 0.615975 | 12.5472ms | 56369 | 30 | 2.88497e+06 | 50343.9 | 2.31698 | 2(Loss) |
| jsonifier | 904.78 | 0.657388 | 14.9263ms | 56369 | 30 | 4.57677e+06 | 59415.2 | 2.73493 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3967.03 | 0.127664 | 3.47218ms | 56369 | 30 | 8978.51 | 13551.1 | 0.622744 | 1(Win) |
| glaze | 3561.74 | 1.85289 | 3.80254ms | 56369 | 30 | 2.34626e+06 | 15093.1 | 0.693715 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1675.17 | 0.62318 | 13.2952ms | 94370 | 30 | 3.36279e+06 | 53725 | 1.47703 | 1(Win) |
| glaze | 1497.72 | 0.46459 | 14.837ms | 94370 | 30 | 2.33812e+06 | 60090.2 | 1.65212 | 2(Loss) |
| jsonifier | 1030.23 | 0.42798 | 21.5013ms | 94370 | 30 | 4.19343e+06 | 87357.6 | 2.40212 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4711.93 | 0.980404 | 10.9213ms | 94370 | 32 | 1.1221e+06 | 19100.1 | 0.524599 | 1(Win) |
| glaze | 3382.87 | 1.02631 | 6.7132ms | 94370 | 30 | 2.23651e+06 | 26604.1 | 0.730996 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1280.95 | 1.08388 | 9.74414ms | 52708 | 30 | 5.42722e+06 | 39241.5 | 1.9303 | 1(Win) |
| glaze | 1019.78 | 0.770452 | 12.5237ms | 52708 | 30 | 4.32664e+06 | 49291.2 | 2.42582 | 2(Loss) |
| jsonifier | 958.623 | 0.505079 | 13.4776ms | 52708 | 30 | 2.10426e+06 | 52435.9 | 2.58058 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 4320.82 | 2.30448 | 2.97132ms | 52708 | 30 | 2.15619e+06 | 11633.5 | 0.571486 | 1(Win) |
| jsonifier | 3872.25 | 2.41963 | 3.27793ms | 52708 | 30 | 2.9597e+06 | 12981.2 | 0.637915 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1661.47 | 0.940547 | 9.9723ms | 70103 | 30 | 4.29704e+06 | 40238.7 | 1.4886 | 1(Win) |
| glaze | 1189.12 | 0.62238 | 14.1815ms | 70103 | 30 | 3.67329e+06 | 56222.7 | 2.0807 | 2(Loss) |
| jsonifier | 924.081 | 0.999736 | 18.1809ms | 70103 | 30 | 1.56944e+07 | 72348 | 2.67676 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4454.37 | 0.0945281 | 3.85408ms | 70103 | 30 | 6038.72 | 15009 | 0.554704 | 1(Win) |
| glaze | 3782.91 | 0.251675 | 4.50645ms | 70103 | 30 | 59350.1 | 17673 | 0.653335 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 880.413 | 0.185759 | 3.37989ms | 11812 | 30 | 16947 | 12794.9 | 2.80551 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 868.469 | 1.52791 | 3.30303ms | 11812 | 30 | 1.1783e+06 | 12970.9 | 2.84411 | 1(Tie) |
| jsonifier | 651.496 | 2.02277 | 4.39622ms | 11812 | 30 | 3.66977e+06 | 17290.7 | 3.79383 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3873.09 | 0.154841 | 7.59621ms | 11812 | 128 | 2596.05 | 2908.48 | 0.632659 | 1(Win) |
| glaze | 2493.65 | 0.419266 | 1.28099ms | 11812 | 30 | 10761.6 | 4517.4 | 0.986483 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2028.4 | 0.517034 | 3.73484ms | 31235 | 30 | 172956 | 14685.5 | 1.21802 | 1(Win) |
| glaze | 1586.99 | 1.66053 | 10.9466ms | 31235 | 32 | 3.1087e+06 | 18770.2 | 1.55729 | 2(Loss) |
| jsonifier | 1393.4 | 1.35552 | 5.46424ms | 31235 | 30 | 2.51921e+06 | 21377.9 | 1.77429 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4588.82 | 0.305442 | 1.76342ms | 31235 | 30 | 11794 | 6491.43 | 0.537147 | 1(Win) |
| glaze | 3515.17 | 0.246335 | 2.22984ms | 31235 | 30 | 13072.7 | 8474.13 | 0.701602 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2152.75 | 0.441221 | 12.0181ms | 108313 | 30 | 1.34464e+06 | 47982.9 | 1.14919 | 1(Win) |
| glaze STATISTICAL TIE | 1369.52 | 0.606824 | 18.4823ms | 108313 | 30 | 6.28454e+06 | 75424.7 | 1.80666 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1350.86 | 0.506524 | 18.617ms | 108313 | 30 | 4.50053e+06 | 76466.6 | 1.83197 | 2(Tie) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2464.04 | 0.702405 | 10.3093ms | 108313 | 30 | 2.60113e+06 | 41921.1 | 1.00408 | 1(Win) |
| glaze | 1881.04 | 0.542601 | 13.4503ms | 108313 | 30 | 2.66348e+06 | 54914.1 | 1.31546 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2423.81 | 0.35511 | 20.5125ms | 213963 | 30 | 2.68118e+06 | 84185.9 | 1.021 | 1(Win) |
| glaze | 1919.76 | 0.442704 | 26.3806ms | 213963 | 30 | 6.64249e+06 | 106290 | 1.28919 | 2(Loss) |
| jsonifier | 1570.57 | 0.373302 | 31.6671ms | 213963 | 30 | 7.05676e+06 | 129922 | 1.57569 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3526.81 | 0.629753 | 14.1214ms | 213963 | 30 | 3.98269e+06 | 57857.1 | 0.701631 | 1(Win) |
| glaze | 2262.29 | 0.625692 | 21.9761ms | 213963 | 30 | 9.55481e+06 | 90196.6 | 1.09387 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 557.103 | 0.20202 | 754.179ms | 1834197 | 30 | 1.20707e+09 | 3.13986e+06 | 4.44374 | 1(Win) |
| glaze | 431.832 | 0.0885907 | 973.406ms | 1834197 | 30 | 3.86331e+08 | 4.05071e+06 | 5.73302 | 2(Loss) |
| simdjson (ondemand) | 422.916 | 0.0696659 | 992.441ms | 1834197 | 30 | 2.49085e+08 | 4.13611e+06 | 5.85389 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 737.018 | 0.300659 | 566.407ms | 1834197 | 30 | 1.52758e+09 | 2.37338e+06 | 3.3591 | 1(Win) |
| glaze | 481.64 | 0.0471556 | 871.453ms | 1833577 | 30 | 8.7931e+07 | 3.63059e+06 | 5.14018 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1973.81 | 0.0728933 | 1153.34ms | 9930848 | 30 | 3.66993e+08 | 4.79823e+06 | 1.25426 | 1(Win) |
| jsonifier | 1870.02 | 0.104856 | 1218.08ms | 9930848 | 30 | 8.46034e+08 | 5.06454e+06 | 1.32389 | 2(Loss) |
| glaze | 1682.82 | 0.112698 | 1348.01ms | 9930848 | 30 | 1.20685e+09 | 5.62793e+06 | 1.47116 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2716.01 | 0.165942 | 842.421ms | 9930848 | 30 | 1.00448e+09 | 3.48702e+06 | 0.911522 | 1(Win) |
| glaze | 1691.28 | 0.0981771 | 1349.76ms | 9930228 | 30 | 9.06624e+08 | 5.59942e+06 | 1.46378 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1012.9 | 0.315933 | 146.857ms | 642697 | 30 | 1.09644e+08 | 605115 | 2.44385 | 1(Win) |
| simdjson (ondemand) | 842.072 | 0.245494 | 176.508ms | 642697 | 30 | 9.57898e+07 | 727876 | 2.93985 | 2(Loss) |
| glaze | 773.437 | 0.272168 | 189.065ms | 642697 | 30 | 1.39559e+08 | 792467 | 3.20066 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1213.84 | 1.12075 | 121.91ms | 642697 | 30 | 9.60789e+08 | 504944 | 2.03945 | 1(Win) |
| glaze | 801.965 | 0.155094 | 183.417ms | 642692 | 30 | 4.21507e+07 | 764271 | 3.08678 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1500.55 | 0.130882 | 187.998ms | 1225964 | 30 | 3.11989e+07 | 779162 | 1.64975 | 1(Win) |
| glaze | 1197.2 | 0.241543 | 233.423ms | 1225964 | 30 | 1.66931e+08 | 976590 | 2.06781 | 2(Loss) |
| jsonifier | 1064.96 | 0.174251 | 261.948ms | 1225964 | 30 | 1.0979e+08 | 1.09786e+06 | 2.32453 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2064.66 | 0.329212 | 135.945ms | 1225964 | 30 | 1.04264e+08 | 566278 | 1.19899 | 1(Win) |
| glaze | 1241.35 | 0.0840663 | 226.96ms | 1225970 | 30 | 1.88077e+07 | 941857 | 1.99426 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 758.441 | 0.249535 | 124.503ms | 409725 | 30 | 4.95822e+07 | 515194 | 3.2637 | 1(Win) |
| glaze | 525.728 | 0.170619 | 179.483ms | 409725 | 30 | 4.82436e+07 | 743244 | 4.70883 | 2(Loss) |
| jsonifier | 516.55 | 0.178307 | 182.693ms | 409725 | 30 | 5.45782e+07 | 756450 | 4.79229 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2446.94 | 0.451754 | 38.6326ms | 409725 | 30 | 1.56121e+07 | 159687 | 1.01144 | 1(Win) |
| glaze | 2157.17 | 0.916588 | 43.2163ms | 409725 | 30 | 8.26964e+07 | 181138 | 1.14728 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1365.23 | 0.193671 | 132.158ms | 785750 | 30 | 3.39003e+07 | 548880 | 1.81314 | 1(Win) |
| glaze | 892.747 | 0.120996 | 202.566ms | 785750 | 30 | 3.09437e+07 | 839375 | 2.773 | 2(Loss) |
| jsonifier | 775.276 | 0.0842096 | 232.344ms | 785750 | 30 | 1.98747e+07 | 966559 | 3.19305 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3828.35 | 0.305467 | 47.4546ms | 785750 | 30 | 1.0725e+07 | 195737 | 0.646542 | 1(Win) |
| glaze | 2585.35 | 1.01767 | 67.4655ms | 785750 | 30 | 2.61012e+08 | 289844 | 0.957361 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 878.145 | 0.581705 | 2220.1ms | 8587914 | 30 | 8.83019e+10 | 9.32656e+06 | 2.81927 | 1(Win) |
| glaze | 791.452 | 0.203182 | 2506.33ms | 8587914 | 30 | 1.32623e+10 | 1.03482e+07 | 3.1281 | 2(Loss) |
| jsonifier | 731.318 | 0.239901 | 2692.36ms | 8587914 | 30 | 2.16545e+10 | 1.11991e+07 | 3.38527 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2788.73 | 0.10128 | 711.798ms | 8588126 | 30 | 2.65434e+08 | 2.93692e+06 | 0.887726 | 1(Win) |
| jsonifier | 2647.52 | 0.978647 | 728.937ms | 8588126 | 30 | 2.74975e+10 | 3.09357e+06 | 0.935077 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 983.305 | 0.354701 | 2275.94ms | 9804437 | 30 | 3.41284e+10 | 9.50899e+06 | 2.51777 | 1(Win) |
| glaze | 837.039 | 0.184961 | 2677.85ms | 9804437 | 30 | 1.28066e+10 | 1.11706e+07 | 2.95773 | 2(Loss) |
| jsonifier | 697.317 | 0.107982 | 3235ms | 9804437 | 30 | 6.2894e+09 | 1.34089e+07 | 3.55031 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3156.39 | 0.147764 | 810.343ms | 11078090 | 30 | 7.33852e+08 | 3.34715e+06 | 0.784302 | 1(Win) |
| glaze | 2634.94 | 0.131533 | 965.602ms | 11078090 | 30 | 8.34412e+08 | 4.00954e+06 | 0.939519 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 4478.42 | 0.621757 | 13.7005ms | 264040 | 30 | 3.6665e+06 | 56227 | 0.552446 | 1(Win) |
| jsonifier | 4007.73 | 0.455504 | 15.3265ms | 264040 | 30 | 2.45724e+06 | 62830.7 | 0.617488 | 2(Loss) |
| glaze | 1085.83 | 0.277986 | 55.9652ms | 264040 | 30 | 1.24676e+07 | 231904 | 2.27971 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 5760.13 | 0.508791 | 16.1294ms | 399947 | 30 | 3.40519e+06 | 66217.1 | 0.429607 | 1(Win) |
| jsonifier | 5142.71 | 0.542942 | 18.0594ms | 399947 | 30 | 4.86463e+06 | 74167 | 0.481231 | 2(Loss) |
| glaze | 1456.65 | 0.271534 | 63.194ms | 399947 | 30 | 1.51657e+07 | 261846 | 1.69933 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1458.56 | 0.470005 | 44.0049ms | 264040 | 30 | 1.97522e+07 | 172641 | 1.69668 | 1(Win) |
| glaze STATISTICAL TIE | 1152.99 | 0.338475 | 53.3265ms | 264040 | 30 | 1.63932e+07 | 218396 | 2.14644 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1146.73 | 0.416575 | 55.1923ms | 264040 | 30 | 2.51029e+07 | 219587 | 2.15814 | 2(Tie) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3461.82 | 0.706276 | 17.7972ms | 263923 | 30 | 7.91073e+06 | 72706.5 | 0.714656 | 1(Win) |
| jsonifier | 3140.79 | 0.67698 | 19.3687ms | 264040 | 30 | 8.8376e+06 | 80173.5 | 0.78792 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1924.46 | 0.457345 | 47.8048ms | 399947 | 30 | 2.46488e+07 | 198195 | 1.28601 | 1(Win) |
| glaze | 1368.74 | 0.351116 | 67.6342ms | 399947 | 30 | 2.87202e+07 | 278665 | 1.80837 | 2(Loss) |
| jsonifier | 1130.43 | 0.629944 | 81.4887ms | 399947 | 30 | 1.35533e+08 | 337411 | 2.18926 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4229.9 | 0.643365 | 22.6372ms | 399947 | 30 | 1.00967e+07 | 90172.2 | 0.585058 | 1(Win) |
| glaze | 3588.09 | 0.399938 | 26.1273ms | 399830 | 30 | 5.41917e+06 | 106270 | 0.689653 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1908.47 | 0.25911 | 56.3689ms | 466906 | 30 | 1.09642e+07 | 233316 | 1.29697 | 1(Win) |
| glaze | 1674.16 | 0.246016 | 63.5241ms | 466906 | 30 | 1.28443e+07 | 265969 | 1.47704 | 2(Loss) |
| simdjson (ondemand) | 927.348 | 0.249432 | 116.11ms | 466906 | 30 | 4.30329e+07 | 480161 | 2.66925 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3046.86 | 0.318266 | 52.8307ms | 699405 | 30 | 1.45631e+07 | 218915 | 0.812371 | 1(Win) |
| glaze | 2721.95 | 0.272937 | 58.3091ms | 699405 | 30 | 1.34197e+07 | 245046 | 0.909293 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1795.93 | 0.224446 | 80.8009ms | 631514 | 30 | 1.69953e+07 | 335346 | 1.37834 | 1(Win) |
| glaze | 1730.26 | 0.197555 | 83.8535ms | 631514 | 30 | 1.41853e+07 | 348073 | 1.43074 | 2(Loss) |
