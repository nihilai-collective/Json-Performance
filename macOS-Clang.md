# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.5.0 using the Clang 22.1.8 compiler).  

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

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 695.861 | 2.42725 | 40.9837ms | 1811 | 30 | 108879 | 2481.97 | 1(Win) |
| glaze | 503.035 | 0.198794 | 0.962ms | 1811 | 30 | 1397.55 | 3433.37 | 2(Loss) |
| simdjson (ondemand) | 175.862 | 0.2858 | 2.66017ms | 1811 | 30 | 23634.1 | 9820.8 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 529.808 | 0.596074 | 0.93625ms | 1811 | 30 | 11327.2 | 3259.87 | 1(Win) |
| glaze | 350.033 | 0.166797 | 1.39863ms | 1798 | 30 | 2002.91 | 4898.7 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1304.22 | 2.15422 | 0.743292ms | 3873 | 30 | 111660 | 2832.03 | 1(Win) |
| glaze | 912.303 | 0.111594 | 1.05387ms | 3873 | 30 | 612.378 | 4048.63 | 2(Loss) |
| simdjson (ondemand) | 363.546 | 1.77334 | 2.39242ms | 3873 | 30 | 973826 | 10159.9 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1676.72 | 0.349454 | 0.785375ms | 3873 | 30 | 1777.77 | 2202.87 | 1(Win) |
| glaze | 982.221 | 2.04723 | 2.28471ms | 3873 | 32 | 189653 | 3760.44 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1524.08 | 0.248026 | 0.725959ms | 3862 | 30 | 1077.77 | 2416.6 | 1(Win) |
| glaze | 848.339 | 1.98558 | 1.10554ms | 3862 | 30 | 222936 | 4341.53 | 2(Loss) |
| simdjson (ondemand) | 409.481 | 0.171607 | 2.35221ms | 3862 | 30 | 7147.43 | 8994.53 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1696.63 | 0.310936 | 0.667916ms | 3862 | 30 | 1366.83 | 2170.83 | 1(Win) |
| glaze | 1051.05 | 0.215709 | 0.986542ms | 3862 | 30 | 1714.1 | 3504.2 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1095.97 | 0.39036 | 0.3015ms | 905 | 30 | 283.5 | 787.5 | 1(Win) |
| glaze | 337.354 | 0.16763 | 0.715333ms | 905 | 30 | 551.757 | 2558.37 | 2(Loss) |
| simdjson (ondemand) | 184.942 | 0.0610502 | 1.30229ms | 905 | 30 | 243.513 | 4666.73 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 666.759 | 0.148008 | 0.437875ms | 905 | 30 | 110.116 | 1294.43 | 1(Win) |
| glaze | 296.054 | 0.500975 | 1.22762ms | 905 | 30 | 6398.96 | 2915.27 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2082.55 | 0.163564 | 1.27329ms | 9578 | 30 | 1544.02 | 4386.1 | 1(Win) |
| glaze | 1388.96 | 0.125494 | 1.79058ms | 9578 | 30 | 2043.34 | 6576.37 | 2(Loss) |
| simdjson (ondemand) | 659.779 | 1.13001 | 3.50496ms | 9578 | 30 | 734238 | 13844.5 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2975.92 | 0.163888 | 0.942416ms | 9578 | 30 | 759.145 | 3069.4 | 1(Win) |
| glaze | 2413.52 | 0.190395 | 1.05783ms | 9578 | 30 | 1557.69 | 3784.63 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3222.13 | 1.51629 | 16.3886ms | 233995 | 30 | 3.30838e+07 | 69257.1 | 1(Win) |
| simdjson (ondemand) | 2992.42 | 0.761161 | 19.1242ms | 233995 | 30 | 9.66594e+06 | 74573.5 | 2(Loss) |
| glaze | 1100.21 | 0.527458 | 48.7327ms | 233995 | 30 | 3.43366e+07 | 202829 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4082.73 | 0.504216 | 22.3777ms | 346753 | 30 | 5.00373e+06 | 80997.2 | 1(Win) |
| simdjson (ondemand) | 3629.38 | 0.758133 | 83.3644ms | 346753 | 32 | 1.52692e+07 | 91114.7 | 2(Loss) |
| glaze | 1486.89 | 1.18659 | 56.9626ms | 346753 | 30 | 2.08929e+08 | 222403 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1523.73 | 0.629305 | 35.7961ms | 233995 | 30 | 2.54823e+07 | 146453 | 1(Win) |
| glaze | 1138.26 | 2.45223 | 54.1085ms | 233995 | 30 | 6.93381e+08 | 196049 | 2(Loss) |
| simdjson (ondemand) | 900.363 | 2.12778 | 55.9998ms | 233995 | 30 | 8.34357e+08 | 247850 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2131.55 | 0.736016 | 60.8082ms | 233995 | 32 | 1.89997e+07 | 104691 | 1(Win) |
| glaze | 1979.67 | 0.884702 | 28.2638ms | 233995 | 30 | 2.98363e+07 | 112724 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1765.72 | 1.39444 | 44.8448ms | 346753 | 30 | 2.04605e+08 | 187283 | 1(Win) |
| jsonifier | 1482.75 | 0.476527 | 130.19ms | 346753 | 32 | 3.61436e+07 | 223025 | 2(Loss) |
| simdjson (ondemand) | 1290.54 | 1.46754 | 62.556ms | 346753 | 30 | 4.24231e+08 | 256242 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2461.95 | 0.472711 | 79.1063ms | 346753 | 32 | 1.29011e+07 | 134320 | 1(Win) |
| glaze | 2013.01 | 0.418414 | 487.992ms | 346753 | 128 | 6.04741e+07 | 164276 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3357.46 | 0.722118 | 16.3421ms | 233995 | 30 | 6.91081e+06 | 66465.4 | 1(Win) |
| simdjson (ondemand) | 2141.55 | 0.849424 | 25.4998ms | 233995 | 30 | 2.35032e+07 | 104203 | 2(Loss) |
| glaze | 1109.3 | 0.808766 | 47.8107ms | 233995 | 30 | 7.94108e+07 | 201167 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4004.17 | 0.504658 | 20.1573ms | 346753 | 30 | 5.21112e+06 | 82586.2 | 1(Win) |
| simdjson (ondemand) | 2722.94 | 1.22693 | 29.7845ms | 346753 | 30 | 6.66078e+07 | 121446 | 2(Loss) |
| glaze | 1543.42 | 0.494233 | 52.0265ms | 346753 | 30 | 3.36399e+07 | 214257 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1381.86 | 0.690766 | 42.8116ms | 233995 | 30 | 3.73308e+07 | 161489 | 1(Win) |
| glaze | 1305.84 | 0.9909 | 42.4357ms | 233995 | 30 | 8.60233e+07 | 170890 | 2(Loss) |
| simdjson (ondemand) | 245.492 | 0.603538 | 216.794ms | 233995 | 30 | 9.02962e+08 | 909011 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2305.75 | 0.984223 | 23.6881ms | 233995 | 30 | 2.72205e+07 | 96781.8 | 1(Win) |
| glaze | 1937.39 | 1.69038 | 33.854ms | 233995 | 30 | 1.13729e+08 | 115183 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1788.72 | 0.554161 | 48.6731ms | 346753 | 30 | 3.14883e+07 | 184875 | 1(Win) |
| jsonifier | 1456.78 | 0.399004 | 147.712ms | 346753 | 32 | 2.62516e+07 | 227000 | 2(Loss) |
| simdjson (ondemand) | 362.676 | 0.696833 | 257.065ms | 346753 | 30 | 1.2111e+09 | 911804 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2684.59 | 0.664959 | 29.9138ms | 346753 | 30 | 2.01278e+07 | 123181 | 1(Win) |
| glaze | 1993.81 | 0.573184 | 111.571ms | 346753 | 32 | 2.89209e+07 | 165858 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 760.011 | 0.2059 | 31.6893ms | 94651 | 30 | 1.79409e+06 | 118770 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 738.123 | 0.874127 | 30.4733ms | 94651 | 30 | 3.42818e+07 | 122292 | 2(Tie) |
| glaze STATISTICAL TIE | 702.172 | 2.48698 | 32.0931ms | 94651 | 30 | 3.06639e+08 | 128553 | 2(Tie) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3027.67 | 1.03607 | 32.7803ms | 94651 | 32 | 3.05326e+06 | 29813.8 | 1(Win) |
| glaze | 2709.99 | 1.30332 | 24.6954ms | 94651 | 32 | 6.03065e+06 | 33308.7 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1026.99 | 0.876618 | 36.3472ms | 136024 | 30 | 3.67827e+07 | 126314 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1010.48 | 1.03995 | 31.2624ms | 136024 | 30 | 5.34718e+07 | 128378 | 1(Tie) |
| jsonifier | 885.101 | 0.515637 | 36.8407ms | 136024 | 30 | 1.71339e+07 | 146562 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 2652.19 | 1.10628 | 11.9484ms | 136046 | 30 | 8.78643e+06 | 48919.5 | 1(Win) |
| jsonifier | 2489.41 | 1.48811 | 12.6045ms | 136024 | 30 | 1.80397e+07 | 52109.8 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 555.046 | 0.391544 | 860.054ms | 2090234 | 30 | 5.93218e+09 | 3.59142e+06 | 1(Win) |
| glaze | 445.178 | 1.60222 | 1068.67ms | 2090234 | 30 | 1.54415e+11 | 4.47777e+06 | 2(Loss) |
| simdjson (ondemand) | 350.8 | 0.338912 | 3431.64ms | 2090234 | 32 | 1.18684e+10 | 5.68244e+06 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1572.97 | 0.201416 | 318.998ms | 2090234 | 30 | 1.95461e+08 | 1.26729e+06 | 1(Win) |
| glaze | 1411.23 | 0.255317 | 346.473ms | 2090234 | 30 | 3.90192e+08 | 1.41253e+06 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1489.02 | 0.168759 | 1040.54ms | 6661897 | 30 | 1.55543e+09 | 4.26675e+06 | 1(Win) |
| glaze STATISTICAL TIE | 1076.34 | 2.44 | 1364.31ms | 6661897 | 30 | 6.22297e+11 | 5.90266e+06 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1050.91 | 0.350078 | 3617.07ms | 6661897 | 32 | 1.43334e+10 | 6.04553e+06 | 2(Tie) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2711.25 | 0.763654 | 581.458ms | 6661897 | 30 | 9.60661e+09 | 2.3433e+06 | 1(Win) |
| glaze | 2151.63 | 2.13601 | 676.947ms | 6661897 | 30 | 1.19341e+11 | 2.95277e+06 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1426.32 | 1.71816 | 228.732ms | 500299 | 32 | 1.05707e+09 | 334513 | 1(Win) |
| glaze | 939.035 | 1.27082 | 124.237ms | 500299 | 30 | 1.2508e+09 | 508099 | 2(Loss) |
| simdjson (ondemand) | 644.013 | 0.758906 | 188.724ms | 500299 | 30 | 9.48347e+08 | 740858 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2180.36 | 0.988073 | 125.126ms | 500299 | 32 | 1.49599e+08 | 218827 | 1(Win) |
| glaze | 1603.38 | 1.24971 | 76.9502ms | 500299 | 30 | 4.14889e+08 | 297574 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2357.28 | 0.32888 | 143.9ms | 1439562 | 30 | 1.10061e+08 | 582397 | 1(Win) |
| glaze STATISTICAL TIE | 1718.43 | 2.26725 | 176.209ms | 1439562 | 30 | 9.84275e+09 | 798913 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1673.78 | 0.644412 | 200.816ms | 1439562 | 30 | 8.38135e+08 | 820225 | 2(Tie) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3161.86 | 1.14796 | 261.874ms | 1439562 | 32 | 7.95022e+08 | 434198 | 1(Win) |
| glaze | 2443.02 | 1.2051 | 147.36ms | 1439584 | 30 | 1.3759e+09 | 561965 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1506.57 | 1.76701 | 44.6346ms | 56369 | 64 | 2.54427e+07 | 35682.2 | 1(Win) |
| glaze | 1100.49 | 0.522716 | 12.4609ms | 56369 | 30 | 1.95595e+06 | 48848.7 | 2(Loss) |
| simdjson (ondemand) | 843.385 | 1.7355 | 14.6948ms | 56369 | 30 | 3.67115e+07 | 63740.4 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2597.33 | 0.963757 | 5.12217ms | 56369 | 30 | 1.19367e+06 | 20697.3 | 1(Win) |
| glaze | 2090.11 | 1.88989 | 19.4967ms | 56369 | 32 | 7.5608e+06 | 25720.1 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1509.47 | 1.05248 | 15.5777ms | 94370 | 30 | 1.18131e+07 | 59622.4 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1465.27 | 1.17782 | 17.0291ms | 94370 | 30 | 1.57004e+07 | 61420.8 | 1(Tie) |
| simdjson (ondemand) | 1374.95 | 1.62864 | 15.5634ms | 94370 | 30 | 3.4093e+07 | 65455.6 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2818.07 | 0.720214 | 8.19508ms | 94370 | 30 | 1.58711e+06 | 31936.1 | 1(Win) |
| glaze | 2308.63 | 1.18243 | 9.40029ms | 94370 | 30 | 6.37422e+06 | 38983.3 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1347.42 | 0.633578 | 10.4363ms | 52708 | 30 | 1.67598e+06 | 37305.5 | 1(Win) |
| glaze | 1127.5 | 1.29703 | 10.9174ms | 52708 | 30 | 1.00308e+07 | 44581.9 | 2(Loss) |
| simdjson (ondemand) | 1037.58 | 1.70471 | 10.9791ms | 52708 | 30 | 2.04612e+07 | 48445.8 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4061.01 | 0.207341 | 3.17604ms | 52708 | 30 | 19759.5 | 12377.8 | 1(Win) |
| glaze | 3198.58 | 1.43265 | 4.02779ms | 52708 | 30 | 1.52069e+06 | 15715.2 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1393.84 | 2.20951 | 39.9675ms | 70103 | 32 | 3.59409e+07 | 47964.9 | 1(Win) |
| simdjson (ondemand) | 1296.33 | 2.45614 | 35.8586ms | 70103 | 32 | 5.13451e+07 | 51572.9 | 2(Loss) |
| jsonifier | 1156.16 | 1.64582 | 17.9907ms | 70103 | 30 | 2.71719e+07 | 57825.2 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 3212.51 | 1.74061 | 5.23033ms | 70103 | 30 | 3.93648e+06 | 20811 | 1(Win) |
| jsonifier | 2911.32 | 1.32501 | 7.2485ms | 70103 | 30 | 2.77751e+06 | 22964 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1013.17 | 1.70231 | 7.00496ms | 11812 | 32 | 1.14633e+06 | 11118.4 | 1(Win) |
| simdjson (ondemand) | 652.403 | 1.8893 | 4.33708ms | 11812 | 30 | 3.19256e+06 | 17266.6 | 2(Loss) |
| glaze | 324.428 | 1.70044 | 28.4387ms | 11812 | 64 | 2.23107e+07 | 34722 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3126.68 | 0.143563 | 1.01304ms | 11812 | 30 | 802.579 | 3602.8 | 1(Win) |
| glaze | 1428.46 | 0.794002 | 2.067ms | 11812 | 30 | 117619 | 7886 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1617.72 | 0.270596 | 202.732ms | 31235 | 512 | 1.27114e+06 | 18413.6 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1616.73 | 1.74051 | 4.62642ms | 31235 | 30 | 3.08521e+06 | 18424.9 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1556.7 | 1.7548 | 10.7991ms | 31235 | 32 | 3.60813e+06 | 19135.4 | 1(Tie) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2989.17 | 1.52459 | 2.52575ms | 31235 | 30 | 692482 | 9965.3 | 1(Win) |
| glaze | 2317.65 | 0.0818254 | 3.26363ms | 31235 | 30 | 3318.08 | 12852.7 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2349.4 | 1.88701 | 16.4857ms | 108313 | 30 | 2.06498e+07 | 43966.6 | 1(Win) |
| glaze | 1062.8 | 1.4 | 24.5907ms | 108313 | 30 | 5.55438e+07 | 97191.7 | 2(Loss) |
| simdjson (ondemand) | 942.442 | 1.29383 | 25.769ms | 108313 | 30 | 6.03296e+07 | 109604 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2087.54 | 1.54576 | 12.2449ms | 108313 | 30 | 1.75507e+07 | 49481.9 | 1(Win) |
| glaze | 1505.67 | 1.42607 | 16.1762ms | 108313 | 30 | 2.87147e+07 | 68604.1 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1996.45 | 1.28818 | 31.1057ms | 213963 | 30 | 5.20035e+07 | 102207 | 1(Win) |
| glaze | 1928.6 | 0.859555 | 26.7562ms | 213963 | 30 | 2.4812e+07 | 105803 | 2(Loss) |
| simdjson (ondemand) | 1766.15 | 0.698456 | 27.9468ms | 213963 | 30 | 1.95355e+07 | 115535 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3695.55 | 1.4048 | 13.429ms | 213963 | 30 | 1.80496e+07 | 55215.3 | 1(Win) |
| glaze | 1745.6 | 1.03861 | 31.8618ms | 213963 | 30 | 4.42195e+07 | 116895 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 602.497 | 0.315368 | 15572.8ms | 1834197 | 256 | 2.14614e+10 | 2.9033e+06 | 1(Win) |
| glaze | 434.69 | 0.145534 | 988.208ms | 1834197 | 30 | 1.02892e+09 | 4.02407e+06 | 2(Loss) |
| simdjson (ondemand) | 325.062 | 1.69478 | 1356.67ms | 1834197 | 30 | 2.49521e+11 | 5.38121e+06 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 755.306 | 0.925132 | 574.427ms | 1834197 | 30 | 1.37713e+10 | 2.31592e+06 | 1(Win) |
| glaze | 674.506 | 0.770021 | 621.491ms | 1833577 | 30 | 1.19551e+10 | 2.59247e+06 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2196.99 | 0.146513 | 2475.75ms | 9930848 | 32 | 1.2765e+09 | 4.31081e+06 | 1(Win) |
| glaze | 1753.27 | 0.119109 | 1310.41ms | 9930848 | 30 | 1.2419e+09 | 5.4018e+06 | 2(Loss) |
| simdjson (ondemand) | 1512.07 | 0.416356 | 1629.92ms | 9930848 | 30 | 2.04023e+10 | 6.26346e+06 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2415.05 | 0.29135 | 1017.37ms | 9930848 | 30 | 3.91626e+09 | 3.92157e+06 | 1(Win) |
| glaze | 2088.27 | 0.154178 | 1141.75ms | 9930228 | 30 | 1.4666e+09 | 4.53494e+06 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1135.96 | 0.615927 | 129.192ms | 642697 | 30 | 3.31337e+08 | 539567 | 1(Win) |
| glaze | 942.927 | 0.649135 | 156ms | 642697 | 30 | 5.34131e+08 | 650022 | 2(Loss) |
| simdjson (ondemand) | 645.43 | 0.643084 | 229.118ms | 642697 | 30 | 1.11885e+09 | 949636 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1231.78 | 0.540054 | 134.503ms | 642697 | 30 | 2.16641e+08 | 497592 | 1(Win) |
| glaze | 954.752 | 0.971241 | 182.023ms | 642692 | 30 | 1.16627e+09 | 641967 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1439.64 | 0.91573 | 553.372ms | 1225964 | 32 | 1.76983e+09 | 812125 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1427.78 | 0.517609 | 195.414ms | 1225964 | 30 | 5.3896e+08 | 818872 | 1(Tie) |
| simdjson (ondemand) | 1194.33 | 0.201869 | 11659.4ms | 1225964 | 512 | 1.99948e+09 | 978935 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1842.36 | 0.359083 | 165.858ms | 1225964 | 30 | 1.55782e+08 | 634605 | 1(Win) |
| glaze | 1536.19 | 0.424735 | 197.461ms | 1225970 | 30 | 3.13491e+08 | 761086 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 752.566 | 1.73684 | 299.665ms | 409725 | 32 | 2.60236e+09 | 519216 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 624.415 | 1.16219 | 152.519ms | 409725 | 30 | 1.58677e+09 | 625776 | 2(Tie) |
| glaze STATISTICAL TIE | 621.976 | 0.746742 | 154.47ms | 409725 | 30 | 6.60237e+08 | 628231 | 2(Tie) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2130.06 | 1.27241 | 48.0854ms | 409725 | 30 | 1.63449e+08 | 183443 | 1(Win) |
| glaze | 1589.29 | 1.00233 | 59.9233ms | 409725 | 30 | 1.8219e+08 | 245861 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1096.91 | 1.62336 | 161.05ms | 785750 | 30 | 3.68957e+09 | 683143 | 1(Win) |
| glaze | 1021.74 | 0.879456 | 1868.64ms | 785750 | 128 | 5.32505e+09 | 733403 | 2(Loss) |
| simdjson (ondemand) | 950.993 | 1.86889 | 175.327ms | 785750 | 30 | 6.50586e+09 | 787965 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2335.54 | 0.788645 | 185.758ms | 785750 | 32 | 2.04884e+08 | 320846 | 1(Win) |
| glaze | 2101.33 | 0.390672 | 88.429ms | 785750 | 30 | 5.82271e+07 | 356607 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 916.648 | 0.603886 | 5242.87ms | 8587914 | 32 | 9.31602e+10 | 8.93481e+06 | 1(Win) |
| glaze | 803.378 | 0.526973 | 5825.97ms | 8587914 | 32 | 9.23555e+10 | 1.01945e+07 | 2(Loss) |
| simdjson (ondemand) | 779.535 | 1.03352 | 2803.97ms | 8587914 | 30 | 3.5372e+11 | 1.05064e+07 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 2955.28 | 0.678551 | 1802.95ms | 8588126 | 32 | 1.13166e+10 | 2.77141e+06 | 1(Win) |
| jsonifier | 2253.03 | 2.33035 | 839.167ms | 8588126 | 30 | 2.15293e+11 | 3.63523e+06 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 890.112 | 0.449877 | 2600.77ms | 9804437 | 30 | 6.69984e+10 | 1.05046e+07 | 1(Tie) |
| jsonifier STATISTICAL TIE | 887.496 | 1.89879 | 2541.11ms | 9804437 | 30 | 1.20057e+12 | 1.05355e+07 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 882.584 | 0.670437 | 2558.58ms | 9804437 | 30 | 1.51346e+11 | 1.05942e+07 | 1(Tie) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 2868.11 | 0.984432 | 969.842ms | 11078090 | 30 | 3.94487e+10 | 3.68358e+06 | 1(Tie) |
| glaze STATISTICAL TIE | 2826.13 | 0.258225 | 979.999ms | 11078090 | 30 | 2.79554e+09 | 3.73829e+06 | 1(Tie) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3238.58 | 0.768699 | 158.936ms | 264040 | 64 | 2.28625e+07 | 77752.6 | 1(Win) |
| simdjson (ondemand) | 2979.05 | 1.45538 | 20.426ms | 264040 | 30 | 4.54e+07 | 84526.4 | 2(Loss) |
| glaze | 1182.75 | 0.451756 | 51.3633ms | 264040 | 30 | 2.77514e+07 | 212901 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4082.42 | 0.72451 | 54.2585ms | 399947 | 32 | 1.46625e+07 | 93429.7 | 1(Win) |
| simdjson (ondemand) | 3770.57 | 1.1385 | 36.1914ms | 399947 | 30 | 3.97903e+07 | 101157 | 2(Loss) |
| glaze | 1658.99 | 0.588691 | 169.345ms | 399947 | 32 | 5.86193e+07 | 229910 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1529.98 | 0.533895 | 8134.56ms | 264040 | 2048 | 1.58128e+09 | 164583 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1239.94 | 0.616216 | 50.4985ms | 264040 | 30 | 4.69812e+07 | 203081 | 2(Tie) |
| glaze STATISTICAL TIE | 1229.35 | 0.813291 | 52.2241ms | 264040 | 30 | 8.32537e+07 | 204831 | 2(Tie) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3888.59 | 0.704778 | 16.5574ms | 264040 | 30 | 6.24857e+06 | 64755.6 | 1(Win) |
| glaze | 3012.02 | 1.0797 | 20.34ms | 263923 | 30 | 2.44211e+07 | 83564.1 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 1677.64 | 1.01203 | 60.0388ms | 399947 | 30 | 1.58822e+08 | 227354 | 1(Win) |
| jsonifier | 1616.49 | 0.952654 | 59.4528ms | 399947 | 30 | 1.51583e+08 | 235956 | 2(Loss) |
| glaze | 1564.16 | 0.713095 | 59.4793ms | 399947 | 30 | 9.07103e+07 | 243849 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3738.08 | 0.854844 | 26.6148ms | 399947 | 30 | 2.28245e+07 | 102036 | 1(Win) |
| glaze | 3037.94 | 1.38212 | 30.0763ms | 399830 | 30 | 9.02832e+07 | 125515 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1642.77 | 1.31507 | 65.4727ms | 466906 | 30 | 3.81176e+08 | 271053 | 1(Win) |
| jsonifier | 1335.38 | 0.923101 | 81.6706ms | 466906 | 30 | 2.84228e+08 | 333444 | 2(Loss) |
| simdjson (ondemand) | 754.558 | 0.353556 | 149.967ms | 466906 | 30 | 1.30591e+08 | 590115 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2260.46 | 0.457132 | 74.8778ms | 699405 | 30 | 5.45845e+07 | 295075 | 1(Win) |
| glaze | 2001.56 | 0.443444 | 89.902ms | 699405 | 30 | 6.55113e+07 | 333242 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2516.17 | 0.426505 | 59.7935ms | 631514 | 30 | 3.12648e+07 | 239356 | 1(Win) |
| glaze | 1672.19 | 0.570036 | 85.7529ms | 631514 | 30 | 1.26451e+08 | 360162 | 2(Loss) |
