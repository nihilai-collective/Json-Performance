# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the Clang 24.0.0 compiler).  

Latest Results: (Oct 10, 2026)
#### Using the following commits:
----
| Jsonifier (Generic): [5aa6104](https://github.com/nihilai-collective/jsonifier/commit/5aa6104)  
| Simdjson (On Demand): [7f6f8dc](https://github.com/simdjson/simdjson/commit/7f6f8dc)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier (generic) | `AVX2` |
| simdjson (ondemand) | `haswell` |
> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. 

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 4 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 5.000000% AND mean shift < 2.500000%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (Both libraries are performing UTF8-validation in these tests. Neither library is given a schema: "jsonifier (generic)" walks its stage-1 structural tape through the schema-free, re-accessible jsonifier::generic API, and "simdjson (ondemand)" walks its On Demand API, with both filling the exact same structs through the exact same field-by-field traversal. In the streaming tests, "jsonifier (generic)" walks each document of the stream through jsonifier::generic::parser::iterateMany, and "simdjson (ondemand)" walks each document through ondemand::parser::iterate_many (unthreaded), using the same 1 MiB batch size)

The "Amazon Cellphones" tests aggregate ratings per brand over amazon_cellphones.ndjson (from the simdjson repository; repeated to 10 MiB for the Large variant). The "Stream Formats" tests read and sum "id" over generated {"id","name","payload","flag"} documents, following simdjson's stream benchmarks, with 16- and 4096-byte payloads, repeated to 16 MB to fit the sampling window. The "Stream" tests split the main record array of each corpus document into one document per record, repeated to 4 MiB. "(NDJSON)" tests separate documents with newlines; "(Comma-Separated)" tests separate them with commas (simdjson's stream_format::comma_delimited, Jsonifier's allowCommaSeparated).

Every test whose name contains "Reverse" deliberately requests each object's keys in the reverse of their order in the JSON document; every other test requests them in document order. The reverse tests exercise out-of-order access, which forces forward-only iterative parsers such as simdjson's On Demand API into sequential rescans (or rewinds), degrading from O(N) toward O(N^2) as object size grows.

Every test whose name contains "Sparse" reads the same document as its full counterpart but requests only a small subset of its fields (a few fields from each record of the document's main arrays, in the spirit of the Twitter Partial test); every other field is skipped by each library. "Sparse Reverse" tests request that subset in the reverse of its document order.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [6196208](https://github.com/nihilai-collective/benchmarksuite/commit/6196208).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 285.289 | 0.0477053 | 1033.92ms | 905 | 4890 | 10185.2 | 3025.26 | 17.9628 | 61.137 | 9.56465 | 0.0310081 | 0.000233197 | 0.000101459 | 1(Win) |
| simdjson (ondemand) | 179.198 | 0.125548 | 1216.08ms | 905 | 30 | 1096.92 | 4816.33 | 28.4555 | 90.9072 | 10.6895 | 0.0268508 | 0.000478821 | 0.000220994 | 2(Loss) |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 288.163 | 0.154845 | 1027.17ms | 905 | 640 | 13765.7 | 2995.1 | 17.7757 | 60.5204 | 9.44199 | 0.0321823 | 0.000160566 | 3.97099e-05 | 1(Win) |
| simdjson (ondemand) | 179.11 | 0.0389711 | 1212.47ms | 905 | 4890 | 17244.6 | 4818.7 | 28.5353 | 90.2929 | 10.5691 | 0.0285214 | 0.000201109 | 5.73953e-05 | 2(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 419.908 | 0.0565322 | 1146.39ms | 1811 | 4890 | 26438 | 4113.05 | 12.26 | 45.2192 | 7.80564 | 0.000780845 | 0.000191739 | 7.90443e-05 | 1(Win) |
| simdjson (ondemand) | 272.843 | 0.0827044 | 1374.37ms | 1811 | 640 | 17540.8 | 6330.02 | 18.6748 | 69.6218 | 9.54887 | 0.0009922 | 0.000131143 | 2.93346e-05 | 2(Loss) |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 426.634 | 0.0461708 | 1136.53ms | 1811 | 4890 | 17083.2 | 4048.21 | 12.0038 | 44.1612 | 7.56985 | 0.000645341 | 0.000139344 | 4.34744e-05 | 1(Win) |
| simdjson (ondemand) | 274.212 | 0.161851 | 1363.87ms | 1811 | 1280 | 133016 | 6298.42 | 18.4165 | 68.5947 | 9.32413 | 0.000929649 | 0.000125535 | 2.93346e-05 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 892.086 | 0.0569162 | 1150.34ms | 3862 | 4890 | 27001.8 | 4128.63 | 5.7485 | 20.052 | 2.94614 | 0.00759834 | 8.80055e-05 | 3.37302e-05 | 1(Win) |
| simdjson (ondemand) | 562.533 | 0.0623398 | 1386.18ms | 3862 | 2560 | 42648.1 | 6547.33 | 9.12418 | 27.6629 | 3.59246 | 0.0125045 | 9.87183e-05 | 5.02695e-05 | 2(Loss) |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 901.788 | 0.0632875 | 1139.46ms | 3862 | 4890 | 32670.9 | 4084.21 | 5.67354 | 19.5586 | 2.833 | 0.0101703 | 6.49716e-05 | 2.94411e-05 | 1(Win) |
| simdjson (ondemand) | 570.702 | 0.0649879 | 1384.09ms | 3862 | 640 | 11257.8 | 6453.62 | 9.08084 | 27.2266 | 3.4956 | 0.0152439 | 4.04583e-05 | 8.90083e-06 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1262.28 | 0.0647561 | 1459.25ms | 9578 | 4890 | 107376 | 7236.34 | 4.05335 | 18.5102 | 3.41919 | 0.00158244 | 4.14635e-05 | 1.65683e-05 | 1(Win) |
| simdjson (ondemand) | 1114.76 | 0.0849627 | 1561.65ms | 9578 | 2560 | 124075 | 8193.95 | 4.54588 | 17.709 | 3.03393 | 0.0032883 | 5.41198e-05 | 2.62238e-05 | 2(Loss) |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1673.64 | 0.0811406 | 1408.03ms | 9578 | 4890 | 95898.1 | 5457.73 | 3.07165 | 14.176 | 2.43245 | 0.000872014 | 4.03319e-05 | 1.71661e-05 | 1(Win) |
| simdjson (ondemand) | 1437.42 | 0.0912932 | 1514.98ms | 9578 | 40 | 1346.23 | 6354.65 | 3.54161 | 13.4358 | 2.07131 | 0.00205419 | 2.08812e-05 | 7.83044e-06 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 898.106 | 0.0692675 | 1150.03ms | 3873 | 4890 | 39683.3 | 4112.63 | 5.71855 | 19.9215 | 2.90498 | 0.0109712 | 0.000127673 | 6.97504e-05 | 1(Win) |
| simdjson (ondemand) | 574.703 | 0.0552538 | 1379.47ms | 3873 | 4890 | 61665.5 | 6426.94 | 8.88597 | 27.2721 | 3.66744 | 0.0141114 | 9.59397e-05 | 4.45114e-05 | 2(Loss) |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 898.176 | 0.22215 | 1146.34ms | 3873 | 160 | 13353.1 | 4112.31 | 5.68122 | 19.4302 | 2.79783 | 0.0137861 | 5.00258e-05 | 3.22747e-06 | 1(Win) |
| simdjson (ondemand) | 584.939 | 0.0698644 | 1364.76ms | 3873 | 2560 | 49822.6 | 6314.47 | 8.74072 | 26.802 | 3.55952 | 0.0162739 | 0.000119517 | 7.03992e-05 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 701.74 | 0.0684497 | 4271.88ms | 2090234 | 40 | 1.51231e+08 | 2.84066e+06 | 7.19884 | 32.1269 | 6.19911 | 0.0227642 | 0.103981 | 0.00408245 | 1(Win) |
| simdjson (ondemand) | 641.132 | 0.515276 | 4557.64ms | 2090234 | 30 | 7.7001e+09 | 3.10919e+06 | 7.79428 | 30.8075 | 5.60208 | 0.0228199 | 0.103934 | 0.0364823 | 2(Loss) |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 811.36 | 0.0833742 | 4281.64ms | 2090234 | 40 | 1.67837e+08 | 2.45687e+06 | 6.2236 | 26.7777 | 4.90547 | 0.022101 | 0.0797942 | 0.00494075 | 1(Win) |
| simdjson (ondemand) | 769.916 | 0.0777728 | 4493.83ms | 2090234 | 80 | 3.24377e+08 | 2.58912e+06 | 6.56641 | 25.4496 | 4.30695 | 0.0218679 | 0.078531 | 0.00820861 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2063.41 | 0.089247 | 4647.65ms | 6661897 | 80 | 6.04094e+08 | 3.07903e+06 | 2.43584 | 10.997 | 1.98549 | 0.00636256 | 0.0554995 | 0.0129679 | 1(Win) |
| simdjson (ondemand) | 1949.88 | 0.107968 | 4908.67ms | 6661897 | 80 | 9.90064e+08 | 3.2583e+06 | 2.58965 | 10.5064 | 1.79617 | 0.00642217 | 0.0546474 | 0.012799 | 2(Loss) |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2351.1 | 0.183824 | 4657.35ms | 6661897 | 40 | 9.87007e+08 | 2.70226e+06 | 2.13721 | 9.33176 | 1.58231 | 0.00607305 | 0.0470557 | 0.0122824 | 1(Win) |
| simdjson (ondemand) | 2214.07 | 0.192196 | 4867.7ms | 6661897 | 30 | 9.12478e+08 | 2.86951e+06 | 2.27893 | 8.83222 | 1.39116 | 0.00612269 | 0.0466449 | 0.0124086 | 2(Loss) |

----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 611.288 | 0.0994085 | 4922.88ms | 2090234 | 30 | 3.15259e+08 | 3.26099e+06 | 8.28083 | 38.8687 | 7.33942 | 0.0234182 | 0.181715 | 0.00928354 | 1(Win) |
| simdjson (ondemand) | 576.329 | 0.121278 | 5199.49ms | 2090234 | 40 | 7.03843e+08 | 3.4588e+06 | 8.75746 | 37.5747 | 6.80131 | 0.0235388 | 0.179832 | 0.0248689 | 2(Loss) |

----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 693.967 | 0.0712273 | 4913.84ms | 2090234 | 80 | 3.34884e+08 | 2.87247e+06 | 7.29719 | 33.5501 | 6.05218 | 0.0221262 | 0.155087 | 0.00545197 | 1(Win) |
| simdjson (ondemand) | 655.904 | 0.146127 | 5190.34ms | 2090234 | 80 | 1.57784e+09 | 3.03917e+06 | 7.66578 | 32.2278 | 5.50823 | 0.0226429 | 0.154217 | 0.0120913 | 2(Loss) |

----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1682.59 | 0.288491 | 5664.86ms | 6661897 | 30 | 3.55982e+09 | 3.7759e+06 | 2.98783 | 13.1283 | 2.34654 | 0.0064893 | 0.111727 | 0.0134784 | 1(Win) |
| simdjson (ondemand) | 1621.1 | 0.318666 | 5763.26ms | 6661897 | 30 | 4.67919e+09 | 3.91912e+06 | 3.11576 | 12.6396 | 2.1744 | 0.00668219 | 0.111109 | 0.0124082 | 2(Loss) |

----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) STATISTICAL TIE | 1884.9 | 0.343654 | 5656.52ms | 6661897 | 40 | 5.36692e+09 | 3.37063e+06 | 2.67061 | 11.4565 | 1.94201 | 0.00618918 | 0.103671 | 0.00991222 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1882.81 | 0.22776 | 5631.87ms | 6661897 | 40 | 2.36264e+09 | 3.37436e+06 | 2.67355 | 10.959 | 1.76808 | 0.00637117 | 0.103158 | 0.00324435 | 1(Tie) |

----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 6394.8 | 0.107322 | 4066.26ms | 2090234 | 640 | 7.16294e+07 | 311722 | 0.789299 | 4.35177 | 0.398857 | 0.00257957 | 0.0509629 | 5.08466e-06 | 1(Win) |
| simdjson (ondemand) | 5925.71 | 0.11682 | 4382.39ms | 2090234 | 320 | 4.94193e+07 | 336399 | 0.85203 | 4.32274 | 0.498818 | 0.00238628 | 0.0507799 | 5.66175e-06 | 2(Loss) |

----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 6407.74 | 0.0574574 | 4063.75ms | 2090234 | 640 | 2.04481e+07 | 311093 | 0.787889 | 4.3517 | 0.398839 | 0.00259786 | 0.0509 | 4.51205e-06 | 1(Win) |
| simdjson (ondemand) | 5927.19 | 0.158432 | 4380.41ms | 2090234 | 30 | 8.51726e+06 | 336315 | 0.852237 | 4.32266 | 0.498801 | 0.00249073 | 0.0507094 | 3.92301e-06 | 2(Loss) |

----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 12830.4 | 0.0829397 | 6422.92ms | 6661897 | 320 | 5.3975e+07 | 495175 | 0.393135 | 2.18627 | 0.151579 | 0.000315279 | 0.0376702 | 1.08335e-05 | 1(Win) |
| simdjson (ondemand) | 11168.1 | 0.0789883 | 7331.18ms | 6661897 | 320 | 6.4612e+07 | 568877 | 0.451751 | 2.20353 | 0.196346 | 0.000408516 | 0.0377269 | 1.23857e-05 | 2(Loss) |

----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 12783.1 | 0.0925069 | 6429.3ms | 6661897 | 320 | 6.76424e+07 | 497005 | 0.393288 | 2.18625 | 0.151574 | 0.00031484 | 0.0376457 | 1.32629e-05 | 1(Win) |
| simdjson (ondemand) | 11155.8 | 0.0660751 | 7354.06ms | 6661897 | 320 | 4.53131e+07 | 569507 | 0.451832 | 2.20351 | 0.196341 | 0.000408272 | 0.0377136 | 1.42067e-05 | 2(Loss) |

----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4290.6 | 0.135187 | 6023.62ms | 2090234 | 40 | 1.57792e+07 | 464597 | 1.17752 | 6.91118 | 0.718797 | 0.00262191 | 0.0760134 | 9.58027e-06 | 1(Win) |
| simdjson (ondemand) | 4121.81 | 0.233936 | 6236.62ms | 2090234 | 160 | 2.04799e+08 | 483623 | 1.22524 | 6.67133 | 0.89919 | 0.00266538 | 0.075517 | 9.5713e-06 | 2(Loss) |

----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4290.68 | 0.0873827 | 6024.43ms | 2090234 | 160 | 2.637e+07 | 464589 | 1.17687 | 6.91111 | 0.71878 | 0.00259347 | 0.0759753 | 1.04803e-05 | 1(Win) |
| simdjson (ondemand) | 4129.12 | 0.0953812 | 6239.66ms | 2090234 | 640 | 1.357e+08 | 482767 | 1.21893 | 6.67125 | 0.899173 | 0.0026019 | 0.0754724 | 1.07486e-05 | 2(Loss) |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 9600.67 | 0.233782 | 4217.61ms | 6661897 | 80 | 1.91472e+08 | 661754 | 0.521456 | 2.98931 | 0.251964 | 0.000316862 | 0.0565241 | 1.74256e-05 | 1(Win) |
| simdjson (ondemand) | 8725.45 | 0.124916 | 4648.08ms | 6661897 | 320 | 2.64733e+08 | 728132 | 0.578282 | 2.94043 | 0.321967 | 0.000482982 | 0.056568 | 2.06248e-05 | 2(Loss) |

----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 9638.54 | 0.143464 | 4213.3ms | 6661897 | 160 | 1.4308e+08 | 659154 | 0.520117 | 2.98929 | 0.251958 | 0.00031641 | 0.0564302 | 1.41814e-05 | 1(Win) |
| simdjson (ondemand) | 8729.8 | 0.0937632 | 4642.56ms | 6661897 | 320 | 1.49006e+08 | 727770 | 0.5768 | 2.9404 | 0.321961 | 0.000481837 | 0.0565421 | 1.60704e-05 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1124.18 | 0.0499928 | 5485.89ms | 500299 | 640 | 2.88128e+07 | 424419 | 4.49121 | 17.5688 | 2.99629 | 0.0153681 | 0.0176791 | 0.000186894 | 1(Win) |
| simdjson (ondemand) | 1078.59 | 0.206655 | 5731.11ms | 500299 | 30 | 2.50702e+07 | 442356 | 4.66587 | 17.1113 | 2.92827 | 0.0207061 | 0.0185762 | 0.000199681 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1256.62 | 0.0825466 | 5370.34ms | 500299 | 320 | 3.14341e+07 | 379688 | 4.02583 | 16.4255 | 2.71979 | 0.0100517 | 0.0141793 | 0.000122783 | 1(Win) |
| simdjson (ondemand) | 1212.22 | 0.398264 | 5592.03ms | 500299 | 30 | 7.37152e+07 | 393593 | 4.16749 | 15.9683 | 2.65284 | 0.0151321 | 0.0157034 | 9.00128e-05 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2807.36 | 0.432476 | 6325.9ms | 1439562 | 640 | 2.86265e+09 | 489026 | 1.78781 | 7.08419 | 1.08728 | 0.00524163 | 0.0427678 | 0.000104208 | 1(Win) |
| simdjson (ondemand) | 2740.48 | 0.349524 | 6476.41ms | 1439562 | 640 | 1.96219e+09 | 500960 | 1.84164 | 6.81014 | 1.05874 | 0.00751038 | 0.04107 | 7.68007e-05 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3100.86 | 0.389022 | 6178.23ms | 1439562 | 640 | 1.89856e+09 | 442740 | 1.61557 | 6.68527 | 0.990758 | 0.00351719 | 0.0386357 | 6.71765e-05 | 1(Win) |
| simdjson (ondemand) | 3040.97 | 0.257557 | 6321.89ms | 1439562 | 40 | 5.40807e+07 | 451459 | 1.65926 | 6.41109 | 0.962628 | 0.00564845 | 0.0370432 | 3.5358e-05 | 2(Loss) |

----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 414.343 | 0.0633088 | 7323.01ms | 500299 | 320 | 1.70067e+08 | 1.15152e+06 | 12.1769 | 52.6472 | 12.2871 | 0.0451931 | 0.0351181 | 0.00079563 | 1(Win) |
| simdjson (ondemand) | 249.701 | 0.0636806 | 5956.94ms | 500299 | 40 | 5.92232e+07 | 1.91077e+06 | 20.226 | 87.6374 | 15.6461 | 0.0851699 | 0.028689 | 0.00139572 | 2(Loss) |

----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 431.046 | 0.0465173 | 7255.81ms | 500299 | 320 | 8.48383e+07 | 1.10689e+06 | 11.6964 | 51.5017 | 12.0107 | 0.0397014 | 0.0280977 | 0.000592627 | 1(Win) |
| simdjson (ondemand) | 256.613 | 0.0775357 | 5929.79ms | 500299 | 40 | 8.31314e+07 | 1.85931e+06 | 19.669 | 86.4901 | 15.3696 | 0.0780355 | 0.0206604 | 0.00124715 | 2(Loss) |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1133.89 | 0.116482 | 7717.78ms | 1439562 | 160 | 3.18237e+08 | 1.21076e+06 | 4.42565 | 19.267 | 4.31344 | 0.0151279 | 0.0740574 | 0.000442787 | 1(Win) |
| simdjson (ondemand) | 692.17 | 0.670632 | 6214.48ms | 1439562 | 30 | 5.30793e+09 | 1.98343e+06 | 7.28415 | 31.2994 | 5.47415 | 0.0287261 | 0.117494 | 0.000534329 | 2(Loss) |

----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1184.62 | 0.157154 | 7633.79ms | 1439562 | 40 | 1.32683e+08 | 1.15891e+06 | 4.24645 | 18.8694 | 4.21765 | 0.013144 | 0.0686444 | 0.00034349 | 1(Win) |
| simdjson (ondemand) | 712.235 | 0.467527 | 6142.63ms | 1439562 | 40 | 3.24854e+09 | 1.92756e+06 | 7.07912 | 30.899 | 5.37765 | 0.0262541 | 0.109219 | 0.0010076 | 2(Loss) |

----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4555.32 | 0.126745 | 5765.85ms | 500299 | 640 | 1.12788e+07 | 104740 | 1.10899 | 5.70425 | 1.03869 | 0.00261765 | 0.000194749 | 1.61497e-05 | 1(Win) |
| simdjson (ondemand) | 3347.44 | 0.0384923 | 7682.26ms | 500299 | 1280 | 3.85294e+06 | 142534 | 1.50773 | 6.73799 | 0.860648 | 0.00297272 | 0.000954053 | 3.19512e-05 | 2(Loss) |

----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4588.84 | 0.0636457 | 5702.89ms | 500299 | 1280 | 5.60533e+06 | 103974 | 1.09787 | 5.67563 | 1.03195 | 0.00260117 | 0.000135692 | 2.43589e-05 | 1(Win) |
| simdjson (ondemand) | 3375.74 | 0.0402257 | 7618.86ms | 500299 | 1280 | 4.13751e+06 | 141339 | 1.49799 | 6.70939 | 0.853906 | 0.00292923 | 0.000724162 | 4.24684e-05 | 2(Loss) |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 8855.39 | 0.167922 | 4187.46ms | 1439562 | 320 | 2.16875e+07 | 155033 | 0.567784 | 2.90392 | 0.398711 | 0.00132846 | 0.01495 | 1.95698e-05 | 1(Win) |
| simdjson (ondemand) | 6943.49 | 0.324029 | 5293.05ms | 1439562 | 1280 | 5.25393e+08 | 197721 | 0.728982 | 3.20355 | 0.339831 | 0.00142634 | 0.0168983 | 2.18296e-05 | 2(Loss) |

----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 8865.72 | 0.545435 | 4180.73ms | 1439562 | 640 | 4.5656e+08 | 154852 | 0.56582 | 2.89397 | 0.396368 | 0.00131383 | 0.0139049 | 1.68997e-05 | 1(Win) |
| simdjson (ondemand) | 7098.77 | 0.165218 | 5205.91ms | 1439562 | 40 | 4.08383e+06 | 193396 | 0.716535 | 3.19361 | 0.337488 | 0.00141409 | 0.0166328 | 1.3459e-05 | 2(Loss) |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2121.04 | 0.0377735 | 5930.56ms | 500299 | 1280 | 9.24156e+06 | 224947 | 2.38406 | 12.3712 | 2.35949 | 0.00501951 | 0.000263506 | 3.10533e-05 | 1(Win) |
| simdjson (ondemand) | 1690.75 | 0.0288052 | 7401.5ms | 500299 | 640 | 4.22883e+06 | 282195 | 2.99282 | 13.8243 | 2.14 | 0.0073886 | 0.00106803 | 6.02827e-05 | 2(Loss) |

----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2144.24 | 0.0343749 | 5879.61ms | 500299 | 1280 | 7.48871e+06 | 222514 | 2.36653 | 12.3426 | 2.35275 | 0.00496081 | 0.000140998 | 3.01757e-05 | 1(Win) |
| simdjson (ondemand) | 1697.17 | 0.0196285 | 7354.39ms | 500299 | 1280 | 3.89754e+06 | 281127 | 2.9789 | 13.7957 | 2.13326 | 0.00726436 | 0.000807706 | 2.08204e-05 | 2(Loss) |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4981.92 | 0.265574 | 7225.54ms | 1439562 | 80 | 4.28478e+07 | 275571 | 1.0072 | 5.22094 | 0.857736 | 0.00218673 | 0.0149953 | 7.81488e-06 | 1(Win) |
| simdjson (ondemand) | 4055.62 | 0.335338 | 4406.15ms | 1439562 | 320 | 4.12345e+08 | 338511 | 1.24322 | 5.66629 | 0.784451 | 0.00310831 | 0.0171442 | 6.46898e-06 | 2(Loss) |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4985.46 | 0.214757 | 7228.58ms | 1439562 | 160 | 5.59582e+07 | 275375 | 1.00497 | 5.21099 | 0.855393 | 0.0021761 | 0.0142133 | 7.76278e-06 | 1(Win) |
| simdjson (ondemand) | 4088.84 | 0.0505417 | 4363.58ms | 1439562 | 320 | 9.21534e+06 | 335761 | 1.23208 | 5.65635 | 0.782108 | 0.00306953 | 0.0168039 | 1.20718e-05 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1419.25 | 0.0440527 | 4535.73ms | 56369 | 1280 | 356385 | 37877.6 | 3.56948 | 15.0482 | 2.79781 | 0.00658963 | 2.31732e-05 | 1.22934e-05 | 1(Win) |
| simdjson (ondemand) | 1277.61 | 0.037887 | 4960.6ms | 56369 | 2560 | 650589 | 42076.9 | 3.96007 | 15.3297 | 2.79284 | 0.0116556 | 3.42886e-05 | 2.16694e-05 | 2(Loss) |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1802.09 | 0.043772 | 4052.93ms | 56369 | 2560 | 436474 | 29830.7 | 2.81696 | 12.8137 | 2.3115 | 0.00444386 | 2.2605e-05 | 1.49198e-05 | 1(Win) |
| simdjson (ondemand) | 1573.87 | 0.0604504 | 4515.56ms | 56369 | 1280 | 545697 | 34156.3 | 3.21265 | 13.1456 | 2.31787 | 0.00801612 | 1.09906e-05 | 4.85085e-06 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2255.55 | 0.052381 | 4733.09ms | 94370 | 2560 | 1.11828e+06 | 39900.8 | 2.24785 | 9.62161 | 1.69396 | 0.00400142 | 9.9343e-06 | 5.21965e-06 | 1(Win) |
| simdjson (ondemand) | 1988.57 | 0.0428468 | 5272.08ms | 94370 | 2560 | 962639 | 45257.8 | 2.55185 | 9.69771 | 1.69422 | 0.00968428 | 1.81756e-05 | 1.10602e-05 | 2(Loss) |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2829.6 | 0.0682208 | 4270.56ms | 94370 | 4890 | 2.30229e+06 | 31806 | 1.79439 | 8.29363 | 1.40429 | 0.00279529 | 9.90315e-06 | 5.92889e-06 | 1(Win) |
| simdjson (ondemand) | 2445.03 | 0.0866071 | 4834.95ms | 94370 | 320 | 325205 | 36808.7 | 2.10716 | 8.38857 | 1.41023 | 0.00748189 | 6.12615e-06 | 3.14586e-06 | 2(Loss) |

----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 484.742 | 0.0610303 | 6071.16ms | 56369 | 2560 | 1.17271e+07 | 110900 | 10.5269 | 46.2315 | 9.5616 | 0.0273168 | 5.84458e-05 | 3.72407e-05 | 1(Win) |
| simdjson (ondemand) | 135.06 | 0.0732962 | 5196.2ms | 56369 | 160 | 1.3618e+07 | 398029 | 37.9199 | 178.77 | 33.0174 | 0.0622517 | 0.000272867 | 0.000200908 | 2(Loss) |

----
### Discord Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 523.24 | 0.0556908 | 5807.66ms | 56369 | 640 | 2.0952e+06 | 102740 | 9.70413 | 44.0617 | 9.09477 | 0.0245395 | 3.57022e-05 | 2.38107e-05 | 1(Win) |
| simdjson (ondemand) | 136.892 | 0.064859 | 5144.64ms | 56369 | 160 | 1.03797e+07 | 392701 | 37.0218 | 176.636 | 32.5607 | 0.0579547 | 9.86801e-05 | 6.61933e-05 | 2(Loss) |

----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 793.375 | 0.0553385 | 6179.68ms | 94370 | 640 | 2.52201e+06 | 113437 | 6.39398 | 28.215 | 5.72079 | 0.0163968 | 5.36452e-05 | 3.95054e-05 | 1(Win) |
| simdjson (ondemand) | 222.787 | 0.0897097 | 5216.66ms | 94370 | 30 | 3.93991e+06 | 403965 | 22.6761 | 107.131 | 19.6991 | 0.037027 | 8.6892e-05 | 5.54555e-05 | 2(Loss) |

----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 856.519 | 0.0584432 | 5926ms | 94370 | 320 | 1.20674e+06 | 105074 | 5.90141 | 26.9227 | 5.44282 | 0.0144361 | 1.89414e-05 | 1.23848e-05 | 1(Win) |
| simdjson (ondemand) | 228.24 | 0.13642 | 5150.26ms | 94370 | 40 | 1.15745e+07 | 394313 | 22.2162 | 105.863 | 19.4276 | 0.0347992 | 9.6164e-05 | 6.99375e-05 | 2(Loss) |

----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2117.31 | 0.033723 | 3280.44ms | 56369 | 4890 | 358485 | 25389.5 | 2.38273 | 10.5642 | 1.76445 | 0.00369668 | 4.04652e-05 | 2.77169e-05 | 1(Win) |
| jsonifier (generic) | 1986.64 | 0.0621583 | 3459.25ms | 56369 | 1280 | 362118 | 27059.6 | 2.56872 | 11.1265 | 1.75601 | 0.00824976 | 2.23e-05 | 1.36794e-05 | 2(Loss) |

----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2587.15 | 0.0486997 | 3115.06ms | 56369 | 1280 | 131069 | 20778.7 | 1.9547 | 8.95583 | 1.41803 | 0.00285838 | 1.30419e-05 | 7.62276e-06 | 1(Win) |
| jsonifier (generic) | 2434.12 | 0.0458109 | 3229.73ms | 56369 | 2560 | 262046 | 22085.1 | 2.09162 | 9.5321 | 1.41191 | 0.00634068 | 1.33468e-05 | 8.35039e-06 | 2(Loss) |

----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 3254.31 | 0.0327083 | 3513.33ms | 94370 | 2560 | 209463 | 27655.1 | 1.5543 | 6.8403 | 1.0786 | 0.0029643 | 1.15155e-05 | 7.23134e-06 | 1(Win) |
| jsonifier (generic) | 3158.92 | 0.036626 | 3592.37ms | 94370 | 2560 | 278747 | 28490.2 | 1.60185 | 7.29024 | 1.07449 | 0.00411081 | 1.13003e-05 | 6.95401e-06 | 2(Loss) |

----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 3977.75 | 0.0673674 | 3283.28ms | 94370 | 640 | 148687 | 22625.4 | 1.27264 | 5.88417 | 0.87228 | 0.00182788 | 4.27175e-06 | 1.9703e-06 | 1(Win) |
| jsonifier (generic) | 3756.23 | 0.0325218 | 3432.45ms | 94370 | 4890 | 296907 | 23959.7 | 1.35231 | 6.33195 | 0.867373 | 0.00378578 | 8.36242e-06 | 5.38281e-06 | 2(Loss) |

----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1309.68 | 0.0374163 | 4843.3ms | 56369 | 2560 | 603826 | 41046.4 | 3.85981 | 18.6728 | 3.78548 | 0.00969143 | 4.36161e-05 | 3.04911e-05 | 1(Win) |
| simdjson (ondemand) | 1230.01 | 0.0762833 | 5115.41ms | 56369 | 320 | 355692 | 43705.1 | 4.1154 | 18.3159 | 3.29443 | 0.00769322 | 1.61325e-05 | 8.37118e-06 | 2(Loss) |

----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1479.77 | 0.078886 | 4665.68ms | 56369 | 640 | 525622 | 36328.4 | 3.4178 | 17.1001 | 3.44782 | 0.00871066 | 1.70195e-05 | 1.05887e-05 | 1(Win) |
| simdjson (ondemand) | 1357.91 | 0.0198782 | 4985.51ms | 56369 | 4890 | 302831 | 39588.4 | 3.7295 | 16.8015 | 2.97037 | 0.00680268 | 1.84295e-05 | 1.20518e-05 | 2(Loss) |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2155.25 | 0.0663925 | 4948.44ms | 94370 | 1280 | 983832 | 41757.7 | 2.38644 | 11.7546 | 2.27098 | 0.00545974 | 1.09526e-05 | 6.4573e-06 | 1(Win) |
| simdjson (ondemand) | 2001.83 | 0.218802 | 5238.66ms | 94370 | 30 | 290292 | 44957.9 | 2.57255 | 11.3637 | 1.96856 | 0.00528346 | 2.15464e-05 | 1.37756e-05 | 2(Loss) |

----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2396.83 | 0.170884 | 4799.48ms | 94370 | 160 | 658746 | 37548.9 | 2.12513 | 10.8163 | 2.0695 | 0.00496073 | 4.76846e-06 | 1.78817e-06 | 1(Win) |
| simdjson (ondemand) | 2217.47 | 0.0216798 | 5084.14ms | 94370 | 4890 | 378592 | 40586 | 2.30404 | 10.457 | 1.7747 | 0.00411214 | 6.34928e-06 | 3.46285e-06 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1318.76 | 0.120178 | 1596.84ms | 11812 | 640 | 67444.9 | 8541.98 | 3.91049 | 17.7295 | 3.15099 | 0.00536279 | 2.6853e-05 | 9.52421e-06 | 1(Win) |
| simdjson (ondemand) | 1075.14 | 0.0371222 | 1801.58ms | 11812 | 4890 | 73976.9 | 10477.6 | 4.78214 | 18.951 | 3.58509 | 0.00594461 | 4.14469e-05 | 1.98751e-05 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1403.39 | 0.107656 | 1585.71ms | 11812 | 1280 | 95582.1 | 8026.82 | 3.6726 | 16.6682 | 2.91263 | 0.00522899 | 2.77128e-05 | 1.38233e-05 | 1(Win) |
| simdjson (ondemand) | 1151.18 | 0.0394007 | 1766.12ms | 11812 | 4890 | 72690.9 | 9785.47 | 4.43167 | 17.8119 | 3.33026 | 0.00437452 | 2.87046e-05 | 1.41792e-05 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3032.98 | 0.0470648 | 1728.84ms | 31235 | 4890 | 104483 | 9821.36 | 1.68902 | 7.72658 | 1.24967 | 0.00254604 | 1.90194e-05 | 1.07242e-05 | 1(Win) |
| simdjson (ondemand) | 2676.26 | 0.126888 | 1879.16ms | 31235 | 40 | 7978.56 | 11130.5 | 1.93216 | 7.95249 | 1.3904 | 0.0014495 | 8.00384e-06 | 4.80231e-06 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3219.01 | 0.0555251 | 1715.8ms | 31235 | 4890 | 129100 | 9253.78 | 1.59203 | 7.34638 | 1.16402 | 0.00236133 | 1.21514e-05 | 5.78765e-06 | 1(Win) |
| simdjson (ondemand) | 2792.06 | 0.0348694 | 1858.74ms | 31235 | 4890 | 67675.6 | 10668.8 | 1.82059 | 7.55387 | 1.30117 | 0.00131678 | 1.26294e-05 | 6.63877e-06 | 2(Loss) |

----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 632.728 | 0.184746 | 2513.68ms | 11812 | 320 | 346191 | 17803.5 | 8.01298 | 34.3779 | 7.49662 | 0.0176992 | 3.59804e-05 | 1.48154e-05 | 1(Win) |
| simdjson (ondemand) | 614.079 | 0.0411087 | 2584.82ms | 11812 | 2560 | 145581 | 18344.2 | 8.31194 | 35.9749 | 6.43608 | 0.0141978 | 7.63921e-05 | 4.53723e-05 | 2(Loss) |

----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 657.572 | 0.0462879 | 2505.7ms | 11812 | 2560 | 160966 | 17130.9 | 7.73684 | 33.3298 | 7.26118 | 0.0173119 | 4.24621e-05 | 2.59601e-05 | 1(Win) |
| simdjson (ondemand) | 638.214 | 0.0576497 | 2571.4ms | 11812 | 1280 | 132532 | 17650.5 | 8.05108 | 34.8869 | 6.19286 | 0.014638 | 5.34414e-05 | 3.42607e-05 | 2(Loss) |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1600.15 | 0.0587434 | 2601.05ms | 31235 | 1280 | 153069 | 18615.7 | 3.16476 | 13.9476 | 2.87168 | 0.00654779 | 2.30361e-05 | 1.35315e-05 | 1(Win) |
| simdjson (ondemand) | 1540.02 | 0.0267648 | 2682.99ms | 31235 | 4890 | 131060 | 19342.7 | 3.29593 | 14.2837 | 2.44447 | 0.0058038 | 2.3563e-05 | 1.32186e-05 | 2(Loss) |

----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1645.4 | 0.0796367 | 2601.02ms | 31235 | 640 | 133029 | 18103.8 | 3.07841 | 13.557 | 2.78393 | 0.00651088 | 1.78085e-05 | 1.00548e-05 | 1(Win) |
| simdjson (ondemand) | 1587.1 | 0.0258099 | 2673.13ms | 31235 | 4890 | 114751 | 18768.8 | 3.18977 | 13.8779 | 2.35387 | 0.00588141 | 1.223e-05 | 5.40137e-06 | 2(Loss) |

----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2263.74 | 0.0483553 | 1240.47ms | 11812 | 4890 | 28313.4 | 4976.2 | 2.2506 | 11.0111 | 1.9702 | 0.00361125 | 2.474e-05 | 1.09417e-05 | 1(Win) |
| simdjson (ondemand) | 2170.49 | 0.0507484 | 1261.41ms | 11812 | 2560 | 17758.9 | 5189.99 | 2.34639 | 10.4887 | 1.7864 | 0.00277422 | 2.08011e-05 | 8.06912e-06 | 2(Loss) |

----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2322.22 | 0.145748 | 1235.81ms | 11812 | 640 | 31990.9 | 4850.88 | 2.19467 | 10.8198 | 1.92415 | 0.00352528 | 1.97098e-05 | 8.33369e-06 | 1(Win) |
| simdjson (ondemand) | 2203.85 | 0.141263 | 1279.05ms | 11812 | 320 | 16683.6 | 5111.43 | 2.31224 | 10.2969 | 1.74035 | 0.00277049 | 1.11116e-05 | 1.85193e-06 | 2(Loss) |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5031.56 | 0.0521678 | 1332.43ms | 31235 | 4890 | 46643.7 | 5920.24 | 1.01341 | 5.10354 | 0.790525 | 0.00171473 | 8.39339e-06 | 3.32593e-06 | 1(Win) |
| simdjson (ondemand) | 4813.16 | 0.0358396 | 1358.5ms | 31235 | 4890 | 24058 | 6188.87 | 1.05726 | 4.77023 | 0.714263 | 0.00108473 | 8.84515e-06 | 3.46997e-06 | 2(Loss) |

----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5126.97 | 0.0538956 | 1327.89ms | 31235 | 4890 | 47948.7 | 5810.06 | 0.994967 | 5.03122 | 0.773107 | 0.00165096 | 7.41133e-06 | 2.41588e-06 | 1(Win) |
| simdjson (ondemand) | 4886.7 | 0.0975055 | 1354.65ms | 31235 | 640 | 22609.4 | 6095.73 | 1.04026 | 4.69768 | 0.696847 | 0.00109147 | 5.0024e-06 | 1.55074e-06 | 2(Loss) |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1671.06 | 0.0697452 | 1415.47ms | 11812 | 2560 | 56588.9 | 6741.11 | 3.06347 | 14.6997 | 2.68981 | 0.00637176 | 1.59398e-05 | 3.86921e-06 | 1(Win) |
| simdjson (ondemand) | 1637.79 | 0.0568974 | 1428.5ms | 11812 | 1280 | 19603 | 6878.03 | 3.11006 | 13.963 | 2.3747 | 0.006292 | 1.87839e-05 | 6.94474e-06 | 2(Loss) |

----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1691.93 | 0.12549 | 1415.87ms | 11812 | 640 | 44676.8 | 6657.95 | 3.00515 | 14.5085 | 2.64375 | 0.00605542 | 2.50011e-05 | 9.12737e-06 | 1(Win) |
| simdjson (ondemand) | 1670.99 | 0.0694843 | 1426.28ms | 11812 | 1280 | 28085.4 | 6741.38 | 3.06426 | 13.7728 | 2.32865 | 0.0063082 | 1.0847e-05 | 2.44719e-06 | 2(Loss) |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3814.07 | 0.0861429 | 1526.98ms | 31235 | 2560 | 115873 | 7810.03 | 1.32618 | 6.49845 | 1.06265 | 0.00263629 | 6.70322e-06 | 2.0885e-06 | 1(Win) |
| simdjson (ondemand) | 3757.12 | 0.0355123 | 1533.1ms | 31235 | 4890 | 38764.9 | 7928.41 | 1.35089 | 6.08228 | 0.936066 | 0.00268143 | 8.17734e-06 | 2.93311e-06 | 2(Loss) |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3847.48 | 0.0600485 | 1529.02ms | 31235 | 4890 | 105692 | 7742.22 | 1.31541 | 6.42612 | 1.04524 | 0.00250508 | 7.39823e-06 | 2.49445e-06 | 1(Win) |
| simdjson (ondemand) | 3812.74 | 0.033919 | 1528.07ms | 31235 | 4890 | 34340.3 | 7812.77 | 1.33358 | 6.01034 | 0.918649 | 0.0026129 | 1.25246e-05 | 5.73527e-06 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1571.81 | 0.113416 | 7323.13ms | 108313 | 2560 | 1.42216e+07 | 65717.3 | 3.21002 | 14.3468 | 2.59225 | 0.00391831 | 2.7611e-05 | 1.66077e-05 | 1(Win) |
| simdjson (ondemand) | 1486.04 | 0.0292898 | 7732.44ms | 108313 | 2560 | 1.06114e+06 | 69510.3 | 3.42417 | 15.0223 | 2.53195 | 0.00614065 | 5.30616e-05 | 3.87008e-05 | 2(Loss) |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1717.14 | 0.0342531 | 6938.93ms | 108313 | 2560 | 1.0869e+06 | 60155.4 | 2.95168 | 13.6246 | 2.42921 | 0.00350241 | 1.10682e-05 | 7.56993e-06 | 1(Win) |
| simdjson (ondemand) | 1598.93 | 0.0163886 | 7380.09ms | 108313 | 4890 | 548141 | 64602.7 | 3.16309 | 14.3024 | 2.36882 | 0.00565088 | 1.61767e-05 | 1.06108e-05 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2804.5 | 0.0452172 | 4099.81ms | 213963 | 2560 | 2.77084e+06 | 72758.3 | 1.79423 | 8.14026 | 1.36925 | 0.00201672 | 1.4096e-05 | 1.01306e-05 | 1(Win) |
| simdjson (ondemand) | 2701.71 | 0.0687605 | 4250.58ms | 213963 | 320 | 863037 | 75526.7 | 1.87611 | 8.23311 | 1.31017 | 0.00353826 | 2.21855e-05 | 1.66939e-05 | 2(Loss) |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3037.16 | 0.0802904 | 7679.53ms | 213963 | 640 | 1.8623e+06 | 67184.8 | 1.66173 | 7.77515 | 1.28677 | 0.00179106 | 6.8499e-06 | 4.84167e-06 | 1(Win) |
| simdjson (ondemand) | 2915.2 | 0.214619 | 4096.56ms | 213963 | 40 | 902687 | 69995.6 | 1.73332 | 7.8707 | 1.22803 | 0.00313033 | 6.19266e-06 | 4.90739e-06 | 2(Loss) |

----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 448.171 | 0.11813 | 6186.09ms | 108313 | 40 | 2.96521e+06 | 230482 | 11.4838 | 52.0049 | 10.9091 | 0.0199567 | 9.9711e-05 | 7.43216e-05 | 1(Win) |
| simdjson (ondemand) | 205.282 | 0.0304168 | 6483.47ms | 108313 | 640 | 1.49923e+07 | 503188 | 24.6675 | 117.487 | 23.2114 | 0.0690338 | 0.000124985 | 8.52997e-05 | 2(Loss) |

----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 453.109 | 0.0435042 | 6061.28ms | 108313 | 320 | 3.14752e+06 | 227970 | 11.1514 | 51.2825 | 10.7465 | 0.0193122 | 8.02939e-05 | 5.90015e-05 | 1(Win) |
| simdjson (ondemand) | 207.629 | 0.0698615 | 6425.38ms | 108313 | 160 | 1.93278e+07 | 497501 | 24.4042 | 116.767 | 23.0488 | 0.0697199 | 4.06807e-05 | 2.18118e-05 | 2(Loss) |

----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 841.137 | 0.0581653 | 6386.47ms | 213963 | 1280 | 2.54849e+07 | 242590 | 5.99083 | 27.1591 | 5.56762 | 0.0101017 | 6.36719e-05 | 3.94198e-05 | 1(Win) |
| simdjson (ondemand) | 408.113 | 0.0246037 | 6436.02ms | 213963 | 640 | 9.68493e+06 | 499987 | 12.3981 | 59.4285 | 11.6244 | 0.0332173 | 0.00015467 | 0.000131638 | 2(Loss) |

----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 864.334 | 0.13028 | 6270.94ms | 213963 | 320 | 3.02703e+07 | 236079 | 5.82761 | 26.792 | 5.48498 | 0.00993855 | 7.32019e-05 | 5.46093e-05 | 1(Win) |
| simdjson (ondemand) | 414.292 | 0.0385948 | 6383.5ms | 213963 | 80 | 2.89076e+06 | 492529 | 12.1938 | 59.0635 | 11.542 | 0.0323769 | 3.1197e-05 | 2.42448e-05 | 2(Loss) |

----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4169.49 | 0.0550524 | 3231.26ms | 108313 | 1280 | 238099 | 24774.1 | 1.21471 | 6.76675 | 0.871327 | 0.000865843 | 6.94602e-06 | 4.37823e-06 | 1(Win) |
| simdjson (ondemand) | 4046.03 | 0.0296017 | 3296.7ms | 108313 | 4890 | 279284 | 25530.1 | 1.2616 | 6.29815 | 0.847849 | 0.00114464 | 8.5377e-06 | 5.89634e-06 | 2(Loss) |

----
### Instruments Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4351.65 | 0.0882419 | 3110.58ms | 108313 | 640 | 280791 | 23737 | 1.16266 | 6.58481 | 0.82269 | 0.000684446 | 7.54469e-06 | 5.43852e-06 | 1(Win) |
| simdjson (ondemand) | 4244.47 | 0.0389811 | 3208.86ms | 108313 | 2560 | 230389 | 24336.4 | 1.20925 | 6.11687 | 0.79923 | 0.00104136 | 5.3123e-06 | 3.39006e-06 | 2(Loss) |

----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 6872.85 | 0.0814486 | 3722.36ms | 213963 | 1280 | 748481 | 29689.4 | 0.739064 | 4.14431 | 0.468203 | 0.000487099 | 7.29536e-06 | 5.22506e-06 | 1(Win) |
| simdjson (ondemand) | 6659.89 | 0.0548434 | 3797.98ms | 213963 | 1280 | 361412 | 30638.8 | 0.759513 | 3.80806 | 0.455116 | 0.000569403 | 1.0169e-05 | 8.66096e-06 | 2(Loss) |

----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 7103.54 | 0.0380305 | 3631.44ms | 213963 | 4890 | 583580 | 28725.3 | 0.711196 | 4.05241 | 0.443619 | 0.000366965 | 4.64981e-06 | 3.27924e-06 | 1(Win) |
| simdjson (ondemand) | 6927.98 | 0.0238454 | 3694.78ms | 213963 | 4890 | 241202 | 29453.2 | 0.731141 | 3.71632 | 0.430533 | 0.000502648 | 4.09833e-06 | 2.86922e-06 | 2(Loss) |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2383.16 | 0.0672146 | 5107.75ms | 108313 | 640 | 543204 | 43343.9 | 2.12277 | 11.3474 | 2.15823 | 0.00292354 | 9.14595e-06 | 6.14538e-06 | 1(Win) |
| simdjson (ondemand) | 2258.53 | 0.0561894 | 5320.4ms | 108313 | 1280 | 845335 | 45735.7 | 2.24018 | 11.6365 | 1.82873 | 0.00289462 | 6.75127e-06 | 3.96709e-06 | 2(Loss) |

----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2446.53 | 0.0461876 | 4968.96ms | 108313 | 2560 | 973528 | 42221.1 | 2.06851 | 11.1646 | 2.10971 | 0.00232526 | 8.43908e-06 | 5.88211e-06 | 1(Win) |
| simdjson (ondemand) | 2329.94 | 0.274124 | 5204.63ms | 108313 | 80 | 1.18156e+06 | 44333.8 | 2.20075 | 11.4541 | 1.78021 | 0.00284096 | 3.11597e-06 | 1.96191e-06 | 2(Loss) |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4229.64 | 0.0435497 | 5591.68ms | 213963 | 2560 | 1.13001e+06 | 48243.2 | 1.19489 | 6.46042 | 1.11879 | 0.00140479 | 3.86311e-06 | 2.40258e-06 | 1(Win) |
| simdjson (ondemand) | 3944.19 | 0.0472498 | 5930.72ms | 213963 | 1280 | 764841 | 51734.5 | 1.28511 | 6.50022 | 0.948725 | 0.00177571 | 4.16252e-06 | 2.48656e-06 | 2(Loss) |

----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4309.24 | 0.0441143 | 5498.11ms | 213963 | 2560 | 1.11706e+06 | 47352 | 1.17301 | 6.36786 | 1.09425 | 0.00126314 | 1.52078e-06 | 5.31269e-07 | 1(Win) |
| simdjson (ondemand) | 4077.55 | 0.297705 | 5840.03ms | 213963 | 30 | 665843 | 50042.6 | 1.2397 | 6.40783 | 0.924193 | 0.00162458 | 1.71369e-06 | 3.1158e-07 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 606.355 | 0.307589 | 4366.52ms | 1834197 | 30 | 2.3621e+09 | 2.88482e+06 | 8.35568 | 36.5717 | 7.18608 | 0.0384136 | 0.138955 | 0.00224218 | 1(Win) |
| simdjson (ondemand) | 593.24 | 0.116773 | 4447.92ms | 1834197 | 80 | 9.48425e+08 | 2.9486e+06 | 8.50857 | 35.9316 | 6.36859 | 0.0447426 | 0.139683 | 0.000203877 | 2(Loss) |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) STATISTICAL TIE | 645.442 | 0.867632 | 4379.96ms | 1834197 | 40 | 2.21161e+10 | 2.71012e+06 | 7.807 | 33.5735 | 6.48548 | 0.0373587 | 0.118292 | 0.00014584 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 640.272 | 0.150737 | 4449.24ms | 1834197 | 30 | 5.08772e+08 | 2.73201e+06 | 7.89103 | 32.9308 | 5.66721 | 0.0436612 | 0.118935 | 0.000296951 | 1(Tie) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2839.46 | 0.444452 | 5025.57ms | 9930848 | 40 | 8.79044e+09 | 3.33542e+06 | 1.7801 | 7.79328 | 1.36944 | 0.00744358 | 0.0518529 | 0.000631389 | 1(Win) |
| simdjson (ondemand) | 2768.76 | 0.502958 | 5135.63ms | 9930848 | 80 | 2.36786e+10 | 3.42059e+06 | 1.81658 | 7.67647 | 1.22193 | 0.00781255 | 0.052251 | 0.000686819 | 2(Loss) |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3042.6 | 0.498198 | 5018.73ms | 9930848 | 80 | 1.92387e+10 | 3.11273e+06 | 1.66097 | 7.23984 | 1.24011 | 0.00724829 | 0.0479999 | 0.000680617 | 1(Win) |
| simdjson (ondemand) | 2999.45 | 0.101873 | 5131.46ms | 9930848 | 40 | 4.13874e+08 | 3.15751e+06 | 1.68104 | 7.12326 | 1.09261 | 0.00763364 | 0.0483897 | 0.00130151 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 257.176 | 0.258338 | 4783.87ms | 1834197 | 40 | 1.235e+10 | 6.80168e+06 | 19.6604 | 95.2238 | 22.004 | 0.0438528 | 0.537928 | 0.00167494 | 1(Win) |
| simdjson (ondemand) | 190.869 | 0.11531 | 6439.32ms | 1834197 | 30 | 3.35026e+09 | 9.16453e+06 | 26.4023 | 131.413 | 22.7652 | 0.0522618 | 0.791187 | 0.00198576 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 267.024 | 0.072756 | 4776.29ms | 1834197 | 40 | 9.08631e+08 | 6.55081e+06 | 18.9104 | 92.2281 | 21.3039 | 0.042599 | 0.516606 | 0.00172053 | 1(Win) |
| simdjson (ondemand) | 195.671 | 0.106926 | 6432.93ms | 1834197 | 30 | 2.74113e+09 | 8.93964e+06 | 25.8105 | 128.421 | 22.0662 | 0.051109 | 0.769795 | 0.00351414 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1281.61 | 0.389582 | 5189.78ms | 9930848 | 40 | 3.31529e+10 | 7.38979e+06 | 3.93629 | 18.6266 | 4.10641 | 0.00835587 | 0.28056 | 0.00114073 | 1(Win) |
| simdjson (ondemand) | 969.524 | 0.265662 | 6874.57ms | 9930848 | 40 | 2.69385e+10 | 9.7685e+06 | 5.20876 | 25.3132 | 4.25074 | 0.00943704 | 0.408406 | 0.0018108 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1319.39 | 0.348341 | 5200.76ms | 9930848 | 40 | 2.50091e+10 | 7.17818e+06 | 3.82358 | 18.0738 | 3.97725 | 0.00813895 | 0.276618 | 0.00157125 | 1(Win) |
| simdjson (ondemand) | 982.651 | 0.593889 | 6880.13ms | 9930848 | 40 | 1.31052e+11 | 9.638e+06 | 5.13259 | 24.7601 | 4.12149 | 0.00920601 | 0.404511 | 0.00142118 | 2(Loss) |

----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4118.04 | 0.10933 | 5535.63ms | 1834197 | 30 | 6.47008e+06 | 424771 | 1.22642 | 6.46237 | 1.20929 | 0.00204696 | 0.0755231 | 5.63371e-06 | 1(Win) |
| simdjson (ondemand) | 3456.92 | 0.616078 | 6517.51ms | 1834197 | 640 | 6.21963e+09 | 506007 | 1.4631 | 7.63588 | 0.930035 | 0.0037277 | 0.0754734 | 3.88539e-06 | 2(Loss) |

----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4115.78 | 0.0521587 | 5527.8ms | 1834197 | 80 | 3.93125e+06 | 425005 | 1.2272 | 6.46217 | 1.20925 | 0.00198577 | 0.0754867 | 2.80777e-06 | 1(Win) |
| simdjson (ondemand) | 3494.91 | 0.0763459 | 6484.8ms | 1834197 | 640 | 9.34483e+07 | 500507 | 1.44358 | 7.63568 | 0.929988 | 0.00378323 | 0.0754494 | 5.58231e-06 | 2(Loss) |

----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 11870.2 | 0.212134 | 5189.73ms | 9930848 | 40 | 1.14588e+08 | 797865 | 0.423994 | 2.19668 | 0.259132 | 0.000688995 | 0.0395227 | 1.81505e-05 | 1(Win) |
| simdjson (ondemand) | 10072.8 | 0.678719 | 5983.16ms | 9930848 | 160 | 6.51585e+09 | 940233 | 0.501185 | 2.45184 | 0.217843 | 0.000728611 | 0.0395408 | 4.71762e-05 | 2(Loss) |

----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 11834.3 | 0.307254 | 5171.75ms | 9930848 | 30 | 1.81387e+08 | 800285 | 0.424902 | 2.19664 | 0.259123 | 0.000701602 | 0.039513 | 4.3135e-05 | 1(Win) |
| simdjson (ondemand) | 10227.8 | 0.122969 | 5966.15ms | 9930848 | 30 | 3.88974e+07 | 925983 | 0.493674 | 2.4518 | 0.217834 | 0.000739427 | 0.0395323 | 1.25669e-05 | 2(Loss) |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1999.25 | 0.62402 | 5585.35ms | 1834197 | 320 | 9.53902e+09 | 874941 | 2.54667 | 13.5572 | 3.35419 | 0.00238287 | 0.150766 | 1.10811e-05 | 1(Win) |
| simdjson (ondemand) | 1635.15 | 0.132474 | 6847.82ms | 1834197 | 80 | 1.60666e+08 | 1.06977e+06 | 3.08872 | 16.6097 | 2.47757 | 0.0044854 | 0.150754 | 5.5065e-06 | 2(Loss) |

----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2004.24 | 0.0784077 | 5573.76ms | 1834197 | 320 | 1.49851e+08 | 872763 | 2.52139 | 13.557 | 3.35414 | 0.00248355 | 0.150722 | 7.1029e-06 | 1(Win) |
| simdjson (ondemand) | 1630.12 | 0.0700794 | 6861.82ms | 1834197 | 320 | 1.80961e+08 | 1.07307e+06 | 3.08569 | 16.6095 | 2.47752 | 0.00454173 | 0.150708 | 5.99036e-06 | 2(Loss) |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 7394.82 | 0.670144 | 4025.93ms | 9930848 | 30 | 2.20991e+09 | 1.28073e+06 | 0.679601 | 3.50708 | 0.655287 | 0.000777987 | 0.078988 | 0.000121235 | 1(Win) |
| simdjson (ondemand) | 6304.5 | 0.0846744 | 4720.18ms | 9930848 | 160 | 2.58879e+08 | 1.50223e+06 | 0.802435 | 4.10927 | 0.503668 | 0.000810802 | 0.079047 | 3.30511e-05 | 2(Loss) |

----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 7376.08 | 0.177112 | 4021.35ms | 9930848 | 160 | 8.2744e+08 | 1.28399e+06 | 0.680624 | 3.50704 | 0.655279 | 0.000767137 | 0.0789714 | 6.35872e-05 | 1(Win) |
| simdjson (ondemand) | 6255.24 | 0.345575 | 4781.83ms | 9930848 | 160 | 4.38015e+09 | 1.51406e+06 | 0.806576 | 4.10923 | 0.503659 | 0.000805801 | 0.0790317 | 4.3733e-05 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1185.29 | 0.0756197 | 6687.58ms | 642697 | 320 | 4.8931e+07 | 517109 | 4.24691 | 22.4467 | 3.99095 | 0.0111876 | 0.0579613 | 4.47869e-05 | 1(Win) |
| simdjson (ondemand) | 1164.63 | 0.114867 | 6874.24ms | 642697 | 80 | 2.9236e+07 | 526283 | 4.32546 | 21.7399 | 3.44073 | 0.0104091 | 0.0585758 | 1.74266e-05 | 2(Loss) |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1315.68 | 0.0797089 | 6380.62ms | 642697 | 160 | 2.20621e+07 | 465861 | 3.83262 | 21.2289 | 3.71166 | 0.0102978 | 0.0213647 | 3.82568e-05 | 1(Win) |
| simdjson (ondemand) | 1284.33 | 0.0588758 | 6520.96ms | 642697 | 320 | 2.52629e+07 | 477232 | 3.92132 | 20.5206 | 3.16147 | 0.00953931 | 0.0248173 | 9.81703e-06 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) STATISTICAL TIE | 2114.87 | 0.402539 | 7174.58ms | 1225964 | 640 | 3.16945e+09 | 552834 | 2.36145 | 12.5649 | 2.13449 | 0.00463659 | 0.0597916 | 1.28687e-05 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2104.54 | 0.493638 | 7156.76ms | 1225964 | 640 | 4.81324e+09 | 555547 | 2.38924 | 12.0324 | 1.82642 | 0.00423567 | 0.0589164 | 1.59734e-05 | 1(Tie) |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2369.03 | 0.175254 | 6774.88ms | 1225964 | 80 | 5.98466e+07 | 493524 | 2.11783 | 11.9263 | 1.98813 | 0.00430711 | 0.036498 | 4.9247e-06 | 1(Win) |
| simdjson (ondemand) | 2348.09 | 0.0293577 | 6757.77ms | 1225964 | 640 | 1.36757e+07 | 497924 | 2.14979 | 11.3933 | 1.68006 | 0.00384288 | 0.0362442 | 7.78724e-06 | 2(Loss) |

----
### Mesh Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 966.239 | 0.0755845 | 4056.51ms | 642697 | 320 | 7.3563e+07 | 634339 | 5.20487 | 28.9363 | 5.94387 | 0.0112257 | 0.0520241 | 2.14283e-05 | 1(Win) |
| simdjson (ondemand) | 717.36 | 0.324378 | 5459.72ms | 642697 | 160 | 1.22902e+09 | 854415 | 7.01667 | 39.3164 | 6.40386 | 0.0104109 | 0.0738958 | 5.48956e-05 | 2(Loss) |

----
### Mesh Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1048.47 | 0.12343 | 7920.21ms | 642697 | 40 | 2.08255e+07 | 584587 | 4.81818 | 27.7197 | 5.66517 | 0.0109045 | 0.0214457 | 1.96827e-05 | 1(Win) |
| simdjson (ondemand) | 766.017 | 0.0396625 | 5273.12ms | 642697 | 320 | 3.2229e+07 | 800144 | 6.59108 | 38.0992 | 6.12537 | 0.00970939 | 0.0410425 | 1.42758e-05 | 2(Loss) |

----
### Mesh Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1752.86 | 0.266312 | 4278.32ms | 1225964 | 40 | 1.26213e+08 | 667008 | 2.84963 | 15.9674 | 3.15838 | 0.00472502 | 0.0723158 | 1.72517e-05 | 1(Win) |
| simdjson (ondemand) | 1333.8 | 0.0637773 | 5631.46ms | 1225964 | 320 | 1.00013e+08 | 876571 | 3.77875 | 21.2474 | 3.37987 | 0.00433362 | 0.103527 | 0.000111458 | 2(Loss) |

----
### Mesh Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1893.94 | 0.0975739 | 4116.78ms | 1225964 | 320 | 1.16102e+08 | 617322 | 2.63768 | 15.329 | 3.01233 | 0.00446143 | 0.0426637 | 1.62627e-05 | 1(Win) |
| simdjson (ondemand) | 1400.32 | 0.543638 | 5469.79ms | 1225964 | 160 | 3.2964e+09 | 834931 | 3.59813 | 20.6088 | 3.23398 | 0.00395493 | 0.0713865 | 1.83325e-05 | 2(Loss) |

----
### Mesh Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3036.69 | 0.0695788 | 5357.48ms | 642697 | 1280 | 2.52449e+07 | 201839 | 1.64765 | 9.71942 | 1.61505 | 0.000114895 | 0.0170617 | 1.70133e-05 | 1(Win) |
| simdjson (ondemand) | 2847.18 | 0.0621593 | 5724.54ms | 642697 | 640 | 1.14597e+07 | 215274 | 1.76767 | 10.2379 | 1.38551 | 0.000178403 | 0.020072 | 1.77718e-05 | 2(Loss) |

----
### Mesh Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3209.63 | 0.0261255 | 5080.14ms | 642697 | 1280 | 3.18599e+06 | 190964 | 1.56931 | 9.70832 | 1.61259 | 9.95062e-05 | 0.00416414 | 1.69744e-05 | 1(Win) |
| simdjson (ondemand) | 2964.69 | 0.0976434 | 5498.15ms | 642697 | 160 | 6.52019e+06 | 206741 | 1.69306 | 10.227 | 1.38306 | 0.000216675 | 0.0100397 | 9.55933e-06 | 2(Loss) |

----
### Mesh Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5030.23 | 0.385233 | 6265.65ms | 1225964 | 80 | 6.41383e+07 | 232429 | 0.995725 | 5.78952 | 0.868393 | 4.26297e-05 | 0.028757 | 1.3051e-05 | 1(Win) |
| simdjson (ondemand) | 4748.33 | 0.247101 | 6653.09ms | 1225964 | 30 | 1.11056e+07 | 246228 | 1.06173 | 6.00271 | 0.749033 | 4.54336e-05 | 0.0310164 | 1.12021e-05 | 2(Loss) |

----
### Mesh Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5254.24 | 0.0605427 | 5926.88ms | 1225964 | 1280 | 2.32311e+07 | 222520 | 0.947516 | 5.78371 | 0.867102 | 3.46551e-05 | 0.0154048 | 5.83979e-06 | 1(Win) |
| simdjson (ondemand) | 4903.95 | 0.194945 | 6363.45ms | 1225964 | 30 | 6.4805e+06 | 238414 | 1.01338 | 5.99692 | 0.74774 | 3.93976e-05 | 0.0183758 | 3.8881e-06 | 2(Loss) |

----
### Mesh Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3033.5 | 0.209823 | 5405.85ms | 642697 | 80 | 1.43788e+07 | 202052 | 1.65105 | 9.72061 | 1.61538 | 0.000180139 | 0.0175767 | 7.83806e-06 | 1(Win) |
| simdjson (ondemand) | 2843.33 | 0.198998 | 5777.8ms | 642697 | 1280 | 2.35541e+08 | 215566 | 1.7782 | 10.2392 | 1.38573 | 0.000153871 | 0.0202686 | 3.91356e-05 | 2(Loss) |

----
### Mesh Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3217.82 | 0.0950397 | 5066.6ms | 642697 | 80 | 2.62174e+06 | 190478 | 1.57167 | 9.70952 | 1.61291 | 0.000146492 | 0.0042784 | 4.2205e-05 | 1(Win) |
| simdjson (ondemand) | 2976.54 | 0.105963 | 5482.23ms | 642697 | 80 | 3.8088e+06 | 205918 | 1.69751 | 10.2283 | 1.38328 | 0.000139782 | 0.0100237 | 1.03081e-06 | 2(Loss) |

----
### Mesh Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5019.68 | 0.0848046 | 6170.41ms | 1225964 | 1280 | 4.99404e+07 | 232917 | 0.996474 | 5.79015 | 0.868562 | 4.42063e-05 | 0.0286343 | 7.27361e-06 | 1(Win) |
| simdjson (ondemand) | 4751.38 | 0.125481 | 6528.4ms | 1225964 | 80 | 7.62717e+06 | 246070 | 1.06197 | 6.00339 | 0.749146 | 4.69732e-05 | 0.0305608 | 6.83136e-06 | 2(Loss) |

----
### Mesh Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5310.37 | 0.188207 | 5841.67ms | 1225964 | 160 | 2.74724e+07 | 220167 | 0.949311 | 5.78433 | 0.867271 | 3.65427e-05 | 0.0153403 | 3.63489e-06 | 1(Win) |
| simdjson (ondemand) | 4979 | 0.123126 | 6210.11ms | 1225964 | 40 | 3.34372e+06 | 234820 | 1.01443 | 5.99759 | 0.747853 | 4.16611e-05 | 0.0182275 | 1.34588e-06 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1238.96 | 0.118726 | 4139.5ms | 409725 | 30 | 4.20614e+06 | 315380 | 4.07738 | 18.2546 | 3.41164 | 0.0101501 | 0.024439 | 3.37625e-05 | 1(Win) |
| simdjson (ondemand) | 996.01 | 0.245497 | 5104.25ms | 409725 | 320 | 2.96826e+08 | 392310 | 5.06547 | 19.489 | 3.72541 | 0.0155887 | 0.0352115 | 1.67109e-05 | 2(Loss) |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1561.21 | 0.0662661 | 7792.68ms | 409725 | 160 | 4.40113e+06 | 250283 | 3.23583 | 15.2642 | 2.74245 | 0.00648403 | 0.0120692 | 1.15016e-05 | 1(Win) |
| simdjson (ondemand) | 1200.35 | 0.191853 | 4839.15ms | 409725 | 320 | 1.24813e+08 | 325526 | 4.20942 | 16.5122 | 3.0595 | 0.0115133 | 0.0164521 | 8.81689e-06 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2211.07 | 0.119947 | 4457.57ms | 785750 | 160 | 2.64399e+07 | 338907 | 2.2793 | 10.2193 | 1.80597 | 0.00640494 | 0.0332692 | 1.24483e-05 | 1(Win) |
| simdjson (ondemand) | 1782.94 | 0.182854 | 5473.64ms | 785750 | 640 | 3.77993e+08 | 420289 | 2.83126 | 10.7703 | 1.97177 | 0.00963428 | 0.0391252 | 1.27605e-05 | 2(Loss) |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2704.18 | 0.468344 | 4211.15ms | 785750 | 320 | 5.38987e+08 | 277108 | 1.84611 | 8.66238 | 1.45751 | 0.00444308 | 0.0190228 | 1.18875e-05 | 1(Win) |
| simdjson (ondemand) | 2140.32 | 0.102649 | 5169.99ms | 785750 | 80 | 1.03327e+07 | 350111 | 2.36025 | 9.21835 | 1.6245 | 0.00743301 | 0.0225285 | 3.51575e-06 | 2(Loss) |

----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 491.949 | 0.0529045 | 5077.66ms | 409725 | 320 | 5.65042e+07 | 794278 | 10.2673 | 40.9202 | 8.48035 | 0.0452005 | 0.0736543 | 6.21758e-05 | 1(Win) |
| simdjson (ondemand) | 403.613 | 0.165956 | 6153.09ms | 409725 | 160 | 4.13007e+08 | 968115 | 12.5172 | 56.1266 | 10.7007 | 0.0200073 | 0.0463902 | 3.28116e-05 | 2(Loss) |

----
### Random Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 539.271 | 0.187302 | 4937.71ms | 409725 | 30 | 5.52558e+07 | 724579 | 9.40579 | 37.9502 | 7.8159 | 0.0409771 | 0.0349174 | 0.000142128 | 1(Win) |
| simdjson (ondemand) | 435.275 | 0.238273 | 6024.38ms | 409725 | 320 | 1.46405e+09 | 897695 | 11.5517 | 53.1631 | 10.0379 | 0.015935 | 0.0195015 | 1.8038e-05 | 2(Loss) |

----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 907.149 | 0.55668 | 5265.99ms | 785750 | 320 | 6.76663e+09 | 826049 | 5.54659 | 22.021 | 4.44246 | 0.023275 | 0.0719443 | 0.000101499 | 1(Win) |
| simdjson (ondemand) | 770.227 | 0.065507 | 6260.92ms | 785750 | 40 | 1.62468e+07 | 972894 | 6.55192 | 29.7739 | 5.58758 | 0.0116287 | 0.0468736 | 0.000217054 | 2(Loss) |

----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 992.467 | 0.599224 | 5134.18ms | 785750 | 320 | 6.55036e+09 | 755037 | 5.08692 | 20.4748 | 4.09659 | 0.0209685 | 0.0462253 | 6.10444e-05 | 1(Win) |
| simdjson (ondemand) | 815.448 | 0.375535 | 6140.95ms | 785750 | 320 | 3.81089e+09 | 918943 | 6.16554 | 28.2285 | 5.24196 | 0.00937203 | 0.0240515 | 1.51328e-05 | 2(Loss) |

----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2249.53 | 0.208968 | 4637.87ms | 409725 | 30 | 3.95261e+06 | 173700 | 2.24007 | 10.6565 | 1.89187 | 0.00683434 | 0.00190656 | 3.03456e-05 | 1(Win) |
| simdjson (ondemand) | 1996.28 | 0.0900141 | 5204.77ms | 409725 | 40 | 1.24172e+06 | 195736 | 2.5312 | 10.1933 | 1.78492 | 0.00733693 | 0.00259876 | 9.09146e-06 | 2(Loss) |

----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2608.3 | 0.128955 | 4548.79ms | 409725 | 80 | 2.98565e+06 | 149808 | 1.9377 | 9.63408 | 1.65868 | 0.0048096 | 0.00111111 | 3.53896e-06 | 1(Win) |
| simdjson (ondemand) | 2283.48 | 0.04941 | 5056.77ms | 409725 | 160 | 1.14377e+06 | 171118 | 2.21299 | 9.17919 | 1.55049 | 0.00565364 | 0.00132578 | 1.96778e-05 | 2(Loss) |

----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3795.25 | 0.0744537 | 5242.85ms | 785750 | 640 | 1.38306e+07 | 197444 | 1.32184 | 6.25115 | 1.0108 | 0.00479655 | 0.00626008 | 1.7537e-05 | 1(Win) |
| simdjson (ondemand) | 3448.93 | 0.0950687 | 5758.95ms | 785750 | 80 | 3.41324e+06 | 217270 | 1.46467 | 5.90343 | 0.957497 | 0.00443495 | 0.00466931 | 6.55584e-05 | 2(Loss) |

----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4394.35 | 0.128335 | 5093.02ms | 785750 | 40 | 1.91571e+06 | 170526 | 1.15004 | 5.71833 | 0.889258 | 0.00340573 | 0.00429077 | 4.01845e-05 | 1(Win) |
| simdjson (ondemand) | 3881.02 | 0.0885367 | 5664.95ms | 785750 | 40 | 1.16892e+06 | 193081 | 1.3022 | 5.37373 | 0.834962 | 0.00368651 | 0.00267801 | 2.06809e-06 | 2(Loss) |

----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1517.66 | 0.141462 | 6784.79ms | 409725 | 1280 | 1.69796e+08 | 257465 | 3.32458 | 16.3227 | 3.02859 | 0.00755821 | 0.00213949 | 9.49055e-05 | 1(Win) |
| simdjson (ondemand) | 1499.16 | 0.0893206 | 6872.31ms | 409725 | 320 | 1.73437e+07 | 260642 | 3.36893 | 15.5518 | 2.75777 | 0.00670684 | 0.00247025 | 2.31481e-05 | 2(Loss) |

----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1673.03 | 0.0588236 | 6647.66ms | 409725 | 1280 | 2.41597e+07 | 233555 | 3.01944 | 15.2984 | 2.79207 | 0.00632928 | 0.00105948 | 6.06733e-06 | 1(Win) |
| simdjson (ondemand) | 1633.64 | 0.146531 | 6796.32ms | 409725 | 30 | 3.68514e+06 | 239187 | 3.0932 | 14.5345 | 2.52252 | 0.00581048 | 0.00142746 | 2.13151e-05 | 2(Loss) |

----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2697.45 | 0.315001 | 7409.8ms | 785750 | 80 | 6.126e+07 | 277800 | 1.8649 | 9.20832 | 1.60438 | 0.00504747 | 0.00633058 | 7.58829e-06 | 1(Win) |
| simdjson (ondemand) | 2641.95 | 0.0858941 | 7554.57ms | 785750 | 30 | 1.78061e+06 | 283635 | 1.91222 | 8.70451 | 1.46524 | 0.00453215 | 0.00464427 | 5.93912e-06 | 2(Loss) |

----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) STATISTICAL TIE | 2904.09 | 0.453269 | 7267.29ms | 785750 | 640 | 8.7547e+08 | 258033 | 1.72799 | 8.67348 | 1.48112 | 0.0041542 | 0.00439562 | 2.77541e-05 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2897.25 | 0.142538 | 7368.62ms | 785750 | 30 | 4.07735e+06 | 258642 | 1.74431 | 8.174 | 1.34256 | 0.00348139 | 0.00261207 | 5.81186e-06 | 1(Tie) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1838.26 | 0.0811849 | 7397.03ms | 264040 | 1280 | 1.58302e+07 | 136982 | 2.75795 | 10.3111 | 1.78646 | 0.00808153 | 0.000242746 | 9.86356e-05 | 1(Win) |
| simdjson (ondemand) | 1653.28 | 0.245964 | 4090.68ms | 264040 | 320 | 4.49094e+07 | 152308 | 3.03909 | 10.1983 | 1.76552 | 0.0147332 | 0.000435741 | 3.30916e-05 | 2(Loss) |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2306.11 | 0.117933 | 6621.22ms | 264040 | 160 | 2.6532e+06 | 109192 | 2.19171 | 8.89979 | 1.46328 | 0.0037585 | 1.56463e-05 | 1.02967e-05 | 1(Win) |
| simdjson (ondemand) | 1988.34 | 0.0545717 | 7664.79ms | 264040 | 2560 | 1.22274e+07 | 126643 | 2.52824 | 8.79308 | 1.44512 | 0.0118752 | 6.65249e-05 | 1.04639e-05 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2499.13 | 0.128741 | 4097.59ms | 399947 | 640 | 2.47081e+07 | 152621 | 2.00659 | 7.38644 | 1.20269 | 0.00759907 | 0.00137576 | 2.489e-05 | 1(Win) |
| simdjson (ondemand) | 2392.06 | 0.102945 | 4280.6ms | 399947 | 640 | 1.72444e+07 | 159452 | 2.10474 | 7.17081 | 1.18431 | 0.0096899 | 0.00165091 | 3.64853e-05 | 2(Loss) |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3059.04 | 0.0613761 | 7527.57ms | 399947 | 2560 | 1.49925e+07 | 124686 | 1.64349 | 6.45487 | 0.989369 | 0.00525792 | 8.80156e-05 | 1.10786e-05 | 1(Win) |
| simdjson (ondemand) | 2865.08 | 0.0603095 | 8012.63ms | 399947 | 1280 | 8.25111e+06 | 133127 | 1.759 | 6.24698 | 0.97383 | 0.0077005 | 0.000153639 | 8.67693e-06 | 2(Loss) |

