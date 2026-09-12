# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36256.0 compiler).  

Latest Results: (Sep 12, 2026)
#### Using the following commits:
----
| Jsonifier: [8fed030](https://github.com/nihilai-collective/jsonifier/commit/8fed030)  
| Glaze: [52fb059](https://github.com/stephenberry/glaze/commit/52fb059)  
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
| jsonifier | 422.964 | 0.169481 | 2.5013ms | 1811 | 30 | 1436.78 | 4083.33 | 5.47364 | 1(Win) |
| glaze | 163.603 | 0.0871664 | 3.7708ms | 1811 | 30 | 2540.23 | 10556.7 | 14.1661 | 2(Loss) |
| simdjson (ondemand) | 95.7729 | 0.0553465 | 5.6981ms | 1811 | 30 | 2988.51 | 18033.3 | 24.2952 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 316.706 | 0.228144 | 2.5358ms | 1811 | 30 | 4643.68 | 5453.33 | 7.31349 | 1(Win) |
| glaze | 174.469 | 0.114074 | 7.9695ms | 1798 | 32 | 4022.18 | 9828.12 | 13.2992 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1038.62 | 0.25054 | 3.9605ms | 3873 | 32 | 2540.32 | 3556.25 | 2.21743 | 1(Win) |
| glaze | 625.699 | 0.0926721 | 5.7756ms | 3873 | 32 | 957.661 | 5903.12 | 3.70499 | 2(Loss) |
| simdjson (ondemand) | 230.624 | 0.166122 | 11.002ms | 3873 | 32 | 22651.2 | 16015.6 | 10.0877 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1689.14 | 0.288678 | 1.7987ms | 3873 | 30 | 1195.4 | 2186.67 | 1.35543 | 1(Win) |
| glaze | 709.394 | 0.224308 | 2.5526ms | 3873 | 30 | 4091.95 | 5206.67 | 3.26626 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1145 | 0.215144 | 2.1719ms | 3862 | 30 | 1436.78 | 3216.67 | 2.01418 | 1(Win) |
| glaze | 558.891 | 0.151745 | 2.9527ms | 3862 | 30 | 3000 | 6590 | 4.14445 | 2(Loss) |
| simdjson (ondemand) | 233.353 | 0.0613853 | 5.0372ms | 3862 | 30 | 2816.09 | 15783.3 | 9.97447 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1582.99 | 0.352941 | 1.7904ms | 3862 | 30 | 2022.99 | 2326.67 | 1.45357 | 1(Win) |
| glaze | 678.285 | 0.179879 | 2.6033ms | 3862 | 30 | 2862.07 | 5430 | 3.41446 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 816.79 | 0.870839 | 1.6514ms | 905 | 30 | 2540.23 | 1056.67 | 2.78659 | 1(Win) |
| glaze | 143.686 | 0.0771152 | 2.6814ms | 905 | 30 | 643.678 | 6006.67 | 16.1239 | 2(Loss) |
| simdjson (ondemand) | 67.2701 | 0.066326 | 4.3332ms | 905 | 30 | 2172.41 | 12830 | 34.5517 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 389.357 | 0.312201 | 1.7481ms | 905 | 30 | 1436.78 | 2216.67 | 5.87101 | 1(Win) |
| glaze | 119.264 | 0.140287 | 3.2011ms | 905 | 30 | 3091.95 | 7236.67 | 19.3906 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1108.03 | 1.05044 | 6.7219ms | 9578 | 32 | 239960 | 8243.75 | 2.09343 | 1(Win) |
| glaze | 877.735 | 0.102333 | 3.8198ms | 9578 | 30 | 3402.3 | 10406.7 | 2.64833 | 2(Loss) |
| simdjson (ondemand) | 391.925 | 0.0692966 | 16.572ms | 9578 | 32 | 8346.77 | 23306.2 | 5.94195 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2186.98 | 0.188045 | 2.1701ms | 9578 | 30 | 1850.57 | 4176.67 | 1.06129 | 1(Win) |
| glaze | 1537.6 | 0.166616 | 5.3162ms | 9578 | 32 | 3135.08 | 5940.62 | 1.50415 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2337.19 | 1.17867 | 24.6716ms | 233995 | 30 | 3.79954e+07 | 95480 | 0.997409 | 1(Win) |
| simdjson (ondemand) | 1520.61 | 1.06103 | 36.7073ms | 233995 | 30 | 7.27371e+07 | 146753 | 1.53306 | 2(Loss) |
| glaze | 1031.31 | 0.689088 | 56.3116ms | 233995 | 30 | 6.66968e+07 | 216380 | 2.26068 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2982.68 | 1.45567 | 28.0803ms | 346753 | 30 | 7.81401e+07 | 110870 | 0.781431 | 1(Win) |
| simdjson (ondemand) | 1922.43 | 1.54418 | 50.8008ms | 346753 | 30 | 2.11668e+08 | 172017 | 1.21247 | 2(Loss) |
| glaze | 1336.61 | 1.09189 | 151.295ms | 346753 | 32 | 2.33529e+08 | 247409 | 1.74439 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 745.98 | 0.712211 | 76.5834ms | 233995 | 30 | 1.36175e+08 | 299143 | 3.12475 | 1(Win) |
| glaze | 631.35 | 0.975425 | 92.0126ms | 233995 | 30 | 3.566e+08 | 353457 | 3.69235 | 2(Loss) |
| simdjson (ondemand) | 426.536 | 0.744685 | 125.444ms | 233995 | 30 | 4.55375e+08 | 523180 | 5.46656 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1205.07 | 2.26374 | 46.2051ms | 233995 | 30 | 5.27185e+08 | 185180 | 1.93412 | 1(Win) |
| glaze | 1078.76 | 2.40576 | 578.693ms | 233995 | 128 | 3.17016e+09 | 206863 | 2.16088 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 913.044 | 0.95136 | 88.5812ms | 346753 | 30 | 3.56179e+08 | 362183 | 2.55361 | 1(Win) |
| glaze | 853.84 | 0.67922 | 94.2698ms | 346753 | 30 | 2.07601e+08 | 387297 | 2.73093 | 2(Loss) |
| simdjson (ondemand) | 613.137 | 0.546535 | 130.107ms | 346753 | 30 | 2.60665e+08 | 539340 | 3.80284 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1863.74 | 1.30747 | 44.4069ms | 346753 | 30 | 1.61457e+08 | 177433 | 1.2508 | 1(Win) |
| glaze | 1005.23 | 2.25709 | 826.739ms | 346753 | 128 | 7.05694e+09 | 328968 | 2.31925 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2260.26 | 2.02592 | 24.9317ms | 233995 | 30 | 1.20023e+08 | 98730 | 1.03096 | 1(Win) |
| simdjson (ondemand) | 1037.69 | 0.777771 | 52.9917ms | 233995 | 30 | 8.39274e+07 | 215050 | 2.24677 | 2(Loss) |
| glaze | 640.355 | 0.692003 | 64.0231ms | 233995 | 30 | 1.74465e+08 | 348487 | 3.64132 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2903.76 | 1.32055 | 28.8673ms | 346753 | 30 | 6.78497e+07 | 113883 | 0.802522 | 1(Win) |
| simdjson (ondemand) | 1380.73 | 0.863693 | 68.2139ms | 346753 | 30 | 1.2837e+08 | 239503 | 1.6886 | 2(Loss) |
| glaze | 1339.35 | 0.820812 | 60.6671ms | 346753 | 30 | 1.23215e+08 | 246903 | 1.74078 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 744.951 | 0.91943 | 72.9012ms | 233995 | 30 | 2.27571e+08 | 299557 | 3.12972 | 1(Win) |
| glaze | 708.114 | 1.45336 | 76.0571ms | 233995 | 30 | 6.29327e+08 | 315140 | 3.29245 | 2(Loss) |
| simdjson (ondemand) | 101.25 | 0.236754 | 538.758ms | 233995 | 30 | 8.16839e+08 | 2.20399e+06 | 23.032 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1573.84 | 1.58423 | 35.345ms | 233995 | 30 | 1.51373e+08 | 141790 | 1.48099 | 1(Win) |
| glaze | 1110.54 | 1.86964 | 505.281ms | 233995 | 128 | 1.80665e+09 | 200943 | 2.09909 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 915.64 | 0.881022 | 88.0111ms | 346753 | 30 | 3.03729e+08 | 361157 | 2.54622 | 1(Win) |
| glaze | 867.837 | 0.598971 | 92.9008ms | 346753 | 30 | 1.56278e+08 | 381050 | 2.68674 | 2(Loss) |
| simdjson (ondemand) | 146.225 | 0.148631 | 547.011ms | 346753 | 30 | 3.38954e+08 | 2.26151e+06 | 15.9481 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1892.25 | 1.46176 | 43.1762ms | 346753 | 30 | 1.95775e+08 | 174760 | 1.23194 | 1(Win) |
| glaze | 1073.82 | 1.98702 | 771.723ms | 346753 | 128 | 4.79277e+09 | 307955 | 2.17108 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 448.572 | 1.5391 | 49.6615ms | 94651 | 30 | 2.87766e+08 | 201230 | 5.1976 | 1(Win) |
| glaze | 361.135 | 2.00149 | 304.371ms | 94651 | 64 | 1.60176e+09 | 249952 | 6.45522 | 2(Loss) |
| simdjson (ondemand) | 290.149 | 2.38972 | 69.7401ms | 94651 | 30 | 1.65815e+09 | 311103 | 8.03495 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1643.99 | 2.26004 | 15.0749ms | 94651 | 30 | 4.61958e+07 | 54906.7 | 1.41707 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1597.44 | 1.73758 | 14.8773ms | 94651 | 30 | 2.89206e+07 | 56506.7 | 1.45874 | 1(Tie) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 539.253 | 0.982123 | 58.914ms | 136024 | 30 | 1.67456e+08 | 240560 | 4.32355 | 1(Win) |
| glaze | 503.288 | 2.49401 | 153.342ms | 136024 | 32 | 1.32234e+09 | 257750 | 4.63236 | 2(Loss) |
| simdjson (ondemand) | 476.804 | 0.8856 | 67.8904ms | 136024 | 30 | 1.7416e+08 | 272067 | 4.88993 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1841.95 | 1.47874 | 18.4357ms | 136024 | 30 | 3.25372e+07 | 70426.7 | 1.26503 | 1(Win) |
| glaze | 1289.18 | 0.847247 | 59.005ms | 136046 | 32 | 2.32657e+07 | 100641 | 1.80779 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 335.219 | 1.01799 | 1520.36ms | 2090234 | 30 | 1.09937e+11 | 5.94657e+06 | 6.95669 | 1(Win) |
| glaze | 214.154 | 0.515935 | 2261.35ms | 2090234 | 30 | 6.91912e+10 | 9.30829e+06 | 10.8896 | 2(Loss) |
| simdjson (ondemand) | 203.54 | 0.481298 | 2367.44ms | 2090234 | 30 | 6.66559e+10 | 9.79366e+06 | 11.4575 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 556.019 | 0.419101 | 865.407ms | 2090234 | 30 | 6.77282e+09 | 3.58514e+06 | 4.19392 | 1(Win) |
| glaze | 455.535 | 0.944441 | 1047.1ms | 2090234 | 30 | 5.1241e+10 | 4.37596e+06 | 5.11903 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 894.051 | 0.944096 | 1732.29ms | 6661897 | 30 | 1.35028e+11 | 7.10617e+06 | 2.60834 | 1(Win) |
| glaze | 590.173 | 0.721464 | 2571.31ms | 6661897 | 30 | 1.80963e+11 | 1.07651e+07 | 3.95147 | 2(Loss) |
| simdjson (ondemand) | 571.023 | 0.875176 | 2719.07ms | 6661897 | 30 | 2.84447e+11 | 1.11261e+07 | 4.08366 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1280.04 | 0.403089 | 1211.13ms | 6661897 | 30 | 1.2008e+10 | 4.96334e+06 | 1.82172 | 1(Win) |
| glaze | 737.64 | 0.310671 | 2122.71ms | 6661897 | 30 | 2.14798e+10 | 8.61298e+06 | 3.16134 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 462.189 | 0.244405 | 179.967ms | 500299 | 30 | 1.90968e+08 | 1.03231e+06 | 5.04544 | 1(Win) |
| glaze | 449.756 | 0.335587 | 268.537ms | 500299 | 30 | 3.80223e+08 | 1.06085e+06 | 5.18488 | 2(Loss) |
| simdjson (ondemand) | 266.623 | 0.185533 | 1020.94ms | 500299 | 32 | 3.5274e+08 | 1.7895e+06 | 8.74621 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1661.71 | 0.776529 | 70.3319ms | 500299 | 30 | 1.49137e+08 | 287127 | 1.40291 | 1(Win) |
| glaze | 1270.64 | 0.443287 | 92.4126ms | 500299 | 30 | 8.31196e+07 | 375497 | 1.83495 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1326.82 | 1.29107 | 256.675ms | 1439562 | 30 | 5.35371e+09 | 1.03471e+06 | 1.7574 | 1(Win) |
| glaze | 967.79 | 0.2381 | 3733.97ms | 1439562 | 128 | 1.46025e+09 | 1.41857e+06 | 2.40949 | 2(Loss) |
| simdjson (ondemand) | 706.972 | 0.117402 | 490.19ms | 1439562 | 30 | 1.5593e+08 | 1.94191e+06 | 3.29855 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2041.06 | 0.615007 | 163.047ms | 1439562 | 30 | 5.13368e+08 | 672627 | 1.14222 | 1(Win) |
| glaze | 921.566 | 0.610825 | 359.841ms | 1439584 | 30 | 2.48414e+09 | 1.48974e+06 | 2.53002 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 629.113 | 1.49246 | 22.4912ms | 56369 | 30 | 4.87922e+07 | 85450 | 3.70475 | 1(Tie) |
| glaze STATISTICAL TIE | 604.132 | 1.68865 | 22.6616ms | 56369 | 30 | 6.77359e+07 | 88983.3 | 3.85735 | 1(Tie) |
| simdjson (ondemand) | 292.49 | 0.904421 | 45.5459ms | 56369 | 30 | 8.28937e+07 | 183793 | 7.96982 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1418.66 | 0.318577 | 10.4902ms | 56369 | 30 | 437195 | 37893.3 | 1.64226 | 1(Win) |
| glaze | 1264.99 | 0.14023 | 11.7081ms | 56369 | 30 | 106540 | 42496.7 | 1.84176 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 906.966 | 1.05628 | 25.438ms | 94370 | 30 | 3.2958e+07 | 99230 | 2.56942 | 1(Win) |
| jsonifier | 715.464 | 1.37318 | 32.2835ms | 94370 | 30 | 8.95099e+07 | 125790 | 3.25757 | 2(Loss) |
| simdjson (ondemand) | 473.185 | 0.910043 | 47.115ms | 94370 | 30 | 8.98776e+07 | 190197 | 4.92719 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2286.35 | 2.0717 | 10.5882ms | 94370 | 30 | 1.99507e+07 | 39363.3 | 1.01877 | 1(Win) |
| glaze | 1152.25 | 1.06573 | 20.1806ms | 94370 | 30 | 2.07869e+07 | 78106.7 | 2.02268 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 626.42 | 1.86934 | 48.5649ms | 52708 | 32 | 7.20025e+07 | 80243.8 | 3.717 | 1(Win) |
| glaze | 488.829 | 1.21198 | 26.5514ms | 52708 | 30 | 4.65967e+07 | 102830 | 4.76762 | 2(Loss) |
| simdjson (ondemand) | 414.339 | 2.26248 | 30.1004ms | 52708 | 30 | 2.26012e+08 | 121317 | 5.62509 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2222.53 | 0.924088 | 6.7492ms | 52708 | 30 | 1.3104e+06 | 22616.7 | 1.04657 | 1(Win) |
| glaze | 1904.75 | 1.10459 | 7.6887ms | 52708 | 30 | 2.54921e+06 | 26390 | 1.22198 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 591.728 | 1.30372 | 28.8051ms | 70103 | 30 | 6.50911e+07 | 112983 | 3.93902 | 1(Win) |
| simdjson (ondemand) | 545.521 | 1.30709 | 30.9299ms | 70103 | 30 | 7.69812e+07 | 122553 | 4.27236 | 2(Loss) |
| jsonifier | 510.412 | 1.7826 | 34.6329ms | 70103 | 30 | 1.63553e+08 | 130983 | 4.56384 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2778.31 | 1.01216 | 7.1879ms | 70103 | 30 | 1.77964e+06 | 24063.3 | 0.837473 | 1(Win) |
| glaze | 1687.98 | 0.83791 | 10.9277ms | 70103 | 30 | 3.30409e+06 | 39606.7 | 1.38008 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 512.347 | 0.0606428 | 6.8601ms | 11812 | 30 | 5333.33 | 21986.7 | 4.54325 | 1(Win) |
| glaze | 381.656 | 0.128283 | 18.6794ms | 11812 | 32 | 45877 | 29515.6 | 6.10206 | 2(Loss) |
| simdjson (ondemand) | 251.69 | 2.11606 | 12.0389ms | 11812 | 30 | 2.69087e+07 | 44756.7 | 9.25996 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1114.96 | 0.46855 | 3.7067ms | 11812 | 30 | 67229.9 | 10103.3 | 2.08314 | 1(Win) |
| glaze | 1014.54 | 0.294409 | 3.9751ms | 11812 | 30 | 32057.5 | 11103.3 | 2.28925 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 994.924 | 0.112783 | 8.8185ms | 31235 | 30 | 34206.9 | 29940 | 2.34196 | 1(Win) |
| glaze | 790.972 | 0.0801166 | 10.4341ms | 31235 | 30 | 27310.3 | 37660 | 2.94452 | 2(Loss) |
| simdjson (ondemand) | 615.031 | 1.9732 | 12.8139ms | 31235 | 30 | 2.74002e+07 | 48433.3 | 3.78854 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2545.26 | 0.517373 | 4.156ms | 31235 | 30 | 109989 | 11703.3 | 0.913929 | 1(Win) |
| glaze | 1412.54 | 1.2237 | 55.5952ms | 31235 | 128 | 8.52403e+06 | 21088.3 | 1.64747 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1232.89 | 1.7944 | 21.8745ms | 108313 | 30 | 6.7807e+07 | 83783.3 | 1.8902 | 1(Win) |
| glaze | 555.62 | 1.031 | 46.0325ms | 108313 | 30 | 1.10215e+08 | 185910 | 4.19566 | 2(Loss) |
| simdjson (ondemand) | 334.712 | 0.681644 | 178.678ms | 108313 | 32 | 1.41607e+08 | 308609 | 6.96577 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1679.33 | 1.2683 | 15.9643ms | 108313 | 30 | 1.82582e+07 | 61510 | 1.38743 | 1(Win) |
| glaze | 1305.17 | 1.03771 | 20.4525ms | 108313 | 30 | 2.0235e+07 | 79143.3 | 1.78568 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1069.51 | 1.1232 | 47.9204ms | 213963 | 30 | 1.37769e+08 | 190790 | 2.17961 | 1(Win) |
| glaze | 856.386 | 1.11395 | 58.6098ms | 213963 | 30 | 2.11346e+08 | 238270 | 2.72239 | 2(Loss) |
| simdjson (ondemand) | 625.757 | 0.676833 | 79.8799ms | 213963 | 30 | 1.46134e+08 | 326087 | 3.72582 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2803.93 | 1.03336 | 18.738ms | 213963 | 30 | 1.69655e+07 | 72773.3 | 0.830968 | 1(Win) |
| glaze | 1276.09 | 1.32105 | 40.3385ms | 213963 | 30 | 1.33867e+08 | 159903 | 1.82692 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 348.474 | 0.493455 | 1232.37ms | 1834197 | 30 | 1.84063e+10 | 5.01967e+06 | 6.69206 | 1(Win) |
| glaze | 187.963 | 0.793626 | 2255.97ms | 1834197 | 30 | 1.63645e+11 | 9.30625e+06 | 12.407 | 2(Loss) |
| simdjson (ondemand) | 168.216 | 2.07071 | 2476.17ms | 1834197 | 30 | 1.39097e+12 | 1.03987e+07 | 13.8633 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 335.158 | 0.136296 | 1253.92ms | 1834197 | 30 | 1.51803e+09 | 5.21912e+06 | 6.95783 | 1(Win) |
| glaze | 284.136 | 0.0577135 | 1483.51ms | 1833577 | 30 | 3.7846e+08 | 6.15421e+06 | 8.20727 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1284.71 | 0.161903 | 1780.31ms | 9930848 | 30 | 4.27363e+09 | 7.37194e+06 | 1.81518 | 1(Win) |
| glaze STATISTICAL TIE | 794.516 | 2.06631 | 2834.75ms | 9930848 | 30 | 1.82003e+12 | 1.19202e+07 | 2.9351 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 782.914 | 1.24045 | 6761.28ms | 9930848 | 32 | 7.20534e+11 | 1.20969e+07 | 2.97854 | 2(Tie) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 681.309 | 0.287841 | 218.236ms | 642697 | 30 | 2.01164e+08 | 899627 | 3.42277 | 1(Win) |
| glaze | 434.082 | 0.205233 | 341.485ms | 642697 | 30 | 2.51933e+08 | 1.412e+06 | 5.3721 | 2(Loss) |
| simdjson (ondemand) | 423.72 | 0.208965 | 349.377ms | 642697 | 30 | 2.74108e+08 | 1.44653e+06 | 5.5033 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 637.168 | 0.278034 | 232.56ms | 642697 | 30 | 2.14596e+08 | 961950 | 3.65973 | 1(Win) |
| glaze | 410.192 | 0.25493 | 364.046ms | 642692 | 30 | 4.35305e+08 | 1.49422e+06 | 5.68437 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 976.243 | 0.368271 | 704.044ms | 1225964 | 32 | 6.22479e+08 | 1.19762e+06 | 2.38863 | 1(Win) |
| simdjson (ondemand) | 750.864 | 0.15698 | 375.502ms | 1225964 | 30 | 1.79244e+08 | 1.5571e+06 | 3.10562 | 2(Loss) |
| glaze | 726.858 | 0.123461 | 388.687ms | 1225964 | 30 | 1.18314e+08 | 1.60853e+06 | 3.20829 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 925.313 | 0.364745 | 305.759ms | 1225964 | 30 | 6.37202e+08 | 1.26354e+06 | 2.51976 | 1(Win) |
| glaze | 542.703 | 2.02013 | 998.235ms | 1225970 | 32 | 6.06101e+10 | 2.15436e+06 | 4.29627 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 460.107 | 0.462865 | 208.538ms | 409725 | 30 | 4.63551e+08 | 849247 | 5.06817 | 1(Win) |
| glaze | 297.921 | 0.50258 | 315.827ms | 409725 | 30 | 1.30351e+09 | 1.31157e+06 | 7.82736 | 2(Loss) |
| simdjson (ondemand) | 263.908 | 0.266319 | 874.135ms | 409725 | 32 | 4.97547e+08 | 1.48061e+06 | 8.83586 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1039.96 | 0.465796 | 91.8539ms | 409725 | 30 | 9.18891e+07 | 375730 | 2.24197 | 1(Tie) |
| glaze STATISTICAL TIE | 1035.46 | 0.742415 | 96.0569ms | 409725 | 30 | 2.35469e+08 | 377363 | 2.25171 | 1(Tie) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 576.668 | 0.254081 | 325.172ms | 785750 | 30 | 3.27025e+08 | 1.29945e+06 | 4.04377 | 1(Win) |
| glaze | 505.395 | 0.23869 | 361.987ms | 785750 | 30 | 3.75749e+08 | 1.4827e+06 | 4.61408 | 2(Loss) |
| simdjson (ondemand) | 485.43 | 0.243245 | 379.729ms | 785750 | 30 | 4.22984e+08 | 1.54368e+06 | 4.80382 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1617.94 | 0.573296 | 112.73ms | 785750 | 30 | 2.11506e+08 | 463150 | 1.4411 | 1(Win) |
| glaze | 842.61 | 0.735586 | 220.118ms | 785750 | 30 | 1.28382e+09 | 889320 | 2.76706 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 408.764 | 1.80658 | 4350.14ms | 8587914 | 30 | 3.93065e+12 | 2.00362e+07 | 5.70475 | 1(Win) |
| glaze | 356.939 | 0.283463 | 5920.84ms | 8587914 | 30 | 1.26911e+11 | 2.29453e+07 | 6.5333 | 2(Loss) |
| simdjson (ondemand) | 352.261 | 0.192935 | 5650.11ms | 8587914 | 30 | 6.03655e+10 | 2.325e+07 | 6.62012 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 502.227 | 0.36882 | 4516.19ms | 9804437 | 30 | 1.41447e+11 | 1.86175e+07 | 4.6432 | 1(Win) |
| glaze | 400.797 | 0.313478 | 5638.39ms | 9804437 | 30 | 1.60448e+11 | 2.33291e+07 | 5.81835 | 2(Loss) |
| simdjson (ondemand) | 396.995 | 0.341845 | 5706.12ms | 9804437 | 30 | 1.94471e+11 | 2.35525e+07 | 5.87412 | 3(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2021.04 | 1.27114 | 32.7276ms | 264040 | 30 | 7.52482e+07 | 124593 | 1.15336 | 1(Win) |
| simdjson (ondemand) | 1403.04 | 0.914048 | 44.4071ms | 264040 | 30 | 8.07344e+07 | 179473 | 1.66163 | 2(Loss) |
| glaze | 761.563 | 0.795196 | 81.9966ms | 264040 | 30 | 2.07395e+08 | 330647 | 3.06157 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2723.39 | 1.0599 | 35.1757ms | 399947 | 30 | 6.6106e+07 | 140053 | 0.855958 | 1(Win) |
| simdjson (ondemand) | 1822.39 | 1.18848 | 51.0128ms | 399947 | 30 | 1.85623e+08 | 209297 | 1.27922 | 2(Loss) |
| glaze | 1059.07 | 0.638033 | 88.6671ms | 399947 | 30 | 1.58404e+08 | 360147 | 2.20153 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 786.515 | 0.974728 | 78.9824ms | 264040 | 30 | 2.92155e+08 | 320157 | 2.96407 | 1(Win) |
| glaze | 475.696 | 0.619324 | 138.217ms | 264040 | 30 | 3.22432e+08 | 529347 | 4.90155 | 2(Loss) |
| simdjson (ondemand) | 414.711 | 0.674475 | 147.223ms | 264040 | 30 | 5.03155e+08 | 607190 | 5.62258 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2102.43 | 1.03124 | 31.1372ms | 264040 | 30 | 4.57649e+07 | 119770 | 1.10867 | 1(Win) |
| glaze | 1630.44 | 0.835657 | 38.8226ms | 263923 | 30 | 4.99255e+07 | 154373 | 1.42974 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 705.922 | 0.786555 | 138.965ms | 399947 | 30 | 5.4184e+08 | 540313 | 3.30255 | 1(Win) |
| glaze | 637.224 | 0.599124 | 158.389ms | 399947 | 30 | 3.85811e+08 | 598563 | 3.6591 | 2(Loss) |
| simdjson (ondemand) | 601.102 | 0.549405 | 154.111ms | 399947 | 30 | 3.64599e+08 | 634533 | 3.87921 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2825.82 | 0.933806 | 34.0112ms | 399947 | 30 | 4.76598e+07 | 134977 | 0.82492 | 1(Win) |
| glaze | 1540.93 | 0.664861 | 61.2831ms | 399830 | 30 | 8.12026e+07 | 247453 | 1.51304 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1142.52 | 0.823885 | 94.8447ms | 466906 | 30 | 3.09307e+08 | 389733 | 2.04077 | 1(Win) |
| glaze | 911.941 | 0.516174 | 118.483ms | 466906 | 30 | 1.90563e+08 | 488273 | 2.55691 | 2(Loss) |
| simdjson (ondemand) | 531.02 | 0.320196 | 205.651ms | 466906 | 30 | 2.16267e+08 | 838530 | 4.39132 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1758.22 | 0.690043 | 93.3334ms | 699405 | 30 | 2.05582e+08 | 379363 | 1.32608 | 1(Win) |
| glaze | 1081.41 | 0.436171 | 149.773ms | 699405 | 30 | 2.17124e+08 | 616790 | 2.15627 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1351.11 | 0.479703 | 108.564ms | 631514 | 30 | 1.37167e+08 | 445750 | 1.72581 | 1(Win) |
| jsonifier | 1128.33 | 0.52917 | 129.608ms | 631514 | 30 | 2.39337e+08 | 533763 | 2.06656 | 2(Loss) |
