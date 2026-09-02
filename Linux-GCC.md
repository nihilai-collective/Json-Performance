# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.18.33.2-microsoft-standard-WSL2 using the GCC 16.1.0 compiler).  

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

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1219.3 | 0.176527 | 1.21526ms | 1811 | 30 | 187.568 | 1416.47 | 2.45378 | 1(Win) |
| glaze | 875.325 | 0.234206 | 0.745446ms | 1811 | 30 | 640.645 | 1973.1 | 3.43236 | 2(Loss) |
| simdjson (ondemand) | 229.384 | 0.110111 | 2.08656ms | 1811 | 30 | 2062.01 | 7529.3 | 13.2067 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 721.782 | 0.0838726 | 0.862974ms | 1811 | 30 | 120.833 | 2392.83 | 4.15362 | 1(Win) |
| glaze | 493.19 | 0.228788 | 1.10814ms | 1798 | 30 | 1898.19 | 3476.77 | 6.09746 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1998.01 | 0.0476465 | 0.742762ms | 3873 | 30 | 23.2747 | 1848.63 | 1.49779 | 1(Win) |
| glaze | 1863.06 | 0.0405933 | 0.754219ms | 3873 | 30 | 19.4299 | 1982.53 | 1.60948 | 2(Loss) |
| simdjson (ondemand) | 456.065 | 0.245751 | 2.26283ms | 3873 | 30 | 11883.8 | 8098.8 | 6.64179 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3033.24 | 0.0804195 | 0.608492ms | 3873 | 30 | 28.769 | 1217.7 | 0.974998 | 1(Win) |
| glaze | 1408.03 | 0.176941 | 0.967717ms | 3873 | 30 | 646.323 | 2623.23 | 2.13633 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2067.33 | 0.0380298 | 0.723957ms | 3862 | 30 | 13.7713 | 1781.57 | 1.44947 | 1(Win) |
| glaze | 1721.23 | 0.0568359 | 0.777276ms | 3862 | 30 | 44.3724 | 2139.8 | 1.74939 | 2(Loss) |
| simdjson (ondemand) | 463.258 | 1.61975 | 2.17105ms | 3862 | 30 | 497501 | 7950.4 | 6.53721 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2930.45 | 0.258794 | 0.588545ms | 3862 | 30 | 317.385 | 1256.83 | 1.01034 | 1(Win) |
| glaze | 1405.67 | 0.104032 | 0.95099ms | 3862 | 30 | 222.902 | 2620.17 | 2.14249 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1833.99 | 0.0347002 | 0.385191ms | 905 | 30 | 0.8 | 470.6 | 1.5905 | 1(Win) |
| glaze | 643.396 | 0.0398784 | 1.10328ms | 905 | 32 | 9.15726 | 1341.44 | 4.65881 | 2(Loss) |
| simdjson (ondemand) | 198.925 | 0.0953526 | 1.43361ms | 905 | 30 | 513.459 | 4338.7 | 15.2022 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1305.97 | 0.304431 | 0.414043ms | 905 | 30 | 121.43 | 660.867 | 2.26269 | 1(Win) |
| glaze | 344.917 | 0.125924 | 0.922651ms | 905 | 30 | 297.857 | 2502.27 | 8.73061 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3705.09 | 0.0349708 | 0.929425ms | 9578 | 30 | 22.2989 | 2465.33 | 0.811133 | 1(Win) |
| glaze | 2964.59 | 0.154062 | 1.04172ms | 9578 | 30 | 675.982 | 3081.13 | 1.01513 | 2(Loss) |
| simdjson (ondemand) | 1491.98 | 0.062759 | 1.81858ms | 9578 | 30 | 442.892 | 6122.27 | 2.02998 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5981.2 | 0.171274 | 0.635928ms | 9578 | 30 | 205.247 | 1527.17 | 0.498298 | 1(Win) |
| glaze | 2954.14 | 0.1094 | 1.03573ms | 9578 | 30 | 343.275 | 3092.03 | 1.01684 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5290.16 | 0.897783 | 14.5437ms | 233995 | 30 | 4.30268e+06 | 42183 | 0.574153 | 1(Win) |
| simdjson (ondemand) | 3586.05 | 1.15263 | 14.56ms | 233995 | 30 | 1.54342e+07 | 62228.6 | 0.847159 | 2(Loss) |
| glaze | 2150.7 | 0.5296 | 27.0014ms | 233995 | 30 | 9.0588e+06 | 103759 | 1.41278 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7014.28 | 0.513768 | 11.9993ms | 346753 | 30 | 1.76007e+06 | 47145.2 | 0.433059 | 1(Win) |
| simdjson (ondemand) | 5249.15 | 1.41701 | 15.9466ms | 346753 | 30 | 2.39072e+07 | 62998.7 | 0.578755 | 2(Loss) |
| glaze | 2731.52 | 0.488972 | 30.1473ms | 346753 | 30 | 1.05129e+07 | 121064 | 1.11243 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1856.68 | 0.648911 | 29.7757ms | 233995 | 30 | 1.82487e+07 | 120190 | 1.63653 | 1(Win) |
| glaze | 1718.06 | 1.44343 | 32.4407ms | 233995 | 30 | 1.05451e+08 | 129887 | 1.76838 | 2(Loss) |
| simdjson (ondemand) | 1559.11 | 0.758368 | 36.1196ms | 233995 | 30 | 3.53463e+07 | 143130 | 1.94878 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4495.85 | 0.348165 | 12.5184ms | 233995 | 30 | 895943 | 49635.7 | 0.674999 | 1(Win) |
| glaze | 4179.75 | 0.911302 | 13.493ms | 233995 | 30 | 7.10164e+06 | 53389.6 | 0.726679 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 2142.64 | 1.03378 | 40.2389ms | 346753 | 30 | 7.63694e+07 | 154338 | 1.41817 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2134.25 | 1.17961 | 38.4889ms | 346753 | 30 | 1.00218e+08 | 154944 | 1.42367 | 1(Tie) |
| jsonifier | 1592.02 | 0.587081 | 122.113ms | 346753 | 32 | 4.75874e+07 | 207717 | 1.90875 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4785.12 | 1.43596 | 172.575ms | 346753 | 128 | 1.26052e+08 | 69107.8 | 0.634414 | 1(Win) |
| glaze | 4456.8 | 0.558302 | 19.6976ms | 346753 | 30 | 5.14818e+06 | 74198.9 | 0.681602 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5218.52 | 0.164131 | 10.7723ms | 233995 | 30 | 147781 | 42762.1 | 0.582083 | 1(Win) |
| simdjson (ondemand) | 2771.46 | 0.370488 | 19.501ms | 233995 | 30 | 2.66973e+06 | 80519.1 | 1.09625 | 2(Loss) |
| glaze | 2161.21 | 0.439621 | 24.9597ms | 233995 | 30 | 6.18153e+06 | 103254 | 1.40591 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6638.2 | 0.589728 | 12.2509ms | 346753 | 30 | 2.58919e+06 | 49816.1 | 0.457573 | 1(Win) |
| simdjson (ondemand) | 3896.79 | 0.850935 | 20.7727ms | 346753 | 30 | 1.56437e+07 | 84862 | 0.779679 | 2(Loss) |
| glaze | 2791.83 | 0.342704 | 29.0321ms | 346753 | 30 | 4.94337e+06 | 118449 | 1.0884 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1859.05 | 0.71004 | 28.9844ms | 233995 | 30 | 2.1793e+07 | 120037 | 1.63449 | 1(Win) |
| jsonifier | 1654.36 | 0.359651 | 33.2093ms | 233995 | 30 | 7.06051e+06 | 134889 | 1.83678 | 2(Loss) |
| simdjson (ondemand) | 280.058 | 0.897339 | 187.929ms | 233995 | 30 | 1.53374e+09 | 796816 | 10.852 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4805.71 | 0.683877 | 11.6566ms | 233995 | 30 | 3.02535e+06 | 46435.4 | 0.631593 | 1(Win) |
| glaze | 4402.32 | 0.474254 | 12.7781ms | 233995 | 30 | 1.73377e+06 | 50690.3 | 0.689957 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2105.06 | 1.58865 | 39.9581ms | 346753 | 30 | 1.86849e+08 | 157093 | 1.44348 | 1(Win) |
| jsonifier | 1550.95 | 2.44536 | 51.4555ms | 346753 | 30 | 8.15561e+08 | 213218 | 1.95914 | 2(Loss) |
| simdjson (ondemand) | 417.868 | 0.497477 | 190.531ms | 346753 | 30 | 4.64975e+08 | 791372 | 7.27306 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5071.18 | 0.77759 | 17.5894ms | 346753 | 30 | 7.71338e+06 | 65209.5 | 0.598875 | 1(Win) |
| glaze | 4044.26 | 1.2176 | 20.0348ms | 346753 | 30 | 2.97365e+07 | 81767.6 | 0.750593 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1306.88 | 0.516148 | 17.3132ms | 94651 | 30 | 3.81283e+06 | 69069.9 | 2.32403 | 1(Win) |
| glaze | 1286.32 | 0.58897 | 17.0578ms | 94651 | 30 | 5.12457e+06 | 70173.8 | 2.36178 | 2(Loss) |
| simdjson (ondemand) | 1248.63 | 1.31747 | 18.2672ms | 94651 | 30 | 2.72139e+07 | 72292.5 | 2.43298 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 5734.98 | 1.29826 | 4.12885ms | 94651 | 30 | 1.25265e+06 | 15739.6 | 0.528873 | 1(Tie) |
| jsonifier STATISTICAL TIE | 5558.58 | 1.292 | 4.2793ms | 94651 | 30 | 1.32059e+06 | 16239.1 | 0.545383 | 1(Tie) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1668.16 | 1.2427 | 45.601ms | 136024 | 32 | 2.98838e+07 | 77763.7 | 1.82108 | 1(Win) |
| glaze | 1489.9 | 0.701264 | 21.1514ms | 136024 | 30 | 1.11842e+07 | 87068.2 | 2.03861 | 2(Loss) |
| jsonifier | 1193.47 | 0.730439 | 26.636ms | 136024 | 30 | 1.89103e+07 | 108694 | 2.54588 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6508.4 | 2.17646 | 99.352ms | 136024 | 256 | 4.81753e+07 | 19931.6 | 0.46614 | 1(Win) |
| glaze | 5474.74 | 0.967851 | 6.17386ms | 136046 | 30 | 1.57827e+06 | 23698.6 | 0.554419 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 787.06 | 0.244479 | 607.239ms | 2090234 | 30 | 1.15021e+09 | 2.53272e+06 | 3.86119 | 1(Win) |
| simdjson (ondemand) | 760.221 | 0.246929 | 643.745ms | 2090234 | 30 | 1.25769e+09 | 2.62213e+06 | 3.9973 | 2(Loss) |
| glaze | 667.262 | 1.95517 | 689.312ms | 2090234 | 30 | 1.0235e+11 | 2.98744e+06 | 4.55421 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1524.7 | 1.20247 | 314.689ms | 2090234 | 30 | 7.4147e+09 | 1.30741e+06 | 1.99282 | 1(Win) |
| glaze | 1329.87 | 1.31871 | 355.385ms | 2090234 | 30 | 1.17216e+10 | 1.49894e+06 | 2.28479 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2121.95 | 0.970392 | 705.163ms | 6661897 | 30 | 2.53245e+10 | 2.99408e+06 | 1.43213 | 1(Win) |
| jsonifier | 1850.87 | 1.31914 | 822.067ms | 6661897 | 30 | 6.15098e+10 | 3.43258e+06 | 1.6419 | 2(Loss) |
| glaze | 1662.14 | 1.22225 | 919.073ms | 6661897 | 30 | 6.54785e+10 | 3.82235e+06 | 1.82837 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3102.29 | 0.482593 | 511.812ms | 6661897 | 30 | 2.93032e+09 | 2.04793e+06 | 0.979428 | 1(Win) |
| jsonifier | 3037.87 | 0.435681 | 506.973ms | 6661897 | 30 | 2.49066e+09 | 2.09136e+06 | 1.00024 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1876.79 | 0.274356 | 61.8782ms | 500299 | 30 | 1.45942e+07 | 254223 | 1.61926 | 1(Win) |
| glaze | 1788.86 | 0.429781 | 64.5157ms | 500299 | 30 | 3.94207e+07 | 266719 | 1.69886 | 2(Loss) |
| simdjson (ondemand) | 1152.83 | 0.438846 | 521.012ms | 500299 | 64 | 2.11123e+08 | 413872 | 2.636 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 5460.21 | 0.494945 | 22.3958ms | 500299 | 30 | 5.61145e+06 | 87381.6 | 0.556266 | 1(Tie) |
| glaze STATISTICAL TIE | 5265.89 | 1.7584 | 52.8896ms | 500299 | 32 | 8.12269e+07 | 90606.2 | 0.576604 | 1(Tie) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2919.94 | 0.491728 | 112.032ms | 1439562 | 30 | 1.60356e+08 | 470172 | 1.04068 | 1(Win) |
| jsonifier | 2855.76 | 0.688477 | 116.905ms | 1439562 | 30 | 3.28638e+08 | 480738 | 1.06411 | 2(Loss) |
| glaze | 2794.27 | 0.694646 | 120.985ms | 1439562 | 30 | 3.4944e+08 | 491317 | 1.08752 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7075.53 | 1.42502 | 48.4611ms | 1439562 | 30 | 2.29354e+08 | 194031 | 0.429133 | 1(Win) |
| glaze | 4623.93 | 2.25455 | 167.215ms | 1439584 | 32 | 1.43391e+09 | 296911 | 0.656907 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1910.41 | 0.0407213 | 7.50247ms | 56369 | 30 | 3939.07 | 28139.4 | 1.58934 | 1(Win) |
| glaze | 1742.99 | 0.554758 | 7.57398ms | 56369 | 30 | 878257 | 30842.3 | 1.74203 | 2(Loss) |
| simdjson (ondemand) | 1269.41 | 1.1812 | 10.9826ms | 56369 | 30 | 7.50662e+06 | 42348.5 | 2.3926 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6364.16 | 0.517355 | 2.34076ms | 56369 | 30 | 57292.3 | 8446.93 | 0.475931 | 1(Win) |
| jsonifier | 5413.88 | 0.141154 | 2.81796ms | 56369 | 30 | 5893.49 | 9929.6 | 0.557559 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2308.98 | 0.89005 | 9.73028ms | 94370 | 30 | 3.61058e+06 | 38977.5 | 1.31528 | 1(Win) |
| simdjson (ondemand) | 2070.16 | 0.772471 | 32.7539ms | 94370 | 32 | 3.6089e+06 | 43474.1 | 1.46712 | 2(Loss) |
| jsonifier | 1851.4 | 1.38957 | 12.3505ms | 94370 | 30 | 1.36883e+07 | 48611 | 1.64066 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7095.96 | 0.0482517 | 3.56975ms | 94370 | 30 | 1123.55 | 12683 | 0.427508 | 1(Win) |
| glaze | 5387.78 | 1.57164 | 44.8035ms | 94370 | 128 | 8.82198e+06 | 16704.2 | 0.563012 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1637.56 | 1.51074 | 7.9279ms | 52708 | 30 | 6.45148e+06 | 30695.9 | 1.85415 | 1(Win) |
| jsonifier | 1466.8 | 1.14556 | 8.91875ms | 52708 | 30 | 4.62348e+06 | 34269.4 | 2.07013 | 2(Loss) |
| glaze | 1289.68 | 1.59849 | 9.95347ms | 52708 | 30 | 1.16448e+07 | 38975.8 | 2.35458 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 7201.09 | 0.694804 | 2.35282ms | 52708 | 30 | 70567.1 | 6980.37 | 0.420173 | 1(Win) |
| jsonifier | 6049.18 | 2.36998 | 5.11747ms | 52708 | 32 | 1.24107e+06 | 8309.59 | 0.498064 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2220.3 | 1.25836 | 7.98568ms | 70103 | 30 | 4.30703e+06 | 30111 | 1.36742 | 1(Win) |
| glaze | 1568.04 | 1.5838 | 10.7455ms | 70103 | 30 | 1.36798e+07 | 42636.3 | 1.93672 | 2(Loss) |
| jsonifier | 1319.57 | 0.954132 | 14.3694ms | 70103 | 30 | 7.01051e+06 | 50664.7 | 2.30198 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6393.73 | 0.143205 | 3.01104ms | 70103 | 30 | 6726.73 | 10456.4 | 0.4719 | 1(Win) |
| glaze | 5693.5 | 0.864709 | 28.8169ms | 70103 | 128 | 1.31967e+06 | 11742.4 | 0.532254 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1529.28 | 0.901973 | 2.13676ms | 11812 | 30 | 132429 | 7366.1 | 1.98118 | 1(Win) |
| glaze | 1378.28 | 0.136903 | 5.08258ms | 11812 | 32 | 4006.35 | 8173.09 | 2.19789 | 2(Loss) |
| simdjson (ondemand) | 1085.94 | 0.791009 | 2.87127ms | 11812 | 30 | 201986 | 10373.3 | 2.79178 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5936.56 | 0.518101 | 1.47659ms | 11812 | 32 | 3092.84 | 1897.53 | 0.501511 | 1(Win) |
| glaze | 4738.22 | 0.167615 | 1.05039ms | 11812 | 30 | 476.392 | 2377.43 | 0.63313 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2682.6 | 1.93008 | 6.66893ms | 31235 | 32 | 1.46984e+06 | 11104.2 | 1.13029 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2631.67 | 0.0630222 | 3.12765ms | 31235 | 30 | 1526.62 | 11319.1 | 1.15229 | 1(Tie) |
| glaze | 2214.28 | 2.10042 | 3.57944ms | 31235 | 30 | 2.39524e+06 | 13452.7 | 1.3697 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8222.6 | 0.120585 | 1.26283ms | 31235 | 30 | 572.493 | 3622.7 | 0.362864 | 1(Win) |
| glaze | 6706.34 | 0.214385 | 1.51199ms | 31235 | 30 | 2720.32 | 4441.77 | 0.450054 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3717.62 | 0.186266 | 16.7821ms | 108313 | 32 | 85713 | 27785.3 | 0.816685 | 1(Win) |
| glaze | 2142.41 | 1.20443 | 12.3319ms | 108313 | 30 | 1.01167e+07 | 48214.5 | 1.41778 | 2(Loss) |
| simdjson (ondemand) | 1612.67 | 1.81664 | 15.8654ms | 108313 | 30 | 4.06189e+07 | 64052.4 | 1.88377 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6582.9 | 0.0849721 | 4.22677ms | 108313 | 30 | 5333.36 | 15691.5 | 0.460371 | 1(Win) |
| glaze | 5816.66 | 1.03481 | 4.67788ms | 108313 | 30 | 1.0131e+06 | 17758.5 | 0.521531 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2960.21 | 0.752926 | 16.9617ms | 213963 | 30 | 8.08087e+06 | 68931.2 | 1.02625 | 1(Win) |
| glaze | 2843.51 | 0.96168 | 17.7936ms | 213963 | 30 | 1.42873e+07 | 71760.2 | 1.06843 | 2(Loss) |
| jsonifier | 2328.65 | 0.889748 | 23.4401ms | 213963 | 30 | 1.82358e+07 | 87626.4 | 1.30471 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8453.89 | 0.0750555 | 6.30405ms | 213963 | 30 | 9845.79 | 24136.9 | 0.358759 | 1(Win) |
| glaze | 5857.73 | 0.928235 | 9.04076ms | 213963 | 30 | 3.13658e+06 | 34834.5 | 0.518411 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 805.5 | 0.299421 | 528.504ms | 1834197 | 30 | 1.26837e+09 | 2.1716e+06 | 3.77242 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 587.778 | 0.288747 | 716.589ms | 1834197 | 30 | 2.21524e+09 | 2.976e+06 | 5.16989 | 2(Tie) |
| glaze STATISTICAL TIE | 578.253 | 1.20708 | 708.051ms | 1834197 | 30 | 3.99987e+10 | 3.02502e+06 | 5.25523 | 2(Tie) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1007.13 | 0.256455 | 416.649ms | 1834197 | 30 | 5.95207e+08 | 1.73685e+06 | 3.01714 | 1(Win) |
| glaze | 923.357 | 0.672478 | 458.73ms | 1833577 | 30 | 4.8656e+09 | 1.89378e+06 | 3.29087 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2744.4 | 0.382356 | 821.44ms | 9930848 | 30 | 5.22317e+09 | 3.45095e+06 | 1.10728 | 1(Win) |
| glaze | 2441.79 | 0.230014 | 929.309ms | 9930848 | 30 | 2.38774e+09 | 3.87863e+06 | 1.24454 | 2(Loss) |
| jsonifier | 2346.99 | 0.359808 | 974.463ms | 9930848 | 30 | 6.32429e+09 | 4.03529e+06 | 1.29482 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2583.27 | 2.33022 | 821.118ms | 9930848 | 30 | 2.18953e+11 | 3.66621e+06 | 1.1761 | 1(Win) |
| glaze | 2024.65 | 1.42698 | 1050.32ms | 9930228 | 30 | 1.33652e+11 | 4.67745e+06 | 1.50064 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1409.72 | 0.288679 | 105.651ms | 642697 | 30 | 4.72605e+07 | 434783 | 2.1557 | 1(Win) |
| simdjson (ondemand) | 1174.22 | 0.545424 | 125.239ms | 642697 | 30 | 2.43168e+08 | 521985 | 2.58795 | 2(Loss) |
| glaze | 1049.66 | 0.560211 | 139.925ms | 642697 | 30 | 3.21028e+08 | 583928 | 2.89519 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1642.89 | 0.323209 | 90.3613ms | 642697 | 30 | 4.36197e+07 | 373076 | 1.84963 | 1(Win) |
| glaze | 1416.84 | 0.791253 | 103.813ms | 642692 | 30 | 3.51493e+08 | 432596 | 2.14405 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2208.3 | 0.591669 | 129.496ms | 1225964 | 30 | 2.94388e+08 | 529444 | 1.37599 | 1(Win) |
| glaze | 1784.06 | 0.3277 | 157.834ms | 1225964 | 30 | 1.38359e+08 | 655341 | 1.70326 | 2(Loss) |
| jsonifier | 1641.37 | 0.628794 | 169.601ms | 1225964 | 30 | 6.01838e+08 | 712313 | 1.8511 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2553.14 | 0.609955 | 110.335ms | 1225964 | 30 | 2.34058e+08 | 457935 | 1.18995 | 1(Win) |
| glaze | 2129.16 | 1.26758 | 129.443ms | 1225970 | 30 | 1.45349e+09 | 549126 | 1.42677 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1142.1 | 0.387021 | 83.4072ms | 409725 | 30 | 5.25982e+07 | 342129 | 2.66074 | 1(Win) |
| simdjson (ondemand) | 964.116 | 0.717904 | 98.3656ms | 409725 | 30 | 2.53969e+08 | 405288 | 3.15177 | 2(Loss) |
| glaze | 914.305 | 0.4768 | 104.137ms | 409725 | 30 | 1.24565e+08 | 427368 | 3.32377 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4343.26 | 2.46543 | 21.6991ms | 409725 | 30 | 1.4759e+08 | 89965.6 | 0.699149 | 1(Win) |
| glaze | 3589.44 | 1.19032 | 28.0625ms | 409725 | 30 | 5.03712e+07 | 108859 | 0.846269 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1750.29 | 0.410249 | 103.976ms | 785750 | 30 | 9.25472e+07 | 428128 | 1.73605 | 1(Win) |
| glaze | 1383.62 | 0.90057 | 129.078ms | 785750 | 30 | 7.13661e+08 | 541587 | 2.19613 | 2(Loss) |
| jsonifier | 1170.5 | 0.963508 | 152.625ms | 785750 | 30 | 1.14146e+09 | 640197 | 2.59599 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5481.37 | 0.622349 | 34.4413ms | 785750 | 30 | 2.1716e+07 | 136708 | 0.554091 | 1(Win) |
| glaze | 3740.77 | 2.09838 | 46.8125ms | 785750 | 30 | 5.30076e+08 | 200320 | 0.812116 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1306.59 | 0.283185 | 1543.99ms | 8587914 | 30 | 9.45277e+09 | 6.26828e+06 | 2.32592 | 1(Win) |
| simdjson (ondemand) | 1224.28 | 0.270076 | 1665.77ms | 8587914 | 30 | 9.79281e+09 | 6.6897e+06 | 2.48219 | 2(Loss) |
| glaze | 1135.14 | 1.32325 | 1684.7ms | 8587914 | 30 | 2.7345e+11 | 7.21501e+06 | 2.6772 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3412.62 | 1.08148 | 578.295ms | 8588126 | 30 | 2.02105e+10 | 2.4e+06 | 0.89022 | 1(Win) |
| glaze | 2979.54 | 0.502099 | 666.471ms | 8588126 | 30 | 5.71476e+09 | 2.74884e+06 | 1.01962 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1248.24 | 1.45672 | 1767.26ms | 9804437 | 30 | 3.57212e+11 | 7.49074e+06 | 2.43454 | 1(Win) |
| glaze | 1193.81 | 0.475276 | 1882.68ms | 9804437 | 30 | 4.15709e+10 | 7.83229e+06 | 2.54566 | 2(Loss) |
| jsonifier | 1168.72 | 0.368644 | 1973.7ms | 9804437 | 30 | 2.60951e+10 | 8.00039e+06 | 2.60028 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3190.61 | 1.56936 | 826.55ms | 11078090 | 30 | 8.10113e+10 | 3.31124e+06 | 0.952102 | 1(Win) |
| glaze | 2506.93 | 1.0392 | 999.601ms | 11078090 | 30 | 5.75392e+10 | 4.21427e+06 | 1.21185 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 5387.53 | 0.487251 | 11.8305ms | 264040 | 30 | 1.55592e+06 | 46739 | 0.563822 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 5329.49 | 0.572282 | 11.8157ms | 264040 | 30 | 2.19336e+06 | 47248.1 | 0.569976 | 1(Tie) |
| glaze | 2023.15 | 0.480996 | 30.5893ms | 264040 | 30 | 1.07519e+07 | 124463 | 1.50191 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 6899.9 | 0.562439 | 14.0628ms | 399947 | 30 | 2.89996e+06 | 55279 | 0.440277 | 1(Tie) |
| jsonifier STATISTICAL TIE | 6852.81 | 0.462726 | 14.8408ms | 399947 | 30 | 1.98993e+06 | 55658.8 | 0.443288 | 1(Tie) |
| glaze | 2618.68 | 0.545544 | 35.9774ms | 399947 | 30 | 1.89419e+07 | 145653 | 1.16038 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1714.74 | 0.360818 | 390.625ms | 264040 | 128 | 3.59358e+07 | 146849 | 1.77201 | 1(Win) |
| simdjson (ondemand) | 1631.39 | 0.659407 | 38.1699ms | 264040 | 30 | 3.10782e+07 | 154352 | 1.86264 | 2(Loss) |
| glaze | 1506.83 | 1.00806 | 41.2583ms | 264040 | 30 | 8.51348e+07 | 167111 | 2.01643 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6384.82 | 1.11511 | 10.5403ms | 263923 | 30 | 5.79713e+06 | 39421.1 | 0.475578 | 1(Win) |
| jsonifier | 5792.2 | 2.00008 | 11.2748ms | 264040 | 30 | 2.26813e+07 | 43473.6 | 0.524091 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2265.08 | 1.46294 | 40.9149ms | 399947 | 30 | 1.82061e+08 | 168391 | 1.34148 | 1(Win) |
| glaze | 1815.73 | 2.3819 | 49.0899ms | 399947 | 30 | 7.51055e+08 | 210064 | 1.6733 | 2(Loss) |
| jsonifier | 1428.66 | 0.929138 | 65.013ms | 399947 | 30 | 1.846e+08 | 266978 | 2.12687 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6613.13 | 0.635922 | 14.4908ms | 399947 | 30 | 4.03572e+06 | 57676.1 | 0.459336 | 1(Win) |
| glaze | 5324.88 | 0.656338 | 389.803ms | 399830 | 256 | 5.65492e+07 | 71608.7 | 0.570425 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2369.09 | 0.510513 | 45.6869ms | 466906 | 30 | 2.76205e+07 | 187953 | 1.28269 | 1(Win) |
| jsonifier | 2264.71 | 0.908493 | 47.5365ms | 466906 | 30 | 9.57194e+07 | 196616 | 1.34169 | 2(Loss) |
| simdjson (ondemand) | 1230.21 | 1.94073 | 83.5178ms | 466906 | 30 | 1.48032e+09 | 361953 | 2.46882 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3593.21 | 1.10327 | 46.5156ms | 699405 | 30 | 1.25827e+08 | 185629 | 0.845699 | 1(Win) |
| jsonifier | 3199.74 | 1.96217 | 113.758ms | 699405 | 32 | 5.35366e+08 | 208456 | 0.949333 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3898.93 | 1.43624 | 37.4106ms | 631514 | 30 | 1.47656e+08 | 154468 | 0.779212 | 1(Win) |
| glaze | 2568.53 | 0.397199 | 56.5072ms | 631514 | 30 | 2.60216e+07 | 234476 | 1.18315 | 2(Loss) |