----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 619.132 | 0.054622 | 5241.45ms | 264040 | 320 | 1.57927e+07 | 406712 | 8.16057 | 30.4845 | 5.87072 | 0.0245706 | 0.0128902 | 6.36741e-05 | 1(Win) |
| simdjson (ondemand) | 207.439 | 0.0861374 | 7699.74ms | 264040 | 320 | 3.49859e+08 | 1.21389e+06 | 24.1874 | 84.3303 | 17.0274 | 0.166454 | 0.00334294 | 0.000195425 | 2(Loss) |

----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 661.438 | 0.0853556 | 5135.08ms | 264040 | 320 | 3.3789e+07 | 380698 | 7.62855 | 29.0752 | 5.548 | 0.020745 | 0.0058756 | 9.36648e-05 | 1(Win) |
| simdjson (ondemand) | 214.288 | 0.120911 | 7577.55ms | 264040 | 160 | 3.22992e+08 | 1.17509e+06 | 23.4532 | 82.9241 | 16.7072 | 0.157412 | 0.000864571 | 6.81715e-05 | 2(Loss) |

----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 925.019 | 0.0716123 | 5335.99ms | 399947 | 320 | 2.79016e+07 | 412337 | 5.45338 | 20.6821 | 3.89341 | 0.0148797 | 0.0146598 | 4.97644e-05 | 1(Win) |
| simdjson (ondemand) | 328.953 | 0.0847952 | 7350.93ms | 399947 | 320 | 3.09336e+08 | 1.1595e+06 | 15.2755 | 55.6125 | 11.149 | 0.0893331 | 0.00355868 | 0.00032166 | 2(Loss) |

