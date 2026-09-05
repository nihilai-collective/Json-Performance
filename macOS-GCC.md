# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.5.0 using the GCC 16.1.0 compiler).  

Latest Results: (Sep 02, 2026)
#### Using the following commits:
----
| Jsonifier: [7b97dcd](https://github.com/nihilai-collective/jsonifier/commit/7b97dcd)  
| Glaze: [a5f515c](https://github.com/stephenberry/glaze/commit/a5f515c)  
| Simdjson: [06856ec](https://github.com/simdjson/simdjson/commit/06856ec)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `NEON` |
| simdjson (ondemand) | `arm64` |
| Glaze (utf8-validation) | `NEON64` |
| Glaze (string-escape) | `NEON` |
| Glaze (float-write) | `NEON` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Apple M1 (Virtual)-NEON): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.5% AND mean shift < 1% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [f0ef39c](https://github.com/realtimechris/benchmarksuite/commit/f0ef39c).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 877.594 | 1.79433 | 35.1301ms | 1811 | 32 | 39903 | 1968 | 1(Win) |
| glaze | 686.448 | 1.82368 | 7.41888ms | 1811 | 128 | 269481 | 2516 | 2(Loss) |
| simdjson (ondemand) | 166.452 | 2.38113 | 6.16294ms | 1811 | 32 | 1.95333e+06 | 10376 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 541.163 | 2.48454 | 0.882944ms | 1811 | 30 | 188623 | 3191.47 | 1(Win) |
| glaze | 381.294 | 1.92385 | 1.29408ms | 1798 | 30 | 224555 | 4497.07 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1578.45 | 1.30083 | 12.3151ms | 3873 | 256 | 237199 | 2340 | 1(Win) |
| jsonifier | 1391.7 | 1.69124 | 6.94886ms | 3873 | 128 | 257883 | 2654 | 2(Loss) |
| simdjson (ondemand) | 381.022 | 1.41979 | 2.33882ms | 3873 | 30 | 568280 | 9693.87 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1899.99 | 2.36176 | 6.17395ms | 3873 | 128 | 269820 | 1944 | 1(Win) |
| glaze | 1219.27 | 1.40845 | 0.824064ms | 3873 | 30 | 54613.3 | 3029.33 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1463.87 | 1.27213 | 15.0648ms | 3862 | 256 | 262256 | 2516 | 1(Win) |
| glaze | 1142.4 | 2.1639 | 3.69306ms | 3862 | 64 | 311491 | 3224 | 2(Loss) |
| simdjson (ondemand) | 340.926 | 1.81574 | 2.95603ms | 3862 | 30 | 1.15434e+06 | 10803.2 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1844.5 | 0.952284 | 0.587776ms | 3862 | 30 | 10847.3 | 1996.8 | 1(Win) |
| glaze | 987.671 | 2.04719 | 0.92288ms | 3862 | 30 | 174838 | 3729.07 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1461.6 | 1.85211 | 25.695ms | 905 | 2048 | 244965 | 590.5 | 1(Win) |
| glaze | 725.273 | 2.09374 | 6.29402ms | 905 | 256 | 158921 | 1190 | 2(Loss) |
| simdjson (ondemand) | 202.283 | 1.9792 | 1.14509ms | 905 | 30 | 213934 | 4266.67 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 839.567 | 2.44868 | 1.51885ms | 905 | 64 | 40553.7 | 1028 | 1(Win) |
| glaze | 378.542 | 1.7676 | 6.05389ms | 905 | 128 | 207896 | 2280 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2282.36 | 0.572402 | 1.05395ms | 9578 | 30 | 15743.7 | 4002.13 | 1(Win) |
| glaze | 1851.95 | 1.08284 | 1.28512ms | 9578 | 30 | 85573.4 | 4932.27 | 2(Loss) |
| simdjson (ondemand) | 646.392 | 0.429053 | 3.52691ms | 9578 | 30 | 110281 | 14131.2 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3857.39 | 1.81857 | 6.17395ms | 9578 | 128 | 237374 | 2368 | 1(Win) |
| glaze | 1164.79 | 2.00218 | 51.1821ms | 9578 | 512 | 1.2622e+07 | 7842 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3903.71 | 0.30679 | 14.1939ms | 233995 | 30 | 922702 | 57164.8 | 1(Win) |
| simdjson (ondemand) | 2711.63 | 0.103046 | 34.0029ms | 233995 | 30 | 215741 | 82295.5 | 2(Loss) |
| glaze | 1017.23 | 0.624819 | 297.235ms | 233995 | 64 | 1.20245e+08 | 219376 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4205.96 | 1.52655 | 49.6602ms | 346753 | 32 | 4.60982e+07 | 78624 | 1(Win) |
| simdjson (ondemand) | 3622.08 | 0.323634 | 22.0631ms | 346753 | 30 | 2.6191e+06 | 91298.1 | 2(Loss) |
| glaze | 1669.22 | 0.65263 | 47.3111ms | 346753 | 30 | 5.01497e+07 | 198110 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1364.87 | 0.408186 | 40.151ms | 233995 | 30 | 1.33618e+07 | 163499 | 1(Win) |
| glaze | 1270.25 | 0.343024 | 508.48ms | 233995 | 128 | 4.64828e+07 | 175678 | 2(Loss) |
| simdjson (ondemand) | 894.524 | 0.732942 | 355.11ms | 233995 | 64 | 2.13968e+08 | 249468 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1838.77 | 1.38356 | 28.756ms | 233995 | 30 | 8.45818e+07 | 121361 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1827.72 | 1.32242 | 27.3549ms | 233995 | 30 | 7.8209e+07 | 122095 | 1(Tie) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1543.07 | 1.28377 | 47.0679ms | 346753 | 30 | 2.27074e+08 | 214306 | 1(Win) |
| jsonifier | 1329.88 | 0.569077 | 62.3532ms | 346753 | 30 | 6.00732e+07 | 248661 | 2(Loss) |
| simdjson (ondemand) | 1300.38 | 0.160843 | 61.6492ms | 346753 | 30 | 5.01908e+06 | 254302 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2417.96 | 1.15114 | 32.353ms | 346753 | 30 | 7.43571e+07 | 136764 | 1(Win) |
| glaze | 2266.64 | 0.930908 | 36.928ms | 346753 | 30 | 5.53366e+07 | 145894 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3408.63 | 2.10585 | 16.9341ms | 233995 | 30 | 5.70205e+07 | 65467.7 | 1(Win) |
| simdjson (ondemand) | 1817.3 | 0.914453 | 30.0731ms | 233995 | 30 | 3.78271e+07 | 122795 | 2(Loss) |
| glaze | 1064.3 | 0.760988 | 51.5702ms | 233995 | 30 | 7.63765e+07 | 209673 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4381.8 | 0.442549 | 18.3841ms | 346753 | 30 | 3.3464e+06 | 75468.8 | 1(Win) |
| simdjson (ondemand) | 2359.8 | 0.826992 | 34.518ms | 346753 | 30 | 4.02915e+07 | 140134 | 2(Loss) |
| glaze | 1631.42 | 0.424238 | 48.553ms | 346753 | 30 | 2.21846e+07 | 202701 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1360.75 | 0.349427 | 49.665ms | 233995 | 30 | 9.85119e+06 | 163994 | 1(Win) |
| jsonifier | 1165.69 | 1.14455 | 46.6959ms | 233995 | 30 | 1.44027e+08 | 191437 | 2(Loss) |
| simdjson (ondemand) | 220.364 | 0.932755 | 328.408ms | 233995 | 30 | 2.67664e+09 | 1.01267e+06 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 2587.06 | 0.244301 | 506.215ms | 233995 | 256 | 1.13681e+07 | 86258 | 1(Win) |
| jsonifier | 2513.07 | 0.225328 | 21.5639ms | 233995 | 30 | 1.20104e+06 | 88797.9 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1684.97 | 0.240966 | 47.082ms | 346753 | 30 | 6.70946e+06 | 196258 | 1(Win) |
| jsonifier | 1292.27 | 0.220412 | 62.23ms | 346753 | 30 | 9.54385e+06 | 255898 | 2(Loss) |
| simdjson (ondemand) | 330.108 | 0.157816 | 240.742ms | 346753 | 30 | 7.4981e+07 | 1.00176e+06 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2973.2 | 1.33886 | 31.541ms | 346753 | 30 | 6.65246e+07 | 111223 | 1(Win) |
| glaze | 2023.85 | 1.27599 | 40.289ms | 346753 | 30 | 1.30407e+08 | 163396 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 815.895 | 0.272454 | 26.8649ms | 94651 | 30 | 2.72577e+06 | 110635 | 1(Win) |
| simdjson (ondemand) | 709.752 | 0.0852873 | 726.051ms | 94651 | 256 | 3.01194e+06 | 127180 | 2(Loss) |
| jsonifier | 666.671 | 1.50099 | 33.4269ms | 94651 | 30 | 1.2391e+08 | 135398 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5195.52 | 0.51787 | 4.41318ms | 94651 | 30 | 242860 | 17373.9 | 1(Win) |
| glaze | 4141.77 | 2.40512 | 4.92288ms | 94651 | 30 | 8.24277e+06 | 21794.1 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 920.436 | 1.85163 | 99.6442ms | 136024 | 32 | 2.17922e+08 | 140936 | 1(Win) |
| jsonifier STATISTICAL TIE | 811.459 | 0.211351 | 41.386ms | 136024 | 30 | 3.42475e+06 | 159863 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 808.266 | 0.931487 | 41.1479ms | 136024 | 30 | 6.70498e+07 | 160495 | 2(Tie) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 3721.08 | 1.55985 | 8.38195ms | 136046 | 30 | 8.87403e+06 | 34867.2 | 1(Win) |
| jsonifier | 2966.22 | 0.477193 | 12.2941ms | 136024 | 30 | 1.30658e+06 | 43733.3 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 590.767 | 1.4388 | 966.067ms | 2090234 | 30 | 7.07101e+10 | 3.37426e+06 | 1(Win) |
| glaze | 514.156 | 0.500898 | 932.446ms | 2090234 | 30 | 1.13141e+10 | 3.87703e+06 | 2(Loss) |
| simdjson (ondemand) | 401.965 | 1.96921 | 1063.77ms | 2090234 | 30 | 2.861e+11 | 4.95915e+06 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1761.64 | 0.26486 | 309.903ms | 2090234 | 30 | 2.69471e+08 | 1.13156e+06 | 1(Win) |
| glaze | 1504.8 | 0.371447 | 374.878ms | 2090234 | 30 | 7.26354e+08 | 1.3247e+06 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1376.76 | 0.627736 | 7189.37ms | 6661897 | 64 | 5.37052e+10 | 4.61467e+06 | 1(Win) |
| simdjson (ondemand) | 1271.3 | 0.634404 | 1238.1ms | 6661897 | 30 | 3.01545e+10 | 4.99746e+06 | 2(Loss) |
| glaze | 1063.52 | 1.94185 | 1680.58ms | 6661897 | 30 | 4.037e+11 | 5.97383e+06 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 2949.81 | 0.141155 | 542.52ms | 6661897 | 30 | 2.77285e+08 | 2.1538e+06 | 1(Win) |
| jsonifier | 2482.65 | 1.23118 | 639.03ms | 6661897 | 30 | 2.97801e+10 | 2.55907e+06 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1515.95 | 0.864644 | 76.8061ms | 500299 | 30 | 2.2217e+08 | 314735 | 1(Win) |
| glaze | 1246.74 | 0.125429 | 92.512ms | 500299 | 30 | 6.91224e+06 | 382694 | 2(Loss) |
| simdjson (ondemand) | 760.035 | 0.164373 | 152.421ms | 500299 | 30 | 3.19427e+07 | 627763 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3921.5 | 0.59657 | 29.5309ms | 500299 | 30 | 1.58052e+07 | 121668 | 1(Win) |
| glaze | 1956.63 | 0.153728 | 58.7461ms | 500299 | 30 | 4.2157e+06 | 243849 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2284.53 | 0.192165 | 145.906ms | 1439562 | 30 | 4.00072e+07 | 600943 | 1(Win) |
| glaze | 1854.07 | 0.453365 | 184.277ms | 1439562 | 30 | 3.38083e+08 | 740463 | 2(Loss) |
| simdjson (ondemand) | 1814.76 | 0.582243 | 184.712ms | 1439562 | 30 | 5.82043e+08 | 756506 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3753.79 | 1.94527 | 83.796ms | 1439562 | 30 | 1.51846e+09 | 365730 | 1(Win) |
| glaze | 2194.42 | 0.961797 | 158.579ms | 1439584 | 30 | 1.08623e+09 | 625630 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1249.2 | 0.632885 | 11.071ms | 56369 | 30 | 2.22529e+06 | 43033.6 | 1(Win) |
| glaze | 864.279 | 1.41829 | 14.7592ms | 56369 | 30 | 2.33466e+07 | 62199.5 | 2(Loss) |
| simdjson (ondemand) | 807.243 | 0.13257 | 18.336ms | 56369 | 30 | 233820 | 66594.1 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4066.24 | 2.01352 | 141.315ms | 56369 | 512 | 3.6281e+07 | 13220.5 | 1(Win) |
| glaze | 2249.65 | 2.36174 | 122.979ms | 56369 | 256 | 8.1537e+07 | 23896 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1442.83 | 0.237865 | 37.63ms | 94370 | 32 | 704446 | 62376 | 1(Win) |
| jsonifier | 1286.28 | 1.49468 | 46.347ms | 94370 | 32 | 3.49981e+07 | 69968 | 2(Loss) |
| simdjson (ondemand) | 1224.93 | 0.603502 | 46.4689ms | 94370 | 32 | 6.29146e+06 | 73472 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2625.31 | 0.91341 | 202.576ms | 94370 | 256 | 2.51003e+07 | 34281 | 1(Win) |
| glaze | 1845.13 | 2.25941 | 572.74ms | 94370 | 512 | 6.21831e+08 | 48776 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1131.28 | 1.54094 | 16.023ms | 52708 | 30 | 1.4064e+07 | 44433.1 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 954.471 | 1.83783 | 137.925ms | 52708 | 128 | 1.19908e+08 | 52664 | 2(Tie) |
| glaze STATISTICAL TIE | 950.644 | 2.09553 | 153.241ms | 52708 | 128 | 1.5715e+08 | 52876 | 2(Tie) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4650.84 | 1.43769 | 6.89894ms | 52708 | 32 | 772625 | 10808 | 1(Win) |
| glaze | 3201.4 | 1.3112 | 4.16794ms | 52708 | 30 | 1.27155e+06 | 15701.3 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1311.89 | 0.165005 | 14.743ms | 70103 | 30 | 212126 | 50961.1 | 1(Win) |
| simdjson (ondemand) | 1206.25 | 1.50084 | 17.022ms | 70103 | 30 | 2.0758e+07 | 55424 | 2(Loss) |
| jsonifier | 1024.07 | 0.690084 | 90.4461ms | 70103 | 64 | 1.29896e+07 | 65284 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2967.66 | 1.65416 | 15.4499ms | 70103 | 32 | 4.44376e+06 | 22528 | 1(Win) |
| glaze | 2299.57 | 1.90531 | 7.43091ms | 70103 | 30 | 9.20525e+06 | 29073.1 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 915.46 | 1.85259 | 3.38995ms | 11812 | 30 | 1.559e+06 | 12305.1 | 1(Win) |
| glaze | 679.76 | 1.68726 | 5.63098ms | 11812 | 30 | 2.34544e+06 | 16571.7 | 2(Loss) |
| simdjson (ondemand) | 534.383 | 2.06256 | 32.801ms | 11812 | 64 | 1.20986e+07 | 21080 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3612.83 | 2.38874 | 22.2592ms | 11812 | 256 | 1.42014e+06 | 3118 | 1(Win) |
| glaze | 1466.77 | 2.0739 | 6.51802ms | 11812 | 32 | 811801 | 7680 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1429.09 | 0.500506 | 28.5768ms | 31235 | 64 | 696564 | 20844 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1367.93 | 2.11997 | 18.1261ms | 31235 | 32 | 6.81971e+06 | 21776 | 1(Tie) |
| simdjson (ondemand) | 1244.49 | 1.50948 | 15.1199ms | 31235 | 32 | 4.17739e+06 | 23936 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3359.75 | 2.18228 | 2.32602ms | 31235 | 30 | 1.12308e+06 | 8866.13 | 1(Win) |
| glaze | 2511.35 | 0.541014 | 3.0569ms | 31235 | 30 | 123539 | 11861.3 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2409.9 | 1.70467 | 10.9801ms | 108313 | 30 | 1.60165e+07 | 42862.9 | 1(Win) |
| glaze | 1198.39 | 1.42949 | 21.2518ms | 108313 | 30 | 4.55459e+07 | 86195.2 | 2(Loss) |
| simdjson (ondemand) | 871.234 | 0.828449 | 28.426ms | 108313 | 30 | 2.89431e+07 | 118562 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1829.09 | 0.164953 | 13.9681ms | 108313 | 30 | 260336 | 56473.6 | 1(Win) |
| jsonifier | 1622.43 | 1.10196 | 15.6219ms | 108313 | 30 | 1.47666e+07 | 63667.2 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2111.64 | 0.0931105 | 25.545ms | 213963 | 30 | 242860 | 96631.5 | 1(Win) |
| glaze | 1819.8 | 0.473245 | 28.2268ms | 213963 | 30 | 8.44736e+06 | 112128 | 2(Loss) |
| simdjson (ondemand) | 1748.35 | 1.2347 | 29.4351ms | 213963 | 30 | 6.22969e+07 | 116710 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2637.28 | 0.852782 | 23.584ms | 213963 | 30 | 1.30606e+07 | 77371.7 | 1(Win) |
| glaze | 1611.34 | 1.8462 | 30.5078ms | 213963 | 30 | 1.63977e+08 | 126635 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 562.032 | 1.22633 | 4245.1ms | 1834197 | 64 | 9.32322e+10 | 3.11232e+06 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 372.055 | 0.955963 | 3039.51ms | 1834197 | 32 | 6.46413e+10 | 4.70153e+06 | 2(Tie) |
| glaze STATISTICAL TIE | 361.242 | 2.43713 | 1024.4ms | 1834197 | 30 | 4.17805e+11 | 4.84226e+06 | 2(Tie) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 699.499 | 0.606002 | 1457.28ms | 1833577 | 32 | 7.34382e+09 | 2.49984e+06 | 1(Win) |
| jsonifier | 574.874 | 0.99148 | 717.223ms | 1834197 | 30 | 2.73046e+10 | 3.0428e+06 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1830.11 | 0.522424 | 1293.88ms | 9930848 | 30 | 2.19275e+10 | 5.175e+06 | 1(Win) |
| glaze | 1804.62 | 0.382447 | 1310.02ms | 9930848 | 30 | 1.20856e+10 | 5.24809e+06 | 2(Loss) |
| simdjson (ondemand) | 1643.21 | 1.38701 | 1742.25ms | 9930848 | 30 | 1.9172e+11 | 5.76359e+06 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 2122.69 | 1.29365 | 1161.65ms | 9930228 | 30 | 9.993e+10 | 4.46141e+06 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2109.16 | 1.52854 | 1063.66ms | 9930848 | 30 | 1.41327e+11 | 4.49031e+06 | 1(Tie) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 989.502 | 1.08372 | 133.648ms | 642697 | 30 | 1.35188e+09 | 619426 | 1(Win) |
| glaze | 793.739 | 0.905905 | 179.737ms | 642697 | 30 | 1.46806e+09 | 772198 | 2(Loss) |
| simdjson (ondemand) | 634.469 | 1.51337 | 200.371ms | 642697 | 30 | 6.41213e+09 | 966042 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1010.98 | 0.30902 | 159.941ms | 642697 | 30 | 1.05299e+08 | 606268 | 1(Win) |
| glaze | 877.441 | 0.958479 | 173.062ms | 642692 | 30 | 1.3448e+09 | 698530 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1412.1 | 0.439881 | 197.074ms | 1225964 | 30 | 3.97938e+08 | 827964 | 1(Win) |
| simdjson (ondemand) | 1393.08 | 0.478064 | 202.235ms | 1225964 | 30 | 4.82944e+08 | 839270 | 2(Loss) |
| jsonifier | 1334.06 | 0.134536 | 212.315ms | 1225964 | 30 | 4.17066e+07 | 876399 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1851.34 | 0.533943 | 153.616ms | 1225964 | 30 | 3.4111e+08 | 631526 | 1(Win) |
| glaze | 1208.88 | 1.04284 | 220.007ms | 1225970 | 30 | 3.05178e+09 | 967159 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 694.035 | 0.685957 | 146.091ms | 409725 | 30 | 4.47442e+08 | 563004 | 1(Win) |
| glaze | 542.045 | 0.50185 | 173.613ms | 409725 | 30 | 3.9263e+08 | 720870 | 2(Loss) |
| simdjson (ondemand) | 492.247 | 1.12565 | 178.365ms | 409725 | 30 | 2.39521e+09 | 793796 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3518.27 | 0.798111 | 26.91ms | 409725 | 30 | 2.35707e+07 | 111061 | 1(Win) |
| glaze | 1775.3 | 0.966417 | 56.2158ms | 409725 | 30 | 1.35735e+08 | 220100 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 902.363 | 0.896633 | 199.771ms | 785750 | 30 | 1.66325e+09 | 830430 | 1(Win) |
| simdjson (ondemand) | 863.202 | 1.04255 | 194.881ms | 785750 | 30 | 2.45729e+09 | 868105 | 2(Loss) |
| jsonifier | 776.851 | 0.669095 | 233.093ms | 785750 | 30 | 1.24966e+09 | 964599 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2645.09 | 0.323311 | 69.3591ms | 785750 | 30 | 2.5168e+07 | 283298 | 1(Win) |
| glaze | 1960.8 | 1.34516 | 89.0371ms | 785750 | 30 | 7.9281e+08 | 382165 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 869.562 | 0.257136 | 2656.98ms | 8587914 | 30 | 1.75963e+10 | 9.41862e+06 | 1(Win) |
| jsonifier | 828.818 | 0.670581 | 2235.62ms | 8587914 | 30 | 1.31729e+11 | 9.88163e+06 | 2(Loss) |
| simdjson (ondemand) | 675.239 | 0.939988 | 2633.7ms | 8587914 | 30 | 3.89966e+11 | 1.21292e+07 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 2719.76 | 1.88645 | 829.419ms | 8588126 | 30 | 9.6816e+10 | 3.0114e+06 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2663.78 | 0.773574 | 740.391ms | 8588126 | 30 | 1.69717e+10 | 3.07468e+06 | 1(Tie) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 899.327 | 1.18828 | 2671.88ms | 9804437 | 30 | 4.57894e+11 | 1.03969e+07 | 1(Win) |
| jsonifier | 833.334 | 1.68102 | 13741.4ms | 9804437 | 64 | 2.27683e+12 | 1.12203e+07 | 2(Loss) |
| simdjson (ondemand) | 716.312 | 1.51097 | 2868.6ms | 9804437 | 30 | 1.167e+12 | 1.30533e+07 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 2782.16 | 1.9619 | 2282.46ms | 11078090 | 32 | 1.77612e+11 | 3.79738e+06 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2712.31 | 0.592376 | 942.145ms | 11078090 | 30 | 1.59723e+10 | 3.89517e+06 | 1(Tie) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3263.16 | 1.02353 | 20.3461ms | 264040 | 30 | 1.87147e+07 | 77166.9 | 1(Win) |
| simdjson (ondemand) | 2426.91 | 1.05333 | 26.0411ms | 264040 | 30 | 3.58331e+07 | 103757 | 2(Loss) |
| glaze | 1247.71 | 1.76116 | 119.363ms | 264040 | 32 | 4.04258e+08 | 201816 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3712.73 | 1.44465 | 26.2152ms | 399947 | 30 | 6.6079e+07 | 102733 | 1(Win) |
| simdjson (ondemand) | 3277.67 | 1.25981 | 28.2099ms | 399947 | 30 | 6.4477e+07 | 116369 | 2(Loss) |
| glaze | 1533.68 | 1.68678 | 57.2749ms | 399947 | 30 | 5.2793e+08 | 248695 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1492.6 | 1.65252 | 221.039ms | 264040 | 64 | 4.97422e+08 | 168704 | 1(Win) |
| glaze STATISTICAL TIE | 1042.29 | 1.66967 | 357.674ms | 264040 | 64 | 1.04137e+09 | 241592 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1027.79 | 1.2488 | 62.2971ms | 264040 | 30 | 2.80826e+08 | 245001 | 2(Tie) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 2983.32 | 0.72464 | 251.076ms | 263923 | 128 | 4.78421e+07 | 84368 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2928.91 | 1.15793 | 22.4179ms | 264040 | 30 | 2.97311e+07 | 85973.3 | 1(Tie) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 1637.27 | 0.903738 | 64.3988ms | 399947 | 30 | 1.32975e+08 | 232960 | 1(Win) |
| glaze | 1537.58 | 1.05875 | 154.354ms | 399947 | 32 | 2.20729e+08 | 248064 | 2(Loss) |
| jsonifier | 1152.92 | 1.20219 | 78.9821ms | 399947 | 30 | 4.74545e+08 | 330829 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3519.41 | 2.09672 | 55.1411ms | 399947 | 32 | 1.65234e+08 | 108376 | 1(Win) |
| glaze | 2833.51 | 2.19119 | 31.0682ms | 399830 | 30 | 2.60844e+08 | 134571 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1723.79 | 1.01513 | 180.881ms | 466906 | 32 | 2.2003e+08 | 258312 | 1(Win) |
| jsonifier | 1289.24 | 0.642333 | 112.61ms | 466906 | 30 | 1.47649e+08 | 345378 | 2(Loss) |
| simdjson (ondemand) | 842.673 | 0.350017 | 145.442ms | 466906 | 30 | 1.02622e+08 | 528410 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1808.36 | 0.563064 | 90.997ms | 699405 | 30 | 1.29397e+08 | 368845 | 1(Win) |
| jsonifier | 1643.29 | 1.58636 | 85.4269ms | 699405 | 30 | 1.24381e+09 | 405897 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2418.77 | 2.15005 | 66.069ms | 631514 | 30 | 8.59798e+08 | 248994 | 1(Win) |
| glaze | 1600.35 | 1.44133 | 85.8271ms | 631514 | 30 | 8.82641e+08 | 376329 | 2(Loss) |
