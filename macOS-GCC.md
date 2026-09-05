# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.5.0 using the GCC 16.1.0 compiler).  

Latest Results: (Sep 05, 2026)
#### Using the following commits:
----
| Jsonifier: [5656577](https://github.com/nihilai-collective/jsonifier/commit/5656577)  
| Glaze: [a5f515c](https://github.com/stephenberry/glaze/commit/a5f515c)  
| Simdjson: [a346223](https://github.com/simdjson/simdjson/commit/a346223)  

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
  This is the commit of BenchmarkSuite that was used to generate these results: [c0b7b4a](https://github.com/realtimechris/benchmarksuite/commit/c0b7b4a).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 861.255 | 0.883463 | 16.0141ms | 1811 | 30 | 9416.09 | 2005.33 | 1(Win) |
| glaze | 441.911 | 1.90862 | 1.18016ms | 1811 | 30 | 166928 | 3908.27 | 2(Loss) |
| simdjson (ondemand) | 175.082 | 0.678486 | 2.63603ms | 1811 | 30 | 134386 | 9864.53 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 574.986 | 0.699866 | 0.834048ms | 1811 | 30 | 13257.9 | 3003.73 | 1(Win) |
| glaze | 378.422 | 2.47009 | 1.22317ms | 1798 | 30 | 375815 | 4531.2 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1362.94 | 1.59778 | 7.2489ms | 3873 | 128 | 239983 | 2710 | 1(Win) |
| jsonifier | 1251.21 | 2.02541 | 3.41299ms | 3873 | 64 | 228791 | 2952 | 2(Loss) |
| simdjson (ondemand) | 383.385 | 1.17794 | 2.784ms | 3873 | 30 | 386361 | 9634.13 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2011.75 | 2.04659 | 4.94515ms | 3873 | 128 | 180724 | 1836 | 1(Win) |
| glaze | 1193.02 | 1.67525 | 1.97094ms | 3873 | 32 | 86082.1 | 3096 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1539.75 | 1.84836 | 6.33907ms | 3862 | 128 | 250211 | 2392 | 1(Win) |
| glaze | 1183.51 | 1.97512 | 3.97184ms | 3862 | 64 | 241794 | 3112 | 2(Loss) |
| simdjson (ondemand) | 332.009 | 0.619351 | 2.84493ms | 3862 | 30 | 141618 | 11093.3 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1812.54 | 1.48997 | 1.27206ms | 3862 | 32 | 29332.6 | 2032 | 1(Win) |
| glaze | 1198.92 | 1.78685 | 0.827136ms | 3862 | 30 | 90394.5 | 3072 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1373.78 | 2.45157 | 14.2118ms | 905 | 1024 | 242915 | 628.25 | 1(Win) |
| glaze | 656.331 | 2.2477 | 7.41197ms | 905 | 256 | 223649 | 1315 | 2(Loss) |
| simdjson (ondemand) | 176.205 | 2.29305 | 1.22189ms | 905 | 30 | 378452 | 4898.13 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 697.153 | 2.21218 | 6.69696ms | 905 | 256 | 192010 | 1238 | 1(Win) |
| glaze | 299.679 | 2.22222 | 1.53984ms | 905 | 32 | 131072 | 2880 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1826.86 | 2.29877 | 3.30598ms | 9578 | 32 | 422747 | 5000 | 1(Win) |
| glaze | 1572.71 | 1.44676 | 3.74298ms | 9578 | 32 | 225941 | 5808 | 2(Loss) |
| simdjson (ondemand) | 511.431 | 2.07505 | 4.18304ms | 9578 | 30 | 4.12056e+06 | 17860.3 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3162.84 | 2.1306 | 3.54893ms | 9578 | 64 | 242314 | 2888 | 1(Win) |
| glaze | 2958 | 1.53196 | 2.00883ms | 9578 | 32 | 71613.9 | 3088 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3253.01 | 0.936844 | 15.9409ms | 233995 | 30 | 1.23907e+07 | 68599.5 | 1(Win) |
| simdjson (ondemand) | 2504.64 | 0.843231 | 21.717ms | 233995 | 30 | 1.69331e+07 | 89096.5 | 2(Loss) |
| glaze | 1006.39 | 1.12582 | 53.0289ms | 233995 | 30 | 1.86959e+08 | 221739 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4239.43 | 0.798052 | 18.8772ms | 346753 | 30 | 1.16254e+07 | 78003.2 | 1(Win) |
| simdjson (ondemand) | 3322.13 | 0.456421 | 24.788ms | 346753 | 30 | 6.1924e+06 | 99541.3 | 2(Loss) |
| glaze | 1582.52 | 0.204991 | 52.5691ms | 346753 | 30 | 5.50472e+06 | 208964 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1177.12 | 1.1493 | 49.4259ms | 233995 | 30 | 1.42415e+08 | 189577 | 1(Tie) |
| glaze STATISTICAL TIE | 1172.06 | 2.21667 | 45.417ms | 233995 | 30 | 5.34367e+08 | 190396 | 1(Tie) |
| simdjson (ondemand) | 743.517 | 1.70505 | 68.7229ms | 233995 | 30 | 7.85648e+08 | 300134 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 2522.52 | 0.308906 | 21.409ms | 233995 | 30 | 2.24035e+06 | 88465.1 | 1(Win) |
| jsonifier | 2036.68 | 0.834035 | 26.868ms | 233995 | 30 | 2.50528e+07 | 109568 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1286.4 | 2.19044 | 56.278ms | 346753 | 30 | 9.51208e+08 | 257067 | 1(Win) |
| simdjson (ondemand) | 1132.13 | 1.0211 | 70.4271ms | 346753 | 30 | 2.66876e+08 | 292096 | 2(Loss) |
| jsonifier | 1081.06 | 1.31157 | 75.5991ms | 346753 | 30 | 4.82889e+08 | 305894 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2294.41 | 1.09058 | 35.7161ms | 346753 | 30 | 7.4119e+07 | 144128 | 1(Win) |
| glaze | 2220.4 | 0.460322 | 37.207ms | 346753 | 30 | 1.41001e+07 | 148932 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3211.07 | 1.64624 | 17.5749ms | 233995 | 30 | 3.92662e+07 | 69495.5 | 1(Win) |
| simdjson (ondemand) | 1695.36 | 1.59611 | 32.5732ms | 233995 | 30 | 1.32415e+08 | 131627 | 2(Loss) |
| glaze | 1023.96 | 0.804176 | 54.015ms | 233995 | 30 | 9.21443e+07 | 217933 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4509.79 | 0.132528 | 19.0228ms | 346753 | 30 | 283311 | 73326.9 | 1(Win) |
| simdjson (ondemand) | 2345.95 | 0.715737 | 35.028ms | 346753 | 30 | 3.05374e+07 | 140962 | 2(Loss) |
| glaze | 1408.21 | 0.342637 | 58.1901ms | 346753 | 30 | 1.94219e+07 | 234829 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1198.93 | 0.78205 | 43.3242ms | 233995 | 30 | 6.35651e+07 | 186129 | 1(Win) |
| jsonifier | 1067.26 | 0.471805 | 52.2409ms | 233995 | 30 | 2.9196e+07 | 209092 | 2(Loss) |
| simdjson (ondemand) | 195.848 | 1.13137 | 274.347ms | 233995 | 30 | 4.98547e+09 | 1.13943e+06 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 2262.59 | 0.818434 | 25.3481ms | 233995 | 30 | 1.95475e+07 | 98628.3 | 1(Tie) |
| glaze STATISTICAL TIE | 2213 | 1.01135 | 25.7869ms | 233995 | 30 | 3.12012e+07 | 100838 | 1(Tie) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1419.04 | 2.02233 | 59.1409ms | 346753 | 30 | 6.66307e+08 | 233037 | 1(Win) |
| jsonifier | 1062.77 | 2.23837 | 70.5769ms | 346753 | 30 | 1.45529e+09 | 311159 | 2(Loss) |
| simdjson (ondemand) | 330.045 | 0.173425 | 630.932ms | 346753 | 32 | 9.66201e+07 | 1.00195e+06 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2607.85 | 1.52733 | 31.134ms | 346753 | 30 | 1.12529e+08 | 126805 | 1(Win) |
| glaze | 2043.06 | 0.646266 | 39.1429ms | 346753 | 30 | 3.28265e+07 | 161860 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 801.916 | 0.0852702 | 27.5612ms | 94651 | 30 | 276381 | 112563 | 1(Win) |
| jsonifier STATISTICAL TIE | 606.645 | 2.06693 | 36.6551ms | 94651 | 30 | 2.8376e+08 | 148796 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 595.981 | 1.927 | 37.2628ms | 94651 | 30 | 2.55547e+08 | 151458 | 2(Tie) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 4360.29 | 1.82528 | 5.26106ms | 94651 | 30 | 4.28349e+06 | 20701.9 | 1(Tie) |
| jsonifier STATISTICAL TIE | 4353.12 | 1.02354 | 5.13613ms | 94651 | 30 | 1.3514e+06 | 20736 | 1(Tie) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 904.173 | 0.683438 | 35.8679ms | 136024 | 30 | 2.88434e+07 | 143471 | 1(Win) |
| simdjson (ondemand) | 801.617 | 1.81336 | 39.532ms | 136024 | 30 | 2.58337e+08 | 161826 | 2(Loss) |
| jsonifier | 710.7 | 0.40691 | 109.203ms | 136024 | 32 | 1.76524e+07 | 182528 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 3306.73 | 1.19734 | 9.68806ms | 136046 | 30 | 6.62109e+06 | 39236.3 | 1(Win) |
| jsonifier | 2591.08 | 1.20946 | 12.2092ms | 136024 | 30 | 1.09996e+07 | 50065.1 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 509.234 | 0.651507 | 933.111ms | 2090234 | 30 | 1.95126e+10 | 3.91451e+06 | 1(Win) |
| glaze | 465.792 | 0.249512 | 1066.67ms | 2090234 | 30 | 3.42065e+09 | 4.27959e+06 | 2(Loss) |
| simdjson (ondemand) | 402.466 | 0.576521 | 1182.02ms | 2090234 | 30 | 2.44615e+10 | 4.95298e+06 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1526.87 | 0.858836 | 739.034ms | 2090234 | 32 | 4.02303e+09 | 1.30554e+06 | 1(Win) |
| glaze | 1376.87 | 0.342859 | 389.409ms | 2090234 | 30 | 7.39185e+08 | 1.44777e+06 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1239.43 | 1.14422 | 1134.95ms | 6661897 | 30 | 1.03203e+11 | 5.12597e+06 | 1(Win) |
| simdjson (ondemand) | 1202.42 | 0.968436 | 1280.08ms | 6661897 | 30 | 7.85503e+10 | 5.28375e+06 | 2(Loss) |
| glaze | 1128.7 | 0.553321 | 1360.08ms | 6661897 | 30 | 2.91012e+10 | 5.62883e+06 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3096.9 | 0.620491 | 525.7ms | 6661897 | 30 | 4.86111e+09 | 2.0515e+06 | 1(Win) |
| glaze | 2587.16 | 0.982038 | 595.719ms | 6661897 | 30 | 1.74473e+10 | 2.4557e+06 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1371.72 | 0.827181 | 83.3731ms | 500299 | 30 | 2.48341e+08 | 347827 | 1(Win) |
| glaze | 1082.89 | 1.17457 | 108.013ms | 500299 | 30 | 8.03473e+08 | 440602 | 2(Loss) |
| simdjson (ondemand) | 704.28 | 0.370797 | 169.74ms | 500299 | 30 | 1.89306e+08 | 677461 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3901.53 | 1.23996 | 28.6648ms | 500299 | 30 | 6.89807e+07 | 122291 | 1(Win) |
| glaze | 1633.25 | 1.52421 | 67.764ms | 500299 | 30 | 5.9479e+08 | 292130 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1924.24 | 1.43161 | 176.758ms | 1439562 | 30 | 3.12978e+09 | 713463 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1870.59 | 0.148801 | 178.099ms | 1439562 | 30 | 3.57797e+07 | 733926 | 1(Tie) |
| glaze | 1850.64 | 0.343182 | 179.054ms | 1439562 | 30 | 1.9444e+08 | 741837 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3681.57 | 0.711886 | 243.654ms | 1439562 | 32 | 2.2551e+08 | 372904 | 1(Win) |
| glaze | 2384.13 | 1.5951 | 342.328ms | 1439584 | 32 | 2.69986e+09 | 575848 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1390.05 | 0.679185 | 10.2651ms | 56369 | 30 | 2.06973e+06 | 38673.1 | 1(Win) |
| glaze | 1241.57 | 0.784449 | 10.858ms | 56369 | 30 | 3.4609e+06 | 43298.1 | 2(Loss) |
| simdjson (ondemand) | 868.928 | 0.107453 | 15.0871ms | 56369 | 30 | 132579 | 61866.7 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5223.65 | 1.65006 | 2.66778ms | 56369 | 30 | 865075 | 10291.2 | 1(Win) |
| glaze | 2489.03 | 1.7447 | 5.40698ms | 56369 | 30 | 4.25976e+06 | 21597.9 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1415.66 | 1.47828 | 15.7322ms | 94370 | 30 | 2.64961e+07 | 63573.3 | 1(Win) |
| jsonifier | 1198.49 | 1.23538 | 21.238ms | 94370 | 30 | 2.58182e+07 | 75093.3 | 2(Loss) |
| simdjson (ondemand) | 1123.18 | 1.91883 | 20.79ms | 94370 | 30 | 7.0919e+07 | 80128 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2769.61 | 0.581424 | 7.97798ms | 94370 | 30 | 1.07087e+06 | 32494.9 | 1(Win) |
| glaze | 2686.37 | 0.81409 | 8.5929ms | 94370 | 30 | 2.23154e+06 | 33501.9 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1279.73 | 0.204157 | 10.9819ms | 52708 | 30 | 192917 | 39278.9 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1134.77 | 0.544742 | 10.857ms | 52708 | 30 | 1.7468e+06 | 44296.5 | 2(Tie) |
| glaze STATISTICAL TIE | 1134.55 | 0.712231 | 10.9519ms | 52708 | 30 | 2.98724e+06 | 44305.1 | 2(Tie) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4880.35 | 0.814236 | 2.75098ms | 52708 | 30 | 210996 | 10299.7 | 1(Win) |
| glaze | 3404.96 | 0.521448 | 3.79802ms | 52708 | 30 | 177776 | 14762.7 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 1443.11 | 0.211099 | 11.328ms | 70103 | 30 | 286927 | 46327.5 | 1(Win) |
| glaze | 1378.61 | 0.433749 | 11.9629ms | 70103 | 30 | 1.32737e+06 | 48494.9 | 2(Loss) |
| jsonifier | 1095.75 | 0.138406 | 17.269ms | 70103 | 30 | 213934 | 61013.3 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3931.07 | 0.138513 | 4.40397ms | 70103 | 30 | 16647.7 | 17006.9 | 1(Win) |
| glaze | 3506.99 | 2.03682 | 4.77978ms | 70103 | 30 | 4.52304e+06 | 19063.5 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1053.18 | 0.734676 | 6.29094ms | 11812 | 32 | 197599 | 10696 | 1(Win) |
| glaze | 766.605 | 0.576298 | 3.712ms | 11812 | 30 | 215139 | 14694.4 | 2(Loss) |
| simdjson (ondemand) | 556.767 | 0.731731 | 5.64608ms | 11812 | 30 | 657545 | 20232.5 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4729.14 | 1.83735 | 7.11603ms | 11812 | 128 | 245175 | 2382 | 1(Win) |
| glaze | 1716.64 | 1.51362 | 1.73389ms | 11812 | 30 | 295967 | 6562.13 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1686.37 | 1.01651 | 4.55501ms | 31235 | 30 | 967221 | 17664 | 1(Win) |
| glaze STATISTICAL TIE | 1459.97 | 0.737157 | 4.94618ms | 31235 | 30 | 678637 | 20403.2 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1425.39 | 1.2535 | 5.06701ms | 31235 | 30 | 2.05866e+06 | 20898.1 | 2(Tie) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4257.05 | 0.32026 | 1.86496ms | 31235 | 30 | 15065.7 | 6997.33 | 1(Win) |
| glaze | 2636.54 | 0.766148 | 2.88998ms | 31235 | 30 | 224781 | 11298.1 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2734.96 | 0.214917 | 10.0321ms | 108313 | 30 | 197663 | 37768.5 | 1(Win) |
| glaze STATISTICAL TIE | 1130.98 | 2.08678 | 19.8331ms | 108313 | 30 | 1.08974e+08 | 91332.3 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1114.74 | 0.365285 | 26.1151ms | 108313 | 30 | 3.43717e+06 | 92663.5 | 2(Tie) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2038.55 | 0.700361 | 12.2281ms | 108313 | 30 | 3.77819e+06 | 50670.9 | 1(Win) |
| glaze | 1591.5 | 1.18354 | 16.351ms | 108313 | 30 | 1.77026e+07 | 64904.5 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2058.38 | 0.355355 | 24.9211ms | 213963 | 30 | 3.72282e+06 | 99131.7 | 1(Win) |
| glaze | 1922.36 | 0.548566 | 25.7298ms | 213963 | 30 | 1.01716e+07 | 106146 | 2(Loss) |
| simdjson (ondemand) | 1866.98 | 0.199299 | 26.3739ms | 213963 | 30 | 1.42341e+06 | 109295 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2920.76 | 0.301428 | 16.8809ms | 213963 | 30 | 1.33038e+06 | 69862.4 | 1(Win) |
| glaze | 2051.5 | 0.353747 | 23.9839ms | 213963 | 30 | 3.71401e+06 | 99464.5 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 613.924 | 0.106739 | 686.815ms | 1834197 | 30 | 2.77476e+08 | 2.84925e+06 | 1(Win) |
| glaze | 439.572 | 1.88047 | 950.807ms | 1834197 | 30 | 1.67992e+11 | 3.97938e+06 | 2(Loss) |
| simdjson (ondemand) | 422.904 | 0.193401 | 999.61ms | 1834197 | 30 | 1.91977e+09 | 4.13623e+06 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 782.656 | 0.171015 | 539.119ms | 1833577 | 30 | 4.37974e+08 | 2.23423e+06 | 1(Win) |
| jsonifier | 601.38 | 0.61647 | 691.453ms | 1834197 | 30 | 9.64584e+09 | 2.90869e+06 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1895.87 | 0.491253 | 1207.05ms | 9930848 | 30 | 1.80672e+10 | 4.9955e+06 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1823.52 | 0.294643 | 1246.26ms | 9930848 | 30 | 7.02534e+09 | 5.19369e+06 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1814.89 | 0.386226 | 1225.22ms | 9930848 | 30 | 1.21864e+10 | 5.21839e+06 | 2(Tie) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2395.04 | 0.308919 | 970.38ms | 9930848 | 30 | 4.47669e+09 | 3.95434e+06 | 1(Win) |
| glaze | 2274.29 | 0.339708 | 1098.48ms | 9930228 | 30 | 6.00289e+09 | 4.16403e+06 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1125.32 | 0.158928 | 131.076ms | 642697 | 30 | 2.24793e+07 | 544666 | 1(Win) |
| glaze | 953.675 | 0.210614 | 155.368ms | 642697 | 30 | 5.49677e+07 | 642697 | 2(Loss) |
| simdjson (ondemand) | 834.257 | 0.181106 | 177.567ms | 642697 | 30 | 5.31129e+07 | 734694 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1044.94 | 0.188516 | 142.689ms | 642697 | 30 | 3.66818e+07 | 586564 | 1(Win) |
| glaze | 942.085 | 0.699265 | 158.084ms | 642692 | 30 | 6.20913e+08 | 650598 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1485.61 | 0.124589 | 190.045ms | 1225964 | 30 | 2.88422e+07 | 786995 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1484.6 | 0.12558 | 190.472ms | 1225964 | 30 | 2.93427e+07 | 787533 | 1(Tie) |
| jsonifier | 1290.9 | 0.96537 | 213.289ms | 1225964 | 30 | 2.2934e+09 | 905702 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1920.9 | 0.18204 | 146.108ms | 1225964 | 30 | 3.68298e+07 | 608657 | 1(Win) |
| glaze | 1218.31 | 0.655739 | 230.285ms | 1225970 | 30 | 1.18802e+09 | 959667 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 729.494 | 0.261559 | 129.444ms | 409725 | 30 | 5.88845e+07 | 535637 | 1(Win) |
| simdjson (ondemand) | 571.073 | 0.178766 | 164.61ms | 409725 | 30 | 4.48839e+07 | 684228 | 2(Loss) |
| glaze | 559.695 | 0.260812 | 168.078ms | 409725 | 30 | 9.94626e+07 | 698138 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3640.51 | 1.02972 | 25.4269ms | 409725 | 30 | 3.66456e+07 | 107332 | 1(Win) |
| glaze | 1944.39 | 0.427023 | 48.5361ms | 409725 | 30 | 2.20924e+07 | 200960 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 1022.17 | 0.0974311 | 177.484ms | 785750 | 30 | 1.53053e+07 | 733099 | 1(Win) |
| glaze | 989.815 | 0.0941745 | 185.314ms | 785750 | 30 | 1.52492e+07 | 757060 | 2(Loss) |
| jsonifier | 971.334 | 0.111028 | 186.845ms | 785750 | 30 | 2.20099e+07 | 771465 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2636.36 | 0.194954 | 68.608ms | 785750 | 30 | 9.21188e+06 | 284237 | 1(Win) |
| glaze | 2373.88 | 0.227891 | 75.9452ms | 785750 | 30 | 1.5525e+07 | 315665 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1026.36 | 0.126702 | 2010.94ms | 8587914 | 30 | 3.06664e+09 | 7.97972e+06 | 1(Win) |
| simdjson (ondemand) | 892.191 | 0.144379 | 2219.82ms | 8587914 | 30 | 5.26972e+09 | 9.17973e+06 | 2(Loss) |
| glaze | 805.365 | 0.64335 | 2274.58ms | 8587914 | 30 | 1.28412e+11 | 1.01694e+07 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3508.55 | 0.28927 | 593.157ms | 8588126 | 30 | 1.36795e+09 | 2.33438e+06 | 1(Win) |
| glaze | 2197.53 | 2.34433 | 775.466ms | 8588126 | 30 | 2.29027e+11 | 3.72704e+06 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 1001.76 | 0.126296 | 2245.81ms | 9804437 | 30 | 4.1689e+09 | 9.33382e+06 | 1(Win) |
| jsonifier | 988.895 | 0.258286 | 2277.15ms | 9804437 | 30 | 1.78924e+10 | 9.45524e+06 | 2(Loss) |
| glaze | 940.764 | 0.202214 | 2461.47ms | 9804437 | 30 | 1.21179e+10 | 9.93899e+06 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 3271.66 | 0.202633 | 802.925ms | 11078090 | 30 | 1.2845e+09 | 3.22922e+06 | 1(Win) |
| jsonifier | 2530.41 | 1.80152 | 939.081ms | 11078090 | 30 | 1.69727e+11 | 4.17517e+06 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3525.12 | 0.434524 | 17.526ms | 264040 | 30 | 2.89029e+06 | 71432.5 | 1(Win) |
| simdjson (ondemand) | 2801.02 | 0.752933 | 21.2859ms | 264040 | 30 | 1.37449e+07 | 89898.7 | 2(Loss) |
| glaze | 1303.56 | 1.08022 | 47.6401ms | 264040 | 30 | 1.30623e+08 | 193169 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4242.77 | 0.482352 | 21.8739ms | 399947 | 30 | 5.64099e+06 | 89898.7 | 1(Win) |
| simdjson (ondemand) | 3740.69 | 0.281063 | 24.7199ms | 399947 | 30 | 2.46393e+06 | 101965 | 2(Loss) |
| glaze | 1841.38 | 0.195971 | 50.284ms | 399947 | 30 | 4.94337e+06 | 207138 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1485.61 | 0.976626 | 42.2139ms | 264040 | 30 | 8.22063e+07 | 169498 | 1(Win) |
| glaze STATISTICAL TIE | 1222.96 | 0.185581 | 49.8941ms | 264040 | 30 | 4.38029e+06 | 205901 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1220.03 | 0.270157 | 49.802ms | 264040 | 30 | 9.32728e+06 | 206396 | 2(Tie) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 3362.1 | 0.359092 | 18.1289ms | 263923 | 30 | 2.16804e+06 | 74862.9 | 1(Win) |
| jsonifier | 2772 | 1.10096 | 52.9231ms | 264040 | 32 | 3.20074e+07 | 90840 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1574.19 | 1.32071 | 61.1131ms | 399947 | 30 | 3.07204e+08 | 242295 | 1(Tie) |
| glaze STATISTICAL TIE | 1568.78 | 0.976535 | 58.5428ms | 399947 | 30 | 1.69114e+08 | 243132 | 1(Tie) |
| jsonifier | 1339.85 | 0.222211 | 70.9811ms | 399947 | 30 | 1.20044e+07 | 284672 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4211.59 | 0.535422 | 21.801ms | 399947 | 30 | 7.05386e+06 | 90564.3 | 1(Win) |
| glaze | 3605.33 | 0.288447 | 25.9059ms | 399830 | 30 | 2.79198e+06 | 105762 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1775.34 | 0.164649 | 60.3489ms | 466906 | 30 | 5.11603e+06 | 250812 | 1(Win) |
| jsonifier | 1613.31 | 0.166856 | 66.583ms | 466906 | 30 | 6.36257e+06 | 276002 | 2(Loss) |
| simdjson (ondemand) | 782.826 | 1.00492 | 138.269ms | 466906 | 30 | 9.80199e+08 | 568806 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 2308.81 | 0.290584 | 69.472ms | 699405 | 30 | 2.11421e+07 | 288896 | 1(Win) |
| jsonifier | 2201.82 | 0.32438 | 71.9831ms | 699405 | 30 | 2.89684e+07 | 302933 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2557.42 | 0.367385 | 57.1589ms | 631514 | 30 | 2.24556e+07 | 235494 | 1(Win) |
| glaze | 1922.09 | 0.163567 | 75.3682ms | 631514 | 30 | 7.88006e+06 | 313335 | 2(Loss) |