----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 997.014 | 0.116265 | 5185.83ms | 399947 | 160 | 3.16533e+07 | 382561 | 5.07317 | 19.7489 | 3.6798 | 0.0119812 | 0.00689582 | 5.07255e-05 | 1(Win) |
| simdjson (ondemand) | 340.796 | 0.108773 | 7239.14ms | 399947 | 160 | 2.37126e+08 | 1.1192e+06 | 14.7512 | 54.6831 | 10.9374 | 0.0828923 | 0.000965331 | 0.000156536 | 2(Loss) |

----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5935.16 | 0.0400504 | 5001.91ms | 264040 | 2560 | 739141 | 42426.5 | 0.851906 | 4.45532 | 0.501258 | 0.000969103 | 4.50334e-06 | 2.66295e-06 | 1(Win) |
| simdjson (ondemand) | 5725.32 | 0.0323192 | 5145.62ms | 264040 | 4890 | 988034 | 43981.5 | 0.881478 | 4.15972 | 0.473239 | 0.000810921 | 8.85563e-06 | 5.78242e-06 | 2(Loss) |

----
### Twitter Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 6126.22 | 0.0286823 | 4926.66ms | 264040 | 4890 | 679661 | 41103.4 | 0.825731 | 4.37171 | 0.482723 | 0.0009525 | 5.53613e-06 | 3.91432e-06 | 1(Win) |
| simdjson (ondemand) | 5888.64 | 0.0450672 | 5081.85ms | 264040 | 2560 | 950763 | 42761.7 | 0.85648 | 4.07744 | 0.454655 | 0.000794577 | 5.06404e-06 | 2.96475e-06 | 2(Loss) |

