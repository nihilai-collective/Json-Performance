# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

Latest Results: (Sep 15, 2026)
#### Using the following commits:
----
| Jsonifier: [d6b5beb](https://github.com/nihilai-collective/jsonifier/commit/d6b5beb)  
| Glaze: [2518e75](https://github.com/stephenberry/glaze/commit/2518e75)  
| Simdjson: [9572dd0](https://github.com/simdjson/simdjson/commit/9572dd0)  

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
  This is the commit of BenchmarkSuite that was used to generate these results: [43ba991](https://github.com/realtimechris/benchmarksuite/commit/43ba991).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 484.343 | 0.139913 | 1.157ms | 1811 | 30 | 746.74 | 3565.87 | 4.76429 | 1(Win) |
| jsonifier | 294.14 | 0.257633 | 4.3644ms | 1811 | 30 | 6865.18 | 5871.7 | 7.87215 | 2(Loss) |
| simdjson (ondemand) | 152.784 | 0.346155 | 3.04484ms | 1811 | 30 | 45935.2 | 11304.2 | 15.2154 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 364.587 | 0.500066 | 3.21579ms | 1811 | 32 | 17957.2 | 4737.16 | 6.34482 | 1(Win) |
| glaze | 272.99 | 1.35749 | 1.78981ms | 1798 | 30 | 218114 | 6281.2 | 8.49055 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1302.44 | 0.0943059 | 1.01856ms | 3873 | 30 | 214.576 | 2835.9 | 1.76764 | 1(Win) |
| glaze | 991.468 | 0.0971808 | 1.18506ms | 3873 | 30 | 393.206 | 3725.37 | 2.32854 | 2(Loss) |
| simdjson (ondemand) | 341.071 | 2.36865 | 2.85711ms | 3873 | 30 | 1.97391e+06 | 10829.4 | 6.81486 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1450.53 | 0.0995728 | 0.977755ms | 3873 | 30 | 192.861 | 2546.37 | 1.5844 | 1(Win) |
| glaze | 1051.03 | 2.17173 | 1.07373ms | 3873 | 30 | 174741 | 3514.23 | 2.19466 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1329.67 | 0.0619028 | 1.00323ms | 3862 | 30 | 88.2023 | 2769.93 | 1.72911 | 1(Win) |
| glaze | 803.659 | 0.0975738 | 1.38759ms | 3862 | 30 | 599.886 | 4582.9 | 2.87779 | 2(Loss) |
| simdjson (ondemand) | 343.902 | 0.0451949 | 2.84987ms | 3862 | 30 | 702.838 | 10709.7 | 6.75872 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1604.16 | 0.116205 | 0.890501ms | 3862 | 30 | 213.551 | 2295.97 | 1.43077 | 1(Win) |
| glaze | 1046.24 | 0.228402 | 1.1418ms | 3862 | 30 | 1939.46 | 3520.3 | 2.20448 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 543.51 | 0.150408 | 0.73023ms | 905 | 30 | 171.137 | 1587.97 | 4.18622 | 1(Win) |
| glaze | 425.888 | 0.203878 | 0.781526ms | 905 | 30 | 512.12 | 2026.53 | 5.37285 | 2(Loss) |
| simdjson (ondemand) | 115.809 | 0.068455 | 2.10168ms | 905 | 30 | 780.806 | 7452.57 | 20.0368 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 721.514 | 0.325096 | 0.626385ms | 905 | 30 | 453.683 | 1196.2 | 3.13587 | 1(Win) |
| glaze | 281.548 | 0.258848 | 0.991059ms | 905 | 30 | 1888.88 | 3065.47 | 8.17576 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1833.23 | 0.064166 | 1.62457ms | 9578 | 30 | 306.654 | 4982.63 | 1.26246 | 1(Win) |
| glaze | 1439.32 | 0.0878107 | 1.82553ms | 9578 | 30 | 931.651 | 6346.27 | 1.61031 | 2(Loss) |
| simdjson (ondemand) | 773.535 | 0.616817 | 3.12452ms | 9578 | 30 | 159156 | 11808.5 | 3.00541 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2938.05 | 0.148832 | 1.09891ms | 9578 | 30 | 642.309 | 3108.97 | 0.783921 | 1(Win) |
| glaze | 2200.65 | 0.140774 | 1.27543ms | 9578 | 30 | 1024.27 | 4150.73 | 1.04997 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2783.87 | 1.41646 | 19.5046ms | 233995 | 30 | 3.86762e+07 | 80160 | 0.83723 | 1(Win) |
| simdjson (ondemand) | 2649.33 | 0.540383 | 20.7576ms | 233995 | 30 | 6.21536e+06 | 84230.8 | 0.87983 | 2(Loss) |
| glaze | 1494.21 | 0.458005 | 36.7212ms | 233995 | 30 | 1.40362e+07 | 149346 | 1.56035 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3513.22 | 0.519644 | 23.1952ms | 346753 | 30 | 7.17734e+06 | 94127.3 | 0.663316 | 1(Win) |
| simdjson (ondemand) | 3286.12 | 0.55287 | 24.4992ms | 346753 | 30 | 9.28625e+06 | 100632 | 0.709261 | 2(Loss) |
| glaze | 1815.23 | 0.426914 | 44.0678ms | 346753 | 30 | 1.81461e+07 | 182175 | 1.28437 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1234.25 | 0.382201 | 44.3898ms | 233995 | 30 | 1.43255e+07 | 180802 | 1.8889 | 1(Win) |
| glaze | 921.646 | 0.92314 | 57.9408ms | 233995 | 30 | 1.49879e+08 | 242127 | 2.52964 | 2(Loss) |
| simdjson (ondemand) | 838.563 | 0.356124 | 64.1617ms | 233995 | 30 | 2.69442e+07 | 266116 | 2.7804 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2286.91 | 0.661102 | 23.8097ms | 233995 | 30 | 1.24845e+07 | 97579.1 | 1.01916 | 1(Win) |
| glaze | 1920.09 | 0.67582 | 28.4804ms | 233995 | 30 | 1.85077e+07 | 116221 | 1.21385 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1295.69 | 0.408936 | 61.6664ms | 346753 | 30 | 3.26789e+07 | 255222 | 1.79939 | 1(Win) |
| glaze | 1196.1 | 0.386552 | 66.4824ms | 346753 | 30 | 3.42645e+07 | 276474 | 1.94912 | 2(Loss) |
| simdjson (ondemand) | 1177.12 | 0.501271 | 67.5877ms | 346753 | 30 | 5.9493e+07 | 280931 | 1.98074 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2067.51 | 0.82007 | 38.9502ms | 346753 | 30 | 5.16139e+07 | 159945 | 1.12752 | 1(Win) |
| glaze | 1663.16 | 0.572273 | 48.489ms | 346753 | 30 | 3.88421e+07 | 198832 | 1.40178 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2709.91 | 0.700642 | 20.0709ms | 233995 | 30 | 9.9866e+06 | 82347.8 | 0.860108 | 1(Win) |
| simdjson (ondemand) | 1912.78 | 0.535485 | 28.4733ms | 233995 | 30 | 1.17084e+07 | 116665 | 1.21859 | 2(Loss) |
| glaze | 1473.68 | 0.452217 | 36.6439ms | 233995 | 30 | 1.40677e+07 | 151427 | 1.58207 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3432.34 | 0.644013 | 23.5604ms | 346753 | 30 | 1.15497e+07 | 96345.1 | 0.67902 | 1(Win) |
| simdjson (ondemand) | 2512 | 0.504075 | 31.968ms | 346753 | 30 | 1.32103e+07 | 131644 | 0.927977 | 2(Loss) |
| glaze | 1838.39 | 0.383357 | 43.5055ms | 346753 | 30 | 1.42658e+07 | 179880 | 1.26827 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1145.65 | 0.462314 | 47.4598ms | 233995 | 30 | 2.43279e+07 | 194784 | 2.03506 | 1(Win) |
| glaze | 951.812 | 0.352116 | 57.1147ms | 233995 | 30 | 2.04457e+07 | 234453 | 2.44962 | 2(Loss) |
| simdjson (ondemand) | 218.259 | 0.286138 | 245.607ms | 233995 | 30 | 2.5677e+08 | 1.02243e+06 | 10.6843 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2304.79 | 0.792343 | 23.6896ms | 233995 | 30 | 1.76563e+07 | 96822.4 | 1.01127 | 1(Win) |
| glaze | 1977.49 | 0.505406 | 27.7619ms | 233995 | 30 | 9.75862e+06 | 112848 | 1.17871 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1253.81 | 0.411998 | 63.5672ms | 346753 | 30 | 3.54234e+07 | 263748 | 1.85953 | 1(Win) |
| jsonifier | 1209.72 | 0.531016 | 67.4443ms | 346753 | 30 | 6.32128e+07 | 273360 | 1.92737 | 2(Loss) |
| simdjson (ondemand) | 314.511 | 0.355762 | 251.467ms | 346753 | 30 | 4.19767e+08 | 1.05144e+06 | 7.41452 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2118.62 | 0.545133 | 37.8534ms | 346753 | 30 | 2.17201e+07 | 156088 | 1.10031 | 1(Win) |
| glaze | 1654.7 | 0.46216 | 48.6335ms | 346753 | 30 | 2.55922e+07 | 199848 | 1.40893 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 698.758 | 0.427003 | 31.6616ms | 94651 | 30 | 9.1281e+06 | 129181 | 3.33625 | 1(Win) |
| simdjson (ondemand) | 657.935 | 0.537592 | 33.2411ms | 94651 | 30 | 1.63197e+07 | 137196 | 3.54285 | 2(Loss) |
| glaze | 639.323 | 0.499251 | 34.3956ms | 94651 | 30 | 1.49063e+07 | 141190 | 3.64636 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2759.81 | 1.09865 | 8.13606ms | 94651 | 30 | 3.87374e+06 | 32707.4 | 0.844054 | 1(Win) |
| glaze | 2634.05 | 1.09701 | 8.45457ms | 94651 | 30 | 4.2398e+06 | 34269 | 0.883827 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 911.543 | 0.538827 | 34.5239ms | 136024 | 30 | 1.764e+07 | 142311 | 2.55743 | 1(Win) |
| jsonifier | 816.388 | 0.443197 | 38.7675ms | 136024 | 30 | 1.48783e+07 | 158898 | 2.85548 | 2(Loss) |
| glaze | 788.534 | 0.51202 | 39.9526ms | 136024 | 30 | 2.12855e+07 | 164511 | 2.95581 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3291.04 | 0.858786 | 9.86072ms | 136024 | 30 | 3.43761e+06 | 39416.9 | 0.707703 | 1(Win) |
| glaze | 1840.95 | 0.853017 | 17.2698ms | 136046 | 30 | 1.08423e+07 | 70476.3 | 1.26572 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 452.457 | 0.14642 | 1058.53ms | 2090234 | 30 | 1.24842e+09 | 4.40573e+06 | 5.15426 | 1(Win) |
| glaze | 326.524 | 0.231275 | 1462.33ms | 2090234 | 30 | 5.98051e+09 | 6.10492e+06 | 7.1421 | 2(Loss) |
| simdjson (ondemand) | 304.025 | 0.092751 | 1576.79ms | 2090234 | 30 | 1.1095e+09 | 6.5567e+06 | 7.6707 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 670.564 | 0.116056 | 714.741ms | 2090234 | 30 | 3.57081e+08 | 2.97273e+06 | 3.47776 | 1(Win) |
| glaze | 661.611 | 0.0738801 | 737.664ms | 2090234 | 30 | 1.48648e+08 | 3.01295e+06 | 3.52483 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1166.23 | 0.0739246 | 1308.55ms | 6661897 | 30 | 4.86546e+08 | 5.44769e+06 | 1.99966 | 1(Win) |
| simdjson (ondemand) | 914.122 | 0.0842742 | 1674.85ms | 6661897 | 30 | 1.0292e+09 | 6.95015e+06 | 2.55117 | 2(Loss) |
| glaze | 861.129 | 0.104467 | 1775.26ms | 6661897 | 30 | 1.78213e+09 | 7.37785e+06 | 2.70817 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1920.74 | 0.182607 | 805.536ms | 6661897 | 30 | 1.0945e+09 | 3.30772e+06 | 1.21414 | 1(Win) |
| glaze | 1500.46 | 0.200182 | 1032.67ms | 6661897 | 30 | 2.15536e+09 | 4.23424e+06 | 1.55422 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1006.61 | 0.279321 | 114.011ms | 500299 | 30 | 5.25857e+07 | 473990 | 2.31648 | 1(Win) |
| glaze | 825.18 | 0.277568 | 138.722ms | 500299 | 30 | 7.72722e+07 | 578204 | 2.82586 | 2(Loss) |
| simdjson (ondemand) | 501.604 | 0.11275 | 229.533ms | 500299 | 30 | 3.45055e+07 | 951193 | 4.64897 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2036.48 | 0.538209 | 56.5496ms | 500299 | 30 | 4.77003e+07 | 234288 | 1.14486 | 1(Win) |
| jsonifier | 1842.29 | 0.380558 | 63.0648ms | 500299 | 30 | 2.91412e+07 | 258984 | 1.26558 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1816.54 | 0.163294 | 182.581ms | 1439562 | 30 | 4.5691e+07 | 755762 | 1.28371 | 1(Win) |
| glaze | 1582.68 | 0.161311 | 208.931ms | 1439562 | 30 | 5.8738e+07 | 867433 | 1.47339 | 2(Loss) |
| simdjson (ondemand) | 1320.52 | 0.173899 | 251.057ms | 1439562 | 30 | 9.80588e+07 | 1.03965e+06 | 1.76595 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3221.72 | 0.501349 | 102.975ms | 1439562 | 30 | 1.36927e+08 | 426131 | 0.723735 | 1(Win) |
| glaze | 2085.2 | 0.278094 | 160.188ms | 1439584 | 30 | 1.00574e+08 | 658401 | 1.1183 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 942.861 | 0.781177 | 14.2979ms | 56369 | 30 | 5.95122e+06 | 57015.5 | 2.47117 | 1(Win) |
| glaze | 816.98 | 0.7251 | 16.2858ms | 56369 | 30 | 6.82927e+06 | 65800.4 | 2.85257 | 2(Loss) |
| simdjson (ondemand) | 686.041 | 0.803421 | 19.4594ms | 56369 | 30 | 1.18902e+07 | 78359.3 | 3.39703 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1986.99 | 1.12338 | 6.86242ms | 56369 | 30 | 2.77119e+06 | 27054.8 | 1.17204 | 1(Win) |
| jsonifier | 1703.04 | 0.929221 | 7.91668ms | 56369 | 30 | 2.58102e+06 | 31565.8 | 1.3678 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1128.13 | 0.861665 | 19.7857ms | 94370 | 30 | 1.41757e+07 | 79776.3 | 2.06566 | 1(Win) |
| glaze STATISTICAL TIE | 1089.5 | 0.61832 | 20.4093ms | 94370 | 30 | 7.82637e+06 | 82605 | 2.13894 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1087.83 | 0.607029 | 20.3711ms | 94370 | 30 | 7.56636e+06 | 82731.9 | 2.14263 | 2(Tie) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2460.47 | 1.36354 | 9.00654ms | 94370 | 30 | 7.4626e+06 | 36577.7 | 0.946612 | 1(Win) |
| glaze | 1757.29 | 0.981598 | 12.6614ms | 94370 | 30 | 7.58175e+06 | 51214.2 | 1.32544 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 842.514 | 1.09303 | 14.7243ms | 52708 | 30 | 1.2758e+07 | 59662.3 | 2.76503 | 1(Win) |
| jsonifier | 756.114 | 1.40807 | 16.5142ms | 52708 | 30 | 2.62874e+07 | 66479.7 | 3.07835 | 2(Loss) |
| glaze | 707.873 | 0.756908 | 17.647ms | 52708 | 30 | 8.66661e+06 | 71010.3 | 3.2918 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2690.94 | 0.245523 | 4.99304ms | 52708 | 30 | 63102.8 | 18679.8 | 0.864528 | 1(Win) |
| jsonifier | 2477.15 | 2.39425 | 11.6001ms | 52708 | 32 | 7.55335e+06 | 20292 | 0.938715 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1097.28 | 0.990124 | 15.2078ms | 70103 | 30 | 1.0918e+07 | 60928.6 | 2.12306 | 1(Win) |
| glaze | 839.533 | 0.79299 | 19.7407ms | 70103 | 30 | 1.19634e+07 | 79634.1 | 2.77583 | 2(Loss) |
| jsonifier | 710.082 | 1.34259 | 23.4687ms | 70103 | 30 | 4.7936e+07 | 94151.7 | 3.27606 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2904.59 | 1.96458 | 5.8291ms | 70103 | 30 | 6.13434e+06 | 23017.2 | 0.801289 | 1(Win) |
| glaze | 2496.36 | 0.100155 | 6.93451ms | 70103 | 30 | 21583.8 | 26781.2 | 0.932788 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 734.351 | 0.0577972 | 4.19281ms | 11812 | 30 | 2358.17 | 15339.8 | 3.16821 | 1(Win) |
| glaze | 601.436 | 0.221671 | 5.00046ms | 11812 | 30 | 51714.1 | 18729.8 | 3.87004 | 2(Loss) |
| simdjson (ondemand) | 550.332 | 1.6818 | 5.2573ms | 11812 | 30 | 3.55524e+06 | 20469.1 | 4.22997 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2566.01 | 0.156242 | 1.31913ms | 11812 | 30 | 1411.38 | 4390 | 0.901228 | 1(Win) |
| glaze | 1186.95 | 0.979414 | 5.66796ms | 11812 | 32 | 276480 | 9490.53 | 1.95768 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1439.36 | 0.0603266 | 5.4198ms | 31235 | 30 | 4676.06 | 20695.3 | 1.61738 | 1(Win) |
| simdjson (ondemand) | 1349.49 | 1.26197 | 5.60779ms | 31235 | 30 | 2.32787e+06 | 22073.5 | 1.72534 | 2(Loss) |
| glaze | 1124.95 | 0.084022 | 15.5521ms | 31235 | 32 | 15840 | 26479.5 | 2.07022 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2833.88 | 0.718908 | 2.84177ms | 31235 | 30 | 171312 | 10511.4 | 0.820222 | 1(Win) |
| glaze | 1867.51 | 0.265748 | 4.18922ms | 31235 | 30 | 53903.4 | 15950.6 | 1.24585 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1856.27 | 0.901436 | 13.8562ms | 108313 | 30 | 7.54866e+06 | 55646.7 | 1.25535 | 1(Win) |
| glaze | 986.057 | 0.877499 | 25.3474ms | 108313 | 30 | 2.53496e+07 | 104756 | 2.36352 | 2(Loss) |
| simdjson (ondemand) | 794.968 | 0.540443 | 31.7281ms | 108313 | 30 | 1.47939e+07 | 129936 | 2.93245 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1837.24 | 1.05534 | 13.7084ms | 108313 | 30 | 1.05617e+07 | 56223.1 | 1.26851 | 1(Win) |
| glaze | 1700.33 | 0.852853 | 14.9447ms | 108313 | 30 | 8.05313e+06 | 60750.2 | 1.37041 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1443.69 | 0.498926 | 33.6342ms | 213963 | 30 | 1.49183e+07 | 141339 | 1.61482 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1442.59 | 0.460718 | 34.5612ms | 213963 | 30 | 1.27404e+07 | 141448 | 1.61608 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1432.81 | 1.39752 | 34.4173ms | 213963 | 30 | 1.18833e+08 | 142414 | 1.62675 | 1(Tie) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2867.35 | 0.888016 | 17.3705ms | 213963 | 30 | 1.19806e+07 | 71163.7 | 0.81282 | 1(Win) |
| glaze | 1643.96 | 0.658771 | 29.918ms | 213963 | 30 | 2.00579e+07 | 124122 | 1.41778 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 488.851 | 0.133022 | 862.935ms | 1834197 | 30 | 6.79686e+08 | 3.57824e+06 | 4.7705 | 1(Win) |
| glaze | 352.631 | 0.0837356 | 1186.55ms | 1834197 | 30 | 5.17597e+08 | 4.9605e+06 | 6.61335 | 2(Loss) |
| simdjson (ondemand) | 267.77 | 0.193884 | 1565.75ms | 1834197 | 30 | 4.81254e+09 | 6.53257e+06 | 8.70925 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 391.78 | 0.0729049 | 1071.32ms | 1833577 | 30 | 3.1765e+08 | 4.46331e+06 | 5.95252 | 1(Win) |
| jsonifier | 385.596 | 0.174476 | 1088.91ms | 1834197 | 30 | 1.87941e+09 | 4.53643e+06 | 6.04795 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1515.5 | 0.0956648 | 1503.69ms | 9930848 | 30 | 1.07222e+09 | 6.24927e+06 | 1.53879 | 1(Win) |
| glaze | 1370.08 | 0.07773 | 1662.85ms | 9930848 | 30 | 8.66119e+08 | 6.91257e+06 | 1.70214 | 2(Loss) |
| simdjson (ondemand) | 1302.21 | 0.12242 | 1749.74ms | 9930848 | 30 | 2.37813e+09 | 7.27287e+06 | 1.79084 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1613.7 | 0.267397 | 1409ms | 9930848 | 30 | 7.38865e+09 | 5.86901e+06 | 1.44513 | 1(Win) |
| glaze | 1322.12 | 0.297624 | 1717ms | 9930228 | 30 | 1.36343e+10 | 7.16289e+06 | 1.76385 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 853.947 | 0.205882 | 173.172ms | 642697 | 30 | 6.55104e+07 | 717753 | 2.73075 | 1(Win) |
| glaze | 734.938 | 0.750544 | 199.039ms | 642697 | 30 | 1.1754e+09 | 833980 | 3.17291 | 2(Loss) |
| simdjson (ondemand) | 551.071 | 0.209957 | 267.16ms | 642697 | 30 | 1.63598e+08 | 1.11224e+06 | 4.23174 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 705.55 | 0.125325 | 209.121ms | 642697 | 30 | 3.55593e+07 | 868718 | 3.30508 | 1(Win) |
| glaze | 628.949 | 0.262316 | 234.802ms | 642692 | 30 | 1.96041e+08 | 974512 | 3.70768 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1165.51 | 0.123309 | 241.564ms | 1225964 | 30 | 4.59023e+07 | 1.00314e+06 | 2.00081 | 1(Win) |
| glaze | 1069.38 | 0.0637534 | 263.206ms | 1225964 | 30 | 1.45755e+07 | 1.09332e+06 | 2.18069 | 2(Loss) |
| simdjson (ondemand) | 937.448 | 0.750364 | 298.476ms | 1225964 | 30 | 2.6274e+09 | 1.24718e+06 | 2.48759 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1246.03 | 0.192204 | 224.832ms | 1225964 | 30 | 9.7576e+07 | 938316 | 1.8715 | 1(Win) |
| glaze | 1038.57 | 0.158995 | 271.56ms | 1225970 | 30 | 9.61123e+07 | 1.12576e+06 | 2.24538 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 596.678 | 0.168349 | 158.118ms | 409725 | 30 | 3.64628e+07 | 654866 | 3.90816 | 1(Win) |
| simdjson (ondemand) | 503.624 | 0.252631 | 185.979ms | 409725 | 30 | 1.15257e+08 | 775864 | 4.63033 | 2(Loss) |
| glaze | 411.322 | 0.254626 | 228.173ms | 409725 | 30 | 1.75529e+08 | 949972 | 5.66946 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1410.99 | 0.389682 | 67.5796ms | 409725 | 30 | 3.49366e+07 | 276930 | 1.65244 | 1(Win) |
| jsonifier | 1247.47 | 0.306543 | 75.734ms | 409725 | 30 | 2.76586e+07 | 313230 | 1.86904 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 912.932 | 0.618509 | 195.545ms | 785750 | 30 | 7.73226e+08 | 820817 | 2.55434 | 1(Win) |
| jsonifier | 789.584 | 0.287753 | 227.826ms | 785750 | 30 | 2.23735e+08 | 949043 | 2.9534 | 2(Loss) |
| glaze | 641.185 | 0.130665 | 281.026ms | 785750 | 30 | 6.99584e+07 | 1.16869e+06 | 3.63701 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1871.52 | 0.493907 | 95.5484ms | 785750 | 30 | 1.17325e+08 | 400396 | 1.24586 | 1(Win) |
| glaze | 1608.51 | 0.397703 | 112.113ms | 785750 | 30 | 1.02982e+08 | 465867 | 1.44966 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 738.559 | 0.307884 | 2684.19ms | 8587914 | 30 | 3.49703e+10 | 1.10893e+07 | 3.15759 | 1(Win) |
| simdjson (ondemand) | 655.097 | 0.283494 | 3107.92ms | 8587914 | 30 | 3.76855e+10 | 1.25021e+07 | 3.55985 | 2(Loss) |
| glaze | 612.354 | 0.370936 | 3223.85ms | 8587914 | 30 | 7.38399e+10 | 1.33747e+07 | 3.80837 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2130.28 | 0.35622 | 933.651ms | 8588126 | 30 | 5.62704e+09 | 3.84469e+06 | 1.09466 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2123.97 | 0.499753 | 950.535ms | 8588126 | 30 | 1.11412e+10 | 3.85611e+06 | 1.09792 | 1(Tie) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 709.089 | 0.757754 | 3138.11ms | 9804437 | 30 | 2.99518e+11 | 1.31863e+07 | 3.28881 | 1(Win) |
| jsonifier | 688.253 | 0.597026 | 3259.68ms | 9804437 | 30 | 1.97359e+11 | 1.35855e+07 | 3.38833 | 2(Loss) |
| glaze | 642.728 | 0.805178 | 3818.99ms | 9804437 | 30 | 4.1162e+11 | 1.45477e+07 | 3.62839 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2213.57 | 0.192406 | 1121.92ms | 11078090 | 30 | 2.52989e+09 | 4.77278e+06 | 1.05345 | 1(Win) |
| glaze | 2046.05 | 0.375785 | 1238.01ms | 11078090 | 30 | 1.12953e+10 | 5.16355e+06 | 1.13972 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2747.03 | 0.927963 | 22.3363ms | 264040 | 30 | 2.17068e+07 | 91665.6 | 0.848339 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2744.32 | 0.772421 | 22.5193ms | 264040 | 30 | 1.50695e+07 | 91756.2 | 0.849168 | 1(Tie) |
| glaze | 1145.23 | 0.398513 | 53.1814ms | 264040 | 30 | 2.30333e+07 | 219875 | 2.03588 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 3587.48 | 0.486203 | 26.0356ms | 399947 | 30 | 8.01648e+06 | 106320 | 0.649695 | 1(Tie) |
| jsonifier STATISTICAL TIE | 3501.03 | 1.62513 | 26.2162ms | 399947 | 30 | 9.40398e+07 | 108945 | 0.665684 | 1(Tie) |
| glaze | 1583.77 | 0.389027 | 58.4331ms | 399947 | 30 | 2.6333e+07 | 240829 | 1.47208 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 956.587 | 0.456671 | 63.7953ms | 264040 | 30 | 4.33529e+07 | 263236 | 2.4373 | 1(Win) |
| simdjson (ondemand) | 869.435 | 0.404181 | 70.4203ms | 264040 | 30 | 4.11092e+07 | 289623 | 2.68173 | 2(Loss) |
| glaze | 817.118 | 0.35911 | 75.2441ms | 264040 | 30 | 3.67406e+07 | 308166 | 2.85353 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2360.76 | 0.754688 | 25.8663ms | 264040 | 30 | 1.94399e+07 | 106664 | 0.987293 | 1(Win) |
| glaze | 2296.62 | 0.631128 | 27.3589ms | 263923 | 30 | 1.43526e+07 | 109594 | 1.01486 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1189.62 | 0.402526 | 77.6362ms | 399947 | 30 | 4.99689e+07 | 320624 | 1.95999 | 1(Win) |
| glaze | 1020.55 | 0.370256 | 90.4631ms | 399947 | 30 | 5.74468e+07 | 373740 | 2.28477 | 2(Loss) |
| jsonifier | 988.78 | 0.385333 | 94.8082ms | 399947 | 30 | 6.62825e+07 | 385747 | 2.35815 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2992.32 | 0.761909 | 30.8785ms | 399947 | 30 | 2.82955e+07 | 127466 | 0.778971 | 1(Win) |
| glaze | 2144.46 | 0.490761 | 43.561ms | 399830 | 30 | 2.28442e+07 | 177810 | 1.08715 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1560.34 | 0.327337 | 68.9169ms | 466906 | 30 | 2.61776e+07 | 285370 | 1.49433 | 1(Win) |
| jsonifier | 1214.56 | 0.250248 | 88.6625ms | 466906 | 30 | 2.52512e+07 | 366615 | 1.91977 | 2(Loss) |
| simdjson (ondemand) | 628.014 | 0.16127 | 171.094ms | 466906 | 30 | 3.92238e+07 | 709022 | 3.71302 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1887.82 | 0.300389 | 85.2788ms | 699405 | 30 | 3.37929e+07 | 353320 | 1.23513 | 1(Win) |
| jsonifier | 1798.35 | 0.346307 | 90.9428ms | 699405 | 30 | 4.94939e+07 | 370897 | 1.29654 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2309.1 | 0.400109 | 63.0097ms | 631514 | 30 | 3.26705e+07 | 260819 | 1.00977 | 1(Win) |
| glaze | 1537.98 | 0.224918 | 94.694ms | 631514 | 30 | 2.32721e+07 | 391591 | 1.51617 | 2(Loss) |
