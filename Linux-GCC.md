# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the GCC 16.0.1 compiler).  

Latest Results: (Sep 11, 2026)
#### Using the following commits:
----
| Jsonifier: [4d4a69d](https://github.com/nihilai-collective/jsonifier/commit/4d4a69d)  
| Glaze: [565edc9](https://github.com/stephenberry/glaze/commit/565edc9)  
| Simdjson: [f9c973a](https://github.com/simdjson/simdjson/commit/f9c973a)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX512` |
| simdjson (ondemand) | `icelake` |
| Glaze (utf8-validation) | `AVX512BW` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Intel(R) Xeon(R) 6973P-C-AVX512): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.500000% AND mean shift < 1.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [c0b7b4a](https://github.com/realtimechris/benchmarksuite/commit/c0b7b4a).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 794.985 | 0.156613 | 3.04831ms | 1811 | 30 | 347.293 | 2172.5 | 3.0723 | 1(Win) |
| glaze | 590.288 | 0.324446 | 1.24042ms | 1811 | 30 | 2703.43 | 2925.87 | 4.16142 | 2(Loss) |
| simdjson (ondemand) | 160.612 | 0.0509236 | 6.73528ms | 1811 | 32 | 959.548 | 10753.2 | 15.3854 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 597.69 | 0.0690433 | 1.68256ms | 1811 | 30 | 119.413 | 2889.63 | 4.0868 | 1(Win) |
| glaze | 401.235 | 0.465458 | 1.53554ms | 1798 | 30 | 11870.3 | 4273.57 | 6.12088 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1547.87 | 0.0421799 | 1.06687ms | 3873 | 30 | 30.392 | 2386.23 | 1.57668 | 1(Win) |
| jsonifier | 1396.6 | 0.0406656 | 1.29638ms | 3873 | 30 | 34.7 | 2644.7 | 1.75232 | 2(Loss) |
| simdjson (ondemand) | 306.21 | 0.190484 | 3.38259ms | 3873 | 30 | 15837.7 | 12062.2 | 8.07099 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2297.15 | 0.12903 | 1.08871ms | 3873 | 30 | 129.128 | 1607.9 | 1.06102 | 1(Win) |
| glaze | 1133.19 | 0.157826 | 1.31765ms | 3873 | 30 | 793.913 | 3259.47 | 2.15151 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1494.26 | 0.0513951 | 1.2579ms | 3862 | 30 | 48.1437 | 2464.83 | 1.6324 | 1(Win) |
| glaze | 1380.4 | 0.0621391 | 1.12848ms | 3862 | 30 | 82.4644 | 2668.13 | 1.78006 | 2(Loss) |
| simdjson (ondemand) | 347.902 | 1.82813 | 14.4191ms | 3862 | 64 | 2.3972e+06 | 10586.6 | 7.10061 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1938.64 | 0.287483 | 1.17925ms | 3862 | 30 | 894.902 | 1899.83 | 1.25795 | 1(Win) |
| glaze | 1131.25 | 0.101354 | 1.32572ms | 3862 | 30 | 326.668 | 3255.77 | 2.15964 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1191.65 | 0.226044 | 0.867023ms | 905 | 30 | 80.4092 | 724.267 | 2.00413 | 1(Win) |
| glaze | 504.742 | 0.0386435 | 0.912392ms | 905 | 30 | 13.0989 | 1709.93 | 4.77591 | 2(Loss) |
| simdjson (ondemand) | 139.464 | 0.164322 | 4.13519ms | 905 | 32 | 3309.16 | 6188.53 | 17.6889 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1396.34 | 0.332682 | 0.764656ms | 905 | 30 | 126.852 | 618.1 | 1.70917 | 1(Win) |
| glaze | 359.25 | 0.0855771 | 1.09329ms | 905 | 30 | 126.806 | 2402.43 | 6.76818 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2290.73 | 0.108569 | 1.7023ms | 9578 | 30 | 562.259 | 3987.5 | 1.07448 | 1(Win) |
| glaze | 1766.18 | 0.0829292 | 7.18709ms | 9578 | 64 | 1177.26 | 5171.77 | 1.39634 | 2(Loss) |
| simdjson (ondemand) | 1065.09 | 0.0880607 | 2.61159ms | 9578 | 30 | 1711.06 | 8576.1 | 2.32071 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4663.05 | 0.249069 | 1.5833ms | 9578 | 30 | 714.12 | 1958.87 | 0.520749 | 1(Win) |
| glaze | 2844.54 | 0.163324 | 1.32055ms | 9578 | 30 | 825.178 | 3211.17 | 0.85702 | 2(Loss) |

----
### Abc (In Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4467.66 | 1.14187 | 12.8802ms | 233995 | 30 | 9.75911e+06 | 49949 | 0.554511 | 1(Win) |
| simdjson (ondemand) | 3347.88 | 1.0844 | 41.6148ms | 233995 | 32 | 1.67186e+07 | 66655.7 | 0.740123 | 2(Loss) |
| glaze | 1684.54 | 0.389888 | 32.696ms | 233995 | 30 | 8.00297e+06 | 132472 | 1.47149 | 3(Loss) |

----
### Abc (In Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6382.03 | 1.0314 | 13.2254ms | 346753 | 30 | 8.56845e+06 | 51815.7 | 0.388236 | 1(Win) |
| simdjson (ondemand) | 4934.57 | 1.11839 | 16.6974ms | 346753 | 30 | 1.68519e+07 | 67014.8 | 0.502174 | 2(Loss) |
| glaze | 2185.53 | 0.339562 | 37.1755ms | 346753 | 30 | 7.91927e+06 | 151308 | 1.13422 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1493.62 | 0.382608 | 37.5608ms | 233995 | 30 | 9.80308e+06 | 149406 | 1.65962 | 1(Win) |
| simdjson (ondemand) | 1472.2 | 0.385814 | 37.6529ms | 233995 | 30 | 1.02602e+07 | 151579 | 1.68377 | 2(Loss) |
| jsonifier | 1398.22 | 0.358044 | 41.0964ms | 233995 | 30 | 9.79619e+06 | 159600 | 1.77289 | 3(Loss) |

----
### Abc (In Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3487.16 | 1.63467 | 15.866ms | 233995 | 30 | 3.28286e+07 | 63993.3 | 0.710199 | 1(Win) |
| glaze | 3212.36 | 1.95245 | 18.9058ms | 233995 | 30 | 5.51884e+07 | 69467.7 | 0.771433 | 2(Loss) |

----
### Abc (In Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2080.55 | 0.441321 | 39.2256ms | 346753 | 30 | 1.4761e+07 | 158943 | 1.19145 | 1(Win) |
| glaze | 1733.56 | 0.269943 | 48.3767ms | 346753 | 30 | 7.95481e+06 | 190758 | 1.42999 | 2(Loss) |
| jsonifier | 1363.29 | 0.308108 | 61.1479ms | 346753 | 30 | 1.67569e+07 | 242568 | 1.81844 | 3(Loss) |

----
### Abc (In Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28In%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28In%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4132.22 | 0.52942 | 21.7373ms | 346753 | 30 | 5.38512e+06 | 80027 | 0.599395 | 1(Win) |
| glaze | 3299.45 | 0.957855 | 26.1558ms | 346753 | 30 | 2.76489e+07 | 100226 | 0.751117 | 2(Loss) |

----
### Abc (Out of Order) Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4661.31 | 0.522505 | 12.8706ms | 233995 | 30 | 1.87715e+06 | 47873.9 | 0.531522 | 1(Win) |
| simdjson (ondemand) | 2130.81 | 0.803139 | 27.19ms | 233995 | 30 | 2.1224e+07 | 104728 | 1.1632 | 2(Loss) |
| glaze | 1671.63 | 0.449192 | 32.7383ms | 233995 | 30 | 1.07875e+07 | 133496 | 1.4828 | 3(Loss) |

----
### Abc (Out of Order) Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6181.98 | 1.0764 | 13.867ms | 346753 | 30 | 9.94621e+06 | 53492.5 | 0.400793 | 1(Win) |
| simdjson (ondemand) | 2908.39 | 0.307849 | 27.7613ms | 346753 | 30 | 3.67564e+06 | 113702 | 0.852251 | 2(Loss) |
| glaze | 2170.29 | 0.503845 | 38.7527ms | 346753 | 30 | 1.76816e+07 | 152371 | 1.14218 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1504.97 | 0.371114 | 36.8771ms | 233995 | 30 | 9.08439e+06 | 148279 | 1.64711 | 1(Win) |
| jsonifier | 1335.16 | 0.389631 | 41.7217ms | 233995 | 30 | 1.27226e+07 | 167138 | 1.85663 | 2(Loss) |
| simdjson (ondemand) | 183.326 | 0.159625 | 295.007ms | 233995 | 30 | 1.13263e+08 | 1.21726e+06 | 13.5243 | 3(Loss) |

----
### Abc (Out of Order) Test (Minified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3712.08 | 0.51796 | 16.6566ms | 233995 | 30 | 2.90866e+06 | 60115.9 | 0.666967 | 1(Win) |
| glaze | 3507.5 | 0.546258 | 17.5785ms | 233995 | 30 | 3.62357e+06 | 63622.3 | 0.706484 | 2(Loss) |

----
### Abc (Out of Order) Test (Prettified) Read Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in these two tests feature keys ranging from "a" to "z", where each key corresponds to an array of values. Notably, the library parsing methods in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.
This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently locate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.
In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.  

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1654.97 | 0.70605 | 49.7099ms | 346753 | 30 | 5.97105e+07 | 199815 | 1.49782 | 1(Win) |
| jsonifier | 1194.62 | 0.261458 | 66.8035ms | 346753 | 30 | 1.57146e+07 | 276815 | 2.07518 | 2(Loss) |
| simdjson (ondemand) | 270.423 | 0.206851 | 296.144ms | 346753 | 30 | 1.91951e+08 | 1.22286e+06 | 9.16851 | 3(Loss) |

----
### Abc (Out of Order) Test (Prettified) Write Results [(View the data used in the following test)](./json/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Abc%20%28Out%20of%20Order%29%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4273.9 | 0.356532 | 19.5898ms | 346753 | 30 | 2.28302e+06 | 77374.1 | 0.579805 | 1(Win) |
| glaze | 3217.13 | 0.687835 | 26.9651ms | 346753 | 30 | 1.49966e+07 | 102790 | 0.770221 | 2(Loss) |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1034.66 | 0.480713 | 21.7516ms | 94651 | 30 | 5.27656e+06 | 87242.7 | 2.39539 | 1(Win) |
| glaze | 974.427 | 0.432698 | 24.4544ms | 94651 | 30 | 4.81996e+06 | 92635.2 | 2.54349 | 2(Loss) |
| jsonifier | 883.07 | 0.532719 | 27.1325ms | 94651 | 30 | 8.89565e+06 | 102219 | 2.80668 | 3(Loss) |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4542.08 | 0.0295169 | 5.69226ms | 94651 | 30 | 1032.3 | 19873.3 | 0.543226 | 1(Win) |
| glaze | 3954.39 | 0.540228 | 6.01741ms | 94651 | 30 | 456213 | 22826.9 | 0.616442 | 2(Loss) |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1428.96 | 0.509583 | 24.0792ms | 136024 | 30 | 6.42008e+06 | 90781 | 1.73441 | 1(Win) |
| glaze | 1183.58 | 0.392111 | 27.321ms | 136024 | 30 | 5.54085e+06 | 109602 | 2.09415 | 2(Loss) |
| jsonifier | 1030.91 | 0.515923 | 31.4253ms | 136024 | 30 | 1.26438e+07 | 125833 | 2.4043 | 3(Loss) |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5459.34 | 1.34354 | 6.58953ms | 136024 | 30 | 3.05753e+06 | 23761.6 | 0.452396 | 1(Win) |
| glaze | 4431.51 | 1.06518 | 7.83866ms | 136046 | 30 | 2.91767e+06 | 29277.5 | 0.55871 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 711.197 | 0.176571 | 675.153ms | 2090234 | 30 | 7.34803e+08 | 2.80288e+06 | 3.48584 | 1(Win) |
| simdjson (ondemand) | 564.479 | 0.438806 | 833.753ms | 2090234 | 30 | 7.20378e+09 | 3.5314e+06 | 4.39197 | 2(Loss) |
| glaze | 529.411 | 0.243173 | 901.057ms | 2090234 | 30 | 2.51511e+09 | 3.76532e+06 | 4.68285 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1263.33 | 0.186573 | 381.737ms | 2090234 | 30 | 2.60002e+08 | 1.57789e+06 | 1.96201 | 1(Win) |
| glaze | 967.701 | 0.238995 | 493.893ms | 2090234 | 30 | 7.27119e+08 | 2.05994e+06 | 2.56179 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1681.2 | 0.245216 | 911.233ms | 6661897 | 30 | 2.57617e+09 | 3.77901e+06 | 1.47462 | 1(Win) |
| jsonifier | 1431.73 | 0.88006 | 1048.25ms | 6661897 | 30 | 4.57529e+10 | 4.43748e+06 | 1.73164 | 2(Loss) |
| glaze | 1358.17 | 0.0730996 | 1125.68ms | 6661897 | 30 | 3.50782e+08 | 4.67781e+06 | 1.82539 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2633.52 | 0.116911 | 582.821ms | 6661897 | 30 | 2.38646e+08 | 2.41247e+06 | 0.941342 | 1(Win) |
| glaze | 2169.54 | 0.285866 | 704.909ms | 6661897 | 30 | 2.10237e+09 | 2.9284e+06 | 1.14268 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1429.59 | 0.353556 | 81.244ms | 500299 | 30 | 4.1771e+07 | 333748 | 1.73408 | 1(Win) |
| glaze | 1212.29 | 0.282489 | 94.7096ms | 500299 | 30 | 3.70827e+07 | 393571 | 2.04491 | 2(Loss) |
| simdjson (ondemand) | 1080.54 | 0.362363 | 107.489ms | 500299 | 30 | 7.68038e+07 | 441557 | 2.29434 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3897.97 | 1.23116 | 31.4612ms | 500299 | 30 | 6.81294e+07 | 122403 | 0.63581 | 1(Win) |
| jsonifier | 3659.75 | 1.43356 | 31.15ms | 500299 | 30 | 1.04787e+08 | 130370 | 0.677009 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2646.09 | 0.287934 | 126.045ms | 1439562 | 30 | 6.69513e+07 | 518830 | 0.936701 | 1(Win) |
| glaze | 2191.91 | 0.297794 | 151.855ms | 1439562 | 30 | 1.04368e+08 | 626336 | 1.13094 | 2(Loss) |
| jsonifier | 2159.2 | 0.255873 | 155.228ms | 1439562 | 30 | 7.94044e+07 | 635825 | 1.14808 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4717.05 | 0.904461 | 72.5772ms | 1439562 | 30 | 2.07884e+08 | 291045 | 0.525072 | 1(Win) |
| glaze | 3221.98 | 0.5073 | 102.829ms | 1439584 | 30 | 1.40178e+08 | 426102 | 0.769136 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1430.78 | 1.80891 | 10.0092ms | 56369 | 30 | 1.38576e+07 | 37572.2 | 1.73129 | 1(Win) |
| glaze | 1188.42 | 1.5836 | 11.9693ms | 56369 | 30 | 1.53941e+07 | 45234.6 | 2.08449 | 2(Loss) |
| simdjson (ondemand) | 1117.63 | 1.1116 | 12.3762ms | 56369 | 30 | 8.5763e+06 | 48099.6 | 2.2168 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4746.42 | 0.415726 | 3.40725ms | 56369 | 30 | 66509.7 | 11325.9 | 0.518683 | 1(Win) |
| glaze | 4046.28 | 0.874339 | 3.55078ms | 56369 | 30 | 404809 | 13285.7 | 0.610732 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1830.2 | 0.830174 | 13.9276ms | 94370 | 30 | 4.99956e+06 | 49174.1 | 1.35375 | 1(Win) |
| glaze | 1752.07 | 0.726885 | 13.3584ms | 94370 | 30 | 4.18235e+06 | 51366.9 | 1.41417 | 2(Loss) |
| jsonifier | 1531.15 | 0.514185 | 15.5912ms | 94370 | 30 | 2.74027e+06 | 58778.3 | 1.61839 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5911.94 | 0.372972 | 4.29387ms | 94370 | 30 | 96712.5 | 15223.1 | 0.417473 | 1(Win) |
| glaze | 3899.21 | 2.22562 | 6.36268ms | 94370 | 30 | 7.91664e+06 | 23081.2 | 0.634344 | 2(Loss) |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1404.36 | 1.36016 | 9.63332ms | 52708 | 30 | 7.11042e+06 | 35792.9 | 1.76382 | 1(Win) |
| jsonifier | 1156.19 | 1.17778 | 12.2352ms | 52708 | 30 | 7.86585e+06 | 43475.8 | 2.14261 | 2(Loss) |
| glaze | 1047.33 | 1.59707 | 13.9379ms | 52708 | 30 | 1.76258e+07 | 47994.5 | 2.3655 | 3(Loss) |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4598.73 | 0.606473 | 3.38147ms | 52708 | 30 | 131832 | 10930.5 | 0.535761 | 1(Win) |
| glaze | 4438.47 | 0.351566 | 3.08061ms | 52708 | 30 | 47557.7 | 11325.1 | 0.556465 | 2(Loss) |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1612.15 | 1.13948 | 11.0665ms | 70103 | 30 | 6.69882e+06 | 41469.7 | 1.53648 | 1(Win) |
| jsonifier STATISTICAL TIE | 1140.76 | 1.79912 | 15.6283ms | 70103 | 30 | 3.33521e+07 | 58606 | 2.17206 | 2(Tie) |
| glaze STATISTICAL TIE | 1088.31 | 1.65685 | 15.4064ms | 70103 | 30 | 3.10779e+07 | 61430.3 | 2.27651 | 2(Tie) |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5419.25 | 1.88527 | 7.81452ms | 70103 | 32 | 1.73099e+06 | 12336.7 | 0.455529 | 1(Win) |
| glaze | 4126.83 | 0.948348 | 4.77021ms | 70103 | 30 | 708105 | 16200.2 | 0.599102 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 902.599 | 2.11035 | 3.65014ms | 11812 | 30 | 2.08107e+06 | 12480.4 | 2.73939 | 1(Win) |
| jsonifier | 844.076 | 0.10946 | 8.40944ms | 11812 | 32 | 6828.79 | 13345.7 | 2.93045 | 2(Loss) |
| simdjson (ondemand) | 829.304 | 0.0989384 | 3.97478ms | 11812 | 30 | 5418.39 | 13583.4 | 2.98155 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5109.14 | 0.264302 | 1.11398ms | 11812 | 30 | 1018.76 | 2204.83 | 0.474952 | 1(Win) |
| glaze | 2831.8 | 0.674101 | 2.64461ms | 11812 | 32 | 23010.4 | 3977.97 | 0.868053 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2304.67 | 0.101184 | 3.75843ms | 31235 | 30 | 5131.1 | 12925.1 | 1.07289 | 1(Win) |
| jsonifier | 1695.98 | 1.11585 | 5.01396ms | 31235 | 30 | 1.15232e+06 | 17563.9 | 1.45958 | 2(Loss) |
| glaze | 1560.83 | 0.905599 | 5.4673ms | 31235 | 30 | 896115 | 19084.7 | 1.58566 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5822.9 | 0.558269 | 1.78041ms | 31235 | 30 | 24468.8 | 5115.67 | 0.417811 | 1(Win) |
| glaze | 4248.55 | 1.79717 | 9.23475ms | 31235 | 64 | 1.01616e+06 | 7011.34 | 0.579642 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2891.16 | 1.07565 | 9.53441ms | 108313 | 30 | 4.43081e+06 | 35728 | 0.856692 | 1(Win) |
| glaze | 1825.09 | 0.767839 | 14.1112ms | 108313 | 30 | 5.66573e+06 | 56597.5 | 1.35759 | 2(Loss) |
| simdjson (ondemand) | 1585.89 | 0.570168 | 17.9693ms | 108313 | 30 | 4.13756e+06 | 65134.2 | 1.56252 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3204.24 | 0.732747 | 8.2476ms | 108313 | 30 | 1.67394e+06 | 32237.1 | 0.772838 | 1(Win) |
| jsonifier | 3100.52 | 1.38238 | 8.55237ms | 108313 | 30 | 6.36308e+06 | 33315.5 | 0.797494 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2797.63 | 0.613082 | 19.5664ms | 213963 | 30 | 5.99866e+06 | 72937.1 | 0.885871 | 1(Win) |
| glaze | 2406.64 | 0.547601 | 21.094ms | 213963 | 30 | 6.46706e+06 | 84786.8 | 1.02986 | 2(Loss) |
| jsonifier | 2073.8 | 0.428682 | 25.9207ms | 213963 | 30 | 5.33746e+06 | 98394.8 | 1.19507 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3951.81 | 1.44314 | 13.751ms | 213963 | 30 | 1.6658e+07 | 51634.8 | 0.626639 | 1(Win) |
| glaze | 3735.28 | 0.786468 | 14.937ms | 213963 | 30 | 5.53749e+06 | 54628 | 0.663223 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 594.58 | 0.372808 | 723.387ms | 1834197 | 30 | 3.6088e+09 | 2.94195e+06 | 4.16977 | 1(Win) |
| simdjson (ondemand) | 475.826 | 0.264158 | 898.188ms | 1834197 | 30 | 2.82908e+09 | 3.67619e+06 | 5.21054 | 2(Loss) |
| glaze | 449.744 | 0.325886 | 935.088ms | 1834197 | 30 | 4.81962e+09 | 3.88938e+06 | 5.51277 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 798.951 | 0.449485 | 525.729ms | 1834197 | 30 | 2.90539e+09 | 2.18941e+06 | 3.10295 | 1(Win) |
| glaze | 735.81 | 0.539404 | 567.634ms | 1833577 | 30 | 4.92965e+09 | 2.37648e+06 | 3.36937 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1989.64 | 0.304445 | 1166.75ms | 9930848 | 30 | 6.30035e+09 | 4.76006e+06 | 1.24614 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1979.5 | 0.385311 | 1109.11ms | 9930848 | 30 | 1.01954e+10 | 4.78443e+06 | 1.25251 | 1(Tie) |
| glaze | 1860.23 | 0.530429 | 1223.89ms | 9930848 | 30 | 2.18785e+10 | 5.0912e+06 | 1.33284 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2153.55 | 0.0730374 | 978.67ms | 9930848 | 30 | 3.09511e+08 | 4.39777e+06 | 1.15126 | 1(Win) |
| glaze | 1912.83 | 0.271213 | 1193.33ms | 9930228 | 30 | 5.40885e+09 | 4.95088e+06 | 1.29613 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1182.52 | 0.355386 | 126.783ms | 642697 | 30 | 1.01793e+08 | 518319 | 2.09615 | 1(Win) |
| simdjson (ondemand) | 936.536 | 0.40342 | 148.59ms | 642697 | 30 | 2.09122e+08 | 654458 | 2.64631 | 2(Loss) |
| glaze | 841.136 | 0.230641 | 176.895ms | 642697 | 30 | 8.4737e+07 | 728685 | 2.947 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1346.97 | 1.00977 | 108.495ms | 642697 | 30 | 6.3338e+08 | 455038 | 1.83986 | 1(Win) |
| glaze | 1094.56 | 0.205542 | 136.339ms | 642692 | 30 | 3.97418e+07 | 559967 | 2.26445 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1855.53 | 0.26641 | 152.522ms | 1225964 | 30 | 8.45366e+07 | 630102 | 1.33581 | 1(Win) |
| glaze | 1358.13 | 0.258806 | 207.381ms | 1225964 | 30 | 1.48917e+08 | 860868 | 1.82507 | 2(Loss) |
| jsonifier | 1309.52 | 0.196517 | 215.576ms | 1225964 | 30 | 9.23535e+07 | 892824 | 1.89284 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1829.11 | 0.5343 | 157.36ms | 1225964 | 30 | 3.49921e+08 | 639203 | 1.35479 | 1(Win) |
| glaze | 1506.22 | 0.833345 | 188.311ms | 1225970 | 30 | 1.25531e+09 | 776231 | 1.64558 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 874.037 | 0.392008 | 108.63ms | 409725 | 30 | 9.21373e+07 | 447057 | 2.83601 | 1(Win) |
| jsonifier | 730.218 | 0.494954 | 130.802ms | 409725 | 30 | 2.10441e+08 | 535106 | 3.39503 | 2(Loss) |
| glaze | 559.224 | 1.73757 | 148.909ms | 409725 | 30 | 4.422e+09 | 698726 | 4.4327 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3712.37 | 0.663697 | 27.9292ms | 409725 | 30 | 1.464e+07 | 105255 | 0.667196 | 1(Win) |
| glaze | 2491.28 | 1.68482 | 39.0279ms | 409725 | 30 | 2.09492e+08 | 156845 | 0.994695 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1344.61 | 0.479046 | 125.533ms | 785750 | 30 | 2.13823e+08 | 557300 | 1.84325 | 1(Win) |
| glaze | 1080.44 | 0.274124 | 168.078ms | 785750 | 30 | 1.08438e+08 | 693559 | 2.29438 | 2(Loss) |
| jsonifier | 995.283 | 0.261965 | 183.574ms | 785750 | 30 | 1.16704e+08 | 752901 | 2.49083 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4243.73 | 0.665677 | 43.8359ms | 785750 | 30 | 4.14498e+07 | 176578 | 0.583506 | 1(Win) |
| glaze | 2859.28 | 1.28426 | 63.4503ms | 785750 | 30 | 3.39844e+08 | 262076 | 0.866666 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1032.86 | 0.190928 | 1920.15ms | 8587914 | 30 | 6.87619e+09 | 7.92948e+06 | 2.40053 | 1(Win) |
| jsonifier | 925.409 | 0.206909 | 2138.43ms | 8587914 | 30 | 1.00598e+10 | 8.85022e+06 | 2.67929 | 2(Loss) |
| glaze | 823.115 | 0.374557 | 2392.26ms | 8587914 | 30 | 4.16688e+10 | 9.95009e+06 | 3.01227 | 3(Loss) |

----
### Semanticscholar Corpus Test (Minified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2862.45 | 0.453023 | 692.766ms | 8588126 | 30 | 5.04058e+09 | 2.86128e+06 | 0.866105 | 1(Win) |
| glaze | 2764.15 | 0.171339 | 716.319ms | 8588126 | 30 | 7.73225e+08 | 2.96303e+06 | 0.896925 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Read Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1118.5 | 0.370134 | 2028.93ms | 9804437 | 30 | 2.8722e+10 | 8.35965e+06 | 2.21668 | 1(Win) |
| jsonifier | 906.784 | 0.0536998 | 2597.85ms | 9804437 | 30 | 9.19823e+08 | 1.03114e+07 | 2.73433 | 2(Loss) |
| glaze | 895.871 | 0.216776 | 2518.11ms | 9804437 | 30 | 1.53567e+10 | 1.0437e+07 | 2.76763 | 3(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Write Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3121.79 | 0.518556 | 816.299ms | 11078090 | 30 | 9.23921e+09 | 3.38424e+06 | 0.794173 | 1(Win) |
| glaze | 2805.96 | 0.0672768 | 912.134ms | 11078090 | 30 | 1.92495e+08 | 3.76516e+06 | 0.883572 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5416.84 | 0.866933 | 12.163ms | 264040 | 30 | 4.87236e+06 | 46486.1 | 0.457422 | 1(Win) |
| simdjson (ondemand) | 5040.48 | 0.418474 | 12.7936ms | 264040 | 30 | 1.31115e+06 | 49957.2 | 0.491608 | 2(Loss) |
| glaze | 1649.39 | 0.381507 | 38.8115ms | 264040 | 30 | 1.01769e+07 | 152667 | 1.50292 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6966.6 | 0.619933 | 15.4451ms | 399947 | 30 | 3.45601e+06 | 54749.7 | 0.355705 | 1(Win) |
| simdjson (ondemand) | 6440.11 | 0.735092 | 16.3082ms | 399947 | 30 | 5.6862e+06 | 59225.5 | 0.384777 | 2(Loss) |
| glaze | 2102.39 | 0.270312 | 44.2777ms | 399947 | 30 | 7.21491e+06 | 181422 | 1.17912 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1594.44 | 0.581292 | 39.9875ms | 264040 | 30 | 2.52831e+07 | 157928 | 1.55457 | 1(Win) |
| simdjson (ondemand) | 1541.15 | 0.455072 | 41.9128ms | 264040 | 30 | 1.65856e+07 | 163390 | 1.60837 | 2(Loss) |
| glaze | 1303.92 | 0.572043 | 47.3837ms | 264040 | 30 | 3.66116e+07 | 193117 | 1.90101 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 5125.74 | 0.664652 | 12.6475ms | 263923 | 30 | 3.19559e+06 | 49104.4 | 0.483233 | 1(Win) |
| jsonifier | 4516.9 | 2.17119 | 36.2177ms | 264040 | 32 | 4.68818e+07 | 55748.1 | 0.548239 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2188.7 | 0.432826 | 43.0973ms | 399947 | 30 | 1.70679e+07 | 174267 | 1.13253 | 1(Win) |
| glaze | 1640.85 | 0.493492 | 58.3481ms | 399947 | 30 | 3.94776e+07 | 232453 | 1.51076 | 2(Loss) |
| jsonifier | 1203.09 | 0.455857 | 80.4492ms | 399947 | 30 | 6.26596e+07 | 317033 | 2.06055 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5769.24 | 1.53789 | 16.1244ms | 399947 | 30 | 3.10128e+07 | 66112.5 | 0.42936 | 1(Win) |
| glaze | 4516.37 | 0.98384 | 21.1434ms | 399830 | 30 | 2.06987e+07 | 84427.9 | 0.548647 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2041.09 | 0.345238 | 53.9289ms | 466906 | 30 | 1.70174e+07 | 218156 | 1.21442 | 1(Win) |
| glaze | 2005.61 | 0.31289 | 55.5696ms | 466906 | 30 | 1.44768e+07 | 222015 | 1.23607 | 2(Loss) |
| simdjson (ondemand) | 1110.94 | 0.407518 | 99.5684ms | 466906 | 30 | 8.00374e+07 | 400810 | 2.23046 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3653.83 | 0.649981 | 47.2359ms | 699405 | 30 | 4.2236e+07 | 182549 | 0.678108 | 1(Win) |
| glaze | 3082 | 0.254463 | 53.1871ms | 699405 | 30 | 9.09836e+06 | 216420 | 0.804388 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2224.45 | 0.245497 | 65.9397ms | 631514 | 30 | 1.32535e+07 | 270744 | 1.11448 | 1(Win) |
| jsonifier | 2154.59 | 0.366623 | 69.1332ms | 631514 | 30 | 3.15062e+07 | 279523 | 1.15051 | 2(Loss) |