----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 7632.28 | 0.0450635 | 5759.79ms | 399947 | 4890 | 2.48002e+06 | 49974.4 | 0.657679 | 3.50088 | 0.350522 | 0.000649137 | 6.35105e-06 | 3.72033e-06 | 1(Win) |
| simdjson (ondemand) | 7478.36 | 0.0421474 | 5849.05ms | 399947 | 2560 | 1.18297e+06 | 51003.1 | 0.672979 | 3.19337 | 0.333542 | 0.000546288 | 5.74686e-06 | 3.20257e-06 | 2(Loss) |

----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 7820.06 | 0.0509352 | 5722.01ms | 399947 | 4890 | 3.01807e+06 | 48774.5 | 0.642386 | 3.44573 | 0.33829 | 0.000614327 | 1.36071e-05 | 1.11288e-05 | 1(Win) |
| simdjson (ondemand) | 7693.29 | 0.0673328 | 5786.45ms | 399947 | 640 | 713205 | 49578.2 | 0.655894 | 3.13905 | 0.321273 | 0.000560981 | 4.74672e-06 | 3.35201e-06 | 2(Loss) |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3534 | 0.0692249 | 4034.62ms | 264040 | 320 | 778539 | 71253 | 1.43038 | 7.63412 | 1.20138 | 0.00146688 | 9.66946e-06 | 6.60411e-06 | 1(Win) |
| simdjson (ondemand) | 3202.08 | 0.059947 | 4408.89ms | 264040 | 1280 | 2.84459e+06 | 78639 | 1.57516 | 7.37076 | 1.07019 | 0.002128 | 8.14862e-06 | 4.79923e-06 | 2(Loss) |

----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3608.04 | 0.0184908 | 7818.64ms | 264040 | 4890 | 814365 | 69790.8 | 1.40141 | 7.55522 | 1.18419 | 0.00141671 | 5.30223e-06 | 3.60685e-06 | 1(Win) |
| simdjson (ondemand) | 3251.26 | 0.152152 | 4375.75ms | 264040 | 1280 | 1.77746e+07 | 77449.4 | 1.55352 | 7.29275 | 1.05294 | 0.00203874 | 1.69304e-05 | 1.33769e-05 | 2(Loss) |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4810.18 | 0.0551173 | 4452.63ms | 399947 | 2560 | 4.88988e+06 | 79294.1 | 1.04552 | 5.60033 | 0.813073 | 0.0012408 | 3.10393e-06 | 1.68284e-06 | 1(Win) |
| simdjson (ondemand) | 4411.96 | 0.150387 | 4808.17ms | 399947 | 160 | 2.70447e+06 | 86451.3 | 1.1431 | 5.32179 | 0.729649 | 0.00146313 | 5.657e-06 | 3.84426e-06 | 2(Loss) |

----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4914.13 | 0.303618 | 4405.52ms | 399947 | 30 | 1.66605e+06 | 77616.9 | 1.02875 | 5.5483 | 0.801744 | 0.00122341 | 5.66742e-06 | 3.7505e-06 | 1(Win) |
| simdjson (ondemand) | 4508.01 | 0.0620738 | 4749.11ms | 399947 | 1280 | 3.53071e+06 | 84609.2 | 1.11754 | 5.27028 | 0.718265 | 0.00142268 | 3.44186e-06 | 1.92994e-06 | 2(Loss) |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 721.507 | 0.0551322 | 1363.58ms | 4630 | 4890 | 55667.3 | 6119.85 | 7.08477 | 32.4382 | 6.13197 | 0.00263062 | 0.000188068 | 0.000106975 | 1(Win) |
| simdjson (ondemand) | 695.331 | 0.0669963 | 1381.93ms | 4630 | 2560 | 46336.2 | 6350.23 | 7.31129 | 30.6868 | 5.47128 | 0.00284642 | 9.63485e-05 | 4.59807e-05 | 2(Loss) |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 857.586 | 0.0794132 | 1360ms | 4630 | 2560 | 42798.9 | 5148.77 | 5.96573 | 27.5611 | 5.01706 | 0.0017838 | 4.46308e-05 | 1.18959e-05 | 1(Win) |
| simdjson (ondemand) | 813.349 | 0.0576605 | 1386.66ms | 4630 | 4890 | 47915.3 | 5428.81 | 6.29355 | 26.2598 | 4.44687 | 0.00122041 | 7.53069e-05 | 2.416e-05 | 2(Loss) |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2164.62 | 0.0507646 | 1400.36ms | 14795 | 4890 | 53542.4 | 6518.29 | 2.34984 | 10.8935 | 1.92748 | 0.00100104 | 2.65247e-05 | 9.37143e-06 | 1(Win) |
| simdjson (ondemand) | 2058.49 | 0.126248 | 1430.86ms | 14795 | 640 | 47925.2 | 6854.36 | 2.48856 | 10.4166 | 1.74606 | 0.000808973 | 1.26732e-05 | 1.37293e-06 | 2(Loss) |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2565.08 | 0.157144 | 1400.42ms | 14795 | 40 | 2988.69 | 5500.65 | 2.02453 | 9.51254 | 1.60757 | 0.000873606 | 3.5485e-05 | 1.35181e-05 | 1(Win) |
| simdjson (ondemand) | 2377.12 | 0.0442821 | 1440.24ms | 14795 | 4890 | 33782.7 | 5935.59 | 2.14384 | 9.03718 | 1.42697 | 0.000476188 | 1.57711e-05 | 4.20194e-06 | 2(Loss) |

----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 611.556 | 0.0423957 | 1471.87ms | 4630 | 4890 | 45818.6 | 7220.13 | 8.3097 | 38.8207 | 7.21253 | 0.00393817 | 5.0926e-05 | 1.64306e-05 | 1(Win) |
| simdjson (ondemand) | 559.814 | 0.0603754 | 1535.25ms | 4630 | 2560 | 58054.3 | 7887.47 | 9.09884 | 37.3888 | 6.65486 | 0.00809032 | 0.000100398 | 4.07499e-05 | 2(Loss) |

----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 702.261 | 0.0541426 | 1468.71ms | 4630 | 4890 | 56669.8 | 6287.57 | 7.24503 | 34.3276 | 6.17495 | 0.00295786 | 5.42828e-05 | 1.55472e-05 | 1(Win) |
| simdjson (ondemand) | 625.275 | 0.042709 | 1546.43ms | 4630 | 4890 | 44480.2 | 7061.71 | 8.13004 | 33.1104 | 5.66112 | 0.00655315 | 6.0113e-05 | 1.70489e-05 | 2(Loss) |

