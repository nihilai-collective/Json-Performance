# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36260.0 compiler).  

Latest Results: (Oct 03, 2026)
#### Using the following commits:
----
| Jsonifier: [701dfa9](https://github.com/nihilai-collective/jsonifier/commit/701dfa9)  
| Glaze: [52971fe](https://github.com/stephenberry/glaze/commit/52971fe)  
| Simdjson: [2a690bc](https://github.com/simdjson/simdjson/commit/2a690bc)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX2` |
| simdjson (ondemand) | `haswell` |
| Glaze (utf8-validation) | `AVX2` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |
| Glaze (structural-skip) | `AVX2` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (AMD EPYC 7763 64-Core Processor-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 5.000000% AND mean shift < 2.500000%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

Every iteration constructs a new object to parse into, or a new string to serialize into, and destroys it again inside the timed region, so allocation and deallocation are part of each measurement. Parser instances are reused.

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

`simdjson (reflection)` (simdjson 5's C++26 static-reflection API) is absent from these results because this compiler does not provide P2996 reflection.

`simdjson (ondemand)` extracts each field with an individual `find_field` lookup (`find_field_unordered` for the reverse-order tests) on MSVC/Windows, rather than the `object::for_each` API used on the other platforms, because instantiating `for_each` across these test structures drives MSVC compile times to intractable levels.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [4e7c701](https://github.com/nihilai-collective/benchmarksuite/commit/4e7c701).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 335.827 | 0.331114 | 304.528ms | 905 | 30 | 2172.41 | 2570 | 6.83834 | 1(Win) |
| glaze | 198.323 | 0.0844531 | 468.425ms | 905 | 320 | 4322.49 | 4351.88 | 11.6519 | 2(Loss) |
| simdjson (ondemand) | 60.5919 | 1.12798 | 1504.46ms | 905 | 320 | 8.26072e+06 | 14244.1 | 38.3665 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 518.753 | 0.216096 | 173.666ms | 905 | 320 | 4136.36 | 1663.75 | 4.39368 | 1(Win) |
| glaze | 48.4198 | 0.54179 | 1904.75ms | 905 | 1280 | 1.19378e+07 | 17824.8 | 48.0655 | 2(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 363.219 | 0.198516 | 491.695ms | 1811 | 40 | 3564.1 | 4755 | 6.36612 | 1(Win) |
| glaze | 195.306 | 0.243081 | 912.85ms | 1811 | 4890 | 2.25953e+06 | 8843.09 | 11.8842 | 2(Loss) |
| simdjson (ondemand) | 91.2205 | 0.23869 | 1902.49ms | 1811 | 2560 | 5.22829e+06 | 18933.3 | 25.5143 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 118.032 | 0.0749737 | 1535.21ms | 1811 | 40 | 4814.1 | 14632.5 | 19.7214 | 1(Win) |
| glaze | 73.0379 | 0.25328 | 2359.32ms | 1798 | 4890 | 1.72899e+07 | 23476.9 | 31.8777 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1030.24 | 0.193951 | 374.943ms | 3862 | 40 | 1923.08 | 3575 | 2.24174 | 1(Win) |
| glaze | 451.636 | 0.134293 | 874.633ms | 3862 | 80 | 9594.94 | 8155 | 5.13448 | 2(Loss) |
| simdjson (ondemand) | 213.288 | 0.178187 | 1731.34ms | 3862 | 4890 | 4.62965e+06 | 17268.1 | 10.9091 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 280.378 | 0.337283 | 1335.98ms | 3862 | 1280 | 2.51268e+06 | 13136.2 | 8.29401 | 1(Win) |
| glaze | 190.136 | 0.285724 | 1944.39ms | 3862 | 4890 | 1.49795e+07 | 19370.8 | 12.242 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 567.347 | 0.115339 | 1662.35ms | 9578 | 30 | 10344.8 | 16100 | 4.09731 | 1(Win) |
| glaze | 424.868 | 0.417244 | 2196.75ms | 9578 | 1280 | 1.02999e+07 | 21499.1 | 5.47984 | 2(Loss) |
| simdjson (ondemand) | 345.821 | 0.118663 | 2698.47ms | 9578 | 30 | 29471.3 | 26413.3 | 6.73361 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 657.199 | 0.504872 | 1429.29ms | 9578 | 1280 | 6.30274e+06 | 13898.8 | 3.53908 | 1(Win) |
| glaze | 494.422 | 0.800434 | 1887.8ms | 9578 | 320 | 6.9977e+06 | 18474.7 | 4.70638 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1001.31 | 0.0930555 | 380.319ms | 3873 | 160 | 1885.22 | 3688.75 | 2.30791 | 1(Win) |
| glaze | 537.444 | 0.081752 | 703.45ms | 3873 | 80 | 2525.32 | 6872.5 | 4.3056 | 2(Loss) |
| simdjson (ondemand) | 220.688 | 0.0783671 | 1709.72ms | 3873 | 30 | 5160.92 | 16736.7 | 10.5439 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 289.607 | 0.0520845 | 1311.83ms | 3873 | 80 | 3530.06 | 12753.8 | 8.03145 | 1(Win) |
| glaze | 199.169 | 0.481493 | 1850.93ms | 3873 | 1280 | 1.02057e+07 | 18545 | 11.6855 | 2(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 553.259 | 0.18773 | 5413.92ms | 2090234 | 40 | 1.83003e+09 | 3.60302e+06 | 4.21497 | 1(Win) |
| glaze | 452.652 | 0.100871 | 6651.18ms | 2090234 | 80 | 1.57865e+09 | 4.40383e+06 | 5.15188 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 886.33 | 1.18068 | 5136.37ms | 6661897 | 30 | 2.14879e+11 | 7.16808e+06 | 2.63105 | 1(Win) |
| simdjson (ondemand) | 598.126 | 0.551146 | 7437.76ms | 6661897 | 30 | 1.02817e+11 | 1.0622e+07 | 3.89885 | 2(Loss) |
| glaze | 583.251 | 0.570089 | 7637.99ms | 6661897 | 30 | 1.15689e+11 | 1.08929e+07 | 3.99838 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1347.32 | 0.257793 | 7138.16ms | 6661897 | 80 | 1.1822e+10 | 4.71551e+06 | 1.73082 | 1(Win) |
| glaze | 727.997 | 0.168234 | 6087.92ms | 6661897 | 30 | 6.46677e+09 | 8.72707e+06 | 3.20318 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 728.956 | 0.162175 | 8352.4ms | 500299 | 640 | 7.21117e+08 | 654528 | 3.19885 | 1(Win) |
| glaze | 491.839 | 0.200595 | 6151.86ms | 500299 | 320 | 1.21173e+09 | 970078 | 4.74132 | 2(Loss) |
| simdjson (ondemand) | 262.152 | 0.14361 | 5629.01ms | 500299 | 160 | 1.09307e+09 | 1.82002e+06 | 8.89572 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4321.85 | 0.21637 | 5642.79ms | 500299 | 1280 | 7.30336e+07 | 110398 | 0.539189 | 1(Win) |
| glaze | 1325.75 | 0.274904 | 9246.14ms | 500299 | 160 | 1.5661e+08 | 359889 | 1.75877 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1397.69 | 0.13719 | 6199.57ms | 1439562 | 320 | 5.8108e+08 | 982247 | 1.66838 | 1(Win) |
| glaze | 1056.17 | 0.241785 | 8231.34ms | 1439562 | 160 | 1.58043e+09 | 1.29986e+06 | 2.20797 | 2(Loss) |
| simdjson (ondemand) | 697.722 | 0.0878719 | 6119.59ms | 1439562 | 160 | 4.78317e+08 | 1.96765e+06 | 3.34233 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3331.85 | 0.256839 | 5270.45ms | 1439562 | 320 | 3.58395e+08 | 412046 | 0.699648 | 1(Win) |
| glaze | 1008.63 | 0.328732 | 8625.17ms | 1439584 | 30 | 6.00647e+08 | 1.36115e+06 | 2.31183 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 728.589 | 0.14053 | 7401.16ms | 56369 | 4890 | 5.25726e+07 | 73783.2 | 3.19867 | 1(Win) |
| glaze | 662.493 | 0.252751 | 8125.28ms | 56369 | 1280 | 5.38409e+07 | 81144.5 | 3.5178 | 2(Loss) |
| simdjson (ondemand) | 298.22 | 0.114833 | 9240.01ms | 56369 | 2560 | 1.09694e+08 | 180262 | 7.81735 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4635.28 | 0.0723229 | 1190.37ms | 56369 | 40 | 2814.1 | 11597.5 | 0.500797 | 1(Win) |
| glaze | 1236.99 | 0.142748 | 4358.07ms | 56369 | 4890 | 1.88193e+07 | 43458.6 | 1.8828 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 958.993 | 0.1187 | 9428.8ms | 94370 | 4890 | 6.06798e+07 | 93846.6 | 2.43014 | 1(Win) |
| jsonifier | 796.974 | 0.332862 | 5865.77ms | 94370 | 640 | 9.0425e+07 | 112925 | 2.92431 | 2(Loss) |
| simdjson (ondemand) | 479.044 | 0.141498 | 9580.4ms | 94370 | 2560 | 1.80908e+08 | 187871 | 4.86653 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6408.05 | 0.626943 | 1460.02ms | 94370 | 2560 | 1.98478e+07 | 14044.6 | 0.362717 | 1(Win) |
| glaze | 1173.44 | 0.15324 | 7701.82ms | 94370 | 2560 | 3.53617e+07 | 76696.3 | 1.98564 | 2(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3622.12 | 0.252239 | 321.801ms | 11812 | 40 | 2461.54 | 3110 | 0.636404 | 1(Win) |
| glaze | 1088.61 | 0.264843 | 1041.35ms | 11812 | 4890 | 3.67274e+06 | 10347.9 | 2.13381 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1339.79 | 0.069322 | 2386.81ms | 31235 | 30 | 7126.44 | 22233.3 | 1.73789 | 1(Win) |
| glaze | 1037.55 | 0.145924 | 3079.25ms | 31235 | 30 | 52655.2 | 28710 | 2.24308 | 2(Loss) |
| simdjson (ondemand) | 621.6 | 0.19751 | 4858.4ms | 31235 | 2560 | 2.2934e+07 | 47921.5 | 3.74877 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8191.96 | 0.113031 | 376.052ms | 31235 | 160 | 2702.83 | 3636.25 | 0.282218 | 1(Win) |
| glaze | 1406.02 | 0.270118 | 2122.64ms | 31235 | 2560 | 8.38392e+06 | 21186 | 1.65491 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 846.248 | 0.136509 | 6264.24ms | 108313 | 2560 | 7.10769e+07 | 122063 | 2.75475 | 1(Win) |
| glaze | 699.078 | 0.238701 | 7649.87ms | 108313 | 640 | 7.96155e+07 | 147759 | 3.33459 | 2(Loss) |
| simdjson (ondemand) | 341.208 | 0.163775 | 7784.62ms | 108313 | 640 | 1.57325e+08 | 302734 | 6.8333 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5858.92 | 0.231831 | 1802.74ms | 108313 | 4890 | 8.16917e+06 | 17630.4 | 0.39714 | 1(Win) |
| glaze | 1321.47 | 0.101562 | 7846.67ms | 108313 | 4890 | 3.08188e+07 | 78166.9 | 1.76367 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1051.64 | 0.17067 | 9971.65ms | 213963 | 1280 | 1.40368e+08 | 194032 | 2.21656 | 1(Win) |
| jsonifier | 957.035 | 0.163695 | 5447.31ms | 213963 | 1280 | 1.55919e+08 | 213212 | 2.43612 | 2(Loss) |
| simdjson (ondemand) | 632.357 | 0.113979 | 8297.87ms | 213963 | 1280 | 1.73146e+08 | 322683 | 3.68718 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9196.54 | 0.286281 | 2221.09ms | 213963 | 4890 | 1.97297e+07 | 22187.8 | 0.252994 | 1(Win) |
| glaze | 1331.41 | 0.1339 | 7852.42ms | 213963 | 2560 | 1.07808e+08 | 153259 | 1.75079 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 270.757 | 0.524617 | 9642.13ms | 1834197 | 40 | 4.59492e+10 | 6.4605e+06 | 8.61292 | 1(Win) |
| glaze | 173.362 | 0.694096 | 7011.23ms | 1834197 | 40 | 1.96192e+11 | 1.009e+07 | 13.4514 | 2(Loss) |
| simdjson (ondemand) | 53.5965 | 0.167506 | 9823.21ms | 1834197 | 30 | 8.96609e+10 | 3.26369e+07 | 43.5113 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 386.393 | 0.106919 | 6775.94ms | 1834197 | 40 | 9.37145e+08 | 4.52707e+06 | 6.03536 | 1(Win) |
| glaze | 301.713 | 0.0935408 | 8812.11ms | 1833577 | 30 | 8.81726e+08 | 5.79569e+06 | 7.72926 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1516.14 | 0.142813 | 9402.33ms | 9930848 | 80 | 6.36678e+09 | 6.24667e+06 | 1.53813 | 1(Win) |
| glaze | 928.146 | 0.191351 | 7199.01ms | 9930228 | 30 | 1.14359e+10 | 1.02034e+07 | 2.51257 | 2(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 385.894 | 0.165641 | 6832.01ms | 1834197 | 40 | 2.25503e+09 | 4.53292e+06 | 6.04316 | 1(Win) |
| glaze | 283.953 | 0.157929 | 9230.38ms | 1833577 | 30 | 2.83757e+09 | 6.15818e+06 | 8.21253 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1168.34 | 0.438503 | 5629.75ms | 9930848 | 30 | 3.79052e+10 | 8.10618e+06 | 1.99591 | 1(Win) |
| glaze | 811.55 | 0.361759 | 8237.2ms | 9930848 | 30 | 5.34691e+10 | 1.167e+07 | 2.87353 | 2(Loss) |
| simdjson (ondemand) | 795.634 | 0.439255 | 8324.66ms | 9930848 | 40 | 1.09355e+11 | 1.19034e+07 | 2.9309 | 3(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 483.658 | 0.0739178 | 8052.55ms | 642697 | 320 | 2.80791e+08 | 1.26727e+06 | 4.82163 | 1(Win) |
| simdjson (ondemand) | 432.216 | 0.151386 | 8983.91ms | 642697 | 320 | 1.4748e+09 | 1.4181e+06 | 5.39537 | 2(Loss) |
| glaze | 414.995 | 0.451106 | 9439.04ms | 642697 | 160 | 7.10236e+09 | 1.47694e+06 | 5.61927 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 593.406 | 0.212302 | 6553.82ms | 642697 | 80 | 3.84685e+08 | 1.03289e+06 | 3.92916 | 1(Win) |
| glaze | 515.968 | 0.148052 | 7503.88ms | 642692 | 160 | 4.94889e+08 | 1.1879e+06 | 4.51911 | 2(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1050.92 | 0.208931 | 7036.67ms | 1225964 | 80 | 4.32222e+08 | 1.11252e+06 | 2.21872 | 1(Win) |
| glaze | 769.451 | 0.214373 | 9712.52ms | 1225970 | 30 | 3.18315e+08 | 1.51949e+06 | 3.03053 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 576.851 | 0.225766 | 8765.75ms | 409725 | 160 | 3.74192e+08 | 677374 | 4.04242 | 1(Win) |
| glaze | 433.431 | 0.465944 | 5852.14ms | 409725 | 40 | 7.05788e+08 | 901515 | 5.38023 | 2(Loss) |
| simdjson (ondemand) | 267.995 | 0.190301 | 9315.96ms | 409725 | 30 | 2.3096e+08 | 1.45803e+06 | 8.70185 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1373.8 | 0.315167 | 7317.72ms | 409725 | 320 | 2.57141e+08 | 284427 | 1.69663 | 1(Win) |
| glaze | 1068.13 | 0.395018 | 9420.49ms | 409725 | 80 | 1.67054e+08 | 365820 | 2.18289 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 779.795 | 0.663561 | 6161.55ms | 785750 | 30 | 1.21981e+09 | 960957 | 2.99042 | 1(Win) |
| glaze | 677.232 | 0.316492 | 7098.3ms | 785750 | 160 | 1.96219e+09 | 1.10649e+06 | 3.44325 | 2(Loss) |
| simdjson (ondemand) | 489.392 | 0.199403 | 9690.1ms | 785750 | 160 | 1.49155e+09 | 1.53119e+06 | 4.76512 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2116.99 | 0.181387 | 9090.21ms | 785750 | 640 | 2.6383e+08 | 353969 | 1.1011 | 1(Win) |
| glaze | 902.563 | 0.444556 | 5256.12ms | 785750 | 30 | 4.08685e+08 | 830247 | 2.58321 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2182.45 | 0.673318 | 6086.33ms | 264040 | 80 | 4.82817e+07 | 115379 | 1.068 | 1(Win) |
| simdjson (ondemand) | 1428.5 | 0.242326 | 9114.45ms | 264040 | 640 | 1.16778e+08 | 176275 | 1.63195 | 2(Loss) |
| glaze | 1264.4 | 0.474953 | 5102.3ms | 264040 | 160 | 1.4315e+08 | 199152 | 1.84396 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2970.98 | 0.306913 | 6618.5ms | 399947 | 640 | 9.93609e+07 | 128382 | 0.784583 | 1(Win) |
| simdjson (ondemand) | 1895.71 | 0.51108 | 5280.59ms | 399947 | 80 | 8.4592e+07 | 201201 | 1.2299 | 2(Loss) |
| glaze | 1608.76 | 0.228666 | 6027.89ms | 399947 | 1280 | 3.76216e+08 | 237089 | 1.44928 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 748.285 | 0.414091 | 8893.61ms | 264040 | 160 | 3.10683e+08 | 336514 | 3.11591 | 1(Win) |
| glaze | 643.856 | 0.366066 | 5142.97ms | 264040 | 160 | 3.27944e+08 | 391094 | 3.62155 | 2(Loss) |
| simdjson (ondemand) | 419.394 | 0.50221 | 7680.57ms | 264040 | 40 | 3.63687e+08 | 600410 | 5.55966 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4080.76 | 0.350773 | 6303.21ms | 264040 | 1280 | 5.9968e+07 | 61706.2 | 0.570841 | 1(Win) |
| glaze | 1706.9 | 0.371516 | 7465.56ms | 263923 | 640 | 1.92076e+08 | 147459 | 1.36564 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 840.512 | 0.28938 | 5864.64ms | 399947 | 320 | 5.51829e+08 | 453794 | 2.77421 | 1(Win) |
| jsonifier | 768.526 | 0.352297 | 6392ms | 399947 | 640 | 1.95653e+09 | 496300 | 3.03401 | 2(Loss) |
| simdjson (ondemand) | 604.014 | 0.315378 | 8066.33ms | 399947 | 160 | 6.3459e+08 | 631474 | 3.86031 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5507.67 | 0.228722 | 7025.63ms | 399947 | 2560 | 6.42283e+07 | 69252.3 | 0.422927 | 1(Win) |
| glaze | 1624.42 | 0.208032 | 6062.74ms | 399830 | 1280 | 3.0523e+08 | 234735 | 1.43516 | 2(Loss) |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 347.371 | 0.36044 | 1279.06ms | 4630 | 4890 | 1.02648e+07 | 12711.2 | 6.69291 | 1(Win) |
| glaze | 187.912 | 0.206693 | 2427.05ms | 4630 | 4890 | 1.15349e+07 | 23497.8 | 12.3896 | 2(Loss) |
| simdjson (ondemand) | 185.787 | 0.251564 | 2365.87ms | 4630 | 2560 | 9.15097e+06 | 23766.5 | 12.5291 | 3(Loss) |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 716.949 | 0.204776 | 620.599ms | 4630 | 4890 | 777773 | 6158.75 | 3.23319 | 1(Win) |
| glaze | 483.759 | 0.20379 | 898.345ms | 4630 | 40 | 13839.7 | 9127.5 | 4.79141 | 2(Loss) |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 925.22 | 0.140875 | 1576.14ms | 14795 | 40 | 18461.5 | 15250 | 2.51582 | 1(Win) |
| simdjson (ondemand) | 545.827 | 0.170664 | 2618.32ms | 14795 | 4890 | 9.51723e+06 | 25850 | 4.26535 | 2(Loss) |
| glaze | 529.81 | 0.191508 | 2756.49ms | 14795 | 4890 | 1.27196e+07 | 26631.5 | 4.39526 | 3(Loss) |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2166.27 | 0.142233 | 671.695ms | 14795 | 30 | 2574.71 | 6513.33 | 1.06981 | 1(Win) |
| glaze | 1157.2 | 0.247125 | 1227.53ms | 14795 | 4890 | 4.43974e+06 | 12192.9 | 2.00714 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 523.288 | 0.129126 | 953.932ms | 5092 | 40 | 5743.59 | 9280 | 4.43485 | 1(Win) |
| glaze | 393.632 | 0.171549 | 1311.41ms | 5092 | 30 | 13436.8 | 12336.7 | 5.90286 | 2(Loss) |
| simdjson (ondemand) | 255.989 | 0.107106 | 1971.16ms | 5092 | 40 | 16512.8 | 18970 | 9.0878 | 3(Loss) |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3457.84 | 0.13987 | 170.182ms | 5092 | 320 | 1234.72 | 1404.38 | 0.656709 | 1(Win) |
| glaze | 1182 | 0.391077 | 416.641ms | 5092 | 4890 | 1.26234e+06 | 4108.38 | 1.95363 | 2(Loss) |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 849.611 | 0.106844 | 1352.61ms | 11724 | 30 | 5931.03 | 13160 | 2.73309 | 1(Win) |
| glaze | 704.913 | 0.251684 | 1634.93ms | 11724 | 4890 | 7.79292e+06 | 15861.3 | 3.29857 | 2(Loss) |
| simdjson (ondemand) | 546.884 | 0.610283 | 2103.43ms | 11724 | 640 | 9.96332e+06 | 20444.7 | 4.25522 | 3(Loss) |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5939.38 | 0.263495 | 196.594ms | 11724 | 80 | 1968.35 | 1882.5 | 0.385031 | 1(Win) |
| glaze | 1519.96 | 0.315061 | 753.648ms | 11746 | 4890 | 2.63644e+06 | 7369.86 | 1.52347 | 2(Loss) |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 600.388 | 0.188806 | 814.335ms | 4857 | 40 | 8487.18 | 7715 | 3.87085 | 1(Win) |
| glaze | 567.908 | 0.113002 | 865.288ms | 4857 | 80 | 6795.89 | 8156.25 | 4.08548 | 2(Loss) |
| simdjson (ondemand) | 306.729 | 0.1227 | 1586.95ms | 4857 | 80 | 27466.8 | 15101.2 | 7.58386 | 3(Loss) |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2800.9 | 0.371755 | 158.795ms | 4857 | 80 | 3023.73 | 1653.75 | 0.8139 | 1(Win) |
| glaze | 1169.7 | 0.431743 | 387.276ms | 4857 | 40 | 11692.3 | 3960 | 1.96876 | 2(Loss) |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 755.412 | 0.0939585 | 996.497ms | 7376 | 160 | 12248 | 9311.88 | 3.06924 | 1(Win) |
| jsonifier | 654.734 | 0.0791379 | 1129.3ms | 7376 | 80 | 5783.23 | 10743.8 | 3.54782 | 2(Loss) |
| simdjson (ondemand) | 440.892 | 0.994003 | 1650.83ms | 7376 | 320 | 8.04825e+06 | 15954.7 | 5.27397 | 3(Loss) |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4596.64 | 0.142762 | 208.295ms | 7376 | 640 | 3054.68 | 1530.31 | 0.494579 | 1(Win) |
| glaze | 1168 | 0.339982 | 635.128ms | 7376 | 4890 | 2.05012e+06 | 6022.54 | 1.98093 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 705.117 | 0.143817 | 626.601ms | 4390 | 40 | 2916.67 | 5937.5 | 3.29173 | 1(Win) |
| glaze | 496.697 | 0.30418 | 886.513ms | 4390 | 4890 | 3.21451e+06 | 8428.94 | 4.67313 | 2(Loss) |
| simdjson (ondemand) | 253.53 | 0.214806 | 1722.11ms | 4390 | 30 | 37747.1 | 16513.3 | 9.17327 | 3(Loss) |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3228.76 | 0.450346 | 120.946ms | 4390 | 30 | 1022.99 | 1296.67 | 0.699096 | 1(Win) |
| glaze | 1067.53 | 0.424779 | 399.818ms | 4390 | 4890 | 1.35708e+06 | 3921.8 | 2.16058 | 2(Loss) |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1208.72 | 0.0862997 | 993.435ms | 11521 | 40 | 2461.54 | 9090 | 1.91985 | 1(Win) |
| glaze | 983.202 | 0.156148 | 1245.53ms | 11521 | 40 | 12179.5 | 11175 | 2.36675 | 2(Loss) |
| simdjson (ondemand) | 622.597 | 0.0884104 | 1853.53ms | 11521 | 40 | 9737.18 | 17647.5 | 3.73609 | 3(Loss) |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7119.19 | 0.596233 | 163.503ms | 11521 | 30 | 2540.23 | 1543.33 | 0.319894 | 1(Win) |
| glaze | 1333.69 | 0.302873 | 835.095ms | 11521 | 4890 | 3.04438e+06 | 8238.24 | 1.73909 | 2(Loss) |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 760.713 | 0.158271 | 612.793ms | 4669 | 30 | 2574.71 | 5853.33 | 3.04769 | 1(Win) |
| glaze | 700.937 | 0.17813 | 682.969ms | 4669 | 40 | 5121.79 | 6352.5 | 3.30623 | 2(Loss) |
| simdjson (ondemand) | 340.226 | 0.122924 | 1350.84ms | 4669 | 40 | 10352.6 | 13087.5 | 6.82475 | 3(Loss) |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4320.78 | 0.5171 | 108.756ms | 4669 | 4890 | 138861 | 1030.53 | 0.519682 | 1(Win) |
| glaze | 1235.58 | 0.263266 | 361.009ms | 4669 | 80 | 7200.95 | 3603.75 | 1.86656 | 2(Loss) |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6918.07 | 0.214006 | 142.399ms | 9249 | 320 | 2382.45 | 1275 | 0.326864 | 1(Win) |
| glaze | 1376.06 | 0.185339 | 659.854ms | 9249 | 80 | 11291.1 | 6410 | 1.682 | 2(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 215.718 | 0.435209 | 2017.93ms | 4604 | 4890 | 3.83709e+07 | 20353.9 | 10.7877 | 1(Win) |
| glaze | 163.078 | 0.868829 | 3052.41ms | 4604 | 320 | 1.75105e+07 | 26924.1 | 14.2725 | 2(Loss) |
| simdjson (ondemand) | 37.0007 | 1.58889 | 5886.6ms | 4604 | 320 | 1.13759e+09 | 118666 | 62.9876 | 3(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 547.743 | 0.496606 | 803.034ms | 4604 | 2560 | 4.05678e+06 | 8016.02 | 4.23525 | 1(Win) |
| glaze | 350.52 | 0.245676 | 1255ms | 4604 | 4890 | 4.63105e+06 | 12526.3 | 6.6258 | 2(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 782.313 | 0.939786 | 2913.72ms | 24579 | 1280 | 1.01493e+08 | 29962.9 | 2.97529 | 1(Win) |
| glaze | 657.054 | 0.61479 | 3772.81ms | 24579 | 1280 | 6.15729e+07 | 35674.9 | 3.54454 | 2(Loss) |
| simdjson (ondemand) | 195.499 | 0.69571 | 6087.92ms | 24579 | 1280 | 8.90646e+08 | 119900 | 11.9208 | 3(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2896.33 | 0.0842392 | 883.148ms | 24579 | 160 | 7436.71 | 8093.12 | 0.801827 | 1(Win) |
| glaze | 1263.4 | 0.240672 | 1910.01ms | 24579 | 30 | 59816.1 | 18553.3 | 1.84163 | 2(Loss) |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 275.395 | 0.102792 | 1647.94ms | 4604 | 30 | 8057.47 | 15943.3 | 8.45014 | 1(Win) |
| glaze | 165.165 | 0.928453 | 2849.38ms | 4604 | 160 | 9.74703e+06 | 26583.8 | 14.0976 | 2(Loss) |
| simdjson (ondemand) | 139.519 | 0.264037 | 3235.05ms | 4604 | 2560 | 1.76755e+07 | 31470.3 | 16.6887 | 3(Loss) |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 598.811 | 0.329182 | 738.459ms | 4604 | 4890 | 2.84887e+06 | 7332.39 | 3.87343 | 1(Win) |
| glaze | 354.805 | 0.212127 | 1221.08ms | 4604 | 40 | 27564.1 | 12375 | 6.54791 | 2(Loss) |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1006.48 | 0.542011 | 2396.96ms | 24579 | 1280 | 2.03962e+07 | 23289.5 | 2.31237 | 1(Win) |
| glaze | 695.265 | 0.368631 | 3501.16ms | 24579 | 1280 | 1.97707e+07 | 33714.3 | 3.34979 | 2(Loss) |
| simdjson (ondemand) | 664.459 | 0.173998 | 3533.62ms | 24579 | 4890 | 1.84243e+07 | 35277.4 | 3.50463 | 3(Loss) |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2951.72 | 0.0766028 | 812.17ms | 24579 | 80 | 2960.44 | 7941.25 | 0.785221 | 1(Win) |
| glaze | 1254.5 | 0.209524 | 1889.85ms | 24579 | 40 | 61307.7 | 18685 | 1.85225 | 2(Loss) |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 330.532 | 0.169735 | 352.573ms | 1181 | 160 | 5352.2 | 3407.5 | 6.97566 | 1(Win) |
| glaze | 190.312 | 0.0596879 | 608.017ms | 1181 | 160 | 1996.46 | 5918.12 | 12.1844 | 2(Loss) |
| simdjson (ondemand) | 179.703 | 0.132603 | 644.302ms | 1181 | 40 | 2762.82 | 6267.5 | 12.892 | 3(Loss) |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 700.647 | 0.184347 | 157.361ms | 1181 | 80 | 702.532 | 1607.5 | 3.25156 | 1(Win) |
| glaze | 490.758 | 0.310076 | 219.014ms | 1181 | 40 | 2025.64 | 2295 | 4.63753 | 2(Loss) |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 511.175 | 0.197606 | 481.29ms | 2496 | 30 | 2540.23 | 4656.67 | 4.53093 | 1(Win) |
| simdjson (ondemand) | 368.669 | 0.160703 | 661.834ms | 2496 | 30 | 3229.89 | 6456.67 | 6.28011 | 2(Loss) |
| glaze | 365.218 | 0.334524 | 654.73ms | 2496 | 4890 | 2.3246e+06 | 6517.67 | 6.34781 | 3(Loss) |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1543.19 | 0.179435 | 162.711ms | 2496 | 320 | 2451.41 | 1542.5 | 1.48433 | 1(Win) |
| glaze | 759.013 | 0.480566 | 321.095ms | 2507 | 2560 | 586620 | 3149.96 | 3.0216 | 2(Loss) |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 585.917 | 0.280961 | 808.003ms | 4926 | 4890 | 2.48151e+06 | 8017.85 | 3.96127 | 1(Win) |
| glaze | 443.764 | 0.104596 | 1088.33ms | 4926 | 80 | 9808.54 | 10586.2 | 5.23523 | 2(Loss) |
| simdjson (ondemand) | 263.995 | 0.159644 | 1821.87ms | 4926 | 40 | 32282.1 | 17795 | 8.80852 | 3(Loss) |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2531.65 | 0.149906 | 193.182ms | 4926 | 320 | 2476.1 | 1855.62 | 0.901202 | 1(Win) |
| glaze | 1026.84 | 0.225055 | 473.88ms | 4926 | 80 | 8481.01 | 4575 | 2.24887 | 2(Loss) |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 778.65 | 0.543932 | 1163.73ms | 9463 | 1280 | 5.08712e+06 | 11590.1 | 2.98526 | 1(Win) |
| glaze | 705.048 | 0.142636 | 1316.82ms | 9463 | 40 | 13333.3 | 12800 | 3.29539 | 2(Loss) |
| simdjson (ondemand) | 476.304 | 0.210385 | 1901.38ms | 9463 | 4890 | 7.77017e+06 | 18947.2 | 4.88648 | 3(Loss) |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4108.32 | 0.462159 | 230.42ms | 9463 | 30 | 3091.95 | 2196.67 | 0.558192 | 1(Win) |
| glaze | 1134.86 | 0.2897 | 801.145ms | 9463 | 4890 | 2.59525e+06 | 7952.19 | 2.04325 | 2(Loss) |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1826.26 | 0.441156 | 171.609ms | 2821 | 160 | 6757.47 | 1473.12 | 1.23847 | 1(Win) |
| simdjson (ondemand) | 1462.13 | 0.494412 | 266.651ms | 2821 | 30 | 2482.76 | 1840 | 1.55867 | 2(Loss) |
| glaze | 1427.22 | 0.233083 | 236.765ms | 2821 | 80 | 1544.3 | 1885 | 1.59684 | 3(Loss) |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2520.04 | 0.352813 | 207.432ms | 4147 | 160 | 4905.27 | 1569.38 | 0.903426 | 1(Win) |
| simdjson (ondemand) | 1163.42 | 0.323152 | 359.18ms | 4147 | 160 | 19307.8 | 3399.38 | 1.97741 | 2(Loss) |
| glaze | 987.179 | 0.263982 | 428.256ms | 4147 | 80 | 8947.78 | 4006.25 | 2.33679 | 3(Loss) |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 429 | 0.41111 | 607.846ms | 2821 | 4890 | 3.25024e+06 | 6271.12 | 5.38873 | 1(Win) |
| glaze | 419.542 | 0.591422 | 608.476ms | 2821 | 40 | 57532.1 | 6412.5 | 5.50861 | 2(Loss) |
| simdjson (ondemand) | 289.81 | 0.462596 | 961.36ms | 2821 | 2560 | 4.7209e+06 | 9283.05 | 8.00498 | 3(Loss) |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1758.38 | 2.75116 | 171.68ms | 2821 | 40 | 70871.8 | 1530 | 1.29231 | 1(Win) |
| glaze | 1115.23 | 0.545054 | 239.073ms | 2819 | 160 | 27622.2 | 2410.62 | 2.04002 | 2(Loss) |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 578.411 | 0.24943 | 734.422ms | 4147 | 40 | 11634.6 | 6837.5 | 4.00449 | 1(Win) |
| simdjson (ondemand) | 410.957 | 0.916537 | 943.437ms | 4147 | 640 | 4.97915e+06 | 9623.59 | 5.64585 | 2(Loss) |
| jsonifier | 314.692 | 0.896163 | 1045.87ms | 4147 | 40 | 507378 | 12567.5 | 7.36434 | 3(Loss) |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1674.03 | 1.52723 | 192.772ms | 4147 | 80 | 104146 | 2362.5 | 1.36258 | 1(Win) |
| glaze | 1094 | 0.867423 | 359.785ms | 4145 | 30 | 29471.3 | 3613.33 | 2.1117 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1143.62 | 0.093819 | 10005.1ms | 466906 | 1280 | 1.70801e+08 | 389358 | 2.03886 | 1(Win) |
| glaze | 603.366 | 0.199646 | 7546.48ms | 466906 | 80 | 1.73664e+08 | 737988 | 3.86426 | 2(Loss) |
| simdjson (ondemand) | 544.513 | 0.178121 | 5233.92ms | 466906 | 320 | 6.78925e+08 | 817751 | 4.2825 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1143.54 | 0.139695 | 7487.14ms | 699405 | 640 | 4.24907e+08 | 583280 | 2.03883 | 1(Win) |
| glaze | 1064.89 | 0.169159 | 8210.89ms | 699405 | 320 | 3.59239e+08 | 626358 | 2.18973 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1411.58 | 0.518476 | 5556.15ms | 631514 | 30 | 1.46803e+08 | 426657 | 1.65188 | 1(Win) |
| jsonifier | 1187.59 | 0.189465 | 6530.38ms | 631514 | 320 | 2.95421e+08 | 507127 | 1.96341 | 2(Loss) |
