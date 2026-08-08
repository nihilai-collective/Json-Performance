# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1020-azure using the Clang 22.1.8 compiler).  

Latest Results: (Aug 08, 2026)
#### Using the following commits:
----
| Jsonifier: [66d99df](https://github.com/nihilai-collective/jsonifier/commit/66d99df)  
| Glaze: [72b670e](https://github.com/stephenberry/glaze/commit/72b670e)  
| Simdjson: [20b2871](https://github.com/simdjson/simdjson/commit/20b2871)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX2` |
| simdjson (ondemand) | `haswell` |
| Glaze (utf8-validation) | `AVX2` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (AMD EPYC 7763 64-Core Processor-AVX2): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.5% AND mean shift < 1% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them? We perform scalar iteration)

#### Note:
  These benchmarks were executed using the CPU benchmark library [benchmarksuite](https://github.com/realtimechris/benchmarksuite).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 606.565 | 0.0543376 | 8.21614ms | 1811 | 128 | 306.403 | 2847.35 | 3.79442 | 1(Win) |
| glaze | 489.959 | 0.0998135 | 1.16406ms | 1811 | 30 | 371.379 | 3525 | 4.70918 | 2(Loss) |
| simdjson (ondemand) | 149.522 | 0.280821 | 2.99281ms | 1811 | 30 | 31565.4 | 11550.9 | 15.5478 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 347.161 | 0.138177 | 1.46543ms | 1811 | 30 | 1417.65 | 4974.93 | 6.66497 | 1(Win) |
| glaze | 293.43 | 0.318876 | 1.69591ms | 1798 | 30 | 10416.9 | 5843.67 | 7.89954 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1338.93 | 0.106995 | 0.870428ms | 3873 | 30 | 261.352 | 2758.6 | 1.71724 | 1(Win) |
| glaze | 978.683 | 0.665526 | 1.17359ms | 3873 | 30 | 18926.2 | 3774.03 | 2.35809 | 2(Loss) |
| simdjson (ondemand) | 350.715 | 0.171262 | 6.33577ms | 3873 | 32 | 10410.1 | 10531.6 | 6.62433 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1430.62 | 0.0671999 | 0.960525ms | 3873 | 30 | 90.3034 | 2581.8 | 1.60658 | 1(Win) |
| glaze | 1139.68 | 0.125991 | 4.52379ms | 3873 | 64 | 1067.07 | 3240.91 | 2.0228 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1339.24 | 0.26434 | 1.93788ms | 3862 | 32 | 1691.15 | 2750.12 | 1.71725 | 1(Win) |
| glaze | 793.359 | 0.103282 | 1.40924ms | 3862 | 30 | 689.697 | 4642.4 | 2.91499 | 2(Loss) |
| simdjson (ondemand) | 349.979 | 0.238854 | 6.33989ms | 3862 | 32 | 20218.8 | 10523.8 | 6.64044 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1694.79 | 0.175822 | 1.57371ms | 3862 | 32 | 467.19 | 2173.19 | 1.35024 | 1(Win) |
| glaze | 1021.37 | 0.102479 | 1.15717ms | 3862 | 30 | 409.689 | 3606.03 | 2.26069 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 643.654 | 0.225022 | 0.622063ms | 905 | 30 | 273.128 | 1340.9 | 3.52659 | 1(Win) |
| glaze | 418.928 | 0.183181 | 0.804143ms | 905 | 30 | 427.269 | 2060.2 | 5.46486 | 2(Loss) |
| simdjson (ondemand) | 118.139 | 0.296169 | 2.11165ms | 905 | 30 | 14044.7 | 7305.6 | 19.6444 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 433.249 | 0.442026 | 0.778766ms | 905 | 30 | 2326.16 | 1992.1 | 5.28442 | 1(Win) |
| glaze | 300.009 | 0.120841 | 0.973269ms | 905 | 30 | 362.557 | 2876.83 | 7.67131 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1983.73 | 0.0855954 | 3.0805ms | 9578 | 32 | 497.088 | 4604.59 | 1.16593 | 1(Win) |
| glaze | 1476.85 | 0.0748526 | 1.78418ms | 9578 | 30 | 642.999 | 6184.97 | 1.56947 | 2(Loss) |
| simdjson (ondemand) | 772.539 | 0.0812304 | 3.19506ms | 9578 | 30 | 2767.37 | 11823.7 | 3.00898 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2486.56 | 0.14874 | 1.21194ms | 9578 | 30 | 895.637 | 3673.47 | 0.928016 | 1(Win) |
| glaze | 2290.53 | 0.644954 | 2.76152ms | 9578 | 32 | 21168.2 | 3987.84 | 1.00825 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2941.62 | 0.237336 | 6.59163ms | 33713 | 32 | 21532.6 | 10929.8 | 0.790126 | 1(Win) |
| simdjson (ondemand) | 2645.74 | 0.0470019 | 7.40047ms | 33713 | 32 | 1043.96 | 12152.1 | 0.879081 | 2(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 3482.32 | 2.26621 | 3.46805ms | 48024 | 30 | 2.66503e+06 | 13151.9 | 0.66787 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3360.8 | 0.0551449 | 3.62452ms | 48024 | 30 | 1694.19 | 13627.5 | 0.692119 | 1(Tie) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1149.55 | 0.399003 | 59.3804ms | 294588 | 30 | 2.85267e+07 | 244393 | 2.02821 | 1(Win) |
| glaze | 1011.94 | 0.355401 | 67.3832ms | 294588 | 30 | 2.92063e+07 | 277625 | 2.30402 | 2(Loss) |
| simdjson (ondemand) | 751.63 | 0.329358 | 90.4584ms | 294588 | 30 | 4.54654e+07 | 373776 | 3.1022 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2510.72 | 0.681549 | 27.5829ms | 294588 | 30 | 1.74482e+07 | 111897 | 0.928413 | 1(Win) |
| glaze | 1944.44 | 0.643811 | 35.4611ms | 294588 | 30 | 2.59585e+07 | 144484 | 1.19882 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1221.12 | 0.452718 | 76.6033ms | 406546 | 30 | 6.19838e+07 | 317505 | 1.90938 | 1(Win) |
| jsonifier | 1185.6 | 0.374916 | 79.5299ms | 406546 | 30 | 4.50956e+07 | 327018 | 1.96664 | 2(Loss) |
| simdjson (ondemand) | 989.629 | 0.428775 | 94.3394ms | 406546 | 30 | 8.46554e+07 | 391776 | 2.35609 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2360.1 | 0.734104 | 39.867ms | 406546 | 30 | 4.36311e+07 | 164278 | 0.987794 | 1(Win) |
| glaze | 1866.85 | 0.551179 | 50.5267ms | 406546 | 30 | 3.93102e+07 | 207682 | 1.24887 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2772.29 | 2.48783 | 6.78616ms | 33713 | 32 | 2.66383e+06 | 11597.3 | 0.838499 | 1(Win) |
| simdjson (ondemand) | 2018.04 | 0.171473 | 4.1901ms | 33713 | 30 | 22389.7 | 15931.9 | 1.15304 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3397.6 | 2.17668 | 3.47137ms | 48024 | 30 | 2.58275e+06 | 13479.9 | 0.684448 | 1(Win) |
| simdjson (ondemand) | 2636.94 | 0.0332367 | 10.2617ms | 48024 | 32 | 1066.35 | 17368.3 | 0.882628 | 2(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1003.48 | 0.386692 | 67.7432ms | 294588 | 30 | 3.51609e+07 | 279966 | 2.32356 | 1(Win) |
| jsonifier | 924.311 | 0.331165 | 73.5637ms | 294588 | 30 | 3.03951e+07 | 303946 | 2.52265 | 2(Loss) |
| simdjson (ondemand) | 259.636 | 0.16525 | 259.767ms | 294588 | 30 | 9.59195e+07 | 1.08206e+06 | 8.98158 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2646.84 | 0.538804 | 26.2533ms | 294588 | 30 | 9.812e+06 | 106142 | 0.880633 | 1(Win) |
| glaze | 2138.09 | 0.654413 | 32.7201ms | 294588 | 30 | 2.21821e+07 | 131398 | 1.09024 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1288.34 | 0.310741 | 72.6999ms | 406546 | 30 | 2.62346e+07 | 300939 | 1.80983 | 1(Win) |
| jsonifier | 1077.74 | 0.322975 | 86.9999ms | 406546 | 30 | 4.04993e+07 | 359744 | 2.16358 | 2(Loss) |
| simdjson (ondemand) | 355.578 | 0.265929 | 261.095ms | 406546 | 30 | 2.52234e+08 | 1.09037e+06 | 6.55824 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2448.82 | 0.457015 | 38.5656ms | 406546 | 30 | 1.57068e+07 | 158326 | 0.951981 | 1(Win) |
| glaze | 1888.2 | 0.489336 | 50.6206ms | 406546 | 30 | 3.02872e+07 | 205334 | 1.23473 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 659.744 | 0.950617 | 33.4683ms | 94651 | 30 | 5.07496e+07 | 136820 | 3.53327 | 1(Win) |
| glaze | 621.552 | 0.460407 | 35.2669ms | 94651 | 30 | 1.34122e+07 | 145227 | 3.75058 | 2(Loss) |
| simdjson (ondemand) | 512.373 | 0.576799 | 42.7373ms | 94651 | 30 | 3.09777e+07 | 176173 | 4.5502 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2587.71 | 1.74103 | 8.43392ms | 94651 | 30 | 1.10651e+07 | 34882.7 | 0.899695 | 1(Win) |
| jsonifier | 2430.23 | 0.839488 | 21.6227ms | 94651 | 32 | 3.11125e+06 | 37143.1 | 0.958286 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 820.391 | 0.468985 | 38.7942ms | 136024 | 30 | 1.64979e+07 | 158123 | 2.84164 | 1(Win) |
| jsonifier | 781.875 | 0.446199 | 40.8391ms | 136024 | 30 | 1.64413e+07 | 165912 | 2.98182 | 2(Loss) |
| simdjson (ondemand) | 718.226 | 0.497334 | 44.0482ms | 136024 | 30 | 2.42062e+07 | 180615 | 3.24619 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2494.92 | 0.665372 | 13.0237ms | 136024 | 30 | 3.59061e+06 | 51994.7 | 0.933694 | 1(Win) |
| glaze | 1842.34 | 0.748009 | 17.6358ms | 136046 | 30 | 8.32462e+06 | 70423.1 | 1.26478 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 457.778 | 0.183589 | 1041.37ms | 2090234 | 30 | 1.91732e+09 | 4.35452e+06 | 5.09437 | 1(Win) |
| glaze | 379.831 | 0.0979311 | 1259.89ms | 2090234 | 30 | 7.92449e+08 | 5.24813e+06 | 6.13984 | 2(Loss) |
| simdjson (ondemand) | 256.796 | 0.111174 | 1866.15ms | 2090234 | 30 | 2.2343e+09 | 7.7626e+06 | 9.08152 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 683.941 | 0.177026 | 701.002ms | 2090234 | 30 | 7.98631e+08 | 2.91458e+06 | 3.40977 | 1(Win) |
| glaze | 655.495 | 0.100389 | 730.321ms | 2090234 | 30 | 2.79608e+08 | 3.04107e+06 | 3.55773 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 972.412 | 0.427153 | 1568.32ms | 6661897 | 30 | 2.33659e+10 | 6.53353e+06 | 2.39826 | 1(Win) |
| jsonifier | 963.537 | 0.0480221 | 1585.18ms | 6661897 | 30 | 3.0079e+08 | 6.59371e+06 | 2.42036 | 2(Loss) |
| simdjson (ondemand) | 779.509 | 0.0870188 | 1962.88ms | 6661897 | 30 | 1.50904e+09 | 8.15036e+06 | 2.99174 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2027.65 | 0.110341 | 754.909ms | 6661897 | 30 | 3.58594e+08 | 3.13332e+06 | 1.15013 | 1(Win) |
| glaze | 1436.49 | 0.112265 | 1071.71ms | 6661897 | 30 | 7.39604e+08 | 4.42277e+06 | 1.62343 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 987.294 | 0.270878 | 116.367ms | 500299 | 30 | 5.14086e+07 | 483263 | 2.36185 | 1(Win) |
| glaze | 839.855 | 0.193724 | 138.544ms | 500299 | 30 | 3.63361e+07 | 568101 | 2.77653 | 2(Loss) |
| simdjson (ondemand) | 496.079 | 0.100222 | 231.203ms | 500299 | 30 | 2.78742e+07 | 961787 | 4.70084 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2009.78 | 0.472368 | 57.8048ms | 500299 | 30 | 3.77264e+07 | 237401 | 1.16011 | 1(Win) |
| jsonifier | 1926.14 | 0.493527 | 60.047ms | 500299 | 30 | 4.48363e+07 | 247710 | 1.2105 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1756.57 | 0.151128 | 188.349ms | 1439562 | 30 | 4.18542e+07 | 781563 | 1.32755 | 1(Win) |
| glaze | 1549.96 | 0.136628 | 213.189ms | 1439562 | 30 | 4.39362e+07 | 885748 | 1.50455 | 2(Loss) |
| simdjson (ondemand) | 1302.42 | 0.123843 | 253.701ms | 1439562 | 30 | 5.11237e+07 | 1.0541e+06 | 1.79051 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3868.86 | 0.552722 | 85.7388ms | 1439562 | 30 | 1.15406e+08 | 354852 | 0.602695 | 1(Win) |
| glaze | 2103.44 | 0.307897 | 160.186ms | 1439584 | 30 | 1.21156e+08 | 652689 | 1.10863 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 950.049 | 0.90185 | 14.0339ms | 56369 | 30 | 7.8123e+06 | 56584.1 | 2.45287 | 1(Win) |
| glaze | 823.339 | 0.911925 | 16.1176ms | 56369 | 30 | 1.06356e+07 | 65292.2 | 2.83003 | 2(Loss) |
| simdjson (ondemand) | 574.766 | 0.817598 | 23.0454ms | 56369 | 30 | 1.75428e+07 | 93529.7 | 4.0536 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1963.58 | 1.27783 | 6.87739ms | 56369 | 30 | 3.67158e+06 | 27377.4 | 1.18599 | 1(Win) |
| jsonifier | 1721.2 | 1.18497 | 7.82093ms | 56369 | 30 | 4.10921e+06 | 31232.7 | 1.35337 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1171.28 | 0.929175 | 18.8672ms | 94370 | 30 | 1.52918e+07 | 76837.2 | 1.98951 | 1(Win) |
| glaze | 1070.78 | 0.603272 | 20.7271ms | 94370 | 30 | 7.71289e+06 | 84049.5 | 2.17644 | 2(Loss) |
| simdjson (ondemand) | 943.626 | 0.525388 | 23.7408ms | 94370 | 30 | 7.53268e+06 | 95374.9 | 2.47001 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2551.19 | 1.48198 | 8.72542ms | 94370 | 30 | 8.19956e+06 | 35277 | 0.913079 | 1(Win) |
| glaze | 1747.07 | 0.996917 | 12.716ms | 94370 | 30 | 7.91205e+06 | 51513.9 | 1.33368 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 712.199 | 1.02288 | 17.2149ms | 52708 | 30 | 1.56359e+07 | 70579 | 3.27162 | 1(Tie) |
| jsonifier STATISTICAL TIE | 702.169 | 1.25105 | 17.6544ms | 52708 | 30 | 2.40624e+07 | 71587.2 | 3.31823 | 1(Tie) |
| simdjson (ondemand) | 650.121 | 0.905668 | 18.9783ms | 52708 | 30 | 1.47104e+07 | 77318.3 | 3.58439 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2675.7 | 1.19692 | 22.8765ms | 52708 | 64 | 3.23586e+06 | 18786.2 | 0.869752 | 1(Win) |
| jsonifier | 2423.26 | 1.72135 | 25.2604ms | 52708 | 64 | 8.15969e+06 | 20743.2 | 0.95987 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 876.818 | 0.781914 | 19.0989ms | 70103 | 30 | 1.06633e+07 | 76247.8 | 2.65775 | 1(Win) |
| glaze | 826.577 | 1.25424 | 19.5483ms | 70103 | 30 | 3.08739e+07 | 80882.2 | 2.81903 | 2(Loss) |
| jsonifier | 663.974 | 2.48632 | 24.157ms | 70103 | 30 | 1.88021e+08 | 100690 | 3.50561 | 3(Loss) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2870.08 | 0.0987064 | 6.17009ms | 70103 | 30 | 15859.7 | 23293.9 | 0.811075 | 1(Win) |
| glaze | 2475.44 | 0.11557 | 6.93459ms | 70103 | 30 | 29226.7 | 27007.5 | 0.940734 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 749.782 | 0.0448083 | 3.94864ms | 11812 | 30 | 1359.61 | 15024.1 | 3.10309 | 1(Win) |
| glaze | 604.988 | 0.356019 | 4.88295ms | 11812 | 30 | 131832 | 18619.9 | 3.84729 | 2(Loss) |
| simdjson (ondemand) | 455.286 | 1.23049 | 6.26145ms | 11812 | 30 | 2.7807e+06 | 24742.3 | 5.11475 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2507.45 | 0.182738 | 2.98874ms | 11812 | 32 | 2156.71 | 4492.53 | 0.922812 | 1(Win) |
| glaze | 1220.37 | 0.128071 | 2.49803ms | 11812 | 30 | 4192.64 | 9230.67 | 1.90305 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1355.09 | 0.129012 | 5.62575ms | 31235 | 30 | 24128.2 | 21982.3 | 1.71807 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1141.24 | 1.12191 | 6.60653ms | 31235 | 30 | 2.57254e+06 | 26101.4 | 2.04071 | 2(Tie) |
| glaze STATISTICAL TIE | 1128.06 | 1.19305 | 6.71743ms | 31235 | 30 | 2.97754e+06 | 26406.4 | 2.06443 | 2(Tie) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3027.52 | 0.249465 | 2.66585ms | 31235 | 30 | 18073.7 | 9839.07 | 0.767329 | 1(Win) |
| glaze | 1886.81 | 0.321004 | 4.09976ms | 31235 | 30 | 77049.5 | 15787.5 | 1.23304 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1975.05 | 1.59618 | 12.922ms | 108313 | 30 | 2.09068e+07 | 52300.1 | 1.17988 | 1(Win) |
| glaze | 979.743 | 1.64696 | 25.1975ms | 108313 | 30 | 9.04533e+07 | 105431 | 2.37922 | 2(Loss) |
| simdjson (ondemand) | 727.531 | 0.471649 | 34.5815ms | 108313 | 30 | 1.3453e+07 | 141981 | 3.20442 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1983.89 | 0.899823 | 12.8975ms | 108313 | 30 | 6.58507e+06 | 52067 | 1.17467 | 1(Win) |
| glaze | 1745.96 | 0.86029 | 14.6256ms | 108313 | 30 | 7.7715e+06 | 59162.5 | 1.33483 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1554.19 | 0.59443 | 32.0616ms | 213963 | 30 | 1.82722e+07 | 131291 | 1.49985 | 1(Win) |
| glaze | 1488.32 | 0.783727 | 33.4229ms | 213963 | 30 | 3.46369e+07 | 137102 | 1.56637 | 2(Loss) |
| simdjson (ondemand) | 1339.54 | 0.526114 | 36.9333ms | 213963 | 30 | 1.92684e+07 | 152329 | 1.74044 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2980.66 | 1.18119 | 16.6158ms | 213963 | 30 | 1.96163e+07 | 68458.4 | 0.781811 | 1(Win) |
| glaze | 1677.05 | 0.582511 | 29.5685ms | 213963 | 30 | 1.507e+07 | 121672 | 1.38991 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 503.837 | 0.117855 | 834.82ms | 1834197 | 30 | 5.02264e+08 | 3.47181e+06 | 4.62864 | 1(Win) |
| glaze | 346.02 | 0.282884 | 1208.68ms | 1834197 | 30 | 6.13516e+09 | 5.05527e+06 | 6.73979 | 2(Loss) |
| simdjson (ondemand) | 210.96 | 0.0627121 | 1990.47ms | 1834197 | 30 | 8.11179e+08 | 8.29175e+06 | 11.0547 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 387.254 | 0.0832606 | 1083.32ms | 1833577 | 30 | 4.2404e+08 | 4.51547e+06 | 6.02216 | 1(Win) |
| jsonifier | 383.444 | 0.0522528 | 1103.22ms | 1834197 | 30 | 1.70462e+08 | 4.56188e+06 | 6.082 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1553.26 | 0.0930037 | 1468.42ms | 9930848 | 30 | 9.64729e+08 | 6.09736e+06 | 1.50141 | 1(Win) |
| glaze | 1385.65 | 0.180908 | 1666.93ms | 9930848 | 30 | 4.58672e+09 | 6.83493e+06 | 1.68304 | 2(Loss) |
| simdjson (ondemand) | 1065.03 | 0.0569211 | 2143.65ms | 9930848 | 30 | 7.68632e+08 | 8.89254e+06 | 2.18971 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1632.65 | 0.232407 | 1398.42ms | 9930848 | 30 | 5.4526e+09 | 5.80086e+06 | 1.42841 | 1(Win) |
| glaze | 1322.11 | 0.301939 | 1751.49ms | 9930228 | 30 | 1.40328e+10 | 7.16296e+06 | 1.76386 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 831.309 | 0.280931 | 176.506ms | 642697 | 30 | 1.28709e+08 | 737299 | 2.80516 | 1(Win) |
| glaze | 754.769 | 0.307054 | 194.931ms | 642697 | 30 | 1.86524e+08 | 812068 | 3.08963 | 2(Loss) |
| simdjson (ondemand) | 354.683 | 0.12164 | 416.346ms | 642697 | 30 | 1.32558e+08 | 1.72809e+06 | 6.57505 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 707.945 | 0.120648 | 208.409ms | 642697 | 30 | 3.27322e+07 | 865779 | 3.29401 | 1(Win) |
| glaze | 628.757 | 0.0889199 | 234.623ms | 642692 | 30 | 2.25403e+07 | 974810 | 3.70883 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1199.7 | 0.0983241 | 234.622ms | 1225964 | 30 | 2.75453e+07 | 974548 | 1.94381 | 1(Win) |
| glaze | 1144.28 | 0.274174 | 244.339ms | 1225964 | 30 | 2.35432e+08 | 1.02175e+06 | 2.03796 | 2(Loss) |
| simdjson (ondemand) | 654.271 | 0.168614 | 428.771ms | 1225964 | 30 | 2.72364e+08 | 1.78698e+06 | 3.56435 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1061.82 | 0.194383 | 263.628ms | 1225964 | 30 | 1.37434e+08 | 1.1011e+06 | 2.19624 | 1(Win) |
| glaze | 1043.81 | 0.118641 | 271.066ms | 1225970 | 30 | 5.29792e+07 | 1.1201e+06 | 2.23415 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 602.268 | 0.153133 | 157.157ms | 409725 | 30 | 2.96118e+07 | 648788 | 3.87179 | 1(Win) |
| glaze | 416.03 | 0.187211 | 226.294ms | 409725 | 30 | 9.27515e+07 | 939221 | 5.60538 | 2(Loss) |
| simdjson (ondemand) | 408.939 | 0.386222 | 229.233ms | 409725 | 30 | 4.08567e+08 | 955508 | 5.70253 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1383.55 | 0.403609 | 68.8478ms | 409725 | 30 | 3.89799e+07 | 282422 | 1.6853 | 1(Win) |
| jsonifier | 1201.56 | 0.292768 | 78.8481ms | 409725 | 30 | 2.71935e+07 | 325198 | 1.94055 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 773.463 | 0.115534 | 233.338ms | 785750 | 30 | 3.75864e+07 | 968824 | 3.015 | 1(Win) |
| simdjson (ondemand) | 759.927 | 0.228591 | 237.578ms | 785750 | 30 | 1.52428e+08 | 986081 | 3.06872 | 2(Loss) |
| glaze | 658.958 | 0.201474 | 273.631ms | 785750 | 30 | 1.57476e+08 | 1.13717e+06 | 3.53893 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2047.94 | 0.269651 | 88.4231ms | 785750 | 30 | 2.92051e+07 | 365903 | 1.13858 | 1(Win) |
| glaze | 1630.6 | 0.314775 | 110.421ms | 785750 | 30 | 6.27764e+07 | 459554 | 1.43003 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 747.8 | 0.212112 | 2640.91ms | 8587914 | 30 | 1.61904e+10 | 1.09522e+07 | 3.1186 | 1(Win) |
| glaze | 627.539 | 0.471239 | 3169.49ms | 8587914 | 30 | 1.13475e+11 | 1.30511e+07 | 3.71626 | 2(Loss) |
| simdjson (ondemand) | 545.452 | 0.663023 | 3537ms | 8587914 | 30 | 2.97331e+11 | 1.50152e+07 | 4.27548 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2017.25 | 0.461208 | 956.686ms | 8588126 | 30 | 1.05195e+10 | 4.06012e+06 | 1.15601 | 1(Win) |
| jsonifier | 1231.78 | 0.406388 | 1594.64ms | 8588126 | 30 | 2.19047e+10 | 6.64916e+06 | 1.89294 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 675.248 | 0.787056 | 3248.63ms | 9804437 | 30 | 3.56329e+11 | 1.38471e+07 | 3.45357 | 1(Win) |
| glaze | 655.551 | 0.538086 | 3487.01ms | 9804437 | 30 | 1.76708e+11 | 1.42632e+07 | 3.55744 | 2(Loss) |
| simdjson (ondemand) | 586.985 | 0.490957 | 3757.86ms | 9804437 | 30 | 1.83485e+11 | 1.59293e+07 | 3.97297 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1967.07 | 0.247505 | 1287.47ms | 11078090 | 30 | 5.30129e+09 | 5.37088e+06 | 1.18548 | 1(Win) |
| jsonifier | 1341.66 | 0.2158 | 1939.6ms | 11078090 | 30 | 8.66308e+09 | 7.87452e+06 | 1.73794 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 2561.53 | 0.638621 | 24.0372ms | 264040 | 30 | 1.18236e+07 | 98303.8 | 0.909907 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2550.4 | 2.33137 | 23.3914ms | 264040 | 30 | 1.58953e+08 | 98732.9 | 0.91381 | 1(Tie) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 3384.19 | 0.621552 | 27.4871ms | 399947 | 30 | 1.47222e+07 | 112706 | 0.688741 | 1(Tie) |
| jsonifier STATISTICAL TIE | 3366.73 | 0.514566 | 28.8723ms | 399947 | 30 | 1.01951e+07 | 113291 | 0.692335 | 1(Tie) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 910.407 | 0.460488 | 67.2285ms | 264040 | 30 | 4.86661e+07 | 276589 | 2.56107 | 1(Win) |
| glaze | 829.29 | 0.32703 | 73.4012ms | 264040 | 30 | 2.95816e+07 | 303643 | 2.81156 | 2(Loss) |
| simdjson (ondemand) | 708.605 | 0.280073 | 86.8021ms | 264040 | 30 | 2.97162e+07 | 355358 | 3.29064 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2387.97 | 0.704708 | 27.2467ms | 264040 | 30 | 1.65661e+07 | 105448 | 0.976233 | 1(Win) |
| glaze | 2277.48 | 0.741953 | 26.8341ms | 263923 | 30 | 2.01707e+07 | 110516 | 1.02342 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1029.39 | 0.348512 | 90.1542ms | 399947 | 30 | 5.00265e+07 | 370528 | 2.26506 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1022.37 | 0.380556 | 91.9584ms | 399947 | 30 | 6.0471e+07 | 373073 | 2.28079 | 1(Tie) |
| jsonifier | 969.902 | 0.49238 | 95.8661ms | 399947 | 30 | 1.12479e+08 | 393256 | 2.40395 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3059.91 | 0.564206 | 30.4617ms | 399947 | 30 | 1.48383e+07 | 124650 | 0.761883 | 1(Win) |
| glaze | 2289.82 | 0.630036 | 40.854ms | 399830 | 30 | 3.30219e+07 | 166523 | 1.0181 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1423.64 | 0.287295 | 75.5667ms | 466906 | 30 | 2.42235e+07 | 312773 | 1.63787 | 1(Win) |
| jsonifier | 1300.31 | 0.314112 | 82.7802ms | 466906 | 30 | 3.47102e+07 | 342439 | 1.79316 | 2(Loss) |
| simdjson (ondemand) | 644.528 | 0.184163 | 166.957ms | 466906 | 30 | 4.85624e+07 | 690856 | 3.61796 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1884.95 | 0.27443 | 85.4727ms | 699405 | 30 | 2.82906e+07 | 353858 | 1.23707 | 1(Win) |
| jsonifier | 1783.58 | 0.285291 | 91.3195ms | 699405 | 30 | 3.41485e+07 | 373970 | 1.3073 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2415.12 | 0.44396 | 60.206ms | 631514 | 30 | 3.67705e+07 | 249371 | 0.965447 | 1(Win) |
| glaze | 1543.5 | 0.267216 | 94.1659ms | 631514 | 30 | 3.26135e+07 | 390189 | 1.51074 | 2(Loss) |