----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1831.52 | 0.0399683 | 1523.19ms | 14795 | 4890 | 46360.4 | 7703.77 | 2.77756 | 13.0257 | 2.29307 | 0.00175229 | 6.29185e-05 | 3.34911e-05 | 1(Win) |
| simdjson (ondemand) | 1694.31 | 0.0512065 | 1579.37ms | 14795 | 2560 | 46551.9 | 8327.67 | 2.99693 | 12.5451 | 2.12329 | 0.00207458 | 1.77161e-05 | 5.91416e-06 | 2(Loss) |

----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2075.91 | 0.097864 | 1528.87ms | 14795 | 640 | 28316.4 | 6796.82 | 2.45051 | 11.6729 | 1.97891 | 0.00122835 | 1.62639e-05 | 3.69635e-06 | 1(Win) |
| simdjson (ondemand) | 1922.55 | 0.0432707 | 1584.72ms | 14795 | 4890 | 49313.9 | 7339 | 2.64516 | 11.1369 | 1.79858 | 0.00224334 | 3.58271e-05 | 1.80794e-05 | 2(Loss) |

----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5645.12 | 0.126196 | 817.674ms | 4630 | 4890 | 4764.46 | 782.183 | 0.944186 | 4.74276 | 0.465227 | 0.000433158 | 1.95224e-05 | 8.92199e-06 | 1(Win) |
| simdjson (ondemand) | 4603.31 | 0.0984927 | 831.172ms | 4630 | 4890 | 4364.54 | 959.204 | 1.14376 | 4.69482 | 0.565443 | 0.00204861 | 1.03354e-05 | 1.63423e-06 | 2(Loss) |

----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5785.02 | 0.26621 | 811.651ms | 4630 | 30 | 123.857 | 763.267 | 0.923492 | 4.70778 | 0.457235 | 0.000439165 | 1.43988e-05 | 0 | 1(Win) |
| simdjson (ondemand) | 4643.02 | 0.259107 | 834.57ms | 4630 | 1280 | 7771.91 | 951 | 1.13251 | 4.65961 | 0.557452 | 0.00192427 | 6.41199e-06 | 1.34989e-06 | 2(Loss) |

----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 11953.9 | 0.0916598 | 859.362ms | 14795 | 4890 | 5723.74 | 1180.34 | 0.437693 | 2.288 | 0.171477 | 0.000165977 | 6.02647e-06 | 1.6863e-06 | 1(Win) |
| simdjson (ondemand) | 9634.99 | 0.0688525 | 886.874ms | 14795 | 4890 | 4971.37 | 1464.41 | 0.536977 | 2.30896 | 0.216627 | 0.000494958 | 4.92069e-06 | 2.34977e-07 | 2(Loss) |

----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 12086.6 | 0.0964327 | 856.982ms | 14795 | 4890 | 6197 | 1167.38 | 0.43093 | 2.27705 | 0.168976 | 0.000164746 | 3.74581e-06 | 1.38222e-07 | 1(Win) |
| simdjson (ondemand) | 9752.63 | 0.186291 | 883.836ms | 14795 | 640 | 4648.9 | 1446.75 | 0.532636 | 2.29794 | 0.214126 | 0.000526571 | 2.74586e-06 | 3.1683e-07 | 2(Loss) |

----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3841.25 | 0.0820565 | 850.526ms | 4630 | 160 | 142.352 | 1149.5 | 1.36427 | 7.34255 | 0.796544 | 0.000650648 | 2.69978e-06 | 0 | 1(Win) |
| simdjson (ondemand) | 3117.28 | 0.083097 | 876.479ms | 4630 | 2560 | 3546.68 | 1416.46 | 1.68243 | 7.10821 | 0.978618 | 0.00280474 | 2.19357e-05 | 7.1713e-06 | 2(Loss) |

----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3915.88 | 0.144537 | 847.721ms | 4630 | 2560 | 6799.89 | 1127.59 | 1.3488 | 7.30734 | 0.788553 | 0.000653601 | 2.00796e-05 | 1.06304e-05 | 1(Win) |
| simdjson (ondemand) | 3161.99 | 0.0865082 | 877.24ms | 4630 | 2560 | 3735.92 | 1396.44 | 1.65243 | 7.07322 | 0.970627 | 0.00329002 | 1.04617e-05 | 1.34989e-06 | 2(Loss) |

----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 9207.22 | 0.112418 | 891.204ms | 14795 | 40 | 118.715 | 1532.45 | 0.563472 | 3.10159 | 0.275161 | 0.000202771 | 1.68976e-05 | 1.18283e-05 | 1(Win) |
| simdjson (ondemand) | 7346.18 | 0.0591677 | 929.809ms | 14795 | 4890 | 6315.18 | 1920.67 | 0.702771 | 3.06421 | 0.345928 | 0.00105787 | 4.34016e-06 | 2.07333e-07 | 2(Loss) |

----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 9178.8 | 0.0878836 | 894.725ms | 14795 | 4890 | 8924.49 | 1537.2 | 0.565012 | 3.09057 | 0.27266 | 0.000203227 | 4.60278e-06 | 7.74041e-07 | 1(Win) |
| simdjson (ondemand) | 7440.11 | 0.0583286 | 928.787ms | 14795 | 2560 | 3132.38 | 1896.42 | 0.694177 | 3.05326 | 0.343427 | 0.001145 | 4.51483e-06 | 5.2805e-07 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1123.77 | 0.105581 | 1178.41ms | 5092 | 1280 | 26644.2 | 4321.28 | 4.53751 | 17.4389 | 3.09603 | 0.0024065 | 9.38973e-05 | 5.33926e-05 | 1(Win) |
| jsonifier (generic) | 1071.22 | 0.0909925 | 1208.75ms | 5092 | 2560 | 43558.6 | 4533.27 | 4.76081 | 18.3184 | 3.25788 | 0.00361466 | 4.79459e-05 | 1.08166e-05 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1284.7 | 0.0634302 | 1201.56ms | 5092 | 4890 | 28110.7 | 3779.95 | 3.97846 | 15.5008 | 2.64336 | 0.00202178 | 0.000104338 | 5.80324e-05 | 1(Win) |
| jsonifier (generic) | 1244.99 | 0.181993 | 1221.79ms | 5092 | 640 | 32250.2 | 3900.51 | 4.10353 | 16.1472 | 2.7529 | 0.00250362 | 3.95842e-05 | 1.65701e-05 | 2(Loss) |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2395.37 | 0.0558249 | 1219.11ms | 11724 | 4890 | 33202.5 | 4667.71 | 2.12952 | 8.28437 | 1.3759 | 0.00151028 | 7.30852e-05 | 4.15138e-05 | 1(Win) |
| jsonifier (generic) | 2248.54 | 0.227418 | 1251.58ms | 11724 | 640 | 81842.8 | 4972.52 | 2.26428 | 8.86209 | 1.45949 | 0.00157649 | 1.5593e-05 | 4.79785e-06 | 2(Loss) |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2717 | 0.111703 | 1236.89ms | 11724 | 1280 | 27046.4 | 4115.16 | 1.87948 | 7.46366 | 1.18304 | 0.00136339 | 2.26565e-05 | 9.86225e-06 | 1(Win) |
| jsonifier (generic) | 2584.84 | 0.125298 | 1273.87ms | 11724 | 1280 | 37599.5 | 4325.55 | 1.97089 | 7.92134 | 1.24111 | 0.0011063 | 1.45935e-05 | 2.33229e-06 | 2(Loss) |

----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 463.739 | 0.105239 | 1819.77ms | 5092 | 1280 | 155450 | 10471.6 | 10.952 | 45.1514 | 10.1196 | 0.00588346 | 9.06753e-05 | 4.05047e-05 | 1(Win) |
| simdjson (ondemand) | 307.549 | 0.0497354 | 2332.19ms | 5092 | 2560 | 157877 | 15789.7 | 16.4977 | 70.479 | 12.7997 | 0.00968216 | 0.000139849 | 7.54861e-05 | 2(Loss) |

----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 488.505 | 0.0521869 | 1796.08ms | 5092 | 4890 | 131605 | 9940.77 | 10.4037 | 43.1526 | 9.6506 | 0.00612003 | 0.00011478 | 6.54622e-05 | 1(Win) |
| simdjson (ondemand) | 316.433 | 0.0321249 | 2323.52ms | 5092 | 4890 | 118852 | 15346.4 | 16.0138 | 68.7151 | 12.3777 | 0.0106143 | 5.48195e-05 | 1.95182e-05 | 2(Loss) |

----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1023.3 | 0.0565297 | 1844.66ms | 11724 | 4890 | 186554 | 10926.2 | 4.95972 | 20.5495 | 4.44618 | 0.00284942 | 5.6375e-05 | 3.12923e-05 | 1(Win) |
| simdjson (ondemand) | 696.271 | 0.0332174 | 2354.91ms | 11724 | 4890 | 139135 | 16058.2 | 7.29851 | 31.2955 | 5.58333 | 0.0041942 | 3.20424e-05 | 1.34833e-05 | 2(Loss) |

----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1085.66 | 0.054334 | 1834.26ms | 11724 | 4890 | 153115 | 10298.7 | 4.67875 | 19.6501 | 4.23606 | 0.00266771 | 2.69142e-05 | 9.24467e-06 | 1(Win) |
| simdjson (ondemand) | 721.347 | 0.0427212 | 2348.13ms | 11724 | 2560 | 112251 | 15500 | 7.04733 | 30.5306 | 5.39974 | 0.00422331 | 4.7612e-05 | 2.70545e-05 | 2(Loss) |

----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4350.5 | 0.0935609 | 849.401ms | 5092 | 4890 | 5333.31 | 1116.22 | 1.2044 | 5.25177 | 0.900432 | 0.000740405 | 7.91168e-06 | 2.81126e-07 | 1(Win) |
| simdjson (ondemand) | 3584.38 | 0.111355 | 873.406ms | 5092 | 2560 | 5826.51 | 1354.8 | 1.44775 | 6.00668 | 0.752946 | 0.00119059 | 2.33976e-05 | 4.83295e-06 | 2(Loss) |

----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4564.6 | 0.121997 | 840.69ms | 5092 | 2560 | 4312.3 | 1063.86 | 1.151 | 5.13865 | 0.875491 | 0.000433048 | 1.08933e-05 | 2.22469e-06 | 1(Win) |
| simdjson (ondemand) | 3697.54 | 0.0793321 | 863.466ms | 5092 | 4890 | 5308.34 | 1313.34 | 1.40706 | 5.89415 | 0.728005 | 0.00101872 | 1.30121e-05 | 9.6386e-07 | 2(Loss) |

----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 7812.2 | 0.0882887 | 879.883ms | 11724 | 4890 | 7807.72 | 1431.21 | 0.665725 | 3.08828 | 0.422467 | 0.00030783 | 7.84924e-06 | 9.41909e-07 | 1(Win) |
| simdjson (ondemand) | 6698.81 | 0.101876 | 900.024ms | 11724 | 2560 | 7401.91 | 1669.08 | 0.772318 | 3.34092 | 0.362078 | 0.000491846 | 9.5957e-06 | 1.43269e-06 | 2(Loss) |

----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 8060.11 | 0.0747023 | 873.595ms | 11724 | 4890 | 5251.05 | 1387.19 | 0.64541 | 3.03917 | 0.411638 | 0.000219203 | 7.50039e-06 | 1.37798e-06 | 1(Win) |
| simdjson (ondemand) | 6862.33 | 0.0899794 | 895.413ms | 11724 | 2560 | 5502.18 | 1629.31 | 0.754429 | 3.29205 | 0.351245 | 0.000458128 | 8.79606e-06 | 7.99642e-07 | 2(Loss) |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2496.63 | 0.0848905 | 930.609ms | 5092 | 80 | 218.11 | 1945.06 | 2.06903 | 9.56049 | 1.76493 | 0.0010924 | 7.36449e-06 | 2.45483e-06 | 1(Win) |
| simdjson (ondemand) | 2092.89 | 0.0976193 | 970.661ms | 5092 | 80 | 410.435 | 2320.29 | 2.45774 | 10.6298 | 1.59878 | 0.00107031 | 3.92773e-05 | 0 | 2(Loss) |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2532.78 | 0.0869347 | 927.499ms | 5092 | 2560 | 7112.26 | 1917.3 | 2.03786 | 9.44737 | 1.73998 | 0.000821908 | 8.89876e-06 | 8.43848e-07 | 1(Win) |
| simdjson (ondemand) | 2160.99 | 0.120285 | 959.965ms | 5092 | 1280 | 9351.95 | 2247.17 | 2.3816 | 10.4179 | 1.5542 | 0.000638563 | 1.64167e-05 | 2.14798e-06 | 2(Loss) |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4909.19 | 0.0656935 | 965.628ms | 11724 | 4890 | 10946.7 | 2277.54 | 1.04793 | 4.95966 | 0.797936 | 0.000494206 | 8.00623e-06 | 1.16867e-06 | 1(Win) |
| simdjson (ondemand) | 4219.15 | 0.054034 | 998.882ms | 11724 | 4890 | 10026.4 | 2650.03 | 1.21636 | 5.32728 | 0.725179 | 0.000505823 | 1.26809e-05 | 3.36645e-06 | 2(Loss) |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 5015.08 | 0.0737145 | 959.873ms | 11724 | 4890 | 13207.2 | 2229.45 | 1.02621 | 4.91053 | 0.787104 | 0.000376153 | 8.14577e-06 | 1.46519e-06 | 1(Win) |
| simdjson (ondemand) | 4371.49 | 0.0866105 | 992.65ms | 11724 | 320 | 1570.31 | 2557.68 | 1.17629 | 5.25682 | 0.710082 | 0.000458195 | 5.0644e-06 | 7.99642e-07 | 2(Loss) |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1431.94 | 0.0941024 | 1067.73ms | 4857 | 2560 | 23720.8 | 3234.77 | 3.57695 | 14.1723 | 2.61581 | 0.00080771 | 6.78788e-05 | 2.64599e-05 | 1(Win) |
| simdjson (ondemand) | 1409.83 | 0.207948 | 1071.22ms | 4857 | 320 | 14937 | 3285.5 | 3.62103 | 14.0296 | 2.55631 | 0.000465179 | 2.18756e-05 | 5.79061e-06 | 2(Loss) |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1793.18 | 0.0688204 | 1026.44ms | 4857 | 4890 | 15453.7 | 2583.12 | 2.85962 | 11.358 | 1.99815 | 0.00169801 | 3.89041e-05 | 1.72205e-05 | 1(Win) |
| simdjson (ondemand) | 1740.28 | 0.100376 | 1029.71ms | 4857 | 2560 | 18272.4 | 2661.63 | 2.94412 | 11.7437 | 2.06547 | 0.000545363 | 5.23568e-05 | 2.38863e-05 | 2(Loss) |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2067.25 | 0.132065 | 1086.57ms | 7376 | 640 | 12924.4 | 3402.73 | 2.47527 | 9.70363 | 1.70702 | 0.00038194 | 2.7115e-05 | 7.41425e-06 | 1(Win) |
| jsonifier (generic) | 2034.92 | 0.102877 | 1089.67ms | 7376 | 4890 | 61842.8 | 3456.8 | 2.51219 | 10 | 1.7599 | 0.000652811 | 9.21853e-05 | 5.27605e-05 | 2(Loss) |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2606.85 | 0.195917 | 1036.45ms | 7376 | 640 | 17886.9 | 2698.4 | 1.97171 | 8.06345 | 1.33663 | 0.00117844 | 4.93577e-05 | 2.64795e-05 | 1(Win) |
| simdjson (ondemand) | 2533.43 | 0.145573 | 1045.5ms | 7376 | 80 | 1307 | 2776.59 | 2.02639 | 8.19835 | 1.38381 | 0.000411809 | 2.20309e-05 | 1.01681e-05 | 2(Loss) |

----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 546.908 | 0.0646766 | 1597.36ms | 4857 | 4890 | 146727 | 8469.42 | 9.2752 | 37.7908 | 7.6644 | 0.00748246 | 0.000326811 | 0.000227235 | 1(Win) |
| simdjson (ondemand) | 156.131 | 0.0573777 | 3743.26ms | 4857 | 640 | 185448 | 29667.3 | 32.4052 | 142.877 | 27.1355 | 0.0641809 | 5.88712e-05 | 1.41548e-05 | 2(Loss) |

----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 615.71 | 0.0557485 | 1525.94ms | 4857 | 4890 | 86012.1 | 7523.01 | 8.25845 | 34.9234 | 7.03727 | 0.00750798 | 6.66506e-05 | 3.41042e-05 | 1(Win) |
| simdjson (ondemand) | 158.226 | 0.034286 | 3701.38ms | 4857 | 2560 | 257902 | 29274.5 | 31.9752 | 140.602 | 26.6494 | 0.0643155 | 7.16588e-05 | 2.2519e-05 | 2(Loss) |

----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 827.842 | 0.17307 | 1597.64ms | 7376 | 640 | 138411 | 8497.16 | 6.13833 | 25.5008 | 5.0743 | 0.00437928 | 3.15635e-05 | 1.08036e-05 | 1(Win) |
| simdjson (ondemand) | 236.467 | 0.0245267 | 3721.18ms | 7376 | 4890 | 260310 | 29747.5 | 21.4265 | 94.2332 | 17.8167 | 0.03899 | 9.90888e-05 | 4.79364e-05 | 2(Loss) |

----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 921.692 | 0.0916335 | 1536.11ms | 7376 | 1280 | 62602.1 | 7631.94 | 5.53092 | 23.5775 | 4.65415 | 0.00441264 | 1.73705e-05 | 5.82548e-06 | 1(Win) |
| simdjson (ondemand) | 241.668 | 0.0851852 | 3675.36ms | 7376 | 320 | 196735 | 29107.3 | 20.9352 | 92.7347 | 17.4966 | 0.0412054 | 2.66913e-05 | 4.66039e-06 | 2(Loss) |

----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 3598.41 | 0.211121 | 866.025ms | 4857 | 30 | 221.564 | 1287.23 | 1.44791 | 5.98147 | 0.87029 | 0.000247066 | 6.86295e-05 | 4.11777e-05 | 1(Win) |
| jsonifier (generic) | 3525.11 | 0.106415 | 865.356ms | 4857 | 4890 | 9561.04 | 1314 | 1.47727 | 6.23368 | 0.889438 | 0.000469122 | 2.22309e-05 | 7.53661e-06 | 2(Loss) |

----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 4025.11 | 0.106687 | 850.314ms | 4857 | 4890 | 7370.74 | 1150.77 | 1.311 | 5.44307 | 0.743875 | 0.000551983 | 2.36624e-05 | 7.62082e-06 | 1(Win) |
| jsonifier (generic) | 3945.32 | 0.225812 | 857.339ms | 4857 | 1280 | 8996.55 | 1174.05 | 1.32882 | 5.67449 | 0.759111 | 0.000992446 | 1.54416e-05 | 3.21701e-06 | 2(Loss) |

----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 5029.52 | 0.167463 | 875.564ms | 7376 | 1280 | 7021.65 | 1398.6 | 1.05076 | 4.39683 | 0.593682 | 0.000140023 | 2.00185e-05 | 1.04859e-05 | 1(Win) |
| jsonifier (generic) | 4820.28 | 0.430701 | 878.797ms | 7376 | 80 | 3160.37 | 1459.31 | 1.08512 | 4.68167 | 0.604664 | 0.000327074 | 1.86415e-05 | 3.38937e-06 | 2(Loss) |

----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 5510.61 | 0.121709 | 865.886ms | 7376 | 2560 | 6179.18 | 1276.5 | 0.946574 | 4.0423 | 0.510439 | 0.000381198 | 8.52639e-06 | 1.27101e-06 | 1(Win) |
| jsonifier (generic) | 5390.15 | 0.18265 | 872.516ms | 7376 | 320 | 1818.15 | 1305.03 | 0.969667 | 4.31345 | 0.518845 | 0.000586361 | 1.86415e-05 | 7.20241e-06 | 2(Loss) |

----
### Discord Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2035.64 | 0.108278 | 963.917ms | 4857 | 2560 | 15540 | 2275.45 | 2.54933 | 11.139 | 2.25015 | 0.0012379 | 3.51458e-05 | 1.87391e-05 | 1(Win) |
| simdjson (ondemand) | 1984.54 | 0.139488 | 969.811ms | 4857 | 640 | 6783.71 | 2334.04 | 2.6002 | 11.2269 | 1.8845 | 0.000517938 | 2.34841e-05 | 1.12595e-05 | 2(Loss) |

----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2158.62 | 0.0787439 | 956.066ms | 4857 | 4890 | 13961.3 | 2145.81 | 2.40191 | 10.5981 | 2.12683 | 0.00227728 | 4.18934e-05 | 2.38308e-05 | 1(Win) |
| simdjson (ondemand) | 2072.26 | 0.286829 | 959.789ms | 4857 | 160 | 6576.84 | 2235.24 | 2.48077 | 10.7037 | 1.76591 | 0.00154416 | 1.67284e-05 | 2.57361e-06 | 2(Loss) |

----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2912.03 | 0.141047 | 982.036ms | 7376 | 1280 | 14858.9 | 2415.6 | 1.76396 | 7.88476 | 1.49132 | 0.00092085 | 1.08036e-05 | 3.81304e-06 | 1(Win) |
| simdjson (ondemand) | 2876.04 | 0.100074 | 986.601ms | 7376 | 40 | 239.635 | 2445.82 | 1.78637 | 7.79108 | 1.24824 | 0.00080667 | 0 | 0 | 2(Loss) |

