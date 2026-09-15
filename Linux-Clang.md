# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

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

> Adaptive sampling on (AMD EPYC 9V45 96-Core Processor-AVX512): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.500000% AND mean shift < 1.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [43ba991](https://github.com/realtimechris/benchmarksuite/commit/43ba991).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1000.33 | 0.0804732 | 1.75349ms | 1811 | 30 | 57.9126 | 1726.53 | 2.43959 | 1(Win) |
| glaze | 938.423 | 0.129597 | 0.509879ms | 1811 | 30 | 170.668 | 1840.43 | 2.59902 | 2(Loss) |
| simdjson (ondemand) | 227.031 | 0.0325264 | 1.92511ms | 1811 | 30 | 183.678 | 7607.33 | 10.8642 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 741.618 | 0.0490276 | 0.662657ms | 1811 | 30 | 39.1092 | 2328.83 | 3.30009 | 1(Win) |
| glaze | 504.662 | 0.0423087 | 0.904467ms | 1798 | 30 | 61.9954 | 3397.73 | 4.86639 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1928.53 | 0.0534985 | 0.578411ms | 3873 | 30 | 31.4954 | 1915.23 | 1.26516 | 1(Win) |
| glaze | 1421.26 | 0.0511085 | 0.694944ms | 3873 | 30 | 52.9241 | 2598.8 | 1.72348 | 2(Loss) |
| simdjson (ondemand) | 478.743 | 0.0497051 | 2.02617ms | 3873 | 30 | 441.178 | 7715.17 | 5.15365 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2781.94 | 0.101703 | 0.399315ms | 3873 | 30 | 54.7 | 1327.7 | 0.871564 | 1(Win) |
| glaze | 2047.06 | 0.0935099 | 0.536338ms | 3873 | 30 | 85.4023 | 1804.33 | 1.19089 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2034.07 | 0.0552368 | 0.554075ms | 3862 | 30 | 30.0103 | 1810.7 | 1.19942 | 1(Win) |
| glaze | 1428.9 | 0.0708487 | 0.696527ms | 3862 | 30 | 100.047 | 2577.57 | 1.71599 | 2(Loss) |
| simdjson (ondemand) | 492.798 | 0.0377469 | 1.90205ms | 3862 | 30 | 238.764 | 7473.83 | 5.00763 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2966.57 | 0.0991178 | 0.410431ms | 3862 | 30 | 45.4299 | 1241.53 | 0.815441 | 1(Win) |
| glaze | 2038.23 | 0.0958523 | 0.553023ms | 3862 | 30 | 90 | 1807 | 1.19807 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1042.11 | 0.101171 | 0.325024ms | 905 | 30 | 21.0621 | 828.2 | 2.30103 | 1(Win) |
| glaze | 1011.63 | 0.110411 | 0.592472ms | 905 | 32 | 28.3942 | 853.156 | 2.37099 | 2(Loss) |
| simdjson (ondemand) | 157.289 | 0.072705 | 1.43142ms | 905 | 30 | 477.476 | 5487.2 | 15.665 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1252.59 | 0.408273 | 0.238075ms | 905 | 30 | 237.413 | 689.033 | 1.90173 | 1(Win) |
| glaze | 637.411 | 0.241425 | 0.422149ms | 905 | 30 | 320.585 | 1354.03 | 3.81028 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3133.94 | 0.0381731 | 0.798649ms | 9578 | 30 | 37.1368 | 2914.63 | 0.782867 | 1(Win) |
| glaze | 2642.92 | 0.0685651 | 0.923344ms | 9578 | 30 | 168.464 | 3456.13 | 0.929717 | 2(Loss) |
| simdjson (ondemand) | 1124.02 | 0.0633057 | 2.06449ms | 9578 | 30 | 793.982 | 8126.47 | 2.19498 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5874.14 | 0.0748947 | 0.465894ms | 9578 | 30 | 40.6897 | 1555 | 0.41422 | 1(Win) |
| glaze | 4359.77 | 0.164447 | 0.576438ms | 9578 | 30 | 356.12 | 2095.13 | 0.560461 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 6424.55 | 1.53591 | 8.40484ms | 233995 | 30 | 8.53845e+06 | 34734.7 | 0.384693 | 1(Win) |
| jsonifier | 6006.49 | 1.30831 | 9.01087ms | 233995 | 30 | 7.08785e+06 | 37152.3 | 0.411901 | 2(Loss) |
| glaze | 2254 | 0.34893 | 24.0667ms | 233995 | 30 | 3.58017e+06 | 99004 | 1.09813 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 7750.5 | 0.75627 | 10.2854ms | 346753 | 30 | 3.12361e+06 | 42666.9 | 0.318898 | 1(Win) |
| jsonifier | 7550.81 | 0.562283 | 10.6517ms | 346753 | 30 | 1.81921e+06 | 43795.2 | 0.327691 | 2(Loss) |
| glaze | 2689.21 | 0.315722 | 29.408ms | 346753 | 30 | 4.52193e+06 | 122969 | 0.92046 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2001.26 | 0.301376 | 27.1653ms | 233995 | 30 | 3.388e+06 | 111507 | 1.23654 | 1(Win) |
| glaze | 1951.44 | 1.01371 | 28.0541ms | 233995 | 30 | 4.03137e+07 | 114354 | 1.26833 | 2(Loss) |
| simdjson (ondemand) | 1694.62 | 0.289595 | 31.899ms | 233995 | 30 | 4.36288e+06 | 131684 | 1.46034 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5098.53 | 0.382076 | 10.774ms | 233995 | 30 | 838966 | 43768.5 | 0.485324 | 1(Win) |
| glaze | 3926.05 | 0.54667 | 13.6642ms | 233995 | 30 | 2.89651e+06 | 56839.6 | 0.630313 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2488.56 | 0.292905 | 31.9556ms | 346753 | 30 | 4.54485e+06 | 132884 | 0.994672 | 1(Tie) |
| glaze STATISTICAL TIE | 2487.49 | 0.31409 | 32.56ms | 346753 | 30 | 5.23055e+06 | 132941 | 0.995144 | 1(Tie) |
| simdjson (ondemand) | 2398.04 | 0.333139 | 33.3732ms | 346753 | 30 | 6.33139e+06 | 137900 | 1.03223 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6124.74 | 0.844987 | 13.1446ms | 346753 | 30 | 6.24434e+06 | 53992.4 | 0.404044 | 1(Win) |
| glaze | 4321.95 | 0.520661 | 18.5078ms | 346753 | 30 | 4.76115e+06 | 76513.9 | 0.572569 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5901.87 | 1.24234 | 9.03694ms | 233995 | 30 | 6.61965e+06 | 37810.9 | 0.419198 | 1(Win) |
| simdjson (ondemand) | 3818.51 | 0.536808 | 14.0805ms | 233995 | 30 | 2.95246e+06 | 58440.3 | 0.648032 | 2(Loss) |
| glaze | 2294.89 | 0.35776 | 23.3584ms | 233995 | 30 | 3.63073e+06 | 97240 | 1.07857 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7560.09 | 0.414155 | 10.4624ms | 346753 | 30 | 984541 | 43741.5 | 0.327291 | 1(Win) |
| simdjson (ondemand) | 5353.56 | 0.368485 | 14.9125ms | 346753 | 30 | 1.55423e+06 | 61770 | 0.46224 | 2(Loss) |
| glaze | 2781.88 | 0.306894 | 28.9237ms | 346753 | 30 | 3.99265e+06 | 118873 | 0.889803 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2006.84 | 0.365849 | 26.904ms | 233995 | 30 | 4.96493e+06 | 111197 | 1.23313 | 1(Win) |
| jsonifier | 1942.06 | 0.247646 | 27.843ms | 233995 | 30 | 2.42923e+06 | 114906 | 1.27456 | 2(Loss) |
| simdjson (ondemand) | 373.874 | 0.126866 | 141.037ms | 233995 | 30 | 1.72019e+07 | 596873 | 6.62186 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4875.63 | 0.573479 | 11.2493ms | 233995 | 30 | 2.06685e+06 | 45769.5 | 0.507514 | 1(Win) |
| glaze | 4013.62 | 0.518492 | 13.539ms | 233995 | 30 | 2.49314e+06 | 55599.5 | 0.616568 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2599.79 | 0.244107 | 30.7367ms | 346753 | 30 | 2.89232e+06 | 127199 | 0.951945 | 1(Win) |
| jsonifier | 2416.91 | 0.272642 | 33.211ms | 346753 | 30 | 4.17473e+06 | 136823 | 1.02419 | 2(Loss) |
| simdjson (ondemand) | 557.06 | 0.239649 | 143.454ms | 346753 | 30 | 6.07166e+07 | 593633 | 4.44429 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6322.5 | 0.483206 | 12.8893ms | 346753 | 30 | 1.91624e+06 | 52303.6 | 0.391367 | 1(Win) |
| glaze | 4257.35 | 0.45786 | 19.0922ms | 346753 | 30 | 3.79445e+06 | 77675 | 0.581238 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1209.64 | 0.33278 | 18.1473ms | 94651 | 30 | 1.85e+06 | 74622.4 | 2.04579 | 1(Tie) |
| glaze STATISTICAL TIE | 1195.12 | 0.54263 | 18.4849ms | 94651 | 30 | 5.03909e+06 | 75528.7 | 2.07089 | 1(Tie) |
| jsonifier | 1172.48 | 0.333845 | 18.7634ms | 94651 | 30 | 1.98175e+06 | 76987.3 | 2.11086 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6383.72 | 0.0277714 | 3.59116ms | 94651 | 30 | 462.616 | 14140.1 | 0.387098 | 1(Win) |
| glaze | 5908.22 | 0.0353787 | 3.88422ms | 94651 | 30 | 876.478 | 15278.1 | 0.41832 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1682 | 0.312385 | 18.5961ms | 136024 | 30 | 1.74132e+06 | 77123.8 | 1.47122 | 1(Win) |
| glaze | 1508.98 | 0.388296 | 20.7325ms | 136024 | 30 | 3.3428e+06 | 85967 | 1.64017 | 2(Loss) |
| jsonifier | 1472.93 | 0.365806 | 22.5815ms | 136024 | 30 | 3.11379e+06 | 88071.1 | 1.68018 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7271.91 | 0.0250908 | 4.43749ms | 136024 | 30 | 601.016 | 17838.9 | 0.339941 | 1(Win) |
| glaze | 6337.99 | 1.03944 | 4.99435ms | 136046 | 30 | 1.35829e+06 | 20470.8 | 0.390116 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 778.457 | 0.109982 | 599.065ms | 2090234 | 30 | 2.37949e+08 | 2.56071e+06 | 3.18039 | 1(Win) |
| glaze | 623.096 | 1.52017 | 1736.11ms | 2090234 | 32 | 7.56861e+10 | 3.19919e+06 | 3.97343 | 2(Loss) |
| simdjson (ondemand) | 490.366 | 0.859864 | 966.772ms | 2090234 | 30 | 3.66546e+10 | 4.06513e+06 | 5.04889 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1621.2 | 0.226783 | 294.568ms | 2090234 | 30 | 2.33271e+08 | 1.22958e+06 | 1.52713 | 1(Win) |
| glaze | 1024.18 | 0.0422472 | 481.522ms | 2090234 | 30 | 2.0284e+07 | 1.94634e+06 | 2.41736 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2074.1 | 0.114646 | 752.974ms | 6661897 | 30 | 3.69979e+08 | 3.06315e+06 | 1.19367 | 1(Win) |
| glaze | 1746.52 | 0.165242 | 884.616ms | 6661897 | 30 | 1.08395e+09 | 3.63767e+06 | 1.41757 | 2(Loss) |
| simdjson (ondemand) | 1492.33 | 0.325503 | 1029.03ms | 6661897 | 30 | 5.76098e+09 | 4.25728e+06 | 1.65897 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4324.11 | 0.153758 | 357.66ms | 6661897 | 30 | 1.53109e+08 | 1.46927e+06 | 0.572543 | 1(Win) |
| glaze | 2798.68 | 0.136573 | 553.355ms | 6661897 | 30 | 2.88363e+08 | 2.2701e+06 | 0.884624 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1741.36 | 0.213462 | 65.3415ms | 500299 | 30 | 1.02623e+07 | 273994 | 1.42165 | 1(Win) |
| glaze | 1383.05 | 0.221684 | 81.3191ms | 500299 | 30 | 1.75459e+07 | 344979 | 1.78995 | 2(Loss) |
| simdjson (ondemand) | 1032.16 | 0.160323 | 112.33ms | 500299 | 30 | 1.64771e+07 | 462258 | 2.39848 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5702.81 | 1.26404 | 20.4926ms | 500299 | 30 | 3.35525e+07 | 83664.5 | 0.433957 | 1(Win) |
| glaze | 4380.7 | 0.391088 | 26.6251ms | 500299 | 30 | 5.44303e+06 | 108915 | 0.564951 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3458.74 | 0.174773 | 95.1363ms | 1439562 | 30 | 1.44377e+07 | 396929 | 0.715768 | 1(Win) |
| glaze STATISTICAL TIE | 2777.64 | 0.273416 | 118.202ms | 1439562 | 30 | 5.47869e+07 | 494259 | 0.891287 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2758.24 | 0.301107 | 119.388ms | 1439562 | 30 | 6.73848e+07 | 497736 | 0.897544 | 2(Tie) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7858.89 | 0.347549 | 41.6652ms | 1439562 | 30 | 1.10584e+07 | 174690 | 0.314966 | 1(Win) |
| glaze | 6048.3 | 0.304509 | 54.1775ms | 1439584 | 30 | 1.43327e+07 | 226989 | 0.409269 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1606.19 | 0.740426 | 8.32411ms | 56369 | 30 | 1.84235e+06 | 33469.1 | 1.54016 | 1(Win) |
| glaze STATISTICAL TIE | 1415.39 | 0.785632 | 9.61777ms | 56369 | 30 | 2.67109e+06 | 37980.8 | 1.74802 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1408.34 | 1.39158 | 9.46118ms | 56369 | 30 | 8.46444e+06 | 38170.8 | 1.75669 | 2(Tie) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7306.02 | 2.45234 | 1.88129ms | 56369 | 30 | 976793 | 7358 | 0.337661 | 1(Win) |
| glaze | 6093.5 | 0.562578 | 2.25561ms | 56369 | 30 | 73898.1 | 8822.13 | 0.4052 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2247.26 | 0.578481 | 9.97015ms | 94370 | 30 | 1.61013e+06 | 40048 | 1.10099 | 1(Win) |
| simdjson (ondemand) | 2092.74 | 1.10278 | 10.3198ms | 94370 | 30 | 6.74743e+06 | 43005 | 1.18228 | 2(Loss) |
| glaze | 1982.07 | 0.421899 | 11.4989ms | 94370 | 30 | 1.10096e+06 | 45406.3 | 1.24839 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9139.41 | 0.0497471 | 2.53894ms | 94370 | 30 | 719.926 | 9847.27 | 0.270174 | 1(Win) |
| glaze | 5575.85 | 1.12798 | 4.55375ms | 94370 | 30 | 994414 | 16140.7 | 0.443296 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1780 | 0.861453 | 7.05062ms | 52708 | 30 | 1.7754e+06 | 28239.4 | 1.38905 | 1(Win) |
| jsonifier | 1518.15 | 0.657573 | 19.0206ms | 52708 | 32 | 1.51691e+06 | 33110.2 | 1.62907 | 2(Loss) |
| glaze | 1297.84 | 1.06377 | 10.0488ms | 52708 | 30 | 5.09246e+06 | 38730.6 | 1.90629 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6560.41 | 0.148853 | 4.55171ms | 52708 | 32 | 4162.51 | 7662.06 | 0.376156 | 1(Win) |
| glaze | 6153.42 | 0.27796 | 2.11776ms | 52708 | 30 | 15467 | 8168.83 | 0.401085 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2185.02 | 0.65779 | 7.62499ms | 70103 | 30 | 1.21523e+06 | 30597.2 | 1.13172 | 1(Win) |
| glaze | 1613.31 | 0.85744 | 10.3293ms | 70103 | 30 | 3.78764e+06 | 41440 | 1.53362 | 2(Loss) |
| jsonifier | 1465.05 | 0.577085 | 11.523ms | 70103 | 30 | 2.08051e+06 | 45633.6 | 1.68872 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6698.58 | 1.86565 | 2.58193ms | 70103 | 30 | 1.04014e+06 | 9980.53 | 0.368571 | 1(Win) |
| glaze | 6204.26 | 0.0442715 | 2.74319ms | 70103 | 30 | 682.754 | 10775.7 | 0.39803 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1192.37 | 0.0629548 | 2.4613ms | 11812 | 30 | 1061.21 | 9447.4 | 2.07039 | 1(Win) |
| glaze | 1115.06 | 0.327325 | 2.69432ms | 11812 | 30 | 32804.2 | 10102.4 | 2.21478 | 2(Loss) |
| simdjson (ondemand) | 1096.43 | 0.0582951 | 5.96049ms | 11812 | 32 | 1147.89 | 10274.1 | 2.25232 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5203.38 | 0.0555602 | 0.622447ms | 11812 | 30 | 43.4034 | 2164.9 | 0.470152 | 1(Win) |
| glaze | 3683.11 | 0.153467 | 0.854783ms | 11812 | 30 | 660.948 | 3058.5 | 0.666427 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2747.79 | 0.102629 | 2.74563ms | 31235 | 30 | 3713.44 | 10840.7 | 0.898572 | 1(Win) |
| jsonifier | 2327.84 | 1.49001 | 3.20832ms | 31235 | 30 | 1.09063e+06 | 12796.4 | 1.06131 | 2(Loss) |
| glaze | 2085.22 | 1.52125 | 3.7256ms | 31235 | 30 | 1.41678e+06 | 14285.3 | 1.1853 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7691.07 | 0.0654465 | 1.06921ms | 31235 | 30 | 192.754 | 3873.07 | 0.319557 | 1(Win) |
| glaze | 5309.11 | 0.195771 | 1.48052ms | 31235 | 30 | 3619.58 | 5610.73 | 0.464306 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3357.29 | 0.783217 | 7.67496ms | 108313 | 30 | 1.74209e+06 | 30767.5 | 0.736786 | 1(Win) |
| simdjson (ondemand) | 1644.86 | 0.392244 | 15.1316ms | 108313 | 30 | 1.82028e+06 | 62798.8 | 1.50447 | 2(Loss) |
| glaze | 1532.18 | 0.385833 | 16.155ms | 108313 | 30 | 2.02985e+06 | 67417.4 | 1.61524 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4111.52 | 0.0549223 | 6.17091ms | 108313 | 30 | 5711.83 | 25123.4 | 0.601472 | 1(Win) |
| glaze | 2720.84 | 0.707007 | 9.22943ms | 108313 | 30 | 2.16135e+06 | 37964.6 | 0.909345 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 3183.02 | 0.386983 | 15.5743ms | 213963 | 30 | 1.84631e+06 | 64106.1 | 0.777477 | 1(Win) |
| jsonifier | 2833.3 | 0.439858 | 17.6035ms | 213963 | 30 | 3.0105e+06 | 72018.9 | 0.873523 | 2(Loss) |
| glaze | 2676.8 | 0.344427 | 18.5604ms | 213963 | 30 | 2.06805e+06 | 76229.5 | 0.924601 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6303.09 | 0.508453 | 7.93538ms | 213963 | 30 | 812818 | 32373.2 | 0.392469 | 1(Win) |
| glaze | 3911.57 | 1.0724 | 12.5614ms | 213963 | 30 | 9.38888e+06 | 52166 | 0.632634 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 914.264 | 0.269831 | 453.77ms | 1834197 | 30 | 7.99564e+08 | 1.91326e+06 | 2.70798 | 1(Win) |
| glaze | 617.782 | 0.117265 | 703.729ms | 1834197 | 30 | 3.30736e+08 | 2.83146e+06 | 4.0076 | 2(Loss) |
| simdjson (ondemand) | 545.954 | 0.08354 | 788.901ms | 1834197 | 30 | 2.14927e+08 | 3.20398e+06 | 4.53486 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1010.2 | 0.120555 | 398.521ms | 1834197 | 30 | 1.30728e+08 | 1.73156e+06 | 2.45075 | 1(Win) |
| glaze | 648.371 | 0.115421 | 649.133ms | 1833577 | 30 | 2.90699e+08 | 2.69697e+06 | 3.81851 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3459.81 | 0.117713 | 661.027ms | 9930848 | 30 | 3.11487e+08 | 2.73737e+06 | 0.715581 | 1(Win) |
| glaze | 2691.34 | 0.0995318 | 856.556ms | 9930848 | 30 | 3.68028e+08 | 3.51899e+06 | 0.919919 | 2(Loss) |
| simdjson (ondemand) | 2607.67 | 0.0970248 | 916.099ms | 9930848 | 30 | 3.72524e+08 | 3.6319e+06 | 0.949416 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3956.19 | 0.185461 | 576.48ms | 9930848 | 30 | 5.91353e+08 | 2.39392e+06 | 0.625787 | 1(Win) |
| glaze | 2406.46 | 0.187494 | 917.75ms | 9930228 | 30 | 1.63326e+09 | 3.93533e+06 | 1.02877 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1529.35 | 0.183568 | 98.1186ms | 642697 | 30 | 1.62373e+07 | 400773 | 1.61872 | 1(Win) |
| glaze | 1360.63 | 0.272603 | 107.901ms | 642697 | 30 | 4.52391e+07 | 450471 | 1.81946 | 2(Loss) |
| simdjson (ondemand) | 1091.6 | 0.136267 | 136.99ms | 642697 | 30 | 1.75626e+07 | 561492 | 2.26794 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1835.58 | 0.29493 | 80.2858ms | 642697 | 30 | 2.90956e+07 | 333913 | 1.34864 | 1(Win) |
| glaze | 1458.5 | 0.1796 | 99.7714ms | 642692 | 30 | 1.70895e+07 | 420241 | 1.69736 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2132.67 | 0.141057 | 131.682ms | 1225964 | 30 | 1.79398e+07 | 548220 | 1.16082 | 1(Win) |
| glaze | 2062.8 | 0.121645 | 136.272ms | 1225964 | 30 | 1.42612e+07 | 566789 | 1.20015 | 2(Loss) |
| simdjson (ondemand) | 1983.36 | 0.140073 | 141.2ms | 1225964 | 30 | 2.04543e+07 | 589490 | 1.24821 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3077.16 | 0.197717 | 91.0943ms | 1225964 | 30 | 1.69302e+07 | 379951 | 0.804478 | 1(Win) |
| glaze | 2444.03 | 0.134131 | 115.074ms | 1225970 | 30 | 1.23517e+07 | 478380 | 1.01294 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1059.12 | 0.928744 | 92.7383ms | 409725 | 30 | 3.52213e+08 | 368932 | 2.33733 | 1(Win) |
| jsonifier | 988.074 | 0.15595 | 96.3505ms | 409725 | 30 | 1.14104e+07 | 395461 | 2.50547 | 2(Loss) |
| glaze | 709.184 | 0.700073 | 131.969ms | 409725 | 30 | 4.46349e+08 | 550977 | 3.49083 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3303.47 | 0.899589 | 28.6905ms | 409725 | 30 | 3.39668e+07 | 118283 | 0.749233 | 1(Win) |
| glaze | 3066.42 | 0.307876 | 30.5686ms | 409725 | 30 | 4.61737e+06 | 127427 | 0.807144 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1971.93 | 0.1688 | 91.5006ms | 785750 | 30 | 1.23439e+07 | 380009 | 1.25539 | 1(Win) |
| jsonifier | 1560.48 | 0.159992 | 115.271ms | 785750 | 30 | 1.7708e+07 | 480205 | 1.58646 | 2(Loss) |
| glaze | 1204.42 | 0.132675 | 149.636ms | 785750 | 30 | 2.04416e+07 | 622167 | 2.05549 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5021.5 | 0.287076 | 35.9433ms | 785750 | 30 | 5.50575e+06 | 149228 | 0.492916 | 1(Win) |
| glaze | 4154.39 | 0.341787 | 42.947ms | 785750 | 30 | 1.14021e+07 | 180375 | 0.595825 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1235.77 | 0.898843 | 1572.38ms | 8587914 | 30 | 1.06461e+11 | 6.62753e+06 | 2.00341 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1040.13 | 0.674459 | 1884.72ms | 8587914 | 30 | 8.46118e+10 | 7.87407e+06 | 2.38027 | 2(Tie) |
| glaze STATISTICAL TIE | 1010.09 | 1.40297 | 1981.73ms | 8587914 | 30 | 3.88217e+11 | 8.10829e+06 | 2.45108 | 2(Tie) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3628.27 | 0.268524 | 575.14ms | 8588126 | 30 | 1.10226e+09 | 2.25735e+06 | 0.682334 | 1(Win) |
| jsonifier | 3438.24 | 0.258146 | 565.002ms | 8588126 | 30 | 1.13443e+09 | 2.38211e+06 | 0.719978 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1188.01 | 1.39493 | 1857.24ms | 9804437 | 30 | 3.61602e+11 | 7.87049e+06 | 2.08396 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1167.45 | 0.574605 | 1929.9ms | 9804437 | 30 | 6.35369e+10 | 8.00909e+06 | 2.1207 | 1(Tie) |
| glaze | 1043.36 | 1.24908 | 2051.6ms | 9804437 | 30 | 3.75902e+11 | 8.96162e+06 | 2.37291 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3857.56 | 0.827011 | 678.647ms | 11078090 | 30 | 1.53904e+10 | 2.73875e+06 | 0.641712 | 1(Win) |
| glaze | 3714.99 | 0.260954 | 678.308ms | 11078090 | 30 | 1.65221e+09 | 2.84386e+06 | 0.666356 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 7486.93 | 0.899426 | 8.2395ms | 264040 | 30 | 2.74526e+06 | 33633 | 0.330399 | 1(Win) |
| jsonifier | 7003.3 | 0.862693 | 8.92118ms | 264040 | 30 | 2.88648e+06 | 35955.6 | 0.35328 | 2(Loss) |
| glaze | 2097.27 | 0.275694 | 29.0373ms | 264040 | 30 | 3.28705e+06 | 120065 | 1.18025 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 8858.79 | 0.749892 | 10.4424ms | 399947 | 30 | 3.12734e+06 | 43055.4 | 0.279316 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 8820.5 | 0.745066 | 10.5072ms | 399947 | 30 | 3.11408e+06 | 43242.4 | 0.280497 | 1(Tie) |
| glaze | 2754.05 | 0.307504 | 33.365ms | 399947 | 30 | 5.44109e+06 | 138494 | 0.898805 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1718.96 | 0.421063 | 34.1534ms | 264040 | 30 | 1.14137e+07 | 146489 | 1.43982 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1713.4 | 0.36233 | 35.9653ms | 264040 | 30 | 8.50655e+06 | 146964 | 1.44469 | 1(Tie) |
| glaze | 1563.15 | 0.589968 | 39.0641ms | 264040 | 30 | 2.70967e+07 | 161090 | 1.58357 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7043.67 | 1.93468 | 8.82332ms | 264040 | 30 | 1.43509e+07 | 35749.6 | 0.351206 | 1(Win) |
| glaze | 5398.23 | 0.824293 | 11.593ms | 263923 | 30 | 4.43136e+06 | 46625.8 | 0.458226 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2846.4 | 1.23731 | 33.1342ms | 399947 | 30 | 8.24696e+07 | 134001 | 0.869555 | 1(Win) |
| glaze | 2020.79 | 0.347052 | 47.6107ms | 399947 | 30 | 1.28727e+07 | 188747 | 1.22499 | 2(Loss) |
| jsonifier | 1857.71 | 0.30026 | 50.2781ms | 399947 | 30 | 1.14015e+07 | 205317 | 1.33251 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6796.16 | 0.604168 | 14.1287ms | 399947 | 30 | 3.44917e+06 | 56122.8 | 0.3641 | 1(Win) |
| glaze | 5834.66 | 0.495597 | 16.0656ms | 399830 | 30 | 3.14702e+06 | 65352.2 | 0.424069 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 3147.63 | 0.343452 | 34.1511ms | 466906 | 30 | 7.08184e+06 | 141464 | 0.78639 | 1(Tie) |
| glaze STATISTICAL TIE | 3130.8 | 0.297667 | 34.2204ms | 466906 | 30 | 5.37688e+06 | 142224 | 0.790642 | 1(Tie) |
| simdjson (ondemand) | 1362.18 | 0.197541 | 78.3177ms | 466906 | 30 | 1.25092e+07 | 326886 | 1.81736 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5528.09 | 0.374802 | 67.5752ms | 699405 | 32 | 6.54427e+06 | 120657 | 0.447715 | 1(Win) |
| glaze | 3985 | 0.276429 | 39.7675ms | 699405 | 30 | 6.42227e+06 | 167379 | 0.621158 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4977.46 | 0.413861 | 29.5237ms | 631514 | 30 | 7.52282e+06 | 120997 | 0.497259 | 1(Win) |
| glaze | 2673.22 | 0.20417 | 54.683ms | 631514 | 30 | 6.34752e+06 | 225293 | 0.926068 | 2(Loss) |
