# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36256.0 compiler).  

Latest Results: (Sep 11, 2026)
#### Using the following commits:
----
| Jsonifier: [9a2d193](https://github.com/nihilai-collective/jsonifier/commit/9a2d193)  
| Glaze: [565edc9](https://github.com/stephenberry/glaze/commit/565edc9)  
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
  This is the commit of BenchmarkSuite that was used to generate these results: [c0b7b4a](https://github.com/realtimechris/benchmarksuite/commit/c0b7b4a).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 423.656 | 0.192658 | 2.4894ms | 1811 | 30 | 1850.57 | 4076.67 | 5.45927 | 1(Win) |
| glaze | 162.271 | 0.257538 | 3.8346ms | 1811 | 30 | 22540.2 | 10643.3 | 14.2955 | 2(Loss) |
| simdjson (ondemand) | 95.6017 | 0.0741939 | 24.6421ms | 1811 | 64 | 11498 | 18065.6 | 24.3417 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 308.595 | 0.104339 | 2.7985ms | 1811 | 30 | 1022.99 | 5596.67 | 7.4785 | 1(Win) |
| glaze | 124.979 | 0.0884079 | 4.8021ms | 1798 | 30 | 4413.79 | 13720 | 18.6107 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1053.3 | 0.132093 | 2.3164ms | 3873 | 30 | 643.678 | 3506.67 | 2.19381 | 1(Win) |
| glaze | 628.873 | 0.181318 | 2.7645ms | 3873 | 30 | 3402.3 | 5873.33 | 3.69197 | 2(Loss) |
| simdjson (ondemand) | 231.89 | 0.0452416 | 22.0841ms | 3873 | 64 | 3323.41 | 15928.1 | 10.0394 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1707.36 | 0.413647 | 1.8649ms | 3873 | 30 | 2402.3 | 2163.33 | 1.34002 | 1(Win) |
| glaze | 717.2 | 0.223245 | 2.5165ms | 3873 | 30 | 3965.52 | 5150 | 3.22807 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 674.971 | 0.445301 | 2.8183ms | 3862 | 30 | 17712.6 | 5456.67 | 3.42335 | 1(Win) |
| glaze | 554.961 | 0.134835 | 2.8865ms | 3862 | 30 | 2402.3 | 6636.67 | 4.1675 | 2(Loss) |
| simdjson (ondemand) | 226.652 | 0.567357 | 5.1903ms | 3862 | 30 | 255000 | 16250 | 10.262 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1556.24 | 0.369877 | 1.8705ms | 3862 | 30 | 2298.85 | 2366.67 | 1.47557 | 1(Win) |
| glaze | 698.879 | 0.18534 | 2.5082ms | 3862 | 30 | 2862.07 | 5270 | 3.31249 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 809.924 | 0.800517 | 2.6658ms | 905 | 32 | 2328.63 | 1065.62 | 2.76985 | 1(Win) |
| glaze | 141.798 | 0.130233 | 2.6843ms | 905 | 30 | 1885.06 | 6086.67 | 16.3125 | 2(Loss) |
| simdjson (ondemand) | 67.7276 | 0.0722093 | 4.3059ms | 905 | 30 | 2540.23 | 12743.3 | 34.3479 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 395.302 | 0.316967 | 1.806ms | 905 | 30 | 1436.78 | 2183.33 | 5.82597 | 1(Win) |
| glaze | 119.983 | 0.0926784 | 2.9972ms | 905 | 30 | 1333.33 | 7193.33 | 19.2652 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1161.63 | 0.129107 | 3.5158ms | 9578 | 30 | 3091.95 | 7863.33 | 1.99452 | 1(Win) |
| glaze | 904.087 | 0.0885703 | 3.7467ms | 9578 | 30 | 2402.3 | 10103.3 | 2.57304 | 2(Loss) |
| simdjson (ondemand) | 383.643 | 1.78348 | 30.9017ms | 9578 | 64 | 1.15402e+07 | 23809.4 | 6.0689 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2178.29 | 0.158983 | 2.2078ms | 9578 | 30 | 1333.33 | 4193.33 | 1.06076 | 1(Win) |
| glaze | 1512.3 | 0.170254 | 2.8045ms | 9578 | 30 | 3172.41 | 6040 | 1.53204 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2346.37 | 1.0899 | 24.7193ms | 233995 | 30 | 3.22344e+07 | 95106.7 | 0.993151 | 1(Win) |
| simdjson (ondemand) | 1537.09 | 1.07262 | 36.4222ms | 233995 | 30 | 7.27492e+07 | 145180 | 1.51683 | 2(Loss) |
| glaze | 1032.3 | 0.843938 | 53.5393ms | 233995 | 30 | 9.98496e+07 | 216173 | 2.25879 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2994.65 | 1.22323 | 28.1227ms | 346753 | 30 | 5.47379e+07 | 110427 | 0.778345 | 1(Win) |
| simdjson (ondemand) | 1970.23 | 0.865524 | 41.8806ms | 346753 | 30 | 6.33122e+07 | 167843 | 1.18326 | 2(Loss) |
| glaze | 1324.35 | 1.80867 | 61.1244ms | 346753 | 30 | 6.11895e+08 | 249700 | 1.76042 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 750.53 | 1.94329 | 72.0797ms | 233995 | 30 | 1.00156e+09 | 297330 | 3.10643 | 1(Win) |
| glaze | 636.065 | 1.90551 | 89.2542ms | 233995 | 30 | 1.34076e+09 | 350837 | 3.66594 | 2(Loss) |
| simdjson (ondemand) | 439.772 | 0.565767 | 123.658ms | 233995 | 30 | 2.4726e+08 | 507433 | 5.30234 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1198.13 | 1.79529 | 227.551ms | 233995 | 64 | 7.15574e+08 | 186253 | 1.94521 | 1(Win) |
| glaze | 1090.42 | 2.41895 | 623.528ms | 233995 | 128 | 3.13681e+09 | 204650 | 2.13792 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 936.806 | 0.800711 | 113.789ms | 346753 | 30 | 2.3967e+08 | 352997 | 2.48903 | 1(Win) |
| simdjson (ondemand) | 617.869 | 0.673639 | 129.717ms | 346753 | 30 | 3.89964e+08 | 535210 | 3.77408 | 2(Loss) |
| glaze | 460.299 | 0.650626 | 109.775ms | 346753 | 30 | 6.55459e+08 | 718423 | 5.06587 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1814.22 | 1.64987 | 44.4393ms | 346753 | 30 | 2.71319e+08 | 182277 | 1.28494 | 1(Win) |
| glaze | 1081.06 | 2.16431 | 766.192ms | 346753 | 128 | 5.61038e+09 | 305895 | 2.15669 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1324.18 | 0.94975 | 32.0028ms | 233995 | 30 | 7.68529e+07 | 168523 | 1.76005 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1046.07 | 0.879495 | 52.6528ms | 233995 | 30 | 1.05603e+08 | 213327 | 2.2289 | 2(Tie) |
| glaze STATISTICAL TIE | 1040.85 | 0.878373 | 52.9762ms | 233995 | 30 | 1.06393e+08 | 214397 | 2.23989 | 2(Tie) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2916.73 | 1.39366 | 28.6173ms | 346753 | 30 | 7.48998e+07 | 113377 | 0.799012 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1399.72 | 0.758246 | 58.4816ms | 346753 | 30 | 9.62715e+07 | 236253 | 1.66566 | 2(Tie) |
| glaze STATISTICAL TIE | 1371.83 | 0.735084 | 63.265ms | 346753 | 30 | 9.41963e+07 | 241057 | 1.69956 | 2(Tie) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 755.826 | 0.770265 | 74.5011ms | 233995 | 30 | 1.55157e+08 | 295247 | 3.08486 | 1(Win) |
| glaze | 732.328 | 0.691378 | 79.4408ms | 233995 | 30 | 1.33154e+08 | 304720 | 3.18394 | 2(Loss) |
| simdjson (ondemand) | 102.149 | 0.161919 | 548.665ms | 233995 | 30 | 3.75373e+08 | 2.18461e+06 | 22.8301 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1523.21 | 1.4948 | 36.7325ms | 233995 | 30 | 1.43875e+08 | 146503 | 1.53031 | 1(Win) |
| glaze | 1153.04 | 2.32444 | 238.921ms | 233995 | 64 | 1.29521e+09 | 193536 | 2.02181 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 917.452 | 0.860708 | 88.784ms | 346753 | 30 | 2.8874e+08 | 360443 | 2.54132 | 1(Win) |
| glaze | 843.215 | 1.11127 | 95.6992ms | 346753 | 30 | 5.698e+08 | 392177 | 2.76526 | 2(Loss) |
| simdjson (ondemand) | 148.481 | 0.192014 | 1267.86ms | 346753 | 32 | 5.85216e+08 | 2.22716e+06 | 15.706 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1874.87 | 1.60052 | 43.6131ms | 346753 | 30 | 2.39079e+08 | 176380 | 1.24332 | 1(Win) |
| glaze | 1084.74 | 2.33406 | 386.684ms | 346753 | 64 | 3.24033e+09 | 304855 | 2.14935 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 447.113 | 1.87372 | 51.5891ms | 94651 | 30 | 4.29286e+08 | 201887 | 5.21364 | 1(Win) |
| glaze | 406.645 | 2.20466 | 137.108ms | 94651 | 32 | 7.66399e+08 | 221978 | 5.73333 | 2(Loss) |
| simdjson (ondemand) | 331.699 | 1.48037 | 77.4113ms | 94651 | 30 | 4.86882e+08 | 272133 | 7.02877 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1667.17 | 1.70638 | 14.7399ms | 94651 | 30 | 2.56074e+07 | 54143.3 | 1.39714 | 1(Win) |
| jsonifier | 1511.24 | 2.39919 | 15.4234ms | 94651 | 30 | 6.16077e+07 | 59730 | 1.54187 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 541.971 | 1.06277 | 59.7489ms | 136024 | 30 | 1.94125e+08 | 239353 | 4.3019 | 1(Win) |
| glaze | 505.495 | 0.982254 | 1337.47ms | 136024 | 256 | 1.62662e+09 | 256625 | 4.61199 | 2(Loss) |
| simdjson (ondemand) | 476.408 | 0.754835 | 67.3749ms | 136024 | 30 | 1.26736e+08 | 272293 | 4.8941 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1799.05 | 1.30447 | 42.2325ms | 136024 | 32 | 2.83116e+07 | 72106.2 | 1.29534 | 1(Win) |
| glaze | 1270.79 | 1.05978 | 25.9842ms | 136046 | 30 | 3.51217e+07 | 102097 | 1.83403 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 334.83 | 1.13282 | 1467.66ms | 2090234 | 30 | 1.36454e+11 | 5.95347e+06 | 6.96479 | 1(Win) |
| glaze | 210.201 | 0.745554 | 2296.98ms | 2090234 | 30 | 1.49969e+11 | 9.48333e+06 | 11.0941 | 2(Loss) |
| simdjson (ondemand) | 196.257 | 0.813055 | 2482.6ms | 2090234 | 30 | 2.04599e+11 | 1.01571e+07 | 11.8819 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 554.981 | 0.235537 | 907.097ms | 2090234 | 30 | 2.14719e+09 | 3.59184e+06 | 4.20165 | 1(Win) |
| glaze | 453.201 | 0.30019 | 1096.8ms | 2090234 | 30 | 5.23023e+09 | 4.39849e+06 | 5.14543 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 878.816 | 0.742503 | 1802.6ms | 6661897 | 30 | 8.64406e+10 | 7.22937e+06 | 2.65354 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 582.726 | 0.518432 | 2673.68ms | 6661897 | 30 | 9.58458e+10 | 1.09027e+07 | 4.00186 | 2(Tie) |
| glaze STATISTICAL TIE | 575.146 | 0.745809 | 6340.71ms | 6661897 | 32 | 2.17193e+11 | 1.10464e+07 | 4.05447 | 2(Tie) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1332.39 | 0.24977 | 1193.83ms | 6661897 | 30 | 4.25537e+09 | 4.76834e+06 | 1.75023 | 1(Win) |
| glaze | 730.333 | 0.895694 | 2105.47ms | 6661897 | 30 | 1.82136e+11 | 8.69916e+06 | 3.19302 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 740.337 | 0.734547 | 171.914ms | 500299 | 30 | 6.72298e+08 | 644467 | 3.14962 | 1(Win) |
| glaze | 446.673 | 0.299606 | 273.515ms | 500299 | 30 | 3.07258e+08 | 1.06817e+06 | 5.22073 | 2(Loss) |
| simdjson (ondemand) | 266.078 | 0.127575 | 434.486ms | 500299 | 30 | 1.56997e+08 | 1.79317e+06 | 8.76446 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1684 | 0.673967 | 69.1366ms | 500299 | 30 | 1.09389e+08 | 283327 | 1.38452 | 1(Win) |
| glaze | 1279.53 | 0.609749 | 92.1442ms | 500299 | 30 | 1.55091e+08 | 372890 | 1.82227 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1347.68 | 0.973929 | 244.965ms | 1439562 | 30 | 2.95302e+09 | 1.0187e+06 | 1.73026 | 1(Win) |
| glaze | 960.546 | 1.19922 | 337.019ms | 1439562 | 30 | 8.81347e+09 | 1.42926e+06 | 2.42753 | 2(Loss) |
| simdjson (ondemand) | 703.612 | 0.377729 | 484.108ms | 1439562 | 30 | 1.62958e+09 | 1.95118e+06 | 3.3143 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1967.76 | 0.700593 | 168.751ms | 1439562 | 30 | 7.16753e+08 | 697683 | 1.18485 | 1(Win) |
| glaze | 908.75 | 0.437384 | 360.879ms | 1439584 | 30 | 1.30988e+09 | 1.51075e+06 | 2.56586 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 675.404 | 1.37245 | 21.2905ms | 56369 | 30 | 3.57986e+07 | 79593.3 | 3.45137 | 1(Win) |
| glaze | 612.67 | 1.37858 | 22.5667ms | 56369 | 30 | 4.3895e+07 | 87743.3 | 3.80331 | 2(Loss) |
| simdjson (ondemand) | 291.496 | 0.799859 | 46.116ms | 56369 | 30 | 6.52775e+07 | 184420 | 7.99767 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1427.83 | 2.00182 | 10.2315ms | 56369 | 30 | 1.70412e+07 | 37650 | 1.63139 | 1(Win) |
| glaze | 1224.18 | 2.33385 | 11.7253ms | 56369 | 30 | 3.15109e+07 | 43913.3 | 1.90272 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 901.391 | 1.43327 | 58.286ms | 94370 | 32 | 6.55309e+07 | 99843.8 | 2.58547 | 1(Win) |
| jsonifier | 723.846 | 1.44734 | 31.892ms | 94370 | 30 | 9.71492e+07 | 124333 | 3.22046 | 2(Loss) |
| simdjson (ondemand) | 467.645 | 0.93149 | 47.6437ms | 94370 | 30 | 9.64081e+07 | 192450 | 4.98516 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2245.09 | 2.19128 | 11.0532ms | 94370 | 30 | 2.31481e+07 | 40086.7 | 1.03788 | 1(Win) |
| glaze | 1130.11 | 1.51331 | 20.2347ms | 94370 | 30 | 4.35714e+07 | 79636.7 | 2.06227 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 611.363 | 2.47208 | 22.1935ms | 52708 | 30 | 1.23938e+08 | 82220 | 3.81087 | 1(Win) |
| glaze | 490.132 | 1.66524 | 26.4869ms | 52708 | 30 | 8.74984e+07 | 102557 | 4.75582 | 2(Loss) |
| simdjson (ondemand) | 425.037 | 1.39797 | 29.8786ms | 52708 | 30 | 8.20003e+07 | 118263 | 5.48446 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2279.3 | 0.370705 | 6.6427ms | 52708 | 30 | 200506 | 22053.3 | 1.02018 | 1(Win) |
| glaze | 1884.75 | 1.25421 | 7.7196ms | 52708 | 30 | 3.35666e+06 | 26670 | 1.23445 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 584.384 | 1.77231 | 28.8839ms | 70103 | 30 | 1.23333e+08 | 114403 | 3.98809 | 1(Win) |
| simdjson (ondemand) | 548.543 | 1.23362 | 71.4885ms | 70103 | 32 | 7.23379e+07 | 121878 | 4.24872 | 2(Loss) |
| jsonifier | 516.67 | 2.33726 | 33.8183ms | 70103 | 30 | 2.74399e+08 | 129397 | 4.50664 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2772.55 | 0.171892 | 7.1012ms | 70103 | 30 | 51540.2 | 24113.3 | 0.838893 | 1(Win) |
| glaze | 1675.01 | 2.43316 | 10.8994ms | 70103 | 30 | 2.82943e+07 | 39913.3 | 1.39003 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 524.821 | 0.0444697 | 28.9911ms | 11812 | 64 | 5830.85 | 21464.1 | 4.43692 | 1(Win) |
| glaze | 387.55 | 0.0952356 | 8.5442ms | 11812 | 30 | 22988.5 | 29066.7 | 6.00781 | 2(Loss) |
| simdjson (ondemand) | 251.166 | 1.53699 | 12.5898ms | 11812 | 30 | 1.42557e+07 | 44850 | 9.27758 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1066.74 | 0.453128 | 3.8524ms | 11812 | 30 | 68689.7 | 10560 | 2.17551 | 1(Win) |
| glaze | 1017.9 | 0.431803 | 4.0241ms | 11812 | 30 | 68505.7 | 11066.7 | 2.28358 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 967.458 | 0.0719523 | 9.1011ms | 31235 | 30 | 14724.1 | 30790 | 2.40691 | 1(Win) |
| glaze | 791.533 | 0.285832 | 10.4983ms | 31235 | 30 | 347126 | 37633.3 | 2.94452 | 2(Loss) |
| simdjson (ondemand) | 614.651 | 1.86298 | 12.9639ms | 31235 | 30 | 2.44548e+07 | 48463.3 | 3.79086 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2418.51 | 0.343986 | 4.319ms | 31235 | 30 | 53850.6 | 12316.7 | 0.960942 | 1(Win) |
| glaze | 1429.43 | 2.41253 | 27.5073ms | 31235 | 64 | 1.61764e+07 | 20839.1 | 1.62871 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1241.63 | 1.29728 | 21.9875ms | 108313 | 30 | 3.49434e+07 | 83193.3 | 1.8766 | 1(Win) |
| glaze | 553.714 | 0.747023 | 46.882ms | 108313 | 30 | 5.82612e+07 | 186550 | 4.21034 | 2(Loss) |
| simdjson (ondemand) | 318.537 | 2.21128 | 76.5626ms | 108313 | 30 | 1.54259e+09 | 324280 | 7.31855 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1697.45 | 1.37634 | 15.8732ms | 108313 | 30 | 2.10446e+07 | 60853.3 | 1.37266 | 1(Win) |
| glaze | 1298.66 | 1.42292 | 20.4917ms | 108313 | 30 | 3.84287e+07 | 79540 | 1.79456 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1076.75 | 0.938284 | 57.2288ms | 213963 | 30 | 9.48503e+07 | 189507 | 2.16515 | 1(Win) |
| glaze | 852.902 | 0.867158 | 59.7139ms | 213963 | 30 | 1.29121e+08 | 239243 | 2.73335 | 2(Loss) |
| simdjson (ondemand) | 620.128 | 0.674642 | 189.787ms | 213963 | 32 | 1.57693e+08 | 329047 | 3.75992 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2870.72 | 1.52146 | 18.4864ms | 213963 | 30 | 3.50865e+07 | 71080 | 0.811693 | 1(Win) |
| glaze | 1160.26 | 2.14371 | 40.8367ms | 213963 | 30 | 4.26404e+08 | 175867 | 2.00905 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 346.159 | 0.644891 | 1257.55ms | 1834197 | 30 | 3.18592e+10 | 5.05325e+06 | 6.73675 | 1(Win) |
| glaze | 188.76 | 0.741936 | 2283.25ms | 1834197 | 30 | 1.41816e+11 | 9.26693e+06 | 12.3544 | 2(Loss) |
| simdjson (ondemand) | 170.238 | 1.54138 | 2438.86ms | 1834197 | 30 | 7.52522e+11 | 1.02752e+07 | 13.6985 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 329.936 | 0.866179 | 1269.3ms | 1834197 | 30 | 6.32659e+10 | 5.30171e+06 | 7.06783 | 1(Win) |
| glaze | 274.808 | 0.956023 | 1530.95ms | 1833577 | 30 | 1.11019e+11 | 6.36311e+06 | 8.48583 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1226.71 | 1.72437 | 1950.46ms | 9930848 | 30 | 5.317e+11 | 7.72047e+06 | 1.90099 | 1(Win) |
| glaze STATISTICAL TIE | 826.012 | 0.939081 | 2799.63ms | 9930848 | 30 | 3.47798e+11 | 1.14657e+07 | 2.82317 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 819.834 | 0.28213 | 2812.01ms | 9930848 | 30 | 3.18671e+10 | 1.15521e+07 | 2.84448 | 2(Tie) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1188.45 | 0.291667 | 1930.17ms | 9930848 | 30 | 1.62072e+10 | 7.96905e+06 | 1.96216 | 1(Win) |
| glaze | 598.661 | 2.05514 | 3653.94ms | 9930228 | 30 | 3.17074e+12 | 1.5819e+07 | 3.89513 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 674.086 | 0.435327 | 219.952ms | 642697 | 30 | 4.70041e+08 | 909267 | 3.45933 | 1(Win) |
| glaze | 433.132 | 0.238257 | 376.741ms | 642697 | 30 | 3.41024e+08 | 1.4151e+06 | 5.38406 | 2(Loss) |
| simdjson (ondemand) | 425.654 | 0.320194 | 358.204ms | 642697 | 30 | 6.37743e+08 | 1.43996e+06 | 5.47845 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 595.31 | 2.05603 | 235.111ms | 642697 | 30 | 1.34433e+10 | 1.02959e+06 | 3.91683 | 1(Win) |
| glaze | 361.616 | 2.46343 | 371.72ms | 642692 | 30 | 5.23012e+10 | 1.69494e+06 | 6.4474 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 979.038 | 0.197859 | 314.645ms | 1225964 | 30 | 1.67491e+08 | 1.1942e+06 | 2.38194 | 1(Win) |
| simdjson (ondemand) | 759.531 | 0.487145 | 884.232ms | 1225964 | 32 | 1.79941e+09 | 1.53933e+06 | 3.07027 | 2(Loss) |
| glaze | 721.7 | 0.363135 | 418.069ms | 1225964 | 30 | 1.03825e+09 | 1.62002e+06 | 3.23118 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 890.708 | 1.47671 | 312.843ms | 1225964 | 30 | 1.12718e+10 | 1.31263e+06 | 2.61753 | 1(Win) |
| glaze | 699.868 | 0.282364 | 420.474ms | 1225970 | 30 | 6.67524e+08 | 1.67057e+06 | 3.33149 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 461.56 | 0.45352 | 211.833ms | 409725 | 30 | 4.42225e+08 | 846573 | 5.05229 | 1(Win) |
| glaze | 300.137 | 0.362093 | 325.756ms | 409725 | 30 | 6.66667e+08 | 1.30189e+06 | 7.76953 | 2(Loss) |
| simdjson (ondemand) | 263.651 | 0.244839 | 363.218ms | 409725 | 30 | 3.95012e+08 | 1.48205e+06 | 8.84511 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1079.42 | 0.663441 | 88.308ms | 409725 | 30 | 1.73032e+08 | 361993 | 2.16022 | 1(Win) |
| glaze | 1038.27 | 0.709374 | 92.5952ms | 409725 | 30 | 2.13812e+08 | 376340 | 2.24578 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 574.85 | 0.422956 | 348.085ms | 785750 | 30 | 9.1195e+08 | 1.30356e+06 | 4.05658 | 1(Win) |
| glaze | 509.059 | 0.286942 | 378.727ms | 785750 | 30 | 5.35232e+08 | 1.47203e+06 | 4.58086 | 2(Loss) |
| simdjson (ondemand) | 481.297 | 0.649562 | 388.701ms | 785750 | 30 | 3.06835e+09 | 1.55694e+06 | 4.8452 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1602.18 | 0.630882 | 126.707ms | 785750 | 30 | 2.61195e+08 | 467707 | 1.45529 | 1(Win) |
| glaze | 855.269 | 0.677024 | 207.909ms | 785750 | 30 | 1.05558e+09 | 876157 | 2.72598 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 467.307 | 1.37511 | 4250.42ms | 8587914 | 30 | 1.74247e+12 | 1.75261e+07 | 4.99009 | 1(Win) |
| glaze STATISTICAL TIE | 331.452 | 1.63682 | 5914.97ms | 8587914 | 30 | 4.90745e+12 | 2.47097e+07 | 7.03563 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 326.403 | 1.64133 | 5911.26ms | 8587914 | 30 | 5.08837e+12 | 2.50919e+07 | 7.14448 | 2(Tie) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1200.35 | 0.947527 | 1682.6ms | 8588126 | 30 | 1.25396e+11 | 6.82323e+06 | 1.94264 | 1(Win) |
| glaze | 699.51 | 1.95252 | 6512.1ms | 8588126 | 32 | 1.67243e+12 | 1.17086e+07 | 3.33357 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 471.615 | 0.75373 | 4910.63ms | 9804437 | 30 | 6.69921e+11 | 1.9826e+07 | 4.94458 | 1(Win) |
| simdjson (ondemand) | 375.749 | 1.00655 | 6203.86ms | 9804437 | 30 | 1.88211e+12 | 2.48842e+07 | 6.2062 | 2(Loss) |
| glaze | 354.855 | 1.21833 | 6481.94ms | 9804437 | 30 | 3.09165e+12 | 2.63494e+07 | 6.57166 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1131.61 | 0.523949 | 11496.1ms | 11078090 | 64 | 1.53142e+11 | 9.33616e+06 | 2.06065 | 1(Win) |
| glaze | 716.662 | 1.20069 | 3559.61ms | 11078090 | 30 | 9.3991e+11 | 1.47418e+07 | 3.25382 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2071.25 | 1.46621 | 31.1053ms | 264040 | 30 | 9.53213e+07 | 121573 | 1.12522 | 1(Win) |
| simdjson (ondemand) | 1412.07 | 0.76423 | 105.514ms | 264040 | 32 | 5.94323e+07 | 178325 | 1.65094 | 2(Loss) |
| glaze | 759.76 | 0.609477 | 193.024ms | 264040 | 32 | 1.30573e+08 | 331431 | 3.06891 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2735.76 | 1.37988 | 35.0982ms | 399947 | 30 | 1.11034e+08 | 139420 | 0.852009 | 1(Win) |
| simdjson (ondemand) | 1844.39 | 0.870863 | 63.6046ms | 399947 | 30 | 9.73021e+07 | 206800 | 1.26403 | 2(Loss) |
| glaze | 1057.15 | 0.639277 | 89.1281ms | 399947 | 30 | 1.596e+08 | 360800 | 2.20566 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 787.91 | 0.988814 | 78.9525ms | 264040 | 30 | 2.99597e+08 | 319590 | 2.95902 | 1(Win) |
| glaze | 476.383 | 0.673349 | 129.238ms | 264040 | 30 | 3.80039e+08 | 528583 | 4.89451 | 2(Loss) |
| simdjson (ondemand) | 416.363 | 0.615209 | 159.119ms | 264040 | 30 | 4.153e+08 | 604780 | 5.60026 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2108.89 | 0.739281 | 30.5622ms | 264040 | 30 | 2.33762e+07 | 119403 | 1.10528 | 1(Win) |
| glaze | 1573.66 | 1.16331 | 39.8714ms | 263923 | 30 | 1.03859e+08 | 159943 | 1.48136 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 693.519 | 0.797157 | 134.767ms | 399947 | 30 | 5.7663e+08 | 549977 | 3.36181 | 1(Win) |
| glaze | 638.376 | 0.726915 | 144.737ms | 399947 | 30 | 5.659e+08 | 597483 | 3.65216 | 2(Loss) |
| simdjson (ondemand) | 607.969 | 0.502228 | 152.533ms | 399947 | 30 | 2.97828e+08 | 627367 | 3.83534 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2734.51 | 1.0153 | 34.9466ms | 399947 | 30 | 6.0167e+07 | 139483 | 0.852366 | 1(Win) |
| glaze | 1438.05 | 1.85022 | 62.4491ms | 399830 | 30 | 7.22061e+08 | 265157 | 1.62087 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1170.77 | 0.57227 | 93.2633ms | 466906 | 30 | 1.42114e+08 | 380327 | 1.9916 | 1(Win) |
| glaze | 934.545 | 0.688575 | 117.949ms | 466906 | 30 | 3.22911e+08 | 476463 | 2.49505 | 2(Loss) |
| simdjson (ondemand) | 538.393 | 0.378734 | 199.869ms | 466906 | 30 | 2.94341e+08 | 827047 | 4.33112 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1709.14 | 1.28088 | 103.606ms | 699405 | 30 | 7.49618e+08 | 390257 | 1.36412 | 1(Win) |
| glaze | 1068.21 | 0.457897 | 151.461ms | 699405 | 30 | 2.45246e+08 | 624413 | 2.1829 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1350.08 | 0.490656 | 108.743ms | 631514 | 30 | 1.43721e+08 | 446090 | 1.72711 | 1(Win) |
| jsonifier | 1140.15 | 0.424535 | 129.402ms | 631514 | 30 | 1.50865e+08 | 528227 | 2.04517 | 2(Loss) |