----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3073.17 | 0.153105 | 975.711ms | 7376 | 160 | 1965.03 | 2288.94 | 1.67465 | 7.52861 | 1.41011 | 0.00157521 | 9.32077e-06 | 0 | 1(Win) |
| simdjson (ondemand) | 2934.28 | 0.0861733 | 981.736ms | 7376 | 2560 | 10925.1 | 2397.29 | 1.73969 | 7.44658 | 1.17015 | 0.00121678 | 1.09625e-05 | 1.95948e-06 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1288.48 | 0.0717928 | 1067.33ms | 4390 | 4890 | 26609.8 | 3249.27 | 3.97236 | 17.7998 | 3.15376 | 0.00130581 | 4.72817e-05 | 1.70028e-05 | 1(Win) |
| simdjson (ondemand) | 1080.29 | 0.0548912 | 1127.87ms | 4390 | 4890 | 22129 | 3875.46 | 4.72663 | 18.9052 | 3.5615 | 0.000821769 | 6.61012e-05 | 2.54809e-05 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1402.54 | 0.10157 | 1064.17ms | 4390 | 2560 | 23532.4 | 2985.03 | 3.65371 | 16.374 | 2.83417 | 0.0016126 | 3.95964e-05 | 7.20743e-06 | 1(Win) |
| simdjson (ondemand) | 1190.52 | 0.0683047 | 1114.76ms | 4390 | 2560 | 14770.6 | 3516.65 | 4.2949 | 17.3554 | 3.21868 | 0.000783475 | 3.45245e-05 | 9.60991e-06 | 2(Loss) |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2986.67 | 0.0648463 | 1109.79ms | 11521 | 4890 | 27828.3 | 3678.77 | 1.71129 | 7.81877 | 1.26326 | 0.000908646 | 2.40869e-05 | 9.58506e-06 | 1(Win) |
| simdjson (ondemand) | 2580.86 | 0.0576314 | 1166.13ms | 11521 | 2560 | 15410.2 | 4257.21 | 1.97784 | 8.00339 | 1.39597 | 0.00031844 | 2.77347e-05 | 1.00021e-05 | 2(Loss) |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3210.92 | 0.0880552 | 1107.15ms | 11521 | 2560 | 23241.9 | 3421.85 | 1.59294 | 7.25354 | 1.13714 | 0.00131011 | 2.38356e-05 | 7.39139e-06 | 1(Win) |
| simdjson (ondemand) | 2829.1 | 0.0429944 | 1153.87ms | 11521 | 4890 | 13633.8 | 3883.67 | 1.80563 | 7.41281 | 1.26534 | 0.000371847 | 2.40159e-05 | 7.7923e-06 | 2(Loss) |

----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 625.719 | 0.113441 | 1414.33ms | 4390 | 640 | 36871.7 | 6690.91 | 8.12837 | 34.1925 | 7.43895 | 0.01168 | 6.79812e-05 | 3.34567e-05 | 1(Win) |
| simdjson (ondemand) | 608.138 | 0.146563 | 1436.45ms | 4390 | 320 | 32578 | 6884.34 | 8.35684 | 35.7173 | 6.38383 | 0.00798121 | 2.91856e-05 | 9.25399e-06 | 2(Loss) |

----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 659.005 | 0.090839 | 1404.24ms | 4390 | 1280 | 42629.1 | 6352.95 | 7.71757 | 32.7089 | 7.10775 | 0.0115896 | 3.86176e-05 | 1.24573e-05 | 1(Win) |
| simdjson (ondemand) | 641.814 | 0.0574127 | 1417.29ms | 4390 | 2560 | 35906 | 6523.12 | 7.88195 | 34.1672 | 6.04078 | 0.0071592 | 2.94526e-05 | 8.45316e-06 | 2(Loss) |

----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1552.53 | 0.0797134 | 1451.83ms | 11521 | 2560 | 81471.2 | 7077.03 | 3.25896 | 13.9791 | 2.87267 | 0.00481254 | 3.24814e-05 | 1.46811e-05 | 1(Win) |
| simdjson (ondemand) | 1526.98 | 0.0459403 | 1464.93ms | 11521 | 4890 | 53433.2 | 7195.44 | 3.31885 | 14.2752 | 2.44137 | 0.00302591 | 2.95007e-05 | 1.20168e-05 | 2(Loss) |

----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1635.23 | 0.0734046 | 1440.87ms | 11521 | 2560 | 62274.5 | 6719.12 | 3.10845 | 13.4138 | 2.74646 | 0.00483173 | 1.84785e-05 | 5.89955e-06 | 1(Win) |
| simdjson (ondemand) | 1599.07 | 0.042436 | 1452.87ms | 11521 | 4890 | 41574.3 | 6871.06 | 3.15761 | 13.7065 | 2.31499 | 0.00301013 | 1.87264e-05 | 5.04103e-06 | 2(Loss) |

----
### Google Maps Response Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) STATISTICAL TIE | 2053.58 | 0.145243 | 953.645ms | 4390 | 640 | 5611.46 | 2038.7 | 2.50567 | 11.18 | 1.99226 | 0.00283208 | 3.95074e-05 | 2.06435e-05 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2050.22 | 0.160222 | 942.858ms | 4390 | 160 | 1712.74 | 2042.04 | 2.51937 | 10.6267 | 1.80433 | 0.00130268 | 1.13895e-05 | 0 | 1(Tie) |

----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) STATISTICAL TIE | 2171.92 | 0.189061 | 937.34ms | 4390 | 1280 | 17000.2 | 1927.61 | 2.37258 | 10.8287 | 1.91093 | 0.0021512 | 2.34909e-05 | 1.08556e-05 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2159.65 | 0.32478 | 932.575ms | 4390 | 320 | 12685 | 1938.57 | 2.39068 | 10.274 | 1.72301 | 0.00126353 | 2.84738e-05 | 1.42369e-06 | 1(Tie) |

----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 4630.98 | 0.180744 | 984.759ms | 11521 | 640 | 11769 | 2372.56 | 1.11094 | 4.84784 | 0.726152 | 0.00053218 | 9.76478e-06 | 0 | 1(Win) |
| jsonifier (generic) | 4546.64 | 0.165344 | 981.838ms | 11521 | 1280 | 20435.5 | 2416.57 | 1.12372 | 5.19642 | 0.804705 | 0.00113271 | 1.19347e-05 | 2.37338e-06 | 2(Loss) |

----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 4855.55 | 0.14001 | 969.603ms | 11521 | 160 | 1605.98 | 2262.83 | 1.06036 | 4.71348 | 0.695165 | 0.000515363 | 4.88239e-06 | 0 | 1(Win) |
| jsonifier (generic) | 4799.13 | 0.141817 | 975.458ms | 11521 | 30 | 316.254 | 2289.43 | 1.07347 | 5.06258 | 0.773718 | 0.00109076 | 3.76125e-05 | 2.02529e-05 | 2(Loss) |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) STATISTICAL TIE | 1581.64 | 0.080863 | 1004.89ms | 4390 | 4890 | 22404 | 2647.03 | 3.2279 | 14.7458 | 2.68929 | 0.00406795 | 2.99062e-05 | 1.17389e-05 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1579.97 | 0.111579 | 1008.98ms | 4390 | 320 | 2797.36 | 2649.82 | 3.24968 | 13.9875 | 2.37677 | 0.00432873 | 1.56606e-05 | 0 | 1(Tie) |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 1651.31 | 0.198981 | 999.485ms | 4390 | 320 | 8144.08 | 2535.33 | 3.11444 | 13.6383 | 2.29544 | 0.00360194 | 1.92198e-05 | 0 | 1(Tie) |
| jsonifier (generic) STATISTICAL TIE | 1648.63 | 0.148198 | 1025.56ms | 4390 | 640 | 9064.58 | 2539.46 | 3.11587 | 14.3945 | 2.60797 | 0.00411304 | 9.60991e-06 | 3.55923e-07 | 1(Tie) |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 3773.84 | 0.116013 | 1027.2ms | 11521 | 30 | 342.254 | 2911.43 | 1.35831 | 6.1065 | 0.939936 | 0.00134537 | 5.78653e-06 | 0 | 1(Win) |
| jsonifier (generic) | 3668.12 | 0.056254 | 1039.92ms | 11521 | 4890 | 13883.8 | 2995.34 | 1.39666 | 6.55516 | 1.07031 | 0.0017211 | 1.29221e-05 | 3.05302e-06 | 2(Loss) |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) STATISTICAL TIE | 3824.56 | 0.188053 | 1073.43ms | 11521 | 640 | 18679.2 | 2872.82 | 1.36888 | 6.42132 | 1.03932 | 0.00197832 | 1.32909e-05 | 5.5605e-06 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3823.21 | 0.11034 | 1025.23ms | 11521 | 320 | 3217.69 | 2873.84 | 1.34177 | 5.9954 | 0.913289 | 0.00162936 | 7.59483e-06 | 0 | 1(Tie) |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1475.09 | 0.160203 | 1041.15ms | 4669 | 320 | 7483.47 | 3018.6 | 3.47411 | 14.8657 | 2.51017 | 0.000886164 | 4.28357e-05 | 1.47248e-05 | 1(Win) |
| jsonifier (generic) | 1456.3 | 0.0627896 | 1045.6ms | 4669 | 4890 | 18023.2 | 3057.55 | 3.51625 | 14.2465 | 2.58771 | 0.00164602 | 5.96985e-05 | 2.93455e-05 | 2(Loss) |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1597.8 | 0.0467315 | 1017.44ms | 4669 | 4890 | 8293.37 | 2786.77 | 3.212 | 13.4427 | 2.40437 | 0.00161803 | 7.25317e-05 | 3.97698e-05 | 1(Win) |
| simdjson (ondemand) | 1585.16 | 0.0643222 | 1022.6ms | 4669 | 4890 | 15963.7 | 2809 | 3.23223 | 14.1452 | 2.34633 | 0.000879709 | 4.53761e-05 | 2.61482e-05 | 2(Loss) |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2712.85 | 0.0600749 | 1063.89ms | 9249 | 4890 | 18656.7 | 3251.39 | 1.88582 | 8.13439 | 1.29528 | 0.00101078 | 1.53225e-05 | 6.1688e-06 | 1(Win) |
| jsonifier (generic) | 2647.84 | 0.0984847 | 1073.62ms | 9249 | 2560 | 27553.9 | 3331.22 | 1.93175 | 8.04876 | 1.35799 | 0.000870702 | 2.64809e-05 | 1.19945e-05 | 2(Loss) |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2908.72 | 0.0797708 | 1043.85ms | 9249 | 2560 | 14980 | 3032.44 | 1.7603 | 7.77068 | 1.21256 | 0.000783024 | 1.86253e-05 | 7.60217e-06 | 1(Win) |
| jsonifier (generic) | 2857.51 | 0.0836798 | 1052.3ms | 9249 | 2560 | 17080.4 | 3086.79 | 1.7924 | 7.65272 | 1.26792 | 0.00111004 | 2.00613e-05 | 9.03814e-06 | 2(Loss) |

----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 425.078 | 0.0475194 | 1787.4ms | 4669 | 4890 | 121161 | 10475 | 11.9551 | 51.9732 | 10.9055 | 0.00994582 | 0.000165605 | 8.23865e-05 | 1(Win) |
| simdjson (ondemand) | 196.586 | 0.0578512 | 3010.25ms | 4669 | 1280 | 219774 | 22650.1 | 25.8221 | 122.987 | 24.4162 | 0.0378751 | 0.000157287 | 9.88903e-05 | 2(Loss) |

----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 438.204 | 0.0884935 | 1764.95ms | 4669 | 1280 | 103497 | 10161.3 | 11.5759 | 51.1953 | 10.7278 | 0.00978345 | 4.91942e-05 | 2.30911e-05 | 1(Win) |
| simdjson (ondemand) | 198.502 | 0.0263672 | 2993.61ms | 4669 | 4890 | 171063 | 22431.6 | 25.5032 | 122.267 | 24.2529 | 0.0378772 | 3.90252e-05 | 1.26142e-05 | 2(Loss) |

----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 815.654 | 0.119146 | 1823.78ms | 9249 | 640 | 106248 | 10814.1 | 6.21623 | 27.0733 | 5.55111 | 0.00516272 | 2.1624e-05 | 7.60217e-06 | 1(Win) |
| simdjson (ondemand) | 389.802 | 0.0367649 | 3002.86ms | 9249 | 2560 | 177177 | 22628.2 | 12.9945 | 62.0056 | 12.1888 | 0.0212912 | 4.15163e-05 | 2.11594e-05 | 2(Loss) |

----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 838.852 | 0.0763368 | 1798.72ms | 9249 | 1280 | 82470.2 | 10515 | 6.04897 | 26.6805 | 5.46135 | 0.00489952 | 2.56785e-05 | 6.75749e-06 | 1(Win) |
| simdjson (ondemand) | 393.967 | 0.0496058 | 2987.01ms | 9249 | 1280 | 157887 | 22389 | 12.8507 | 61.642 | 12.1064 | 0.0216541 | 2.66076e-05 | 1.19101e-05 | 2(Loss) |

----
### Instruments Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 3885.79 | 0.100709 | 843.74ms | 4669 | 4890 | 6512.34 | 1145.9 | 1.3606 | 5.86807 | 0.762048 | 0.000884439 | 1.27456e-05 | 4.11714e-06 | 1(Win) |
| jsonifier (generic) | 3781.1 | 0.108294 | 847.102ms | 4669 | 4890 | 7952.92 | 1177.62 | 1.39698 | 6.33904 | 0.786464 | 0.000866088 | 1.37968e-05 | 4.02954e-06 | 2(Loss) |

----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4110.13 | 0.225827 | 837.037ms | 4669 | 40 | 239.413 | 1083.35 | 1.29924 | 6.08524 | 0.727351 | 0.000894196 | 3.21268e-05 | 0 | 1(Win) |
| simdjson (ondemand) | 4090.25 | 0.0779628 | 835.843ms | 4669 | 4890 | 3522.34 | 1088.61 | 1.29669 | 5.61662 | 0.702934 | 0.001246 | 9.59205e-06 | 2.23376e-06 | 2(Loss) |

----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 6603.72 | 0.144699 | 861.573ms | 9249 | 2560 | 9562.8 | 1335.69 | 0.799832 | 3.58071 | 0.409342 | 0.000447388 | 6.0395e-06 | 8.8692e-07 | 1(Win) |
| jsonifier (generic) | 6320.13 | 0.123513 | 874.863ms | 9249 | 40 | 118.856 | 1395.62 | 0.823067 | 3.91729 | 0.423613 | 0.000540599 | 2.97329e-05 | 2.1624e-05 | 2(Loss) |

----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 6828.32 | 0.108307 | 863.152ms | 9249 | 2560 | 5010.85 | 1291.76 | 0.764458 | 3.45378 | 0.379501 | 0.000499125 | 5.61716e-06 | 4.64577e-07 | 1(Win) |
| jsonifier (generic) | 6716.57 | 0.418456 | 863.586ms | 9249 | 320 | 9663.7 | 1313.25 | 0.780237 | 3.78917 | 0.393772 | 0.000498027 | 9.12261e-06 | 2.70299e-06 | 2(Loss) |

----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2177.62 | 0.31234 | 937.252ms | 4669 | 320 | 13052.3 | 2044.75 | 2.36446 | 10.8556 | 2.07025 | 0.00228033 | 1.87406e-05 | 1.33862e-05 | 1(Win) |
| simdjson (ondemand) | 2049.97 | 0.0735242 | 952.012ms | 4669 | 2560 | 6529.11 | 2172.09 | 2.50992 | 11.1743 | 1.73528 | 0.00301356 | 1.14619e-05 | 9.20299e-07 | 2(Loss) |

----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2275.42 | 0.0710373 | 931.478ms | 4669 | 4890 | 9449.43 | 1956.87 | 2.2719 | 10.6018 | 2.01114 | 0.0020269 | 1.82643e-05 | 6.83269e-06 | 1(Win) |
| simdjson (ondemand) | 2125.52 | 0.0587777 | 946.495ms | 4669 | 4890 | 7413.98 | 2094.88 | 2.42549 | 10.9229 | 1.67616 | 0.00318206 | 1.0906e-05 | 1.35778e-06 | 2(Loss) |

----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3912.42 | 0.0790446 | 959.26ms | 9249 | 2560 | 8129.86 | 2254.49 | 1.3141 | 6.19397 | 1.07071 | 0.00114873 | 7.2643e-06 | 8.44686e-07 | 1(Win) |
| simdjson (ondemand) | 3757.92 | 0.0565717 | 970.355ms | 9249 | 4890 | 8621.86 | 2347.18 | 1.36775 | 6.24651 | 0.896962 | 0.00116365 | 7.51753e-06 | 8.40195e-07 | 2(Loss) |

----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4070.64 | 0.0621721 | 946.515ms | 9249 | 4890 | 8874.92 | 2166.87 | 1.26538 | 6.06585 | 1.04087 | 0.00100461 | 7.47331e-06 | 5.7487e-07 | 1(Win) |
| simdjson (ondemand) | 3863.67 | 0.0571078 | 964.821ms | 9249 | 4890 | 8311.67 | 2282.94 | 1.33162 | 6.11958 | 0.867121 | 0.00127256 | 6.21302e-06 | 6.41201e-07 | 2(Loss) |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 576.164 | 0.0686131 | 1505.29ms | 4604 | 2560 | 69989.4 | 7620.6 | 8.81975 | 36.6188 | 7.28172 | 0.0104183 | 8.74749e-05 | 3.97922e-05 | 1(Win) |
| simdjson (ondemand) | 572.527 | 0.0652394 | 1508.55ms | 4604 | 2560 | 64082.4 | 7669.01 | 8.87678 | 36.2402 | 6.79648 | 0.0108867 | 9.19717e-05 | 3.94528e-05 | 2(Loss) |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 664.914 | 0.0580453 | 1497.63ms | 4604 | 4890 | 71842.7 | 6603.43 | 7.65316 | 32.11 | 6.25597 | 0.0096429 | 5.80983e-05 | 1.9677e-05 | 1(Win) |
| simdjson (ondemand) | 654.446 | 0.0467788 | 1511.74ms | 4604 | 4890 | 48164.7 | 6709.06 | 7.77181 | 31.9583 | 5.81885 | 0.0095363 | 6.09855e-05 | 1.88331e-05 | 2(Loss) |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2734.12 | 0.123065 | 1610.95ms | 24579 | 320 | 35621.5 | 8573.27 | 1.87717 | 7.81903 | 1.31836 | 0.00188741 | 1.05527e-05 | 4.9585e-06 | 1(Win) |
| jsonifier (generic) | 2705.75 | 0.0770632 | 1611.32ms | 24579 | 2560 | 114101 | 8663.18 | 1.87631 | 7.92392 | 1.41092 | 0.00197828 | 2.01995e-05 | 1.01554e-05 | 2(Loss) |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3066.85 | 0.0538441 | 1604.15ms | 24579 | 4890 | 82819 | 7643.15 | 1.65808 | 7.08235 | 1.21942 | 0.001773 | 8.02887e-06 | 1.80545e-06 | 1(Win) |
| simdjson (ondemand) | 3050.71 | 0.0853073 | 1609.91ms | 24579 | 1280 | 54993.2 | 7683.57 | 1.66584 | 7.01099 | 1.13398 | 0.0015132 | 6.29348e-06 | 7.62846e-07 | 2(Loss) |

----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 208.458 | 0.0593938 | 2851.39ms | 4604 | 1280 | 200320 | 21062.8 | 24.2838 | 101.891 | 23.5745 | 0.0341681 | 7.9245e-05 | 2.42656e-05 | 1(Win) |
| simdjson (ondemand) | 157.511 | 0.031829 | 3532.82ms | 4604 | 2560 | 201527 | 27875.6 | 32.1443 | 137.261 | 24.7767 | 0.046489 | 0.00019387 | 9.68078e-05 | 2(Loss) |

----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 217.557 | 0.0424527 | 2865.06ms | 4604 | 2560 | 187921 | 20181.9 | 23.2765 | 97.5219 | 22.5747 | 0.0340368 | 6.94878e-05 | 2.38414e-05 | 1(Win) |
| simdjson (ondemand) | 164.445 | 0.105923 | 3546.52ms | 4604 | 320 | 255954 | 26700.2 | 31.1451 | 132.953 | 23.7882 | 0.0443263 | 0.000131679 | 7.80571e-05 | 2(Loss) |

----
### Marine IK Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1065.65 | 0.131025 | 2959.88ms | 24579 | 320 | 265803 | 21996.3 | 4.74831 | 20.1651 | 4.46554 | 0.00628827 | 1.30955e-05 | 3.68709e-06 | 1(Win) |
| simdjson (ondemand) | 812.553 | 0.030072 | 3629.55ms | 24579 | 2560 | 192659 | 28847.8 | 6.22653 | 26.7245 | 4.68209 | 0.00861347 | 2.42363e-05 | 1.12997e-05 | 2(Loss) |

----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1103.35 | 0.0335263 | 2967.84ms | 24579 | 4890 | 248073 | 21244.7 | 4.58771 | 19.3596 | 4.28069 | 0.00625311 | 1.36283e-05 | 5.28324e-06 | 1(Win) |
| simdjson (ondemand) | 839.309 | 0.0274039 | 3639.54ms | 24579 | 2560 | 149951 | 27928.2 | 6.03031 | 25.9073 | 4.4949 | 0.00852373 | 2.48243e-05 | 1.11089e-05 | 2(Loss) |

