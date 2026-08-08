# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36252.0 compiler).  

Latest Results: (Aug 08, 2026)
#### Using the following commits:
----
| Jsonifier: [66d99df](https://github.com/nihilai-collective/jsonifier/commit/66d99df)  
| Glaze: [72b670e](https://github.com/stephenberry/glaze/commit/72b670e)  
| Simdjson: [20b2871](https://github.com/simdjson/simdjson/commit/20b2871)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX512` |
| simdjson (ondemand) | `icelake` |
| Glaze (utf8-validation) | `SSSE3` |
| Glaze (string-escape) | `SSE2` |
| Glaze (float-write) | `SSE4.1` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Intel(R) Xeon(R) 6973P-C-AVX512): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.5% AND mean shift < 1% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them? We perform scalar iteration)

#### Note:
  These benchmarks were executed using the CPU benchmark library [benchmarksuite](https://github.com/realtimechris/benchmarksuite).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 807.058 | 0.48053 | 3.1708ms | 1811 | 30 | 3172.41 | 2140 | 3.02073 | 1(Win) |
| glaze | 241.553 | 0.129857 | 4.1962ms | 1811 | 30 | 2586.21 | 7150 | 10.1973 | 2(Loss) |
| simdjson (ondemand) | 152.257 | 0.0914729 | 5.2789ms | 1811 | 30 | 3229.89 | 11343.3 | 16.2378 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 384.87 | 1.71531 | 10.4526ms | 1811 | 64 | 379206 | 4487.5 | 6.37835 | 1(Tie) |
| glaze STATISTICAL TIE | 378.157 | 0.254579 | 6.0378ms | 1798 | 32 | 4264.11 | 4534.38 | 6.52312 | 1(Tie) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1513.76 | 0.372835 | 3.0407ms | 3873 | 30 | 2482.76 | 2440 | 1.62074 | 1(Win) |
| glaze | 1006.43 | 0.23187 | 3.3186ms | 3873 | 30 | 2172.41 | 3670 | 2.45424 | 2(Loss) |
| simdjson (ondemand) | 326.384 | 1.36769 | 5.004ms | 3873 | 30 | 718678 | 11316.7 | 7.59391 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2063.45 | 0.490258 | 3.0944ms | 3873 | 30 | 2310.34 | 1790 | 1.18193 | 1(Win) |
| glaze | 1262.04 | 0.280584 | 3.1601ms | 3873 | 30 | 2022.99 | 2926.67 | 1.93965 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1599.17 | 0.135685 | 5.0798ms | 3862 | 32 | 312.5 | 2303.12 | 1.52835 | 1(Win) |
| glaze | 872.383 | 0.295778 | 5.7497ms | 3862 | 32 | 4989.92 | 4221.88 | 2.82737 | 2(Loss) |
| simdjson (ondemand) | 326.998 | 0.0901341 | 4.9871ms | 3862 | 30 | 3091.95 | 11263.3 | 7.56004 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1785.02 | 0.492024 | 2.9811ms | 3862 | 30 | 3091.95 | 2063.33 | 1.37107 | 1(Win) |
| glaze | 1039.44 | 1.86853 | 3.3427ms | 3862 | 30 | 131506 | 3543.33 | 2.36371 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1120.88 | 1.10515 | 2.5326ms | 905 | 30 | 2172.41 | 770 | 2.1902 | 1(Win) |
| glaze | 220.172 | 0.189485 | 3.6613ms | 905 | 30 | 1655.17 | 3920 | 11.093 | 2(Loss) |
| simdjson (ondemand) | 94.616 | 0.0813962 | 8.8925ms | 905 | 32 | 1764.11 | 9121.88 | 26.1146 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 694.162 | 0.740096 | 2.4889ms | 905 | 30 | 2540.23 | 1243.33 | 3.53134 | 1(Win) |
| glaze | 199.632 | 0.212842 | 3.5997ms | 905 | 30 | 2540.23 | 4323.33 | 12.273 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2147.56 | 0.24525 | 3.5425ms | 9578 | 30 | 3264.37 | 4253.33 | 1.14521 | 1(Win) |
| glaze | 1271.6 | 0.134877 | 4.2032ms | 9578 | 30 | 2816.09 | 7183.33 | 1.94553 | 2(Loss) |
| simdjson (ondemand) | 582.049 | 1.01603 | 6.2586ms | 9578 | 30 | 762713 | 15693.3 | 4.25201 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2981.81 | 0.331407 | 3.3136ms | 9578 | 30 | 3091.95 | 3063.33 | 0.826498 | 1(Win) |
| glaze | 2632.36 | 0.281482 | 3.2569ms | 9578 | 30 | 2862.07 | 3470 | 0.933375 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3527.93 | 0.146306 | 4.6955ms | 33713 | 30 | 5333.33 | 9113.33 | 0.700355 | 1(Win) |
| simdjson (ondemand) | 2030.18 | 0.294286 | 6.3834ms | 33713 | 30 | 65160.9 | 15836.7 | 1.21881 | 2(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4273.65 | 0.452036 | 4.9305ms | 48024 | 30 | 70402.3 | 10716.7 | 0.578547 | 1(Win) |
| simdjson (ondemand) | 2595.84 | 0.298537 | 6.7597ms | 48024 | 30 | 83229.9 | 17643.3 | 0.95379 | 2(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1023.98 | 1.88375 | 189.312ms | 294588 | 32 | 8.54762e+08 | 274362 | 2.42106 | 1(Win) |
| jsonifier | 934.176 | 1.23658 | 78.0927ms | 294588 | 30 | 4.14892e+08 | 300737 | 2.65377 | 2(Loss) |
| simdjson (ondemand) | 578.048 | 1.09746 | 121.493ms | 294588 | 30 | 8.53495e+08 | 486017 | 4.28895 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3430.82 | 0.655127 | 52.0125ms | 294588 | 32 | 9.20952e+06 | 81887.5 | 0.722493 | 1(Win) |
| glaze | 2448.95 | 2.48349 | 1178.01ms | 294588 | 512 | 4.15592e+09 | 114719 | 1.01198 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1420.9 | 0.586725 | 69.0638ms | 406546 | 30 | 7.68921e+07 | 272863 | 1.7448 | 1(Win) |
| glaze | 1355.07 | 0.592956 | 70.7218ms | 406546 | 30 | 8.63499e+07 | 286120 | 1.82951 | 2(Loss) |
| simdjson (ondemand) | 801.224 | 0.673073 | 120.831ms | 406546 | 30 | 3.18241e+08 | 483900 | 3.09433 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3529.47 | 0.881037 | 67.0166ms | 406546 | 32 | 2.99735e+07 | 109850 | 0.702108 | 1(Win) |
| glaze | 2834.92 | 1.16822 | 38.9818ms | 406546 | 30 | 7.65796e+07 | 136763 | 0.874255 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3417.92 | 0.196969 | 4.7674ms | 33713 | 30 | 10298.9 | 9406.67 | 0.723851 | 1(Win) |
| simdjson (ondemand) | 1500.99 | 0.0755768 | 8.0319ms | 33713 | 30 | 7862.07 | 21420 | 1.65092 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4122.35 | 0.287401 | 5.004ms | 48024 | 30 | 30586.2 | 11110 | 0.599925 | 1(Win) |
| simdjson (ondemand) | 1701.52 | 0.246233 | 9.0167ms | 48024 | 30 | 131782 | 26916.7 | 1.45576 | 2(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1138.84 | 0.583893 | 62.8091ms | 294588 | 30 | 6.2243e+07 | 246690 | 2.17687 | 1(Win) |
| jsonifier | 1067.28 | 1.23509 | 65.8787ms | 294588 | 30 | 3.17097e+08 | 263230 | 2.32285 | 2(Loss) |
| simdjson (ondemand) | 145.232 | 0.460228 | 464.445ms | 294588 | 30 | 2.37778e+09 | 1.93443e+06 | 17.072 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3531.48 | 1.42149 | 23.1937ms | 294588 | 30 | 3.8364e+07 | 79553.3 | 0.701799 | 1(Win) |
| glaze | 2762.96 | 1.5078 | 66.4624ms | 294588 | 32 | 7.52177e+07 | 101681 | 0.896847 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1357.19 | 0.551162 | 72.12ms | 406546 | 30 | 7.43737e+07 | 285673 | 1.82654 | 1(Win) |
| jsonifier | 1320.88 | 1.03325 | 73.2707ms | 406546 | 30 | 2.7595e+08 | 293527 | 1.87682 | 2(Loss) |
| simdjson (ondemand) | 196.348 | 0.580423 | 469.115ms | 406546 | 30 | 3.94075e+09 | 1.97462e+06 | 12.6272 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3526.48 | 0.989013 | 30.7723ms | 406546 | 30 | 3.54701e+07 | 109943 | 0.702907 | 1(Win) |
| glaze | 2773.67 | 0.927065 | 39.5476ms | 406546 | 30 | 5.03794e+07 | 139783 | 0.893571 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 671.69 | 0.558718 | 35.2345ms | 94651 | 30 | 1.69129e+07 | 134387 | 3.69027 | 1(Win) |
| glaze | 584.602 | 2.006 | 385.862ms | 94651 | 128 | 1.22801e+09 | 154406 | 4.24024 | 2(Loss) |
| simdjson (ondemand) | 483.673 | 0.71049 | 48.4391ms | 94651 | 30 | 5.27455e+07 | 186627 | 5.12522 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3591.02 | 0.0646371 | 9.1135ms | 94651 | 30 | 7919.54 | 25136.7 | 0.68953 | 1(Win) |
| jsonifier | 2685.16 | 0.216813 | 11.0562ms | 94651 | 30 | 159368 | 33616.7 | 0.922408 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 872.867 | 0.871886 | 38.4973ms | 136024 | 30 | 5.03704e+07 | 148617 | 2.84039 | 1(Win) |
| glaze | 768.044 | 2.23284 | 207.759ms | 136024 | 64 | 9.10238e+08 | 168900 | 3.2274 | 2(Loss) |
| simdjson (ondemand) | 677.214 | 0.562022 | 48.9875ms | 136024 | 30 | 3.47702e+07 | 191553 | 3.66041 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3342.47 | 0.809229 | 12.4635ms | 136046 | 30 | 2.96006e+06 | 38816.7 | 0.741149 | 1(Win) |
| jsonifier | 2775.61 | 1.40735 | 14.285ms | 136024 | 30 | 1.2979e+07 | 46736.7 | 0.892449 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 501.401 | 2.02836 | 1004.91ms | 2090234 | 30 | 1.95087e+11 | 3.97566e+06 | 4.94448 | 1(Win) |
| glaze | 295.418 | 1.1826 | 1631.9ms | 2090234 | 30 | 1.91035e+11 | 6.74773e+06 | 8.39225 | 2(Loss) |
| simdjson (ondemand) | 213.457 | 1.04689 | 2269.54ms | 2090234 | 30 | 2.86744e+11 | 9.33866e+06 | 11.615 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 601.349 | 0.622579 | 798.062ms | 2090234 | 30 | 1.27776e+10 | 3.31489e+06 | 4.12226 | 1(Win) |
| glaze | 516.729 | 0.19209 | 931.182ms | 2090234 | 30 | 1.64739e+09 | 3.85773e+06 | 4.79748 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1183.03 | 1.30981 | 1321.7ms | 6661897 | 30 | 1.48438e+11 | 5.37034e+06 | 2.09566 | 1(Win) |
| glaze | 850.934 | 1.07226 | 1794.85ms | 6661897 | 30 | 1.92278e+11 | 7.46624e+06 | 2.91353 | 2(Loss) |
| simdjson (ondemand) | 638.22 | 0.838674 | 2386.32ms | 6661897 | 30 | 2.09104e+11 | 9.95469e+06 | 3.88472 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1114.44 | 0.0985427 | 1369.19ms | 6661897 | 30 | 9.46796e+08 | 5.7009e+06 | 2.22464 | 1(Win) |
| glaze | 793.822 | 0.0823776 | 1930.63ms | 6661897 | 30 | 1.30404e+09 | 8.00341e+06 | 3.12323 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1049.91 | 2.2408 | 112.841ms | 500299 | 30 | 3.11085e+09 | 454440 | 2.36093 | 1(Win) |
| glaze | 717.01 | 0.454961 | 163.604ms | 500299 | 30 | 2.74966e+08 | 665433 | 3.45785 | 2(Loss) |
| simdjson (ondemand) | 368.229 | 0.330211 | 314.551ms | 500299 | 30 | 5.49195e+08 | 1.29572e+06 | 6.73226 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4335.37 | 2.06631 | 30.1291ms | 500299 | 30 | 1.55138e+08 | 110053 | 0.571689 | 1(Win) |
| glaze | 2907.27 | 1.06048 | 43.5711ms | 500299 | 30 | 9.08688e+07 | 164113 | 0.852494 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1933.06 | 0.708638 | 175.304ms | 1439562 | 30 | 7.5987e+08 | 710207 | 1.28241 | 1(Win) |
| glaze | 1533.33 | 0.401836 | 218.139ms | 1439562 | 30 | 3.88338e+08 | 895357 | 1.61664 | 2(Loss) |
| simdjson (ondemand) | 948.816 | 0.293578 | 351.722ms | 1439562 | 30 | 5.41333e+08 | 1.44693e+06 | 2.6127 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1476.41 | 0.668357 | 227.763ms | 1439562 | 30 | 1.15873e+09 | 929870 | 1.67803 | 1(Win) |
| glaze | 813.643 | 1.01251 | 396.726ms | 1439584 | 30 | 8.75647e+09 | 1.68734e+06 | 3.04621 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1023.31 | 1.16317 | 15.5993ms | 56369 | 30 | 1.12016e+07 | 52533.3 | 2.4218 | 1(Tie) |
| glaze STATISTICAL TIE | 990.073 | 1.29833 | 15.4771ms | 56369 | 30 | 1.49086e+07 | 54296.7 | 2.5022 | 1(Tie) |
| simdjson (ondemand) | 420.551 | 1.91247 | 33.0904ms | 56369 | 30 | 1.79289e+08 | 127827 | 5.89433 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3900.19 | 0.163468 | 5.8355ms | 56369 | 30 | 15229.9 | 13783.3 | 0.634696 | 1(Win) |
| glaze | 3305.45 | 0.162771 | 7.0379ms | 56369 | 30 | 21023 | 16263.3 | 0.748953 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1383.39 | 1.10357 | 42.4431ms | 94370 | 32 | 1.64942e+07 | 65056.2 | 1.79138 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1382.67 | 1.28026 | 18.593ms | 94370 | 30 | 2.08327e+07 | 65090 | 1.79256 | 1(Tie) |
| simdjson (ondemand) | 681.667 | 0.591621 | 35.0374ms | 94370 | 30 | 1.83034e+07 | 132027 | 3.63594 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4304.76 | 0.157113 | 7.4973ms | 94370 | 30 | 32367.8 | 20906.7 | 0.57487 | 1(Win) |
| glaze | 2905.36 | 2.49851 | 9.9327ms | 94370 | 30 | 1.79701e+07 | 30976.7 | 0.852604 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 936.173 | 1.34512 | 16.4564ms | 52708 | 30 | 1.56489e+07 | 53693.3 | 2.64628 | 1(Win) |
| glaze | 774.002 | 1.05115 | 18.2877ms | 52708 | 30 | 1.39805e+07 | 64943.3 | 3.20131 | 2(Loss) |
| simdjson (ondemand) | 615.254 | 1.13321 | 23.0069ms | 52708 | 30 | 2.57152e+07 | 81700 | 4.02787 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3887.57 | 0.2135 | 6.007ms | 52708 | 30 | 22862.1 | 12930 | 0.636456 | 1(Win) |
| jsonifier | 3595.58 | 1.25142 | 5.7662ms | 52708 | 30 | 918207 | 13980 | 0.687939 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1086.61 | 1.15254 | 18.1828ms | 70103 | 30 | 1.50855e+07 | 61526.7 | 2.28032 | 1(Win) |
| glaze | 973.387 | 1.04586 | 19.4163ms | 70103 | 30 | 1.54801e+07 | 68683.3 | 2.54612 | 2(Loss) |
| simdjson (ondemand) | 779.837 | 0.758141 | 23.3857ms | 70103 | 30 | 1.26732e+07 | 85730 | 3.17784 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3862.24 | 0.413026 | 6.683ms | 70103 | 30 | 153345 | 17310 | 0.64107 | 1(Win) |
| glaze | 2652.01 | 1.35897 | 18.3818ms | 70103 | 32 | 3.75572e+06 | 25209.4 | 0.93341 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 781.554 | 0.0796516 | 6.1356ms | 11812 | 30 | 3954.02 | 14413.3 | 3.16752 | 1(Win) |
| glaze | 595.077 | 0.186382 | 6.96ms | 11812 | 30 | 37344.8 | 18930 | 4.16084 | 2(Loss) |
| simdjson (ondemand) | 368.975 | 0.0847906 | 9.9186ms | 11812 | 30 | 20103.4 | 30530 | 6.71303 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2701.39 | 0.307448 | 3.4085ms | 11812 | 30 | 4931.03 | 4170 | 0.909956 | 1(Win) |
| jsonifier | 2039.49 | 0.480845 | 3.562ms | 11812 | 30 | 21160.9 | 5523.33 | 1.20643 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1672.86 | 0.879923 | 6.8444ms | 31235 | 30 | 736506 | 17806.7 | 1.48108 | 1(Win) |
| glaze | 1236.19 | 0.146869 | 8.4406ms | 31235 | 30 | 37574.7 | 24096.7 | 2.00289 | 2(Loss) |
| simdjson (ondemand) | 877.064 | 1.84294 | 10.7868ms | 31235 | 30 | 1.17534e+07 | 33963.3 | 2.82477 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4644.7 | 0.144451 | 3.9537ms | 31235 | 30 | 2574.71 | 6413.33 | 0.530742 | 1(Win) |
| glaze | 3640.08 | 0.176583 | 4.5815ms | 31235 | 30 | 6264.37 | 8183.33 | 0.677443 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1967.16 | 1.79292 | 15.3912ms | 108313 | 30 | 2.65906e+07 | 52510 | 1.2593 | 1(Win) |
| glaze | 1050.5 | 0.726045 | 27.4513ms | 108313 | 30 | 1.52904e+07 | 98330 | 2.35955 | 2(Loss) |
| simdjson (ondemand) | 481.167 | 0.4566 | 54.6389ms | 108313 | 30 | 2.88246e+07 | 214677 | 5.15226 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3979.11 | 0.684012 | 19.5479ms | 108313 | 32 | 1.00894e+06 | 25959.4 | 0.622404 | 1(Win) |
| glaze | 3228.99 | 2.45076 | 10.0746ms | 108313 | 30 | 1.84396e+07 | 31990 | 0.766949 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2320.7 | 0.84391 | 24.3322ms | 213963 | 30 | 1.65179e+07 | 87926.7 | 1.06797 | 1(Win) |
| glaze | 1555.74 | 0.851554 | 34.3109ms | 213963 | 30 | 3.74239e+07 | 131160 | 1.59329 | 2(Loss) |
| simdjson (ondemand) | 891.948 | 0.467733 | 58.069ms | 213963 | 30 | 3.43491e+07 | 228770 | 2.77927 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5416.8 | 1.68025 | 11.7139ms | 213963 | 30 | 1.20187e+07 | 37670 | 0.457107 | 1(Win) |
| glaze | 3283.91 | 1.55757 | 17.5527ms | 213963 | 30 | 2.81003e+07 | 62136.7 | 0.754496 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 532.152 | 1.19648 | 800.669ms | 1834197 | 30 | 4.64036e+10 | 3.28708e+06 | 4.65828 | 1(Win) |
| glaze | 231.95 | 0.880777 | 1798.29ms | 1834197 | 30 | 1.3236e+11 | 7.5414e+06 | 10.6888 | 2(Loss) |
| simdjson (ondemand) | 184.891 | 0.672459 | 2261.19ms | 1834197 | 30 | 1.21426e+11 | 9.46083e+06 | 13.4095 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 381.035 | 0.722453 | 1113.69ms | 1833577 | 30 | 3.29769e+10 | 4.58917e+06 | 6.50631 | 1(Win) |
| jsonifier | 322.069 | 0.397853 | 1308.22ms | 1834197 | 30 | 1.40075e+10 | 5.43121e+06 | 7.69768 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1669.51 | 1.32868 | 1469.06ms | 9930848 | 30 | 1.70435e+11 | 5.67281e+06 | 1.48496 | 1(Win) |
| glaze | 1162.31 | 0.732971 | 2117.41ms | 9930848 | 30 | 1.0701e+11 | 8.14825e+06 | 2.13304 | 2(Loss) |
| simdjson (ondemand) | 888.252 | 0.785169 | 2579.25ms | 9930848 | 30 | 2.10256e+11 | 1.06623e+07 | 2.7912 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 991.252 | 0.62214 | 2272.28ms | 9930848 | 30 | 1.05999e+11 | 9.55438e+06 | 2.50121 | 1(Win) |
| glaze | 566.589 | 0.0862998 | 4026.92ms | 9930228 | 30 | 6.242e+09 | 1.67144e+07 | 4.376 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1077.57 | 0.564859 | 137.414ms | 642697 | 30 | 3.09686e+08 | 568800 | 2.30033 | 1(Win) |
| glaze | 584.713 | 0.342664 | 279.609ms | 642697 | 30 | 3.87065e+08 | 1.04825e+06 | 4.23965 | 2(Loss) |
| simdjson (ondemand) | 384.021 | 0.275479 | 390.012ms | 642697 | 30 | 5.79964e+08 | 1.59607e+06 | 6.45456 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 440.681 | 0.243779 | 335.693ms | 642697 | 30 | 3.44888e+08 | 1.39086e+06 | 5.62366 | 1(Win) |
| glaze | 390.846 | 0.888415 | 364.942ms | 642692 | 30 | 5.82302e+09 | 1.56819e+06 | 6.34073 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1517.6 | 0.826751 | 192.507ms | 1225964 | 30 | 1.21706e+09 | 770407 | 1.63318 | 1(Win) |
| glaze | 1002.85 | 0.247563 | 285.785ms | 1225964 | 30 | 2.49905e+08 | 1.16585e+06 | 2.47162 | 2(Loss) |
| simdjson (ondemand) | 711.417 | 0.237655 | 400.207ms | 1225964 | 30 | 4.57638e+08 | 1.64344e+06 | 3.48394 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 755.065 | 0.32902 | 372.839ms | 1225970 | 30 | 7.78676e+08 | 1.54844e+06 | 3.28209 | 1(Win) |
| jsonifier | 678.501 | 0.240787 | 414.435ms | 1225964 | 30 | 5.16467e+08 | 1.72317e+06 | 3.65277 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 658.965 | 0.604077 | 145.566ms | 409725 | 30 | 3.84916e+08 | 592967 | 3.76227 | 1(Win) |
| glaze | 437.359 | 1.06063 | 207.963ms | 409725 | 30 | 2.69373e+09 | 893417 | 5.66732 | 2(Loss) |
| simdjson (ondemand) | 359.129 | 0.482788 | 288.523ms | 409725 | 30 | 8.27789e+08 | 1.08803e+06 | 6.90272 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2028.72 | 1.34332 | 49.4569ms | 409725 | 30 | 2.00828e+08 | 192607 | 1.22142 | 1(Win) |
| jsonifier | 448.707 | 1.0706 | 217.852ms | 409725 | 30 | 2.60758e+09 | 870823 | 5.52176 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1021.11 | 1.78193 | 176.406ms | 785750 | 30 | 5.13011e+09 | 733860 | 2.42769 | 1(Win) |
| glaze | 757.814 | 0.91536 | 241.157ms | 785750 | 30 | 2.45781e+09 | 988830 | 3.27116 | 2(Loss) |
| simdjson (ondemand) | 649.511 | 0.383746 | 306.406ms | 785750 | 30 | 5.88036e+08 | 1.15371e+06 | 3.81681 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1054.35 | 0.491178 | 176.021ms | 785750 | 30 | 3.65595e+08 | 710723 | 2.34924 | 1(Win) |
| jsonifier | 800.02 | 0.354539 | 227.74ms | 785750 | 30 | 3.3084e+08 | 936663 | 3.09695 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 677.981 | 2.04081 | 3021.18ms | 8587914 | 30 | 1.82335e+12 | 1.20801e+07 | 3.65694 | 1(Win) |
| glaze STATISTICAL TIE | 455.738 | 1.28523 | 4235.06ms | 8587914 | 30 | 1.6004e+12 | 1.7971e+07 | 5.4404 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 450.73 | 1.34905 | 4313.43ms | 8587914 | 30 | 1.80269e+12 | 1.81707e+07 | 5.50069 | 2(Tie) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 668.197 | 0.262214 | 2921.03ms | 8588126 | 30 | 3.09899e+10 | 1.22573e+07 | 3.71037 | 1(Win) |
| jsonifier | 482.512 | 0.407404 | 4105.13ms | 8588126 | 30 | 1.43467e+11 | 1.69742e+07 | 5.13851 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 653.247 | 1.73951 | 3512.29ms | 9804437 | 30 | 1.8598e+12 | 1.43135e+07 | 3.79536 | 1(Win) |
| glaze | 485.444 | 0.581828 | 4746.16ms | 9804437 | 30 | 3.76772e+11 | 1.92612e+07 | 5.10742 | 2(Loss) |
| simdjson (ondemand) | 454.558 | 1.14369 | 5027.63ms | 9804437 | 30 | 1.66038e+12 | 2.057e+07 | 5.45399 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 739.627 | 0.278961 | 3468.25ms | 11078090 | 30 | 4.76336e+10 | 1.42841e+07 | 3.35216 | 1(Win) |
| jsonifier | 560.335 | 0.1422 | 4517.68ms | 11078090 | 30 | 2.15654e+10 | 1.88546e+07 | 4.42483 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3600.35 | 0.804083 | 19.8701ms | 264040 | 30 | 9.488e+06 | 69940 | 0.688255 | 1(Win) |
| simdjson (ondemand) | 2058.88 | 1.12702 | 32.138ms | 264040 | 30 | 5.69983e+07 | 122303 | 1.20396 | 2(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4771.32 | 0.813991 | 22.6472ms | 399947 | 30 | 1.27025e+07 | 79940 | 0.519402 | 1(Win) |
| simdjson (ondemand) | 2710.48 | 0.83443 | 36.431ms | 399947 | 30 | 4.1363e+07 | 140720 | 0.914583 | 2(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1109.16 | 0.956688 | 59.5275ms | 264040 | 30 | 1.41519e+08 | 227027 | 2.23521 | 1(Win) |
| glaze | 654.546 | 0.944802 | 97.1246ms | 264040 | 30 | 3.96335e+08 | 384707 | 3.78734 | 2(Loss) |
| simdjson (ondemand) | 520.079 | 0.653109 | 118.853ms | 264040 | 30 | 2.99981e+08 | 484173 | 4.76682 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3694.73 | 1.87806 | 19.7158ms | 264040 | 30 | 4.91488e+07 | 68153.3 | 0.670636 | 1(Win) |
| glaze | 2785.08 | 2.34619 | 24.2589ms | 263923 | 30 | 1.34874e+08 | 90373.3 | 0.889974 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1218.33 | 1.08668 | 79.0658ms | 399947 | 30 | 3.47217e+08 | 313067 | 2.03472 | 1(Win) |
| glaze | 847.95 | 0.878221 | 112.968ms | 399947 | 30 | 4.68159e+08 | 449813 | 2.92361 | 2(Loss) |
| simdjson (ondemand) | 749.095 | 0.728004 | 126.441ms | 399947 | 30 | 4.12211e+08 | 509173 | 3.30908 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3982.38 | 1.76676 | 26.9548ms | 399947 | 30 | 8.59005e+07 | 95776.7 | 0.622318 | 1(Win) |
| glaze | 2775.3 | 1.87081 | 37.3876ms | 399830 | 30 | 1.98205e+08 | 137393 | 0.892938 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1947.58 | 1.26405 | 57.1754ms | 466906 | 30 | 2.50564e+08 | 228630 | 1.27235 | 1(Win) |
| glaze | 1349.59 | 0.625549 | 81.9256ms | 466906 | 30 | 1.2779e+08 | 329933 | 1.83699 | 2(Loss) |
| simdjson (ondemand) | 822.494 | 0.512052 | 134.83ms | 466906 | 30 | 2.30538e+08 | 541373 | 3.01355 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2622.01 | 1.15926 | 64.2354ms | 699405 | 30 | 2.60898e+08 | 254387 | 0.945161 | 1(Win) |
| glaze | 2129.06 | 0.705825 | 78.5776ms | 699405 | 30 | 1.46689e+08 | 313287 | 1.16441 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2514.9 | 0.505924 | 60.3894ms | 631514 | 30 | 4.4037e+07 | 239477 | 0.985561 | 1(Win) |
| glaze | 2029.04 | 0.563632 | 72.3908ms | 631514 | 30 | 8.39651e+07 | 296820 | 1.22173 | 2(Loss) |
