# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26200 using the MSVC 19.44.35228.0 compiler).  

Latest Results: (Aug 07, 2026)
#### Using the following commits:
----
| Jsonifier: [e32235c](https://github.com/nihilai-collective/jsonifier/commit/e32235c)  
| Glaze: [2f6f5dc](https://github.com/stephenberry/glaze/commit/2f6f5dc)  
| Simdjson: [b3072d2](https://github.com/simdjson/simdjson/commit/b3072d2)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX2` |
| simdjson (ondemand) | `haswell` |
| Glaze (utf8-validation) | `SSSE3` |
| Glaze (string-escape) | `SSE2` |
| Glaze (float-write) | `SSE4.1` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.5% AND mean shift < 1% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them? We perform scalar iteration)

#### Note:
  These benchmarks were executed using the CPU benchmark library [benchmarksuite](https://github.com/realtimechris/benchmarksuite).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1029.19 | 0.44245 | 2.6434ms | 1811 | 32 | 1764.11 | 1678.12 | 2.89267 | 1(Win) |
| glaze | 347.739 | 0.17625 | 2.2934ms | 1811 | 30 | 2298.85 | 4966.67 | 8.71839 | 2(Loss) |
| simdjson (ondemand) | 183.308 | 2.1199 | 6.9997ms | 1811 | 32 | 1.2766e+06 | 9421.88 | 16.545 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 568.75 | 0.797051 | 1.8301ms | 1811 | 30 | 17574.7 | 3036.67 | 5.30502 | 1(Win) |
| glaze | 366.018 | 1.81897 | 27.4148ms | 1798 | 256 | 1.85894e+06 | 4684.77 | 8.24103 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2159.99 | 0.325781 | 1.5245ms | 3873 | 30 | 931.034 | 1710 | 1.39032 | 1(Win) |
| glaze | 1331.82 | 0.296097 | 1.818ms | 3873 | 30 | 2022.99 | 2773.33 | 2.26674 | 2(Loss) |
| simdjson (ondemand) | 389.755 | 0.0828776 | 3.4446ms | 3873 | 30 | 1850.57 | 9476.67 | 7.77884 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2970.71 | 0.740096 | 1.5466ms | 3873 | 30 | 2540.23 | 1243.33 | 0.989999 | 1(Win) |
| glaze | 1352.34 | 1.32988 | 3.2336ms | 3873 | 32 | 42217.7 | 2731.25 | 2.21897 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2194.77 | 0.44245 | 2.6048ms | 3862 | 32 | 1764.11 | 1678.12 | 1.35586 | 1(Win) |
| glaze | 1323.27 | 0.248639 | 1.8892ms | 3862 | 30 | 1436.78 | 2783.33 | 2.26444 | 2(Loss) |
| simdjson (ondemand) | 375.706 | 0.552462 | 7.2011ms | 3862 | 32 | 93860.9 | 9803.12 | 8.05954 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2819.59 | 0.478469 | 2.4679ms | 3862 | 32 | 1250 | 1306.25 | 1.05018 | 1(Win) |
| glaze | 1352.42 | 1.40497 | 1.755ms | 3862 | 30 | 43919.5 | 2723.33 | 2.22153 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1307.69 | 1.37836 | 1.3176ms | 905 | 30 | 2482.76 | 660 | 2.25621 | 1(Win) |
| glaze | 375.25 | 2.11166 | 2.9771ms | 905 | 32 | 75483.9 | 2300 | 8.03253 | 2(Loss) |
| simdjson (ondemand) | 145.093 | 1.97419 | 17.6646ms | 905 | 128 | 1.76519e+06 | 5948.44 | 20.8877 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1409.1 | 0.969777 | 1.9476ms | 905 | 32 | 1129.03 | 612.5 | 2.08139 | 1(Win) |
| glaze | 376.786 | 0.359281 | 3.0105ms | 905 | 32 | 2167.34 | 2290.62 | 7.96312 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2998.13 | 0.304074 | 1.9674ms | 9578 | 30 | 2574.71 | 3046.67 | 1.00547 | 1(Win) |
| glaze | 1920.31 | 0.193452 | 2.2877ms | 9578 | 30 | 2540.23 | 4756.67 | 1.57294 | 2(Loss) |
| simdjson (ondemand) | 840.837 | 0.0823739 | 3.8393ms | 9578 | 30 | 2402.3 | 10863.3 | 3.60777 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4315.41 | 0.326951 | 1.7068ms | 9578 | 30 | 1436.78 | 2116.67 | 0.699555 | 1(Win) |
| glaze | 3164.3 | 1.60807 | 1.8848ms | 9578 | 30 | 64643.7 | 2886.67 | 0.950171 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3673.03 | 0.237077 | 3.3831ms | 33713 | 30 | 12919.5 | 8753.33 | 0.826594 | 1(Win) |
| simdjson (ondemand) | 1358.89 | 2.13758 | 6.8148ms | 33713 | 30 | 7.67352e+06 | 23660 | 2.23444 | 2(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4732.24 | 0.137115 | 7.3489ms | 48024 | 32 | 5635.08 | 9678.12 | 0.641476 | 1(Win) |
| simdjson (ondemand) | 1869.61 | 1.88279 | 7.0477ms | 48024 | 30 | 6.38171e+06 | 24496.7 | 1.62436 | 2(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1198.23 | 1.41254 | 57.6042ms | 294588 | 30 | 3.29058e+08 | 234463 | 2.53506 | 1(Tie) |
| glaze STATISTICAL TIE | 1160.1 | 1.66291 | 66.7124ms | 294588 | 30 | 4.86517e+08 | 242170 | 2.61883 | 1(Tie) |
| simdjson (ondemand) | 724.106 | 0.898098 | 93.6774ms | 294588 | 30 | 3.64246e+08 | 387983 | 4.19665 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4768.72 | 1.46857 | 15.794ms | 294588 | 30 | 2.24564e+07 | 58913.3 | 0.637025 | 1(Win) |
| glaze | 3032.42 | 2.01602 | 935.617ms | 294588 | 512 | 1.78612e+09 | 92645.9 | 1.00149 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1814.11 | 0.3577 | 55.0229ms | 406546 | 30 | 1.75327e+07 | 213720 | 1.67504 | 1(Win) |
| glaze | 1656.63 | 1.16882 | 57.7807ms | 406546 | 30 | 2.24484e+08 | 234037 | 1.83435 | 2(Loss) |
| simdjson (ondemand) | 1005.18 | 0.468211 | 95.6271ms | 406546 | 30 | 9.7844e+07 | 385713 | 3.02336 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4583.79 | 0.984222 | 21.9374ms | 406546 | 30 | 2.07911e+07 | 84583.3 | 0.662774 | 1(Win) |
| glaze | 3389.36 | 2.24822 | 579.295ms | 406546 | 256 | 1.69318e+09 | 114391 | 0.896041 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3581.69 | 2.25258 | 13.217ms | 33713 | 64 | 2.61674e+06 | 8976.56 | 0.846771 | 1(Win) |
| simdjson (ondemand) | 733.99 | 1.48341 | 11.7336ms | 33713 | 30 | 1.26665e+07 | 43803.3 | 4.13882 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4605.83 | 1.83973 | 7.2626ms | 48024 | 32 | 1.07093e+06 | 9943.75 | 0.657969 | 1(Win) |
| simdjson (ondemand) | 1027.12 | 1.15136 | 12.2543ms | 48024 | 30 | 7.90714e+06 | 44590 | 2.95746 | 2(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1376.31 | 0.583868 | 51.1592ms | 294588 | 30 | 4.26137e+07 | 204127 | 2.20775 | 1(Tie) |
| glaze STATISTICAL TIE | 1363.11 | 0.705596 | 50.9578ms | 294588 | 30 | 6.34459e+07 | 206103 | 2.22927 | 1(Tie) |
| simdjson (ondemand) | 69.3505 | 0.17084 | 980.491ms | 294588 | 30 | 1.43692e+09 | 4.05103e+06 | 43.8272 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4829.93 | 2.15128 | 15.5495ms | 294588 | 30 | 4.69747e+07 | 58166.7 | 0.629013 | 1(Win) |
| glaze | 3152.68 | 2.09165 | 919.171ms | 294588 | 512 | 1.77876e+09 | 89111.7 | 0.96337 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1680.4 | 0.686432 | 57.1957ms | 406546 | 30 | 7.5251e+07 | 230727 | 1.80846 | 1(Win) |
| jsonifier | 1618.41 | 0.701702 | 59.3468ms | 406546 | 30 | 8.47748e+07 | 239563 | 1.87762 | 2(Loss) |
| simdjson (ondemand) | 94.9151 | 0.20067 | 982.609ms | 406546 | 30 | 2.01575e+09 | 4.08483e+06 | 32.0226 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4391.68 | 1.5768 | 22.998ms | 406546 | 30 | 5.81345e+07 | 88283.3 | 0.691775 | 1(Win) |
| glaze | 3684.31 | 0.943565 | 29.3387ms | 406546 | 30 | 2.95782e+07 | 105233 | 0.824618 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 817.826 | 1.39307 | 27.9244ms | 94651 | 30 | 7.09248e+07 | 110373 | 3.71509 | 1(Win) |
| glaze | 659.321 | 1.87802 | 165.281ms | 94651 | 64 | 4.23094e+08 | 136908 | 4.60803 | 2(Loss) |
| simdjson (ondemand) | 580.192 | 1.86652 | 39.7775ms | 94651 | 30 | 2.52984e+08 | 155580 | 5.23682 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 4777.57 | 0.978403 | 12.6983ms | 94651 | 32 | 1.09351e+06 | 18893.8 | 0.635367 | 1(Win) |
| jsonifier | 3792.7 | 2.04822 | 6.9959ms | 94651 | 30 | 7.12897e+06 | 23800 | 0.80085 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1032.88 | 1.88028 | 31.2447ms | 136024 | 30 | 1.67302e+08 | 125593 | 2.94172 | 1(Win) |
| glaze | 987.234 | 0.782181 | 32.8096ms | 136024 | 30 | 3.16903e+07 | 131400 | 3.07791 | 2(Loss) |
| simdjson (ondemand) | 819.957 | 1.68182 | 40.8973ms | 136024 | 30 | 2.12388e+08 | 158207 | 3.70589 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 4421.98 | 1.70363 | 18.9495ms | 136046 | 32 | 7.99539e+06 | 29340.6 | 0.686542 | 1(Win) |
| jsonifier | 3689.56 | 1.22991 | 21.8599ms | 136024 | 32 | 5.98378e+06 | 35159.4 | 0.823215 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 605.355 | 1.06396 | 830.123ms | 2090234 | 30 | 3.6825e+10 | 3.29295e+06 | 5.02015 | 1(Win) |
| glaze | 361.624 | 0.90453 | 1325.66ms | 2090234 | 30 | 7.45834e+10 | 5.51236e+06 | 8.40396 | 2(Loss) |
| simdjson (ondemand) | 262.937 | 0.391243 | 1831.57ms | 2090234 | 30 | 2.63937e+10 | 7.58129e+06 | 11.5584 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1027.47 | 0.420841 | 469.504ms | 2090234 | 30 | 1.9999e+09 | 1.94011e+06 | 2.95763 | 1(Win) |
| glaze | 725.564 | 0.232018 | 663.197ms | 2090234 | 30 | 1.219e+09 | 2.74738e+06 | 4.18853 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1531.88 | 0.820651 | 1009.43ms | 6661897 | 30 | 3.47524e+10 | 4.14737e+06 | 1.98363 | 1(Win) |
| glaze | 1003.53 | 0.612078 | 1523.23ms | 6661897 | 30 | 4.50476e+10 | 6.33094e+06 | 3.0283 | 2(Loss) |
| simdjson (ondemand) | 800.491 | 0.366052 | 1913.95ms | 6661897 | 30 | 2.53215e+10 | 7.93673e+06 | 3.79664 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1926.41 | 0.344612 | 798.683ms | 6661897 | 30 | 3.87508e+09 | 3.29799e+06 | 1.57756 | 1(Win) |
| glaze | 1178.86 | 0.254645 | 1274.87ms | 6661897 | 30 | 5.65013e+09 | 5.38932e+06 | 2.57795 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1356.64 | 0.731774 | 86.2299ms | 500299 | 30 | 1.98703e+08 | 351693 | 2.24 | 1(Win) |
| glaze | 849.184 | 0.359029 | 137.791ms | 500299 | 30 | 1.22078e+08 | 561860 | 3.57868 | 2(Loss) |
| simdjson (ondemand) | 425.156 | 0.454338 | 270.434ms | 500299 | 30 | 7.79908e+08 | 1.12223e+06 | 7.14816 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4790.22 | 1.26563 | 25.4998ms | 500299 | 30 | 4.76741e+07 | 99603.3 | 0.634214 | 1(Win) |
| glaze | 4295.3 | 2.36957 | 27.8443ms | 500299 | 30 | 2.07841e+08 | 111080 | 0.707272 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2668.38 | 0.449056 | 125.024ms | 1439562 | 30 | 1.60136e+08 | 514497 | 1.13871 | 1(Win) |
| glaze | 1769.87 | 0.370412 | 187.168ms | 1439562 | 30 | 2.47668e+08 | 775693 | 1.71702 | 2(Loss) |
| simdjson (ondemand) | 1156.65 | 0.350859 | 286.398ms | 1439562 | 30 | 5.20285e+08 | 1.18694e+06 | 2.62742 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2578.07 | 1.02833 | 125.275ms | 1439562 | 30 | 8.99613e+08 | 532520 | 1.17819 | 1(Win) |
| glaze | 1329.41 | 0.626104 | 248.618ms | 1439584 | 30 | 1.2542e+09 | 1.03271e+06 | 2.28546 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1295.68 | 2.47207 | 11.4342ms | 56369 | 30 | 3.15596e+07 | 41490 | 2.34346 | 1(Win) |
| glaze | 1132.38 | 1.56042 | 12.5178ms | 56369 | 30 | 1.64627e+07 | 47473.3 | 2.68255 | 2(Loss) |
| simdjson (ondemand) | 534.548 | 1.00031 | 25.749ms | 56369 | 30 | 3.03595e+07 | 100567 | 5.68393 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4710.08 | 0.236647 | 4.2446ms | 56369 | 30 | 21885.1 | 11413.3 | 0.644946 | 1(Win) |
| glaze | 4264.37 | 1.96319 | 8.9682ms | 56369 | 32 | 1.95996e+06 | 12606.2 | 0.711418 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1726.53 | 1.62441 | 13.9551ms | 94370 | 30 | 2.15096e+07 | 52126.7 | 1.75875 | 1(Tie) |
| glaze STATISTICAL TIE | 1684.87 | 1.52787 | 32.4747ms | 94370 | 32 | 2.13136e+07 | 53415.6 | 1.80287 | 1(Tie) |
| simdjson (ondemand) | 859.418 | 1.25738 | 26.7265ms | 94370 | 30 | 5.20134e+07 | 104720 | 3.53539 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5296.94 | 1.73459 | 22.68ms | 94370 | 64 | 5.55896e+06 | 16990.6 | 0.57303 | 1(Win) |
| glaze | 4041.46 | 1.88365 | 29.3998ms | 94370 | 64 | 1.12609e+07 | 22268.8 | 0.751267 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1169.92 | 1.51141 | 26.5817ms | 52708 | 32 | 1.34946e+07 | 42965.6 | 2.59663 | 1(Win) |
| glaze | 965.359 | 1.44182 | 14.2329ms | 52708 | 30 | 1.69091e+07 | 52070 | 3.14672 | 2(Loss) |
| simdjson (ondemand) | 748.084 | 2.4281 | 17.3506ms | 52708 | 30 | 7.98558e+07 | 67193.3 | 4.05991 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5722.91 | 0.110307 | 3.6866ms | 52708 | 30 | 2816.09 | 8783.33 | 0.529225 | 1(Win) |
| glaze | 4928.07 | 1.11138 | 3.8736ms | 52708 | 30 | 385517 | 10200 | 0.614925 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1286.92 | 1.30528 | 14.3021ms | 70103 | 30 | 1.37943e+07 | 51950 | 2.36012 | 1(Win) |
| glaze | 1170.44 | 1.7736 | 15.3627ms | 70103 | 30 | 3.07899e+07 | 57120 | 2.59568 | 2(Loss) |
| simdjson (ondemand) | 1000.38 | 1.62821 | 17.4171ms | 70103 | 30 | 3.55208e+07 | 66830 | 3.03705 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5528.1 | 0.703408 | 8.7641ms | 70103 | 32 | 231573 | 12093.8 | 0.549038 | 1(Win) |
| glaze | 3457.57 | 2.27123 | 50.9311ms | 70103 | 128 | 2.46866e+07 | 19335.9 | 0.877908 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1091.19 | 2.06702 | 14.7676ms | 11812 | 64 | 2.9142e+06 | 10323.4 | 2.78065 | 1(Win) |
| glaze | 758.743 | 1.00203 | 4.8338ms | 11812 | 30 | 663954 | 14846.7 | 4.00141 | 2(Loss) |
| simdjson (ondemand) | 449.468 | 1.77173 | 16.161ms | 11812 | 32 | 6.30952e+06 | 25062.5 | 6.75693 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3663.35 | 0.50583 | 3.5048ms | 11812 | 32 | 7741.94 | 3075 | 0.823225 | 1(Win) |
| glaze | 3382.82 | 0.458716 | 2.0828ms | 11812 | 30 | 7000 | 3330 | 0.895284 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2113.12 | 1.99879 | 4.4202ms | 31235 | 30 | 2.38171e+06 | 14096.7 | 1.43693 | 1(Win) |
| glaze | 1591.52 | 0.1451 | 5.9339ms | 31235 | 30 | 22126.4 | 18716.7 | 1.90645 | 2(Loss) |
| simdjson (ondemand) | 1105.58 | 1.80573 | 7.6561ms | 31235 | 30 | 7.10116e+06 | 26943.3 | 2.74715 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 4899.34 | 0.183252 | 2.657ms | 31235 | 30 | 3724.14 | 6080 | 0.618116 | 1(Tie) |
| glaze STATISTICAL TIE | 4714.23 | 2.32594 | 19.7714ms | 31235 | 128 | 2.76484e+06 | 6318.75 | 0.642239 | 1(Tie) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2505.75 | 1.44904 | 11.5287ms | 108313 | 30 | 1.07046e+07 | 41223.3 | 1.21164 | 1(Win) |
| glaze | 1246.22 | 1.00737 | 21.8792ms | 108313 | 30 | 2.09157e+07 | 82886.7 | 2.43826 | 2(Loss) |
| simdjson (ondemand) | 592.165 | 1.4329 | 43.5152ms | 108313 | 30 | 1.87424e+08 | 174437 | 5.13127 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4909.33 | 0.624312 | 14.1083ms | 108313 | 32 | 552167 | 21040.6 | 0.618474 | 1(Win) |
| glaze | 4239.21 | 2.4203 | 7.2372ms | 108313 | 30 | 1.0434e+07 | 24366.7 | 0.716526 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2676.78 | 1.91109 | 19.909ms | 213963 | 30 | 6.36698e+07 | 76230 | 1.13516 | 1(Win) |
| glaze | 1898.27 | 0.934919 | 27.322ms | 213963 | 30 | 3.02993e+07 | 107493 | 1.60066 | 2(Loss) |
| simdjson (ondemand) | 1113.07 | 1.31326 | 45.3528ms | 213963 | 30 | 1.73883e+08 | 183323 | 2.72986 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6000.32 | 1.92797 | 9.3291ms | 213963 | 30 | 1.28958e+07 | 34006.7 | 0.506024 | 1(Win) |
| glaze | 3600.48 | 2.4697 | 14.7685ms | 213963 | 30 | 5.87717e+07 | 56673.3 | 0.843634 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 648.865 | 0.786805 | 653.835ms | 1834197 | 30 | 1.3497e+10 | 2.69582e+06 | 4.6828 | 1(Win) |
| glaze | 274.454 | 0.607886 | 1507.78ms | 1834197 | 30 | 4.50316e+10 | 6.37347e+06 | 11.0733 | 2(Loss) |
| simdjson (ondemand) | 220.323 | 0.327848 | 1909.26ms | 1834197 | 30 | 2.03254e+10 | 7.93937e+06 | 13.7943 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 659.38 | 0.259129 | 637.304ms | 1834197 | 30 | 1.41767e+09 | 2.65284e+06 | 4.60901 | 1(Win) |
| glaze | 532.914 | 0.256505 | 789.529ms | 1833577 | 30 | 2.12519e+09 | 3.28127e+06 | 5.70279 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2396.53 | 0.417341 | 951.268ms | 9930848 | 30 | 8.16036e+09 | 3.95187e+06 | 1.26811 | 1(Win) |
| glaze | 1310.61 | 0.56954 | 1725.33ms | 9930848 | 30 | 5.08156e+10 | 7.22626e+06 | 2.31885 | 2(Loss) |
| simdjson (ondemand) | 1122.13 | 0.334171 | 2019.39ms | 9930848 | 30 | 2.3864e+10 | 8.44001e+06 | 2.70835 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1799.81 | 0.204837 | 1267.33ms | 9930848 | 30 | 3.48545e+09 | 5.26212e+06 | 1.68855 | 1(Win) |
| glaze | 893.475 | 0.324729 | 2489.58ms | 9930228 | 30 | 3.554e+10 | 1.05993e+07 | 3.4016 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1331.98 | 0.663112 | 111.493ms | 642697 | 30 | 2.79327e+08 | 460160 | 2.28128 | 1(Win) |
| glaze | 661.034 | 0.966745 | 223.573ms | 642697 | 30 | 2.41052e+09 | 927220 | 4.59706 | 2(Loss) |
| simdjson (ondemand) | 471.857 | 0.344067 | 314.49ms | 642697 | 30 | 5.99239e+08 | 1.29896e+06 | 6.44063 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1302.05 | 0.81207 | 114.352ms | 642697 | 30 | 4.38393e+08 | 470737 | 2.3337 | 1(Win) |
| glaze | 618.39 | 0.414231 | 239.614ms | 642692 | 30 | 5.05695e+08 | 991153 | 4.91334 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1896.79 | 0.504002 | 150.089ms | 1225964 | 30 | 2.89536e+08 | 616393 | 1.60206 | 1(Win) |
| glaze | 1163.04 | 1.19967 | 239.987ms | 1225964 | 30 | 4.36327e+09 | 1.00527e+06 | 2.61287 | 2(Loss) |
| simdjson (ondemand) | 876.429 | 0.706032 | 321.697ms | 1225964 | 30 | 2.66129e+09 | 1.33402e+06 | 3.46747 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1420.79 | 0.607102 | 200.342ms | 1225964 | 30 | 7.4876e+08 | 822903 | 2.13826 | 1(Win) |
| glaze | 1160.79 | 0.337114 | 243.347ms | 1225970 | 30 | 3.4588e+08 | 1.00722e+06 | 2.6175 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 829.547 | 0.796746 | 114.108ms | 409725 | 30 | 4.22537e+08 | 471033 | 3.66315 | 1(Win) |
| glaze | 559.226 | 0.523462 | 169.688ms | 409725 | 30 | 4.01331e+08 | 698723 | 5.434 | 2(Loss) |
| simdjson (ondemand) | 450.536 | 0.415028 | 210.262ms | 409725 | 30 | 3.88689e+08 | 867287 | 6.74495 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2844.95 | 0.8794 | 34.8915ms | 409725 | 30 | 4.37653e+07 | 137347 | 1.06771 | 1(Win) |
| jsonifier | 2405.96 | 1.07758 | 39.7144ms | 409725 | 30 | 9.1882e+07 | 162407 | 1.26275 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1251.38 | 0.558744 | 143.111ms | 785750 | 30 | 3.35841e+08 | 598817 | 2.42816 | 1(Win) |
| glaze | 913.395 | 1.14494 | 194.723ms | 785750 | 30 | 2.64693e+09 | 820400 | 3.32691 | 2(Loss) |
| simdjson (ondemand) | 821.412 | 1.10415 | 216.793ms | 785750 | 30 | 3.04388e+09 | 912270 | 3.69958 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3148.13 | 1.37492 | 57.9809ms | 785750 | 30 | 3.21321e+08 | 238030 | 0.965008 | 1(Win) |
| glaze | 1759.5 | 1.0034 | 104.509ms | 785750 | 30 | 5.47848e+08 | 425887 | 1.72615 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 784.448 | 1.3669 | 2476ms | 8587914 | 30 | 6.10998e+11 | 1.04406e+07 | 3.87431 | 1(Win) |
| glaze | 596.924 | 0.412057 | 3330.97ms | 8587914 | 30 | 9.589e+10 | 1.37205e+07 | 5.09162 | 2(Loss) |
| simdjson (ondemand) | 579.652 | 0.345333 | 3416.96ms | 8587914 | 30 | 7.14229e+10 | 1.41293e+07 | 5.24336 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1711.66 | 2.21756 | 1098.54ms | 8588126 | 30 | 3.37781e+11 | 4.785e+06 | 1.77538 | 1(Win) |
| glaze | 1096 | 0.604757 | 1787.07ms | 8588126 | 30 | 6.12719e+10 | 7.4729e+06 | 2.77292 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 855.399 | 0.787126 | 2652.38ms | 9804437 | 30 | 2.22084e+11 | 1.09308e+07 | 3.55304 | 1(Win) |
| glaze STATISTICAL TIE | 669.163 | 0.747675 | 3351.21ms | 9804437 | 30 | 3.27437e+11 | 1.3973e+07 | 4.54199 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 661.518 | 0.231456 | 3386.77ms | 9804437 | 30 | 3.21086e+10 | 1.41345e+07 | 4.59445 | 2(Tie) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1747.35 | 2.00254 | 1375.37ms | 11078090 | 30 | 4.398e+11 | 6.04624e+06 | 1.7391 | 1(Win) |
| glaze | 1261.29 | 0.4024 | 2013.4ms | 11078090 | 30 | 3.40831e+10 | 8.37628e+06 | 2.4096 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4078.75 | 2.1619 | 16.1331ms | 264040 | 30 | 5.34417e+07 | 61736.7 | 0.744726 | 1(Win) |
| simdjson (ondemand) | 1822.89 | 1.10169 | 34.4815ms | 264040 | 30 | 6.94803e+07 | 138137 | 1.66685 | 2(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5332.05 | 1.4983 | 18.4021ms | 399947 | 30 | 3.44616e+07 | 71533.3 | 0.56963 | 1(Win) |
| simdjson (ondemand) | 2622.22 | 0.810161 | 36.8309ms | 399947 | 30 | 4.16612e+07 | 145457 | 1.15889 | 2(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1493.02 | 1.6709 | 42.4106ms | 264040 | 30 | 2.38247e+08 | 168657 | 2.03543 | 1(Win) |
| glaze | 871.238 | 1.14179 | 70.8398ms | 264040 | 30 | 3.26709e+08 | 289023 | 3.488 | 2(Loss) |
| simdjson (ondemand) | 743.535 | 1.97425 | 82.2867ms | 264040 | 30 | 1.34111e+09 | 338663 | 4.08685 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4909.82 | 1.87209 | 13.4656ms | 264040 | 30 | 2.76557e+07 | 51286.7 | 0.618669 | 1(Win) |
| glaze | 4166.01 | 2.21628 | 16.4254ms | 263923 | 30 | 5.37876e+07 | 60416.7 | 0.729123 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1685.26 | 1.01866 | 56.2994ms | 399947 | 30 | 1.5946e+08 | 226327 | 1.80295 | 1(Win) |
| glaze | 1138.8 | 0.831095 | 81.828ms | 399947 | 30 | 2.3245e+08 | 334930 | 2.66849 | 2(Loss) |
| simdjson (ondemand) | 1089.29 | 1.1323 | 85.1201ms | 399947 | 30 | 4.71586e+08 | 350153 | 2.78935 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6005.66 | 1.65415 | 17.2345ms | 399947 | 30 | 3.31099e+07 | 63510 | 0.505789 | 1(Win) |
| glaze | 3081.7 | 1.83699 | 148.898ms | 399830 | 64 | 3.30645e+08 | 123733 | 0.985825 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2464.36 | 1.18162 | 44.8499ms | 466906 | 30 | 1.3675e+08 | 180687 | 1.23277 | 1(Win) |
| glaze | 1906.94 | 0.842707 | 57.6051ms | 466906 | 30 | 1.16161e+08 | 233503 | 1.59342 | 2(Loss) |
| simdjson (ondemand) | 1077.08 | 1.37268 | 99.3909ms | 466906 | 30 | 9.66095e+08 | 413410 | 2.82081 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3249.98 | 1.08871 | 51.0221ms | 699405 | 30 | 1.49777e+08 | 205233 | 0.934791 | 1(Win) |
| glaze | 2814.6 | 1.13585 | 57.876ms | 699405 | 30 | 2.17363e+08 | 236980 | 1.07964 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4146.55 | 1.275 | 36.159ms | 631514 | 30 | 1.02881e+08 | 145243 | 0.732871 | 1(Win) |
| glaze | 2317.75 | 0.930494 | 62.835ms | 631514 | 30 | 1.75381e+08 | 259847 | 1.31114 | 2(Loss) |
