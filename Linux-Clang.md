# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 20.1.8 compiler).  

Latest Results: (Sep 11, 2026)
#### Using the following commits:
----
| Jsonifier: [4d4a69d](https://github.com/nihilai-collective/jsonifier/commit/4d4a69d)  
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

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 613.216 | 0.0725527 | 4.73358ms | 1811 | 64 | 267.237 | 2816.47 | 3.75201 | 1(Win) |
| glaze | 477.484 | 0.102391 | 2.34182ms | 1811 | 32 | 438.926 | 3617.09 | 4.83341 | 2(Loss) |
| simdjson (ondemand) | 151.129 | 0.392576 | 2.97436ms | 1811 | 30 | 60382.3 | 11428 | 15.38 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 270.7 | 0.214744 | 3.85186ms | 1798 | 32 | 5921.01 | 6334.34 | 8.5658 | 1(Win) |
| jsonifier | 268.433 | 0.183929 | 1.86449ms | 1811 | 30 | 4201.34 | 6434.03 | 8.62435 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1341.27 | 0.116802 | 0.896625ms | 3873 | 30 | 310.372 | 2753.8 | 1.71449 | 1(Win) |
| glaze | 987.835 | 0.535679 | 1.07502ms | 3873 | 30 | 12035.3 | 3739.07 | 2.33486 | 2(Loss) |
| simdjson (ondemand) | 355.576 | 0.0622432 | 2.74338ms | 3873 | 30 | 1254.11 | 10387.6 | 6.53458 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1427.62 | 0.125658 | 0.846521ms | 3873 | 30 | 317.082 | 2587.23 | 1.60998 | 1(Win) |
| glaze | 915.945 | 0.119543 | 1.2061ms | 3873 | 30 | 697.154 | 4032.53 | 2.52232 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1372.35 | 0.0832966 | 1.86346ms | 3862 | 32 | 159.918 | 2683.78 | 1.67579 | 1(Win) |
| glaze | 823.276 | 0.0802598 | 1.29703ms | 3862 | 30 | 386.769 | 4473.7 | 2.80865 | 2(Loss) |
| simdjson (ondemand) | 356.341 | 1.5141 | 27.5943ms | 3862 | 128 | 3.13482e+06 | 10335.9 | 6.52155 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1562.55 | 0.0903378 | 0.820793ms | 3862 | 30 | 136.024 | 2357.1 | 1.47028 | 1(Win) |
| glaze | 1003.34 | 0.376074 | 1.12593ms | 3862 | 30 | 5717.39 | 3670.83 | 2.30155 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 602.076 | 0.149907 | 0.608359ms | 905 | 30 | 138.534 | 1433.5 | 3.76899 | 1(Win) |
| glaze | 433.757 | 0.146468 | 0.682407ms | 905 | 30 | 254.806 | 1989.77 | 5.27808 | 2(Loss) |
| simdjson (ondemand) | 121.648 | 0.0692413 | 4.28335ms | 905 | 32 | 772.265 | 7094.84 | 19.0689 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 735.687 | 0.109741 | 0.997597ms | 905 | 32 | 53.0393 | 1173.16 | 3.07427 | 1(Win) |
| glaze | 266.656 | 0.144948 | 0.980785ms | 905 | 30 | 660.299 | 3236.67 | 8.64597 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1880.06 | 0.0764784 | 3.13488ms | 9578 | 32 | 441.806 | 4858.5 | 1.231 | 1(Win) |
| glaze | 1477.09 | 0.113362 | 1.67038ms | 9578 | 30 | 1474.31 | 6183.97 | 1.56921 | 2(Loss) |
| simdjson (ondemand) | 773.734 | 0.069841 | 3.08129ms | 9578 | 30 | 2039.43 | 11805.5 | 3.00523 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3176.7 | 0.111154 | 1.03504ms | 9578 | 30 | 306.455 | 2875.4 | 0.724247 | 1(Win) |
| glaze | 2207.07 | 0.161714 | 2.62195ms | 9578 | 32 | 1433.39 | 4138.66 | 1.04774 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2821.85 | 0.622944 | 19.3776ms | 233995 | 30 | 7.28056e+06 | 79081.1 | 0.825821 | 1(Win) |
| simdjson (ondemand) | 2678.71 | 0.772435 | 20.189ms | 233995 | 30 | 1.24225e+07 | 83307 | 0.870107 | 2(Loss) |
| glaze | 1433.45 | 1.53003 | 37.0689ms | 233995 | 30 | 1.70204e+08 | 155677 | 1.62647 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3503.23 | 0.717051 | 23.0155ms | 346753 | 30 | 1.37444e+07 | 94395.7 | 0.665224 | 1(Win) |
| simdjson (ondemand) | 3366.46 | 0.625531 | 23.7816ms | 346753 | 30 | 1.13269e+07 | 98230.7 | 0.6924 | 2(Loss) |
| glaze | 1798.31 | 0.372363 | 44.4368ms | 346753 | 30 | 1.40659e+07 | 183889 | 1.29655 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1248.62 | 0.456259 | 43.723ms | 233995 | 30 | 1.99479e+07 | 178722 | 1.86718 | 1(Win) |
| glaze | 936.116 | 0.474232 | 57.3288ms | 233995 | 30 | 3.83404e+07 | 238384 | 2.49075 | 2(Loss) |
| simdjson (ondemand) | 841.393 | 0.353366 | 63.9774ms | 233995 | 30 | 2.63504e+07 | 265221 | 2.7711 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2274.62 | 0.647958 | 23.9427ms | 233995 | 30 | 1.2123e+07 | 98106.4 | 1.02468 | 1(Win) |
| glaze | 1864.58 | 0.619155 | 29.14ms | 233995 | 30 | 1.6473e+07 | 119681 | 1.25002 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1267.82 | 0.343299 | 63.3108ms | 346753 | 30 | 2.40542e+07 | 260833 | 1.83909 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1138.45 | 2.15524 | 67.3708ms | 346753 | 30 | 1.17578e+09 | 290474 | 2.04795 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1113.57 | 0.359124 | 71.7877ms | 346753 | 30 | 3.41208e+07 | 296965 | 2.09387 | 2(Tie) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2110.76 | 0.472481 | 38.276ms | 346753 | 30 | 1.64382e+07 | 156668 | 1.10436 | 1(Win) |
| glaze | 1683.97 | 0.429444 | 47.849ms | 346753 | 30 | 2.13357e+07 | 196375 | 1.38447 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2767.36 | 0.538177 | 19.7757ms | 233995 | 30 | 5.65007e+06 | 80638.3 | 0.842239 | 1(Win) |
| simdjson (ondemand) | 1804.57 | 0.521329 | 29.6948ms | 233995 | 30 | 1.24684e+07 | 123661 | 1.29193 | 2(Loss) |
| glaze | 1467.16 | 0.405647 | 36.9238ms | 233995 | 30 | 1.14203e+07 | 152100 | 1.58916 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3397.29 | 0.757744 | 24.4544ms | 346753 | 30 | 1.63208e+07 | 97339.2 | 0.685997 | 1(Win) |
| simdjson (ondemand) | 2391.3 | 0.496192 | 33.3081ms | 346753 | 30 | 1.41251e+07 | 138288 | 0.974803 | 2(Loss) |
| glaze | 1778.1 | 0.794754 | 45.1487ms | 346753 | 30 | 6.55414e+07 | 185979 | 1.31128 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1143.45 | 0.520524 | 47.3178ms | 233995 | 30 | 3.09587e+07 | 195160 | 2.03901 | 1(Win) |
| glaze | 968.295 | 0.349155 | 56.1502ms | 233995 | 30 | 1.94247e+07 | 230462 | 2.4079 | 2(Loss) |
| simdjson (ondemand) | 216.231 | 0.0892631 | 248.627ms | 233995 | 30 | 2.5459e+07 | 1.03202e+06 | 10.7844 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2332.79 | 0.681207 | 23.5203ms | 233995 | 30 | 1.27392e+07 | 95660.2 | 0.999101 | 1(Win) |
| glaze | 1902.31 | 0.820963 | 65.9994ms | 233995 | 32 | 2.96789e+07 | 117307 | 1.22527 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1274.63 | 0.314662 | 148.743ms | 346753 | 32 | 2.13259e+07 | 259439 | 1.8292 | 1(Win) |
| jsonifier | 1067.3 | 0.666123 | 74.3181ms | 346753 | 30 | 1.27791e+08 | 309839 | 2.18458 | 2(Loss) |
| simdjson (ondemand) | 311.779 | 0.116627 | 255.153ms | 346753 | 30 | 4.59056e+07 | 1.06065e+06 | 7.47941 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2074.98 | 0.502787 | 38.7691ms | 346753 | 30 | 1.9262e+07 | 159370 | 1.12339 | 1(Win) |
| glaze | 1647.94 | 0.5653 | 48.4281ms | 346753 | 30 | 3.86045e+07 | 200669 | 1.41461 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 644.676 | 0.472001 | 33.9803ms | 94651 | 30 | 1.31031e+07 | 140018 | 3.61638 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 636.387 | 0.524198 | 34.2867ms | 94651 | 30 | 1.65852e+07 | 141842 | 3.66339 | 1(Tie) |
| glaze STATISTICAL TIE | 627.218 | 0.545175 | 34.6753ms | 94651 | 30 | 1.84674e+07 | 143915 | 3.7172 | 1(Tie) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2779.4 | 1.42794 | 8.38101ms | 94651 | 30 | 6.45193e+06 | 32476.9 | 0.838108 | 1(Win) |
| glaze | 2514.79 | 1.5365 | 8.76842ms | 94651 | 30 | 9.12498e+06 | 35894.1 | 0.92583 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 862.686 | 1.08127 | 36.7276ms | 136024 | 30 | 7.93082e+07 | 150371 | 2.70229 | 1(Win) |
| glaze | 834.505 | 0.488132 | 37.9969ms | 136024 | 30 | 1.7273e+07 | 155449 | 2.79364 | 2(Loss) |
| jsonifier | 751.924 | 0.470486 | 42.0226ms | 136024 | 30 | 1.9765e+07 | 172521 | 3.10072 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3317.51 | 1.49938 | 9.74258ms | 136024 | 30 | 1.03122e+07 | 39102.4 | 0.702167 | 1(Win) |
| glaze | 1793.59 | 0.759624 | 17.5529ms | 136046 | 30 | 9.05829e+06 | 72337.5 | 1.29914 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 447.067 | 0.352886 | 1060.48ms | 2090234 | 30 | 7.42736e+09 | 4.45884e+06 | 5.21641 | 1(Win) |
| glaze | 385.344 | 0.151405 | 1243.39ms | 2090234 | 30 | 1.84032e+09 | 5.17305e+06 | 6.05201 | 2(Loss) |
| simdjson (ondemand) | 301.975 | 0.115594 | 1587.12ms | 2090234 | 30 | 1.74679e+09 | 6.60122e+06 | 7.72286 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 664.265 | 0.108503 | 720.532ms | 2090234 | 30 | 3.18065e+08 | 3.00092e+06 | 3.51076 | 1(Win) |
| glaze | 648.401 | 0.0622751 | 738.819ms | 2090234 | 30 | 1.09964e+08 | 3.07433e+06 | 3.59666 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1112.51 | 0.255851 | 1372.47ms | 6661897 | 30 | 6.40447e+09 | 5.71075e+06 | 2.09625 | 1(Win) |
| glaze | 1000.5 | 0.073181 | 1525.22ms | 6661897 | 30 | 6.47855e+08 | 6.35009e+06 | 2.33093 | 2(Loss) |
| simdjson (ondemand) | 913.939 | 0.117262 | 1673.23ms | 6661897 | 30 | 1.99342e+09 | 6.95154e+06 | 2.55171 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1947.57 | 0.200327 | 795.05ms | 6661897 | 30 | 1.28117e+09 | 3.26215e+06 | 1.19743 | 1(Win) |
| glaze | 1494.02 | 0.152126 | 1030.45ms | 6661897 | 30 | 1.25548e+09 | 4.25247e+06 | 1.56092 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 999.28 | 0.963174 | 113.407ms | 500299 | 30 | 6.34477e+08 | 477466 | 2.33344 | 1(Win) |
| glaze | 826.566 | 0.260263 | 138.44ms | 500299 | 30 | 6.77096e+07 | 577234 | 2.82118 | 2(Loss) |
| simdjson (ondemand) | 492.741 | 0.379417 | 230.731ms | 500299 | 30 | 4.04927e+08 | 968303 | 4.7326 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2016.32 | 0.579015 | 57.4496ms | 500299 | 30 | 5.63171e+07 | 236630 | 1.1563 | 1(Win) |
| jsonifier | 1831.52 | 0.533676 | 62.827ms | 500299 | 30 | 5.79846e+07 | 260506 | 1.27301 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1511.92 | 0.195518 | 217.64ms | 1439562 | 30 | 9.45581e+07 | 908033 | 1.54237 | 1(Tie) |
| glaze STATISTICAL TIE | 1503.89 | 0.779568 | 217.018ms | 1439562 | 30 | 1.51934e+09 | 912880 | 1.5506 | 1(Tie) |
| simdjson (ondemand) | 1306.55 | 0.151331 | 252.507ms | 1439562 | 30 | 7.58546e+07 | 1.05076e+06 | 1.78484 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3359.77 | 0.289992 | 98.6797ms | 1439562 | 30 | 4.21245e+07 | 408621 | 0.694015 | 1(Win) |
| glaze | 2071.38 | 0.389895 | 159.088ms | 1439584 | 30 | 2.00342e+08 | 662793 | 1.12577 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 915.069 | 2.15532 | 14.4816ms | 56369 | 30 | 4.80972e+07 | 58747.1 | 2.54643 | 1(Win) |
| glaze | 801.263 | 0.718688 | 16.5844ms | 56369 | 30 | 6.97482e+06 | 67091.2 | 2.90887 | 2(Loss) |
| simdjson (ondemand) | 674.632 | 0.592617 | 19.8137ms | 56369 | 30 | 6.68987e+06 | 79684.5 | 3.45524 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1930.42 | 1.35837 | 6.85931ms | 56369 | 30 | 4.29274e+06 | 27847.7 | 1.20645 | 1(Win) |
| jsonifier | 1684.94 | 1.00202 | 7.92734ms | 56369 | 30 | 3.06609e+06 | 31904.8 | 1.38254 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1107.31 | 0.773199 | 19.854ms | 94370 | 30 | 1.18478e+07 | 81276.8 | 2.10502 | 1(Win) |
| simdjson (ondemand) | 1019.81 | 0.659114 | 21.4178ms | 94370 | 30 | 1.01501e+07 | 88249.8 | 2.28573 | 2(Loss) |
| jsonifier | 862.005 | 0.868472 | 25.4336ms | 94370 | 30 | 2.4665e+07 | 104406 | 2.70371 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2434.29 | 1.21508 | 9.13807ms | 94370 | 30 | 6.05419e+06 | 36971 | 0.957041 | 1(Win) |
| glaze | 1731.35 | 0.938721 | 12.7045ms | 94370 | 30 | 7.14318e+06 | 51981.5 | 1.34545 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 836.613 | 1.11565 | 14.8034ms | 52708 | 30 | 1.34796e+07 | 60083 | 2.78469 | 1(Win) |
| jsonifier STATISTICAL TIE | 739.809 | 1.30717 | 17.0614ms | 52708 | 30 | 2.36647e+07 | 67944.9 | 3.14767 | 2(Tie) |
| glaze STATISTICAL TIE | 723.567 | 0.836931 | 17.2443ms | 52708 | 30 | 1.01413e+07 | 69470.1 | 3.22039 | 2(Tie) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2698.22 | 1.57915 | 4.75451ms | 52708 | 30 | 2.59636e+06 | 18629.4 | 0.862127 | 1(Win) |
| jsonifier | 2461.04 | 1.72745 | 11.8169ms | 52708 | 32 | 3.9836e+06 | 20424.8 | 0.945975 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1084.11 | 0.988654 | 15.2741ms | 70103 | 30 | 1.11515e+07 | 61668.2 | 2.14804 | 1(Win) |
| glaze | 842.644 | 1.24654 | 19.4977ms | 70103 | 30 | 2.93441e+07 | 79340.1 | 2.76577 | 2(Loss) |
| jsonifier | 583.973 | 1.12898 | 28.2842ms | 70103 | 30 | 5.01163e+07 | 114484 | 3.98971 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2943.36 | 2.22631 | 5.62834ms | 70103 | 30 | 7.67146e+06 | 22714 | 0.79099 | 1(Win) |
| glaze | 2436.78 | 1.19455 | 6.79131ms | 70103 | 30 | 3.22233e+06 | 27435.9 | 0.955378 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 702.308 | 1.98844 | 9.28306ms | 11812 | 32 | 3.25513e+06 | 16039.7 | 3.31302 | 1(Win) |
| glaze | 566.452 | 1.97135 | 4.98264ms | 11812 | 30 | 4.61071e+06 | 19886.6 | 4.10946 | 2(Loss) |
| simdjson (ondemand) | 542.213 | 0.143108 | 5.20948ms | 11812 | 30 | 26518.9 | 20775.6 | 4.29351 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2412.47 | 0.178536 | 1.27223ms | 11812 | 30 | 2084.94 | 4669.4 | 0.959163 | 1(Win) |
| glaze | 943.788 | 0.10496 | 14.7956ms | 11812 | 64 | 10044.4 | 11935.7 | 2.46229 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1325.46 | 0.0468926 | 5.6931ms | 31235 | 30 | 3331.8 | 22473.7 | 1.75672 | 1(Win) |
| jsonifier | 1217.8 | 0.03561 | 6.25652ms | 31235 | 30 | 2276.12 | 24460.5 | 1.91234 | 2(Loss) |
| glaze | 1127.82 | 1.06662 | 6.66207ms | 31235 | 30 | 2.38092e+06 | 26411.9 | 2.0649 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2469.47 | 0.341364 | 7.03013ms | 31235 | 32 | 54257.8 | 12062.5 | 0.941674 | 1(Win) |
| glaze | 1837.53 | 2.26707 | 9.22324ms | 31235 | 32 | 4.32209e+06 | 16210.9 | 1.26603 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1790.48 | 2.1948 | 13.9474ms | 108313 | 30 | 4.80987e+07 | 57691.4 | 1.30108 | 1(Win) |
| glaze | 991.436 | 0.622525 | 25.2252ms | 108313 | 30 | 1.26202e+07 | 104188 | 2.35088 | 2(Loss) |
| simdjson (ondemand) | 781.886 | 0.606498 | 31.9546ms | 108313 | 30 | 1.92599e+07 | 132110 | 2.98131 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1896.9 | 0.771585 | 13.3536ms | 108313 | 30 | 5.29615e+06 | 54454.7 | 1.22865 | 1(Win) |
| glaze | 1701.51 | 1.12337 | 14.7ms | 108313 | 30 | 1.39526e+07 | 60708 | 1.3696 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1472.18 | 0.506367 | 33.5489ms | 213963 | 30 | 1.47778e+07 | 138605 | 1.58348 | 1(Win) |
| simdjson (ondemand) | 1423.35 | 0.651028 | 34.5963ms | 213963 | 30 | 2.61323e+07 | 143360 | 1.63771 | 2(Loss) |
| jsonifier | 1171.64 | 1.76301 | 41.5729ms | 213963 | 30 | 2.82829e+08 | 174159 | 1.98923 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2981.58 | 0.928401 | 16.6104ms | 213963 | 30 | 1.21109e+07 | 68437.2 | 0.781681 | 1(Win) |
| glaze | 1684.78 | 0.475121 | 68.8222ms | 213963 | 32 | 1.05962e+07 | 121115 | 1.38352 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 478.598 | 0.133092 | 878.621ms | 1834197 | 30 | 7.09867e+08 | 3.6549e+06 | 4.87275 | 1(Win) |
| glaze | 348.155 | 0.520467 | 1202.61ms | 1834197 | 30 | 2.05142e+10 | 5.02427e+06 | 6.69844 | 2(Loss) |
| simdjson (ondemand) | 262.408 | 0.0797874 | 1599.25ms | 1834197 | 30 | 8.4865e+08 | 6.66607e+06 | 8.88737 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 391.235 | 0.0474821 | 1076.73ms | 1833577 | 30 | 1.35115e+08 | 4.46952e+06 | 5.96084 | 1(Win) |
| jsonifier | 387.969 | 0.0724085 | 1080.32ms | 1834197 | 30 | 3.19741e+08 | 4.50868e+06 | 6.01102 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1385.63 | 0.117465 | 1639.09ms | 9930848 | 30 | 1.93382e+09 | 6.83499e+06 | 1.68304 | 1(Win) |
| glaze | 1376.52 | 0.0643552 | 1654.09ms | 9930848 | 30 | 5.88163e+08 | 6.88025e+06 | 1.6942 | 2(Loss) |
| simdjson (ondemand) | 1287.78 | 0.0623488 | 1758.53ms | 9930848 | 30 | 6.30763e+08 | 7.35435e+06 | 1.81095 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1683.92 | 0.180762 | 1365.1ms | 9930848 | 30 | 3.10074e+09 | 5.62426e+06 | 1.38493 | 1(Win) |
| glaze | 1311.55 | 0.170418 | 1726.69ms | 9930228 | 30 | 4.54254e+09 | 7.22061e+06 | 1.77807 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 833.412 | 0.267056 | 176.364ms | 642697 | 30 | 1.15723e+08 | 735439 | 2.79805 | 1(Win) |
| glaze | 757.864 | 0.120874 | 195.684ms | 642697 | 30 | 2.86694e+07 | 808752 | 3.07703 | 2(Loss) |
| simdjson (ondemand) | 562.766 | 0.218819 | 261.25ms | 642697 | 30 | 1.70391e+08 | 1.08913e+06 | 4.14378 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 709.045 | 0.189828 | 207.72ms | 642697 | 30 | 8.07802e+07 | 864435 | 3.28882 | 1(Win) |
| glaze | 638.706 | 0.138543 | 230.656ms | 642692 | 30 | 5.30267e+07 | 959626 | 3.65108 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1138.43 | 0.0818021 | 247.087ms | 1225964 | 30 | 2.11733e+07 | 1.027e+06 | 2.04843 | 1(Win) |
| jsonifier | 1038.95 | 0.163347 | 269.951ms | 1225964 | 30 | 1.01369e+08 | 1.12534e+06 | 2.24456 | 2(Loss) |
| simdjson (ondemand) | 1028.04 | 0.179735 | 273.192ms | 1225964 | 30 | 1.25348e+08 | 1.13728e+06 | 2.2684 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1246.28 | 0.11459 | 225.712ms | 1225964 | 30 | 3.46688e+07 | 938125 | 1.87111 | 1(Win) |
| glaze | 1007.4 | 0.674838 | 277.272ms | 1225970 | 30 | 1.84025e+09 | 1.16059e+06 | 2.31486 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 593.144 | 0.174068 | 159.4ms | 409725 | 30 | 3.94481e+07 | 658768 | 3.93147 | 1(Win) |
| simdjson (ondemand) | 488.02 | 0.162305 | 192.343ms | 409725 | 30 | 5.06637e+07 | 800673 | 4.77843 | 2(Loss) |
| glaze | 413.522 | 0.0837759 | 228.848ms | 409725 | 30 | 1.87995e+07 | 944917 | 5.63934 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1384.47 | 0.531684 | 68.4145ms | 409725 | 30 | 6.75532e+07 | 282234 | 1.6841 | 1(Win) |
| jsonifier | 1192.51 | 0.348299 | 79.3415ms | 409725 | 30 | 3.9074e+07 | 327665 | 1.95531 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 875.163 | 0.342719 | 204.372ms | 785750 | 30 | 2.58338e+08 | 856240 | 2.6646 | 1(Win) |
| glaze | 676.283 | 0.155318 | 266.715ms | 785750 | 30 | 8.88537e+07 | 1.10804e+06 | 3.44827 | 2(Loss) |
| jsonifier | 662.403 | 0.275021 | 271.204ms | 785750 | 30 | 2.90388e+08 | 1.13126e+06 | 3.52053 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1887.74 | 0.407078 | 95.3735ms | 785750 | 30 | 7.83361e+07 | 396957 | 1.23517 | 1(Win) |
| glaze | 1611.56 | 0.33149 | 112.236ms | 785750 | 30 | 7.12754e+07 | 464984 | 1.44691 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 713.928 | 0.241433 | 2746.81ms | 8587914 | 30 | 2.30134e+10 | 1.14718e+07 | 3.26652 | 1(Win) |
| simdjson (ondemand) | 637.76 | 0.208201 | 3082.91ms | 8587914 | 30 | 2.14461e+10 | 1.28419e+07 | 3.65669 | 2(Loss) |
| glaze | 631.567 | 0.0966797 | 3118.73ms | 8587914 | 30 | 4.7155e+09 | 1.29679e+07 | 3.69255 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2171.26 | 0.263569 | 917.107ms | 8588126 | 30 | 2.96542e+09 | 3.77214e+06 | 1.07402 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2164.24 | 0.345883 | 905.97ms | 8588126 | 30 | 5.14004e+09 | 3.78437e+06 | 1.07753 | 1(Tie) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 709.69 | 0.222058 | 3164.95ms | 9804437 | 30 | 2.5678e+10 | 1.31751e+07 | 3.28604 | 1(Win) |
| glaze | 657.364 | 0.191055 | 3411.55ms | 9804437 | 30 | 2.21549e+10 | 1.42238e+07 | 3.54762 | 2(Loss) |
| jsonifier | 620.595 | 0.317842 | 3615.07ms | 9804437 | 30 | 6.87975e+10 | 1.50666e+07 | 3.75783 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2334.12 | 0.43372 | 1065.1ms | 11078090 | 30 | 1.15618e+10 | 4.52628e+06 | 0.999079 | 1(Win) |
| glaze | 2066.96 | 0.41697 | 1222.25ms | 11078090 | 30 | 1.36269e+10 | 5.11132e+06 | 1.12822 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2857.13 | 0.618914 | 21.5336ms | 264040 | 30 | 8.92609e+06 | 88133.2 | 0.815618 | 1(Win) |
| simdjson (ondemand) | 2667.46 | 0.665709 | 22.9355ms | 264040 | 30 | 1.18477e+07 | 94400.1 | 0.873754 | 2(Loss) |
| glaze | 1123.98 | 0.387775 | 54.1802ms | 264040 | 30 | 2.26412e+07 | 224032 | 2.07443 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3687.01 | 0.617129 | 25.2461ms | 399947 | 30 | 1.22273e+07 | 103449 | 0.632127 | 1(Win) |
| simdjson (ondemand) | 3466.25 | 1.61979 | 26.494ms | 399947 | 30 | 9.53073e+07 | 110038 | 0.672394 | 2(Loss) |
| glaze | 1521.35 | 0.410888 | 60.4691ms | 399947 | 30 | 3.18357e+07 | 250711 | 1.53258 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 953.221 | 0.984938 | 63.7899ms | 264040 | 30 | 2.03092e+08 | 264166 | 2.44582 | 1(Win) |
| simdjson (ondemand) | 849.841 | 0.415031 | 73.235ms | 264040 | 30 | 4.53676e+07 | 296300 | 2.74354 | 2(Loss) |
| glaze | 829.818 | 0.39378 | 73.7861ms | 264040 | 30 | 4.28354e+07 | 303450 | 2.80979 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2441.99 | 0.636153 | 25.3735ms | 264040 | 30 | 1.29091e+07 | 103116 | 0.954279 | 1(Win) |
| glaze | 2249.93 | 0.758394 | 26.8993ms | 263923 | 30 | 2.15937e+07 | 111869 | 1.03595 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1206.31 | 0.314733 | 77.3282ms | 399947 | 30 | 2.97092e+07 | 316186 | 1.93287 | 1(Win) |
| glaze | 1011.13 | 0.748895 | 90.5387ms | 399947 | 30 | 2.39416e+08 | 377220 | 2.306 | 2(Loss) |
| jsonifier | 792.333 | 0.366762 | 116.139ms | 399947 | 30 | 9.35149e+07 | 481388 | 2.94291 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3067.5 | 0.622151 | 30.2512ms | 399947 | 30 | 1.79535e+07 | 124342 | 0.759903 | 1(Win) |
| glaze | 2255.35 | 0.542587 | 41.0923ms | 399830 | 30 | 2.52455e+07 | 169068 | 1.03366 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1406.53 | 0.278133 | 76.3119ms | 466906 | 30 | 2.32587e+07 | 316578 | 1.65774 | 1(Win) |
| jsonifier | 1241.4 | 0.285085 | 86.7322ms | 466906 | 30 | 3.13696e+07 | 358690 | 1.87829 | 2(Loss) |
| simdjson (ondemand) | 641.576 | 0.146337 | 167.716ms | 466906 | 30 | 3.0945e+07 | 694035 | 3.63463 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2028.26 | 0.572502 | 79.1788ms | 699405 | 30 | 1.06338e+08 | 328856 | 1.14956 | 1(Win) |
| glaze | 1897.51 | 0.292896 | 84.3227ms | 699405 | 30 | 3.18008e+07 | 351516 | 1.22884 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2304.93 | 0.32067 | 63.3243ms | 631514 | 30 | 2.10614e+07 | 261291 | 1.01158 | 1(Win) |
| glaze | 1513.75 | 0.350397 | 95.7383ms | 631514 | 30 | 5.83041e+07 | 397858 | 1.54042 | 2(Loss) |