----
### Marine IK Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3282.51 | 0.0992343 | 868.158ms | 4604 | 4890 | 8615.74 | 1337.61 | 1.5909 | 6.99609 | 1.28258 | 0.00174735 | 1.89219e-05 | 6.48498e-06 | 1(Win) |
| simdjson (ondemand) | 2957.26 | 0.10914 | 880.47ms | 4604 | 2560 | 6721.95 | 1484.72 | 1.75654 | 8.10882 | 1.05647 | 0.00150277 | 1.55266e-05 | 4.49677e-06 | 2(Loss) |

----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3342.63 | 0.0728214 | 866.762ms | 4604 | 4890 | 4474.25 | 1313.55 | 1.55854 | 6.91594 | 1.2639 | 0.00174375 | 1.10156e-05 | 1.77671e-06 | 1(Win) |
| simdjson (ondemand) | 3003.01 | 0.0820538 | 879.628ms | 4604 | 4890 | 7038.22 | 1462.1 | 1.73541 | 8.02932 | 1.03779 | 0.00165611 | 8.08402e-06 | 8.88354e-07 | 2(Loss) |

----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 10559.2 | 0.0991065 | 959.856ms | 24579 | 1280 | 6195.57 | 2219.9 | 0.487941 | 2.33138 | 0.27849 | 0.000401289 | 5.43528e-06 | 9.53558e-08 | 1(Win) |
| simdjson (ondemand) | 9703.5 | 0.0694399 | 972.427ms | 24579 | 2560 | 7203.28 | 2415.66 | 0.53046 | 2.551 | 0.243582 | 0.000325783 | 5.22868e-06 | 2.86067e-07 | 2(Loss) |

----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 10784.5 | 0.106034 | 955.346ms | 24579 | 1280 | 6798.8 | 2173.52 | 0.479181 | 2.31637 | 0.274991 | 0.000325004 | 5.40349e-06 | 1.90712e-07 | 1(Win) |
| simdjson (ondemand) | 9803.72 | 0.119788 | 968.592ms | 24579 | 1280 | 10499.9 | 2390.97 | 0.524971 | 2.53611 | 0.240083 | 0.000316104 | 5.46707e-06 | 3.81423e-07 | 2(Loss) |

----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1563.05 | 0.151032 | 1003.58ms | 4604 | 640 | 11519.7 | 2809.07 | 3.30313 | 14.2324 | 3.45048 | 0.00464134 | 6.4482e-06 | 0 | 1(Win) |
| simdjson (ondemand) | 1353.74 | 0.0904923 | 1057.97ms | 4604 | 1280 | 11026.4 | 3243.4 | 3.7934 | 17.4474 | 2.72024 | 0.00406389 | 1.5272e-05 | 1.5272e-06 | 2(Loss) |

----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1588.72 | 0.0677203 | 1003.77ms | 4604 | 2560 | 8967.17 | 2763.69 | 3.28434 | 14.1523 | 3.4318 | 0.00461445 | 1.88355e-05 | 4.92099e-06 | 1(Win) |
| simdjson (ondemand) | 1352.85 | 0.0707691 | 1057.18ms | 4604 | 2560 | 13505.1 | 3245.53 | 3.80454 | 17.3679 | 2.70156 | 0.00416146 | 1.1454e-05 | 1.27267e-06 | 2(Loss) |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 6366.32 | 0.192695 | 1100.02ms | 24579 | 30 | 1510.13 | 3681.93 | 0.80329 | 3.6864 | 0.684405 | 0.000893717 | 6.78086e-06 | 0 | 1(Win) |
| simdjson (ondemand) | 5519.53 | 0.0610701 | 1153.38ms | 24579 | 2560 | 17219.5 | 4246.8 | 0.928073 | 4.30042 | 0.555352 | 0.000854579 | 5.88027e-06 | 7.62846e-07 | 2(Loss) |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 6412.14 | 0.0599369 | 1095.67ms | 24579 | 2560 | 12290 | 3655.62 | 0.801531 | 3.67139 | 0.680907 | 0.000887206 | 5.67367e-06 | 3.81423e-07 | 1(Win) |
| simdjson (ondemand) | 5591.22 | 0.0444843 | 1152.87ms | 24579 | 4890 | 17007.4 | 4192.36 | 0.918864 | 4.28553 | 0.551853 | 0.000783734 | 4.83396e-06 | 4.57604e-07 | 2(Loss) |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 737.921 | 0.197891 | 875.06ms | 1181 | 80 | 729.833 | 1526.3 | 7.02909 | 29.1101 | 5.1033 | 0.00429721 | 3.17528e-05 | 0 | 1(Tie) |
| jsonifier (generic) STATISTICAL TIE | 736.807 | 0.108242 | 879.032ms | 1181 | 2560 | 7008.49 | 1528.61 | 7.11849 | 29.9822 | 5.64522 | 0.00471925 | 8.53355e-05 | 3.50603e-05 | 1(Tie) |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 971.678 | 0.21633 | 853.649ms | 1181 | 1280 | 8048.24 | 1159.12 | 5.46777 | 22.8069 | 3.69179 | 0.00253757 | 8.4674e-05 | 2.38146e-05 | 1(Win) |
| jsonifier (generic) | 952.062 | 0.271746 | 861.346ms | 1181 | 40 | 413.385 | 1183 | 5.5982 | 23.5944 | 4.21253 | 0.00224386 | 0.000105843 | 0 | 2(Loss) |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1487.94 | 0.0893642 | 885.578ms | 2496 | 4890 | 9994.31 | 1599.77 | 3.5209 | 14.5397 | 2.45793 | 0.00172743 | 2.96589e-05 | 8.02921e-06 | 1(Win) |
| jsonifier (generic) | 1474.34 | 0.184209 | 888.402ms | 2496 | 30 | 265.361 | 1614.53 | 3.58309 | 15.3217 | 2.77364 | 0.00209669 | 0.000307158 | 8.01282e-05 | 2(Loss) |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 1948.82 | 0.245916 | 864.272ms | 2496 | 640 | 5774.31 | 1221.45 | 2.73077 | 11.4559 | 1.77003 | 0.00104041 | 1.1894e-05 | 0 | 1(Win) |
| jsonifier (generic) | 1844.05 | 0.157107 | 871.506ms | 2496 | 2560 | 10528.6 | 1290.84 | 2.86137 | 12.1979 | 2.07572 | 0.0014168 | 2.55096e-05 | 4.53851e-06 | 2(Loss) |

----
### Mesh Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 540.629 | 0.0837008 | 938.775ms | 1181 | 4890 | 14868.6 | 2083.3 | 9.69692 | 40.5504 | 8.58087 | 0.00664319 | 0.0001974 | 9.83534e-05 | 1(Win) |
| simdjson (ondemand) | 434.904 | 0.0761109 | 987.069ms | 1181 | 4890 | 18998.3 | 2589.74 | 11.8692 | 50.7909 | 8.93311 | 0.00636544 | 0.000130388 | 6.44146e-05 | 2(Loss) |

----
### Mesh Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 657.208 | 0.128143 | 918.98ms | 1181 | 80 | 385.81 | 1713.75 | 8.04525 | 34.1634 | 7.14818 | 0.00473116 | 7.40898e-05 | 0 | 1(Win) |
| simdjson (ondemand) | 504.67 | 0.18594 | 967.363ms | 1181 | 640 | 11020.7 | 2231.73 | 10.3891 | 44.4886 | 7.52159 | 0.00727138 | 7.14437e-05 | 1.98455e-05 | 2(Loss) |

----
### Mesh Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1089.08 | 0.0794998 | 947.22ms | 2496 | 4890 | 14764.3 | 2185.67 | 4.79806 | 20.2208 | 4.14263 | 0.00304536 | 0.000112409 | 5.16983e-05 | 1(Win) |
| simdjson (ondemand) | 895.651 | 0.197873 | 996.653ms | 2496 | 640 | 17699.6 | 2657.7 | 5.73423 | 24.6973 | 4.25013 | 0.00291654 | 1.6276e-05 | 1.878e-06 | 2(Loss) |

----
### Mesh Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1291.43 | 0.182715 | 928.219ms | 2496 | 1280 | 14518.1 | 1843.21 | 4.04362 | 17.1987 | 3.46474 | 0.00196252 | 4.78891e-05 | 1.565e-05 | 1(Win) |
| simdjson (ondemand) | 1045.23 | 0.116996 | 974.266ms | 2496 | 320 | 2271.73 | 2277.36 | 4.97927 | 21.7147 | 3.58213 | 0.00232372 | 2.37881e-05 | 2.50401e-06 | 2(Loss) |

----
### Mesh Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2409.28 | 0.353248 | 774.803ms | 1181 | 1280 | 3490.56 | 467.48 | 2.30811 | 8.73497 | 1.60881 | 0.000865262 | 2.44761e-05 | 4.63061e-06 | 1(Win) |
| simdjson (ondemand) | 2268.15 | 0.169367 | 781.181ms | 1181 | 30 | 21.2195 | 496.567 | 2.40446 | 9.56647 | 1.4039 | 0.00084674 | 0 | 0 | 2(Loss) |

----
### Mesh Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2724.87 | 0.201313 | 774.348ms | 1181 | 4890 | 3385.81 | 413.337 | 2.03589 | 7.89924 | 1.41406 | 0.00089609 | 9.69682e-05 | 3.93067e-05 | 1(Win) |
| simdjson (ondemand) | 2580.41 | 0.124772 | 775.057ms | 1181 | 4890 | 1450.31 | 436.476 | 2.14645 | 8.75868 | 1.21338 | 0.000865095 | 2.21642e-05 | 2.4242e-06 | 2(Loss) |

----
### Mesh Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4331.29 | 0.203044 | 787.799ms | 2496 | 80 | 99.6146 | 549.575 | 1.25273 | 4.89383 | 0.790465 | 0.000400641 | 3.50561e-05 | 0 | 1(Win) |
| simdjson (ondemand) | 4181.83 | 0.194723 | 788.37ms | 2496 | 4890 | 6007.59 | 569.218 | 1.29184 | 5.19431 | 0.688703 | 0.000414979 | 3.44928e-05 | 1.49114e-05 | 2(Loss) |

----
### Mesh Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4842.05 | 0.379853 | 778.788ms | 2496 | 1280 | 4463.46 | 491.604 | 1.13156 | 4.4984 | 0.698318 | 0.000419734 | 4.82021e-05 | 3.03611e-05 | 1(Win) |
| simdjson (ondemand) | 4661.37 | 0.20421 | 781.169ms | 2496 | 2560 | 2783.91 | 510.659 | 1.16935 | 4.8121 | 0.598558 | 0.00040831 | 2.09711e-05 | 2.19101e-06 | 2(Loss) |

----
### Mesh Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2048.14 | 0.203897 | 784.124ms | 1181 | 2560 | 3218.43 | 549.909 | 2.6418 | 10.2667 | 1.52159 | 0.000958205 | 3.07605e-05 | 9.26122e-06 | 1(Win) |
| jsonifier (generic) | 2022.25 | 0.278045 | 789.528ms | 1181 | 80 | 191.846 | 556.95 | 2.68087 | 9.38527 | 1.78493 | 0.00257197 | 2.11685e-05 | 0 | 2(Loss) |

----
### Mesh Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) STATISTICAL TIE | 2292.47 | 0.245174 | 784.097ms | 1181 | 30 | 43.5276 | 491.3 | 2.38978 | 8.54953 | 1.59018 | 0.00279424 | 5.64493e-05 | 0 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2283.51 | 0.290116 | 782.885ms | 1181 | 1280 | 2620.88 | 493.227 | 2.39429 | 9.45893 | 1.33108 | 0.000867909 | 6.94591e-05 | 3.24143e-05 | 1(Tie) |

----
### Mesh Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 3842.28 | 0.35141 | 793.463ms | 2496 | 1280 | 6066.66 | 619.521 | 1.39687 | 5.52564 | 0.744391 | 0.000418482 | 1.565e-05 | 4.38201e-06 | 1(Tie) |
| jsonifier (generic) STATISTICAL TIE | 3810.75 | 0.352146 | 792.815ms | 2496 | 640 | 3096.68 | 624.647 | 1.42611 | 5.20152 | 0.873798 | 0.000922726 | 1.0016e-05 | 2.50401e-06 | 1(Tie) |

----
### Mesh Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 4239.08 | 0.184603 | 789.178ms | 2496 | 4890 | 5254.55 | 561.531 | 1.27907 | 5.14353 | 0.654268 | 0.000423418 | 2.17116e-05 | 5.32549e-06 | 1(Win) |
| jsonifier (generic) | 4147.34 | 0.186343 | 790.294ms | 2496 | 4890 | 5593.51 | 573.951 | 1.31207 | 4.80609 | 0.781651 | 0.00115039 | 3.21168e-05 | 1.90079e-05 | 2(Loss) |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1232.28 | 0.069917 | 1124.05ms | 4926 | 2560 | 18187.6 | 3812.28 | 4.1464 | 16.8112 | 3.07836 | 0.00438791 | 7.84263e-05 | 2.45033e-05 | 1(Win) |
| simdjson (ondemand) | 1087.59 | 0.108879 | 1169.63ms | 4926 | 160 | 3538.9 | 4319.46 | 4.69386 | 17.9972 | 3.37718 | 0.00337495 | 6.09013e-05 | 2.66443e-05 | 2(Loss) |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1520.8 | 0.05844 | 1088.02ms | 4926 | 4890 | 15935.9 | 3089.04 | 3.36332 | 14.1098 | 2.48559 | 0.00391151 | 3.59928e-05 | 1.32015e-05 | 1(Win) |
| simdjson (ondemand) | 1308.67 | 0.0312724 | 1138.07ms | 4926 | 4890 | 6162.58 | 3589.76 | 3.90818 | 15.2978 | 2.78583 | 0.0036919 | 3.3502e-05 | 9.96341e-06 | 2(Loss) |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2247.68 | 0.115082 | 1146.32ms | 9463 | 1280 | 27328.4 | 4015.08 | 2.27624 | 9.42037 | 1.62612 | 0.00229776 | 5.00304e-05 | 2.5428e-05 | 1(Win) |
| simdjson (ondemand) | 1979.08 | 0.059303 | 1195.59ms | 9463 | 2560 | 18720.8 | 4560.01 | 2.57571 | 9.97105 | 1.78707 | 0.00157418 | 2.72855e-05 | 1.10215e-05 | 2(Loss) |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2758.85 | 0.143891 | 1109.38ms | 9463 | 80 | 1772.38 | 3271.15 | 1.86411 | 8.01416 | 1.31755 | 0.00206726 | 3.03815e-05 | 1.9814e-05 | 1(Win) |
| simdjson (ondemand) | 2367.96 | 0.100343 | 1159.29ms | 9463 | 1280 | 18719.6 | 3811.14 | 2.15682 | 8.56536 | 1.47902 | 0.00208658 | 1.44477e-05 | 2.72443e-06 | 2(Loss) |

----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 560.265 | 0.134158 | 1583.42ms | 4926 | 640 | 80987.3 | 8384.96 | 9.06233 | 38.8709 | 8.05502 | 0.00969219 | 2.09348e-05 | 9.51583e-07 | 1(Win) |
| simdjson (ondemand) | 395.626 | 0.0331542 | 1929.65ms | 4926 | 4890 | 75789.2 | 11874.4 | 12.7805 | 54.7578 | 10.3792 | 0.0145655 | 9.47354e-05 | 4.07254e-05 | 2(Loss) |

----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 612.017 | 0.131696 | 1559.63ms | 4926 | 40 | 4087.61 | 7675.93 | 8.30688 | 36.1807 | 7.46793 | 0.00980512 | 3.55258e-05 | 1.01502e-05 | 1(Win) |
| simdjson (ondemand) | 425.566 | 0.034906 | 1888.43ms | 4926 | 4890 | 72604.5 | 11039 | 11.8901 | 52.0696 | 9.79355 | 0.0124511 | 2.82712e-05 | 7.80467e-06 | 2(Loss) |

----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1059.92 | 0.165873 | 1599.28ms | 9463 | 30 | 5983.91 | 8514.43 | 4.79376 | 20.8861 | 4.20987 | 0.00533305 | 1.409e-05 | 0 | 1(Win) |
| simdjson (ondemand) | 753.267 | 0.0885486 | 1937.91ms | 9463 | 640 | 72028.3 | 11980.6 | 6.73046 | 28.9598 | 5.40051 | 0.00704438 | 3.20327e-05 | 1.30442e-05 | 2(Loss) |

----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1140.47 | 0.0976382 | 1571.15ms | 9463 | 1280 | 76407.5 | 7913.04 | 4.44098 | 19.4857 | 3.90426 | 0.00570379 | 1.94838e-05 | 3.46745e-06 | 1(Win) |
| simdjson (ondemand) | 808.118 | 0.0479542 | 1902.21ms | 9463 | 2560 | 73417.9 | 11167.5 | 6.26826 | 27.56 | 5.09543 | 0.00625987 | 1.92361e-05 | 5.57269e-06 | 2(Loss) |

----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2283.66 | 0.113793 | 946.454ms | 4926 | 2560 | 14028.1 | 2057.14 | 2.24486 | 9.8581 | 1.71843 | 0.00215962 | 2.42654e-05 | 1.03088e-05 | 1(Win) |
| simdjson (ondemand) | 2171.56 | 0.0603141 | 949.688ms | 4926 | 4890 | 8325.15 | 2163.33 | 2.36893 | 9.33435 | 1.59095 | 0.00311718 | 1.67717e-05 | 2.53237e-06 | 2(Loss) |

----
### Random Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2501.56 | 0.126653 | 934.714ms | 4926 | 2560 | 14482.2 | 1877.95 | 2.06442 | 9.26391 | 1.57268 | 0.00240322 | 1.95075e-05 | 3.88563e-06 | 1(Win) |
| simdjson (ondemand) | 2358.1 | 0.118454 | 945.42ms | 4926 | 2560 | 14256.2 | 1992.19 | 2.18688 | 8.74482 | 1.44519 | 0.00298163 | 1.2212e-05 | 2.45826e-06 | 2(Loss) |

----
### Random Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4026.61 | 0.0984567 | 961.631ms | 9463 | 2560 | 12465.5 | 2241.24 | 1.27781 | 5.80662 | 0.918314 | 0.00110608 | 9.90701e-06 | 1.48605e-06 | 1(Win) |
| simdjson (ondemand) | 3790.82 | 0.0599139 | 968.231ms | 9463 | 160 | 325.512 | 2380.65 | 1.3558 | 5.44257 | 0.855014 | 0.00169872 | 7.26514e-06 | 6.60467e-07 | 2(Loss) |

----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 4319.28 | 0.167527 | 955.836ms | 9463 | 1280 | 15682.5 | 2089.38 | 1.19292 | 5.49731 | 0.842439 | 0.00147317 | 9.16398e-06 | 1.56861e-06 | 1(Win) |
| simdjson (ondemand) | 4068.42 | 0.0929286 | 966.527ms | 9463 | 2560 | 10877.9 | 2218.21 | 1.2655 | 5.13569 | 0.77914 | 0.00173938 | 4.99478e-06 | 4.12792e-07 | 2(Loss) |

----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1520.06 | 0.110499 | 1045.83ms | 4926 | 2560 | 29855.1 | 3090.53 | 3.36594 | 15.552 | 2.86379 | 0.00288108 | 2.79924e-05 | 9.67443e-06 | 1(Win) |
| simdjson (ondemand) | 1449.17 | 0.0743832 | 1059.28ms | 4926 | 2560 | 14884.7 | 3241.72 | 3.53093 | 14.7203 | 2.56963 | 0.00512451 | 4.7262e-05 | 2.4424e-05 | 2(Loss) |

----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1619.93 | 0.109079 | 1038.09ms | 4926 | 2560 | 25616.5 | 2900 | 3.16401 | 14.9557 | 2.7162 | 0.00261749 | 1.94282e-05 | 4.20283e-06 | 1(Win) |
| simdjson (ondemand) | 1533.88 | 0.0661517 | 1049.88ms | 4926 | 4890 | 20072.3 | 3062.69 | 3.34517 | 14.1248 | 2.42306 | 0.00470945 | 3.27962e-05 | 1.71869e-05 | 2(Loss) |

----
### Random Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2764.29 | 0.180759 | 1063.89ms | 9463 | 1280 | 44575.9 | 3264.72 | 1.8589 | 8.77143 | 1.51495 | 0.00123144 | 9.49421e-06 | 1.40349e-06 | 1(Win) |
| simdjson (ondemand) | 2634.5 | 0.208925 | 1076.5ms | 9463 | 40 | 2048.82 | 3425.55 | 1.942 | 8.2532 | 1.36532 | 0.00243316 | 7.13304e-05 | 5.54792e-05 | 2(Loss) |

