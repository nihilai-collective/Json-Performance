# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest Results: (Sep 15, 2026)
#### Using the following commits:
----
| Jsonifier: [57ce61b](https://github.com/nihilai-collective/jsonifier/commit/57ce61b)  
| Glaze: [29f478d](https://github.com/stephenberry/glaze/commit/29f478d)  
| Simdjson: [f9c973a](https://github.com/simdjson/simdjson/commit/f9c973a)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `NEON` |
| simdjson (ondemand) | `arm64` |
| Glaze (utf8-validation) | `NEON64` |
| Glaze (string-escape) | `NEON` |
| Glaze (float-write) | `NEON` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Apple M1 (Virtual)-NEON): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.500000% AND mean shift < 1.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [43ba991](https://github.com/realtimechris/benchmarksuite/commit/43ba991).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 877.594 | 1.79433 | 29.7039ms | 1811 | 32 | 39903 | 1968 | 1(Win) |
| glaze | 749.611 | 1.8029 | 6.1568ms | 1811 | 128 | 220861 | 2304 | 2(Loss) |
| simdjson (ondemand) | 189.686 | 0.627733 | 2.42509ms | 1811 | 30 | 98002.7 | 9105.07 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 595.279 | 1.95401 | 0.827136ms | 1811 | 30 | 96420.8 | 2901.33 | 1(Win) |
| glaze | 422.147 | 1.27252 | 1.12896ms | 1798 | 30 | 80149.8 | 4061.87 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1643.05 | 1.72703 | 6.00986ms | 3873 | 128 | 192931 | 2248 | 1(Win) |
| glaze | 1482.18 | 1.83197 | 6.49907ms | 3873 | 128 | 266772 | 2492 | 2(Loss) |
| simdjson (ondemand) | 389.947 | 1.02035 | 2.37005ms | 3873 | 30 | 280223 | 9472 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2065.76 | 2.11275 | 5.09798ms | 3873 | 128 | 182659 | 1788 | 1(Win) |
| glaze | 1261.93 | 1.66074 | 0.784896ms | 3873 | 30 | 70884.3 | 2926.93 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1635.48 | 2.457 | 2.96909ms | 3862 | 64 | 195942 | 2252 | 1(Win) |
| glaze | 1412.23 | 2.42337 | 3.2809ms | 3862 | 64 | 255642 | 2608 | 2(Loss) |
| simdjson (ondemand) | 359.977 | 0.781928 | 2.57306ms | 3862 | 30 | 192013 | 10231.5 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1930.34 | 1.98059 | 2.54387ms | 3862 | 64 | 91396.1 | 1908 | 1(Win) |
| glaze | 1215.81 | 1.15198 | 0.827904ms | 3862 | 30 | 36534.4 | 3029.33 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1317.17 | 2.29616 | 14.4282ms | 905 | 1024 | 231802 | 655.25 | 1(Win) |
| glaze | 752.463 | 1.96481 | 6.21901ms | 905 | 256 | 130019 | 1147 | 2(Loss) |
| simdjson (ondemand) | 203.915 | 1.96115 | 1.17709ms | 905 | 30 | 206702 | 4232.53 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 816.533 | 1.43993 | 6.70592ms | 905 | 256 | 59302.7 | 1057 | 1(Win) |
| glaze | 368.206 | 1.81484 | 6.11507ms | 905 | 128 | 231634 | 2344 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 2031.17 | 2.07296 | 1.32403ms | 9578 | 30 | 260713 | 4497.07 | 1(Tie) |
| glaze STATISTICAL TIE | 1928.69 | 1.88233 | 1.25696ms | 9578 | 30 | 238415 | 4736 | 1(Tie) |
| simdjson (ondemand) | 678.343 | 0.738281 | 3.36896ms | 9578 | 30 | 296494 | 13465.6 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3653.72 | 1.81548 | 6.06208ms | 9578 | 128 | 263676 | 2500 | 1(Win) |
| glaze | 2718.54 | 1.83939 | 4.25907ms | 9578 | 64 | 244460 | 3360 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3600.58 | 1.52935 | 14.935ms | 233995 | 30 | 2.69527e+07 | 61977.6 | 1(Win) |
| simdjson (ondemand) | 2801.09 | 0.39653 | 19.1969ms | 233995 | 30 | 2.99387e+06 | 79667.2 | 2(Loss) |
| glaze | 1182.61 | 0.214395 | 45.751ms | 233995 | 30 | 4.91e+06 | 188698 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4721.9 | 0.0545387 | 17.1082ms | 346753 | 30 | 43766 | 70033.1 | 1(Win) |
| simdjson (ondemand) | 3633.97 | 0.0260618 | 22.2272ms | 346753 | 30 | 16873.6 | 90999.5 | 2(Loss) |
| glaze | 1644.15 | 0.200212 | 47.8569ms | 346753 | 30 | 4.86473e+06 | 201131 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1373.55 | 0.305531 | 39.7819ms | 233995 | 30 | 7.39193e+06 | 162466 | 1(Win) |
| jsonifier | 1286.96 | 0.456964 | 40.247ms | 233995 | 30 | 1.88352e+07 | 173397 | 2(Loss) |
| simdjson (ondemand) | 905.442 | 0.758352 | 59.0049ms | 233995 | 30 | 1.04799e+08 | 246460 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2344.12 | 0.334915 | 22.9601ms | 233995 | 30 | 3.04961e+06 | 95197.9 | 1(Win) |
| glaze | 2254.2 | 0.999254 | 22.014ms | 233995 | 30 | 2.93563e+07 | 98995.2 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1519 | 0.836921 | 50.882ms | 346753 | 30 | 9.95903e+07 | 217702 | 1(Win) |
| jsonifier | 1482.67 | 0.465594 | 52.9142ms | 346753 | 30 | 3.23508e+07 | 223036 | 2(Loss) |
| simdjson (ondemand) | 1243.87 | 1.45349 | 62.2239ms | 346753 | 30 | 4.47958e+08 | 265856 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2997.11 | 0.583477 | 26.4451ms | 346753 | 30 | 1.24338e+07 | 110336 | 1(Win) |
| glaze | 2422.8 | 0.201903 | 32.9958ms | 346753 | 30 | 2.27832e+06 | 136491 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3897.31 | 0.368392 | 14.0759ms | 233995 | 30 | 1.33483e+06 | 57258.7 | 1(Win) |
| simdjson (ondemand) | 1884.08 | 0.560978 | 28.2821ms | 233995 | 30 | 1.32443e+07 | 118443 | 2(Loss) |
| glaze | 1202.95 | 0.142754 | 45.1062ms | 233995 | 30 | 2.10386e+06 | 185506 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4121.75 | 1.57136 | 20.3379ms | 346753 | 30 | 4.76813e+07 | 80230.4 | 1(Win) |
| simdjson (ondemand) | 2551.53 | 0.45181 | 31.2003ms | 346753 | 30 | 1.02866e+07 | 129604 | 2(Loss) |
| glaze | 1679.49 | 0.390534 | 48.0248ms | 346753 | 30 | 1.77387e+07 | 196898 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1396.73 | 0.233698 | 38.6081ms | 233995 | 30 | 4.18233e+06 | 159770 | 1(Win) |
| jsonifier | 1140.72 | 0.387746 | 46.0091ms | 233995 | 30 | 1.72612e+07 | 195627 | 2(Loss) |
| simdjson (ondemand) | 221.487 | 0.628578 | 242.519ms | 233995 | 30 | 1.20325e+09 | 1.00753e+06 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 2588.95 | 0.405567 | 20.8259ms | 233995 | 30 | 3.66617e+06 | 86195.2 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2573.92 | 0.461655 | 21.0109ms | 233995 | 30 | 4.80597e+06 | 86698.7 | 1(Tie) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1747.19 | 0.306541 | 45.8291ms | 346753 | 30 | 1.00986e+07 | 189269 | 1(Win) |
| jsonifier | 1498.56 | 0.166309 | 54.2871ms | 346753 | 30 | 4.04063e+06 | 220672 | 2(Loss) |
| simdjson (ondemand) | 329.426 | 0.144473 | 244.536ms | 346753 | 30 | 6.30984e+07 | 1.00384e+06 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2659.39 | 1.07679 | 29.7239ms | 346753 | 30 | 5.37844e+07 | 124348 | 1(Win) |
| glaze | 2344.1 | 0.446618 | 35.37ms | 346753 | 30 | 1.19092e+07 | 141073 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 861.337 | 0.316987 | 25.374ms | 94651 | 30 | 3.31062e+06 | 104798 | 1(Win) |
| jsonifier | 717.158 | 0.296803 | 31.7309ms | 94651 | 30 | 4.18677e+06 | 125867 | 2(Loss) |
| simdjson (ondemand) | 705.393 | 0.238976 | 30.889ms | 94651 | 30 | 2.80554e+06 | 127966 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5234.08 | 1.38463 | 4.52198ms | 94651 | 30 | 1.71064e+06 | 17245.9 | 1(Win) |
| glaze | 4819.17 | 0.420025 | 4.70298ms | 94651 | 30 | 185685 | 18730.7 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1082.6 | 0.276182 | 28.9748ms | 136024 | 30 | 3.28554e+06 | 119825 | 1(Win) |
| simdjson (ondemand) | 970.497 | 0.253107 | 32.277ms | 136024 | 30 | 3.43379e+06 | 133666 | 2(Loss) |
| jsonifier | 922.611 | 0.217312 | 34.4ms | 136024 | 30 | 2.8008e+06 | 140604 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 3808.7 | 0.13924 | 8.37299ms | 136046 | 30 | 67494.5 | 34065.1 | 1(Win) |
| jsonifier | 3522.21 | 0.599638 | 9.01402ms | 136024 | 30 | 1.46319e+06 | 36829.9 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 624.938 | 1.10675 | 1946.36ms | 2090234 | 32 | 3.98806e+10 | 3.18976e+06 | 1(Win) |
| glaze | 506.467 | 0.954319 | 943.03ms | 2090234 | 30 | 4.23249e+10 | 3.9359e+06 | 2(Loss) |
| simdjson (ondemand) | 479.01 | 0.494571 | 1024.89ms | 2090234 | 30 | 1.27081e+10 | 4.1615e+06 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1764.06 | 0.146913 | 274.995ms | 2090234 | 30 | 8.26809e+07 | 1.13001e+06 | 1(Win) |
| glaze | 1513.16 | 0.217646 | 320.863ms | 2090234 | 30 | 2.46628e+08 | 1.31738e+06 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 1359.09 | 0.64583 | 1124.61ms | 6661897 | 30 | 2.73438e+10 | 4.67466e+06 | 1(Win) |
| glaze | 1308.27 | 0.0966544 | 1187.2ms | 6661897 | 30 | 6.60949e+08 | 4.85626e+06 | 2(Loss) |
| jsonifier | 1170.47 | 0.577655 | 1292.75ms | 6661897 | 30 | 2.94938e+10 | 5.42796e+06 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 2949.57 | 0.0868895 | 543.858ms | 6661897 | 30 | 1.05083e+08 | 2.15397e+06 | 1(Win) |
| jsonifier | 2810.68 | 0.778435 | 575.12ms | 6661897 | 30 | 9.28834e+09 | 2.2604e+06 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1652.61 | 0.261271 | 72.4332ms | 500299 | 30 | 1.70696e+07 | 288708 | 1(Win) |
| glaze | 1240.8 | 0.175182 | 94.122ms | 500299 | 30 | 1.36131e+07 | 384529 | 2(Loss) |
| simdjson (ondemand) | 759.705 | 0.427457 | 151.08ms | 500299 | 30 | 2.1621e+08 | 628036 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4152.76 | 1.46677 | 27.4388ms | 500299 | 30 | 8.51986e+07 | 114893 | 1(Win) |
| glaze | 1828.11 | 0.388461 | 59.754ms | 500299 | 30 | 3.08369e+07 | 260992 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2580.12 | 0.321079 | 129.101ms | 1439562 | 30 | 8.7564e+07 | 532096 | 1(Win) |
| simdjson (ondemand) | 1858.92 | 0.655848 | 176.404ms | 1439562 | 30 | 7.03831e+08 | 738534 | 2(Loss) |
| glaze | 1793.03 | 0.543795 | 182.156ms | 1439562 | 30 | 5.20086e+08 | 765670 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3463.36 | 0.862139 | 93.8409ms | 1439562 | 30 | 3.50381e+08 | 396399 | 1(Win) |
| glaze | 2799.53 | 0.126154 | 118.205ms | 1439584 | 30 | 1.14823e+07 | 490402 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1363.58 | 0.241163 | 10.591ms | 56369 | 30 | 271183 | 39424 | 1(Win) |
| glaze | 1301.6 | 0.788716 | 10.05ms | 56369 | 30 | 3.18339e+06 | 41301.3 | 2(Loss) |
| simdjson (ondemand) | 865.228 | 0.102937 | 15.0369ms | 56369 | 30 | 122711 | 62131.2 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5206.39 | 0.868142 | 2.64499ms | 56369 | 30 | 241052 | 10325.3 | 1(Win) |
| glaze | 2473.39 | 1.6244 | 5.56595ms | 56369 | 30 | 3.73939e+06 | 21734.4 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1765.43 | 0.235582 | 12.5171ms | 94370 | 30 | 432688 | 50978.1 | 1(Win) |
| jsonifier | 1579.79 | 0.877238 | 15.937ms | 94370 | 30 | 7.4925e+06 | 56968.5 | 2(Loss) |
| simdjson (ondemand) | 1329.97 | 0.367875 | 16.7529ms | 94370 | 30 | 1.85911e+06 | 67669.3 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 2909.43 | 1.17044 | 7.776ms | 94370 | 30 | 3.93254e+06 | 30933.3 | 1(Tie) |
| glaze STATISTICAL TIE | 2821.47 | 1.45137 | 7.7289ms | 94370 | 30 | 6.42976e+06 | 31897.6 | 1(Tie) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1241.95 | 1.32723 | 15.4808ms | 52708 | 30 | 8.65685e+06 | 40473.6 | 1(Win) |
| glaze | 1190.98 | 0.178643 | 10.465ms | 52708 | 30 | 170544 | 42205.9 | 2(Loss) |
| simdjson (ondemand) | 1150.5 | 0.193281 | 10.7489ms | 52708 | 30 | 213934 | 43690.7 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4958.4 | 0.636084 | 2.75405ms | 52708 | 30 | 124744 | 10137.6 | 1(Win) |
| glaze | 3686.22 | 0.714069 | 3.55098ms | 52708 | 30 | 284441 | 13636.3 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1457.6 | 0.20395 | 11.3119ms | 70103 | 30 | 262521 | 45866.7 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1450.05 | 0.519198 | 11.4291ms | 70103 | 30 | 1.71908e+06 | 46105.6 | 1(Tie) |
| jsonifier | 1011.96 | 0.859456 | 20.8189ms | 70103 | 30 | 9.67191e+06 | 66065.1 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3876.61 | 1.46981 | 4.36019ms | 70103 | 30 | 1.92759e+06 | 17245.9 | 1(Win) |
| glaze | 3627.14 | 0.51582 | 4.7401ms | 70103 | 30 | 271183 | 18432 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 988.094 | 0.789209 | 3.05203ms | 11812 | 30 | 242860 | 11400.5 | 1(Win) |
| glaze | 773.681 | 0.659341 | 8.37786ms | 11812 | 32 | 294912 | 14560 | 2(Loss) |
| simdjson (ondemand) | 590.646 | 0.560132 | 4.57779ms | 11812 | 30 | 342369 | 19072 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4777.27 | 1.80493 | 6.24384ms | 11812 | 128 | 231855 | 2358 | 1(Win) |
| glaze | 1723.36 | 1.47539 | 1.76102ms | 11812 | 30 | 279018 | 6536.53 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1775.58 | 0.50548 | 4.63206ms | 31235 | 30 | 215741 | 16776.5 | 1(Win) |
| glaze | 1535.08 | 0.483384 | 4.99405ms | 31235 | 30 | 263952 | 19404.8 | 2(Loss) |
| simdjson (ondemand) | 1443.67 | 0.559934 | 5.04781ms | 31235 | 30 | 400448 | 20633.6 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3935.49 | 1.27361 | 2.03597ms | 31235 | 30 | 278792 | 7569.07 | 1(Win) |
| glaze | 2618.74 | 0.790617 | 2.94195ms | 31235 | 30 | 242634 | 11374.9 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2730.02 | 0.190266 | 10.1381ms | 108313 | 30 | 155479 | 37836.8 | 1(Win) |
| glaze | 1315.32 | 0.131403 | 20.3341ms | 108313 | 30 | 319469 | 78532.3 | 2(Loss) |
| simdjson (ondemand) | 1108.71 | 0.296918 | 22.5121ms | 108313 | 30 | 2.29572e+06 | 93166.9 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2022.88 | 0.158961 | 12.446ms | 108313 | 30 | 197663 | 51063.5 | 1(Win) |
| glaze | 1820.56 | 0.144284 | 13.8401ms | 108313 | 30 | 201052 | 56738.1 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2594.92 | 0.459899 | 22.102ms | 213963 | 30 | 3.9235e+06 | 78634.7 | 1(Win) |
| glaze | 1944.56 | 0.3187 | 25.5411ms | 213963 | 30 | 3.35522e+06 | 104934 | 2(Loss) |
| simdjson (ondemand) | 1865.81 | 0.317128 | 26.409ms | 213963 | 30 | 3.60855e+06 | 109363 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2796.42 | 0.464488 | 17.6881ms | 213963 | 30 | 3.44621e+06 | 72968.5 | 1(Win) |
| glaze | 2065.32 | 0.302004 | 23.817ms | 213963 | 30 | 2.67086e+06 | 98798.9 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 570.632 | 1.66548 | 744.735ms | 1834197 | 30 | 7.81955e+10 | 3.06542e+06 | 1(Win) |
| glaze | 495.111 | 0.289066 | 852.653ms | 1834197 | 30 | 3.12898e+09 | 3.533e+06 | 2(Loss) |
| simdjson (ondemand) | 420.761 | 0.412713 | 998.643ms | 1834197 | 30 | 8.83158e+09 | 4.15729e+06 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 788.111 | 0.10258 | 534.382ms | 1833577 | 30 | 1.55406e+08 | 2.21877e+06 | 1(Win) |
| jsonifier | 620.191 | 0.268214 | 635.771ms | 1834197 | 30 | 1.71682e+09 | 2.82046e+06 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2226.66 | 0.441483 | 1039.53ms | 9930848 | 30 | 1.05783e+10 | 4.25336e+06 | 1(Win) |
| glaze | 1881.35 | 0.781034 | 3071.98ms | 9930848 | 32 | 4.94679e+10 | 5.03404e+06 | 2(Loss) |
| simdjson (ondemand) | 1827.09 | 0.593778 | 1242.8ms | 9930848 | 30 | 2.84199e+10 | 5.18354e+06 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2731.65 | 0.914047 | 912.23ms | 9930848 | 30 | 3.01287e+10 | 3.46706e+06 | 1(Win) |
| glaze | 2119.01 | 0.770168 | 1069.3ms | 9930228 | 30 | 3.55422e+10 | 4.46916e+06 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1111.12 | 0.313536 | 135.019ms | 642697 | 30 | 8.97409e+07 | 551629 | 1(Win) |
| simdjson (ondemand) | 813.074 | 0.583598 | 179.478ms | 642697 | 30 | 5.80632e+08 | 753835 | 2(Loss) |
| glaze | 593.597 | 0.0809875 | 251.924ms | 642697 | 30 | 2.09791e+07 | 1.03256e+06 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1029.58 | 0.115622 | 145.582ms | 642692 | 30 | 1.42131e+07 | 595311 | 1(Win) |
| jsonifier | 1005.35 | 0.379533 | 148.183ms | 642697 | 30 | 1.60621e+08 | 609664 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1471.95 | 0.520534 | 207.921ms | 1225964 | 30 | 5.12848e+08 | 794300 | 1(Tie) |
| glaze STATISTICAL TIE | 1467.16 | 0.712394 | 192.443ms | 1225964 | 30 | 9.66858e+08 | 796894 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1448.61 | 0.157443 | 197.067ms | 1225964 | 30 | 4.84421e+07 | 807100 | 1(Tie) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2569.04 | 0.175659 | 110.7ms | 1225964 | 30 | 1.91724e+07 | 455100 | 1(Win) |
| glaze | 1339.22 | 0.130411 | 208.688ms | 1225970 | 30 | 3.88874e+07 | 873028 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 711.737 | 0.124716 | 132.623ms | 409725 | 30 | 1.40642e+07 | 549001 | 1(Win) |
| glaze | 581.849 | 0.339742 | 161.656ms | 409725 | 30 | 1.56165e+08 | 671556 | 2(Loss) |
| simdjson (ondemand) | 569.461 | 0.307679 | 165.397ms | 409725 | 30 | 1.33713e+08 | 686165 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3807.3 | 0.297637 | 24.9631ms | 409725 | 30 | 2.79929e+06 | 102630 | 1(Win) |
| glaze | 1940.76 | 0.508411 | 49.303ms | 409725 | 30 | 3.14335e+07 | 201335 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1083.81 | 0.164855 | 167.808ms | 785750 | 30 | 3.89754e+07 | 691405 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1020.08 | 0.187069 | 177.388ms | 785750 | 30 | 5.66535e+07 | 734601 | 2(Tie) |
| glaze STATISTICAL TIE | 1018.65 | 0.348366 | 177.144ms | 785750 | 30 | 1.97022e+08 | 735633 | 2(Tie) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3090.86 | 1.0277 | 57.3558ms | 785750 | 30 | 1.86237e+08 | 242441 | 1(Win) |
| glaze | 2395.64 | 0.203094 | 75.221ms | 785750 | 30 | 1.21071e+07 | 312798 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 979.669 | 0.824512 | 1996.85ms | 8587914 | 30 | 1.42538e+11 | 8.36004e+06 | 1(Win) |
| glaze | 896.385 | 0.481875 | 2219.3ms | 8587914 | 30 | 5.81535e+10 | 9.13678e+06 | 2(Loss) |
| simdjson (ondemand) | 803.008 | 0.72854 | 2255.67ms | 8587914 | 30 | 1.65639e+11 | 1.01992e+07 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 2650.8 | 1.22623 | 697.546ms | 8588126 | 30 | 4.30632e+10 | 3.08974e+06 | 1(Tie) |
| glaze STATISTICAL TIE | 2614.58 | 1.42521 | 656.938ms | 8588126 | 30 | 5.97958e+10 | 3.13254e+06 | 1(Tie) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1023.84 | 0.721263 | 2295.98ms | 9804437 | 30 | 1.30165e+11 | 9.13256e+06 | 1(Win) |
| simdjson (ondemand) | 991.574 | 0.494492 | 2313.84ms | 9804437 | 30 | 6.5228e+10 | 9.42969e+06 | 2(Loss) |
| glaze | 956.897 | 0.492151 | 2336.65ms | 9804437 | 30 | 6.93798e+10 | 9.77142e+06 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3586.75 | 1.00952 | 713.144ms | 11078090 | 30 | 2.65267e+10 | 2.94554e+06 | 1(Win) |
| glaze | 3260.33 | 0.554174 | 810.679ms | 11078090 | 30 | 9.67429e+09 | 3.24043e+06 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3546.3 | 0.45979 | 17.4441ms | 264040 | 30 | 3.19763e+06 | 71005.9 | 1(Win) |
| simdjson (ondemand) | 2987.02 | 0.353408 | 21.2841ms | 264040 | 30 | 2.6628e+06 | 84300.8 | 2(Loss) |
| glaze | 1443.04 | 0.264079 | 42.3122ms | 264040 | 30 | 6.37048e+06 | 174498 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4276.05 | 0.348846 | 21.804ms | 399947 | 30 | 2.90475e+06 | 89198.9 | 1(Win) |
| simdjson (ondemand) | 3078.34 | 1.25911 | 29.0609ms | 399947 | 30 | 7.30161e+07 | 123904 | 2(Loss) |
| glaze | 1819.49 | 0.353779 | 50.3419ms | 399947 | 30 | 1.65003e+07 | 209630 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1653.34 | 0.225502 | 39.05ms | 264040 | 30 | 3.53864e+06 | 152303 | 1(Win) |
| glaze | 1252.33 | 1.73418 | 48.0891ms | 264040 | 30 | 3.64763e+08 | 201071 | 2(Loss) |
| simdjson (ondemand) | 1165.07 | 0.272295 | 50.0818ms | 264040 | 30 | 1.03905e+07 | 216132 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 3121.57 | 0.36359 | 18.5789ms | 263923 | 30 | 2.57843e+06 | 80631.5 | 1(Win) |
| jsonifier | 3014.48 | 0.163063 | 20.482ms | 264040 | 30 | 556604 | 83532.8 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 1704.71 | 0.137036 | 54.0659ms | 399947 | 30 | 2.82031e+06 | 223744 | 1(Win) |
| glaze | 1589.25 | 0.531386 | 58.9292ms | 399947 | 30 | 4.87938e+07 | 240000 | 2(Loss) |
| jsonifier | 1389.68 | 0.348583 | 70.4131ms | 399947 | 30 | 2.74606e+07 | 274466 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3847.6 | 0.781199 | 24.215ms | 399947 | 30 | 1.79916e+07 | 99131.7 | 1(Win) |
| glaze | 3622.28 | 0.36806 | 25.5969ms | 399830 | 30 | 4.50345e+06 | 105267 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1696.22 | 0.312423 | 67.6088ms | 466906 | 30 | 2.01791e+07 | 262511 | 1(Win) |
| jsonifier | 1576.22 | 0.232961 | 71.2602ms | 466906 | 30 | 1.29931e+07 | 282496 | 2(Loss) |
| simdjson (ondemand) | 866.69 | 0.206463 | 125.596ms | 466906 | 30 | 3.37549e+07 | 513766 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2566.05 | 0.160792 | 62.6949ms | 699405 | 30 | 5.24054e+06 | 259934 | 1(Win) |
| glaze | 2297.88 | 0.156613 | 69.9049ms | 699405 | 30 | 6.19986e+06 | 290270 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2729.2 | 0.340706 | 53.6381ms | 631514 | 30 | 1.6958e+07 | 220672 | 1(Win) |
| glaze | 1899.69 | 0.442598 | 74.0019ms | 631514 | 30 | 5.90665e+07 | 317030 | 2(Loss) |
