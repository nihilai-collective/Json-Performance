# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

Latest Results: (Sep 15, 2026)
#### Using the following commits:
----
| Jsonifier: [4d272c2](https://github.com/nihilai-collective/jsonifier/commit/4d272c2)  
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
| jsonifier | 544.885 | 0.104235 | 1.96578ms | 1811 | 30 | 327.471 | 3169.67 | 4.23081 | 1(Win) |
| glaze | 493.684 | 0.0922393 | 1.11609ms | 1811 | 30 | 312.386 | 3498.4 | 4.67272 | 2(Loss) |
| simdjson (ondemand) | 137.466 | 0.199295 | 3.21529ms | 1811 | 30 | 18808.7 | 12563.9 | 16.9132 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 366.647 | 0.0954111 | 1.38408ms | 1811 | 30 | 605.982 | 4710.53 | 6.31001 | 1(Win) |
| glaze | 270.616 | 0.337909 | 1.77346ms | 1798 | 30 | 13752.8 | 6336.3 | 8.56774 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1322.76 | 0.100977 | 1.001ms | 3873 | 30 | 238.506 | 2792.33 | 1.73963 | 1(Win) |
| glaze | 999.413 | 0.0775569 | 2.39818ms | 3873 | 32 | 262.903 | 3695.75 | 2.30914 | 2(Loss) |
| simdjson (ondemand) | 346.178 | 0.0525202 | 2.76484ms | 3873 | 30 | 942.041 | 10669.6 | 6.71462 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1457.74 | 0.101387 | 0.873006ms | 3873 | 30 | 197.978 | 2533.77 | 1.57662 | 1(Win) |
| glaze | 1004.92 | 0.160503 | 1.10834ms | 3873 | 30 | 1044.05 | 3675.5 | 2.29736 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1324.31 | 0.0870183 | 0.931817ms | 3862 | 30 | 175.706 | 2781.13 | 1.73715 | 1(Win) |
| glaze | 813.805 | 0.101514 | 1.28608ms | 3862 | 30 | 633.22 | 4525.77 | 2.84142 | 2(Loss) |
| simdjson (ondemand) | 348.27 | 0.261691 | 6.22892ms | 3862 | 32 | 24508.6 | 10575.4 | 6.67294 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1598.42 | 0.1172 | 0.82688ms | 3862 | 30 | 218.786 | 2304.2 | 1.43689 | 1(Win) |
| glaze | 1046.65 | 0.290157 | 1.05364ms | 3862 | 30 | 3127.58 | 3518.93 | 2.20508 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 544.435 | 0.0481962 | 0.614532ms | 905 | 30 | 17.5126 | 1585.27 | 4.1835 | 1(Win) |
| glaze | 275.025 | 0.0626618 | 0.919984ms | 905 | 30 | 116.006 | 3138.17 | 8.3607 | 2(Loss) |
| simdjson (ondemand) | 115.208 | 0.375665 | 1.98489ms | 905 | 30 | 23760.3 | 7491.43 | 20.1467 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 699.753 | 0.260091 | 0.516277ms | 905 | 30 | 308.731 | 1233.4 | 3.23602 | 1(Win) |
| glaze | 282.383 | 0.207116 | 0.936605ms | 905 | 30 | 1202.18 | 3056.4 | 8.15499 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1805.51 | 0.0646031 | 1.54527ms | 9578 | 30 | 320.464 | 5059.13 | 1.28186 | 1(Win) |
| glaze | 1433.41 | 0.10828 | 1.73637ms | 9578 | 30 | 1428.32 | 6372.4 | 1.6174 | 2(Loss) |
| simdjson (ondemand) | 756.655 | 2.4334 | 3.02484ms | 9578 | 30 | 2.58883e+06 | 12071.9 | 3.07217 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3282.65 | 0.132213 | 0.968626ms | 9578 | 30 | 406.041 | 2782.6 | 0.700606 | 1(Win) |
| glaze | 2148.57 | 0.654382 | 1.19741ms | 9578 | 30 | 23218.5 | 4251.33 | 1.07553 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 2757.22 | 0.599389 | 19.7967ms | 233995 | 30 | 7.06009e+06 | 80934.9 | 0.84538 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2751.72 | 1.31693 | 19.8394ms | 233995 | 30 | 3.4218e+07 | 81096.7 | 0.847058 | 1(Tie) |
| glaze | 1458.84 | 0.573 | 36.9216ms | 233995 | 30 | 2.30479e+07 | 152968 | 1.59814 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 3451.05 | 1.0596 | 23.2013ms | 346753 | 30 | 3.09275e+07 | 95823 | 0.675386 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3398.02 | 0.626918 | 23.5712ms | 346753 | 30 | 1.11668e+07 | 97318.2 | 0.685945 | 1(Tie) |
| glaze | 1760.62 | 0.746311 | 45.4241ms | 346753 | 30 | 5.8948e+07 | 187825 | 1.32421 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1269.1 | 0.482255 | 43.235ms | 233995 | 30 | 2.15724e+07 | 175838 | 1.83711 | 1(Win) |
| glaze | 914.926 | 0.477935 | 59.0179ms | 233995 | 30 | 4.07662e+07 | 243905 | 2.54841 | 2(Loss) |
| simdjson (ondemand) | 835.192 | 0.64771 | 64.2493ms | 233995 | 30 | 8.98509e+07 | 267190 | 2.7917 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1911.75 | 0.559089 | 28.5231ms | 233995 | 30 | 1.27772e+07 | 116728 | 1.21933 | 1(Tie) |
| glaze STATISTICAL TIE | 1883.2 | 1.16287 | 28.4647ms | 233995 | 30 | 5.69648e+07 | 118498 | 1.23774 | 1(Tie) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1259.37 | 0.713511 | 63.1159ms | 346753 | 30 | 1.05306e+08 | 262582 | 1.85136 | 1(Win) |
| glaze | 1207.14 | 0.431803 | 66.7971ms | 346753 | 30 | 4.19773e+07 | 273944 | 1.93146 | 2(Loss) |
| simdjson (ondemand) | 1177.97 | 0.661765 | 68.022ms | 346753 | 30 | 1.03538e+08 | 280728 | 1.97931 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2101.25 | 0.577671 | 38.2895ms | 346753 | 30 | 2.47952e+07 | 157378 | 1.10943 | 1(Win) |
| glaze | 1683.93 | 0.64045 | 47.5618ms | 346753 | 30 | 4.74553e+07 | 196380 | 1.3845 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2708.62 | 0.595178 | 20.256ms | 233995 | 30 | 7.21326e+06 | 82387 | 0.86054 | 1(Win) |
| simdjson (ondemand) | 1875.28 | 0.448298 | 28.8793ms | 233995 | 30 | 8.53765e+06 | 118999 | 1.24324 | 2(Loss) |
| glaze | 1488.7 | 0.540693 | 36.2238ms | 233995 | 30 | 1.97071e+07 | 149899 | 1.56613 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3449.5 | 0.468554 | 23.4211ms | 346753 | 30 | 6.05298e+06 | 95866 | 0.675624 | 1(Win) |
| simdjson (ondemand) | 2450.97 | 0.811471 | 32.6294ms | 346753 | 30 | 3.59612e+07 | 134922 | 0.951174 | 2(Loss) |
| glaze | 1848.47 | 0.537736 | 43.2613ms | 346753 | 30 | 2.77635e+07 | 178899 | 1.26133 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1145.32 | 0.582378 | 47.5005ms | 233995 | 30 | 3.86269e+07 | 194841 | 2.0356 | 1(Win) |
| glaze | 952.461 | 0.504879 | 57.0085ms | 233995 | 30 | 4.19773e+07 | 234293 | 2.44808 | 2(Loss) |
| simdjson (ondemand) | 240.189 | 0.160645 | 223.649ms | 233995 | 30 | 6.68281e+07 | 929079 | 9.70876 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2232.59 | 0.910922 | 24.1197ms | 233995 | 30 | 2.48703e+07 | 99953.6 | 1.04405 | 1(Win) |
| glaze | 1999.3 | 0.837151 | 26.9743ms | 233995 | 30 | 2.6193e+07 | 111616 | 1.16591 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1272.94 | 0.503316 | 62.8751ms | 346753 | 30 | 5.1289e+07 | 259783 | 1.83136 | 1(Win) |
| glaze | 1225.94 | 0.553485 | 65.7169ms | 346753 | 30 | 6.68712e+07 | 269745 | 1.90196 | 2(Loss) |
| simdjson (ondemand) | 348.984 | 0.119565 | 228.258ms | 346753 | 30 | 3.85089e+07 | 947579 | 6.68213 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2137.75 | 0.757227 | 37.457ms | 346753 | 30 | 4.11623e+07 | 154690 | 1.09048 | 1(Win) |
| glaze | 1668.87 | 0.608264 | 47.981ms | 346753 | 30 | 4.35814e+07 | 198152 | 1.39699 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 657.073 | 0.639904 | 33.3344ms | 94651 | 30 | 2.31833e+07 | 137376 | 3.54776 | 1(Win) |
| jsonifier | 642.537 | 0.641589 | 34.0844ms | 94651 | 30 | 2.4372e+07 | 140484 | 3.61984 | 2(Loss) |
| glaze | 585.597 | 0.582879 | 37.7642ms | 94651 | 30 | 2.42176e+07 | 154144 | 3.98079 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2747.07 | 2.21651 | 8.04135ms | 94651 | 30 | 1.59137e+07 | 32859.1 | 0.847876 | 1(Win) |
| glaze | 2595.76 | 1.57449 | 8.52709ms | 94651 | 30 | 8.99334e+06 | 34774.5 | 0.897004 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 909.616 | 0.755899 | 34.6469ms | 136024 | 30 | 3.48629e+07 | 142612 | 2.56258 | 1(Win) |
| jsonifier | 725.482 | 0.707391 | 43.1197ms | 136024 | 30 | 4.79975e+07 | 178809 | 3.21308 | 2(Loss) |
| glaze | 702.707 | 0.610336 | 44.679ms | 136024 | 30 | 3.80839e+07 | 184604 | 3.31752 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3236.02 | 1.64256 | 9.79738ms | 136024 | 30 | 1.30069e+07 | 40087.1 | 0.719753 | 1(Win) |
| glaze | 1683.83 | 2.34199 | 18.0272ms | 136046 | 30 | 9.76937e+07 | 77052.7 | 1.3839 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 394.073 | 0.0761861 | 1214.34ms | 2090234 | 30 | 4.45564e+08 | 5.05846e+06 | 5.91792 | 1(Win) |
| glaze | 372.002 | 0.11241 | 1285.34ms | 2090234 | 30 | 1.0885e+09 | 5.35858e+06 | 6.26903 | 2(Loss) |
| simdjson (ondemand) | 301.372 | 0.0530072 | 1588.58ms | 2090234 | 30 | 3.68785e+08 | 6.61442e+06 | 7.73827 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 678.184 | 0.0488435 | 706.157ms | 2090234 | 30 | 6.18343e+07 | 2.93932e+06 | 3.4387 | 1(Win) |
| glaze | 642.364 | 0.10101 | 746.414ms | 2090234 | 30 | 2.94765e+08 | 3.10323e+06 | 3.63046 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1170.45 | 0.114882 | 1303.76ms | 6661897 | 30 | 1.16657e+09 | 5.42806e+06 | 1.99247 | 1(Win) |
| simdjson (ondemand) | 904.085 | 0.154148 | 1685.4ms | 6661897 | 30 | 3.52026e+09 | 7.0273e+06 | 2.5795 | 2(Loss) |
| glaze | 897.544 | 0.119193 | 1697.61ms | 6661897 | 30 | 2.13554e+09 | 7.07852e+06 | 2.59831 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1935.97 | 0.110007 | 795.988ms | 6661897 | 30 | 3.90984e+08 | 3.2817e+06 | 1.20459 | 1(Win) |
| glaze | 1513.23 | 0.188426 | 1022.54ms | 6661897 | 30 | 1.87754e+09 | 4.1985e+06 | 1.54113 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1013.67 | 0.213261 | 113.504ms | 500299 | 30 | 3.02281e+07 | 470689 | 2.3004 | 1(Win) |
| glaze | 814.042 | 0.35016 | 140.75ms | 500299 | 30 | 1.26363e+08 | 586115 | 2.8646 | 2(Loss) |
| simdjson (ondemand) | 505.83 | 0.175476 | 226.558ms | 500299 | 30 | 8.21876e+07 | 943246 | 4.61015 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2026.99 | 0.548786 | 56.9298ms | 500299 | 30 | 5.00589e+07 | 235384 | 1.15023 | 1(Win) |
| jsonifier | 1836.04 | 0.416064 | 62.7386ms | 500299 | 30 | 3.50701e+07 | 259865 | 1.26992 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1792.17 | 0.875559 | 181.219ms | 1439562 | 30 | 1.34956e+09 | 766038 | 1.30109 | 1(Win) |
| glaze | 1529.22 | 0.244922 | 214.486ms | 1439562 | 30 | 1.45044e+08 | 897763 | 1.52492 | 2(Loss) |
| simdjson (ondemand) | 1320.68 | 0.14614 | 250.15ms | 1439562 | 30 | 6.92351e+07 | 1.03952e+06 | 1.76575 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3329.92 | 0.351172 | 99.9451ms | 1439562 | 30 | 6.28862e+07 | 412285 | 0.700231 | 1(Win) |
| glaze | 2160.02 | 0.30924 | 155.288ms | 1439584 | 30 | 1.15897e+08 | 635592 | 1.07957 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 837.412 | 1.36644 | 15.9753ms | 56369 | 30 | 2.30837e+07 | 64195 | 2.78231 | 1(Win) |
| glaze | 775.361 | 1.15425 | 17.0171ms | 56369 | 30 | 1.92129e+07 | 69332.4 | 3.00601 | 2(Loss) |
| simdjson (ondemand) | 691.116 | 0.573124 | 19.5527ms | 56369 | 30 | 5.96207e+06 | 77783.8 | 3.37237 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1983.87 | 1.45923 | 6.79335ms | 56369 | 30 | 4.69056e+06 | 27097.4 | 1.17384 | 1(Win) |
| jsonifier | 1655.04 | 1.76841 | 8.08864ms | 56369 | 30 | 9.89798e+06 | 32481.1 | 1.40747 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1068.26 | 1.03123 | 20.5509ms | 94370 | 30 | 2.26439e+07 | 84247.8 | 2.18182 | 1(Win) |
| glaze STATISTICAL TIE | 1021.96 | 1.20678 | 21.522ms | 94370 | 30 | 3.38826e+07 | 88064.4 | 2.28079 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1001.16 | 1.2728 | 22.0752ms | 94370 | 30 | 3.92738e+07 | 89894.2 | 2.32763 | 2(Tie) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2402.63 | 0.933888 | 9.23805ms | 94370 | 30 | 3.67117e+06 | 37458.2 | 0.969762 | 1(Win) |
| glaze | 1746.38 | 0.599991 | 12.7835ms | 94370 | 30 | 2.86815e+06 | 51534.2 | 1.33386 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 842.181 | 0.860553 | 14.8215ms | 52708 | 30 | 7.91442e+06 | 59685.8 | 2.76683 | 1(Win) |
| jsonifier | 763.869 | 0.99928 | 16.7112ms | 52708 | 30 | 1.29721e+07 | 65804.8 | 3.04756 | 2(Loss) |
| glaze | 698.691 | 0.797657 | 18.0413ms | 52708 | 30 | 9.87955e+06 | 71943.5 | 3.33517 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2740.9 | 0.159203 | 10.9553ms | 52708 | 32 | 27278.4 | 18339.3 | 0.848872 | 1(Win) |
| jsonifier | 2597.56 | 0.168403 | 11.5484ms | 52708 | 32 | 33983.5 | 19351.3 | 0.896037 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1087.16 | 1.05906 | 15.2428ms | 70103 | 30 | 1.27248e+07 | 61495.4 | 2.14292 | 1(Win) |
| glaze | 767.718 | 1.48129 | 21.1649ms | 70103 | 30 | 4.99194e+07 | 87083.3 | 3.03548 | 2(Loss) |
| jsonifier | 689.092 | 1.38913 | 24.3028ms | 70103 | 30 | 5.44909e+07 | 97019.6 | 3.381 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2898.2 | 1.82781 | 5.93307ms | 70103 | 30 | 5.33337e+06 | 23067.9 | 0.802851 | 1(Win) |
| glaze | 2448.71 | 1.14492 | 7.02381ms | 70103 | 30 | 2.93138e+06 | 27302.3 | 0.951053 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 708.556 | 2.21798 | 9.3277ms | 11812 | 32 | 3.97889e+06 | 15898.2 | 3.28386 | 1(Win) |
| glaze | 587.81 | 0.239838 | 11.394ms | 11812 | 32 | 67602.2 | 19164 | 3.96015 | 2(Loss) |
| simdjson (ondemand) | 554.671 | 1.57443 | 5.17243ms | 11812 | 30 | 3.06721e+06 | 20309 | 4.19714 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2483.37 | 0.239806 | 1.36986ms | 11812 | 30 | 3549.82 | 4536.1 | 0.932063 | 1(Win) |
| glaze | 1242.95 | 0.190334 | 2.48016ms | 11812 | 30 | 8926.75 | 9062.93 | 1.8686 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1407.15 | 1.56498 | 5.41754ms | 31235 | 30 | 3.29261e+06 | 21169 | 1.6543 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1375.64 | 0.052016 | 5.56143ms | 31235 | 30 | 3806 | 21653.9 | 1.69258 | 1(Tie) |
| glaze | 1066.34 | 1.10744 | 7.07099ms | 31235 | 30 | 2.87112e+06 | 27934.7 | 2.18396 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2737.54 | 1.59999 | 2.91519ms | 31235 | 30 | 909320 | 10881.3 | 0.848875 | 1(Win) |
| glaze | 1885.5 | 0.312784 | 4.14624ms | 31235 | 30 | 73255.5 | 15798.5 | 1.23387 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1675.97 | 0.585174 | 15.4474ms | 108313 | 30 | 3.9023e+06 | 61633.3 | 1.39035 | 1(Win) |
| glaze | 1010.28 | 0.592861 | 25.0503ms | 108313 | 30 | 1.10232e+07 | 102245 | 2.30734 | 2(Loss) |
| simdjson (ondemand) | 810.308 | 0.744801 | 31.0092ms | 108313 | 30 | 2.70434e+07 | 127477 | 2.87699 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1899.15 | 1.1405 | 13.4189ms | 108313 | 30 | 1.1544e+07 | 54390.2 | 1.22715 | 1(Win) |
| glaze | 1689 | 1.11095 | 14.9946ms | 108313 | 30 | 1.38487e+07 | 61157.7 | 1.37971 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1487.55 | 0.816397 | 33.3088ms | 213963 | 30 | 3.76235e+07 | 137173 | 1.56715 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1460.63 | 0.922538 | 34.5821ms | 213963 | 30 | 4.98293e+07 | 139700 | 1.59591 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1447.51 | 0.713695 | 34.0835ms | 213963 | 30 | 3.03656e+07 | 140967 | 1.61048 | 1(Tie) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2943.53 | 1.25626 | 16.836ms | 213963 | 30 | 2.2752e+07 | 69321.9 | 0.791655 | 1(Win) |
| glaze | 1690.4 | 0.674307 | 29.2624ms | 213963 | 30 | 1.98764e+07 | 120712 | 1.37896 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 458.548 | 0.111309 | 917.102ms | 1834197 | 30 | 5.40883e+08 | 3.81471e+06 | 5.08569 | 1(Win) |
| glaze | 336.977 | 0.0913514 | 1238.69ms | 1834197 | 30 | 6.74595e+08 | 5.19094e+06 | 6.92062 | 2(Loss) |
| simdjson (ondemand) | 268.529 | 0.0867135 | 1563.94ms | 1834197 | 30 | 9.57204e+08 | 6.5141e+06 | 8.68468 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 390.531 | 0.0769358 | 1074.49ms | 1833577 | 30 | 3.56013e+08 | 4.47759e+06 | 5.97157 | 1(Win) |
| jsonifier | 389.607 | 0.0523208 | 1078.07ms | 1834197 | 30 | 1.65542e+08 | 4.48972e+06 | 5.98568 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1638.62 | 0.0557269 | 1391.36ms | 9930848 | 30 | 3.11219e+08 | 5.77972e+06 | 1.42317 | 1(Win) |
| glaze | 1371.81 | 0.0978374 | 1657.19ms | 9930848 | 30 | 1.36872e+09 | 6.90385e+06 | 1.7 | 2(Loss) |
| simdjson (ondemand) | 1321.11 | 0.0712505 | 1723.6ms | 9930848 | 30 | 7.82693e+08 | 7.16881e+06 | 1.76524 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1658 | 0.36897 | 1372.54ms | 9930848 | 30 | 1.33262e+10 | 5.71218e+06 | 1.40655 | 1(Win) |
| glaze | 1323.99 | 0.195312 | 1718.93ms | 9930228 | 30 | 5.855e+09 | 7.15276e+06 | 1.76137 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 858.609 | 0.199383 | 171.974ms | 642697 | 30 | 6.0774e+07 | 713857 | 2.71591 | 1(Win) |
| glaze | 742.995 | 0.144714 | 197.375ms | 642697 | 30 | 4.27548e+07 | 824936 | 3.13856 | 2(Loss) |
| simdjson (ondemand) | 548.582 | 0.113297 | 268.877ms | 642697 | 30 | 4.80713e+07 | 1.11729e+06 | 4.25097 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 715.708 | 0.252145 | 205.425ms | 642697 | 30 | 1.39883e+08 | 856388 | 3.2582 | 1(Win) |
| glaze | 636.121 | 0.0951701 | 231.79ms | 642692 | 30 | 2.52261e+07 | 963526 | 3.66591 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1129.36 | 0.122314 | 249.163ms | 1225964 | 30 | 4.81029e+07 | 1.03525e+06 | 2.06489 | 1(Win) |
| jsonifier | 1052.2 | 0.16295 | 267.976ms | 1225964 | 30 | 9.83527e+07 | 1.11117e+06 | 2.21624 | 2(Loss) |
| simdjson (ondemand) | 1001.43 | 0.141908 | 280.94ms | 1225964 | 30 | 8.23469e+07 | 1.1675e+06 | 2.32866 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1212.91 | 0.148197 | 231.602ms | 1225964 | 30 | 6.1221e+07 | 963942 | 1.92261 | 1(Win) |
| glaze | 1030.61 | 0.21391 | 271.859ms | 1225970 | 30 | 1.76667e+08 | 1.13445e+06 | 2.26273 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 580.636 | 0.407411 | 162.264ms | 409725 | 30 | 2.25509e+08 | 672958 | 4.01617 | 1(Win) |
| simdjson (ondemand) | 509.021 | 0.240961 | 184.21ms | 409725 | 30 | 1.02643e+08 | 767639 | 4.58128 | 2(Loss) |
| glaze | 359.32 | 0.234554 | 261.499ms | 409725 | 30 | 1.95178e+08 | 1.08746e+06 | 6.49006 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1340.23 | 0.528513 | 70.4422ms | 409725 | 30 | 7.12294e+07 | 291550 | 1.73975 | 1(Win) |
| jsonifier | 1240.76 | 0.410452 | 75.9751ms | 409725 | 30 | 5.01251e+07 | 314923 | 1.8793 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 925.821 | 0.166828 | 194.214ms | 785750 | 30 | 5.46984e+07 | 809389 | 2.51879 | 1(Win) |
| jsonifier | 781.26 | 0.165503 | 230.215ms | 785750 | 30 | 7.55979e+07 | 959155 | 2.9849 | 2(Loss) |
| glaze | 599.498 | 0.200583 | 301.729ms | 785750 | 30 | 1.88583e+08 | 1.24996e+06 | 3.88994 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1917.64 | 0.290709 | 94.1368ms | 785750 | 30 | 3.87145e+07 | 390766 | 1.2159 | 1(Win) |
| glaze | 1618.24 | 0.307328 | 111.674ms | 785750 | 30 | 6.07584e+07 | 463064 | 1.44095 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 701.007 | 0.33251 | 2796.06ms | 8587914 | 30 | 4.52751e+10 | 1.16833e+07 | 3.32674 | 1(Win) |
| simdjson (ondemand) | 657.556 | 0.848528 | 2979.88ms | 8587914 | 30 | 3.35092e+11 | 1.24553e+07 | 3.54656 | 2(Loss) |
| glaze | 592.637 | 0.189677 | 3322.22ms | 8587914 | 30 | 2.06133e+10 | 1.38197e+07 | 3.9351 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2282.65 | 0.187881 | 875.255ms | 8588126 | 30 | 1.36334e+09 | 3.58806e+06 | 1.02161 | 1(Win) |
| glaze | 2088.93 | 0.568502 | 920.379ms | 8588126 | 30 | 1.49051e+10 | 3.92081e+06 | 1.11635 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 729.439 | 0.406565 | 3081.42ms | 9804437 | 30 | 8.14797e+10 | 1.28184e+07 | 3.19706 | 1(Win) |
| jsonifier | 671.54 | 0.299207 | 3339.75ms | 9804437 | 30 | 5.20675e+10 | 1.39236e+07 | 3.47275 | 2(Loss) |
| glaze | 611.41 | 0.326781 | 3678.63ms | 9804437 | 30 | 7.4923e+10 | 1.52929e+07 | 3.81427 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2409.22 | 0.421463 | 1057.42ms | 11078090 | 30 | 1.02475e+10 | 4.38519e+06 | 0.96792 | 1(Win) |
| glaze | 2080.99 | 0.291044 | 1220.49ms | 11078090 | 30 | 6.54981e+09 | 5.07687e+06 | 1.1206 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2689.16 | 0.776116 | 53.2215ms | 264040 | 32 | 1.69009e+07 | 93638.3 | 0.866776 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2647.9 | 0.882508 | 23.281ms | 264040 | 30 | 2.11298e+07 | 95097.4 | 0.880301 | 1(Tie) |
| glaze | 1139.67 | 0.530709 | 53.5104ms | 264040 | 30 | 4.12495e+07 | 220949 | 2.04589 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 3503.41 | 0.683941 | 26.4524ms | 399947 | 30 | 1.66334e+07 | 108871 | 0.66537 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3481.57 | 0.827411 | 26.684ms | 399947 | 30 | 2.46501e+07 | 109554 | 0.669502 | 1(Tie) |
| glaze | 1525.61 | 0.882129 | 60.1416ms | 399947 | 30 | 1.45915e+08 | 250010 | 1.52829 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 969.761 | 0.630095 | 64.1515ms | 264040 | 30 | 8.03053e+07 | 259660 | 2.40414 | 1(Win) |
| simdjson (ondemand) | 854.337 | 0.481179 | 72.7775ms | 264040 | 30 | 6.03414e+07 | 294741 | 2.7292 | 2(Loss) |
| glaze | 791.717 | 0.540072 | 76.4435ms | 264040 | 30 | 8.85166e+07 | 318053 | 2.94505 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2446.11 | 1.20657 | 25.1347ms | 264040 | 30 | 4.62824e+07 | 102942 | 0.952897 | 1(Win) |
| glaze | 2303.83 | 0.765969 | 26.6089ms | 263923 | 30 | 2.10086e+07 | 109251 | 1.0117 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1217.86 | 0.400018 | 77.1721ms | 399947 | 30 | 4.70861e+07 | 313189 | 1.91461 | 1(Win) |
| glaze | 1004.2 | 0.511103 | 91.4747ms | 399947 | 30 | 1.13058e+08 | 379824 | 2.32191 | 2(Loss) |
| jsonifier | 950.173 | 0.600201 | 97.4122ms | 399947 | 30 | 1.74146e+08 | 401421 | 2.45378 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3038.52 | 0.809967 | 30.5426ms | 399947 | 30 | 3.10126e+07 | 125528 | 0.767172 | 1(Win) |
| glaze | 2285.3 | 0.718658 | 40.8291ms | 399830 | 30 | 4.31348e+07 | 166852 | 1.02011 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1384.69 | 0.499201 | 76.7958ms | 466906 | 30 | 7.73084e+07 | 321571 | 1.68394 | 1(Win) |
| jsonifier | 1179.33 | 0.446916 | 91.4078ms | 466906 | 30 | 8.54201e+07 | 377566 | 1.97716 | 2(Loss) |
| simdjson (ondemand) | 629.688 | 0.344372 | 169.39ms | 466906 | 30 | 1.77904e+08 | 707138 | 3.70326 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1892.5 | 1.75913 | 83.1293ms | 699405 | 30 | 1.15319e+09 | 352446 | 1.23206 | 1(Win) |
| glaze | 1733.25 | 0.825152 | 91.8073ms | 699405 | 30 | 3.02499e+08 | 384829 | 1.3453 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2343.25 | 0.393191 | 62.623ms | 631514 | 30 | 3.06377e+07 | 257019 | 0.995061 | 1(Win) |
| glaze | 1565.44 | 0.209224 | 93.292ms | 631514 | 30 | 1.94373e+07 | 384722 | 1.48958 | 2(Loss) |
