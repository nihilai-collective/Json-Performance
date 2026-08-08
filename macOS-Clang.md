# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.5.0 using the Clang 22.1.8 compiler).  

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

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 692.356 | 2.05443 | 29.5429ms | 1811 | 30 | 78792.1 | 2494.53 | 1(Win) |
| glaze | 463.051 | 1.00146 | 12.5529ms | 1811 | 128 | 178588 | 3729.84 | 2(Loss) |
| simdjson (ondemand) | 165.448 | 1.83118 | 3.27158ms | 1811 | 30 | 1.09622e+06 | 10438.9 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 502.474 | 0.911108 | 11.8207ms | 1811 | 128 | 125534 | 3437.2 | 1(Win) |
| glaze | 382.478 | 0.160971 | 2.80467ms | 1798 | 32 | 1666.52 | 4483.16 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1540.84 | 0.793351 | 9.1425ms | 3873 | 128 | 46293.7 | 2397.12 | 1(Win) |
| glaze | 846.666 | 2.02838 | 1.21579ms | 3873 | 30 | 234903 | 4362.5 | 2(Loss) |
| simdjson (ondemand) | 378.554 | 2.03025 | 2.99996ms | 3873 | 30 | 1.17722e+06 | 9757.07 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1597.27 | 2.02618 | 1.48042ms | 3873 | 32 | 70250.2 | 2312.44 | 1(Win) |
| glaze | 885.291 | 1.91728 | 1.72292ms | 3873 | 30 | 191963 | 4172.17 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1668.82 | 0.109769 | 0.8365ms | 3862 | 30 | 176.069 | 2207 | 1(Win) |
| glaze | 927.863 | 0.333453 | 1.14813ms | 3862 | 30 | 5255.91 | 3969.43 | 2(Loss) |
| simdjson (ondemand) | 381.233 | 1.86819 | 2.32662ms | 3862 | 30 | 977255 | 9661 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1380.4 | 0.960557 | 0.723459ms | 3862 | 30 | 19705.3 | 2668.13 | 1(Win) |
| glaze | 1047.26 | 1.70404 | 0.94225ms | 3862 | 30 | 107743 | 3516.87 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1220.87 | 0.195153 | 0.343125ms | 905 | 30 | 57.0989 | 706.933 | 1(Win) |
| glaze | 337.358 | 0.371376 | 0.783083ms | 905 | 30 | 2708.09 | 2558.33 | 2(Loss) |
| simdjson (ondemand) | 188.082 | 0.376353 | 1.25008ms | 905 | 30 | 8947.8 | 4588.83 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 627.037 | 1.42501 | 0.483708ms | 905 | 30 | 11541.6 | 1376.43 | 1(Win) |
| glaze | 322.72 | 0.214457 | 1.75921ms | 905 | 32 | 1052.63 | 2674.38 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1803.83 | 2.0185 | 1.41333ms | 9578 | 30 | 313429 | 5063.83 | 1(Win) |
| glaze | 1260.88 | 1.80848 | 1.88563ms | 9578 | 30 | 514938 | 7244.4 | 2(Loss) |
| simdjson (ondemand) | 609.573 | 2.30285 | 3.87208ms | 9578 | 30 | 3.57232e+06 | 14984.7 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2368.3 | 2.05276 | 1.14096ms | 9578 | 30 | 188050 | 3856.9 | 1(Win) |
| glaze | 2070.8 | 0.815425 | 1.15ms | 9578 | 30 | 38811.8 | 4411 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3828.19 | 0.0565115 | 2.38983ms | 33713 | 30 | 675.775 | 8398.53 | 1(Win) |
| simdjson (ondemand) | 2491.54 | 1.78015 | 3.39613ms | 33713 | 30 | 1.58304e+06 | 12904.1 | 2(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3596.01 | 1.84497 | 3.31917ms | 48024 | 30 | 1.65643e+06 | 12736.1 | 1(Win) |
| simdjson (ondemand) | 3336.57 | 1.86701 | 3.48317ms | 48024 | 30 | 1.97029e+06 | 13726.4 | 2(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1113.73 | 0.746921 | 54.337ms | 294588 | 30 | 1.06498e+08 | 252253 | 1(Win) |
| glaze | 949.575 | 0.84172 | 71.242ms | 294588 | 30 | 1.86049e+08 | 295860 | 2(Loss) |
| simdjson (ondemand) | 809.735 | 2.45543 | 102.116ms | 294588 | 30 | 2.17731e+09 | 346954 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2674.78 | 1.38799 | 26.574ms | 294588 | 30 | 6.37597e+07 | 105033 | 1(Win) |
| glaze | 2491.26 | 0.210678 | 28.1088ms | 294588 | 30 | 1.69338e+06 | 112771 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1418.99 | 0.577343 | 67.5946ms | 406546 | 30 | 7.4653e+07 | 273231 | 1(Win) |
| simdjson (ondemand) | 1370.14 | 0.811836 | 181.956ms | 406546 | 32 | 1.6888e+08 | 282974 | 2(Loss) |
| jsonifier | 1307.12 | 1.5492 | 78.0328ms | 406546 | 30 | 6.33469e+08 | 296615 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3102.18 | 1.25298 | 31.9805ms | 406546 | 30 | 7.3569e+07 | 124980 | 1(Win) |
| glaze | 2176.46 | 1.10053 | 43.5403ms | 406546 | 30 | 1.15303e+08 | 178139 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3268.26 | 2.00187 | 3.68833ms | 33713 | 30 | 1.16347e+06 | 9837.4 | 1(Win) |
| simdjson (ondemand) | 2010.76 | 1.23026 | 19.33ms | 33713 | 64 | 2.47655e+06 | 15989.6 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3969.65 | 1.46725 | 3.00762ms | 48024 | 30 | 859687 | 11537.4 | 1(Win) |
| simdjson (ondemand) | 2699.38 | 1.4985 | 4.31271ms | 48024 | 30 | 1.93921e+06 | 16966.6 | 2(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1230.2 | 0.984278 | 56.6463ms | 294588 | 30 | 1.51577e+08 | 228369 | 1(Tie) |
| glaze STATISTICAL TIE | 1198.92 | 1.02244 | 52.1885ms | 294588 | 30 | 1.72207e+08 | 234329 | 1(Tie) |
| simdjson (ondemand) | 313.076 | 0.758815 | 221.744ms | 294588 | 30 | 1.39099e+09 | 897357 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2845.17 | 1.05263 | 24.8965ms | 294588 | 30 | 3.24108e+07 | 98743.1 | 1(Win) |
| glaze | 2404.26 | 1.34367 | 28.6235ms | 294588 | 30 | 7.3956e+07 | 116851 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1601.09 | 1.30539 | 54.476ms | 406546 | 30 | 2.99771e+08 | 242156 | 1(Win) |
| jsonifier | 1410.69 | 0.76255 | 362.584ms | 406546 | 64 | 2.81108e+08 | 274839 | 2(Loss) |
| simdjson (ondemand) | 387.008 | 1.40816 | 243.808ms | 406546 | 30 | 5.97046e+09 | 1.00182e+06 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2714.76 | 1.03581 | 37.8363ms | 406546 | 30 | 6.56506e+07 | 142817 | 1(Win) |
| glaze | 2310.83 | 0.757402 | 41.0428ms | 406546 | 30 | 4.84459e+07 | 167780 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 765.535 | 0.523752 | 36.3178ms | 94651 | 30 | 1.14418e+07 | 117913 | 1(Win) |
| jsonifier STATISTICAL TIE | 729.301 | 1.34677 | 29.276ms | 94651 | 30 | 8.33571e+07 | 123771 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 708.41 | 0.770709 | 31.8685ms | 94651 | 30 | 2.89323e+07 | 127421 | 2(Tie) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3056.23 | 0.99327 | 17.7959ms | 94651 | 32 | 2.75399e+06 | 29535.2 | 1(Win) |
| glaze | 2782.9 | 0.195723 | 9.42921ms | 94651 | 30 | 120909 | 32436 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1044.96 | 0.78627 | 75.9848ms | 136024 | 32 | 3.04875e+07 | 124141 | 1(Win) |
| simdjson (ondemand) | 956.597 | 1.05653 | 32.1309ms | 136024 | 30 | 6.15823e+07 | 135608 | 2(Loss) |
| jsonifier | 890.884 | 1.00065 | 35.6362ms | 136024 | 30 | 6.3691e+07 | 145611 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2977.19 | 2.05605 | 10.5076ms | 136024 | 30 | 2.40773e+07 | 43572.2 | 1(Win) |
| glaze | 2611.77 | 1.54577 | 14.2508ms | 136046 | 30 | 1.76893e+07 | 49676.4 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 520.288 | 0.628245 | 917.117ms | 2090234 | 30 | 1.73813e+10 | 3.83134e+06 | 1(Win) |
| glaze | 472.581 | 0.408649 | 1111.53ms | 2090234 | 30 | 8.91373e+09 | 4.21812e+06 | 2(Loss) |
| simdjson (ondemand) | 340.937 | 0.630145 | 1440.32ms | 2090234 | 30 | 4.07233e+10 | 5.84683e+06 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1568.9 | 0.532493 | 317.789ms | 2090234 | 30 | 1.37324e+09 | 1.27057e+06 | 1(Win) |
| glaze | 1331.67 | 1.7347 | 360.761ms | 2090234 | 30 | 2.02287e+10 | 1.49692e+06 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1263.31 | 0.609823 | 3002.33ms | 6661897 | 32 | 3.00977e+10 | 5.02907e+06 | 1(Win) |
| glaze | 1167.45 | 0.870388 | 3199.45ms | 6661897 | 32 | 7.17955e+10 | 5.44203e+06 | 2(Loss) |
| simdjson (ondemand) | 866.983 | 2.13905 | 1671.58ms | 6661897 | 30 | 7.37121e+11 | 7.32804e+06 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3092.17 | 0.75239 | 1317.16ms | 6661897 | 32 | 7.64724e+09 | 2.05463e+06 | 1(Win) |
| glaze | 2310.47 | 0.717454 | 746.176ms | 6661897 | 30 | 1.16763e+10 | 2.74978e+06 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1439.61 | 2.25496 | 78.313ms | 500299 | 30 | 1.67559e+09 | 331425 | 1(Win) |
| glaze | 933.762 | 2.23625 | 121.731ms | 500299 | 30 | 3.91697e+09 | 510968 | 2(Loss) |
| simdjson (ondemand) | 660.343 | 0.432555 | 173.235ms | 500299 | 30 | 2.93038e+08 | 722538 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2313.13 | 1.31654 | 47.8967ms | 500299 | 30 | 2.21232e+08 | 206267 | 1(Win) |
| glaze | 1688.17 | 0.801862 | 69.1695ms | 500299 | 30 | 1.54082e+08 | 282628 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1965.93 | 0.66685 | 172.035ms | 1439562 | 30 | 6.50583e+08 | 698333 | 1(Win) |
| glaze | 1855.09 | 1.67182 | 408.408ms | 1439562 | 32 | 4.89846e+09 | 740059 | 2(Loss) |
| simdjson (ondemand) | 1476.41 | 2.30675 | 232.728ms | 1439562 | 30 | 1.38028e+10 | 929870 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4673.5 | 0.412926 | 78.262ms | 1439562 | 30 | 4.41411e+07 | 293757 | 1(Win) |
| glaze | 2513.95 | 0.563696 | 132.045ms | 1439584 | 30 | 2.84296e+08 | 546110 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1667.83 | 0.421693 | 8.90567ms | 56369 | 30 | 554231 | 32232.1 | 1(Win) |
| glaze | 1060.2 | 0.521967 | 12.4012ms | 56369 | 30 | 2.10144e+06 | 50705.4 | 2(Loss) |
| simdjson (ondemand) | 924.026 | 2.07927 | 15.0581ms | 56369 | 30 | 4.3899e+07 | 58177.6 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 2540.57 | 1.7464 | 5.0005ms | 56369 | 30 | 4.09664e+06 | 21159.7 | 1(Tie) |
| glaze STATISTICAL TIE | 2475.41 | 1.09866 | 5.36763ms | 56369 | 30 | 1.70777e+06 | 21716.6 | 1(Tie) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1545.22 | 0.792099 | 14.641ms | 94370 | 30 | 6.3851e+06 | 58243 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1482.03 | 1.90762 | 15.2149ms | 94370 | 30 | 4.02586e+07 | 60726.3 | 1(Tie) |
| simdjson (ondemand) | 1290.42 | 2.04488 | 42.3259ms | 94370 | 32 | 6.50872e+07 | 69743.6 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3458.87 | 1.77072 | 15.4669ms | 94370 | 32 | 6.79277e+06 | 26019.5 | 1(Win) |
| glaze | 2088.57 | 2.2634 | 111.545ms | 94370 | 128 | 1.2176e+08 | 43090.8 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1259.61 | 2.28753 | 23.6562ms | 52708 | 32 | 2.66663e+07 | 39906.2 | 1(Win) |
| glaze STATISTICAL TIE | 1127.43 | 1.33255 | 11.1588ms | 52708 | 30 | 1.05892e+07 | 44584.8 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1096.55 | 1.06672 | 12.7984ms | 52708 | 30 | 7.17325e+06 | 45840.4 | 2(Tie) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3629.71 | 2.04243 | 3.47979ms | 52708 | 30 | 2.40008e+06 | 13848.6 | 1(Win) |
| glaze | 3284.77 | 1.27952 | 3.99179ms | 52708 | 30 | 1.15016e+06 | 15302.8 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1450.58 | 0.781362 | 12.0915ms | 70103 | 30 | 3.89061e+06 | 46088.8 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1375.35 | 1.60125 | 14.2978ms | 70103 | 30 | 1.81756e+07 | 48609.9 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1343.51 | 0.351233 | 33.1389ms | 70103 | 32 | 977533 | 49761.7 | 2(Tie) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4054.19 | 0.0692709 | 4.76296ms | 70103 | 30 | 3914.6 | 16490.4 | 1(Win) |
| glaze | 3138.76 | 2.08071 | 6.53362ms | 70103 | 30 | 5.89253e+06 | 21300 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1180.59 | 1.10669 | 3.58838ms | 11812 | 30 | 334520 | 9541.67 | 1(Win) |
| glaze | 783.707 | 1.02745 | 3.53717ms | 11812 | 30 | 654304 | 14373.7 | 2(Loss) |
| simdjson (ondemand) | 735.159 | 0.0502669 | 9.20421ms | 11812 | 32 | 1898.45 | 15322.9 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3249.27 | 0.105703 | 1.01508ms | 11812 | 30 | 402.878 | 3466.87 | 1(Win) |
| glaze | 1452.49 | 0.125634 | 2.03037ms | 11812 | 30 | 2848.12 | 7755.5 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1665.04 | 1.26726 | 4.4975ms | 31235 | 30 | 1.542e+06 | 17890.2 | 1(Tie) |
| glaze STATISTICAL TIE | 1610.53 | 1.92451 | 4.42242ms | 31235 | 30 | 3.8011e+06 | 18495.8 | 1(Tie) |
| jsonifier | 1513.46 | 1.82735 | 4.86917ms | 31235 | 30 | 3.88066e+06 | 19682.1 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3493.57 | 1.91452 | 2.23721ms | 31235 | 30 | 799441 | 8526.53 | 1(Win) |
| glaze | 2186.93 | 1.59487 | 3.54242ms | 31235 | 30 | 1.41573e+06 | 13620.9 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2288.3 | 1.87899 | 26.8604ms | 108313 | 32 | 2.30215e+07 | 45140.7 | 1(Win) |
| glaze | 1122.21 | 0.442686 | 283.744ms | 108313 | 128 | 2.12529e+07 | 92046.6 | 2(Loss) |
| simdjson (ondemand) | 992.297 | 0.973508 | 25.6354ms | 108313 | 30 | 3.08091e+07 | 104097 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2287.98 | 1.57912 | 10.458ms | 108313 | 30 | 1.52479e+07 | 45147 | 1(Win) |
| glaze | 1594.03 | 1.44211 | 15.5765ms | 108313 | 30 | 2.61991e+07 | 64801.4 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2161.94 | 0.809038 | 23.9398ms | 213963 | 30 | 1.74925e+07 | 94383.4 | 1(Win) |
| glaze | 1948.02 | 0.616658 | 131.483ms | 213963 | 64 | 2.6703e+07 | 104748 | 2(Loss) |
| simdjson (ondemand) | 1779.81 | 1.42786 | 28.4804ms | 213963 | 30 | 8.03934e+07 | 114647 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4418.02 | 1.71795 | 11.5753ms | 213963 | 30 | 1.88871e+07 | 46186.1 | 1(Win) |
| glaze | 1757.46 | 1.28104 | 28.387ms | 213963 | 30 | 6.63668e+07 | 116106 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 565.755 | 0.875295 | 1754.77ms | 1834197 | 32 | 2.34365e+10 | 3.09184e+06 | 1(Win) |
| glaze | 419.888 | 0.798298 | 986.316ms | 1834197 | 30 | 3.318e+10 | 4.16593e+06 | 2(Loss) |
| simdjson (ondemand) | 309.549 | 1.50794 | 1303ms | 1834197 | 30 | 2.17833e+11 | 5.65089e+06 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 745.786 | 0.596719 | 576.449ms | 1834197 | 30 | 5.87658e+09 | 2.34548e+06 | 1(Win) |
| glaze | 686.345 | 1.07972 | 3315.79ms | 1833577 | 64 | 4.84305e+10 | 2.54775e+06 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1800.12 | 1.06325 | 1279.88ms | 9930848 | 30 | 9.38772e+10 | 5.2612e+06 | 1(Win) |
| glaze | 1559.2 | 1.77693 | 1704.83ms | 9930848 | 30 | 3.49487e+11 | 6.07412e+06 | 2(Loss) |
| simdjson (ondemand) | 1328.88 | 2.09972 | 1805.45ms | 9930848 | 30 | 6.71808e+11 | 7.12691e+06 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2432.61 | 1.37434 | 10292.7ms | 9930848 | 128 | 3.66462e+11 | 3.89326e+06 | 1(Win) |
| glaze | 1787.89 | 0.544434 | 1349.14ms | 9930228 | 30 | 2.49487e+10 | 5.29686e+06 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1005.76 | 1.29527 | 155.357ms | 642697 | 30 | 1.86923e+09 | 609412 | 1(Win) |
| glaze | 863.406 | 1.42221 | 518.333ms | 642697 | 32 | 3.26181e+09 | 709891 | 2(Loss) |
| simdjson (ondemand) | 537.69 | 1.60638 | 3069.63ms | 642697 | 128 | 4.29198e+10 | 1.13992e+06 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1118.12 | 0.914378 | 147.334ms | 642697 | 30 | 7.53723e+08 | 548175 | 1(Win) |
| glaze | 862.747 | 1.87947 | 916.996ms | 642692 | 64 | 1.14101e+10 | 710427 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1400.12 | 0.740952 | 216.429ms | 1225964 | 30 | 1.14849e+09 | 835050 | 1(Tie) |
| glaze STATISTICAL TIE | 1393.83 | 1.01268 | 2113.38ms | 1225964 | 128 | 9.23618e+09 | 838821 | 1(Tie) |
| simdjson (ondemand) | 1016.24 | 0.580055 | 622.757ms | 1225964 | 32 | 1.42512e+09 | 1.15049e+06 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2139.3 | 0.817794 | 371.989ms | 1225964 | 32 | 6.3922e+08 | 546521 | 1(Win) |
| glaze | 1452.35 | 0.716035 | 4812.8ms | 1225970 | 256 | 8.50601e+09 | 805023 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 734.787 | 0.666751 | 136.806ms | 409725 | 30 | 3.77148e+08 | 531779 | 1(Win) |
| glaze | 629.837 | 1.13239 | 153.538ms | 409725 | 30 | 1.48061e+09 | 620389 | 2(Loss) |
| simdjson (ondemand) | 590.042 | 2.08788 | 171.005ms | 409725 | 30 | 5.73524e+09 | 662231 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2335.31 | 0.563614 | 1932.05ms | 409725 | 512 | 4.55333e+08 | 167320 | 1(Win) |
| glaze | 1662.76 | 0.356182 | 56.867ms | 409725 | 30 | 2.1018e+07 | 234997 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1202.18 | 0.554975 | 3816ms | 785750 | 256 | 3.06351e+09 | 623327 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 853.319 | 2.43185 | 1234.29ms | 785750 | 64 | 2.91877e+10 | 878159 | 2(Tie) |
| glaze STATISTICAL TIE | 818.159 | 1.62757 | 4754.62ms | 785750 | 256 | 5.68868e+10 | 915897 | 2(Tie) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2735.85 | 0.650463 | 415.56ms | 785750 | 64 | 2.03147e+08 | 273900 | 1(Win) |
| glaze | 1695.31 | 1.00383 | 2424.91ms | 785750 | 256 | 5.04e+09 | 442013 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 612.009 | 1.43464 | 7689.97ms | 8587914 | 32 | 1.17949e+12 | 1.33823e+07 | 1(Win) |
| simdjson (ondemand) | 558.701 | 1.16397 | 3663.13ms | 8587914 | 30 | 8.73419e+11 | 1.46591e+07 | 2(Loss) |
| jsonifier | 529.056 | 2.14773 | 3615.03ms | 8587914 | 30 | 3.3163e+12 | 1.54805e+07 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2025.94 | 2.49656 | 1054.5ms | 8588126 | 30 | 3.05596e+11 | 4.0427e+06 | 1(Win) |
| glaze | 1863.34 | 1.84527 | 11322.4ms | 8588126 | 128 | 8.42061e+11 | 4.39548e+06 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 605.604 | 1.1982 | 8978.98ms | 9804437 | 32 | 1.09516e+12 | 1.54395e+07 | 1(Win) |
| jsonifier STATISTICAL TIE | 568.864 | 1.972 | 18067.2ms | 9804437 | 64 | 6.72393e+12 | 1.64367e+07 | 2(Tie) |
| glaze STATISTICAL TIE | 548.742 | 2.3184 | 3798.46ms | 9804437 | 30 | 4.68174e+12 | 1.70394e+07 | 2(Tie) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 1673.41 | 2.4011 | 7525.43ms | 11078090 | 64 | 1.47071e+12 | 6.31339e+06 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1614.43 | 2.36392 | 1416.24ms | 11078090 | 30 | 7.17929e+11 | 6.54405e+06 | 1(Tie) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3259.81 | 1.222 | 78.6887ms | 264040 | 32 | 2.85134e+07 | 77246.2 | 1(Win) |
| simdjson (ondemand) | 2974.84 | 0.862182 | 73.4916ms | 264040 | 32 | 1.70435e+07 | 84645.9 | 2(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3376.43 | 1.93999 | 643.644ms | 399947 | 256 | 1.2295e+09 | 112965 | 1(Win) |
| simdjson (ondemand) | 2819.97 | 2.44694 | 733.597ms | 399947 | 256 | 2.80416e+09 | 135256 | 2(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1654.12 | 0.529641 | 38.4189ms | 264040 | 30 | 1.95024e+07 | 152231 | 1(Win) |
| glaze STATISTICAL TIE | 1193.36 | 0.538298 | 54.0145ms | 264040 | 30 | 3.87044e+07 | 211007 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1173.55 | 0.959165 | 57.7219ms | 264040 | 30 | 1.2707e+08 | 214569 | 2(Tie) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3729.03 | 1.60523 | 38.9464ms | 264040 | 30 | 3.52485e+07 | 67526.4 | 1(Win) |
| glaze | 2777.64 | 1.1534 | 118.651ms | 263923 | 64 | 6.99103e+07 | 90615.3 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1628.36 | 0.808458 | 56.8624ms | 399947 | 30 | 1.07582e+08 | 234235 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1606.7 | 0.506439 | 1350.76ms | 399947 | 256 | 3.70024e+08 | 237393 | 1(Tie) |
| glaze | 1419.99 | 1.87853 | 443.091ms | 399947 | 64 | 1.62948e+09 | 268607 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4821.99 | 1.57698 | 19.6966ms | 399947 | 30 | 4.66794e+07 | 79100 | 1(Win) |
| glaze | 3207.77 | 1.2395 | 72.8572ms | 399830 | 32 | 6.94687e+07 | 118870 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1601.87 | 1.49089 | 180.609ms | 466906 | 32 | 5.49596e+08 | 277973 | 1(Win) |
| jsonifier | 1418.29 | 1.76778 | 186.544ms | 466906 | 32 | 9.85681e+08 | 313953 | 2(Loss) |
| simdjson (ondemand) | 652.216 | 1.6351 | 179.602ms | 466906 | 30 | 3.73842e+09 | 682712 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2228.53 | 0.632983 | 75.374ms | 699405 | 30 | 1.07678e+08 | 299303 | 1(Win) |
| glaze | 1800.02 | 1.03672 | 93.9683ms | 699405 | 30 | 4.4274e+08 | 370554 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2343.66 | 1.30519 | 1512.24ms | 631514 | 256 | 2.87979e+09 | 256973 | 1(Win) |
| glaze | 1746.17 | 0.573434 | 83.1407ms | 631514 | 30 | 1.1735e+08 | 344903 | 2(Loss) |
