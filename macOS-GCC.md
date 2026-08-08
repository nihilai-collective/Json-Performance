# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.5.0 using the GCC 16.1.0 compiler).  

Latest Results: (Aug 08, 2026)
#### Using the following commits:
----
| Jsonifier: [66d99df](https://github.com/nihilai-collective/jsonifier/commit/66d99df)  
| Glaze: [72b670e](https://github.com/stephenberry/glaze/commit/72b670e)  
| Simdjson: [20b2871](https://github.com/simdjson/simdjson/commit/20b2871)  

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

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them? We perform scalar iteration)

#### Note:
  These benchmarks were executed using the CPU benchmark library [benchmarksuite](https://github.com/realtimechris/benchmarksuite).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 657.193 | 2.32903 | 3.4409ms | 1811 | 64 | 239762 | 2628 | 1(Win) |
| jsonifier | 294.607 | 1.15345 | 22.5039ms | 1811 | 30 | 137174 | 5862.4 | 2(Loss) |
| simdjson (ondemand) | 152.062 | 1.45585 | 3.18592ms | 1811 | 30 | 820255 | 11357.9 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 665.807 | 1.84595 | 7.64109ms | 1811 | 128 | 293489 | 2594 | 1(Win) |
| glaze | 401.884 | 1.89373 | 1.35808ms | 1798 | 30 | 195855 | 4266.67 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1461.07 | 2.46548 | 3.40685ms | 3873 | 64 | 248621 | 2528 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1440.27 | 1.67029 | 30.7182ms | 3873 | 512 | 939415 | 2564.5 | 1(Tie) |
| simdjson (ondemand) | 338.952 | 1.9303 | 2.70208ms | 3873 | 30 | 1.32737e+06 | 10897.1 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2812.55 | 2.29718 | 57.4909ms | 3873 | 2048 | 1.86387e+06 | 1313.25 | 1(Win) |
| glaze | 1130.23 | 1.73366 | 8.22605ms | 3873 | 64 | 205434 | 3268 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1518.64 | 1.04918 | 58.22ms | 3862 | 1024 | 663002 | 2425.25 | 1(Win) |
| glaze | 1261.33 | 1.26118 | 3.80314ms | 3862 | 64 | 86796.2 | 2920 | 2(Loss) |
| simdjson (ondemand) | 311.408 | 2.16798 | 3.13907ms | 3862 | 30 | 1.97241e+06 | 11827.2 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2193.62 | 1.83848 | 13.621ms | 3862 | 256 | 243928 | 1679 | 1(Win) |
| glaze | 1108.03 | 1.90613 | 4.93491ms | 3862 | 64 | 256926 | 3324 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1272.74 | 1.74833 | 61.6279ms | 905 | 4096 | 575743 | 678.125 | 1(Win) |
| glaze | 513.659 | 2.04027 | 68.9098ms | 905 | 2048 | 2.40686e+06 | 1680.25 | 2(Loss) |
| simdjson (ondemand) | 174.986 | 1.70486 | 1.34298ms | 905 | 30 | 212126 | 4932.27 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 993.754 | 1.84234 | 9.84909ms | 905 | 512 | 131084 | 868.5 | 1(Win) |
| glaze | 317.657 | 1.24223 | 14.442ms | 905 | 256 | 291626 | 2717 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1767.47 | 1.82911 | 7.6649ms | 9578 | 64 | 571880 | 5168 | 1(Tie) |
| glaze STATISTICAL TIE | 1701.79 | 1.85051 | 1.56109ms | 9578 | 30 | 295967 | 5367.47 | 1(Tie) |
| simdjson (ondemand) | 527.823 | 2.16018 | 4.06093ms | 9578 | 30 | 4.1925e+06 | 17305.6 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3148.31 | 1.95401 | 0.882176ms | 9578 | 30 | 96420.8 | 2901.33 | 1(Win) |
| glaze | 2773.12 | 2.28903 | 1.04499ms | 9578 | 30 | 170544 | 3293.87 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3314.56 | 1.43512 | 13.513ms | 33713 | 64 | 1.24023e+06 | 9700 | 1(Win) |
| simdjson (ondemand) | 2550.93 | 1.81588 | 3.71994ms | 33713 | 30 | 1.57143e+06 | 12603.7 | 2(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3787.65 | 1.71573 | 3.37485ms | 48024 | 30 | 1.29121e+06 | 12091.7 | 1(Win) |
| simdjson (ondemand) | 3157.7 | 1.68792 | 8.62592ms | 48024 | 32 | 1.91792e+06 | 14504 | 2(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1216.39 | 0.80188 | 59.5579ms | 294588 | 30 | 1.02902e+08 | 230963 | 1(Tie) |
| glaze STATISTICAL TIE | 1172.88 | 1.62805 | 66.5201ms | 294588 | 30 | 4.56227e+08 | 239531 | 1(Tie) |
| simdjson (ondemand) | 740.303 | 2.43348 | 92.341ms | 294588 | 30 | 2.55851e+09 | 379494 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2642.07 | 0.941561 | 26.0288ms | 294588 | 30 | 3.00719e+07 | 106334 | 1(Win) |
| glaze | 2352.13 | 1.58918 | 31.7581ms | 294588 | 30 | 1.08088e+08 | 119441 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1713.04 | 0.697619 | 57.1891ms | 406546 | 30 | 7.47895e+07 | 226330 | 1(Win) |
| jsonifier STATISTICAL TIE | 1129.75 | 2.19335 | 447.973ms | 406546 | 64 | 3.62619e+09 | 343184 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1082.9 | 0.96807 | 83.0239ms | 406546 | 30 | 3.60397e+08 | 358033 | 2(Tie) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2853.34 | 2.37867 | 78.0119ms | 406546 | 32 | 3.34296e+08 | 135880 | 1(Win) |
| glaze | 2128.01 | 2.46884 | 43.337ms | 406546 | 30 | 6.06991e+08 | 182195 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3217.52 | 1.94406 | 2.96986ms | 33713 | 30 | 1.13212e+06 | 9992.53 | 1(Win) |
| simdjson (ondemand) | 1641.04 | 1.53442 | 11.146ms | 33713 | 32 | 2.89197e+06 | 19592 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3732.34 | 2.10992 | 3.72992ms | 48024 | 30 | 2.01098e+06 | 12270.9 | 1(Win) |
| simdjson (ondemand) | 2019.63 | 2.3171 | 126.503ms | 48024 | 256 | 7.06808e+07 | 22677 | 2(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1157.28 | 2.26631 | 293.092ms | 294588 | 64 | 1.9372e+09 | 242760 | 1(Win) |
| jsonifier | 1028.62 | 0.577825 | 1577.35ms | 294588 | 256 | 6.376e+08 | 273123 | 2(Loss) |
| simdjson (ondemand) | 217.754 | 0.870134 | 1675.15ms | 294588 | 64 | 8.06585e+09 | 1.29018e+06 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2675.56 | 1.38228 | 27.5901ms | 294588 | 30 | 6.31997e+07 | 105003 | 1(Win) |
| glaze | 2161.72 | 2.44361 | 366.813ms | 294588 | 128 | 1.29094e+09 | 129962 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1501.88 | 0.769466 | 151.694ms | 406546 | 32 | 1.26264e+08 | 258152 | 1(Win) |
| jsonifier | 879.962 | 1.96674 | 98.23ms | 406546 | 30 | 2.25272e+09 | 440602 | 2(Loss) |
| simdjson (ondemand) | 306.261 | 1.86532 | 316.25ms | 406546 | 30 | 1.67288e+10 | 1.26595e+06 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3142.55 | 0.293603 | 32.5199ms | 406546 | 30 | 3.93638e+06 | 123375 | 1(Win) |
| glaze | 2135.78 | 1.0085 | 208.612ms | 406546 | 64 | 2.14505e+08 | 181532 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 716.769 | 1.28269 | 30.882ms | 94651 | 30 | 7.82813e+07 | 125935 | 1(Win) |
| jsonifier STATISTICAL TIE | 629.198 | 1.05914 | 34.1901ms | 94651 | 30 | 6.9263e+07 | 143462 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 614.504 | 1.25674 | 38.677ms | 94651 | 30 | 1.02238e+08 | 146893 | 2(Tie) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 4241.83 | 0.388582 | 12.2952ms | 94651 | 32 | 218806 | 21280 | 1(Win) |
| jsonifier | 2730.71 | 1.61079 | 31.252ms | 94651 | 32 | 9.07251e+06 | 33056 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 843.187 | 0.964068 | 88.4439ms | 136024 | 32 | 7.03962e+07 | 153848 | 1(Win) |
| simdjson (ondemand) | 769.442 | 2.28963 | 41.471ms | 136024 | 30 | 4.47026e+08 | 168593 | 2(Loss) |
| jsonifier | 702.23 | 1.08528 | 46.133ms | 136024 | 30 | 1.2058e+08 | 184730 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3259.69 | 0.824634 | 57.8089ms | 136024 | 64 | 6.89258e+06 | 39796 | 1(Win) |
| glaze | 3022.73 | 1.47023 | 10.8088ms | 136046 | 30 | 1.19471e+07 | 42922.7 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 498.338 | 0.889935 | 949.713ms | 2090234 | 30 | 3.80172e+10 | 4.0001e+06 | 1(Win) |
| glaze | 410.327 | 1.21911 | 1149.21ms | 2090234 | 30 | 1.05229e+11 | 4.85808e+06 | 2(Loss) |
| simdjson (ondemand) | 338.816 | 1.88184 | 1510.15ms | 2090234 | 30 | 3.67749e+11 | 5.88344e+06 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1521.81 | 0.387216 | 336.194ms | 2090234 | 30 | 7.71791e+08 | 1.30989e+06 | 1(Win) |
| glaze | 1230.47 | 0.863617 | 392.146ms | 2090234 | 30 | 5.87237e+09 | 1.62004e+06 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1018.17 | 0.936922 | 3518.37ms | 6661897 | 32 | 1.09373e+11 | 6.23988e+06 | 1(Tie) |
| glaze STATISTICAL TIE | 1006.17 | 1.80455 | 1689.04ms | 6661897 | 30 | 3.89508e+11 | 6.31435e+06 | 1(Tie) |
| simdjson (ondemand) | 894.061 | 2.47596 | 1640.2ms | 6661897 | 30 | 9.28691e+11 | 7.10609e+06 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3010.33 | 1.01537 | 1239.1ms | 6661897 | 32 | 1.4695e+10 | 2.1105e+06 | 1(Win) |
| glaze | 2316.62 | 1.05753 | 689.115ms | 6661897 | 30 | 2.52346e+10 | 2.74248e+06 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1419.47 | 0.500664 | 249.828ms | 500299 | 32 | 9.06257e+07 | 336128 | 1(Win) |
| glaze | 1021.47 | 1.82699 | 689.344ms | 500299 | 64 | 4.66083e+09 | 467096 | 2(Loss) |
| simdjson (ondemand) | 624.347 | 1.96435 | 180.631ms | 500299 | 30 | 6.76028e+09 | 764194 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1407.85 | 2.14056 | 78.999ms | 500299 | 30 | 1.57879e+09 | 338901 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1362.8 | 2.19301 | 79.2512ms | 500299 | 30 | 1.76848e+09 | 350106 | 1(Tie) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1788.29 | 1.39488 | 219.242ms | 1439562 | 30 | 3.44017e+09 | 767701 | 1(Win) |
| glaze | 1516.68 | 1.01417 | 527.456ms | 1439562 | 32 | 2.69677e+09 | 905184 | 2(Loss) |
| simdjson (ondemand) | 1466.44 | 0.924514 | 210.108ms | 1439562 | 30 | 2.24739e+09 | 936192 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3957.58 | 0.452113 | 92.821ms | 1439562 | 30 | 7.37932e+07 | 346897 | 1(Win) |
| glaze | 2372.46 | 1.59161 | 146.243ms | 1439584 | 30 | 2.54492e+09 | 578679 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1062.23 | 1.87994 | 540.419ms | 56369 | 512 | 4.63452e+08 | 50608.5 | 1(Win) |
| glaze | 1006.09 | 1.00795 | 31.3951ms | 56369 | 32 | 9.28173e+06 | 53432 | 2(Loss) |
| simdjson (ondemand) | 710.986 | 0.964388 | 220.543ms | 56369 | 128 | 6.80569e+07 | 75610 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 2551.53 | 1.06015 | 7.25504ms | 56369 | 30 | 1.49671e+06 | 21068.8 | 1(Win) |
| jsonifier | 1873.25 | 1.72169 | 7.52ms | 56369 | 30 | 7.32354e+06 | 28697.6 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1247.86 | 1.95789 | 355.608ms | 94370 | 256 | 5.10451e+08 | 72122 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1230.83 | 1.5417 | 45.918ms | 94370 | 32 | 4.06651e+07 | 73120 | 1(Tie) |
| simdjson (ondemand) | 1173.2 | 1.20245 | 49.449ms | 94370 | 32 | 2.72275e+07 | 76712 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2970.06 | 1.8793 | 8.33792ms | 94370 | 30 | 9.72863e+06 | 30301.9 | 1(Win) |
| glaze | 2320.38 | 2.47954 | 124.427ms | 94370 | 128 | 1.18387e+08 | 38786 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1073.7 | 1.59082 | 67.0761ms | 52708 | 64 | 3.54987e+07 | 46816 | 1(Tie) |
| glaze STATISTICAL TIE | 1045.73 | 0.927623 | 13.3612ms | 52708 | 30 | 5.9646e+06 | 48068.3 | 1(Tie) |
| simdjson (ondemand) | 904.851 | 1.8965 | 315.339ms | 52708 | 256 | 2.84148e+08 | 55552 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3661.02 | 0.647636 | 3.85997ms | 52708 | 30 | 237210 | 13730.1 | 1(Win) |
| glaze | 3090.54 | 0.965656 | 4.28109ms | 52708 | 30 | 740029 | 16264.5 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1160.75 | 1.92906 | 299.584ms | 70103 | 256 | 3.16031e+08 | 57597 | 1(Tie) |
| glaze STATISTICAL TIE | 1144.43 | 2.31578 | 332.801ms | 70103 | 256 | 4.6852e+08 | 58418 | 1(Tie) |
| jsonifier | 816.645 | 2.35368 | 215.072ms | 70103 | 128 | 4.75238e+08 | 81866 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3293.24 | 1.85978 | 6.24589ms | 70103 | 30 | 4.27634e+06 | 20300.8 | 1(Win) |
| glaze | 3113.61 | 1.55777 | 14.2792ms | 70103 | 32 | 3.58017e+06 | 21472 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 936.237 | 0.792932 | 16.3011ms | 11812 | 64 | 582542 | 12032 | 1(Win) |
| glaze | 663.885 | 1.83438 | 10.338ms | 11812 | 32 | 3.10021e+06 | 16968 | 2(Loss) |
| simdjson (ondemand) | 528.884 | 2.02961 | 5.37088ms | 11812 | 30 | 5.60627e+06 | 21299.2 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3922.28 | 2.36124 | 3.95597ms | 11812 | 64 | 294327 | 2872 | 1(Win) |
| glaze | 1609.87 | 0.32026 | 2.39206ms | 11812 | 30 | 15065.7 | 6997.33 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1336.03 | 1.10782 | 29.63ms | 31235 | 64 | 3.90453e+06 | 22296 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1317.77 | 0.414066 | 8.96691ms | 31235 | 30 | 262822 | 22604.8 | 1(Tie) |
| glaze | 1241.39 | 1.84639 | 7.6119ms | 31235 | 30 | 5.8889e+06 | 23995.7 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3598.75 | 2.41547 | 3.39021ms | 31235 | 30 | 1.19923e+06 | 8277.33 | 1(Win) |
| glaze | 2030.61 | 2.01581 | 153ms | 31235 | 512 | 4.47712e+07 | 14669.5 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2531 | 2.20221 | 55.1178ms | 108313 | 64 | 5.16981e+07 | 40812 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 969.327 | 1.66961 | 147.86ms | 108313 | 64 | 2.02596e+08 | 106564 | 2(Tie) |
| glaze STATISTICAL TIE | 935.671 | 1.68676 | 1322.04ms | 108313 | 512 | 1.77538e+09 | 110397 | 2(Tie) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1765.73 | 1.47011 | 69.494ms | 108313 | 64 | 4.73357e+07 | 58500 | 1(Win) |
| glaze | 1506.64 | 2.46912 | 39.8671ms | 108313 | 32 | 9.17015e+07 | 68560 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1766.74 | 1.6628 | 146.811ms | 213963 | 64 | 2.36044e+08 | 115496 | 1(Win) |
| simdjson (ondemand) | 1683.13 | 0.647627 | 30.187ms | 213963 | 30 | 1.84933e+07 | 121233 | 2(Loss) |
| glaze | 1441.77 | 2.2577 | 92.693ms | 213963 | 32 | 3.26712e+08 | 141528 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2959.32 | 0.735059 | 90.5211ms | 213963 | 64 | 1.64406e+07 | 68952 | 1(Win) |
| glaze | 1685.93 | 2.26373 | 67.966ms | 213963 | 32 | 2.40216e+08 | 121032 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 497.077 | 0.600258 | 2026.95ms | 1834197 | 32 | 1.42781e+10 | 3.51902e+06 | 1(Win) |
| glaze STATISTICAL TIE | 317.66 | 1.67731 | 1279.24ms | 1834197 | 30 | 2.55925e+11 | 5.50659e+06 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 316.301 | 1.38716 | 3413.62ms | 1834197 | 32 | 1.88319e+11 | 5.53026e+06 | 2(Tie) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 626.671 | 1.02195 | 669.718ms | 1833577 | 30 | 2.4395e+10 | 2.79036e+06 | 1(Win) |
| jsonifier | 520.665 | 0.94599 | 788.356ms | 1834197 | 30 | 3.03018e+10 | 3.3596e+06 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1497.08 | 1.09655 | 1502.86ms | 9930848 | 30 | 1.44364e+11 | 6.32616e+06 | 1(Win) |
| jsonifier | 1352.69 | 0.88292 | 1655.3ms | 9930848 | 30 | 1.14642e+11 | 7.00147e+06 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 683.546 | 1.91073 | 8853.18ms | 642697 | 512 | 1.50296e+11 | 896682 | 1(Win) |
| glaze | 616.282 | 2.34148 | 5225.7ms | 642697 | 256 | 1.38827e+11 | 994551 | 2(Loss) |
| simdjson (ondemand) | 570.531 | 2.05349 | 732.706ms | 642697 | 32 | 1.55737e+10 | 1.0743e+06 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 692.329 | 1.49404 | 9246.39ms | 642692 | 512 | 8.95726e+10 | 885300 | 1(Win) |
| jsonifier | 648.84 | 2.22904 | 4572.32ms | 642697 | 256 | 1.13505e+11 | 944645 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 1025.2 | 0.469836 | 3713.19ms | 1225964 | 128 | 3.6749e+09 | 1.14044e+06 | 1(Win) |
| glaze | 976.198 | 1.86794 | 6773.47ms | 1225964 | 256 | 1.28128e+11 | 1.19768e+06 | 2(Loss) |
| jsonifier | 816.649 | 2.37711 | 7063.58ms | 1225964 | 256 | 2.96498e+11 | 1.43167e+06 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1397.9 | 1.79408 | 8285ms | 1225964 | 512 | 1.15281e+11 | 836374 | 1(Win) |
| glaze | 852.778 | 1.90052 | 6637.49ms | 1225970 | 256 | 1.73809e+11 | 1.37102e+06 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 493.79 | 1.99384 | 4184.64ms | 409725 | 256 | 6.37269e+10 | 791317 | 1(Win) |
| glaze | 455.334 | 0.767496 | 5434.6ms | 409725 | 256 | 1.1105e+10 | 858149 | 2(Loss) |
| simdjson (ondemand) | 335.551 | 2.25398 | 5452.78ms | 409725 | 256 | 1.76364e+11 | 1.16449e+06 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2294.11 | 2.10312 | 1723.87ms | 409725 | 512 | 6.56981e+09 | 170325 | 1(Win) |
| glaze | 1639.63 | 1.2844 | 172.562ms | 409725 | 32 | 2.99805e+08 | 238312 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 775.474 | 1.21869 | 616.276ms | 785750 | 32 | 4.43783e+09 | 966312 | 1(Win) |
| jsonifier STATISTICAL TIE | 631.394 | 1.98375 | 6067.2ms | 785750 | 256 | 1.419e+11 | 1.18682e+06 | 2(Tie) |
| glaze STATISTICAL TIE | 605.027 | 1.61679 | 11992.7ms | 785750 | 512 | 2.05304e+11 | 1.23854e+06 | 2(Tie) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1997.12 | 2.49208 | 952.326ms | 785750 | 128 | 1.11917e+10 | 375216 | 1(Win) |
| glaze | 1854.7 | 2.12222 | 115.035ms | 785750 | 30 | 2.20558e+09 | 404028 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 792.729 | 1.04217 | 6934.63ms | 8587914 | 32 | 3.70983e+11 | 1.03315e+07 | 1(Win) |
| glaze | 698.48 | 0.86905 | 2872.99ms | 8587914 | 30 | 3.11514e+11 | 1.17256e+07 | 2(Loss) |
| simdjson (ondemand) | 677.576 | 1.03858 | 7195.34ms | 8587914 | 32 | 5.04299e+11 | 1.20873e+07 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 2478.67 | 2.14201 | 857.023ms | 8588126 | 30 | 1.50288e+11 | 3.3043e+06 | 1(Win) |
| jsonifier | 2284.47 | 1.31163 | 913.951ms | 8588126 | 30 | 6.63391e+10 | 3.58519e+06 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 804.122 | 1.65262 | 2873.72ms | 9804437 | 30 | 1.10782e+12 | 1.16279e+07 | 1(Tie) |
| jsonifier STATISTICAL TIE | 771.863 | 2.41441 | 3207.59ms | 9804437 | 30 | 2.5663e+12 | 1.21139e+07 | 1(Tie) |
| glaze STATISTICAL TIE | 760.588 | 0.996417 | 3026.44ms | 9804437 | 30 | 4.50143e+11 | 1.22934e+07 | 1(Tie) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 2575.7 | 0.641315 | 1059.02ms | 11078090 | 30 | 2.07588e+10 | 4.10175e+06 | 1(Win) |
| jsonifier | 2401.19 | 1.19484 | 2745.67ms | 11078090 | 32 | 8.84403e+10 | 4.39986e+06 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2861 | 1.17742 | 446.913ms | 264040 | 256 | 2.74919e+08 | 88014 | 1(Win) |
| simdjson (ondemand) | 2584.08 | 1.47338 | 259.355ms | 264040 | 128 | 2.63858e+08 | 97446 | 2(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3437.2 | 1.26719 | 280.581ms | 399947 | 128 | 2.53099e+08 | 110968 | 1(Win) |
| simdjson (ondemand) | 2929.76 | 2.32434 | 160.278ms | 399947 | 64 | 5.86031e+08 | 130188 | 2(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1136.5 | 1.91965 | 2376.01ms | 264040 | 512 | 9.26226e+09 | 221565 | 1(Win) |
| simdjson (ondemand) | 1091.62 | 0.549693 | 61.28ms | 264040 | 30 | 4.82342e+07 | 230673 | 2(Loss) |
| glaze | 891.773 | 1.0644 | 92.2051ms | 264040 | 30 | 2.70994e+08 | 282368 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 2885.01 | 1.06695 | 481.392ms | 263923 | 256 | 2.21816e+08 | 87243 | 1(Win) |
| jsonifier | 2534.3 | 1.71859 | 121.219ms | 264040 | 64 | 1.86616e+08 | 99360 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 1384.16 | 1.29808 | 363.676ms | 399947 | 64 | 8.18875e+08 | 275560 | 1(Win) |
| glaze | 1292.21 | 1.19859 | 74.027ms | 399947 | 30 | 3.75494e+08 | 295168 | 2(Loss) |
| jsonifier | 1117.51 | 1.47684 | 225.532ms | 399947 | 32 | 8.13052e+08 | 341312 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3476.45 | 0.970518 | 1311.95ms | 399947 | 512 | 5.80509e+08 | 109715 | 1(Win) |
| glaze | 2934.75 | 2.40061 | 31.681ms | 399830 | 30 | 2.9186e+08 | 129929 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1451.02 | 1.18944 | 175.431ms | 466906 | 32 | 4.26332e+08 | 306872 | 1(Win) |
| jsonifier | 1294.06 | 1.03565 | 446.414ms | 466906 | 64 | 8.1274e+08 | 344092 | 2(Loss) |
| simdjson (ondemand) | 702.696 | 0.974745 | 149.788ms | 466906 | 30 | 1.14453e+09 | 633668 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 2036.86 | 1.18115 | 81.1151ms | 699405 | 30 | 4.48814e+08 | 327467 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1980.4 | 1.20087 | 89.2749ms | 699405 | 30 | 4.90754e+08 | 336802 | 1(Tie) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2294.84 | 1.19905 | 151.81ms | 631514 | 32 | 3.16873e+08 | 262440 | 1(Win) |
| glaze | 1629.6 | 1.18567 | 2142.03ms | 631514 | 256 | 4.91552e+09 | 369575 | 2(Loss) |