----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2910.89 | 0.101912 | 1057.58ms | 9463 | 2560 | 25556.4 | 3100.3 | 1.75908 | 8.46106 | 1.43813 | 0.0013824 | 1.35396e-05 | 4.08664e-06 | 1(Win) |
| simdjson (ondemand) | 2774.93 | 0.0578645 | 1075.2ms | 9463 | 4890 | 17317.6 | 3252.2 | 1.84465 | 7.94325 | 1.28902 | 0.00234892 | 2.3015e-05 | 1.2037e-05 | 2(Loss) |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2140.78 | 0.137569 | 863.196ms | 2821 | 4890 | 14615.3 | 1256.7 | 2.43708 | 8.93903 | 1.48139 | 0.000421104 | 6.5605e-05 | 4.09578e-05 | 1(Win) |
| jsonifier (generic) | 2130.57 | 0.198603 | 865.013ms | 2821 | 2560 | 16099.9 | 1262.72 | 2.45338 | 9.08898 | 1.51542 | 0.00043272 | 6.68812e-05 | 4.52798e-05 | 2(Loss) |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 2370.01 | 0.371441 | 858.744ms | 2821 | 640 | 11378 | 1135.15 | 2.21767 | 8.47678 | 1.36228 | 0.00039381 | 2.99096e-05 | 1.3847e-05 | 1(Win) |
| simdjson (ondemand) | 2298.18 | 0.111506 | 859.806ms | 2821 | 4890 | 8331.88 | 1170.63 | 2.27835 | 8.47678 | 1.36831 | 0.000406533 | 4.84969e-05 | 3.0809e-05 | 2(Loss) |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 3027.16 | 0.158976 | 859.203ms | 4147 | 4890 | 21094.4 | 1306.47 | 1.73602 | 6.43435 | 1.01255 | 0.000442333 | 4.59099e-05 | 2.80588e-05 | 1(Win) |
| jsonifier (generic) | 2974.73 | 0.213362 | 870.908ms | 4147 | 2560 | 20599.1 | 1329.5 | 1.78359 | 6.72679 | 1.05016 | 0.000377155 | 0.00010173 | 6.60304e-05 | 2(Loss) |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 3266.95 | 0.174125 | 859.54ms | 4147 | 80 | 355.463 | 1210.58 | 1.63055 | 6.16518 | 0.946467 | 0.000247167 | 1.80854e-05 | 6.02845e-06 | 1(Win) |
| jsonifier (generic) | 3244.5 | 0.149045 | 864.036ms | 4147 | 4890 | 16140.6 | 1218.95 | 1.62699 | 6.31035 | 0.945985 | 0.000326301 | 3.54557e-05 | 2.29796e-05 | 2(Loss) |

----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 740.503 | 0.0911923 | 1099.61ms | 2821 | 4890 | 53675.8 | 3633.09 | 6.90299 | 28.3481 | 5.36796 | 0.00180932 | 7.64787e-05 | 4.58147e-05 | 1(Win) |
| simdjson (ondemand) | 287.579 | 0.0537903 | 1675.2ms | 2821 | 2560 | 64824.5 | 9355.04 | 17.647 | 77.0625 | 15.6133 | 0.00628268 | 0.000158687 | 9.55446e-05 | 2(Loss) |

----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 764.481 | 0.104191 | 1096.84ms | 2821 | 4890 | 65742 | 3519.14 | 6.69251 | 27.7348 | 5.21376 | 0.00185144 | 8.04657e-05 | 4.364e-05 | 1(Win) |
| simdjson (ondemand) | 291.216 | 0.120762 | 1674.53ms | 2821 | 320 | 39827.8 | 9238.2 | 17.4206 | 76.5966 | 15.4981 | 0.00592764 | 7.9759e-05 | 4.98493e-05 | 2(Loss) |

----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1059.57 | 0.141572 | 1110.85ms | 4147 | 2560 | 71484 | 3732.56 | 4.82886 | 19.8066 | 3.66554 | 0.00185111 | 6.46175e-05 | 3.099e-05 | 1(Win) |
| simdjson (ondemand) | 424.284 | 0.0812614 | 1679.07ms | 4147 | 1280 | 73440.1 | 9321.31 | 11.9563 | 52.2428 | 10.5045 | 0.00683872 | 0.00011228 | 5.46329e-05 | 2(Loss) |

----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1096.1 | 0.127746 | 1106.02ms | 4147 | 2560 | 54387.1 | 3608.13 | 4.66509 | 19.387 | 3.55968 | 0.00145691 | 3.79604e-05 | 1.07382e-05 | 1(Win) |
| simdjson (ondemand) | 426.545 | 0.040255 | 1672.25ms | 4147 | 4890 | 68122 | 9271.92 | 11.8974 | 51.9308 | 10.428 | 0.0069864 | 7.40181e-05 | 3.10669e-05 | 2(Loss) |

----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 5188.47 | 0.148566 | 781.017ms | 2821 | 4890 | 2901.84 | 518.518 | 1.06636 | 4.20808 | 0.480326 | 0.000356949 | 3.76957e-05 | 2.33423e-05 | 1(Win) |
| jsonifier (generic) | 4619.67 | 0.206768 | 788.31ms | 2821 | 2560 | 3711.87 | 582.361 | 1.17105 | 4.67742 | 0.533854 | 0.000674766 | 3.07404e-05 | 1.67549e-05 | 2(Loss) |

----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 5330.7 | 0.157991 | 785.684ms | 2821 | 4890 | 3108.92 | 504.683 | 1.02543 | 4.13187 | 0.462248 | 0.000356152 | 1.21061e-05 | 3.98704e-06 | 1(Win) |
| jsonifier (generic) | 4882.05 | 0.161903 | 779.823ms | 2821 | 80 | 63.6796 | 551.062 | 1.13218 | 4.60227 | 0.515775 | 0.000651365 | 8.86211e-06 | 0 | 2(Loss) |

----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 6568.22 | 0.163119 | 789.07ms | 4147 | 80 | 77.1741 | 602.125 | 0.821968 | 3.26525 | 0.344586 | 0.000247167 | 1.80854e-05 | 0 | 1(Win) |
| jsonifier (generic) | 5921.29 | 0.274045 | 802.634ms | 4147 | 1280 | 4288.34 | 667.909 | 0.906567 | 3.7169 | 0.380757 | 0.000454206 | 1.07382e-05 | 3.39101e-06 | 2(Loss) |

----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 6754.29 | 0.194128 | 786.267ms | 4147 | 80 | 103.366 | 585.538 | 0.799943 | 3.21341 | 0.332288 | 0.000253195 | 6.02845e-06 | 0 | 1(Win) |
| jsonifier (generic) | 6029.59 | 0.242323 | 799.697ms | 4147 | 2560 | 6467.31 | 655.914 | 0.889059 | 3.66578 | 0.36846 | 0.000442432 | 2.33603e-05 | 1.36582e-05 | 2(Loss) |

----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 3119.84 | 0.147837 | 816.892ms | 2821 | 2560 | 4160.54 | 862.326 | 1.69635 | 7.09217 | 1.01879 | 0.000369716 | 2.17399e-05 | 9.13905e-06 | 1(Win) |
| jsonifier (generic) | 3041.18 | 0.176525 | 815.775ms | 2821 | 4890 | 11924.6 | 884.629 | 1.7535 | 7.55131 | 1.16202 | 0.000937462 | 3.63908e-05 | 2.1385e-05 | 2(Loss) |

----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 3176.19 | 0.143506 | 817.991ms | 2821 | 2560 | 3782.45 | 847.026 | 1.66698 | 7.01772 | 1.00106 | 0.000367362 | 1.56472e-05 | 3.18482e-06 | 1(Win) |
| jsonifier (generic) | 3103.88 | 0.145556 | 813.293ms | 2821 | 2560 | 4074.74 | 866.76 | 1.71834 | 7.47678 | 1.14428 | 0.000850901 | 1.10776e-05 | 1.24623e-06 | 2(Loss) |

----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) STATISTICAL TIE | 4126.32 | 0.310794 | 825.222ms | 4147 | 320 | 2839.46 | 958.453 | 1.30304 | 5.67398 | 0.808777 | 0.000582499 | 6.78201e-06 | 3.76778e-06 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 4118.39 | 0.388162 | 829.38ms | 4147 | 80 | 1111.55 | 960.3 | 1.27948 | 5.23559 | 0.712804 | 0.000560646 | 6.02845e-06 | 0 | 1(Tie) |

----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 4260.06 | 0.254478 | 827.307ms | 4147 | 640 | 3572.04 | 928.364 | 1.24201 | 5.18495 | 0.700748 | 0.000250558 | 6.78201e-06 | 2.63745e-06 | 1(Win) |
| jsonifier (generic) | 4112.21 | 0.113706 | 832.706ms | 4147 | 4890 | 5847.8 | 961.742 | 1.28123 | 5.62334 | 0.796721 | 0.000568179 | 9.12281e-06 | 2.46563e-06 | 2(Loss) |

----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3961.87 | 0.2091 | 7469.35ms | 277673 | 640 | 1.25014e+07 | 66839.6 | 1.27416 | 4.53744 | 0.701029 | 0.00460267 | 2.48719e-06 | 1.24922e-06 | 1(Win) |
| simdjson (ondemand) | 3689.07 | 0.0539201 | 4045.95ms | 277673 | 1280 | 1.91754e+06 | 71782.2 | 1.37028 | 4.67095 | 0.758367 | 0.00371083 | 1.98075e-06 | 7.70916e-07 | 2(Loss) |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3403.2 | 0.373054 | 4451.24ms | 10548466 | 30 | 3.64813e+09 | 2.95599e+06 | 1.4921 | 4.53778 | 0.701061 | 0.0103705 | 0.0174945 | 0.00305906 | 1(Win) |
| simdjson (ondemand) | 3230.58 | 0.255972 | 4687.51ms | 10548466 | 40 | 2.54134e+09 | 3.11393e+06 | 1.57402 | 4.67073 | 0.758763 | 0.00979032 | 0.0176789 | 0.00195123 | 2(Loss) |

----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 3636.79 | 0.0955959 | 6337.94ms | 16002592 | 80 | 1.2874e+09 | 4.19636e+06 | 1.38804 | 7.66238 | 1.03597 | 0.00074919 | 0.0374639 | 0.000640688 | 1(Win) |
| jsonifier (generic) | 3428.41 | 0.127666 | 6676.29ms | 16002592 | 30 | 9.68866e+08 | 4.45141e+06 | 1.44443 | 8.47236 | 1.01527 | 0.000833044 | 0.0336927 | 0.00186259 | 2(Loss) |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 3712.14 | 0.192302 | 6203.99ms | 16002591 | 40 | 2.50012e+09 | 4.11118e+06 | 1.3548 | 8.03323 | 1.36628 | 0.000847136 | 0.0369986 | 0.000380504 | 1(Win) |
| simdjson (ondemand) | 2048.51 | 0.113563 | 5220.74ms | 16002591 | 40 | 2.86311e+09 | 7.44993e+06 | 2.46381 | 11.8249 | 1.89574 | 0.000638643 | 0.0536613 | 0.00204218 | 2(Loss) |

----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 18218 | 0.118299 | 5404.91ms | 16197086 | 30 | 3.01827e+07 | 847884 | 0.27723 | 1.26957 | 0.0713027 | 8.66596e-05 | 0.0157312 | 5.4057e-05 | 1(Win) |
| jsonifier (generic) | 18031.2 | 0.167781 | 5440.9ms | 16197086 | 40 | 8.26363e+07 | 856666 | 0.275852 | 1.49245 | 0.0671122 | 7.76961e-05 | 0.0157207 | 4.99303e-05 | 2(Loss) |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 18207.9 | 0.0890421 | 5400.81ms | 16197085 | 320 | 1.82597e+08 | 848354 | 0.275797 | 1.48848 | 0.0728897 | 9.33526e-05 | 0.0157313 | 7.81292e-05 | 1(Win) |
| simdjson (ondemand) | 17211.6 | 0.13614 | 5742.04ms | 16197085 | 30 | 4.47839e+07 | 897460 | 0.293399 | 1.33855 | 0.0856353 | 9.16255e-05 | 0.0157677 | 3.35472e-05 | 2(Loss) |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1283.93 | 0.0884479 | 5341.85ms | 4525120 | 30 | 2.65137e+08 | 3.36115e+06 | 3.93361 | 16.216 | 2.61374 | 0.00891585 | 0.0776484 | 0.000257989 | 1(Win) |
| simdjson (ondemand) | 1262.37 | 0.126634 | 5442.45ms | 4525120 | 40 | 7.49623e+08 | 3.41855e+06 | 4.01057 | 15.6211 | 2.55198 | 0.012142 | 0.0774551 | 0.000497666 | 2(Loss) |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 553.691 | 0.13099 | 5600.68ms | 4525120 | 40 | 4.16931e+09 | 7.79404e+06 | 9.13063 | 41.1414 | 8.80731 | 0.0234277 | 0.0786199 | 0.0040249 | 1(Win) |
| simdjson (ondemand) | 408.471 | 0.0837803 | 7579.18ms | 4525120 | 40 | 3.13387e+09 | 1.0565e+07 | 12.3611 | 54.1335 | 9.53457 | 0.039182 | 0.0787821 | 0.00735496 | 2(Loss) |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1104.23 | 0.080337 | 6238.98ms | 4525119 | 30 | 2.95727e+08 | 3.90813e+06 | 4.5775 | 19.091 | 3.49358 | 0.0113765 | 0.078126 | 0.00116073 | 1(Win) |
| simdjson (ondemand) | 953.18 | 0.271253 | 7117.69ms | 4525119 | 80 | 1.20657e+10 | 4.52747e+06 | 5.29559 | 20.1666 | 3.4932 | 0.0149748 | 0.0946032 | 0.0002408 | 2(Loss) |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 558.279 | 0.135314 | 5622.94ms | 4525119 | 40 | 4.37623e+09 | 7.72999e+06 | 9.05405 | 39.5917 | 9.13423 | 0.0247595 | 0.0788563 | 0.000545196 | 1(Win) |
| simdjson (ondemand) | 372.335 | 0.129285 | 8339.65ms | 4525119 | 30 | 6.73616e+09 | 1.15903e+07 | 13.5845 | 58.6795 | 10.4759 | 0.0418058 | 0.0956318 | 0.00141556 | 2(Loss) |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1255.8 | 1.02303 | 5029.06ms | 4203059 | 40 | 4.26507e+10 | 3.19187e+06 | 4.02164 | 17.5545 | 3.10616 | 0.0128301 | 0.0898085 | 0.000610496 | 1(Win) |
| simdjson (ondemand) | 938.507 | 0.140568 | 6703.33ms | 4203059 | 30 | 1.0813e+09 | 4.27098e+06 | 5.38406 | 18.568 | 3.52795 | 0.0335341 | 0.0875602 | 0.000917181 | 2(Loss) |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 786.356 | 0.523502 | 7912.33ms | 4203059 | 80 | 5.69665e+10 | 5.09737e+06 | 6.43376 | 29.2325 | 5.91312 | 0.0204037 | 0.0891836 | 0.000796851 | 1(Win) |
| simdjson (ondemand) | 686.84 | 0.621522 | 4194.43ms | 4203059 | 40 | 5.26252e+10 | 5.83593e+06 | 7.36339 | 29.0551 | 5.23648 | 0.0378849 | 0.087425 | 0.000368666 | 2(Loss) |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1059.29 | 1.10116 | 5934.71ms | 4203058 | 30 | 5.20861e+10 | 3.78398e+06 | 4.8034 | 20.2953 | 3.93803 | 0.0148702 | 0.0893734 | 0.00100302 | 1(Win) |
| simdjson (ondemand) | 777.315 | 0.1131 | 8049.69ms | 4203058 | 30 | 1.02043e+09 | 5.15666e+06 | 6.48426 | 22.8583 | 4.41242 | 0.0348958 | 0.103969 | 0.00471689 | 2(Loss) |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 712.006 | 0.0870061 | 4092.95ms | 4203058 | 30 | 7.19754e+08 | 5.62965e+06 | 7.08406 | 31.9733 | 6.74499 | 0.0220325 | 0.0894378 | 0.00348167 | 1(Win) |
| simdjson (ondemand) | 594.685 | 0.693058 | 4806.07ms | 4203058 | 30 | 6.54663e+10 | 6.74029e+06 | 8.49081 | 33.3453 | 6.12096 | 0.0392472 | 0.103488 | 0.00542434 | 2(Loss) |

----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1808.18 | 0.171458 | 7331.23ms | 4197496 | 30 | 4.32246e+08 | 2.21385e+06 | 2.77141 | 14.9515 | 2.59258 | 0.000490769 | 0.0819775 | 0.000115505 | 1(Win) |
| simdjson (ondemand) | 1499.03 | 1.13945 | 4130.6ms | 4197496 | 40 | 3.70346e+10 | 2.67042e+06 | 3.36521 | 15.6407 | 2.55432 | 0.00700926 | 0.0810028 | 6.74628e-05 | 2(Loss) |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 727.064 | 0.0503548 | 8483.9ms | 4197496 | 40 | 3.07452e+08 | 5.50576e+06 | 6.94364 | 32.4371 | 6.09653 | 0.0223358 | 0.0816818 | 0.00035863 | 1(Win) |
| jsonifier (generic) | 677.526 | 0.307142 | 4199.25ms | 4197496 | 40 | 1.31725e+10 | 5.90832e+06 | 7.3869 | 38.9529 | 7.24938 | 0.00104448 | 0.0827617 | 0.000744986 | 2(Loss) |

----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1560.1 | 0.887452 | 4016.43ms | 4197495 | 80 | 4.14816e+10 | 2.56589e+06 | 3.1948 | 17.6168 | 3.41476 | 0.000534697 | 0.084677 | 6.11168e-05 | 1(Win) |
| simdjson (ondemand) | 1109.69 | 0.924557 | 5508.66ms | 4197495 | 40 | 4.4494e+10 | 3.60734e+06 | 4.54602 | 20.3751 | 3.53935 | 0.00731597 | 0.10376 | 0.000390137 | 2(Loss) |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 684.217 | 0.253804 | 4179.84ms | 4197495 | 30 | 6.61472e+09 | 5.85054e+06 | 7.26678 | 38.1234 | 7.63976 | 0.00122246 | 0.0851557 | 8.98552e-05 | 1(Win) |
| simdjson (ondemand) | 623.449 | 0.272732 | 4588.81ms | 4197495 | 40 | 1.22662e+10 | 6.4208e+06 | 8.07113 | 37.1715 | 7.08158 | 0.0224467 | 0.103506 | 0.000486278 | 2(Loss) |

----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1464.13 | 0.748706 | 5188.7ms | 4506447 | 40 | 1.93192e+10 | 2.93531e+06 | 3.41691 | 15.4778 | 2.74814 | 0.0085496 | 0.0806662 | 0.000255379 | 1(Win) |
| simdjson (ondemand) | 1187.23 | 0.103972 | 6277.87ms | 4506447 | 80 | 1.13324e+09 | 3.61991e+06 | 4.24354 | 16.5892 | 3.06881 | 0.0121454 | 0.0790635 | 0.000242883 | 2(Loss) |

----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 717.885 | 0.340575 | 4544.57ms | 4506447 | 30 | 1.24711e+10 | 5.98659e+06 | 6.99932 | 33.1608 | 6.402 | 0.0122741 | 0.0813041 | 0.000550515 | 1(Win) |
| simdjson (ondemand) | 475.133 | 0.129544 | 6696.68ms | 4506447 | 30 | 4.11901e+09 | 9.04522e+06 | 10.5812 | 47.7837 | 9.10522 | 0.0158271 | 0.0797535 | 0.00101569 | 2(Loss) |

----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1378.1 | 0.135638 | 5501.43ms | 4506446 | 40 | 7.15693e+08 | 3.11855e+06 | 3.65218 | 17.5952 | 3.38775 | 0.00837611 | 0.0809747 | 0.000226154 | 1(Win) |
| simdjson (ondemand) | 981.62 | 0.593639 | 7360.7ms | 4506446 | 80 | 5.40401e+10 | 4.37815e+06 | 5.13481 | 19.9756 | 3.77335 | 0.0121309 | 0.0880346 | 0.000271844 | 2(Loss) |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 718.885 | 0.689986 | 4558.91ms | 4506446 | 40 | 6.80597e+10 | 5.97826e+06 | 6.99582 | 32.0688 | 6.64139 | 0.0122879 | 0.0814282 | 0.000660376 | 1(Win) |
| simdjson (ondemand) | 441.075 | 0.399322 | 7231.7ms | 4506446 | 30 | 4.54162e+10 | 9.74365e+06 | 11.4234 | 51.1698 | 9.80966 | 0.0159612 | 0.0885604 | 0.000645742 | 2(Loss) |

----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1991.76 | 1.92047 | 6975.71ms | 4219120 | 30 | 4.5155e+10 | 2.02015e+06 | 2.5329 | 9.19035 | 1.48442 | 0.0119152 | 0.0567208 | 4.94416e-05 | 1(Win) |
| simdjson (ondemand) | 1886.23 | 0.106504 | 7424.08ms | 4219120 | 160 | 8.25861e+08 | 2.13317e+06 | 2.64765 | 8.88317 | 1.45989 | 0.0158578 | 0.0546251 | 0.0013334 | 2(Loss) |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 709.975 | 0.333554 | 4137.35ms | 4219120 | 30 | 1.07204e+10 | 5.66734e+06 | 7.11842 | 28.091 | 5.18403 | 0.0184854 | 0.057641 | 0.00671251 | 1(Win) |
| simdjson (ondemand) | 219.908 | 0.222679 | 5569.66ms | 4219120 | 30 | 4.98016e+10 | 1.82971e+07 | 22.7158 | 81.4408 | 16.4505 | 0.138485 | 0.0566298 | 0.00239261 | 2(Loss) |

----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 1807.11 | 0.234399 | 7673.4ms | 4219119 | 40 | 1.08954e+09 | 2.22657e+06 | 2.77439 | 10.4847 | 1.87313 | 0.0129763 | 0.05675 | 0.000281996 | 1(Win) |
| simdjson (ondemand) | 1601.39 | 0.168343 | 4141.78ms | 4219119 | 40 | 7.15647e+08 | 2.51261e+06 | 3.13329 | 10.9215 | 1.88232 | 0.0169884 | 0.0570183 | 0.00111866 | 2(Loss) |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (generic) | 722.035 | 0.100399 | 4098.4ms | 4219119 | 40 | 1.25211e+09 | 5.57267e+06 | 7.00512 | 27.3797 | 5.32209 | 0.0186336 | 0.058245 | 0.00910325 | 1(Win) |
| simdjson (ondemand) | 216.053 | 0.128682 | 5671.64ms | 4219119 | 30 | 1.723e+10 | 1.86235e+07 | 23.1824 | 83.4784 | 16.8727 | 0.140424 | 0.0588441 | 0.0178972 | 2(Loss) |
