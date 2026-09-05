# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.18.33.2-microsoft-standard-WSL2 using the Clang 24.0.0 compiler).  

Latest Results: (Sep 02, 2026)
#### Using the following commits:
----
| Jsonifier: [a1bd83c](https://github.com/nihilai-collective/jsonifier/commit/a1bd83c)  
| Glaze: [a5f515c](https://github.com/stephenberry/glaze/commit/a5f515c)  
| Simdjson: [06856ec](https://github.com/simdjson/simdjson/commit/06856ec)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX2` |
| simdjson (ondemand) | `haswell` |
| Glaze (utf8-validation) | `AVX2` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.5% AND mean shift < 1% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [f0ef39c](https://github.com/realtimechris/benchmarksuite/commit/f0ef39c).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1219.22 | 0.118598 | 1.73421ms | 1811 | 32 | 90.3185 | 1416.56 | 2.44578 | 1(Win) |
| glaze | 776.331 | 0.135368 | 0.772575ms | 1811 | 30 | 272.079 | 2224.7 | 3.86731 | 2(Loss) |
| simdjson (ondemand) | 219.658 | 0.367009 | 2.12259ms | 1811 | 30 | 24981.5 | 7862.7 | 13.7791 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 761.823 | 0.0742309 | 0.781334ms | 1811 | 30 | 84.9609 | 2267.07 | 3.94132 | 1(Win) |
| glaze | 531.368 | 1.27529 | 1.09627ms | 1798 | 30 | 50807.2 | 3226.97 | 5.65899 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2164.88 | 0.0744438 | 0.650046ms | 3873 | 30 | 48.3954 | 1706.13 | 1.38911 | 1(Win) |
| glaze | 1663.15 | 0.0382615 | 0.79607ms | 3873 | 30 | 21.6609 | 2220.83 | 1.805 | 2(Loss) |
| simdjson (ondemand) | 518.946 | 0.0335009 | 5.26012ms | 3873 | 32 | 181.934 | 7117.47 | 5.84233 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3166.38 | 0.0755385 | 0.52523ms | 3873 | 30 | 23.2931 | 1166.5 | 0.932602 | 1(Win) |
| glaze | 1474.05 | 0.151127 | 0.854955ms | 3873 | 30 | 430.202 | 2505.73 | 2.0433 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2068.3 | 0.161863 | 0.660044ms | 3862 | 30 | 249.237 | 1780.73 | 1.44753 | 1(Win) |
| glaze | 1350.32 | 0.0712454 | 0.955777ms | 3862 | 30 | 113.289 | 2727.57 | 2.22411 | 2(Loss) |
| simdjson (ondemand) | 494.498 | 0.0456224 | 2.09065ms | 3862 | 30 | 346.395 | 7448.13 | 6.11516 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3008.16 | 0.0959609 | 0.53187ms | 3862 | 30 | 41.4126 | 1224.37 | 0.9768 | 1(Win) |
| glaze | 1499.24 | 0.152514 | 0.857575ms | 3862 | 30 | 421.137 | 2456.63 | 2.00287 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1405.97 | 0.143751 | 0.377976ms | 905 | 30 | 23.3609 | 613.867 | 2.0951 | 1(Win) |
| glaze | 675.069 | 0.917595 | 0.687379ms | 905 | 30 | 4128.81 | 1278.5 | 4.39606 | 2(Loss) |
| simdjson (ondemand) | 226.791 | 0.0620884 | 1.23997ms | 905 | 30 | 167.49 | 3805.6 | 13.3202 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1436.7 | 0.033799 | 0.383625ms | 905 | 30 | 1.23678 | 600.733 | 2.05087 | 1(Win) |
| glaze | 377.075 | 0.150819 | 0.80811ms | 905 | 30 | 357.499 | 2288.87 | 7.97772 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3758.71 | 0.0362233 | 1.35079ms | 9578 | 30 | 23.2471 | 2430.17 | 0.799742 | 1(Win) |
| glaze | 2641.73 | 0.142576 | 2.28543ms | 9578 | 32 | 777.706 | 3457.69 | 1.14312 | 2(Loss) |
| simdjson (ondemand) | 1584.1 | 0.13502 | 1.65894ms | 9578 | 30 | 1818.46 | 5766.23 | 1.91194 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5784.98 | 0.0507645 | 0.620647ms | 9578 | 30 | 19.2747 | 1578.97 | 0.517404 | 1(Win) |
| glaze | 3435.15 | 0.233189 | 0.913324ms | 9578 | 30 | 1153.44 | 2659.07 | 0.874153 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5813.45 | 0.560675 | 9.58383ms | 233995 | 30 | 1.3896e+06 | 38386 | 0.522423 | 1(Win) |
| simdjson (ondemand) | 5567.8 | 0.0388834 | 23.677ms | 233995 | 32 | 7771.87 | 40079.6 | 0.545494 | 2(Loss) |
| glaze | 2288.89 | 0.393801 | 124.252ms | 233995 | 64 | 9.434e+06 | 97494.7 | 1.32733 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7347.03 | 0.459334 | 58.4109ms | 346753 | 64 | 2.7356e+06 | 45009.9 | 0.413418 | 1(Win) |
| simdjson (ondemand) | 6927.55 | 0.785075 | 11.7494ms | 346753 | 30 | 4.21333e+06 | 47735.4 | 0.4383 | 2(Loss) |
| glaze | 2945.17 | 1.23093 | 26.4846ms | 346753 | 30 | 5.73068e+07 | 112282 | 1.03159 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2254.74 | 0.385708 | 24.2919ms | 233995 | 30 | 4.3718e+06 | 98971.6 | 1.34756 | 1(Win) |
| glaze | 1815.36 | 0.697431 | 30.4302ms | 233995 | 30 | 2.20501e+07 | 122926 | 1.67366 | 2(Loss) |
| simdjson (ondemand) | 1240.67 | 1.13 | 105.944ms | 233995 | 32 | 1.32193e+08 | 179866 | 2.44922 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4649.22 | 1.06652 | 11.8401ms | 233995 | 30 | 7.86159e+06 | 47998.4 | 0.653013 | 1(Win) |
| glaze | 4127.84 | 0.551593 | 13.4968ms | 233995 | 30 | 2.66764e+06 | 54061 | 0.73583 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2333.93 | 0.579833 | 34.5776ms | 346753 | 30 | 2.02485e+07 | 141688 | 1.30194 | 1(Win) |
| glaze | 2221.1 | 0.564248 | 36.3379ms | 346753 | 30 | 2.11722e+07 | 148885 | 1.368 | 2(Loss) |
| simdjson (ondemand) | 1776.98 | 0.703607 | 47.1933ms | 346753 | 30 | 5.14347e+07 | 186096 | 1.71007 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4514.68 | 0.625188 | 17.7576ms | 346753 | 30 | 6.29114e+06 | 73247.6 | 0.672653 | 1(Win) |
| glaze | 4267.63 | 0.867566 | 18.7451ms | 346753 | 30 | 1.35579e+07 | 77487.9 | 0.711763 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5463.06 | 1.15326 | 9.79124ms | 233995 | 30 | 6.6576e+06 | 40848 | 0.555909 | 1(Win) |
| simdjson (ondemand) | 3771.5 | 0.683752 | 14.454ms | 233995 | 30 | 4.91026e+06 | 59168.8 | 0.805413 | 2(Loss) |
| glaze | 2280.57 | 1.61632 | 23.4557ms | 233995 | 30 | 7.5042e+07 | 97850.5 | 1.33191 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6933.23 | 0.625608 | 11.6478ms | 346753 | 30 | 2.67113e+06 | 47696.3 | 0.4381 | 1(Win) |
| simdjson (ondemand) | 5070.51 | 1.13657 | 15.9603ms | 346753 | 30 | 1.64836e+07 | 65218.2 | 0.599116 | 2(Loss) |
| glaze | 3014.55 | 0.861954 | 26.4365ms | 346753 | 30 | 2.68216e+07 | 109698 | 1.00792 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1978.17 | 0.677126 | 27.5397ms | 233995 | 30 | 1.75044e+07 | 112809 | 1.53601 | 1(Win) |
| glaze | 1781.7 | 1.00949 | 29.9757ms | 233995 | 30 | 4.7959e+07 | 125249 | 1.70544 | 2(Loss) |
| simdjson (ondemand) | 402.22 | 0.333567 | 134.513ms | 233995 | 30 | 1.02748e+08 | 554808 | 7.55557 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4591.6 | 0.658982 | 12.086ms | 233995 | 30 | 3.07718e+06 | 48600.7 | 0.661353 | 1(Win) |
| glaze | 4361.86 | 0.34386 | 13.1839ms | 233995 | 30 | 928443 | 51160.6 | 0.696313 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2277.3 | 0.720103 | 35.6731ms | 346753 | 30 | 3.28029e+07 | 145211 | 1.33433 | 1(Tie) |
| glaze STATISTICAL TIE | 2243.2 | 0.473658 | 35.8253ms | 346753 | 30 | 1.4627e+07 | 147419 | 1.35462 | 1(Tie) |
| simdjson (ondemand) | 590.24 | 0.25964 | 136.51ms | 346753 | 30 | 6.34818e+07 | 560263 | 5.14876 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4398.71 | 0.887352 | 18.6957ms | 346753 | 30 | 1.33506e+07 | 75178.7 | 0.690488 | 1(Win) |
| glaze | 4133.57 | 1.0339 | 19.8846ms | 346753 | 30 | 2.05243e+07 | 80001 | 0.734716 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1301.4 | 0.868551 | 16.8346ms | 94651 | 30 | 1.08877e+07 | 69360.6 | 2.33393 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1286.03 | 0.826692 | 17.1099ms | 94651 | 30 | 1.01009e+07 | 70190 | 2.36224 | 1(Tie) |
| simdjson (ondemand) | 996.258 | 0.605261 | 22.3961ms | 94651 | 30 | 9.02222e+06 | 90605.3 | 3.04914 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5625.48 | 1.38616 | 4.30259ms | 94651 | 30 | 1.48416e+06 | 16046 | 0.537954 | 1(Win) |
| glaze | 4866.53 | 1.78262 | 4.94005ms | 94651 | 30 | 3.27982e+06 | 18548.4 | 0.623454 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1547.81 | 1.12505 | 19.9821ms | 136024 | 30 | 2.66721e+07 | 83810.4 | 1.96245 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1521.5 | 0.373879 | 21.4418ms | 136024 | 30 | 3.04838e+06 | 85259.4 | 1.99689 | 1(Tie) |
| simdjson (ondemand) | 1364.33 | 0.478554 | 23.0409ms | 136024 | 30 | 6.21122e+06 | 95081.7 | 2.22694 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4885.08 | 0.196525 | 6.81047ms | 136024 | 30 | 81704.2 | 26554.8 | 0.620383 | 1(Win) |
| glaze | 4730.76 | 0.117628 | 7.1256ms | 136046 | 30 | 31221.3 | 27425.5 | 0.641762 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 938.619 | 0.144923 | 516.384ms | 2090234 | 30 | 2.8419e+08 | 2.12376e+06 | 3.23734 | 1(Win) |
| glaze | 774.416 | 0.332569 | 627.497ms | 2090234 | 30 | 2.19849e+09 | 2.57407e+06 | 3.92411 | 2(Loss) |
| simdjson (ondemand) | 503.341 | 0.246761 | 962.097ms | 2090234 | 30 | 2.8651e+09 | 3.96034e+06 | 6.03762 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1578.6 | 0.220804 | 304.71ms | 2090234 | 30 | 2.33227e+08 | 1.26276e+06 | 1.92463 | 1(Win) |
| glaze | 929.178 | 0.487057 | 518.568ms | 2090234 | 30 | 3.27547e+09 | 2.14534e+06 | 3.27042 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2471.33 | 0.342331 | 626.437ms | 6661897 | 30 | 2.32353e+09 | 2.57079e+06 | 1.22958 | 1(Win) |
| glaze | 1953.2 | 0.233428 | 779.723ms | 6661897 | 30 | 1.72954e+09 | 3.25275e+06 | 1.55579 | 2(Loss) |
| simdjson (ondemand) | 1520.17 | 0.180357 | 1042.35ms | 6661897 | 30 | 1.70451e+09 | 4.17932e+06 | 1.99903 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3372.19 | 0.234918 | 458.309ms | 6661897 | 30 | 5.87658e+08 | 1.88402e+06 | 0.901005 | 1(Win) |
| glaze | 2253.66 | 0.592441 | 686.108ms | 6661897 | 30 | 8.36817e+09 | 2.8191e+06 | 1.34825 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1842.3 | 0.463362 | 64.5417ms | 500299 | 30 | 4.32018e+07 | 258982 | 1.64944 | 1(Win) |
| glaze | 1723.99 | 0.750733 | 66.8912ms | 500299 | 30 | 1.29504e+08 | 276755 | 1.76265 | 2(Loss) |
| simdjson (ondemand) | 973.526 | 0.368435 | 117.722ms | 500299 | 30 | 9.78155e+07 | 490097 | 3.12146 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 5350.92 | 0.579631 | 22.245ms | 500299 | 30 | 8.0136e+06 | 89166.4 | 0.567683 | 1(Tie) |
| jsonifier STATISTICAL TIE | 5338.53 | 0.978304 | 22.4803ms | 500299 | 30 | 2.29343e+07 | 89373.4 | 0.56895 | 1(Tie) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3542.45 | 0.765378 | 93.609ms | 1439562 | 30 | 2.63954e+08 | 387550 | 0.857668 | 1(Win) |
| glaze | 2906.18 | 0.524135 | 113.2ms | 1439562 | 30 | 1.83918e+08 | 472398 | 1.04559 | 2(Loss) |
| simdjson (ondemand) | 2472.47 | 0.745082 | 132.413ms | 1439562 | 30 | 5.13485e+08 | 555264 | 1.22897 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6021.77 | 1.31869 | 55.3142ms | 1439562 | 30 | 2.71157e+08 | 227985 | 0.50436 | 1(Win) |
| glaze | 5205.67 | 0.677534 | 63.8816ms | 1439584 | 30 | 9.57865e+07 | 263731 | 0.583523 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1870.01 | 1.01836 | 7.31569ms | 56369 | 30 | 2.57107e+06 | 28747.2 | 1.62367 | 1(Win) |
| jsonifier | 1805.67 | 1.10552 | 7.60278ms | 56369 | 30 | 3.24984e+06 | 29771.7 | 1.68136 | 2(Loss) |
| simdjson (ondemand) | 1128.68 | 1.23881 | 12.0891ms | 56369 | 30 | 1.04441e+07 | 47628.8 | 2.69107 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6043.24 | 2.08096 | 5.33444ms | 56369 | 32 | 1.09653e+06 | 8895.5 | 0.501188 | 1(Win) |
| jsonifier | 5589.1 | 0.254182 | 2.77657ms | 56369 | 30 | 17931.2 | 9618.3 | 0.539746 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2354.6 | 2.36567 | 21.7029ms | 94370 | 32 | 2.61634e+07 | 38222.4 | 1.28959 | 1(Win) |
| jsonifier | 2022.11 | 0.303536 | 11.1362ms | 94370 | 30 | 547520 | 44507.1 | 1.50215 | 2(Loss) |
| simdjson (ondemand) | 1866.3 | 0.674672 | 12.1783ms | 94370 | 30 | 3.17549e+06 | 48222.8 | 1.62753 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5874.71 | 0.12489 | 4.07256ms | 94370 | 30 | 10981.7 | 15319.6 | 0.514929 | 1(Win) |
| glaze | 5134.93 | 0.426368 | 4.60917ms | 94370 | 30 | 167529 | 17526.7 | 0.590851 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1580 | 0.434349 | 8.43874ms | 52708 | 30 | 572844 | 31814.1 | 1.92202 | 1(Win) |
| glaze | 1460.2 | 0.421736 | 8.72931ms | 52708 | 30 | 632308 | 34424.1 | 2.07949 | 2(Loss) |
| simdjson (ondemand) | 1276.61 | 0.806816 | 9.94666ms | 52708 | 30 | 3.02764e+06 | 39374.7 | 2.37884 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6664.7 | 0.104642 | 2.2731ms | 52708 | 30 | 1868.63 | 7542.17 | 0.454305 | 1(Win) |
| jsonifier | 5885.64 | 0.417516 | 2.5042ms | 52708 | 30 | 38144.7 | 8540.5 | 0.512338 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1695.72 | 0.474326 | 10.1095ms | 70103 | 30 | 1.04915e+06 | 39425.9 | 1.7911 | 1(Tie) |
| glaze STATISTICAL TIE | 1663.74 | 1.75073 | 10.2623ms | 70103 | 30 | 1.48477e+07 | 40183.8 | 1.82539 | 1(Tie) |
| jsonifier | 1580.82 | 0.801398 | 11.9379ms | 70103 | 30 | 3.44608e+06 | 42291.6 | 1.9213 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6289.95 | 0.20504 | 2.8953ms | 70103 | 30 | 14248.8 | 10628.9 | 0.481882 | 1(Win) |
| jsonifier | 6041.41 | 0.300655 | 3.12695ms | 70103 | 30 | 33209 | 11066.2 | 0.499754 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1479.31 | 0.77307 | 4.6156ms | 11812 | 32 | 110896 | 7614.91 | 2.04791 | 1(Win) |
| glaze | 1326.17 | 0.128292 | 2.37763ms | 11812 | 30 | 3562.62 | 8494.27 | 2.28477 | 2(Loss) |
| simdjson (ondemand) | 908.956 | 0.113139 | 7.35104ms | 11812 | 32 | 6291.27 | 12393.1 | 3.33683 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5435.28 | 0.171189 | 0.816319ms | 11812 | 30 | 377.637 | 2072.53 | 0.547711 | 1(Win) |
| glaze | 4547.33 | 0.125935 | 0.973227ms | 11812 | 30 | 291.978 | 2477.23 | 0.66161 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2745.9 | 0.183478 | 2.95174ms | 31235 | 30 | 11885 | 10848.2 | 1.10406 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 2144.32 | 0.118798 | 3.68285ms | 31235 | 30 | 8170.46 | 13891.6 | 1.41469 | 2(Tie) |
| glaze STATISTICAL TIE | 2108.8 | 1.67689 | 3.69156ms | 31235 | 30 | 1.68323e+06 | 14125.6 | 1.43857 | 2(Tie) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6029.03 | 0.046567 | 1.50602ms | 31235 | 30 | 158.806 | 4940.77 | 0.497303 | 1(Win) |
| glaze | 5863.36 | 0.120037 | 1.57001ms | 31235 | 30 | 1115.69 | 5080.37 | 0.515299 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3521.1 | 0.928682 | 7.53016ms | 108313 | 30 | 2.2267e+06 | 29336.1 | 0.862218 | 1(Win) |
| glaze | 2119.92 | 1.3732 | 61.0948ms | 108313 | 64 | 2.8653e+07 | 48726.1 | 1.43247 | 2(Loss) |
| simdjson (ondemand) | 1471.13 | 0.625658 | 17.2043ms | 108313 | 30 | 5.7897e+06 | 70215.1 | 2.06508 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6308.93 | 0.950959 | 4.24931ms | 108313 | 30 | 727268 | 16372.9 | 0.479484 | 1(Win) |
| glaze | 5041.9 | 2.17089 | 4.33755ms | 108313 | 30 | 5.93431e+06 | 20487.4 | 0.601862 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2894.06 | 1.20407 | 17.5553ms | 213963 | 30 | 2.16215e+07 | 70506.9 | 1.04973 | 1(Win) |
| jsonifier | 2785.54 | 0.505027 | 17.9953ms | 213963 | 30 | 4.10591e+06 | 73253.6 | 1.09059 | 2(Loss) |
| simdjson (ondemand) | 2668.72 | 0.655061 | 18.7111ms | 213963 | 30 | 7.52585e+06 | 76460.2 | 1.13838 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6698.84 | 0.962321 | 7.84781ms | 213963 | 30 | 2.57774e+06 | 30460.6 | 0.452768 | 1(Win) |
| glaze | 5673.42 | 0.888792 | 9.04559ms | 213963 | 30 | 3.06556e+06 | 35966.2 | 0.535256 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 926.483 | 0.324115 | 465.835ms | 1834197 | 30 | 1.12341e+09 | 1.88803e+06 | 3.27982 | 1(Win) |
| glaze | 684.925 | 0.262969 | 620.338ms | 1834197 | 30 | 1.35312e+09 | 2.5539e+06 | 4.43678 | 2(Loss) |
| simdjson (ondemand) | 395.642 | 0.205618 | 1064.9ms | 1834197 | 30 | 2.47932e+09 | 4.42124e+06 | 7.68114 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1084.23 | 0.249644 | 389.43ms | 1834197 | 30 | 4.86641e+08 | 1.61333e+06 | 2.80269 | 1(Win) |
| glaze | 562.46 | 1.0798 | 716.8ms | 1833577 | 30 | 3.38081e+10 | 3.10891e+06 | 5.40296 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3206.28 | 0.709545 | 699.799ms | 9930848 | 30 | 1.31781e+10 | 2.95383e+06 | 0.947799 | 1(Win) |
| glaze | 2604.16 | 0.521256 | 875.941ms | 9930848 | 30 | 1.07811e+10 | 3.6368e+06 | 1.16699 | 2(Loss) |
| simdjson (ondemand) | 1826.5 | 0.798784 | 1222.24ms | 9930848 | 30 | 5.14654e+10 | 5.18522e+06 | 1.66381 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3172.37 | 0.273199 | 744.097ms | 9930848 | 30 | 1.99565e+09 | 2.9854e+06 | 0.957721 | 1(Win) |
| glaze | 1685.71 | 0.688638 | 1400.19ms | 9930228 | 30 | 4.4901e+10 | 5.61793e+06 | 1.80255 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1659.64 | 0.539287 | 216.072ms | 642697 | 32 | 1.26932e+08 | 369311 | 1.83088 | 1(Win) |
| glaze | 1398.53 | 0.329879 | 105.444ms | 642697 | 30 | 6.27044e+07 | 438262 | 2.17283 | 2(Loss) |
| simdjson (ondemand) | 659.236 | 0.324282 | 544.731ms | 642697 | 32 | 2.90888e+08 | 929748 | 4.60981 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1809.03 | 0.497744 | 81.7853ms | 642697 | 30 | 8.53203e+07 | 338813 | 1.67957 | 1(Win) |
| glaze | 889.92 | 1.33831 | 164.703ms | 642692 | 30 | 2.54882e+09 | 688735 | 3.41372 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2294.9 | 0.668599 | 122.265ms | 1225964 | 30 | 3.48082e+08 | 509465 | 1.32393 | 1(Win) |
| glaze | 2103.69 | 0.483877 | 703.198ms | 1225964 | 64 | 4.6285e+08 | 555770 | 1.44427 | 2(Loss) |
| simdjson (ondemand) | 1186.14 | 0.649027 | 582.564ms | 1225964 | 32 | 1.30966e+09 | 985690 | 2.56129 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2472 | 0.438673 | 120.271ms | 1225964 | 30 | 1.2914e+08 | 472966 | 1.22905 | 1(Win) |
| glaze | 1542.59 | 1.64299 | 419.25ms | 1225970 | 32 | 4.96226e+09 | 757933 | 1.96915 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1201.61 | 0.44076 | 80.3485ms | 409725 | 30 | 6.16293e+07 | 325185 | 2.52891 | 1(Win) |
| glaze | 939.241 | 0.408009 | 101.506ms | 409725 | 30 | 8.64355e+07 | 416021 | 3.23533 | 2(Loss) |
| simdjson (ondemand) | 796.477 | 0.524942 | 118.825ms | 409725 | 30 | 1.98968e+08 | 490591 | 3.8152 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3412.16 | 0.729695 | 27.9453ms | 409725 | 30 | 2.09474e+07 | 114515 | 0.89016 | 1(Win) |
| glaze | 3024.81 | 1.94851 | 31.18ms | 409725 | 30 | 1.90071e+08 | 129180 | 1.00415 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1574.81 | 0.395312 | 115.868ms | 785750 | 30 | 1.06148e+08 | 475834 | 1.9296 | 1(Win) |
| simdjson (ondemand) | 1472.11 | 0.457824 | 124.021ms | 785750 | 30 | 1.62932e+08 | 509030 | 2.06423 | 2(Loss) |
| glaze | 1423.79 | 0.466524 | 127.135ms | 785750 | 30 | 1.80862e+08 | 526307 | 2.13434 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4023.09 | 0.724218 | 45.1573ms | 785750 | 30 | 5.45896e+07 | 186262 | 0.755106 | 1(Win) |
| glaze | 3758.2 | 0.669984 | 49.7672ms | 785750 | 30 | 5.35375e+07 | 199390 | 0.808331 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1254.23 | 1.28126 | 1556.24ms | 8587914 | 30 | 2.1e+11 | 6.52998e+06 | 2.42278 | 1(Win) |
| glaze | 1098.29 | 1.2252 | 1830.02ms | 8587914 | 30 | 2.50426e+11 | 7.45714e+06 | 2.76681 | 2(Loss) |
| simdjson (ondemand) | 911.266 | 0.330893 | 2144.9ms | 8587914 | 30 | 2.65327e+10 | 8.98758e+06 | 3.3348 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2668.85 | 0.697795 | 789.054ms | 8588126 | 30 | 1.3757e+10 | 3.06884e+06 | 1.13822 | 1(Win) |
| glaze | 2394.49 | 0.747467 | 876.632ms | 8588126 | 30 | 1.961e+10 | 3.42047e+06 | 1.26876 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1228.66 | 0.271323 | 1873.02ms | 9804437 | 30 | 1.27902e+10 | 7.6101e+06 | 2.47328 | 1(Win) |
| glaze | 1174.02 | 1.13989 | 2036.68ms | 9804437 | 30 | 2.47254e+11 | 7.96429e+06 | 2.58843 | 2(Loss) |
| simdjson (ondemand) | 1083.21 | 0.534051 | 2134.98ms | 9804437 | 30 | 6.37535e+10 | 8.63194e+06 | 2.80536 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2846.44 | 0.613491 | 902.076ms | 11078090 | 30 | 1.55548e+10 | 3.71162e+06 | 1.06732 | 1(Win) |
| glaze | 2774.99 | 0.986434 | 974.59ms | 11078090 | 30 | 4.2312e+10 | 3.80718e+06 | 1.09485 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 5571.93 | 0.858968 | 11.3191ms | 264040 | 30 | 4.52068e+06 | 45192.3 | 0.544882 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 5506.39 | 0.746307 | 11.4923ms | 264040 | 30 | 3.49431e+06 | 45730.2 | 0.551563 | 1(Tie) |
| glaze | 2244.76 | 0.549155 | 27.5489ms | 264040 | 30 | 1.13844e+07 | 112176 | 1.35347 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 7246.11 | 0.684515 | 13.3539ms | 399947 | 30 | 3.89478e+06 | 52637.8 | 0.419138 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 7019.91 | 1.68663 | 13.5201ms | 399947 | 30 | 2.51942e+07 | 54333.9 | 0.432641 | 1(Tie) |
| glaze | 2989.16 | 0.506861 | 31.1141ms | 399947 | 30 | 1.25489e+07 | 127601 | 1.01653 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1806.12 | 0.573322 | 34.1978ms | 264040 | 30 | 1.91676e+07 | 139420 | 1.68203 | 1(Win) |
| glaze | 1618.99 | 0.904083 | 38.3958ms | 264040 | 30 | 5.93182e+07 | 155534 | 1.87677 | 2(Loss) |
| simdjson (ondemand) | 1332.99 | 0.565346 | 46.5239ms | 264040 | 30 | 3.42163e+07 | 188904 | 2.27925 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6840.83 | 1.09504 | 9.86136ms | 264040 | 30 | 4.87423e+06 | 36809.6 | 0.44366 | 1(Win) |
| glaze | 5990.96 | 1.46395 | 11.3861ms | 263923 | 30 | 1.13484e+07 | 42012.7 | 0.506638 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2032.2 | 1.11819 | 45.4912ms | 399947 | 30 | 1.32138e+08 | 187688 | 1.49525 | 1(Win) |
| simdjson (ondemand) | 1937.64 | 0.718439 | 48.5465ms | 399947 | 30 | 6.0001e+07 | 196847 | 1.56808 | 2(Loss) |
| jsonifier | 1861.71 | 0.514426 | 123.745ms | 399947 | 32 | 3.55446e+07 | 204875 | 1.63226 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6178.91 | 1.32554 | 78.5631ms | 399947 | 64 | 4.28497e+07 | 61729.2 | 0.491387 | 1(Win) |
| glaze | 5797.54 | 1.29193 | 16.9386ms | 399830 | 30 | 2.16603e+07 | 65770.6 | 0.523933 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2880.38 | 0.739312 | 38.0373ms | 466906 | 30 | 3.91865e+07 | 154589 | 1.05486 | 1(Win) |
| jsonifier | 2781.68 | 0.863015 | 38.4377ms | 466906 | 30 | 5.72536e+07 | 160075 | 1.09194 | 2(Loss) |
| simdjson (ondemand) | 1305.47 | 0.541097 | 82.3406ms | 466906 | 30 | 1.02187e+08 | 341086 | 2.32745 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3969.38 | 0.713457 | 40.8485ms | 699405 | 30 | 4.31191e+07 | 168038 | 0.764507 | 1(Win) |
| glaze | 3384.07 | 2.03711 | 46.4426ms | 699405 | 30 | 4.83646e+08 | 197101 | 0.897322 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4544.91 | 0.319856 | 33.6557ms | 631514 | 30 | 5.38948e+06 | 132513 | 0.668407 | 1(Win) |
| glaze | 2735.96 | 0.503127 | 53.9507ms | 631514 | 30 | 3.67979e+07 | 220127 | 1.11054 | 2(Loss) |
